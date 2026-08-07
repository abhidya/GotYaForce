# Port driver — implementation record (2026-08-06 evening)

Phases 0–2 of `port-driver-design-2026-08-06.md` shipped same-day, on fork
`abhidya/RustyOGhidra` main: `5db2dee` (Phase 0) → `c8b3b88` (Phase 1) → `f350f61`
(enrichment scope) → `b7e56fa` (BOM lock) → `d9e86b2` (Phase 2) → `6039f46`
(request_limit). 257 tests pass. This note records what exists, what was verified
live, and what remains — read alongside the design and the distillation
(G/R IDs cited there).

## Shipped

- **Phase 0** (G2/G3/G5/G6/G10/G15/R2/R7/R8/R13/R15): analyze() reuses a
  sha-matching `analysis.json` at zero model requests; `--force-reanalyze`
  override; no provenance downgrades; `port_unit` returns a typed
  `UnitSkipResult` for non-portable and all-placeholder-entry units before any
  generation; legacy-only flags rejected on the chunk path; control.json checked
  at start.
- **Phase 1** (D1–D6, R3/R5/R9/R19/R20/R23): `src/port_driver.py` behind
  `finish-port --drive` — one durable step per invocation, exits
  0 no-work / 2 stopped / 3 progressed / 4 provider-paused / 5 locked;
  `port-ledger.json` (+ history JSONL) with the 16 legacy integrations imported;
  `driver.lock` single-instance with stale-pid reclaim; `events.jsonl` (32 MB
  rotation); real counters mirrored into `run-state.json`;
  `--build-session-index` merged 40 sessions → 6,595 functions latest-wins;
  parse-time rename enrichment (placeholders only — real export names are
  authoritative) took chunk_0048 from 17 to **81/84 eligible units**;
  `command_for` → `--drive`; fake Eagle Jet queue row deleted.
- **Phase 2** (D4, G11/R11/R12/R14/R27): analyzer delta-repair ≤3 structured
  requests/chunk with exact violations fed back; `max_tokens =
  clamp(4096, 90·fn_count+2048, 28672)`; every raw response archived before
  validation; classification lists derived from units; combat-touching patches
  gate on `audit:family-state-machines` + `audit:move-wiring` (both green on
  main); gates already ordered cheap-first.
- **Supervisor**: monitor launches `--drive`; exit-4 → no relaunch until
  `Get-UnslothStatus` answers; `completed` → no hot relaunch; rig.psd1 cmd and
  progress paths updated; dashboard card shows
  `chunks x/80 | units x/84 | functions x/11,980` from the ledger.

## Verified live

- Back-to-back `finish-port` runs: second run exit 0, `api_calls` unchanged.
- kill -9 mid-port → next (monitor-launched) driver resumed the same `porting`
  unit first, rationale recorded.
- Lock: concurrent drive blocked (and a BOM-prefixed lock is honored, not
  reclaimed — utf-8-sig).
- rig task **#7 closed**: `structured_tool_calls` > 0 observed (analysis run
  20:35, port loop continuously after).

## Found live, fixed

1. The historical 20-minute analysis losses were real: tonight's first model
   analysis (81,494 prompt tokens, 10,194 completion) validated-and-died with no
   archive. Raw responses are now archived per attempt.
2. PydanticAI `request_limit = MAX_WORKSPACE_TOOL_CALLS + 1` rejected the first
   live unit (`fun-80195d8c`, 3 attempts) with `UsageLimitExceeded` *after*
   paying generation — the final patch request needs its own slot (+2). Unit
   reset to pending under the driver lock.
3. Session renames must never override real export names: the product anchors
   (`dispatch_challenge_flow_state` @ 0x80195f2c, `init_challenge_flow_state`
   @ 0x80195fbc, `build_challenge_battle_setup` @ 0x801962c4) are export
   symbols; the newer corpus carries mechanical camelCase renames for them.

## Remaining

- Family-priority chunk scoring beyond the seeded `priority_chunks` (Phase 2
  leftover); D8 batch push (per-unit push still in the source loop); Phase 3
  structured export (blocked on llnl/OGhidra#49); Phase 4 legacy-stream
  deletion; per-unit `model_requests_spent` in ledger counters.
- First **integrated** unit still pending: queue is `fun-80195d8c`
  (challenge-flow cluster) and `build-challenge-battle-setup`;
  `dispatch-challenge-flow-state` is a deterministic singleton and waits for
  model analysis per locked decision #2.
