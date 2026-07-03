// Self-test for ATK-006 (passive contact-damage scaffold, DISABLED by default).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// own entry point, own runner (scripts/run-contact-damage-tests.mjs), per the
// commandSchema.selftest.ts / burst.selftest.ts precedent. Does not import or modify
// selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-contact-damage-tests.mjs

import { stepContactDamage } from "./combat.js";
import { CONTACT_DAMAGE } from "./constants.js";
import type { BorgRuntime } from "./types.js";

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

/** Flag default is false (the ticket's whole point). */
function testFlagDefaultsDisabled(): void {
  assertEqual(CONTACT_DAMAGE.ENABLED, false, "CONTACT_DAMAGE.ENABLED default is false");
}

/**
 * Two borgs overlapping (same position, opposing teams) for 120 frames take zero damage
 * with the flag off — the ticket's required regression test.
 */
function testOverlap120FramesZeroDamage(): void {
  const a = makeBorg({ uid: "a", team: 0, pos: { x: 0, y: 10, z: 0 } });
  const b = makeBorg({ uid: "b", team: 1, pos: { x: 0, y: 10, z: 0 } });
  const all = [a, b];
  const startHpA = a.hp;
  const startHpB = b.hp;
  for (let i = 0; i < 120; i++) {
    stepContactDamage(a, all);
    stepContactDamage(b, all);
  }
  assertEqual(a.hp, startHpA, "overlapping borg A takes zero contact damage over 120 frames");
  assertEqual(b.hp, startHpB, "overlapping borg B takes zero contact damage over 120 frames");
}

/** stepContactDamage never mutates anything else on the borg while disabled. */
function testNoOtherOutputChanges(): void {
  const a = makeBorg({ uid: "a", hp: 77, state: "idle" });
  const b = makeBorg({ uid: "b", hp: 55 });
  const all = [a, b];
  const before = JSON.stringify(a);
  stepContactDamage(a, all);
  const after = JSON.stringify(a);
  assertEqual(after, before, "stepContactDamage mutates nothing while CONTACT_DAMAGE.ENABLED is false");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testFlagDefaultsDisabled();
  testOverlap120FramesZeroDamage();
  testNoOtherOutputChanges();

  if (failures > 0) {
    console.error(`contactDamage.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`contactDamage.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
