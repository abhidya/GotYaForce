#!/usr/bin/env python3
"""Fleet-wide cue->state table extraction (48 rows x 2 bytes per family).

Reads every family ctor's cue-table address from actionStreamTables.json (the +0x4f0
binding recovered by gen-action-stream-tables.mjs's ctor emulation) and dumps the 96
bytes from boot.dol. Supersedes the 17-family lis+addi extractor for cue tables
(familyCueTables.json keeps its historical shape; this writes the full-fleet file).

Validation: hard-fails unless the two hand-verified dumps match byte-exact:
  - family 0 @0x802d3ff8  (nn-family-decode-2026-07-06.md §A11)
  - G RED    @0x80365cf8  (same doc; deltas at rows 5/8/25/26)

Output: packages/combat/src/data/familyCueTablesFull.json
  { _meta, families: { "<ctorAddr>": { cueTable, members, rows: [[fb,ub] x48] } } }
Rows are SIGNED bytes (-1 = no transition), matching bridge.ts Int8Array semantics.
"""
import json, os, struct, sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "research", "decomp"))
from dol import addr_to_off, data  # noqa: E402

AST = json.load(open(os.path.join(ROOT, "packages/combat/src/data/actionStreamTables.json"), encoding="utf-8"))

def s8(b):
    return b - 256 if b >= 128 else b

families = {}
unresolved = []
for borg_id, b in sorted(AST["borgs"].items()):
    ctor = b.get("constructorAddress")
    cue = b.get("cueTable")
    if ctor not in families:
        families[ctor] = {"cueTable": cue, "members": [], "rows": None}
    fam = families[ctor]
    fam["members"].append(borg_id)
    if fam["cueTable"] != cue:
        # Some ctors bind a DIFFERENT cue table per borg variant (borg-number switch
        # inside the ctor, same pattern as NEO G RED's +0x4e8 override). Store the
        # override per member; the base stays the first-seen table.
        fam.setdefault("memberOverrides", {})[borg_id] = {"cueTable": cue, "rows": None}

def dump_rows(cue_addr_hex):
    addr = int(cue_addr_hex, 16)
    off = addr_to_off(addr)
    if off is None:
        return None
    raw = data[off : off + 96]
    return [[s8(raw[i * 2]), s8(raw[i * 2 + 1])] for i in range(48)]

for ctor, fam in sorted(families.items()):
    cue = fam["cueTable"]
    if not cue:
        unresolved.append({"ctor": ctor, "reason": "no cueTable in actionStreamTables"})
        continue
    fam["rows"] = dump_rows(cue)
    if fam["rows"] is None:
        unresolved.append({"ctor": ctor, "reason": f"cueTable {cue} not DOL-mapped (bss/runtime)"})
    for borg_id, ov in (fam.get("memberOverrides") or {}).items():
        ov["rows"] = dump_rows(ov["cueTable"])
        if ov["rows"] is None:
            unresolved.append({"ctor": ctor, "reason": f"override {borg_id} cueTable {ov['cueTable']} not DOL-mapped"})

# --- hard validation against the two hand-verified dumps ---
def expect(ctor, row, fb, ub):
    got = families[ctor]["rows"][row]
    assert got == [fb, ub], f"{ctor} row {row}: got {got}, expected {[fb, ub]}"

# family 0 (0x8006f4f8) @0x802d3ff8
for r in range(18):
    if 9 <= r <= 11:
        expect("0x8006f4f8", r, 0, r + 1)
    else:
        expect("0x8006f4f8", r, r + 1, r + 1)
expect("0x8006f4f8", 35, 0, 0x2B)
expect("0x8006f4f8", 36, 0x2F, 0)
expect("0x8006f4f8", 43, 0, 0x3C)
expect("0x8006f4f8", 44, 0x3D, 0)
expect("0x8006f4f8", 45, 0x3D, 0)
expect("0x8006f4f8", 46, 0, 0x3E)
expect("0x8006f4f8", 47, 0, 0x3F)
# G RED (0x8018ccfc) @0x80365cf8 — the four deltas + shared rows
expect("0x8018ccfc", 5, 0x16, 0x16)
expect("0x8018ccfc", 8, 0x17, 0x17)
expect("0x8018ccfc", 25, 0, 0x1F)
expect("0x8018ccfc", 26, 0, 0x20)
expect("0x8018ccfc", 44, 0x3D, 0)
expect("0x8018ccfc", 45, 0x3D, 0)

resolved = {c: f for c, f in families.items() if f["rows"] is not None}
# attack-cue sanity census: how many families route cue 44 to state 61?
cue44_61 = sum(1 for f in resolved.values() if f["rows"][44][0] == 0x3D)
cue45_61 = sum(1 for f in resolved.values() if f["rows"][45][0] == 0x3D)

out = {
    "_meta": {
        "generatedBy": "scripts/extract-family-cue-tables-full.py",
        "date": "2026-07-06",
        "source": "boot.dol cue-table bytes at each ctor's +0x4f0 binding (actionStreamTables.json)",
        "validation": "family-0 + G RED dumps byte-exact vs nn-family-decode-2026-07-06.md §A11",
        "rowSemantics": "48 rows x [fullBodyState, upperBodyState], signed; -1 = no transition",
        "familiesResolved": len(resolved),
        "familiesUnresolved": len(unresolved),
        "cue44ToState61": cue44_61,
        "cue45ToState61": cue45_61,
    },
    "families": {c: f for c, f in sorted(families.items())},
    "unresolved": unresolved,
}
dst = os.path.join(ROOT, "packages/combat/src/data/familyCueTablesFull.json")
json.dump(out, open(dst, "w", encoding="utf-8"), indent=1)
print(f"families: {len(families)} | resolved: {len(resolved)} | unresolved: {len(unresolved)}")
print(f"cue44->61: {cue44_61}/{len(resolved)} | cue45->61: {cue45_61}/{len(resolved)}")
for u in unresolved:
    print("  UNRESOLVED:", u)
conflicts = {c: f["cueTableConflicts"] for c, f in families.items() if "cueTableConflicts" in f}
print("cueTable conflicts:", conflicts if conflicts else "none")
print("wrote", dst)
