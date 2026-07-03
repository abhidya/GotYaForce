# ATK-004: Movement-context enum and state capture

## Purpose
Make the sim KNOW its movement context (standing/dashing/air-dash/flying/rising/falling/
landing) each frame, so the future resolver (ATK-003) and melee-context mapping (ATK-005)
have an input. Capture only — no behavior change.

## Evidence
- Wiki taxonomy contexts (findings mechanic D-K) — WIKI_TAXONOMY_ONLY as a list, so this
  enum is explicitly a port-side capture, not a ROM enum.
- ROM has a variant channel (subtype +0x586, air gate; chunk_0009.c:500-534) that will
  consume this once mapped.
- The sim already computes the raw signals: `dashActive` cooldown (movement.ts:92-109),
  `grounded`, `state === "fly"`, `vel.y`, landing edge in `onLand` (movement.ts:202-205).

## Dependencies
None (parallel to ATK-001).

## Files to edit
- `packages/combat/src/types.ts` (add `movementContext` field or a derived helper — prefer
  a pure helper `movementContextOf(b): MovementContext` in `movement.ts` to avoid new
  mutable state)
- `packages/combat/src/movement.ts` (landing-edge frame counter: a `landedFrames` cooldown
  set in `onLand`, ticking like other cooldowns)

## Required behavior
- `MovementContext = "standing" | "ground_dash" | "air_dash" | "flying" | "jump_rise" |
  "neutral_air" | "landing"` with deterministic derivation rules documented per value
  (e.g. landing = within N frames after onLand; N is a named TUNED constant, default small,
  clearly labeled TUNED).
- Exposed for debug overlay (ATK-015) and future resolver use. Nothing consumes it for
  gameplay yet.

## Fallbacks allowed
- The landing-window frame count is TUNED by necessity — label it.

## Tests to add
- Frame-scripted: jump → context sequence standing → jump_rise → neutral_air → landing →
  standing; dash on ground → ground_dash; flyer boosting → flying; dash while airborne →
  air_dash.

## Do not change
- `stepAttacks`, resolver order, any damage path.

## Done when
Helper returns the documented sequence in tests; typecheck/selfcheck green.
