# Fleet Task 3 report: Titan/Panther aimed-shot and morph families

## Status

DONE_WITH_CONCERNS. The live constructor routing and executable combat behavior are implemented, including the exact five-phase `zz_0178394_` repair needed by action-1 variants 3/4. I did not add schema-v2 `ported` classifications because the existing shared modules still contain proof-blocking host residuals listed below.

## Implemented

- Verified Titan root `0x80125dac` / table `0x8032f41c` and Panther root `0x8018c79c` / table `0x8036546c` from `boot.dol`, Ghidra chunks 0033/0046, and `actionStreamTables.json`.
- Added action 0 for all four members and live variants: exact five-volley timer/cursor, aim accumulator, ammo-0 gate, family projectile record pairs (`2b/2c`, `4b/4c`, `32/33`, `4d/4e`), input exit, cue, cooldown, and control-word behavior.
- Added action 1 variant routing for all four members: v0-v2 use `zz_0177dd8_` with exact config slots; v3/v4 use the repaired five-phase `zz_0178394_` table with exact config slots, 20/0 timers, 40 launch velocity, 0.95 reposition, 1.0/0.25 transition scale, and 0.9 recovery damping.
- Restricted action 2 morph routing to live base commands (`pl0604`, `pl0613`); prototype members preserve generic fallback.
- Replaced action 3's prototype ammo approximation with the live weapon-2 consume gate. Panther now exposes and mutates both `+0x144/+0x145 |= 0xc0` part ownership bytes. Callback denial/success, Titan backdash/motion zeroing, Panther setup/rise/control word, spawn records, and sound behavior are tested.
- Removed tuned aimed/morph completion timers. The machines now consume bridge-replayed `+0x1cef` part-state and `+0x1cee` decoded stream-completion events.
- Added real-handler tests for every action-1 variant branch, five lunge phases, ammo denial/success, Panther part bytes, base/prototype morph routing, and all 60 live action 0/1/3 member-variant bridge routes.

## Remaining proof blockers

- Action 0 / both constructors: the firing loop is executable, but its unconditional `zz_0048d54_(actor, 1)` weapon/part-animation update needs the unsurfaced `+0x579`, `+0x1b03`, `+0x1b20..+0x1b45`, and per-part `+0x1bd4..+0x1c05` blocks. The pre-spawn `zz_006bf80_` also updates global six-player visibility masks through actor `+0x3e5`, target `+0xcc/+0x83/+0x5e6`, which the isolated actor/bridge does not own. This blocks full action-0 classification despite exact timers, ammo, record pairs, cursor, and exit behavior.
- Action 2 / `shared-morph-x.ts`: the renderer/runtime cannot hot-swap to forms `0x605`/`0x614`. Missing lifecycle state includes actor mirror `+0x94`, carried `+0x3e4/+0x3e7 -> +0x96/+0x97`, descriptor/model re-init `zz_0056ce0_`, weapon/ammo re-init `FUN_800562b8`, and event post `zz_01cb750_`. The actor-side borg id, counter, gun wipe, control word, and stream exit are executable, but visual/descriptor lifecycle prevents full action-2 classification.
- Action 1 proof gaps are resolved: `pl####data.bin` descriptor offsets `+0x134/+0x140/+0x14c` now generate production actor rows `+0x868/+0x874/+0x880`. Exact rows are Titan/Proto Titan `[1000,600,1000]` and Panther/Proto Panther `[1000,1200,1000]`; `zz_01782dc_` indexes them by `prevAction % 3` with no tuned fallback.
- Action 3 proof gaps are resolved: descriptor s16 `+0xae` is the existing `turnStep1`, actor `+0x768` and body pitch `+0x70` are surfaced, and the exact target/rate equations are used. `+0x1d0f` is proven to be part 1's signed state byte (`+0x1cd4 + 0x20 + 0x1b`) and gates gravity reload. Saved ground position `+0x2c..+0x34`, `+0x73f`, and `+0x80c` are surfaced and bridge-synchronized where host state exists.
- Reviewed schema-v2 statuses were not advanced in this slice: action 0 still has the weapon/visibility residual above and action 2 still has morph lifecycle residuals. Action 1 and action 3's specifically assigned field/equation blockers are resolved and production-tested.

## Verification

- `pnpm --filter @gf/combat build` — PASS.
- `pnpm selfcheck:rom` — PASS, including the complete Titan/Panther member/variant matrix.
- `pnpm audit:family-state-machines` — PASS: 119 constructors, 325 slots, structural errors 0; ported 7, partial 247, missing 71.
- `pnpm audit:family-state-machines -- --strict` — expected FAIL because repository-wide partial/missing slots remain.
- `git diff --check` — PASS.

## Scope

Combat edits are limited to `bridge.ts`, `shared-aimed-shot-x.ts`, `shared-engine.ts`, `rom/actor.ts`, and `rom/rom.selfcheck.ts`. Concurrent non-combat changes, including `apps/game/src/sim/getStorage.ts`, were not touched.
