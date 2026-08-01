#!/usr/bin/env node
// Runner for packages/render/src/camera/sourceCamera.ts runSourceCameraSelfTests.
// Verifies the GG4E source camera port: applyFrame interpolation + setupView matrix +
// boot view-setup + step-driver countdown + end-frame getter.
//
// Requires packages/render to be built first:
//   pnpm --filter @gf/render run build
//   node scripts/run-source-camera-tests.mjs

import { runSourceCameraSelfTests } from "../packages/render/dist/camera/sourceCamera.js";
import assert from "node:assert";

let failures = 0;
try {
  runSourceCameraSelfTests((cond, msg) => assert(cond, msg));
  console.log("sourceCamera.selftest: all checks passed");
} catch (err) {
  failures = 1;
  console.error("sourceCamera.selftest: FAILED —", err.message);
  console.error(err);
}

process.exit(failures);
