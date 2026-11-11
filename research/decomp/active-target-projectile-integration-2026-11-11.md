# Active ally target reaches projectile aiming and the ROM bridge

## Source evidence

All locations refer to `docs-site/public/chunks/chunk_0009.c`.

- `zz_006b450_` request 5 saves the enemy actor at +0x6e0, selects a same-team entry (1490–1511), and writes shared active entry/actor +0x504/+0x508 and position +0x50c (1564–1571). Request 4 restores the saved enemy (1468–1477).
- `zz_006bda8_` copies active +0x504/+0x508 to attack +0xc8/+0xcc (1810–1811), then obtains aim +0x518 and target distance from that entry (1830 onward). This consumer has no enemy-only filter. Its separate +0x6b8 interruption gate is not changed here.
- `zz_006ee14_` copies the attack's +0xc8/+0xcc into the projectile (3795–3796) and applies its existing cone test against aim +0x518 (3840–3842). The retained enemy is not the selected projectile target during ally lock.
- `zz_006bf80_` calls `zz_006bda8_` and uses resulting +0xcc to update target visibility +0x5e6 (1868–1880). Bridge visibility selection therefore follows the active target too.

## Reproduced browser-core gap

An in-memory fixture acquired an enemy, then selected an ally. It returned `mode=ally`, `activeTarget=ally`, but `homingTargetForSpawn=enemy`. With the enemy behind and ally ahead, the same helper incorrectly returned null. Movement/camera and aimed-target telemetry already used the active selector, making shots disagree with the selected target.

## Bounded implementation

`targetLock.ts` shares the existing active UID selector without introducing a combat/bridge/projectile import cycle. The public `combat.ts` export and legacy null-coalescing fallback remain unchanged. A live-target resolver rejects missing/dead/self targets. Spawn cone checks, generic and family firing now use the active target; the ROM bridge uses it for lock coordinates, distance, cached position, yaw, and visibility. FireChild telemetry copies the active UID. Launched shots retain their spawn-time target.

No changes to contextual B's enemy-only selection, damage/team rules, ally-support powers, aim-cone angle, projectile speed, homing rate, or interruption rules. This is a target-routing correction, not a claim of full ally-support parity.

## Regression coverage

`targetLock.selftest.ts`, called by the existing lifecycle suite, uses real Battle Z/release inputs. It checks generic B press/release projectiles and their opposite-bearing velocity, actual Battle family spawning through the installed Ninja bridge callback, bridge target/visibility fields, FireChild target copying, cone rejection, dead/missing targets, normal reacquisition, immutable launched targets, and legacy fallback.

Focused runner: `node packages/combat/scripts/run-target-lock-tests.mjs`.
Existing aggregate route: `node packages/combat/scripts/run-lifecycle-tests.mjs`.

Verified: focused suite, lifecycle suite, and `pnpm exec tsc -b packages/combat` pass. An in-memory esbuild negative control substituted only the former enemy-only spawn selector, with all symbols and other code intact; it failed at `spawn aim follows ally`, proving the regression detects the original behavior rather than a missing export. Family firing coverage exercises the installed bridge-to-Battle spawn callback, not the entire action-stream choreography. Browser visual QA is separate.
