# Design: OGhidra Port Driver (rig task #20) — 2026-08-06

Architect-agent output, grounded in `port-pipeline-distillation-2026-08-06.md` (gaps G1–G28,
requirements R1–R27). Status: **awaiting owner sign-off; no code written.**

## 1. Architecture

```
finish-port --drive [--units N] [--chunk X] [--mode resume]
        │
        ▼
src/port_driver.py :: PortDriver          (NEW, ~400-600 lines, policy only)
  ├─ acquire driver.lock (R9)
  ├─ load port-ledger.json (durable truth, R5)
  ├─ check control.json (R15)                      ── ported from PortScheduler._check_control
  ├─ SELECT next work item (R3, recorded rationale)
  ├─ ensure analysis:  load_analysis / analyze     (existing mechanism)
  │       └─ NEW: repair-feedback wrapper (R14) + output budget (R12)
  ├─ eligibility gate (R13, G10/G12/G15) — before any generation
  ├─ port one unit:    port_unit → SequentialSourcePortLoop  (existing validators/attempt dirs)
  ├─ write ledger + emit events (R19/R20) + update run-state.json
  └─ exit: 0 no-work-left · 3 progressed-more-remains · 4 provider-paused · 2 stopped
```

**Core principle:** `ChunkPortWorkflow` / `SequentialSourcePortLoop` stay *mechanisms* (the
audited-good parts). All *policy* — what next, skip-done, budgets, eligibility, git cadence,
events, control — lives in the new `PortDriver`. The spec's interactive commands
(`--analyze-chunk`, `--list-units`, `--port-unit`) stay untouched for the owner.

## 2. D1 — Driver architecture

New `src/port_driver.py`, wired as `finish-port --drive`. `PortRunController.command_for` emits
`--drive`, making the supervisor's relaunch honest (fixes G2/G3/G4 at the entry).
One invocation = one durable step (analyze-if-needed OR port-one-unit), then exit; default
`--units 1`, supervisor relaunches to advance; `--until-blocked` for the owner. SIGKILL loses at
most one in-flight request — ledger + immutable attempt dirs make resume exact (R5).
Rejected: loop inside ChunkPortWorkflow (policy in mechanism); retrofitting legacy stream_units
(welded to manifest schema 2 + live Ghidra); external PS loop (no lock/state — how G3 happened).

## 3. D2 — Work selection

1. **Chunk order:** owner-editable `priority_chunks` in the ledger, seeded by combat-family
   relevance scoring (session-corpus renamed symbols × family audits, R27). chunk_0048 first.
2. **Unit order:** eligible-only, leaf-first *within chunk*, ties by address. Cross-chunk
   leaf-first deferred to Phase 3 (G13: regex call edges miss PTR_FUN_* dispatch — a global
   topo order from them would be confidently wrong).
3. **Skip rules:** terminal ledger statuses; fingerprint dupes (Phase-3-gated; degraded mode =
   body-sha exact dupes).

## 4. D3 — State model & ledger

New durable `port-ledger.json` (atomic writes, single writer via lock) + append-only
`ledger-history.jsonl`. `run-state.json` stays the live GUI snapshot; legacy manifest becomes a
frozen read-once import; analysis gets **versioned writes** (`analysis.v{N}.json`, provenance rank
model > saved > deterministic; never overwrite better with worse — G5/G6/R8).

Ledger schema (abridged; see agent output for the full example):

```json
{
  "ledger_schema": 1,
  "priority_chunks": ["chunk_0048", "..."],
  "counters": {"chunks_analyzed": 1, "units_integrated": 0, "functions_integrated": 16,
                "model_requests_total": 3, "commits_unpushed": 0},
  "imported_legacy": {"integrated_addresses": ["0x800bd6a8", "…15 more"]},
  "chunks": {"chunk_0048": {
    "analysis": {"current_version": 2, "chunk_sha256": "…", "generated_by": "model",
                  "model_requests_spent": 2, "repair_rounds": 1, "evidence_tier": "text_only"},
    "units": {"challenge-controller": {
      "status": "integrated", "eligibility": "eligible",
      "entry_symbols": ["dispatch_challenge_flow_state"],
      "attempts_spent": 2, "model_requests_spent": 5,
      "commit": "9f3ac21…", "pushed": false,
      "files": ["packages/combat/src/challenge.ts"],
      "selection_rationale": "leaf_first_in_chunk"}}}}
}
```

Unit status: `pending|analyzing|porting|integrated|rejected_final|skipped|alias|paused_provider`.
Eligibility: `eligible|ineligible_fun_entry|ineligible_classification|
ineligible_singleton_pending_model|duplicate_fingerprint`. Closes G7.

## 5. D4 — Eligibility + analyzer repair (the G10/G11/G12 fix)

Eligible iff: (1) classification ∈ {game_owned, shared_runtime} (G15: skip, never crash);
(2) after **session-rename enrichment**, ≥1 entry symbol not matching `^(FUN|LAB)_[0-9a-f]{8}$`
(G10 — the single check that stops the current GPU waste); (3) not a dup fingerprint.
Singletons from deterministic analyses are `ineligible_singleton_pending_model` (G12).

Analyzer: model no longer re-emits the functions list; `max_tokens = clamp(4096, 90·fn_count+2048,
28672)`; truncation detected via finish-reason and treated as repairable; ≤2 delta-repair rounds
feeding exact coverage violations back ("reassign only these addresses"); total budget 3 structured
requests per chunk analysis, ledger-counted (R11/R12/R14). All-fail → archived with
`model_failed` provenance, chunk marked `analysis_blocked`, move on.

## 6. D5 — Session grounding (R23)

One-time `finish-port --build-session-index`: merge all `analysis_sessions/*/session.json`
(latest-timestamp-wins per address, ~6,580 entries, summaries truncated ~600 chars) →
`session-index.json`; refuse to write an index below a floor (corrupt-session guard, G21).
Consumed at: parse-time rename map (unlocks eligibility), analysis prompt one-liners
(~40 tok/fn), unit prompt full summaries (~8k tok cap) framed as advisory / fresh-evidence-wins.
Rejected: runtime RAG (infra weight for a corpus that fits in context per-unit).

## 7. D6 — Control + events

Driver checks `control.json` at every stage boundary (stop → exit 2 flushed; pause → poll with
`run-state.status=paused`); provider outage → `paused_provider`, exit 4 so the supervisor backs
off via LLM liveness. One `events.jsonl` (rotate 32 MB, never per-token — G26); unit-level
activity stays per-unit with `unit_activity_path` emitted so the GUI can tail (G23). 12 events:
driver_started, selection, analysis_started/done/blocked, unit_started/attempt/integrated/
rejected/skipped, provider_paused, driver_stopped, progress (chunks x/80, units x/known,
functions x/11,972 → mirrors into run-state for the rig dashboard; fake Eagle Jet row deleted).

## 8. D7 — Structured-export contract (#11)

`research/decomp/ghidra-export/structured/` — `_export-meta.json`, `_functions-index.tsv`,
`chunk_NNNN/0xADDR.json` per function: signature, thunk/inline/no_return, callsites (incl.
CALLIND + resolved PTR_FUN_* tables), callers, ram def-use varnodes, CFG blocks, pcode,
constants, normalized-pcode fingerprint, data_tables. One-time headless dump when a CodeBrowser
is next up. Driver records `evidence_tier` per chunk; every feature degrades gracefully:
call edges (real vs regex), grouping (SSA vs token heuristic), **dispatcher/callback detection —
the combat-state-machine payoff** (vs empty), bundle pcode slots, fingerprint dedup, structural
fidelity gate (R18), cross-chunk leaf-first (R25).

## 9. D8 — Git policy

Commit stays per-unit after green gates (revert story intact, R16); **push removed from the
per-unit path** (dissolves G16+G17). Batch push at exit + every `--push-every 5`; push failure
non-fatal, ledger-tracked, retried. Modes: `--git commit` (default) | `commit-push` | `none`
(dry-run). Undo = `git revert <ledger.commit>` + status flip.

## 10. D9 — Pipeline A disposition

Port its patterns (control checks, progress/ETA shape, 0/2/3/4 exit codes, provider-pause);
import its data once (16 integrated addresses + fingerprints → `imported_legacy`; manifest frozen
thereafter — prevents another `--mode fresh` wipe); quarantine `--legacy-address-stream` behind a
deprecation banner + `--i-understand-manifest-wipe` for fresh; delete the streaming body in
Phase 4 only after the driver has its first end-to-end integrations.

## 11. D10 — Staged rollout

**Phase 0 — stop the burn (same day, pre-driver):**
(1) commit the dirty OGhidra checkout to a branch FIRST; (2) chunk path reuses `load_analysis`
on sha match (stops re-analyze churn); (3) `port_unit` eligibility pre-check (skip
non-portable + all-FUN_* before any model call); (4) reject ignored flags; check control.json
once at start. Verify: back-to-back runs → zero model requests on the second; FUN_* unit →
`skipped` with reason, zero requests.

**Phase 1 — driver + ledger + grounding (~1 wk):** port_driver.py, ledger + legacy import,
`--drive`, lock, events + progress, session index + rename enrichment, command_for → `--drive`,
GUI fake-row removal. Verify: kill -9 mid-port resumes exactly; all-terminal → exit 0 zero
requests zero commits; dashboard shows real counts; concurrent drive → lock.

**Phase 2 — make units passable (~1 wk):** analyzer repair + scaled max_tokens; singleton
policy; family-priority scoring; family audits added to VERIFY_COMMANDS for combat units (R27);
gate tiering cheap-first. Verify: chunk_0048 model analysis ≤3 requests, 100% coverage; a real
unit reaches gates with non-FUN symbols; broken patch dies at typecheck, not browser smoke.

**Phase 3 — structured evidence:** one-time export, evidence_tier switch, fingerprint dedup,
dispatcher detection, fidelity gate, cross-chunk leaf-first.

**Phase 4 — cleanup:** delete legacy streaming body, dead imports, dedupe 3× atomic_write_json
+ 3× transient-marker lists, GUI honesty pass.

## 12. Open questions for the owner (recommendations attached)

1. Push cadence `--push-every 5` + push-on-exit, failures non-fatal? **Recommend yes.**
2. Port deterministic multi-function units before a chunk has model analysis? **Recommend yes**
   (faster to first combat port); singletons always wait.
3. Supervisor treats exit 4 with liveness-gated backoff (no relaunch until LLM up)?
   **Recommend yes** — one rig-monitor change.
4. Session-index merge: latest-timestamp-wins across ALL sessions vs newest-only?
   **Recommend latest-wins merge.**
5. Analyzer cap: scaled-with-repair (28,672 ceiling) vs raising the flat 32,768?
   **Recommend scaled-with-repair.**
