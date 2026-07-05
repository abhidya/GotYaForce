#!/usr/bin/env node
// Runner for packages/combat/src/rom/rom.selfcheck.ts (the ROM-faithful actor runtime
// foundation: physics integrator + cue/command dispatch + G RED family reference port).
// Requires packages/combat to be built first (tsc -b), same as scripts/run-xammo-tests.mjs.

import { runSelfTest } from "../packages/combat/dist/rom/rom.selfcheck.js";

const code = runSelfTest();
process.exit(code);
