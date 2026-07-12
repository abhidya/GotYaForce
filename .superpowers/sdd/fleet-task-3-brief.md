# Fleet Task 3: Complete Titan/Panther aimed-shot and morph families

Complete the two constructor families that use `shared-aimed-shot-x.ts`, preserving the exact root-dispatch seam with `shared-morph-x.ts`.

## Families and live slots

- Titan constructor `0x80125a28`: `pl0604` TITAN ROBOT and `pl0618` PROTO TITAN.
- Panther constructor `0x8018c2b0`: `pl0613` PANTHER ROBOT and `pl0627` PROTO PANTHER.
- Action 0: live variants 0–4 for both members of each constructor.
- Action 1: live variants 0–4 for both members of each constructor.
- Action 2: shared morph engine is live only for `pl0604` variant 0 and `pl0613` variant 0 according to extracted command data. Do not capture prototype commands that are not live.
- Action 3: shared aimed-shot engine is live variants 0–4 for both members of each constructor.
- Root-table action 4/5 entries are not live command slots in the current audit. Record evidence if they are dead/inactive, but do not invent routing.

## Requirements

- Verify root, variant, phase, config, callback, constant, command, and descriptor data directly against GG4E `boot.dol`, Ghidra exports, and extracted JSON before modifying behavior.
- Port actions 0 and 1 completely for both constructors and every live member/variant. Reuse a shared engine only when the ROM function/table address proves identity.
- Audit and correct action 2 morph composition. The bridge must route it only for the live base-member commands while preserving fallback for prototype members.
- Audit and correct action 3 aimed-shot behavior. Replace the current documented approximations: use the live weapon/ammo gate, surface required part ownership/flag bytes, and model exact callback success/failure behavior.
- Preserve exact Titan/Panther differences: config addresses, stream slots, setup callback, pitch-halving condition, projectile/spawn records, backdash/motion-zeroing, and control-word behavior.
- Add real-handler selfchecks for every distinct phase/variant/callback branch, bridge routing for all four members, prototype morph exclusion, ammo denial/success, and state synchronization.
- Add schema-v2 reviewed classifications only when every live member/variant and all seven proof dimensions are satisfied. Partial work remains `partial`.
- Regenerate coverage artifacts and update the concise coverage summary.
- Run `pnpm --filter @gf/combat build`, `pnpm selfcheck:rom`, default fleet audit, expected strict audit failure, and `git diff --check`.
- Do not fix or include the unrelated baseline TypeScript error in `apps/game/src/sim/getStorage.ts`; Task 3 is combat-scoped.

## Global constraints

- GG4E ROM/decomp evidence is authoritative; no guessed constants or behavioral resemblance.
- Preserve generic fallback outside proven live slots.
- A ported slot requires root dispatch, exact member/variant coverage, phases, constants, streams, bridge wiring, and focused tests.
- Preserve unrelated files and the clean `ce20f299` baseline.

## Workspace/report

- Work in `D:/GotYaForce` on `codex/state-machine-fleet`.
- Do not stage or commit; the controller will create a scoped commit after review.
- Prefix every shell command with `rtk`; use `apply_patch` for edits.
- Write the report to `D:/GotYaForce/.superpowers/sdd/fleet-task-3-report.md`.
