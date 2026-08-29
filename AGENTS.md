# AGENTS.md — GotYaForce port: operating runbook for agents

This machine runs an unattended LLM port pipeline. Three cooperating pieces:

- **rig supervisor** — Windows scheduled task `rig supervisor` (`D:\rig\supervisor\`).
  Owns the machine: starts/stops the driver, loads/unloads the model, enforces
  the manual gate, reaps zombie generations, writes `D:\rig\state\supervisor-state.json`.
- **port driver** — `src/port_wasm_units.py` in `D:\GotYaForce\research\tools\OGhidra`.
  Ports one unit per run (compile → LLM compile-fix loop → link → oracle → commit+push).
- **Unsloth serving slot** — `127.0.0.1:8888`, one model resident
  (`unsloth/Qwen3.8-27B-GGUF:UD-Q4_K_XL`). Admin API under `/api/inference/*`.

Goals, in order: (1) a playable, buildable version of the game; (2) steady
progress, no time wasted on dead ends; (3) git pushes flowing (no pushes = RCA);
(4) dead ends detected and killed fast.

---

## Stopping the port — THE ONE CORRECT WAY

**Never `Stop-Process` / `taskkill` the driver, the supervisor, or Unsloth.**
A raw kill orphans bash/emcc children (the Job Object in
`D:\rig\supervisor\driver.py` exists precisely because tree-kills miss
grandchildren), leaves the in-flight server generation running as a zombie
(one held the slot 79 minutes), and skips the stop checkpoint.
This was done once on 2026-08-20 and documented here so it is never repeated.

Correct stop — pause the manual gate:

```python
# write D:\rig\state\manual-gate.json
{"paused": true, "changed_at": "<iso8601 local>", "by": "widget",
 "note": "<why>"}
```

The supervisor then does everything: cooperative `stop_at_boundary`, a grace
period, then `kill_all()` via Job Object (clean tree kill), cancels the
abandoned generation, releases the model, checkpoints. Verified behaviour:
driver stopped and VRAM released within ~15 s of the gate flipping.

Verify stopped: `supervisor-state.json` shows `mode: manual-paused`,
`driver_pid: null`; total VRAM < ~3 GB.

Resume: write the same file with `"paused": false`. The supervisor reloads the
model and relaunches on its own; full recovery takes a few minutes (model load).

## Needing the GPU yourself (benchmarks, experiments)

Gate pause is NOT enough — a paused supervisor actively **unloads any model you
load** to enforce the pause (it tore down two benchmark loads this way).

1. Pause the gate (clean stop as above).
2. `Disable-ScheduledTask -TaskName "rig supervisor"; Stop-ScheduledTask -TaskName "rig supervisor"`
3. Do the work. **File a restore reminder immediately** — a disabled supervisor
   means the port is down until you undo this.
4. `Enable-ScheduledTask -TaskName "rig supervisor"; Start-ScheduledTask -TaskName "rig supervisor"`,
   then unpause the gate.

## Killing a dead-end unit

A unit grinding an unfixable contradiction is a design failure signal — kill it
and fix the design, but kill it properly:

1. Pause the gate; wait for `driver_pid: null`.
2. Settle it **through the journal** (design section 2.9 [V4-9] —
   settle-through-journal rule). **Hand-editing `wasm-units-state.json` is
   forbidden**: the 2026-08-20 migration wrote 15 verdicts straight into the
   state file with no journal event, and `events.jsonl` has disagreed with
   live state ever since. Any operation that settles, carries, or unsettles a
   verdict MUST go through a code path that emits the corresponding journal
   event. The sanctioned path (backs up the state file, edits, emits the
   journal checkpoint + `verdict_settled` event, saves atomically):

   ```
   cd research/tools/OGhidra
   .venv\Scripts\python.exe -m src.port_wasm_units settle-unit \
     --unit <name> --status structural_ineligible \
     --reason "<proof: file:line of the contradiction in the verbatim .c>"
   ```

   Only do this for provable contradictions — the status is permanent.
3. Unpause. The settle CLI takes the driver lock, so it refuses to run while
   a driver is alive (`WinError 5` races and lost updates are proven failure
   modes here).

## Zombie generation on the serving slot

The server keeps generating for disconnected clients. To cancel:

```
POST http://127.0.0.1:8888/api/inference/unload
  {"model_path": "unsloth/Qwen3.8-27B-GGUF", "force_cancel_active": true}
```

(`{}` alone is a 422 — `model_path` is required.) The supervisor also reaps
these automatically on release; prefer letting it.

---

## Git traps

- **OGhidra repo (`research/tools/OGhidra`): `origin` is LLNL upstream — never
  push to it.** The user's fork is remote `fork`; `main`'s upstream is
  `fork/main`, so bare `git push` is safe, `git push origin` is not.
- GotYaForce repo: product commits on `main`, machine journal on
  `port-progress` (worktree under `.tmp/port-progress-worktree`).
- **The driver publishes the sha it just committed on the CURRENT branch, with an
  explicit refspec `<sha>:refs/heads/port-staging` — fast-forward only.** It does
  not consult upstream config (a bare `git push` caused the gate-ledger bug, which
  is why the refspec is explicit). Two consequences, both proven by the 2026-08-23
  outage: moving `HEAD` off the lineage that `origin/port-staging` already points
  into makes every subsequent push non-fast-forward and **stops the port**; and a
  repair commit made on top of the wrong lineage can invalidate a promotion that
  was already pending. Before touching branches while the driver is alive, pause
  the gate — then check `git ls-remote origin refs/heads/port-staging` against your
  local lineage.
- No vendor branding / Co-Authored-By in commit messages. A guard test in
  OGhidra (`tests/test_port_wasm_units.py`) fails if it reappears.
- Verify pushes with `git ls-remote origin <branch>` — local tracking refs lie.

## Monitoring invariants (breach = RCA, not waiting)

- origin `port-staging` should receive a push whenever a unit goes green
  (owner-ordered interim, 2026-08-20: artifact pushes redirected off
  origin/main pending docs/git-topology-design.md in the OGhidra repo;
  local lineage and commits unchanged); >4 h with the driver `running`
  and no green → investigate the current unit for a dead end.
- `red_retryable` climbing across consecutive units → classify errors before
  assuming model quality; nearly all reds to date were infrastructure.
- Greens tiered `compile-only (UNVERIFIED)` are **not** progress toward a
  playable game by themselves — they need eventual oracle coverage.
- Dashboard: `http://127.0.0.1:7800/`. State: `D:\rig\state\supervisor-state.json`,
  unit state: `wasm-units-state.json`, events: `events.jsonl` (same dir).

## No ad-hoc orchestration scripts

Operate the machine through its documented controls directly -- the manual gate
file, the scheduled-task cmdlets, the sweep's own launch command, the admin API.
Do not write one-off orchestration scripts that chain these steps; they encode
stale assumptions, race the real controllers, and pile up. If a sequence is
needed repeatedly, it belongs in the rig or pipeline repo as reviewed, tested
code -- not in a scratchpad.

## Toolchain traps on this machine

- **PowerShell/bash heredocs corrupt backslashed paths** (`D:\rig` → `D:` + CR).
  Edit files by writing a Python script to a file and running it; verify bytes.
- Anaconda `python` on PATH is **3.7** (no walrus operator — it silently broke
  two tools). Use `D:\colibri\.venv-convert\Scripts\python.exe` (3.13) or
  `C:\Users\manny\AppData\Local\Programs\Python\Python313\python.exe`.
- `strings` does not exist (silently returns nothing); `grep -E` here lacks
  `\s`. Prefer Python for binary/regex scans.
- `CUSTOM_API_TIMEOUT` is schema-capped at 3600 (`src/config.py`,
  pydantic `le=3600`); values above crash the driver at startup.
- `.env` in OGhidra wins over process env (`load_dotenv(override=True)`).
