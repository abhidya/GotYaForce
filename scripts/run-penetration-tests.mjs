#!/usr/bin/env node
// Runner for packages/combat/src/projectilePenetration.selftest.ts (OBSERVED_WIKI projectile
// penetration, ATK-008). Requires packages/combat built first (tsc -b).
//   tools/node/node.exe scripts/run-penetration-tests.mjs

import { runSelfTest } from "../packages/combat/dist/projectilePenetration.selftest.js";

const code = runSelfTest();
process.exit(code);
