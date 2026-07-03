#!/usr/bin/env node
// Runner for packages/combat/src/moveProperties.selftest.ts (OBSERVED_WIKI per-move dataset).
// Requires packages/combat to be built first (tsc -b).
import { runSelfTest } from "../packages/combat/dist/moveProperties.selftest.js";

const code = runSelfTest();
process.exit(code);
