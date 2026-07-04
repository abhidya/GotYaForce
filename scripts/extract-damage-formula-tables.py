#!/usr/bin/env python3
"""Extract every float table consumed by the base-damage formula zz_003cd5c_
(@0x8003cd5c, chunk_0004.c:6672-6828). See behavior-notes.md (ah).

Table roles (attacker side / defender side, hero-flag selects set [0] or [1]):
  PTR_DAT_804335e0[2]  -> f32[32]  attack scale by side rank byte (PTR_DAT_80433950[side])
  PTR_PTR_804335e8[2]  -> ptr[N] -> f32[32]  attacker HP-ratio curves (record u8 +0x06)
  PTR_PTR_804335f0[2]  -> ptr[N] -> f32[32]  attacker force-gauge curves (record u8 +0x07)
  PTR_DAT_804335f8[2]  -> f32[..] attack handicap by actor+0x43a
  PTR_PTR_80433600[2]  -> ptr[N] -> f32[32]  defense rank curves (pl data u8 +0x9c) x side rank
  PTR_PTR_80433608[2]  -> ptr[N] -> f32[32]  defender HP-ratio curves (pl data u8 +0x9d)
  PTR_PTR_80433610[2]  -> ptr[N] -> f32[32]  defender force-gauge curves (pl data u8 +0x9e)
  PTR_DAT_80433618[2]  -> f32[..] defense handicap by actor+0x43a
  DAT_802c7ca0         -> f32[..] combo-rank damage scale (victim+0x6ca), skipped when flagsB&0x4000
Scalars: FLOAT_80436f68 gate, 80436f78 (1.0), 80436f7c (0.5), 80436f9c, 80437024
(same-team), 80437028 (block divisor).
Challenge side rank bytes: PTR_DAT_80433950[0/1] = DAT_804356e4[diff*2 +0/+1]
(chunk_0048.c:404-405) = (0,31),(10,5),(28,4).
"""
import json
import struct
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
DOL = Path(r"D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol")
ROOT = Path(r"D:\GotYaForce\user-data\GG4E\afs_data\root")
OUT = REPO / "research" / "decomp" / "data" / "damage-formula-tables-804335e0.json"

data = DOL.read_bytes()
offs = struct.unpack(">18I", data[0:72])
addrs = struct.unpack(">18I", data[72:144])
sizes = struct.unpack(">18I", data[144:216])
SECS = [(offs[i], addrs[i], sizes[i]) for i in range(18) if sizes[i] > 0]


def rd(vaddr, n):
    for o, a, s in SECS:
        if a <= vaddr < a + s:
            return data[o + (vaddr - a): o + (vaddr - a) + n]
    raise ValueError(hex(vaddr))


def u32s(vaddr, n):
    return list(struct.unpack(f">{n}I", rd(vaddr, n * 4)))


def f32s(vaddr, n):
    return [round(v, 6) for v in struct.unpack(f">{n}f", rd(vaddr, n * 4))]


def curve_sets(base, n_curves):
    sets = []
    for p in u32s(base, 2):
        ptrs = u32s(p, n_curves)
        sets.append({"ptr": f"0x{p:08x}", "curves": [f32s(cp, 32) for cp in ptrs]})
    return sets


N_CURVES = 8  # dump the first 8 curve pointers per set; selector bytes observed are small

out = {
    "provenance": {
        "extractor": "scripts/extract-damage-formula-tables.py",
        "consumer": "zz_003cd5c_ @0x8003cd5c (chunk_0004.c:6672-6828); see behavior-notes.md (ah)",
    },
    "scalars": {
        "gate_80436f68": f32s(0x80436F68, 1)[0],
        "one_80436f78": f32s(0x80436F78, 1)[0],
        "half_80436f7c": f32s(0x80436F7C, 1)[0],
        "pairNerf_80436f9c": f32s(0x80436F9C, 1)[0],
        "sameTeam_80437024": f32s(0x80437024, 1)[0],
        "blockDiv_80437028": f32s(0x80437028, 1)[0],
    },
    "attackRankBySideRank_804335e0": [
        {"ptr": f"0x{p:08x}", "values": f32s(p, 32)} for p in u32s(0x804335E0, 2)
    ],
    "attackerHpCurves_804335e8": curve_sets(0x804335E8, N_CURVES),
    "attackerForceCurves_804335f0": curve_sets(0x804335F0, N_CURVES),
    "attackHandicap_804335f8": [
        {"ptr": f"0x{p:08x}", "values": f32s(p, 16)} for p in u32s(0x804335F8, 2)
    ],
    "defenseRankCurves_80433600": curve_sets(0x80433600, N_CURVES),
    "defenderHpCurves_80433608": curve_sets(0x80433608, N_CURVES),
    "defenderForceCurves_80433610": curve_sets(0x80433610, N_CURVES),
    "defenseHandicap_80433618": [
        {"ptr": f"0x{p:08x}", "values": f32s(p, 16)} for p in u32s(0x80433618, 2)
    ],
    "comboRankScale_802c7ca0": f32s(0x802C7CA0, 16),
    "challengeSideRankBytes_804356e4": {
        "normal": list(rd(0x804356E4, 2)),
        "tuff": list(rd(0x804356E6, 2)),
        "insane": list(rd(0x804356E8, 2)),
    },
}

# defense curve selector bytes per borg (pl data +0x9c/+0x9d/+0x9e)
sel = {}
for p in sorted(ROOT.glob("pl????data.bin")):
    raw = p.read_bytes()
    sel[p.name[:6]] = [raw[0x9C], raw[0x9D], raw[0x9E]]
out["defenseCurveSelectors_pldata_9c9d9e"] = sel

OUT.write_text(json.dumps(out, indent=1))
print("scalars:", out["scalars"])
print("attackRank[0][:8]:", out["attackRankBySideRank_804335e0"][0]["values"][:8])
print("attackRank[0][28..31]:", out["attackRankBySideRank_804335e0"][0]["values"][28:32])
print("atkHpCurve set0 curve0[:8]:", out["attackerHpCurves_804335e8"][0]["curves"][0][:8])
print("combo:", out["comboRankScale_802c7ca0"])
print("selectors pl0615:", sel.get("pl0615"))
print("wrote", OUT)
