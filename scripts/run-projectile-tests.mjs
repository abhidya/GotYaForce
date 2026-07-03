#!/usr/bin/env node
// Runner for packages/combat/src/projectileConsumption.selftest.ts (ATK-008 projectile
// consumption refactor: persist + rehit interval). Separate from selfcheck.ts/its runner by
// design — see the concurrency coordination note in
// research/tasks/attack-port/ATK-008-penetration-consumption.md.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-projectile-tests.mjs

import { runSelfTest } from "../packages/combat/dist/projectileConsumption.selftest.js";

const code = runSelfTest();
process.exit(code);
