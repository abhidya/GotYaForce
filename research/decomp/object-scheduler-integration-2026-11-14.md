# Source object scheduling over genuine projectile storage

## Implemented source route

`source-object-scheduler.ts` implements the authenticated bounded89a94 wrapper,
8997c six-slot eligibility loop, and89898 direct-group loop. It borrows the
allocator's existing group records and canonical bytes; it does not iterate a
copied list or the root's host registry. Explicit standalone invocations can
now run genuine projectile initialization, retirement and cleanup through the
actual scheduler traversal instead of individually calling the projectile root.

Inputs to the three public entry points are raw unsigned32 register bits.
Comparisons interpret those bits as signed32. Group addresses use the low32
multiply/add semantics, represented by the effective low30 group index. There
is no invented group0..55 validation. Missing reached group records refuse.

The wrapper calls8997c(base),89898(base),89898(base+7) when signed base<56 and
the low three bits are zero. Other bases call only89898. Each six-slot
iteration reads its current pointer, the target's signed active0 byte, then,
only for a nonzero byte, the current global mask and the corresponding group
head. The mask choice uses the original signed base, not the resulting group.
Direct group walks implement their separate bit80 pause test and low3==7 and
signed>=56 exceptions. No empty/inactive slot or mask value is defaulted.

Both walkers retain this source order for an admitted active object:

1. Read raw words20 and24, then write2c and30.
2. Read28 and write34.
3. Read raw word70 and write the whole word at76.
4. Read unsigned halfword74 and write7a.
5. Load the numeric callback0c exactly once and invoke the genuine selected
   projectile body when it is8007dcec.
6. After normal return, read signed86, clear1ca if nonzero, then read live8.

All snapshots preserve raw bits, including nonfinite float encodings and signed
zero. The allocator's general aligned-word APIs remain strict. Its new narrow
word76 method requires the exact private active scheduler snapshot scope and
preflights all four destination bytes before committing them together. This is
an explicit synchronous byte-record execution model, not proof of original
hardware alignment handling or exception behavior.

Initially inactive objects skip snapshot, callback and post-callback fields,
but still read their live next8. The source does not recheck active0 after a
callback. Cleanup therefore proceeds to86/1ca/8 even after returning that same
object to its free pool. A4096-node host visit budget bounds malformed cycles;
it is not a source cycle detector or a retail object-count claim.

## Actual ownership and admitted domain

The allocator's lazy `getGroup` returns its original retained record. The
803c7070 array expression is represented as803c706c[base+slot+1], not as a second
independent table. Existing owner-retention and alias checks remain active.

The match-global record comes from the root's genuine spawn runtime, through
its already-established command-admission/charge global owner. Existing
`maskD2` and optional `maskD1` are fields of that SAME80433934 record. No caller
supplies a substitute pause record. Scalars are loaded only when source gates
reach them; the record identity is retained across invocations.

The optional six-slot table is an explicit retained pointer table. Each reached
symbol resolves through the allocator to its original target. The new optional
`RomActor.active0` is the missing source+0 byte, without a constructor default
or a copied side binding. A minimal inactive target may explicitly contain only
that byte; no model actor is fabricated. The unrelated port-side stream
`active` flag, lifecycle18, HP and roster presence are never used. Null is a
reached dereference failure. A competing raw[0] owner is rejected.

Active list nodes are bounded to genuine completed projectiles explicitly bound
to this root. Before snapshots, host admission checks that original byte owner,
completed lifetime and source actor are valid and not frame-owned. An unbound
active node is outside this domain and refuses before snapshots. A bound node
whose numeric callback differs retains the completed snapshot prefix and refuses
at the reached callback. Neither a forged8007dcec word nor a registered free
record supplies a completed spawn or root binding.

A scheduler claims its genuine root once. Public standalone root dispatch then
refuses; possessing the scheduler object does not authorize the internal join.
Private synchronous prepare and callback stages match the scheduler, root,
child and completed allocation lifetime. The selected-body join omits the old
standalone callback-cell admission read, so the scheduler's actual0c read is not
duplicated. No caller-supplied dispatcher or callback map is accepted.

## Completion, refusal and next boundary

A successful state3 callback intentionally revokes completed-spawn identity.
The scheduler does not call root owner/lifetime checks after that return. Its
post-callback work reads the same retained allocation bytes and follows live8,
including the stale next pointer that actual cleanup preserves. Subsequent
real allocation can reuse those bytes with a fresh completed lifetime and
explicit root rebind.

Any admitted scheduler failure permanently closes this scheduler, its allocator
and the root's captured actor graph. Earlier writes and callback effects remain.
Closure uses retained actor identities, including after cleanup removed the
spawn record. Caught scheduler reentry may be detected after an entered scalar
or genuine callback completes; it is not rollback or a promise to stop every
inner operation. Existing allocator/root guards retain their own finer bounds.
Invalid public register arguments and idle capability requests cannot initiate
source work.

Frame-owned actors still refuse before scheduler snapshots. No frame capability,
consumed epoch, incomplete-frame state or private actor operation is reset or
bypassed. A future genuine outer-frame/order join is still required to connect
these loops to frame-owned actors and browser execution. Nonnull JObj teardown,
positive flight Normalize/frsqrte, motion/collision/damage completion and visible
projectile/clone activation remain separate boundaries. This checkpoint imports
no estimator and claims neither original execution, MATCH, hardware parity nor
playability. Current heap records and slot data in tests are explicit synthetic
offline inputs, not retail heap hydration.
