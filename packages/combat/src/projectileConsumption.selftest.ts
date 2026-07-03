// Self-test for ATK-008 (projectile consumption refactor: persist + rehit interval).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// this is its own entry point with its own runner (scripts/run-projectile-tests.mjs), per the
// commandSchema.selftest.ts precedent (ATK-001/ATK-004). Does not import or modify selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-projectile-tests.mjs
// main()/runSelfTest() return an exit code (0 = pass).

import { stepProjectiles } from "./combat.js";
import { DAMAGE_RECORD_INDEX } from "./gauges.js";
import { JUMP } from "./constants.js";
import type { BorgRuntime, Projectile } from "./types.js";
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

function assertTrue(cond: boolean, label: string): void {
  checks++;
  if (!cond) {
    failures++;
    console.error(`FAIL: ${label}`);
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

// Balance/down gauges set far above anything the SHOT record (hp10/down25/balance25) can
// deplete across these tests, so repeated hits never trigger a stagger/invincibility window
// that would otherwise gate out the re-hits under test (ATK-008 tests only the rehit-counter
// mechanism, not the gauge/stagger model — see gauges.ts).
function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "test",
    team: 1,
    ownerPlayer: null,
    hp: 1_000_000,
    maxHp: 1_000_000,
    pos: { x: 0, y: JUMP.GROUND_Y, z: 0 },
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
    balanceGauge: 1_000_000,
    balanceGaugeMax: 1_000_000,
    downGauge: 1_000_000,
    downGaugeBase: 1_000_000,
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

function makeOwner(): BorgRuntime {
  return makeBorg({ uid: "owner", team: 0 });
}

function makeProjectile(overrides: Partial<Projectile> = {}): Projectile {
  return {
    uid: "proj1",
    ownerUid: "owner",
    team: 0,
    pos: { x: 0, y: JUMP.GROUND_Y, z: 0 },
    vel: { x: 0, y: 0, z: 10 },
    damage: 5,
    hitstun: 0,
    knockback: 0,
    homingTurn: 0,
    homingTarget: null,
    life: 999,
    hitRadius: 30,
    visualKind: "energy",
    damageRecordIndex: DAMAGE_RECORD_INDEX.SHOT,
    ...overrides,
  };
}

// --- Test 1: default consumption (bit-for-bit unchanged) --------------------------------

function testDefaultConsumesOnFirstHit(): void {
  const owner = makeOwner();
  const target = makeBorg({ uid: "t1", team: 1, pos: { x: 0, y: JUMP.GROUND_Y, z: 20 } });
  const all = [owner, target];
  const profiles = new Map<string, BorgProfile>([
    ["owner", makeProfile()],
    ["t1", makeProfile()],
  ]);
  const byUid = new Map(all.map((b) => [b.uid, b]));

  // consumeOnHit absent: default path.
  const proj = makeProjectile({ pos: { x: 0, y: JUMP.GROUND_Y, z: 19 } });
  const survivors = stepProjectiles([proj], all, profiles, byUid);

  assertEqual(survivors.length, 0, "default projectile: consumed (not in survivors) after first hit");
  assertTrue(target.hp < 1_000_000, "default projectile: target took damage on first hit");

  // consumeOnHit explicitly true behaves the same as absent.
  const target2 = makeBorg({ uid: "t2", team: 1, pos: { x: 0, y: JUMP.GROUND_Y, z: 20 } });
  const all2 = [owner, target2];
  const profiles2 = new Map<string, BorgProfile>([
    ["owner", makeProfile()],
    ["t2", makeProfile()],
  ]);
  const byUid2 = new Map(all2.map((b) => [b.uid, b]));
  const proj2 = makeProjectile({ pos: { x: 0, y: JUMP.GROUND_Y, z: 19 }, consumeOnHit: true });
  const survivors2 = stepProjectiles([proj2], all2, profiles2, byUid2);
  assertEqual(survivors2.length, 0, "consumeOnHit:true projectile: consumed after first hit (same as default)");
}

// --- Test 2: persist + interval 0 hits 2 lined-up borgs in one flight -------------------

function testPersistIntervalZeroHitsTwoLinedUpBorgs(): void {
  const owner = makeOwner();
  // Two borgs lined up along +Z, far enough apart that the projectile (speed 10/frame,
  // hitRadius 30) cannot overlap both in the same frame, but flies through both in sequence.
  const near = makeBorg({ uid: "near", team: 1, pos: { x: 0, y: JUMP.GROUND_Y, z: 100 } });
  const far = makeBorg({ uid: "far", team: 1, pos: { x: 0, y: JUMP.GROUND_Y, z: 300 } });
  const all = [owner, near, far];
  const profiles = new Map<string, BorgProfile>([
    ["owner", makeProfile()],
    ["near", makeProfile()],
    ["far", makeProfile()],
  ]);
  const byUid = new Map(all.map((b) => [b.uid, b]));

  let projectiles: Projectile[] = [
    makeProjectile({
      pos: { x: 0, y: JUMP.GROUND_Y, z: 0 },
      vel: { x: 0, y: 0, z: 10 },
      life: 200,
      consumeOnHit: false,
      // rehitIntervalFrames for SHOT record is 0 — persist forever, hit-ready every frame.
    }),
  ];

  const nearHpAfterHits: number[] = [];
  const farHpAfterHits: number[] = [];
  for (let frame = 0; frame < 60 && projectiles.length > 0; frame++) {
    const nearHpBefore = near.hp;
    const farHpBefore = far.hp;
    projectiles = stepProjectiles(projectiles, all, profiles, byUid);
    if (near.hp !== nearHpBefore) nearHpAfterHits.push(frame);
    if (far.hp !== farHpBefore) farHpAfterHits.push(frame);
  }

  assertTrue(nearHpAfterHits.length >= 1, `persist/interval0: near borg was hit at least once (hits at frames ${nearHpAfterHits.join(",")})`);
  assertTrue(farHpAfterHits.length >= 1, `persist/interval0: far borg was hit at least once (hits at frames ${farHpAfterHits.join(",")})`);
  assertTrue(projectiles.length === 1, "persist/interval0: projectile survives both hits (never consumed)");
}

// --- Test 3: persist + interval 10 re-hits the same overlapping target exactly every 10 frames

// All 9 extracted borg-family damage records currently have rehitIntervalFrames=0 (see
// damageRecords.json / attack-mechanics-findings.md mechanic O — per-move nonzero intervals are
// BLOCKED pending T6). ATK-008 tests the counter MECHANISM stepProjectiles implements, so this
// test seeds `rehitCounter` directly on a synthetic projectile the first time it goes hit-ready
// after a hit, standing in for "a damage record whose rehitIntervalFrames is 10" — the ticket's
// own framing ("Synthetic persist projectile with interval 10"). This does not touch any real
// damage-record data and no gameplay caller does this.
function testPersistIntervalTenRehitsSameTargetEveryTenFrames(): void {
  const owner = makeOwner();
  // Target sits exactly on the projectile's spawn position so it overlaps every frame
  // (projectile velocity 0 — "the same overlapping target").
  const target = makeBorg({ uid: "t1", team: 1, pos: { x: 0, y: JUMP.GROUND_Y, z: 0 } });
  const all = [owner, target];
  const profiles = new Map<string, BorgProfile>([
    ["owner", makeProfile()],
    ["t1", makeProfile()],
  ]);
  const byUid = new Map(all.map((b) => [b.uid, b]));

  const REHIT_INTERVAL = 10;
  let projectiles: Projectile[] = [
    makeProjectile({
      pos: { x: 0, y: JUMP.GROUND_Y, z: 0 },
      vel: { x: 0, y: 0, z: 0 },
      life: 200,
      consumeOnHit: false,
      damageRecordIndex: DAMAGE_RECORD_INDEX.SHOT,
    }),
  ];

  const hitFrames: number[] = [];
  let lastHp = target.hp;
  for (let frame = 0; frame < 120 && projectiles.length > 0; frame++) {
    projectiles = stepProjectiles(projectiles, all, profiles, byUid);
    const pr = projectiles[0];
    if (target.hp !== lastHp) {
      hitFrames.push(frame);
      lastHp = target.hp;
      // The production reload (`pr.rehitCounter = record.rehitIntervalFrames`) just ran inside
      // stepProjectiles and set it to 0 (the SHOT record's real interval). Immediately after
      // that reload — i.e. before the next frame's step — stand in for a record with interval
      // 10 by overwriting the counter it just reloaded to.
      if (pr) pr.rehitCounter = REHIT_INTERVAL;
    }
  }

  assertTrue(hitFrames.length >= 4, `interval-10 cadence: at least 4 hits recorded (got ${hitFrames.length}: ${hitFrames.join(",")})`);
  for (let i = 1; i < hitFrames.length; i++) {
    const prevFrame = hitFrames[i - 1];
    const curFrame = hitFrames[i];
    if (prevFrame === undefined || curFrame === undefined) {
      failures++;
      console.error(`FAIL: interval-10 cadence: missing hit-frame entry at index ${i - 1} or ${i}`);
      continue;
    }
    // Hit at frame F reloads the counter to 10 that same frame; the object then only ticks
    // (no hit) for 10 frames and becomes hit-ready again on frame F+11, which is when the next
    // hit test succeeds — matching stepProjectiles' documented "gate the NEXT application"
    // contract (combat.ts stepProjectiles comment block, chunk_0013.c:1175-1182).
    const gap = curFrame - prevFrame;
    assertEqual(
      gap,
      REHIT_INTERVAL + 1,
      `interval-10 cadence: gap between hit ${i - 1} and ${i} is ${REHIT_INTERVAL + 1} frames (hits at ${hitFrames.join(",")})`,
    );
  }
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testDefaultConsumesOnFirstHit();
  testPersistIntervalZeroHitsTwoLinedUpBorgs();
  testPersistIntervalTenRehitsSameTargetEveryTenFrames();

  if (failures > 0) {
    console.error(`projectileConsumption.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`projectileConsumption.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
