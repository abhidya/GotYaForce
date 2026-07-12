# Fleet Task 4A report: 14-borg Girl cluster

## Status

DONE_WITH_CONCERNS. All 14 members now obey the exact command-derived live matrix, the shared ranged/melee/Cyber/series-3 executable state has been repaired, and exhaustive direct-handler plus bridge routing tests pass. No schema-v2 slot was promoted in this slice because the remaining presentation/aim residuals below prevent an honest seven-dimension `ported` claim.

## Implemented

- Enforced all 182 live member/action/variant combinations and excluded every other action 0..4 / variant 0..13 combination. This includes `pl0306` action 3 variants 7/13 only, no `pl0306` melee, no `pl0308` ranged action, and no accidental Delta-II/Spinner rows.
- Removed the shared ranged engine's tuned 20-frame fire and 120-frame exit budgets. Fire and exit now consume only the ROM event/input fields `+0x1cef`, `+0x1b03`, `+0x5d4`, `+0x5d8`, `+0x5b4`, and `+0x1cee`.
- Replaced tuned 1000 descriptor-row and dash-byte-16 fallbacks with production `actionSpeedRows[0/1]` (`+0x868/+0x86c`) and surfaced signed `+0x1d0f` state. Replaced the instant ranged yaw approximation with the recovered `zz_006dee8_` helper.
- Surfaced actor/bridge state for `+0x144`, `+0x5e8`, `+0x1cf0`, `+0x1d0f`, `+0x1d10`, `+0x1b03`, `+0x6eb`, `+0x5b4`, `+0x5d4`, and `+0x5d8`. The bridge now preserves the target cache and stamps the exact input/status names consumed by Girl handlers.
- Read Cyber Girl's float bank directly from GG4E `boot.dol`: `0x80439e40..50` words `00000000/bf800000/3f733333/41400000/41000000`, correcting cooldowns from inferred 4/4 to exact 12/8. Corrected both reposition-vector equations, stream cursor/counter behavior, first-set `+0x144` beam row selection, repeat gate, and gravity event restore.
- Repaired shared series-3 X: removed both synthetic 60-frame budgets; phase 1 advances only on `+0x1cef > 0`; phase 2 exits only on `+0x1cee`; meter/landing consume `+0x1cef < 0`; gravity restore consumes `+0x1d0f < 0`; Delta-II consume and Spinner follow-up peek use the exact weapon hook modes 1/0 without permissive fallback.
- Added ROM selfchecks for all 182 live slots, all exclusions, the same exhaustive bridge matrix, both shared-X config branches, Cyber literals, Delta-II ammo denial/common exit, series-3 event gates, and absence of synthetic whiff/recovery exits.

## Remaining exact blockers

- Shared and bespoke Girl handlers still omit renderer-only `zz_00b22f4_` afterimage emissions and several `+0x80/+0x7e/+0x7c/+0x80c` animation housekeeping writes. These prevent complete stream/presentation proof for the affected action 0/1/2 slots.
- `zz_006e514_` melee pitch convergence is represented by the exact target pitch but not its complete descriptor-rate accumulator behavior; melee action 1 therefore remains partial.
- Cyber/Battle/Barrier/Killer and series-3 X retain family-specific face/air-steering and ground-snap/revert helper effects that are host-owned or not fully surfaced in the isolated actor. Their core phase/config/callback logic is executable, but those slots remain partial under the seven-dimension rule.
- Constructor/action/variant tables, config blocks, phase tables, constants, callbacks, live exclusions, and weapon gates have no known data-page blocker. The remaining blockers are helper/presentation state, not absent ROM or player data pages.

## Verification

- `pnpm --filter @gf/combat build` — PASS.
- `pnpm selfcheck:rom` — PASS, including exhaustive Girl live-routing/exclusion tests.
- `pnpm audit:family-state-machines` — PASS: 119 constructors, 325 slots; ported 13, partial 241, missing 71, structural errors 0. Coverage JSON/Markdown regenerated.
- `pnpm audit:family-state-machines -- --strict` — expected FAIL because repository-wide partial/missing slots remain.
- `git diff --check` — PASS.

## Scope

Task-owned edits are limited to `packages/combat/src/bridge.ts`, the five Girl/shared engine files, `packages/combat/src/rom/actor.ts`, `packages/combat/src/rom/rom.selfcheck.ts`, regenerated family coverage outputs when content changed, and this report. Existing unrelated `.superpowers/sdd/task-2-report.md` and `packages/combat/src/battleJudge.selftest.ts` changes were preserved untouched. Nothing was staged or committed.

## Final review addendum

The final certified Girl keys are the six complete action-0 entries plus Cyber Girl action 2.
Seven action-1 entries were demoted because their `zz_006e514_` pitch path shares the
unresolved renderer part-row anchor. Final counts are ported 20, partial 234, missing 71.
The afterimage path now uses exact subtype-1 efct-bank id 69 and its authored 20-frame
scale/alpha lifecycle; no inferred actor-model ghost remains.
