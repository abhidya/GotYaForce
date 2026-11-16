# Projectile state3 cleanup and reusable storage

## Implemented route

The existing source projectile adapter now admits explicit state3 dispatch
cell802d6fa4→8007e678. This is a separate invocation after state2 has returned;
it is never called inline merely because state2 writes3. The wrapper invokes
the actual88e50 cleanup chain against the allocator's original byte records,
groups, descriptor pools and object pools. The root supplies its same separate
draw-list record. No list is reconstructed and no host cleanup callback stands
in for source code.

The bounded chain is:

-88e50: load signed group byte1. A genuine−1 skips group/draw/descriptor work.
 Otherwise unlink the group using captured child4/8. The singleton path reloads
 byte1 between the head and tail stores. Raw type4 then skips draw/descriptors.
-89444: signed draw class85=−1 returns immediately. Otherwise load both104/108
 links first. Group0 is supported; other list families refuse at that reached
 boundary. The singleton path clears tail before head. Source then clears100
 and writes85=ff. Draw links themselves are not erased.
-88e50's descriptor loop reloads and sign-extends99 on every condition check,
 reads each current e0+4*i pointer and calls06d80 only for nonnull descriptors.
-06d80: inspect descriptor+c. Nonnull reaches the explicit unsupported
 8024fd74 JObjUnref boundary before clearing+c. Null proceeds to197ad8.
-197ad8: capture signed descriptor8, resolve the retained row0 pool and require
 its **actual nonnull80006ed8** release callback. Missing, null or substituted
 callback metadata refuses before descriptor unlink. The real callback reloads
 descriptor+c; null returns0, while nonnull reaches its own Unref boundary.
-197ad8 then freshly loads both active links, unlinks the descriptor, pushes it
 on the free list, clears active byte9, and uses the real signed-count load plus
 low16 increment/store semantics of197bec/197bd8. Captured type and row pointer
 remain distinct from the helpers' fresh pool resolutions.
-89814: append the same child to its free queue, reloading signed byte3 between
 source global accesses. Increment the raw u16 count with wrap, then clear only
 active byte0 and word4. The source leaves callback0c, state3, descriptor slots,
 group8 and other stale fields intact until subsequent allocation memset.

See `projectile-cleanup-evidence-2026-11-14.md` for all nine fixed selections,
two independent scope stages, complete instruction operands and read provenance.
The callback scalar was first reported as nonzero; its separately C/index/map
bounded body was then authenticated. A missing or nonnull callback was never
converted into an invented null return.

## Canonical owners and admission

`SourceObjectAllocationRuntime.releaseProjectile` uses the allocator's existing
private caller capability and holds its guard through the complete helper chain.
It reuses the retained group/pool/descriptor identities and scalar atomic-store
preflights. The draw record stays owned by the root rather than being added to a
competing allocator owner registry.

`SourceActorProjectileSpawnRuntime.cleanupProjectile` holds the spawn guard and
requires a genuine root's **private active state3 invocation** for the exact
child and completed allocation lifetime. Possessing a genuine idle root is not
sufficient. The root establishes that scope only after fresh state3 selection
and the explicit dispatch-cell check, and removes it in finally. There is no
injected function or exposed private allocation token. The existing frame-owned
actor prohibition is checked before scope creation.

Both optional dispatch metadata and descriptor release metadata are lazy. Old
fixtures that omit them keep their previous unsupported boundaries. Type4,
group−1, negative/zero descriptor count and null descriptor slots genuinely skip
unreached metadata; missing data is never interpreted as a skip condition.

## Completion, failures and reuse

Every completed source spawn has a fresh opaque **host lifetime token**. It is
not written into source memory. Root binding captures the owner and token;
subsequent owner checks require both to remain unchanged.

Only after every source cleanup store completes does the spawn adapter revoke
the completed-spawn record. The root then marks its old entry permanently
released and removes its byte-storage claim. Repeated root dispatch refuses
before source reads and outside the failure-poisoning catch. A later HIT call
also refuses the absent completed spawn before poisoning an actor. Registered
storage and pointer identities remain intact because source free pools contain
addresses to the same storage.

A later genuine allocation can pop and memset those exact bytes again. It gets
a fresh completed-spawn token. Explicit root rebind creates a **new entry**;
it never resets the old released entry. Stale root bindings therefore remain
harmless even when the symbol and byte object are reused. This is not automatic
scheduler activation.

Any admitted cleanup failure retains prior effects and permanently closes the
current child, source actor and allocator. No partial failure releases the root
claim. Scalar preflight remains indivisible within the admitted synchronous
ordinary-record model. Caught allocator reentry interrupts its entered operation;
caught outer root/spawn reentry may be detected only after the already-entered
allocator helper returns. In the latter case its source stores can complete
before failure closure, and root-level reentry may follow completed-spawn
revocation. Tests distinguish these boundaries rather than promise rollback.

## Genuine composition and claim limit

`createProjectileCleanupTestFixture` supplies the two authenticated root cells,
releaseCallback18 and explicit row0 markers in descriptor byte8 **before** the
actual allocation. The existing allocator does not initialize8, so adding a
runtime store there would be incorrect. Old fixtures retain their earlier
sentinels. These supplied current pool/descriptor records are synthetic offline
inputs, not retail heap hydration or a completed source constructor.

`runProjectileCleanupHydratedCompositionTests` is included in the existing
attached-setup aggregate. It runs the genuine sequence: completed spawn, actual
HIT-zero initializer return, separate state2 return, separate state3 cleanup,
then genuine allocation and explicit rebind of reused storage. A successful
source release is now executable without any reciprocal-square-root estimate.

This does not make a visible projectile or a playable clone. A real source
scheduler, browser activation, positive flight initialization, motion, collision
and damage remain unfinished. Frame-owned actors cannot use this standalone
entry point. Nonnull JObj teardown remains unsupported. Mandatory Normalize and
positive target frsqrte remain blocked by unresolved exact estimator provenance;
no idealized substitute, disputed implementation, original execution, MATCH or
hardware-parity claim was added.
