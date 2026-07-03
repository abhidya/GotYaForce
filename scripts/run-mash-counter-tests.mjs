#!/usr/bin/env node
// Runner for packages/combat/src/mashCounter.selftest.ts (ATK-017 button-mash counter
// scaffold, DISABLED by default). Separate from selfcheck.ts/its runner by design — see
// commandSchema.selftest.ts / burst.selftest.ts precedent.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-mash-counter-tests.mjs

import { runSelfTest } from "../packages/combat/dist/mashCounter.selftest.js";

const code = runSelfTest();
process.exit(code);
