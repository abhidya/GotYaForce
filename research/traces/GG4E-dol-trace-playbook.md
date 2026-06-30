# GG4E DOL Trace Playbook

Status: bounded fallback path when decompiled gameplay source is not present in the workspace.

Goal: gather original Gotcha Force mechanics evidence without broad emulator tracing or fragile browser/MCP automation.

## Tool Choice

- Primary: local files, symbol map, static analysis, extraction scripts.
- Dolphin use: manual GUI debugger only when mechanics need runtime proof.
- Avoid: full instruction logs, broad MCP control, guessed code paths.

## Launch

```powershell
rtk .\dolphin\Dolphin.exe --debugger --logger --exec="D:\GotYaForce\Gotcha Force.iso"
```

If launch flags fail, open `D:\GotYaForce\dolphin\Dolphin.exe`, then open Debugger and Logger panes manually.

## Symbols

1. Dolphin: `File > Open User Folder`.
2. Create/use `Maps`.
3. Copy `D:\GotYaForce\research\symbols\GG4E-CSM-20220412.map`.
4. Name copied file `GG4E08.map`.
5. If auto-load fails, also try `GG4E.map`, or use `Symbols > Load Symbol Map`.

Static target for Ghidra/source comparison:

```text
D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol
```

## First Breakpoint Proof

Use wake-up invincibility first because repo already has address evidence.

| Address | Use | DOL offset |
| --- | --- | --- |
| `0x8005d4b0` | wake-up invincibility init | `0x0005a4b0` |
| `0x8005c7d8` | secondary timer init | `0x000597d8` |
| `0x80055c00` | timer countdown | `0x00052c00` |
| `0x80437448` | static float `60.0` (`42 70 00 00`) | `0x003af668` |

At `0x8005d4b0`, inspect `r3`. Timer field is expected near `r3 + 0x720`.

At `0x80055c00`, inspect `r31`. Timer field is expected near `r31 + 0x720`.

Add a 4-byte read/write memory breakpoint on that computed runtime address. This gives an active-borg struct anchor for HP, state, position, action, hitstun, knockdown, and death fields.

## Adventure Flow Trace

Use Branch Watch snapshots around small event windows.

1. Snapshot before selecting Adventure/Story mission.
2. Snapshot after mission load.
3. Snapshot before final enemy kill.
4. Snapshot after victory/reward/save.

Save snapshot files and notes under:

```text
D:\GotYaForce\research\traces\GG4E\
```

Manual note format:

```text
event:
save/state:
PC:
LR:
callstack:
watched address:
value before:
value after:
asset/files loaded:
confidence:
```

## Extra Runtime Anchors

- `0x8025b34c` `gnt4-HSD_Randi-bl`: enable only around reward/GET screens; likely noisy.
- `0x80231c70` `SaveLoad::DidGameIDChange(void)`.
- `0x80220e64` `CARDCheckAsync`.
- `0x8022332c` `CARDDeleteAsync`.
- `0x80223748` `CARDSetStatusAsync`.

## Fallback

If Branch Watch is too broad:

1. Make a save state immediately before the event.
2. Clear Branch Watch.
3. Run only the short event window.
4. Save Branch Watch snapshot.
5. Repeat with one narrowed breakpoint/watchpoint.

Do not chase full-game traces. Each trace must answer one system question.
