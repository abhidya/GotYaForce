# NEO G RED melee chain investigation and bounded port

Continuation from `f2162d4f`. Publication remains paused; original numeric facts
are inspected in place on the authorized rig, not uploaded as game assets.

## Original route

Actor629/action1/variant0 selects `8018de9c` → config `80365664` → engine
`80177dd8`. Its seed25, timer20, proximity150 and f32(.95) damping are verified.
The chain callback `8018ded0` redispatches `(actor,1,1,0)` through `8006a3d0`,
then selects variant6. That route uses config `803657c4` and a distinct
five-phase engine `80179280`, not the ordinary four-phase opener engine.

Finisher configuration: slot27, timer20, range200, carry and deceleration .95,
transition multiplier .25, recovery deceleration .95, horizontal speed0,
horizontal deceleration0, vertical speed60, gravity−2, and null callback+28.

## Chain gates

The source requires all of these, not simply held B plus stick direction:
- Contact `+1d9` latches `+745`. A fighter contact sets bit10 and the source
  collision frame clears the transient contact word. The host's old label
  “alt input” is misleading.
- `+5d4` bit40 latches `+746`. Descriptor `802d3904` has count1, flags0,
  buffer duration1 and mask0200. The buffered-input state machine consumes
  `+5bc` press edges and emits this bit in the same update, so this particular
  descriptor is a single fresh B rising edge. Held B does not repeatedly retap.
- Signed aux `+1cf0` must be negative. Stream25 auxFF permits ordinary rearm;
  stream26 auxFE clears bit0 and invokes the variant6 callback.

## Stream and motion distinctions

Positive mode2 waits compare directly to animation frame; only negative values
add animation length. The known thresholds are stream25 5/10, stream26 5/13,
and stream27 2/9/19. Stream27 aux1 at frame9 releases the finisher phase.
Final mode0/−1 waits depend on animation completion. Original PZZ member3
AOBJ bindings are verified: g3s0→bank1/slot1 EndFrame27, g3s1→bank1/slot2
EndFrame35, g3s18→bank1/slot19 EndFrame40, and g0s14→bank0/slot24 EndFrame1.
All have flags0. These are raw ends, not exporter duration-plus-one counts.
Stream25 starts mode1/blend5/frame0; stream26 mode2/blend4/frame0;
stream27 mode1/blend4/frame0; final g0s14 mode1/blend10/frame0. Rate byte0
preserves the current rate. Mode1 holds the frame during blend; mode2 advances.
Both initialize elapsed=dt and total=blend+1; completion adds only elapsed excess
and clears blend mode. Completion requires inactive blend and currentFrame>=end.
Descriptor flags1 and AOBJ flags0 do not loop these animations.

The target lunge helper `801782dc` uses full 3D distance `+760`, divided by own
scale, multiplied by signed dash byte `+1d0f` and .0625, then divided by timer;
it clears the dash byte. Stream25/26 write24 (factor1.5), stream27 writes32
(factor2). Finisher helper `801793e8` does not clear that byte at this step.
No-target movement uses the existing per-actor action-speed rows instead.
`80066838` tests horizontal range; `800668cc` tests 3D range. A null target
returns−1 and force flag1dd80 returns1, distinctions that cannot be reduced to
an ordinary target-present boolean.

## Finisher HIT identity

Original HIT8 remaps to records24/25, both shape2/bone7/flags1. Record24 uses
family damage20 and animation window7–9; record25 uses damage21 and window10–16.
Both damage records have refresh0. Source actor attack identity renews at each
activation wave, so a victim may receive each window once. These windows do not
overlap. Neither independent same-frame multiplication nor permanent per-arming
suppression is justified. Host root-envelope collision remains an approximation
to the original animated bone shape.

## Bounded host surfaces

Admission is restricted to NEO's fresh grounded action1/variant0 and its chained
variant6. Other variants and neighboring borgs keep their existing routes.
Only accepted fighter contacts feed the chain latch; mine/object-class contacts
are not newly inferred. Existing same-team exclusion and incomplete special
collision filters remain. Root-envelope/front/vertical collision is not original
animated bone geometry. Facing, floor and target-root adapters remain bounded.

The admitted host runs fixed dt1/current playback rate1; arbitrary retained
animation-rate parity is not established. Source force-range flag1dd80 is an
explicit state seam, not a newly proven general host flag binding. Hold71c
currently defaults to0 without a live host binding. Equipment
visual default page+bf remains unresolved; cosmetic trail mode is not rendered.
At large animation-frame jumps, source HIT first-activation ordering differs
from the host closed-window check. Collision claims remain at ordinary dt1
cadence even though the pure clock tests include fractional/oversized steps.
These gaps do not authorize invented original assets or presentation.

## Status

Scoped runtime/bridge implementation is present. Focused actual-input tests
pass: accepted hit plus fresh B progresses25→26→variant6/27, observable upward
motion and airborne state occur, authored recovery relinquishes ownership, and
normal landing follows. Animation mapping is3/0,3/1,3/18,0/14.

Held-B, missed hit, stick-only and invincible-target controls do not chain.
Death interruption and neighbor routes are checked. Finisher contact is required
and bounded to its two activation waves without multiplied per-update hits.
A separately labeled helper-level zero-HP record verifies accepted-contact
callback semantics; invincibility rejects that callback.

All focused NEO Battle, stream-clock, pure finisher, prior G RED configuration
and prior G RED mine suites pass. Nine hand-derived clock traces at dt1/.5/.75
plus oversized blend-crossing tests cover wait ordering, non-loop stop versus
end flag, aux values and recovery timing. Combat typecheck passes.
Full `verify:contributor` passes, including all frontend/render/ROM/lifecycle
checks and production build. A final lifecycle rerun covers the last added
signed-wrapper regression: variant0 shifts once and variant6 twice, including
negative and 16-bit boundary fixtures. Combat typecheck and diff checks pass.
Logs are `neo-chain-contributor-final.log` and `neo-chain-lifecycle-final.log`
in the reconstruction workspace parent. The existing large-bundle warning remains.

No original console replay or browser screenshot comparison was performed.
No publication/deployment occurred and no whole-game parity claim is made.
