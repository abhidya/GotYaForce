# G BLACK charged B: bounded browser restoration

## Scope and baseline

`pl062a` charged release reaches the host's exact command row `80365e38`
(type3/subtype5, cue44/mode3/action3/variant0), but the previous press-only bridge
entry left the actor in action0. Real held/released B then spent another ordinary
ammo and emitted generic twin shots. This is distinct from the RED/NEO charged
B restored in the preceding local checkpoint.

No publication, original asset transfer, whole-game parity or live deployment
is implied. This report records bounded implementation evidence and limits.

## Actual original route

Original `8018ed4c` sends BLACK to `8018ee08` / shared engine `80179d20`, not
RED/NEO's `80179814`. Config `8036586c` is slot3, f32(.95), setup `8018ee30`;
phase table `804347a8` contains only `80179d58` and `80179e60`.

Setup `8018ee30` allocates `8016cc24` with literal **0x10 (decimal16)** and seeds
vertical velocity4/gravity0. It is not decimal10 and is not the `800e19a8` row17
branch found in another wrapper. The existence of that row17 branch does not
establish its reachability from this action. Slot4/3 contains no discharge
callback or actor HIT registration; the setup child is the functional dependency.

Source references are the existing `research/decomp/ghidra-export/chunk_0044.c`
(two-phase engine), `chunk_0047.c` (family wrappers), and `chunk_0043.c`
(16cc24 allocation and child phases).

## Actor ordering

Phase0 advances phase, clears541, selects slot3, calls target yaw/pitch helpers
6d144/6e1ac in modeC1, zeros physics and pose, then invokes setup. It carries
`(pos - own5e8) * f32(.95)`, probes terrain and starts group4 slot3 while advancing
the next-slot byte. Source5e8 is the actor's own saved position.

Phase1 ticks the stream first. Negative P0 damps signed part pitch by f32(.9).
Unless both P0 and541 are positive, it aims only when faceGate is nonzero,
restores descriptor gravity on negative dash, carries, integrates primary
physics and probes. With no stream completion it returns. The positive-P0/541
branch instead restores gravity and sets cooldown30+dt, skipping that ordinary
motion path. Both exits clear ownership and horizontal velocity and call the
source airborne return. There is no RED30-frame fire timer, no fresh-edge
extension budget and no owner6f7 sustained-beam release callback in this engine.

## Authored stream

Group4 slot3 at `803671b8` begins opcode0c `00ff00`, plays metadata4/2 with mode2,
blend8/start0, and sets contact0. Frame19 sets contact1; frame24 disables facing.
Animation end plays recovery metadata0/14 with blend8, contact−1/dash−1, then
waits elapsed8 before terminal completion. Main MOT4/2 has original end38 and recovery MOT0/24 end1. Opcode0c is
part0-gated; `00ff00` clears both source57a and57b. Independent clock traces
at dt1 have gates21/26, recovery40 and terminal49; dt.5 gives40/50,78,95.
These are interpreter-call counts, not a claim of complete fractional actor
physics or rendered-pose parity.

## Setup child and impact dependency

Original `8016cc24` row16 is at `8035045c`: joint12, HIT28, effect16,
basis columns2 and1 with positive signs, cone f32(pi/4), local offset0.
HIT28 maps record37, sphere radius30/flags1/damage32 (HP30), window0..−1.
The staged table `80350598` has durations25/6/10 and model indices7/8/9.

Initial child272=ffff disables its attack-list admission: source8a2bc requires
recordflags bit1 and actor272 bit1 clear. Stages0/1 therefore cannot damage.
At stage2 launch it clears272, adds10000 to localZ43.37525939941406 and admits
one registered attack pass. The following child update16d2d0 disables HIT.
The final state16d344 is visual-tail expiry at age>=duration, not another attack.

Accepted actor or terrain contact can allocate `80085e00` effect16. This is not
assumed cosmetic: the row at `802da0b8 + 16*36` selects shared HIT110 and lifetime4.
Original shared HIT110 maps record150, sphere radius310/flags1, global damage23
(HP20/refresh0), window0..−1. The primary HP30 ray and HP20 impact are independent
attack identities; immunity means this is not a guaranteed total50 hit.

Original AFS1890 BLACK model joint12 has identity rotation/scale and static bind
world translation `(70.31999206542969,166.96002197265625,0.00002288818348157698)`.
Helper45ef4 normalizes the basis axes: local ray distances43.37525939941406 and
launch+10000 are not multiplied by modelScale. Joint translation and collision
radius still use their respective scale paths. Static bind geometry is not
animated joint parity.

## Verification and limitations

Final implementation and test results are recorded after integration below.
No positive541 writer was established in the reachable actor/setup/child call
path. It remains an explicit unbound input; accepted contact must not fabricate
it merely because an early-exit branch exists.

## Implemented bounded behavior

- `gblack-charge-engine.ts` implements the separate two-phase ordering; the
  existing RED/NEO engine and legacy unadmitted routes are not replaced.
- `gblackCharge.ts` binds captured-target aiming, source stream and motion hooks.
  `gblackChargeStream.ts` drives the exact clip playhead independently of rendering.
- `gblackChargeProjectile.ts` owns stage0/1 windup, the single launch attack,
  stage2 visual tail, and the separate effect16 impact. Owner death/form changes
  and source control bit0x01000000 retire the child without a fabricated impact.
  Child lifetime is independent of the actor charge-state object after allocation.
- Stage0 reads the cached owner518 target point, retaining it when the target is
  lost. Stage1 freezes the transform. Static joint12 is a deliberate fallback for
  the original animated cache. The ray's prior and current endpoints feed the host
  sweep; an accepted shape contact is approximated by the defender root for impact.
- Both standalone bridge and production Battle family-spawn paths use the new
  adapter. The source type3 release does not debit another normal-shot cell.
- Renderer placeholders use crossed planes and an impact sprite, with dimensions
  and alpha sampled from simulation. Original models7/8/9 are not guessed or
  replaced with unrelated assets. Stage scale keys are `(time,value)`:
  stage0 `(0,1),(5,.5),(25,0)` on all axes; stage1 `(0,1),(5,f32(1.1)),(6,0)`;
  stage2 X/Y `(0,1),(2,f32(.1)),(10,0)` with Z1. The source ray length is separate
  from these presentation scales and the collision radius.

## Verification

- Fourteen pure engine groups cover source order, signed fields, own-position
  carry, explicit541 early-exit input, ordinary completion and no RED-style timer.
- Two independent clock traces cover mode2, both gates, recovery and terminal.
- Child tests cover25/6 staging, one registered attack pass, frozen matrix,
  model-scale versus unscaled ray length, separate impact identity/history,
  whiff/death/terrain cases, owner control-bit invalidation and retained518.
- Actual input tests cover banked BLACK release, source setup child provenance,
  source animation epochs, no mash extension, no extra debit, damage/impact,
  empty-bank release, cancellation and neighboring RED/NEO/Beam/melee/X routes.
  Real Time Bomber mine-constructor fixtures also verify no windup damage and
  separate sweep/impact receiver identities with delayed mine retirement.
- Synthetic renderer tests cover pending/freed visibility, source scales/geometry,
  paused render updates, duplicate observations, same-UID kind replacement and
  exactly-once material disposal without disposing shared geometry. The existing
  source-animation check also covers BLACK's charge_shot clip and recovery.

## Remaining accuracy limits

Host charge accumulation/thresholds, the 240-update safety ceiling and the
existing post-action cooldown remain entry/exit
adapters. Static joint transforms, helper rounding/nonunit rates, target sampling,
host terrain ray clipping, instantaneous capsule/body tests and accepted contact
point are not original animated shape/terrain parity. The first absent owner518
sample uses the forward fallback until a saved point exists. Source541 remains
unbound, so its early-exit test is not a claim that normal player hits trigger it.
Procedural art is not the original charge/impact presentation. Synthetic renderer
checks are not an in-browser screenshot or original-console replay. Nothing in
this local checkpoint has been published or deployed.

Final local `verify:contributor` passed after the runtime/renderer freeze, including
policy, TypeScript, all renderer checks, ROM, full combat lifecycle, importer and
production build (21.54 seconds). The existing large-bundle warning remains.
