#!/usr/bin/env node
// Runner for packages/combat/src/healing.selftest.ts (ATK-019 healing & lifesteal shells,
// DISABLED by default). Separate from selfcheck.ts/its runner by design — see
// commandSchema.selftest.ts / burst.selftest.ts precedent.
//
// Also (re)writes research/tasks/attack-port/NOTES-ATK-019.md with the roster-verification
// log every run.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-healing-tests.mjs

import { runSelfTest } from "../packages/combat/dist/healing.selftest.js";

const code = runSelfTest();
process.exit(code);
