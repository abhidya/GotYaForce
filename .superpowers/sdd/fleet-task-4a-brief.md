# Fleet Task 4A: Complete the 14-borg Girl cluster

Audit, repair, test, and classify the eight Girl-cluster constructors implemented across `girl-cluster.ts`, `cyber-girl.ts`, and their shared melee engines.

## Exact live slot matrix

- `0x800c04c0` pl0300/pl030b: actions 0,1,2; variants 0–4 for both members.
- `0x80106e3c` pl0301: actions 0,1,3; variants 0–4.
- `0x80107e7c` pl0302/pl0306: action0 both v0–4; action1 pl0302 v0–4 only; action2 both v0–4; action3 pl0302 v0–4 and pl0306 variants 7/13.
- `0x8012f204` pl0305/pl0309/pl030a: actions 0,1,2; variants 0–4 for all members.
- `0x80134078` pl0304/pl0308: action0 pl0304 v0–4 only; actions1/2 both v0–4.
- `0x8019c380` pl0303: actions 0 and 3; variants 0–4.
- `0x801ba020` pl0307/pl030d: actions 1 and 2; variants 0–4 for both.
- `0x801d429c` pl030c: action1 variants 0–4.

Do not route slots/members absent from this command-derived matrix.

## Requirements

- Verify every constructor root table, action wrapper, variant table, config block, phase table, literal, descriptor row, stream group/slot, callback, and exit against GG4E `boot.dol`, Ghidra exports, action/command tables, and player data pages.
- Audit existing `girl-cluster.ts`, `cyber-girl.ts`, `melee-girl-lunge.ts`, and `melee-girl-standing.ts`. Replace tuned values, synthetic timers, inferred callbacks, or host-only approximations with exact executable state where evidence exists.
- Reuse shared engines only when ROM addresses/table identity prove reuse. Preserve bespoke differences for Battle, Wire, Barrier, Delta II, Killer/Shadow, Cyber Girl, Spinner, and Delta families.
- Surface required actor/descriptor/bridge state; preserve generic fallback outside live commands.
- Add real-handler tests for every distinct phase/config/callback branch and bridge routing for every live member/action/variant combination, including pl0306 action3 variants 7/13 and all member exclusions.
- Add schema-v2 reviewed entries only for constructor/action slots meeting all seven proof dimensions and exact live coverage. Leave specific gaps partial with exact blockers.
- Regenerate fleet outputs and update the summary.
- Run combat build, full ROM selfcheck, default audit, expected strict failure, and task-owned diff check.

## Constraints

- ROM/decomp/data pages are authoritative; no tuned or inferred behavior can support `ported`.
- Preserve unrelated concurrent app/docs/missions/architecture changes and existing Task-3 output.
- Work in `D:/GotYaForce` on `codex/state-machine-fleet`; do not stage or commit.
- Prefix all shell commands with `rtk`; use `apply_patch` for edits.
- Report to `D:/GotYaForce/.superpowers/sdd/fleet-task-4a-report.md`.
