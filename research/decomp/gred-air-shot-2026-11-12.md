# G RED-family airborne ordinary B

## Reproduced gap and admitted route

Before this lane, real jump then far B for RED/NEO/BLACK selects row80365d98,
action0/variant3, but the bridge forces a full-body action. It zeros vertical
velocity, holds the actor at jump height for four calls, then fires through the
fallback clock. Missing air-entry visibility clears the child target, so a
receiver1000 units away is missed. Jump-only control traces continue moving.

The original default air row is [45,1,0,3], an upper-body mode1 action. Original
55568 runs lower movement before upper action. Subtype3 all directions and
subtype4 directions0/1/3 select variant3. Subtype4 direction2 is separately
[45,3,0,4]. The browser's lowest-direction selector does not reproduce direct
direction2 admission; this lane must not replace ordinary variant3 withvariant4.

## Original phases and aim

Variant3 uses18d6f0 with phases18d72c/18d7e4/18d8c0. Variant4 uses18dab4 with
18dafc/18dbb4 and the same18d8c0. Existing18dcb0 releases the verified c3be0
projectile and owns its debit/repeat timers. No new projectile geometry is needed.

Upper-body aim6dee8 uses eligible saved-target yaw minus actor heading. Inclusive
cone is ±0x4800, result clamps to ±0x4000, and side angle1dfc approaches by0x800
per call. It returns0x8444 when aligned, zero while turning and−1 outside the
cone. No eligible target gives desired relative angle zero. Out-of-cone phase1
redirects to full-body variant4 while airborne or grounded variant0 otherwise.

Variant4 phase0 aims with81, runs primary67310(1,5ae) and677b0 terrain, starts
upper g2(6+6ee) mask1 and lower g0s13 mask2. Phase1 ticks all parts with dt0 while
P0 is nonzero, then runs physics/terrain. It always decrements aimtimer30 before
short-circuiting the81 aim helper, releases on the source gate, clears control
bit2 and invokes6a5a4. Shared phase2 retains source repeat/handoff conditions.

## Stream distinctions

With the explicit40-only host-air posture mapping, variant3 g2s4/5 alias the
grounded startup/repeat0/1 streams. Original control80 selects6/7 instead;
browser airborne state alone does not establish that distinct original posture. Variant4 g2s6/7
resolve centered MOT3/5 ending11 and MOT3/16 ending15. Side clips share these
ends; all AOBJ flags are zero. No hidden functional callback or HIT registration
exists in these upper/lower streams.

Upper clocks use the verified opcode0d mode6 startup and mode9 final countdown.
Standalone initialization call0: dt1 P0+16/P0−20/completion36; dt0.5
P0+33/P0−41/completion73. Engine dt0 holds can change wall-clock timing.

Air repeated restart uses the literal18d8c0 identity comparison. Default start
requires P0<0 AND raw desired slot equal to current animation slot+group*0x1000.
For these descriptors desired5/7 does not equal0x2006/0x2009, so even a late
retap uses frame4/blend1. Grounded variant0's simpler rule must not be reused.

Lower g0s13 at8036642c plays descriptor0/14→MOT0/24, mode1 blend10/start0,
replaces posture bits4–11 with40, and ends on an animation-ended wait; AOBJ
end1/flags0. Its opcode02 advances without writing P0/P1 when mask2 is used. Initialization call0 yields dt1 blend
clear10/end11/completion12 and dt0.5 clear21/end23/completion24. Upper dt0 hold
also freezes this lower stream.

## Fidelity boundaries

Host lower locomotion is an explicit adapter for the original lower-before-upper
ordering, not a newly verified console locomotion port. Upper centered animation
is visible; lower metadata/clock remains separate because the current renderer
has one source sample. This is not two-layer pose or directional side-blend
parity. Aim geometry, stage collision, input/posture selection and transition
adapters retain stated limitations. Direct direction2 selector remains unrestored.
No original assets are copied or uploaded; publication remains paused.

## Verification

Independent actual-input tests pass for all three families: jump/B lower motion
matches a jump-only control; firing retains targets and deals damage; ammo is
consumed at release; landing then retapping reaches the grounded variant0;
out-of-cone captured targets reach source variant4 and its return to part mode.
Repeated airborne longevity uses a labeled elevated-root fixture after a real
jump, verifying gaps14/10/18 without pretending the normal short host jump lasts
that long. Held B does not auto-repeat. Captured selection, source samples,
death cleanup and immediate fresh admission after cleanup are also covered.

Pure engine, upper and lower clock tests pass, as do grounded timing, source
projectiles, carry and all family charged-shot regressions. Six additional
synthetic renderer cases cover MOT3/5 and3/16 clock ownership for all families;
the existing grounded middle-clip cases remain. Final source review approved
the bounded implementation. `verify:contributor` passed policy, TypeScript,
UI/renderer, ROM/full combat lifecycle, importer and production build
(19.73 seconds). Existing large-bundle warning remains.

No original-console replay, live deployment or actual browser screenshot was
performed. Lower layered animation, full original locomotion and direct
input selection of direction2 remain unverified/unrestored as stated above.
