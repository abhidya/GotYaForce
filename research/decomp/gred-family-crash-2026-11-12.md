# NEO G RED and G BLACK neutral X

Continuation frome45360a8. Scope is fresh grounded neutral action2/variant0 for
pl0629 and pl062a; RED's restored route is a regression requirement. Publication
remains paused. No original assets are added by this work.

## Verified source differences

Original PZZ604/605 descriptor member0 supplies AE3072, gravity6c−1 and range rows
[1000,1200,1300], matching RED. NEO starts group4 stream1 at8036728c; BLACK starts
stream4 at80367210. Their124-byte streams differ only in blend16 versus6.
Both play animation g4s3 at **start frame36**, mode1/rate0. Original motion bank4
slot3 has raw end80, AOBJflags0; recoveryg0s14 bank0slot24 has end1. Descriptor
loop-clear is1. Mode1 holds frame36 through blend; elapsed begins0.

Startup arms HIT29/status0/arg255, contact0, flags6e8=2, faceGate1 and control40.
Gates are40(contact1/callback2 target refresh),41(callback1 arg4),52(callback1
arg0 then arg2),62(mode8 countdown10),64(contact−1/flags6e8=3/face0/callback1
arg3). There are no RED gates7/34/68. Animation end starts recoveryg0s14 with
mode1/blend15/start0, resets part flags/contact−1 and waits elapsed15.

Shared phase initialization sets all horizontal/vertical speed, deceleration and
gravity to0 and clears pose7c/7e/80. Aiming, source scalar acceleration and target
refresh follow the verified common phase engine. Non-RED phase3 differs from RED:
on no landing it decrements timer120 bydt and returns while result>=0, exiting
only strictly negative, independently of animation completion. Landing still
returns immediately via cue7 and694=1+dt.

## Paired HIT29 identity and renewal

Original HIT29 maps records41/42, both shape0/bone1/flags1, damage17, active53..64.
Record41 offset[0,0,50], radius110; record42 offset[0,20,210], radius80.
Damage17 has HP30 and refresh7. The volumes must remain distinct, but their
attack identity belongs to the actor, not independently to each shape.

Original8008a65c initializes both counters0; only the first newly active record
while actor1ca==0 seeds7 and allocates identity. Second record therefore starts0.
PPC8008a980..994 explicitly decrements an8-bit value then sign-extends it before
comparison, so second record0 becomes−1 and reloads7 on the next eligible update.
Counter pairs evolve[7,0]→[6,7]→[5,6]..., renewing the shared actor identity at
relative updates+1,+7,+8,+14,+15,... after initial activation. This is not a
single seven-update period and not two independent simultaneous hits.

Source29434 resets registries, calls89aec to update all HIT objects, then resolves
collision pairs. Actor1ca is not reset between the two callbacks. Both sphere
volumes therefore use the final actor-wide identity after lifecycle updates.
Victim history resets once per identity change. The same ordering applies during
frozen animation frame63. Source burst/hitstop eligibility remains an explicit
host limitation, as in the prior RED lane.

## Visible source-frame binding

The old renderer starts every clip at0 and advances on render time, which cannot
represent the original start36 or mode8 hold. A narrow optional simulation-owned
animation sample is being added for admitted G Crash routes, retaining generic
rendering for other actors. Exact clip sample rate, asynchronous load epochs,
interruption and recovery must be tested. Original model/FX presentation and
crossfade fidelity are not implied merely by seeking the pose frame.

## Status

Implementation and independent simulation/renderer tests are in progress. Host
root/aim/collision/terrain adapters, cosmetic children, nonunit numerical effects
and full original pause/burst rules remain limitations. No console parity or
whole-game completion percentage is claimed.

## Focused verified checkpoint

Both family clocks and actual-input suites pass. Four independent dt1/.5 traces
verify start36, distinct blends, original gate/callback order, mode8 hold, raw ends
and recovery. Real tests cover zero launch velocity and pose clearing, actual
target-cycle refresh/range rejection, landing, and no-floor timer retention at0
followed by exit only when negative. Distinct41-only,42-only and overlapping-sphere
geometry fixtures verify shared identity without same-pass double damage; accepted
contacts follow relative updates[0,1,7,8,14,15], including two renewals while frame63
is frozen. Target placement/immunity/survival fixtures are labeled rather than
claimed as original-console collision evidence. Air variants and interruptions
are checked; RED X/motion and all three neutral melee chains remain green.

Simulation-owned animation samples now carry a new serial per original clip play
and the source frame. Renderer exact-stream loading seeks the baked pose sample,
pauses action-local advancement and follows simulation holds/recovery. Current
local main clips have60Hz/81 samples and recovery60Hz/2 samples; seeking derives
actual track sample times rather than assuming seconds conversion. Generic or
missing-stream fallback is not source-owned. Focused scene tests pass for start36,
hold, recovery, cached repeats, latest-frame async completion, stale epochs,
interruption/fallback, pause and cleanup. Existing crossfades remain cosmetic and
are not a reproduction of original bone blending.

Source review found no new blocker in the simulation extension. Runtime probes
show NEO's authored40 transition atX+21 and BLACK's atX+11, reflecting their
10-update blend difference. Both remain near rootY10 rather than the oldY871;
these are host fixture measurements, not console trajectory benchmarks.

Opcode0b wording was rechecked directly in original PPC8004c75c: nonzero b1 ORs
mask bits, zero b1 clears them. Startup0b010100 therefore sets709bit1. The historical
July report was corrected and marked superseded for old G Crash interpretations.
Generic stream-vm.ts still reverses0b and is intentionally left for a separate
scoped, tested fix; this admitted source route already tracks it correctly.

Full contributor verification is running. Original burst/hitstop gates, global
collision scheduling, animated bone/target geometry, terrain, original cosmetic
children and source crossfade fidelity remain limitations.

## Final local verification

Full `verify:contributor` passed on the frozen implementation: repository policy,
TypeScript, frontend/session/input/pause/Challenge gates, new source-animation
scene gate plus existing resource/lifecycle scenes, ROM checks, all combat tests,
importer checks and production Vite build. Existing bundle-size warning remains.
No original assets were added, nothing was published or deployed, and no whole-game
or bit-exact console parity percentage is implied by these two verified routes.
