# Source target dispatch integration

This checkpoint continues the bounded offline actor/frame lifecycle through
`8006b7f4` and the authenticated entry-zero path at `8006b850`. It does not
complete an outer battle frame or activate browser gameplay.

## Evidence and scope

See [target-dispatch evidence](target-dispatch-evidence-2026-11-14.md). The
complete map-sized dispatcher is 92 bytes. Its signed index has no retail
bounds check. Only the separately selected four-byte cell at `802d39a0` is
known here; the implementation deliberately refuses every index other than
zero before a table load. This is a host admission bound, not an inferred
source table size. Entry zero resolves to `8006b850`.

The `8006b850..8006ba60` span is independently delimited by C and the function
index, **not** by a named map entry. Its authenticated instructions and exit
support the bounded branches implemented here. No neighboring table entries,
original execution, live actor capture, or source-data defaults are used.

## Canonical ownership

`createSourceActorTargetDispatchRuntime` joins the existing genuine scheduler,
allocator, spawn, command admission and action request runtimes. `byte502` is
an optional actual `RomActor` cell with a codec mapping at `+502`, without a
constructor default. `pointer508` and `pointer504` remain the command-admission
binding's existing object/null cells. No raw pointer-byte overlay is added.

The new optional `candidateGlobals` record contains explicitly supplied
`half80436242` and `count804361a0`. The first is a halfword, not a byte. The
record is retained by identity and shared across calls/actors in this runtime;
no constructor value or count is inferred. Reached table/global records must
be distinct from each other, the sources, and the retained canonical graph,
including declared and reached slot-status data. The declared inventory reads
only own-data references, never state/table scalar values or accessors. A shared
claim registry also protects later slot-row and scheduler-table admission, so
reversing reach order cannot create two owners of one record. Cross-runtime claims prevent reuse as a
second target-dispatch owner. Shallow metadata inventories never grant frame
or scheduler execution authority.

## Reached source paths

- Inactive `active0 == 0`: store byte `502 = 0`, then word `508 = null`, then
  word `504 = null`. There is no load or validation of the previous destination
  values, no `502` selector read, and no dispatch/global read. Each destination
  is checked when its store is reached; prior stores survive a later refusal.
- Active: load raw `502`, sign-extend it, admit only zero, load the supplied
  entry-zero word and require exactly `8006b850`. A successful callback or an
  arbitrary address is not accepted.
- `6b850` with nonzero signed `73f`: return without actor/global writes.
- `6b850` with zero `73f`: load halfword `80436242` first, then clear word
  `804361a0`. If the captured count is nonzero, refuse immediately before the
  candidate-list load at `8006b898`. If zero, reload scratch count at
  `8006b918`; zero returns, while a nonzero reloaded value refuses before
  descriptor `4b0` at `8006b924`. The empty path does not read/write the
  candidate list or actor target words.

These rules follow instructions rather than the C export's apparent
`DAT_803b2208` load/write at the loop header; those accesses are not present on
the zero-count instruction path.

## Outer-frame integration and closure

Optional `targetPreparation.targetDispatch` is selected only after genuine
`action.prepareTarget` returns, at the existing `6ae60 -> 6b7f4` site. It must
own the same scheduler. Absence preserves the old boundary. A successful
bounded dispatch continues the real second loop and third-pass pointer checks;
it does not skip them or fabricate a completed `6ae60`/outer frame.

Any failed dispatch conservatively marks the actual actor incomplete. Checks
span every own-data access and destination preflight, so a concurrently caught
outer failure cannot be followed by another target/global write. Reentry
poisons the enclosing call. Outer reentry now closes its graph immediately,
before a nested helper can complete a pending store. Outer failures retain
their existing whole-graph closure. Metadata remains queryable; public scheduler methods remain blocked
by outer ownership.

The fixture is explicit synthetic current data on the existing real graph. It
has one fully bound actor and five inactive physical rows, not six retail
hydrated actors. Advancing beyond the selected dispatch can therefore expose
an existing unbound inactive-row owner. This is not reported as a playable
frame.

## Remaining work

The immediate positive-count boundary is `8006b898`: candidate list
`803c1d7c`, current object/actor pointers, canonical team and lifecycle owners,
and the scratch list/count must be joined in instruction order. Other signed
selector states and active `6b450` target selection remain unsupported. Full
six-actor hydration, mandatory `27764`/`bef4` predecessors, scheduler authority,
normalization provenance, flight/collision/damage and browser acceptance also
remain open. No `MATCH`, hardware parity or playability claim is made.

## Review corrections

Independent tests exposed an unreached slot-row alias and reverse late slot-root
and scheduler-table aliases. The shared claims plus declared-reference checks
close those gaps. A caught outer reentry previously left the nested pending
scratch store possible until the caller regained control; immediate outer
closure now blocks it. Preliminary failing traces are retained separately from
the final verification.
