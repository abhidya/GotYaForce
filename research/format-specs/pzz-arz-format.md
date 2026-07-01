# PZZ/ARZ archive format notes

Generated: 2026-07-01T03:10:58.081Z
Scanner: `scripts/inspect-pzz-arz.mjs`

## Inputs

- `user-data/GG4E/afs_data/root`
- `research/asset-inventory/particle-effect-inventory.json`
- `research/asset-inventory/weapons-effects-projectiles.json`
- `efct.pzz`
- `gets.pzz`
- `cmn_data.pzz`
- `st*.pzz`
- `pl*.pzz`
- `it####_mdl.arz`
- `stc##_mdl.arz`

## Summary

- Files scanned: 355
- PZZ archives: 252
- Direct ARZ files: 103
- PZZ members listed: 3104
- Compressed PZZ members: 2833
- Payload kinds: hsd-dat 1407, tpl-texture 833, empty 231, borg-data-bin 209, borg-hit-bin 209, mot-bank-container 186, unknown-binary 132

## PZZ layout

| Offset | Field | Observation |
|---:|---|---|
| `0x00` | `u32 memberCount` | Big-endian. All scanned PZZ files have plausible counts. |
| `0x04` | `u32 memberTable[memberCount]` | Each word is a block-count descriptor. Bit `0x40000000` marks pzzp-compressed payload. Low 30 bits are the number of `0x800` byte blocks occupied in the archive. |
| `0x800` | payload data | Members are stored sequentially after one fixed `0x800` byte header/table block. The sum of member block counts plus the header block matches every scanned file size. |

## ARZ / pzzp stream

ARZ files and compressed PZZ members use the same 16-bit big-endian LZ stream. There is no separate static magic in the direct `.arz` files scanned here; the first halfword is a control word. Control bits are consumed from bit 15 down to bit 0. Literal tokens copy one 16-bit word. Back-reference tokens use an 11-bit word distance and a 5-bit word count, with a zero count extended by the following word. A back-reference with distance zero terminates the stream.

## Representative PZZ archives

| Archive | Role | Members | Compressed/raw/zero | Valid block sum | Recognized member kinds |
|---|---|---:|---|---|---|
| `user-data/GG4E/afs_data/root/cmn_data.pzz` | shared common battle-data PZZ archive | 4 | 4/0/0 | true | unknown-binary:3, mot-bank-container:1 |
| `user-data/GG4E/afs_data/root/efct.pzz` | shared effect PZZ archive | 3 | 3/0/0 | true | hsd-dat:2, tpl-texture:1 |
| `user-data/GG4E/afs_data/root/gets.pzz` | GET/item shared PZZ archive | 11 | 11/0/0 | true | hsd-dat:8, unknown-binary:3 |
| `user-data/GG4E/afs_data/root/pl0100.pzz` | Borg/player PZZ archive | 14 | 13/0/1 | true | hsd-dat:6, tpl-texture:4, borg-data-bin:1, borg-hit-bin:1, empty:1, mot-bank-container:1 |
| `user-data/GG4E/afs_data/root/pl0200.pzz` | Borg/player PZZ archive | 14 | 13/0/1 | true | hsd-dat:6, tpl-texture:4, borg-data-bin:1, borg-hit-bin:1, empty:1, mot-bank-container:1 |
| `user-data/GG4E/afs_data/root/st00.pzz` | stage PZZ archive | 4 | 3/1/0 | true | unknown-binary:3, hsd-dat:1 |
| `user-data/GG4E/afs_data/root/st01.pzz` | stage PZZ archive | 4 | 3/1/0 | true | unknown-binary:3, hsd-dat:1 |

## Representative member listing

### cmn_data.pzz

| Id | Table word | Offset | Blocks | Compression | Name / kind | Exact bytes |
|---:|---|---:|---:|---|---|---:|
| 000 | `0x40000003` | `0x000800` | 3 | pzzp | comhit.bin / unknown-binary | 21504 |
| 001 | `0x40000001` | `0x002000` | 1 | pzzp | comhit2.bin / unknown-binary | 15680 |
| 002 | `0x400000aa` | `0x002800` | 170 | pzzp | cmn_data.member002.mot-bank-container / mot-bank-container |  |
| 003 | `0x40000001` | `0x057800` | 1 | pzzp | cmn_data.member003.unknown-binary / unknown-binary |  |

### efct.pzz

| Id | Table word | Offset | Blocks | Compression | Name / kind | Exact bytes |
|---:|---|---:|---:|---|---|---:|
| 000 | `0x40000003` | `0x000800` | 3 | pzzp | efct00.tpl / tpl-texture | 32832 |
| 001 | `0x4000008f` | `0x002000` | 143 | pzzp | efct00_mdl.arc / hsd-dat | 417955 |
| 002 | `0x4000008b` | `0x049800` | 139 | pzzp | efct01_mdl.arc / hsd-dat | 408295 |

### gets.pzz

| Id | Table word | Offset | Blocks | Compression | Name / kind | Exact bytes |
|---:|---|---:|---:|---|---|---:|
| 000 | `0x4000006f` | `0x000800` | 111 | pzzp | gets00_mdl.arc / hsd-dat | 366747 |
| 001 | `0x40000055` | `0x038000` | 85 | pzzp | gets01_mdl.arc / hsd-dat | 300131 |
| 002 | `0x40000067` | `0x062800` | 103 | pzzp | gets02_mdl.arc / hsd-dat | 353299 |
| 003 | `0x4000006a` | `0x096000` | 106 | pzzp | gets03_mdl.arc / hsd-dat | 372983 |
| 004 | `0x4000006d` | `0x0cb000` | 109 | pzzp | gets04_mdl.arc / hsd-dat | 392635 |
| 005 | `0x40000071` | `0x101800` | 113 | pzzp | gets05_mdl.arc / hsd-dat | 411327 |
| 006 | `0x4000003a` | `0x13a000` | 58 | pzzp | gets06_mdl.arc / hsd-dat | 204623 |
| 007 | `0x4000001e` | `0x157000` | 30 | pzzp | gets07.hsd-dat / hsd-dat | 105415 |
| 008 | `0x4000000e` | `0x166000` | 14 | pzzp | gets08.unknown-binary / unknown-binary |  |
| 009 | `0x40000017` | `0x16d000` | 23 | pzzp | gets09.unknown-binary / unknown-binary |  |
| 010 | `0x40000005` | `0x178800` | 5 | pzzp | gets10.unknown-binary / unknown-binary |  |

### pl0100.pzz

| Id | Table word | Offset | Blocks | Compression | Name / kind | Exact bytes |
|---:|---|---:|---:|---|---|---:|
| 000 | `0x40000001` | `0x000800` | 1 | pzzp | pl0100data.bin / borg-data-bin | 432 |
| 001 | `0x00000000` | `0x001000` | 0 | zero | pl0100.slot001.empty / empty |  |
| 002 | `0x40000001` | `0x001000` | 1 | pzzp | pl0100hit.bin / borg-hit-bin | 7840 |
| 003 | `0x40000091` | `0x001800` | 145 | pzzp | pl0100mot.bin / mot-bank-container | 413344 |
| 004 | `0x40000052` | `0x04a000` | 82 | pzzp | pl0100_mdl.arc / hsd-dat | 225767 |
| 005 | `0x40000052` | `0x073000` | 82 | pzzp | pl0100b_mdl.arc / hsd-dat | 225767 |
| 006 | `0x40000045` | `0x09c000` | 69 | pzzp | pl0100g_mdl.arc / hsd-dat | 162363 |
| 007 | `0x40000044` | `0x0be800` | 68 | pzzp | pl0100s_mdl.arc / hsd-dat | 162363 |
| 008 | `0x40000044` | `0x0e0800` | 68 | pzzp | pl0100c_mdl.arc / hsd-dat | 162363 |
| 009 | `0x4000001d` | `0x102800` | 29 | pzzp | pl0100k_mdl.arc / hsd-dat | 75103 |
| 010 | `0x40000003` | `0x111000` | 3 | pzzp | pl0100.slot010.tpl-texture / tpl-texture | 14464 |
| 011 | `0x40000002` | `0x112800` | 2 | pzzp | pl0100.slot011.tpl-texture / tpl-texture | 3712 |
| 012 | `0x40000003` | `0x113800` | 3 | pzzp | pl0100.slot012.tpl-texture / tpl-texture | 14464 |
| 013 | `0x40000002` | `0x115000` | 2 | pzzp | pl0100.slot013.tpl-texture / tpl-texture | 3712 |

## Direct ARZ groups

| First words | Count | Size range | Payload kinds | Examples |
|---|---:|---:|---|---|
| `0x00400003 0xc6970003 0xbb840000 0x02b80000 0x00010000` | 89 | 156.9 KiB-174.8 KiB | hsd-dat:89 | `user-data/GG4E/afs_data/root/it0007_mdl.arz`<br>`user-data/GG4E/afs_data/root/it0009_mdl.arz`<br>`user-data/GG4E/afs_data/root/it000a_mdl.arz`<br>`user-data/GG4E/afs_data/root/it000b_mdl.arz`<br>`user-data/GG4E/afs_data/root/it0102_mdl.arz`<br>`user-data/GG4E/afs_data/root/it0104_mdl.arz`<br>`user-data/GG4E/afs_data/root/it0108_mdl.arz`<br>`user-data/GG4E/afs_data/root/it0203_mdl.arz` |
| `0x00400003 0xc6e70003 0xbbc40000 0x02bc0000 0x00010000` | 1 | 168.1 KiB-168.1 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/it0006_mdl.arz` |
| `0x00420001 0x52470001 0x519c0000 0x001e0000 0x00010000` | 1 | 26.2 KiB-26.2 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc06_mdl.arz` |
| `0x00420001 0x5cc70001 0x5c1c0000 0x001e0000 0x00010000` | 1 | 30.9 KiB-30.9 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc0a_mdl.arz` |
| `0x00420001 0x63c70001 0x631c0000 0x001e0000 0x00010000` | 1 | 26.3 KiB-26.3 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc0b_mdl.arz` |
| `0x00420001 0x8dc70001 0x8d1c0000 0x001e0000 0x00010000` | 1 | 29.6 KiB-29.6 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc08_mdl.arz` |
| `0x00420001 0x9bc70001 0x9b1c0000 0x001e0000 0x00010000` | 1 | 27.2 KiB-27.2 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc04_mdl.arz` |
| `0x00420001 0xb0070001 0xaf5c0000 0x001e0000 0x00010000` | 1 | 32.1 KiB-32.1 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc0d_mdl.arz` |
| `0x00420001 0xb7c70001 0xb71c0000 0x001e0000 0x00010000` | 1 | 29.8 KiB-29.8 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc01_mdl.arz` |
| `0x00440001 0x33a70001 0x32fc0000 0x001e0000 0x00010000` | 1 | 28.5 KiB-28.5 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc05_mdl.arz` |
| `0x00450001 0x1fc70001 0x1f1c0000 0x001e0000 0x00010000` | 1 | 23.4 KiB-23.4 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc09_mdl.arz` |
| `0x00450001 0x60a70001 0x5ffc0000 0x001e0000 0x00010000` | 1 | 28.4 KiB-28.4 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc07_mdl.arz` |
| `0x00450001 0xb7c70001 0xb71c0000 0x001e0000 0x00010000` | 1 | 27.9 KiB-27.9 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc02_mdl.arz` |
| `0x00450001 0xe8c70001 0xe81c0000 0x001e0000 0x00010000` | 1 | 32.0 KiB-32.0 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc0c_mdl.arz` |
| `0x00450002 0x51c70002 0x511c0000 0x001e0000 0x00010000` | 1 | 29.8 KiB-29.8 KiB | hsd-dat:1 | `user-data/GG4E/afs_data/root/stc03_mdl.arz` |

## Representative direct ARZ payloads

| File | Role | Compressed | Decompressed | Kind | Roots |
|---|---|---:|---:|---|---|
| `user-data/GG4E/afs_data/root/it0006_mdl.arz` | item/attachment model ARZ | 168.1 KiB | 241.7 KiB | hsd-dat | scene_data |
| `user-data/GG4E/afs_data/root/it0102_mdl.arz` | item/attachment model ARZ | 173.2 KiB | 241.6 KiB | hsd-dat | scene_data |
| `user-data/GG4E/afs_data/root/stc01_mdl.arz` | stage collision/variant model ARZ | 29.8 KiB | 109.9 KiB | hsd-dat | scene_data |
| `user-data/GG4E/afs_data/root/stc0d_mdl.arz` | stage collision/variant model ARZ | 32.1 KiB | 108.0 KiB | hsd-dat | scene_data |

## Blockers

- PZZ member semantics are only partly named: open; 132 item(s). The table and compression are decoded, but several payloads need runtime correlation or sibling file matches before naming their fields.
- Exact payload length can be padded: open; 1590 item(s). HSD and sibling-file matches recover exact byte counts for many payloads, but unknown binary members still expose the decompressed stream length only.
- Direct ARZ payloads not recognized by magic: clear; 0 item(s). Direct item/stc ARZ files should normally decompress to HSD DAT; non-HSD cases need separate format work.
- Runtime effect/item/stage meaning still needs correlation: open; 355 item(s). This scanner lists and classifies bytes. It does not claim which game event, particle emitter, or stage state consumes each payload.

## Notes for effect/item/stage work

- `efct.pzz` is now listable as three compressed members: member 000 is a TPL texture payload, and members 001/002 are effect HSD model payloads. Runtime effect usage still needs correlation.
- `gets.pzz` is listable as eleven compressed members. Several members identify as HSD DAT payloads, but the per-member item meaning remains unnamed.
- `st##.pzz` archives are listable. Their first member is raw/uncompressed in the sampled stage pattern; later compressed members decode to smaller binary payloads that need stage-runtime correlation.
- `it####_mdl.arz` and `stc##_mdl.arz` are direct compressed streams, not multi-entry archives. They now decompress in memory for header/root sniffing.

