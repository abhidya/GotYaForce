// ATK-011/012: Hyper/Power Burst input, meter, activation, and core effects.
//
// Ports the ROM's two-stage arm/consume shape for the Y button and the value-level T3/Q5
// findings: player meter max/fill, charged flag, active drain, and x1.5 movement speed.
// Evidence:
//   - Arm gate: `FUN_80069814` chunk_0009.c:104-115 — the Y-family bit in the transformed
//     input word (+0x5d4) sets object+0x6fb = 6 (a 6-frame arm window).
//   - Consume: `zz_005b2b8_` @0x8005b2b8 chunk_0007.c:3354-3494 — while +0x6fb is nonzero and
//     the borg is active, +0x6fc = 1 (activation) and +0x6fa = 1 (paired), with +0x6fb
//     decrementing once per frame in the same per-slot loop (chunk_0007.c:3473-3490).
//
// NOTE (behavior-notes.md (aj)): the audit's reading of +0x6fb as "just a 6-frame arm window"
// needs reconciling against a SECOND reading of the same field — the fusion per-slot loop also
// decrements +0x6fb and its expiry there drives the burst/fusion END path. It's unresolved
// whether these are the same timer serving two roles or two different fields at a shared
// offset misread as one. The value-level drain/speed model is now wired; exact per-action
// burst costs and the code path carrying the x1.5 multiplier remain unmapped.
//
// UPDATE (behavior-notes.md (ao), official NA instruction manual, CONFIRMED_MANUAL tier — still
// not numeric ROM truth): the manual documents the Y button as "Power burst — press when the
// burst gauge is at max to power up temporarily. With your friends, press the button at the
// same time for simultaneous power bursts." This gives the 6-frame window a coherent reading
// as a SIMULTANEITY tolerance for synchronized co-op bursts (a partner's Y within the window
// counts as "same time"), not merely a solo activation buffer — and confirms the real
// activation precondition is a full "Power Burst meter" (officially named; StrategyWiki's
// interface page adds that it "fills as the player inflicts and receives damage").
//
// UPDATE (Q4 RESOLVED 2026-07-03 — research/decomp/attack-mechanics-open-questions.md Q4
// lines 51-79, attack-mechanics-findings.md §S): the meter is now LOCATED and PORTED. It is
// PER-PLAYER (player struct +i*0x3c: +0x126 clamped u16 meter, +0x124 max = 3000, +0x12a
// unclamped accumulator, +0x103 charged flag one frame late) — see BurstMeterState in
// types.ts, BURST.METER_MAX/FILL_PER_HIT in constants.ts, the fill in combat.ts applyHit,
// and the charged sweep wired in battle.ts step().
//
// UPDATE (Q5 RESOLVED at value level 2026-07-04): paired activation drains the meter at
// -5/frame from 3000 and gives x1.5 movement speed. That core gameplay is ported here and in
// movement.ts; per-action extra meter costs are still not ported because their table is not
// mapped yet.

import { BURST } from "./constants.js";
import type { BorgRuntime, BurstMeterState } from "./types.js";

/**
 * Advance one frame of Power Burst arm-window state for a single borg.
 *
 * Shape (mirrors the ROM's two-stage arm -> consume):
 *   - Y press edge (`hyperPressed`) sets `burstArmFrames = BURST.ARM_WINDOW_FRAMES` (6),
 *     re-arming on every fresh press even if a previous window is still counting down.
 *   - Otherwise, while `burstArmFrames > 0`, it decrements by 1 per frame (floored at 0).
 *   - Activation is handled separately once all active same-team players have had their Y
 *     press sampled for the frame; see `tryActivateBurst`.
 */
export function stepBurst(b: BorgRuntime, hyperPressed: boolean): void {
  if (hyperPressed) {
    b.burstArmFrames = BURST.ARM_WINDOW_FRAMES;
  } else if (b.burstArmFrames > 0) {
    b.burstArmFrames -= 1;
  }

  if (!b.alive) {
    b.burstActive = false;
    b.burstPaired = false;
  }
}

/** True when this borg/player currently satisfies the ROM-observed Power Burst activation
 *  preconditions the port can model: enabled feature, alive active borg, an armed Y window,
 *  and a charged full per-player meter. */
export function canActivateBurst(b: BorgRuntime, meter: BurstMeterState | undefined): boolean {
  return (
    BURST.ENABLED &&
    b.alive &&
    b.burstArmFrames > 0 &&
    !b.burstActive &&
    !!meter &&
    meter.charged &&
    meter.meter >= BURST.METER_MAX
  );
}

/** Activate Power Burst if `canActivateBurst` holds. `paired` records the same-team
 *  simultaneous activation shape; it does not yet imply fusion. */
export function tryActivateBurst(
  b: BorgRuntime,
  meter: BurstMeterState | undefined,
  paired: boolean,
): boolean {
  if (!meter || !canActivateBurst(b, meter)) return false;
  b.burstActive = true;
  b.burstPaired = paired;
  meter.charged = false;
  return true;
}

/** Drain an active burst by the measured -5/frame meter drain and end it when empty. */
export function stepActiveBurst(b: BorgRuntime, meter: BurstMeterState | undefined): void {
  if (!b.burstActive) return;
  if (!BURST.ENABLED || !b.alive || !meter) {
    b.burstActive = false;
    b.burstPaired = false;
    return;
  }

  meter.meter = Math.max(0, meter.meter - BURST.DRAIN_PER_FRAME);
  meter.charged = false;
  if (meter.meter <= 0) {
    b.burstActive = false;
    b.burstPaired = false;
  }
}

// ---------------------------------------------------------------------------------------
// Per-player Power Burst meter (Q4 RESOLVED 2026-07-03 — open-questions Q4 lines 51-79,
// findings §S). See BurstMeterState in types.ts for the ROM field map (+0x126/+0x124/
// +0x12a/+0x103).
// ---------------------------------------------------------------------------------------

/** A fresh (battle-start) per-player meter: empty, uncharged. */
export function createBurstMeter(): BurstMeterState {
  return { meter: 0, unclamped: 0, charged: false };
}

/**
 * Credit the ATTACKER'S player meter for one hit connection (Q4 fill rule, T3 live traces
 * 2026-07-03): `meter = min(meter + FILL_PER_HIT, METER_MAX); unclamped += FILL_PER_HIT` —
 * flat +50 per connection, damage-independent (see BURST.FILL_PER_HIT's caveat re: possible
 * per-move overrides). Called once per applyHit connection per victim, matching the ROM's
 * per-connection semantics (a penetrating beam through a dead husk credited 3 x 50).
 *
 * CPU-owned attackers (`ownerPlayer === null`) are NOT credited in this wave — a documented
 * port decision, not ROM truth: the ROM meter lives in the per-controller player-struct array
 * (+i*0x3c), so CPU-occupied slots plausibly accumulate too, but the port's BorgRuntime only
 * carries `ownerPlayer` (null for CPU forces, whose synthetic control keys are not visible in
 * the damage path), and the player meter map only models human-owned entries. Revisit
 * (per-controlKey slots) if/when CPU bursts need to activate.
 */
export function creditBurstFill(
  meters: Record<string, BurstMeterState>,
  ownerPlayer: string | null,
): void {
  if (ownerPlayer === null) return; // CPU attacker — see doc comment above.
  const m = meters[ownerPlayer] ?? (meters[ownerPlayer] = createBurstMeter());
  m.meter = Math.min(m.meter + BURST.FILL_PER_HIT, BURST.METER_MAX);
  m.unclamped += BURST.FILL_PER_HIT;
}

/**
 * Charged-flag sweep (ROM +0x103): the flag flips to 1 ONE frame AFTER the clamped meter
 * +0x126 reaches max (live-observed delay, Q4). Ported deterministically via check-before-fill
 * ordering: battle.ts runs this at the TOP of step(), before any of this frame's hit
 * connections fill meters (stepAttacks/stepProjectiles run later in the same step) — so a
 * meter that reaches METER_MAX on frame N is first seen here on frame N+1. The flag never
 * clears on activation/drain in `tryActivateBurst` and `stepActiveBurst`.
 */
export function sweepBurstCharged(meters: Record<string, BurstMeterState>): void {
  for (const key of Object.keys(meters)) {
    const m = meters[key];
    if (m && m.meter >= BURST.METER_MAX) m.charged = true;
  }
}
