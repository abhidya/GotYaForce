# GG4E Mechanics Runtime Trace Plan

Date: 2026-06-30
Region: GG4E / USA
Target ISO: `D:\GotYaForce\Gotcha Force.iso`
Target DOL: `D:\GotYaForce\user-data\GG4E\disc\sys\boot.dol`
Symbol map: `D:\GotYaForce\research\symbols\GG4E-CSM-20220412.map`
Companion kit: `research/traces/GG4E/breakpoints-watchpoints.json`

## Scope

Produce a small Dolphin/static trace kit for importing original camera, lock-on, targeting, jump/fly, shoot, melee, damage, death, next-borg spawn, and CPU AI mechanics. This plan intentionally avoids broad instruction logs and broad branch watches. Each Dolphin use should start from a save state immediately before one event, enable only that event window, capture the fields listed in the JSON kit, then disable the breakpoints.

I did not run Dolphin for this plan. The addresses and DOL offsets below come from the GG4E symbol map, the existing GG4E DOL trace playbook, and a static parse of `boot.dol` section headers.

## Launch And Symbols

Launch with the debugger:

```powershell
rtk .\dolphin\Dolphin.exe --debugger --logger --exec="D:\GotYaForce\Gotcha Force.iso"
```

If the flags do not open the debugger, start `D:\GotYaForce\dolphin\Dolphin.exe`, then open the Debugger and Logger panes manually.

Symbol map setup:

1. In Dolphin, use `File > Open User Folder`.
2. Create or open `Maps`.
3. Copy `D:\GotYaForce\research\symbols\GG4E-CSM-20220412.map` into that folder.
4. Name the copied file `GG4E08.map`.
5. If symbols do not auto-load, also try `GG4E.map`, then use `Symbols > Load Symbol Map`.

## DOL Offset Basis

`boot.dol` maps most mechanics code into `text1`:

| Section | File offset | Runtime address | Size |
| --- | ---: | ---: | ---: |
| `text1` | `0x000025e0` | `0x800055e0` | `0x002aab80` |
| `data3` | `0x002b7e60` | `0x802bae60` | `0x000f42c0` |
| `data5` | `0x003aec40` | `0x80436a20` | `0x00006ae0` |

For example, `0x8005d4b0` maps to DOL offset `0x0005a4b0`, and static float `0x80437448` maps to DOL offset `0x003af668`.

## Trace Windows

Use one save state per row. In each window, enable only the listed group from `breakpoints-watchpoints.json`.

| Group | Save state setup | Event to trigger | Primary proof to capture |
| --- | --- | --- | --- |
| Camera | Arena loaded, one controllable borg, one visible enemy, no active attack. | Let one frame run, move/turn slightly, then lock onto enemy. | Final eye/up/interest vectors from `C_MTXLookAt` and HSD CObj setters; active borg and target pointers if present in callers. |
| Lock-on/targeting | Same arena, two enemies at different bearings if possible. | Tap/hold the lock/target input once, then target-cycle if available. | PAD state, `cTeam::GetPlayer(int)` results, action/state fields, and any candidate target pointer writer. |
| Jump/fly | Grounded flying-capable borg and non-flying borg if possible. | Press jump once, air-jump, then hold boost/fly. | Changes to `base+0x544`, `base+0x5e0`, `base+0x6b4`, `base+0x6b6`, `base+0x6fe`; any velocity/grounded fields discovered from the same writer. |
| Shoot | Enemy locked at mid range. | Tap each ranged shot once in separate short runs. | Input bits, action index at `base+0x6fe`, handler/table lookup near `0x802d35a4`, projectile/shot object pointer if returned or stored. |
| Melee | Enemy locked at close range. | Press close-range attack once. | Action index transition, target pointer, hitbox or contact pointer, and first damage-side writer. |
| Damage | Player borg vulnerable and enemy ready to hit. | Take one hit, then take one knockdown/wake-up hit. | Wake-up timer init/countdown, target base pointer, invulnerability timer at `base+0x720`, HP field writer if found. |
| Death | Player or enemy at low HP. | Kill one borg, pause immediately after defeat state starts. | Death/swap lead callstack, player pointer, active borg pointer, remaining GF-energy or force index if visible. |
| Next-borg spawn | Same as death, force has at least two borgs. | Let defeated borg disappear and next borg spawn. | `cTeam::GetPlayer(int)` lookups, `cPlayer::ClearSwapControllerTimer`, active index before/after, next active borg base. |
| CPU AI | Player idle, one CPU enemy active and visible. | Do not press input for a short window; let CPU approach and attack. | CPU player/borg pointer, target pointer, action index transitions, and branch from AI decision into shared action handlers. |

## Confirmed Anchors

- `0x8005d4b0` / DOL `0x0005a4b0`: wake-up invincibility timer init; inspect `r3`.
- `0x8005c7d8` / DOL `0x000597d8`: secondary wake-up/invulnerability init.
- `0x80055c00` / DOL `0x00052c00`: timer countdown; inspect `r31`.
- `0x80437448` / DOL `0x003af668`: static float `60.0`.
- `base+0x720`: confirmed active-borg wake-up/invulnerability timer after base is captured.

## High-Confidence Runtime Fields

Capture these only after an active borg base is known from `0x8005d4b0` or `0x80055c00`:

| Field | Size | Current meaning |
| --- | ---: | --- |
| `base+0x544` | 1 byte | likely action/state byte |
| `base+0x5e0` | 4 bytes | likely flags |
| `base+0x6b4` | 2 bytes | likely countdown/state halfword |
| `base+0x6b6` | 2 bytes | likely countdown/state halfword |
| `base+0x6fe` | 2 bytes | likely action/handler index |
| `base+0x720` | 4 bytes | confirmed wake-up/invulnerability timer |

The action/handler index at `base+0x6fe` is used with a table near `0x802d35a4` (DOL `0x002d05a4`).

## What Still Requires Runtime Capture

Do not implement these from static guesses alone:

- Lock-on target pointer location and target selection rules.
- Projectile spawn table, projectile owner/target fields, homing parameters, and shot cooldowns.
- Melee hitbox/contact representation and exact close-range attack gating.
- HP field offset, damage formula, defense scaling, hitstun, and knockdown thresholds.
- Death-to-next-borg timing, force active index location, and GF-energy decrement source.
- Jump/fly velocity fields, grounded/airborne flags, boost drain, and per-borg air-jump counts.
- CPU AI decision state, target choice, approach/retreat thresholds, and attack selection.

The JSON kit marks these as `runtime_capture_required` where the base pointer or field offset is not yet known.
