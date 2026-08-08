# Design: Port Supervisor Fix (post-mortem + rebuild) — 2026-08-08

Status: **awaiting owner sign-off; no supervisor code written yet.** A stopgap
`finish-port --drive --until-blocked` driver is running loose (see §7).

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

## 7. Current stopgap (in effect now)

`finish-port --drive --until-blocked` launched directly, logging to
`monitor\oghidra-manual-drive.out.log`; porting `challenge_menu_objects` on 35B UD-Q4_K_XL.
**It bypasses palworld gameplay protection** — safe only while the server is empty (it is;
0 players). Retire it as soon as a fixed supervisor is installed.

Model state settled 2026-08-07: 35B **UD-Q4_K_XL @ 131 072** loaded via
`POST /api/inference/load`; 27B UD-Q4_K_XL downloaded to
`D:\models\unsloth\Qwen3.6-27B-MTP-GGUF` as the escalation model.

---

## 8. Open questions for the owner

1. Implement A+B+C in the existing PS monitor now (fastest return to protected operation), or
   go straight to §6 option 1+3 (driver self-supervises + small Python watchdog)?
2. Split the `run-state.json` writers (§2.4) as part of this, or track separately?
3. Restore `omr-sweep` to GPU priority 1 when the port pipeline is stable (it is temporarily
   at 3; oghidra temporarily at 1).
