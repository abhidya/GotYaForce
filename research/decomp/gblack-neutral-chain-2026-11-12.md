# G BLACK neutral chain investigation

Local continuation from `6e311b10`. Publication remains paused.

## Verified mismatch

An actual close B press for pl062a resolves command type1/subtype0 row80365db8,
action1/variant0. The existing bridge starts group3/slot0 with legacy config.
Original wrapper8018de68 instead selects shared engine80177dd8 with config
8036564c: seed13, range150, timer20, f32(.95) damping, both callbacks null.

The original chain uses slots13,14,15. Negative auxFF then FE permits rearm;
FE does not imply NEO variant6 when the callback is null. Third swing aux0
terminates chaining. Accepted contact and fresh B edge gates must be preserved.

## Original animation and HIT data

Read in place from the authorized original disc; no assets copied into this lane.
All three animations have AOBJflags0 and descriptorflags1 (nonloop), rate0,
start frame0. Stream13 plays g3s24, mode1/blend4, motion1/25 raw End35.
Stream14 plays g3s4, mode1/blend5, motion1/5 End40. Stream15 plays g3s23,
mode1/blend4, motion1/24 End70. Positive mode2 waits are absolute frames.

- HIT31: records46/47, both active9..11, damage35.
- HIT17: records35/23, both active8..10, damage19.
- HIT30: records43/45, both active20..24, damage34.

All six records have collisionflags1. Damage35/19/34 have flagsA1, flagsB0,
refresh0. Simultaneous records must share activation-wave victim deduplication,
not independently damage each victim twice. Existing tracked HIT data agrees
with these remaps/windows; animated-bone geometry is not thereby recreated.

## Functional dependency, not cosmetic

Stream15 frame22 invokes opcode11 callback3/0 through8018cff0 to8018d1d8.
It requires control40 clear and actor1db==0, transforms a root-local offset,
then calls800fc208(type5). Parent800fc32c creates children800fc6a0 at intervals;
child800fc810 calls8008ae3c using the HIT selector in type5 row8031eb60+5*0x30.
This is a damaging ground wave, not an optional visual trail. Its lifecycle,
constants and host integration remain under investigation. The gameplay chain
must not be described as complete while silently omitting this callback.

## Status

Source investigation only at this checkpoint. No new gameplay admission enabled,
no new tests claimed, no publication or deployment. Original console replay and
visual comparison remain outstanding.

## Ground-wave numeric and lifecycle findings

Type5 row8031ec50 selects shared HIT84, counter4, turn factor1, projection limit100,
travel limit5000, scalar speed50, acceleration1, scalar clamp50..150, spacing200,
vertical visual factor.5, horizontal factor f32(.4), and target threshold−1.
Parent lifetime is600; pulse lifetime30. Root-local emission offset is[0,0,50].
The stored movement vector is initialized at magnitude50 and retained/rotated;
the separate speed scalar increments after movement but does not rebuild that
vector in the traced update. Treating this as accelerating travel is unsupported.

The parent initializes without movement and emits its first pulse. Subsequent
updates move once, turning by at most one degree every fourth targeted update.
A target within100 is cleared before ordinary movement. Ground projection follows
movement. Height change≥100, wall contact, travel≥5000×scale, bounds, special
attraction or exhausted lifetime retires it before another pulse. On surviving
updates, distance≥200×scale from the last emission saves the current position
before allocating exactly one pulse. There is no spacing catch-up loop.
Retirement advances through disable and free states without an explosion.

Each pulse registers shared HIT84 before consuming its single RNG8 draw. Failed
registration retires without RNG. Successful initialization projects to terrain,
sets age0, draws yaw as RNG8 shifted8 and emits sound18. It is stationary and
contacts do not consume it. Age30 disables its HIT; disable/free cleanup follows.
Original owner death or form change invalidates both emitters and pulses.

Shared HIT84 remaps to record122: shape0, collisionflags1, damage9, start0,
end−1, local offset0 and extentX150. Shape0 helper8003a4b8 uses radius150×the
inherited source+c0; the visual scaling must not shrink this collision sphere.
Each pulse owns a distinct attack identity/history. Shared damage9 HP is20,
flagsA0x20, flagsB0, refresh0; actual HP change still uses the host damage pipeline.

Visual keyframes are t0[1,1,1], t3[1,5,1], t30[1.25,0,1.25], with source linear
interpolation and at most one key transition per call. X/Z multiply by .4×owner
scale and Y by .5×owner scale. Original model/texture presentation is not supplied
by these numeric facts. Root attachment, target object coordinates, terrain
projection, walls and special-attraction behavior require explicit host adapters.

## Independent clock checkpoint

Six dt1/.5 traces pass for the three streams, including exact gate writes,
wait-before-advance ordering, raw ends, blend setup, frame22 emission exactly once,
overshoot one-block ordering, stable completion and no implicit fourth swing.
The existing NEO clock and actual Battle regression suites and combat TypeScript
check also pass at this intermediate checkpoint. Ground-wave gameplay integration
and its tests are not yet covered by that result.

## Additional fidelity boundaries

The callback's actor1db test is a supporting-actor collision flag. Source80035b3c
sets it when collision descriptorflags0x10 and normalized upward contact.y≥.5;
it is neither the generic grounded flag nor hitstun. A host default0 for ordinary
flat-floor combat is a scoped seam, not proof of all support-contact cases.
Source collisionScale+c0 is kept separate from modelScale+b4 and presentation
scale. Source8005bab8 copies b4 to c0/c4 during size transitions, but that does not
prove every host modelScale×sizeScale combination reproduces c0.

The source wall segment uses saved position+2c; pure engine exposes that snapshot
instead of silently asserting copied current position is identical. Original
terrain helper8003d964 returns inputY outside a valid grid and a stage-specific
sentinel for an in-grid query with no candidate. Host floor fallback behavior is
not a universal source equivalent. Original object-allocation scheduler ordering
is not established; any chosen host next-pass initialization must be identified
as an integration approximation. Exact PPC normalization/rotation is not claimed.

## Integrated local behavior and tests

The bounded ground action now admits pl062a action1/variant0 into the source
three-swing engine and dispatches its groundwave through the dedicated fc208
adapter. It does not redirect auxFE into NEO's finisher. Other entry variants
retain their existing routes. NEO/G RED prior configuration and chain tests pass.

Actual Battle tests pass for real hit-plus-fresh-B chains, each simultaneous HIT
pair accepted once, no variant6/fourth swing, held/missed/invincible/stick-only
controls, and death interruption. Wave tests cover once-only emission, explicitly
next-pass child initialization, real pulse damage and per-child victim dedup,
new pulse re-hit, collisionScale separate from modelScale, age30 disabling HIT
before fresh contact, child survival after normal parent expiry, owner death/form
invalidation and callback support/air gates. These are host integration tests,
not original-console input replays.

The renderer intentionally shows an existing generic flame placeholder using the
source visual scale curve and ground anchoring; it does not claim original type5
assets. Emitters and inactive pulses are excluded from observations. A focused
scene check passes for scale, independent collision radius, render-only/pause
stability and material disposal once under omission/repeated clear.

Target invalidation is limited: original80083874 additionally tests target state,
field656 and HIT-volume penetration with threshold0. The adapter handles
missing/dead targets and the separate every-fourth-update100-distance clear;
it does not reproduce the original shape-based validation. Melee same-team
filtering, target/body/root geometry, terrain, special attraction, inherited rate,
allocation scheduling and original presentation remain stated limitations.

## Final local verification

Full `verify:contributor` passed: repository policy, combat/app TypeScript,
browser/frontend/session/input/pause/Challenge checks, scene resource checks,
all combat lifecycle suites, ROM checks, importer checks and production Vite build.
The existing bundle-size warning remains. After adding the final mine interaction
case, the affected lifecycle suite was rerun separately against the frozen code.
The new mine test uses a clearly labeled constructor/geometry fixture alongside
a real B-created wave: different-owner HP1 mine destruction/explosion ordering,
same-owner drift exclusion and same-owner bob admission pass. No artificial
Time Bomber input or ammo-refund claim is made by that fixture.

This is locally verified implementation, not deployed code and not a claim that
the entire port or these host geometry adapters are 1:1. Publication remains
blocked pending the previously requested approval. No original assets were added.
