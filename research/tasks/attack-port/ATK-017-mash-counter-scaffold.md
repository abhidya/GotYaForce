# ATK-017: Button-mash counter scaffolding — DISABLED by default

## Purpose
Model the ROM's proven mash counter shape (press-edge counter, cap 4) behind an off-flag so
the mechanism exists when its consumer is identified (open-questions Q9). No gameplay
effect.

## Evidence
- Counter: attack-active handler slot 23 (`FUN_8005d494`): `if (+0x1d10 == 1) +0x550 += 1;`
  phase advances when `4 < +0x550` or +0x552 != 0 (chunk_0007.c:4809-4816, corpus read,
  audit).
- Press edges: +0x5bc = +0x5b4 & ~+0x5b8 (chunk_0007.c:291).
- Downstream consumer of the counter: UNKNOWN (Q9) — hence disabled.
- Negative: no stick-rotation accumulator exists; do not add one.

## Dependencies
None.

## Files to edit
- `packages/combat/src/constants.ts` (`MASH = { ENABLED: false, PRESS_CAP: 4 } as const` —
  PRESS_CAP is DERIVED, cite the chunk line; ENABLED false labeled BLOCKED-until-Q9)
- `packages/combat/src/combat.ts` (during an active melee swing, count attack press EDGES
  into `b.cooldowns["mashCount"]`, clamped at MASH.PRESS_CAP, reset on swing start —
  counting always runs (cheap), but NOTHING reads it while ENABLED is false)

## Required behavior
- Press edges only (reuse the attackHeld latch pattern, combat.ts:533-535).
- Counter visible to the debug overlay (ATK-015 picks it up automatically via cooldowns).
- Zero effect on damage, duration, hits.

## Fallbacks allowed
- The whole feature disabled — that IS the ticket.

## Tests to add
- Mash 10 presses during one swing → counter reads 4 (cap).
- Held button (no edges) → counter 0.
- New swing resets the counter.
- Regression: battle outcomes unchanged.

## Do not change
- Combo-chain logic (comboStep/comboWindow) — mash is a separate mechanism.

## Done when
Counter tests pass; no behavioral diff in selfcheck battles.
