#!/usr/bin/env node
// Runner for packages/combat/src/commandSchema.selftest.ts (ATK-001 command schema,
// ATK-004 movement-context capture). Separate from selfcheck.ts/its runner by design — see
// NOTES-ATK-001.md in research/tasks/attack-port/.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-attack-schema-tests.mjs

import { runSelfTest } from "../packages/combat/dist/commandSchema.selftest.js";

const code = runSelfTest();
process.exit(code);
