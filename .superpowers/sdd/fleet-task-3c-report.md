# Fleet Task 3C report — DONE_WITH_CONCERNS

## Result

The two internal morph forms are extracted from authoritative GG4E data and the live
pl0604→0x605 / pl0613→0x614 lifecycle now completes through a normal bridge tick. The
same runtime UID retains its original borg identity, HP, team, owner/progression/results
identity while descriptor movement, weapon cells, actor mirrors, combat form, presentation,
and the `zz_01cb750_` event refresh in place. Prototype pl0618/pl0627 action 2 remains excluded.

## Authoritative extraction

- `pl0604data2.bin` and `pl0613data2.bin` are 864 bytes: two 432-byte descriptor pages.
  Page 1 is generated as internal `pl0605` / `pl0614` in the normal movement schema.
- `pl0605`: speed/accel/jump/min `12/0.24/15/1`; dash `20/-0.05/0/60`; gravity
  `0/-0.6/-0.02`; action rows `[0,800,0]`; turn `[2560,3072]`; camera
  `220/220/600/700/600/700`.
- `pl0614`: `20/0.235/10/5`; dash `25/-0.05/0/60`; gravity `0/-0.6/-0.02`;
  action rows `[0,800,0]`; turn/camera equal to pl0605.
- `PTR_DAT_802f2988` family 06 variants 05/14 supply exact default rows:
  pl0605 `[HP450, weapon0 type/count 5/5, refill 0/180, weapon1 zero]`; pl0614
  `[HP450, 10/10, 0/300, weapon1 zero]`. HP is extracted but intentionally not applied
  during morph; existing HP/max HP remain owned by the original combatant.
- PZZ member 5 `pl0604b_mdl.arc` / `pl0613b_mdl.arc` is exported with the existing
  HSDRaw/Collada/validated-GLB pipeline to internal presentation directories. The original
  MOT files' authored group-2 banks drive each alternate form's clips.

## Implementation

- Movement/stat generators emit internal-form profiles without adding selectable roster rows.
- Morph host refresh now requires both profiles and commits descriptor fields, movement rows,
  three weapon cells, ammo alias, `combatFormId`, clip reset, and event publication synchronously.
- Fixed the normal bridge lifecycle bug: per-frame `dispatchCommandRecord(cue 44)` reset
  `+0x540..+0x543`, trapping multi-phase machines in phase 0. State 61/action fields now persist
  after the entry dispatch. Regression tests prove the decoded scheduler raises `+0x1cee` at
  the authored boundary and the next normal tick consumes it for both forms.
- Battle view carries `combatFormId`. BattleScene detects a same-UID form edge, stops/uncaches
  the old mixer, disposes old model geometry/materials, clears clip actions, guards stale async
  loads with a revision, and attaches the new form without replacing the actor group/UID.

## Verification

- `rtk node scripts/gen-movement-physics.mjs GG4E` — PASS, 210 profiles, missing none.
- `rtk node scripts/gen-borg-source-stats.mjs` — PASS, 210 profiles, roster HP verified.
- Internal HSDRaw model export plus `convert-runtime-models-to-glb.mjs` — PASS; 19 archive
  model roots converted and GLB-validated, runtime uses each `model_00.glb`.
- `rtk proxy pnpm --filter @gf/combat build` — PASS.
- `rtk proxy pnpm --filter game typecheck` — PASS.
- `rtk proxy pnpm selfcheck:rom` — PASS (`ALL PASS`), including exact scheduler boundary,
  full refresh, identity preservation, event post, and prototype exclusion.
- `rtk proxy pnpm selfcheck:battle-scene-morph` — PASS; proves same UID/group, old
  model/material disposal, old mixer/action-cache discard, and new model/clip selection.
- `rtk proxy pnpm audit:family-state-machines` — PASS: 119 constructors / 325 slots,
  ported 7, partial 247, missing 71.
- strict audit — expected FAIL because repository-wide partial/missing live slots remain.
- `rtk git diff --check` — PASS.

## Concerns / classification

- Six schema-v2 classifications are advanced: Titan/Panther actions 0, 1, and 3.
  Both action-2 slots remain partial because exact internal-form group-2 semantic animation
  mappings are not ROM-proven. Final fleet output is 13 ported / 241 partial / 71 missing.
- The exporter materialized all model roots, DAE files, and extracted PNGs in the two internal
  directories although runtime selects `model_00.glb`. They are authoritative generated output,
  but a later asset-packaging pass may choose to retain only runtime GLBs.
- No files were staged or committed. Concurrent battleBootstrap/getStorage/game-session,
  docs, menu, and missions changes were not edited as part of this task.

## Task-owned paths

- `scripts/gen-movement-physics.mjs`, `scripts/gen-borg-source-stats.mjs`
- `packages/combat/src/data/movementPhysics.json`, `packages/combat/src/data/borgSourceStats.json`
- `packages/combat/src/bridge.ts`, `packages/combat/src/rom/rom.selfcheck.ts`
- `apps/game/src/sim/battleView.ts`, `apps/game/src/sim/battleScene.ts`,
  `apps/game/src/sim/borgPresentationAssets.ts`, `apps/game/src/sim/battleScene.morph.selfcheck.ts`
- `scripts/export-internal-morph-models.mjs`, `scripts/run-battle-scene-morph-selfcheck.mjs`
- `apps/game/public/models/pl0605/`, `apps/game/public/models/pl0614/`
- `package.json` (focused selfcheck script only)

## Acceptance follow-up: schema-v2 classifications

The reviewed schema classifies six constructor/action slots as `ported`, with exact
audit-derived live coverage and per-member evidence for all seven
dimensions (`rootDispatch`, `variantDispatch`, `phaseTransitions`, `constants`,
`streamBehavior`, `bridgeWiring`, `focusedTests`):

- Titan constructor `0x80125a28`, actions 0/1/3: pl0604 and pl0618 variants 0–4.
- Panther constructor `0x8018c2b0`, actions 0/1/3: pl0613 and pl0627 variants 0–4.
- Both action-2 slots remain partial because exact internal-form semantic animation
  mappings are unproven; prototype fallbacks remain excluded.

Regenerated coverage: 119 constructors / 325 slots; ported **13**, partial **241**,
missing **71**. Acceptance verification: default audit PASS;
strict audit expected FAIL for remaining repository-wide partial/missing slots; combat
build PASS; full ROM selfcheck PASS; focused BattleScene morph selfcheck PASS; diff
check PASS. No files were staged or committed.

## Review corrections

This section supersedes the earlier acceptance count/classification statement above.

- Action 3 live facing now derives `lockYaw` and `activeYaw` as exact signed BAM16
  `atan2(target.x-actor.x, target.z-actor.z)` from the synchronized target on every
  bridge sync/relevant handler tick. ROM selfchecks cover elevated/offset `0x2000`
  bearing at handler and bridge levels plus a later-tick `-0x4000` target change.
- `SkeletonUtils.clone` shares mesh resources, so `cloneDisposableModel` now clones
  every geometry/material for BattleScene-owned instances. The focused scene test
  creates two same-form actors from one cached source, morphs one, proves only its
  resources are disposed, and verifies the peer remains valid.
- Exact internal group-2 bank identity is proven, but the prior per-slot semantic labels
  (dash direction, shoot/melee/hit/special/death) were Rosetta-derived/TUNED. Those
  `pl0605`/`pl0614` preferred mappings were removed; internal indexes are restricted to
  group 2 so generic heuristics cannot select the base robot's banks. Because exact
  post-morph animation semantics remain unavailable, only Titan/Panther action 2 was
  demoted from reviewed `ported`; executable lifecycle tests remain.
- Action 0 is five volleys, not six. All reviewed/report text is corrected, and the ROM
  regression proves cursor `5→-1`, exactly five projectile pairs (five of each record),
  exit, and no sixth pair.

Fresh verification after review fixes:

- `rtk proxy pnpm --filter @gf/combat build` — PASS.
- `rtk proxy pnpm --filter game typecheck` — PASS.
- `rtk proxy pnpm selfcheck:rom` — PASS (`ALL PASS`), including facing and five-volley tests.
- `rtk proxy pnpm selfcheck:battle-scene-morph` — PASS, including two-actor cache ownership.
- `rtk proxy pnpm audit:family-state-machines` — PASS: 119 constructors / 325 slots;
  ported **13**, partial **241**, missing **71**.
- `rtk proxy node scripts/audit-family-state-machines.mjs --strict` — expected FAIL:
  repository-wide partial/missing live slots remain.
- Task-owned `rtk proxy git -c core.safecrlf=false diff --check -- <Task 3 paths>` — PASS.
  The repository-wide check is blocked by an unrelated concurrent edit:
  `research/asset-coverage/stage-readability.md:65: new blank line at EOF`.

No files were staged or committed.

## Final documentation reconciliation

- `fleet-task-3-aggregate-report.md` now records final coverage as 13 ported / 241
  partial / 71 missing, six new ported entries (Titan/Panther actions 0, 1, 3), and
  both action-2 slots partial for unproven semantic animation mappings.
- Focused grep across `fleet-task-3*.md` found no remaining stale `15/239`, “all
  eight”, “Eight new”, or `7/247/71` wording.
- Task-owned documentation diff check passed. No code, staging, or commits were changed.
