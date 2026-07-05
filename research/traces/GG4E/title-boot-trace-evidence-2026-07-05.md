# Title-intro boot trace evidence (2026-07-05)

Live Dolphin GDB capture of the fresh-boot → title-desk-intro sequence (no save state).
Trace plan: `research/traces/GG4E/title-boot-capture-plan.json` (group `title-boot`,
`desk-dispatcher` skipped — too noisy). Capture:
`user-data/dolphin-trace/traces/title-boot-diorama/gdb-trace-2026-07-05T20-42-03-872Z.json`.

## Breakpoint hit summary (30 hits, 0 errors)

| breakpoint | fn | hits | what it proves |
|---|---|---|---|
| `desk-intro-init` | `FUN_801c795c` @0x801c795c | 1 | Boot reached the desk intro (LR 0x801c7934 = the front-end entry that calls it) |
| `family-ctor-dispatch` | `zz_0056ce0_` @0x80056ce0 | 2 | Both actors' family ctors ran (anim-bank binding) |
| `desk-actor-control` | `FUN_801c81a0` @0x801c81a0 | 17 | All opcode-0x0d actor commands fired |
| `actor-anim-trigger` | `zz_0057ff8_` @0x80057ff8 | 10 | Every anim-start call |

State struct base (r3 in FUN_801c81a0): **`0x803D5D78`** (consistent across all hits).

## Resolved: `groupSel = 5` (was the family-ctor-gated TUNED question)

Every one of the 10 `zz_0057ff8_` hits passes **`r4 = 5`** (groupSel) — exactly the value
the ROM passes from opcode 0x0d mode 0, and exactly what `apps/game/src/ui/intro/titleVm.ts`
hardcodes (`actorPlayAnim(slot, 5, animId)`). **DERIVED-CONFIRMED live.** The
"groupSel=5 → g0 battle bank" mapping is still a port-side convention (the real +0x1d80
bank binding is inside each family ctor), but the groupSel VALUE the desk intro passes is
now proven, not inferred.

## Resolved: slot 1 = Sasuke (pl000a), runtime-confirmed

The borg-id table (`DAT_8038a4ec`, seeded into the state struct at `+0x10`) captured live
in RAM:

```
06 15  00 0A  FF FF  FF FF  FF FF
```

→ slot 0 = `0x0615` (G RED pl0615), slot 1 = `0x000a` (**Sasuke pl000a**), slots 2..5 empty.
This is the definitive runtime proof for the previously-static-only decode
(`research/decomp/title-intro-remaining-decode-2026-07-05.md` §1).

## actor-control payload matches the VM port exactly

The script bytecode at the PC (r4) for the first actor-control hits:

```
0D 01 00 00   actorControl mode=1 slot=0          -> reset G RED
0D 01 01 00   actorControl mode=1 slot=1          -> reset Sasuke
0D 00 00 00   actorControl mode=0 slot=0 value=0  -> G RED anim 0 (idle)
0D 00 01 00   actorControl mode=0 slot=1 value=0  -> Sasuke anim 0
0D 02 00 00   actorControl mode=2 slot=0 value=0  -> G RED visibility off
0D 02 00 01   actorControl mode=2 slot=0 value=1  -> G RED visibility on
```

This is byte-for-byte the dispatch `apps/game/src/ui/intro/titleVm.ts` `op_actorControl`
implements (mode 1 = reset via `actorReset`, mode 0 = `actorPlayAnim(slot, 5, value)`,
mode 2 = `actorSetVisible`). The port's opcode handling is faithful.

## Both actors animate

`zz_0057ff8_` hits alternate between the two actor struct pointers:
- `0x805DBDC0` = slot 0 (G RED)
- `0x805DDBC0` = slot 1 (Sasuke)

Both receive the same animId sequence: **0, 1, 6, 3, 4** (idle / move / jump_takeoff /
dash_back / dash_left). Matches `apps/game/src/ui/screens/TitleIntro.ts`'s
`ANIM_FILES_BY_ID` table.

## Still open: actor spawn coords

The state base is `0x803D5D78`; spawn coords live at `state + 0x1604 + slot*0xc`
(per `FUN_80056d28`). This trace captured memory at the register-pointed addresses
(state head + PC), not at `+0x1604`. A follow-up trace that reads
`0x803D5D78 + 0x1604` (+0x10 for slot 1) — or the actor structs' `+0x20/+0x24/+0x28`
position floats — would retire the last TUNED residual (`stageBaseForSlot`).

## Net

The two residuals flagged in `title-intro-remaining-decode-2026-07-05.md`:
- **groupSel=5 → g0 mapping**: groupSel value CONFIRMED (=5); the +0x1d80 bank-index
  resolution remains inside the family ctor (not a desk-intro concern).
- **anim source**: confirmed both partners animate via the borg mot path (zz_0057ff8_).

The intro VM port (`titleVm.ts`) is now backed by live runtime evidence for every
opcode it implements.
