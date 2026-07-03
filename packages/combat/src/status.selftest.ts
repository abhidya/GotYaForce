// Self-test for ATK-010 (status-effect runtime shell). Deliberately separate from selfcheck.ts
// (another agent is concurrently editing that file) — its own entry point with its own runner
// (scripts/run-status-tests.mjs), matching the commandSchema.selftest.ts precedent.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-status-tests.mjs
// main()/runSelfTest() return an exit code (0 = pass).

import { applyStatusFromRecord, stepStatus, STATUS_ID_MASK } from "./status.js";
import { computeSourceDamage } from "./damageFormula.js";
import { damageRecordByIndex, DAMAGE_RECORD_INDEX } from "./gauges.js";
import type { BorgRuntime } from "./types.js";
import type { BorgProfile } from "./stats.js";

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

function makeProfile(overrides: Partial<BorgProfile> = {}): BorgProfile {
  return {
    id: "test",
    name: "Test",
    energy: 1,
    maxHp: 100,
    defense: 0,
    shot: 0,
    attack: 0,
    speed: 5,
    airJumpLevel: 1,
    flyer: false,
    hasShot: true,
    hasMelee: true,
    rangePref: "mixed",
    ...overrides,
  };
}

function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "test",
    team: 0,
    ownerPlayer: "p1",
    hp: 100,
    maxHp: 100,
    pos: { x: 0, y: 0, z: 0 },
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

// --- Required-behavior tests (ATK-010 ticket "Tests to add") ------------------------------

/** Apply status 5 for 60 -> id/timer set; ticks to 0 and clears. */
function testApplyThenTickToZero(): void {
  const b = makeBorg();
  applyStatusFromRecord(b, 5, 60);
  assertEqual(b.statusId, 5, "apply status 5 -> statusId 5");
  assertEqual(b.statusTimer, 60, "apply status 5 for 60 -> statusTimer 60");

  for (let i = 0; i < 60; i++) stepStatus(b);
  assertEqual(b.statusTimer, 0, "60 ticks -> statusTimer 0");
  assertEqual(b.statusId, 0, "statusId clears at 0");
}

/** Max-merge: apply 30 over a running 60 -> stays 60. */
function testMaxMergeNeverShortens(): void {
  const b = makeBorg();
  applyStatusFromRecord(b, 5, 60);
  applyStatusFromRecord(b, 5, 30);
  assertEqual(b.statusTimer, 60, "shorter re-application max-merges, stays 60");

  applyStatusFromRecord(b, 5, 90);
  assertEqual(b.statusTimer, 90, "longer re-application extends to 90");
}

/** Immunity bit 5 set -> application rejected AND (with the formula param wired) damage 0. */
function testImmunityRejectsApplicationAndZeroesDamage(): void {
  const b = makeBorg({ statusImmunityMask: 1 << 5 });
  applyStatusFromRecord(b, 5, 60);
  assertEqual(b.statusId, 0, "immune status id -> rejected, statusId stays 0");
  assertEqual(b.statusTimer, 0, "immune status id -> rejected, statusTimer stays 0");

  const attacker = makeBorg({ uid: "atk" });
  const attackerProfile = makeProfile();
  const victimProfile = makeProfile();
  const record = damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE);
  const dmgNormal = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: b,
    victimProfile,
    record,
  });
  assertEqual(dmgNormal > 0, true, "sanity: normal hit deals nonzero damage without the immune flag");

  const dmgImmune = computeSourceDamage({
    attacker,
    attackerProfile,
    victim: b,
    victimProfile,
    record,
    victimStatusImmune: true,
  });
  assertEqual(dmgImmune, 0, "victimStatusImmune=true -> formula step 1 zeroes damage");
}

/** Mask: id 0x45 -> stored as 0x05. */
function testIdIsMaskedTo6Bits(): void {
  const b = makeBorg();
  assertEqual(STATUS_ID_MASK, 0x3f, "STATUS_ID_MASK is 0x3f");
  applyStatusFromRecord(b, 0x45, 10);
  assertEqual(b.statusId, 0x05, "0x45 & 0x3f -> stored as 0x05");
}

/** statusId 0 is always a no-op (this ticket's fallback: no statuses fire). */
function testStatusZeroIsNoop(): void {
  const b = makeBorg();
  applyStatusFromRecord(b, 0, 60);
  assertEqual(b.statusId, 0, "statusId 0 -> no-op, id stays 0");
  assertEqual(b.statusTimer, 0, "statusId 0 -> no-op, timer stays 0");
}

/** stepStatus on an already-cleared status is a harmless no-op. */
function testStepStatusOnClearedIsNoop(): void {
  const b = makeBorg();
  stepStatus(b);
  assertEqual(b.statusId, 0, "stepStatus on cleared status -> id stays 0");
  assertEqual(b.statusTimer, 0, "stepStatus on cleared status -> timer stays 0");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testApplyThenTickToZero();
  testMaxMergeNeverShortens();
  testImmunityRejectsApplicationAndZeroesDamage();
  testIdIsMaskedTo6Bits();
  testStatusZeroIsNoop();
  testStepStatusOnClearedIsNoop();

  if (failures > 0) {
    console.error(`status.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`status.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
