# G RED-family airborne X routing

Local continuation from `997f357b`; publication remains paused. No original assets
or executable bytes are added.

## Confirmed bug and original route

Real jump then neutral X selects exact command row80365de0 `[45,3,2,4]` for RED,
NEO and BLACK. The browser previously rejected this path from its restored X
engine, forced cue44 and ran its old variant-insensitive fallback. A flat-floor
miss probe observed recovery animation on the admission tick, followed by runaway
ascent. These are host regressions, not an original-console trajectory benchmark.

Fresh original ISO inspection confirms all five entries of variant table80365830
point to8018e838. That wrapper dispatches phase table80365844. Source18e888 selects
stream4/0,4/1 or4/4 solely by borg number, with no aerial/variant branch. Therefore
the already restored G Crash phase machine and source clocks apply to exactv4 as
well as neutralv0; no new attack constants or guessed motion were needed.

Cue table80365cf8 rows44 and45 are both full-body61/upper-body0. The cue helpers
6a6fc/6a750 reset state/cursors but do not alter velocity or saved position5e8.
Command dispatcher6a104 snapshots584=585, which is button/type2, NOT subtype4.
The original descriptor range row remains index2 (1300). Subtype4 is retained in
its own field. Command mode3 remains unchanged. Family pre18cef8 and post18cf54
do not introduce a cue45-specific physics branch.

## Bounded implementation

Admit only exact grounded action2/v0 and exact airborne action2/v4 for the three
G RED-family members. The airborne path dispatches cue45 and preserves command
type2/subtype4 before the existing dispatcher snapshots type2. Route admittedv4
through the restored phase engine. Keep other variants and unadmitted callers on
their existing paths. Existing source target refresh, hit lifecycle, animation
samples, motion carry, landing, timeout and interruption behavior are reused.

The original selector69ea4 uses controlbit80 for subtype4, whereas the host still
uses its existing grounded/air context selection. This lane repairs the selected
command's execution, not the whole input/context selector. Target/bone geometry,
terrain, inherited animation rate, burst/hitstop and cosmetic children retain
previous limitations. No whole-game 1:1 claim or console replay is made.

## Deferred next candidate: RED airborne B

Read-only audit identified a separate, larger lane, not implemented here:
18e148→178394 uses config80365744 with seed12/range200/pursuit20/brake0,
carryf32(.95), speed60, transition.25 and dampingf32(.9); initial wait30.
Stream80366edc plays metadata3/22 (motion1/23, original AOBJ end30), mode1
blend5/start0/rate0, HIT18/status25/255. Its contact gates are10positive,
15dash24,20dash−1 and26contact−1/709clear1f. HIT18 records26/27 are bone18/radius100
frames15..16/damage22HP10 and bone15/radius150 frames19..21/damage23HP30;
both offsets[0,−30,0], flags1 and refresh0. DescriptorAC is2560.
The pitch54e helper6e514 uses AC*dt, unlike X's part-pitch rate scale; helper6ed8c
performs dt-aware velocity decay. This requires a separately verified five-phase
engine, source clock and real B-input tests. It is not enabled by the X routing fix.

## Final local verification

Dedicated real jump→X tests pass for all three forms: exact row and cue45,
button2/subtype4 distinction, nonzero own-position carry observed around the real
phase0 call, family launch speeds, source clock/sample ownership, callback40,
real R target refresh, active-window damage, descent/landing and death cleanup.
Damage fixtures deliberately position a receiver after source motion; they test
real resolution, not original animated-bone collision parity. Existing grounded
RED and NEO/BLACK X suites pass, with obsolete air-exclusion checks replaced by
positive scoped admission checks.

Full `verify:contributor` passes on the final code: TypeScript, repository policy,
frontend/session/input/Challenge, renderer checks, ROM and combat lifecycle,
importer tests and production build. Only the existing bundle-size warning remains.
The same local jump→X probe no longer emits recovery at admission or accumulates
legacy upward acceleration; all three complete through restored landing handling.
No browser visual replay, original-console benchmark, publication or deployment
was performed.
