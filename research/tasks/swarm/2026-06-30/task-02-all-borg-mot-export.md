# Task 02 - All-Borg MOT Export Automation

Purpose: turn the single-borg MOT exporter into a repeatable path for all borgs without manually extracting clips.

Own these outputs only:
- `scripts/export-all-borg-animations.mjs`
- `research/asset-inventory/borg-animation-export-plan.json`
- `research/asset-inventory/borg-animation-export-plan.md`

Read-only inputs:
- `scripts/export-borg-animation-hsd.mjs`
- `user-data/GG4E/afs_data/root/`
- `apps/game/public/models/`
- `research/format-specs/mot-animation-format.md`

Requirements:
- Do not rewrite `scripts/export-borg-animation-hsd.mjs`; call it or share its public command contract.
- Discover borg ids with model plus MOT blobs.
- Build a batch plan that maps each borg to export commands and destination paths.
- For at least one additional borg beyond `pl0615`, run a small proof export if the skeleton/model exists and the script can do it safely.
- Output must distinguish confirmed exported clips from planned clips.
- Do not mark an animation semantic label as confirmed unless evidence supports it. Use candidate labels when needed.

Verification:
- Run `node --check` on the new script.
- Run the new script in a dry-run/plan mode.
- If a proof export is safe, run it and verify JSON frame counts parse.
