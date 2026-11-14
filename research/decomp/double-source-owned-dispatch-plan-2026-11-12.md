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

The next migration must implement the relevant49e58 animation mode(s),48648/opcode01 setup, source wait bit predicates and current/next command pointers together. For part1 this needs actual animation frame1b20, duration1b38, segment flag1b41, actor1d9a/1dc8 and dispatch-mode state. The earlier recovery capture contains target/accumulator outputs but not these inputs or animation-handler entry/return. Capture05 below supplies actor/part inputs, but not the backing AObj/JObj state that produces them. Neither target subtraction nor the synthetic frameClock can supply missing inputs. This correction does not enable source1cfc production, reaction timing or live ownership.

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

## Animation-input capture05

A new isolated original-game run recorded **269 matched entry/return pairs** and
**236 verified controller readbacks**, with zero capture errors and all return-stack
guards passing. It reached reaction11 but the 240-second bound ended at frame236,
before ordinary recovery. This is independent bounded evidence, not an extension
of capture04's fixture or a new ordinary-return/fresh-X verification.

The pairs comprise 124 calls to 49e58, their 122 mode0/49f10 and two mode2/4a0e0
dispatches, and seven calls each to 48648, 4c298 and 4c050. No call remained open.
Descriptor gates 1d88/1d8c were non-null throughout, and 1db3/1d9a stayed zero.
Dispatch marker578 took values1 and2, but neither early-return gate was exercised.
Mode1 setup appeared at frame235; its handler was not reached before cutoff.

Representative directly observed part1 values (hexadecimal values are float32
bits unless marked as a signed duration):

- Frame105: timestep `3cf5c28f` (0.029999999329447746), animation frame
  `00000000` → `3cf5c28f`, duration60, accumulator0 and status/segment/completion0.
- Frame127: timestep2, animation38 →40 (`42180000` → `42200000`), signed
  duration39 (`0027`), status1b42 changed0 →1. Stream completion1d0e remained0
  at this handler return; animation status and stream completion are distinct.
- Frame148: timestep1.5, animation28.5 →0 (`41e40000` → `00000000`), signed
  duration30 (`001e`), segment1b41 changed0 →1. Accumulator remained39
  (`421c0000`) at handler return; the subsequent same-frame snapshot directly
  read accumulator/target69 (`428a0000`).
- Frame168 repeated the rollover, with accumulator69 →99 in the subsequent
  snapshot. Frame169 directly read frame1.5, accumulator99 (`42c60000`) and
  target100.5 (`42c90000`). None of these inputs was inferred by subtraction.
- Frame205: animation43.5 →45, duration44, status0 →1; stream completion was1
  in frame206's snapshot. Frame208: animation0 →1, duration1, status0 →1;
  elapsed1b1c subsequently reached4 while animation1b20 stayed1. Stream
  completion became1 at frame212.
- Mode2 at214: timestep2, transition limit5, clock1 →3, blend `3f4ccccd`
  (0.800000011920929) → `3ecccccc` (0.3999999761581421), animation0 →2.
  At215, transition clock3 →5 and mode2 →0, but animation stayed2 while elapsed
  increased2 →4. An unconditional animation-frame-plus-timestep implementation
  would fail this observation.

### Dependency boundary exposed by the capture

The next implementation cannot stop at 49f10's initial clock increments.
49e58 snapshots clocks and dispatches through 802d0d84. Mode0/49f10 and
mode2/4a0e0 call 4a830 →4aae0 →4acdc →4adc8/4b76c. Joint ranges and mappings
come from actor1d90–1d93, descriptor4b0 and the1db4 tables. Source4adc8 obtains
segment1b41 from AObj flag `0x04000000`; source4b76c copies AObj+04 back into
animation1b20. Duration comes from AObj+0c. Request243b90 and interpreter243bd0
own request suppression, rate, rewind/end, looping and stopped state. Setup48648
also requires descriptor lookup4d1f4, metadata4d244, table802d0d70 and transition
initialization.

A bounded source AObj clock/request/end/loop implementation and verified
mode0/mode2 handling are the next prerequisites for actual stream-wait and
accumulator production. Captured handler outputs must not stand in for these
implementations. This capture lacks backing AObj/JObj headers, FObj callback
inputs and complete geometry effects. Negative duration, nonzero rewind,
multi-loop steps, bit8 countdown and early-return gates remain unverified.
No source-owned Battle mode or live clone behavior is enabled by this evidence.

Local evidence SHA-256 values (raw captures remain on the rig):

- Raw capture05: `8f485b7900c32ad35951122346852eacd8dabf6cfa87e5a691fc52b079aba893`.
- Derived numeric summary: `c951e560814dde97794348c51eeefb79ba0f3e6f200824339b4d971929ea780a`.
- Capture script: `9047071ddce77a5e573cfa856e4bac5feb3a369698e722908fc605c6f2b81513`.

The task-owned Dolphin was stopped through the existing isolated process ledger;
its process was absent, ledger cleared and listener closed. Existing emulator
profiles and the supervisor were unchanged. No original bytes or raw captures
were uploaded or committed.

### Original AObj clock and callback audit

Bounded read-only DOL inspection verifies request80243b90 (size0x40) and
interpreter80243bd0 (size0x1b8), with the same original DOL hash recorded above.
AObj fields are flags+00, frame+04, rewind+08, end+0c, rate+10 and FObj list+14.
Constant8043d1f8 is positive zero (`00000000`). Request stores float32(frame),
clears STOPPED `0x40000000`, sets REQUEST `0x08000000`, then forwards the original
double request argument to FObjReqAnimAll, not the rounded stored frame.

The interpreter returns immediately for null/stopped objects. A request suppresses
one advance and is cleared; otherwise advance uses `fadds`. When LOOP `0x20000000`
and end≤frame, the finite rewind<end branch stops FObjs, reloads state, computes
`f32(rewind + fmod(f32(frame - rewind), f32(end - rewind)))`, stores the result,
and requests FObjs at that stored frame. Both differences use `fsubs`; the final
addition uses double `fadd` followed by `frsp`. Do not separately round the fmod
result. The other rewind/end branch sets frame=end without stop/request calls.
Both loop branches set WRAPPED `0x04000000` and interpret with delta0; the
non-wrapping path clears WRAPPED. Non-loop completion sets STOPPED without
clamping the frame. Final stopped/running counters depend on the final flags.

FObj calls cannot generally be replaced by a precomputed list of events. The
wrap path executes StopAll before reloading rewind/frame/end, and reloads the
FObj list before ReqAll. The interpreter reloads flags/end/frame after InterpretAll,
and reloads flags after the completion StopAll. StopAll8024895c itself can invoke
FObjInterpretAnim80249ac4 for node state6, including indirect user callbacks.
Flag `0x10000000` suppresses only the ordinary InterpretAll callback; wrap-stop
and end-stop retain the original callback. ReqAll's audited body has no callback,
but noninterference still requires valid, nonaliased objects.

A pure scalar helper is defensible only for a null FObj list or an explicit
non-mutating/nonaliasing effects contract. General callbacks require synchronous
effects and subsequent live-state reads. Nonfinite values, intermediate float32
overflow, unsupported aliasing and unverified FP-environment behavior need explicit
exclusion. In particular, the DOL takes the rewind/end clamp branch on an unordered
comparison, unlike the decompiler's apparent inverse comparison. Capture05 lacks
AObj headers and does not dynamically verify any new helper under these contracts.

Source anchors: `chunk_0070.c:2569–2670` and
`chunk_0071.c:215–273,869–1225`. Original function SHA-256 values:

- Request80243b90: `8a7a3a50f9ea7d80a891bc65745cde96d50b329c296dc359899b6754763b9b29`.
- Interpreter80243bd0: `dd5555ed929b4f8b047ff6d91a36f2c304089c4a7d51d1e265adb959931298e8`.

## Implemented prerequisite: offline AObj scalar control

`rom/aobj-clock.ts` now implements the audited request and interpreter scalar
control, using explicit source-width state and counters. FObj operations are
mandatory synchronous effects, not optional no-ops or precomputed events.
Effects execute between source state operations; subsequent fields and list
identities are read live. This preserves callback-sensitive wrap/completion
ordering and ordinary-only callback suppression. Request forwards the original
double argument while storing float32, and non-loop overshoot remains unclamped.

The admitted domain uses factory-created, nonaliased records with finite float32
clocks and uint32 flags/counters; FObj lists and callbacks use opaque identities,
not raw RAM pointers. Nonfinite values, float32 overflow, malformed/read-only
state, asynchronous effects and same-object reentry fail explicitly. An error
does not roll back earlier state writes or executed effects. In particular,
rejecting an asynchronous effect cannot cancel work it has already started.
These are offline scenario failures, not live-match fallback behavior.

Lifecycle tests cover precision and request suppression, stopped/null handling,
wrap/clamp/overshoot, signed zero, negative/zero rates, source rounding, callback
mutations, reloaded list identities, counters and rejection boundaries. Concrete
negative controls distinguish a rounded request argument, unrounded pre-fmod
subtraction and stale/precomputed callback state. No distinguishing witness is
claimed for rounding an already-representable fmod remainder.
The original-request precision test records the AObj callee boundary; it does
not establish FObj arithmetic on arbitrary wider operands. The executable FObj
instruction domain is restricted by the processor-manual review below.

This is scalar/effect-boundary implementation coverage, not an FObj implementation,
original trace replay or live integration. Source FObj/JObj backing data, callback
receiver bindings, geometry effects, shared reaction setup and source stream-wait
production remain to be supplied and independently verified. Capture05 does not
provide AObj headers and does not dynamically validate this new module. No live
clone or source-owned Battle mode is enabled.

## Implemented prerequisite: FObj header and list effects

`rom/fobj-list.ts` supplies actual bounded request/reset writes and ordered list
walkers for request802488b8, stop8024895c and interpret-all8024a198. Its effect
adapter connects those operations to the offline AObj controller. Request resets
cursor+04 from base+08, stores `f32(s16(+18) + originalRequest)` at+1c,
clears+11/+12/+16/+1a, writes positive zero to+20/+24/+28/+2c, clears flag0x40
and sets the low flag nibble to1. Other modeled fields are preserved. The request
must be single-representable before this single-precision arithmetic executes;
it is refused rather than silently converted when outside that domain. Earlier
wide-double cancellation examples were mathematical extensions, not guaranteed
Gekko behavior, and have been replaced with explicit refusal tests.

Stop invokes the required per-node interpreter only when byte+12 equals6. It
then reloads and clears the flag low nibble, including for nodes not interpreted.
Interpret-all invokes the interpreter for every node. Both walkers load the next
link after the callback and any stop flag write, so callbacks can redirect or
terminate traversal. They do not snapshot a list or precompute effects.

The per-node decoder/interpolator is still a mandatory synchronous dependency,
not implemented by these walkers. Callers must supply that implementation or
throw for unsupported operations. No default no-op is provided. The existing
decoded-key HSDRaw-style sampler is not substituted for the source runtime state
machine. Tests use explicitly labeled interpreter fixtures; they demonstrate
AObj/list ordering and header changes, not original joint callback behavior.

The bounded runtime owns sealed, nonaliased header records and opaque node/data
identities, not RAM addresses or pointer arithmetic. Scalar widths are checked;
clocks are finite float32. Generic list delta arguments are finite doubles, but
nonempty requests and the active timing interpreter additionally require
single-representable operands at the audited single-arithmetic sites. Unknown
nodes, read-only or malformed fields, nonfinite results, cycles/revisits, a
declared traversal budget, asynchronous effects and same-runtime reentry abort
explicitly. These restrictions exclude unsupported scenarios rather than model
retail failure behavior. Earlier writes and callbacks are not rolled back.
Null lists are genuine no-ops. Allocation/free, unmodeled header fields and
exceptional PPC floating-point environments remain outside this contract.

Regression coverage includes signed offsets, supported cancellation, wider-operand refusal,
signed zero/subnormals, preserved fields, live callback rewiring, selective stop
dispatch, callback suppression through the AObj adapter, wrap/end ordering and
failure boundaries. This checkpoint enables no live animation, source-owned
Battle mode or charged clone. Capture06 below adds one observed request sample;
the initial implementation checkpoint alone had no captured FObj replay.

### Original FObj instruction audit

The same original DOL confirms positive-zero constant8043d298 and signed-int
conversion bias8043d2a0. Request802488fc uses `fsubs` for the signed-short
conversion;80248900 uses `fadds` with the unchanged request register f1, then
stores+1c at80248904. Its reset stores occur in the order listed above, with
next reloaded at80248948. Stop calls the interpreter at802489b0, reloads flags
at802489bc, stores the masked flags at802489c4 and reloads next at802489c8.
Interpret-all calls at8024a1d8 and reloads next at8024a1dc. Neither walker
protects the current node's lifetime across a callback; this bounded model
does not admit allocation/free or replacement of the current storage.

Function SHA-256 values:

- Request802488b8, size0xa4: `b5f850795387a7fabffdbbfd933a642b698c0c058cc5f24a373814ad790feeab`.
- Stop8024895c, size0x98: `ebb6701d9c9dfc34323fb798f9477ae8f949d06f315593cc458f4ed2322d8002`.
- Interpret-all8024a198, size0x70: `bcf7c4c9b6022403f2418af170535e1b0e4ac28f37b73cea489370398cb7344d`.

## Backing animation request capture06

A further isolated original-game run recorded 273 matched FObjReqAll pairs and 273
matched AObjReq pairs, with 117 verified controller readbacks and 3,196 debugger
stops. It ended at its existing time bound with no capture errors; one final
unmatched AObj entry was excluded. Observed lists contained 3–10 nodes, with 81
observed AObj pointers and 20 owner-attributed JObj pointers. Every observed
signed offset+18 was zero.
This capture is independent of the preceding action/recovery runs.

Independent local full-header reset assertions matched 3,630 node comparisons:
1,815 at the FObj boundary and the same1,815 at its enclosing AObj boundary.
These are repeated boundary observations, not 3,630 distinct nodes, and the
full-corpus assertions did not run through the new TypeScript implementation.

One complete fractional-request sample was selected by shortest fractional list,
then earliest pair: FObj pair54 nested in AObj pair53 at pad105. Request f1 had
double bits `3fe4444460000000` (0.6333333849906921). The eight-node list retained
its links; each cursor changed from null to its existing base identity. Each
flag changed 0→1, frame+1c changed `00000000`→`3f222223`, and bytes+11/+12,
halfwords+16/+18/+1a and floats+20/+24/+28/+2c stayed zero. AObj flags changed
`40000000`→`08000000`, frame+04 changed to `3f222223`, and rewind0/end60/rate1
and list identity were preserved. All other header bytes were unchanged in
the local capture checks. The derived sample replaces addresses with opaque
aliases and contains no animation stream payload.

The actual compiled TypeScript passed this sample through both a direct FObj
request and the AObj adapter. The lifecycle regression retains the adapter test.
This verifies modeled fields for one observed eight-node request path, not 16
independent nodes, the full corpus, unmodeled fields, StopAll, the per-node
decoder/interpolator, JObj callbacks or geometry. Nonzero offsets and request
precision cancellation remain synthetic/source-audited tests, not newly observed
original-game coverage. Live source-owned animation and clone activation remain
disabled.

Capture SHA-256:
`af316df7bf5b065a3d9cc1a55289300e40773e90f8cbbf749701c94c7452b185`.
Raw capture and full numeric summary remain local on the rig. The task-owned
emulator was stopped through its isolated ledger; process, listener and PID file
were absent afterward. No original assets, stream payloads or raw captures are
included in this checkpoint.

## Implemented prerequisite: bounded per-node data loader

`rom/fobj-data.ts` implements the data-loading stage 802489f4, with entry through
the factory-owned FObj runtime. Headers now include declared length+0c, track+13
and value/tangent formats+14/+15. The runtime owns copied, non-shared byte buffers
and interns cursor identities by stream and offset. Equal positions retain equal
identities across repeated requests and shared-stream nodes. Caller buffer edits
cannot silently change the admitted stream. This supplies actual decoder writes,
not a decoded-key sampler or a default per-node interpreter.

The source entry compares unsigned cursor-minus-base with declared length. At or
beyond the end it returns 6 before changing fields, even when a repeat count
remains. Otherwise it copies opcode+11 to previous-opcode+12, reads a new command
when count+16 is zero, and decrements that halfword. A command count begins with
the first byte's three high payload bits plus 1; continuation contributions are
added at shifts 3,10,17,..., not interpreted as an independent ordinary varint.
The admitted host domain is count 1–65535 with at most two continuation bytes.
Encodings requiring halfword truncation or larger PPC shifts are refused.

Opcodes 1/2 shift the prior value and preserve slopes following opcode 5. Opcode 3
shifts both value and slope before decoding; opcode 4 stores its decoded value
before shifting/decoding the tangent. Opcode 5 changes the slope and retains the
loading state. Opcode 6 preserves the source pending-value flag 40→80 ordering,
including replacing previous-opcode with current-opcode before decoding when 40
is set. Opcodes 1–4/6 change loading state 1→3 or 2→4 while preserving high flags.
Opcodes 0 and 7–15 return 0 after command/count processing without clearing the
stored state. Wait durations and interpolation are not processed by this loader.

Supported numeric inputs are little-endian float32 when the entire format byte
is zero, signed/unsigned16 and signed/unsigned8. Integer division uses the source
signed interpretation of `1 << fractionBits`, followed by single rounding.
Fraction 31 therefore divides by−2147483648 and can produce negative zero.
The original fallback for other numeric formats is positive zero without reading
bytes or dividing; this implementation deliberately refuses those formats.
Nonfinite float payloads are likewise outside the admitted domain. Valid finite
source-width values and signed zeros are preserved; NaN payload parity is not
claimed.

The host enforces every read against both declared length and copied storage,
with a 16 MiB allocation bound. Those are safety limits, not original stream-size
constants or original failure behavior. Retail has only the entry length guard
and may read past its declaration. Source float reads advance the cursor before
each byte load; 16-bit reads load both bytes before advancing. Host refusal does
not emulate a retail memory fault: the failing bounded read does not advance,
while completed earlier byte consumption and field writes remain. No error
rolls back an earlier opcode/count update or preparatory value/slope write.
The public runtime validates owned, writable, source-width headers and stream
provenance before the internal loader can mutate them.

Tests cover all opcode/state cases, previous-opcode 5, pending flags, little-endian
formats and signed boundaries, all 32 fraction counts, negative zero, packed
repeats/count limits, EOF with unfinished repeats, copied buffers, canonical
cursor identities, unsupported input and partial-write refusal. The earlier
capture06 request regression now also uses its observed lengths, track bytes and
format bytes for the newly modeled fields and verifies they are unchanged.
Concrete mutated implementations fail for unsigned signed16 decoding, positive
fraction31 divisor, lost opcode5 slopes, OR-combined command counts, skipped EOF
for repeats and fresh identities for the same cursor. These loader tests use synthetic
streams: capture06 contains headers, not the stream payloads needed to replay
the original loader. No per-node time progression, interpolation, callback
receiver, JObj geometry, mode0/mode2 production integration or live clone is
enabled.

### Original loader and next-interpreter audit

The original DOL hash remains the one recorded above. Loader 802489f4 occupies
0x10d0 bytes; SHA-256:
`03d2adb07e5a89ec9ac2da477ed745bfd4422ab421ec01c34f43268298dd24a2`.
Original anchors confirm unsigned entry comparison at 80248a0c–28; prior-opcode
write at 80248a2c–30; fresh opcode/cursor writes at 80248a48–60; continuation
processing at 80248a78–9c; and halfword store/decrement at 80248aa0–ac. Signed16
extends the high byte at 80248c74, unlike unsigned16 at 80248ca4–b0. Integer
conversion uses `fsubs`, scaling uses `fdivs` at 80248cf4. Original assertions
require loading state 1 or 2. Source: `chunk_0071.c:278–866`.

Read-only inspection also verified interpreter 80249ac4 (size 0x6d4), SHA-256:
`ab8ed02d2a35df72c8d07efb7ea76805a6f6edc9cb203d53768ba0c9640195af`.
This is evidence for the next slice, not an implemented or fully audited
interpolator. Null/state 0 exits before frame writes. Otherwise frame advancement
uses `fadds` at 80249b20–2c; an ordered frame < +0 comparison exits afterward with
the negative frame retained. States 1/2 load data, 3 processes a wait, 4 tests it,
and 5 transitions back to 4. Wait exhaustion chooses local state 6 without storing 6
in the header. Consuming a wait uses `fsubs` and remembers that wait in f31;
state 6 later adds f31 back, so substituting an unconditional zero is incorrect.
The wait varint has its own seven-bit OR decoding and halfword truncation.
Unsupported state ≥7 can loop in retail. Full interpolation/FMA arithmetic,
callback effects and a bounded complete state machine remain to be supplied.

## Implemented prerequisite: callback-disabled FObj timing

`rom/fobj-timing.ts` now provides an explicit callback-null interpreter factory.
It performs actual source frame, loader, wait and end-state writes through the
owned runtime. It does not evaluate interpolation or discard a requested
callback: non-null callbacks on non-null nodes/lists are rejected before the
timing operation. Null nodes/lists are genuine no-ops. Direct state 0 calls return
before reading delta; list effects retain their separate finite-delta contract.
Unsupported initial states 7–15 are refused before frame writes, a host preflight
policy rather than retail behavior.

For admitted states 1–6, frame advancement rounds once to float32 using the
original single-representable delta. Wider operands are refused before a frame
write, rather than converted implicitly. Negative frames remain stored and return without
loading or changing state. State 1/2 calls the actual loader; state 3 calls the
owned wait reader; state 4 consumes an expired wait with single-rounded subtraction
or stores state 5 when time remains. State 5 stores state 4 before testing the wait.
Each consumed wait replaces local lastWait. State 6 adds that value back with
single rounding, promotes pending flag 40 to 80 and copies the prior value as the
source does. A locally reached state 6 does not overwrite the stored state.
Repeated calls after EOF therefore still observe that preserved state.

The separate bounded wait reader asserts stored state 3, checks stream end before
reading, and ORs seven-bit groups starting at shift 0. It accepts up to five bytes
through shift 28, applies source uint32 arithmetic and truncates the stored wait
modulo 65536. A sixth byte is refused rather than approximating PPC large-shift
behavior. Successful reads set flag 20 and stored state 2; EOF returns local 6 with
no such stores. This is distinct from command-count decoding. Previous cursor
consumption remains on refusal, under the already documented host bounds policy.

Callback-only slope evaluation and flag 20/80 clearing are deliberately absent
from this null-callback path. End-state flag 40 promotion still occurs. The AObj
adapter can use this restricted runtime for an actually suppressed ordinary
callback. AObj NO_CALLBACK does not suppress wrap/end stop callbacks: a non-null
stop callback is refused, with prior AObj writes retained. The test suite covers
that distinction rather than treating callback suppression as general purity.

Synthetic regressions cover all admitted states, float32 cancellation and wider-operand refusal,
negative/subnormal/signed-zero frames, multi-wait and zero-wait paths, restoration
of the last consumed wait, repeated EOF, preserved slopes/flags, immutable stream
provenance, malformed waits, finite-clock overflow and transition budgets. Both
transition and node budgets are host safety limits, not original constants.
Five supported-domain mutations are rejected: lost last-wait restoration,
stored state6 on EOF, callback-only flag clearing, untruncated wait
storage and incorrectly suppressed AObj end-stop callbacks. An independent
1,000-case BigInt wait-decoder comparison also passed.
No new original-game timing replay is claimed: capture06 still validates only
the bounded request sample. Full interpolation/FMA behavior, non-null callbacks,
JObj geometry, mode0/mode2 production integration and live clone activation
remain outside the implemented boundary.

## Processor domain and bounded linear evaluation

The [IBM Gekko User Manual, version 1.2](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf),
section 2.2.3, printed page 2-28, states that single-precision arithmetic requires
single-precision operands. Double-to-single conversion must be explicit in
software. A register retaining a wider value is not evidence that single
arithmetic on that value is guaranteed. Accordingly, nonempty FObj requests and
active FObj timing now reject non-single-representable arguments. The AObj
request still forwards its original argument unchanged; a restricted FObj
callee refusal retains the preceding AObj frame/flag writes. Null/no-op cases
keep their documented early-return contracts.

These helpers model nearest-even rounding, FPSCR RN=00, and gradual underflow,
NI=0. Tables 2-21/2-22 distinguish NI=1's denormal arithmetic behavior; load/store
conversion rules must be considered separately. No runtime FPSCR capture existed
at this arithmetic checkpoint. A later capture report indicates NI=1; its raw
record and debugger-register mapping have not yet been reconciled into this
checkout. That provenance-pending observation does not validate this arithmetic
model. These NI=0 helpers remain an explicit domain, not mode-parity evidence.
Other rounding modes,
exception flags/traps, non-IEEE mode and NaN payload behavior remain outside the
model. This qualifies all synthetic subnormal tests; they are not console-mode
verification. Earlier arbitrary-double cancellation expectations at `fadds`
sites are retired source claims, not evidence supporting a wider processor domain.

`rom/source-float.ts` uses exact integer significands/exponents to round finite
float32 sums and fused products once. It preserves signed zero, gradual
underflow, ties-to-even and cancellation without first rounding through binary64.
Nonfinite inputs, wider operands and rounded overflow are explicitly refused.
It does not change the AObj wrap's audited double-add-then-single-convert sequence.

The original three linear paths load slope+28, frame+1c and start+20, then use
`fmadds`, storing a callback scalar. Instruction sites are 80249cb0 (state 6),
80249e40 (state 3) and 8024a0cc (state 4). A concrete supported-input witness is
slope=`1 + 2^-23`, frame=`1.5`, start=`-2^-126`: exact fused single evaluation
under the stated mode produces bits `3fc00001`, while JavaScript's
multiply/add double intermediate followed by float32 conversion gives `3fc00002`.
All three operands in this witness are normal float32 values. A second version
using subnormal start=`-2^-149` is tested under the explicit NI=0 assumption.

`rom/fobj-linear.ts` implements only this opcode 2 scalar stage on owned headers.
The caller must first establish the eligible phase and non-null callback; the
helper supplies no phase gating or callback dispatch. If dirty flag 20 is set,
it clears that flag first. Zero duration stores positive-zero slope then copies
end+24 to start+20. Otherwise it rounds end-minus-start separately, divides by
the exact uint16 duration with single rounding, and stores the slope. The final
scalar uses the exact fused operation. A clean dirty flag retains cached slope.
Overflow refusal retains completed source writes, including the flag clear and
any preceding slope store.

Binary64 division followed by float32 conversion is safe for this restricted
finite-float32 numerator / uint16 denominator 1–65535 domain: a non-tie quotient
is separated from a float32 midpoint by at least `U/(2*d)`, greater than the
binary64 rounding error; exact ties fit binary64. Division is not widened across
the preceding single subtraction. A separate regression distinguishes those
rounding orders. This argument is not a general claim about arbitrary division.

The audit confirms slope arithmetic `fsubs` then `fdivs`, with stores before the
final `fmadds`, at 80249c80–8c, 80249e10–1c and 8024a09c–a0a8. State 3 additionally
requires flag 80 before callback evaluation; the other phase gates differ.
The new helper deliberately does not infer those gates from stored state.
Spline calls target 80255050 and contain further fused operations; full spline
semantics remain unaudited/unimplemented here. The later scalar-callback slice
below supplies bounded dispatch without claiming the original receiver's effects.

Independent numeric validation uses libc `fmaf` with nearest mode and exact
fraction/neighbor comparisons. Synthetic tests cover fused rounding, separate
subtraction/division, dirty/cached/zero-duration paths, signed zeros, subnormals,
overflow prefixes, metadata preservation and ownership/opcode refusal. This
linear-only checkpoint did not supply callback delivery. No new original-game
replay, geometry or live animation is claimed.
The final narrowed arithmetic domain passed 14,961 independent cases; the bounded
division passed 4,206 independent fraction cases as well as the midpoint argument.
Four concrete mutations fail: double-intermediate evaluation instead of fused
single, widened subtraction across division, recomputed clean cached slope and
missing zero-duration endpoint copy.

## Implemented prerequisite: bounded scalar FObj callbacks

`rom/fobj-callback.ts` connects the actual loader, wait reader, timing loop and
linear evaluator to synchronous scalar handlers. `rom/fobj-timing-core.ts` shares
the state machine with the existing explicit callback-null factory, so the two
paths do not use separate timing implementations. This is an offline execution
slice, not the original JObj receiver, a complete interpolator or a live clone.

The factory requires an explicit owner identity and creates its own callback
identities. This binding supplies the owner argument absent from the existing
AObj effect interface without guessing a memory address. A handler receives
that owner, the current unsigned track byte at +13 and a scalar value. The value
is a copy of the source stack scalar; mutable stack pointers and RAM aliasing are
outside this API. A handler may synchronously mutate owned headers, links and
AObj records through its closure. The source call sites are 80249d28 (local
state 6), 80249eb8 (state 3) and 8024a134 (state 4), with owner in r3, track in r4
and scalar pointer in r5. Source: `chunk_0071.c:869–1207` and the previously
hashed original interpreter.

The phase gates and continuations remain distinct:

- State 3 needs flag 80 and a non-null callback before evaluation. After the
  handler, the wait reader checks the live stored state is still 3 and reloads
  the live cursor, base and length. A callback can therefore change the next
  wait input or cause an explicit state refusal. It is not replaced by a cached
  event queue.
- State 4 evaluates only when the current wait exceeds the frame and a callback
  is present. After the handler, it reloads flags and stores low nibble 5 while
  retaining callback-written high bits. If the wait has expired, subtraction
  and the transition to state 3 occur first instead.
- Local state 6 restores the last consumed wait, promotes pending flag 40 to 80,
  copies the pending opcode and end value, then evaluates. After the handler it
  returns without another state store. The consumed wait is a local value;
  changing the header's duration in a callback does not replace that saved wait.

Eligible opcode 1 chooses start when frame < duration and end otherwise.
Opcode 2 uses the already audited separate slope subtraction/division and fused
linear evaluation. Neither clears flag 80. Opcode 6 requires flag 80, copies
start and clears that flag before calling the handler. State 3 can be followed
by a second callback at local state 6 when the wait reader reaches EOF; key
handlers that rearm flag 80 can also receive that second call. No deduplication
is introduced. Eligible opcodes 0, 3–5 and unknown values are refused rather than
inventing a scalar or assuming spline behavior. A null callback does not enter
evaluation and therefore does not trigger these opcode refusals.

The list operations still use live links. StopAll selects interpretation using
the entry prior-opcode byte 6, then clears the live low flags and follows the
live next pointer after the handler. The AObj adapter retains ordinary callback
suppression independently of wrap/end StopAll callbacks; no broader suppression
or production integration is inferred.

Callback ownership is checked before non-null node/list entry writes, including
StopAll lists that would skip every interpreter. Null identities remain no-ops.
Execution and loader reentry on the same runtime, non-undefined handler returns,
deferred handlers and invalid post-handler headers are outside the supported
domain. Refusals retain all earlier frame, slope, flag and handler effects;
there is no rollback or fallback. These checks and budgets are host policy,
not a claim to reproduce original faults. Finite-float32 RN=00/NI=0 assumptions
from the arithmetic section still apply. This callback implementation checkpoint
had no original replay or observed FPSCR; the later, provenance-pending capture
report does not validate its NI=0 arithmetic against the reported NI=1 mode.

An independent comparison against the previous committed callback-null runtime
passed 20,000 operation steps across 5,000 seeded synthetic scenarios (seed
`0xcab2026`). It compares failure versus success and every modeled header field
after direct interpretation, list interpretation, requests and stops, including
malformed streams, invalid operands and budget failures. This is refactor
regression evidence, not original-game replay or additional matching coverage.

Synthetic callback tests exercise all three phase gates, real packed constant,
linear and key streams through the loader, pending-key promotion, repeated EOF,
zero-duration and fused linear values, live stream/link/flag/frame changes,
StopAll selection and clearing, AObj wrap/end suppression and live accounting,
ownership refusals, failures with completed prefixes, execution/loader reentry,
and host budgets. Six concrete mutated implementations fail: removing the
state-3 flag-80 gate, restoring stale state-4 flags, adding a state-6 store after
the callback, omitting the key flag clear, skipping the state-6 callback and
passing the wrong track. These tests validate the declared synthetic contract;
they do not establish original callback receiver behavior or visual animation.

An independent source-shaped phase/EOF reference matched 15,360 scenarios across
all 16 high-flag combinations, states 3/4/5/6, opcodes 1/2/6, eight synchronous
mutation modes, five frame/duration boundaries and deltas 0/1. It compares every
modeled header field, ordered scalar callbacks and success/failure, including
rearmed flag 80, pending flag 40, opcode/track changes, negative frames, changed
durations and invalid stored-state changes. Its empty streams and small finite
operands limit it to synthetic phase/order evidence; it is not a full decoder,
arithmetic or original-game oracle.

## Audited prerequisite: bounded JObj transform receiver

Read-only verification of the same original DOL confirms the scalar receiver
`JObjUpdateFunc` at 8024e120 and dirty-subtree routine at 80251b80. Their SHA-256
values are respectively:

- Receiver, 2,372 bytes:
  `7e6b63c0dc8c3ee1aadf59b65fdd8ae8e6c4229f37dac138ffdd19499c919355`.
- Dirty subtree, 820 bytes:
  `6df54c9f84610de47a84efb0d914fd26275792f57020a354468f5384d53ae612`.

Sources are `chunk_0071.c:4367–4864`, the dirty predicates at `:3383–3430`,
and subtree propagation at `:7391–7581`. The original jump table at 803accb8
confirms these track mappings:

- Tracks 1/2/3 write rotation X/Y/Z at +1c/+20/+24, at original stores
  8024e3d0/8024e464/8024e4f8.
- Tracks 5/6/7 write translation X/Y/Z at +38/+3c/+40, at stores
  8024e570/8024e5e8/8024e660.
- Tracks 8/9/10 write scale X/Y/Z at +2c/+30/+34, at stores
  8024e6d8/8024e750/8024e7c8.

For these nine tracks the receiver only reads the input scalar, so a by-value
handler can model the accepted stores. A null owner returns before inspecting
track or value. Rotation requires owner flag 00020000 clear; the original
otherwise asserts. Track 1 with owner flag 00200000 first searches RObj type
40000000 and may write its +0c before the rotation assertion/store. That path is
outside the bounded receiver. These exclusions apply to the updated owner and
relevant track, not to every descendant visited for dirty propagation.

Each accepted transform store happens before the dirty decision, even for an
unchanged value. Root flag 02000000 suppresses the dirty call. Otherwise the
call is skipped only when the root is logically dirty: flag 00800000 is clear
and flag 40 is set. The called routine always ORs 40 into its entered node,
then stops descent if that node has flag 1000. It traverses children through
+10 and siblings through +08 in depth-first order, skipping an entire child's
subtree when that child has flag 01000000 or is already logically dirty.

The distinction between root and child gates matters. Root 01000000 does not
prevent update or descent; descendant 02000000 does not suppress dirtying.
Flags 00800040 together do not count as logically dirty and must still traverse.
A skipped child still leads to its next sibling. The updated root's own sibling
is never traversed. The original inlines six levels and then recurses; this is
not a source depth limit. No parent walk, dependency evaluation, matrix rebuild,
allocation or arbitrary callback is part of this accepted dirty routine.

Original instruction anchors include the root OR/store at 80251b94–9c, root
1000 gate at 80251ba0–a8, child 01000000 gate at 80251bb4–bc, logical-dirty
gate at 80251bd8–bf8, child OR/store at 80251bfc–c04, final recursive gate/call
at 80251e24–44 and sibling reloads at 80251e48–90.

Track 4 remains excluded: it mutates/clamps the caller's scalar, follows
JObj+7c → AObj+18 → spline+18, calls `splArcLengthPoint`, and then updates three
translation components. It is not an ordinary axis. Quaternion rotations,
RObj-backed track 1 and toggle/event/custom/matrix tracks require additional
implementations. Refusing unknown track IDs is a bounded host policy; some
unknown IDs are no-ops in the original rather than errors.

The admitted receiver's scalar copy is independent of NI/RN arithmetic modes.
Gekko manual section 2.3.4.3.10–12 (printed pages 2-53–2-56), Table 2-41, and
the `lfs`/`stfs` entries (12-98/12-215) specify the conversion/copy of finite
binary32 values, including signed zero and subnormals. PSE=0 widens on load and
explicitly stores single-denormal data; PSE=1 loads both lanes and stores the
high lane. The audited accepted receiver path contains only `lfs`/`stfs` for
this scalar, with no arithmetic. This establishes only the copy's domain; it
does not establish NI=1 FObj arithmetic or justify flushing every binary32
subnormal input merely because the FPSCR bit is set.

The receiver is implemented offline in `packages/combat/src/rom/jobj-update.ts`.
Factory-owned sealed headers retain all nine explicit finite-f32 scalar values;
joint symbols identify only records in the same runtime. These host records are
not aliased console RAM. Validation of encountered headers, lazy link resolution,
cycle/revisit refusal and the inspected-node budget are explicit host policy.
The budget counts the root and skipped children, not only nodes dirtied. A
failure retains the selected scalar store and all preceding subtree flag writes;
there is no full-graph preflight or rollback.

Synthetic lifecycle fixtures cover all 32 relevant root-flag combinations and
all 32 descendant combinations, every admitted axis, signed zero/subnormal/max
finite stores, invalid inputs, unvisited corrupt links, skipped/pruned sibling
continuation, foreign/frozen and individually non-writable records, shared-node
and cycle refusal, every budget cut in a mixed tree and a 12,001-node chain.
Packed constant, linear and key FObj
streams feed actual receiver writes through the existing AObj/FObj helpers;
NO_CALLBACK/end-StopAll and failures preserve their respective ordered prefixes.
These composed tests retain the arithmetic helpers' independent RN=00/NI=0 domain.

A separate recursive source-contract reference matches 5,000 seeded synthetic
acyclic tree/flag/track cases (seed `0x7319c8a2`). Eleven changed receiver variants
are rejected by the selftests: wrong axis, lost logical-dirty override, ignored
root suppression, swapped root/child gates, root-sibling traversal, lost sibling
continuation, reversed scalar/dirty write order, ignored root/child pruning and
incomplete per-field writability validation.
This is source-contract and regression evidence, not original execution or a
new matching-decompilation result. No JObj matrix rebuild, spline/RObj/custom
receiver, original callback replay, live source animation ownership or charged
clone activation is supplied by this checkpoint.

## Implemented prerequisite: one-joint animation dependency and dispatch

`rom/jobj-animation.ts` now implements the bounded control flow of
`HSD_JObjCheckDepend` at 8024d030 and the one-joint `HSD_JObjAnim` at 8024ea64,
from `chunk_0071.c:3321–3380,4865–4931`. This extends the owned scalar receiver;
its flags are the same record the actual FObj callback updates, not a copied
animation-side dirty flag. Parent/AObj/RObj/DObj identities and the resolved
class-info+50 callback selector are explicit, separately owned mutable bindings.
The selector is not JObj+50 and does not reconstruct a class object or vtable.

Dependency checking changes only the current joint's flag 40. An already
logically dirty joint is unchanged. With owner flag 00800000 clear, the source
short-circuit order is parent raw flag 40, then either bit in owner mask 00600000,
then a non-null RObj. With owner flag 00800000 set, the owner must not have
01000000, and its parent must be logically dirty. Raw parent flag 40 and logical
parent dirtiness differ when that parent also has 00800000. Neither 02000000
nor 1000 suppresses this dependency write. It does not walk a parent chain or
dirty the child subtree; a self-parent is just one lookup.

The single-joint dispatch then selects the current class-info callback and AObj,
calls AObj interpretation with that same joint owner, reloads RObj80 and calls
RObj animation, then reloads the joint flags. DObj animation runs only when
neither bit of mask 4020 is set, using the DObj18 read at that point. AObj/RObj
effects may change later bindings and flags. The dependency check is not rerun
after them. AObj and RObj calls still occur for null targets; DObj also receives
null when its flag gate admits the call. The callees' own null behavior is in
`chunk_0070.c:2596–2601`, `chunk_0072.c:532–541`, and
`chunk_0069.c:6323–6341` respectively.

All three effect implementations are mandatory own data-function properties of
a non-proxy table, copied once before dependency writes. Accessor/inherited
methods are refused without invoking their getters; changing a table's methods
during a call does not replace the static source callees. Effects must complete
synchronously. Unsupported RObj/DObj/custom-class work must throw, not be silently
treated as complete.
Owned-record/writability/finite-scalar validation and same-runtime reentry refusal
are host restrictions. Binding values are checked when read, so an invalid
unvisited parent or gated DObj identity is not resolved. Invalid post-effect
state stops the scenario, preserving the dependency write and completed effect
prefix; nothing rolls back. That one-joint checkpoint did not implement global
end-callback handling or JObjAnimAll traversal; the following slice adds them.

Synthetic tests exhaust 3,072 owner/parent/RObj flag cases, verify every effect's
failure prefix and post-effect checks, test mutable bindings and late DObj gates,
and run actual packed linear FObj data through AObj and the scalar receiver for
request, advance, overshoot and stop. RObj/DObj are explicitly null in that
composed case; non-null unsupported work is rejected. Fourteen changed dispatch
variants fail the tests, including raw/logical parent confusion, missing mode
or independence gates, stale RObj/flag reads, wrong owner, skipped null AObj,
repeated dependency checking, unchecked effect returns and rereading callee
methods. The original capture provenance and NI=1 arithmetic remain unresolved;
this checkpoint is source and
synthetic evidence, not an original-game replay or live animation activation.

## Implemented prerequisite: JObj tree traversal and AObj end callbacks

The same owned animation runtime now supplies bounded `animateTree`, corresponding
to `JObjAnimAll` at 8024ebc8 and the wrapper `HSD_JObjAnimAll` at 8024ef10
(`chunk_0071.c:4936–5120`). The four differently inlined source levels execute the
same dependency/AObj/RObj/conditional-DObj sequence before their children, then
the fourth level recursively continues. They are not a source depth limit.

Traversal is preorder. Only flag 1000, read after the current joint's entire
animation sequence, prunes its children. Dirty, independence and render-gating
flags do not skip descendant animation. The child link is selected after that
prune decision. Once its loop begins, changes to the ancestor's flags or child
link do not cancel or restart it. A child's sibling is read after its whole
subtree returns, including changes made by descendants. The updated root's own
sibling is never read. Parent dependency links remain independently supplied;
the traversal does not infer or rewrite them.

An iterative stack retains entered ancestor records, not cached sibling links.
All three source-callee effect methods are captured once for the entire tree,
while each joint still reads its live animation bindings. A separate animation
node budget and cycle/revisit refusal are host bounds, not retail semantics.
Invalid or unowned identities are resolved only when followed. Failures retain
completed joint writes/effects and suppress the final end-callback invocation.
There is no whole-graph preflight or rollback. A null root performs no work,
including no effect-table validation or counter reset. For non-null roots,
host effect-table validation precedes reset, while root resolution follows it.

`rom/aobj-end-callbacks.ts` implements `HSD_AObjInitEndCallBack` at 80243b24 and
`HSD_AObjInvokeCallBacks` at 80243b34 (`chunk_0070.c:2540–2568`). Its actual
`SourceAObjCounters` record is shared with the AObj interpreter: stopped at
80436930 and running at 8043692c. The wrapper resets stopped then running once,
without clearing callback head 80436928. After successful tree execution,
invocation tests stopped nonzero, snapshots the head, then tests running zero.
It traverses that selected list without rechecking the counters or head.
Each owned callback receives no arguments, then its current node's next link
is loaded. Callback changes to next or a later callback selector take effect;
changes to global head do not redirect the in-progress walk. The list is not
consumed and invocation does not reset the counters.

The callback model uses separate sealed records and explicit symbolic links,
not aliased RAM or a reconstruction of registration/removal allocation. Host
writability/type checks occur per accessed field. Reset overwrites old counter
values in source order; failure on the second field retains the first store.
Already-consumed fields and excluded lists are not revalidated. Callback return,
reentry, cycle and visit-budget refusals retain completed prefixes. As elsewhere,
callbacks must be synchronous; rejecting a Promise cannot undo deferred JS work
that a caller violated this contract by scheduling.

Synthetic traversal tests cover post-AObj/RObj/DObj pruning, mutable child and
sibling links, changed ancestor state, root-sibling exclusion, every budget cut,
foreign/frozen nodes, cycles/revisits, failure prefixes and a 12,001-node chain.
Actual packed linear FObj streams update two independent JObj owners through
the real AObj interpreter and shared counters. Only the pass where the final
remaining AObj completes invokes the end callback; a later pass with both
AObjs already stopped contributes zero counts and invokes nothing. This fixture
preserves source overshoot: frame 6 evaluates slope 2 from value 10 to 22 rather
than clamping to the key's value 18.

Twelve changed tree variants and ten changed end-callback variants are rejected
by focused selftests; the fourteen existing one-joint dispatch mutation controls
also still fail after the private-runner refactor. These are source-contract and
synthetic regression results, not original replay, new matched instructions,
matrix/skin evaluation or live animation activation. RObj/DObj internals and
custom-class receivers still require real implementations or explicit refusal.
Original-capture provenance and NI=1 FObj arithmetic remain unresolved.

## Implemented prerequisite: DObj animation list dispatch

`rom/dobj-animation.ts` adds the bounded orchestration of `HSD_DObjAnimAll` at
8023d968 (`chunk_0069.c:6308–6341`). For each display object, it selects the
callback from class-info+44 and the AObj at object+10, then interprets that AObj
with the current display object as owner. After that call it reads the current
PObj list at +0c, animates that list, reads the current MObj at +08, animates the
material, and finally reads next+04. Every later binding is therefore affected
by earlier animation effects. The current callback/AObj pair is already consumed;
changes to those fields do not replace an in-flight call. Later objects select
their own current callback/AObj pair when reached.

There is no DObj flag gate or dependency check in this loop. All three calls
are made even when their target is null. Their own null behavior is visible in
`chunk_0070.c:2596–2601` (AObj), `chunk_0071.c:1526–1538` (PObj) and
`chunk_0070.c:1411–1420` (MObj). A null root bypasses the whole helper, including
host effect-table validation. No counter reset or completion invocation belongs
inside DObjAnimAll; enclosing JObj tree effects must pass its actual shared AObj
counters through the DObj AObj interpreter too.

This uses sealed, separately owned bindings with explicit symbolic identities.
`classUpdate44` is a resolved class-info selector, not a DObj+44 field or a
reconstruction of class memory. The helper supplies no DObj update receiver,
PObj/MObj internals, geometry changes or live display integration. Those remain
mandatory synchronous effects or explicit refusal. The required effect functions
are copied once per list from own data properties; their original table remains
the call receiver. Replacing methods mid-list cannot replace source callees.
Non-proxy records/tables are a caller precondition; accessors and inherited
methods are rejected without invoking getters.

Host data-field/writability checks occur only at each actual read. Previously
consumed fields and unvisited nodes are not revalidated. Invalid live links,
non-owned identities, cycles/revisits and a separate node budget stop the pass
after completed effects. Same-runtime reentry is refused even if an effect catches
the inner error; guards release after failure. Non-undefined/Promise returns are
refused, but already scheduled JS work cannot be rolled back. These admission
limits are not additional retail control-flow conditions.

Synthetic tests exercise live PObj/MObj/next and later callback replacement,
source-order effect prefixes, null calls, frozen and invalid fields at every
boundary, consumed-field changes, static method snapshots, exact owners, reentry,
budget cuts and a 12,001-object list. Fifteen mutated implementations are rejected.
An actual JObj tree drives its own AObj and two DObj AObjs through the real AObj
and empty-list FObj helpers using one shared counter record. The five pass counts
are (running,stopped)=(3,0),(2,1),(1,1),(0,1),(0,0); completion is invoked only
after the final display AObj stops. A material refusal retains all preceding real
AObj counts and suppresses the enclosing tree's final callback. Empty FObj lists
isolate dispatch and accounting; this is not evidence for a DObj scalar receiver.

Independent review confirmed the decompiled source order and bounded contract.
The local map/census reports 0x6c bytes, 27 instructions and three calls, but no
executable/disassembly was available for a separate instruction-level reload
audit. This adds source-contract and synthetic evidence, not original-game replay
or new matching coverage. RObj animation, DObj/custom receivers, PObj/MObj internals,
matrices/skin, source-data ownership and live clone activation remain unfinished.
Original-capture provenance and NI=1 FObj arithmetic are still unresolved.

## Implemented prerequisite: polygon and material animation dispatch

`rom/pobj-animation.ts` implements the bounded control flow of `HSD_PObjAnimAll`
at 8024a6ac (`chunk_0071.c:1517–1540`). Each polygon object interprets its AObj
at +18 with itself as owner and the resolved callback from class-info+48, then
reads its current next link at +04. The source C expression passes both AObj and
callback as arguments to the same call; their relative load order is not proven
by that expression. The host reads the callback first, then AObj, without any
effect between them. This choice is not an instruction-level ordering claim.
Later-node bindings and next links are read only when reached, so effects can
replace future callbacks or append an allocated tail. No geometry/shape receiver,
allocation semantics or source RAM aliasing is inferred from these owned bindings.

`rom/mobj-animation.ts` implements the bounded `HSD_MObjAnim` at 802428a4
(`chunk_0070.c:1396–1424`). Unlike the PObj expression, this source explicitly
assigns its class-info+4c callback before calling AObj interpretation with +14
and the current material owner. It then reads the current TObj list at +08 and
animates that list. This is one material invocation, not a material-list walk.
Its callback/AObj pair remains fixed during the call, while AObj effects can
change the later TObj target. No material scalar receiver or texture animation
internals are supplied by the dispatcher.

Both wrappers forward null AObj/callback targets, and MObj forwards a null TObj
target. A null root bypasses the whole wrapper, including host validation.
Neither wrapper resets the global AObj counters or invokes completion callbacks.
Their effect adapters must use the enclosing JObj tree's actual shared counter
record, and must perform real synchronous work or explicitly refuse unsupported
operations. Required own data-function effects are captured once per PObj list
or MObj invocation, with the original table as `this`; the next invocation may
take a new snapshot. Unknown custom/shape/material/texture work is not a no-op.

As in DObj dispatch, these are sealed symbolic records and resolved class
selectors, not class-info memory or pointer fields at object+48/+4c. Non-proxy
own-data inputs are a caller precondition. Host field-type/writability checks are
per access, not whole-object or whole-list preflight. Consumed fields can change
without being reread, and future fields can be repaired before use. Ownership,
PObj cycle/revisit and visit-budget checks, synchronous-return checks and poisoned
caught-reentry refusal retain completed effects. These are explicit host-domain
bounds, not additional retail branches. Pending JS work cannot be undone if a
caller violates the no-deferred-mutation contract.

Selftests cover exact owners/callbacks, null calls, live links and texture targets,
new tails, skipped frozen nodes, per-field failure prefixes, consumed-field
changes, effect snapshots/receivers, reentry and guard recovery. A 12,001-node
PObj list passes. Twelve changed PObj implementations and eleven changed MObj
implementations are rejected by these tests.

`rom/display-animation.selftest.ts` composes the real JObj, DObj, PObj and MObj
wrappers with five real AObjs sharing `j.endCallbacks.counts`: one joint, one
display object, two polygon objects and one material. Their end frames are
1,2,3,4,5. Across seven passes, the (running,stopped) counts are
(5,0),(4,1),(3,1),(2,1),(1,1),(0,1),(0,0). Completion runs only after the final
material stops and its null texture call returns. The joint also uses actual
packed linear FObj data and the existing scalar receiver, reaching translation
12 at frame 1. The other four AObjs intentionally have empty FObj lists; these
prove dispatch/accounting, not unimplemented polygon/material receivers.
Each JObj display gate excludes the entire nested path and its counts. A required
refusal for a non-null TObj preserves five already completed AObj counts but
suppresses the enclosing tree's completion callback.

Independent read-only source/code review and focused strict TypeScript checks
approved the bounded slice. No instruction match, original-game replay, texture
receiver, matrix/skin result or live clone activation is claimed. RObj animation,
display/polygon/material/custom receivers, TObj internals, source-data ownership,
NI=1 arithmetic and original-capture provenance remain unresolved.

## Implemented prerequisite: bounded texture transforms and list animation

`rom/tobj-update.ts` implements seven scalar cases of `TObjUpdateFunc` at
8023e0c4 (`chunk_0069.c:6753–6950`). Tracks 2/3 copy to translation+34/+38,
4/5 to scale+28/+2c, and 6/7/8 to rotation+18/+1c/+20. Every admitted case stores
the incoming scalar first, then reads flags+4c and ORs 80000000, preserving the
other bits. Already-dirty textures still receive the scalar. Null owner is a
no-op before any other argument inspection. Image selection, palette, clamped
color/material cases and all other tracks are explicitly unsupported, including
source no-ops outside this helper's admitted domain.

The receiver owns sealed symbolic records and copies finite source-f32 values,
including signed zero, subnormals and finite extremes, without FP arithmetic.
Factory inputs are copied from required own data properties; non-proxy records
are a caller precondition. Per-update validation checks the new scalar, then
the selected writable data field, stores without inspecting its overwritten old
value, and only afterward checks the writable uint32 flag field. Thus a flag
refusal retains the scalar store. Unrelated fields are not preflighted. These
host-domain restrictions do not add retail branches, implement RAM aliasing or
establish NI=1 arithmetic parity for the composed AObj/FObj helpers.

`rom/tobj-animation.ts` adds `HSD_TObjAnimAll` at 8023e690
(`chunk_0069.c:6953–6976`) over the same texture identities, with separately owned
next+08, AObj+64 and resolved class-info+48 callback bindings. These offsets differ
from the earlier PObj list. Each node interprets the selected AObj with that
texture as owner, then follows its current next link. The C call expression does
not establish relative AObj/callback load order; callback-first host sampling is
not claimed as instruction-level parity. Both null AObj and callback are forwarded;
a null list bypasses host validation.

The list owns no global reset or completion step. Its mandatory synchronous
interpreter uses the enclosing JObj tree's actual AObj counters and is captured
once per list with its original effect-table receiver. Only accessed binding
fields are checked. Scalar headers are not preflighted by list dispatch: a frozen
or invalid scalar record can remain unused, while actual callbacks may invoke
the admitted scalar receiver during interpretation. Live next links, future
callback changes and allocated tails are followed without graph preflight. Host
ownership, visit-budget, cycle/revisit, return-value and caught-reentry refusals
retain earlier effects. No deferred JS work may be scheduled; rejected Promises
cannot be used to promise rollback of work already scheduled.

The receiver tests cover all seven mappings, every individual existing flag bit,
finite scalar edge values, all refusal boundaries, unread unrelated fields and
scalar-before-flags failure prefixes. The list tests cover mutable bindings,
consumed fields, skipped frozen nodes, scalar-callback admission, null calls,
effect snapshots, recovery and a 12,001-node list. Fifteen scalar mutations and
twelve list mutations are rejected.

`rom/texture-animation.selftest.ts` composes a JObj, DObj, two PObjs, MObj and two
TObjs. Seven real AObjs share one `j.endCallbacks.counts` record, with end frames
1 through 7. The nine passes produce (running,stopped)=(7,0),(6,1),(5,1),(4,1),
(3,1),(2,1),(1,1),(0,1),(0,0), with completion only after the last texture stops.
Actual packed linear FObj data drives the joint and both texture receivers:
joint translation=12 at frame 1, first texture translation=22 at frame 6, and
second texture rotation=24 at frame 7. The texture dirty flag is set while all
other bits remain intact. These preserve source extrapolation rather than
clamping to the stored key. Other display/polygon/material AObjs intentionally
use empty FObj lists and do not claim their receivers are implemented.

JObj display gates exclude the whole nested path and its counts. An unsupported
image-track callback on the last texture retains six completed AObj counts and
the earlier texture write, while refusing the last update and global completion.
A separate readonly-flags case stores the last scalar before refusing its flag
write: that store remains, the failing AObj contributes no final count, and the
global completion callback stays suppressed.

Independent source/code review and strict focused checks approved this bounded
slice. No original-game replay, matched instructions, image/palette/color receiver,
texture upload, texture-matrix rebuild or live clone activation is claimed. RObj
animation, unsupported display/polygon/material/texture/custom receivers, matrix
and skin evaluation, actual source-data ownership, NI=1 arithmetic and original
capture provenance remain unfinished.

## Implemented prerequisite: existing-joint actor-part feedback

`rom/joint-animation-feedback.ts` adds the setup-bit-clear branch of 8004adc8
(`chunk_0006.c:664–671`) and the unmirrored pose/frame extraction in 8004b76c
(`chunk_0006.c:1076–1139`). It accepts pre-resolved, owned joint/AObj/part/pose
identities. This is not the full 80049e58 dispatcher, mode0 or mode2, archive
setup, joint-range mapping, root-motion path, stream wait or live actor wiring.
The part record is separate from the current synthetic `RomActor` parameter
storage; no existing frame counter is silently reinterpreted as the source part.

`advanceExistingJoint` refuses setup bit1. With operation bit2 clear it returns
without consuming the other arguments. Otherwise it reads the selected joint's
AObj, and a null AObj skips the timestep, part and effects. For a non-null AObj,
it stores the actor's finite f32 timestep as its rate, calls exactly one
`HSD_JObjAnim` through the existing real joint runtime, reloads the joint's
current AObj and copies flags bit26 to part+2d. A replacement AObj therefore
supplies the segment feedback, while the old AObj received the rate store.
A stopped AObj still receives the rate and can retain its WRAPPED flag. This
path does not call `animateTree`, reset shared counters or invoke global end
callbacks. Required RObj/DObj effects must perform their work or refuse.

`setSourceAObjRate` in `rom/aobj-clock.ts` models the narrow store in 80243fc0
(`chunk_0070.c:2814–2827`): null target is a no-op; an owned target needs only a
writable rate data field. The old rate and unrelated fields are not inspected.
It admits already-finite source-f32 input, including exact signed zero,
subnormals and finite extremes, and is allowed during a synchronous busy AObj
callback. Wider doubles are refused rather than rounded with `Math.fround`.
The available C cast and four-instruction census do not establish a general
nearest-even double-to-single conversion for the original store. This narrowed
domain covers the actual actor+1dc8 load without making that unverified claim.
A real packed opcode6 test changes rate in both normal and end-stop callbacks,
proving that the same AObj interpretation reloads the new rate for `stopAll`.
Ten changed rate-setter implementations are rejected by these tests.

`capturePoseAndFrame` requires an unmirrored part. It copies JObj translation,
sampling y before storing x, then y, then z, and snapshots rotation+1c/+20/+24.
It calls a mandatory synchronous Euler-to-quaternion effect before reading the
current AObj. The adapter must write the actual conversion into the supplied
quaternion or explicitly refuse, returning undefined; the original converter's
ignored status return is not the adapter return protocol. There is no host-trig
or identity fallback. The source converter 8025acfc (`chunk_0072.c:3457–3505`)
still needs its constant, sin/cos behavior and arithmetic/order evidence before
a general implementation can be claimed. Source rotation+28 is an unused copy
for this converter and is outside the admitted record.

If the current AObj is non-null after conversion, its actual frame is copied to
part+0c. Only mode0 compares that frame with signed16 duration+24 and writes
complete+2e=1 when duration<=frame. It never clears that latch. Thus successive
joints overwrite the last frame and segment, while any earlier completion stays
set. Completion does not mean all AObjs stopped, does not use the global counters
or substitute AObj.end, and does not clamp an overshooting frame. With no AObj,
pose extraction still runs but frame/completion remain unchanged. Mode2's full
crossing path is not implemented: source switches to mode0 only after the mapped
animation update, so this helper does not invent an early mode change.

Factories copy non-proxy own-data records into separate sealed storage and
freeze method tables. Effects retain their original table receiver. Per-access
finite/type/writability checks, mirror preflight and poisoned same-runtime
reentry refusal are explicit host bounds. Consumed fields are not revalidated;
overwritten old scalar/byte values and unrelated AObj flags/rate are ignored.
Refusals retain completed rate/AObj/receiver effects, segment, translation and
partial quaternion stores. Pose failure precedes frame/completion; a frame-store
failure follows complete pose conversion. No deferred mutation is permitted and
already scheduled work cannot be rolled back.

The integration selftest uses the actual AObj, packed linear FObj and JObj scalar
receiver, plus an explicit analytic positive-zero-Euler test backend which
produces (x,y,z,w)=(0,0,0,1) and refuses every nonzero angle. This is a synthetic
fixture, not an installed source backend or general quaternion/original parity.
It verifies request suppression; actual frames 0/2/4 with translations 10/14/18;
end39/frame38/rate2 overshoot to40; end30/frame28.5/rate1.5 wrap to0 with segment1;
signed duration boundaries; sticky completion across two joints; live AObj
replacement; stopped/null cases; exact single-joint accounting; and ordered
readonly/invalid/effect/reentry failure prefixes. Twenty-four changed feedback
implementations are rejected. These are source-contract tests, not a replay of
the previously reported capture, whose local provenance remains unresolved.

Independent review approved the bounded feedback logic and identified the wider
rate-conversion assumption, which was removed. General quaternion conversion,
mirrored poses, descriptor loading/setup, joint mapping and root-motion remain
required before the actor's real animation modes can be activated. Existing
RObj/custom/unsupported receivers, matrices/skin, source-data ownership, NI=1
arithmetic and original-game capture/replay gaps also remain. No playable clone
activation or new instruction matching is claimed by this checkpoint.

## Implemented prerequisite: actor joint-range mapping

`rom/actor-joint-mapping.ts` connects the existing real joint/part feedback to
bounded actor selection from 8004a830, 8004aae0, 8004acdc and 8004b8f4
(`chunk_0006.c:387–611,1140–1157`). Callers provide owned actor headers, two banks
of four inline part identities, two pose banks, live descriptor maps and live
JObj pointer tables. Part descriptor+00 is an opaque null/non-null identity in
this continuation domain, not reconstructed archive data. Part bindings add
scaleIndex+32, jointBank+33 and poseBuffer+35 to the actual feedback part identity.
No separate synthetic frame/completion record is substituted.

`animatePart` first selects the stable part slot and stores the supplied output
buffer byte to part+35. It snapshots the signed-byte interval once: part0 uses
[0,boundary1), part1 [boundary1,boundary2), part2 [boundary2,boundary3), and part3
[boundary3,jointCount). Empty and reversed intervals perform no joint work. The
range end is not reread if animation effects later change the actor's boundaries.

For each ordinal, the current actor descriptor+4b0 and its map+8c entry are read.
The signed mapped value selects both source JObj and destination pose for the
admitted unmirrored path; it is not the ordinal. Repeated entries repeat the
actual animation, and a latched part completion does not terminate the sweep.
The current part descriptor+00 is then read. Null writes complete+2e=1 and skips
mirror, root, count, JObj, pose and scaling checks, even with setup flags or a
root/negative mapped value. The earlier descriptor/map access still must succeed.

For a non-null part descriptor, mirrored mapping and mapped root index0 are
explicitly refused before the joint-count gate. This preserves the reached
boundary instead of pretending a count0 root call has no root-motion effects.
Other indices are compared against the current signed jointCount+1d90 for each
entry. A skipped entry does not read its downstream bank, timestep or pose data.
A negative value that passes that signed comparison is refused when negative
addressing would be required; it is not reinterpreted as an unsigned joint ID.

An admitted index selects the current signed part+33 bank and its current JObj
entry. That JObj is held across the real feedback advancement and pose capture,
even if callbacks change the bank or its entry. Setup bit1 remains a refusal in
the actual feedback helper, after the mapping gates, rather than an unconditional
whole-sweep rejection. To preserve the actor timestep's lazy load, a noninterfering
binding/ownership inspection checks operation bits and AObj nullness before
consuming actor+1dc8. Those duplicate inspections have no intervening effect or
getter and do not change the chosen JObj. Bit2-clear or null-AObj paths leave an
invalid/readonly timestep unconsumed, while pose extraction still runs.

After advancement returns, the current signed part+35 selects the output pose
bank. The real pose/frame feedback runs on the cached JObj, preserving translation,
mandatory quaternion conversion, current AObj frame and sticky completion order.
Only afterward is signed scaleIndex+32 read, including when the target is not1.
The target1/nonnegative-scale-index branch now uses an explicitly bound owned
scale table, described below. If no table is bound, it refuses at that point,
retaining completed animation, pose and frame/latch effects. No default scale,
mirror constant or root-motion calculation is introduced.

Source byte fields and map entries are stored as raw unsigned byte bits; signed
char reads explicitly sign-extend them. Two part banks/four inline parts follow
the source initialization (`chunk_0006.c:1355–1373`). Joint and pose banks admit
at most32 entries, excluding storage aliasing beyond the observed 0x80-byte JObj
bank stride (`:6605–6607`) and 0x180/0x200-byte pose strides. Descriptor maps may
contain up to128 byte entries and may repeat joints. These ownership/layout
bounds are host admission restrictions, not invented original bounds checks.

Factories copy own-data non-proxy inputs. Header, part binding and pointer/map
records are sealed and mutable; inline part/pose identity tables are detached and
frozen. Aliased inline identities within or across actors in the same mapping
runtime are refused, and failed actor construction does not reserve identities.
Referenced descriptor/JObj tables remain live, so callbacks can replace a future
descriptor, map entry, count, JObj bank, timestep or output selector. Fields are
validated only when consumed, preserving earlier writes on late failure.

Animation and conversion adapters are fixed at runtime construction and retain
their original table receivers. They must perform the real synchronous effect
or explicitly refuse; there are no defaults. Non-undefined returns and caught
mapping reentry are checked immediately after each adapter, not delayed until
the enclosing feedback helper returns. Thus caught RObj reentry cannot proceed
to DObj/segment work, and caught converter reentry cannot proceed to frame/latch
stores. Guard recovery and earlier completed effects are retained.

The integration selftest executes actual packed AObj/FObj/JObj scalar and feedback
helpers with independent part, JObj and pose banks. It uses only an explicitly
synthetic positive-zero-Euler analytic converter, rejecting nonzero angles rather
than claiming a general source backend. Repeated mappings advance one joint
multiple times: one scenario maps [1,1,2], producing frame2/translation24 for the
repeated joint before the final joint overwrites part frame with0, while the
completion latch remains1. Shared counts accumulate without reset/end callbacks.
The mapped end39/frame38/rate2 case reaches frame40 and scalar100, preserving
packed-linear extrapolation rather than clamping to the stored key.

A three-entry scenario changes descriptor, map, count, bank selection/table,
timestep and pose selector inside real animation effects. It proves that each
future entry sees the right changes while the current JObj and original range
stay fixed. Other cases cover all four intervals, signed/empty/reversed ranges,
null descriptors, skipped count gates, lazy timestep reads, branch-local setup
refusal, late scaling refusal, readonly fields, partial writes, factory copies,
inline alias rejection, fixed adapters and immediate caught-reentry refusal with
recovery. Converter-time changes outside its quaternion-output contract are
explicit adversarial fault injections, not admitted original conversion behavior.
Thirty-three changed mapping implementations are rejected by the tests.

The bounded implementation passed independent source/code review. This closes
selection between owned actor parts, mappings, real joint callbacks and pose/frame
feedback. It does not supply archive/descriptor loading, setup-bit1 behavior,
root motion, mirrored/scaled paths, general quaternion conversion or complete
mode0/mode2 execution. It is still an offline prerequisite, not live clone
activation, instruction matching, NI=1 arithmetic parity or original replay.

## Implemented prerequisite: FObj descriptor loading

`rom/fobj-descriptor.ts` adds bounded field effects for HSD_FObjLoadDesc
(8024a208) and the zeroed header portion of HSD_FObjAlloc (8024a430), from
`chunk_0071.c:1227–1363`. It allocates real owned FObj nodes through the existing
runtime. Each modeled byte of the 0x30-byte header starts zero/null. Allocation
runs head-to-tail, and each descriptor's next pointer is consumed after that
allocation. Initialization runs tail-to-head, preserving the recursive source's
order without relying on the JavaScript call stack. The five unrolled source
allocations are not a five-node limit; a 12,000-node test exercises this distinction.

Each returning node stores next+00, signed offset+18, track+13, formats+14/+15,
base+08, length+0c, then flags+10=0 in that order. The base identity and declared
u32 length are copied without reading packed bytes or checking stream ownership.
The cursor+04 remains allocation-null until a later real animation request.
Finite source-f32 start offsets may be held in descriptors, but this loader
admits only integral signed16 values and canonicalizes float negative zero to
integer positive zero. Fractional, out-of-range, wider-double and exceptional
conversion behavior is explicitly refused at the reached offset boundary, not
approximated with JavaScript rounding or guessed PowerPC conversion behavior.

Descriptors are copied into owned sealed records; their fields remain live until
consumed. Own-data/type/writability guards are per-field, not whole-list preflight.
Already-consumed next fields and already-initialized tails are not revisited.
Overwritten old target values and unrelated fields are not validated. Refusal
preserves actual allocations, completed tails and the current store prefix;
there is no rollback or free. Opaque foreign descriptor resolution occurs after
its allocation, while host cycle/revisit and visit-budget guards prevent extra
allocations. Same-loader reentry is refused immediately after an adapter, even
if a host wrapper caught its nested error. Null loads remain true no-ops.
Methods are fixed at construction and keep their original receiver. Synthetic
allocator/resolver mutation probes test these host boundaries, not original
allocator callback behavior, allocation failure semantics or source RAM faults.

`rom/descriptor-animation.selftest.ts` loads two six-track lists into the real
packed-stream interpreter, then runs AObj request, JObj scalar callbacks and
mapped actor pose/frame feedback. Three rotation tracks actually replace nonzero
initial Euler values with positive zero; three translation tracks use real linear
streams. A start offset of 2 affects one track while the other tracks start at 0.
AObj state is explicitly seeded, with distinct end frames and rate 2 installed by
actual actor advancement. The integration preserves frame overshoot, stopped
state, sticky completion, shared counters and the absence of tree end callbacks.
It also confirms that later descriptor mutations do not change loaded headers.

Late unsupported-track, foreign-stream and truncated-stream cases retain the
first joint's completed pose/frame and the second joint's earlier scalar writes,
without fabricating a second pose or completion count. The truncated case retains
the actual two consumed bytes despite a copied declared length of 5. The quaternion
converter remains an explicitly synthetic analytic positive-zero-Euler fixture
that rejects all other angles, not a general source converter or replay oracle.
Both new selftests are registered in the contributor lifecycle suite. Independent
source/code review approved this bounded domain. Thirty-two changed loader
implementations are rejected by the tests, and all 168 prior animation/feedback
mutation controls still pass.

This closes the FObj-descriptor-to-actor-feedback connection for the admitted
scalar domain. It does not supply AObj allocation/loading, archive ownership,
JObjAddAnim replacement/removal, setup-bit1 fallback and duration behavior,
root motion, mirrored/scaled paths, NI=1 arithmetic, instruction matching or
original-game replay. In particular, AObjAlloc's rate constant at 8043d1fc is
still unverified; the separately known zero at 8043d1f8 does not establish it.
The Ghidra loader's imperfect prologue and return ABI are not claimed as matched.

## Implemented prerequisite: request-by-flags dispatch

`rom/animation-request.ts` connects HSD_JObjReqAnimByFlags and the nested
DObj/PObj/MObj/TObj/RObj request routines to existing owned animation tables.
Source functions are 8024d838 (`chunk_0071.c:3800–3818`), 8023d8e8
(`chunk_0069.c:6291–6305`), 8024a5ec (`chunk_0071.c:1476–1489`), 802423a4
(`chunk_0070.c:1235–1247`), 8023e050 (`chunk_0069.c:6734–6747`) and 802577d0
(`chunk_0072.c:602–616`). These routines provide the single-joint and nested
list request paths. The later tree extension is described below; neither path
implements attachment/setup, interpretation or actor mode execution.

The JObj path requests its current AObj when mask bit 0x1 is set, then reads the
current flags+14. If both 0x20 and 0x4000 are clear, it requests the current DObj
list. It then requests the current RObj list. This DObj-before-RObj request order
differs from the RObj-before-DObj animation order. It does not inspect the parent,
run CheckDepend, traverse children/siblings, reset shared counters or invoke end
callbacks. Unrelated JObj transforms and class callback selectors are not read.

Each DObj requests its current PObj chain, then its current MObj, then follows
its current next+04. It never reads or requests the DObj's own AObj+10. Each PObj
requests AObj+18 on bit 0x8 and then follows next+04. MObj requests AObj+14 on bit
0x4, then always visits its current TObj list. Each TObj requests AObj+64 on bit
0x10 and follows next+08. RObj reads and null-checks AObj+18 before testing bit
0x80, then follows next+00. Selected J/P/M/T calls forward null AObjs to the real
null-safe request adapter, whereas RObj's source guard skips null AObjs entirely.

Masks suppress selected AObj requests, not list traversal. Mask zero and setup
mask one still consume reachable D/P/M/T links and RObj's AObj null checks. Each
later field or link is read after completed earlier nested work. A shared list
reached from separate DObjs is visited again, not globally deduplicated. Per-list
cycle/revisit and visit-budget limits are host restrictions, not original bounds.

The dispatcher consumes the actual J/D/P/M/T getters, not a copied parallel graph.
It owns only minimal request-only RObj bindings containing next+00 and AObj+18;
this supplies no RObj animation receiver. The required requestAObj adapter resolves
real AObj ownership and invokes `requestSourceAObj` with that object's real FObj
effects, or explicitly refuses. Getter and request methods are snapshotted at
construction with original receivers. Inputs must be non-proxy own-data records.
Consumed fields are checked lazily, without whole-scalar/list preflight. Caught
same-dispatcher reentry is checked immediately after external getters and request
effects, and failures retain completed effects. Null public targets bypass
validation and reentry. Synthetic adapter mutation probes test host boundaries;
AObj request itself does not invoke source user callbacks.

The original double frame is forwarded unchanged, with no dispatcher rounding or
eager numeric admission. Actual AObj request stores its rounded f32 frame and
request flags before forwarding that original double to its FObj chain. The
current non-null FObj model requires an exact f32 operand, so a wider double can
legitimately leave those AObj stores before a FObj refusal. Null AObjs and empty
FObj chains preserve their existing bypass behavior. The dispatcher does not
silently narrow wider arguments to make this unsupported case pass.

`rom/requested-animation.selftest.ts` uses descriptor-loaded real FObj fixtures
for a joint, display, two polygons, material, two textures and relation, proving
the display's own AObj remains untouched. Separate child/sibling AObjs establish
single-joint scope. It checks every mask,
combined request order, both display gate bits, untouched excluded AObj/FObj
state, actual cursor/frame/flag/value resets and repeated requests. Subsequent
real JObj/TObj scalar interpretation updates translations and texture rotation;
request itself produces no receiver or completion effects. A late readonly FObj
refusal preserves preceding requests and the failing AObj's already-written
frame/flags, but no failing FObj stores or later RObj request. Wider-double
refusal and empty-chain acceptance use the real AObj/FObj implementations.

The existing descriptor-to-actor integration now requests both actual joints
through request-by-flags before packed-stream playback and mapped pose/frame
feedback. Its explicit zero-Euler quaternion fixture and all prior limitations
remain. This closes another setup prerequisite without claiming AObj allocation,
archive loading/reference ownership, JObjAddAnim replacement, setup fallback and
duration writes, root motion, general quaternion conversion, NI=1 parity,
instruction matching or original-game replay.

Independent source/code review approved the bounded implementation. Unit tests
also cover poisoned inactive fields, live link changes, consumed-field failure
prefixes, method snapshots and original receivers, repeated shared chains,
12,001-node traversal, and recovery after refusal. Mutation checks specifically
verify immediate caught-reentry refusal before later getter calls or RObj link
reads, rather than accepting detection at some later boundary. Thirty-nine
changed request dispatchers are rejected; all 200 prior animation, descriptor
and actor-feedback mutation controls still pass.

## Local original-evidence verification boundary (2026-11-13)

A read-only workspace check found no standalone DOL or header-valid DOL among
46 nondependency files sized 2–10 MB. The tracked archived Ghidra Program at
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
provides a useful recovery lead. `idata/00/00000000.prp` identifies it as
`boot.dol`; both database generations record
`Program Information.Executable SHA256` with the expected original hash
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
The hash text starts at decimal file offset 177496 in each database.

The checked database hashes are:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`

This establishes the archive's recorded import identity, not an independently
recovered executable, unchanged memory bytes or address-to-file mapping. No
compatible Ghidra reader was found on PATH or in checked standard installation
locations. The archived project was not opened or modified. No software was
installed, no capture was started and no rig/network operation was performed.

AObj allocation rate 8043d1fc, setup rotation fallback 804370f4, root scalar 804370f0
and rewind-conversion double 804370f8 therefore remain unverified. The last is
used at `chunk_0006.c:991–995` to convert signed rewind+26; a familiar-looking
conversion-bias expression is not proof of its bytes. The earlier documented
zero 8043d1f8 does not establish these constants. An older source note describing
804370f4 as zero was located, but no corresponding raw-byte proof was available.

The reported 63 matched pairs, 252 FPSCR samples of 0x00000004, 14 constant and
four zero-linear streams still lack a reconciled raw record and debugger-register
mapping in this checkout. This check found no new proof of that report and does
not promote it to mode or arithmetic parity evidence. The existing NI=0 model
restriction remains. A useful next evidence step is offline extraction using a
compatible reader on a disposable copy of this archive, validating recovered
file bytes and address mapping before certifying any constant.

## Implemented prerequisite: attached non-looping setup continuation

`rom/attached-joint-setup.ts` isolates the successful attached-AObj tail of
8004adc8 (`chunk_0006.c:831–1012`). It starts strictly after archive lookup and
JObjAddAnim have already attached real animation. It does not implement or fake
that boundary, and existing ordinary setup-bit1 callers remain refused. Tests
explicitly seed attached state rather than supply a no-op attachment callback.

The helper consumes existing owned JObj, feedback AObj/part and actor records,
the real request dispatcher and actual synchronous animation effects. Only
rewind+26 and loop+2c are bound separately to an existing feedback part identity;
frame+0c, duration+24 and segment+2d remain the same shared fields later consumed
by actor feedback. Method snapshots preserve original receivers and catch
same-helper reentry immediately after external getters and effects.

Initial joint/AObj null is outside this continuation domain. The initial AObj
identity and FObj head are held while every actual node is scanned, track+13
before next+00. Completing the required mask does not end traversal. Tracks 0–31
are admitted; larger byte values are refused rather than using JavaScript's
modulo-32 shift semantics. All six tracks 1/2/3/5/6/7 must be present (mask 0xee).
The first missing mask in source order 2/4/8/0x20/0x40/0x80 refuses before guessed
rotation or translation fallback writes. No stream bytes or unrelated FObj
interpreter fields are preflighted during this scan.

Loop+2c exactly 1 sets LOOP on the current AObj, then consumes signed rewind+26
and refuses at the unverified DOUBLE_804370f8 conversion boundary. This preserves
the source flag prefix and is explicitly not looping-setup support. Every other
raw byte, including 2 and 255, clears LOOP and never consumes rewind+26. The new
AObj set/clear helpers implement 80243aec/80243b08 (`chunk_0070.c:2512–2536`),
masking requested bits with 0x30000000. They validate only factory ownership,
current flags and the supplied uint32 mask, preserve all other bits/fields and
allow use during synchronous interpretation. Null AObj is a true no-op.

The supported non-loop path reloads current AObj, requires it non-null, reads its
end frame and stores duration+24. Defined finite source-f32 conversion is modeled
by truncating toward zero within signed32 range and storing signed low16. Thus
32768 becomes −32768, 65535 becomes −1 and −3.75 becomes −3; negative zero stores positive
zero. Nonfinite, non-f32 and signed32-overflow inputs refuse before duration store,
after completed flag effects. Overflow conversion behavior is not guessed.

Next it reads the shared part frame and calls actual requestJoint with mask 1.
After that request, it consumes actor timestep+1dc8 and reloads current AObj,
uses the actual rate setter, then calls single-joint animation. The actor field
is still accessed if AObj has become null; numeric admission belongs to the
null-safe setter. A null setter target therefore ignores a poisoned numeric
value, but does not bypass a missing or non-writable actor field. The selected
host order reads actor before AObj; the source call expression establishes both
reloads but not their relative instruction order. Getter mutations are labeled
host fault probes, not original callback behavior.

Only after animation succeeds does the helper write segment+2d=0, unconditionally.
It never reloads AObj or copies WRAPPED there. It does not reset completion,
inspect mode/mirror, capture a pose, reset counters, invoke global end callbacks
or animate a JObj tree. Late failures retain completed flags, duration, request,
rate, scalar stores and counts as applicable. In particular, this is not the
existing continuation helper, whose null gating and WRAPPED feedback differ.

The descriptor-backed integration executes six real packed streams. An attached
AObj starts STOPPED|LOOP with end 3; part frame 2 and actor rate 2 produce translation
(14,24,34), zero rotation, duration 3 and segment 0 after actual request/playback.
Existing mapped actor continuation then reaches frame 4, translation (18,28,38),
pose output and completion. The quaternion converter remains an explicit analytic
positive-zero-Euler fixture. Loop refusal, missing-track refusal, a final readonly
segment and late decoder failure prove retained actual effects rather than just
recording call events.

Focused tests also cover signed duration conversion, live AObj replacement,
null targets after request/animation, unused poisoned fields, precise failure
prefixes, fixed adapters, reentry recovery, the default 4096 visit cap and an
explicit 12,001-node scan. Thirty-seven changed setup implementations and fourteen
changed flag helpers are rejected. No archive ownership, full actor setup,
root motion, general quaternion backend, NI=1 parity, instruction matching or
original-game replay is claimed.

### First-track12 ordering on the attached owned FObj list

`packages/combat/src/rom/jobj-track-order.ts` implements the bounded ordering
block inside `HSD_JObjAddAnim` at `8024dc04`,
`ghidra-export/chunk_0071.c:4005–4015`. The identical algorithm also appears in
`JObjSortAnim` at `8024dbac`, lines 3943–3964. This is field-effect modeling,
not instruction/ABI matching or completion of `HSD_JObjAddAnim`.

`createSourceJObjTrackOrderRuntime` retains the actual `joints.getBinding`,
`feedback.getAObj`, and owner-specific `fobjs.getFObj` methods, with their
original receivers. `promoteFirstTrack12(joint)` reads the joint's attached
AObj identity once, retains that actual AObj, and follows its actual FObj
links. No parallel list or copied header is created. Runtime adapters must
resolve stable owned non-proxy records from the corresponding actual runtimes.

A null joint is a no-op; null AObj or empty FObj head skips the scan. The scan
reads each node's byte `track13` before advancing through `next00`. On the
first track12 it executes all three stores, in order:

1. The predecessor link (or AObj head) receives the matched node's next link.
2. The matched node's next link receives the freshly reloaded AObj head.
3. The AObj head receives the matched identity.

Even a match already at the head is detached temporarily and restored by these
stores. Returning early for that case would lose source failure-prefix
behavior; saving the old head for step 2 would create a self-link. A second
track12 is not moved, and relative order of other nodes is preserved. The
matched successor is copied, not resolved. A malformed or foreign unvisited
suffix can therefore survive this operation and refuse later when actually
traversed; this helper neither validates nor repairs the whole graph.

Host guards admit only byte-valued tracks and symbol/null links. Cycle and
visit-budget checks apply only to the search before its first match. The
default limit of 4096 is an offline safety bound, not a retail list limit.
Fields are inspected only when consumed, without clock/stream/transform
preflight. Unlike some broader existing helpers, read-only data fields are
allowed for reads; writability is checked at each actual store. A later store
failure retains earlier unlink writes. Getters must be synchronous, with
caught same-runtime non-null reentry poisoning the operation immediately after
the getter returns. Null nested calls bypass the guard. No Proxy or source
memory-fault model is claimed; deliberate adapter changes are host fault tests.

`track-order-animation.selftest.ts` loads real owned descriptors and packed
linear streams with tracks `[5,12,6,12,7]`. Promotion produces
`[12,5,6,12,7]`. Actual request-by-flags and the AObj/FObj interpreter emit
values `[44,14,24,54,34]` at frame2, then `[48,18,28,58,38]` at frame4,
with the original owner identity, overshoot, and real running/stopped counts.
The recording callback is explicitly an observer, not a track12 JObj receiver.
A separate case uses the actual JObj scalar receiver and proves that promoted
track12 refuses before later translations or their stream decoding. The
source silent flag permits real packed timing with no callbacks or joint
writes. Repeat already-head promotion preserves the actual list and playback.
The existing descriptor-to-actor integration now runs absent-track12 promotion
before its actual requests and still verifies mapped poses, frames, and sticky
completion with its explicit positive-zero-Euler quaternion fixture.

This slice performs no animation allocation, removal, attachment, request,
interpretation, RObj/DObj setup, flag-bit8 update, reference ownership, or
transform writes by itself. It does not lift the source scalar JObj receiver's
track12 refusal. The full setup-bit1 path, four unverified constants listed
above, root motion, mirrored/scaled output, general source quaternion backend,
NI=1 arithmetic, original replay, and live clone activation remain unsupported.
No publication, source transfer, rig operation, capture, or installation is
part of this implementation.

### Actual joint flag helpers and playback traversal

The existing owned scalar JObj runtime now exposes `setFlags`, `clearFlags`,
`setFlagsAll`, and `clearFlagsAll`. These model `802502dc`, `80250650`,
`80250378`, and `802506ec` respectively, from
`ghidra-export/chunk_0071.c:6306–6689`. They reuse the already implemented
`dirtySub` rather than accepting an event-only dirty callback. The animation
runtime forwards the same four methods on the same owned joint records.

Both set and clear use the source condition `((oldFlags ^ mask) & 8) != 0`.
This is not a test of whether the final operation changes bit8. For example,
clearing mask8 on flags0 performs dirty propagation, but clearing mask8 on
flags8 does not. Mask0 can also dirty an owner whose bit8 is set. If that XOR
condition holds and the owner is not logically dirty, actual dirty propagation
runs before the pending flag store. Unlike transform scalar updates, there is
no flag0x02000000 suppression for this operation. The final OR or AND-NOT
reloads flags after the dirty operation, retaining its writes unless the clear
mask explicitly removes them. A failed dirty walk preserves its completed
prefix and prevents the pending final mask store.

Single-node flag operations can dirty descendants, but only the selected root
receives the requested mask. The All variants perform preorder flag writes on
the selected root and descendants, never its root sibling. They inspect the
post-store 0x1000 bit before entering each child list: setting it prunes
immediately, whereas clearing it opens descendants during that same call.
Flag traversal does not skip logically dirty or 0x01000000 nodes. Those are
separate dirty-propagation decisions, not exclusions from flag visitation.
Entered ancestor records retain live sibling fields; child and sibling links
are checked only when followed.

The scalar factory's existing first argument remains its dirty visit budget;
its new second argument is `maxFlagNodes`, default4096. Each All operation has
its own flag visit/revisit set, independent of the fresh set and dirty budget
for each nested dirtySub call. The animation factory adds this limit as its
fourth argument, preserving its previous three meanings. These limits, cycle
refusals, uint32 mask validation, and whole owned-header validation are host
bounds. In particular, the reused header validation requires finite/writable
transform scalars even though the source flag operation does not read them.
Null targets return before mask validation. No proxy-backed memory, callbacks
inside the helper, rollback, source allocation or original ABI parity is
introduced.

`jobj-flags-animation.selftest.ts` verifies these helpers on an actual joint
tree with descriptor-loaded packed linear streams and real AObj/FObj execution.
A single root flag8 change dirties its descendants without requesting or
advancing any stream. Setting/clearing the prune bit then changes which actual
joint clocks advance, without resetting pending child requests. A real scalar
callback can set the prune bit synchronously before the enclosing animation
traversal reads the child gate. A dirty failure retains earlier dirty writes
and prevents the pending flag8 mutation. The root sibling stays excluded.
Visibility bit0x10 does not suppress this animation traversal; these tests do
not infer renderer behavior. Existing five-owner display composition now
sets/clears its real 0x4020 display gate through these helpers, and descriptor
actor-feedback tests use actual single-node flag8 helpers on their shared
joint records before subsequent request/playback.

These are building blocks for AddAnim's descriptor-controlled flag8 operation
and for the visibility receiver. AddAnim performs its flag8 operation after
RObj attachment and before the final display gate; those missing attachment
steps are not replaced by this test setup. Tracks11/12 still refuse because
the comparison threshold `DOUBLE_8043d310` at lines4743–4767 remains
unverified. A further read-only local search found no exact24MiB MEM1 file,
original DOL, memory snapshot binary, original-byte constant audit or usable
installed Ghidra/database reader. Archived import identity and prose statements
still do not establish addressed original bytes. No constant was guessed,
software installed, archive modified, rig accessed, capture repeated, source
transferred or publication attempted. Full source setup and live clone
activation remain incomplete.

### Post-allocation AObj descriptor initialization

`allocated-aobj-descriptor.ts` models the non-allocation part of
`HSD_AObjLoadDesc`, `80243d88`, `chunk_0070.c:2665–2737`. It does not implement
`AObjAlloc` or infer its unknown rate constant. The caller supplies an explicit
existing factory-owned AObj identity; playback uses that exact mutated clock.
The outer null-descriptor branch returns null without resolving the supplied
AObj or consuming any fields. With a nonnull descriptor, execution starts at
the post-allocation boundary and returns the supplied identity.

Owned descriptors contain `flags00`, `end04`, `fobj08`, and `joint0c`. A nonnull
AObj receives only flags masked by0x30000000, then rewind positive zero from the
previously documented8043d1f8 audit. The descriptor end is read and passed to
the real end-frame setter. The actual FObj descriptor loader runs next. Only
after it returns is the AObj's current old FObj head read. A nonnull old head
now uses the real FObj runtime's bounded logical release, as described below;
the returned real list is attached only after release succeeds. Finally `joint0c`
is read; a nonnull value refuses before unsupported ID-table lookup, joint
loading or reference-count operations. That refusal retains the attached list.
A null joint descriptor performs no joint action and does not clear an
unmodeled reference field.

Null supplied AObj does not skip descriptor processing. It skips descriptor
flags and all AObj stores, but still reads end, invokes the real FObj loader,
and reads the joint descriptor. The end field access is mandatory; numeric
admission belongs to the null-safe setter. This models the explicit guards in
the loader, not proven recoverable allocator failure: the allocator separately
asserts on null, then calls memset and performs initialization.

New `setSourceAObjRewindFrame` and `setSourceAObjEndFrame` implement the narrow
stores at80243fd0 and80243fe0, lines2829–2857. They check factory ownership,
only the written field's writability, and already-finite exact binary32 input.
They preserve signed zero/subnormals without guessing arbitrary-double storage
conversion. Null targets bypass argument checks. Old destination values and
unrelated flags, clocks and FObj data are not inspected. Like the rate setter,
they remain available inside synchronous callbacks. An actual packed-stream
test changes the end during its callback and proves that the same interpreter
reloads it and stops on that pass.

The descriptor runtime captures own-data methods with their original receivers,
retains stable actual records, and validates fields only when consumed. A caught
non-null reentry aborts immediately after the adapter returns; completed
allocations and writes survive. Changed consumed fields are not revalidated
after the loader. There is no simulated allocation callback, parallel clock,
default empty loader, removal stub or invented joint ownership.

The existing attached-setup integration now starts from explicit preallocated
state (frame99, rewind5, end99, rate7, STOPPED, null FObjs), then uses this real
continuation to install descriptor LOOP, rewind0, end3 and the six actual FObj
streams. Frame99 and rate7 are preserved. Only the subsequent explicit JObj
binding remains fixture-supplied; archive lookup and full AddAnim are still not
claimed. The existing non-loop setup tail then requests frame2, takes actor
rate2, produces translations(14,24,34), and later mapped continuation reaches
frame4 with translations(18,28,38) and sticky completion. This connects actual
descriptor initialization to existing source-backed request, playback and actor
feedback rather than only testing a detached data structure.

The five blocked constants, rig process-inspection denial, publication and
source-transfer boundaries remain unchanged. Full allocation, native pool lifetime,
optional joint references, archive attachment, looping setup, root motion,
mirrored/scaled output, general quaternion conversion, NI=1 arithmetic, original
replay and live clone activation remain outside this slice.


### Owned FObj release and actual list replacement

`fobj-list.ts` now exposes `removeNode` and `removeAll`. Source single removal
`8024876c` is null-safe and otherwise calls `FObjFree`; it does not read or
traverse the successor. `RemoveAll`, `80248794`, descends before tail-to-head
release (`chunk_0071.c:128–211`). The nine-node unroll is not a length limit.
The Ghidra export loses the head/recursive-call arguments; this is the bounded
structured-decompilation interpretation, not independently verified instruction
or ABI accuracy. An explicit stack supports 12,001-node tests without relying
on JavaScript recursion depth.

Release actually deletes each identity from the owning runtime's Map and its
header from the ownership WeakSet. Stale symbols can no longer resolve, and
retained headers no longer pass validation, packed-data/wait decoding or linear
evaluation. This is logical lifetime support, not a fake event-only free.
It deliberately does not implement native allocator pool layout, reuse,
allocation counts or memory reclamation. The inspected `FObjFree`,8024a48c,
calls `ObjFree`,80257440 (`chunk_0072.c:380–388`), which overwrites the native
next word with a free-pool link and updates pool counters. A stale JavaScript
record remains an ordinary inspectable object; its unchanged fields are not a
claim about freed native memory. Single release also does not unlink external
AObj/list references. Later runtime use of dangling identities refuses.

Only next00 is consumed while collecting a list: stable own-data readonly
links are admitted, while unrelated invalid scalar fields are ignored. A
cycle, foreign successor, malformed next identity or visit-budget refusal
during descent releases nothing. After successful descent, release runs in
reverse. These are host bounds, not emulated retail fault behavior. Stream
and cursor storage survives release, matching the absence of a stream
destructor in the inspected free path. Existing or newly loaded nodes can
replay the same copied packed stream; no proprietary asset ownership is added.

Both base-list and timing-runtime boundaries reject nonnull removal while an
interpreter is active, including direct `interpretNode`. Caught removal
attempts poison that active operation before its next post-callback store;
completed clock/decoder/callback writes remain. Tests explicitly cover state4's
pending state5 write and StopAll's pending flag clear. Null removal bypasses
the guard without poisoning. This is a host lifetime restriction, not an
inferred source callback behavior.

The allocated-AObj continuation now requires a captured real `removeAll`
adapter. New FObjs load first; the live old head is then read and, when nonnull,
released. The final attachment store is checked for writability only after
release, so a refusal can leave a stale old AObj head and still-live new
allocations, exactly describing the bounded execution prefix. A non-undefined
or asynchronous remover return refuses after invocation. Optional joint
lookup/refcount ownership remains unsupported and refuses after new attachment.
Null new list still releases the old list; null old head skips removal; null
AObj still performs loading without releasing any list. Fixed methods/receiver
and caught-reentry poisoning extend across real removal. Loader and remover
failure cases retain actual allocations and completed clock writes.

The real six-stream attached-setup fixture now plays, replaces its old decoded
list using the same descriptor-backed streams, verifies all old identities and
headers are invalid, and requests fresh state at frame1. Actual JObj callbacks
produce translation(12,22,32), then actor mapping reaches frame3 with
translation(16,26,36) and completion. The original frame2/frame4 tests still
pass. No archive attachment, full AddAnim, source allocator defaults, AObj
removal/refcount ownership, looping conversion, root motion, general quaternion
conversion, NI=1 arithmetic, original replay or live-clone activation is claimed.


### Actor target-1 translation scaling

`actor-joint-mapping.ts` now performs the post-capture scaling branch of
`4acdc`, `chunk_0006.c:593–608`. Once actual joint advancement and pose/frame
capture finish, signed part+32 is read for every target. A nonnegative index
with destination target1 selects the current signed part+35 translation bank,
then reloads the scale index and reads the inline actor+1dd4 float table. It
scales slot1 in that newly selected bank, not a cached pre-capture pose. Negative
signed bytes128–255 and non-target1 entries do not consult the table. Root,
mirror and setup-bit1 boundaries remain explicit refusals.

`bindScaleTable(actor, values)` binds one copied, sealed, factory-owned array to
an existing actor; `getScaleTable(actor)` exposes that live owned data. Up to128
entries admit signed nonnegative indices0–127. This is a host layout bound, not
proof of native table extent. No pointer field is invented in the actor header,
no factor is inferred, and no default1 or skipped required operation is installed.
Binding rejects foreign actors, repeat binding, accessors, holes and nonfinite or
non-float32 values without retaining the caller's array. Executing the branch
checks only the reached table entry, so unused invalid values do not interfere.
Read-only factor entries can be read. Missing tables or out-of-range indices
refuse after actual earlier animation/capture/frame work. Binding during active
mapping refuses and poisons caught reentry, like the mapping execution guard.

The callee labeled `PSQUATScale`,8020ba9c, is a three-float vector operation in
`chunk_0064.c:1299–1317`, not four-component quaternion scaling. It snapshots Y
then Z, reads X, and stores scaled X, Y, Z in that order. The implementation
preserves that decompiled order and in-place destination. Readonly Y/Z may be
snapshotted; they refuse only at their respective stores, retaining earlier
writes. Invalid Y/Z input refuses before X, while Y/Z result overflow can occur
after earlier component stores. The quaternion and source JObj translation
are not scaled. Host fault prefixes are documented, not claimed as retail
fault behavior or original instruction order.

For already finite binary32 operands, the exact product fits binary64 precision
and range; `Math.fround(component * factor)` supplies one nearest-even binary32
rounding. Signed zero and gradual underflow are preserved. Rounded overflow is
rejected before its store. This is the existing RN00/NI0 numerical domain, not
original FPSCR observation, NI=1 parity or paired-instruction/quantization proof.
The separate physics vector helper is not used because it does not round these
stores to float32. There is no new dependency on an unresolved game constant.

Focused tests cover zero/negative/fractional/large/subnormal factors, signed index
and table bounds, readonly and overflow store prefixes, copied/live tables,
lookup ownership, fixed adapters/receivers and caught reentry. Out-of-contract
converter/getter fault injection explicitly verifies late bank/index/factor
reads and retained completed prefixes; it does not grant converters permission
to mutate unrelated state. Repeated mapped entries perform fresh capture and
scaling rather than accumulating scale into the prior pose.

Real integration uses the descriptor-loaded six-stream setup and actual
AObj/FObj/JObj interpretation. It exercises both pose banks, scales captured
translation(18,28,38) by0.5 or−2 while leaving the JObj and clock/completion
unchanged, then changes the owned factor to2, re-requests frame0, and captures
frame2 as(28,48,68). A separate seeded exact-integer reference checks10,000
actual mapping/capture/scaling cases, including binary32 edge values and2,671
overflow prefixes. This reference and the packed-stream fixtures are synthetic
contract evidence, not original-game replay or live-clone activation.

Root motion still reaches unverified 804370f4/804370f0 plus magnitude/angle and
optional rotation; mirroring additionally requires verified 80437128 and the
mirror map. Full archive/setup, quaternion conversion, NI=1 parity and original
replay remain incomplete. No denied rig read, publication or source transfer
was retried.


### Whole-tree animation requests

`animation-request.ts` adds `requestJointTree(root, frame, flags)`, the bounded
semantic reconstruction of `HSD_JObjReqAnimAllByFlags`, 8024d8c0,
`chunk_0071.c:3822–3938`. It calls the existing internal single-joint dispatcher
for each reached node: AObj on bit 1, fresh 0x4020 display gate for DObjs, then
RObjs. Only afterward does it reload flags for the 0x1000 child gate. The root
is always requested, descendants are visited in preorder, and the root sibling
is excluded. No dependency check, interpretation, scalar update, counter reset
or end callback is introduced by the request itself.

Traversal retains entered owned records, not future links. A node's child is
read only after its request and post-request pruning test. Its sibling is read
after its whole subtree returns. Adapter fault-injection tests change those
links/gates to verify late reads and failure prefixes; these are not claims
that original AObj request invokes a user callback. Independent-joint and dirty
bits do not skip requests, while 0x4020 affects only display requests, not tree
children. Mask 0 still traverses reached nodes without selecting AObj work.

An iterative stack avoids host recursion limits; the source unroll is not a
depth limit.
The fourth factory argument `maxTreeNodes`, default 4096, bounds root-inclusive
unique visits independently of the existing third argument's per-list budget.
Each nested display/RObj list still has its own budget. A cycle, repeated DAG
node or tree-budget exhaustion refuses before that node is requested again.
Malformed/foreign children, sibling links, readonly consumed fields and later
adapter failures preserve earlier real requests. Pruned child links and root
sibling fields are never consumed. Null root bypasses frame/flags/reentry and
lookup checks. All nonnull requests share the existing immediate caught-reentry
poisoning across captured getters/effects.

The original double frame and uint32 mask are forwarded unchanged to every
node. Numeric admission stays in actual AObj/FObj request code; in particular,
a non-f32 double is not silently rounded by the tree layer. The Ghidra export
loses the head/frame/recursive-call argument bindings and uses savegpr-derived
values in its recovered prototype. Tree argument propagation and preorder
semantics are therefore an explicit bounded reconstruction, not a matched
prototype, original-instruction audit or ABI-accuracy claim.

The new playback integration loads actual packed linear FObj descriptors for
root, child, grandchild, child sibling and an excluded root sibling. Requesting
frame 2 resets only the four reached AObj/FObj states in preorder, leaving joints,
counters and end callbacks unchanged. Later actual `animateTree` drives source
scalar callbacks to translations 14/24/34/44 while the excluded sibling remains
untouched. Requesting frame 1 again rewinds the actual decoded streams and yields
12/22/32/42. Source flag pruning and reopening control both request and playback.
A late real FObj reset failure retains previous requests and current AObj stores,
without requesting the later sibling. A non-f32 frame test preserves the current
AObj's rounded frame prefix before actual FObj refusal.

The existing joint-flags/playback integration also now uses the real tree
request instead of a manual per-joint loop. Its separately requested root-sibling
sentinel is explicit and remains excluded from both tree operations. Synthetic
traversal tests cover live gate/link changes, masks, failure prefixes, separate
budgets, fixed adapters, cycles/revisits, 12,001-node depth and reentry. These
connections do not implement archive attachment, JObjAddAnim, full actor setup,
missing constants, original replay, NI=1 parity or live-clone activation.

## Actor dispatch into real playback: mode 0

`actor-animation-dispatch.ts` now composes `80049e58` with the non-linked
`80049f10` path and the actual owned actor mapping/feedback runtime. Source is
`ghidra-export/chunk_0006.c:1–68`. The mode-table association at `802d0d84` is
recorded in `docs/knight-authored-windup.md:8–22` from earlier retail-DOL numeric
inspection, and capture05 above records mode 0 entering `49f10`. This task did
not independently reread those DOL bytes or the raw capture. Ghidra loses the
handler's part-number calling-convention binding, so this remains a bounded
semantic reconstruction rather than an instruction/prototype/ABI match.

The dispatcher uses the same actor, layout and feedback part records as real
mapping. Explicit, copied and sealed bindings supply the additional actor fields
`1d88`, `1d8c`, `578`, `1db3` and part fields `08`, `10`, `14`, `36`. The two bank
pointers are presence-only symbolic identities here: this function does not
read their contents or invent descriptor ownership. Existing part fields,
including frame `0c`, mode `2f` and completion `2e`, are shared, not shadowed by
a second clock or completion state.

Execution preserves the source order:

1. A null `1d88` returns 1 without reading `1d8c`. Otherwise null `1d8c` returns 1.
2. Only part 1 examines `578`. If it is exactly 1, `1db3` is tested; both 1
   returns 0 before part resolution or writes.
3. Copy elapsed `08` to previous `10`, then frame `0c` to previous `14`.
4. Read signed mode `2f`. Modes other than 0 refuse after those snapshots.
5. Add the live actor timestep to elapsed and store float32. Then separately
   reload frame and timestep, add and store float32.
6. Read `36`. Its nonzero linked-animation branch refuses after both increments.
7. Call actual `animatePart(actor, 0, 0, partNumber, 2)`. It runs the existing
   JObj/AObj/FObj pipeline, pose capture and completion feedback. AObj frame
   feedback can replace the preliminary frame increment.
8. Return the live completion byte sign-extended to signed 32-bit. Do not
   normalize it to Boolean, clear it or skip work when it is already nonzero.

Factory ownership, four-part bounds, finite exact-f32 input, RN=00/NI=0,
nonaliasing own-data records, fixed synchronous methods and caught-reentry
poisoning are host restrictions. Snapshot copies preserve admitted signed-zero
bits without arithmetic; arbitrary NaN payloads are outside the domain. Each
addition has one f32 rounding. Overflow refuses before its store, retaining
snapshots and any earlier increment. No unknown numeric constant is needed on
this admitted path. Downstream root, mirror, quaternion, track and other
restrictions remain active; the dispatcher does not install fallback effects.

The packed integration in `attached-setup-animation.selftest.ts` starts with
actual descriptor-loaded six-track streams and the existing explicit attachment
boundary. It deliberately sets the part frame to 100 while the actual AObj is
at 2. Dispatch saves 100, provisionally advances it to 102, then real playback
returns frame 4, translation `(18,28,38)` and completion 1. A second call still
advances elapsed and recaptures the stopped pose, while the final frame stays 4
and decoder/counter work does not repeat. Another case enables actual looping
on explicitly supplied finite fixture rewind/end values: stop/request/replay
produces frames 1 and 0, translations `(12,22,32)` then `(10,20,30)`, and real
WRAPPED feedback. This does not claim the unresolved signed-rewind setup
conversion. Null-AObj and null-part-descriptor cases preserve their distinct
frame/capture/completion behavior. A late real scalar-receiver refusal retains
completed dispatcher/AObj writes without successful pose/completion feedback.

This is actor-level playback/completion integration, not a replacement for the
full stream interpreter. Source `1cfc` production, stream-wait completion,
linked animation, other dispatch modes, archive/setup, general quaternion
conversion, root motion, mirroring, native allocation/ref ownership, NI=1
parity, original replay and live clone activation remain incomplete. No
publication, source transfer, rig process inspection or original capture was
attempted in this slice.

## Entered stream-wait continuation produces the source target

`stream-wait-target.ts` implements the already-entered `uVar6 == 0 && bVar3`
continuation inside `8004cd24`, `chunk_0006.c:2082–2092`. Its caller must already
have selected an active, unsatisfied, non-countdown wait. It does not evaluate
that predicate, clear the earlier per-pass marker, walk masks, dispatch commands,
initialize a stream or set stream completion. The method is explicitly named
`continueUnmetNonCountdownWait`; no callback pretends to supply a missing source
predicate or playback implementation.

The owned stream record has three explicit fields: target `08`, previous target
`0c` and accumulator `10`. Four copied, sealed records are bound to an actual
mapping-owned actor. The corresponding animation state is the shared feedback
part selected from mapping bank 0, not a copy of its frame or segment. Native
stream base is `actor + 1cd4 + partNumber * 20`; part 1 target `08` is therefore
`actor + 1cfc`. This does not adopt the legacy VM's synthetic frame clock or
active/cursor sentinels as source fields. Legacy names are misleading:
`RomPartState.prevTarget` denotes source `08`, `curTarget` denotes `0c`, and
`animTime` denotes `10`.

The continuation performs actual effects in source order:

1. Copy current target `08` to previous target `0c`.
2. Call actual actor dispatcher `updatePart(actor, partNumber)` and ignore its
   signed completion result. Its mode-0 path runs real packed FObj playback,
   JObj updates, pose capture, frame and segment feedback.
3. Read the live animation segment `2d`. A nonzero byte refuses at the entire
   duration-conversion expression requiring unknown `DOUBLE_804370f8`. It does
   not read duration, accumulator or final frame after that refusal boundary,
   and does not assume duration 0 removes the dependency. The old-target copy
   and all completed dispatch effects remain.
4. With segment zero, read the live accumulator and animation frame and store
   `f32(accumulator + frame)` into target `08`. This path never reads duration.

Readiness and freeze early returns from the dispatcher do not skip the following
segment check and target addition. Stream completion is distinct from animation
completion; neither a Boolean dispatcher result nor the animation latch is used
as a gate. Finite exact-f32 RN=00/NI=0, four parts, owned nonaliasing own-data
records, stable synchronous runtime methods, fixed receivers and caught-reentry
poisoning remain explicit host limits. Read-only input fields may be read; the
final target's writability is checked at its store, after real playback. Overflow
refuses before that store and does not undo earlier effects. This is source-level
ordered reconstruction, not independently audited instruction order or RAM ABI.

Actual packed integration now exercises part 1, not just an isolated arithmetic
fixture. After real descriptor/setup playback reaches AObj frame 2, the part
frame is deliberately set to 100. The entered continuation snapshots target 78,
real dispatch replaces the provisional frame 102 with AObj frame 4, and the
source target becomes 4 or 6 for explicit accumulators 0 or 2. Completed/stopped
playback leaves the target stable on the next call while elapsed still advances.
Real looping produces frame 1 and segment 1, then refuses the unknown conversion,
including with duration 0. Readiness/freeze skips, malformed unused duration,
read-only final target and late real scalar-receiver failure have distinct
verified prefixes.

A deliberately explicit test-only bridge copies the produced target into the
existing `updateReactionStream` comparison. Values 4 and 6 choose continuation
and restart around the independently recorded reaction threshold 5, despite a
synthetic frame clock of 10000. That consumer still delegates to the legacy
`tickStream`/`startStream`, which are not made source-faithful by this bridge.
No production wiring, codec ownership change, full wait execution, reaction
playback or live clone activation is claimed. Original constant reads, full
predicate/countdown/parser and wrapped-accumulator support remain unresolved.

## Archived constant evidence recovered

The prior missing-byte boundary for six constants now has address-mapped local
archive evidence. See [the reproducible ProgramDB audit](archived-program-constants-2026-11-13.md).
Both archived snapshots and two independent parsers agree; four prior original-DOL
controls also match. Values are: 804370f0 float 1, 804370f4 positive float zero,
804370f8 double (2^52 + 2^31), 80437128 float -1, 8043d1fc float 1, and
8043d310 double 0.5. The entire containing data block is identical between snapshots.

This supersedes earlier statements that those addresses have no mapped local
byte evidence. It does not retroactively implement paths that currently refuse,
prove an unchanged original executable, or establish live/NI=1 parity. The File
Bytes table is empty, so original executable hash reconstruction was unavailable.
No runtime behavior changes in this evidence checkpoint; future ports must cite
this archive provenance and retain its limits.

## Implemented prerequisite: wrapped stream-target accumulation

`rom/stream-wait-target.ts` now admits the nonzero-segment arm of the already
entered unmet non-countdown continuation in `4cd24` (chunk_0006.c:2082–2092).
The previous unknown-constant refusal is replaced using the
[archived ProgramDB evidence](archived-program-constants-2026-11-13.md):
`DOUBLE_804370f8` has bits `4330000080000000`, making the source's double
`CONCAT44` subtraction exactly the signed16 duration. Exhaustive synthetic
arithmetic confirms every signed16 input. This is archived-byte evidence, not
proof of an unchanged original executable or a fresh original execution.

The source duration is the signed short at actor `1af8 + part * 40`, represented
by feedback part `duration24`. It is not the stream completion byte at `1a`.
After the existing old-target copy, actual dispatcher call and live segment read:

1. A zero segment still skips duration entirely and leaves the accumulator alone.
2. Any nonzero byte segment reads the signed16 duration and live f32 accumulator,
   stores `f32(accumulator + duration)` into `accumulator10`, then proceeds.
3. Both arms freshly read the live accumulator and frame and store
   `f32(accumulator + frame)` into `target08`. The two sums are not fused.

Duration-before-accumulator validation within the conditional sum is a chosen
host fault order. The decompiled C does not prove operand evaluation order for
that expression. The separate source statements establish the accumulator store
before the later target calculation; this port preserves that boundary. Read-only
duration is allowed. A read-only accumulator is acceptable on the zero-segment
arm but refuses at the wrapped store even for duration zero. A later bad frame,
target overflow or read-only target preserves the successful accumulator store
and all earlier dispatch/pose effects. No rollback or inferred loop-count
multiplication is introduced. Signed completion still does not gate this path.

The packed setup/playback integration now produces real wrap feedback and adds
zero, positive and negative signed durations. Repeated real wraps each add once;
a subsequent non-wrapping frame leaves the accumulated value unchanged. A large
actual AObj step crossing multiple loop lengths still adds only one duration,
as the source's nonzero flag requires. Store-refusal cases retain the actual
stop/request/replay and captured pose, with accumulator preservation determined
by whether its own store succeeded.

This remains a bounded continuation, not full wait-predicate evaluation,
countdowns, command parsing, stream completion or production source-owner wiring.
All prior ownership, synchronous-effect, no-aliasing, finite exact-f32 RN=00/NI=0
and caught-reentry restrictions remain. Original replay, instruction/ABI parity,
NI=1 behavior and live clone activation are not established by these tests.

## Implemented prerequisite: actor-level source wait routing

`rom/stream-wait.ts` composes the actual mapping, animation-dispatch, feedback
and target-continuation runtimes into a bounded `4cd24` update. It implements
actor/part selection, blocked and finished routing, the ordinary wait predicates
and countdown waits. This removes the need for tests to preselect the unmet
non-countdown branch externally. It does not replace the production legacy
stream runtime, parse commands, or claim full source execution.

New copied/sealed sidecars contain only previously absent fields: actor masks
`activeMask579` and `blockedMask1d9a`, and each stream's symbolic `current00`,
float `wait14`, byte `finished1a` and byte `event1e`. Owned current-record objects
provide `flags01`; these explicit fields are not claimed to be parsed archive
bytes. Existing target records retain `target08`, `previous0c` and `accumulator10`.
Existing dispatcher records retain `elapsed08` and `linked36`; feedback retains
frame, duration, completion and segment. There is no duplicated animation clock
or hydration from legacy `active`, `frameClock` or `streamPtr`.

Source routing from chunk_0006.c:1995–2121 is preserved:

- Snapshot the active mask before testing part 0's current pointer. Null part 0
  sets all four finished bytes to 1 in order and returns 1, even for request mask
  zero. It does not clear events, inspect the other current pointers or animate.
- Otherwise visit selected low-four mask bits in ascending order. Clear the
  selected event byte first, then read the live blocked mask. Blocked parts call
  actual animation dispatch and skip their finished/predicate fields.
- An unblocked finished byte is any nonzero raw byte. It contributes 1 to the
  aggregate result; only exact `linked36 == 1` calls actual animation dispatch.
  Other valid linked-byte values skip it. Existing unsupported dispatcher paths
  still refuse after their existing successful prefix.
- An unfinished selected part reads its current record's flags lazily. Countdown
  bit 8 takes precedence over bits 2 and 4. It stores
  `wait14 = f32(wait14 - timestep1dc8)`, reloads the value, and keeps waiting if
  positive. Otherwise it stores positive zero and handles a met wait. Countdown
  does not animate or update targets while waiting.
- Without bit 8, bit 2 is refused before bit 4. Their unusual decompiler
  conversions and `FLOAT_80437148` are not inferred from nearby constants.
- Ordinary nonnegative `wait14` compares against the actual dispatch-owned
  `elapsed08`, not animation `frame0c`. A negative non-stop wait tests signed
  `complete2e > 0`. A negative stop wait tests signed completion first, then signed
  `segment2d > 0` only if completion was not positive. Raw bytes 128–255 are
  negative here, while the target continuation's separate segment test is
  nonzero. Those two predicates must not be conflated.
- An unmet ordinary wait calls the actual target continuation, including real
  animation, wrapped accumulation and frame feedback. A met wait reloads its
  current pointer/flags. Stop bit 1 stores finished=1; non-stop refuses at the
  reached `4c050` command-execution boundary. No fake parser or completion
  callback stands in for that missing implementation.

Source `wait14` is binary32 despite Ghidra's `int *` casts; `4c050` explicitly
stores floats at actor offsets `1ce8`, `1d08`, `1d28` and `1d48`. This port neither
truncates fractional waits nor converts float bit patterns into numeric integers.
The archived positive zero is the countdown clamp value. Countdown's chosen
wait-before-timestep validation is host fault ordering, not an instruction-order
claim from C. Store checks occur only when reached, and later failures preserve
event clears, countdown stores/clamps and successful dispatch/target effects.

Actual packed integration enters through actor-level waits. An elapsed threshold
of 8 first observes elapsed 7, runs packed playback, and produces elapsed 9,
frame 4 and target 6. The next call finishes without replay even though frame 4
is still below the threshold. A negative stop wait observes actual wrap feedback
on its next call and finishes without a second wrap. Fractional countdowns,
countdown priority, blocked actual playback and met non-stop parser refusals
also exercise the shared owned records rather than a predicate-only fixture.

The host domain remains finite exact-f32 RN=00/NI=0, four parts, owned non-proxy
data, no RAM aliases/deferred effects, fixed runtime methods/receivers and
caught-reentry poisoning. Archived-byte evidence retains its original-file
provenance limits. No original replay, instruction/ABI match, NI=1 behavior,
complete command VM or live clone activation is established here.

## Implemented prerequisite: relative and percentage wait predicates

The two predicate cuts in `rom/stream-wait.ts` now have bounded implementations
supported by the [mapped archive instruction audit](archived-wait-predicates-2026-11-13.md).
`FLOAT_80437148` is 100. Crucially, the odd duration casts in the decompiled C are
Gekko `psq_l` loads using GQR5, not the previously recovered double-conversion
idiom. Mapped startup code sets GQR5 to signed16, scale zero. The model requires
an explicit immutable `gqr5: 0x00070007` option only when a duration load is
reached; this is a startup-derived host profile, not measured live-register state.

Relative bit 2 retains nonnegative wait values without reading duration or the
profile. A negative wait loads signed16 duration, adds with one f32 rounding,
clamps only a negative sum to +0, then compares against actual frame0c. It never
rewrites wait14. Percentage bit 4 reads duration and frame, performs f32 division,
reads wait, then performs a separate f32 multiply by 100 before comparison.
Zero divisor and nonfinite product behavior are deliberately outside the admitted
host domain. Negative nonzero signed durations remain valid. Countdown still
wins over both modes, and relative wins over percentage.

Actual packed playback integration exercises positive and negative relative
waits and a 100-percent wait: pre-step frame 2 keeps waiting, actual playback
produces frame 4 and target 6, and the next update finishes without replay.
A relative wait of -1 with duration 3 already meets at frame 2 and does not
animate. A met non-stop percentage wait still refuses at the source command
execution boundary. An unsupported selected numeric profile refuses before
animation/target effects, retaining the selected event clear.

All modes share existing actor routing, source-owned feedback/clocks, target
production, lazy field access, readonly/store checks and reentry contracts.
Independent rational validation establishes the two-round percentage expression
for the finite binary32/signed16 RN=00/NI=0 domain. It does not establish PPC
exception behavior, NI=1 parity, live GQR contents, command parser completeness
or production replacement of the legacy stream owner.

## Byte-backed opcode0 wait-record continuation (2026-11-13)

The source-owned stream control runtime now supports the bounded initial-opcode0
path in `zz_004c050_` (`chunk_0006.c:1538–1603`) and its reached non-stop call
from `zz_004cd24_` (`:2095–2098`). The stream factory privately copies bounded,
non-shared bytes. Owned cursor identities carry their original backing stream
and byte offset; they are not legacy `streamPtr` values or fabricated RAM
addresses. Parsed wait flags come from byte+1, and the installed signed wait
comes from the big-endian halfword at byte+2. The archived `804370f8` conversion
evidence makes every signed16 value exactly representable as binary32. This
conversion does not require the separate quantized-duration GQR5 profile.

Opcode0 is read before any target effects. Other opcodes refuse before dispatch;
there is no generic handler callback pretending to execute them. For selected
low-four mask bits, all actual target fallbacks run in ascending part order
before the first control install. Each fallback uses the same real dispatch,
feedback, wrapped accumulator and target stores as the unmet ordinary wait
branch. Then each selected part receives current00, next04=cursor+4, signed
wait14 and finished1a=0, in that order. The parser neither clears event1e nor
consults active, blocked or finished gates. A mask selecting no low-four bits
still consumes the opcode but does not read the wait operand.

Current and next cursor stores precede a reached truncated-operand failure;
prior target/animation effects also remain. Deriving next04 does not dereference
it, so a final four-byte stop record needs no trailing bytes. Bounds failures,
uint32 offset overflow, fixed ownership, no source RAM aliasing, immutable byte
snapshots and synchronous/reentry checks are explicit host constraints, not
claims to emulate retail memory faults or allocation behavior.

A met non-stop wait reloads its current flags, enters the parser once at actual
next04 using only that part's bit, and leaves the new wait for the following
actor update. Parser completion alone does not contribute to the finished
aggregate. This includes countdown waits: while countdown is positive there is
no animation, but its reached parser fallback does animate. Earlier countdown
clamping and event clearing survive an unsupported next opcode. Existing direct
command fixtures remain supported with an explicit null-next parser refusal;
byte-backed cursors never expose a detached mutable flags record.

Packed integration now covers installation through actual FObj/AObj/JObj
playback, a multi-tick countdown advancing to the final stop record, an ordinary
elapsed wait transition, a signed negative completion wait, end-of-buffer next
storage, and failure prefixes for truncation and nonzero opcodes. It continues
to supply explicit post-allocation attachment/bootstrap fixtures; it does not
claim original-asset replay or source-owned live gameplay.

### Production ownership remains an explicit next boundary

Production call-site inspection found no constructor calls for the new mapping,
dispatch or wait runtimes outside their selftests. Live ownership is still
`battle.ts` actor spawn/tick → `RomDriverBridge`/`stepRomActor` and legacy stream
context → `BattleActorView` → `battleScene.ts` presentation mixers. Adding a
second source animation call to that route would duplicate clocks and ownership.
The current bridge's special-action early exits also do not form an exclusive
source-owned actor lifecycle.

The next integration should compose one source owner with real descriptor,
AObj/FObj, JObj, feedback, mapping, dispatch, target and byte-backed wait
runtimes. Inputs must explicitly supply maps, banks, part and pose state,
backing bytes and admitted numeric profile. Actual archive/JObjAddAnim and
opcode01/48648 setup, descriptor/metadata lookup, allocation/reference ownership,
reached RObj/DObj effects, nonzero Euler conversion and unsupported animation
modes cannot be replaced with no-op callbacks or inferred legacy fields.

Only after that owner has supported source-backed inputs should actor creation
attach it and choose an exclusive update route before legacy host
status/movement/reaction writes. This checkpoint deliberately does not enable a
production call, map legacy frameClock/active/sentinel values into source fields,
or claim Double clone activation.

## Nonzero stream commands on shared animation state (2026-11-13)

The byte-backed parser now executes opcode `0x10` modes 1 and 2 before its
terminal opcode0 wait. `archived-stream-command-2026-11-13.md` records the exact
handler table entry, handler instruction range, conversion bias, provenance and
reproduction command. Both authenticated ProgramDB snapshots agree that table
entry 16 points to `8004caa4` and `DOUBLE_80437140` is `2^52`. This is archived
static evidence, not new original-DOL invariance or runtime parity.

Mode1 stores the exact unsigned operand byte as float32 in the actual target
runtime's accumulator10 for selected low-four mask bits, ascending. Mode2 uses
the actual bank0 feedback part's mirror30: operand1 clears, 2 sets, 3 XORs with 1;
0 and values 4–255 do nothing. XOR preserves the other byte bits. Clear/set do
not validate the overwritten old value, while XOR reads and validates it.
Ignored operands do not resolve or read mirror state. Neither mode reads byte1.

Each handler advances the local same-backed cursor by four before reading mode
byte2. Operand byte3 is consumed only for selected parts. Every handler's
completed stores survive a later malformed or unsupported suffix. No fallback
or current/next/wait/finished installation occurs until opcode0 is reached.
The terminal fallback still uses actual animation/feedback and occurs exactly
once per selected part, after all admitted handlers. Opcode1 remains unsupported,
so the source's fallback-suppression branch is not inferred or simulated.

A positive immutable maxCommands option defaults to 4096 as a host execution
bound, counts nonzero commands only, and resets per parser invocation. It
refuses before executing an excess handler. Only modes1/2 are admitted; all
other modes, including source no-op subdomains, explicitly refuse rather than
invent missing actor-field ownership. Missing terminal bytes and budgets do not
undo completed command effects.

Packed integration demonstrates mode1 changing accumulator 2 to 7 before actual
frame 4 yields target 11; a set-then-XOR mirror chain returning the shared byte to 0
before the one real fallback; clearing an existing mirror byte before actual
mapping; and a countdown continuation executing a nonzero accumulator command
before installing its next wait. A set-mirror command followed by fallback
naturally reaches the real unsupported mirrored-mapping boundary, retaining the
command and dispatcher prefix without pretending the animation succeeded.

The production bootstrap/lifecycle boundary above remains unchanged. These
commands directly modify shared source-owned runtime records, but no adapter
maps them into legacy active/frameClock fields, no second animation tick was
enabled, and no live clone or original-data playback is claimed. Full opcode01
setup and source-owned bootstrap remain the next prerequisite for production
ownership, alongside the still unsupported mapping and lifecycle paths.

## Source-owned stream start and reset (2026-11-13)

`stream-wait.ts` now composes the bounded `zz_004beb8_` bank-selection/start
path and `zz_004c020_` reset with its existing actual parser and shared target
records. `archived-stream-start-2026-11-13.md` preserves both authenticated
ProgramDB instruction ranges, signed loads/index operations and reset stores.
These static snapshots do not establish unchanged original DOL or live parity.

The explicit start binding owns familyBank1d80, sharedBank1d84,
defaultSelector582 and marker709. The existing actor binding remains the sole
owner of activeMask579. Existing stream controls gain group18, action19 and
status1d; omitted initial values default to zero for fixture compatibility,
not as evidence of source allocation defaults. No target or animation field is
duplicated or imported from legacy `active`, `frameClock` or `streamPtr` state.

Start snapshots requested mask AND signed8(activeMask579), then clears marker709
if effective bit value 2 is set. The original selector bit 7 chooses family or
shared bank before default substitution. A null chosen bank resets all four
parts and sets each finished1a to 1 immediately after its reset, regardless of
mask; it does not read the default selector, bank bytes or parser.

Only original family selector zero reads signed8(defaultSelector582), promoted
to uint32. A negative default keeps the family bank. Shared lookup masks the
original selector with 0x7f; family lookup uses the full effective selector.
Each table index uses the evidenced 32-bit left-shift, including wrapped index
values. Both table offsets are signed BE16: the first relative to bank, the
second relative to resolved group. Final parser cursor is formed before any
selected stamps or resets, matching archived instruction `8004bfbc`.

Selected low-four parts are processed ascending: low-byte group18 and action19
stores, then reset. Reset writes actual target previous0c, accumulator10,
target08 to +0, followed by control status1d, event1e, next04, current00,
wait14 and finished1a in that exact order. Pointer fields become null, numeric
fields +0. Group/action and animation feedback/clocks are not reset. Every
selected reset completes before the single parser call; even zero effective
mask still resolves tables and invokes the parser. Unsupported setup opcode1
therefore refuses after the real start/reset prefix, without a no-op substitute.

Host admission is explicit: uint32 mask/selector, signed32 action index, owned
copied byte storage, and uint32 local cursor coordinates. Shifted indices are
interpreted as signed32 local displacements; valid negative offsets from an
interior cursor are supported. Local pointer underflow/overflow refuses rather
than inventing wrapping virtual addresses, aliases or bytes outside the snapshot.
Bytes beyond the copied view fail only when read. Banks are mutable owned
binding fields with lazy cursor-ownership checks on reached non-null paths.
Read-only source operands are accepted; reached stores check writability. Fixed
method receivers, synchronous contracts and poisoned reentry guards continue
to preserve earlier effects on failure.

Actual packed integration now starts from two real signed-relative tables,
resets stale targets, executes accumulator commands, performs real FObj/AObj/JObj
playback and pose capture, and continues into the next countdown/terminal wait.
Repeated starts reset stream state while preserving the real animation clock.
Shared banks retain the original selector stamp. Missing banks reset all four
without animation; bad tables and unsupported setup retain only their reached
prefixes. Supplementary tests exercise all 256 default bytes, shared selector
forms and low-four masks, plus exact readonly reset prefixes.

This removes bank start/reset as a bootstrap prerequisite for the admitted
command domain. It does not supply retail actor data, source allocator/reference
ownership, archive/JObjAddAnim, opcode01/48648 setup, linked/blend/root-motion/
mirrored mapping, general quaternion conversion, or exclusive production
lifecycle. Live Double clone activation remains blocked on those real inputs
and implementations; no production constructor or second clock was enabled.

## Owned AObj lifetime and actual single-joint attachment (2026-11-13)

The next setup slice removes caller-preallocated AObjs and manual JObj binding
assignment from the admitted first-attachment and replacement path. It composes
actual existing owners rather than installing an adapter that pretends setup
occurred. `aobj-lifecycle.ts` follows AObjAlloc `80243f20`, AObjRemove `80243eb0`,
AObjFree `80243f8c` and AObjLoadDesc `80243d88` in `chunk_0070.c:2665–2813`.
`jobj-add-animation.ts` follows single-joint HSD_JObjAddAnim `8024dc04` in
`chunk_0071.c:3971–4054`, with material and shape descriptor arguments fixed null,
as in the actual caller `8004adc8`.

The existing feedback owner now allocates an actual clock record with STOPPED,
frame/rewind/end +0, rate 1, null FObjs and null joint reference +18. These are the
source success-path initialization, using already authenticated archived
`FLOAT_8043d1fc = 1`; no new numeric constant is guessed. The clock factory
stores joint18 on every record; an omitted initial reference defaults to null
for compatibility. Clock interpretation does not inspect that unrelated field.
Physical allocator pool layout, reuse, capacity, counters and OOM are not modeled.

Descriptor loading allocates first, then invokes the existing real
post-allocation loader. Invalid descriptors or later unsupported reference work
retain the allocation and any completed FObj loads/stores. No cleanup is
invented. The delegated descriptor helper retains its existing stricter
writable-descriptor admission checks.

Removal reads the current actual FObj head, calls the real remover when
non-null, then stores fobjs=null. It next consumes joint18, refuses a non-null
reference until real unref exists, stores joint18=null, then releases the actual
identity. The existing FObj remover descends before releasing nodes in reverse
order; malformed descent therefore retains all nodes, rather than inventing
partial releases. Read-only operands are allowed, while each reached pointer
store checks writability. A failed store after release preserves a dangling
pointer, as a failed later stage preserves the source prefix.

Logical free removes the feedback identity and invalidates the clock record.
Retained records reject every later scalar setter, request or interpretation;
getAObj checks live ownership without requiring valid numeric fields. Even a
direct clock free cannot leave a resolvable dead record in the feedback map.
Busy request/interpret lifetimes refuse free before invalidation. Other clock
fields are not erased or validated by free, and no physical freed-RAM behavior
is claimed. Null removal/free/load entry points bypass their work.

The single-joint attachment runtime owns a copied AnimJoint descriptor with
actual aobj08, robj0c and flags10 fields. With a non-null descriptor, it removes
the old attached AObj first, then consumes descriptor aobj08 and loads a new one,
stores the returned identity (including null) into the actual JObj binding,
executes actual first-track12 promotion, handles the admitted RObj branch,
sets/clears JObj flag8 using the real flag helper, then freshly checks flags14
against 0x4020 before any DObj access. A null animation descriptor skips the
attachment stages but still reaches that final DObj gate. A null joint skips all.

RObjAddAnimAll `802578c0` (`chunk_0072.c:639–674`) has a genuine no-op branch when
either target list or descriptor list is null. Both arguments are consumed, but
only both-non-null work refuses. DObjAddAnimAll `8023d838`
(`chunk_0069.c:6241–6294`) has a genuine null-target no-op. A non-null target still
requires traversal even with fixed null descriptors, so that reached domain
explicitly refuses; 0x4020 skips the DObj pointer read entirely. These are source
null branches, not empty effect callbacks. Target-before-descriptor RObj argument
reads are a declared host order where decompiled C does not establish one.

Replacement deliberately does not clear old aobj7c between removal and loading.
If the new load fails, the binding retains the now-invalid old identity. A
read-only attachment destination fails after successful new allocation/loading.
Track-order, RObj, flag and DObj failures retain their respective completed
prefixes. Methods use fixed original receivers, real synchronous effects and
caught-reentry poisoning; unsupported asynchronous returns are rejected after
whatever real work already occurred. Delegated helpers retain their own
existing host admission bounds.

Actual packed integration starts with no preallocated AObj, loads six descriptor
tracks, attaches them to the real joint, executes the existing non-loop setup,
starts a byte-backed bank, performs packed animation/pose capture, and continues
through command/wait completion. Replacement releases the original tracks and
clock, allocates/attaches a distinct graph, and performs subsequent playback by
resolving the replacement identity, not a captured stale first record. A null
AObj descriptor performs real removal and stores null. This is a source-owned
animation lifetime, not the exclusive production actor lifecycle.

Source review checked allocation defaults, removal and attachment ordering,
null branches, stale identities and failure prefixes. Supplementary reference
coverage compares 4,096 actual first/replacement/removal scenarios and 32,762
allocated FObj nodes against independent list-order/flag expectations. This is
synthetic source-contract evidence, not original-game replay.

Remaining production requirements are still real: archive public-index/name/
address lookup and actor bind-pose inputs before `8004adc8`; full opcode01 and
`80048648` dispatch; non-null joint reference load/ref/unref; reached RObj/DObj
attachment; setup transform fallbacks and signed rewind continuation; linked,
blend, root-motion and mirrored mapping; general quaternion conversion; and
exclusive actor reaction/physics/update ownership. No live gameplay constructor,
legacy-field hydration or second animation clock has been enabled. The static
constant evidence remains archived ProgramDB evidence, not newly proven
unchanged retail bytes or NI=1 parity.

## Archive public lookup feeding actual joint setup (2026-11-13)

The next offline prerequisite now performs real public-index/name/address lookup
before actual AObj allocation and attachment. It does not enable opcode01 or
production actor ownership.

`archive-public.ts` implements the bounded results of `8025b178` and
`8025b1b0` (`ghidra-export/chunk_0072.c:3685–3719`). Its copied byte snapshots,
canonical opaque cursors and copied/sealed archive bindings preserve public count
at +0c, data base +20, public table +28 and string table +30. Public entries are
pairs of big-endian 32-bit offsets. Indexed lookup first rejects a signed-negative
index, then checks unsigned count and returns the indexed name pointer. Address
lookup compares NUL-terminated byte names from entry zero and returns the first
matching data address. Consequently, a later public index with a duplicate name
can select an earlier entry's animation. No index-to-descriptor shortcut exists.

The lookup copies the supplied Uint8Array view with native operations, rejects
shared/proxy backing, and never exposes its bytes. Mutating original bytes does
not change lookup. Cursor construction does not read target bytes. A zero public
count ignores even a null/foreign query; missing names never consume the data
base. Readonly input fields work, and missing/accessor/malformed fields fail only
when reached. The uint32 table displacement wraps as source arithmetic does.
Offsets use an explicit unsigned local-coordinate convention with overflow
refusal, not a virtual RAM model or negative-displacement inference. Bytewise
comparison models the equality result, not the aligned-word reads, overreads or
fault ordering of `gnt4_strcmp` at `chunk_0069.c:2586–2650`. Copy, entry and string
budgets are host admission bounds. No archive parse, relocation or original asset
provenance is implied.

`archive-joint-setup.ts` is a named continuation of `8004adc8` after `6f98` and
four global fallback loads, with setup bit1 already selected. `6f98` itself uses
actor signed byte +97 and the global pool (`chunk_0000.c:1501–1506`); this is not
implemented by supplying a decoded pose table. The runtime owns explicit
part+04 → descriptor+0c archive bindings, copied decoded translation entries, and
one-time address-to-actual-AnimJoint hydration bindings. Address registration
checks the archive cursor owner and actual attachment descriptor owner. This is
an explicit object hydration boundary, not parsing original descriptor bytes.

The continuation resolves the archive pointer, consumes all three translations
at the source joint index's 0x30 stride, then tests public count. The reached
out-of-count removal/default-transform branch remains an explicit refusal. For
an in-count index it looks up the name, re-resolves the live part/descriptor
archive pointer for address lookup, then calls real `JObjAddAnim` with fixed-null
material/shape arguments and the existing real attached setup tail. It never
assigns a precomputed AObj identity to the joint. An unresolved non-null address
refuses rather than invent a descriptor. A null public address passes a genuine
null animation descriptor to attachment: that can retain an existing AObj, but
still executes the source DObj gate. Null/missing-track tail fallbacks remain
unsupported, after preceding real effects have occurred.

Methods are captured with original receivers. Own-data records, synchronous
returns, finite exact-f32 decoded translations, source-sized index arithmetic,
local coordinate bounds and caught-reentry poisoning are host constraints.
Later failures do not undo removal, allocation, attachment, flags or completed
tail effects. No second clock, production constructor or legacy activation was
added.

The packed integration starts the new path with a null joint animation and no
caller-created AObj. A two-entry synthetic public table deliberately gives both
entries the same name but different data addresses: entry zero owns six real
FObj tracks, while entry one names an empty animation. Selecting index one must
resolve entry zero, allocate the actual graph and run setup through frame2,
rate2 and duration3. Real stream-bank start then advances frame4, captures pose
translation18, progresses through the accumulator20 command/target24 and finishes
the wait. Repeated archive setup frees the first graph, allocates a new identity
and makes it the current playback owner. A later unsupported rewind continuation
retains its newly allocated replacement and completed LOOP flag, demonstrating
that failure does not repair or resurrect the old animation.

Full opcode01 remains excluded. `8004c298` requires shared per-command starting
frame/override semantics and actual `80048648` dispatch. Even its mode0 target
`8004871c` requires real `4d1f4` descriptor selection, `4d244` metadata, `4a754`
setup, family/shared bank and archive selection, followed by part1 movement
side-effects. Calling the attached tail alone would not satisfy those effects.
Exclusive reaction/physics/update ownership, bind-pose pool selection, archive
parse/hydration, setup transform fallbacks/rewind, references, blend/link/mirror,
general quaternion conversion and original replay/NI1 parity remain open.

Validation: both focused archive suites and actual packed integration pass, as
well as enhanced strict standalone TypeScript, full `verify:contributor` through
the production game build, docs with `GF_ATLAS_SKIP_MODELS=1`, 93 matching tests,
and 83 oracle tests with one expected absent-private-MEM1 skip. The existing
bundle-size warnings remain. All 31 private mutation runners pass, covering 877
selected controls: 842 existing controls unchanged plus 35 archive/front variants.
Only assertions or precisely enumerated valid-path admission failures count;
syntax/build/unrelated errors never count. An independent synthetic reference
checks 8,192 archive tables, 65,521 first-match lookups and 8,192 misses. All prior
allocation, bank, command, wait-record, scalar/scaling and exact-rational
references were rerun successfully. These are source-contract and regression
checks, not original game execution or proof of complete clone gameplay.

## Opcode01 sequencing through actual setup gates (2026-11-13)

The copied-byte parser now admits opcode01 only through the genuine no-op gates
of `80048648`. It is a setup-command foundation, not a completed ready-actor
setup or live gameplay route. The actual shared animation dispatcher owns the
readiness/marker fields. Its new `setupPart(actor, partNumber, blockedSource,
request)` reads family1d88, shared1d8c and, for part 1, the exact marker578==1 AND
marker1db3==1 conjunction. A missing pointer or that conjunction returns void.
Only afterward does it read the live signed blocked byte from the original
stream actor binding, passed by reference. Reached blocked 4a41c and unblocked
setup-table/4871c paths explicitly refuse. No playback call, archive setup or
attached tail stands in for those missing effects. No extra blocked-mask owner,
source clocks, production constructor or legacy activation was introduced.

`startStream` and `parseWaitRecord` accept optional start-frame, transition and
mode arguments. Start forwards them through actual bank resolution and reset;
update continuation explicitly supplies source -1/ffffffff/ffffffff. Public
API defaults match those values for compatibility fixtures only: actual source
callers can supply explicit nonnegative overrides. Arguments are admitted lazily
when opcode01 is reached, so terminal opcode0/opcode10 paths do not inspect unused setup
arguments. Frame is finite exact-f32; integer overrides admit natural signed32
or uint32 representations and retain full bit patterns until source defaulting.

Opcode01 first advances its local cursor by eight. Each invocation begins with
the parser's original frame argument. Negative frame selects signed BE16 +6;
negative signed mode selects unsigned byte +3; negative signed transition then
selects unsigned byte +4. Selected low-four parts are visited in ascending order.
For each, actual target08 is copied to previous0c. Nonzero stream status1d causes
signed prior duration24 to be converted exactly, then added to the actual
accumulator10 with f32 rounding. This is integer conversion, not GQR quantization.
If the handler-local frame is still negative, it becomes f32(actual frame0c +
live timestep1dc8). A nonnegative replacement persists for later selected parts;
a still-negative replacement causes another fallback at the next selected part.
The next opcode01 starts over from the parser argument rather than inheriting
that handler-local replacement.

The real setup gate receives that frame, unsigned group/action bytes +1/+2,
transition and mode. After a synchronous void return, status1d becomes 1 and
actual target08 becomes f32(live accumulator10 + live part frame0c). After all
selected parts, mask value 2 (part 1) clears actor marker71d. The existing stream binding now
owns that byte with an optional zero initial value only for older fixtures.
Finally byte +5 is read. Zero skips the original speed branch; nonzero explicitly
refuses the still-unverified 8043712c conversion, after all prior effects.

A completed opcode01 suppresses the parser's entire terminal fallback loop,
including after subsequent opcode10 commands and when no low-four bit was
selected. Terminal wait installation still follows. Suppression is local to one
parse invocation. Failures preserve prior target/accumulator and earlier-part
writes, but do not invent later status/target/marker/terminal effects. Readonly
operands work; reached stores require writable fields. Overwritten stale fields
are not read. Exact effect prefixes, synchronous contracts and caught reentry
remain explicit host boundaries; no rollback is implied.

The new authenticated fixed-range reader and eight synthetic tests are in
`read_archived_setup_command_evidence.py` and its matching test. The evidence note
`archived-setup-command-2026-11-13.md` preserves hashes and selected instruction
facts from both existing snapshots, with their unchanged-original/live-parity
caveat. It verifies the parser (584 bytes), actual opcode01 extent (396 bytes)
and setup gate (212 bytes), plus the existing dispatch-table entry 1. The decompiler's next
shown function at 4c5fc would imply 868 bytes, but opcode01 actually returns at
4c420; neighboring handlers are deliberately excluded. Instructions prove the
parser saves original f1 and overrides before restoring them for every handler,
while handler f31 persists across selected parts. They also establish signed
duration load before accumulator load, source cursor/default/store ordering,
fallback suppression and the actual setup gates. No constant targets were added;
nonzero byte5 remains unsupported.

Packed integration begins with the real archive-selected six-track graph. A
marker-gated opcode01 completes target/status/marker stores while leaving the
actual clock, request count, callbacks and pose untouched. After unfreezing, the
next parse without opcode01 performs the existing actual fallback, reaching
frame 4, elapsed 9 and pose translation 18 on that same graph. Additional cases show
later opcode10 accumulator changes do not revive suppressed fallback; an earlier
marker-gated part's writes survive a later ready-part refusal; nonzero byte5
refusal retains completed marker and part effects but no terminal install.

This still cannot start normal ready animations from opcode01. Next required
work is actual setup-table targets, mode 0 `4871c`, descriptor lookup `4d1f4`,
metadata `4d244`, ordered mode/frame/link reset and `4a754` mapping; blocked 4a41c,
part 1 movement follow-up and nonzero byte5 also remain absent. Original archive
hydration, actor input selection and exclusive reaction/physics/update ownership
remain separate requirements before live activation.

Verification at this checkpoint: focused dispatch, wait and packed integration
suites and enhanced strict TypeScript pass. The full contributor check passes
through the production build; docs pass with model synchronization deliberately
skipped. Matching-source tests pass 101/101; oracle tests pass 83 with one
expected absent-private-MEM1 skip. Both authenticated snapshot reader runs agree
on instruction and mapping facts. All 32 private mutation runners pass, rejecting
918 controls (877 prior plus 41 opcode01 variants). Four older runners received
only precise anchor/fault updates for the added handler and argument forwarding;
their prior versions are retained. Baselines must pass, and only assertions or
explicitly enumerated valid-path admission failures count, never build errors.
A new independent reference passes 4,096 two-command sequences and 16,384 actual
setup-gate calls, checking original argument reset, per-handler frame reuse,
duration/status/target effects and fallback suppression. All prior archive,
attachment, bank, command, wait-record, scalar/scaling and exact-rational
references were rerun successfully. These are synthetic source-contract and
regression results, not ready setup, original execution or playable-parity proof.

## Descriptor banks and shared setup metadata (2026-11-13)

The next ready-setup prerequisites are implemented as explicit operations, not
as a successful `48648`/`4871c` dispatch. `animation-descriptor-bank.ts` follows
`8004d1f4` over privately copied bytes with canonical owned cursors. It receives
the actual dispatch readiness record and actual stream-start selector record by
reference, preserving single ownership of family1d88, shared1d8c and actor+582.
Group bit 7 selects the shared bank and masks the index to seven bits. Otherwise,
only group zero substitutes the raw default byte, sign-extended before the
family lookup. Signed BE16 displacements are relative to the bank, then to the
selected group. Doubled group and action indexes preserve modulo-32 arithmetic.
A returned cursor need not yet point inside the backing; reads impose bounds.
The 16 MiB copy cap, non-proxy own-data inputs, local coordinate overflow/negative
refusal and lack of virtual RAM wrap are explicit host limits. These bytes are
synthetic inputs, not a retail asset parser or original runtime capture.

`animation-setup-metadata.ts` implements `8004d244` writes against actual existing
part records: mapping owns scaleIndex32 and jointBank33, feedback owns mirror30,
and attached setup owns rewind26 and loop2c. New sidecars contain only previously
unmodeled selectors2a/2b, auxiliary37, actor bytes1d74..1d77/1d94..1d95/1d98/1d99/
1d9b, and descriptor fallback bytes+be/+bf. Descriptor defaults are keyed to an
actual owned actor descriptor; the current actor descriptor pointer is read only
when a negative metadata byte reaches that fallback. No duplicate actor+582,
frame, mirror, loop, rewind, mapping or playback clock is introduced.

Metadata first writes byte0 to actual scaleIndex32. An out-of-range signed
channel returns after that write. Channels 0..3 use their source offsets to write
selector2a, selector2b, the unsigned byte widened into rewind26, and auxiliary37.
The low two flag bits preserve, clear, set or XOR bit0 of actual mirror30; the
preserve branch does not inspect or rewrite it. The flag byte is then reread for
the loop2c store. Channel 1 also writes actor bytes1d98/1d99/1d9b. Channel 0 uses
signed metadata9/10: nonnegative values are retained from the sign-test load,
not read again; negative values read the current descriptor fallback byte. Each
indexed target separately snapshots actual jointBank33. After both stores,
bank33 is reread; bank zero copies the stored actor1d74/1d75 to actor1d94/1d95.
Two-bank host admission rejects unsupported target addressing rather than
inventing RAM aliases. Operands may be readonly, stores require writable own
data, overwritten stale values are not validated, and failure preserves the
completed prefix. Actual getter methods and receivers are captured.

`archived-setup-metadata-2026-11-13.md` and its fixed-range reader preserve the
instruction facts for selector `8004d1f4..8004d244` (80 bytes) and metadata
`8004d244..8004d548` (772 bytes), with ends exclusive. Both authenticated existing
ProgramDB snapshots agree. The metadata instructions correct a misleading
expression in the decompiler: positive metadata9/10 values are retained across
the bank/address calculation, whereas the flag byte is genuinely reread after
mirror effects. The negative branch loads bank33 before descriptor4b0 and the
fallback byte. No new constant or setup-table target was added. Snapshot
agreement remains archived instruction evidence, not unchanged executable or
live-runtime parity proof.

Packed integration resolves a real copied family bank using the existing
stream-start default, applies metadata to the same records used by the existing
owned animation graph, then explicitly runs the already-supported archive
continuation. Clearing metadata's mirror and loop settings allows real graph
replacement; metadata's scale index then makes the next real playback capture
scale translation from 18/28/38 to 36/56/76. Changing the actual stream default
selects a second descriptor and updates the same scale field. A separate loop-bit
case reaches the real unsupported rewind branch after allocation/replacement;
it does not fake success or discard those effects. Metadata application itself
does not tick animation, request frames, attach anything or claim ready setup.

Ready dispatch still requires setup-table/handler ABI evidence, the `4871c`
ordered reset body and `4a754` selection/mapping, including `4d548` archive-table
and tagged descriptor handling. Non-null setup mapping additionally needs the
`4adc8` actor bind-pose/global prefix before the existing archive continuation,
then normal capture/scaling in order. Channel 1's `48648` movement postamble,
blocked setup, nonzero opcode01 speed byte, general missing-track/transform and
loop paths, source asset hydration and exclusive production ownership remain
unsupported. This checkpoint does not add a null-bank-only “playable” claim.

Verification: both new focused suites, packed integration and enhanced strict
TypeScript pass. Full contributor checks pass through production build; docs
pass with model synchronization deliberately skipped. Matching-source tests pass
108/108, oracle tests pass 83 with one expected absent-private-MEM1 skip. Both
authenticated archive reader runs agree. Final read-only source review found no
source-order or shared-ownership blocker. All 33 private mutation runners pass,
rejecting 948 controls (918 prior plus 30 descriptor/metadata variants), with no
prior-runner edits needed. Only semantic assertions or explicitly enumerated
valid-path admission failures count, never build errors. The new independent
reference checks 8,192 actual shared-metadata cases across channels, flag bytes
and banks, plus 8,192 signed-relative descriptor lookups. It uses the actual unit
fixture construction with separate expected-state logic and independently
authored lookup tables. All prior reference suites were rerun successfully.
These are source-contract regressions, not ready dispatch or gameplay proof.

## Bounded non-null ready mode0 setup (2026-11-13)

The source-owned path can now execute an admitted **ready** opcode01 through
actual mode0 setup, non-null archive selection, allocation/attachment, pose
capture and subsequent stream-wait playback. This is synthetic decoded-input
integration, not exclusive production activation or complete gameplay parity.

Instruction inspection corrected an earlier decompiler-based prerequisite.
`4adc8` does not load four globals before an in-count setup. They belong only to
the out-of-count reset/transform branch. It calls `6f98`, reads part+4 and wrapper+c,
snapshots public count, reads pose X and Y, compares unsigned count/index, reads
pose Z, then branches. The archive helper now snapshots count before poses.
Previous statements requiring four initial global loads or a count load after
poses are superseded by `archived-ready-setup-2026-11-13.md`. This correction
removes an invented dependency without bypassing any reached source effect.

`archive-joint-setup` now optionally owns a live actor byte97 binding, validated
against the actual mapping actor. A once-bound copied pose pool supplies complete
65-matrix blocks. `setupActorJoint` sign-extends byte97 and computes source address
`803bb4c0 + signedByte * c30` modulo32 before resolving its owned block. The bounded
pool covers nonnegative slots; negative selectors still compute the right address
and then refuse an unowned region. Cross-slot addressing is explicitly outside
the decoded host model. Count and pose reads, saved first archive for name lookup,
reloaded part/wrapper for address lookup, actual JObjAddAnim and attached tail all
retain source order. The explicit post-prefix method remains available. Reached
null descriptor04 refuses on dereference, not at the earlier table store.

`animation-archive-bank` models admitted decoded, untagged pointer tables. Owned
canonical table cursors permit a signed selector2b displacement from a shifted
group base. Tables are copied/sealed but their cells remain live. `4d548` reads
actual mapping descriptor00; null returns -1 without consuming metadata or
part+4. Otherwise it reads selector2a once, masks to seven bits and retains the
group pointer. Missing group uses the initial bank's first group/first slot.
Existing group uses signed selector2b, stores actual descriptor04, rereads it for
null, and on null rereads actual descriptor00 before fallback. Both paths reload
descriptor04 before admitted owned-wrapper validation. Null is a legal untagged
zero here; later setup owns its refusal. Tagged or unhydrated pointers are outside
this decoded-pointer admission, with no fake tag stripping, allocation or parse.
Earlier stores survive refusal.

`actor-animation-setup` composes real `4871c` and `4a754`. It retains actual
readiness/default-selector, metadata, feedback, dispatch and mapping records.
New sidecars own only source fields that had no prior owner: actor animation
banks1d78/1d7c and movement6d8; part group28/action29/bank31/status38 and floats
18/1c/20. It snapshots ABI arguments, resolves the descriptor before part writes,
stamps group/action, then calls real metadata. Mode0 writes bank31, mode2f, floats
20/18/1c, linked36, previous10, previous14, elapsed08 and frame0c in audited order.
The first numeric frame admission is at the reached frame store, preserving prior
writes on failure. Transition is unused by mode0. Existing archived constants
prove +0 and +1; no new constant value was inferred.

The `4a754` continuation stores poseBuffer35 once, selects actual family/shared
animation bank by bank31 into descriptor00, clears complete2e, calls actual
archive resolution, stores status38 as the returned low byte, and latches
completion for nonzero status. New `mapPreparedPart` runs the original signed
range/map loop without duplicating the initial selector store. Mapping has an
optional once-bound real archive setup runtime; setup bit1 takes precedence over
advance bit2, then actual capture and translation scaling follow. There is no
extra playback tick, setup-result cache or replacement clock. Repeated map entries
repeat allocation/replacement and capture just as the source loop requires.

The existing dispatcher can once-bind the real setup runtime after constructing
its dependencies. Authenticated slot0 at `802d0d70` is `8004871c`; only mode0 is
admitted. No-op readiness gates and blocked-mask ordering remain unchanged. Other
modes and blocked `4a41c` refuse. For part1, a completed real setup is followed by
the actual movement6d8 = 1 store, then an explicit refusal at the unimplemented
`4d08c` call. No caller status/target/marker/terminal continuation is fabricated
past that refusal. Captured methods, original receivers, synchronous effects and
caught reentry are enforced at the dispatch/setup boundaries.

Packed integration starts with a genuinely removed old graph. A ready mode0
opcode01 selects the non-null decoded archive, resolves byte97's owned pose block,
allocates and attaches six real tracks, requests frame2, captures translation
14/24/34, resets elapsed to zero and installs the terminal wait. No terminal
fallback tick occurs. The next source wait progression advances that graph once
to frame4, elapsed2 and translation18/28/38; final stop does not tick again.
Repeating the command frees and replaces the graph. Additional cases cover
negative command-frame resolution, repeated map entries, actual archive fallback,
status-store failure before attachment, captured setup methods, asynchronous and
caught-reentry refusal after completed setup, and part1's preserved-effect stop.

Remaining production requirements include tagged archive parsing/hydration,
nonzero opcode01 speed conversion, other setup modes and blocked setup, part1
movement follow-up, root/mirrored and general quaternion paths, transform and
missing-track/loop fallbacks, original replay/NI1 parity, and exclusive actor
reaction/physics/update ownership. The live bridge remains unchanged. No denied
publication, rig inspection, source transfer or original runtime action was used.

Validation: focused units and composed packed integration pass, as does enhanced
strict TypeScript with exact optional fields, unchecked-index and unused checks.
The full contributor aggregate passes through the production game build; docs
pass with model synchronization intentionally skipped. Matching tests pass
116/116; oracle tests pass 83 with one expected absent-private-MEM1 skip. Both
authenticated archive snapshots agree on all six selected text ranges and slot0.
Final independent source review found no blocker in the admitted path.

All 34 private mutation runners pass, rejecting 992 controls (948 prior plus
44 ready setup/archive/mapping variants). Three prior runner anchors were adapted
to the shared mapping refactor or newly added dispatch branches; previous runner
versions are retained. Only assertions or enumerated valid-path admission
failures count, never syntax/build/unrelated errors. One new mutation exposed a
missing ABI-snapshot assertion for previous14; the implementation was already
correct and the test now checks that field as well. The new independent reference
passes 1,024 actual composed ready-command cases with repeated replacement,
covering frames, rates, primary/fallback archive routes and repeated map entries.
All prior reference and rational-review suites were rerun successfully. These
are synthetic source-contract checks, not original execution or playable-clone
certification.

## Real part1 movement follow-up (2026-11-13)

Ready mode0 opcode01 can now finish part1 through the actual `4d08c` step-height
calculation, rather than stopping after movement6d8 = 1. This completes the
admitted setup continuation; it does not enable the live bridge or supply
missing production assets, actor lifecycle or collision ownership.

`actor-movement-followup` binds an explicitly supplied real `RomActor` to its
existing mapping symbol. It retains that object, the real mapping descriptor4b0,
the real stream marker71d and setup movement6d8 records. It writes the actual
`RomActor.stepHeight` field at +6d0, reads the existing borgNumber high byte,
controlWord, modelScale and position.y, and does not copy those fields into a
parallel actor. Duplicate object/symbol associations refuse. New storage covers
only previously unowned byte661, floats66c/670, descriptor bytes+f/+22/+2a/+32/+3a
and explicitly decoded world-matrix Ys. These Ys mean actor+8f0+j*30; neither
captured local pose translation nor renderer-authored partAimAnchors substitutes
for those matrices. Absent and negative matrix regions refuse when reached.
Direct binding is a host identity association, not original asset hydration.

The archived instruction audit in `archived-movement-followup-2026-11-13.md`
corrects several decompiler traps:

- Ordered short circuits inspect family byte3e8 == 5, byte661 != 0, then
  control5e0 bit40 clear. Any true path stores +0 to6d0 and returns without
  consuming marker, descriptor, world matrices or normal-path constants.
- The nonzero marker branch sign-extends marker71d and evaluates the source
  products with authenticated5.0 and actual model scale. It runs before opcode01
  clears that same marker, not from a copied or already-cleared value.
- The normal path retains the first descriptor's list pointer, snapshots670
  before920, stores920 to6d0, reads66c and reloads6d0. The `fnmsubs` result is
  fused-rounded and then negated, preserving its signed-zero behavior.
- The root clamp reloads descriptor4b0, reads position.y, signed descriptor+f,
  then6d0 before the indexed world matrix. `fsubs` precedes `fmadds` and a strict
  comparison. The four-entry list retains the initial descriptor, uses the
  entry-time670 snapshot, and stops at signed-1 without consuming later bytes.
- The tail reloads6d0 and position.y, stores the difference, then reads6d8 before
  reloading6d0. It computes `.7f * movement6d8` before multiplying the difference,
  contrary to the decompiled association. A negative result clamps to+0; -0 is
  not negative and survives.

Finite exact-f32 operands with RN00/NI0 remain explicit host bounds. Existing
integer-exact fused helpers provide the source fused operations; products round
once after an exactly representable binary64 product. Unsupported/nonfinite
operands refuse without rolling back earlier stores. Methods and receivers are
captured, readonly operands are allowed, destination writability is checked at
reached stores, and caught same-runtime reentry poisons the operation.

`actor-animation-setup.bindMovementRuntime` is once-bound. `finishPartOneSetup`
retains its original6d8=1 store and then invokes the actual follow-up. Missing
binding keeps the previous explicit4d08c refusal. It cannot turn a missing
calculation into success, skip the store, accept deferred effects or run the
host physics/legacy stream VM. The dispatcher and parser continue only after
this actual call succeeds.

Packed integration now covers real archive attachment and part1 completion on
all three movement branches. Early-zero setup resets actual stepHeight and then
allows command status, target, marker-clear and terminal-pointer stores. The
marker case consumes9 with modelScale2 to produce80 before the caller clears9.
The normal case uses separate decoded world matrices to compute its clamp while
the captured local pose remains24. Repeating setup replaces the actual graph and
rereads live position/matrices. Later wait playback advances once without
replaying setup or changing host yVel or the legacy synthetic frameClock.
Readonly stepHeight failure retains completed attachment and6d8 while refusing
all later parser continuation. The former unbound part1 refusal test remains.

### Production hydration and exclusive ownership findings

A read-only inspection confirmed that a Battle activation flag is not the next
missing input. `actionStreamTables.json` identifies Double's family/shared bank
addresses, but `meleeAnimKinds.json` contains lossy event summaries, not original
program bytes. `animMetadataHop.generated.json` preserves only the part0 motion
mapping from metadata+4/+5, not full signed-relative directory bytes or other
parts. The exported pl0003 model has 35 nodes and 14 skins with no source-runtime
metadata; 56 baked clips are presentation samples. `user-data/` is absent in this
checkout. No original asset was obtained, uploaded or inferred from baked poses.

The smallest useful next boundary is a bounded hydrator for one already-supplied
HSD DAT animation blob. Parse its header, data block, relocation/public tables
and strings with bounds, preserving relocated offset-zero versus null identity.
Decode actual AnimJoint/AObjDesc/FObjDesc records and retain original FObj bytes,
then construct existing archive-public, FObj descriptor, AObj descriptor,
JObj-add-animation and archive-joint-setup owners. Actual public lookup,
attachment, request and playback must consume those owners. Pre-hydrated input
must not masquerade as executing the still-unsupported tagged4d548 parse branch.
A synthetic byte fixture can validate this parser boundary, but original-input
validation remains unavailable locally.

Beyond hydration, the admitted packed fixture still has one JObj, positive-zero
Euler conversion and only eligible FObj opcodes1/2/6. Reached DObj attachment,
root/mirrored mapping and other interpolation/transform paths remain unsupported.
Full family/shared program and metadata banks, JObj graph/flags, map boundaries,
scale tables, bind poses, actor input/eligibility state and actual matrix update
ownership cannot be reconstructed from current presentation assets.

Battle.step already owns position history, status, ammo, invincibility, gauges
and reactions before bridge.tick. Source ownership must be selected before those
writes, not installed as another bridge or renderer tick. Collision-time reaction
entry stays distinct from the actor sweep. The fixed simulation clock is
main.ts's stepSimOnce, not BattleScene.update. Reaction62/death63 remain no-op
state-table entries and stepRomActor is not the complete lifecycle. Presentation
also needs an explicit source pose path that suppresses baked mixer fallback.
No source activation, partial-state fallback, duplicate clock or claim of
playable-clone completion is introduced here.

Validation: final focused tests, enhanced strict TypeScript and the full
contributor aggregate pass through the production game build. Docs pass with
model synchronization intentionally skipped. Matching tests pass 128/128; oracle
tests pass 83 with one expected absent-private-MEM1 skip. Both authenticated
movement reader reports agree. Independent read-only source review found no
blocking order, arithmetic or shared-ownership discrepancy.

All 35 private mutation runners pass, rejecting 1,030 variants, including 38 new
movement/follow-up controls. A prior ready-setup mutation anchor was narrowed to
the new missing-binding condition; its earlier version is preserved. Only
assertions or exact enumerated valid-path admission failures count, never build
or unrelated failures. A source-copy regression assertion now checks external
array mutation before deliberately changing the owned copy. The independent
reference passes 8,192 composed part1 commands: 1,207 gated-zero, 3,492 signed-marker
and 3,493 normal world-matrix cases. It uses small dyadic inputs and separately
written expected-state logic, not the production fused helper as its oracle.
Focused tests additionally check fused subnormal and signed-zero witnesses and
the distinguishable tail multiplication order. All prior independent reference
and rational-review suites were rerun. These checks do not establish NI1,
original-execution parity or production readiness.

## Bounded DAT bytes into actual animation owners (2026-11-13)

`animation-archive-hydration.ts` now imports an explicitly supplied bare HSD DAT
into the existing archive-public, FObj data/descriptor, allocated AObj descriptor,
JObj-add-animation and archive-joint-setup owners. It accepts explicit public
indices for leaf AnimJoint roots. Header, relocation/public/string regions,
reachable descriptor fields and original packed-stream spans are checked before
any factory call. The source layout and narrower host contract are documented in
`animation-dat-hydration-contract-2026-11-13.md`.

Relocated raw zero denotes data+0; unrelocated pointer zero is null. Public
ordering, first-name match semantics, same-address descriptors, shared FObj
suffixes and exact packed-data starts retain identity. A shared data start uses
one actual data base sized to the maximum declared length, while each FObj keeps
its own length. Different overlapping starts use bounded separate immutable
copies, not a claim of physical RAM aliases. Typed views are copied by their
actual bounds; factory callbacks cannot mutate the private archive used for
later stream extraction. Methods retain their original receivers, calls must
return synchronous owned identities, and caught reentry refuses. A late factory
failure retains completed owner effects rather than inventing rollback.

This importer has a 16MiB ceiling and count/string/descriptor/aggregate stream
budgets. It refuses external references, non-leaf AnimJoints, RObj animation,
AObj joint references, cycles, record-type/extent conflicts, scalar or packed
relocations, and out-of-bounds pointers. Finite start values outside the actual
loader's signed16-integral domain are deliberately left to that loader. The
importer never decodes or re-encodes packed FObj bytes or substitutes baked poses.
These are host admission limits, not retail ArchiveParse fault or effect order.

The composed part1 test now builds an independent six-track DAT fixture and
passes its actual wrapper through archive-bank selection, public name/address
lookup, attachment, source request/playback, pose capture and movement follow-up.
Distinct stream bytes produce translation17/27/37 at frame2, then23/33/43 at
frame4. The original input is overwritten after hydration. Repeated setup
replaces the real AObj/FObj lifetime; malformed reimport leaves the current graph
untouched, while a separately imported valid archive can replace it and produce
a new pose. Host yVel and the old synthetic frame clock do not advance. Unit
coverage also checks two distinct AObjs sharing a FObj suffix and independent
runtime allocation/replacement despite shared immutable descriptors.

This removes the handwritten-descriptor requirement within the admitted leaf
input domain. It does not provide original DAT assets or validate real MOT
container padding/root selection. Full tree/model graph hydration, source
program/metadata bank bytes, tagged4d548 allocation/cache, wider interpolation
and transforms, exclusive Battle lifecycle/reaction/physics ownership and source
pose presentation remain unfinished. No production activation or playable-clone
claim is introduced.

Validation: focused integration and enhanced strict TypeScript pass. The full
contributor aggregate passes through the production game build; docs pass with
model synchronization intentionally skipped. Matching tests pass 128/128; oracle
tests pass 83 with one expected absent-private-MEM1 skip. Read-only source review
found no remaining blocking format or ownership discrepancy.

All 36 private mutation runners pass, rejecting 1,073 variants including 43 new
DAT controls. Only assertions or exact enumerated valid-path admission failures
count, never syntax/build or unrelated failures. Extra descriptor-flag and
archive-layout assertions close cases where downstream defaults could otherwise
hide a lost field. No existing mutation runner needed modification. The new
independent reference passes 4,096 separately authored DAT layouts and actual
part1 setups, varying relocated offsets, relocation order, duplicate names,
reserved/padding bytes, duration and packed fractional formats. It overwrites
input bytes after import and checks separately computed poses and repeated
replacement. All previous independent reference and rational-review suites pass
again. These synthetic checks do not establish original-input, NI1 or live
production parity.

## Preserve display owners during joint setup (2026-11-13)

The actual single-JObj caller supplies null material and shape descriptors.
`HSD_DObjAddAnimAll` still walks the target DObj list, but both nested helpers
return immediately for those null descriptors. In particular, the misleading
`PObjRemoveAnimAll` export name does not justify removing an existing animation.
`display-null-animation-attachment-2026-11-13.md` records the exact guards and
source order.

`display-animation-attachment.ts` now consumes the existing DObj owner records
in PObj-link, MObj-link, next-DObj order. It resolves no nested PObj/MObj objects,
loads no descriptor, changes no display binding and performs no animation tick.
Consumed fields are read-only own-data admission; unrelated AObj/callback fields
are never inspected. Captured getter/receiver, finite visits, cycles, synchronous
records and caught-reentry checks are host bounds. No non-null descriptor route
is invented. JObjAddAnim uses this optional actual owner after reloading its
final flags and display binding; a missing owner retains the explicit refusal.
Null AnimJoint still reaches the display tail, and flags0x4020 still skip it.
Completed joint removal/allocation/stores survive a later display-list failure.

The packed DAT/opcode01 composition now shares real DObj/PObj/MObj/TObj owners
between attachment, request and animation dispatch. Two display objects retain
all seven existing display AObj identities and their decoder ownership while
joint AObj replacement proceeds. The PObj/MObj/DObj clocks remain stopped. One
material's actual packed texture stream and scalar receiver continue from
frame1/translation12 to frame2/14 and frame3/16 across setup, source wait and
repeated setup. No texture reset or display cleanup is substituted. A later
explicit material/shape/texture request reaches these same retained identities;
DObj's own AObj is correctly not requested. Null attachment and terminal source
stop do not add a tick. Late invalid DObj traversal retains the new joint AObj
but stops before request/playback. Both display-gate bits skip the actual list
through attachment, request and playback.

This admits display-bearing setup targets in the supported null-descriptor
route. It does not hydrate model geometry or original JObj graphs, implement
non-null material/shape attachment, supply arbitrary display receivers, or
activate the production Battle loop. Full source program/metadata inputs,
source-pose presentation and exclusive lifecycle/reaction/physics ownership
remain unfinished. No original asset, source transfer or remote publication was
needed or attempted.

Validation: final focused integration, enhanced strict TypeScript and the full
contributor aggregate pass through production build. Docs pass with model
synchronization intentionally skipped. Matching tests pass 128/128; oracle
passes 83 with one expected absent-private-MEM1 skip. Independent read-only
source and composition review found no blocking discrepancy.

All 37 private mutation runners pass, rejecting 1,099 variants, including 26 new
display attachment controls. The older owned-attachment runner's two changed
conditional anchors were updated; its prior version is preserved. Only
assertions or exact enumerated valid-path admission errors count, never syntax,
build or unrelated failures. The independent display reference passes 6,144
actual DAT ready setups with separately computed texture state and preservation
checks: 2,100 display playback passes and 4,044 source-gated/absent-list skips.
It varies display-list length, stopped clock states, gate bits, packed values
and fractional formats across repeated setup. All earlier reference and
rational-review suites pass again. No original-runtime, model hydration or live
production claim follows from these synthetic checks.

## Bounded model DAT transform ownership (2026-11-13)

`jobj-model-hydration.ts` imports one explicitly selected bare DAT model public
into the existing JObj animation/scalar owners. This is an initial-transform and
topology projection, not the complete source JObj layout: even a null descriptor
matrix still leaves source live-matrix initialization unimplemented. The source
contract is recorded in `jobj-model-hydration-2026-11-13.md`.

The importer preflights copied bytes, DAT geometry/public names/relocations and
the complete admitted graph before owner factories. It preserves the distinction
between relocated offset zero and a null pointer. The selected root's own next
is source-ignored; children and their siblings form the actual owned graph.
Rotation, scale and translation copy as finite f32, including signed zero and
subnormals. Initialization adds flag0x40; each parent's summary includes the
completed child subtree's `(flags | flags << 10) & 0x70000000`. Runtime parent,
child and sibling links are actual owner identities, never descriptor pointers.
A repeated descriptor is an explicit bounded refusal, not a falsely shared
runtime object; retail ordinary repeated occurrences would allocate separately.

Custom classes, instances, quaternion mode, non-null DObj/RObj/matrix payloads,
external references, overlaps and scalar relocations refuse. Null display-mode
payloads preserve their flags. Finite node/depth/byte budgets, synchronous
captured adapters, record stability and caught-reentry validation are host
limits. The 4,096-deep test uses iterative traversal and flag propagation.
Failures after factory entry retain completed allocations/writes. Metadata is
frozen; real transform and binding records retain their existing mutability.
No callback, geometry, AObj or actor bank is fabricated by the importer.

Actual integration composes independently authored model and animation DATs
with the existing source descriptor banks, metadata, opcode01, ready part1
setup, single-joint attachment, packed callbacks, actor pose capture and movement
follow-up. The actor's bank explicitly selects the model descriptor at data+40,
not model traversal order. Its root, sibling and grandchild retain their own
transforms and null animations while the selected child receives frame2 pose
17/27/37, then source wait frame4 pose23/33/43. Terminal stop adds no tick;
repeated setup replaces the AObj while retaining model identity and parent
links. Original input buffers are overwritten after import. Failed reimport
leaves existing owners untouched; successful reimport creates fresh joints and
does not silently rebind an actor. The imported graph is also consumed by the
real dirty-subtree receiver. Host yVel and legacy part frameClock remain fixed.

The independent reference generates 4,096 differently ordered, relocated,
variable-size model trees containing 36,884 actual owned joints. It computes
parent/sibling relationships, bottom-up flags and exact transform expectations
separately, then exercises actual packed setup, wait, terminal stop and repeated
replacement on the explicitly selected joint. These are synthetic source
contracts, not original-model evidence or live playability. Geometry/skinning,
world matrices, complete source inputs, actor-model mapping provenance and
exclusive production lifecycle/reaction/physics ownership remain unfinished.

Focused integration, enhanced strict TypeScript, independent source review and
the full contributor aggregate pass through production build. Docs pass with
model synchronization intentionally skipped. Matching tests pass 128/128;
oracle passes 83 with one expected absent-private-MEM1 skip. All 38 private
mutation runners pass, rejecting 1,144 variants, including 45 new model controls
for fields, topology, flags, admission, receivers, reentry and output mutability.
Only assertions or exactly enumerated valid-input admission errors count.
All 14 reference suites and both rational reviews pass. The existing ready-setup
reference was adapted to the new optional model-fixture parameter while keeping
all 1,024 frame/rate/fallback/repeated-map scenarios; its prior version is
preserved. No runtime changes followed the successful contributor aggregate.

## Explicit actor joint matrices and retained consumers (2026-11-13)

The actual game matrix path is `46698/465fc →46754 →46bd0 →4679c →46dd4`,
not HSD JObjMakeMatrix. It consumes bank-zero captured actor pose fields and a
separate actor topology. Rendering later copies actor matrices into JObj+44.
Setup 48648 captures pose and immediately calls movement 4d08c without rebuilding
matrices between them. A new matrix calculation inside that follow-up would
change source ordering. `jobj-world-matrix-integration-2026-11-13.md` records
these distinctions and the special joint 1 translation/pre-rotation branch.

`actor-joint-matrix.ts` implements an explicit bounded 46dd4 callee boundary:
caller-resolved parent matrix, actual feedback pose, correction shorts and a
separate actor scale vector. It owns sealed 12-float matrices. The quaternion
domain is exactly (+0,+0,+0,1); correction shorts must be zero, which selects the
real 45838 Copy path rather than a trig approximation. Arbitrary quaternion
reciprocal estimates, rotation angles, actor topology and root generation remain
unsupported. This callee input demonstration is not the special joint 1 caller.

The archived evidence reader authenticates both existing ProgramDB snapshots,
five fixed instruction spans and four constants. It emits derived instruction
facts, not raw ranges. Concat performs multiply then two fused additions, with
an additional (+0,1) translation pair in columns 2/3. It snapshots both inputs
before writes and preserves the actual paired-store order, including aliasing.
Identity-quaternion output contains negative zero at indices 6/8. Zero-correction
Copy is pairwise; scale inputs load X/Y/Z. Finite f32 RN=00/NI=0 and GQR0
floating-point load/store types are explicit host preconditions, not newly
observed console state. Host overflow refusal does not emulate source FP faults.

Movement can now bind actual full-matrix identities through a captured owner.
Each reached Y load reads element 7 of that same owned matrix. No second Y table,
implicit recompute or new clock is introduced. The earlier explicit decoded-Y
binding remains available, but an actor cannot bind both. Getter ownership and
record stability, source read order, early gates, read-only inputs and caught
reentry are checked. Source stores before a later failure remain visible.

Actual integration uses the two DAT imports, source setup/packed playback and
bank-zero capture before the explicit matrix call. A supplied parent with scale
2/3/4 and translation 100/200/300 combines pose 17/27/37 into world translation
134/281/448. Separate scale 1/2/1 changes the basis, not translation. Packed wait
advances pose to 23/33/43 without changing that matrix. The next setup recaptures
pose 17/27/37 but movement consumes retained Y 281. A later explicit helper call
produces 146/299/472; subsequent setup consumes retained Y 299 even though its new
local pose Y is 27. Other pose-bank writes do not change the selected bank-zero
input. Unsupported correction leaves the completed first concat, without the
later scale. Host vertical velocity and legacy frameClock remain unchanged.

The independent small-dyadic reference covers 4,096 actual DAT/pose scenarios,
8,192 independently calculated full matrix results and retained-matrix movement
consumers, plus 128 partial-prefix and parent/destination-alias cases. Its scalar
products/sums fit exactly in binary64 before explicit f32 rounding; it imports
no source arithmetic helpers. Unit coverage also discriminates fused cancellation
and signed-zero behavior that simplified matrix multiplication would lose.

Full actor topology hydration, special joint 1 caller resolution, nonzero-angle
and general quaternion paths, root generation, terrain/IK second pass, source
pose presentation and exclusive production lifecycle remain unfinished. No
original inputs, remote execution, capture or publication was needed.

Focused execution, enhanced strict TypeScript, the full contributor build and
both snapshot evidence checks passed. Docs passed with model synchronization
skipped. Matching tools passed 143 tests; oracle tests passed 83 with one expected
private-input skip. All 39 mutation runners rejected 1,178 variants, including
34 new matrix controls. All 15 independent reference suites and both rational
reviews passed. Mutation checks count assertions or explicitly enumerated
valid-input admission failures, never build errors. Three older ready-setup
mutants now encounter the new quaternion guard before their earlier assertion;
the exact new diagnostic is admitted only for those cases, and the previous
runner is preserved. These remain synthetic source-contract checks, not an
original-game replay or a playable-clone result.

## Explicit first-pass actor traversal (2026-11-13)

`actor-world-matrix.ts` now composes the real bounded first-pass caller:
`46698 →46754 →46bd0(mode 0) →4679c`. It shares the actual matrix owner with
movement and uses the mapping owner's bank-zero captured poses. Actor position,
body pitch, heading and movement height stay in the original RomActor. Missing
source fields, four-byte topology rows, correction shorts and scales have
explicit owned storage. This hierarchy is separate from the imported JObj tree.

The caller preserves its early mode-2 return, special translation preparation,
root generation, both root copies and the separate lifted copy. `46754` adds
captured joint-1 translation and its offset, storing XY before loading Z; its
alternate flag path writes only the authenticated Y value 20. Root correction
uses signed-short loads and wraps the conditional yaw sum to 16 bits before
admission. Root scale is a real Concat. Only copy `1aa4[7]` receives the previous
movement height; the root and `114` copy remain unchanged.

Traversal preserves the source's recursive branch with the incoming parent,
then its continuation with the current joint as parent. Disabled joints retain
their matrices but still traverse both links, so a child can consume a retained
disabled-parent matrix. Negative signed-byte links terminate. Repeated nodes
repeat the work. The 32-joint domain and iterative visit budget are explicit
host bounds, not newly inferred source topology or cycle rejection rules.

Joint 1 now takes its actual special path: mandatory Z, X and Y wrappers into
scratch storage, then the same quaternion/correction/scale helper with `1d54`
as an explicit translation override. Captured pose translation is not rewritten
to impersonate that field. Ordinary joints consume their own bank-zero poses.
The primitive owner exposes source Identity, TransApply, Copy, zero-short
correction, Scale/Concat and zero-short axis wrappers. Even unit scales and
zero rotations execute their audited Concats, including signed-zero effects.

`read_archived_actor_traversal_evidence.py` authenticates 16 fixed instruction
spans and seven constants in both existing ProgramDB snapshots. Its 26 synthetic
tests cover decoding and admission. Zero-angle sin returns +0 through its early
branch; cos returns authenticated 1.0. Paired RotTrig stores give X a -0 at index
6, Y at index 8 and Z at index 1. The exported C loses these paired-lane facts
and is wrong at several Y/Z entries. Instruction evidence, not the simplified
expressions, determines the implementation. RN=00/NI=0, raw floating GQR0,
signed16/scale-zero GQR5 and the recorded SDA2 basis remain explicit assumptions.

The actual DAT/packed-animation integration now generates its parent instead
of supplying it. Root position 100/2/300 and scale 2/3/4 combine captured pose
17/27/37 plus offset 3/4/5 into world translation 140/95/468. The separate joint
scale changes its basis to 2/6/4. A wait changes captured pose to 23/33/43 without
refreshing matrices. Setup subsequently reads retained Y 95. A later explicit
caller produces 152/113/492; the following setup reads retained Y 113. Alternate
flags preserve prior special X/Z while setting Y to 20. Root copies preserve
prior movement height, and neither host vertical velocity nor the legacy
animation clock advances.

The independent dyadic reference covers 4,096 actual DAT/setup contexts and
8,192 complete first-pass operations, comparing all four full matrix outputs,
flag/disabled paths, yaw cancellation, retained movement consumption and 64
early gates with invalid unused inputs. Unit fixtures additionally cover real
multi-branch owner graphs, repeated nodes, inactive parents, high mask bits,
late store/load failures, ownership, captured methods and reentry.

This is an explicit callee operation, not an enabled production mode. The normal
`54070` route calls `465fc`, including terrain, corrected traversal and further
callbacks; `46698` cannot replace it. Other source callsites refresh matrices
again during action/collision processing, so per-frame deduplication is also
incorrect. `actor-matrix-production-routing-2026-11-13.md` records those exact
calls and the remaining constructor/lifecycle/presentation gaps. No fallback,
automatic setup refresh, additional clock or live routing switch was added.

Focused integration, enhanced strict checking, both authenticated readers and
the 4,096-context reference passed. Full contributor verification and production
build passed; docs passed with model synchronization skipped. Matching tools
passed 169 tests; oracle tests passed 83 with one expected private-input skip.
All 40 mutation runners rejected 1,223 variants, including 45 new traversal
controls. All 16 independent reference suites and both rational reviews passed.
Checks admit assertions or exact enumerated valid-input admission failures,
never syntax/build failures. The prior 34-control matrix runner is preserved;
its anchors were updated for the shared primitive extraction without dropping
cases. These remain synthetic source-contract results, not original-game replay.

## Bounded normal matrix update and linked receiver (2026-11-13)

`actor-matrix-update.ts` adds an explicitly invoked normal `800465fc` caller
using the existing mapping, metadata, movement, world and matrix owners. It
executes one preparation, a first traversal, the reached real damping and
corrected traversal, sequential postprocess guards and the final linked-actor
matrix copy. It does not install a Battle hook or become another clock.

The previously missing fields `1d96`, `1d97`, `1d60`, `660` and `4a4` have one
controller-owned record. Corrected traversal references this actual record.
`RomActor.controlWord`, `visibilityBit`, optional `flyer741`, actual movement
`byte661`, setup metadata `byte1d98`, mapping descriptor/count and all matrices
remain in their existing owners. Global `D2` is a required shared record,
retained by reference; there is no guessed default or per-update copy.

The source branch is now backed by two independently authenticated existing
ProgramDB snapshots. New fixed-span evidence covers six routines, the exact
16-word address window reachable by the dispatch mask and the float32 damping
constant `3f4ccccd` (0.800000011920929). This window is not evidence of a
separately allocated semantic sixteen-entry terrain table. Its other targets
remain explicit refusals. The new reader has 22 passing synthetic checks and
no arbitrary-address option; it reports derived facts rather than raw ranges.
See `normal-actor-matrix-evidence-2026-11-13.md` for hashes and reproducibility.

Specific source behavior:

- Initial `4a0==2` skips all work. Otherwise `46754` prepares translation once
  and `46bd0(mode0)` really builds root, copies and traversal output.
- Only then does the actual movement `661` decide whether to clear `1d96`
  followed by `1d97`, read the control word and dispatch. Suppression bit
  `0x20000000` calls `46ef4` directly. Unsuppressed selector `1d98&15==1`
  genuinely selects that same routine. Both load the mapping descriptor
  pointer to form `+22`; damping does not dereference descriptor bytes.
  Suppression skips metadata; the other path reads metadata before descriptor.
- Real `46ef4` multiplies and stores `1d60` with one binary32 rounding. It does
  not add drift to prepared Y. `46bd0(mode1)` actually rebuilds root and visits
  `46914`. Reached signed counts 0 or raw128–255 skip their respective scans;
  positive scans refuse after completed root/prior-node work. Disabled nodes
  still traverse their links but do not read correction counts.
- Source visibility intersects the current shared `D2` byte. When the
  intersection is zero, `47904` returns sequentially for explicit nonzero
  `flyer741`, nonzero `660`, or metadata high nibble `0x10`. Otherwise the
  unsupported active body refuses before lifecycle/short writes. No guard
  is replaced by an ignored effect, and unused later fields are not read.
- Final `4a0==1` loads the actual link and runs `47a2c`. Each loop condition
  reloads the signed source joint count. Target mode/count do not apply.
  Nonpositive counts perform no target lookup; positive iterations copy only
  world slots with the real pairwise matrix primitive. Late failures retain
  earlier matrices and the current matrix's completed store prefix.

The field review also identified a genuine shared short: `18d4 + 1*6 == 18da`,
which is existing `RomActor.steerYaw`. Joint1's X correction now uses that
actual BAM16 value, read after the first pose concatenation. Joint1's stored
correction record owns only Y/Z and ignores caller X. New `composePose` shares
the original quaternion/translation/first-Concat implementation with
`composeJoint`; correction and scale remain real later stages. This preserves
failure timing without rewriting pose or silently copying steering state.

Actual integration now begins from synthetic model DAT and animation DAT,
source bank/opcode01 setup, AObj replacement and captured bank-zero poses.
A second genuine actor shares the same world/matrix owners but has its own
slots, pose and cached root storage. Its mode2 and count0 deliberately do not
block the source-count-driven receiver copy. No target controller, movement
or metadata binding is fabricated to make copying work.

Captured17/27/37 plus offset3/4/5, source position100/2/300 and scale2/3/4
produce world140/95/468; normal damping changes10 to8 without changing
prepared translation. Wait changes the actual pose to23/33/43 while both
actors' matrices remain retained. Explicit normal refresh yields152/113/492
and copies that result into the target. Subsequent real replacement setup
consumes retained worldY113 through movement, not newly captured localY27.
Target poses, positions, root caches and scratch remain unchanged. Alternate
flags, source masks, normal/alternate callers and repeated explicit refreshes
retain their distinct source semantics.

Focused unit/composite tests and enhanced strict TypeScript pass. Independent
scalar checks cover 4,096 actual DAT/setup contexts and 8,192 explicit normal
calls, all four source matrices and linked slots, both damping selections,
float32 edge values, signed copy counts, shared movement/guard state, retained
setup consumption and 64 disabled gates. They use a bounded synthetic numeric
domain and do not constitute original replay or general arithmetic proof.

Remaining limits are unchanged: zero admitted shorts and exact identity pose
quaternions, explicit RN00/NI0 and GQR assumptions, supported no-entry corrected
traversal only, no active terrain/IK/postprocess implementation, original
runtime inputs/provenance, full source lifecycle/contact ownership and actual
matrix-driven presentation. The linked receiver is a completed source data
operation, not a playable production clone. No rig inspection, source transfer,
asset/capture acquisition, installation or publication is part of this slice.

Final serial validation also passes the full contributor build, documentation
build with `GF_ATLAS_SKIP_MODELS=1`, 191 matching-tool tests and 83 oracle tests
with the existing one expected absent-private-MEM1 skip. All 41 private
mutation runners reject 1,275 independently counted variants, including the
52 new normal-caller/receiver controls. The affected older traversal runner
retains all 45 controls with two refactor-only anchor updates and a preserved
previous version. All 17 reference-name scripts and both rational reviews
also complete successfully. The division review retains its intentional
staged-rounding distinction; it is not a blanket claim of arithmetic parity.
No production execution, original capture or remote publication was performed.

## Bounded terrain matrix dispatch integration (2026-11-13)

The existing normal matrix owner now executes two additional authentic dispatch
paths without adding shadow actor state or a second tick owner:

- Selector3 enters the distinct `80047344` leaf. It dampens actual `1d60`,
  stores it, reads actual adjusted Y, reloads the stored drift and adds it
  with source binary32 rounding. It does not demand descriptor payload,
  metadata99, clearance or position that the leaf never reads.
- Selector2 enters `80047164`. Its threshold is
  `fma32(2, metadata99 & 15, add32(positionY, field670))`, in source read order.
  It consumes the four existing movement-descriptor joint bytes, stops only
  for signed -1, reloads/sign-extends the skip byte per entry and reads the
  existing full world matrices. X uses the cached descriptor index; Y and Z
  use the reloaded index. Above-threshold joints still read Z. Exact equality
  reaches the terrain query and refuses immediately before `8003d6e4`.
- Genuine no-query exits, including sentinel, skipped and above-threshold
  mixtures, execute the real damping/adjusted-Y tail, corrected matrix pass
  and reached linked-actor copy. A refused query preserves completed first-pass
  matrices and dispatcher count clears but never performs these later effects.

`world.getWorldMatrix` returns the actual twelve-element owned matrix record,
not a copy, refresh or optional movement-Y cache. Existing actual position,
metadata, mapping and descriptor records remain authoritative. Descriptor and
position replacement are rejected when reached. Callback tests preserve real
source reloads, including the stored drift reload after the adjusted-Y owner
read. No terrain adapter, guessed height, empty correction result or successful
fake callback is introduced.

Two authenticated existing ProgramDB snapshots agree on both spans and all
three constants. The fixed stdlib reader exposes only derived instructions,
physical traces and constants for allowlisted spans; its twelve synthetic tests
cover instruction fields, hashes, widths, constants, tail order and failure.
The selected decoder explicitly represents `fmadds` operands as A*C+B.
`terrain-matrix-handlers-evidence-2026-11-13.md` records reproduction and limits.

Real-owner integration begins with the existing synthetic model and animation
DAT import, opcode01 setup, attachment, captured poses and actual shared matrix
storage. Selector3 and admitted selector2 paths change drift10 to8, adjustedY31
to39 and worldY95 to119 before copying119 into the linked target. Source pose
and root lift remain unchanged. A source wait changes poseY to33 while retaining
matrixY119; subsequent replacement setup captures27 but movement consumes the
retained worldY119. The rejected-query example completes its first pass, clears
counts, and preserves drift10/adjustedY31 and the target's prior matrix.

The independent reference runs 4,096 synthetic DAT/setup contexts and 8,192
explicit normal calls: 6,826 complete and 1,366 stop at a genuinely reached query.
It compares complete first/corrected matrices, receiver copies, adjusted Y,
threshold comparisons, signed skip/sentinel behavior and retained movement
consumption against bounded dyadic scalar calculations. This is not original
replay or proof of arbitrary arithmetic. Existing RN00/NI0 and GQR assumptions,
zero shorts and identity pose-quaternion bounds remain explicit.

Production activation remains disabled. Reached terrain queries, positive
correction scans, active postprocessing, unsupported setup/animation domains,
original input provenance, source lifecycle/contact closure and matrix-driven
presentation are still required. No rig inspection, source transfer, raw
capture or asset acquisition, installation, or publication was performed.

Final serial validation passes focused real-owner integration and enhanced
strict TypeScript; the full contributor verification/production build; docs
with model synchronization skipped; 203 matching-tool tests; and 83 oracle
tests with the existing one expected absent-private-MEM1 skip. Both terrain
evidence readers agree on decoded spans, constants and physical traces.
All 42 mutation runners reject 1,305 variants, including the 30 new terrain
controls. All 18 reference-name scripts and both rational reviews pass.
The older 52-control normal runner retains every case, with its prior version
preserved and source-anchor/earlier valid-input diagnostic updates documented
in the private audit. Assertion failures and narrowly enumerated admission
failures count; syntax/build failures do not. The rational division review's
staged-rounding distinction remains explicit, not a claim of universal parity.
An independent read-only source/order/ownership review found no blocking issue.

## Explicit source transform-history owner (2026-11-13)

`actor-transform-history.ts` implements the real `8005685c` snapshot as an
explicit operation over the existing world owner and actual RomActor. It adds
only missing prior rotation76, prior prerotation1d6a, previousStepHeight6d4 and
aimOrigin524 storage, each with required explicit initial values. Current,
saved and older positions, bodyPitch/heading bits, world roll/prerotation,
current stepHeight, aim origin and visibility association remain authoritative
in their existing records. No new position or current-height shadow is made.

Two existing authenticated ProgramDB snapshots agree on the complete 164-byte
function and all 41 instructions. The fixed reader introduces no arbitrary
address interface or executable-byte dump. Evidence resolves details that the
C export alone obscures: each vector loads X/Y together before two separate
word stores, then loads/stores Z; each rotation's first two shorts use one raw
word load/store, followed by an unsigned halfword tail; height uses lfs/stfs.
There are no calls or function-specific constants. The source note is
`actor-transform-history-evidence-2026-11-13.md`.

The runtime preserves these boundaries. Both destinations of a paired-short
word are checked before either half changes; a separate later halfword failure
retains the completed word. Float-word X and Y stores remain distinct, so an
unwritable Y retains the completed X write. Scalar and vector floats preserve
finite exact-binary32 values including signed zero/subnormals. Historical
shorts are decoded signed values with the original BAM16 bits preserved;
short negative zero normalizes to integer zero because it has no separate
source encoding. This is an explicit host domain, not arbitrary RAM/NaN-payload
or original-machine exception behavior.

All position, rotation and height history stores precede the dynamic target
association read at actual `+cc`. Null returns. Nonzero target `+83` admits the
aim copy without reading either mask. Otherwise the actual target mask `+5e6`
and source visibility `+3e5` decide whether to copy source `+518` to `+524`.
Target controlWord, target positions, world mode and normal-controller `+4a4`
are not inputs. The clone matrix receiver is never snapshotted or ticked as a
side effect. Required actual records and captured methods retain their owners;
reentry and late failures preserve completed source prefixes.

Real-owner integration starts with the existing synthetic model/animation DAT,
setup, pose, movement and matrix composition. Snapshot first captures current
position 100/2/300, prior position 10/20/30 and height 9. A source wait changes the
pose without touching history or retained matrices. After the current position
changes to 104/6/308, replacement setup consumes retained world Y95 and writes
real movement height `f32(44.5 * 0.7f)`, leaving previous height 9 intact. With
explicit admitted synthetic matrix metadata selected after setup, the normal
caller refreshes world/receiver Y99 without advancing history. The next explicit
snapshot captures that real movement result and shifts the prior position.
Separate tests cover signed-short edges, all target gates and a late aim-store
failure, with no new animation, matrix, receiver or host clock.

An independent scalar reference checks 8,192 actual synthetic DAT/setup
contexts and 16,384 explicit snapshots. It varies finite binary32 bit patterns
including signed zero/subnormal/extreme values, raw BAM16 bits, signed shorts,
all visibility branches and matrix modes. Between snapshots it executes actual
wait, replacement setup/movement and normal linked-copy operations and checks
that retained history changes only at the explicit snapshot. These are bounded
synthetic results, not original gameplay replay or production activation.

Live Battle routing remains unchanged. Its existing beginFrame uses host
runtime.pos before syncIn, and source world inputs are not yet production
constructed. Calling the new primitive there would risk stale inputs and
duplicate existing history. Full lifecycle/contact closure and an exclusive
switch before overlapping host writes remain necessary. The new previous-height
owner supplies one missing input for future real terrain queries; it does not
substitute the approximate host floor probe for source `8003d6e4`.

Final serial validation passes focused integration and enhanced strict
TypeScript, full contributor/production build, docs with model sync skipped,
227 matching-tool tests and 83 oracle tests with the existing expected one
absent-private-MEM1 skip. All 43 mutation runners reject 1,339 variants, including
34 new history controls; all 19 reference-name scripts and both rational
reviews pass. Prior controls remain unchanged. One proposed deletion of a
redundant prerotation-record guard was not counted as a behavioral mutation:
the real world owner's property is immutable, and a new test proves it cannot
be replaced. No fabricated replaceable provider was introduced to force that
control to fail. Signed-short normalization, field copying, source order,
partial stores, actual history accessor identity and captured methods are
covered by genuine controls. The rational staged-rounding distinction remains
unchanged. Independent read-only source/order/ownership review found no blocker.
No rig, source transfer, acquisition, installation or publication was performed.

## Genuine terrain-backed normal refresh

The explicit source-owned integration now crosses the actual `8003d6e4`
terrain query and the no-correction return into `47164`. A strict formats view
uses supplied STIH bytes and existing parsed owners for three separate source
layers, file+8-relative pointers and first-sentinel termination. It is not the
host `floorSurfaceYAt` path or a constant ground callback. See
`terrain-query-evidence-2026-11-13.md` for fixed archive evidence and
`actor-matrix-production-routing-2026-11-13.md` for ownership boundaries.

The first admitted domain has zero support contact, empty selected ceiling
lists and flat reached floor triangles. Source bounds, 500-unit signed grid
indexing, separately rounded edge/plane arithmetic, history/current-height
adjustment and all floor selections execute against the actual records.
Out-of-range point-Y returns and genuine empty-floor fallback are separately
covered. Reached unsupported branches stop before their first omitted effect.
The view preserves aliases but does not emulate the original in-place loader's
writes or claim that aliased nonempty source lists are loader-safe.

The composite fixture contains a real triangle and sentinel lists, reaches
selector 2, obtains its height and completes corrected matrices plus the linked
copy only on strict caller-Y > add32(original clearance, returned height).
An equality/lower result preserves the first pass and refuses before stack-Y
or persistent correction stores. Actual wait then retains matrices, and real
replacement setup consumes the retained result. Positive prior-top movement,
post-query point-Y reload and saved caller-clearance independence are tested.
No result is manufactured by the instrumented wrapper: it always calls the
real query. This is bounded synthetic integration, not original-input replay.

Remaining production blockers are positive correction/IK work, nonempty
ceiling geometry, general matrix domains, active `47904`, complete lifecycle
and contact ownership, real spawn inputs and matrix-driven presentation. Host
Battle remains the only live path. A partial source route or host fallback
after source writes would duplicate ownership and is not enabled.

Independent validation covers 4,096 randomized real composite contexts plus
four signed low-word-wrap contexts. It checks 2,286 genuine query returns:
1,270 no-correction successes and 1,016 correction refusals, including 20 exact
boundaries. It also checks all nine ordinary cells, bounds exits, empty cells,
full matrices/linked copies and 829 wait/setup/movement/history sequences.
A separate bit-neighbor/midpoint rational oracle checks the actual private
division helper on 32,768 finite binary32 cases with divisors 1 and 500,
including signed zero, subnormals and gradual underflow. These do not establish
live FPSCR/GQR settings or original replay. The independent scalar matrix
reference remains bounded to dyadic inputs, rather than a general fusion proof.

All 47 current mutation runners reject 1,419 variants. The 80 new controls
cover the query, strict view, caller and strict-view changes through actual
query imports. That last route explicitly resolves formats to current source,
so stale compiled output cannot hide view mutations. Initial genuine test
survivors led to nonzero-height, rounded-sum, negative-displacement, maximum
selection, source header drift and wrapped-index/rounding fixtures. No case
was counted as rejected because it failed to build. The prior terrain-matrix
runner keeps all 30 cases with updated anchors; its previous version remains
preserved privately. Independent source/order review found no blocker.

Final verification includes focused integration, enhanced strict TypeScript,
full contributor checks/production build, docs with model sync skipped, 243
matching-tool tests and 83 oracle passes with the expected one missing-private-
MEM1 skip. All 21 reference-name scripts and both prior rational reviews pass.
Original assets and captures remain excluded; no rig, source transfer,
external installation, live activation or publication was performed.

## Correction-taking terrain normal alignment

The explicit offline path now progresses from a genuine equality/lower terrain
query result through actual correction records, positive-list scans, secondary
`4784c` orientation and linked matrix copy. Controller-owned primary/secondary
rows and counters are shared directly with world traversal. Descriptor bytes
are explicit fields on the existing descriptor owner, not synthesized metadata.
Source store order, independent cursors, count-byte wrapping, per-iteration masks
and untouched padding are retained.

The new `3de80` method writes into caller-local normal storage, uses the existing
strict grids/history, and selects only the source best eligible floor. Its
default output, outside-bounds return and partial failures are distinct from
the height query's min/max selection. The actual secondary effect transforms
raw pose translation, writes target coordinates, reads current clearance,
queries that normal and reconstructs the basis with source vector/matrix math.
No fake correction callback or approximate host collision query is involved.

A finite axis-aligned specialization makes this a complete executable branch.
The pinned canonical Dolphin reciprocal-square-root model plus independent
rational derivation gives normalized `q = 1 - 2^-24`, not one, and a restored
basis magnitude `m * (1 - 2^-23)` for the admitted powers of two. Actual source
arithmetic and Scale/Concat execute in order, preserving signed zero and store
prefixes. This is model-backed finite-domain semantics, not new hardware-run
proof, a general estimator or imported GPL implementation. Fixed archived
instructions and tables are documented in
`terrain-orientation-evidence-2026-11-13.md`.

The composite takes floor heights 8 and 12, writes both lists, genuinely matches
secondary joint1, updates translation to `(134,47,448)`, and copies the rounded
matrix to the linked clone. Later source wait and replacement setup consume
that retained result, producing real movement height `9.449999809265137` before
an explicit next history snapshot. It also covers source masks, independent
cursors, raw byte fields/counts, descriptor/clearance reloads, untouched slots,
repeated calls, early and late refusals, and an actual outside-bounds normal
query whose zero status is ignored by the source effect.

Secondary normal alignment is not the primary `47368` two-bone ground-placement
path: it does not consume the primary entry's corrected height. That effect
and its special topology continuation remain refused. Full production source
ownership, contact closure, broader math/terrain, spawn inputs and presentation
still need integration. Host Battle remains unchanged.


### Folded primary correction closure

The shared actual primary record now drives a bounded `47368` two-bone effect
and `46914` special traversal. Retained lengths2/0.5 and a unit upward target
displacement produce the source's minimum-reach folded placement with actual
length refinement, cosine clamps, signed-zero RotTrig and two matrix writes.
Raw current and adjacent poses, physical matrix adjacency and topology traversal
are kept separate. The skipped topology node is not recomposed over the second
matrix result. Genuine floor-query entry creation, linked clone copying and
later setup/movement consumption are covered in the same real-owner composition.

For the reached fixture, the query point Y10.5 receives floor10+clearance1,
while the primary raw base is Y10 rather than adjusted first-passY8. The folded
endpoint is Y11.5, not the unreachable requestedY11. This is a useful executable
primary path, not a claim of general IK or retail model hydration. Its source
and numerical bounds are recorded in the primary terrain evidence note and
production-routing note. Do not enable an incomplete Battle route or add a
source-to-host fallback after mutations.

### Positive primary bending closure

The primary path also admits equal unit bones, using real nonzero sine
refinement and both source rotations. It keeps the same explicit owner graph,
unit upward target, special traversal and linked-matrix consumers as the
folded case. The actual caller now verifies first-passY8/9/10, real floor10,
primary target11, bent adjacent matrix and traversed distal matrix. X/Z bends
reachY11 in the specified example; Y bends finishY12 without an invented snap.
Later actual wait/setup/movement retains and consumes the result.

The two new estimator facts are pinned canonical-model values, not new
hardware captures. Exact binary64 fused correction and source-stage tests
are required even where a wrong split calculation happens to reach the same
final binary32 output. The evidence note is
`primary-positive-bending-evidence-2026-11-13.md`. Other length pairs, broader
orientation domains and exclusive production lifecycle remain unfinished.

### Source-owned attribute refresh

The explicit `55dcc` helper now supplies existing movement dimensions and
actor speed limits from bound source descriptor records before invoking real
`4d08c` on retained world matrices. Its five products, three separately
reloaded parameter-pointer reads and fifteen sequential row copies preserve
source order and completed prefixes on refusal. Existing actionSpeedRows,
hover offset, movement fields and actor limits remain the single actual owners.
The new evidence note records the authenticated fixed span and finite-f32
assumptions; this is not original-input replay or a claim of complete spawn.

Real spawn and ordinary lifecycle call this helper, but their other steps are
still required. Explicit DAT/setup/world/movement composition must not be
mistaken for an exclusive production tick. Do not insert a successful dummy
callback, skip status/contact effects or switch ownership only at bridge.tick,
after the host has already mutated state. Battle remains unchanged until the
full reached source lifecycle and presentation can own the actor consistently.

### Source-owned status and active ammo prefix

The explicit actual-owner composition now calls real55dcc followed by bounded
5568c, including its unconditional real6dcc0. It shares the existing RomActor,
world6b8/mode4a1, movement661, attribute87/parameter4ac, source stream marker709
and mapping timestep1dc8. New parameter04/08 shorts belong to the same4ac
identity. The actual source clock/marker deliberately differ from legacy actor
dt/contactFlags in the witness, including a genuine start/reset between calls.
The existing source graph gains no shadow copies of those owners.

Host gauge/combo/invulnerability fields are borrowed directly from one supplied
synthetic BorgRuntime-shaped owner. This is not production Borg hydration.
Host invincTimer is the chosen720 owner, and the rival legacy invulnTimer is
refused rather than silently kept coherent. Three distinct actual WeaponCells
plus explicit missing mirror776 storage separate source slot indexing from
browser X/HUD aliases. The fixture deliberately retains aliased browser1/2,
refills source0/1, then source2 once on the next call, and rejects binding an
aliased browser list as source slots. Legacy cached rate, HUD ammo and generic
status duration remain unrelated values.

Active timers, six source counters, balance refill, combo reset,
invulnerability expiry, signed parameter regeneration/caps and FB accumulation
all execute. The real status call does not advance animation or rebuild a
matrix. Genuine wait/replacement, later explicit465fc with linked copy, real
4d08c consumption through55dcc, and explicit history retain their separate
cadence. Source predicates close only the omitted conditional callees; no
callback manufactures a successful f0104,3d3e8,3d444 or5c290 return. Reaching
those calls preserves their actual completed prefix and stops, as do late
missing4ac, readonly ammo mirrors and720 owner conflicts.

See `actor-status-timers-evidence-2026-11-13.md` for the fixed archived evidence
and bounded finite-f32 domain. Zero poison, null children and absence of reached
mode1 positive-debt division bound full returns; mode0 and mode1 expiry are real
ammo operations. The next unconditional59068 remains unimplemented, as do the
rest of55568/54070 and production spawn/contact/presentation closure. Do not
insert an activation flag, substitute host status/ammo steps, or fall back to
the host after any source writes. Battle's live route remains unchanged.

### Actual gauge resets and explicit scale lifecycle

The status graph now optionally binds the real `3d3e8/3d444` implementation.
An additive fixture reaches both positive `688/7d8` expiries and continues the
actual status/ammo suffix. The previous unbound-reset fixture and all historical
failure-prefix assertions remain unchanged. A reached invalid secondary base
also proves a bound failure after the first actual reset and both timer stores.
No callback manufactures success for either helper.

The same borrowed Borg owns `downGaugeBase/downGauge` and its actual
`paramTier` identity. Only missing signed `7d6/7dc`, target `B8`, byte `7c9` and
`C4` fields are added. Model scale remains actual `RomActor.modelScale`, the
three world copies remain the existing `world.scale58` vector, and the `C0`
write requires the actor's own `collisionScale` rather than the host fallback.
The source reset rounds `B4-1`, then `0.5*delta`, then `signedBase*factor`,
followed by truncation and distinct signed16/final low16 wrapping.

An explicit `5bab8` call exercises positive signed750 decrement, both
interpolation directions, clamp completion through actual `3d3e8`, and all five
ordered scale copies. Reached750 expiry refuses `6817c` after decrement but
before tier/delta clears or scale changes: the global gate and table-refresh
owner remain missing, so the existing host clamp is not a source substitute.
Readonly scale fields and missing actual collision scale retain their completed
prefixes. The fixed evidence and arithmetic bounds are in
`actor-gauge-scale-evidence-2026-11-13.md`.

Later real `55dcc` products and `4d08c` movement observe the changed model scale
on retained matrices. Genuine wait changes pose without scale/status work.
Only a subsequent explicit normal matrix refresh consumes world.scale58 and
copies the scaled result to the linked actor's matrices, without copying its
model-scale state. Later `55dcc`, real replacement setup and explicit history
consume that retained output at their own callsites. No hidden matrix rebuild,
animation advance, history snapshot or ordinary tick is attached to `5bab8`.

This is an explicit helper composition, not a continuous ordinary `59068`
prefix: that caller first performs the still-absent760/764 divisions byB4.
Its remaining movement/input/dispatch helpers and the enclosing55568/54070,
source spawn, exclusive host ownership and presentation remain unfinished.
Battle's production route stays unchanged. New composite tests follow all
historical blocks and status tests; focused gauge/scale registration is likewise
appended after focused status tests, before the existing final PASS.

### Bounded59068 distance and contact prefix

See [actor tick-prefix evidence](actor-tick-prefix-evidence-2026-11-13.md) for
the fixed archived spans, exact call order and unreconstructed support body.

The previous stage's absent760/764 divisions are now implemented in an explicit
bounded actual59068 operation on the same DAT/setup/world/attribute/status/gauge
owner graph. This supersedes that missing-prefix statement, not the broader
production boundary. The operation always stops at the first unsupported reached
effect, normally the unconditional59e58 following real5bab8 and real67a70. No
successful full59068 return, ordinary tick or live Battle route is introduced.

Canonical actual `RomActor.targetDistance760` holds the distinct full3D value;
new optional actual `horizontalDistance764` holds XZ. Both arrive together at an
explicit externally decoded pre59068 raw-input boundary. They are not speed
scalar aliases, shadow state, source square-root results synthesized by this
runtime, a capture, a scheduler, or a guessed zero for no target. Only absent598
gets a separate binding. The source target lookup/raw producer and no-target
constant still require authenticated implementation/provenance. The input tag
cannot verify that a caller has not relabeled normalized values as raw.

One guard covers epoch admission, ordered raw stores and the source prefix.
A per-actor increasing safe-integer epoch is consumed before the first store
and remains consumed after partial failure. It prevents repeated ingestion,
division and750 decrement on the same attempt. A fresh epoch supplies fresh raw
fields. This does not assert one normalization per whole frame: source command
6a104 may capture new raw distances later. Ingestion stores are explicit host
boundary effects, not source instructions, and partial stores are not rolled back.

The source order is760/currentB4 divide/store, then764/freshB4 divide/store,
real5bab8, then actual67a70 control bit0x100000 clear,598 clear and actual1db
supporting-contact test. Zero1db genuinely returns to59068; nonzero1db refuses
missing1e4 ownership after both clears. The separate existing collision adapter
is not the same source owner. Real5bab8 can instead stop earlier at6817c or a
missing/readonly destination, retaining the distance and scale/timer prefix.
Finite exact-f32 RN00/NI0 division uses exact rational nearest-even rounding;
zero divisors and rounded overflow remain refusals, not unverified IEEE results.

The permanent claim rejects legacy speedScalar760/764, kfmSpeedScalar760/764
and curTargetDist aliases. A minimal bridge.syncIn entry guard rejects claimed
actors before legacy mutations; unclaimed behavior is unchanged. There is no
unclaim, fallback or production source dispatcher. The raw producer and all
other overlapping host ownership still need resolution before live execution.

The appended composite proves raw64/20 become32/10 before actualB4 changes,
then supplies fresh66/22 at a later input epoch and reaches genuine scale clamp,
actual downGauge reset49 and all five copies. It checks real control/598 clears,
zero-contact return followed by59e58 refusal, retained6817c/C0/67a70 failure
prefixes, same-epoch rejection, and absence of unrelated owner drift. Only later
explicit55dcc/4d08c/wait/465fc/replacement/history calls update attributes,
movement, pose, matrices and history. Linked matrices copy the actual retained
result without copying that actor's scale state. Historical assertions and test
ordering remain unchanged; the new composite and focused registration are additive.

Next are real59e58 and the remaining reached movement/input/dispatch closure,
6817c global/table effects, nonzero1db/1e4 contact, source raw-distance production,
and the enclosing55568/54070/spawn/presentation ownership. A bounded refusal is
not evidence that any of those calls were skipped or successfully implemented.

The existing `NeoGredMeleeState.targetDistance760` accessor is also constructed
over the same actual actor before the prefix and reads its normalized760
after each input epoch, with no copied distance property or family dispatch.
This is a concrete existing consumer witness, not activation of that family.

### Actual stage-boundary counter and transition prefix

Bounded59e58 now follows real5bab8 and zero-support67a70 when a genuine stage
runtime is explicitly supplied. Inclusive stage bounds reset6cc; outside
bounds increment and sign-extend the stored short before the>=30 test.
Control02000000 can force a transition below threshold. The transition resets
the counter, writes actual6cb and conditionally ORs43 into the existing
status272 owner before stopping at unsupported6a750. Legacy cue routines are
not accepted as substitutes. A genuine non-transition return stops next at
685c0, without claiming complete59068 or ordinary lifecycle execution.

The same actual terrain global record owns the new explicit38/3c/40/44 bounds,
which are distinct from grid extents. No copied position, duplicate4a1/272,
default source lifecycle or auto-hydrated host fusion/death state is introduced.
The optional binding preserves the prior unbound59e58 refusal and all earlier
prefix order/epoch semantics. Real-owner fixtures prove that later explicit
wait, attribute/movement, matrix/linked-copy and history calls retain their
separate cadence. [Evidence and limits](actor-stage-bounds-evidence-2026-11-13.md)
remain synthetic and bounded; source stage initialization, cue/input closure,
full lifecycle and production ownership are still unfinished.

### Source cue resets close the bounded stage transition

Explicit6a750/6a6fc now provide genuine upper/full reset effects for a narrower,
source-exclusive actor domain. The stage helper binds this real runtime and
invokes both source calls in order, preserving separate sentinels and all
completed prefixes on later refusal. Previously unbound stage fixtures retain
the same refusal. Bound transitions now reach the next685c0 boundary.

Do not retrofit this with the legacy cue helpers: their omitted previous-cue
stores and reset effects remain inadequate. Legacy full-phase and marker
properties conflict with existing source owners and are refused, not mirrored.
Actual onLand754 is cleared to null; actual dispatch.marker1db3 is cleared only
afterward. Real setup/playback observes the same marker, with no automatic
animation/matrix/history call attached to reset. See
[cue-reset evidence](actor-cue-reset-evidence-2026-11-13.md) for exact operand
order, synthetic input limits and the still-unfinished live ownership boundary.

### Bounded input preprocessing retains the source actor graph

Optional genuine inputPrefix advances the reached685c0 call through real68980
for below-radius direction zero or already-set direction latches. It performs
source-ordered history updates, signed timer wrapping and actual5bc popcount
into the same Borg749, then clears actual5d4 before refusing first68b8c. Reached
active-direction conversion refuses at8b778. There is no successful full tick.

This preserves actual actor/gauge/Borg and prior stage/cue identity, all earlier
writes and consumed epochs. The corrected5d8 halfword annotation prevents
codec overlap with cue states; duplicate legacy input owners are refused, not
mirrored. The approximate browser mash producer cannot overwrite a claimed
Borg. Explicit downstream animation, movement, matrix and history calls retain
their own cadence. See [input evidence](actor-input-prefix-evidence-2026-11-13.md)
for the verified domain and remaining hydration, descriptor-machine, charge,
active-direction and production-ownership work.

### First machine executes without an opaque dispatch substitute

A genuine optional first-machine runtime now reads the retained numeric source
dispatch table and executes actual68c14/68c84/68d04 behavior. It borrows the same
actual actor input/control fields and adds only explicit614..617 storage.
Shared global arrays and per-actor exclusivity remain distinct. The caller
clears5d4 before real68b8c, preserves its actual tail-counter/edge effects, and
refuses the second machine at68610. [Evidence](actor-input-machine-evidence-2026-11-13.md)
corrects the historical omitted-phase interpretation and documents exact lazy
read/store order. No fake callback success advances this boundary.

Active-direction conversion additionally accepts an explicit retained GQR4
profile for signed8/load-scale0, performing both paired loads before refusing
at8b780. [Initializer and ISA evidence](actor-input-gqr-evidence-2026-11-13.md)
does not claim live hardware state or an implemented angle result. Original
input provenance, later machines/charge, active-angle/table behavior and full
production ownership remain open; synthetic owner composition is not playable
acceptance.

### Second descriptor and real axis-return stores

The optional machine runtime now supports a distinct second descriptor3904
and explicit618..61b cells on the same actual actor. Its genuine68b8c call
ORs40 without replaying or clearing the first machine's20, then either real
return value reaches the third call refusal at68628. No implicit second
owner or third descriptor is created. The
[second descriptor audit](actor-second-input-machine-evidence-2026-11-13.md)
proves the separate six-halfword record and discarded caller return.

The input prefix additionally accepts a genuine bounded angular runtime using
the same explicit processor record. Authenticated axis branches, exact
single-precision rounding/multiplication, saturating signed16 quantization and
the source direction-table index now produce real axis bytes. Those returned
bytes drive the source's two direction gates and their ordered latch/halfword/
timer stores; no browser angle, guessed direction or Math.atan2 substitution
is used. The [axis audit](actor-input-angular-axis-evidence-2026-11-13.md) documents
required GQR/FPSCR control profiles and the excluded FPR/stack/status effects.

Absent options keep their previous refusal sites. Non-axis libm, x==1 atan,
remaining eight machines, charge, actual input/hardware/global hydration and
complete production ownership stay open. Source-owned synthetic composition
advances a bounded lifecycle boundary, not browser playability or console
parity.

### Third source machine and diagonal math

The same genuine input owner can now retain descriptor3910 and bytes61c..61f.
Its actual mask400 match produces wrapper bit80 after the first two calls,
without replaying their state or re-clearing5d4. Both returns advance to the
fourth refusal at68640. [Third descriptor evidence](actor-third-input-machine-evidence-2026-11-13.md)
keeps the fourth descriptor and states outside the implemented domain.

Optional genuine atanRuntime closes the diagonal and x==1 source paths for
canonical signed-byte inputs. Authenticated reductions, interleaved polynomial
loads, fused binary64 operations and quadrant correction now feed the real
angular quantizer/table and68980 latch/history stores. Exact fused arithmetic
uses integer representation and one nearest-even rounding, rather than a
rounded host product followed by addition. Source constants and three atan
tables are explicit shared owners, with cross-owner alias checks in the joined
graph. See [finite angular evidence](actor-input-angular-finite-evidence-2026-11-13.md).

Absent opt-in owners preserve historical boundaries. The projection still
excludes general floating libm, negative-zero inputs, full processor effects,
retail input/table/stage provenance, remaining seven machines, charge and full
production lifecycle. Passing synthetic integration does not activate Battle
or prove browser playability.

### Fourth descriptor and genuine caller continuation

An explicit optional descriptor391c and separate624..627 cells now extend the
same machine owner to the fourth call at68640. The authenticated descriptor
matches input800 and the wrapper contributes output200 to the canonical5d4,
retaining first/second/third effects and all actual handler stores. The source
state pointer deliberately skips620..623; no ownership is invented there.
[Fourth descriptor evidence](actor-fourth-input-machine-evidence-2026-11-14.md)
proves the distinct six-halfword storage and the real caller continuation.

Either fourth return reaches the fifth refusal at68658, with descriptor3928,
actor+600 and mask1. No repeated5d4 clear or fake successful callback advances
this boundary. The optional record joins the same alias exclusions as earlier
machine, actor, Borg, processor and angular owners. Missing fourth or earlier
options retain their original reached refusals. Direct genuine graph tests
cover retained partial stores, consumed epochs and separate downstream cadence.
Six later machines, charge, original input/global provenance and full production
activation remain open; this local integration is not browser acceptance.

### Fifth descriptor and persistent source output

An explicit descriptor3928 and separate600..603 cells now support the fifth
actual68b8c call at68658. Its authenticated fields are `[1,0,0,16,0x100,0]`:
flags0 selects canonical5bc input100, with duration16 and wrapper output1.
The [fifth descriptor evidence](actor-fifth-input-machine-evidence-2026-11-14.md)
proves these distinct values and the next caller site. A match leaves tail15;
subsequent no-hit calls consume the remaining tail and keep contributing bit1.
Repeated hits refresh it through the real descriptor read and wrapper store.
No fixed one-call result, copied earlier state or implicit table hydration is
introduced.

Both genuine fifth returns continue to the sixth refusal at68670, descriptor3934,
actor+604, mask2, preserving earlier20/40/80/200 contributions. Earlier optional
refusals, alias exclusions, partial writes and consumed epochs remain intact.
Tests use the same actual DAT/setup/status/gauge/stage/cue/input graph, including
explicit pulse lifetime and downstream cadence. Five later machines, charge,
original input/global provenance and complete production activation remain open.
This is offline composition, not a new browser-playability claim.

### Sixth descriptor and required-set control gate

The same genuine machine owner now admits optional descriptor3934 and separate
604..607 state. Its authenticated fields `[1,4,0,1,0x100,0]` differ from fifth:
phase2 requires control40 set before reading canonical5bc100, uses duration1,
and emits wrapper bit2. See [sixth descriptor evidence](actor-sixth-input-machine-evidence-2026-11-14.md).
Timer decrement/expiry precedes the gate, and a preexisting tail still runs
the wrapper suffix after a gated return. No outer control gate can replace
that ordering or drain fifth's independent duration16 tail.

Either sixth0/1 return reaches the seventh refusal at68688, descriptor3940,
actor+608, mask4, preserving earlier20/40/80/200/1. Missing earlier owners
cannot be bypassed by sixth opt-in; lazy reads, aliases, partial stores and
consumed epochs retain their source-backed boundaries. The actual offline
DAT/setup/status/gauge/stage/cue/input graph continues to use explicit downstream
calls. Four later machines, charge, original input/global provenance and full
production activation remain open; browser acceptance is not claimed.

### Seventh descriptor and separate input20 output

Optional descriptor3940 and explicit608..60b now support the seventh source
call at68688. The authenticated `[1,0,0,1,0x20,0]` selects canonical5bc20,
no control/status gate, duration1 and wrapper output4. See
[seventh descriptor evidence](actor-seventh-input-machine-evidence-2026-11-14.md).
Fifth/sixth100 and seventh20 remain distinct input conditions; held direction20
cannot substitute for canonical5bc20. Seventh reuses genuine timer, phase and
wrapper operations, including source-ordered partial stores and existing-tail
output after expiry. It does not inherit sixth's required-set40 gate.

Either real seventh return reaches eighth refusal686a0, descriptor394c,
actor+60c, mask8. No prior edges are cleared and no later state is hydrated.
Missing earlier descriptors, retained owner identity, aliases and consumed
source epochs preserve their existing boundaries. The genuine offline joined
graph covers seven independent machine states and outputs, with downstream
setup/status/matrix/history still explicitly scheduled. Three later machines,
charge, original input/global provenance and full production activation remain
open. Offline source composition is not browser-playability acceptance.

### Eighth descriptor and canonical input40

Optional descriptor394c and explicit60c..60f extend the genuine source prefix
through eighth call686a0. Its authenticated `[1,0,0,1,0x40,0]` matches
canonical5bc40 with flags0, duration1 and wrapper output8. See
[eighth descriptor evidence](actor-eighth-input-machine-evidence-2026-11-14.md).
Canonical input40 is distinct from controlWord40 and held direction40; neither
can substitute for the reached5bc read. Seventh20, fifth/sixth100 and their
state/tail owners remain independent. Shared genuine handlers retain their
source order, signed expiry, lazy reads and partial stores.

Either eighth0/1 result continues to ninth refusal686b8, descriptor3958,
actor+610, mask10 (hex), preserving prior outputs. No ninth descriptor bytes,
state hydration or extra edge clear are supplied. Existing owner exclusions,
optional refusal order and consumed epochs remain intact. Genuine offline
graph coverage includes eight independent state/output groups and explicit
later setup/status/matrix/history calls. Two later machines, charge, original
input/global provenance and complete production activation remain open;
browser-playability acceptance is not claimed.

### Ninth descriptor and noncontiguous tenth boundary

Optional descriptor3958 and explicit610..613 now support ninth call686b8.
Its authenticated `[1,0,0,1,0x10,0]` selects canonical5bc10 with flags0,
duration1 and caller output10. See
[ninth descriptor evidence](actor-ninth-input-machine-evidence-2026-11-14.md).
Input10 and output10 have equal values but separate owners and source roles:
the retained descriptor supplies the match mask, while the caller supplies the
output mask. Held/status/control values do not replace canonical input. Shared
genuine handlers preserve signed expiry, phase1 ordering, retained tails and
partial effects without eager unrelated reads.

Either ninth return reaches tenth refusal686d0, descriptor3964, actor+628,
mask2000 (hex). The caller proves this noncontiguous state pointer; no adjacency
guess can borrow first-machine614. All prior outputs survive, and no tenth
state or table is hydrated. Optional ordering, owner identity, aliases and
consumed epochs retain their existing boundaries. The actual offline lifecycle
graph continues with explicit downstream status/setup/matrix/history calls.
The tenth machine, charge, original input/global provenance and full production
activation remain open. This is not browser-playability acceptance.

### Tenth descriptor and genuine charge call boundary

Optional descriptor3964 and explicit628..62b now support tenth call686d0.
Both archived snapshots authenticate `[1,0x10,0,1,0x0f,0]`; see the
[tenth descriptor evidence](actor-tenth-input-machine-evidence-2026-11-14.md).
Flags0x10 switches phase2 to any-bit matching against canonical5bc. Any low
nibble bit suffices, but the zero mask at index1 never matches. Control/status
gates are not reached. The retained input mask remains independent from the
caller's fixed output2000, and no first/ninth state owner is borrowed.

Signed expiry, phase1 reload/index order, phase-clear-before-duration and
unsigned tail-decrement-before-edge-OR remain in the unchanged shared handlers.
All ten wrappers execute in source order; either tenth return reaches exact
charge refusal800686d8→800686f0 without clearing earlier edges. The next data
pointer3970 bounds the tenth descriptor but does not hydrate charge tables.

Genuine offline graph tests cover all2048 canonical input combinations under
both control40 states, independent ten-machine state/output ownership, mutable
any/all semantics, partial stores, angular routes, aliases, consumed epochs
and explicit downstream setup/status/matrix/history cadence. Charge is a
distinct remaining helper, not an eleventh wrapper. Original input/global
provenance, charge numeric/effect behavior and full production activation
remain unfinished; browser-playability acceptance is not claimed.

### Source charge closure after all ten input machines

A genuine optional charge runtime now joins the same actor/world/status/mapping/
attribute ownership graph after the tenth wrapper. Its explicit global1829 skip,
three-slot disabled/reset/release/warmup paths and their ordinary returns follow
the [complete archived helper evidence](actor-charge-helper-evidence-2026-11-14.md).
Charge is not a new wrapper and does not borrow legacy Double-charge or ammo
fields. Existing6fc,768,4b0 raw8c and4ac parameter records are retained; only
missing actor cells and explicit shared source data are added.

Releases compare readiness before exact fused decay, reload the unboosted768
rate, preserve intermediate signed zero, clear654, then reload and clamp.
Warmup increments and reloads its cell, using strict overshoot and source-rounded
excess/bank additions. Source constants are checked lazily against10/+0/1/2;
missing or invalid unreached fields remain unobserved. Prior effects are never
rolled back on a later failure.

Mature-held work stops at80068838→800f0104 after its bank/654 stores, before
threshold and655 writes. Losing a prior ready mask stops at80068960→800061cc
with argument0x14. No sound/effect implementation or fake successful callback is
introduced, and newly-ready655 is not claimed reachable within this closure.

For admitted returns, the complete bounded685c0 input helper now returns to the
outer tick's exact next unsupported call800590bc→8005a190. Historical missing
charge behavior is unchanged. Genuine graph tests retain source owner identity,
partial writes and consumed epochs while later status/setup/matrix/history work
keeps its explicit cadence. This remains offline source-model composition;
source hydration, effect closure, full actor lifecycle and production/browser
acceptance are unfinished.

### Actor-control countdowns and bounded charge effects

The same source-owned graph now optionally continues through8005a190's genuine
returned-zero gates/countdowns and the actual6ab9c/6abb8 mask predicates.
Existing world modes/flags, status6fc and actual5e0 remain the only owners;
new490/49a/49c cells are explicit. Positive49c reaches0 without a same-call
readiness test, while49a decrements before its expiration test and restores1
when blocked. Ready transitions remain exact6aab0/6a980 refusals, and known
incomplete transitions cannot be silently bypassed on a later invocation.
After a real0 return, actual signed5e4 selects the unresolved802d3300 entry
at590e0; indirect call590e8 and subsequent actor work remain unsupported.

Required charge effects now have a genuine optional bounded implementation,
backed by [fixed archived evidence](actor-control-effect-evidence-2026-11-14.md).
The61cc→61f0 setter initializes the real color-script channel0 with selected
pointer13/14 and source-ordered writes; it neither renders nor dereferences
unreconstructed color scripts. Sound f0104 keeps an explicitly supplied active
shared scheduler row alive when first signed16 heads match, writing owner then
countdown2. Actor carriedSlot96 is signed for row selection. The runtime does
not create an active row, equate pointer identity with head equality, or treat
sequence index1 as sound ID1.

A null sound row retains its selected pointer store and refuses the real
OSGetTick call; replacement refuses its earlier cleanup call. Known incomplete
activation rows remain blocked across actors/runtimes, so a later call cannot
mistake the retained pointer for completed activation. These admission guards
preserve source writes without inventing source flags or a recovery path.

After genuine sound keepalive, charge reloads the actual parameter pointer,
bank and threshold in order, clamps and sets655, advances remaining slots,
and runs genuine ready-color initialization. This closes supported rising and
falling ready transitions while preserving old missing-effect boundaries.
Canonical owners, lazy reads, partial writes and explicit downstream cadence
remain enforced. Full sound start/stop/timing, color rendering, actor transitions,
indirect dispatch, source-state hydration and production/browser playability
are still open; no synthetic active-row fixture establishes cold-start gameplay.

### Ready-transition continuation after the bounded control/effects checkpoint

The next local slice preserves the completed control/effects checkpoint and
adds an explicit ready-transition opt-in. Actual `6a980` can complete its fresh
zero-`4a0` path using the existing stage, world, status, control and Borg owners.
After the caller's `489=4, 19=3` stores, `5a190` genuinely returns1. This takes
the archived branch around indirect cue/family dispatch and `59f5c/5a144`, then
reaches `5a298`. Its bounded special-request/early-return implementation can
advance to the next explicit `5a378` refusal. No whole tick completes.

The companion `6aab0` leaf is implemented, but its caller still stops at
`176ec0` after loading signed actual team. The `6a980` nonzero-mode branch
stops at `66198` after the exact prior stores and argument loads. Missing or
read-only reached cells retain their completed store prefix. Host-only
incomplete-transition guards prevent retrying such partial calls into a false
success; they do not claim an original source state or automatic recovery.

Canonical health/palette cells are the same Borg `hp`, `maxHp` and
`colorVariant`; stage18 remains the existing stage-boundary binding. No
parallel health, stage, palette, status272 or world/control owners are added.
Post-ready `5a298` has explicit missing `7d2/73c` cells and continues to refuse
its unresolved `10514` global predicate or pointer508 equality path. The
normal returned0 route still refuses the unresolved `802d3300` table cell.
See `actor-ready-lifecycle-evidence-2026-11-14.md` and the routing note's
bounded-ready section for instruction spans and exact remaining boundaries.

These are source-backed offline semantics with supplied source owners. Native
hydration, full effects and lifecycle closure, original/hardware behavior,
production selection and browser playability remain separate unfinished work.

### Bounded source rate continuation (2026-11-14)

The ready-return path can now opt into genuine `5a378` after `5a298`, writing
existing seek/timescale and shared mapping-clock owners. Status hit timers and
levels stay on the same Borg. Freeze and base clock retain their existing status
owner; only missing field1dd0 has explicit partial storage. An optional genuine
matrix owner supports source-ordered linked-actor copies through existing
link4a4 and the same admitted actor-symbol domain. No legacy UID, default rate,
clamped multiplier index or shadow timer is substituted.

This moves the reached boundary to `59120 → 68030` for supported rate branches.
The zero-control dispatch table, unreconstructed calls, full source hydration,
exclusive production scheduler and browser acceptance remain required. See the
[rate evidence](actor-rate-lifecycle-evidence-2026-11-14.md) for authenticated
instruction order, bounded multiplier cells and arithmetic assumptions.

### Genuine completion of admitted59068 ready path (2026-11-14)

Optional `ceiling` now supplies the actual final68030/8b290 call. A supported
ready branch returns source void rather than inventing a new refusal after
its final instruction. This does not run the enclosing55568 frame, resolve
zero-control table dispatch or establish playable browser behavior.

The path requires one shared match-global record across matrix+d2, ceiling+d9
and charge+1829, plus the same stage terrain owner. New fields come only from
explicit input; prior disconnected fixtures and missing-tail refusals stay
unchanged. See [ceiling evidence](actor-ceiling-lifecycle-evidence-2026-11-14.md)
for ordered add/subtract, ceiling gating, positive-zero velocity store and
retained late-failure prefixes. Real6826c tier-row hydration remains the next
producer needed for B8/1dd0/5f8 rather than borrowing rounded host tables.


### Source tier rows through genuine expiry (2026-11-14)

The optional tier runtime now supplies actual `6817c` and `6826c` on the
same existing Borg, attribute registry, gauge, rate and actual actor owners.
The reached `59068 → 5bab8 → 6817c → 6826c` path can finish tier expiry:
`750` decrements first, the delta helper consumes negated signed `74e`, then
caller `750/74e` clears occur only after its genuine void return. Existing
scale interpolation and the supported ready/action/rate/ceiling branch then
continue in source order. No standalone host tier approximation is substituted.

Only the two authenticated selector cells and rows 15, 16 and 17 are admitted.
Source upper-before-lower clamp semantics, signed tier and unsigned descriptor
selector, null-pointer return, signed32 wrapped delta addition, and ordered
`B8 → 1dd0 → 5f8` stores retain their distinct behaviors. The rows preserve
exact binary32 values rather than six-decimal legacy JSON. Other reached rows
or selectors refuse after the completed clamp prefix. These six windows do
not establish either table's allocation bounds.

Shared match byte `1f` is on the same retained record as matrix `d2`, charge
`1829` and ceiling `d9`. Only absent signed `74b/c/d` receive new binding
storage; existing Borg `paramTier.tier`, gauge `targetScaleB8`, rate `field1dd0`
and actual `tierScale` remain canonical. An explicit one-time gauge/tier
binding resolves their construction cycle. The tick verifies the same owners
and excludes new owner records from raw-distance aliases.

The composition supplies descriptor selector and limits explicitly. It does
not implement constructor `56180`, authenticate a production family page,
execute outer `55568`, supply real target-distance producers or activate the
production scheduler. Explicit subsequent status, animation, matrix and
attribute/history calls observe source-produced values without being silently
inserted into `59068`. The existing host position consumer is a separately
labeled wiring witness, not a binary32 physics oracle. See
[tier evidence](actor-tier-lifecycle-evidence-2026-11-14.md).

The next normal-control boundary remains the signed-cue table load at
`802d3300 + 4*s8(5e4)`. The reached cue9 cell is `802d3324`; no function may
be assigned to it by C declaration order. After its authenticated target
returns, actual actor `4c8` dispatch, `59f5c` and `5a144` still precede the
common continuation. Source-backed progress here is not full gameplay or
browser-playability proof.


### Authenticated normal-control continuation (2026-11-14)

An optional genuine normal lifecycle now follows the returned-zero branch of
`59068`, in order: signed cue dispatch, fresh actual `4c8` dispatch, `59f5c`,
then `5a144`. Both completed control branches join the same existing action,
rate and ceiling tail. The prior no-normal-runtime table refusal is unchanged.

Two static cue cells are authenticated independently: cue9 resolves to the
single-instruction return at `80059138`; cue0 resolves to `8005913c`, whose body
remains unsupported. Other signed cue cells still refuse at the table read.
The Double Ninja constructor at `8006f60c` independently establishes its `4c8`
cell `802d3b28`, which resolves to the return-only leaf `8006f950`. This is not
inferred from another family or declaration order. The separately evidenced
G RED `8018cfe4` leaf is also supported only when explicitly supplied. Adjacent
return words are not automatically admitted. Constructor evidence does not
itself hydrate a production actor or authenticate unrelated callbacks.

The bounded `59f5c` helper supports its control-mask flag merge and the genuine
full-body cue synchronization before the movement-10 return. Existing actual
`stateFlagA/stateFlagB`, source movement `byte661`, mapping, status and cue
records remain canonical. Source-normal movement0 still reaches unsupported
rotation damping at its first constant load; descriptor sentinels cannot skip
the mandatory trailing damping. Explicit movement10 test inputs are synthetic
admission boundaries, not a claimed natural stage transition.

The signed `6bc` countdown stores its decrement before examining `4dc` at
expiry. Explicit null or zero returns; absent, invalid or nonnull callbacks
remain reached refusals. A host-only incomplete-expiry guard prevents that
retained zero from turning an unexecuted callback into success on a later tick,
including a later ready-path bypass. A reached genuine cue synchronization
that throws is also permanently marked incomplete: writing the new full-body
cue cannot erase the unfinished reset on the next equal-cue or ready branch.
These conservative host guards require a future explicit recovery lifecycle;
they are not original source fields. Only absent `4c8`, `4dc`, `6bc` and `1d9`
receive partial binding storage. No generic host callback replaces a source
call and no legacy scheduler is activated.

This extends executable source-owned offline composition, not browser
playability. Active rotation damping, unresolved cue bodies and callbacks,
full constructor and input hydration, outer `55568` and an exclusive production
lifecycle remain unfinished. See [normal lifecycle evidence](actor-normal-lifecycle-evidence-2026-11-14.md)
for fixed snapshot selections, provenance and retained failure prefixes.


### Genuine movement-zero rotation damping (2026-11-14)

A further explicit rotation opt-in supplies the active body of `59f5c` after
its real cue synchronization and movement10 gate. It reads the existing
mapping clock before later `5a378` updates it, applies source `fsubs` then
single fused `fmadds`, and scales each signed correction with the original
single multiply, truncation and low16 store order. The exact coefficient
weight is bits `3dccccd0`, not a rounded host literal for ordinary 0.1.

The existing raw8c descriptor array remains the sole list owner. Its offsets
`24..2b` represent descriptor `b0..b7`; the independently authenticated Double
window is `[12, 2, 7, 11, -1, -1, -1, -1]`. The implementation reloads the
selected descriptor each iteration, processes duplicates repeatedly, and
always applies the trailing joint1 triple after the list or sentinel. Only
explicitly owned correction slots0..31 are admitted. A list sentinel does not
skip the tail, and no joint-count check absent from the source is invented.

Corrections remain in the actual retained world rows. Joint1 X is the existing
unsigned BAM16 `RomActor.steerYaw`, while its Y/Z are signed fields in row1;
there is no second X. Each store follows its own reached validation and keeps
prior effects on failure. A failure after the first successful correction
store permanently marks the attempted damping incomplete, blocking later
normal, movement10, flagged or ready tick bypasses before any new effects.
Failures before the first store remain unmarked and can accept corrected inputs
on a fresh epoch. These guards are conservative host admission, not source
state or automatic recovery.

With explicit descriptor and correction hydration, movement0 can now complete
the supported normal `59068` branch and its actual countdown/action/rate/ceiling
tail. Later status, animation, world-matrix and history calls remain explicit;
nonzero rotations do not imply general matrix/trigonometric support. No
constructor, raw input producer, outer `55568` scheduler, general cue dispatch
or browser acceptance is supplied. See [rotation evidence](actor-rotation-lifecycle-evidence-2026-11-14.md)
for exact constants, instruction order and arithmetic limits.

### Cue0 and ordered ground correction, 2026-11-14

The optional genuine cue0 runtime selects authenticated target `8005913c`
through the existing normal-dispatch table. Movement byte3 executes the real
upper-body and full-body cue27 resets in that order, including the full reset
when the upper entry is the no-op sentinel. It then returns to the existing
actual4c8, cue-state, countdown, action, rate and ceiling sequence. No alternate
host callback or fabricated cue result substitutes for either reset.

Other movement reaches the genuine `80068df8` helper. Its control-bit and mode2
returns are preserved. The active ground path calls the existing byte-backed
`8003d6e4` terrain query with the retained actual position, writes the returned
height, loads the otherwise-missing explicit byte732, and compares the exact
single-precision height difference against the existing attribute674 owner.
Ordinary ground snaps and source-ordered uphill XYZ rollback now execute on the
same positions later consumed by matrix/history. Terrain, attributes, movement,
cue and mapping owners are shared rather than copied; byte732 has no default.

The drop path restores the saved incoming Y before displacement arithmetic.
Its positive squared distance stops before the unsupported reciprocal-square-root
estimate. A zero-norm subset supports exact signed-zero division by nonzero
finite tierScale5f8, preserving a conditional speed store before the unsupported
atan call, or slope698=30 before the unsupported6a5a4 transition. Neither path
fabricates success. A completed ground helper returning0 still reaches the
explicit699d8 boundary: its nested input helpers contain mandatory stores even
with zero input, so treating it as a no-op would be incorrect.

A failed effectful cue0 call remains marked incomplete across later edited cues,
flags or ready branches. Tick checks this before new raw ingress; direct helper
success clears only its own completed invocation. Earlier source effects are
not rolled back. Tests use explicitly supplied synthetic decoded actors and
terrain bytes. This remains bounded source integration, not constructor/input
hydration, a complete normal controller, production activation or browser
playability. See [cue0 evidence](actor-cue0-lifecycle-evidence-2026-11-14.md).

### Ordered source input testers, 2026-11-14

Cue0 now optionally continues its terrain return through actual `800699d8` and
its six ordered helpers: `69cb0`, `69c50`, `69bf0`, `69b98`, `69b10`, `69a88`.
Each unconditional byte595 clear is a separate source store, even with no
input. The first genuine nonzero result stops the chain. Mode2 in `69cb0`
returns1 before linked-actor access, after the required595 clear and any
reached signed593 countdown reset. This path can return through cue0 and the
existing normal/countdown/action/rate/ceiling tail on explicitly supplied owners.
A complete zero-input chain returns0 and reaches the next honest `69814`
boundary; it does not silently complete all of cue0.

The new binding holds only missing byte595 and byte748. Command585 is the
existing actual `cmdButton`, not `variantIndex` at581. Status593, charge58e,
action-request7d2, world4a0 and actual584/5d4/5e0/57a remain their existing live
owners. Tick reconciles the same charge runtime used by the input prefix and
the same action-request runtime used by its later common tail. Shared action
and tier attribute owners are allowed only by exact canonical identity.

Reached `69dd0` loads signed585 before4b0, reads descriptor+b8, preserves the
sentinel−1 return before control flags, and preserves genuine other-type zero
returns. It reloads585/pointer/type when the source does. Raw8c indices are
bounded by actual supplied storage, not an invented six-action restriction.
The descriptor is resolved through a narrow guarded getter on the genuine
charge runtime's existing registry, so b8..bd and the overlapping charge slots
cannot acquire a second owner. Known-descriptor metadata never eagerly reads
an unselected pointer. PowerPC `slw` uses the low six count bits; counts32..63
produce zero, unlike JavaScript's implicit modulo32 shift.

The mode1 linked4a4 branch, `5c080`, `69ea4` and `69fe0` remain explicit
boundaries. No linked3e6 owner is borrowed from unrelated damage snapshots.
Failures retain all earlier source stores. A partial tester invocation blocks
later continuation before raw ingress; a complete tester call does not clear
the surrounding cue0 invocation's still-pending69814 boundary. The latter
marker begins conservatively at the genuine call, like the existing cue reset
calls. Successful direct helper calls clear only their own completed marker.

Tests use synthetic decoded data and genuine runtime composition. This does
not supply native input/descriptor hydration, a complete normal controller,
production activation or browser playability. See [input-tester evidence](actor-input-testers-evidence-2026-11-14.md)
for the full307-instruction schedule and archive authentication limits.

### Remaining cue0 tail, 2026-11-14

The optional genuine tail continues after `699d8` returns0 through `69814`,
`696f4`, `69038`, `69354` and `68f9c`. It implements the reached `694c0`
predicate and uses the genuine upper-cue reset runtime for every active call.
Intermediate nonzero returns short-circuit; the final helper's native0/1 is
ignored by the source void epilogue. Missing optional tail preserves the
historical69814 boundary. This closes that bounded cue0 call chain without
pretending earlier terrain/input boundaries or subsequent cues are complete.

The source global is the same retained `PTR_DAT_80433934` owner used by charge,
matrix, ceiling and tier paths. `teamRows103` is an explicit source team-indexed
array of references to existing `BurstMeterState.charged` cells, admitting their
boolean0/1 subset. It does not infer a mapping from the browser's player-keyed
meter map. Negative signed indices or absent rows outside explicitly supplied
storage refuse rather than receiving default flags. Selected rows and the array
retain identity; real team sharing is allowed, actor-owner aliasing is not.

`69814` loads actual `team` at88 before the global pointer and reads the selected
charged flag before inputEdge5d4. A charged edge200 writes the existing actual
Borg's `burstArmFrames=6` at6fb and still returns0. It never creates a second
byte6fb. `694c0` reads new byte7cd; zero returns1 without short736, otherwise a
single read of the existing signed status.short736 tests positivity.

Only missing byte57c, byte58f and byte7cd receive partial tail-binding storage.
Existing actual control/status/input words, inputHeld5d8, movement.byte661,
status.short736, Borg.burstArmFrames and real cue/dispatch records stay live.
`69038` stores57c=0 before upper cue4, including sentinel-return0. `69354`
selects upper cue37 or12; on native success it reloads held5d8, stores58f from
bits4..7, reloads held5d8 again and clears those bits. `696f4` invokes694c0
before its control/input gates and real cue32. `68f9c` selects real cue29 or1.

Reached failures retain source prefixes and incomplete-call guards across
standalone calls, later cue9/ready branches and raw ingress. A completed child
call never clears an unfinished outer cue0 invocation. Shared-global and owner
reconciliation uses metadata without eagerly loading unselected rows. Tests use
explicit decoded inputs and genuine offline composition, not live player/team
hydration, original execution, a complete frame, production activation or
browser-playability evidence. See [tail evidence](actor-cue0-tail-evidence-2026-11-14.md)
for the authenticated159-instruction schedule and its limits.

### Ordinary X command admission, 2026-11-14

The optional genuine command-admission runtime continues the actual mode1
descriptor branch from `69dd0`. `69ea4` stays in input-testers, which owns595;
it loads694 before the authenticated zero constant only when595 is zero,
retains one5e0 word for subtype priority, and reads7cc/5e4 only on their reached
branches. Only absent7cc joins the tester binding.586/587 remain the actual
`cmdSubtype`/`cmdChargedRanged` fields. Omission preserves the old69ea4 boundary.

The child performs the real6c674 null508 return, stores587, then reloads the
three signed selectors before loading actual `commandTable` at4ec. Its optional
`sourceTables` extension retains source pointer slots and raw byte rows;
legacy normalized records cannot supply the omitted cue/mode bytes. Double's
existing derived table evidence identifies root8033b180, X pointer slot8033b188,
and ground record8033b108 `[44,3,2,0]`. The pointer slot is not the root, and
the JSON's type2 denotes the command slot, not a Borg type. These addresses and
record bytes remain derived evidence, not newly authenticated table payloads.

Real6a104 sentinel returns0 before capture. Non-sentinel dispatch stores584 and
executes the mandatory6bda8 prefix. Explicit504/508/C8/D0 cells are partial;
missing pointers never mean null. CC remains actual `visibilityTarget`,7d2
belongs to genuine actionRequest, and6b8 is world `yawOffset6b8`. No-target
capture stores the authenticated20000f raw distances, performs source zero-yaw
trig, and reads the descriptor-selected actual world matrix lane7 for51c.
Descriptor byte10 extends the same attribute/mapping descriptor identity.
Existing aimOrigin518 and distance760/764 owners receive the actual stores.

The narrow45204/45238 wrappers require the explicitly supplied GQR5
signed16/scale0 profile, positive factor38c90fdb and the existing authenticated
zero sin/cos kernel paths. No host sine/cosine or general nonzero trig is
substituted. Constants and the six authenticated57a/b mask pairs share the
existing charge data owner; reached values are checked, never defaulted.

Admission then executes actual action/variant/control/timer writes, canonical
stream marker709 and blockedMask1d9a clears, and all six explicit shared
visibility references in source order. Genuine6a6fc/6a750 perform cue resets.
The status runtime exposes its retained ammo slot/cell by identity; max0 or
refillType3 genuinely skips6dbe0. The finalea2c8/ea2ec path returns before RNG
only when the same explicit match-global byte45 is signed>=5. This is a bounded
non-normal-match voice gate, not full active-match voice behavior. Unsupported
targeting, nonzero trig, transition4beb8, ammo checking/sound and active voice
remain ordered failures with their completed writes retained.

The genuine attached graph demonstrates an X edge from the third input machine
through69b98/69dd0/69ea4 and the ground record to native1, followed by the existing
normal/action/rate/ceiling suffix. Partial command effects block later cue9,
ready and raw-ingress bypasses. A subsequent unsupported cue44 still refuses.
This does not supply live target/table/global hydration, full55568 scheduling,
source family playback, sustained attack effects, production activation or
browser acceptance. See [command-admission evidence](actor-command-admission-evidence-2026-11-14.md)
for421 primary plus54 bounded support instructions and explicit libm/voice
coverage omissions.

## Ordinary X cue44 control continuation, 2026-11-14

Fixed archived cell802d33b0 selects80059cd0 for signed upper cue44. The complete
352-byte handler and160-byte690a0 helper are independently selected from their
named C markers, with all128 instructions represented and terminal returns
checked in both snapshots. Neither extent is claimed to come from the retail
symbol map. The fixed witness is
[actor-x-playback-evidence-2026-11-14.md](actor-x-playback-evidence-2026-11-14.md).

This handler continues control decisions; it is not the action-state playback
inside55568. The existing genuine cue0 runtime now exposes dispatchCue44 on its
same actual, terrain, movement, attribute, cue, tester and tail owners. No new
actor binding or second588 cell is introduced. It stores the existing cue-reset
binding's byte588=1 before reading controlWord bit40. The ground branch calls
68df8,699d8,69814,696f4,690a0,69038,69354 and68f9c in source order, retaining each
real short-circuit return. It cannot substitute the whole cue0 tail, whose call
sequence omits690a0. The air branch performs699d8/69814 and then refuses at its
first unsupported69210 call.

Real690a0 returns0 on its ordered stateFlagA bit40, inputEdge5d4 bit1 and
statusWord5b4 bit100 gates. When all pass, it invokes genuine upper cue5. A
sentinel return0 leaves later control storage untouched. Successful cue5 is
followed by a fresh controlWord load, mask00ff0000 and store; the next actual
5c080 remains unsupported. No later OR2000 or native1 is manufactured. Required
equal-value writes and completed effect prefixes are retained. Shared lifecycle
incomplete state protects later direct lifecycle methods, normal dispatch,
ready/control bypasses and explicit raw-distance ingress.

Normal dispatch now selects the authenticated cue44 target and reuses the same
canonical graph. Byte588 and familiar raw aliases are checked across composed
owners before raw ingress, including paths that would otherwise bypass cue44.
The attached witness can run real X admission then subsequent ground-control
epochs without repeating the command or pretending to advance animation.

Actual Double cue44 hydration is now separately grounded: the already selected
constructor8006f60c copies producer cell802d3b50 to actor4f0. That fixed pointer
cell is newly authenticated as802d3ff8, and only the fixed two-byte cue44 row at
802d4050 is selected, yielding full-body61 and upper0. The old test fixture's
[61,62] is deliberately synthetic; it is not the Double row. Upper0 performs a
real cue transition/reset and is not the signed-1 sentinel. No full cue table,
live actor constructor, or runtime pointer-driven archive read is supplied.

### Next actual playback boundary

Source55568 still needs its outer schedule: marker578=2;55dcc;5568c;59068;
position snapshot; actual4bc; capture upper5db then full5da; marker578=1 and
captured upper-state dispatch; marker578=0 and saved full-state dispatch; marker578=2;
actual4c0;55ee4; conditional position restore;5b880. Marker578 is the existing
animation-dispatch binding, not a new outer flag. Source-owned graph operations
must be joined at these exact boundaries rather than inserted as extra refreshes.

Existing C and derived family evidence identify the next selection route to
reauthenticate: upper0 cell802d37a8 ->5f238 return; full61 cell802d379c ->65dfc
->actual4b4; Double constructor root cell802d3b14 ->6facc; action2 cell802d3b70
->71598; variant0 cell802d3c48 ->715d4; hidden config80433868 ->ff2bc; phase0
cell8031f000 ->ff30c. These later pointer cells/callees are not covered by the
current fixed reader. See [family decode](nn-family-decode-2026-07-06.md) and
[ninja source X](ninja-source-x-2026-11-12.md) for the existing derived evidence.

Before this playback, Double4bc=6f7c0 must write the canonical stream-start582,
charge58e and status272 owners and honor its persistent clone arm7c8. Phase0
requires genuine6d144 ->669d0 ->66a30 even with no target, then677b0's distinct
3e0a8 height/normal query. The current3d6e4 terrain helper cannot replace it.
The real ordinary group4 programs start with opcode01 mode1/blend6; the current
source animation setup accepts mode0 only. Replacing that request with mode0 or
using the legacy Ninja private stream schedule would not establish playback.
Source mode1 setup487ec, mode1 playback4a00c and reached authored opcodes remain
work. Later resource debit, projectile/clone allocation, source posthook and
render scheduling are also unfinished. This checkpoint makes no full55568,
sustained attack/clone behavior, production selection or browser-playability claim.


## Source mode1 animation and outer-frame prefix, 2026-11-14

The next bounded slice authenticates seven complete functions and seven scalar
constants in both archived snapshots. All553 instructions and operands are
represented, including the whole55568 envelope, setup487ec, playback4a00c,
copy4b94c, blend4a8cc, three-component paired scale8020ba9c and quaternion
slerp8020bf08. See [mode1/envelope evidence](actor-mode1-envelope-evidence-2026-11-14.md).
This is static evidence plus bounded offline integration, not original execution,
matching-decompilation MATCH, full action2 playback or browser acceptance.

### Real mode1 operations

Opcode01 mode1 can now reach actual487ec rather than being changed into mode0.
A zero transition takes the source4871c fallback. A nonzero transition first
copies the entire64-byte inline part to the opposite bank in eight ordered
load/load/store/store pairs. Existing mapping, feedback, dispatch, attached,
metadata, archive and setup records retain their canonical fields. Only the
previously absent bytes34 and39..3f get explicit raw storage; none are defaulted.
Destination33 is then updated, channel0 copies visibility history, and selected
quaternion and translation poses are copied between the existing independent
banks. A packed source word cannot partially write its component fields on a
host readonly failure.

The same source metadata/archive/mapping setup then prepares mode1, seeds its
blend clock from the actual mapping1dc8, converts wrapped signed duration+1,
and computes the exact RN00/NI0 fdivs/subtraction weight. No shadow clock or
copied descriptor owner is introduced. Genuine direct runtime identities are
reconciled; the older explicit lower animation-effect adapter contracts remain
bounded requirements, not a proof of arbitrary transitive adapter behavior.

Blend4a8cc updates translation before quaternion processing, using two actual
paired vector scales and vector addition with separate single rounding. It
performs the source hemisphere comparison and real linear branch of8020bf08.
The strict threshold is0.9999899864196777; equality still reaches the unsupported
nonlinear call8023cc8c. There is no host trig, identity shortcut, normalization,
clamping or fused replacement. Successful slerp then performs the two-entry
signed descriptor42/43 visibility selection, using old visibility only when
weight>0.5. The actual GQR0 float/scale0 and finite RN00/NI0 domain is a host
precondition, not an observed machine configuration.

Playback4a00c increments elapsed08 then blendElapsed1c with two fresh1dc8 loads.
The unfinished branch calls real mapping with flags0 before blending. On
completion it adds the source overshoot to frame0c, calls real mapping with
flags1, and only then stores mode0. It does not inspect linked36. The composed
synthetic DAT witness exercises old-pose preservation, real archive/JObj/AObj/
FObj replacement and feedback. With blend6 and timestep1, six updates reach
mode0; the sixth may reattach/evaluate frame0, and the seventh genuinely advances
the current AObj to frame1. Failed containing mode1 operations keep completed
writes and block later setup/playback despite changed mode or readiness gates.

### Actual55568 prefix, without skipped action dispatch

A separate genuine frame runtime now joins the existing55dcc,5568c and59068
operations on the same actual actor, Borg, world, attributes, movement, status,
mapping and marker578 owners. Its explicitly tagged pre55568 raw-distance
input is a host boundary before the first source write. The source sequence is
marker578=2, attributes, status, control, then actual position20/24/28 snapshots.
The next actual4bc family prehook remains a refusal. No hook, state machine,
posthook,55ee4, conditional position restore or5b880 is invented or skipped.
No465fc matrix refresh is inserted.

The tick's private one-time frame claim is available only during a genuine
frame binding with its exact private pending owner record. It permanently
closes direct standalone tick ingress. Failed host preflights consume their
epoch; once source execution begins, an incomplete frame cannot replay or be
bypassed by a later ready/control branch. A prior incomplete mode1 operation
also refuses before frame ingress. This remains an offline graph: the browser
still uses its existing bridge/stepRomActor route.

Next required work is actual4bc/Double6f7c0 with canonical582,58e,272 and
persistent clone7c8 ownership, followed by authenticated UB0/full61/root/action2/
variant/phase dispatch. The exact archived55568 instructions capture upper5db
then full5da after the prehook and before marker1; full dispatch uses that saved
full byte after upper returns. Phase0 still needs6d144,669d0,66a30 and the distinct
677b0/3e0a8 ground path. General nonlinear quaternion interpolation, root-motion/
mirrored mapping, later authored opcodes, posthooks, projectile/clone allocation
and the render scheduler remain separate reached boundaries. This slice does
not claim a playable clone or completed action2 lifecycle.
