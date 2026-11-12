# Double source-owned dispatch migration

Audited baseline: `2a385888`. This is a design and acceptance boundary, not an enabled runtime mode. No original assets are included.

## Decision and first executable milestone

Do not add an unconditional `stepRomActor` call to the existing bridge. The next useful milestone is a deterministic offline Battle/replay scenario containing a Double actor whose ordinary lifecycle, movement and accepted ordinary reactions are owned by one source dispatcher. Inputs and contacts are bounded by the scenario; this is not a user-selectable live mode. Host mode remains the only live path. Success means an ordinary action can finish, receive a supported contact, complete its reaction and return to ordinary control without changing owners midway.

This is larger than porting reaction selectors 1–8. Their reachable continuations include 10 (landing), 12 (terrain fall) and 19 (recovery input); those handlers have their own reachable transitions. Audit and implement the reachable closure before enabling the mode. A first-entry control-bit classifier is not that closure.

Static lifecycle18/19 mappings are now verified (see eligibility below). First remaining prerequisite: record one deterministic ordinary Double scenario through the actor sweep and collision phase, including the exact eligibility gates. This establishes which source handlers must replace host ownership before implementing the offline slice.

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
