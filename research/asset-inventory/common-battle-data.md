# Common Battle Data Inventory

Generated: 2026-07-04T20:20:51.212Z
Scanner: `scripts/inventory-common-battle-data.mjs`

## Scope

Byte-level inventory for common battle data and actor-data records. Actor-data fields are named only where they match every metadata-backed pl####data.bin record exactly, or where the verifiable metadata domain proves the byte semantics.

## Summary

- Source archive: `user-data/GG4E/afs_data/root/cmn_data.pzz`
- Member: 003 (0x40000001, 864 bytes decompressed)
- Actor data files compared: 198
- Member 003 splits into 2 x 432-byte candidate records.
- Exact actor-data matches: pl0f05 ROACH, pl0f06 DEATH EYE.
- Actor-data stat offsets exact: yes (190 metadata rows).
- Actor-data air-jump offset exact: yes on 175 verifiable Air jump/Boost jump rows; 15 N/A rows carry sentinel/no-count values.
- Runtime binds actor-data combat stats and discrete air-jump count: yes.

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

## Actor Data Runtime Offsets

typeCode/defense/shot/attack/speed are exact unsigned-byte matches for every actor-data file that has borgs.json metadata. airJump is exact on the verifiable jump domains: `Air jump level N` -> N and `Boost jump` -> 0; most `N/A` flyers carry sentinel/no-count byte 0xff.

| Field | Offset | Exact matches |
|---|---:|---:|
| typeCode | `0x01a0` | 190/190 |
| airJump | `0x01a3` | 175/175 verifiable + 15 N/A sentinel rows |
| defense | `0x01a4` | 190/190 |
| shot | `0x01a5` | 190/190 |
| attack | `0x01a6` | 190/190 |
| speed | `0x01a7` | 190/190 |

## Assessment

cmn_data.pzz member 003 cleanly splits into 432-byte records, the same stride as pl####data.bin actor data. typeCode/airJump/defense/shot/attack/speed are now mapped actor-data bytes and runtime-bound; the remaining common-record fields still require DOL/runtime trace or HexWorkshop bookmark correlation.

## Runtime Binding

- App imports borgs.json: yes (apps/game/src/sim/borgCatalog.ts:1)
- Generated actor-data stats JSON exists: yes (packages/combat/src/data/actorDataStats.json)
- Actor-data stats accessor exists: yes (packages/combat/src/actorDataStats.ts:37)
- Combat buildProfile consumes actor-data stats: yes (packages/combat/src/stats.ts:149)
- Combat buildProfile consumes stat fields and discrete air-jump count: yes (packages/combat/src/stats.ts:149)
- Combat constants still declare tuned formulas: yes (packages/combat/src/constants.ts:52)
- Generic PZZ parser package implemented: yes (packages/formats/src/pzz.ts:103)

Runtime combat profiles now bind typeCode/airJump/defense/shot/attack/speed to original pl####data.bin actor-data bytes via packages/combat/src/data/actorDataStats.json. Energy, HP, flyer classification, and the absolute damage coefficients still use the existing roster/tuned formula path until their binary fields or formula consumers are proven.

## Verification

```bash
rtk node scripts/inventory-common-battle-data.mjs
```
