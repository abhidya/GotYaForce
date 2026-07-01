#!/usr/bin/env node
// Self-test for the golden-trace harness: synthesize a trajectory with KNOWN constants
// (semi-implicit Euler, same integration order as the sim: v += a, then p += v), run it
// through analyzeGolden(), and assert every fit recovers the truth. Proves the analyzer's
// segmentation/fitting math before any Dolphin capture depends on it.
//
// Usage: node scripts/trace-golden-selftest.mjs   (exit 0 = PASS)

import { analyzeGolden } from "./trace-golden-analyze.mjs";

const TRUTH = { groundY: 10, gravity: 0.42, jumpVelocity: 4.2, maxGroundSpeed: 8.5, accel: 1.2, dashSpeed: 9.6, dashFrames: 10 };

function pad(stickY, buttons = []) {
  return { stickX: 0, stickY, substickX: 0, substickY: 0, triggerL: 0, triggerR: 0, buttons, raw: "" };
}

function synthesize() {
  const records = [];
  let pos = { x: 0, y: TRUTH.groundY, z: 0 };
  let vel = { x: 0, y: 0, z: 0 };
  let f = 0;
  const push = (p) => records.push({ f: f++, pos: { ...pos }, vel: { ...vel }, pad: p, state: 0 });

  const idle = (frames) => {
    for (let i = 0; i < frames; i += 1) {
      vel = { x: 0, y: 0, z: 0 };
      push(pad(0));
    }
  };
  const runForward = (frames) => {
    for (let i = 0; i < frames; i += 1) {
      vel.z = Math.min(TRUTH.maxGroundSpeed, vel.z + TRUTH.accel);
      pos.z += vel.z;
      push(pad(127));
    }
  };
  const jump = () => {
    vel.y = TRUTH.jumpVelocity;
    for (;;) {
      pos.y += vel.y;
      if (pos.y <= TRUTH.groundY) {
        pos.y = TRUTH.groundY;
        vel.y = 0;
        push(pad(0));
        return;
      }
      push(pad(0, ["A"]));
      vel.y -= TRUTH.gravity;
    }
  };
  const dash = () => {
    for (let i = 0; i < TRUTH.dashFrames; i += 1) {
      vel = { x: 0, y: 0, z: TRUTH.dashSpeed };
      pos.z += vel.z;
      push(pad(127, ["X"]));
    }
    vel = { x: 0, y: 0, z: 0 };
  };

  idle(40);
  runForward(60);
  idle(30);
  jump();
  idle(20);
  jump();
  idle(20);
  runForward(40);
  idle(30);
  dash();
  idle(30);
  dash();
  idle(30);
  return records;
}

const result = analyzeGolden(synthesize());
const failures = [];
const expect = (name, actual, truth, tol) => {
  const ok = actual !== null && actual !== undefined && Math.abs(actual - truth) <= tol;
  console.log(`${ok ? "PASS" : "FAIL"}  ${name}: fit=${actual?.toFixed?.(4) ?? actual} truth=${truth} (±${tol})`);
  if (!ok) failures.push(name);
};

expect("groundY", result.groundY, TRUTH.groundY, 0.01);
expect("gravity", result.fits.gravityPerFrame.value, TRUTH.gravity, 0.005);
expect("jumpVelocity", result.fits.jumpVelocity.value, TRUTH.jumpVelocity, 0.05);
expect("maxGroundSpeed", result.fits.maxGroundSpeed.value, TRUTH.maxGroundSpeed, 0.05);
expect("groundAccel", result.fits.groundAccelPerFrame.value, TRUTH.accel, 0.05);
expect("dashCount", result.fits.dashes.length, 2, 0);
if (result.fits.dashes.length) {
  expect("dashSpeed", result.fits.dashes[0].medianSpeed, TRUTH.dashSpeed, 0.05);
  expect("dashFrames", result.fits.dashes[0].durationFrames, TRUTH.dashFrames, 0);
}
expect("velFieldCheck", result.checks.velFieldVsDerived?.meanAbsDiffY ?? null, 0, 0.001);

if (failures.length) {
  console.error(`\nSELF-TEST FAILED: ${failures.join(", ")}`);
  process.exit(1);
}
console.log("\nSELF-TEST PASSED — analyzer recovers all synthetic constants.");
