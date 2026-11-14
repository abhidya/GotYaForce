# Third-pass canonical target83 gate, 2026-11-14

## Bounded continuation

This checkpoint implements the already-authenticated `8006b374..8006b37c`
active-target gate inside `8006ae60`. It does not implement `80027764`, the
remaining association scan, or a completed outer frame.

After the caller has loaded its active byte and canonical `+508` pointer, an
inactive caller or null pointer still skips target dereference. An active
nonnull pointer is captured and resolved through the **same** allocator and
world. This bounded domain requires a genuine allocation-bound actor with an
explicit canonical `SourceObjectAllocationActorBinding.byte83`. It does not
invent `eligibility83` on an actual actor or accept a separate target table.

The gate loads that existing byte once. Any nonzero signed-byte result skips
to the next physical row. Zero reaches the explicit next boundary:

`8006b380 reached unsupported source actor7d3 association guard`

Target records without the demonstrated allocator/world ownership remain
unsupported at `8006b374`. No general non-actor target or constructor hydration
is inferred from this bounded actor domain.

## Existing evidence only

The [target-preparation evidence](target-preparation-evidence-2026-11-14.md)
and its existing fixed reader already authenticate all 380 instructions of
`8006ae60..8006b44c`. The original selected body digest is
`6b725b93ac0755d146b4a67fe61ec81127d98afccc77ca5c3fcd990fa199b50a`.
This checkpoint uses those retained derived operands and existing tests. It
makes no new archive payload selection, global-data read, pointer-following
selection, download, original execution, or raw-binary publication.

The relevant existing operands are:

| PC | Operation |
| --- | --- |
| `8006b35c` | `lbz r0,0(r4)` captures caller active. |
| `8006b360` | `lwz r5,1288(r4)` unconditionally captures caller508. |
| `8006b364..368` | Sign-extend active, then skip if zero. |
| `8006b36c..370` | Compare captured pointer to zero, then skip if null. |
| `8006b374` | `lbz r0,131(r5)` loads captured target83. |
| `8006b378` | `extsb. r0,r0` establishes the signed-byte condition. |
| `8006b37c` | Branch to `8006b42c` on nonzero. |
| `8006b380` | Next actor7d3 load remains outside this checkpoint. |

The existing allocator actor binding owns this byte for projectile allocation;
its source ownership is already enforced by the projectile-spawn runtime. This
continuation borrows that exact sealed binding and retains the exact actual
pointer identity. It does not create a second byte83 owner.

## Ownership and failure behavior

The captured target must resolve to the same actual record in allocator and
world, with an unchanged allocation binding. Caller admission, caller/target
lifecycle and reached source aliases are checked before and after the source
byte load. These are host-domain checks, not additional retail scalar loads.
Caught outer reentry, independently closed owners and late aliases cannot
permit later row reads. The previously written mass, candidate, distance and
vector state is retained on failure, and the entire retained outer graph
remains permanently incomplete.

Canonical field-name checks cover retained allocator records. Numeric offset
131 aliases are checked only on actor-role records: unrelated allocated byte
buffers legitimately have a byte at that offset. Source group cells and pause
masks remain unread; metadata checks for competing names are not scheduler
execution. No public scheduler or root execution authority is granted.

## Tests and remaining work

The focused suite is wired into the existing attached-setup aggregate. It uses
the same genuine six-actor composition, explicit host-supplied byte83 cells,
and the existing real zero-candidate/null-direction source path. Active caller
changes are injected only when the actual third-pass active load is reached;
this does not claim a preceding full active-actor lifecycle.

Cases exercise zero and positive/negative signed-byte representations, exact
active/508/83 read order, self-targets, readonly sources, opaque inactive and
null targets, captured pointers/active values/83 values, a fresh target83 load
for a later caller, missing or malformed canonical cells, late aliases,
independent caller/target failure, reentry and preserved earlier stores.

The six-actor target path may still reach mandatory `80027764`. That separate
routine has readable C and an independently named 736-byte extent, but no
selected authenticated operand body in this evidence set. In particular, its
actor330..333 byte clears and later pointer-width stores cannot be implemented
as a single inferred null store. It remains closed. The existing repeated-
primary mass-table caveat also remains: these tests are not six-actor mass
hydration, retail construction, hardware replay, browser playability or a
completed battle frame.
