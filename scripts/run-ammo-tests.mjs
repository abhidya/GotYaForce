#!/usr/bin/env node
// Runner for packages/combat/src/ammo.selftest.ts (ATK-009 ROM-shaped ammo/refill model).
//
// Deliberately separate from selfcheck.ts/its runner by design — see ATK-009's coordination
// note in research/tasks/attack-port/ATK-009-ammo-refill-model.md. Modeled on
// scripts/run-attack-schema-tests.mjs.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/selfcheck-*.mjs.
//   tools/node/node.exe node_modules/typescript/bin/tsc -b packages/combat
//   node scripts/run-ammo-tests.mjs

import { runSelfTest } from "../packages/combat/dist/ammo.selftest.js";

const code = runSelfTest();
process.exit(code);
