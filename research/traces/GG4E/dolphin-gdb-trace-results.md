# Dolphin GDB Trace Results

Generated: 2026-06-30

## What Is Confirmed

- Dolphin's built-in GDB stub works with the local build when launched through `scripts/launch-dolphin-gdb.mjs`.
- `scripts/dolphin-gdb-trace.mjs` can connect to `127.0.0.1:5555`, install `Z0` execute breakpoints from `research/traces/GG4E/breakpoints-watchpoints.json`, continue the emulated CPU, and capture PC/LR/registers/MEM1 pointer snapshots.
- The first broad trace captured live hits from original DOL code:
  - `camera-lookat-final` at `0x8020b61c` (`gnt4-C_MTXLookAt-bl`): 65 hits.
  - `game-pad-normalization-cluster` at `0x8010d450`: 18 hits.
  - `pad-read` at `0x8021379c`: 18 hits.
  - `pad-clamp-circle` at `0x80212a14`: 18 hits.
- No saved trace currently captures `action-state-entry`, `action-handler-table`, or
  `action-helper-cluster`, so the local trace set does not prove B/X action mapping, Z
  ally-charge/power-up behavior, or per-action audio cue IDs.
- Fresh local parse on 2026-07-02 checked every JSON under
  `user-data/dolphin-trace/traces/` (including `camera-next/`, `damage-next/`, and
  `summary.json`): all returned zero hits for those three action IDs.

## Trace Files

- `user-data/dolphin-trace/traces/gdb-trace-2026-06-30T08-10-54-261Z.json`
  - Broad proof trace.
  - 120 hits, no errors.
  - Useful for proving GDB capture path and camera/PAD anchors.
- `user-data/dolphin-trace/traces/gdb-trace-2026-06-30T08-12-04-959Z.json`
  - Save-state pass with lock-on/input groups still enabled.
  - 200 hits, no errors.
  - Dominated by PAD breakpoints, so it does not prove mechanics.
- `user-data/dolphin-trace/traces/gdb-trace-2026-06-30T08-19-13-228Z.json`
  - Narrow action/death/AI pass from `dolphin/soon we fight mirror b.sav`.
  - Only one unmapped boot/core hit, then timeout.
  - Evidence says this save-state launch did not enter the active gameplay/action path under the current headless batch launch.
- `user-data/dolphin-trace/traces/damage-next/gdb-trace-2026-06-30T21-25-14-937Z.json`
  - First pass after `scripts/dolphin-gdb-trace.mjs` gained derived active-borg watchpoints.
  - Damage breakpoints installed and six runtime watchpoint templates parsed, but no wake/damage breakpoint fired.
  - Result: no `active_borg_base` was derived and no mechanics field writes were captured.
- `user-data/dolphin-trace/traces/camera-next/gdb-trace-2026-06-30T21-28-19-435Z.json`
  - Focused camera pass from `dolphin/soon we fight mirror b.sav`.
  - 120 hits, no errors.
  - Caller distribution: startup/control `0x80005424` x1, `0x80005a44` x1, early camera `0x8000bd08` x13, later camera callers `0x8008c93c` x35 and `0x8008ca90` x70.
  - Decoded `C_MTXLookAt` vectors were stable setup values in this capture:
    - `0x8008c93c`: eye `[0, 0, 100]`, up `[0, 1, 0]`, interest `[0, 0, -100]`.
    - `0x8008ca90`: eye `[0, 0, 0]`, up `[0, 1, 0]`, interest `[0, 0, -10]`.
  - Result: proves camera callsite/capture path, but not enough to replace the browser gameplay follow camera formula yet.

## Commands

```bash
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --save-state "D:\GotYaForce\dolphin\soon we fight mirror b.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids action-state-entry,action-helper-cluster,movement-helper-cluster,wakeup-invulnerability-init,secondary-wakeup-timer-init,wakeup-timer-countdown,timer-status-helper,death-swap-lead,clear-swap-controller-timer,player-team-lookup-band,team-get-player --max-hits 80 --timeout-ms 90000

rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\dolphin\soon we fight mirror b.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups damage --max-hits 60 --timeout-ms 90000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\damage-next"

rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\dolphin\soon we fight mirror b.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups camera --max-hits 120 --timeout-ms 60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\camera-next"
```

Note: do not probe `127.0.0.1:5555` with `Test-NetConnection` before tracing; Dolphin's GDB stub behaves as a single-client endpoint and the probe can consume the connection.

## Implementation Gate

Do not implement lock-on, projectile spawn, melee contact, jump/fly velocity, death-to-next-borg, B/X action mapping, Z ally-charge/power-up behavior, per-action audio cue IDs, or CPU AI from guesses. The current browser mechanics remain candidate wiring until one action-specific trace captures the original DOL state transitions:

- Active borg base from `0x8005d4b0` or `0x80055c00`.
- Writes to `active_borg_base+0x544`, `+0x5e0`, `+0x6b4`, `+0x6b6`, `+0x6fe`, and `+0x720`.
- Target pointer writer.
- HP writer.
- Action helper/projectile pointer from `0x800660b8`.
- Gameplay camera follow formula. The latest camera trace proves callsites and static vectors, but not target-relative distance/height/lag.

## Next Trace

Use visible Dolphin or a verified gameplay save-state boot path, then run one short trace per action. For B/X/Z/audio proof, use the expanded proof groups and summarize the ignored raw JSON before promoting any rule:

```bash
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\dolphin\soon we fight mirror b.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups action-proof,audio-proof --max-hits 80 --timeout-ms 45000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\bx-close-b"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups action-proof,audio-proof --max-hits 80 --timeout-ms 45000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\bx-ranged-b"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups action-proof,audio-proof --max-hits 80 --timeout-ms 45000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\x-special"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups action-proof,power-up/param-tier,audio-proof --max-hits 80 --timeout-ms 45000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\z-ally-lock"
rtk .\tools\node\node.exe scripts\summarize-dolphin-gdb-trace.mjs user-data\dolphin-trace\traces\bx-close-b user-data\dolphin-trace\traces\bx-ranged-b user-data\dolphin-trace\traces\x-special user-data\dolphin-trace\traces\z-ally-lock
```

Proof gate: a B/X mapping needs PAD bytes and either `state-transition-primitive` or
`borg-state-dispatch`/`active-action-handler-invuln` in the same labeled capture. Z
charge/power-up needs a Z-labeled PAD sample and a `param-tier-*` hit. Audio cue IDs need
an action-labeled trace with audio hits plus argument/handle inspection; counts alone do not
identify a cue.
