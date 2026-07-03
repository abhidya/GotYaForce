#!/usr/bin/env node
// Runner for packages/combat/src/burst.selftest.ts (ATK-011 Hyper/Power Burst input + state
// shell). Separate from selfcheck.ts/its runner by design — see commandSchema.selftest.ts /
// fusionPairs.selftest.ts precedent.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-burst-tests.mjs

import { runSelfTest } from "../packages/combat/dist/burst.selftest.js";

const code = runSelfTest();
process.exit(code);
