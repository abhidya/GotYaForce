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
// interface page adds that it "fills as the player inflicts and receives damage"). The meter
// itself is still unlocated in RAM, which is exactly why BURST.ENABLED stays false here; exact
// window/pairing semantics remain for trace T3.
//
// Do not add gameplay effects here — burstActive/burstPaired are inert bookkeeping until
// ATK-012 (blocked on trace T3).

import { BURST } from "./constants.js";
import type { BorgRuntime } from "./types.js";

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
