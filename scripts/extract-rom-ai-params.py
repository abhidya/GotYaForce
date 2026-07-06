#!/usr/bin/env python3
"""Extract the CPU AI's DERIVED parameter set from boot.dol (cpu-ai-decode-2026-07-06.md).

- retarget cadence DAT_802cfaf4 (8 u16)
- idle-duration tables (&PTR_u_VTRPNLJ_802cb2f0)[tier] rows [level*8 + rand&7] (6 ptrs x 4 levels x 8)
- second cadence (&PTR_DAT_802cc138)[tier] -> +0x320
- range/steering constants (FLOAT_80436df8..FLOAT_80436eb8)
- per-borg attack-slot RANGES (descriptor +0xf0..+0x104 f32) + params (+0x10e..+0x113 u8)
  — the floats are the zz_002347c_ queue-range arguments (evidence: chunk_0002.c:7284-7288
  passes +0x104 as the 0x400/X queue range). The roulette WEIGHTING itself is not decoded;
  only the ranges/params are DERIVED here.

Output: packages/combat/src/data/romAiParams.json
"""
import json, os, struct, sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "research", "decomp"))
from dol import read_u32, read_f32, addr_to_off, data  # noqa: E402

def u16(addr):
    off = addr_to_off(addr)
    return struct.unpack(">H", data[off:off+2])[0]

retarget = [u16(0x802CFAF4 + i * 2) for i in range(8)]
assert retarget == [4, 8, 10, 12, 15, 30, 45, 60], retarget

def cadence_family(base_ptr_addr):
    ptrs = [read_u32(base_ptr_addr + i * 4) for i in range(6)]
    tables = {}
    for p in ptrs:
        if hex(p) in tables:
            continue
        rows = [[u16(p + (lvl * 8 + k) * 2) for k in range(8)] for lvl in range(4)]
        tables[hex(p)] = rows
    return {"tierPointers": [hex(p) for p in ptrs], "tables": tables}

idle = cadence_family(0x802CB2F0)
cad2 = cadence_family(0x802CC138)
# spot-validate the doc's quoted rows
assert idle["tables"]["0x802ca4f0"][0] == [86, 84, 82, 80, 78, 76, 74, 0], idle["tables"]["0x802ca4f0"][0]
assert cad2["tables"]["0x802cb338"][1] == [180, 181, 182, 183, 184, 185, 186, 187], cad2["tables"]["0x802cb338"][1]

constants = {
    "wakeRadiusSq_80436df8": read_f32(0x80436DF8),
    "xPressRange_80436e10": read_f32(0x80436E10),
    "probeStep_80436e20": read_f32(0x80436E20),
    "borgRange800_80436e28": read_f32(0x80436E28),
    "stickMagnitude_80436e60": read_f32(0x80436E60),
    "airborneY_80436e84": read_f32(0x80436E84),
    "searchRadiusSq_80436e88": read_f32(0x80436E88),
    "allyBlockRadius_80436e9c": read_f32(0x80436E9C),
    "stickScaleMode1_80436ea4": read_f32(0x80436EA4),
    "borgRange1200_80436ea8": read_f32(0x80436EA8),
    "borgRange600_80436eb8": read_f32(0x80436EB8),
}
assert constants["xPressRange_80436e10"] == 1000.0
assert constants["searchRadiusSq_80436e88"] == 4e8

CMT = json.load(open(os.path.join(ROOT, "packages/combat/src/data/commandMoveTables.json"), encoding="utf-8"))
borgs = {}
for bid, b in sorted(CMT["borgs"].items()):
    desc = int(b["commandStructAddress"], 16)
    off = addr_to_off(desc)
    if off is None:
        borgs[bid] = {"descriptor": hex(desc), "error": "descriptor not DOL-mapped"}
        continue
    ranges = [read_f32(desc + 0xF0 + i * 4) for i in range(6)]
    params = [data[addr_to_off(desc + 0x10E) + i] for i in range(6)]
    borgs[bid] = {"descriptor": hex(desc), "attackRanges": ranges, "attackParams": params}

nonzero = sum(1 for v in borgs.values() if "attackRanges" in v and any(r for r in v["attackRanges"]))
out = {
    "_meta": {
        "generatedBy": "scripts/extract-rom-ai-params.py",
        "date": "2026-07-06",
        "source": "cpu-ai-decode-2026-07-06.md (all addresses DERIVED there); ranges/params via commandMoveTables commandStructAddress (+0xf0/+0x10e)",
        "honest": "attackRanges are the zz_002347c_ queue-range floats per attack slot; the roulette WEIGHTING itself (zz_0021f7c_/FUN_80022b80 slice logic) is NOT decoded — consumers must not present slot ranges as probabilities",
        "borgsWithRanges": nonzero,
    },
    "retargetFrames": retarget,
    "idleCadence": idle,
    "cadence2": cad2,
    "constants": constants,
    "borgs": borgs,
}
dst = os.path.join(ROOT, "packages/combat/src/data/romAiParams.json")
json.dump(out, open(dst, "w", encoding="utf-8"), indent=1)
print(f"borgs: {len(borgs)} | with nonzero ranges: {nonzero}")
print("idle lvl0 row @802ca4f0:", idle["tables"]["0x802ca4f0"][0])
print("wrote", dst)
