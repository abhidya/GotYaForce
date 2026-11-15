# Finite passenger traversal integration

This extends the existing bounded `80053b30` host execution from one zero83
passenger to finite traversal. It does not complete the outer battle frame,
hydrate retail actors, or authenticate any new source selection.

## Evidence and source order

The already derived `mass-preparation-evidence-2026-11-14.md` lines 194–214
and 248–252 describe the two unrolled passenger loops and signed stable ordering.
The unchanged `test_archived_mass_preparation_evidence.py` operand fixtures at
lines 636–666 independently assert both loops: current+1e4, target+83, target
slot+3e4, target+204, **original**+208, unsigned local count, binary32 addition,
wrapped count store, mass store, target+1db, backedge. Existing db3/db4 derived
reports retain the same 336-instruction selection. No new archive/DOL selection
or raw game-payload extraction is involved.

`battle-outer-frame.ts` now keeps original identity/actual/Borg separate from
current traversal identity/actual/Borg. Each admitted hop reloads original208;
current advances only after the updated passenger's captured contact is nonzero.
Canonical original owner, allocation, world, status, Borg and lifecycle
checks remain active after current advances. Each reached target resolves via
`actual()`, retaining it for failure closure even when admission later fails.
The existing per-store metadata checks, pointer and byte captures, aliases,
float32 arithmetic, and counter-before-mass store order remain intact.

## Explicit host domain

Immediately before the six live original table reads, a private Set captures
canonical actual identities from the world's frozen identity-only registry
inventory. No scalar values or passenger chain are prefetched. For each original,
an initially empty processed-target Set is used: even the original actor may be
its own first passenger. Captured nonzero83 exits before either membership or
repeat checks. Captured zero83 then requires membership in the initial registry
and no earlier processed zero83 target for this original, before slot, mass, or
counter access. The set resets for every original, including repeated originals
and shared suffixes. Thus successful updates per original cannot exceed the
captured registry size, without inventing a source depth limit.

Repeats and newly registered zero83 targets are explicit unsupported **host-domain
refusals**, not source cycle behavior. A repeated or newly registered nonzero83
target still exits normally. Unrelated late registrations do not eagerly fail.
Captured pointer and zero83 values remain authoritative despite later valid cell
mutations. Contact zero does not read a further pointer. No chain is prevalidated.

## Unchanged boundaries and validation

The six original table cells remain live, physical counter initialization remains
sparse, and sorting uses signed counter bytes with stable equal-count insertion.
Tests exercise genuine wrapped increments through final sorting rather than a
second private-counter model. Static source-order assertions do not claim to
observe the private counter at a failing mass store.

The focused passenger suites cover 129 accumulation, 113 early-stop and 34 finite
traversal fixtures. The unchanged fixed-selection evidence suite passes 18 tests.
Strict combat TypeScript compilation also passes; exact source hashes and logs
are recorded in the coordinator's frozen validation artifacts. Existing single-passenger
and early-stop assertions are updated only where the removed second-link boundary
must now reach the next pointer or explicit repeated-zero83 refusal. Later missing
RNG/ordering ingress, unsupported continuations, failure closure and exclusive
scheduler authority remain fail-closed. No commit or publication is part of this
implementation step.
