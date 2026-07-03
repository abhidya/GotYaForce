#!/usr/bin/env node
// Runner for packages/combat/src/xammo.selftest.ts (X-attack ammo wiring: weapon cell 1 =
// X-attack ammo, separate from weapon cell 0 = B-attack ammo; behavior-notes.md (ao),
// CONFIRMED_MANUAL). Separate from selfcheck.ts/its runner by design — see
// healing.selftest.ts / burst.selftest.ts precedent.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/run-healing-tests.mjs.
//   node scripts/run-xammo-tests.mjs

import { runSelfTest } from "../packages/combat/dist/xammo.selftest.js";

const code = runSelfTest();
process.exit(code);
