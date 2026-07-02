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
- Fresh visible-Dolphin attempt on 2026-07-02 from `dolphin/right before hit.sav`
  wrote `user-data/dolphin-trace/traces/x-special/gdb-trace-2026-07-02T19-28-49-065Z.json`
  (ignored raw trace). It captured 80 `pad-read` and 80
  `game-pad-normalization-cluster` hits, decoded `padButtons: {"none": 80}`, and
  captured zero action-state/audio hits. Result: the attempted keyboard `C`/GC-X input
  did not reach the sampled PAD frames before the short trace filled; it is not X proof.
- Corrected GDB-injection input proof on 2026-07-02:
  - `scripts/dolphin-gdb-trace.mjs` now supports `--inject-pad-buttons`,
    `--inject-pad-frames`, and `--inject-pad-port`.
  - Injection happens at `0x8010d4d0`, after `PADRead` returns and before
    `zz_010d450_` copies/clamps the `PADStatus[4]` buffer into normalized globals.
    The injector also clears `PADStatus.err` to zero; preserving Dolphin's `err=-3`
    made the game-side normalizer ignore the synthetic button.
  - `pad-normalization-complete` at `0x8010d86c` captures `DAT_803c727c` after the
    normalizer writes current/previous/pressed/released slot records.
  - These traces are explicitly `gdb-pad-injection`, not physical keyboard/controller
    captures. They prove the downstream normalizer path for injected PADStatus bits,
    not full player action semantics.
- Corrected normalized-input captures from `2v2 gred cotrolled players no cpu.sav`:
  - B: raw write `020000000000000000000000`; normalized slot-0 current
    `0x00000200`, pressed `0x00000200`.
  - X: raw write `040000000000000000000000`; normalized slot-0 current
    `0x00000400`, pressed `0x00000400`.
  - Z: raw write `001000000000000000000000`; normalized slot-0 current
    `0x00000010`, pressed `0x00000010`.
  - The same corrected runs still captured zero `player-input-bridge`,
    `action-handler-table`, `borg-state-dispatch`, `state-transition-primitive`,
    param-tier, or audio hits. Therefore B/X action mapping, Z ally-lock/charge or
    power-up side effects, and cue IDs remain unproven.

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
- `user-data/dolphin-trace/traces/x-special/gdb-trace-2026-07-02T19-28-49-065Z.json`
  - Visible Dolphin pass from local save `dolphin/right before hit.sav`.
  - 160 hits, no errors.
  - `scripts/summarize-dolphin-gdb-trace.mjs` reports `padButtons: {"none": 80}`,
    `firstNonNeutralPad: null`, and zero action/audio proof IDs.
  - Result: proves the new proof summarizer can reject a mislabeled/too-short X run;
    does not prove B/X mapping, Z behavior, or cue IDs.
- `user-data/dolphin-trace/traces/b-normalization-complete/gdb-trace-2026-07-02T20-35-11-537Z.json`
  - Corrected post-PADRead GDB injection from `2v2 gred cotrolled players no cpu.sav`.
  - 100 hits, no errors. B is observed at PADRead and normalized slot 0 as
    `current=0x00000200`, `pressed=0x00000200`.
  - Result: proves injected GC-B survives through `zz_010d450_` normalization; no
    actor/action/param/audio consumer fired.
- `user-data/dolphin-trace/traces/x-normalization-complete/gdb-trace-2026-07-02T20-35-42-336Z.json`
  - Corrected post-PADRead GDB injection from the same save.
  - 100 hits, no errors. X is observed at PADRead and normalized slot 0 as
    `current=0x00000400`, `pressed=0x00000400`.
  - Result: proves injected GC-X survives through `zz_010d450_` normalization; no
    actor/action/audio consumer fired.
- `user-data/dolphin-trace/traces/z-normalization-paramtier/gdb-trace-2026-07-02T20-36-13-645Z.json`
  - Corrected post-PADRead GDB injection from the same save.
  - 150 hits, no errors. Z is observed at PADRead and normalized slot 0 as
    `current=0x00000010`, `pressed=0x00000010`.
  - Result: proves injected GC-Z survives through `zz_010d450_` normalization; zero
    param-tier/action/audio hits, so no ally-lock charge or power-up behavior is proven.

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
- Player input bridge from `0x80056900` (`FUN_80056900`) copying normalized
  `DAT_803c727c` into actor `+0x5b4` current command and `+0x5bc` pressed edge.
- Writes to `active_borg_base+0x544`, `+0x5e0`, `+0x6b4`, `+0x6b6`, `+0x6fe`, and `+0x720`.
- Target pointer writer.
- HP writer.
- Action helper/projectile pointer from `0x800660b8`.
- Gameplay camera follow formula. The latest camera trace proves callsites and static vectors, but not target-relative distance/height/lag.

## Next Trace

Use visible Dolphin or a verified gameplay save-state boot path, then run one trace per
action. For physical controller proof, do not use `--inject-pad-buttons`; for deterministic
downstream PADStatus proof, use the post-PADRead injector below. Summarize the ignored raw JSON
before promoting any rule:

```bash
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\dolphin\right before hit.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids=pad-read,pad-post-read-normalization,pad-normalization-complete,game-pad-normalization-cluster,player-input-bridge,active-borg-command-current,active-borg-command-pressed,state-transition-primitive,borg-state-dispatch,active-action-handler-invuln,action-handler-table,action-helper-cluster,battle-frame-target-action-dispatch,audio-sfx-playing,audio-object-callback,audio-seq-continue,audio-sfx-init,audio-sfx-update --inject-pad-buttons=B --inject-pad-frames=90 --max-hits=1200 --timeout-ms=60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\bx-close-b"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids=pad-read,pad-post-read-normalization,pad-normalization-complete,game-pad-normalization-cluster,player-input-bridge,active-borg-command-current,active-borg-command-pressed,state-transition-primitive,borg-state-dispatch,active-action-handler-invuln,action-handler-table,action-helper-cluster,battle-frame-target-action-dispatch,audio-sfx-playing,audio-object-callback,audio-seq-continue,audio-sfx-init,audio-sfx-update --inject-pad-buttons=X --inject-pad-frames=90 --max-hits=1200 --timeout-ms=60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\x-special"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids=pad-read,pad-post-read-normalization,pad-normalization-complete,game-pad-normalization-cluster,player-input-bridge,active-borg-command-current,active-borg-command-pressed,state-transition-primitive,borg-state-dispatch,active-action-handler-invuln,action-handler-table,action-helper-cluster,battle-frame-target-action-dispatch,param-tier-reset,param-tier-delta-127,param-tier-delta-63,param-tier-refresh,audio-sfx-playing,audio-object-callback,audio-seq-continue,audio-sfx-init,audio-sfx-update --inject-pad-buttons=Z --inject-pad-frames=90 --max-hits=1200 --timeout-ms=60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\z-ally-lock"
rtk .\tools\node\node.exe scripts\summarize-dolphin-gdb-trace.mjs user-data\dolphin-trace\traces\bx-close-b user-data\dolphin-trace\traces\x-special user-data\dolphin-trace\traces\z-ally-lock
```

Proof gate: a B/X mapping needs PAD bytes and either `state-transition-primitive` or
`borg-state-dispatch`/`active-action-handler-invuln` in the same labeled capture. Z
charge/power-up needs a Z-labeled PAD sample and a `param-tier-*` hit. Audio cue IDs need
an action-labeled trace with audio hits plus argument/handle inspection; counts alone do not
identify a cue.
