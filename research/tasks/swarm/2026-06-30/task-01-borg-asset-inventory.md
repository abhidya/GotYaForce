# Task 01 - Borg Asset Inventory

Purpose: create a complete, script-generated inventory of playable/enemy borg assets from the extracted disc.

Own these outputs only:
- `scripts/inventory-borg-assets.mjs`
- `research/asset-inventory/borg-assets.json`
- `research/asset-inventory/borg-assets.md`

Inputs to inspect:
- `user-data/GG4E/afs_data/root/`
- `apps/game/public/models/`
- `packages/assets/data/borgs.json`
- `research/format-specs/`

Requirements:
- Script must scan for borg model, texture, and MOT candidates, especially `pl####*`, `pl####mot.bin`, `.arc`, `.dae`, `.png`.
- Output one record per borg id with name, energy if known, source files, exported browser model status, MOT status, texture status, and missing pieces.
- Identify which borgs are safe to render now and which would T-pose because MOT mapping is missing.
- Include counts and top missing categories in the markdown report.
- Do not hand-list files. The markdown must be generated from JSON or clearly cite the script output.

Verification:
- Run the script.
- Confirm JSON parses.
- Report command output summary and changed paths.
