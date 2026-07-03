# Borg Animation Export Plan

Generated: 2026-07-03T01:57:48.342Z
Region: GG4E

## Summary

- Borgs with model + MOT: 104
- Borgs with public DAE/model evidence: 104
- Borgs safe for current single-borg exporter: 41
- MOT clips discovered: 4433
- Confirmed exported clips: 9
- Planned clips: 4424
- Planned clips blocked by current exporter assumption: 2583
- Existing export JSON files parsed: 4767

## Semantics

Generated names use structural candidate labels (`bankN_slotNN`). This confirms where clips live and how to export them, not gameplay meaning such as walk, attack, or hit reaction.
Clips are marked exporter-safe only when the MOT's first blob starts at `0x240`, matching the current single-borg exporter's fixed table scan boundary.

## Proof Export Candidate

- Borg: pl0000
- Source blob: 0x240
- Destination: `apps/game/public/models/pl0000/anim_b00_s00_candidate.json`
- Command: `node scripts/export-borg-animation-hsd.mjs GG4E pl0000 0x240:anim_b00_s00_candidate.json`
- Reason: first non-pl0615 borg with a discovered model, MOT clip, public DAE, and no confirmed matching export

## Borg Batch Summary

| Borg | Public model | Exporter-safe | First blob | Clips | Confirmed exported | Planned | First planned command |
|---|---:|---:|---:|---:|---:|---:|---|
| pl0000 | yes | yes | 0x240 | 56 | 0 | 56 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0000 0x240:anim_b00_s00_candidate.json` |
| pl0001 | yes | yes | 0x240 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0001 0x240:anim_b00_s00_candidate.json` |
| pl0002 | yes | yes | 0x240 | 56 | 0 | 56 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0002 0x240:anim_b00_s00_candidate.json` |
| pl0004 | yes | yes | 0x240 | 51 | 0 | 51 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0004 0x240:anim_b00_s00_candidate.json` |
| pl0005 | yes | no | 0x260 | 53 | 0 | 53 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0005 0x260:anim_b00_s00_candidate.json` |
| pl0006 | yes | yes | 0x240 | 51 | 0 | 51 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0006 0x240:anim_b00_s00_candidate.json` |
| pl0007 | yes | yes | 0x240 | 61 | 0 | 61 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0007 0x240:anim_b00_s00_candidate.json` |
| pl0008 | yes | yes | 0x240 | 56 | 0 | 56 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0008 0x240:anim_b00_s00_candidate.json` |
| pl0009 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0009 0x260:anim_b00_s00_candidate.json` |
| pl000c | yes | yes | 0x240 | 56 | 0 | 56 | `node scripts/export-borg-animation-hsd.mjs GG4E pl000c 0x240:anim_b00_s00_candidate.json` |
| pl0100 | yes | no | 0x220 | 55 | 0 | 55 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0100 0x220:anim_b00_s00_candidate.json` |
| pl0101 | yes | no | 0x220 | 55 | 0 | 55 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0101 0x220:anim_b00_s00_candidate.json` |
| pl0102 | yes | no | 0x220 | 59 | 0 | 59 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0102 0x220:anim_b00_s00_candidate.json` |
| pl0103 | yes | yes | 0x240 | 64 | 0 | 64 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0103 0x240:anim_b00_s00_candidate.json` |
| pl0104 | yes | no | 0x220 | 62 | 0 | 62 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0104 0x220:anim_b00_s00_candidate.json` |
| pl0105 | yes | no | 0x220 | 55 | 0 | 55 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0105 0x220:anim_b00_s00_candidate.json` |
| pl0107 | yes | no | 0x220 | 59 | 0 | 59 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0107 0x220:anim_b00_s00_candidate.json` |
| pl0109 | yes | yes | 0x240 | 41 | 1 | 40 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0109 0x1D00:anim_b00_s01_candidate.json` |
| pl0200 | yes | yes | 0x240 | 33 | 0 | 33 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0200 0x240:anim_b00_s00_candidate.json` |
| pl0201 | yes | yes | 0x240 | 37 | 0 | 37 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0201 0x240:anim_b00_s00_candidate.json` |
| pl0202 | yes | yes | 0x240 | 41 | 0 | 41 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0202 0x240:anim_b00_s00_candidate.json` |
| pl0203 | yes | no | 0x260 | 37 | 0 | 37 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0203 0x260:anim_b00_s00_candidate.json` |
| pl0204 | yes | no | 0x260 | 37 | 0 | 37 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0204 0x260:anim_b00_s00_candidate.json` |
| pl0205 | yes | yes | 0x240 | 38 | 0 | 38 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0205 0x240:anim_b00_s00_candidate.json` |
| pl0207 | yes | yes | 0x240 | 39 | 0 | 39 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0207 0x240:anim_b00_s00_candidate.json` |
| pl0208 | yes | yes | 0x240 | 53 | 0 | 53 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0208 0x240:anim_b00_s00_candidate.json` |
| pl020e | yes | yes | 0x240 | 49 | 0 | 49 | `node scripts/export-borg-animation-hsd.mjs GG4E pl020e 0x240:anim_b00_s00_candidate.json` |
| pl0300 | yes | yes | 0x240 | 47 | 0 | 47 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0300 0x240:anim_b00_s00_candidate.json` |
| pl0301 | yes | yes | 0x240 | 48 | 0 | 48 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0301 0x240:anim_b00_s00_candidate.json` |
| pl0302 | yes | yes | 0x240 | 49 | 0 | 49 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0302 0x240:anim_b00_s00_candidate.json` |
| pl0303 | yes | yes | 0x240 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0303 0x240:anim_b00_s00_candidate.json` |
| pl0304 | yes | no | 0x260 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0304 0x260:anim_b00_s00_candidate.json` |
| pl0305 | yes | no | 0x260 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0305 0x260:anim_b00_s00_candidate.json` |
| pl0307 | yes | no | 0x260 | 53 | 0 | 53 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0307 0x260:anim_b00_s00_candidate.json` |
| pl0308 | yes | no | 0x260 | 49 | 0 | 49 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0308 0x260:anim_b00_s00_candidate.json` |
| pl0309 | yes | no | 0x260 | 47 | 0 | 47 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0309 0x260:anim_b00_s00_candidate.json` |
| pl030c | yes | no | 0x260 | 48 | 0 | 48 | `node scripts/export-borg-animation-hsd.mjs GG4E pl030c 0x260:anim_b00_s00_candidate.json` |
| pl0400 | yes | no | 0x200 | 31 | 0 | 31 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0400 0x200:anim_b00_s00_candidate.json` |
| pl0401 | yes | no | 0x200 | 34 | 0 | 34 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0401 0x200:anim_b00_s00_candidate.json` |
| pl0402 | yes | no | 0x200 | 33 | 0 | 33 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0402 0x200:anim_b00_s00_candidate.json` |
| pl0403 | yes | no | 0x200 | 31 | 0 | 31 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0403 0x200:anim_b00_s00_candidate.json` |
| pl0404 | yes | no | 0x200 | 31 | 0 | 31 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0404 0x200:anim_b00_s00_candidate.json` |
| pl0405 | yes | no | 0x200 | 33 | 0 | 33 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0405 0x200:anim_b00_s00_candidate.json` |
| pl0406 | yes | no | 0x200 | 31 | 0 | 31 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0406 0x200:anim_b00_s00_candidate.json` |
| pl0407 | yes | no | 0x200 | 34 | 0 | 34 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0407 0x200:anim_b00_s00_candidate.json` |
| pl040b | yes | no | 0x200 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl040b 0x200:anim_b00_s00_candidate.json` |
| pl0500 | yes | no | 0x120 | 27 | 0 | 27 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0500 0x120:anim_b00_s00_candidate.json` |
| pl0501 | yes | no | 0x140 | 30 | 0 | 30 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0501 0x140:anim_b00_s00_candidate.json` |
| pl0502 | yes | no | 0x140 | 29 | 0 | 29 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0502 0x140:anim_b00_s00_candidate.json` |
| pl0503 | yes | no | 0x140 | 30 | 0 | 30 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0503 0x140:anim_b00_s00_candidate.json` |
| pl0504 | yes | no | 0x140 | 39 | 0 | 39 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0504 0x140:anim_b00_s00_candidate.json` |
| pl0600 | yes | yes | 0x240 | 42 | 0 | 42 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0600 0x240:anim_b00_s00_candidate.json` |
| pl0601 | yes | yes | 0x240 | 68 | 0 | 68 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0601 0x240:anim_b00_s00_candidate.json` |
| pl0602 | yes | yes | 0x240 | 42 | 0 | 42 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0602 0x240:anim_b00_s00_candidate.json` |
| pl0604 | yes | no | 0x1A0 | 45 | 0 | 45 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0604 0x1A0:anim_b00_s00_candidate.json` |
| pl0606 | yes | yes | 0x240 | 38 | 0 | 38 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0606 0x240:anim_b00_s00_candidate.json` |
| pl0608 | yes | yes | 0x240 | 42 | 0 | 42 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0608 0x240:anim_b00_s00_candidate.json` |
| pl0610 | yes | no | 0x260 | 53 | 0 | 53 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0610 0x260:anim_b00_s00_candidate.json` |
| pl0613 | yes | no | 0x1A0 | 40 | 0 | 40 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0613 0x1A0:anim_b00_s00_candidate.json` |
| pl0615 | yes | yes | 0x240 | 55 | 8 | 47 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0615 0x5200:anim_b00_s03_candidate.json` |
| pl0619 | yes | no | 0x200 | 26 | 0 | 26 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0619 0x200:anim_b00_s00_candidate.json` |
| pl061a | yes | yes | 0x240 | 38 | 0 | 38 | `node scripts/export-borg-animation-hsd.mjs GG4E pl061a 0x240:anim_b00_s00_candidate.json` |
| pl061f | yes | no | 0x2A0 | 39 | 0 | 39 | `node scripts/export-borg-animation-hsd.mjs GG4E pl061f 0x2A0:anim_b00_s00_candidate.json` |
| pl0628 | yes | no | 0x200 | 25 | 0 | 25 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0628 0x200:anim_b00_s00_candidate.json` |
| pl062a | yes | yes | 0x240 | 58 | 0 | 58 | `node scripts/export-borg-animation-hsd.mjs GG4E pl062a 0x240:anim_b00_s00_candidate.json` |
| pl0700 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0700 0x260:anim_b00_s00_candidate.json` |
| pl0701 | yes | no | 0x260 | 33 | 0 | 33 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0701 0x260:anim_b00_s00_candidate.json` |
| pl0702 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0702 0x260:anim_b00_s00_candidate.json` |
| pl0703 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0703 0x260:anim_b00_s00_candidate.json` |
| pl0704 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0704 0x260:anim_b00_s00_candidate.json` |
| pl0706 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0706 0x260:anim_b00_s00_candidate.json` |
| pl0707 | yes | no | 0x260 | 28 | 0 | 28 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0707 0x260:anim_b00_s00_candidate.json` |
| pl0708 | yes | no | 0x260 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0708 0x260:anim_b00_s00_candidate.json` |
| pl0800 | yes | yes | 0x240 | 33 | 0 | 33 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0800 0x240:anim_b00_s00_candidate.json` |
| pl0801 | yes | yes | 0x240 | 34 | 0 | 34 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0801 0x240:anim_b00_s00_candidate.json` |
| pl0802 | yes | no | 0x260 | 54 | 0 | 54 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0802 0x260:anim_b00_s00_candidate.json` |
| pl0804 | yes | yes | 0x240 | 43 | 0 | 43 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0804 0x240:anim_b00_s00_candidate.json` |
| pl0805 | yes | yes | 0x240 | 56 | 0 | 56 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0805 0x240:anim_b00_s00_candidate.json` |
| pl0806 | yes | yes | 0x240 | 35 | 0 | 35 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0806 0x240:anim_b00_s00_candidate.json` |
| pl0807 | yes | yes | 0x240 | 33 | 0 | 33 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0807 0x240:anim_b00_s00_candidate.json` |
| pl0808 | yes | no | 0x260 | 42 | 0 | 42 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0808 0x260:anim_b00_s00_candidate.json` |
| pl080a | yes | no | 0x260 | 43 | 0 | 43 | `node scripts/export-borg-animation-hsd.mjs GG4E pl080a 0x260:anim_b00_s00_candidate.json` |
| pl080c | yes | yes | 0x240 | 41 | 0 | 41 | `node scripts/export-borg-animation-hsd.mjs GG4E pl080c 0x240:anim_b00_s00_candidate.json` |
| pl0900 | yes | yes | 0x240 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0900 0x240:anim_b00_s00_candidate.json` |
| pl0901 | yes | yes | 0x240 | 34 | 0 | 34 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0901 0x240:anim_b00_s00_candidate.json` |
| pl0902 | yes | yes | 0x240 | 34 | 0 | 34 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0902 0x240:anim_b00_s00_candidate.json` |
| pl0903 | yes | yes | 0x240 | 32 | 0 | 32 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0903 0x240:anim_b00_s00_candidate.json` |
| pl0904 | yes | yes | 0x240 | 34 | 0 | 34 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0904 0x240:anim_b00_s00_candidate.json` |
| pl0a00 | yes | no | 0x280 | 68 | 0 | 68 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0a00 0x280:anim_b00_s00_candidate.json` |
| pl0a01 | yes | no | 0x280 | 70 | 0 | 70 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0a01 0x280:anim_b00_s00_candidate.json` |
| pl0a02 | yes | no | 0x280 | 57 | 0 | 57 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0a02 0x280:anim_b00_s00_candidate.json` |
| pl0a03 | yes | no | 0x280 | 74 | 0 | 74 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0a03 0x280:anim_b00_s00_candidate.json` |
| pl0a04 | yes | no | 0x280 | 70 | 0 | 70 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0a04 0x280:anim_b00_s00_candidate.json` |
| pl0b00 | yes | no | 0x2A0 | 54 | 0 | 54 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0b00 0x2A0:anim_b00_s00_candidate.json` |
| pl0b01 | yes | no | 0x2A0 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0b01 0x2A0:anim_b00_s00_candidate.json` |
| pl0b02 | yes | no | 0x2A0 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0b02 0x2A0:anim_b00_s00_candidate.json` |
| pl0b03 | yes | no | 0x2A0 | 54 | 0 | 54 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0b03 0x2A0:anim_b00_s00_candidate.json` |
| pl0b04 | yes | no | 0x2A0 | 50 | 0 | 50 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0b04 0x2A0:anim_b00_s00_candidate.json` |
| pl0b06 | yes | no | 0x2A0 | 54 | 0 | 54 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0b06 0x2A0:anim_b00_s00_candidate.json` |
| pl0c00 | yes | no | 0x120 | 13 | 0 | 13 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0c00 0x120:anim_b00_s00_candidate.json` |
| pl0c01 | yes | no | 0x120 | 14 | 0 | 14 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0c01 0x120:anim_b00_s00_candidate.json` |
| pl0c02 | yes | no | 0x120 | 13 | 0 | 13 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0c02 0x120:anim_b00_s00_candidate.json` |
| pl0c04 | yes | no | 0x120 | 13 | 0 | 13 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0c04 0x120:anim_b00_s00_candidate.json` |
| pl0c05 | yes | no | 0x120 | 13 | 0 | 13 | `node scripts/export-borg-animation-hsd.mjs GG4E pl0c05 0x120:anim_b00_s00_candidate.json` |

## Confirmed Export Examples

- pl0109 0x240 -> `apps/game/public/models/pl0109/anim_b00_s00_candidate.json`
- pl0615 0x240 -> `apps/game/public/models/pl0615/anim_b00_idle.json`
- pl0615 0x1A40 -> `apps/game/public/models/pl0615/anim_b00_clip1.json`, `apps/game/public/models/pl0615/anim_b00_move.json`
- pl0615 0x3680 -> `apps/game/public/models/pl0615/anim_b00_boost_forward.json`
- pl0615 0xA520 -> `apps/game/public/models/pl0615/anim_b00_jump_takeoff_candidate.json`
- pl0615 0xE3A0 -> `apps/game/public/models/pl0615/anim_b00_fly_transition_candidate.json`
- pl0615 0x345E0 -> `apps/game/public/models/pl0615/anim_b00_attack_arm_candidate.json`
- pl0615 0x3AE00 -> `apps/game/public/models/pl0615/anim_b00_hit_flinch_candidate.json`
- pl0615 0x49720 -> `apps/game/public/models/pl0615/anim_b00_down_candidate.json`

## Recent Exports

- None in this run.

