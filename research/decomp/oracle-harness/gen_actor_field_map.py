#!/usr/bin/env python3
"""Extract the RomActor field<->offset map from packages/combat/src/rom/actor.ts
into research/decomp/oracle-harness/actor-field-map.json.

Phase 1 of the oracle workstream (research/tools/OGhidra/docs/
oracle-workstream-plan.md §3.3 D-3 + P1.0): `actor.ts` is the single source of
truth for the actor-struct layout; this generator parses its `@romfield` doc-tag
annotations and emits one record per TS field. The JSON is tracked, so actor.ts
drift shows up as a reviewable diff. A field without a tag extracts as
`kind: "unmapped"` — present, visible, and codec-refused (never guessed).

Annotation grammar (also documented at the top of actor.ts):

    @romfield <tsField> port_side
    @romfield <tsField> +0xNNN <kind>
    @romfield <tsField> +0xA <kind>, +0xB <kind>, ...      (tuple)
    @romfield <tsField> +0xBASE struct stride=0xSS count=N elem=<kind|Interface>

Kinds: u8 s8 u16 s16 u32 s32 f32 vec3 bam16 u16be ptr bytes[N]
  vec3  = three LE f32 at +0/+4/+8
  bam16 = u16 binary angle (encodes as u16)
  u16be = big-endian u16 — byte order preserved at the data boundary
  ptr   = u32 LE pointer

Interfaces scanned: RomActor, RomPartState (block-relative offsets),
RomWeaponAnimationParams, RomWeaponAnimationTiming.

Deterministic; re-run to regenerate:

    python research/decomp/oracle-harness/gen_actor_field_map.py

(Python >= 3.7; paths resolve from this file.)
"""

import hashlib
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
ACTOR_TS = os.path.join(ROOT, "packages", "combat", "src", "rom", "actor.ts")
OUT_PATH = os.path.join(HERE, "actor-field-map.json")

INTERFACES = [
    "RomActor",
    "RomPartState",
    "RomWeaponAnimationParams",
    "RomWeaponAnimationTiming",
]

SCALAR_KINDS = {
    "u8": 1, "s8": 1,
    "u16": 2, "s16": 2, "bam16": 2, "u16be": 2,
    "u32": 4, "s32": 4, "f32": 4, "ptr": 4,
    "vec3": 12,
}

TAG_RX = re.compile(r"@romfield\s+(\w+)\s+([^\n*]+)")
FIELD_RX = re.compile(r"^\s{2}(\w+)\??:\s")
BYTES_RX = re.compile(r"^bytes\[(0x[0-9a-fA-F]+|\d+)\]$")
STRUCT_RX = re.compile(
    r"^\+((?:0x)?[0-9a-fA-F]+)\s+struct\s+stride=((?:0x)?[0-9a-fA-F]+)"
    r"\s+count=(\d+)\s+elem=([\w\[\]0-9x]+)\s*$"
)
SCALAR_ITEM_RX = re.compile(r"^\+((?:0x)?[0-9a-fA-F]+)\s+([\w\[\]0-9x]+)$")


def parse_int(s):
    return int(s, 16) if s.lower().startswith("0x") else int(s, 10)


def kind_width(kind):
    if kind in SCALAR_KINDS:
        return SCALAR_KINDS[kind]
    m = BYTES_RX.match(kind)
    if m:
        return parse_int(m.group(1))
    return None


def parse_spec(field, spec):
    """Parse one @romfield spec string into a record dict (sans tsField)."""
    spec = spec.strip().rstrip("*/").strip()
    if spec == "port_side":
        return {"kind": "port_side"}
    m = STRUCT_RX.match(spec)
    if m:
        elem = m.group(4)
        rec = {
            "kind": "struct",
            "offset": parse_int("0x" + m.group(1) if not m.group(1).startswith("0x") else m.group(1)),
            "stride": parse_int(m.group(2)),
            "count": int(m.group(3)),
            "elem": elem,
        }
        w = kind_width(elem)
        if w is not None:
            rec["elem_width"] = w
        return rec
    items = [p.strip() for p in spec.split(",")]
    parsed = []
    for it in items:
        m = SCALAR_ITEM_RX.match(it)
        if not m:
            raise ValueError("unparseable @romfield spec for %s: %r" % (field, spec))
        off = m.group(1)
        kind = m.group(2)
        w = kind_width(kind)
        if w is None:
            raise ValueError("unknown kind %r in @romfield for %s" % (kind, field))
        parsed.append({"offset": parse_int(off if off.startswith("0x") else "0x" + off),
                       "kind": kind, "width": w})
    if len(parsed) == 1:
        return parsed[0]
    return {"kind": "tuple", "elems": parsed}


def extract_interface(src, name):
    """Return (tags, declared_fields) for one interface body, in source order."""
    start_rx = re.compile(r"^export interface %s\b.*\{" % re.escape(name), re.M)
    m = start_rx.search(src)
    if not m:
        raise SystemExit("interface %s not found in actor.ts" % name)
    depth = 0
    i = m.end() - 1
    for j in range(i, len(src)):
        if src[j] == "{":
            depth += 1
        elif src[j] == "}":
            depth -= 1
            if depth == 0:
                body = src[m.end():j]
                break
    else:
        raise SystemExit("unbalanced braces for interface %s" % name)
    tags = {}
    order = []
    for tm in TAG_RX.finditer(body):
        field = tm.group(1)
        if field in tags:
            raise SystemExit("duplicate @romfield tag for %s.%s" % (name, field))
        tags[field] = tm.group(2)
        order.append(field)
    declared = []
    for line in body.splitlines():
        fm = FIELD_RX.match(line)
        if fm and not line.lstrip().startswith("*"):
            declared.append(fm.group(1))
    return tags, declared


def main():
    with open(ACTOR_TS, "rb") as f:
        raw = f.read()
    # Normalize line endings before hashing: the binding must survive CRLF
    # checkouts (run-unit.mjs verifies this sha at harness load and refuses drift).
    raw = raw.replace(b"\r\n", b"\n")
    src = raw.decode("utf-8")
    out = {
        "generated_by": "research/decomp/oracle-harness/gen_actor_field_map.py",
        "map_schema": 1,
        "source": "packages/combat/src/rom/actor.ts",
        "source_sha256": hashlib.sha256(raw).hexdigest(),
        "interfaces": {},
    }
    unmapped_total = 0
    for iface in INTERFACES:
        tags, declared = extract_interface(src, iface)
        stray = sorted(set(tags) - set(declared))
        if stray:
            raise SystemExit("@romfield tags without a declared field in %s: %s" % (iface, stray))
        fields = []
        for field in declared:
            if field in tags:
                rec = parse_spec(field, tags[field])
                rec["tsField"] = field
            else:
                rec = {"tsField": field, "kind": "unmapped"}
                unmapped_total += 1
            fields.append(rec)
        out["interfaces"][iface] = {"fields": fields}
    with open(OUT_PATH, "w", encoding="utf-8", newline="\n") as f:
        json.dump(out, f, indent=1)
        f.write("\n")
    n_fields = sum(len(v["fields"]) for v in out["interfaces"].values())
    sys.stdout.write("actor-field-map.json: %d fields across %d interfaces, %d unmapped\n"
                     % (n_fields, len(INTERFACES), unmapped_total))


if __name__ == "__main__":
    main()
