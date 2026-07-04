# Static Borg Animation Indexes

Generated: 2026-07-04T03:33:55.315Z

These indexes are generated only for Borgs whose original PZZ motion-bank member is present but empty (`payloadBytes: 0`, `blockCount: 0`). The emitted clip is a one-frame no-op so runtime animation references resolve without inventing motion that is absent from the source archive.

## Summary

| Metric | Count |
|---|---:|
| Static roster indexes emitted | 23 |
| Non-roster source-empty motion banks skipped | 1 |
| Existing non-static indexes protected | 0 |

## Emitted

| Borg | Source member | Output |
|---|---|---|
| `pl0505` | `pl0505mot.bin` | `apps/game/public/models/pl0505/anim_index.json` |
| `pl0511` | `pl0511mot.bin` | `apps/game/public/models/pl0511/anim_index.json` |
| `pl0d00` | `pl0d00mot.bin` | `apps/game/public/models/pl0d00/anim_index.json` |
| `pl0d01` | `pl0d01mot.bin` | `apps/game/public/models/pl0d01/anim_index.json` |
| `pl0d02` | `pl0d02mot.bin` | `apps/game/public/models/pl0d02/anim_index.json` |
| `pl0d03` | `pl0d03mot.bin` | `apps/game/public/models/pl0d03/anim_index.json` |
| `pl0d04` | `pl0d04mot.bin` | `apps/game/public/models/pl0d04/anim_index.json` |
| `pl0d05` | `pl0d05mot.bin` | `apps/game/public/models/pl0d05/anim_index.json` |
| `pl0d06` | `pl0d06mot.bin` | `apps/game/public/models/pl0d06/anim_index.json` |
| `pl0d07` | `pl0d07mot.bin` | `apps/game/public/models/pl0d07/anim_index.json` |
| `pl0e00` | `pl0e00mot.bin` | `apps/game/public/models/pl0e00/anim_index.json` |
| `pl0e01` | `pl0e01mot.bin` | `apps/game/public/models/pl0e01/anim_index.json` |
| `pl0e02` | `pl0e02mot.bin` | `apps/game/public/models/pl0e02/anim_index.json` |
| `pl0e03` | `pl0e03mot.bin` | `apps/game/public/models/pl0e03/anim_index.json` |
| `pl0e04` | `pl0e04mot.bin` | `apps/game/public/models/pl0e04/anim_index.json` |
| `pl0e05` | `pl0e05mot.bin` | `apps/game/public/models/pl0e05/anim_index.json` |
| `pl0f00` | `pl0f00mot.bin` | `apps/game/public/models/pl0f00/anim_index.json` |
| `pl0f01` | `pl0f01mot.bin` | `apps/game/public/models/pl0f01/anim_index.json` |
| `pl0f02` | `pl0f02mot.bin` | `apps/game/public/models/pl0f02/anim_index.json` |
| `pl0f03` | `pl0f03mot.bin` | `apps/game/public/models/pl0f03/anim_index.json` |
| `pl0f04` | `pl0f04mot.bin` | `apps/game/public/models/pl0f04/anim_index.json` |
| `pl0f05` | `pl0f05mot.bin` | `apps/game/public/models/pl0f05/anim_index.json` |
| `pl0f06` | `pl0f06mot.bin` | `apps/game/public/models/pl0f06/anim_index.json` |

## Skipped Non-Roster

- `pl0f07` (pl0f07mot.bin)

## Reproduce

```bash
rtk node scripts/generate-static-borg-anims.mjs --force
rtk node scripts/validate-borg-animation-actions.mjs --strict
```
