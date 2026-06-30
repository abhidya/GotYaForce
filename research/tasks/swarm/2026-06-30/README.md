# Gotcha Force Port Swarm - 2026-06-30

Goal: move from a one-borg browser slice to an asset- and trace-driven Adventure port.

Hard constraints for every task:
- Do not invent mechanics, enemies, weapons, stages, menus, or UI.
- Prefer repeatable scripts over manual extraction.
- Treat Dolphin as a narrow runtime probe only when static files cannot prove a field or behavior.
- Do not touch unrelated files or revert other workers' changes.
- Outputs must identify evidence: ISO path, extracted file path, DOL address, map symbol, or script result.
- Browser code may consume manifests, but this swarm is mostly extraction, mapping, and trace prep.

Tasks:
1. `task-01-borg-asset-inventory.md` - inventory all borg model/MOT/texture assets.
2. `task-02-all-borg-mot-export.md` - automate all-borg MOT export and animation manifests.
3. `task-03-weapons-effects-projectiles.md` - locate sword, fire, gun, beam, projectile, and effect assets.
4. `task-04-mechanics-runtime-trace.md` - prepare exact camera/targeting/combat trace probes.
5. `task-05-adventure-flow-ai.md` - trace Adventure mode flow and CPU player/AI path.
6. `task-06-stage-lighting-render-state.md` - extract original stage lighting, fog, camera render state, and material state.
7. `task-07-stage-geometry-collision.md` - verify walls, ceiling, skybox, collision, culling, and all stage pieces.

Integration order:
1. Inventory assets and effect families.
2. Batch-export animation clips with manifests.
3. Import verified assets into the browser scene only when model, skeleton, MOT, and effect attachments are mapped.
4. Use Dolphin watchpoints for fields that static analysis cannot identify.
5. Implement mechanics from traced fields and original asset manifests, then multiplayer sync.
6. Replace browser fallback lighting only after original stage/render-state evidence exists.
7. Replace partial stage loading only after geometry/collision inventory proves what belongs in the arena.
