# Acceleration Ninja dash collision seam

## Verified source route

Acceleration Ninja (`pl0004`) X selects action 2, variant 0. `FUN_80162804`
(`docs-site/public/chunks/chunk_0042.c:732`) enters phase 1 and calls
`zz_01628d4_` inline. In that phase's dash body (lines 796–800), the source calls
`FUN_80067310` to integrate motion, then `zz_00677b0_` to probe collision, and
clears vertical velocity when the probe returns nonzero.

The browser already ran the integrator, but substituted a scratch grounded flag
for the probe. Its ROM-owned Battle branch skips ordinary movement, including
that movement path's stage wall and ceiling checks. Bounds and floor support
checks cannot catch an interior wall with supported floor on both sides.

A real Battle reproducer with the shipped family, ordinary special-button input,
floor triangles and an interior wall at z=10 crossed the wall on entry (z=36.635)
and the next owned frame (z=73.270). No family phase injection was needed.

## Bounded implementation

The optional battle-local `RomPhysicsRuntime.probeMotion` callback runs only at
that verified phase-1 probe site. Its previous position is captured immediately
before integration. The callback resolves the already-integrated segment using
existing host wall and ceiling geometry, then applies the existing ROM host floor
clamp. It returns grounded and vertical velocity to the family. It does not run
movement, apply gravity again, tick timers, or dispatch attacks.

The callback does not change ROM horizontal scalar speed or heading. The family's
per-frame speed reset remains authoritative; a blocked dash can continue pushing
against a wall. Recovery, actions 0/3 and teleport families do not opt in. No
blanket bridge sweep has been added, because instantaneous warps must not inherit
physical-dash segment semantics.

## Fidelity boundary

This is host collision wiring, not a complete port of `zz_00677b0_` or its
`FUN_8003e0a8` surface query. The exact ROM surface-selection inputs, descriptor
slope thresholds, wall damping, touchdown callbacks and coordinate conventions
remain separate work. Existing host wall/ceiling clearance and floor policy are
unchanged. In particular, this patch does not reconcile the pre-existing floor
height convention difference between normal movement and the ROM floor clamp.
It does not reinterpret the stream-authored wall-contact byte as a geometry hit.

## Regression coverage

`pnpm --filter @gf/combat test:lifecycle` includes a real Battle test with actual
special input for walls crossed on entry and on subsequent owned frames. It
checks the returned grounded flag, vertical reset, ceiling clipping, open-space
39-unit movement per frame, missing optional callback, and isolation of both
Teleport Ninja variants and Acceleration Ninja recovery. Teleport isolation enters
the registered X bridge directly and verifies a phase ran, avoiding their different
input charge gates. A negative control
removes the callback and verifies the same real X input crosses the interior wall.
Ceiling coverage supplies upward velocity after entry, because source phase 0
explicitly zeros vertical velocity. Synthetic triangles exercise geometry without
game assets.
