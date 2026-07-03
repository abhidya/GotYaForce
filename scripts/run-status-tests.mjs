#!/usr/bin/env node
// Runner for packages/combat/src/status.selftest.ts (ATK-010 status-effect runtime shell).
// Separate from selfcheck.ts/its runner by design — see the ATK-010 ticket's coordination note.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-status-tests.mjs

import { runSelfTest } from "../packages/combat/dist/status.selftest.js";

const code = runSelfTest();
process.exit(code);
