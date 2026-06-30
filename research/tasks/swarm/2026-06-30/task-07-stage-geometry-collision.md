# Task 07 - Stage Geometry, Walls, Ceiling, Collision

Purpose: verify the browser is not missing original stage shell pieces such as walls, ceiling, skybox/backdrop, collision, invisible bounds, culling flags, or draw groups.

Own these outputs only:
- `scripts/inventory-stage-geometry.mjs`
- `research/asset-inventory/stage-geometry-collision.json`
- `research/asset-inventory/stage-geometry-collision.md`

Inputs to inspect:
- `user-data/GG4E/afs_data/root/`
- `user-data/GG4E/disc/`
- `apps/game/public/stages/`
- `research/format-specs/`
- `research/symbols/GG4E-CSM-20220412.map`

Requirements:
- Inventory every exported `st00` model piece and compare it to source archive contents.
- Identify likely walls, ceiling, floor, background/skybox, props, invisible collision, spawn/arena bounds, and culling groups.
- Report bounding boxes, material/texture names, triangle counts if available, and whether the browser currently loads each piece.
- Check whether the current `DEFAULT_STAGE_MODEL_COUNT = 40` is complete or just a partial assumption.
- Identify any stage collision files or archive members that are not visual DAE exports.
- Do not edit browser source. Do not create fake walls/ceiling.

Verification:
- Run the inventory script.
- Confirm JSON parses.
- Markdown must cite real stage source/export paths and list missing or uncertain pieces.
