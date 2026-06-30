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

## Commands

```bash
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --save-state "D:\GotYaForce\dolphin\soon we fight mirror b.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids action-state-entry,action-helper-cluster,movement-helper-cluster,wakeup-invulnerability-init,secondary-wakeup-timer-init,wakeup-timer-countdown,timer-status-helper,death-swap-lead,clear-swap-controller-timer,player-team-lookup-band,team-get-player --max-hits 80 --timeout-ms 90000
```

## Implementation Gate

Do not implement lock-on, projectile spawn, melee contact, jump/fly velocity, death-to-next-borg, or CPU AI from guesses. The current browser mechanics remain candidate wiring until one action-specific trace captures the original DOL state transitions:

- Active borg base from `0x8005d4b0` or `0x80055c00`.
- Writes to `active_borg_base+0x544`, `+0x5e0`, `+0x6b4`, `+0x6b6`, `+0x6fe`, and `+0x720`.
- Target pointer writer.
- HP writer.
- Action helper/projectile pointer from `0x800660b8`.

## Next Trace

Use visible Dolphin or a verified gameplay save-state boot path, then run one short trace per action. Start with camera and one manual jump/shot:

```bash
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\dolphin\soon we fight mirror b.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --groups camera --max-hits 30 --timeout-ms 30000
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids action-state-entry,action-helper-cluster,movement-helper-cluster --max-hits 40 --timeout-ms 60000
```
