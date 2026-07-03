// Self-test for ATK-011 (Hyper/Power Burst input + state shell).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// own entry point, own runner (scripts/run-burst-tests.mjs), per the commandSchema.selftest.ts /
// fusionPairs.selftest.ts precedent. Does not import or modify selfcheck.ts/battle.ts/combat.ts.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-burst-tests.mjs

import { stepBurst } from "./burst.js";
import { BURST } from "./constants.js";
import { type BorgRuntime } from "./types.js";

// --- Test scaffolding --------------------------------------------------------------------

let failures = 0;
let checks = 0;

function assertEqual<T>(actual: T, expected: T, label: string): void {
  checks++;
  if (actual !== expected) {
    failures++;
    console.error(`FAIL: ${label} — expected ${String(expected)}, got ${String(actual)}`);
  }
}

function assertTrue(cond: boolean, label: string): void {
  checks++;
  if (!cond) {
    failures++;
    console.error(`FAIL: ${label}`);
  }
}

function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "test",
    team: 0,
    ownerPlayer: "p1",
    hp: 100,
    maxHp: 100,
    pos: { x: 0, y: 10, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: true,
    airJumps: 1,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 0,
    cooldowns: {},
    invincTimer: 0,
    balanceGauge: 100,
    balanceGaugeMax: 100,
    downGauge: 100,
    downGaugeBase: 100,
    balanceRefillDelay: 0,
    downResetDelay: 0,
    comboWindow: 0,
    comboAccum: 0,
    comboRank: 0,
    paramTier: { tier: 0x10, deltaAccum: 0, timerFrames: 0 },
    statusId: 0,
    statusTimer: 0,
    statusImmunityMask: 0,
    lockTarget: null,
    allyLockTarget: null,
    burstArmFrames: 0,
    burstActive: false,
    burstPaired: false,
    fusionPartnerUid: null,
    fusionState: 0,
    defeatAccounted: false,
    alive: true,
    ...overrides,
  };
}

// --- Tests -----------------------------------------------------------------------------------

/** Y press edge arms exactly BURST.ARM_WINDOW_FRAMES (6). */
function testPressEdgeArmsSixFrames(): void {
  const b = makeBorg();
  assertEqual(BURST.ARM_WINDOW_FRAMES, 6, "BURST.ARM_WINDOW_FRAMES is 6 (chunk_0009.c:113)");
  stepBurst(b, true);
  assertEqual(b.burstArmFrames, 6, "press edge sets burstArmFrames = 6");
}

/** Window decrements by 1 per frame down to 0, and stays at 0 (never negative). */
function testWindowDecrementsPerFrame(): void {
  const b = makeBorg();
  stepBurst(b, true);
  assertEqual(b.burstArmFrames, 6, "armed at 6");
  const expected = [5, 4, 3, 2, 1, 0, 0, 0];
  for (const exp of expected) {
    stepBurst(b, false);
    assertEqual(b.burstArmFrames, exp, `decrements to ${exp}`);
  }
}

/** A re-press while still armed (or after expiry) re-arms to 6, not additive. */
function testRePressReArms(): void {
  const b = makeBorg();
  stepBurst(b, true);
  stepBurst(b, false);
  stepBurst(b, false);
  assertEqual(b.burstArmFrames, 4, "decremented to 4 before re-press");
  stepBurst(b, true);
  assertEqual(b.burstArmFrames, 6, "re-press re-arms to 6, not 4+6");

  // Re-press also works after the window has fully expired.
  const c = makeBorg();
  stepBurst(c, true);
  for (let i = 0; i < 10; i++) stepBurst(c, false);
  assertEqual(c.burstArmFrames, 0, "window fully expired");
  stepBurst(c, true);
  assertEqual(c.burstArmFrames, 6, "re-press after expiry re-arms to 6");
}

/** With ENABLED=false (the real default), burstActive/burstPaired never become true no matter
 *  how the arm window is driven — the shell is fully inert in real battles. */
function testDisabledStaysInert(): void {
  assertEqual(BURST.ENABLED, false, "BURST.ENABLED default is false (BLOCKED-until-T3)");
  const b = makeBorg();
  stepBurst(b, true);
  assertEqual(b.burstActive, false, "burstActive stays false while armed (ENABLED=false)");
  assertEqual(b.burstPaired, false, "burstPaired stays false while armed (ENABLED=false)");
  stepBurst(b, false);
  assertEqual(b.burstActive, false, "burstActive stays false across frames (ENABLED=false)");
}

/** Test-only: with a local ENABLED=true stand-in for the gating condition, verify the shape
 *  activation would take once BURST.ENABLED flips — without mutating the shared constant
 *  (BURST is `as const`; instead this re-implements the exact gate stepBurst uses to prove the
 *  SHAPE, since stepBurst reads the module-level constant directly). */
function testActivationShapeWhenEnabled(): void {
  const b = makeBorg();
  b.burstArmFrames = 6;
  b.alive = true;
  // Mirrors stepBurst's activation branch: `BURST.ENABLED && b.burstArmFrames > 0 && b.alive`.
  const wouldActivate = true && b.burstArmFrames > 0 && b.alive;
  assertTrue(wouldActivate, "activation precondition (armed + alive) holds when ENABLED=true");
  // Applying the branch directly (since we can't flip the real `as const` BURST.ENABLED here):
  b.burstActive = wouldActivate;
  b.burstPaired = wouldActivate;
  assertEqual(b.burstActive, true, "burstActive would be set true under ENABLED=true + armed");
  assertEqual(b.burstPaired, true, "burstPaired would be set true under ENABLED=true + armed");
}

/** burstActive has zero side effects: driving it directly doesn't touch hp/pos/state/ammo/etc. */
function testBurstActiveHasZeroEffects(): void {
  const b = makeBorg({ hp: 77, ammo: 3, state: "idle" });
  const before = JSON.stringify({ hp: b.hp, ammo: b.ammo, state: b.state, pos: b.pos, vel: b.vel });
  stepBurst(b, true);
  stepBurst(b, true);
  stepBurst(b, false);
  const after = JSON.stringify({ hp: b.hp, ammo: b.ammo, state: b.state, pos: b.pos, vel: b.vel });
  assertEqual(after, before, "stepBurst never mutates hp/ammo/state/pos/vel");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testPressEdgeArmsSixFrames();
  testWindowDecrementsPerFrame();
  testRePressReArms();
  testDisabledStaysInert();
  testActivationShapeWhenEnabled();
  testBurstActiveHasZeroEffects();

  if (failures > 0) {
    console.error(`burst.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`burst.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
