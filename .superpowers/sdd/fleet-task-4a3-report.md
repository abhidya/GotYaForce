# Fleet Task 4A3 report: Girl helper boundaries and honest classification

## Status

PARTIAL by the task's full-eight-constructor objective, with all independently complete
Girl constructor/action slots promoted. Exact family call boundaries are wired and verified;
the remaining blocker is the missing authoritative renderer-to-runtime part-1 world anchor
for `zz_006e1ac_`.

## Implemented

- Wired `zz_006d0dc_`/`zz_006d144_` call sites across the shared ranged/melee cluster,
  Cyber Girl, Battle/Barrier/Killer X, and series-3. Aim types `0xc0`, `0xc1`, and `0x81`
  now select descriptor `+0xac/+0xae` exactly. `zz_006d144_` target loss retains `+0x5ac`
  and settles heading; `zz_006d0dc_` target loss settles to the current heading.
- Changed the host `zz_00677b0_` surface to return its grounded result and consumed that
  result at every landing/phase boundary. Replaced all Girl `zz_00679d0_` placeholders with
  `groundSnapRevert`, preserving supported snap, unsupported saved-position revert, and the
  `+0x5e0&0x40` frozen-position exception.
- Wired Cyber Girl Super P0/P1/P2 and normal P0/P1 in ROM order, including gated re-facing,
  same-frame Super P0 tail call, P2 stream tick, and normal P1's exact snap return driving
  the air-landing transition.
- Wired series-3 P0/P1 face and air-pitch invocation order plus P0/P1/P2 snap/revert calls;
  P2 now branches on the direct helper return.
- Added `partAimAnchors` and a `zz_006e1ac_` convergence surface with exact signed BAM16,
  descriptor selector, `+0x768` rate scale, clamp, settle, and target-loss decay. A supplied
  part-1 anchor is exact; unported slots use a deterministic root fallback and remain partial.
- Preserved the existing Task-4A/4A2 afterimage, pose housekeeping, pitch, scale, ammo,
  event-byte, and phase repairs.

## Authoritative-anchor audit and blocker

ROM `zz_006e1d0_` consumes the per-part world row at actor `+0x8e0/+part*0x30`,
`+0x8f0/+part*0x30`, and `+0x900/+part*0x30`. The repository has weapon-attachment
`boneIndex` data and renderer model nodes, but no proven identity between those indices and
the ROM part rows, and no renderer-to-combat world-transform feed. Existing aerial-dive,
flight, and Samurai ports explicitly document the same missing renderer-owned anchor.
Therefore no anchor-dependent slot was certified from the root fallback.

Constructor/actions left partial specifically because at least one live member invokes the
blocked air/part pitch path:

- Battle Girl `0x800c04c0` action 2: pl030b air path.
- Wire Girl `0x80106e3c` action 3: series-3.
- Barrier Girl `0x80107e7c` action 2 (pl0306 shared X) and action 3 (series-3).
- Delta II `0x8019c380` action 3: series-3.
- Killer/Shadow Girl `0x80134078` action 2: pl0304 shared X and pl0308 bespoke X.
- Spinner Girl `0x801ba020` action 2: series-3.

Cyber Girl and Delta have no additional live anchor-dependent action beyond their promoted
complete slots. Auditor schema requires a constructor/action `ported` entry to cover every
live member, so the independently complete pl0300 Battle X and pl0302 Barrier X could not be
promoted while their sibling members remain blocked.

## Classifications and coverage

Review correction: seven complete constructor/action slots remain schema-v2 `ported`:

- Battle Girl: action 0.
- Wire Girl: action 0.
- Barrier Girl: action 0.
- Delta II: action 0.
- Killer/Shadow Girl: action 0.
- Cyber Girl: actions 0 and 2.

Coverage regenerated successfully after review: 119 constructors, 325 slots; ported 20,
delegated 0, inactive 0, partial 234, missing 71. The exhaustive real-handler and bridge matrix remains
182 live Girl member/action/variant routes with all exclusions exact.

All seven action-1 entries were demoted because `zz_006e514_` consumes the same renderer
part-row anchor whose identity/feed remains unproven. Cyber Girl action 2 remains complete.

Final afterimage review confirms the subtype-1 backward offset uses owner `+0x5ae` lock yaw.
Its `+0x84=0x1e` value is executed as `FUN_80047aa4` transform flags (X/Y/Z rotation and
authored scale), with focused bridge and presentation regressions.

## Focused evidence

`rom.selfcheck.ts` now asserts descriptor `+0xac` yaw stepping, `zz_006d144_` retained-yaw
target-loss settling, descriptor `+0xae * +0x768` part-1 pitch stepping at an explicit anchor,
`zz_00677b0_` grounded return, and all earlier supported/unsupported/frozen
`zz_00679d0_` branches. The full Girl matrix and existing Cyber/series-3 phase assertions pass.

## Verification

- `rtk pnpm --filter @gf/combat build` — PASS.
- `rtk proxy pnpm --filter game typecheck` — PASS.
- `rtk pnpm selfcheck:rom` — PASS after the final build, including the new helper tests.
- `rtk pnpm selfcheck:battle-scene-morph` — PASS.
- `rtk pnpm audit:family-state-machines` — PASS; counts above.
- `rtk pnpm audit:family-state-machines -- --strict` — expected FAIL: repository-wide
  partial/missing live slots remain.
- `rtk git diff --check` — PASS.

## Scope

All edits are unstaged and uncommitted. No unrelated files were staged, reset, or committed.
