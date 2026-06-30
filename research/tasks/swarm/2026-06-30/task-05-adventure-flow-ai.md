# Task 05 - Adventure Flow And CPU AI

Purpose: trace the original Adventure path and CPU player/AI path so the port follows the game flow instead of fake menus or fake enemies.

Own these outputs only:
- `scripts/inventory-adventure-flow.mjs`
- `research/asset-inventory/adventure-flow-ai.json`
- `research/asset-inventory/adventure-flow-ai.md`

Inputs to inspect:
- `packages/assets/data/stages.json`
- `packages/assets/data/borgs.json`
- `packages/missions/`
- `user-data/GG4E/afs_data/root/`
- `user-data/GG4E/disc/`
- `research/symbols/GG4E-CSM-20220412.map`
- `research/traces/GG4E-dol-trace-playbook.md`

Required flow to map:
- main menu -> Adventure select/load -> force/player setup -> mission intro/load -> battle HUD/gameplay.

Requirements:
- Script must inventory data files and extracted assets that correspond to Adventure stage, enemy force, intro/load, HUD, and CPU-controlled actors.
- Report current repo implementation gaps for that flow, with file references.
- Identify likely DOL symbols/functions for team/player lookup and CPU AI control.
- Do not propose story mode work. Adventure only.
- Do not add fake UI. This is mapping and script output only.

Verification:
- Run the inventory script.
- Confirm JSON parses and markdown report cites real files.
