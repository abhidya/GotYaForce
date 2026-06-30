# Task 04 - Mechanics Runtime Trace

Purpose: produce the smallest Dolphin/static trace kit needed to import original camera, lock-on, targeting, jump/fly/shoot/melee/death mechanics.

Own these outputs only:
- `research/traces/GG4E/mechanics-runtime-trace-plan.md`
- `research/traces/GG4E/breakpoints-watchpoints.json`

Inputs to inspect:
- `dolphin/Dolphin.exe`
- `Gotcha Force.iso`
- `user-data/GG4E/disc/sys/boot.dol`
- `research/symbols/GG4E-CSM-20220412.map`
- `research/traces/GG4E-dol-trace-playbook.md`
- `packages/combat/`

Requirements:
- Produce breakpoint/watchpoint JSON grouped by camera, lock-on/targeting, jump/fly, shoot, melee, damage, death, next-borg spawn, CPU AI.
- Include exact address, DOL offset when known, register/memory fields to capture, and event to trigger.
- Include launch command and symbol map setup.
- Keep Dolphin usage targeted: one event window per save state.
- Explicitly mark what cannot be implemented without runtime capture.

Verification:
- Validate JSON parses.
- Do not run Dolphin unless necessary for file/path discovery.
