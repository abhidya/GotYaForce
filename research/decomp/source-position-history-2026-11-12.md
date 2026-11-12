# Source own-position history prerequisite

Audit baseline: `31a242036f1b931ec799d8c1706a68b596c1cec7`. This change fixes the
browser bridge's ownership and update timing for two actor position samples. It
does not establish general source equivalence for movement, aiming or attacks.

## Source evidence and ordering

The checked-in source corpus is under `docs-site/public/chunks/`:

- `chunk_0007.c:201-206`, `zz_005685c_`: copy own position `+0x2c/30/34` into
  `+0x5e8/5ec/5f0`, then copy current own position `+0x20/24/28` into `+0x2c/30/34`.
  These writes are unconditional, before any target-pointer checks at lines 212+.
- `chunk_0007.c:699-704`: spawn setup seeds both samples from the placed actor's
  current position. The preceding floor-placement probes finish at lines 685-698.
- `chunk_0006.c:6680-6682`, `zz_0053a2c_`: the actor loop calls `FUN_80054070`.
  That wrapper calls `zz_005685c_` at line 6965 before the actor action dispatch
  at lines 6966-6967. Other actor wrappers also put the history update first:
  `chunk_0007.c:885`, `961`, `1226` and `1991`.

Consequently `+0x5e8` is an older **own-position sample**, not an enemy cache.
`+0x2c` is the current actor frame's pre-movement position, not a last-grounded
position. A family subtracting `pos - +0x5e8` is consuming recent displacement.
The source position-revert helper also uses `+0x2c`, which explains why some
ground-only browser fixtures hid the bad input.

## Baseline failure reproduced through Battle

The old `RomDriverBridge.syncIn` overwrote `targetCache5e8` with the active target
position and updated `savedGroundPos` only when grounded. It ran at admission
and active ROM ticks, but not during ordinary movement.

With an explicit wide supported floor, a stationary Revolver Gunman (`pl0100`)
or Billy (`pl0108`) at `(0,0,0)` and an enemy at `(0,0,6000)` moved to
`(0,19.5,-5700)` on the first X-input frame. At input frame 16 the recorded
position was `(0,26.4833729609375,-9890.023776562499)`. Both produced no shot in
that separate attack audit. The horizontal phase-zero error is directly
explained by `(0 - 6000) * 0.95 = -5700`; the vertical values also include the
host floor behavior and are not claimed as source physics.

Without explicit collision geometry the unsupported-floor revert could restore
the runtime position while leaving the incorrect `motion.z = -5700`, masking
the problem in position-only tests. The new regressions use a supported floor
and inspect both runtime position and the actor's movement accumulator.

## Bounded implementation

- Attachment seeds actor position and both historical samples from runtime
  spawn position, preserving independent vector objects.
- `Battle.step` calls `beginFrame(runtime, state.frame)` for every alive runtime
  actor before ordinary movement and lifecycle/action branches. Actors in the
  death state remain alive during their death animation and are included.
- The bridge shifts the two samples once per frame token. `syncIn`, admission,
  repeated calls and interruption cannot advance or reset history.
- Grounded and airborne paths use the same history update. Idle, hit and death
  frames still contribute movement; actual redeployment creates newly seeded
  history. Morph and interruption do not reset it.
- Existing field names and oracle mappings remain unchanged for compatibility:
  `targetCache5e8` and `savedGroundPos` now have corrected semantic comments.

This deliberately keeps the host's existing interleaved movement/admission
order. An attack admitted after ordinary movement sees that movement plus the
older sample, rather than having its carry zeroed by a second history update.
Direct bridge harnesses that simulate frames must call `beginFrame` explicitly;
`syncIn` remains synchronization, not a clock.

## Regression coverage and results

`packages/combat/src/sourcePositionHistory.selftest.ts`, registered in the combat
lifecycle suite, covers:

- Spawn initialization and non-aliasing of both samples.
- Stationary X admission with near and far targets on a supported floor for
  Revolver, Billy, Gatling, Powered, Beam, Cyber Girl and Sapphire Knight.
- Ordinary walking into attack admission, preserving nonzero movement carry.
- Airborne position history, including vertical samples rather than a stale
  grounded location.
- Repeated synchronization, frame preparation and admission in one frame.
- Interruption, hit/death frames, and real force replacement deployment.

The old target-lock assertion that `+0x5e8` follows an ally was replaced with an
assertion that lock synchronization leaves own-position history unchanged.

Passed during implementation: the focused new suite, `pnpm --filter @gf/combat
test:lifecycle` (including existing Powered/Gatling, target-lock and collision
tests), `pnpm selfcheck:rom`, `pnpm typecheck`, and `git diff --check`. Full
contributor validation passed repository policy, typecheck and browser gate,
then stopped at the three existing sparse-checkout HUD assets (ASCII font,
face-marker roundel and pl0000 banner). All remaining contributor stages were
run separately and passed: menu, Force Builder, game session, pause, input focus,
title, camera, Challenge, render disposal, Powered/Gatling scene checks, ROM,
lifecycle, OGhidra guards and game build. `verify:docs` remains blocked by absent
`research/asset-inventory/borg-assets.json`. Browser GPU/visual play-testing was
not performed.

## Scope and remaining work

This prerequisite does **not** change captured-target aim, source airborne-bit
mapping, Revolver/Billy stream contact gates, ammunition, projectile spawning,
flight, hit behavior, muzzle transforms or presentation. It makes their future
tests meaningful by removing a shared false movement input.

Separate source evidence shows that `zz_006ae60_` refreshes `+0x518` from the
captured attack target every global frame (`chunk_0009.c:1366-1382`), before actor
updates (`chunk_0003.c:4315`, `4322`). That is distinct from freezing the target's
coordinates at admission. It is not fixed here: current generic aim helpers use
the historically named `aimOrigin518` as an origin, so replacing its values
without reviewing the consumer contract would introduce another error.

Nineteen family modules reference `targetCache5e8`. Most directly consume the
source displacement, but Panther Vehicle's approximate aim-channel helper and
Ninja's missing-lock fallback also use it as a target. Those consumers require
separate source review; this patch does not silently rewrite their aiming logic.
Family comments calling displacement a target-distance blink are historical
misinterpretations, not evidence to preserve the old bridge behavior.

Independent review found no blocking live Battle regression. Isolated handler
probes confirmed the Panther/Ninja caveat: Panther's aim-channel fields have no
downstream readers, while the current Battle bridge does not admit Ninja's
contextual-B handler (`hasBCharge` is false). These unsupported family surfaces
are not claimed fixed or equivalent; their aim integration remains separate.
