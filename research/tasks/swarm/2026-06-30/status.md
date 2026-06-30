# Swarm Status

Started: 2026-06-30

| Task | Agent | Ownership | Status |
| --- | --- | --- | --- |
| 01 Borg asset inventory | Russell `019f176d-cef9-7b20-a6fa-0121c6c10132` | `scripts/inventory-borg-assets.mjs`, `research/asset-inventory/borg-assets.*` | complete: 219 records, 58 static-safe, 1 animation-safe |
| 02 All-borg MOT export | Anscombe `019f176e-06e4-7b50-8cb7-99413abfe018` | `scripts/export-all-borg-animations.mjs`, `research/asset-inventory/borg-animation-export-plan.*` | complete: 102 borgs, 4,321 clips, pl0109 proof |
| 03 Weapons/effects/projectiles | Kant `019f176e-3e0c-7b42-a296-ab50abbc0ce8` | `scripts/inventory-effect-assets.mjs`, `research/asset-inventory/weapons-effects-projectiles.*` | complete: 1,485 candidates, 443 textures |
| 04 Mechanics runtime trace | Kuhn `019f176e-7034-7a22-9216-a8fbc2ba25af` | `research/traces/GG4E/mechanics-runtime-trace-plan.md`, `research/traces/GG4E/breakpoints-watchpoints.json` | complete: 38 breakpoints validated |
| 05 Adventure flow and CPU AI | Mill `019f176e-a05c-7a33-812d-51ef8867b37c` | `scripts/inventory-adventure-flow.mjs`, `research/asset-inventory/adventure-flow-ai.*` | complete: 70 Adventure rows, 130 enemy actors |
| 06 Stage lighting/render state | Turing `019f1774-ab08-70f0-b763-953e87cbef8d` | `scripts/inventory-stage-lighting.mjs`, `research/asset-inventory/stage-lighting-render-state.*` | complete: st00 camera, light, fog decoded |
| 07 Stage geometry/collision | Raman `019f1776-2f85-7771-a9dc-ba0a2ef07e69` | `scripts/inventory-stage-geometry.mjs`, `research/asset-inventory/stage-geometry-collision.*` | complete: st00 visual slots complete, collision/set undecoded |
| 08 All-stage export coverage | Darwin `019f177a-946c-75d2-851b-83c71ccd57f7` | `scripts/export-all-stages.mjs`, `research/asset-inventory/stage-export-plan.*` | complete: 40 stage pairs, st02 proof partial |
| 09 MOT exporter generalization | Socrates `019f177a-d4a0-7b21-803c-2cc73c542b81` | `scripts/export-borg-animation-hsd.mjs`, `research/asset-inventory/mot-exporter-generalization.md` | complete: explicit non-0x240 clip export works |
| 10 Hit/collision decode | Archimedes `019f177d-d5cd-7990-b5d9-b5f26cddf198` | `scripts/inspect-hit-bins.mjs`, `research/format-specs/hit-bin-format.md`, `research/asset-inventory/hit-bin-inventory.json` | complete: STIH grids and 0xF4 actor hit records |
| 11 Particle/effect decode | Erdos `019f177e-1186-7430-80e9-78045d43f647` | `scripts/inspect-particle-effects.mjs`, `research/format-specs/particle-effect-format.md`, `research/asset-inventory/particle-effect-inventory.json` | complete: fire/beam/gun/sword/effect inventory |
| 12 PZZ/ARZ archive inspection | Ramanujan `019f1788-4299-7d31-96aa-78bce8ad2928` | `scripts/inspect-pzz-arz.mjs`, `research/format-specs/pzz-arz-format.md`, `research/asset-inventory/pzz-arz-inventory.json` | running |
| 13 UI/HUD asset inventory | Pasteur `019f1788-94c7-7190-9fb2-3fb59f2badea` | `scripts/inventory-ui-hud-assets.mjs`, `research/asset-inventory/ui-hud-assets.*` | complete: 558 candidates, 441 TPLs, 102 HSD archives |
| 14 Weapon attachment map | Leibniz `019f1788-d87c-73c3-8006-d073fcb59e7d` | `scripts/map-weapon-attachments.mjs`, `research/asset-inventory/weapon-attachment-map.*` | running |
| 15 Stage render-state export | Beauvoir `019f1789-1ca6-79a3-b570-95c2b35c4314` | `scripts/export-stage-render-state.mjs`, `apps/game/public/stages/st00/render-state.json` | running |

Main-thread notes:
- Current browser playable slice is not enough: sword, fire, gun, beam, targeting, and CPU AI are still unported.
- Current browser lighting is a visibility fallback, not verified original stage lighting.
- Current `st00` visual load may be missing walls/ceiling/collision/render groups until Task 07 proves completeness.
- `st00` DAE visual slots are complete; collision/set/PZZ still need importer work.
- `st01` and `st02` proof exports are partial due texture file lock failures, so do not route Adventure to them as complete arenas yet.
- Next integration gate is asset manifests, not fake effects.
- Deploy waits until multiplayer build works and live playtest passes.
