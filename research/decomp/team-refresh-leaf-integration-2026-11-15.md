# Bounded team-refresh match-state leaf

The existing battle-outer-frame runtime now executes complete `8008b290` when
reached by the active-burst branch of `80029d48`. This is a bounded offline
continuation, **not a completed outer frame, runnable scheduler, browser
activation, retail replay or playability claim**.

The later [burst-expiry continuation](burst-expiry-integration-2026-11-15.md)
implements the reached `8008b480` leaf from existing matched-source records and
the integer expiry branch. The zero-path boundary described below is the prior
checkpoint; fixtures without explicit `byteEB` now refuse that missing input.

## Existing evidence only

The original [outer-frame evidence](outer-frame-evidence-2026-11-14.md) selected
all of the caller and recorded `8008b290` as unselected at that checkpoint.
The later [actor-ceiling evidence](actor-ceiling-lifecycle-evidence-2026-11-14.md)
already authenticates its complete three-instruction body, end-exclusive
`8008b29c`, span SHA-256
`bed0f0166ee2d2521bf4778199e5f52e29e6c02e88cb20f8e9ad9c4faed7c25e`:

1. `8008b290`: load the match-global pointer with `lwz r3,-31852(r13)`.
2. `8008b294`: load unsigned byte `217` (`d9`) from that owner into `r3`.
3. `8008b298`: return with `blr`.

The already recorded `r13=8043b5a0` basis names `80433934`. It does not prove
live pointer values or supply source objects. This implementation uses only
those existing derived operands and reports. No archive reader, payload
selection, executable extraction, private asset, source-global pointer read or
retired port driver was added or run to implement this continuation.

## Ordered behavior and canonical storage

The outer runtime gets the same match owner from its genuine scheduler and
spawn/admission graph. Optional `SourceBattleOuterGlobalFields.byteD9` names the
same cell already used by actor-matrix and actor-ceiling. There is no second
state record, cached frame result, default value or replacement callee callback.

After the existing ordered six-slot roster refresh of each team:

- Signed row count `+1 <= 0` still skips burst and charge work. Nonburst rows
  still compare the unsigned meter `+32` with threshold `+30`.
- A populated row with signed nonzero burst byte `+10` first clears existing
  `charged` (`+0f`) at `80029d8c`. A missing or invalid leaf input cannot roll
  this store or the earlier roster stores back.
- Callsite `80029d90` loads the canonical match owner and its unsigned `byteD9`
  afresh. The caller compares the full returned `r3` with zero at `80029d94`.
  Since the authenticated leaf uses `lbz`, its supported result is `0..255`.
  Inputs outside that range are refused, not truncated or sign-converted.
- Every nonzero byte branches at `80029d98` to the loop continuation at
  `80029e70`. Current-row meter, threshold, timer and pause-mask suffix work is
  skipped. Later team rows still refresh in order, and another burst row reads
  the live leaf again.
- Zero stops at **`80029d9c -> mandatory8008b480`** before that callee. It does not
  decrement a timer or run the suffix's unsupported floating-point sequence.

Only after all four team rows return does the outer caller load mode `66`.
The existing `53b30`/target continuation and all of its refusals remain intact,
including mandatory `27764`, `0bef4`, and unsupported positive estimators.
This change provides no new actor hydration, frame epoch or scheduler authority.

## Defensive host bounds

The supported host domain remains stable synchronous nonproxy own-data
records. At the reached leaf, metadata checks retain the scheduler/global,
captured team table and visited rows, slot-team and system owners. Semantic
`byteD9` on a competing owner, raw/spelling aliases on the global, and competing
semantic aliases in retained or immediate nested records refuse execution.
Numeric `217` is global-relative, not banned on unrelated raw byte windows.
Independent lifecycle closure and caught same-runtime reentry prevent later
rows and permanently close the retained graph on failure.

A final native descriptor pass follows the last observable metadata inventory.
It rejects late owner replacement, newly inserted alias storage, missing or
accessor leaf cells, invalid live raw-byte cells and lifecycle closure. The
captured valid byte remains the source register result if its own-data value
changes to another valid byte; only a later reached leaf reads that new value.
These terminal validations are host admission, not extra source scalar loads.
The charged store also rechecks its existing writable boolean destination with
a retained native descriptor immediately before assigning, so a stale public
preflight cannot create a missing cell or invoke a replacement getter/setter.

## Verification

`runBattleTeamRefreshLeafHydratedCompositionTests` is a distinct exported
wrapper invoked by the normal ROM aggregate through
`runAttachedSetupAnimationSelfTest`. Its **86 deterministic genuine shared-graph
fixtures** use explicitly synthetic cells and exercise:

- all four burst-row positions, nonzero values including `80` and `ff`, zero
  and negative zero, mixed burst/nonburst teams, normal and paused boundaries;
- exact charged-clear/leaf/next-row ordering, one leaf load per reached burst,
  late valid scalar changes and fresh next-row loads;
- lazy empty/nonburst paths and skipped suffix accessors, read-only leaf input,
  missing/inherited/accessor/invalid raw bytes and preserved partial writes;
- destination deletion/accessor/readonly/type changes at the final charged
  preflight, without setter invocation or unauthorized cell creation;
- aliases, canonical owner replacement, nested aliases, independent lifecycle
  closure and caught reentry at the leaf load and final observable metadata
  check, with no later row or scheduler work.

The older outer-frame suite now supplies explicit zero `byteD9` for its burst
boundary fixtures and now expects missing `byteEB` when reaching `8008b480`. Its scheduler observation continues
to distinguish numeric source traversal/snapshot fields from identity-only
alias metadata. The existing full graph storage snapshots remain checked.
Focused wrapper and workspace TypeScript results are reported with this
checkpoint's external validation logs; focused tests alone are not the full
contributor, evidence-reader or retail execution gates.
