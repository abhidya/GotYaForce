# Bounded first-passenger mass accumulation

Date: 2026-11-15. Implementation base:
`152668b638c2d7fdebb3487cb502a8f0289371be`.

## Evidence and admitted continuation

This lane uses only the existing checked-in
[mass-preparation evidence](mass-preparation-evidence-2026-11-14.md), especially
its six-live-pointer discussion and complete `80053b30` operand listing.
No archive/DOL/ProgramDB selection, payload extraction, raw game-binary read,
new retail replay, matching result or retired driver run was made.
It extends the zero83 boundary recorded in
[passenger early-stop integration](passenger-early-stop-integration-2026-11-15.md).
That report's nonzero83 behavior and resumed self204 fix remain in effect.

Both original unrolled halves now admit exactly one zero83 passenger update:

1. Capture the actual passenger's raw slot3e4 at `53cc8` / `53d24`.
2. Load that passenger's canonical Borg `sourceArrowMass204` at `53ccc` / `53d28`.
3. Freshly load the **original actual actor's** `mass208` at `53cd0` / `53d2c`.
4. Sign-extend the captured slot, then load the unsigned private local counter
   at `53cd8` / `53d34`.
5. Call the existing exact `addSourceFloat32(passenger204, original208)`.
6. Increment and store the local byte with low-byte wrapping at `53ce4` / `53d40`.
7. Store the sum to the same passenger Borg204 at `53ce8` / `53d44`.
8. Load and sign-test the passenger's actual `supportContact1db` at `53cec` /
   `53d48`. Zero resumes the next original live-table half. Every signed
   nonzero byte refuses **before** the second link load at `53cb8` / `53d14`,
   preserving both stores.

The source does not impose a one-passenger depth limit. The nonzero-contact
refusal is an explicit **unsupported continuation**, not an original check,
cycle detector, visited set, successful traversal or completed outer frame.
All six original table cells are still loaded live, and each original self204
store still precedes its original contact test. No captured passenger list or
cached original contribution replaces those source loads.

## Canonical ownership and host bounds

The first passenger helper returns its already captured identity, actual
object, allocation83 owner and ownership guards. The zero83 branch does not
resolve the pointer again or reread83. A nonzero83 branch does not reach the
passenger slot, status/Borg, mass, counter, contact or next link.

Passenger204 uses the existing genuine `status.getActualBorg` admission.
Passenger slot/contact remain on the same actual object retained by the
allocator and world. Original208 remains on the original actual object. There
is no actual204 copy, alternate passenger map, new production actor field,
codec change, status API or allocator API.

The six local counter cells remain private and sparse. Only the first pass's
**active physical row** initializes its corresponding cell. Passenger identity,
team and current slot do not initialize a counter. The captured signed slot
must select0..5 and an initialized cell. An out-of-domain or uninitialized
selection refuses after both mass loads, before addition/stores. Raw malformed
bytes refuse at their source load. Arithmetic remains finite exact binary32,
nearest-even with gradual underflow under the existing helper's explicit
FPSCR assumptions; overflow refuses before either passenger store.

The increment uses unsigned-byte load semantics and `(old + 1) & 255` storage.
At most six increments are reachable in this bounded lane, so the tests do not
inject counter storage or claim a source-path255-to0 wrap witness. The existing
ordering suffix now genuinely consumes nonzero local counts, including a
six-contribution case that shifts an actor ahead of earlier zero-count actors.

Reached-role alias checks, canonical owner retention, lifecycle checks and
native terminal descriptors surround the captured loads and stores. Unreached
genuine Borg204 owners are not mistaken for shadows or eagerly inspected.
A late missing/accessor/read-only destination cannot call a setter or recreate
a deleted cell. Captured valid values survive later scalar changes; owner,
descriptor, lifecycle and alias violations refuse while preserving completed
prefix effects. Any refusal closes the retained outer/scheduler graph, without
creating a frame epoch or scheduler execution authority.

## Integration and checks

`battle-passenger-accumulation.selftest.ts` reuses
`createActorThirdPassTestFixture` and its genuine distinct multi-actor bindings.
It adds explicit test204 to the already bound passenger Borg, plus actual
slot/contact fields and the genuine sealed allocation83 binding. Extra active
physical rows use genuine stage `lifecycle18=0`, so counter initialization does
not invent parameter4ac data. The fixtures remain synthetic host compositions,
not reconstructed retail constructors or hydrated game assets.

Focused exports in `attached-setup-animation.selftest.ts` are
`createBattlePassengerAccumulationTestFixture()` and
`runBattlePassengerAccumulationHydratedCompositionTests()`. The suite is wired
into the existing attached-setup lifecycle runner and contributor gate.

The new suite covers129 genuine fixtures: both halves/all six positions,
shared/repeated/self passengers, all six initialized counter positions,
physical-inactive and out-of-range counters, raw slots6/127/128/255 and malformed
bytes, captured pointer/83/slot/mass/contact changes, fresh original208 rather
than passenger208, next-table mutation, poisoned second links, exact-f32
rounding/subnormal/signed-zero/overflow behavior, missing or counterfeit owners,
late aliases/descriptors/owner replacement, reentry, closure and nonzero-count
ordering. The existing early-stop suite has113 fixtures after replacing its
obsolete zero83-boundary expectations with genuine missing-status refusal and
bounded self accumulation. Its nonzero83 lazy checks and resumed self-store
regressions remain intact.

Implementer validation uses strict combat-project TypeScript, `git diff
--check`, and focused affected suites for passenger accumulation/early-stop,
mass preparation/ordering, outer frame, burst expiry, team refresh, target
preparation, third pass/target83, association guards/scan, secondary nonnull,
and nonflat height-query composition. Frozen source hashes and command logs
are kept with the validation artifacts. Independent semantic/mutation review
and the full contributor/oracle publication gates are separate checks owned by
the parent workflow; focused success alone does not claim those gates passed.

No browser activation, hardware parity, complete normal stage, arbitrary
passenger chain, complete scheduler frame or playability is claimed.
