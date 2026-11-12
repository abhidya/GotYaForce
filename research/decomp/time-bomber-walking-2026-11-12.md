# Time Bomber bounded grounded-running X

This extends the neutral-ground and airborne work at `a373c14`. No original assets are included. It is a local implementation, not an original-console replay or visual-parity claim.

## Source evidence

Original walk `8005f3a0` and run `8005f578` both set actor control bit `0x10`. Run reads descriptor `+0x2c`, also the source of the host's ordinary ground speed. The host's acceleration remains tuned rather than source-identical. `80069ea4` maps that control state to command subtype 1. Stop/recovery `8005f6c0` retains `0x10` until its authored stop-tail signal; releasing the stick alone does not identify original idle.

`8006c674` classifies the currently selected target (`+0x508/+0x50c`) before attack-target capture (`+0xcc`). It uses `8004516c` to transform the target through the inverse actor-root affine matrix. `80046bd0` constructs that root from translation, Euler rotation Z74/Y72/X70, scale, and optional actor6b8 yaw correction. For the supported upright uniform-scale host actor without that correction, the inverse reduces to translating and rotating the target into local X/Z.

`800452a0` calls atan2(localX,localZ), rounds to f32 (`frsp`), multiplies in f32 by original constant `8043707c`, bytes `4622f983`, value `10430.3779296875`, then stores a quantized signed16 via GQR5. Standard game initialization `8002a414..8002a41c` writes `GQR5=0x00070007`: scale-zero signed16 quantization truncates toward zero and saturates to [-32768,32767]. The host reproduces that conversion, but JS trig and reduced matrix arithmetic are not a bit-exact original libm/matrix oracle.

Signed yaw buckets are strict: greater than +0x5000 or less than -0x5000 selects direction2; greater than +0x2800 selects1; less than -0x2800 selects3; otherwise0. Thus equality at either inner threshold selects0, while equality at outer thresholds stays1/3. No current target selects0. The subtype1 X records are:

- Direction0: `803361e8`, `[44,1,0,1]`.
- Direction1: `803361ec`, `[44,1,0,1]`.
- Direction2: `803361f0`, `[44,3,0,0]`.
- Direction3: `803361f4`, `[44,1,0,1]`.

Variant1 shares `80130c5c` / phase table `80335ce8` with variants2/3. It owns part mask1, not whole-body motion. Source control10 selects group2 slot15. Original slots15 and18 alias `803351e4` byte-for-byte, including initial animation triplet31/30/32 and tail35/34/36. Existing center30/34 presentation and original END20/wait8/END9 clock therefore remain applicable. The bounded renderer still does not reproduce the directional animation blend.

The shared windup aim gate can redispatch to grounded variant0 if the captured target moves outside ±0x4800 before release. This is distinct from selecting direction2/variant0 at admission. Recovery checks stick-direction bits after firing, so holding movement normally releases part0 ownership on the next recovery tick, rather than waiting for the whole animation tail.

## Implementation boundary

`timeBomberCommand.ts` refines only Time Bomber type2/action0 for established host grounded movement. `battle.ts` requires pre-movement state `move`, active stick above the existing 0x34/127 threshold, no jump/dash/hyper request, no active dash, and zero represented body pitch. The post-movement command adapter also requires grounded `move`. First-frame movement starts, coasting entry, stop-tail states, dash, air directional entry, and tilted actors are not newly admitted. The existing generic resolver/fallback outside this boundary is preserved, not declared source-correct.

The bridge composes variant1 with the same existing host lower-body movement adapter used for airborne variant3. It preserves movement through windup and restores the live locomotion state on source completion. Temporary source movement-control bits are scoped to the action and restored on completion, interruption, or failed admission. Source ammo is still the shared slot2/X alias; denied admission inside the supported lane cannot fabricate a generic projectile. B behavior and neutral ground/air routing are unchanged.

Current source limitations remain: no represented root roll or actor6b8 correction, no original stop-tail mapping, host acceleration/collision/locomotion rather than source movement execution, static joint7 muzzle rather than animated attachment, center animation rather than full directional blending, and no original-console replay or visual comparison. Synthetic signed-boundary checks are adjuncts to actual-input integration tests, not a substitute for them.

## Verification

The new actual-input test initially failed on established running X selecting legacy variant0 instead of source variant1. With the bounded implementation, actual-input tests cover forward and lateral movement paired against no-X controls, natural stopping, source allocation/aliased ammo debt, held/released/repressed X, empty ammo, targetless aim, target movement and target switching, nonzero owner heading, positive/negative target-side records, rear-target whole-body admission, released-stick recovery timing, death interruption, and follow-up neutral/air shots with movement-control restoration. Negative tests keep dash, coasting, and simultaneous first-start/X outside the new running lane. A baseline bundle confirms excluded dash still produces its inherited generic projectile; the change preserves that behavior rather than claiming it source-correct.

Synthetic adjuncts cover exact signed boundaries at ±0x2800 and ±0x5000, fractional-angle truncation, rotated-root reduction, no-target default, and positive-pi signed16 saturation. They are implementation tests, not original-console comparisons.

Passed locally: full combat lifecycle tests, root `pnpm typecheck`, `pnpm selfcheck:rom`, `pnpm selfcheck:time-bomber-projectiles`, and `git diff --check`. Standalone package `typecheck` is not the root check and fails TS6310 reference/noEmit configuration; the supported root check passes. Broader contributor checks are separate from this focused verification.

The official Wire Gunner reference generator was rerun after the family dispatch import changed. Its action2 reference remains an existing regression seam and does not certify the new Time Bomber variant1 path against console execution.

Reconstruction follow-up: the separate full clone now passes the complete `verify:contributor` aggregate, including the HUD checks. The earlier missing-HUD-assets limit no longer applies to this clone. See `time-bomber-reconstruction-2026-11-12.md` for fresh scope, checks and remaining limitations.
