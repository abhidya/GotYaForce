# OGhidra "finish-port" Pipeline — Requirements / Problems / Current-State Distillation (2026-08-06)

Produced by an independent read-only audit agent; verified citations `file:line` against
`D:\GotYaForce\research\tools\OGhidra`. Companion to the rig supervisor work and to
`docs/14_design_review` in the OMR repo. Feeds the driver redesign (rig task #20).

## 0. Executive shape

There are TWO whole pipelines in one CLI, plus a vestigial third:

| Pipeline | Entry | Status | Produced |
|---|---|---|---|
| A. Legacy address stream (`PortScheduler`) | `finish-port --legacy-address-stream` | Dead-by-default since 2026-08-01; only path that ever integrated code | `bundles/` (1136), `source-checkpoints/` (25), `whole-program-manifest.json`, all **16 integrated commits** |
| B. Chunk/unit workflow (`ChunkPortWorkflow`) | `finish-port` (default; any `--mode`) | Currently burning GPU | exactly one file ever: `chunks/chunk_0048/analysis.json` (deterministic, 2026-08-01) |
| C. Artifact/dossier exporters | `export-port`, `prove-incremental-port`, ... | one-shot tools, unwired | `port_artifacts/`, `port_dossiers/` |

`artifacts/` under the run root is created and never written (dead imports in `port_scheduler.py:21-22,334,379`).

**Pipeline A produced 100% of the ported code; A is now unreachable from every used entry point** —
`PortRunController.command_for` (`port_run_controller.py:185-197`) and the GUI "Resume whole-program run"
button both build `finish-port --mode <mode>` with no `--legacy-address-stream`, which silently runs a
single chunk_0048 analysis instead.

## 1. Intended chunk pipeline (spec: `docs/chunk-unit-port-workflow-spec.md`)

Three separate human-in-the-loop invocations — analyze / list-units / port-unit — with "never
automatically port more than the selected unit" (`:102-103`). **The pipeline was designed as a
one-unit-at-a-time tool, not an autonomous driver.** That is the root mismatch with the monitor
relaunching it endlessly.

- `analyze` (`port_chunk_workflow.py:492-575`): parse chunk (`:197-240`), deterministic partition
  (`:287-387`; union-find over name-regex call edges `:214-218` + a 2..8-member shared-global
  heuristic `:259-268`), one structured model request (`:511-539`, `max_tokens` default **32768**
  `:524`), all-or-nothing coverage validation (`:459-474`), atomic write `chunks/<chunk>/analysis.json`.
- `list_units` (`:577-590`): reads analysis, re-hashes chunk (`:585-586` — the cache check that
  `analyze` never uses), stdout only.
- `port_unit` (`:592-664`): hard-fails on `hardware_or_sdk`/`data_or_table` (`:598-601`); fabricates a
  v1 bundle with **empty** `normalized_disassembly`/`normalized_pcode` (`:630-631`); runs
  `SequentialSourcePortLoop` in `chunks/<chunk>/units/<id>`; never writes unit status back —
  `ExecutionUnit.status` is write-only (G7).
- Source loop (`port_source_loop.py:1356-1703`): ≤3 repair attempts × ≤3 workspace tool turns;
  patch allowlist `apps/game/ packages/ scripts/`; validators = semantic integration (`:345-401`) →
  entry-symbol reachability (`:404-468`) → six pnpm gates (`:64-71`) → git commit + push (`:630-660`).
  Attempt evidence dirs (`attempt-NN/`) are the strongest part of the design.

## 2. Key facts about on-disk state

- `whole-program-manifest.json` (schema 2, updated 2026-08-01T13:15): 11,980 functions, 31 bundled,
  **16 integrated / 8 model_invalid / 6 excluded**. `whole-program-manifest.previous.json` shows a
  `--mode fresh` wipe discarded **1,105 bundle registrations** (1136 → 31).
- The 16 integrations land in: `packages/combat/src/{bootGlobals(×9),battle,prng(×3),types}.ts`,
  `packages/render/src/index.ts`, `apps/game/src/main.ts`, `apps/game/src/stages/lighting.ts`.
- 42 MB `analysis_sessions/.../session.json` holds **6,580 curated function summaries** (renames,
  behavior prose). Pipeline B never loads it (§4 of full audit) — the semantic gold behind names
  like `dispatch_challenge_flow_state` is unused by the chunk prompts.
- `control.json` (`run`/`pause_after_stage`/`stop_after_stage`) is read **only** by the legacy path
  (`port_scheduler.py:604-626`); **the chunk path never reads it** — no pause/stop except SIGKILL.
- The chunk path emits **zero** activity events (`activity.jsonl` last event 2026-08-01); per-unit
  loop activity goes to `chunks/<chunk>/units/<id>/activity.jsonl` which the GUI never tails (G23);
  the GUI renders a hardcoded fake "Eagle Jet 0x8012b458" row when `queue` is absent
  (`port_run_controller.py:500-508`, G24).

## 3. Complete gap list (G1–G28, abridged headers)

Sequencing: G1 hardcoded `chunk_0048` (`port_scheduler.py:1447`); G2 `--mode/--session/--max-*`
parsed and discarded on chunk path; G3 default operation is always re-`analyze` — no unit iteration,
no chunk advancement; G4 GUI/controller labels lie (and `recommended_mode()` would pick `fresh`,
which wipes the manifest).

Caching/idempotency: G5 `analyze` never reuses a matching `analysis.json`; G6 a failed later run can
overwrite a good model analysis (no versioning/provenance; current file is `generated_by:
deterministic`); G7 unit status never persisted → no skip-done; G8 `run-state.json` single-slot
clobbered by both pipelines (schema 3 vs 2); G9 no lock/single-instance guard on the chunk path.

Validation: G10 **67/84 units have `FUN_*` runtime_entry_symbols — guaranteed gate rejection after
paying full generation + six pnpm gates**; G11 all-or-nothing coverage check with no
repair-feedback retry, and `max_tokens=32768` is plausibly too small for a 150-address partition
(likely cause of the historical failure loop); G12 deterministic partition yields 72/84
single-function units while the prompt demands 2–40; G13 call graph misses `PTR_FUN_*` indirect
dispatch — the dominant pattern in the combat state machines this project targets
(`state_dispatchers`/`callback_tables` always empty); G14 5-line classification heuristic; G15
non-portable classifications crash `port_unit` instead of skipping.

Error handling: G16 commit-then-push failure reverts working tree but leaves the commit (divergence);
G17 `git push` per unit; G18 provider-unavailable = substring matching, three duplicated marker
lists; G19 `generate_structured` may issue up to 3 requests vs spec's "at most one" and
`model_requests:1` bookkeeping; G21 corrupt session silently degrades to zero grounding.

Observability: G22 no activity events from chunk path; G23 unit activity invisible to GUI; G24
fabricated Eagle Jet row; G25 no progress counts (units x/y, chunks x/80); G26 `activity.jsonl`
122.7 MB unrotated, per-token event lines; G27 adjacent-context carry-over dead on per-unit run
roots; G28 liveness env only set in `main()`.

Smells: `ChunkAnalysis.schema` shadows BaseModel; 3× `atomic_write_json`; hardcoded
`_known_integrated` address; `schedule` discards `dependency_order`; six pnpm gates (incl. browser
smoke) on every attempt with no cheap-first tiering; **OGhidra checkout has uncommitted mods to 7
files and `port_chunk_workflow.py` untracked**.

## 4. What llnl/OGhidra#49 concretely buys pipeline B

The local Java plugin's `/function_bundle` already emits flat P-code + thunk/inline/no_return, but
needs a live CodeBrowser. #49-style structured export **to disk** would: (7.1) replace name-regex
call edges with real call targets; (7.2) replace the shared-global heuristic with SSA def-use over
ram varnodes; (7.3) **populate `state_dispatchers`/`callback_tables` from `CALLIND` + `PTR_FUN_*`
tables — the single highest-value item for combat state machines**; (7.4) fill the bundle's empty
pcode/disasm prompt slots; (7.5) real thunk/inline/no_return offline classification; (7.6)
per-function P-code fingerprints → cross-chunk alias dedup (pipeline A's cost-saver, absent in B);
(7.7) a structural fidelity gate (constants/branches/call-sequence vs P-code) before the pnpm
gates; (7.8) typed varnodes → big-endian struct widths for `GcMemory`/`bootGlobals`.

## 5. Distilled requirements (R1–R27)

Drive & scope: R1 one-command forward progress (analyze if needed → next eligible unit → advance);
R2 flags take effect or are rejected; R3 deterministic next-chunk/next-unit selection with recorded
rationale; R4 legacy-vs-chunk is an honest labelled choice.

Resumability: R5 resume across kills from durable artifacts; R6 skip completed (reuse matching
analysis — check exists at `:585-586`; skip integrated units); R7 idempotent re-runs = zero model
calls, zero commits; R8 never overwrite a paid-for artifact (version + provenance); R9
single-writer lock; R10 separate or merged state namespaces.

Bounded spend: R11 counted request budget per work item (incl. `generate_structured` ladder); R12
prompt/output budgets sized to the answer (32,768 for 150-address partition is a silent failure);
R13 never generate for units that cannot pass (FUN_* symbols, non-portable class); R14
repair-with-feedback for the analyzer (source loop already has it); R15 pause visibly on provider
outage so the supervisor backs off.

Validation: R16 integrated requires the four existing gates, mandatory, with full revert incl. git;
R17 entry symbols must be plausibly reachable in TS, or record the emitted-export mapping; R18
(future, #49) structural fidelity gate.

Observability: R19 machine-readable progress counts at chunk/unit/attempt level; R20 one bounded
event stream, both pipelines, `run_id` on every event; R21 no fabricated UI state; R22 per-attempt
evidence dirs survive everywhere.

Grounding: R23 feed the 6,580-function session corpus to chunk/unit prompts (advisory, fresh
evidence wins); R24 structured decompiler evidence exportable offline (§4); R25 cross-chunk dep
resolution → leaf-first ordering across the program; R26 fingerprint alias dedup at unit
granularity; R27 the unit of value is a combat-family state machine routed to the right package,
validated by the existing family audits (`scripts/audit-family-state-machines.mjs`,
`audit-move-wiring.mjs`) — currently not in `VERIFY_COMMANDS`.
