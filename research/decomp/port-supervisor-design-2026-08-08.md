# Design: Port Supervisor Fix (post-mortem + rebuild) — 2026-08-08

Status: **IMPLEMENTED + DEPLOYED 2026-08-08 ~17:13 ET** — Fixes A/B/C plus the
§4b adversarial additions are live in `palworld-oghidra-monitor.ps1`; the
scheduled task is running and has adopted the stopgap driver (§7 note). A
versioned snapshot of the fixed script lives beside this doc
(`port-supervisor/palworld-oghidra-monitor.ps1`); the live copy at
`D:\Palworld_Server_Setup\monitor\` is not under git.

Incident: **~23 h of zero progress, 2026-08-07T18:03 → 2026-08-08T16:43.** No units
integrated, no commits. The port pipeline was healthy the whole time; nothing launched it.

---

## 1. Root cause — three independent defects in `palworld-oghidra-monitor.ps1`

The launcher is `D:\Palworld_Server_Setup\monitor\palworld-oghidra-monitor.ps1` (535 lines).
The rig does **not** launch OGhidra — `rig.psd1` has it as `mode = observe`.

**A. A telemetry write can kill the whole monitor. (the actual killer)**
`Write-JsonAtomic` (:71-81) ends with `Move-Item -Destination $Path -Force`. On PS 5.1
(.NET Framework) that is *not* atomic replace: with the destination present and a reader
(rig collector / dashboard, 3 s poll) holding it, `FileInfo.MoveTo` throws
`IOException: Cannot create a file when that file already exists`. It is called from
`Write-MonitorState` — pure telemetry — but `$ErrorActionPreference='Stop'` (:19) plus the
loop's outer `catch { ...; throw }` (:527-531) makes *any* exception fatal. Observed
verbatim in the log at 18:03:25, after which the process never logged again.

**B. Crash-loop guard misfires on by-design short steps.**
The monitor launches `finish-port --drive` (:402) = **one durable step per invocation**,
then the process exits. The guard (:380-398) counts any run < `MinHealthyRuntimeSeconds`
(120) as a failed start and blocks after 3. It never reads the driver's exit code.
Legitimate fast steps (exit 0 no-work, exit 5 lock-held, a quick analyze reuse) therefore
look like a crash loop. The log shows repeated
`BLOCKED: OGhidra exited in under 120s on 3 consecutive attempts` with a *stderr tail that
is only a benign pydantic UserWarning* — i.e. blocked on healthy runs.

**C. Force-kill orphans the liveness flag.**
`Protect-Gameplay → Stop-OGhidraTrees` (:186-205) SIGKILLs the driver mid-request. The
client cannot clear its own telemetry on SIGKILL, so `llm-liveness.json` keeps
`active: true` forever. That trips the rig health assertion
(`active == true implies updated_at fresher than 20m`, rig.psd1 :225) and makes a dead
driver look alive — observed at 1386 min stale. The *killer* must do the cleanup.

---

## 2. Verified against source (corrections to the first draft of this design)

Claims re-checked in code rather than assumed. Three came back different:

1. **VERIFIED — exit-0 writes a durable `completed`.** `port_driver.py:588-592`: no-work
   emits `_write_progress(ledger, "completed")` with `run_mode: "driver"` (:547) *before*
   returning `EXIT_NO_WORK`. The monitor's don't-respin guard (:371) is therefore sound.
   This was the load-bearing unverified assumption of the first draft; it holds.
2. **CORRECTED — `--until-blocked` honors control.json between steps.** `port_driver.py:581-586`
   re-reads `control.json` at the **top of every loop iteration**, not once per process. So a
   long-lived driver still stops cooperatively on `stop_after_stage` at each step boundary.
   The first draft understated this; it makes `--until-blocked` *safer* than assumed.
   (Within a single 10-20 min generation it still cannot yield — force-kill remains required
   for instant protection.)
3. **CORRECTED — liveness writes are already atomic.** `custom_api_client.py:195-202` uses a
   uuid temp + `os.replace`. Defect C is *only* the stale `active:true` flag, not corruption.
   Note the asymmetry: the **Python side already does atomic writes correctly; the PowerShell
   side does not** — evidence for §6.
4. **NEW DEFECT FOUND — `run-state.json` has two racing writers.**
   `port_driver._write_progress` writes `run_mode: "driver"` (:547) and
   `port_chunk_workflow._write_state` writes `run_mode: "chunk_unit"` (:612) to the *same*
   file. Mid-port the workflow clobbers the driver's view. At rest the driver writes last, so
   the `completed` guard survives — but **`run-state.json` is not a trustworthy supervisor
   signal while a step is in flight.** Any design keying relaunch off it must read only at
   rest, or the two writers must be separated (recommended: workflow writes
   `unit-state.json`, driver keeps `run-state.json`).

---

## 3. Fix

**A — telemetry may never kill protection.**
- `Write-JsonAtomic`: `[IO.File]::Replace($tmp, $Path, $null)` when the destination exists
  (true Win32 atomic replace; same-volume, satisfied), `[IO.File]::Move` when it does not;
  GUID temp name; 3 × 50 ms retry for transient AV/reader locks.
- `Write-MonitorState` swallows its own exceptions.
- Outer `catch` becomes a consecutive-failure counter: log + continue; exit fatally only
  after N consecutive iteration failures, preserving the scheduled task as the backstop.

**B — long-lived driver; stop using duration as a health signal.**
- Launch `finish-port --drive --until-blocked` (loops internally, exits on
  no-work / stopped / provider-paused / crash).
- Keep the `< 120 s` guard *only* as a genuine crash detector — for an `--until-blocked`
  process, dying in seconds really is a crash.
- Read `run-state.json` **only when no driver is running** (§2.4 race).

**C — reset liveness on kill.**
- `Reset-OGhidraLiveness`: atomic `active:false`, called at the end of `Stop-OGhidraTrees`
  and when the monitor observes the driver gone outside protected mode. Guarded on
  `Get-OGhidraRoots` being empty so it can never clobber a live driver.

---

## 4. Adversarial review

- `[IO.File]::Replace` needs same volume — satisfied (same directory). Exclusive lock still
  possible → retry, then swallow (dropping one telemetry sample is the intended outcome).
- Narrowed catch could spin on an unrecoverable error → consecutive-failure counter still
  exits fatally after N.
- Does `--until-blocked` holding the single decode slot cause the `Confirm-ChatContract`
  preflight to queue and false-BLOCK (the 2026-08-06 bug, :430)? **No** — :434-440 returns
  early when a driver is already running, before any preflight. Fewer preflight windows.
- `--until-blocked` vs the per-invocation isolation the driver was designed around: force-kill
  on player-join still works, but discards more in-flight work. Players-first makes that
  acceptable; Fix C cleans the resulting stale liveness.
- Fix C race (monitor resets `active:false` as a new driver sets `true`) → only reset when no
  driver is alive, sequenced before relaunch; client overwrites on its next request. Benign.
- **Residual risk:** none of this addresses §2.4. If a future change keys supervision off
  `run-state.json` mid-flight it will misread. Fix the two-writer split separately.

### 4b. Second adversarial pass (pre-implementation) — four gaps found, all fixed

1. **The `completed` guard latched forever.** Nothing cleared it when new work arrived
   (ledger reset/extension), so the next quiet outage was built in. Fixed: relaunch once
   when `port-ledger.json`'s mtime is newer than `run-state.json`'s (driver writes ledger
   first, state last, so at rest ledger ≤ state; file mtimes avoid timezone parsing).
   Worst case is one harmless exit-0 probe.
2. **"Dying in seconds really is a crash" was false.** Exits 0/2/3/4/5 are all healthy
   fast exits even under `--until-blocked` — and exit 5 (lock held) would have fired the
   day the fixed monitor was installed next to the stopgap. Fixed: the monitor now keeps
   the `-PassThru` handle (`$null = $process.Handle` to cache it), reads `.ExitCode`, and
   only counts short runs with unknown/unexpected codes toward the crash block. Exit 5
   with no visible driver gets its own counter → block → recheck cadence.
3. **The telemetry swallow was in the wrong layer.** `Write-JsonAtomic` also writes
   `control.json` (protection-adjacent), so it retries then *throws*; only
   `Write-MonitorState` swallows. `Protect-Gameplay` wraps its control write and Unsloth
   unload in try/catch so nothing can abort the force-kill.
4. **NEW DEFECT D — the stopgap driver was invisible to protection.** `Get-OGhidraProcesses`
   required the absolute `main.py` path in the command line; the stopgap was launched with
   a relative `main.py`, so `Get-OGhidraRoots` returned nothing — player-join protection
   could not have killed it. §7's "bypasses protection" was more literal than this doc
   knew. Fixed: match `python.exe` + `main.py` + `finish-port` regardless of path form.

Implementation traps hit and verified by test (not assumption):
- `[IO.File]::Replace($tmp,$dst,$null)` fails on PS 5.1 — PowerShell binds `$null` to `""`
  for string parameters and Replace rejects an empty backup path ("path is not of a legal
  form"). Must pass `[NullString]::Value`. Caught by an 800-write stress test against a
  concurrent reader loop (800/800 succeeded after the fix, 0/800 before it).
- `$process.ExitCode` after `-PassThru` was verified readable post-exit on this host;
  handle caching kept anyway as belt-and-braces.
- Driver stdout/err logs rotate at 5 MB before each launch (a long-lived
  `--until-blocked` run can grow them; rotation preserves the crash-tail evidence the
  block message reports).
- Iteration failures in the main loop log + count and only kill the monitor after 10
  consecutive failures (scheduled task remains the restart backstop).

---

## 5. Alternatives considered

1. **Fix A only.** Restores the status quo ante. Smallest blast radius; leaves false-BLOCK
   churn and stale liveness. *Rejected — less dead, not reliable.*
2. **Keep single-step `--drive`, gate on exit codes.** Preserves per-step isolation (bounded
   blast radius, no memory growth). Fiddlier async exit-code capture. Viable purist variant.
3. **Rig `mode: manage`.** One control plane (priority/gates/health exist). *Con:* rig is also
   PS 5.1 (same footguns) and its 3 s poll is slower than this monitor's sub-second kill on
   player-join — a few seconds of VRAM contention / frame hitch. Right strategic direction,
   separate piece of work.
4. **Split launcher from protector** (keep-alive service + palworld watchdog). Cleanest
   separation; most new surface.

---

## 6. Is PowerShell the wrong medium?

**The medium did not cause the outage — the design did.** All three defects are ordinary
supervisor mistakes that fail identically in any language written the same way. What PS 5.1
changed is how *easy* they were to write:

- `File.Move(src, dst, overwrite)` does not exist on .NET Framework (arrived in .NET Core 3),
  so the clean primitive was unavailable and the racy delete-then-move was the path of least
  resistance. `os.replace` / PS7 `File.Move(...,$true)` cannot throw this — and note the
  Python half of this same system already gets it right (§2.3).
- `$ErrorActionPreference='Stop'` + terminating-error semantics make "one cmdlet throw kills
  the loop" the *default*; per-iteration isolation must be added deliberately.
- `Get-CimInstance Win32_Process` for process discovery is slow, racy, and returns null
  `CommandLine` for elevated processes (already documented in HANDOFF.md).

**Ranked options:** (1) **shrink the supervisor until the medium stops mattering** — push
supervision into the driver (`--until-blocked` + gate file), leaving a watchdog that only
(a) keeps one process alive and (b) flips a gate file on player-join; (2) **PS 7** — near
source-compatible, gets atomic move and sane errors, but two PS versions in one rig;
(3) **Python colocated with the driver** — `os.replace`, `psutil`, `httpx`, testable, one
language owns the port stack; needs a thin Windows keep-alive wrapper; (4) **WinSW/NSSM +
policy sidecar** — battle-tested restart/backoff/log-rotation instead of hand-rolled guards
and mutexes (exactly where the bugs were), but supervises one process so a small policy
component remains; (5) **Go/Rust static binary** — over-engineered for a 3 s poll loop.

**Recommendation: (1) + (3).** The architectural win is making the driver self-supervise so
the fragile supervisor mostly disappears; do the thin remainder in Python beside the driver.
Not "rewrite the same 535-line design in a nicer language."

---

## 7. Current stopgap (RESOLVED 2026-08-08 17:14 ET)

`finish-port --drive --until-blocked` launched directly, logging to
`monitor\oghidra-manual-drive.out.log`; porting `challenge_menu_objects` on 35B UD-Q4_K_XL.
~~It bypasses palworld gameplay protection~~ **The fixed monitor now sees it** (defect D
fix, §4b.4) and has adopted it: state.json shows `mode: running, oghidra_pids: [4608]`.
Player-join now cooperatively signals, force-kills, and liveness-resets it like any
monitor-launched driver. No manual retirement needed — when it exits, the monitor
relaunches its own `--until-blocked` driver with exit-code-aware supervision.

Model state settled 2026-08-07: 35B **UD-Q4_K_XL @ 131 072** loaded via
`POST /api/inference/load`; 27B UD-Q4_K_XL downloaded to
`D:\models\unsloth\Qwen3.6-27B-MTP-GGUF` as the escalation model.

---

## 8. Open questions for the owner

1. ~~PS monitor now vs §6 option 1+3?~~ **Both, sequentially — ALL IMPLEMENTED 2026-08-08.**
   The patched PS monitor restored protection at 17:13; the §6 option 1+3 Python watchdog
   (`src/palworld_watchdog.py` on the OGhidra checkout, commit f9fa8c2, 9 unit tests)
   replaced it the same evening: scheduled task "Palworld - Python watchdog (port
   supervisor)" is live, the PS task is disabled (kept as rollback). The watchdog owns
   force-kill + forced VRAM unload, Unsloth bring-up with the settled UD-Q4_K_XL @ 131072
   config (the PS helper still encoded stale ud-iq3_s @ 262144 — config drift the rewrite
   caught), the tool_choice-object preflight, and embeddings sync.
2. ~~Split the `run-state.json` writers (§2.4)~~ — **DONE 2026-08-08** (OGhidra commit
   b27d6d5): the unit workflow writes `unit-state.json`; the driver is the sole
   `run-state.json` writer and now includes chunk/unit on analyzing/porting writes, so
   the rig dashboard keeps its detail with no collector change.
3. Restore `omr-sweep` to GPU priority 1 when the port pipeline is stable (it is temporarily
   at 3; oghidra temporarily at 1). — still open.

Also closed 2026-08-08: reachability gate hardened (block-comment mentions no longer
count as use sites; regression tests for the multiline-import false positive) — OGhidra
commit cb25ab4. Combat-family priority chunks moved into driver code with startup ledger
reconcile — commit 2b1b459.
