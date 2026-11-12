# Time Bomber reconstruction and fresh verification

## Scope and provenance

The prior checkout became inaccessible. A separate, fresh clone was verified at remote main `110ca2a73e213990e2502045b2a8ae6d478ba098` (PR48). No previous workspace path was overwritten. Retained authored source and patch text were used to reconstruct the ground-neutral, airborne/fallback and bounded-running X implementations, their tests, and the isolated primary-mine lifecycle.

The unavailable historical local commits were `5d9c5ca`, `a373c14`, `58e28ac` and `907cae5`. This reconstruction does not claim to restore their Git objects or exact trees. The recovered Wire Gunner source SHA256 `73d1408bf58c0d6329bb3feb3ccab79866ee72faf248ddc5091b18ead8abdae0` matches its previously recorded generator binding. Recovered projectile source/tests were independently compared against their retained authored text. Other recovery hashes identify the new files, not unavailable old objects.

The Time Bomber renderer regression was freshly recreated from the maintained Gatling explosion harness. Ground, air and mine evidence summaries were also reconstructed rather than asserted byte-identical. No original disc, executable or extracted asset was added.

## Fresh verification

- Full `verify:contributor` passes, including repository policy, typecheck, HUD, menu/force/session/input/Challenge checks, render and projectile checks, ROM checks, complete combat lifecycle, import tests and game build.
- Existing oracle harness:81 passed,0 failed,1 expected private-snapshot skip. Its regenerated Wire Gunner reference certifies only the existing oracle domain, not the new Time Bomber actions against console execution.
- Matching helper suite:52 passed.
- Independent Time Bomber and existing Gatling renderer regressions pass.
- Diff whitespace check passes.

The full clone includes the three already-tracked HUD images missing from the earlier checkout, resolving that previous aggregate blocker. No new assets were uploaded or substituted. Build warnings about large output bundles remain non-fatal.

## Unfinished work stays separate

The B-mine gameplay adapter was still uncommitted and had not passed its new integration tests when the prior checkout disappeared. Its recovered adapter, patch scripts, known issues and test fixture are staged separately and are not installed in this verified baseline. They must be reviewed, applied and tested as a distinct next change.

Remaining mine integration includes shared694/B-X ordering, event-return ammo, direct damage30, durability1 receiving collision, next-update detonation, independently registered explosion eligibility and owner/team gates. Static attachment, host geometry/trigonometry and incomplete specialized receiving windows must remain explicit limitations. No guaranteed50 damage or complete game-parity claim is justified.

Nothing in this reconstruction was pushed, published, merged or deployed. Existing publication approval remains pending.
