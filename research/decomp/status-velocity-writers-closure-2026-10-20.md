# Status / param-tier velocity writers — closure note (2026-10-20)

Round-2 wiring pass, item #5 residual ("haste/slow velocity writers — the
Acceleration Ninja speed mechanism"). **Verdict: the premise is closed. The
writers are decoded AND already wired; the one genuinely unwired piece is a
different, much smaller residual (below). No new wiring was needed, and none
was invented.**

## What the corpus actually says

Source of record: `research/decomp/status-effects-decode-2026-07-04.md` §A
("Velocity-scale writers — who writes tier/status that timescale reads? —
EXHAUSTIVE"), cross-checked against the current tree on 2026-10-20.

1. **The "+4 tiers / 1200f acceleration self-buff" is not Acceleration Ninja.**
   It is the STAR HERO (pl0804) / PLANET HERO (pl080c) X ramming-dash special
   (`zz_011230c_`, chunk_0031.c:576-617): on hit it raises the attacker's tier
   byte +0x74a by +4 for 1200 frames (velocity ×2.366, size ×2.6), reverted by
   `FUN_8010f790` (chunk_0030.c:4018). Acceleration Ninja (pl0004) is a
   different module (ctor 0x80162128) with a bespoke state machine; no corpus
   source ties it to tier deltas. The family attribution of the +4 buff to
   pl0004 was never established (movement-hit-decode-2026-07-04.md §1 says so
   explicitly).

2. **The tier-delta call-site census is exhaustive.** §A's verified table lists
   every caller of the tier writer: `zz_011230c_` (+4 hero buff),
   `FUN_8010f790` (−4 revert), `zz_005bab8_` (engine −1/+1 auto-revert toward
   16), `battle_frame_target_action_dispatch` (grow/shrink ±, from hit-record
   flagsA bits 2/3), and `reset_actor_param_tier`. "No other callers exist."

3. **Hit-inflicted status writers are discrete, and decoded.** From
   `resolve_hitbox_target_effects_and_damage` @0x8002e2a8 (chunk_0003.c):
   flagsB&4 → slow level 2 (900f), flagsB&8 → haste level 2 (900f),
   flagsB&0x400/0x800 → slow/haste auras, flagsA&4/&8 → grow/shrink tier
   deltas, freeze via the +0x718/+0x71c channel. Durations: 900f discrete /
   300f aura / hit-counted freeze. Timescale side: `+0x5f4` rebuilt per frame
   by FUN_8005a378; consumed as `statusTimescale × tierVelocityScale`.

## What is wired in the port today (verified 2026-10-20)

- `packages/combat/src/combat.ts` `applyHitInflictedStatus` — writes
  slow/haste hit levels, auras, grow/shrink tier deltas, and freeze from a
  hit's damage-record flagsA/flagsB, with the ROM durations.
- `packages/combat/src/combat.ts` `applyHeroXBuff` (line ~3036) +
  `startSpecialAttack` hit branch — the pl0804/pl080c +4-tier / 1200f
  self-buff, gated by `HERO_X_BUFF.BORG_IDS`; reverted at timer expiry in
  `stepHitStatus` (line ~2052).
- `packages/combat/src/timescale.ts` — `statusTimescale()` consumes the
  hit/aura levels (slow skipped for burst actors, per the decode);
  `actorVelocityScale()` = status × tier.
- `packages/combat/src/movement.ts` (line ~242) — ground movement consumes
  `actorVelocityScale(b)`; `paramTier.ts` + `bridge.ts` (~1921) and
  `combat.ts` (~1733) consume `tierSizeScale`.
- Acceleration Ninja itself is bespoke-ported in
  `packages/combat/src/families/acceleration-ninja.ts` (honest partial: its
  FUN_80067310 scalar-speed integrator is a documented host no-op there).

## The actual residual (small, precisely scoped)

- **The +0x74/+0x78/+0x7c accel-clamp triplet** (page fields at actor+0x678,
  active while +0x4c > 0): fields are defined in the `rom/` reference layer
  (`rom/actor.ts`, `rom/physics.ts`, `rom/physicsExtras.ts`) but no live-sim
  consumer exists in `packages/combat/src`. This is a movement-feel detail,
  not a status writer; wiring it needs a read of the consuming state code,
  not a table.
- **minTurnSpeed**: exported by `movementData.ts` and forwarded by
  `bridge.ts` (lines ~1635/~1803) as `minSpeed`; the 0.5× landing-seed
  nuance (FLOAT_80437460) is not separately modeled.

## Changes made with this note

Stale comments corrected (they claimed the writers were unwired):
`packages/combat/src/movementData.ts` header and
`packages/combat/src/timescale.ts` header + `actorVelocityScale` doc.
