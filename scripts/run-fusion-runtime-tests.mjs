#!/usr/bin/env node
// Runner for packages/combat/src/fusionRuntime.selftest.ts (ATK-018 Power Burst fusion
// pair-table runtime wiring). Separate from scripts/run-fusion-tests.mjs (which validates
// the research extraction) by design — see the fusionPairs.selftest.ts precedent.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/run-fusion-tests.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-fusion-runtime-tests.mjs

import { runSelfTest } from "../packages/combat/dist/fusionRuntime.selftest.js";

const code = runSelfTest();
process.exit(code);
