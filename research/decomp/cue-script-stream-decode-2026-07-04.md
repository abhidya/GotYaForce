# Command-cue → action-script-stream selection chain — DECODED (2026-07-04)

Decode agent report; every hop quoted from the corpus. Scratch scripts:
`scratchpad/dump-cue-state.mjs`, `dump-gred-tables.mjs`, `disasm.mjs` (section mapping
cloned from `scripts/scan-damage-table-bindings.mjs`).

## Hop 1: the +0x4f0 table (cueId → state pair)

`zz_006a6fc_` (chunk_0009.c:835-853): `cVar1 = *(char *)(*(int *)(param_1 + 0x4f0) + param_2 * 2)`
→ `+0x5da = cVar1` (and `+0x5e5 = cueId`), resets phase bytes `+0x540..+0x543 = 0`. Twin
`zz_006a750_` (857-880) reads `+ param_2 * 2 + 1` → `+0x5db`, resets `+0x544..+0x547`.

**Layout: 48 entries (cue 0..47) × 2 bytes = [fullBodyState(+0x5da), upperBodyState(+0x5db)],
-1 = "no state change".** Length proof: G RED's table at 0x80365cf8 + 0x60 = 0x80365d58 =
exactly his type-0 command records (commandMoveTables.json); same adjacency for family-01
(0x802d4590 + 0x60 = 0x802d45f0). `zz_006a104_` calls `zz_006a6fc_(actor, byte[0])` always
(chunk_0009.c:658) and `zz_006a750_` only when stateMode byte[1]==3 (659-661).

Dumped tables:
- **G RED @0x80365cf8**: cue 44/45 → **[61, 0]**; cues 9/10/11 → [0,10]/[0,11]/[0,12]
  (upper-body fire); cue 36 → [47,0] (deploy); 5→[22,22], 8→[23,23], 25→[0,31], 26→[0,32].
- **family-01 @0x802d4590** and **pl0200 @0x802d4b50** (ctor block-copy from 0x802d47b8,
  word 15; disassembled at 0x80073b70): cue 44/45 → **[61, 0]** in all three. Attack cues
  are fleet-uniform.

## Hop 2: per-frame state dispatch

`FUN_80055568` (chunk_0006.c:7793-7798): `(&PTR_LAB_802d37a8)[+0x5db]()` then
`(&PTR_LAB_802d36a8)[+0x5da]()`. Correction: 0x802d3570 is a *phase* table indexed by +0x540
inside the deploy state (chunk_0007.c:3781), not the cue table.

**State 61 = FUN_80065dfc (chunk_0008.c:2724-2731) = `(**(code **)(actor + 0x4b4))()`** —
the per-family virtual bound in the ctor (G RED: PTR_zz_018d24c__80365538, chunk_0046.c:4790;
pl0200: FUN_80073f3c via block 0x802d47b8[0]).

## Hop 3: family layer — actionIndex/variantIndex jump tables → config struct → shared engine

- G RED root zz_018d24c_ (chunk_0046.c:5063): `(&PTR_zz_018d288__80365588)[+0x580]()` —
  actionIndex table, 5 entries: a0=zz_018d288_ (dash attack), a1=FUN_8018dd9c (B melee),
  a2=FUN_8018e7fc (air B), a3=FUN_8018ed4c (B charge), a4=FUN_8018ee84.
- a1 FUN_8018dd9c (chunk_0047.c:283-291) picks a per-borg-id variant table
  (0x615→0x803655d4, 0x62a→0x803655f4, else 0x80365614) indexed by +0x581.
- Each variant leaf loads a static config struct into r4 then tail-calls a shared engine
  (`8018de9c: lis r4,0x8036; addi r4,r4,0x5664; bl 0x80177dd8`).
- Engines dispatch phaseTable[+0x540]; phase 0 starts the stream — e.g. FUN_80177e28
  (chunk_0044.c:3027-3041): `*(actor+0x6ea) = (char)*config; zz_004beb8_(rate, actor, 0xf, 3,
  (+0x6ea)++)`. Combo re-arms replay `(+0x6ea)++` (FUN_801780e4, chunk_0044.c:3151-3153);
  config+0x10 is a chain callback that re-issues a command via zz_006a3d0_ and may override
  +0x581 (FUN_8018ded0 chunk_0047.c:335-341: subtype 1 then +0x581 = 6).
- zz_004beb8_ (chunk_0006.c:1445-1490): group bit7 → shared bank +0x1d84 (group&0x7f), else
  family bank +0x1d80; group==0 → group = +0x582; stream = bank + s16[bank + group*2] +
  s16[groupBase + slot*2].

**The rule: bank = family (+0x1d80) for all attack streams; group = engine constant
(3 = melee strikes, 4 = charge/air specials, 2 = dash rams w/ cursor +0x6ee); slot = config
seed byte (config[0] ground / config[1] air), then +0x6ea auto-increment for combo
follow-ups.** NOT arithmetic on the record bytes — bytes[2]/[3] are jump-table indices —
but every hop is static DOL data, mechanically extractable per family like
gen-command-move-tables.mjs walks ctors.

## G RED end-to-end validation (bank 0x80366220, remap = attackHitTables pl0613)

| record (type.sub) | +0x580/+0x581 | leaf @0x80365614 | engine | config | seed→stream | armHit kind → records |
|---|---|---|---|---|---|---|
| B atk 1.0 [44,3,1,0] | 1/0 | FUN_8018de9c | zz_0177dd8_ | 0x80365664 | 25 → g3 s25 | kind 1 → [1,8] (plays 3/0) |
| mash chain | — | FUN_801780e4 ++ | — | — | 26 → g3 s26 | kind 2 → [2,9] |
| chain cb → v6 | 1/6 | FUN_8018e1f4 | zz_0179280_ | 0x803657c4 (u16=27) | 27 → **g3 s27** | kind 8 → [16], plays g3 s18 |
| 1.1 [44,3,1,2] | 1/2 | FUN_8018e25c | zz_0177dd8_ | 0x80365808 | 28 → g3 s28 | kind 20 → [38] |
| 1.2 [45,3,1,3] | 1/3 | FUN_8018e0f8 | zz_0178394_ | 0x80365728 | 30 → g3 s30 | kind 23 → [41] |
| 1.3 [44,3,1,1] | 1/1 | FUN_8018df78 | zz_0179280_ | 0x803656c0 (u16=29) | 29 → g3 s29 | kind 19 → [37] |
| 1.4 [45,3,1,4] | 1/4 | FUN_8018e198 | zz_0178394_ | 0x8036577c | 33 → g3 s33 | kind 24 → [42] |
| air B [44,3,2,v] | 2/* | FUN_8018e888 | (own phases 0x80365844) | id-switched | 0 → g4 s0 | kind 15 → [33] |
| B charge [44,3,3,v] | 3/* | zz_018ed80_ | zz_0179814_ | 0x80365854 | 2/2 → g4 s2 | no armHit — windup only; fire = child spawn zz_00e19a8_(actor,0xf,&+0x6f7) type 0x20 (chunk_0047.c:1001-1012, chunk_0024.c:1587-1591) |

**Honest correction:** the prior claim *g3 s27 = charge fire* is wrong — s27 (kind 8, anim
g3 s18) is the **standing-mash 3rd-hit finisher** (reached via +0x6ea 25→26→27, or via
chain-callback variant 6 whose config hard-codes slot 27). Action 3 (B hold) never touches
g3; its damage is the spawned projectile child. The melee ladder = kinds 1,2,8 (standing
chain) + 19/20/23/24 (context variants), matching remap kinds 1..8.

## Second family: pl0200 Sword Knight (bank 0x802bff80)

Same shape: cue table 0x802d4b50 44/45→[61,0]; +0x4b4=FUN_80073f3c → action table 0x802d4820;
a1=zz_00743d0_ (chunk_0010.c:1586) → variant table 0x802d4844: v0→zz_015809c_(actor,0),
v1→zz_0158688_(actor,3), v2→zz_0158688_(actor,4) — engines seed +0x6ea=param and play
zz_004beb8_(...,0xf,3,(+0x6ea)++) (chunk_0040.c:2377-2382, 2581-2594). Validation: seed 0 →
g3 s0 kind 1 → [1,25,26] (first slash), chain s1 kind 2, s2 kind 5; seeds 3/4 → g3 s3/s4
kinds 4/6. Charge (a2/a3 → zz_007454c_ chunk_0010.c:1687): zz_004beb8_(...,0xf,4,
airborne?1:0) → g4 s0 kind 3 [3,9] ground / g4 s1 kind 18 [34,35] air. Every stream/kind
exists in meleeAnimKinds.json exactly where the seeds point. **Consistent across both
families.**

## Fleet extraction recipe (for the port)

Per ctor: capture +0x4b4 (direct store or 0x802d47b8-style block copy) → walk its dispatch
on +0x580, then +0x581 (emulating borg-id compares as gen-command-move-tables.mjs does) → at
each leaf capture (lis/addi r4 = config, bl engine) → engine identity gives config layout +
group constant (engines seen: zz_0177dd8_/zz_0178394_/zz_0178b6c_/zz_0179280_/zz_0179814_/
zz_0179fcc_/zz_0179d20_ @0x80352b08-64/0x804347a8; zz_015809c_/zz_0158688_/zz_0158a94_
@0x80343c00-28; plus bespoke per-family phase tables) → emit
`(borg, actionIndex, variantIndex) → {bank: familyBank, group, seedSlot, airSeedSlot,
chainCallback}`; join with meleeAnimKinds.json streams for kind/anim and attackHitTables.json
remap for hitboxes. The only genuinely dynamic bits are the two runtime cursors: +0x6ea
(combo depth, deterministic from seed + re-arm count) and +0x6ee (dash-anim cursor, group 2).
