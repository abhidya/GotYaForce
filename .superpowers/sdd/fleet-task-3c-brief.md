# Fleet Task 3C: Extract alternate forms and close morph lifecycle

Extract the missing Titan/Panther alternate-form data (`0x605`/`0x614`) and finish Task 3's exact morph lifecycle.

## Requirements

- Locate authoritative GG4E sources for forms `0x605` and `0x614` in `user-data/GG4E`, `boot.dol`, player data archives, model archives, and descriptor tables. Do not assume roster absence means data absence.
- Extract the movement descriptor values used by `zz_0056ce0_`, exact weapon/ammo cells initialized by `FUN_800562b8`, model identity/assets, and animation banks for both forms using existing repository extractors where possible.
- Store generated source data in the same authoritative schemas/manifests used by normal borgs, clearly marking these as internal morph forms rather than selectable roster entries.
- Finish the live in-place morph path for pl0604→0x605 and pl0613→0x614: update `combatFormId`, descriptor/movement fields, weapon cells, model/animation presentation, actor mirrors/carry bytes, and `zz_01cb750_` event atomically while preserving runtime UID, original borg identity, HP, team, progression, and results ownership.
- Add a same-UID BattleScene/presentation reload when `combatFormId` changes, with focused tests proving old model/clip disposal and new form selection.
- Drive a normal bridge tick through the authored `+0x1cee` stream completion event; do not rely only on direct root-handler invocation.
- Preserve prototype pl0618/pl0627 action-2 fallback.
- Re-audit Titan/Panther actions 0–3. Add schema-v2 classifications only for fully proven slots; regenerate fleet outputs.
- Run the extraction validation, combat build, game/root typecheck if applicable, full ROM selfcheck, focused presentation test, default fleet audit, expected strict failure, and diff check.

## Constraints

- ROM/disc data is authoritative. Do not synthesize model, animation, stats, or ammo values.
- Reuse existing extraction scripts and formats; avoid bespoke binary parsers unless existing tooling cannot address the source.
- Preserve concurrent non-task changes. Do not stage or commit.
- Prefix shell commands with `rtk`; use `apply_patch` for edits.
- Report to `D:/GotYaForce/.superpowers/sdd/fleet-task-3c-report.md`.
