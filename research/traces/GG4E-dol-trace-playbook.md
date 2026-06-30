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

## Camera / Input Anchors

Use these to import camera behavior into the app from evidence instead of tuning `OrbitControls`.

| Address | Use |
| --- | --- |
| `0x80008998` | `cCameraManager::HasCamera(cBaseCamera...)` |
| `0x80174adc..0x80174ce8` | likely game camera/update cluster; calls `C_MTXLookAt`, vector math, `HasCamera` |
| `0x801dc668..0x801dc744` | smaller camera/vector lead |
| `0x8020b61c` | `C_MTXLookAt`; capture final eye/up/interest vectors |
| `0x80247198` | `HSD_CObjSetInterest` |
| `0x80247270` | `HSD_CObjSetEyePosition` |
| `0x80247810` | `HSD_CObjSetUpVector` |
| `0x8024807c` | `HSD_CObjSetFov` |
| `0x8010d450` | likely game-side PAD read/normalization cluster |
| `0x8021379c` | likely `PADRead` |
| `0x80212a14` | `PADClampCircle` |

Capture per frame: camera manager pointer, `cBaseCamera` pointer, HSD CObj pointer, eye/interest/up vectors, roll/fov/near/far, final look-at matrix, active borg pointer, target/enemy pointer if known, raw/clamped PAD state.

Known HSD CObj field leads:

- `cobj+0x24`: eye WObj pointer.
- `cobj+0x28`: interest WObj pointer.
- `cobj+0x38`: near.
- `cobj+0x3c`: far.
- `cobj+0x40`: fov when projection type byte `cobj+0x50 == 1`.

## Combat / Action-State Anchors

Confirmed active-borg struct field:

- `base+0x720`: wake-up/invulnerability timer.

High-confidence nearby state leads:

- `base+0x544`: likely action/state byte; read/written heavily in same cluster.
- `base+0x5e0`: flags.
- `base+0x6b4`, `base+0x6b6`: countdown/state halfwords.
- `base+0x6fe`: action/handler index; used with table near `0x802d35a4`.

Candidate clusters:

| Address range | Use |
| --- | --- |
| `0x8005568c..0x80055dcc` | per-frame object timer/status update; contains `0x80055c00` |
| `0x8005c290..0x8005c4a4` | timer/status helper touching `+0x720`, `+0x6b4`, `+0x6b6` |
| `0x8005c694..0x8005c7f0` | secondary wake/invulnerability setter |
| `0x8005d494..0x8005d9d8` | likely knockdown/wake state transition |
| `0x8005ec04..0x800660b8` | dense action/state handlers touching `+0x544` |
| `0x800660b8..0x80068004` | action/helper cluster |
| `0x8006a104..0x8006ae60` | helpers called from wake/action cluster |
| `0x80281c38..0x80281e60` | death/swap lead; calls `cPlayer::ClearSwapControllerTimer` |
| `0x80297538..0x802a5e70` | team/player lookup band; many `cTeam::GetPlayer(int)` callers |

Do not implement lock-on, projectile homing, melee hitboxes, death/respawn, or AI behavior from guesses. Use short watch windows around one input/event, then backtrace writers.

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
