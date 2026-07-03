#!/usr/bin/env node
// Runner for packages/combat/src/levelRows.selftest.ts (ATK-020 borg level plumbing).
// Separate from selfcheck.ts/its runner by design -- see commandSchema.selftest.ts /
// ammo.selftest.ts's own runners for the same pattern.
//
// Requires packages/combat to be built first (tsc -b), same as scripts/run-ammo-tests.mjs.
//   tools/node/node.exe node_modules/typescript/bin/tsc -b tsconfig.json apps/game/tsconfig.json
//   tools/node/node.exe scripts/run-level-tests.mjs

import { runSelfTest } from "../packages/combat/dist/levelRows.selftest.js";

const code = runSelfTest();
process.exit(code);
