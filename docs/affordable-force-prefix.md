# Affordable saved-force deployment

Each human gets their own difficulty budget. Up to 30 saved IDs are considered
in order; the first cost that would exceed budget ends deployment. Equality is
accepted. Later cheaper Borgs cannot fill an earlier over-budget gap. Confirmation
requires a nonempty deployment for every human. The second human still uses the
next saved slot, wrapping around: existing browser behavior, not a new parity claim.

## Source evidence

- `docs-site/public/chunks/chunk_0047.c:2433-2436`: reload budget per human.
- `chunk_0047.c:2568-2602`: saved-force branch, 30 slots, cumulative cost,
  stop before overflow, copy accepted entries into battle work memory.
- `chunk_0047.c:2032-2052` and `chunk_0056.c:680-718`: confirmation calls the
  read-only count helper and rejects zero affordable entries.

`apps/game/src/forceDeployment.ts` is shared by the session (VM human roster and
mission-run fallback) and SelectForce preview. `beginRun` must not write this
copy back to the selected slot. The editor receives the saved list. Selection
reports deployment count, cost and remainder per human, and explains empty-prefix
rejection without inventing a default Borg.

## Limits

Supported scope: dense, valid browser IDs with known positive costs. The helper
stops defensively at unknown, nonpositive or nonfinite costs; it does not skip
those entries or replace them with a default. This does not assert source parity
for malformed/sparse saves. Full cost/variant parity, zero-cost exact-budget
behavior and random-force generation remain unverified. Preview wording/layout
is a browser accommodation, not a retail UI reconstruction. Existing Force
Builder capacity/edit validation is unchanged. Confirmation does not prune or
persist the deployment prefix.

## Regression checks

`pnpm selfcheck:game-session` includes the existing navigation/storage and real
Challenge restart campaigns, followed by 24 focused prefix checks. The new checks
exercise the real helper, session, VM, mission fallback, combat-config conversion,
storage reload and SelectForce behavior. Drawing/DOM and combat construction are
isolated; the fallback test injects a VM-build failure. Costs are synthetic.

Negative control: `GF_PREFIX_BASELINE=9c62021 node --test
scripts/affordable-force-prefix.test.mjs` substitutes only historical session/UI
source into the emitted scratch graph, leaving the checkout untouched. It produces
12 semantic failures out of 24 tests on the pre-fix source, versus 24/24 on the fix.
The helper cases remain current-source tests in this negative control.

Typecheck, game build, Force Builder, menu flow, title frontend and Challenge VM
checks pass. The unchanged contributor aggregate stops at the pre-existing HUD
check because this checkout lacks the ascii font, fmg00 roundel and bn0000 banner
assets. No assets were copied. Full visual/browser validation is not claimed.
