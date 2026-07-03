#!/usr/bin/env python3
"""Extract per-borg core combat stat sources proven by the decomp.

Sources (research/decomp/ghidra-export):
  1. HP/stat rows — zz_0055f90_ @0x80055f90 (chunk_0006.c:8169-8232):
       row = (&PTR_DAT_802f2988)[familyByte(obj+0x3e8)]
             + ((obj+0x3ee) + (obj+0x3e9 variant)*0x14 + DAT_804339e8[obj+0x3ec level]) * 0x12
       u16 row[0] = max HP (written to +0x1c4/+0x1c6/+0x1c8).
     The same row's +2/+4/+6.. feed ammo/charge fields +0x774/+0x776/+0x78c/+0x790
     (chunk_0007.c:60-94).
  2. Gauge init — chunk_0007.c:47-52: actor-data page (obj+0x4ac, the borg's
     pl####data.bin) u16[0] -> balance-gauge max (+0x6be/+0x6c2), u16[1] ->
     down-gauge base (+0x6c6/+0x6c4). Also u16@0xa8 -> +0x59c state bits,
     u32@0x98 -> +0x204/+0x208.
  3. Damage records — 0x18-stride tables consumed by
     resolve_hitbox_target_effects_and_damage/zz_003cd5c_: borg family table
     DAT_802d46e0 (9 records), generic/comhit table DAT_802c4760.

Outputs:
  research/decomp/data/borg-hp-stat-rows-802f2988.json
  research/decomp/data/damage-records-802d46e0.json
  research/decomp/data/borg-gauge-init-pldata.json
"""
import json
import struct
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
DOL = Path(r"D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol")
ROOT = Path(r"D:\GotYaForce\user-data\GG4E\afs_data\root")
OUTDIR = REPO / "research" / "decomp" / "data"

data = DOL.read_bytes()
offs = struct.unpack(">18I", data[0:72])
addrs = struct.unpack(">18I", data[72:144])
sizes = struct.unpack(">18I", data[144:216])
SECS = [(offs[i], addrs[i], sizes[i]) for i in range(18) if sizes[i] > 0]


def rd(vaddr: int, n: int) -> bytes:
    for o, a, s in SECS:
        if a <= vaddr < a + s:
            return data[o + (vaddr - a): o + (vaddr - a) + n]
    raise ValueError(f"vaddr 0x{vaddr:08x} unmapped")


def u32s(vaddr: int, n: int):
    return list(struct.unpack(f">{n}I", rd(vaddr, n * 4)))


# Borg ids present in the exported roster (family/variant span).
borg_ids = sorted(p.name[:6] for p in ROOT.glob("pl????data.bin"))
fam_variants = {}
for bid in borg_ids:
    fam = int(bid[2:4], 16)
    var = int(bid[4:6], 16)
    fam_variants[fam] = max(fam_variants.get(fam, -1), var)

# 1) family stat-table pointers.
n_fams = max(fam_variants) + 1
fam_ptrs = u32s(0x802F2988, n_fams)
level_offsets = list(struct.unpack(">16b", rd(0x804339E8, 16)))

ROWS_PER_VARIANT = 0x14
ROW_SIZE = 0x12
hp_tables = {}
for fam, max_var in sorted(fam_variants.items()):
    ptr = fam_ptrs[fam]
    if ptr == 0:
        continue
    fam_rows = {}
    for var in range(max_var + 1):
        base = ptr + var * ROWS_PER_VARIANT * ROW_SIZE
        rows = []
        for r in range(ROWS_PER_VARIANT):
            raw = rd(base + r * ROW_SIZE, ROW_SIZE)
            vals = struct.unpack(">9H", raw)
            rows.append(list(vals))
        fam_rows[f"{var:02x}"] = rows
    hp_tables[f"{fam:02x}"] = {"ptr": f"0x{ptr:08x}", "variants": fam_rows}

(OUTDIR / "borg-hp-stat-rows-802f2988.json").write_text(json.dumps({
    "provenance": {
        "extractor": "scripts/extract-borg-stat-tables.py",
        "reader": "zz_0055f90_ @0x80055f90 (chunk_0006.c:8169-8232); ammo/charge reader chunk_0007.c:60-94",
        "index": "row = subIdx(+0x3ee) + variant(+0x3e9)*0x14 + DAT_804339e8[level(+0x3ec)]; row stride 0x12, values dumped as 9 big-endian u16s",
        "fields": "u16[0]=maxHP (+0x1c4/6/8); u16[1]/u16[2]=ammo-type/count feeds (+0x774/+0x776); u16[3..4]=charge feed (+0x78c/+0x790 pair)",
        "levelOffsetTable_DAT_804339e8": level_offsets,
    },
    "familyPointers": [f"0x{p:08x}" for p in fam_ptrs],
    "tables": hp_tables,
}, indent=1))

# 2) damage records.
def dmg_records(vaddr: int, count: int):
    recs = []
    for i in range(count):
        raw = rd(vaddr + i * 0x18, 0x18)
        hp, down = struct.unpack(">HH", raw[0:4])
        recs.append({
            "index": i,
            "hpDamage": hp,
            "downGaugeDamage": down,
            "balanceGaugeDamage": raw[4],
            "comboScoreValue": raw[5],
            "attackerHpCurveIndex": raw[6],
            "forceGaugeCurveIndex": raw[7],
            "hitStrength": raw[8],
            "impactEffectId": raw[9],
            "unknown0a": raw[0x0A],
            "reactionFlags": raw[0x0B],
            "unknown0c": raw[0x0C],
            "reactionAnimVariant": raw[0x0D],
            "knockbackDirMode": struct.unpack(">b", raw[0x0E:0x0F])[0],
            "unknown0f": raw[0x0F],
            "flagsA": struct.unpack(">H", raw[0x10:0x12])[0],
            "flagsB": struct.unpack(">H", raw[0x12:0x14])[0],
            "knockbackYawTrim": struct.unpack(">b", raw[0x14:0x15])[0],
            "knockbackPitchTrim": struct.unpack(">b", raw[0x15:0x16])[0],
            "rehitIntervalFrames": struct.unpack(">b", raw[0x16:0x17])[0],
            "unknown17": raw[0x17],
        })
    return recs

(OUTDIR / "damage-records-802d46e0.json").write_text(json.dumps({
    "provenance": {
        "extractor": "scripts/extract-borg-stat-tables.py",
        "consumers": "resolve_hitbox_target_effects_and_damage @0x8002e2a8 (chunk_0003.c:7473+), zz_003cd5c_ @0x8003cd5c (chunk_0004.c:6667+)",
        "binding": "borg family: actor+0x27c = DAT_802d46e0 via zz_0072048_ @0x80072048 (chunk_0010.c:139); generic/comhit: DAT_802c4760 (chunk_0013.c:1453). Hitbox record u16 +0x04 indexes this table.",
        "fieldEvidence": "see hit-bin agent census: chunk_0004.c:6693 (+0x00), chunk_0003.c:7541/8002 (+0x02), :8011-8019 (+0x04), :8021-8030 (+0x05), chunk_0004.c:6730/6738 (+0x06/+0x07), chunk_0003.c:7623 (+0x08), :8087 (+0x09), :7524/7636 (+0x0b), :7637 (+0x0d), :7945 (+0x0e), :7520-7885 (flagsA), :7538-7745 (flagsB), knockback-direction-800300bc.json (+0x14/+0x15), chunk_0013.c:1173 (+0x16)",
    },
    "borgFamily_802d46e0": dmg_records(0x802D46E0, 9),
    "generic_802c4760": dmg_records(0x802C4760, 12),
}, indent=1))

# 3) per-borg gauge init words from pl####data.bin.
gauges = {}
for bid in borg_ids:
    raw = (ROOT / f"{bid}data.bin").read_bytes()
    balance, down = struct.unpack(">HH", raw[0:4])
    gauges[bid] = {
        "balanceGaugeMax": balance,
        "downGaugeBase": down,
        "u32_98": struct.unpack(">I", raw[0x98:0x9C])[0],
        "stateBits_a8": struct.unpack(">H", raw[0xA8:0xAA])[0],
        "stateBits_aa": struct.unpack(">H", raw[0xAA:0xAC])[0],
    }

(OUTDIR / "borg-gauge-init-pldata.json").write_text(json.dumps({
    "provenance": {
        "extractor": "scripts/extract-borg-stat-tables.py",
        "reader": "borg init chunk_0007.c:47-52: +0x6be/+0x6c2 (balance max/cur) = u16@0 of actor-data page (+0x4ac); +0x6c6/+0x6c4 (down cur/base) = u16@2; +0x59c=u16@0xa8; +0x204/+0x208=u32@0x98",
        "source": "user-data/GG4E/afs_data/root/pl####data.bin",
    },
    "borgs": gauges,
}, indent=1))

# quick correlation print
g = hp_tables.get("06", {}).get("variants", {}).get("15")
print("G RED (pl0615) stat rows 0..4:", g[:5] if g else None)
print("gauges pl0615:", gauges.get("pl0615"))
print("damage records[1..4]:", json.loads((OUTDIR / "damage-records-802d46e0.json").read_text())["borgFamily_802d46e0"][1:5])
print("level offsets:", level_offsets)
print("wrote 3 JSONs to", OUTDIR)
