#!/usr/bin/env python3
"""Extract the Power Burst fusion pair table DAT_802d352c from boot.dol.

See behavior-notes.md (aj) for the full corpus evidence. Summary:

  Pair table DAT_802d352c: indexed by FAMILY byte (actor+0x3e8), 4-byte pointer
  entries. HARD BOUND: exactly 17 entries (families 0-16, 0x802d352c..0x802d356c
  inclusive of the last entry at 0x802d356c). The next word at 0x802d3570 belongs
  to the already-confirmed 35-slot state-handler table (behavior-notes s4u) --
  reading "pairs" at index >= 17 overflows into CODE pointers, not data. This
  script asserts that overflow (proves the bound) and then stops.

  Only families 5 and 6 have non-null pair-list pointers: 0x802d3420 (family 5)
  and 0x802d3480 (family 6). Each of those is itself a per-VARIANT (actor+0x3e9)
  pointer table (`listPtr + variant*4`), confirmed here to run exactly up to the
  next known address (family5 list: 0x802d3420..0x802d3480, 24 words; family6
  list: 0x802d3480..0x802d352c, 43 words -- these bounds are address-adjacency
  confirmed, not symbol-named, since this region has no map symbols). Most
  variant slots are null; the non-null ones point to a further sub-list of
  (s16 partnerSpawnId, s16 resultSpawnId) entries, terminated by partnerId == -1.

  Spawn ids pack as family = id >> 8, variant = id & 0xff (behavior-notes (n)),
  rendered here as pl%04x strings and cross-checked against
  packages/assets/data/borgs.json.
"""
import json
import struct
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
DOL = Path(r"D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol")
BORGS_JSON = REPO / "packages" / "assets" / "data" / "borgs.json"
OUT = REPO / "research" / "decomp" / "data" / "fusion-pairs-802d352c.json"

PAIR_TABLE_ADDR = 0x802D352C
PAIR_TABLE_COUNT = 17  # HARD BOUND -- families 0-16. Do not read past this.
STATE_TABLE_ADDR = 0x802D3570  # 35-slot state-handler table; must NOT be read as pairs.

FAMILY_LIST_BOUNDS = {
    5: (0x802D3420, 0x802D3480),
    6: (0x802D3480, PAIR_TABLE_ADDR),
}

data = DOL.read_bytes()
offs = struct.unpack(">18I", data[0:72])
addrs = struct.unpack(">18I", data[72:144])
sizes = struct.unpack(">18I", data[144:216])
SECS = [(offs[i], addrs[i], sizes[i]) for i in range(18) if sizes[i] > 0]


def addr_to_off(vaddr):
    for o, a, s in SECS:
        if a <= vaddr < a + s:
            return o + (vaddr - a)
    raise ValueError(f"address 0x{vaddr:08x} not in any DOL section")


def rd(vaddr, n):
    o = addr_to_off(vaddr)
    return data[o : o + n]


def u32(vaddr):
    return struct.unpack(">I", rd(vaddr, 4))[0]


def s16(vaddr):
    return struct.unpack(">h", rd(vaddr, 2))[0]


def pl_id(spawn_id):
    family = (spawn_id >> 8) & 0xFF
    variant = spawn_id & 0xFF
    return family, variant, f"pl{family:02x}{variant:02x}"


# --- Load roster for cross-check --------------------------------------------------------

roster_ids = set()
if BORGS_JSON.exists():
    borgs_doc = json.loads(BORGS_JSON.read_text())
    roster_ids = {b["id"] for b in borgs_doc.get("borgs", [])}
else:
    raise SystemExit(f"roster file not found: {BORGS_JSON}")


def resolve(spawn_id):
    family, variant, name = pl_id(spawn_id)
    entry = {"spawnId": spawn_id, "family": family, "variant": variant, "plId": name}
    if name not in roster_ids:
        entry["nonRosterResult"] = True
    return entry


# --- 1. Dump the 17-entry pair table, bounded HARD at 17 --------------------------------

pair_table = []
for i in range(PAIR_TABLE_COUNT):
    addr = PAIR_TABLE_ADDR + i * 4
    ptr = u32(addr)
    pair_table.append({"family": i, "addr": f"0x{addr:08x}", "listPtr": f"0x{ptr:08x}" if ptr else None})

# Prove the HARD BOUND: the word immediately after the 17th entry must be the
# state-handler table's first entry (a CODE pointer, not a plausible data pointer
# for this table) -- fail loudly if that invariant doesn't hold.
if PAIR_TABLE_ADDR + PAIR_TABLE_COUNT * 4 != STATE_TABLE_ADDR:
    raise SystemExit(
        f"pair table bound mismatch: 17 entries from 0x{PAIR_TABLE_ADDR:08x} should end "
        f"exactly at STATE_TABLE_ADDR 0x{STATE_TABLE_ADDR:08x}, got "
        f"0x{PAIR_TABLE_ADDR + PAIR_TABLE_COUNT * 4:08x}"
    )
overflow_sample = [u32(STATE_TABLE_ADDR + i * 4) for i in range(3)]
if not all(0x80000000 <= v < 0x80200000 for v in overflow_sample):
    raise SystemExit(
        f"overflow-bound sanity check failed: expected the words at/after "
        f"0x{STATE_TABLE_ADDR:08x} to look like CODE pointers (text section), got "
        f"{[hex(v) for v in overflow_sample]} -- (aj)'s 17-entry bound may be wrong, "
        f"stop and re-verify before trusting this extraction."
    )

# Validate against (aj): only families 5 and 6 non-null, at the exact recorded addresses.
non_null = {e["family"]: e["listPtr"] for e in pair_table if e["listPtr"] is not None}
expected_non_null = {5: "0x802d3420", 6: "0x802d3480"}
if non_null != expected_non_null:
    raise SystemExit(
        f"pair table non-null entries do not match (aj): expected {expected_non_null}, "
        f"got {non_null}. Fix the extraction or update behavior-notes.md (aj) -- do not "
        f"silently accept a mismatch."
    )

# --- 2. Raw bytes for the whole 0x802d3420..0x802d352c region (the two per-variant pointer
#    arrays for families 5 and 6). NOTE: the pair SUB-LISTS these arrays point to live
#    elsewhere (family 5's sub-lists are in a separate 0x80433... rodata blob; family 6's
#    happen to sit just BEFORE this window, at 0x802d33f0..0x802d3420) -- captured
#    separately per sub-list below so every byte this script interprets is recorded raw.

raw_region_start = 0x802D3420
raw_region_end = PAIR_TABLE_ADDR
raw_region_bytes = rd(raw_region_start, raw_region_end - raw_region_start)

# --- 3. Parsed interpretation: per-family variant list -> pair sub-lists ----------------

families = {}
for family, (list_start, list_end) in FAMILY_LIST_BOUNDS.items():
    n_variants = (list_end - list_start) // 4
    variants = []
    for variant in range(n_variants):
        entry_addr = list_start + variant * 4
        sub_ptr = u32(entry_addr)
        if sub_ptr == 0:
            continue
        pairs = []
        i = 0
        while True:
            entry_addr2 = sub_ptr + i * 4
            partner = s16(entry_addr2)
            if partner == -1:
                break
            result = s16(entry_addr2 + 2)
            pairs.append(
                {
                    "partner": resolve(partner),
                    "result": resolve(result),
                }
            )
            i += 1
            if i > 64:
                raise SystemExit(
                    f"family {family} variant {variant} sub-list @0x{sub_ptr:08x} did not "
                    f"terminate (partner==-1) within 64 entries -- refusing to loop forever."
                )
        # Raw bytes for this exact sub-list, INCLUDING the terminating 0xffffffff word, so a
        # human can re-check the parse without trusting this script's arithmetic. Recorded
        # per-sub-list (rather than assuming one contiguous window) because family 5's and
        # family 6's sub-lists live in different, non-adjacent rodata regions -- see note above
        # raw_region_start.
        sub_list_byte_len = (len(pairs) + 1) * 4  # +1 word for the -1 terminator
        sub_list_raw = rd(sub_ptr, sub_list_byte_len)
        variants.append(
            {
                "variant": variant,
                "listEntryAddr": f"0x{entry_addr:08x}",
                "subListPtr": f"0x{sub_ptr:08x}",
                "pairCount": len(pairs),
                "pairs": pairs,
                "subListRawHex": sub_list_raw.hex(),
            }
        )
    families[str(family)] = {
        "familyByte": family,
        "listPtr": f"0x{list_start:08x}",
        "listWordCount": n_variants,
        "listBoundNote": (
            "bound is address-adjacency confirmed (next known table start), "
            "not symbol-named -- see module docstring"
        ),
        "nonNullVariantCount": len(variants),
        "variants": variants,
    }

if families["5"]["nonNullVariantCount"] == 0:
    raise SystemExit("family 5 pair list is empty -- expected non-empty per (aj)")
if families["6"]["nonNullVariantCount"] == 0:
    raise SystemExit("family 6 pair list is empty -- expected non-empty per (aj)")

# Families other than 5/6 must be null in the pair table (already validated above via
# expected_non_null, restated here for the JSON's own self-check record).
empty_families = sorted(f for f in range(PAIR_TABLE_COUNT) if f not in (5, 6))

# --- 4. Cross-check every referenced spawn id against the roster ------------------------

unknown_ids = []
for fam in families.values():
    for v in fam["variants"]:
        for pr in v["pairs"]:
            for role in ("partner", "result"):
                e = pr[role]
                if e.get("nonRosterResult"):
                    unknown_ids.append({"role": role, **e})

out = {
    "provenance": {
        "extractor": "scripts/gen_fusion_pairs.py",
        "citation": "research/decomp/behavior-notes.md (aj) Power Burst fusion system decoded",
        "readMethod": (
            "dol.py-style: DOL section table parsed directly from "
            "user-data/GG4E/disc/sys/boot.dol, addr_to_off()+struct.unpack for each read."
        ),
        "romConstant": "DAT_802d352c",
        "date": "2026-07-03",
    },
    "pairTable": {
        "addr": f"0x{PAIR_TABLE_ADDR:08x}",
        "hardBoundCount": PAIR_TABLE_COUNT,
        "hardBoundNote": (
            "17 entries only (families 0-16). The word at 0x802d3570 belongs to the "
            "35-slot state-handler table, NOT this table -- verified above by asserting "
            "the overflow words look like code pointers."
        ),
        "entries": pair_table,
        "emptyFamilies": empty_families,
        "nonNullFamilies": sorted(non_null.keys()),
    },
    "rawRegion": {
        "note": (
            "Raw bytes for the whole 0x802d3420..0x802d352c region: this is the two "
            "PER-VARIANT POINTER ARRAYS for families 5 and 6 (listPtr + variant*4), NOT the "
            "pair sub-lists themselves -- the sub-lists those pointers target live in "
            "separate, non-adjacent regions (family 5's in a 0x80433... rodata blob, family "
            "6's just BEFORE this window at 0x802d33f0..0x802d3420). Recorded verbatim per "
            "(aj)'s 'dump raw bytes... record both the raw hex AND your parsed "
            "interpretation' instruction. Each variant's actual pair sub-list raw bytes are "
            "recorded separately as families[*].variants[*].subListRawHex below."
        ),
        "start": f"0x{raw_region_start:08x}",
        "end": f"0x{raw_region_end:08x}",
        "hex": raw_region_bytes.hex(),
    },
    "families": families,
    "unknownIds": unknown_ids,
    "spawnIdPacking": {
        "formula": "family = spawnId >> 8; variant = spawnId & 0xff; plId = f'pl{family:02x}{variant:02x}'",
        "citation": "behavior-notes.md (n)",
    },
}

OUT.write_text(json.dumps(out, indent=1))

print("pair table non-null families:", sorted(non_null.keys()))
print("family 5: variants with pairs:", [v["variant"] for v in families["5"]["variants"]])
print("family 6: variants with pairs:", [v["variant"] for v in families["6"]["variants"]])
print("unknown (non-roster) ids:", unknown_ids if unknown_ids else "none")
print("wrote", OUT)
