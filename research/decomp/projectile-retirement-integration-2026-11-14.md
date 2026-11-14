# Projectile state2 retirement integration

## What runs

The production `projectile-root-lifecycle.ts` adapter now accepts a separate,
explicit `retirementState2` input representing authenticated dispatch cell
802d6fa0. It is inspected only when the callback's **fresh signed child18** selects
state2. Its only admitted target is8007e63c; absence is still an unsupported
state2 boundary, not permission to infer a target. Accessors, invalid integers
and other code addresses refuse. No supplied callback executes.

The handler operates on the same allocator-owned bytes used by completed7db5c
and the real8008ac80 HIT registration adapter. Its complete ordered effects are:

1. 7e654 writes child18=3.
2. 7e658 invokes the existing authenticated8aff0 implementation with the same
   child. It first compares raw child2 with3, then tests the sign-extended byte
   against0. Only types3 and0 set child1d8=1.
3. After that helper returns,7e660 clears child82 and the handler returns.

The root's existing guard is unchanged. It captures child18, loads child90, then
uses the saved signed state to decide whether owner lifecycle/family validation
is reached. For saved state2, child90 is still loaded but its owner is not
source-dereferenced by that guard. For a live earlier state whose owner has
retired or changed family, the guard first stores18=2, invalidates and clears82;
its fresh state reload then selects the new handler. Both actual invalidation
calls occur in that path.

This is one completed root invocation. It does not loop into state3, free the
object, return descriptors, unlink any list, or claim a source scheduler. A later
state3 invocation remains an explicit unsupported boundary.

## Genuine composition and failure behavior

`createProjectileRetirementTestFixture` extends the existing completed-spawn/HIT
composition solely with the authenticated state2 cell. It does not alter the
child state, owner family, HIT result, position, target or processor. The new
`runProjectileRetirementHydratedCompositionTests` is included in the attached
setup aggregate and can also be run separately.

In the tests, explicitly supplied negative remap or exhausted allocation inputs
make the **real HIT implementation** return zero. The actual initializer then
stores state2 and returns normally. A second explicit root invocation now runs
state2 to completion, leaving state3 without poisoning the shared actor. This
is distinct from replacing the HIT helper with an injected success/failure
callback. The owner-retirement guard is a second authentic way to reach it.

All source stores retain existing scalar byte preflight behavior. Failures after
the18=3 write retain that write and any subsequent completed invalidation. The82
store is not moved before the helper. A failed invocation closes the same child,
actor lifecycle and allocator through the existing failure mechanism. Caught
same-runtime reentry cannot turn partial execution into a completed invocation.
No normal return performs that failure closure.

The declared host domain remains synchronous, ordinary non-proxy own-data
storage. Test instrumentation of descriptor access observes source ordering and
host admission boundaries; it is not a claim about hardware memory faults.

## Evidence and limits

See `projectile-retirement-evidence-2026-11-14.md` for the two fixed archive
selections, exact operands, table/body identity join and independent reader
checks. The handler has C/index-adjacent bounds and an authenticated terminal
return, **not a named map extent**. Existing8aff0 evidence is reused without
rereading the helper. No estimator, third-party implementation, new FP constant,
asset body, state3 cell or downstream pointer referent is imported.

Completed retirement is useful lifecycle progress independent of the unresolved
reciprocal-square-root estimate. It is not full cleanup or a visible projectile:
state3 freeing, source object scheduling, successful flight initialization,
active movement/collision/damage and browser activation remain unfinished.
Normal null-target initialization still refuses at mandatory8020bab8 Normalize;
positive target distance still refuses at7dec0 frsqrte. No exact-sqrt substitution,
skipped normalization, original execution, MATCH or hardware-parity claim is made.
