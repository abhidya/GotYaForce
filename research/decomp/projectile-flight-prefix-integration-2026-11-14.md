# Saved-owner projectile position and bounded launch direction

## Executed continuation

The optional genuine HIT continuation of `projectile-root-lifecycle.ts` now
continues the already-authenticated `8007dd84` initializer after a positive
`8008ac80` result. It operates on the same allocator-backed child bytes, the
same actor, its retained world-matrix runtime and its canonical admission
binding. It does not introduce a second actor or target-pointer record.

1. `8007de1c..8007de38` uses the initializer's **saved owner90**, not a fresh
   child90 or child8c. Signed row1 joint02 selects the existing owner matrix
   at8d4 +48×joint. The genuine paired-single `8020b7a8` helper transforms
   authenticated row1 local04 directly into child20/24/28, with its actual
   arithmetic/load/store schedule. No copied vector is committed afterward.
2. The source row1 offset2c is read only after that transform returns. Its
   authenticated zero skips `8020ba54`; unsupported nonzero data is not
   replaced by a default owner offset.
3. `8007de58` reads fresh owner72, then `8007de60` reads the canonical ownerc8.
   Child72 and childc8 do not replace those owner fields. The exact xoris/bias
   conversion, single-rounded subtraction and single-rounded multiplication
   use the three typed cells in `projectile-flight-prefix-evidence-2026-11-14.md`.
   All 65,536 raw signed-short patterns have an exact arithmetic domain. The
   integer result has at most16 significant bits, so multiplying it by the
   24-bit source scale is exact in binary64 before the one float32 rounding.
4. An actual nonnull ownerc8 stops at the reached target-displacement call
   `8020ba78`. No target vector, ballistic angle or target default is invented.
   A genuine null pointer reaches source fneg of positive zero, producing
   **negative-zero pitch**.
5. Explicit source temporary matrices are required at the first reached
   `8020b238` call. They must be distinct, belong to the same genuine matrix
   runtime, and not be any actor matrix bound in the same retained world
   runtime. Their supplied lanes are overwritten, not used as launch inputs.
   Claimed stack storage cannot be reused by another initializer. This is a
   host ownership contract for temporary storage, not a console-stack address.
6. Standalone `rotateRadiansZero` implements the existing authenticated
   `8020b238`/`8020b2a8` path for actual radians +0 and −0. The sin kernel returns
   that signed zero unchanged; the cos kernel returns authenticated +1.
   RotTrig preserves its axis-specific signed sine and actual store order.
   This is neither the short-angle wrapper nor an identity/copy shortcut.
   Nonzero yaw stops at its reached sinf boundary **after** the X rotation.
7. For zero yaw, the genuine paired-single Concat runs Y×X with X as both
   right input and output. The actual matrix lanes2/6/10 are separately loaded
   and stored to the same child's38/3c/40 in source order. The next operation,
   mandatory `8020bab8` Normalize at8007e074, remains an explicit boundary.

The zero-HIT return still writes child18=2 and returns through the real
initializer epilogue. It reads none of the new world matrix, heading, target
or stack inputs. Failed positive continuations preserve completed stores and
permanently close the child and its shared spawn/allocator path; catching the
error cannot turn a partially initialized projectile into a completed one.

## Source and numerical scope

The existing initializer evidence authenticates all287 instructions in
`[8007dd84,8007e200)` with SHA256
`e8732a065c806b75274606baf717082e907c68db87400e1a4299b77820148ec2`.
The existing traversal reader authenticates the fixed RotRad/RotTrig ranges
and the sin/cos zero branches. Re-running that unchanged reader for both
archived snapshots adds no selection. The only new selected archive inputs
are three typed cells,16 bytes total. No source executable is executed.

The finite-float32, RN=00/NI=0 and GQR0 floating-point load/store assumptions
remain explicit. Non-proxy synchronous own-data storage is the host domain.
Byte-backed stfs validates all four destination bytes before writing any of
that scalar; earlier scalars remain when a later scalar fails. Matrix stores
retain the established per-lane host fault contract, not a claim about PPC
paired-store atomicity or original memory faults.

No new trigonometric approximation or reciprocal-estimate implementation is
imported. The real mandatory Normalize is not removed even though this narrow
rotation result is unit length. Launch speed, gravity, lifetime and later model
row cells remain unread; no later initializer or flight-state operation runs.

## Integration and tests

The fixture composes actual source runtimes from supplied decoded state and
synthetic current allocation pools. Its inherited source actor heading is0 and
canonical admission pointerc8 isnull. The new fixture merely provides explicit
temporary matrix storage; it does not set either field to force success.
This is not proof that a live retail actor starts in that state.

Focused suites exercise changed live matrices after spawn, saved-owner capture
across HIT-side pointer changes, fresh heading/target reads, zero-HIT skip,
signed-zero rotations, aliased Concat, partial transform/direction stores,
whole-width byte refusals, stack aliases and permanent failure closure. Matrix
unit tests cover all axes and both zero signs, every RotTrig/Concat destination
fault lane, nonzero refusal and reentry. The independent integer rounding
reference covers all65,536 heading patterns. Existing root, HIT, allocator,
spawn, frame/ground and actor regressions remain in the focused gate.

This checkpoint advances the actual standalone projectile initializer through
position refresh and narrowly supported launch-direction stores. It does not
complete initialization, normalization, nonzero-angle trig, target ballistics,
state1 flight, collision/damage, a source object scheduler, production actor
hydration or browser activation. No original parity, MATCH or playable-clone
completion is claimed. Existing frame-owned actors still refuse standalone
callback execution until their later genuine scheduler is implemented.
