# Proposal: Port Pipeline — audit, fixes, and roadmap (2026-08-08 evening)

Status: **owner review requested.** Every claim below is verified against source or
live state this session; file:line citations throughout. Companion to
`port-supervisor-design-2026-08-08.md` (morning doc; its items are all closed).

---

## 1. Product goals (the yardstick every fix is measured against)

1. **GotYaForce**: first *integrated* combat unit — the pipeline's own gate-passing
   `git add/commit/push` (`port_source_loop.py:733-763`, invoked at :2058) — then a
   stream of them. Current: 16/11,980 functions, 0/108 units integrated.
2. **Palworld players first**: sub-second protection on join; the supervisor may
   never die silently (the 23h outage) and protection actions may never corrupt
   pipeline state (tonight's 400 storm — see §2.3).
3. **OMR Paper A**: 9,000-run sweep against a closing novelty window; parked at GPU
   priority 3 by owner hold until goal-1's first valid commit.
4. **Rig = the one supervisor and the one pane of glass**: `rig.psd1` declares units,
   gates, priorities; the widget/dashboard is the owner-facing truth. No consoles,
   no bolt-on surfaces, no contradictory signals.

## 2. Audit — what today actually established

### 2.1 Fixed and verified live (all pushed to `abhidya/RustyOGhidra` main)
- Supervisor rebuilt: PS monitor A/B/C fixes → Python watchdog (`src/palworld_watchdog.py`),
  windowless (pythonw task), 11 DI tests; rig dashboard contract (metrics jsonl,
  roster, toast path, reset marker) honored. Commits `9ff3bd5b`(docs)…`b471c4b`.
- Validator bugs that were eating analysis budget:
  - `FUN_/LAB_` placeholder names in address slots rejected whole analyses
    (`normalize_address`, fixed `78ee267`; regression tests).
  - Oversized prompts burned 3 deterministic 400s per chunk
    (preflight added `1013072`; blocks with reason, spends nothing).
- run-state two-writer race closed (`b27d6d5`); reachability gate hardened (`cb25ab4`);
  combat priority chunks live in driver code with startup reconcile (`2b1b459`).
- Rig config: stall detector counts attempt archives, threshold 60 min (`0734bf6`).

### 2.2 Where the milestone hunt stands (live, 19:2x)
- Driver relaunched clean; ledger repaired at rest (12 chunks restored, full budgets).
- chunk_0009 (~102k tokens) fits the served 131,072 context and is next to analyze.
- Tonight's only full port attempt (`startup_init`, boot code) **passed the
  reachability gate** (`main.ts:379` wiring) and failed honestly on typecheck
  (duplicate implementations in `bootGlobals.ts`) — the funnel filters correctly;
  the model's patch discipline is the remaining quality frontier, as the earlier
  hollow-shell finding predicted.

### 2.3 Open defect (the one remaining landmine) — 400 cascade
**Observed twice tonight:** with the model unloaded and the driver alive, every
request fails `HTTPError: 400 Client Error: Bad Request` and the driver burns
3-request budgets per chunk in seconds (8 chunks in 20s at 22:55Z).
**Root cause, refined:** the design already anticipated this — `TRANSIENT_MARKERS`
includes `"no model loaded"` (`port_chunk_workflow.py:54-62`) — but the raised
exception is the bare `raise_for_status()` string, which **discards the response
body** where the server actually says "no model loaded". The marker can never match.
**Exposure:** player-join protection unloads the model (`palworld_watchdog.py`
`unload_force`) up to `stop_grace_seconds` before the kill lands → every join risks
a mini-storm. Manual/maintenance unloads have the same window.

### 2.3b Incident addendum (19:15, after this doc's first draft) — BOM provider flip
A `.env` rewrite performed with PowerShell `Set-Content -Encoding UTF8` added a
UTF-8 BOM, corrupting the first env key; provider resolution fell back to
**OllamaClient**, which lacks `generate_structured` — in ~2 minutes the driver
wrongly blocked 7 chunks and terminally rejected 7 units (`AttributeError` /
`TypeError: unexpected keyword argument 'tools'`). Contained: BOM stripped,
targeted ledger repair (legitimate verdicts preserved), provider verified
(`CustomAPIClient`) before relaunch. This is the third time a PS-side write
default caused pipeline damage (JSON BOM trap, `Move-Item` non-atomicity, now
dotenv BOM) — it reinforces the no-PS-tooling rule and adds one hardening item
to Proposal A: load `.env` BOM-tolerantly (`load_dotenv(encoding="utf-8-sig")`
in `main.py:13`) and fail LOUDLY on unknown provider fallback instead of
silently substituting Ollama (`_llm_for_config`).

### 2.4 Structural finding — two supervisors
The rig declares supervision (units, gates, priorities, verbs — `rig.ps1:211-279`)
but has **no resident enforcement loop**; `mode='manage'` exists only as intent
(`rig.psd1` omr comment "switch to manage only after probes are proven"). The PS
monitor, and now the Python watchdog, each filled that vacuum from *outside* the
rig — the watchdog even lives in the worker's repo. Consequences: two readers of
the palworld gate, two managers of unsloth, bolt-on widget hacks to make the
out-of-tree supervisor visible.

### 2.5 Hardware truth (measured, not assumed)
- 131,072 ctx f16 KV serving leaves 398 MiB + 1,872 MiB free (nvidia-smi, mid-gen).
- Studio auto-clamps requested 262,144 → 131,072 (`requested_context_length`
  observed); it will do so on every automated reload.
- Five priority chunks exceed the served context (server-measured prompt tokens):
  0007=141,173 · 0003=162,370 · 0004=193,030 · 0006=158,239 · 0002=140,326.
- `studio.db app_settings` carries a per-model override
  `{custom_context_length: 262144, kv_cache_dtype: "q8_0"}` for this exact quant —
  **contradicts the owner's f16 rule** if the studio ever applies it.

## 3. Proposal A — error-body propagation (the 400 fix)

**Design.** In the API client, when an HTTP error status is raised, append the first
~300 chars of `response.text` to the exception message. No new control flow: the
existing `TRANSIENT_MARKERS` check (`port_chunk_workflow.py:739`) then matches
"no model loaded" naturally → `ProviderUnavailable` → driver pauses (exit 4), spends
nothing, watchdog reloads, driver resumes. One regression test: a 400 whose body
says "no model loaded" must pause, not fail.

**Pros:** ~10 lines; uses the design's own recovery path; closes the player-join
corruption window; also improves every future error report (bodies visible).
**Cons / adversarial:**
- A *legitimate* 400 whose body happens to contain a transient marker would pause
  instead of fail → infinite pause/resume loop? Mitigated: watchdog reloads the
  model, after which the same request either succeeds or fails with a non-transient
  body; the pause is self-limiting.
- Oversized prompts also 400 ("Message too long") — must NOT become transient.
  Verified: no marker matches that body, and the preflight (`1013072`) prevents the
  request entirely.
- Alternative rejected: probing `/api/inference/status` inside the workflow's
  exception handler — couples the workflow to the provider's management API and
  duplicates watchdog knowledge.

**Cost:** small. **Risk:** low. **Asks owner:** yes/no tonight.

## 4. Proposal B — big-chunk strategy (four alternatives, one recommendation)

| Alternative | Coverage | Quality | Hardware risk | Throughput | Verdict |
|---|---|---|---|---|---|
| B1 Chunk splitting at 131k | all 80 chunks | f16, unchanged | none | best (prompts stay ~100k; prefill scales superlinearly) | **recommended** |
| B2 262k f16 + MoE experts on CPU | all | unchanged | none, but decode/prefill collapses (hours/attempt) | worst | rejected by owner (GPU-only) |
| B3 Probe max GPU-resident f16 ctx (~160-230k?) | partial (0004 likely misses) | unchanged | load experiments, auto-clamp opacity | poor at >150k prompts on Pascal | rejected by owner (no probing churn) |
| B4 q8_0 KV @ 262k | all | KV precision reduced | none | good | **rejected by owner (f16 rule)** |

**B1 design sketch (the only engineering item):** the analysis prompt builder
(`_model_prompt`) takes a `ParsedChunk`; add a deterministic pre-splitter that
partitions an oversized chunk's functions into windows under a token budget
(split on call-graph community boundaries the deterministic analyzer already
computes; overlap = the cross-window `external_dependencies` list). Each window
gets its own analysis; a mechanical merge validates whole-chunk coverage (same
validator, run over the union). Ledger: per-window request accounting under the
chunk's record. Estimated effort: one focused session + tests.
**Adversarial:** unit coherence across windows is the real risk — a family split
across windows yields two half-units. Mitigation: windows follow the deterministic
call-graph partition (families are exactly its communities), and the merge step
re-runs `_validate_model_analysis` over the union so coverage errors surface as
repairable, not silent. Worst case a window boundary costs one repair round.
**Not blocking the milestone:** chunk_0009 + chunk_0048 + 74 normal-size chunks are
analyzable today; B1 unblocks 0007/0003/0004/0006/0002 (4 of the 6 combat-core
priorities), so it is the highest-value post-milestone engineering.

## 5. Proposal C — rig manage engine (ending the two-supervisor era)

**Design.** Promote the watchdog's logic into `D:\rig\engine.py` (Python, windowless,
one scheduled task): a generic loop that reads `rig.psd1`, and for every unit with
`mode='manage'` enforces lifecycle — launch when its gate opens, cooperative-stop +
kill + dependency unload when it closes, exit-code policy, crash/lock guards,
heartbeat into the unit's own card. oghidra flips to `mode='manage'`; unsloth
becomes a managed dependency (`depends_on` already exists in the manifest); the
OGhidra-side watchdog is deleted. The widget needs zero special cases because
managed state *is* rig state. Collector's health arbitration (degraded = stalled
AND heartbeat-silent) lands here as engine-owned Python, honoring the no-PS rule.
**Pros:** one supervisor (the owner's stated architecture); omr-sweep GPU
arbitration becomes a manifest edit, not a new system; kills the entire class of
"bolt-on visibility" hacks; HANDOFF Phase 5 (GPU lease + queue) gets its natural home.
**Cons / adversarial:**
- Biggest change of the three; supervision churn is what made tonight messy — do it
  **after** the first integrated unit, never concurrent with the milestone hunt.
- Generic manage loops grow policy warts (per-unit exit-code maps, backoffs). Scope
  guard: engine v1 manages exactly two units (oghidra, unsloth-as-dependency);
  everything else stays `observe`.
- Migration risk of a second 23h-style gap → mitigation: cutover identical to
  tonight's (old task disabled not deleted; rollback is one `Start-ScheduledTask`).
**Cost:** 1-2 focused sessions. **Risk:** medium, schedule-gated.

## 6. Sequenced plan (no ambiguity about order)

1. **Tonight, standing:** monitor to first valid oghidra commit; fix only what the
   watcher surfaces. On the commit: notify owner → flip omr-sweep to priority 1 /
   oghidra to 3 (owner's standing instruction) → notify on OMR's first ledger append.
2. **Tonight, on approval:** Proposal A (error-body propagation).
3. **Next session:** Proposal B1 (chunk splitting) — unblocks 4 of 6 combat-core chunks.
4. **After milestone + B1:** Proposal C (rig manage engine), single project, with the
   widget arbitration fix inside it.
5. **Housekeeping awaiting owner yes/no:** delete the `studio.db` q8_0 override
   (contradicts f16 rule); decide GitHub remotes for the rig and monitor repos
   (currently local-only).

## 7. Open questions for the owner

1. Approve Proposal A tonight? (small, closes the player-join corruption window)
2. Approve B1 as the big-chunk strategy? (B2/B3/B4 are recorded as rejected)
3. Approve C's schedule gate (post-milestone, post-B1)?
4. Delete the q8_0 studio.db override?
5. Remotes for `D:\rig` / monitor repos, or keep local-only?
