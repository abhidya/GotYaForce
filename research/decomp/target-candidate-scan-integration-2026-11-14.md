# Positive target candidate scan

This checkpoint continues authenticated `8006b850` at `8006b898` through the
candidate loop and its final scratch-count reload. It does not select a nearest
target or complete an outer battle frame.

## Evidence

The complete selected instructions already exist in
[target-dispatch evidence](target-dispatch-evidence-2026-11-14.md). No new
archive payload selection or execution is needed. The `8006b850..8006ba60`
span remains C/index-bounded, **not** named-map-size-proven. The fixed literal
instruction test now separately checks all candidate-loop loads, signed gates,
register provenance, count-before-pointer store order and original CTR loop.

Readable producer provenance is `chunk_0013.c:973–1066`, `8008a2bc`: an object
is appended to `803c1d7c` when its pointed flag word includes `0x400` and the
owner actor's `+272` mask does not. `8008a28c` resets the count. This C text does
not authenticate producer execution, supply a live list, or initialize one.

## Existing owners, explicit new lists

- `candidateGlobals.half80436242` and `count804361a0` remain the existing
  explicit halfword and scratch-word cells.
- Optional `candidateList1d7c` is the actual current object-pointer list;
  `scratchCandidates2208` is a distinct writable scratch pointer list. Neither
  is inferred from a roster or initialized implicitly.
- Each nonnull candidate entry must be a genuine allocator-registered **object**
  record. `readPointer(object, 0x20)` reads the same BE backing and pointer
  identity domain. External records, descriptors and interior object identities
  do not stand in for registered object bytes.
- The pointed actor uses its actual `active0` and `team` (`+88`). Lifecycle18 is
  read only when reached, from the same root's genuine stage runtime, with its
  actual-actor identity checked. It is never a byte18 shadow or a copied target.
- Earlier null/inactive/self/team returns do not require fabricated stage,
  action, admission or spawn bindings for that candidate.

The list/global/table records are retained, checked for distinct ownership and
claimed through the shared helper registry. Declared/reached slot data and all
known status owners are excluded. Allocator identity registration reserves
pointer-target records against helper storage, including later registrations.
These reservations allow immutable external metadata to be referenced by more
than one allocator, preserving its existing contract. Writable object backing
still follows the allocator's separate exclusive ownership rules.

## Exact loop prefix

The unsigned half count is captured once before resetting the scratch count.
For each original-count iteration:

1. Load the list word. Null skips this entry.
2. Load registered object `+20`. Null skips this entry.
3. Load candidate active byte. Zero skips this entry.
4. Compare the candidate actor with the calling actor. Self skips this entry.
5. Load caller team, then candidate team. Sign-extend both. Equal teams skip;
   captured candidate team four also skips, without a second team load.
6. Load canonical lifecycle18 and sign-extend it. Raw `0,1,128..255` admit;
   raw `2..127` skip.
7. Reload scratch count. Store `(count + 1) mod 2^32` at `8006b908`, then store
   the **original object pointer** at the old-count scratch index at
   `8006b90c`. The pointed actor identity is not the stored value.

Entries are not deduplicated. Pointer words and caller team are freshly loaded
on later iterations, while each selected actor/team and the loop's original
count remain captured as the source specifies. Unused scratch slots remain
stale. There is no object-active, object `+28`, scratch-loop-header, or repeated
candidate-count load in this scan.

After the loop, the current scratch count is reloaded. Zero takes the genuine
return even if pointer stores occurred before an explicit later count change.
Nonzero stops before descriptor `4b0` at `8006b924`; no distance or successful
nearest-target result is manufactured.

## Bounds, faults and integration

A 4,096-iteration budget and scratch indices `0..4095` are explicit host bounds,
not source table extents. The visit bound is checked when the next load would
occur. The scratch index bound and scratch-owner/destination admission occur
**after** the increment store, preserving that source prefix on failure.
Missing cells never become null by default. Missing optional list ingress
retains the former `8006b898` boundary.

The existing real `6ae60 -> 6b7f4 -> 6b850` composition selects this path. An
all-rejected positive list now returns to the genuine remaining outer loop;
a surviving candidate preserves its scratch writes and reaches the existing
`6b924` boundary. The synthetic witness binds the already existing second
world actor through genuine dispatch/control/start/setup/movement/attribute/
status/cue/stage/allocator methods. It does not substitute successful callees,
replace root methods, or hydrate six retail actors.

Source faults retain prior effects and close the caller. A known-incomplete
candidate is refused before its first scalar load, and completeness checks
continue through candidate-derived scratch stores; read-only metadata cannot
bypass that closure. Caught helper and outer reentry must prevent pending writes; scheduler execution/epoch authority
remains unavailable. The next work is descriptor `4b0` and its source joint
index/matrix projection, then the still-unselected `8020bc88` distance helper.
Active `6b450` selection, other signed502 dispatch entries, full six-actor
hydration and mandatory outer predecessors also remain open. This is bounded
offline synthetic integration, not `MATCH`, hardware equivalence or browser
playability.
