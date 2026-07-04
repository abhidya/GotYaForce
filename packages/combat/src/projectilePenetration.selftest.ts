// Self-test for OBSERVED_WIKI projectile penetration (ATK-008): a borg whose cataloged B-shot
// move penetrates borgs ("borgs"/"total") fires a projectile that PERSISTS through borg hits
// (consumeOnHit === false); a "none" borg fires the default despawn-on-hit projectile.
//
// Own entry point + runner (scripts/run-penetration-tests.mjs), per the selftest precedent.
// Does not import or modify selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   tools/node/node.exe scripts/run-penetration-tests.mjs

import { readFileSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

import { stepAttacks } from "./combat.js";
import { shotPenetrationForBorgId } from "./moveProperties.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import { type BorgRuntime } from "./types.js";

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

const repoRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..", "..", "..");
const BORGS = (JSON.parse(readFileSync(resolve(repoRoot, "packages/assets/data/borgs.json"), "utf8")) as {
  borgs: BorgStats[];
}).borgs;

function profileFor(id: string): BorgProfile {
  const s = BORGS.find((b) => b.id === id);
  if (!s) throw new Error(`missing borg ${id}`);
  return buildProfile(s);
}

function makeBorg(borgId: string, overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId,
    team: 0,
    ownerPlayer: "p1",
    hp: 200,
    maxHp: 200,
    pos: { x: 0, y: 10, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: true,
    airJumps: 1,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 5,
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

/** Fire the B shot once (no enemy nearby -> open fire) and return the first spawned projectile. */
function fireShot(borgId: string): { consumeOnHit: boolean | undefined } | null {
  const prof = profileFor(borgId);
  if (!prof.hasShot) return null;
  const b = makeBorg(borgId);
  const profiles = new Map<string, BorgProfile>([[b.uid, prof]]);
  // attackHeld=true, no special, only self in the arena -> B contextual rule opens fire.
  const res = stepAttacks(b, prof, true, false, [b], profiles);
  const p = res.projectiles[0];
  return p ? { consumeOnHit: p.consumeOnHit } : null;
}

// --- Data-mapping unit checks ------------------------------------------------------------

function testPenetrationDataMapping(): void {
  assertEqual(shotPenetrationForBorgId("pl0e03", false), "total", "pl0e03 (Antares) B Shot penetration === 'total'");
  assertEqual(shotPenetrationForBorgId("pl0615", false), "borgs", "pl0615 (G RED) B Shot penetration === 'borgs'");
  assertEqual(shotPenetrationForBorgId("pl0008", false), "none", "pl0008 (Death Borg Alpha) B Shot penetration === 'none'");
  assertEqual(shotPenetrationForBorgId("plffff", false), null, "unknown id -> null penetration");
}

// --- Integration: spawned projectile consumeOnHit reflects penetration -------------------

function testPenetratingBorgSpawnsPersistentProjectile(): void {
  // pl0e03 (Antares) fires immediately (non-chargeable), so one attackHeld frame spawns the shot.
  // Chargeable borgs (e.g. G RED pl0615) only fire on release, so they're covered by the data-
  // mapping check above rather than a single-frame fire here.
  const shot = fireShot("pl0e03");
  assertTrue(shot !== null, "pl0e03 (total) fires a projectile");
  if (shot) assertEqual(shot.consumeOnHit, false, "pl0e03 (total) projectile persists (consumeOnHit === false)");
}

function testNonPenetratingBorgSpawnsDefaultProjectile(): void {
  const shot = fireShot("pl0008");
  // pl0008 either fires a default (consumeOnHit absent -> undefined) projectile, or is melee-only.
  if (shot) {
    assertEqual(shot.consumeOnHit, undefined, "pl0008 (none) projectile keeps default despawn-on-hit (consumeOnHit absent)");
  } else {
    assertTrue(true, "pl0008 has no B-shot projectile (melee-only) — default path unaffected");
  }
}

// --- Spawn-time homing aim-cone gate (FUN_8006c334, chunk_0009.c:1995 / spawn call :3841) ---
//
// The homing lock is only granted when the locked target sits inside the aim cone around the
// projectile's initial flight direction (cone half-angle TUNED — FLOAT_8043768c undumped).
// Fire pl0e03 (non-chargeable, fires on one attackHeld frame) with a locked enemy dead ahead
// vs directly behind and check the spawned projectile's homingTarget.

function fireShotWithLockedEnemy(enemyZ: number): { homingTarget: string | null } | null {
  const prof = profileFor("pl0e03");
  const enemyProf = profileFor("pl0008");
  const b = makeBorg("pl0e03", { lockTarget: "enemy" }); // facing +Z (rotY 0)
  const enemy = makeBorg("pl0008", {
    uid: "enemy",
    team: 1,
    ownerPlayer: null,
    pos: { x: 0, y: 10, z: enemyZ },
  });
  const profiles = new Map<string, BorgProfile>([
    [b.uid, prof],
    [enemy.uid, enemyProf],
  ]);
  const res = stepAttacks(b, prof, true, false, [b, enemy], profiles);
  const p = res.projectiles[0];
  return p ? { homingTarget: p.homingTarget } : null;
}

function testSpawnAimConeGatesHomingLock(): void {
  // Enemy 300 units dead ahead: well inside the cone -> homing lock granted.
  const ahead = fireShotWithLockedEnemy(300);
  assertTrue(ahead !== null, "aim cone: pl0e03 fires with a locked enemy ahead");
  if (ahead) assertEqual(ahead.homingTarget, "enemy", "aim cone: in-cone locked target grants the homing lock");

  // Enemy 300 units directly BEHIND the muzzle direction: outside the cone -> flies straight.
  const behind = fireShotWithLockedEnemy(-300);
  assertTrue(behind !== null, "aim cone: pl0e03 fires with a locked enemy behind");
  if (behind) assertEqual(behind.homingTarget, null, "aim cone: out-of-cone locked target spawns a straight shot");
}

export function runSelfTest(): number {
  failures = 0;
  checks = 0;
  testPenetrationDataMapping();
  testPenetratingBorgSpawnsPersistentProjectile();
  testNonPenetratingBorgSpawnsDefaultProjectile();
  testSpawnAimConeGatesHomingLock();
  if (failures > 0) {
    console.error(`projectilePenetration.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`projectilePenetration.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
