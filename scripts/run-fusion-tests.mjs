#!/usr/bin/env node
// Runner for packages/combat/src/fusionPairs.selftest.ts (ATK-018 Power Burst fusion
// pair-data shell). Separate from selfcheck.ts/its runner by design — see
// commandSchema.selftest.ts / run-attack-schema-tests.mjs precedent.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-fusion-tests.mjs

import { runSelfTest } from "../packages/combat/dist/fusionPairs.selftest.js";

const code = runSelfTest();
process.exit(code);
