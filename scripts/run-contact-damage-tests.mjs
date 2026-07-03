#!/usr/bin/env node
// Runner for packages/combat/src/contactDamage.selftest.ts (ATK-006 passive contact-damage
// scaffold, DISABLED by default). Separate from selfcheck.ts/its runner by design — see
// commandSchema.selftest.ts / burst.selftest.ts precedent.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   pnpm --filter @gf/combat build
//   node scripts/run-contact-damage-tests.mjs

import { runSelfTest } from "../packages/combat/dist/contactDamage.selftest.js";

const code = runSelfTest();
process.exit(code);
