# Fleet Task 4A2 report: Girl host-helper proof gaps

## Status

PARTIAL. The exact afterimage state machine, descriptor-driven melee pitch convergence,
actor animation housekeeping fields, bridge/presentation handoff, and reusable battle-floor
snap/revert primitive are implemented and verified. No Girl schema-v2 classification was
promoted because the remaining family-specific face/air-steering and helper-boundary floor
calls listed below are not yet complete across every live member/variant.

## Implemented

- Ported `zz_00b22f4_` with the DOL-read constants and exact order: accumulator `+0x80c`
  interval 8, displacement spacing `100 * +0xb4 * +0x7fc`, reset and position snapshot at
  `+0x800/+0x804/+0x808`, variant-1 presentation edge, then unconditional `+0x768` increment.
- Surfaced signed pose/animation fields `+0x7c/+0x7e/+0x80`, reset them at recovered Girl
  setup boundaries, and surfaced/reset `+0x80c` where the ROM does.
- Ported `zz_006e514_`: signed descriptor `+0xac/+0xae` selection by the low aim-type nibble,
  `* +0x1dc8` step, `+0x518` aim origin, `-bodyPitch-atan2` target clamped to +/-`0x4000`,
  signed BAM16 approach/settle returns, and target-loss return `-1` with exact float `0.9`
  truncation.
- Synced `+0x518` from the authoritative host root/world position, `+0xb4` from the existing
  param-tier `tierSizeScale` chain, and `+0x7fc` from `zz_0068004_`'s exact
  `max(dataPage+0x4c,+0x50)/167.75999450683594` equation. Direct Girl page reads are 9/6
  for all members except pl0308 (25/3).
- Added `zz_00679d0_`'s reusable host primitive: battle-owned support probe, grounded return,
  snap commit, unsupported false return, saved `+0x2c/+0x30/+0x34` revert, and `+0x5e0&0x40`
  frozen-position exception.
- Bridged afterimage edges through `BorgRuntime`/`BattleActorView`. `BattleScene` consumes each
  serial once as an independently-owned translucent frozen model snapshot and disposes it at
  the eight-frame interval.
- Added focused ROM tests for all three afterimage branches, both descriptor rate selectors,
  target loss, supported/unsupported/frozen floor branches, exact scale sync, and independent
  cache/presentation ownership for pl0300 and pl0308. Extended the presentation selfcheck for
  transform consumption, material isolation, edge de-duplication, and expiry/disposal.

## Remaining exact blockers

- Girl family face/air steering is not closed at every recovered call site. The common
  `stepTargetYaw` helper is descriptor-rate BAM16 and target-loss aware, but several bespoke
  Cyber/Battle/Barrier/Killer/series-3 phase comments still stand in for their exact helper
  invocations and return-driven transitions.
- The `groundSnapRevert` primitive is exact and focused-tested, but not every
  Cyber/Battle/Barrier/Killer/series-3 call boundary has been replaced. Some paths still rely
  on the bridge's later generic clamp rather than preserving the ROM helper's return at the
  phase boundary.
- Consequently all eight Girl constructors remain `partial`; adding schema-v2 `ported`
  entries would overclaim the seven proof dimensions.

## Classification and coverage

- Exhaustive Girl matrix: 182 live member/action/variant routes and all exclusions pass.
- Default audit regenerated `research/decomp/data/family-state-machine-coverage.json` and
  `research/decomp/family-state-machine-coverage.md`.
- Current totals: 119 constructors, 325 slots; ported 13, delegated 0, inactive 0,
  partial 241, missing 71. Girl promotions: 0.

## Verification

- `rtk pnpm --filter @gf/combat build` — PASS (exit 0).
- `rtk proxy pnpm --filter game typecheck` — PASS (exit 0).
- `rtk pnpm selfcheck:rom` — PASS (exit 0), including the exhaustive Girl matrix and new
  focused helper/bridge/floor tests.
- `rtk pnpm selfcheck:battle-scene-morph` — PASS (exit 0), including focused afterimage
  presentation assertions.
- `rtk pnpm audit:family-state-machines` — PASS (exit 0), counts above.
- `rtk pnpm audit:family-state-machines -- --strict` — expected FAIL (exit 1): repository-wide
  partial/missing live slots remain.
- `rtk git diff --check` — PASS.

## Scope

Task-owned edits are unstaged. Existing Task-4A and unrelated app/docs/missions/architecture
dirt was preserved; nothing was committed.
