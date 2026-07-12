# Fleet Task 3B: Finish Titan/Panther action-0 host state and morph lifecycle

Close the remaining proof blockers for Fleet Task 3 after the action-1/action-3 exact-field pass.

## Scope

- Titan constructor `0x80125a28`: pl0604/pl0618.
- Panther constructor `0x8018c2b0`: pl0613/pl0627.
- Action 0 live variants 0–4 for all four members.
- Action 2 morph live only for pl0604 variant 0 and pl0613 variant 0; prototypes must remain on fallback.
- Preserve the current Task-3 action1/action3 implementation and tests.

## Action 0 requirements

- Trace and implement `zz_0048d54_` weapon/part animation state, including the exact actor bytes/arrays at `+0x579`, `+0x1b03`, `+0x1b20..+0x1b45`, and `+0x1bd4..+0x1c05` that the Titan/Panther handlers exercise.
- Trace and implement `zz_006bf80_` visibility/eligibility behavior, including actor `+0x3e5` and target fields `+0xcc`, `+0x83`, and `+0x5e6` where relevant.
- Surface state through `RomActor`, bridge/runtime, and presentation only to the extent proven necessary by the call graph. Do not create renderer behavior from resemblance.
- Add focused handler and bridge tests covering success/failure branches for all distinct live member/variant paths.

## Action 2 morph requirements

- Implement the exact live morph lifecycle instead of actor-only ID mutation: actor mirror `+0x94`; carried `+0x3e4/+0x3e7 -> +0x96/+0x97`; descriptor/model reinitialization `zz_0056ce0_`; weapon/ammo reinitialization `FUN_800562b8`; and event post `zz_01cb750_`.
- Connect the lifecycle to the battle-owned runtime/presentation so a live pl0604 morph displays/uses form `0x605` and pl0613 uses form `0x614`, with descriptor, weapon cells, model/animation selection, and relevant host state updated atomically.
- Preserve identity/progression semantics that must remain attached to the original combatant. Do not replace the runtime object if that would lose HP/team/result ownership.
- Prototype pl0618/pl0627 action-2 commands remain unhandled by the ROM port.
- Add integration selfchecks for both base morphs, descriptor/model/weapon refresh, event emission, and prototype exclusion.

## Completion and verification

- Re-audit actions 0–3 for both constructors. Add schema-v2 reviewed entries only for slots meeting all seven proof dimensions and exact live-member/variant coverage.
- Regenerate fleet coverage outputs.
- Run combat build, full ROM selfcheck, any focused presentation/runtime checks, default fleet audit, expected strict failure, and diff check.
- Record exact evidence addresses, implementation, tests, changed files, and remaining concerns in `D:/GotYaForce/.superpowers/sdd/fleet-task-3b-report.md`.

## Constraints

- GG4E ROM/Ghidra/data pages are authoritative; no tuned values or inferred visuals.
- Preserve generic fallback outside exact live commands.
- Preserve concurrent unrelated non-combat edits. Do not stage or commit.
- Prefix shell commands with `rtk`; use `apply_patch` for edits.
