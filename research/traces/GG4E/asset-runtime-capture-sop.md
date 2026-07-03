# Asset Runtime Capture SOP

Date: 2026-07-03  
Region: GG4E / USA  
Plan file: `research/traces/GG4E/asset-runtime-capture-plan.json`

## Goal

Capture runtime proof for where extracted frontend assets should plug in, without guessing from filenames. Use static decomp/symbol evidence for breakpoint addresses, and use short Dolphin GDB captures only to prove runtime arguments, caller LR, file paths, public HSD names, cue ids, and AFS member candidates.

## Existing Inputs

- ISO: `D:\GotYaForce\Gotcha Force.iso`
- Dolphin: `D:\GotYaForce\dolphin\Dolphin.exe`
- Symbol map: `D:\GotYaForce\research\symbols\GG4E-CSM-20220412.map`
- Ghidra C: `D:\GotYaForce\research\decomp\ghidra-export`
- Organized decomp map: `D:\GotYaForce\research\decomp\organized\_map.tsv`
- Audio member index: `D:\GotYaForce\research\game-design\poq-adx-member-index.json`
- GDB trace harness: `D:\GotYaForce\scripts\dolphin-gdb-trace.mjs`
- Trace summarizer: `D:\GotYaForce\scripts\summarize-asset-trace.mjs`

## Known-Good Dolphin Run Evidence

Use `scripts\launch-dolphin-gdb.mjs` for capture runs. It pins the Dolphin user directory, ISO, debugger/logger flags, and GDB port instead of relying on global Dolphin state.

Known-good evidence paths:

| Evidence | What it proves |
| --- | --- |
| `D:\GotYaForce\research\traces\GG4E\dolphin-gdb-trace-results.md` | Local Dolphin GDB stub works through `scripts\launch-dolphin-gdb.mjs` on `127.0.0.1:5555` |
| `D:\GotYaForce\user-data\dolphin-trace\traces\gdb-trace-2026-06-30T08-10-54-261Z.json` | Broad proof trace: 120 live hits, no errors |
| `D:\GotYaForce\user-data\dolphin-trace\traces\camera-next\gdb-trace-2026-06-30T21-28-19-435Z.json` | Focused visible-Dolphin camera trace: 120 hits, no errors |
| `D:\GotYaForce\user-data\dolphin-trace\traces\summary.json` | Prior trace inventory/summary |
| `D:\GotYaForce\research\traces\GG4E\spawn-evidence.json` | Existing save-state/MEM1 evidence paths for challenge battle captures |
| `D:\GotYaForce\research\traces\GG4E\challenge-battle1-memory-evidence.md` | Notes on existing challenge battle save-state/MEM1 scans |

Important interpretation:

- For manual asset/event captures, launch visibly with `--batch 0`.
- The default headless `--batch` launch can prove the GDB path, but previous evidence shows a save-state action run can miss the active gameplay path under headless launch.
- Older docs reference `D:\GotYaForce\dolphin\soon we fight mirror b.sav`; that was a different-game save state and was deleted. Any old trace using it is invalid for GG4E gameplay evidence.
- Do not treat a command-line save-state path as proof that Dolphin reached that state. Start the trace only after visually confirming Dolphin is at the intended screen/state.
- Do not probe `127.0.0.1:5555` before tracing. The GDB stub is effectively single-client, and a TCP probe can consume the connection.

Useful save states already present:

| Save state | Best use |
| --- | --- |
| `D:\GotYaForce\main menu gotchaforce.sav` | Title/main-menu/UI/archive captures |
| `D:\GotYaForce\2v2 gred cotrolled players no cpu.sav` | Stable battle/audio captures |
| `D:\GotYaForce\dolphin\right before hit.sav` | Hit SFX / damage event capture |
| `D:\GotYaForce\dolphin\1BEFOREENEMYDIE.sav` | Death/result transition capture |
| `D:\GotYaForce\storymode-first-badguys.sav` | Story/adventure asset captures |

## Hard Rules

- Run one plan group per capture. Broad mixed captures are noisy and harder to prove.
- Do not probe `127.0.0.1:5555` with `Test-NetConnection`; Dolphin's GDB stub is effectively single-client and the probe can consume the connection.
- Keep captures short. Prefer `--max-hits 40` to `--max-hits 120` unless the first run proves it needs more.
- For audio, capture `asset-audio-high` first. Only run `asset-audio-afs-sinks` after you know the event window.
- A claim is high-confidence only when the trace has the relevant breakpoint hit, the caller LR maps back into decomp/symbols, and the captured argument matches a path/public name/cue id/AFS member.

## Standard Run Shape

Open two terminals in `D:\GotYaForce`.

Terminal A launches Dolphin visibly from a fresh boot. This is the preferred capture launch:

```powershell
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0
```

If a state is required, pass it explicitly and verify the screen before tracing:

```powershell
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0 --save-state "D:\GotYaForce\main menu gotchaforce.sav"
```

The launcher validates that the state file exists and contains the expected `GG4E` marker, then passes Dolphin's documented initial-state option as `--save_state=<absolute path>`. This only prevents obvious wrong files; visual confirmation is still required.

Terminal B runs the trace against the focused plan group:

```powershell
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --plan research\traces\GG4E\asset-runtime-capture-plan.json --groups asset-archive-flow --max-hits 60 --timeout-ms 60000 --out-dir user-data\dolphin-trace\traces\asset-archive-main-menu
```

After the trace finishes, summarize the newest JSON:

```powershell
rtk .\tools\node\node.exe scripts\summarize-asset-trace.mjs user-data\dolphin-trace\traces\asset-archive-main-menu\gdb-trace-*.json
```

Send back either the summary output or the JSON path.

Manual GUI fallback, only if the wrapper fails:

```powershell
rtk .\dolphin\Dolphin.exe --debugger --logger --exec="D:\GotYaForce\Gotcha Force.iso"
```

If the flags fail, open `D:\GotYaForce\dolphin\Dolphin.exe` manually, then open the Debugger and Logger panes. The wrapper remains preferred because it uses the known trace user folder: `D:\GotYaForce\user-data\dolphin-trace`.

## Capture Recipes

### UI / HSD Assets

Use this for `tl00`, `box00`, `entry00`, `vsel00`, `vsel01`, `brif00`, `rpot*`, `staff00`, and stage archive loads.

```powershell
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --plan research\traces\GG4E\asset-runtime-capture-plan.json --groups asset-archive-flow --max-hits 80 --timeout-ms 90000 --out-dir user-data\dolphin-trace\traces\asset-archive-main-menu
```

Manual action: reach the intended menu/state in visible Dolphin, then start the trace and move through exactly one screen transition. For example, main menu to Challenge, Challenge to Load Box, Load Box to force select, or force select to battle intro. One transition per trace is best.

### Challenge State Ownership

Use this to prove which original Challenge state owns a frontend screen/result.

```powershell
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --plan research\traces\GG4E\asset-runtime-capture-plan.json --groups asset-challenge-state --max-hits 80 --timeout-ms 90000 --out-dir user-data\dolphin-trace\traces\asset-challenge-state-main-menu
```

Manual action: reach the main menu in visible Dolphin, start the trace, then enter Challenge and proceed until the screen/state you care about appears. This captures the state machine around `dispatch_challenge_flow_state`, stage selection, battle setup, post-battle, clear, and fail branches.

### Audio Cue Requests

Use this first for menu SFX, hit SFX, battle SFX, or result SFX.

```powershell
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --plan research\traces\GG4E\asset-runtime-capture-plan.json --groups asset-audio-high --max-hits 40 --timeout-ms 45000 --out-dir user-data\dolphin-trace\traces\asset-audio-high-2v2
```

Manual action: reach the intended battle/menu state in visible Dolphin, start the trace, then trigger one event only, such as one shot, one hit, one menu confirm, or one result transition. The important fields are LR caller and `r4` cue id at `positional-sfx-request`.

### AFS Member Resolution

Use this after the high-level audio trace proves the event window.

```powershell
rtk .\tools\node\node.exe scripts\launch-dolphin-gdb.mjs --batch 0
rtk .\tools\node\node.exe scripts\dolphin-gdb-trace.mjs --plan research\traces\GG4E\asset-runtime-capture-plan.json --groups asset-audio-afs-sinks --max-hits 30 --timeout-ms 45000 --out-dir user-data\dolphin-trace\traces\asset-audio-afs-2v2
```

Manual action: repeat the same single event from the high-level run. The summarizer will print register and stack candidates that match `poq-adx-member-index.json`.

For extra stack detail on an AFS run:

```powershell
rtk .\tools\node\node.exe scripts\summarize-asset-trace.mjs --stack --hits=20 user-data\dolphin-trace\traces\asset-audio-afs-2v2\gdb-trace-*.json
```

## What Counts As Proof

For UI/HSD:

- `dvd-open` path string identifies the file/archive, or
- `hsd-archive-public-address` captures a public symbol name, and
- LR/caller places it in the expected Challenge state or screen transition.

For audio:

- `positional-sfx-request` captures cue id in `r4`, and LR maps to the action/state caller.
- `mwply-start-afs` or `mwply-start-afs-loop-entry` captures a register/stack candidate that matches an AFS member index.
- The member index maps to an exported key in `poq-adx-member-index.json`.

For stage variants:

- `challenge-select-stage` captures the state transition, and archive/file captures in the same short window prove which `st##` archive is opened.

## Failure Triage

| Symptom | Most likely cause | Fix |
| --- | --- | --- |
| 0 hits | Wrong group for the current save/event, or event never triggered | Use a save closer to the event and run one manual action |
| Trace times out after setup | Breakpoints installed but no event crossed them | Keep Dolphin visible and perform the action after the trace command starts |
| Empty/odd setup response on one breakpoint | GDB stub was already consumed or Dolphin needs restart | Close Dolphin, relaunch, avoid TCP probes |
| Hundreds of `sndSeqContinue` hits | Sequence breakpoint is too noisy | Lower `--max-hits` or use only `positional-sfx-request` |
| Low-level AFS hits but no clear index | Need high-level cue trace first | Run `asset-audio-high`, then repeat event with `asset-audio-afs-sinks` |
