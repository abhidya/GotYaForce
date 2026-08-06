# Next-session prompt — port driver Phase 0/1 + OMR pre-run fixes

Copy everything below the line into a fresh Claude Code session started in `D:\GotYaForce`.

---

## Prompt

Implement the OGhidra port driver per the approved design, then the rig backoff change. Work
autonomously; ask only when a decision isn't covered by the docs below.

**Required reading first (in order):**
1. `research/decomp/port-driver-design-2026-08-06.md` — the approved design (D1–D10, ledger
   schema, staged rollout). All five §12 open questions are DECIDED: take every recommendation
   (batch push every 5 + on exit; deterministic units may port early *only if combat-relevant —
   see product ordering below*; exit-4 liveness backoff yes; session merge latest-wins; analyzer
   scaled-with-repair).
2. `research/decomp/port-pipeline-distillation-2026-08-06.md` — ground truth for gaps G1–G28 and
   requirements R1–R27. Cite these IDs in commits.
3. `D:\rig\HANDOFF.md` — the supervisor/monitoring stack you must stay compatible with.

**Product ordering (overrides generic sequencing):** the product is faithful browser combat,
family-by-family. The FIRST ported unit must be the chunk_0048 challenge-flow controller
(session corpus names: `dispatch_challenge_flow_state`, `init_challenge_flow_state`,
`build_challenge_battle_setup`). Session-rename enrichment is the critical path, not a nicety.
Do not port arbitrary deterministic units just to prove the loop.

**Task 1 — Phase 0 (same session, before the driver):**
The OGhidra baseline is already committed+pushed (`abhidya/RustyOGhidra` main, commit 7ea31e8).
a. Chunk path reuses `load_analysis` on chunk-sha match instead of unconditional re-analyze
   (G3/G5). b. `port_unit` eligibility pre-check: skip (typed result, never crash)
   hardware_or_sdk/data_or_table and all-FUN_* entry units before any model call (G10/G15/R13).
c. Error out on silently-ignored flags (G2/R2). d. Check `control.json` once at chunk-path start.
VERIFY: two back-to-back `finish-port` runs → second makes ZERO model requests (assert via
`llm-liveness.json` api_calls); `--port-unit` on a FUN_*-only unit → skipped, zero requests;
existing pytest suites still green (`tests/test_port_chunk_workflow.py` etc.).

**Task 2 — Phase 1 (driver + ledger + grounding):** per design §D1–D6:
`src/port_driver.py` (+`--drive` in `port_scheduler.main`), `port-ledger.json` with legacy import
of the 16 integrated addresses from `whole-program-manifest.json`, single-instance lock,
`events.jsonl` (rotate 32MB, never per-token) + progress mirrored into `run-state.json`,
`--build-session-index` (merge `analysis_sessions/*/session.json`, latest-wins, floor guard) and
rename enrichment at parse time, `PortRunController.command_for` → `--drive`, delete the fake
Eagle Jet queue row (`port_run_controller.py:~500-508`).
VERIFY (all four from design §D10 Phase 1): kill -9 mid-port resumes exactly; all-terminal →
exit 0/zero requests/zero commits; rig dashboard (localhost:7800) shows real unit/chunk counts;
concurrent `--drive` blocked by lock.

**Task 3 — rig monitor exit-4 backoff:** in
`D:\Palworld_Server_Setup\monitor\palworld-oghidra-monitor.ps1`, before Start-OGhidraResume:
if the last driver exit was 4 (provider paused), do not relaunch until unsloth answers
`Get-UnslothStatus` (lib already dot-sourced). Parse-check + restart the monitor task
(children survive; verified pattern in HANDOFF).

**Task 4 — Phase 2 (if time remains):** analyzer delta-repair loop + scaled max_tokens
(`clamp(4096, 90*fn_count+2048, 28672)`, truncation-detected repair, ≤3 requests/chunk,
ledger-counted); singleton policy; family-priority chunk scoring; append
`scripts/audit-family-state-machines.mjs` + `audit-move-wiring.mjs` to VERIFY_COMMANDS for
combat-target units; reorder gates cheap-first (typecheck → combat build → selfchecks → game
build → browser smoke).

**Watchpoints while working:**
- `rig status` / dashboard: oghidra card shows live tok/s + prompt; `structured_tool_calls > 0`
  in `llm-liveness.json` closes rig task #7 — report it when it happens.
- Commit to OGhidra fork main + GotYaForce main as you complete each task; small commits citing
  G/R IDs.
- Traps: LM Studio answers unknown routes HTTP 200 + error body (shape-validate); Win32_Process
  CommandLine is null for elevated procs; "files changing" ≠ progress — durable artifacts only.

**Separate track (owner's attention, do NOT automate):** OMR pre-run fixes in
`D:\Research\open-model-research-starter-2026-08-03\docs\14_design_review_2026-08-06.md` — the
60-task prompt grid (strata 4/5 expanded to carry primary ground truth), randomized run schedule,
12-task sub-pilot for ICC/MDE, llama-server decision, schema hardening (10-min edit, review §9).
The novelty window for Track A is closing (~12-month cycles). Note: OMR is NOT a git repo — the
owner may want `git init` there first.
