# Fleet Task 3B report — DONE_WITH_CONCERNS

## Result

The action-0 host-state slice is implemented and verified. The live base morph path now commits actor mirrors/carry bytes and publishes an in-place runtime form/event seam, but the descriptor/weapon/model asset refresh is not complete because forms `0x605` and `0x614` have no extracted `pl0605`/`pl0614` movement, stat-row, model, or animation entries in the repository. Per controller direction, scope expansion stopped rather than fabricating those assets or classifying incomplete slots.

## Evidence traced

- Titan action 0: `FUN_80125de8` @ `0x80125de8`; Panther action 0: `FUN_8018c7d8` @ `0x8018c7d8`.
- Weapon/part animation: `zz_0048d54_` @ `0x80048d54`; descriptor resolver/copy `zz_004d1f4_` @ `0x8004d1f4`, `zz_004d244_` @ `0x8004d244`.
- Visibility: target refresh `zz_006bda8_` @ `0x8006bda8`; six-slot mask update `zz_006bf80_` @ `0x8006bf80`.
- Morph: `zz_006a8c0_` @ `0x8006a8c0`; descriptor virtual `zz_0056ce0_` @ `0x80056ce0`; weapon init `FUN_800562b8` @ `0x800562b8`; event post `zz_01cb750_` @ `0x801cb750`.

## Implementation and tests

- `RomActor` now surfaces exact `+0x579`, `+0x1b03`, `+0x1b20..+0x1b45`, raw per-part `+0x1bd4..+0x1c05`, `+0x3e5`, target `+0xcc/+0x83/+0x5e6`, and morph `+0x94/+0x96/+0x97` state.
- `startStream` intersects masks with the real `+0x579` surface.
- Titan/Panther action 0 runs exact success/failure ordering: animation state on active ticks, visibility rebuild only after successful ammo allocation, then member-specific projectile pairs.
- Bridge maps battle-local slots/targets into the six-entry visibility roster and flushes `+0x5e6` atomically.
- Live base morphs retain the original runtime identity/object and publish `combatFormId` plus the `zz_01cb750_` event. Prototype action 2 remains fallback.
- Focused selfchecks cover all four action-0 members, ammo success/denial, part-1 exclusion, visibility clear/re-add, base morph mirrors/events, live base routing, and prototype exclusion.

## Verification

- `rtk pnpm --filter @gf/combat build` — PASS.
- `rtk npm run selfcheck:rom` — PASS (`ALL PASS`).
- `rtk git diff --check` — PASS.

## Remaining concerns

- Repository extraction has no `pl0605`/`pl0614` rows in `movementPhysics.json`, `borgSourceStats.json`, or `borgs.json`, and no corresponding runtime model/animation exports. Therefore `zz_0056ce0_` descriptor selection, exact `FUN_800562b8` cells for those forms, and presentation model/animation hot-swap remain unproven/unimplemented.
- The normal bridge tick's decoded stream scheduler should receive a focused integration test that raises the authored `+0x1cee` completion event; current lifecycle integration invokes the already-started root phase at that exact boundary.
- Schema-v2 classifications and regenerated fleet coverage were intentionally not changed because the seven proof dimensions are not all closed. Default/strict fleet audits were not rerun after the controller requested immediate stop/finalization.

## Task-owned changed files

- `packages/combat/src/rom/actor.ts`
- `packages/combat/src/rom/stream-vm.ts`
- `packages/combat/src/families/shared-aimed-shot-x.ts`
- `packages/combat/src/families/shared-morph-x.ts`
- `packages/combat/src/bridge.ts`
- `packages/combat/src/types.ts`
- `packages/combat/src/rom/rom.selfcheck.ts`

No files were staged or committed. Concurrent app/getStorage/docs/missions changes were not incorporated into this work.
