# Fleet Task 2 report — shared Robot action 0 / action 1

## Status

Implemented and verified the shared Robot action-0 machine for all 13 live members and all ROM-live variants, and corrected the shared action-1 variant-0 melee machine/routing for pl0400 through pl040b. pl0406 remains deliberately unwrapped for action 0. Bespoke action-2 files were not changed.

Seven constructor/action-0 slots were promoted to `ported` under fleet audit schema v2. Action-1 constructor slots were deliberately not promoted: their ROM-live slot coverage also contains distinct variants 1–4, which are outside this shared variant-0 machine and do not yet meet all seven evidence dimensions.

## Evidence verified

- `boot.dol` phase table `0x8031b8a0`: `0x800f1eb8`, `0x800f1f9c`, `0x800f2008`, `0x800f2118`, `0x800f22a8`.
- `boot.dol` phase table `0x8031b8b4`: `0x800f23c4`, `0x800f2498`, `0x800f259c`.
- Shared floats read directly from `user-data/GG4E/disc/sys/boot.dol`:
  - `0x80439078=30`, `0x8043907c=-1`, `0x80439088=0`, `0x8043908c≈0.96`.
  - `0x80439090=60`, `0x80439094=20`, `0x80439098=2`, `0x8043909c=150`, `0x804390a0≈0.9`, `0x804390a4=3`.
- All eleven distinct action-0 config blocks were decoded as `>hhIIhhI` and matched the implementation:
  `0x802d4ea8`, `0x802f57f4`, `0x80310978`, `0x80311c54`, `0x80311c68`, `0x80316ae0`, `0x80327f48`, `0x80327f5c`, `0x8038bdfc`, `0x8038be10`, `0x8038be24`.
- Ghidra exports checked for shared phases and callback bodies, including `FUN_80066838`, `zz_00b2190_`, and `zz_00b22f4_`.
- `actionStreamTables.json` checked for constructor/root/action/leaf/config/variant membership. Action 0 routes v0–v4 to the shared engine for all 13 live members; action 1 routes only v0 to `0x800f2374` for pl0400–pl040b.

## Evidenced corrections

- Action 0 aim recovery now uses ROM `0.96`, not `0.9`.
- Timed config+4 callbacks mutate timer/count before the consuming ammo call, including denial behavior.
- Action 1 now uses the exact 20-frame active/combo timer, coefficient 2, distance gate 150, recovery decay 0.9, and speed-tail threshold 3.
- Action 1 distinguishes target scalar `+0x760` from targetless `+0x868[prevAction%3]`, clears horizontal deceleration at transitions/combo, counts down phase 2, clears `+0x1d9b` inside the proximity gate, and surfaces `zz_00b22f4_` above the speed threshold.
- Initial `FUN_80066838` range behavior is represented; bridge sync now maintains `+0x760` and clears stale lock-target state.
- Ground recovery uses the verified `zz_006a474_` equivalent without an extra full-body cue.
- Shared Robot melee is injected only for action-1 variant 0; variants 1–4 retain their existing bespoke/generic route.

## Focused coverage

- Real action-0 handlers exercise every live member callback family, both ammo branches, timed denial ordering, config+8 continuation, config+0x10 child exit gate, all five phases, stream slot families, and phase-4 exit/decay.
- Bridge assertions exercise action-0 v0–v4 for every live member and prove pl0406 is not wrapped.
- Bridge assertions exercise action-1 v0 for pl0400–pl040b and prove v1 is not incorrectly captured.
- Real melee handlers exercise target/no-target speed, transition and combo timers, deceleration clear, recovery countdown/decay, proximity clear, launch FX, and distance-tail helper.

## Verification

- `pnpm --filter @gf/combat build`: pass.
- `pnpm selfcheck:rom`: pass.
- `pnpm audit:family-state-machines`: pass; `ported=7`, `partial=247`, `missing=71`.
- Strict audit: expected failure because partial/missing fleet gaps remain; no structural error was reported.

## Files touched for Task 2

- `packages/combat/src/families/shared-robot-dash.ts`
- `packages/combat/src/families/melee-robot.ts`
- `packages/combat/src/bridge.ts` (localized Robot routing/target-distance sync; concurrent architecture edits preserved)
- `packages/combat/src/rom/rom.selfcheck.ts` (localized Robot tests; concurrent tests preserved)
- `research/decomp/data/family-state-machine-classifications.reviewed.json`
- `research/decomp/data/family-state-machine-coverage.json`
- `research/decomp/family-state-machine-coverage.md`
- `.superpowers/sdd/fleet-task-2-report.md`

## Concern / intentional non-claim

Action-1 schema-v2 constructor slots cannot be classified `ported` from this task alone because each audited slot includes additional live variants 1–4 using other engines. This task completes and tests the shared variant-0 engine and preserves those other routes, but does not claim their seven-dimension coverage.

## Review-finding corrections (2026-07-12)

- Action-0 phase 4 now decays `aimPitch18e0`/`aimYaw18e2`, the exact fields written by `stepDualTargetAim`; the focused test seeds and asserts those fields.
- Stream completion now gates only on modeled actor `+0x1cee` (`wallContact`). A negative part-0 stream pointer no longer advances the phase. Focused tests prove pointer exhaustion alone holds phase 2 and raising `+0x1cee` advances it. This matches both the Ghidra phases and the stream VM/bridge, which lower `wallContact` on stream start and raise it on part-0 completion.
- Production action-1 v0 targetless rows are now mandatory per-member configuration. `chunk_0007.c:32-38` proves movement-page `+0x134/+0x140/+0x14c` copy to actor `+0x868/+0x874/+0x880`; big-endian reads of GG4E `pl0400data.bin` through `pl040bdata.bin` produced:
  - row 2 = 2500 for pl0400/pl0406/pl0407/pl040a;
  - row 2 = 2000 for pl0401;
  - row 2 = 1000 for pl0402/pl0403/pl0404/pl0405/pl0408/pl0409/pl040b;
  - rows 0/1 = 1000 for every member.
- Actor `+0x760` target distance now uses full 3D Euclidean distance in bridge sync and melee fallback. Elevated `(dy=400,dz=300)` tests prove `+0x760=500` and target speed `2*500/20=50`. The separate initial `FUN_80066838` range gate remains horizontal, matching its vector-Y clear.

Fresh post-review verification:

- `pnpm --filter @gf/combat build`: PASS (exit 0).
- `pnpm selfcheck:rom`: PASS (exit 0), including all review-finding regressions and existing Robot member/variant coverage.
- `pnpm audit:family-state-machines`: PASS (exit 0), `ported=7`, `partial=247`, `missing=71`.
- `pnpm audit:family-state-machines -- --strict`: expected exit 1 only for remaining partial/missing live slots.

## Task-2-owned current line ranges

Task-only files (their complete Git diffs are Fleet Task 2-owned):

- `packages/combat/src/families/melee-robot.ts`: changed ranges 25-29, 33-42, 47-70, 82-141, 153-234.
- `packages/combat/src/families/shared-robot-dash.ts`: changed ranges 10, 38-40, 80-82, 98-103, 123-131, 249-252.
- `research/decomp/data/family-state-machine-classifications.reviewed.json`: lines 3-137.
- `research/decomp/data/family-state-machine-coverage.json`: generated Robot constructor/action-0 entries plus summary counts (full Task-2 generated diff).
- `research/decomp/family-state-machine-coverage.md`: line 8.

Overlapping files (only these ranges are Fleet Task 2-owned; surrounding architecture edits predated this task):

- `packages/combat/src/bridge.ts`: line 71 (Robot melee row import); lines 633-644 (per-member variant-0 factory wiring); lines 736-759 (variant-aware melee wrapper); lines 1617-1631 (lock pointer and full-3D `+0x760` sync).
- `packages/combat/src/rom/rom.selfcheck.ts`: lines 57-61 (Robot melee imports); lines 2436-2530 (shared Robot melee real-handler/DOL-row/3D tests); lines 2638-2854 (shared Robot action-0 callbacks/transitions/member variants, pl0406 exclusion, action-1 routing, and elevated bridge test).

Review artifact: `.superpowers/sdd/fleet-task-2-review.diff`.
