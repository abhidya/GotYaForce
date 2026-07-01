# Challenge Battle 1 Memory Evidence

Generated: 2026-07-01T10:12:27.504950+00:00

## Principle

Challenge battle memory evidence can prove retained runtime data, but absence of strings does not prove absence of a load. Stage selection still needs DVDOpen/archive-open tracing if no selected st## string remains.

## Summary

- stageArchiveStringMatches: 0
- stageSetArchiveStringMatches: 0
- stageHitBinStringMatches: 0
- borgAnimJointStringMatches: 26605
- uniqueBorgAnimPrefixes: 8
- stageSelectionStatus: unproven: no st##_mdl.arc, st##.pzz, set####.arc, hit###.bin, or comhit.bin strings were found in the scanned Challenge battle save-state payloads or MEM1 dumps

## Source Scans

| Source | Kind | Bytes scanned | MEM1 state offset | Stage archive strings | Borg joint strings |
| --- | --- | ---: | --- | ---: | ---: |
| mem1_t1 | mem1 | 25165824 | 0x0 | 0 | 5509 |
| mem1_t2 | mem1 | 25165824 | 0x0 | 0 | 5282 |
| battle1_challenge | dolphin-sav | 187026760 | 0x620637e | 0 | 5509 |
| battle1_challenge_t2 | dolphin-sav | 187026760 | 0x620637e | 0 | 5282 |
| battle1_start_checkpoint | dolphin-sav | 187026760 | 0x620637e | 0 | 5023 |

## Stage String Evidence

No `st##_mdl.arc`, `st##.pzz`, `set####.arc`, `hit###.bin`, or `comhit.bin` strings were retained in the scanned Challenge battle memory/save-state payloads.

## Borg Animation Prefix Evidence

| Borg | Name | Energy | Matches | Sources | Bones seen | Note |
| --- | --- | ---: | ---: | --- | ---: | --- |
| pl0b00 | QUICK VALKRIE | 230 | 10056 | battle1_challenge: 3233<br>battle1_challenge_t2: 1795<br>mem1_t1: 3233<br>mem1_t2: 1795 | 28 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |
| pl0000 | NORMAL NINJA | 150 | 6137 | battle1_challenge: 1120<br>battle1_challenge_t2: 1676<br>battle1_start_checkpoint: 545<br>mem1_t1: 1120<br>mem1_t2: 1676 | 20 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |
| pl0615 | G RED | 300 | 5300 | battle1_challenge: 1060<br>battle1_challenge_t2: 1060<br>battle1_start_checkpoint: 1060<br>mem1_t1: 1060<br>mem1_t2: 1060 | 20 | Matches G RED, the active player borg named in research/decomp/ram-trace-analysis.md. |
| pl0a00 | WING SOLDIER | 200 | 2246 | battle1_challenge: 56<br>battle1_challenge_t2: 56<br>battle1_start_checkpoint: 2022<br>mem1_t1: 56<br>mem1_t2: 56 | 28 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |
| pl0700 | NORMAL SAMURAI | 300 | 1966 | battle1_challenge_t2: 655<br>battle1_start_checkpoint: 656<br>mem1_t2: 655 | 20 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |
| pl0200 | SWORD KNIGHT | 280 | 500 | battle1_start_checkpoint: 500 | 20 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |
| pl0002 | ARROW NINJA | 300 | 200 | battle1_start_checkpoint: 200 | 20 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |
| pl062a | G BLACK | 600 | 200 | battle1_challenge: 40<br>battle1_challenge_t2: 40<br>battle1_start_checkpoint: 40<br>mem1_t1: 40<br>mem1_t2: 40 | 20 | Resident animation joint strings prove this model/animation prefix was in memory, not that it was an active force slot. |

## Required Next Trace Tasks

- Use DVDOpen/gcCiOpen breakpoints from archive-load-xrefs to capture selected st## filenames during Challenge battle entry.
- Use active object spawn/init breakpoints to connect retained pl#### animation prefixes to live active borg object pointers.
- Do not treat resident pl####_b##_animjoint strings as a complete force roster until the object table is traced.
