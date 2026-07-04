# Challenge results-screen scoring — DECODED (2026-07-04)

Static decode of the post-battle results screen (ATTACK / HIT RATIO / DODGE RATIO /
BORGS DEFEATED / TOTAL COST / GRAND TOTAL — reference capture
`apps/game/reference/captures/challenge-11-WIN-results.png`) from the ghidra corpus
(`research/decomp/ghidra-export/`) + boot.dol data extraction
(`user-data/GG4E/disc/sys/boot.dol`, DOL section mapping per
`scripts/scan-damage-table-bindings.mjs`).

Everything in this doc is corpus-quoted or DOL-extracted; honest unknowns at the end.

## 1. The per-actor stat block (actor struct +0x404..+0x437, +0x4fc)

All results counters live on the persistent per-player-slot actor (`DAT_803c4e84`
array, stride 0x1e00, 6 slots) — they survive borg swaps within a battle. Actors with
byte +0x83 != 0 (non-scoring/sub objects) never count.

| offset | type | meaning | incremented by |
|---|---|---|---|
| +0x404 | u32 | attacks initiated ("ATTACK" row, hit-ratio denominator) | `zz_008a5d0_` @0x8008a5d0 (chunk_0013.c:1104) with param_3=1 |
| +0x408 | u32 | cross-team hits landed (once per attack event per victim) | resolver chunk_0003.c:7886 |
| +0x40c | u32 | enemy attacks AIMED at me at activation (attack object target +0xcc == me) | `zz_008a5d0_` chunk_0013.c:1115 |
| +0x410 | u32 | hits taken from attacks aimed at me; clamped <= +0x40c | chunk_0003.c:7888-7891 |
| +0x414 | u32 | hits taken NOT aimed at me: stray/AoE (7894), untracked-record (7898), same-team (7842) |
| +0x418 | u32 | damage dealt cross-team (final damage, pre-winner only) | chunk_0003.c:7979 |
| +0x41c | u32 | damage taken | chunk_0003.c:7981 |
| +0x420 | u32 | COST WON — summed victim cost (u16 victim+0x4aa) on kills I land | kill event `zz_002f8dc_` chunk_0003.c:8291 |
| +0x424 | u32 | COST LOST — my own borgs' cost when defeated | `zz_002f8dc_` chunk_0003.c:8287 |
| +0x428 | u32 | friendly-fire hits dealt | chunk_0003.c:7844 |
| +0x42c | u32 | friendly-fire damage dealt | chunk_0003.c:7975 |
| +0x430 | u32 | ALLY cost lost (victim cost added to every OTHER same-side actor) | `zz_002f8dc_` chunk_0003.c:8312 |
| +0x434 | u8 | kills (enemy borgs I finished off) | `zz_002f8dc_` chunk_0003.c:8290 |
| +0x435 | u8 | own borgs defeated | `zz_002f8dc_` chunk_0003.c:8286 |
| +0x436 | u8 | FIRST STRIKE flag — first cross-team hit of the battle (global gate `DAT_80436128`) | chunk_0003.c:7882-7885 |
| +0x437 | u8 | allies defeated (count) | `zz_002f8dc_` chunk_0003.c:8311 |
| +0x4fc | u16 | max combo (versus rank row only) | combo counters +0x4f4/+0x4f6, 999 cap (chunk_0003.c:7860-7877, 7913-7931) |

### Attempt semantics (`zz_008a5d0_` @0x8008a5d0, chunk_0013.c:1087-1122)

Called from the hitbox activation path `FUN_8008a65c` (chunk_0013.c:1125-1240):

- One attempt per attack-object ACTIVATION (guarded by attack+0x1ca first-activation
  flag): param_3=1 only when the hit record's u16+0x10 (flagsA) bit **0x20 is clear**
  (chunk_0013.c:1219-1224). Flag-0x20 records are "untracked" — no attempt, and their
  connections are also excluded from +0x408 (resolver 7894-7898 routes them to +0x414).
- Rehit re-registrations (interval timer path, chunk_0013.c:1182) pass param_3=0 —
  **rehits never count as new attempts**.
- The SAME activation also increments +0x40c (incoming) on the attack object's target
  (+0xcc) if that target is an enemy (side +0x88 differs) — whether or not the attack
  ever connects. This is the entire "dodge opportunity" counter.

### Hit semantics (resolver `resolve_hitbox_target_effects_and_damage` @0x8002e2a8, chunk_0003.c:7834-7898)

Gates: record flagsB high bits (0xfc0) clear, both actors +0x83==0, neither side 4.
Deduped **once per (attack event, victim)** via the event's per-player bitmask +0x2ad
(bit = victim player index +0x3e4).

- Cross-team, tracked record: attacker +0x408 += 1. Victim: if the event's aimed target
  (+0xcc) == victim → +0x410 += 1 (clamped to +0x40c); else +0x414 += 1.
- Cross-team, untracked (flagsA & 0x20): victim +0x414 += 1 only.
- Same-team: victim +0x414 += 1, attacker +0x428 += 1.
- First cross-team hit of the battle: `DAT_80436128=1`, attacker +0x436 = 1.

### Kill event (`zz_002f8dc_` @0x8002f8dc, chunk_0003.c:8212-8330)

`zz_002f8dc_(attacker, victim)`: cost = u16 victim+0x4aa (`zz_0066168_(borgId)` init).
Victim: +0x435 += 1, +0x424 += cost. Attacker (if cross-team): +0x434 += 1, **+0x420 +=
cost**, and team score `(&DAT_80436154)[side] += 100`. Every OTHER living same-side
actor of the victim: +0x437 += 1, +0x430 += cost. → **the flat +100/kill feeds only the
in-battle team score, NOT the results grand total.** Kill attribution = last damager.

## 2. The results screen rows (`FUN_800d3260` @0x800d3260, chunk_0022.c:1912-2146)

Row index at widget+0x12, actor at widget+0x90. `pct(x) = 100*x` float, 2 decimals:

| row | label (capture) | value |
|---|---|---|
| 0 | ATTACK | `+0x404` — **the attack COUNT, not damage** |
| 1 | HIT RATIO | `100 * +0x408 / +0x404`, 0 if either is 0 |
| 2 | DODGE RATIO | `100 * (+0x40c − +0x410) / (+0x40c + +0x414)`, 0 if +0x40c == 0 |
| 3 | ENEMY BORGS DEFEATED | byte `+0x434` |
| 4 | TOTAL COST | center `+0x420`; right column = tier score `DAT_803cce00[player]` |
| 5 | PLAYER BORGS DEFEATED | byte `+0x435` |
| 6 | TOTAL COST | center `+0x424`; right column = tier score `DAT_803cce08[player]` |
| 7 | ALLY BORGS DEFEATED | byte `+0x437` |
| 8 | (first-strike bonus row) | right column `DAT_803cce14[player]` |
| 9 | GRAND TOTAL | right column `DAT_803cce2c[player]`, sign-rendered |

The `DAT_803ccdxx` addresses are words [0x18]/[0x1a]/[0x1d]/[0x23] of the per-player
0x94-byte results struct array at `DAT_803ccda0` (6 entries), filled by:

## 3. The grand-total builder (`zz_00d1d24_` @0x800d1d24, chunk_0022.c:995-1092)

Runs for each human player (`PTR_DAT_80433934[0x15db]` mask) from `zz_00d285c_`
@0x800d285c, which the battle-flow end-state calls (chunk_0003.c:4070) in EVERY mode.
Key struct words (tier lookup `zz_00d1cbc_` = threshold table; ratio lookup
`zz_00d1ce8_` = percent-bounds table — both DOL-extracted, section 4):

- [0x13] tier(DAT_8030e318, attempts) — versus rank only
- [0x14] ratioTier(0x8030e380, hitRatio%) — versus rank only
- [0x15] tier(DAT_8030e3e8, dodges = +0x40c − +0x410) / [0x16] ratioTier(0x8030e450, dodge%)
- **[0x18] = tier(DAT_8030e4b8, costWon +0x420)** → row 4 right column
- **[0x1a] = tier(DAT_8030e6a8, costLost +0x424)** → row 6 right column
- [0x1b]/[0x1c] tiers of damage dealt/taken (0x8030e710/0x8030e780) — versus only
- **[0x1d] = +0x436 ? DAT_80433b58 (= 5000) : 0** → row 8
- [0x1f]/[0x20]/[0x21]/[0x22] tiers of ally-cost/friendly-hits/friendly-dmg/max-combo — versus only
- **[0x23] = [0x18] + [0x1a] + [0x1d] = GRAND TOTAL** — nothing else contributes.
- Run accumulator: `matchState +0x17e0[playerIdx] += [0x23]` (chunk_0022.c:1088-1089).

**GRAND TOTAL = costWonTier + costLostTier + (firstStrike ? 5000 : 0).**
No win/lose sign handling; negative totals come only from the costLost tiers.
ATTACK, ratios, and defeat counts are display-only.

Capture validation (challenge-11-WIN): TOTAL COST 6000 right column (costWon in
501..600 → 6000), player TOTAL COST 0 → +1000 flawless tier (1 ALLY lost — confirming
ally cost is EXCLUDED from +0x424), no first strike → GRAND TOTAL 7000. ✓

## 4. DOL-extracted tables (all BE s32 pairs `(threshold, value)`, terminator −1)

`tierScore(x)`: last value whose threshold <= x; below the first threshold → 0.

- **DAT_8030e4b8 costWon → score**: 0→0; 1→100; 101→2000; then +1000 per 100 cost
  (201→3000 … 5901→60000 cap). **ROM data quirk: 4901→40000** (the ladder predicts
  50000) — reproduced verbatim in the port.
- **DAT_8030e6a8 costLost → score**: 0→**+1000**; 1→−100; 201→−300; 401→−500; 601→−700;
  801→−1000; 1001→−1200; 1201→−1500; 1401→−2000; 1601→−2500; 2001→−3000; 3001→−5000.
- **DAT_80433b58 first-strike bonus = 5000**.
- Versus-rank tables (not in the grand total, extracted for completeness):
  DAT_8030e318 (attempts) & DAT_8030e3e8 (dodges): 0→0, 1→100, 101→300, 201→500,
  301→700, 401→1000, 501→1200, 601→1500, 701→2000, 801→2500, 901→3000, 1000→5000.
  Ratio tables 0x8030e380/0x8030e450 (identical): >=99.99%→5000, >=95.99→2500,
  >=89.99→2000, >=79.99→1500, >=69.99→1200, >=59.99→1000, >=49.99→800, >=39.99→600,
  >=29.99→400, >=19.99→200, >=0→100.
  Damage dealt 0x8030e710: 0→0, 1→100, 101→2000 … 3001→30000. Damage taken 0x8030e780:
  0→+1000, 1→−200 … 3001→−5000. Ally cost 0x8030e7e8: 0→+1000, 1→−100 … 3001→−5000.
  Friendly hits 0x8030e850: 0→+1000, 1→−200, 2→−500, 6→−1000 … 46→−5000. Friendly dmg
  0x8030e8b8: 0→+1000, 1→−200 … 3001→−5000. Max combo 0x8030e920: 0→0, 3→600, 4→800,
  5→1000, 10→2000, 20→3000, 30→4000, 40→5000, 50→6000, 100→7000, 125→8000, 150→9000,
  200→10000.

Extraction script: scratchpad `dump-results-tables.mjs` (session-local; the derived
values are frozen in `packages/missions/src/scoring.ts`).

## 5. Challenge run totals + clear/fail screen

- Challenge TIME: frames/secs/mins at matchState +0x182c/+0x182e/+0x1830, ticked by
  chunk_0048.c:717-771 (caps 99:59:59).
- Clear/fail screen number widget (chunk_0061.c:2790-2860): rows render secs/mins and
  **row 3 = the accumulated grand total `+0x17e0[player]`, sign-rendered** — the fail
  capture's "TOTAL SCORE". A run total can be negative.
- Per-battle advance test `FUN_801969a0` (chunk_0048.c:466-506) is orthogonal to
  scoring (winner-mask equality only) — decoded in behavior-notes (ae).

## 6. Port wiring (this session)

- `packages/combat/src/types.ts` — `SlotTelemetry` (per-player-slot ROM counters
  +0x404..+0x424), `telemetry.slots`/`firstStrikeBy`, `Projectile.aimedTargetUid`
  (ROM attack object +0xcc), `BorgRuntime.lastHitAttackerOwner`.
- `packages/combat/src/combat.ts` — applyHit books slot hits / hitsTakenAimed (with the
  ROM's clamp) / hitsTakenOther, honors flagsA 0x20, claims first strike; projectile
  spawns bind `aimedTargetUid` from the live lock; `slotTelemetryFor` helper.
- `packages/combat/src/battle.ts` — attack initiations book slot attempts AND the aimed
  enemy's incomingAimed (ROM: same activation increments both); kill accounting books
  kills/costWon to the LAST DAMAGER's slot and costLost to the victim's slot (ally cost
  excluded, per the ROM + capture).
- `apps/game/src/sim/presentation.ts` — `battleOutcomeFromState(battle, playerId)` now
  emits the slot counters 1:1 (DERIVED; old TUNED dodge/attack reading replaced; team
  aggregates remain only as a documented fallback for slot-less battles).
- `packages/missions/src/scoring.ts` — DERIVED formula + verbatim tier tables replace
  the TUNED `ScoreWeights` model (removed; grand total needs no fallback — every term
  is decoded). `accumulateScore` unchanged (matches +0x17e0 semantics, incl. negative).

Port deviations (documented in-code): hit dedup is per CONNECTION, not per
(event, victim) bitmask — divergent only for persisting rehit beams (no gameplay caller
yet); melee/special aimed-target falls back to the attacker's lock at connection time
rather than a stored per-swing target.

## 7. Honest unknowns

- **Which rows the Challenge screen shows vs versus** (row 8 first-strike bar is not
  visible in the WIN capture — bonus was 0 there, so hidden-when-zero vs absent is
  UNDECIDED; harmless either way since the grand total includes it).
- The fail screen's bottom "TOTAL 0" line (vs "TOTAL SCORE") — its source row/reset
  behavior isn't pinned (chunk_0061 rows 0-2 are time fields; the bottom TOTAL is
  likely the same +0x17e0 shown as the final award, but the LOSE-run reset path wasn't
  isolated).
- Whether `zz_00d285c_`'s medal pass (DAT_803cce30 flags) affects anything outside
  versus — not results-relevant.
- Exact ROM meaning of hit-record flagsA 0x20 membership per attack (which port
  attacks would be "untracked") — the port's decoded family records carry flagsA, so
  the gate is honored where data exists.
