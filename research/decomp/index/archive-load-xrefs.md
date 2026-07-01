# Archive Load Xrefs

Generated: 2026-07-01T09:59:46.570Z

## Principle

Archive/stage/load behavior must be ported from original file-open, archive-parse, table, and trace evidence. This report does not authorize fake Challenge stage mappings.

## Findings

- DVDOpen has 2 static callers in the current index: 0x802754ec FUN_802754ec, 0x802756fc FUN_802756fc.
- HSD_ArchiveParse has 2 static callers in the current index: 0x80006c88 zz_0006c88_, 0x8004d548 zz_004d548_.
- 0x800419ec reads DAT_803bb4a0, FLOAT_80437068 and constants 0x3e4, 4, 0x0, 0x600, 0x604, 0x14, 0xc28, 0xff before calling 0x80006c88 zz_0006c88_.
- 0x80006c88 calls 0x8025b00c gnt4_HSD_ArchiveParse_bl, 0x8025b178 zz_025b178_, 0x8025b1b0 gnt4_HSD_ArchiveGetPublicAddress_bl; this is the proven parse/public-address wrapper for active object archive data.
- boot.dol static stage-code scan still has 0 st## hits, so Challenge arena selection still requires runtime archive-open tracing.

## Proven Call Chains

| Chain | Direct path | Proves |
| --- | --- | --- |
| active-borg-spawn-to-hsd-parse | 0x800541ac `FUN_800541ac` -> 0x800419ec `zz_00419ec_` -> 0x80006c88 `zz_0006c88_` -> 0x8025b00c `gnt4-HSD_ArchiveParse-bl` | battle spawn init reaches original HSD_ArchiveParse through the active archive attach wrapper |
| active-object-init-to-hsd-parse | 0x80057b78 `FUN_80057b78` -> 0x800419ec `zz_00419ec_` -> 0x80006c88 `zz_0006c88_` -> 0x8025b00c `gnt4-HSD_ArchiveParse-bl` | active object init reaches original HSD_ArchiveParse through the same attach wrapper |
| active-borg-spawn-to-public-address | 0x800541ac `FUN_800541ac` -> 0x800419ec `zz_00419ec_` -> 0x80006c88 `zz_0006c88_` -> 0x8025b1b0 `gnt4-HSD_ArchiveGetPublicAddress-bl` | spawn init reaches HSD public-symbol lookup after archive parse |
| gcci-open-to-dvdopen | 0x802754ec `FUN_802754ec` -> 0x8020d1ec `gnt4-DVDOpen-bl` | gcCiOpen-style wrapper directly calls DVDOpen |
| gcci-get-file-to-dvdopen | 0x802756fc `FUN_802756fc` -> 0x8020d1ec `gnt4-DVDOpen-bl` | gcCiGetF-style wrapper directly calls DVDOpen |
| secondary-object-path-to-hsd-parse | 0x8004a754 `zz_004a754_` -> 0x8004d548 `zz_004d548_` -> 0x8025b00c `gnt4-HSD_ArchiveParse-bl` | secondary object setup path reaches original HSD_ArchiveParse |

## Root Functions

| Address | Current name | Inferred hint | Callers | Callees | Globals | Strings | Source |
| --- | --- | --- | ---: | ---: | --- | --- | --- |
| 0x8020d1ec | `gnt4-DVDOpen-bl` | `gnt4-DVDOpen-bl` | 2 | 3 | DAT_80436524 | `s_Warning__DVDOpen____file___s__wa_803a4f48` | `research/decomp/ghidra-export/chunk_0064.c:2391` |
| 0x802754ec | `FUN_802754ec` | `` | 0 | 5 | DAT_8040b1d0, DAT_8040b1cc, DAT_8040b1d4, DAT_8040c178 | `s_E0092908_fname_is_null__gcCiOpen_802b7750`<br>`s_E0092910_not_enough_handle_resou_802b7798`<br>`s_E0092911_DVDOpen_fail__gcCiOpen__802b77c8` | `research/decomp/ghidra-export/chunk_0074.c:6214` |
| 0x802756fc | `FUN_802756fc` | `` | 0 | 5 | DAT_8040b1d0, DAT_8040b1cc, DAT_8040c178 | `s_E0092901_fname_is_null__gcCiGetF_802b77ec`<br>`s_E0040201_can_t_open_a_file__gcCi_802b7818`<br>`s_E0040202_can_t_close_a_file__gcC_802b7848` | `research/decomp/ghidra-export/chunk_0075.c:1` |
| 0x8025b00c | `gnt4-HSD_ArchiveParse-bl` | `gnt4-HSD_ArchiveParse-bl` | 2 | 3 | none | `s_HSD_ArchiveParse__byte_order_mis_803ad5c8` | `research/decomp/ghidra-export/chunk_0072.c:3616` |
| 0x8025b1b0 | `gnt4-HSD_ArchiveGetPublicAddress-bl` | `gnt4-HSD_ArchiveGetPublicAddress-bl` | 2 | 1 | none | none | `research/decomp/ghidra-export/chunk_0072.c:3698` |
| 0x80006c88 | `zz_0006c88_` | `assets-animation_candidate_80006c88` | 3 | 3 | none | none | `research/decomp/ghidra-export/chunk_0000.c:1312` |
| 0x8004d548 | `zz_004d548_` | `assets-animation_candidate_8004d548` | 1 | 2 | none | none | `research/decomp/ghidra-export/chunk_0006.c:2366` |
| 0x800419ec | `zz_00419ec_` | `force-setup_candidate_800419ec` | 2 | 6 | DAT_803bb4a0, FLOAT_80437068 | none | `research/decomp/ghidra-export/chunk_0004.c:9936` |
| 0x800541ac | `FUN_800541ac` | `active_borg_spawn_init_from_slot_tables` | 0 | 22 | FLOAT_80437250, PTR_DAT_80433934, PTR_DAT_80433930, FLOAT_8043725c | none | `research/decomp/ghidra-export/chunk_0006.c:6999` |
| 0x80057b78 | `FUN_80057b78` | `active_object_init_from_slot_tables` | 0 | 13 | PTR_DAT_80433934 | none | `research/decomp/ghidra-export/chunk_0007.c:896` |

## Current Web Evidence

- `apps/game/src/sim/battleScene.ts:10` contains `load`.
- `apps/game/src/sim/adapter.ts:23` contains `DEFAULT_ARENA_STAGE`.
- `apps/game/src/main.ts:559` contains `async function loadStage`.
- `packages/formats/src/hsd-anim.ts:1` contains `HSD`.
- `packages/render/src/index.ts` does not contain `Stage`; keep this as a porting gap.

## Supporting Artifacts

- `research/decomp/index/challenge-flow-evidence.md`
- `research/asset-inventory/stage-code-evidence.md`
- `research/asset-inventory/stage-geometry-collision.md`
- `research/asset-inventory/stage-lighting-render-state.md`

## Required Next Trace Tasks

- Break on 0x802754ec, 0x802756fc, and 0x8020d1ec while entering Challenge battle 1 and record filename strings.
- Break on 0x8025b00c and 0x80006c88 during the same run to connect loaded archive bytes to parsed HSD public names.
- Watch DAT_803bb4a0 and object+0x3e4 in 0x800419ec to confirm which slot/type selects each object archive pointer.
- Do not map human arena names or Challenge stage rotation to st## until the trace records the selected st## archive IDs.

