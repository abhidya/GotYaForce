# G RED neutral X source timing, aiming and gravity

Continuation from942d409b, limited to fresh grounded pl0615 action2/variant0.
NEO G RED, G BLACK and other contextual variants retain their existing routes.
Publication remains paused; original assets are inspected in place, not added.

## Demonstrated mismatch

The old route injected gravityCoeff+1 despite original initialization0, used a
compatibility integrator with extra upper clamps, left pitch/face aiming unbound,
played recovery at startup from flattened events and ended near X+67 from the
last event frame rather than animation/recovery completion. Runtime grounded also
remained true while airborne. Authored contactP0 is a stream phase gate, not
proof of hitting an opponent; the old81-frame 'whiff' fallback was based on that
incorrect interpretation.

## Source phase contract

Chunk0047 functions8018e888/8018ea54/8018eb2c/8018ec34 are initial/ascent/descent/
recovery. Initialization checks horizontal range66838 against row86c selected by
signed584%3. Failure sets541 and clears captured target; absent target preserves
lock yaw when control&A0, otherwise current heading. It calls6d144(C1), initializes
hSpeed/hDecel/gravityCoeff0 and yVel4, carries saved own motion, probes ground,
then starts group4 slot0.

Phase1 requests metadata107a0(12) on transient1d9, ticks the stream, aims yawC1,
aims part1 pitchC1 when faceGate1d10 is set, calls primary67310(1,lockYaw), damps
and applies carry, then probes. Authored contactP0>0 advances into descent with
motion[0,10,60]. GravityCoeff0 stays0: passing argument1 does not re-enable it.
Phase2 clears faceGate on accepted transient contact before ticking the stream;
remaining faceGate enables yaw/pitch aiming. It applies the corrected scalar/BAM
motion, primary physics and ground probe. AuthoredP0<0 advances to recovery,
sets timer120 and descriptor gravity6c=−1.
Phase3 ticks, damps signed steering and integrates primary physics, then probes.
A nonzero accepted-landing result immediately clears action housekeeping and
returns through6a750(mode7), setting694=1+dt. Zero means no landing: RED waits
for part0 stream completion before6a5a4 air return. Host terrain is an explicit
adapter, not an assertion of original collision geometry.

## Original stream and clocks

Group4 slot0 at8036704c starts HIT15/status0/arg255, g4s0 mode1/blend2/start0/
rate0, contact0, dash0/face0/control40 and709bit1. Absolute gates are:
-7: callback1 arg0.
-34: face1; callback1 arg1.
-40: contact1; functional callback2 arg0.
-41: callback1 arg4.
-52: callback1 arg2.
-62: mode8 countdown10.
-64: contact−1 and face0.
-68: callback1 arg3.
Animation end starts g0s14 mode1/blend15/start0/rate0; terminal wait is elapsed15.
Original g4s0 descriptor803679a2 maps motion bank4/slot0 raw end80; recovery
803675e2 maps bank0/slot24 raw end1. Both AOBJflags0 and descriptorloopclear1.
Rate0 retains the prior rate; admitted host behavior is bounded to rate1.

One following block is parsed per interpreter call. Mode8 subtracts dt before
testing; positive countdown freezes animation. At dt1 the entry at frame62
advances63, countdown9..1 freezes, zero release advances64, and the next call
applies64 writes. Recovery play has no extra animation advance in that call.

## Target refresh and presentation

Descriptor AE3072, gravity6c−1 and range rows[1000,1200,1300] were read from
PZZ587/member0;562b8 copies the range rows to86c/878/884. Pitch6e1ac(C1,part1)
uses descriptorAE×actor768, not dt, with signed16-bit convergence and clamp±4000.
Its target origin uses an animated part matrix; root fallback remains approximate.

Callback2 at40 resolves8018d120:6bf80 recaptures selected target504/508 into
capturedc8/cc, refreshes target coordinates/distances, resets541, reapplies the
selected range row and clears/falls back if out of range. It must not silently
retain the admission target or disappear as cosmetic metadata.
Callback1 at8018d030 updates6f6 through1/2/3/4 for args0/1/2/3. Args0 and4 create
model children1cf770/1cf360 and sound. Inspected descendants have render/model
state and no HIT registration. These presentation children may remain explicitly
omitted; callback2 is functional and cannot be omitted.

## Verification status

Implementation and independent source-clock/actual-input tests are underway.
No full-X or whole-game parity claim; target/matrix/terrain geometry, source
selection flags and unbound cosmetic/status consumers remain explicit seams.

## HIT15 and collision cadence

Original HIT15 maps record33 (shape0/bone6, radius70, damage16, frames8..16)
and record21 (shape0/bone1, offset[0,0,60], radius100, damage17, frames53..64).
Damage16 has HP40, flagsA1, flagsB0x4000 and refresh0. Damage17 has HP30,
flagsA1, flagsB0 and refresh7. Authored phase gates remain independent of hits.
Accepted transient fighter contact is consumed on the following actor update;
in phase2 it clears aiming before stream processing.

Source8008a65c initializes refresh countdown7 when the late record activates,
without decrementing on that same update. Each following eligible active HIT
update first checks the animation end, then decrements; below1 it reloads7 and
allocates a new attack identity. This continues during mode8's frozen frame63.
It is not animation-frame modulo or permanent whole-window deduplication.
Original burst/hitstop/actor281 pause gates are not fully bound; ordinary live
cadence is the verified scope. Global game pause must not advance simulation.

The scoped host collision uses the original sphere radii/local offsets with
root/yaw substituted for animated bone6/bone1 origins. It performs a 3D distance
check rather than the old XZ-only contact against targets far below. Separate
collisionScale+c0 is preserved, falling back to modelScale when unavailable.
Target volume, animated matrices and full source pair filtering remain unverified.

## Focused implementation checkpoint

The dedicated RED grounded-X state now owns source clocks, captured target and
functional refresh, phase aiming, primary physics, accepted-contact feedback and
landing/air release. Generic flattened scheduling and the81-frame fallback are
bypassed only for this admitted route. NEO/BLACK/air variants remain unchanged.

Pure clock tests pass, including dt1/.5 traces, exact callback gates, countdown
entry/freeze/release, raw end/STOP behavior, recovery elapsed timing and independent
clock instances. Real Battle tests pass for miss and accepted-hit paths waiting
for authored40, gravity0/launch speed4, actual target-cycle refresh and out-of-range
fallback, airborne/landing synchronization, early refresh0 dedup and late refresh7
contacts with fresh identities during frozen frame63. Vertical separation1000 is
rejected. No-floor fixtures verify full hold/recovery/air return; death and excluded
family/air routes are covered. Geometry, receiver immunity/survival and no-floor
fixtures are explicitly labeled, not represented as original-console replays.

Previous motion arithmetic and all three neutral melee-chain regressions pass.
Full contributor verification is running. Runtime probe maximum height near a
target1000 units away drops from about1039 to182, consistent with removing invented
upward acceleration; this measurement is a host fixture, not a console benchmark.

Remaining limitations include original animated model/effect children and sounds,
metadata107a0 consumer, full burst/hitstop pause rules, selected-target flags6b8 and
force-range flag1dd as explicit unbound seams, target shape/matrix geometry and
floor/support tests. Existing helper nonunit pitch-rate f32/atan differences are
not silently promoted to exact source numerical parity.

Independent source review of the completed bridge found no functional blocker in
activation countdown, refresh during hold, record history, callback range/fallback
or teardown. The bridge retains a240-update safety ceiling, not an original
completion rule; normal verified sequences complete through source state before
that limit. Host team/target eligibility remains inherited rather than a new full
port of original collision pair filters.

## Final local verification

Full `verify:contributor` completed successfully on the frozen code: repository
policy, TypeScript, frontend/session/input/pause/Challenge gates, renderer/resource
suites, ROM checks, complete combat lifecycle with the new clock and real-X tests,
importer checks and production Vite build. Existing bundle-size warning remains.
Nothing was published or deployed, and no original assets were added. This local
checkpoint does not establish bit-exact console or full-game parity.
