#!/usr/bin/env python3
"""Extract the Challenge-mode static tables from the GG4E boot.dol.

Source functions (research/decomp/ghidra-export/chunk_0048.c):
  - poll_challenge_menu_selection @0x80196030: battle count `(&DAT_804356d0)[difficulty]`,
    energy limit `*(u32*)(&DAT_8036f554 + difficulty*4)` -> PTR_DAT_80433934+0x120.
  - build_challenge_battle_setup @0x801962c4: per-difficulty per-battle CPU team gen inputs
      local_60[2] = (&PTR_DAT_8036f40c)[difficulty][battleIdx]   (side-0 CPU ally count)
      local_60[3] = (&PTR_DAT_8036f434)[difficulty][battleIdx]   (side-1 enemy count)
      local_60[0] = *(int*)((&PTR_DAT_8036f4b8)[difficulty] + battleIdx*4) (side-0 budget)
      local_60[1] = *(int*)((&PTR_DAT_8036f53c)[difficulty] + battleIdx*4) (side-1 budget)
      pool ids:  (&PTR_DAT_8036f360)[difficulty][battleIdx*4 + rand%4]  (side 0)
                 (&PTR_DAT_8036f3e4)[difficulty][battleIdx*4 + rand%4]  (side 1)
      (pool id -> borg-id list lives in research/decomp/data/spawn-pools-80380804.json)
  - zz_0196dac_ @0x80196dac: stage rotation `(&DAT_8036f548)[rand%11]`, reroll while equal
    to previous stage byte at PTR_DAT_80433934[0x1c].
  - per-difficulty extras DAT_804356e4 pairs and DAT_804356ec side values.

Output: research/decomp/data/challenge-battle-tables-8036f360.json
"""
import json
import struct
import sys
from pathlib import Path

DOL = Path(r"D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol")
OUT = Path(__file__).resolve().parent.parent / "research" / "decomp" / "data" / "challenge-battle-tables-8036f360.json"

data = DOL.read_bytes()
offs = struct.unpack(">18I", data[0:72])
addrs = struct.unpack(">18I", data[72:144])
sizes = struct.unpack(">18I", data[144:216])
SECS = [(offs[i], addrs[i], sizes[i]) for i in range(18) if sizes[i] > 0]


def rd(vaddr: int, n: int) -> bytes:
    for o, a, s in SECS:
        if a <= vaddr < a + s:
            return data[o + (vaddr - a): o + (vaddr - a) + n]
    raise ValueError(f"vaddr 0x{vaddr:08x} not in any DOL section (bss?)")


def u32s(vaddr: int, n: int):
    return list(struct.unpack(f">{n}I", rd(vaddr, n * 4)))


def s8s(vaddr: int, n: int):
    return list(struct.unpack(f">{n}b", rd(vaddr, n)))


BATTLE_COUNTS = s8s(0x804356D0, 3)  # per difficulty (NORMAL, TUFF, INSANE)
ENERGY_LIMITS = u32s(0x8036F554, 3)
STAGE_POOL = list(rd(0x8036F548, 11))

count_ptrs_side0 = u32s(0x8036F40C, 3)
count_ptrs_side1 = u32s(0x8036F434, 3)
budget_ptrs_side0 = u32s(0x8036F4B8, 3)
budget_ptrs_side1 = u32s(0x8036F53C, 3)
pool_ptrs_side0 = u32s(0x8036F360, 3)
pool_ptrs_side1 = u32s(0x8036F3E4, 3)

DIFFS = ["normal", "tuff", "insane"]
battles = {}
for d, name in enumerate(DIFFS):
    n = BATTLE_COUNTS[d]
    rows = []
    for b in range(n):
        rows.append({
            "battle": b,
            "side0AllyCount": s8s(count_ptrs_side0[d] + b, 1)[0],
            "side1EnemyCount": s8s(count_ptrs_side1[d] + b, 1)[0],
            "side0Budget": u32s(budget_ptrs_side0[d] + b * 4, 1)[0],
            "side1Budget": u32s(budget_ptrs_side1[d] + b * 4, 1)[0],
            "side0PoolIds": s8s(pool_ptrs_side0[d] + b * 4, 4),
            "side1PoolIds": s8s(pool_ptrs_side1[d] + b * 4, 4),
        })
    battles[name] = rows

out = {
    "provenance": {
        "source": "GG4E boot.dol (sha inherits repo disc extraction)",
        "extractor": "scripts/extract-challenge-tables.py",
        "functions": {
            "poll_challenge_menu_selection": "0x80196030 (chunk_0048.c:153)",
            "build_challenge_battle_setup": "0x801962c4 (chunk_0048.c:234)",
            "stage_rotation_zz_0196dac_": "0x80196dac (chunk_0048.c:643)",
            "post_battle_branch_FUN_801969a0": "0x801969a0 (chunk_0048.c:466)",
            "battle_end_judge_zz_00297c8_": "0x800297c8 (chunk_0003.c:4488)",
        },
        "notes": [
            "CPU team generation counts each rolled borg at floor(cost*2/3) against side budget (chunk_0048.c:351).",
            "Stage rotation: uniform pick from stagePool (11 entries), reroll while equal to previous stage (chunk_0048.c:649-656).",
            "Stage variant: rand % variantCount(stage) via DAT_802da5d0 table (already in packages/missions/src/challenge-reference.ts).",
            "Challenge freezes the 18000-frame battle timer: PTR_DAT_80433934[0x50]=1 (chunk_0048.c:392); judge timeout branches require [0x50]==0, so Challenge battles cannot time out.",
            "Winner mask [0x1f]: bit0=side0 wins, bit1=side1 wins, 4=timeout-draw (versus only), 8=unused-4th; Challenge continues only when mask has the player's side bit and mask<=2 (chunk_0048.c:486-502).",
        ],
    },
    "battleCountsPerDifficulty": dict(zip(DIFFS, BATTLE_COUNTS)),
    "energyLimitsPerDifficulty": dict(zip(DIFFS, ENERGY_LIMITS)),
    "stagePool": STAGE_POOL,
    "perDifficultyExtras": {
        "DAT_804356e4_pairs": [s8s(0x804356E4 + d * 2, 2) for d in range(3)],
        "DAT_804356ec_sideValues": {
            name: s8s(0x804356EC + d * 2, 2) for d, name in enumerate(DIFFS)
        },
    },
    "battles": battles,
}

OUT.write_text(json.dumps(out, indent=2))
print(f"wrote {OUT}")
print("battleCounts:", BATTLE_COUNTS, "energyLimits:", ENERGY_LIMITS)
print("stagePool:", [f"st{b:02x}" for b in STAGE_POOL])
for name in DIFFS:
    r0 = battles[name][0]
    print(name, "battle0:", r0)
