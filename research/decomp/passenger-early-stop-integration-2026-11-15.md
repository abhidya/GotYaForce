# Bounded passenger early-stop integration

Date: 2026-11-15. Implementation base:
`113f410f4cbb40a74d9cc5983950991edd23d9e3`.

## Evidence and exact boundary

This change uses only the existing checked-in
[mass-preparation evidence](mass-preparation-evidence-2026-11-14.md), which
records the complete `80053b30` body `[80053b30,80054070)`. No new archive,
ProgramDB, DOL or pointer-payload selection/read was made. No new retail replay,
matching result, browser activation, scheduler execution or successful outer
frame is claimed.

The original three unrolled pairs retain their six fresh actual-table loads.
Each reached actual receives its own `mass204 + mass208` store **before** its
signed contact byte at `+1db` is tested. For a nonzero contact:

- First half: `53cb8` loads actual `+1e4`, `53cbc` loads passenger `+83`,
  `53cc0` sign-extends it, and `53cc4` branches on nonzero to `53cf8`, the next
  actual-table half.
- Second half: `53d14` loads actual `+1e4`, `53d18` loads passenger `+83`,
  `53d1c` sign-extends it, and `53d20` branches on nonzero to `53d54`, the pair
  loop continuation.
- A captured zero byte refuses immediately before `53cc8` or `53d24`, the
  respective passenger `+3e4` load. No passenger slot, accumulated mass,
  original-actor mass reload, stack passenger count, passenger contact or next
  chain link is consumed or updated by this continuation.

Nonzero means every valid raw byte from 1 through 255, including negative
signed-byte representations. The implementation does not confuse the branch
with a positive-only test. After all six admitted traversals, the existing
RNG/ordering and target-preparation bounds remain unchanged.

## Canonical storage

`RomActor.linkedOwner1e4?: RomActor | null` is an explicit optional actual
pointer with no constructor default. It is distinct from any collision-runtime
`linkedOwner` binding. Missing, accessor, null, numeric, symbolic, unknown,
foreign, interior or non-actor values refuse at their reached ownership or
source-load boundary, after earlier self-mass writes.

The captured actual object is resolved by the scheduler's **same allocator**
`getPointerIdentity` / `getPointerTarget`. The allocator's actor binding and
the spawn runtime's genuine world must refer to that exact object. The existing
sealed `allocator.getActorBinding(targetId).byte83` remains the sole `+83`
owner, exactly as in the third-pass target83 lane. No actual-actor byte83
shadow, alternate pointer map, passenger mass owner or replacement callback
was added. A self-pointer is accepted when these same constraints hold.

The pointer and byte are each captured once for that traversal. Metadata checks
do not reload their scalar values; a later half sees fresh live values. Zero
contact does not inspect the optional pointer or any passenger cell. Missing
pointer ingress retains the prior immediate boundary without first inspecting
the new alias inventory. Identity and alias inventories are host admission,
not extra source pointer-table loads.

Named `+1e4` and `+83` aliases are rejected on their related owners. Numeric
byte offsets are rejected on actor-role records, not on unrelated allocation
byte buffers that legitimately contain those offsets. Observable checks are
followed by native terminal descriptor/owner/lifecycle checks, so a last-hook
alias, removed/accessor pointer, owner substitution or caught reentry cannot
continue the later actual half. Every resolved passenger is retained for
permanent Double-lifecycle closure with the pre-existing outer scheduler graph.
The closure neither resolves an unreached pointer nor grants execution rights.

Independent review identified a stale descriptor gap in the resumed self204
store: its observable preflight could return an old data descriptor while the
live destination became an accessor. That exact self-accumulation store now
uses a native terminal descriptor check before assignment. A late accessor,
deletion or read-only change refuses without invoking a setter or recreating a
cell. Earlier stores and captured float32 arithmetic are preserved. This is
not a rewrite of unrelated outer-frame stores.

## Oracle codec contract

The generated field map records `linkedOwner1e4` as `ptr +0x1e4`, with the
updated actor-source hash. The runtime's object identity is **not** a numeric
GameCube address. The previous generic `value >>> 0` behavior would silently
encode an object as zero, so the codec explicitly refuses object identities
and other non-address values for this new field. It accepts explicit unsigned
32-bit arena addresses and null (zero); no address resolver or arbitrary actor
serialization is invented. Existing unrelated pointer-field contracts remain
unchanged. Refusal writes no bytes and never calls an object's coercion hook.

## Integration and validation

The new `battle-passenger-early-stop.selftest.ts` uses the existing genuine
mass-preparation composition and its separately world-bound target. It adds
only explicit caller1e4 and the genuine target allocation83 binding. It does
not replace production owners or hydrate passenger mass/status storage.

- `createBattlePassengerEarlyStopTestFixture(value = 1, bind = true)` is the
  focused exported fixture. Passing null omits the sealed83 cell.
- `runBattlePassengerEarlyStopHydratedCompositionTests()` is the focused test
  export, integrated into the existing attached-setup lifecycle self-test and
  therefore the contributor `@gf/combat test:lifecycle` gate.
- The new suite exercises 116 genuine shared-graph fixtures: signed-byte
  branches, all six half-specific zero boundaries, same/self targets, read-only
  byte83, exact source load/store order, fresh table and pointer/byte captures,
  skipped poisoned continuation fields, invalid pointers/bytes, cross-owner and
  late aliases, descriptor/owner/lifecycle changes, resumed-store faults,
  reentry and permanent graph closure.
- The codec suite contains 18 tests, including the new mapping/address/null
  cases and object/coercion refusal with sentinel and write-log checks.
- Focused affected suites cover existing mass preparation and all38 store
  prefixes, mass ordering, outer-frame, team leaf, burst expiry, target
  preparation, third-pass83, association guards/scan, secondary nonnull and
  nonflat Double-ground composition. Strict project TypeScript and
  `git diff --check` are run against the final candidate. Full contributor and
  oracle final gates are a separate publication check, not implied by these
  focused runs.

The fixtures remain explicit synthetic host compositions, not six hydrated
retail actors, passenger mass propagation, hardware parity or playability.
Zero83 passenger propagation, later normal-stage predecessors, complete frame
scheduling and the previously documented unsupported paths remain unfinished.
