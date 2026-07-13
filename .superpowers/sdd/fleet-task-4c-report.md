# Fleet Task 4C report: Machine Red / Machine Blue

Date: 2026-07-12

## Result

Replaced both generic `DEFAULT_CONFIGS.dashAttack(0)` registrations with constructor-exact roots. Machine Red action 2 now follows its actual two-phase engine, but remains `partial` because `stepPartTargetPitch` still lacks the authoritative renderer-owned part-1 anchor feed. Machine Blue action 2 now uses the already-banked `zz_0179fcc_` implementation/config; actions 3 and 4 have their exact hardpoint boundaries, but remain `partial` because the battle host does not yet feed the live `+0x14c..+0x14f` attachment bytes. Actions 0/1 for both constructors remain conservative `partial` pending their distinct melee engines.

Coverage remains **20 ported / 234 partial / 71 missing**.

## Banked evidence

### Machine Red (`0x800c91bc`)

- Root `0x800c94d4`; action table `0x8030a558` = `0x800c9510`, `0x800ca034`, `0x800cb9d4`.
- Action 0 variant table `0x8030a564`, six live leaves: `0x800c9590`, `0x800c997c` x3, `0x800c9d44`, `0x800c95d8`.
- Action 1 variant table `0x8030a59c`, six live leaves: `0x800ca5dc`, `0x800cb3c8`, `0x800cb394`, `0x800caddc`, `0x800cb424`, `0x800ca070`.
- Action 2 variant table `0x8030a658`: all five variants route `0x800cba10 -> 0x80179d20`.
- `zz_0179d20_` table `0x804347a8` has exactly two entries, `0x80179d58` and `0x80179e60`. The adjacent `0x8017a3ac` word begins a different overlapping table and is not a third Red phase.
- Config `0x8030a66c`: slot 0, scale `0x3f733333` (0.949999988079071), callback `0x800cba38`.
- Callback `0x800cba38`: `zz_006dbe0_(2,1,1)`, then `zz_016cc24_` types `0/0x0c/0x0d/0x0e` for `pl0600/pl0608/pl0616/pl061c`; velocity seed `h=0, y=4, decel=0, gravity=0`.

### Machine Blue (`0x800ce730`)

- Root `0x800cea5c`; action table `0x8030ce34` = `0x800cea98`, `0x800cf884`, `0x800cf990`, `0x800cfb94`, `0x800cfc38`.
- Action 0 table `0x8030ce48`: five leaves `0x800ceae0`, `0x800cef38` x3, `0x800cf300`.
- Action 1 table `0x8030ce80`: `0x800cf8c0`, `0x800cf8f4`, `0x800cf928`, `0x800cf968` x2.
- Action 2 table `0x8030cef8`: all five variants route `0x800cf9cc -> 0x80179fcc`, config `0x8030cf0c`.
- Action 3 direct leaf `0x800cfb94`: find first hardpoint with `(+0x14c+i)&1`, deploy `zz_013212c_(base+i, actor+0x14c+i)`, with base 2 or 10 for `pl061d`, then shot-state release. The port preserves this third-argument identity as an explicit hardpoint index hook; the callee's record-mutation contract remains unresolved.
- Action 4 table `0x8030cf24`: variants 0..2 route `0x800cfc74` (group 4 slot 2, scale 0.95, contact deploys all active hardpoints); variants 3..4 route immediate all-hardpoint leaf `0x800cfdf0`.

Evidence sources: GG4E `boot.dol` raw pointer/float reads and disassembly; Ghidra `chunk_0021.c` and `chunk_0044.c`; organized functions for all roots/leaves above; `packages/combat/src/data/actionStreamTables.json`; generated fleet coverage.

## Changes

- Added `families/machine-red-blue.ts` with executable address tables, dedicated family configuration, exact Red action-2 phases/callback, Blue aimed-shot wiring, and Blue action-3/action-4 hardpoint dispatch.
- Switched all eight bridge registrations to the dedicated constructor handlers.
- Surfaced `RomActor.attachmentFlags14c` as four exact bytes rather than substituting unrelated part flags.
- Corrected Machine Blue aimed-shot ammo handling to call the exact host `onAllocateResource(actor,2,1,1)` seam instead of unconditionally passing.
- Added exhaustive live routing checks (all Red 4x(6+6+5) and Blue member-specific live routes) plus focused Red config/ammo/projectile and Blue first/all-hardpoint tests.

## Conservative blockers

- Machine Red and Blue actions 0/1 use several bespoke leaves and config tables; merely resembling shared melee engines is not address identity, so no behavioral alias was installed and those slots remain `partial`.
- Machine Red action 2 uses the exact `stepTargetYaw(0xc1, preserve=true)` and `stepPartTargetPitch(0xc1)` helpers, but the part-1 renderer anchor is not authoritatively fed in production; it therefore remains `partial`.
- Blue `+0x14c..+0x14f` is now represented exactly on `RomActor`, but `BorgRuntime` has no authoritative model/hardpoint ownership feed. Production defaults remain zero, so actions 3/4 stay `partial` even though their state-side dispatch is implemented and directly tested.
- `zz_013212c_` receives the exact `actor+0x14c+i` record identity. The port exposes the corresponding index via `onMachineHardpointDeploy`, but does not guess the callee's mutation of that record.
- Machine Blue action 2 retains the aimed-shot renderer afterimage boundary; without that presentation integration it remains `partial`.
- Blue shot-state release uses the surfaced shared shot fields/cue dispatch, but complete `zz_006a668_` weapon-animation record parity for these leaves is not independently demonstrated here.

## Verification

- `pnpm --filter @gf/combat build` — pass.
- `pnpm --filter game typecheck` — pass.
- `pnpm selfcheck:rom` — pass, including exhaustive and focused Task 4C assertions.
- `pnpm audit:family-state-machines` — pass; `20 / 234 / 71`.
- `git diff --check` — pass.
- Strict audit is expected to fail only for the documented remaining partial/missing fleet slots.
