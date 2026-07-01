# Common Battle Data Inventory

Generated: 2026-07-01T03:20:53.136Z
Scanner: `scripts/inventory-common-battle-data.mjs`

## Scope

Byte-level inventory only. This compares cmn_data.pzz member 003 against the solved 432-byte pl####data.bin actor-data record size without naming fields or binding runtime mechanics.

## Summary

- Source archive: `user-data/GG4E/afs_data/root/cmn_data.pzz`
- Member: 003 (0x40000001, 864 bytes decompressed)
- Actor data files compared: 198
- Member 003 splits into 2 x 432-byte candidate records.
- Exact actor-data matches: pl0f05 ROACH, pl0f06 DEATH EYE.

## Candidate Records

| Record | Offset | SHA1 | Non-zero bytes | First halfwords | First floats |
|---:|---:|---|---:|---|---|
| 0 | `0x0000` | `a397fd9ce9a186e3caf0daa3ee9dc22895e23794` | 245 | `0x01f4` `0x0064` `0x2710` `0x0000` `0x07d0` `0x0000` `0x0000` `0x0000` | 0 0 0 0 0 0 6 5.5 |
| 1 | `0x01b0` | `e15dedd41ca34460a54b07928e0ee40388235739` | 222 | `0x01f4` `0x0064` `0x2710` `0x0000` `0x07d0` `0x0000` `0x0000` `0x0000` | 0 0 0 0 0 0 5 2.5 |

## Actor Data Shape Comparison

### Record 0

Same-offset u16 values observed in actor data: 216

| Actor data | Borg | Same bytes | Same non-zero bytes | Same u16 offsets | Same u32 offsets | Byte ratio |
|---|---|---:|---:|---:|---:|---:|
| `user-data/GG4E/afs_data/root/pl0f05data.bin` | ROACH | 432 | 245 | 216 | 108 | 1 |
| `user-data/GG4E/afs_data/root/pl0905data.bin` | pl0905 | 423 | 236 | 208 | 102 | 0.9792 |
| `user-data/GG4E/afs_data/root/pl0805data.bin` | JELLY DIVER | 370 | 184 | 175 | 78 | 0.8565 |
| `user-data/GG4E/afs_data/root/pl080ddata.bin` | TAR DIVER | 370 | 184 | 175 | 78 | 0.8565 |
| `user-data/GG4E/afs_data/root/pl080edata.bin` | JACK | 370 | 184 | 175 | 78 | 0.8565 |
| `user-data/GG4E/afs_data/root/pl0808data.bin` | CYBER HERO | 366 | 183 | 173 | 77 | 0.8472 |
| `user-data/GG4E/afs_data/root/pl090adata.bin` | SHIELD WITCH | 364 | 183 | 167 | 70 | 0.8426 |
| `user-data/GG4E/afs_data/root/pl0903data.bin` | GUARD WITCH | 363 | 183 | 166 | 69 | 0.8403 |

### Record 1

Same-offset u16 values observed in actor data: 216

| Actor data | Borg | Same bytes | Same non-zero bytes | Same u16 offsets | Same u32 offsets | Byte ratio |
|---|---|---:|---:|---:|---:|---:|
| `user-data/GG4E/afs_data/root/pl0f06data.bin` | DEATH EYE | 432 | 222 | 216 | 108 | 1 |
| `user-data/GG4E/afs_data/root/pl0f04data.bin` | DEATH BORG CHI | 370 | 177 | 171 | 75 | 0.8565 |
| `user-data/GG4E/afs_data/root/pl0f01data.bin` | DEATH BORG NU | 368 | 175 | 171 | 75 | 0.8519 |
| `user-data/GG4E/afs_data/root/pl0c00data.bin` | NORMAL TANK | 363 | 175 | 166 | 71 | 0.8403 |
| `user-data/GG4E/afs_data/root/pl0f02data.bin` | DEATH BORG NU II | 367 | 174 | 170 | 74 | 0.8495 |
| `user-data/GG4E/afs_data/root/pl0f03data.bin` | DEATH BORG NU III | 366 | 173 | 169 | 73 | 0.8472 |
| `user-data/GG4E/afs_data/root/pl0c06data.bin` | LEOPARD | 361 | 173 | 164 | 69 | 0.8356 |
| `user-data/GG4E/afs_data/root/pl0c01data.bin` | GATLING TANK | 362 | 171 | 164 | 67 | 0.838 |

## Assessment

cmn_data.pzz member 003 cleanly splits into 432-byte records, the same stride as pl####data.bin actor data. The same-offset comparisons make it a strong common actor/battle-parameter candidate, but field names still require DOL/runtime trace or HexWorkshop bookmark correlation.

## Verification

```bash
rtk node scripts/inventory-common-battle-data.mjs
```
