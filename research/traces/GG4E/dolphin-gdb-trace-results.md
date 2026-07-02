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
- Static decomp pass on 2026-07-02 proves the next input bridge step after
  normalization:
  - `FUN_80056900` at `0x80056900` copies the previous actor command
    `actor+0x5b4` to `actor+0x5b8`, calls `zz_008bbc0_` with
    `DAT_803c727c[port]`, stores the result in `actor+0x5b4`, derives pressed edge
    `actor+0x5bc = current & ~previous`, and derives release edge
    `actor+0x5c0 = previous & ~current`
    (`research/decomp/ghidra-export/chunk_0007.c:228-270`).
  - `zz_008bbc0_` at `0x8008bbc0` returns `param_2 & 0x00ff1f7f`; this mask
    preserves B `0x00000200`, X `0x00000400`, and Z `0x00000010`
    (`research/decomp/ghidra-export/chunk_0013.c:2197-2202`).
  - This proves injected normalized B/X/Z bits can reach actor command fields if
    the player-input bridge runs. It still does not identify original attack,
    special, ally charge, power-up, or audio cue semantics.
- Static B/X consumer inventory shows command handling is borg/action-specific, not
  one universal table:
  - `FUN_8015b0b4` uses X current bit `0x400` for borg id `0x061e`, but B
    current bit `0x200` for other borgs before advancing `actor+0x54c` and related
    action fields (`research/decomp/ghidra-export/chunk_0040.c:4265-4317`).
  - `FUN_800e622c` contains an X pressed-edge `actor+0x5bc & 0x400` path that can
    call the action helper cluster
    (`research/decomp/ghidra-export/chunk_0024.c:4523-4612`).
  - `FUN_801304b8` contains B pressed-edge `0x200` and X pressed-edge `0x400`
    branches gated by borg ids and cooldown fields
    (`research/decomp/ghidra-export/chunk_0034.c:4873-4947`).
- Direct `boot.dol` table reads on 2026-07-02 add exact table context for those
  consumers:
  - `zz_00e6048_` dispatches `PTR_FUN_803188e8[actor+0x540]`; raw DOL table
    entry 2 at `0x803188f0` points to `FUN_800e622c`.
  - `FUN_8015ae1c` dispatches `PTR_FUN_803448b0[actor+0x540]`; raw DOL table
    entry 2 at `0x803448b8` points to `FUN_8015b0b4`.
  - Raw DOL pointer `0x80335c84` points to `FUN_801304b8` as entry 3 in a small
    table beginning near `0x80335c78`, but no decompiled dispatch reference to
    that table base has been identified yet.
  These table facts are exact code/data facts, not gameplay labels.
- Static audio-wrapper pass on 2026-07-02 found exact cue arguments inside one
  candidate B/X consumer path:
  - In `FUN_801304b8`, a B pressed-edge branch for borg id `0x0106` calls
    `zz_00f036c_(actor, 0xeb)` after `zz_00e058c_(actor, 2, 10)`.
  - The adjacent B pressed-edge branch for borg id `0x0107` calls
    `zz_00f036c_(actor, 0xaa)` after `zz_00e058c_(actor, 3, ...)`.
  - `zz_00f036c_` routes actor requests to positional SFX playback
    (`zz_00f04b4_` -> `zz_00efb3c_`) and null-actor requests straight to
    `zz_00efb3c_`.
  These are exact static code facts for this candidate branch only. They are not
  enough to assign browser B/X cue IDs until a live trace ties PAD input, action
  dispatch, and the audio wrapper call together.
- Static Z inventory found one exact Z current-bit consumer in the focused pass:
  `FUN_8005a298` tests `actor+0x5b4 & 0x10` and writes `actor+0x73c`
  (`research/decomp/ghidra-export/chunk_0007.c:2772-2805`). This is not enough to
  label ally-lock target selection, charge, or power-up.
- Static common-update route on 2026-07-02 links the Z candidate to the actor update
  root: `FUN_80055568` is reached from five known callers
  (`FUN_800547dc`, `FUN_80054c78`, `FUN_80054cbc`, `FUN_80054cf0`,
  `FUN_80054d54`); two of those (`FUN_80054cbc`/`FUN_80054cf0`) call
  `FUN_80056900` first, and `FUN_80055568` calls `zz_0059068_`, whose tail calls
  `FUN_8005a298`. This is static route proof only until a runtime trace hits it.
- Trace tooling update on 2026-07-02:
  - `scripts/dolphin-gdb-trace.mjs` now treats the new caller/consumer/dispatch
    breakpoints as active-actor hits, so traces dump `activeBaseStruct` and install
    active-borg runtime watchpoints when they fire.
  - `scripts/summarize-dolphin-gdb-trace.mjs` now reports `commandConsumer`
    proof counts, `firstCommandConsumer` actor fields (`+0x3e8`, `+0x540`,
    `+0x5b4`, `+0x5bc`, `+0x6fe`, `+0x73c`, `+0x74a/+0x74e/+0x750`), and
    `firstAudio` register arguments for cue-handle inspection.
  - The audio-proof set now includes `audio-sfx-request-wrapper` at `0x800f036c`
    so future action-labeled traces can capture `r3` actor, `r4` cue id, and LR
    caller before falling into broader audio queues.
- Fresh failed action/audio traces from `dolphin/right before hit.sav`:
  - `user-data/dolphin-trace/traces/input-bridge-action-only/gdb-trace-2026-07-02T21-06-13-352Z.json`
    captured 80 `audio-seq-continue` hits and no input/action hits. Result: the
    always-hot sequence breakpoint can starve action proof.
  - `user-data/dolphin-trace/traces/input-bridge-action-noaudio/gdb-trace-2026-07-02T21-08-12-391Z.json`
    captured zero hits before timeout. Result: this save-state/launch path did not
    enter the current input/action bridge under the selected breakpoint set.
- Fresh focused captures after adding caller/consumer IDs:
  - `user-data/dolphin-trace/traces/x-consumer-candidates-2v2/gdb-trace-2026-07-02T21-31-10-770Z.json`
    injected X for 90 frames from `2v2 gred cotrolled players no cpu.sav`.
    It captured X PAD bytes and normalized current/pressed `0x00000400`, but zero
    `player-input-bridge`, command-mask, actor command, command-consumer,
    action-state, or audio hits.
  - `user-data/dolphin-trace/traces/actor-update-candidate-liveness/gdb-trace-2026-07-02T21-34-15-797Z.json`
    used no PAD breakpoints and watched the input bridge callers, post-input actor
    update, B/X/Z consumer candidates, and action anchors from
    `dolphin/right before hit.sav`. It captured zero hits before timeout.
  Result: current save-state launch paths still do not produce original actor input
  or action proof. Do not promote B/X/Z mechanics from these traces.
- Fresh common-update liveness captures after adding `FUN_80055568` and three
  non-input caller probes:
  - `actor-common-liveness-2v2` from `2v2 gred cotrolled players no cpu.sav`:
    zero actor-input, command-consumer, action, param-tier, or audio hits.
  - `actor-common-liveness-battle1-start` from
    `user-data/GG4E/traces/battle1_start_checkpoint.sav`: zero proof hits.
  - `actor-common-liveness-2v2-no547dc` repeated the 2v2 liveness run without the
    first caller breakpoint and still captured zero proof hits.
  - `audio-wrapper-liveness-2v2` added the new `audio-sfx-request-wrapper` probe to
    the same common-update/consumer set from the 2v2 save and also captured zero hits.
  Result: the current save-state/batch launch paths still do not execute these
  actor-update anchors under the selected trace windows. Need verified visible
  gameplay boot path or a different battle state before more B/X/Z claims.

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
- `user-data/dolphin-trace/traces/input-bridge-action-only/gdb-trace-2026-07-02T21-06-13-352Z.json`
  - Narrow action/audio pass from `dolphin/right before hit.sav`.
  - 80 hits, all `audio-seq-continue`.
  - Result: confirms this audio breakpoint is too hot to mix with low-frequency input
    bridge/action proof at small hit budgets.
- `user-data/dolphin-trace/traces/input-bridge-action-noaudio/gdb-trace-2026-07-02T21-08-12-391Z.json`
  - Same save and action-focused IDs with the hot audio breakpoint removed.
  - 0 hits before timeout.
  - Result: this boot path still does not prove B/X/Z action consumers.
- `user-data/dolphin-trace/traces/x-consumer-candidates-2v2/gdb-trace-2026-07-02T21-31-10-770Z.json`
  - Deterministic X injection from `2v2 gred cotrolled players no cpu.sav`.
  - 435 hits, with X observed in PADRead and normalized slot 0 as
    `current=0x00000400`, `pressed=0x00000400`.
  - Zero actor-input bridge, command-consumer, action-state, param-tier, or audio hits.
  - Result: X still only proves PAD normalization on this save/launch path.
- `user-data/dolphin-trace/traces/actor-update-candidate-liveness/gdb-trace-2026-07-02T21-34-15-797Z.json`
  - No-PAD liveness check from `dolphin/right before hit.sav` using input bridge
    callers and B/X/Z consumer/action anchors.
  - 0 hits before timeout.
  - Result: this save/launch path does not reach the actor update/action route under
    the current selected anchors.
- `user-data/dolphin-trace/traces/actor-common-liveness-2v2/gdb-trace-2026-07-02T21-44-44-549Z.json`
  - No-PAD liveness check from `2v2 gred cotrolled players no cpu.sav` using the
    five static `FUN_80055568` caller/root probes plus B/X/Z consumer/action anchors.
  - 0 hits before timeout.
  - Result: this save/launch path does not reach the common actor update route under
    the current selected anchors.
- `user-data/dolphin-trace/traces/actor-common-liveness-battle1-start/gdb-trace-2026-07-02T21-45-44-147Z.json`
  - Same liveness check from `user-data/GG4E/traces/battle1_start_checkpoint.sav`.
  - 0 hits before timeout.
  - Result: no B/X/Z action proof.
- `user-data/dolphin-trace/traces/actor-common-liveness-2v2-no547dc/gdb-trace-2026-07-02T21-46-59-711Z.json`
  - Repeat 2v2 liveness check with `actor-update-spawn-entry` omitted, to rule out
    first-breakpoint setup weirdness.
  - 0 hits before timeout.
  - Result: no B/X/Z action proof.
- `user-data/dolphin-trace/traces/audio-wrapper-liveness-2v2/gdb-trace-2026-07-02T21-53-42-635Z.json`
  - No-PAD liveness check from `2v2 gred cotrolled players no cpu.sav` using common
    actor-update probes, B/X/Z consumer probes, and `audio-sfx-request-wrapper`.
  - 0 hits before timeout.
  - Result: no cue ID proof; wrapper probe is ready, but this launch path still misses.

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
- Input bridge callers at `0x80054cbc` and `0x80054cf0`, and post-input actor
  command update at `0x80059068` (`zz_0059068_`). If those miss, the save/launch
  path is not running the relevant actor update route.
- Common actor update root at `0x80055568` (`FUN_80055568`) plus its non-input
  caller probes `0x800547dc`, `0x80054c78`, and `0x80054d54`.
- Command-mask helper at `0x8008bbc0` (`zz_008bbc0_`) preserving B `0x200`,
  X `0x400`, and Z `0x10` before `actor+0x5b4`.
- Candidate command consumers from static C/DOL table proof:
  `FUN_8005a298`, `zz_00e6048_`/`FUN_800e622c`,
  `FUN_801304b8`, and `FUN_8015ae1c`/`FUN_8015b0b4`.
- Writes to `active_borg_base+0x544`, `+0x5e0`, `+0x6b4`, `+0x6b6`, `+0x6fe`, and `+0x720`.
- Target pointer writer.
- HP writer.
- Action helper/projectile pointer from `0x800660b8`.
- Audio SFX request wrapper at `0x800f036c` (`zz_00f036c_`) in a proven
  action-labeled trace; `r4` alone is not a gameplay cue assignment without the
  matching PAD/action path and LR caller.
- Gameplay camera follow formula. The latest camera trace proves callsites and static vectors, but not target-relative distance/height/lag.

## Next Trace

Use visible Dolphin or a verified gameplay save-state boot path, then run one trace per
action. For physical controller proof, do not use `--inject-pad-buttons`; for deterministic
downstream PADStatus proof, use the post-PADRead injector below. Summarize the ignored raw JSON
before promoting any rule:

```bash
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\dolphin\right before hit.sav"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids=pad-read,pad-post-read-normalization,pad-normalization-complete,game-pad-normalization-cluster,actor-update-spawn-entry,actor-update-no-input-54c78,player-input-update-simple,player-input-update-with-69960,actor-update-transition-entry,actor-common-update,player-input-bridge,input-command-mask-helper,post-input-actor-command-update,active-borg-command-current,active-borg-command-pressed,state-transition-primitive,borg-state-dispatch,active-action-handler-invuln,action-helper-cluster,battle-frame-target-action-dispatch,z-command-state-candidate,x-table-dispatch-803188e8,x-pressed-action-transition-candidate,bx-pressed-borg-action-candidate,bx-table-dispatch-803448b0,bx-borg-conditional-action-061e --inject-pad-buttons=B --inject-pad-frames=90 --max-hits=1200 --timeout-ms=60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\bx-close-b"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids=pad-read,pad-post-read-normalization,pad-normalization-complete,game-pad-normalization-cluster,actor-update-spawn-entry,actor-update-no-input-54c78,player-input-update-simple,player-input-update-with-69960,actor-update-transition-entry,actor-common-update,player-input-bridge,input-command-mask-helper,post-input-actor-command-update,active-borg-command-current,active-borg-command-pressed,state-transition-primitive,borg-state-dispatch,active-action-handler-invuln,action-helper-cluster,battle-frame-target-action-dispatch,z-command-state-candidate,x-table-dispatch-803188e8,x-pressed-action-transition-candidate,bx-pressed-borg-action-candidate,bx-table-dispatch-803448b0,bx-borg-conditional-action-061e --inject-pad-buttons=X --inject-pad-frames=90 --max-hits=1200 --timeout-ms=60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\x-special"
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --only-ids=pad-read,pad-post-read-normalization,pad-normalization-complete,game-pad-normalization-cluster,actor-update-spawn-entry,actor-update-no-input-54c78,player-input-update-simple,player-input-update-with-69960,actor-update-transition-entry,actor-common-update,player-input-bridge,input-command-mask-helper,post-input-actor-command-update,active-borg-command-current,active-borg-command-pressed,state-transition-primitive,borg-state-dispatch,active-action-handler-invuln,action-helper-cluster,battle-frame-target-action-dispatch,z-command-state-candidate,x-table-dispatch-803188e8,x-pressed-action-transition-candidate,bx-pressed-borg-action-candidate,bx-table-dispatch-803448b0,bx-borg-conditional-action-061e,param-tier-reset,param-tier-delta-127,param-tier-delta-63,param-tier-refresh --inject-pad-buttons=Z --inject-pad-frames=90 --max-hits=1200 --timeout-ms=60000 --out-dir "D:\GotYaForce\user-data\dolphin-trace\traces\z-ally-lock"
rtk .\tools\node\node.exe scripts\summarize-dolphin-gdb-trace.mjs user-data\dolphin-trace\traces\bx-close-b user-data\dolphin-trace\traces\x-special user-data\dolphin-trace\traces\z-ally-lock
```

Proof gate: a B/X mapping needs PAD bytes and either `state-transition-primitive` or
`borg-state-dispatch`/`active-action-handler-invuln` in the same labeled capture. Z
charge/power-up needs a Z-labeled PAD sample and a `param-tier-*` hit. Audio cue IDs need
an action-labeled trace with audio hits plus argument/handle inspection; counts alone do not
identify a cue.

Run audio as a separate pass after an action trace has proven the command path. Start with
`audio-sfx-request-wrapper` plus the proven action/consumer IDs; only add broader audio
breakpoints after the wrapper caller and cue argument are understood. Do not mix
`audio-seq-continue` into small B/X/Z proof budgets; it can consume every hit.
