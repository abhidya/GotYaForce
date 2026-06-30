# Task 06 - Stage Lighting And Render State

Purpose: replace hand-tuned browser lighting with original Gotcha Force stage/render evidence.

Own these outputs only:
- `scripts/inventory-stage-lighting.mjs`
- `research/asset-inventory/stage-lighting-render-state.json`
- `research/asset-inventory/stage-lighting-render-state.md`

Inputs to inspect:
- `user-data/GG4E/afs_data/root/`
- `user-data/GG4E/disc/`
- `apps/game/public/stages/`
- `research/format-specs/`
- `research/symbols/GG4E-CSM-20220412.map`
- `user-data/GG4E/disc/sys/boot.dol`

Requirements:
- Find original stage lighting/fog/material/camera render-state candidates, especially HSD light/object data such as LObj, CObj, FObj/AObj, material color, ambient, diffuse, specular, alpha, fog, and draw-state flags.
- Inventory evidence for `st00` first, then report whether other stages follow the same pattern.
- Record exact source paths, archive names, object names when available, byte offsets if discovered, and confidence.
- Identify what the browser currently fakes in `apps/game/src/main.ts` and what should replace it.
- Do not tune colors by eye. Do not edit browser source.
- If Dolphin is necessary, propose the smallest runtime probe only; do not run broad logs.

Verification:
- Run the inventory script.
- Confirm JSON parses.
- Markdown report must cite real files/offsets/symbols and list unresolved questions.
