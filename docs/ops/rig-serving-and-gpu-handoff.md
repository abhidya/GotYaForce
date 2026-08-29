# Rig, model serving, and external-GPU handoff

**Provenance.** Rescued 2026-08-29 from untracked session audits dated 2026-08-21
(`omr-handoff-integrity-audit`, `lmstudio-purge-audit`, `oghidra-lmstudio-residual-audit`,
`rig-omr-handoff-review`, the `backup-health-*` trio) and 2026-08-22/23 status notes.

**Scope note.** Most of this describes machines and repositories *outside* GotYaForce —
`D:\rig` (the supervisor), `D:\Research\open-model-research-starter-*` (OMR), and the
nested `research/tools/OGhidra` checkout. It is kept here because the port pipeline depends
on all of them and because the traps were expensive to find. **This is exactly the
"private operations runbook" material that
[`../audits/public-repo-readiness.md`](../audits/public-repo-readiness.md) §2.5 says should
be split out of a public repository.** If that split is made, this file moves with it.

**Status.** Findings re-checked only where they touch the GotYaForce tree; the rest are
dated evidence. Commit SHAs are labelled with their repository.

---

## 1. The serving topology, stated once

```
scheduled task "rig supervisor"  (D:\rig\supervisor\)
  owns the machine: starts/stops the driver, loads/unloads the model,
  enforces the manual gate, reaps zombie generations
        |
Unsloth serving slot — 127.0.0.1:8888, ONE model resident
  admin API under /api/inference/*
        |
port driver — src/port_wasm_units.py in research/tools/OGhidra
```

The serving contract that must not change:

- Unsloth Studio executable and llama.cpp paths in `D:\rig\supervisor/config.py`;
- **one** serving slot on `127.0.0.1:8888`;
- model identity and context resolved from OGhidra's authoritative configuration;
- a load payload containing exactly `model_path`, the required `gguf_variant`, and
  `max_seq_length` — **no** `llama_extra_args`, cache, parallelism, speculative, GPU, or
  batch overrides. Omitting cache settings preserves Studio's default F16;
- response-shape validation and the object-shaped `tool_choice` preflight;
- force-cancel / unload / release verification, and all manual-gate behaviour.

**Port 1234 was never the chat slot.** It was an LM Studio *embeddings* server. Conflating
the two is the single most expensive misconception recorded in this archive.

---

## 2. LM Studio: why it was removed, and what it left behind

### The removal decision (rig side)

The LM Studio embeddings integration was **not used by the port workflow**, and it was not
"non-blocking" either: on a work-bearing launch the supervisor could spend up to three
120-second subprocess timeouts starting an unrelated embeddings server *before* it started
the Unsloth slot.

```
enable_heavy_work() -> work exists and launch not throttled
  -> embeddings_sync()
     -> GET http://127.0.0.1:1234/v1/models
     -> C:\Users\manny\.lmstudio\bin\lms.exe daemon up
     -> lms.exe server start --port 1234
     -> lms.exe load text-embedding-nomic-embed-text-v1.5
  -> ServingSlot on 127.0.0.1:8888
  -> Unsloth default model load
  -> port driver
```

**That ownership edge is why stopping the application by hand was never durable** — the
next eligible work launch simply started it again. No Windows scheduled task ever matched
`LM Studio`, `lms.exe`, or port 1234; the supervisor was the launcher.

A case-insensitive scan of tracked `D:\rig` found 14 paths, 13 genuine (4 operational
runtime/config, 4 test wiring, 1 safety wording, 4 docs/generated dashboard) and exactly one
false positive — `1234` used as a fake PID in `tests/test_process_and_startup.py`.

**Vendor-neutralize, do not delete, the safety machinery.** The shape checks
(`require_fields`, `reject_fields`) and the object-shaped `tool_choice` preflight protect
port 8888 from *any* wrong process; they are not LM Studio dependencies. The same applies
to `test_impersonating_server_is_rejected_by_shape` and
`test_supervisor_config_has_no_llama_extra_args_override` — rename vendor-specifically,
keep every assertion.

Also: Unsloth's own model and log vocabulary contains generic "embedding" tensor and
settings names. Those belong to Unsloth/llama.cpp and must not be purged.

### The residue that reaches into this repository

The autonomous port does **not** use embeddings. `.env` selects
`OGHIDRA_PORT_MODE=wasm_units`, which dispatches to `WasmUnitDriver`, which constructs
`CustomAPIClient` only for chat generation. Nothing on that path reaches `build_gf_kb.py`,
CAG, `data/vector_db`, or `CustomAPIClient.embed()`.

Three compatibility residues remained:

1. **`research/tools/OGhidra/.env`** (ignored, authoritative) declares
   `CUSTOM_API_EMBEDDING_MODEL=text-embedding-nomic-embed-text-v1.5` and
   `CUSTOM_API_EMBEDDING_URL=http://10.0.0.205:1234`. Loaded into `CustomAPIConfig`, never
   called by the wasm-unit driver. `port-model.env.example` is tracked and can recreate
   both.
2. **The live LLM interaction log has a misleading legacy name.** `.env` sets
   `LLM_LOG_FILE=logs/llm_interactions_lmstudio_nemotron3.json`, but its recent records say
   `provider: custom_api`, model `unsloth/Qwen3.8-27B-GGUF`, phases such as
   `wasm_diagnosis:unit-a`. **The name is legacy; the content is not LM Studio traffic.**
3. **`D:\rig\rig.psd1` consumes that exact filename** to reconstruct the latest prompt for
   status and dashboard output.

**The trap:** repointing only the rig manifest to `logs/llm_interactions_custom.log` is
unsafe — that file is a different, older producer history whose most recent entries used the
placeholder `https://api.example.com`. Doing so silently removes live prompt visibility.

**The safe migration**, as a single reviewed deployment while the gate is paused:
choose a neutral path (`logs/port-llm-interactions.jsonl` — the `.jsonl` suffix matches the
actual one-object-per-line format); change the ignored authoritative `.env` **only** at
`LLM_LOG_FILE`; update the tracked `port-model.env.example` and drop the two embedding keys
from the autonomous-port profile; update `rig.psd1` to the same absolute neutral path in the
same window; **do not rename the three existing log files in place** (35.4 MiB current, plus
49.9 MiB and 443.1 MiB rotations) — rotating the producer to a new base freezes them as
historical evidence and avoids a multi-hundred-MiB move, open-handle races, and broken RCA
references. On the authorized resume, verify one matching `generate_request` /
`generate_response` pair appears at the new path and surfaces in `units[].llm_request`.

Executable-but-out-of-path leftovers, for the public-repo cleanup rather than live repair:
`research/tools/OGhidra/build_gf_kb.py` (hard-codes `http://10.0.0.205:1234/v1/embeddings`,
no call site), `research/decomp/port-supervisor/palworld-oghidra-monitor.ps1` (retired
monitor that dot-sources two absent helpers; the scheduled task points at `D:\rig` instead),
and `scripts/deobfuscate.py` / `scripts/test-lmstudio.py` (standalone, not imported by the
port). Keep concise RCA in docs rather than executable dead paths.

**A machine-wide "all dependencies purged" claim is false** until the OGhidra embedding
configuration and the log-path migration are both done. Removing code prevents future
supervisor starts; it does not stop an already-running external application. Uninstalling
is an owner action.

---

## 3. The GPU handoff is not a lease — three P0 integrity defects

Audited 2026-08-21 against `D:\Research\open-model-research-starter-2026-08-03` at `a25e9e2`
(especially `4ae518b`) plus the append-only results ledger and rig logs.

### 3.1 The owner's manual gate is being used as a GPU lease

`sweep.py:46-101` constructs `RigGate` over `D:\rig\state\status.json`, reads `gates.manual`,
and requires the `unsloth` unit to be `running`. `sweep.py:163-190` then directly unloads the
resident model and loads the requested rung — **with no lease token, ownership epoch,
supervisor acknowledgement, or revocation check.** `sweep.py:550-555` checks the gate before
a run and then mutates the one-model serving slot: a time-of-check observation, not an
exclusive right that survives load and chat.

**That gate cannot arbitrate this handoff, because the two requirements are opposites.** The
documented external-GPU procedure requires the manual gate **paused** and the supervisor
scheduled task **disabled or stopped** — a paused-but-live supervisor still enforces its
configured model. OMR instead waits for that same gate to be **open**.

The conflict is not hypothetical. `D:\rig\logs\supervisor\supervisor.log`, 2026-08-20
18:40:13-04:00: the restarted supervisor logged *"evicting `D:\models\Qwen\Qwen3-8B-GGUF`:
configured model is `unsloth/Qwen3.8-27B-GGUF`"*, then relaunched the port driver — killing
the external workload's model mid-run.

This is a module-boundary error: `RigGate` exposes availability as a boolean while hiding
none of the hard lifecycle.

**The correct shape — a supervisor-owned exclusive lease:**

```python
with lease_client.acquire(owner="omr-sweep", request_id=uuid, ttl_s=300) as lease:
    lease.assert_valid()          # immediately before every load AND every chat
    backend.load_exact(model)
```

A request is not authority. A **grant** contains at least a `lease_id`, an unpredictable
token, a monotonic epoch, the owner, grant and expiry timestamps, and the exact released
resource. The supervisor grants only after the port driver is null, active generations are
cancelled, its model is unloaded, and release is *verified*. While granted, supervisor mode
is `external-leased`: it does not relaunch the driver or enforce its configured model.
Closing the owner manual gate, expiry, or an explicit revoke invalidates the lease.

Add a **separate OMR intent gate** (e.g. `omr-gate.json`) that enables this workload only.
It never substitutes for the owner's manual emergency gate and never grants GPU ownership;
OMR must respect both, plus a live lease. **OMR itself must never toggle the shared gate or
the scheduled task.** Until the lease exists, the only safe handoff is the documented manual
pause plus scheduled-task disable, and autonomous OMR must fail closed.

### 3.2 The resume key crosses model and protocol boundaries

`run_id_for` is only `experiment|quant|set-index|seed` (`sweep.py:404-405`), and
`completed_ids` accepts every complete record by that ID alone (`:408-427`). Model revision
and GGUF hashes are written as fields *afterwards* (`:567-588`) and do not participate in the
lookup key.

Commit `4ae518b` changed Qwen2.5 → Qwen3 in **`sweep.json` only** — 28 lines, no runner, ID,
or ledger migration. The ledger then held **64 complete Qwen2.5 records and 67 complete
Qwen3 records under the same human-form IDs**, and all 64 Qwen2.5 IDs are valid members of
the unchanged namespace, so they were treated as Qwen3 completions.
`D:\rig\logs\omr-sweep.out.log` started the Qwen3 run with `already complete: 91
(resuming)` — 64 Qwen2.5 plus 27 earlier Qwen3.

Second integrity warning from the same commit: `sweep.json:93` still points to
`ladder.json`, whose manifest names a Qwen2.5 revision `bb5d59e…`, and `sweep.py` never
reads or validates `ladder_manifest`.

**The fix is a content-addressed identity:**
`run_id_v2 = "run-v2-" + sha256(canonical_json(identity))`, whose preimage includes the
experiment and protocol version; the runner source-tree digest (or a clean commit plus an
explicit clean-tree assertion); a canonical config-snapshot digest; the source repo and
immutable revision; the quant ID, GGUF variant, and ordered GGUF content digests **verified
against the bytes actually loaded**; the prompt-set revision, prompt index, and prompt
content hash; sampling parameters, retry policy, context size, and an explicit reasoning
policy; the backend build, llama.cpp revision, chat-template hash, and exact live
served-model identity; and extractor/template hashes plus oracle-snapshot content identity.
Exclude timestamps, filesystem spelling, lease token, run index, and host PID — record them
separately.

### 3.3 Thinking-only responses were recorded as complete empty answers

`sweep.py:192-206` discards the response envelope and returns only `message.content or ""`,
losing `reasoning_content`, finish reason, usage, response model, and the raw response.
`:598-607` hashes that possibly-empty string. `:636-642` requires only a **nonempty
`raw_output_sha256`** — and SHA-256 of the empty string is itself a nonempty string, so the
check passes.

**Forty Qwen3 records** have `output_chars: 0`,
`raw_output_sha256 = e3b0c442…b855` (the empty-string hash), zero extraction, and
`status: "complete"`.

Exact correlated example: row
`paper-a-quantized-namespaces|Q6_K|SO_LY-4409|s11` at 2026-08-20T23:19:32Z records empty
content as complete with `wall_clock_s: 74.05`. Server log
`llama-1787267665-port-50227-try0.log` started at 23:14:25Z, shows `enable_thinking`
enabled, starts the corresponding main request at +5:11, and **generates exactly 2,048
tokens in 59.8 seconds**; two 64-token follow-ups finish before the row's 74-second wall
time. Generated reasoning was discarded and an absent final answer was accepted.

**The fix:** the backend adapter returns a structured `ChatTurn`, not a string — `content`,
`reasoning_content`, finish reason, response/model ID, usage counts, and a canonical
raw-envelope hash, with separate hashes and lengths for content and reasoning. A complete
response requires `isinstance(content, str) and content.strip()`, the exact live-model
identity, an allowed finish reason, and a valid response shape. Reasoning-only, missing,
null, whitespace, malformed, or truncated output is `excluded_retryable`, never `complete`.

### 3.4 Migration, not relabelling

**Do not edit or relabel `runs.jsonl`.** Append a separate deterministic migration index
mapping each legacy record to `legacy_run_id_v1`, its recoverable model-bound fingerprint,
and a disposition. Records missing runner/config/protocol identity are `legacy_unbound` —
retained for exploratory analysis, unable to satisfy v2 resume. Keep the 64 Qwen2.5 records
in a distinct legacy cohort so they can never skip Qwen3 work. Mark the 40 empty Qwen3
completes `invalid_empty_answer` and requeue them; the safest confirmatory policy requeues
all 67. Resume consults only exact v2 identities, and two rows sharing a v2 ID with
different preimages or result hashes are a **hard conflict**, not first-or-last-wins.

**Verdict: no-go for autonomous or confirmatory continuation** until all three seams exist.
Freeze the current ledger as legacy evidence; do not delete it.

---

## 4. Manifest executable resolution — hardened (rig `cb5a39e5`)

Reviewed 2026-08-21, PASS, no findings remaining. Worth recording because the closing move
is not obvious.

`D:\rig\lib\control.ps1` now applies a case-insensitive **`.exe` allowlist after every
resolution branch**, so PATH-resolved `.cmd`/`.bat` wrappers and explicit script leaves
cannot reach `Start-Process`; and it opens the resolved leaf as binary and requires **both**
the DOS `MZ` signature and `PE\0\0` at the file's `e_lfanew` offset, so a text file renamed
`.exe` is rejected.

**Why the allowlist is the closing move:** PowerShell classifies `.cmd` wrappers as
`CommandType Application`, so `Get-Command -CommandType Application` alone is not
sufficient.

Absolute paths are normalized with `GetFullPath` and are not prefixed by the unit cwd;
slash-relative paths are joined to the declared unit cwd before normalization, preserving
`..\python_embeded\python.exe`-style semantics. The executable string rejects `;`, `&`, `|`,
CR and LF. There is no `Invoke-Expression`, no command shell, and no string evaluation:
`Start-Process` receives `-FilePath` (a validated native exe), `-ArgumentList`, and
`-WorkingDirectory`.

---

## 5. Traps

1. **`supervisor-state.json` is a shutdown checkpoint, not live authority.** Two independent
   sessions were misled by it. On 2026-08-21 it read `manual-paused` / `driver_pid: null` /
   `release_verified: true` from 18:46:40-04:00 while the manual gate had been set
   **`paused=false`** by `cli` at 18:46:49-04:00. Verify the handoff with scheduled-task and
   process queries instead.
2. **Pause the driver before running `revoke-unit`.** Racing its state writes is a named
   hazard.
3. **Hand-running the driver is not a workaround for a disabled supervisor.** The driver
   pins 60,000 context against whatever the slot holds; if the slot has an 8B at 16,384,
   every request fails the context gate and **writes false reds into the ledger**. Loading
   the configured model is step 7 of the supervisor's startup ordering; it starts the driver
   at step 9.
4. **Watch the slot's actual contents.** Observed 2026-08-22: `:8888` held
   `Qwen3-8B-GGUF (q8_0)` at 37,888 ctx, not the configured `unsloth/Qwen3.8-27B-GGUF` at
   60,000.
5. **Cancel a zombie generation through the admin API, not a kill.** The server keeps
   generating for disconnected clients (one held the slot 79 minutes):
   `POST http://127.0.0.1:8888/api/inference/unload` with
   `{"model_path": "...", "force_cancel_active": true}` — `{}` alone is a 422. The
   supervisor also reaps these on release; prefer letting it.
6. **A transient Unsloth HTTP 500 on load is not automatically a loop.** Two intervening
   records were excluded and the next run recovered in 62.86 s. Check whether the latest
   record is `complete` before escalating.
7. **In the OGhidra checkout, `origin` is LLNL upstream and `fork` is the writable fork.**
   Pushing to `origin` there is wrong. Branches created in that repo often have no upstream
   configured.
8. **`C:\Users\...\Python313\python.exe -m pytest` cannot collect** — that interpreter has no
   `pytest` installed. Use the repository's own test environment. (Separately, the Anaconda
   `python` on PATH is 3.7 and silently breaks anything using the walrus operator.)
9. **Keep temp on `D:`.** `C:` was measured at under 1 GB free while `D:` had ~1.67 TB.
   Redirect `TEMP`/`TMP`/`TMPDIR` for any test run that writes scratch.

---

## 6. Backup-health projection (rig `a62bfdc1`) — one durable sentence

`Supervisor._backup_summary()` was surfacing a stale persisted `health: "failed"` from an
August 18 non-fatal extractor failure even though `backup_policy.enabled` is deliberately
`false` (Palworld is not installed). The fix reports policy `enabled` separately —
disabled yields `{"enabled": false, "health": "disabled"}` while still exposing the
persisted last-known world, commit, push, remote and LFS facts; enabled reports persisted
health unchanged, including `failed`; and the load-error fallback is policy-aware
(`disabled` vs `unknown`).

**The principle worth keeping: the override belongs in the telemetry projection only, never
in persisted state.** Side effect to expect: the dashboard labels every backup row
generically as `BACKUP` and will now display `DISABLED` for this retired policy.
