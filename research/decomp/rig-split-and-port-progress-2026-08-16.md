# Machine supervision moves to the rig; the port workflow gets a remote journal

**2026-08-16.** Two defects, one change.

## Defect 1: split-brain ownership of the single serving slot

`research/tools/OGhidra/src/palworld_watchdog.py` was RustyOGhidra's machine
supervisor. It carried a hard-coded `unsloth/Qwen3.6-35B-A3B-MTP-GGUF`, a
`"Qwen3.6-35B-A3B" in candidate` recognition check, `max_seq_length = 262144`
and a `min_context = 80000` floor — all of which had been correct on 2026-08-08
and none of which was correct after the pipeline moved to the configured 27B at
32,768 context (`CUSTOM_API_MODEL` / `CUSTOM_API_GGUF_VARIANT` /
`CUSTOM_API_MAX_SEQ_LEN` in the OGhidra `.env`).

There is exactly one Unsloth serving slot. Two components believed they owned
it:

* the watchdog would judge a **correct** resident 27B "not loaded" (wrong family
  string, and 32,768 < its 80,000 floor) and load its 35B over it — the
  `35B load → evict → 27B load` churn;
* its unload path posted `model_path = <its configured 35B>` rather than the
  model actually resident, so a cleanup could no-op while a model stayed in
  VRAM;
* meanwhile `CustomAPIClient._preflight_serving_context` /
  `_cancel_abandoned_generation` legitimately manage the slot **for the request
  in flight**.

Patching the literal would have left two literals. The fix is structural.

### One authoritative configuration

`src/port_model_config.py` resolves it, from the same file with the same
precedence `src/config.py` uses — `load_dotenv(<oghidra root>/.env,
override=True)`, so **the .env wins over the process environment**. There is no
model literal in the resolver, and `tests/test_port_model_config.py` fails if one
appears in its executable code.

`src/.env` (a dead LM Studio-era copy that `config.py` never loads, and which
still named the 35B) is now a comment-only tombstone pointing at the real file.

### One serving-slot lifecycle API

`D:\rig\supervisor\unsloth.py` — `status`, `active_model`,
`active_context_length`, `slot_empty`, `configured_model_loaded`,
`ensure_configured_model_loaded`, `cancel_active_generation`,
`unload_active_model`, `cancel_and_unload_active`, `wait_until_unloaded`.

Three rules it encodes:

1. **Cleanup never assumes the configured model is resident.** `status()` is the
   authority; the unload targets `active_model()`.
2. **`slot_empty()` is tri-state.** `None` means *unknowable* (the host is not
   answering). Nothing may treat `None` as empty — reporting a released model
   that is still resident is exactly the failure this prevents.
3. **Identity is exact, never a substring.** A family-prefix substring test is
   what made a correct model look wrong.

### The split

The rig owns the machine; RustyOGhidra owns port execution. The seam is
`python main.py port-contract {config,status,stop,run,checkpoint,progress-flush}`
(`src/port_contract.py`). `src/palworld_watchdog.py` and its tests are deleted;
the one assertion in that test file that was really about the *port* pause rule
moved to `tests/test_transient_markers.py`. The rest of the behaviour, and its
hard-won traps, moved to `D:\rig\supervisor\` with `D:\rig\tests\`.

See `D:\rig\SUPERVISOR.md` for the ownership table, the startup ordering and the
teardown ordering.

## Defect 2: GitHub could not tell a working night from a dead one

The wasm workflow commits only *green* units to the product repo. A night that
attempted forty units and went red forty times produced zero commits — remotely
indistinguishable from a night where nothing ran. The owner cannot remote into
the machine to tell the difference.

### The `port-progress` branch

A dedicated branch on `abhidya/GotYaForce` carrying a compact generated tree:

```
workflow-progress/
  current.json          state, current/previous unit, stage, attempt, model, context,
                        driver status, last transition, last green, last product commit,
                        block reason, manual pause, queue counters
  summary.json          per-class counts, attempts, last-hour transitions/greens,
                        last green, last product commit, repeated failure classes, health
  events.jsonl          bounded rolling journal (last 2000 transitions)
  units/<unit-id>.json  per-unit record + attempt history + driver record
  README.md             RUNNING/PAUSED/BLOCKED/COMPLETE banner + last 50 transitions
```

Written through a **separate git worktree** (`.tmp/port-progress-worktree`,
gitignored), so the product worktree's index and HEAD are never touched and a
progress commit can never race a product commit. Product history stays clean: no
failed candidate source ever lands in the product tree for observability.

### The unit-transition invariant

Before the workflow starts unit B after leaving unit A, a durable record for A
exists. Emitted for `green`, `staged` (compile-only), `retryable`,
`gate_failed`, `deferred`, `structural_ineligible`, and cooperative stops. No
hourly batch, no ten-unit batch. Every commit subject names the unit:

```
progress: auto-c0000-001 retryable at compile-fix
progress: collision-core gate_failed at wasm-link
progress: damage-core green 3/1520
```

A killed run leaves its unit in `porting`; the next run reconciles it to
`deferred`, emits the checkpoint the killed run owed, and returns the unit to the
pool.

### Failure policy

Local durability first, then the snapshot, then the commit, then the push. A
failed push is recorded pending in `<run_root>/progress/pending-push.json` and
retried at the next transition and at every run start. A GitHub outage cannot
fail a unit, and never reverts product work. A journal that raises is swallowed
by the driver — telemetry never costs a unit.

### Correctness gates unchanged

Oracle-green units still commit to `research/decomp/port-units/<unit>/`;
compile-only units still commit to `research/decomp/port-units-staging/<unit>/`
with `verified: false` provenance and are still never wired into the app. The
progress record carries `product_commit` and an explicit `product_effect`
(`durable product commit` / `no product-tree change by design`).

### One correctness fix that came out of this

`structural_ineligible` (an extraction range that does not describe extractable
code) is now a settled status. Previously any non-green status counted as "work
remains", so a permanently impossible unit would have kept the driver reporting
`EXIT_PROGRESSED` forever and the supervisor relaunching it every cycle.
`SETTLED_STATUSES = {green, structural_ineligible}` closes that.
