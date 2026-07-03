#!/usr/bin/env node
// Runner for packages/combat/src/battleJudge.selftest.ts (winner-mask battle judge, (ae)).
// Separate entry point from selfcheck.ts by design (see the selftest header).
//
// Requires packages/combat built first (tsc -b):
//   tools/node/node.exe node_modules/typescript/bin/tsc -b tsconfig.json apps/game/tsconfig.json
//   tools/node/node.exe scripts/run-judge-tests.mjs

import { runSelfTest } from "../packages/combat/dist/battleJudge.selftest.js";

const code = runSelfTest();
process.exit(code);
