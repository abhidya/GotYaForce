# RED airborne B source lane

Local continuation from `25bfafd1`. Publication remains paused; original assets
are inspected in place and are not added to this change.

## Original engine and data

RED action1/variant4 wrapper18e148 selects five-phase engine178394/config80365744.
The independent original-data audit found seed12, range200, pursuit timer20,
brake timer0, carryf32(.95), speed60, transition scale.25 and dampingf32(.9).
Phase0 wait is30. This is not the grounded neutral-chain engine177dd8.

Source functions1783e4/178574/178684/178808/178908 are in rea chunk0044:3206 onward.
Entry zeros velocity scalars/pose accumulators, captures range using584%3, starts
the authored stream, aims withC0 and carries OWN prior position5e8 displacement.
Phase1 ticks the animation only while blend1b03 is nonzero, applies carry, updates
pitch, and transitions on timeout OR yaw settlement. Phase2 ticks while contact0
or blending, pursues with speed60 and pitch54e, and brakes on timeout or the source
full-3D range200 test668cc. Phase3 applies damping and its zero timer advances it
to phase4 after one call. Phase4 resumes stream, handles authored dash/gravity
requests, damps/integrates and exits through accepted landing or stream completion.

The source stream80366edc plays metadata3/22, resolving to motion1/23 with original
AOBJ end30, mode1 blend5/start0/rate0. It arms HIT18/status25/255; starts contact0,
dash0/face1 and709bit1; gates10contact1,15dash24/face1,20dash−1/face0,
26contact−1/709clear1f, then waits for animation end. Its auxiliary contact byte
stays0, so the engine's negative-aux retap continuation is not enabled here.

HIT18 records26 and27 use flags1/refresh0, offsets[0,−30,0]. Record26 is bone18,
radius100, active15..16, damage22/HP10; record27 is bone15, radius150,
active19..21, damage23/HP30. Distinct activation windows require distinct attack
identities, not one hit for the entire move. Geometry still needs the explicit
host adapter rather than claiming original animated bones.

Pitch helper6e514 uses descriptorAC2560 multiplied bydt, not X's part-pitch scale.
Helper6ed8c (chunk0009:3728) directly multiplies h/y speed by damping atdt1; its
fractional-dt path uses the source(1-factor)*dt subtraction with float boundaries.
Helper668cc (chunk0008:3315) tests full3D target distance; missing target returns
signed−1 and force1dd80 bypasses range. These differ from the older generic engine.

## Status

The bounded implementation and validation below are complete locally. No complete
parity, original-console replay, browser visual validation or deployment is claimed.

## Admission and retained presentation assets

Independent real-input tracing confirms jump then B selects row80365dc8
`[45,3,1,4]`. This lane is RED only. The command type1 snapshot selects range1200;
subtype4 is distinct from that snapshot. NEO/BLACK airborne B and RED ground B
remain on their separately scoped paths.

The existing baked RED motion1/23 clip was checked on both rig and cloud:
31 samples at60fps,26 joints, consistent with original AOBJ end30 inclusive.
No extraction or asset upload is needed. Source-frame rendering must use its
existing exact metadata hop and retain ordinary fallback if the clip is missing.

## Numeric and geometry boundaries

The dedicated engine preserves source phase order, conditional stream updates and
float boundaries for carry, launch, braking and damping. Independent source review
found no phase/clock blocker. The inherited yaw helper remains a host adapter:
its nonunit-dt signed-step truncation/clamping is not original-exact. Normaldt1
with descriptor rate2560 is the admitted tested case. Half-step clock tests prove
only animation scheduling, not fractional-dt whole-actor parity. JS trigonometry,
root target/collision approximations and absent original joint matrices remain.

The original92dcc transition presentation child and its RNG consumption are
recorded as an omitted effect, not replaced with invented particles. Status25/255
is forwarded as metadata, without claiming the unbound downstream status effect.

Final bridge source review found no new blocker in the bounded integration:
exact RED air close-B admission, cue45/type1 snapshot, captured target ownership,
conditional clocks, distinct refresh0 hit histories and cleanup are consistent.
The inherited host20-frame exit cooldown and240-update safety watchdog remain
host policy, not original timing. The watchdog is not reached by normal fixtures.
Natural close-target motion can complete airborne; the landing branch is tested
separately with an explicitly accepted floor probe, not by forcing a golden path.

## Final verified checkpoint

The saved engine regression contains16 groups covering phase ordering, timeout
short-circuit, signed fields, conditional clocks, all four braking scalars, damping
at unit/nonunit steps, dash/gravity events and landing precedence. Independent
stream traces pass at dt1 and.5. Real jump→B tests pass for exact RED admission,
pose clearing, capture, all phases, clock stall, zero-timer brake, both actual HIT
windows, no auxiliary-zero chain, return branches, death and neighboring isolation.
Fixture exceptions are labeled: captured-root range fallback, accepted/no-floor
probes, root-volume placement and immunity resets for deduplication.

Full `verify:contributor` passes with these durable suites registered, including
repository policy, TypeScript, frontend/session/input/Challenge, renderer checks,
ROM/combat lifecycle, importer tests and production build. Existing neutral B,
ground X and all three air-X regressions remain green. The renderer's RED1/23
sampling test passes alongside the prior source-animation lifecycle tests. Only
the existing bundle-size warning remains. All changes remain local; no publication
or deployment was attempted.
