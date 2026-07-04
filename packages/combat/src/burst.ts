// ATK-011: Hyper/Power Burst input + state shell.
//
// Ports the ROM's two-stage arm/consume shape for the Y button with ZERO gameplay effects.
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
// offset misread as one. Trace T3 is required to reconcile before ATK-012 wires any real
// duration/effect off this value; this port only implements the arm/decrement/activate SHAPE,
// gated fully inert behind BURST.ENABLED (see constants.ts).
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
// and the charged sweep wired in battle.ts step(). BURST.ENABLED still stays false: the
// gauge is DISPLAY-ONLY until ATK-012 lands real burst gameplay effects (Q5 speed boost
// still open); exact arm-window/pairing semantics remain for trace T3.
//
// Do not add gameplay effects here — burstActive/burstPaired are inert bookkeeping until
// ATK-012 (blocked on trace T3).

import { BURST } from "./constants.js";
import type { BorgRuntime, BurstMeterState } from "./types.js";

/**
 * Advance one frame of Power Burst arm/activation state for a single borg.
 *
 * Shape (mirrors the ROM's two-stage arm -> consume):
 *   - Y press edge (`hyperPressed`) sets `burstArmFrames = BURST.ARM_WINDOW_FRAMES` (6),
 *     re-arming on every fresh press even if a previous window is still counting down.
 *   - Otherwise, while `burstArmFrames > 0`, it decrements by 1 per frame (floored at 0).
 *   - Activation (`burstActive = true`) only happens while armed AND `BURST.ENABLED` is true;
 *     with the default `ENABLED = false` this branch never fires, so `burstActive`/
 *     `burstPaired` stay false in every real battle today (labeled BLOCKED-until-T3 in
 *     constants.ts — no meter/resource precondition exists yet to gate real activation on).
 *   - `burstActive`/`burstPaired` have ZERO effects on damage, movement, or any other system
 *     in this ticket; they exist only as state to be read by ATK-012.
 */
export function stepBurst(b: BorgRuntime, hyperPressed: boolean): void {
  if (hyperPressed) {
    b.burstArmFrames = BURST.ARM_WINDOW_FRAMES;
  } else if (b.burstArmFrames > 0) {
    b.burstArmFrames -= 1;
  }

  if (BURST.ENABLED && b.burstArmFrames > 0 && b.alive) {
    b.burstActive = true;
    b.burstPaired = true;
  } else if (!BURST.ENABLED) {
    // Inert shell: never activate while the feature is disabled (default).
    b.burstActive = false;
    b.burstPaired = false;
  }
}

// ---------------------------------------------------------------------------------------
// Per-player Power Burst meter (Q4 RESOLVED 2026-07-03 — open-questions Q4 lines 51-79,
// findings §S). See BurstMeterState in types.ts for the ROM field map (+0x126/+0x124/
// +0x12a/+0x103). Display-only until ATK-012 (BURST.ENABLED stays false).
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
 * the damage path), and the gauge is display-only for human HUDs until ATK-012. Revisit
 * (per-controlKey slots) if/when CPU bursts gain gameplay effects.
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
 * clears in this wave: the ROM clear path is burst CONSUMPTION (+0x104 mode / zz_005b2b8_
 * end sweep), which is ATK-012 territory (BURST.ENABLED false, no consume exists yet).
 */
export function sweepBurstCharged(meters: Record<string, BurstMeterState>): void {
  for (const key of Object.keys(meters)) {
    const m = meters[key];
    if (m && m.meter >= BURST.METER_MAX) m.charged = true;
  }
}
