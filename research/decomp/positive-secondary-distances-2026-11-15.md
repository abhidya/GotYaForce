# Bounded positive secondary target distances

This extends only the nonnull-secondary path after completed null-primary
preparation in genuine `8006ae60`. It does not complete `80027764`, `80000bef4`,
the outer frame, arbitrary target estimators or primary direction `8006d228`.

## Evidence and admitted arithmetic

The retained `.tmp/target-preparation-evidence-20261114/operands.json` supplies
both source schedules. `actor-command-admission-evidence-2026-11-14.md:106–107`
authenticates binary64 `80437660=.5` (`3fe0000000000000`) and `80437668=3`
(`4008000000000000`), superseding older target reports calling them unselected.
`terrain-orientation-evidence-2026-11-13.md:333–389` supplies model-backed
`frsqrte` seeds for actual square values `.25,1,4,16,64`. Only these seed facts
transfer, not terrain's single-precision refinement. There is no new payload
selection, extraction, hardware capture or startup-register authentication.

At b218/b298 the actual computed square selects respectively the exact seeds
`16381/8192`, `16381/16384`, `16381/32768`, `16381/65536`, `16381/131072`.
Unsupported values refuse before either constant load and before the pending
result store. Each admitted estimator loads half then three from the same
command-admission data owner. Three rounds execute, in order:

1. q = RN64(e × e)
2. h = RN64(half × e)
3. c = −RN64_fused(s × q − three)
4. e = RN64(h × c)

The final RN64(s × e), frsp, local float32 store/reload yield `.5,1,2,4,8`.
The local stack roundtrip is internal numeric storage, not a fabricated source
actor field or callback. Existing exact dyadic binary64 helpers provide fused
rounding. All admitted intermediate values are finite normal values.

Optional `double80437660`/`double80437668` fields have no defaults. Optional
`fpscrControl` belongs to the existing canonical root vector processor, not a
new profile or an inference from GQR0. At each reached positive estimator it
must be an explicit unsigned32 with low byte zero (RN00, NI0, exception enables
disabled). Status bits are neither changed nor emulated. Own-data descriptors,
exact constants, root identity and callback-free terminal declarations remain
required. Zero-only and earlier paths do not require these optional values.

## Source flow and ownership

Actual cc remains an opaque comparison; admission c8 is captured once. The
integer OBJECT copy still loads X,Y, stores X,Y, then loads and stores Z.
The existing live `8020bc88` helper computes total square from the original
position and captured OBJECT. After total760, b268 freshly loads zero, then
A.x, B.x, A.z, B.z. Horizontal differences, squares and addition stay separate
float32 operations. Horizontal admission is independent; failure leaves760
intact. Successful764 rejoins the existing b2e8 → b33c second/third-pass flow.
All existing destination, lifecycle, reentry and captured-owner checks remain.
Shared constant inventories in admission, normal/cue0 lifecycle and tick
composition include both new constants; outer terminal checks catch late
constant aliases and processor declaration replacement/reference aliases.

## Tests and honest limits

`runSourceTargetDistanceRefinementSelfTests` pins independent exact seed,
three-round q/h/c/e, product and final float32 expectations for all five inputs.
`runActorSecondaryPositiveHydratedCompositionTests` is aggregate-wired through
attached setup and executes genuine bounded synthetic owner graphs, not retail
actor hydration. It covers both estimators, positive/zero combinations, live
changes between stores, opaque cc/captured c8, actual multi-component square
candidates, neighboring unsupported squares, source read order, optional
constant/control failures and exact partial-store fault behavior.

Zero rounds, one round, all-float32 arithmetic and squaring the halved estimate
can differ at final float32. Two binary64 rounds already produce the same final
float32 here: intermediate traces and the source schedule distinguish omission
of round three. Nonfused correction and some reassociations can even coincide
at every numeric intermediate in this power-of-two domain. They require static
instruction-order witnesses, not claims of numerical mutant kills. Model-backed
seed admission is not independent hardware evidence or a general square root.
