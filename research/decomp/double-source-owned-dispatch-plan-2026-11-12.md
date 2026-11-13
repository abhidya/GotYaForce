# Double source-owned dispatch migration

Audited baseline: `2a385888`. This is a design and acceptance boundary, not an enabled runtime mode. No original assets are included.

## Decision and first executable milestone

Do not add an unconditional `stepRomActor` call to the existing bridge. The next useful milestone is a deterministic offline Battle/replay scenario containing a Double actor whose ordinary lifecycle, movement and accepted ordinary reactions are owned by one source dispatcher. Inputs and contacts are bounded by the scenario; this is not a user-selectable live mode. Host mode remains the only live path. Success means an ordinary action can finish, receive a supported contact, complete its reaction and return to ordinary control without changing owners midway.

This is larger than porting reaction selectors 1–8. Their reachable continuations include 10 (landing), 12 (terrain fall) and 19 (recovery input); those handlers have their own reachable transitions. Audit and implement the reachable closure before enabling the mode. A first-entry control-bit classifier is not that closure.

Static lifecycle18/19 mappings are verified (see eligibility below). The recovery capture below now establishes one observed two-hit trajectory through ordinary control restoration. It does not yet provide a complete deterministic replay fixture: missing interpreter, physics and initial-state inputs must be captured and the reachable handlers implemented before equivalence can be tested.

The existing repository cannot yet support this milestone honestly. Missing runtime eligibility bindings, shared handlers/streams and source physics/contact bindings below are requirements, not optional adapters. Implementing another detached lifecycle interface would not close them.

## Original baseline capture (2026-11-12)

A dedicated isolated Dolphin run loaded the existing 2v2 save, used the documented
roster reload to select Double Ninja in four slots, observed constructor 8006f60c,
and settled 180 frames. Four live pl0003 actors were verified in battle phase 4.
The bounded observer recorded 100 events over 6.2263 seconds: three complete scheduler
invocations and one partial, with no capture errors. Although input injection was
armed, zero injected pad frames occurred before the event cap. This is an idle
baseline, not action/reaction coverage or a deterministic replay.

All four observed lifecycle paths were 54070 →5475c →54cbc →56900 →55568,
with 18=1 and 19=2. Each complete scheduler invocation observed 55dcc →5568c →59068,
then prehook 6f7c0, UB 5f2a4, FB 5f23c, posthook 6f88c, 55ee4, 5b880 and return.
Marker 578 was 2/1/0/2 at pre/UB/FB/post. Across 97 field snapshots, FB 5da=1,
UB 5db=1, control 5e0=0 and cue-table 4f0=802d3ff8; entry/return stacks matched
for the three complete invocations. No selector transition, saved-FB divergence,
65e24/5c694 reaction call or clone activation was observed.

The original DOL SHA-256 was
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
The local trace SHA-256 was
`11e5f3b6579825bf684af9ed43aa3c7d5366d131b0bdb23e85906843858b1886`.
Raw captures remain local and are not included here. The dedicated emulator was
stopped through its isolated process ledger and its listener was confirmed closed.
These observations corroborate the baseline dispatch envelope only; they do not
validate the callee implementations, reaction semantics or a source-owned mode.

## Controlled action and natural reaction captures (2026-11-12)

Two further isolated runs used the same verified original DOL and documented
pl0003 roster reload, then controller input only. The action run verified 104
injected pad frames, 105 P1 ticks and 22 complete scheduler samples (six idle,
16 active), all with matching return stack pointers. X produced FB/UB
(1,1) → (61,0) → (61,1) → (1,1). Active destinations were prehook 8006f7c0,
UB0 8005f238, FB61 80065dfc and posthook 8006f88c. On the first active tick,
control5e0 changed 0 → 3 during status/input and 3 → 0x43 during FB execution;
it later returned to zero. Clone7c8 stayed zero; no 71750/71858/71938 entry
was observed. This demonstrates real input and an action return, not charged
clone activation or browser equivalence.

The reaction-focused run verified 116 pad frames and captured 13 matched
reaction entry/return pairs on another Double actor: four calls with selector
6fe=1 targeting 8005c810, followed by nine with selector6 targeting 8005cc00.
Eleven complete scheduler samples (three reaction1, eight reaction6) passed
return-stack guards. At pad104 the actor had FB0/UB62, reaction1, phases540/544=0,
control5e0=0x01000003 and timer6b4=30. Initial caller LR was 8005c48c;
subsequent calls used the state62 wrapper with LR80065e34. Observed destinations
were UB62 → 80065e24, FB0 → 8005f238 and posthook → 8006f88c; the actor's4c4
binding was 8006f8d4. The first animation start recorded stream15, group argument
0xffffff80 and variant0.

At pad107 a new initialization call from LR8005c48c replaced reaction1 with
reaction6 and reset phases/timer. The next animation used group argument
0xffffff81 and variant5. Light-stream completion was not observed. This is not
a closed single-contact light-reaction fixture: flat-terrain, nonlethal and
unpaired isolation were not established. Clone state/vector remained zero at
observed posthooks, so these calls do not prove clone-reset behavior. In
particular, do not feed the observed entry control word into the bounded
ordinary classifier as though its excluded 0x01000000 bit were absent.

No deterministic replay was implemented from these traces. Replaying recorded
callee outputs would test a scheduler envelope, not the missing reaction,
terrain, stream and movement implementations. The next executable slice still
requires those actual predicates and the complete reachable continuation;
this interrupted light reaction cannot justify substituting a single-hit path.

Local trace SHA-256 values:

- Action: `e8e08766748431412f6a63bc557ae53ef4402311387712891c932ebf17d469e7`.
- Reaction: `e829db5809dfb4715a6ffbc05965443744d452e5c29047475917241a687b9425`.

Raw traces and numeric capture files remain on the rig. Both task-owned emulator
processes were stopped through isolated ledgers and the listener was confirmed
closed. No original assets, raw trace data or save states are included here.

## Completed nonlethal recovery capture (2026-11-12)

A further isolated run captured the complete observed two-hit trajectory, with
256 verified controller readbacks, 152 frame-state snapshots and no capture
errors. Initial target HP was150. At frame104, damage9 left HP141 and entered
reaction1; at107, damage14 left HP127 and entered reaction6. HP stayed127 for
the remainder of the run. Reaction6 changed to10 at frame174, then11 at212,
and called8006a474 at240. At241 the actor had ordinary FB/UB(1,1) and control0.
Fresh P2 X input at242–243 produced FB61/UB0 and control0x43. Reaction selector6fe
still held11 afterward: that byte alone is not a valid reacting predicate.

Completion flags1cee/1d0e became1 at frames206,212 and240. The observed stream
sequence was group0x80/variant0 interrupted by0x81/5, followed by0x82/3,
0x82/1 and0x82/5. All67 captured original terrain-query argument/result pairs
returned height0 and normal(0,1,0). The ground helper returned0 on66 calls,
then1 at174 when timer6b4 was0. Position moved from(1200,0,1000) to approximately
(1555.459,0,1212.368) at recovery. Eleven paired posthook samples passed
return-stack guards. Two4c4 entries were observed, but clone7c8 remained0;
armed clone cleanup/reset is still untested. Input5bc bit0x100 was never set.

This closes the observed trajectory, not an implementation replay. It remains
a two-hit knockdown/recovery rather than an isolated light reaction. Do not
combine detailed boundaries from capture03 and the later recovery run into a
purported single deterministic fixture. The raw label `motion20_87_raw` in this
capture begins at actor+0x18, not+0x20; parsed position fields were checked.

The concrete offline milestone is now reaction1 →6 →10 →11 →ordinary control
and fresh X admission, with a flat-plane terrain provider and exclusive source
ownership. Port5c290/5c694 admission/cleanup and5c810/5cc00/5d258/5d494, their
movement/rotation dependencies and family hooks. Supply verified shared80/81/82
programs, completion semantics, constants/tables and initial/transition state.
Missing capture inputs still include complete animation-interpreter inputs,
physics parameters/timestep reads and other terrain callbacks. Compute landing
from motion, not from the recorded66-false/one-true results. Match the recorded
transition frames and intermediate fields before claiming equivalence. Existing
contact reducers and scheduler callbacks alone cannot execute this milestone.

Local trace SHA-256:
`199842d40138387d0d82945e64cc81956d772489ce041da83e0d7b44104de18e`.
The raw capture remains on the rig. The isolated emulator was stopped through
its ledger; its process was absent and listener closed. Earlier captures were
preserved. This checkpoint changes documentation only, not live clone behavior.

## Audited ordering and ownership

Source evidence is the local Ghidra export; line numbers identify the current corpus.

- `chunk_0003.c:4311–4345`: global66 gates the actor sweep and later collision/action phase. Actor updates precede collision; do not collapse those phases into each actor's local tick.
- `chunk_0006.c:6670–6688`, 53a2c: global prepass, registered actor54070 updates, then global postpasses.
- `chunk_0006.c:6958–6994`, 54070:5685c previous-transform snapshot runs before the3e5/globalD2 lifecycle gate. Lifecycle18 chooses a handler; cleanup follows even when that handler is gated off.
- `chunk_0006.c:7420–7525`: lifecycle handlers selectively call55568. Death/removal54d54 does so only in some substates. Host `alive` is not an equivalent selector.
- `chunk_0006.c:7778–7808`, 55568:55dcc derived geometry/state,5568c status/timers,59068 input/selection, position snapshot,4bc prehook, saved FB index, UB, saved FB handler with live fields,4c0 posthook,55ee4 flags, conditional position restoration,5b880.
- `chunk_0007.c:2083–2107`, 59068:685c0/686f0 charge input runs before4bc. `chunk_0009.c:4093–4117`,6f7c0 changes58e20 afterward. Charge sampling and later charged-command admission must not be replaced with one current7c8 predicate. This bit does not disable ordinary X.
- `chunk_0003.c:6227–6287`: collision accumulation/admission invokes5c290, potentially5c694 immediately. That call is not a second whole actor dispatch and does not invoke4c0. The next eligible actor dispatch consumes intervening live state.

Host conflicts: `battle.ts:1208–1231` already advances status, invincibility and gauge windows; death owns movement/lifecycle at1268–1284; hit/down interrupts the bridge at1296; input is sampled before bridge tick; inactive bridge tick returns at2950 before sync/dispatch. Ordinary movement/attacks and state timers then run in Battle. `bridge.ts` action admission can already execute an entry dispatch, and its part-mode direct-root exceptions deliberately retain host lower-body movement.

Therefore the source-owned path must replace, rather than layer on, the actor's host movement, reaction progression, action selection, overlapping status/gauge/invulnerability updates and source-owned charge bookkeeping. Team accounting, presentation and projectile containers may remain host services only after their state-write boundaries are explicit. Do not call host `interrupt()` to represent a source reaction.

## Required state and implementations before enabling

1. **Eligibility:** static mapping verified:54070 indexes802d3264 by18 (`541ac,5475c,54d54,5514c`); outer1's5475c indexes802d3274 by19 (`547dc,54c78,54cbc,54cf0`). Writer chain541ac→547dc→54c78 establishes18=1 with19=0→1→2;58244 also explicitly writes1/2.5475c may redirect19=1/2→3;5bbc0 enters18=2,54d54 exits to18=3, and5514c can reset18=0. Original pointer reads independently confirm the separate tables; there are no index bounds checks. Runtime trace/replay remains pending. Bind global66 and per-actor3e5/globalD2 inhibition and verify1a-dependent normal/death/spawn behavior, including outer cleanup while gated. Do not infer these from UI pause, host freeze or `alive`.
2. **Persistent source state:** authoritative control5e0, FB/UB selectors and phase blocks, source input latches and58e, transform history, reaction6fd/6fe, strength702, status1da/599, gauges and timers6b4/6b6/720, invulnerability272 and contact730. Reset/redeployment needs explicit initialization, not reuse of a host hit state.
3. **Shared dispatch:** implement selected ordinary states and the complete reachable reaction closure. Current UB2–31 include approximate stream/physics factories;62 and63 are unported. State-table callability is not proof of coverage.
4. **Reaction dependencies:**5c15c/5c080 cleanup and4c4 callback, descriptor joint resets,5c694 timeout/recovery tail, shared animation completion bytes, knockback direction/strength tables,5ee0c/5ef08 terrain query and landing predicates. See `chunk_0007.c:3895–3998,4159–4596,5529–5839`.
5. **Streams and geometry:** the per-part bank-provenance fix does not supply shared reaction streams. Supply verified permitted decoded data and animation completion semantics, with a source-equivalent terrain/physics adapter. Existing bridge ground clamping is not automatically equivalent.
6. **Collision integration:** bind the bounded contact/frame reducers to actual accepted source collision records, pre-hit HP/gauges and source scaling. Host `applyHit` outputs cannot simply certify the absent inputs. Preserve contact ordering, rejected records, accumulation and immediate reaction dispatch separately from the actor sweep.
7. **Family hooks:** port6f7c0 sampling and6f88c reset only against this authoritative cadence/control. Verify4538c near-zero normalization and source+b4 scaling before touching persistent7b0. Keep charged clone activation disabled in this milestone.

## Unsupported boundaries and transition policy

An explicit opt-in alone is not evidence that a transition is supported. Run the offline scenario only after its reachable states and input/data domains are covered. Preflight its recorded inputs and contact domain before starting. Actor-only preflight cannot predict future unsupported hits in a live battle; it does not authorize live enablement. Never run the host and source movement paths for the same actor update.

During development, an unexpected unsupported state must fail the offline test scenario with a precise diagnostic before further mutation. This is a test failure, not a proposal to freeze a player in a live match. Do not silently continue with a noop or hand a half-mutated actor back to host hit/down. Automatic runtime fallback would require a separate verified whole-step conversion/rollback contract covering gauges, streams, motion, timers, projectiles, other actors and already-issued external effects; none exists today. A rollback of just the source-owned actor is insufficient. Live enablement requires either complete reachable support or verified whole-step unsupported-transition handling without silent host fallback, duplicate effects or freezing the player.

Dispatch accounting should distinguish one eligible whole actor dispatch from a collision-time reaction handler call. Admission must occur inside the chosen actor ownership schedule rather than adding a second whole dispatch from `tryStartXSpecial`. Preserve saved-FB selection and live actor fields. Retain existing part-mode exceptions outside the newly supported mode.

## Acceptance tests for the executable milestone

Use actual Battle stepping plus verified source traces where available, not only pure reducer fixtures:

- Two actors, interleaved input/contact events: every eligible actor update performs exactly one preprocessing/prehook/UB/FB/posthook sequence; action start does not add another. Global collision follows the actor sweep.
- Idle, move, ordinary X start/finish/restart, hit and recovery retain one owner; host movement, gauge/status decay and source equivalents cannot both run. Compare positions and clocks, not just callback counts.
- Global66 pause and per-actor3e5/globalD2 inhibition preserve the exact distinction between skipped inner dispatch and outer snapshots/cleanup. Source lifecycle death substates are tested separately from host `alive`.
- Reaction1–8 phase entry and every reachable continuation: completion, landing, terrain transition, recovery input, timeout and return. Unsupported reachable states fail explicitly. Mixed shared/family stream backing and completion bytes execute real decoded programs.
- A collision after actor posthook may enter5c694 immediately but cannot fire6f88c early. The next eligible posthook reads the actual control word after that dispatch's reaction handler, including a handler that clears the reset bit.
- Charge bookkeeping reads the prior sampled58e20; subsequent prehook updates it; ordinary X remains independently admissible. No test activates an invented charged producer.
- Persistent owner7c8/7b0 survives ordinary action storage teardown, but source reset clears it at its actual hook. Redeployment creates independent state.
- Boundary cases cover rejected/duplicate contacts, signed gauge wrap, zero/near-zero offsets, bank absence and pause/resume. Unsupported diagnostics occur before external effects or partial owner transfer. Existing host-mode Battle/lifecycle regressions remain unchanged; live behavior stays disabled until source-mode tests, matching traces and whole-step boundary handling pass.

No implementation or CI claim is implied by this plan. The stream-bank and owner-lifetime fixes implemented on the draft branch remain separate, bounded prerequisites. File/line anchors above describe this baseline; function names identify the durable source references.

## Implemented prerequisite: signed reaction rotation

`rom/helpers.ts` now ports66ec0/66f1c as `seedReactionTurn`/`stepReactionTurn` on existing actor fields72/7e/5aa/1dc8. Original DOL instruction inspection confirms signed32 `divw` with signed16 numerator, low16 storage and zero-divisor preservation.66f1c uses `fsubs`/`fmuls`/`fctiwz`: multiply the signed16 rate by source float1dc8 with float32 rounding, truncate toward zero, then test the signed16 step and stored signed16 remainder. A rounded-zero step takes the nonpositive branch. A zero rate clears5aa without changing yaw. Adding the short-converted step rather than the full conversion result is equivalent for low16 yaw/remainder stores.

Original function byte SHA-256 evidence (bounded inspection; no binary bytes included):
- `80066ec0..80066ed7`: `f18a8b1390efd1596223654e9ccacfc7a8ccdfe04035ada3af8f9491e25f9c15`
- `80066f1c..80066fef`: `810d9d92c47f065f87635b21d1e83d5e6c9d4189c795bdee46265535999fe38d`

The implementation rejects nonfinite/out-of-signed32 float-to-integer conversions before mutation rather than inventing PPC exceptional conversion results. Deterministic helper tests cover signed division, zero steps, wrap and float32 rounding. The captured recovery had7e=0 at inspected checkpoints and did not capture1dc8: it does **not** dynamically validate nonzero rotation. These helpers are not yet wired into a source-owned reaction handler or live mode.

## Implemented prerequisite: reaction stream continuation

`rom/stream-vm.ts:updateReactionStream` ports the5f188 continue/restart decision for shared groups80/81/82 and nonnegative signed-byte slots, calling the existing real stream runtime. It compares part1's retained signed-byte group/slot and source1cfc (part1+8, represented by `prevTarget`). Matching group80 continues at values≤2; matching other admitted groups continue at≤5; otherwise it restarts mask15 at rate−1. Original reads verified804374e4=2,804374b0=5,80437464=−1. Function5f188..5f237 SHA-256: `0fa0f943d79b1f73907e11433758f4a41ca32b78348508dbc7f2372fd2e29fb3`.

Source uses a GT-clear branch, so unordered floating comparison also continues. This bounded helper rejects nonfinite source1cfc and unknown part identity before mutation instead of claiming that exceptional path. The generic VM does not reconstruct source1cfc; a future source-owned handler must provide that field, not substitute animTime or frameClock. Existing start/reset group identity, per-part backing, countdown reset and decoded-host sentinel behavior are unchanged. Tests seed source1cfc and execute real byte programs through continuation, changed group/slot, interruption and absent-bank cases; they do not validate retail shared programs or complete reaction timing. No live reaction wiring is enabled.

## Source target production and schema correction

Original4c050 stores the next-command pointer at part+04; the port's `frameClock` is a synthetic VM timer, now marked `port_side` instead of falsely mapped to that address. The regenerated oracle map refuses its export and contains no clock mapping for original continuation bytes. The codec has no field-hydration API; raw decode primitives remain explicit post-state assertions. This removes incorrect claimed coverage, not an interpreter discrepancy or a parity improvement. VM behavior is unchanged, and no source continuation field has been invented.

Source1cfc production remains missing.4cd24's unmet, non-bit8 wait path copies target(+08) to previous(+0c), calls49e58, conditionally adds signed animation duration to accumulator(+10), then stores float32(accumulator+animation frame) to+08. Masked/completed paths and bit8 countdown have different behavior.4c050 performs similar postprocessing only when its decoded commands contain no opcode01; opcode01/4c298 has its own animation-change bookkeeping.

The next migration must implement the relevant49e58 animation mode(s),48648/opcode01 setup, source wait bit predicates and current/next command pointers together. For part1 this needs actual animation frame1b20, duration1b38, segment flag1b41, actor1d9a/1dc8 and dispatch-mode state. The existing recovery capture contains target/accumulator outputs but not these inputs or animation-handler entry/return. Neither target subtraction nor the synthetic frameClock can supply them. This correction does not enable source1cfc production, reaction timing or live ownership.

## Source pointer and completion representation correction

The remaining scalar annotations for `RomPartState.streamPtr` and `active` also
claimed an invalid direct conversion. Source 4c020 clears the current/next pointers
and completion byte to zero. Source 4c050 executes commands up to a wait, stores
the absolute current-wait pointer at part+00 and next-command pointer at part+04,
and clears part+1a. Source 4cd24 sets part+1a when a terminal wait completes.
The host cursor instead contains a retained-bank offset, -1 when inactive, or
`Number.MAX_SAFE_INTEGER` for a decoded-only host schedule. Its active flag is 1
during execution and 0 after both reset and completion. Neither raw pointer
encoding nor a direct/inverted flag copy preserves these source states.

Both fields are now `port_side`; the generated oracle map refuses their scalar
export before any write. Regression cases cover inactive/zero/nonzero/sentinel
cursors and both host active values against source completion 0 and 1, preserving
all source bytes and the write log. A future source-owned interpreter needs real
pointer provenance and a separate source completion latch, not these host values.
No runtime behavior, source target production, or live clone activation changes.
