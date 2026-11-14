# Projectile target displacement and the estimator boundary

## Genuine nonnull-target continuation

The positive projectile initializer now supports the next prefix on its
nonnull-target branch. This joins the same completed spawn and HIT allocation,
saved owner, refreshed child position and captured canonical ownerc8 established
by the earlier [flight prefix](projectile-flight-prefix-integration-2026-11-14.md).
No target object is dereferenced. In particular, a later change to the actor's
live aim vector does not replace the aim snapshot already stored in the child.

The existing initializer evidence gives these exact operations:

1. At `8007de90..8007de9c`, call `8020ba78` with child144, child20 and stack28.
   The genuine spawner already wrote child144/148/14c from actual aimOrigin518.
2. The nine-instruction subtractor loads aim XY, then position XY. It rounds
   both subtractions separately and stores stack X/Y as a pair. Only then does
   it load aim Z and position Z, subtract and store stack Z. Its W1 implicit
   lanes also execute `1 - 1`, yielding unused positive zero.
3. `8007dea0` and `8007dea4` freshly load stack X and Z, in that order, before
   either square. Stack Y is not read by this prefix.
4. `8007dea8` rounds X squared to binary32; `8007deac` loads the already
   authenticated positive-zero cell804379a8; `8007deb0` rounds Z squared;
   `8007deb4` rounds their sum. The implementation retains this operation tree,
   rather than a fused expression or an unrounded mathematical norm.
5. A positive rounded sum stops before actual `8007dec0 frsqrte`. A zero
   rounded sum stops before the unauthenticated cell804379c0 at8007df0c,
   and before8007df10 replaces stack X. Nonzero X/Z can square-underflow to
   zero, so testing raw displacement instead would choose the wrong boundary.

Source references are the existing complete initializer report in
[initializer evidence](projectile-initialization-evidence-2026-11-14.md), the
`8020ba78` range in [Double action evidence](double-action-envelope-evidence-2026-11-14.md),
and `ghidra-export/chunk_0011.c:4356–4368`. Both archived snapshots' decoded
instruction records agree. No archive selection or reader is expanded here.
The decompiler's `1/SQRT` notation is not an estimator implementation.

## Ownership and failure semantics

`SourceProjectileRootSources.targetStack` is explicit retained temporary XYZ
storage. It is admitted lazily at the reached target subtractor. Null-target
and genuine zero-HIT paths do not require or inspect it. Its existing values
are overwritten, not treated as source operands. A missing record does not
manufacture a zero vector.

The helper also requires an explicit processor record with `gqr0 === 0`.
The composed fixture passes the same record used by its genuine Double action,
not a copied processor value. This is a host profile, not an observed live GQR.
RN00, NI0, enabled paired-single operations and finite binary32 values remain
explicit numerical assumptions. A product of two binary32 operands has at most
48 significant bits, so binary64 preserves the exact product before its one
binary32 rounding. Subtraction and addition use the existing exact integer
`addSourceFloat32` implementation.

Known source owners, the selected actor's immediate owned vectors, HIT pointer
bindings, registered byte records, processor and source configuration cannot
alias either temporary record. Matrix arrays and other array-like records are
not admitted as scratch vectors. Descriptor inspection for these checks is host
ownership admission, not emulated loads or target-pointer traversal.

Each paired XY output validates both destination fields before either store.
A later Z load or store failure retains XY and every earlier HIT/position store.
The helper captures all source operands in their instruction order, and the
caller then performs fresh X/Z loads. Caught reentry or any incomplete positive
continuation permanently closes the child and shared actor/allocator path.
No failure can be resumed as completed initialization.

## Tests and scope

The new genuine-graph suite supplies explicit synthetic nonnull-target branch
inputs. The factory itself does not change the inherited target, heading or aim.
Tests distinguish captured child aim from live actor aim, refreshed position
from stale spawn position, paired XY faults from later Z faults, null-target and
zero-HIT laziness, profile validation, aliases and permanent failure closure.
The underflow witness X=Z=2^-75 distinguishes separate rounded squares (zero)
from rounding the unrounded sum (minimum positive subnormal).

This checkpoint adds no reciprocal-estimate implementation, table or seed, and
executes no disputed estimator path. Both positive and zero horizontal-distance
branches remain incomplete. It does not claim target ballistics, full projectile
initialization, source scheduling, flight, collision/damage, browser activation,
original parity, MATCH or a playable clone.
