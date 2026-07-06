# Normal Ninja family decode + port (2026-07-06)

Transcription-grade dig of the NORMAL NINJA family (pl0000/pl000a, ctor 0x8006f4f8) action
state machine, run as a verified agent workflow (`wf_a6dd44f6-f67`): 14/16 claims confirmed
by BOTH a corpus lens and a raw-bytes lens; 2 claims refuted on specific constants — the
corrections (both verifiers agreeing byte-exactly) are folded in below and marked ⚠. The
X-special was ported the same session (`packages/combat/src/families/ninja.ts` +
`shared-x-special.ts`; `pnpm selfcheck:rom` green).

## 1. Root dispatcher + action table

`FUN_8006facc` @0x8006facc: `(*(code*)(&PTR_FUN_802d3b68)[*(char*)(actor+0x580)])();`
`PTR_FUN_802d3b68` @0x802d3b68 — exactly 5 entries (bounded by PTR_FUN_802d3b7c):

| idx | addr | role | pl0000/pl000a live? |
|---|---|---|---|
| 0 | 0x8006fb08 | B-tap ground/dash/air sword-combo driver | yes (type 0) |
| 1 | 0x80070604 | contextual-B lunge driver (borg-switched) | yes (type 1) |
| 2 | 0x80071598 | X-special driver | yes (type 2) — **PORTED** |
| 3 | 0x800716d8 | X-charge dash | **DEAD** (see below); live for pl0003 |
| 4 | 0x80071a84 | B-charge shuriken toss | **DEAD**; machine reachable for SASUKE via action-1 v1/v2 |

**Charge moves are command-DISABLED for pl0000/pl000a**: descriptor +0xb8 mode bytes =
`01 00 01 ff ff ff` (types 3/4/5 = 0xff, rejected by the initiator `zz_0069dd0_`
chunk_0009.c:462). ⚠ Verifier extra: **G RED's descriptor 0x80365ac8+0xb8 =
`01 00 00 01 ff ff`** — G RED's types 4/5 are ALSO disabled (only type-3 B-charge is
live); its action-4 record table @0x80365e48 is dead data.

The actionIndex convention is FAMILY-LOCAL, bound by the +0x4ec command records (not a
fixed global semantic). gred.ts's "0=dash, 3=B charge" comment labels should read
"0=B-tap chain, 3/4=charge chains".

## 2. THE ARCHITECTURE FINDING: the X-special is a SHARED ENGINE machine

`zz_0071598_` dispatches all 5 variants to `zz_00715d4_` — a 9-instruction wrapper that
loads **r4 = r13−0x7d38 = 0x80433868** (r13=0x8043b5a0 from `__init_registers`) and
branches to the **shared X handler `zz_00ff2bc_` @0x800ff2bc** (Ghidra dropped the r4
argument). Phase table `PTR_zz_00ff30c__8031f000` = [0x800ff30c, 0x800ff418, 0x800ff4d4,
NULL]. Config block @0x80433868: `u16 groundSlot=0, u16 airSlot=1, ptr onHit=0x800715f8`.

Unlike G RED (bespoke family chain), families whose X routes to 0x800ff2bc differ ONLY in
this config block → ported ONCE as `families/shared-x-special.ts`, parameterized.

### Phase transcriptions (constants all DOL-read)

- **P0 `zz_00ff30c_`**: +0x540++; no target → +0x5ac = +0x72; face (mask 0xc1); zero
  +0x44/+0x48/+0x4c/+0x50 (FLOAT_804392b4=0) + turn rates; **reposition
  motion=(pos−target)×0.95 (FLOAT_804392d0), pos+=motion** (the blink-away, same shape as
  G Crash); ground snap zz_00677b0_; +0x6ea = cfg slot (air fork on +0x5e0&0x40), then
  +0x6ea++; start stream rate −1.0 (FLOAT_804392b8) mask 0xf **group 4**; +0x80c=0.
- **P1 `zz_00ff418_`**: tick 0xf; face 0xc1; reposition ×0.95 continue; on contact byte
  **+0x1cef > 0**: +0x540++ and invoke cfg callback; |motion|>3.0 (FLOAT_804392c8) →
  afterimage zz_00b22f4_.
- **P2 `zz_00ff4d4_`** (no cfg use): tick; FUN_80067310(gravity 1.0 = FLOAT_804392d4,
  yaw +0x5ae); grounded/contact exits (upper cue 7, idle reset zz_006a474_ → cue 0, or
  air-fall zz_006a5a4_); attack cooldown **+0x694 = 4.0 (FLOAT_804392d8) + dt**.

### The ninja on-hit callback `zz_00715f8_` @0x800715f8 (cfg+4)

On stream-event byte +0x1d0f: **BACKFLIP** — +0x5ae = +0x72 − 0x8000 (face away 180°),
+0x44 = 10.0 (FLOAT_80437748), +0x4c = 0.0, +0x48 = 15.0 (FLOAT_80437768), +0x50 = −1.0
(FLOAT_804376e0). Then ammo gate `zz_006dbe0_(actor, slot 2, cost 1)` → **SHURIKEN** via
`zz_007db5c_(actor, type)`: borg 0x000 → type 0; borg 0x00a (SASUKE) → type 3; borg
0x003 (DOUBLE NINJA) → types 1 (+2 if +0x7c8).

## 3. Other actions (transcribed, NOT ported yet — recipe raw material)

- **Action 0 (B-tap)**: variant table PTR_FUN_802d3b7c (10 entries) → 4 three-phase
  machines (ground combo / dash-B / air-B / situation-4), all group-2 streams; combo
  seed zz_0070530_ (+0x6ef=5 swings, timer +0x560=30.0), per-swing kunai via
  zz_0070558_ → zz_006ee14_ (borg 10 → variant 4 @ speed 85; else variant 0), B-held
  re-entry loops (phase--, stream restart slot 1/7), air re-dispatch zz_006a3d0_.
  ⚠ Correction: ground-combo P1 (FUN_8006fc24) faces with mask **0xC1** (raw disasm
  `li r4,0xc1` @0x8006fc50), not 0x81 — 0x81 belongs to the air/situation-4 machines.
  Three distinct face masks in this family: 0xC1 (X phases + ground-combo P1), 0x81
  (machines C/D P1), 0xC0 (lunge/leap/spin/action-4).
- **Action 1 (contextual B)**: borg-switched variant tables (@0x802d3bd4; SASUKE
  @0x802d3be8 reroutes v1/v2 to the action-4 big-shuriken machine zz_0071ac0_). v0/v1 =
  the **SHARED 4-phase melee lunge `zz_00fed6c_` @0x800fed6c** (config @0x802d3bfc =
  {slotBase 1, range 150.0, dashFrames 20, decel 0.95/0.95/0.8}) — another shared-engine
  machine reused across families, worth porting once like shared-X. ⚠ Corrections:
  flying-lunge P2 decay = **0.95 (FLOAT_80437744)** not 0.97; leap P1 gravity term =
  **2.0 × (−vy/30.0)** (FLOAT_80437728/FLOAT_80437708) — 200.0 (FLOAT_8043772c) is only
  the FX distance gate; shared-lunge P3's 0.8 decelC applies WITHIN range (braking near
  target), not past-range. pl0000 v2 = spin slash (1638.4 BAM/frame spin); v4 = 6-phase
  leap dive-slam.
- **Actions 3/4**: transcribed in the workflow output (X-charge dash speed ramp
  150×cos ramp over 15f; big-shuriken toss machines) — dead for this family's two borgs.

## 4. Cue tables (48×2, both dumped byte-exact)

Family 0 @0x802d3ff8: rows 0-17 = (i+1, i+1) except 9/10/11 = (0, i+1); 35=(0,0x2b);
36=(0x2f,0); 43=(0,0x3c); **44=(0x3d,0) AND 45=(0x3d,0)** — both attack cues land in
full-body state 61; 46=(0,0x3e); 47=(0,0x3f); rest = (ff,ff).
G RED @0x80365cf8 = byte-identical EXCEPT rows 5:(16,16), 8:(17,17), 25:(0,1f), 26:(0,20).
State 61 = `FUN_80065dfc` = `(**(code**)(actor+0x4b4))()` (the family root-action
trampoline) — confirms the G RED port's state-61 wiring holds for family 0.
**Ported**: bridge.ts now builds BOTH tables from these full dumps (`makeFamily0BaseCueTable`
+ G RED deltas), retiring the old partial hand-rows (which missed rows 36-upper/43/45/46/47).

## 5. +0x4ec answered (ctor-decode open question CLOSED)

+0x4ec IS the command-move root table: 6 pointers indexed by command type +0x585, records
[cue, ctrlBits→+0x5e0, actionIndex→+0x580, variant→+0x581]; 2-D (situation×direction)
when descriptor+0xb8[type]==1, else 1-D. Byte-exact match with commandMoveTables.json's
existing decode (family 0 root @0x802d4148, G RED @0x80365ea8) — no new extraction needed.
Chain-cancel masks +0x57a/+0x57b from DAT_802d3994[type*2] (family 0: 3a/38/38/38/38/38).

## 6. Projectile spawners (data recorded; ballistics not ported)

- Shuriken `zz_007db5c_` @0x8007db5c: table @0x802d6d68 stride 0x38, 4 records gated by
  borgNumber s16@+0x2e (0/3/3/10); bone 0x0b, muzzle (55,0,0). NOTE this is the same
  table the flight-visual decode identified (its variants 6-9 = the G RED bank-flag row).
- Kunai `zz_006ee14_` @0x8006ee14: table @0x802d39b0 stride 0x34; bone 7/11/matrix;
  speed 60.0 (recs 0-3) / 85.0 (rec 4, SASUKE). ⚠ Verifier extras: u16@rec+0x2e is a
  **direction-negate flag** (recs 0/2/4 = 1 → direction = MINUS the muzzle-matrix X
  column — without it kunai fire backwards); variant 2 hardcodes pos += owner+0x7b0.

## 7. What landed in the port this session

- `families/shared-x-special.ts` — zz_00ff2bc_ + 3 phases, config-parameterized (NEW
  shared layer; next shared-engine family is a config block away).
- `families/ninja.ts` — pl0000 + pl000a registration, X-special wired through the shared
  machine, backflip callback with exact constants, shuriken spawn surfaced through the
  new `StreamContext.onFamilyProjectile` hook (host wiring of table 0x802d6d68 is a
  residual — melee contact is the ported payload; unwired hook = honest no-op).
- bridge.ts — both families registered with the full DERIVED cue tables (cue 45 now maps
  for G RED too).
- rom.selfcheck.ts — 3 new test blocks (phase-0 blink/zero, on-hit backflip + SASUKE
  shuriken type 3, bridge cue rows 44/45).
- **Drive-by bug found by the suite**: 31096d1c's ROM projectile-variant wiring fed the
  ROM's NEGATIVE-down drop values straight into the port's POSITIVE-down
  `Projectile.drop` (`vel.y -= drop`) — ROM-droppy bullets rose. Fixed (negate at the
  boundary, combat.ts spawnProjectile) + assert hardened against sign regressions.
- VALIDATED: `pnpm -r run build` clean; `pnpm selfcheck:rom` all-pass (incl. new ninja
  tests); full combat selfcheck PASS; 1P challenge smoke PASS (resolvedFrame 5191→6524 —
  expected: ROM-variant bullets now fall, and the pl0000-family X path changed);
  11-stage + family-variant smokes PASS; projectile 36/36; xammo 32/32; menu-flow PASS.

## 8. Open questions (carried)

+0x748 close/far context byte writer; zz_006c674_ direction classifier body;
FUN_800061a8(5) feedback identity; trail/FX helper identities (zz_00b2190_/zz_00b22f4_/
zz_0092dcc_); shuriken/kunai record float semantics (child update fns FUN_8007dcec/
FUN_8006f0cc unread); +0x868 range-row writer; +0x57b consumer; DAT_802d3ab4 kunai
enable array bytes; zz_006bf80_ body.
