// Self-test for the X-attack ammo wiring (behavior-notes.md (ao), the official NA instruction
// manual, CONFIRMED_MANUAL tier): "Separate B and X ammo counters are OFFICIAL — weapon 0 =
// B-attack ammo, weapon 1 = X-attack ammo. The port's X/special should consume weapon cell 1."
//
// Deliberately separate from selfcheck.ts (another agent may be editing that file concurrently)
// — own entry point, own runner (scripts/run-xammo-tests.mjs), mirroring the
// healing.selftest.ts / burst.selftest.ts precedent. Does not import or modify selfcheck.ts.
//
// Confidence labels used here:
//   - B/X -> weapon-cell binding: CONFIRMED_MANUAL (ao).
//   - Per-borg weapon-1 data (which borgs have X-ammo, the counts/refill): DERIVED
//     (borgSourceStats.json weaponSlots[1], via weaponOneCellSourceForBorgId).
//   - The cooldown/ammo timing interplay (ammo gate stacked on the existing `special` cooldown):
//     TUNED (the ROM's per-weapon command resolver is unread).
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-xammo-tests.mjs

import { readFileSync } from "node:fs";
import { dirname, resolve as resolvePath } from "node:path";
import { fileURLToPath } from "node:url";

import { stepAmmoRefill, stepAttacks, stepCooldowns } from "./combat.js";
import { weaponOneCellSourceForBorgId } from "./actionProfiles.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import type { BorgRuntime, WeaponCell } from "./types.js";

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

// --- Roster / data loading -------------------------------------------------------------------

const repoRoot = resolvePath(dirname(fileURLToPath(import.meta.url)), "..", "..", "..");
const borgsPath = resolvePath(repoRoot, "packages/assets/data/borgs.json");

function loadStats(id: string): BorgStats {
  const raw = JSON.parse(readFileSync(borgsPath, "utf8")) as { borgs: BorgStats[] };
  const found = raw.borgs.find((b) => b.id === id);
  if (!found) throw new Error(`roster is missing ${id}`);
  return found;
}

// A borg WITH weapon-1 data (X-ammo). pl0000 "NORMAL NINJA" has weaponSlots[1].ammoCount=5
// (borgSourceStats.json), so weaponOneCellSourceForBorgId returns a non-null cell with max 5.
const WITH_XAMMO_ID = "pl0000";
// A borg WITHOUT weapon-1 data. pl0008 "DEATH BORG ALPHA" has no weapon-1 ammo feed, so
// weaponOneCellSourceForBorgId returns null and its cell-1 stays {max:0} (cooldown-only special).
const WITHOUT_XAMMO_ID = "pl0008";

const noEnemies: BorgRuntime[] = [];

/** Weapon cell 1 (X-ammo). Asserts presence — every borg's weaponCells is fully built (length 3)
 *  by stepAmmoRefill/ensureWeaponCells before any test reads it. */
function xcell(b: BorgRuntime): WeaponCell {
  const cells = b.weaponCells;
  if (!cells || !cells[1]) throw new Error("weaponCells[1] not initialized");
  return cells[1];
}

/** Reset a borg to a fresh, ready-to-act state between shots WITHOUT touching its weapon cells,
 *  so we can fire the X-attack repeatedly and observe cell-1 consumption. Clears the `special`
 *  cooldown/`attackLock` (the TUNED cooldown gate that is orthogonal to the ammo gate) and the
 *  press-edge latch so the next press registers as a fresh press. */
function readyForNextX(b: BorgRuntime): void {
  b.state = "idle";
  b.stateTime = 0;
  b.anim = "idle";
  b.cooldowns["special"] = 0;
  b.cooldowns["attackLock"] = 0;
}

// --- Tests -----------------------------------------------------------------------------------

/** (Precondition) The chosen ids actually match the data assumptions this test relies on. */
function testDataPreconditions(): void {
  const withSrc = weaponOneCellSourceForBorgId(WITH_XAMMO_ID);
  assertTrue(!!withSrc && withSrc.max > 0, `${WITH_XAMMO_ID} has weapon-1 data (max>0)`);
  const withoutSrc = weaponOneCellSourceForBorgId(WITHOUT_XAMMO_ID);
  assertEqual(withoutSrc, null, `${WITHOUT_XAMMO_ID} has no weapon-1 data (source is null)`);
}

/** (a) A borg WITH weapon-1 data consumes cell 1 on the X-attack and can't fire at 0. */
function testWithXAmmoConsumesAndGates(): void {
  const stats = loadStats(WITH_XAMMO_ID);
  const p: BorgProfile = buildProfile(stats);
  const profiles = new Map<string, BorgProfile>([["u1", p]]);
  const b = makeBorg({ borgId: WITH_XAMMO_ID });

  // Lazily builds weaponCells from the profile. Cell 1 starts full (spawn-init convention).
  stepAmmoRefill(b, p);
  const cell = xcell(b);
  assertTrue(cell.max > 0, "cell 1 has max>0 (X-ammo present)");
  const startMax = cell.max;
  assertEqual(cell.cur, startMax, "cell 1 starts full");

  // Fire once: cell 1 drops by exactly 1.
  stepAttacks(b, p, false, true, noEnemies, profiles);
  assertEqual(xcell(b).cur, startMax - 1, "X-attack consumes exactly 1 from cell 1");
  assertEqual(b.state, "special", "borg entered the special (X) state after firing");

  // Drain the rest of the magazine, one shot per reset.
  for (let i = startMax - 1; i > 0; i--) {
    readyForNextX(b);
    stepAttacks(b, p, false, true, noEnemies, profiles);
  }
  assertEqual(xcell(b).cur, 0, "cell 1 drains to 0 after firing the full magazine");

  // Now at 0: the X-attack must NOT fire (gated). state stays idle, cell stays 0.
  readyForNextX(b);
  stepAttacks(b, p, false, true, noEnemies, profiles);
  assertEqual(xcell(b).cur, 0, "cell 1 stays 0 (can't go negative)");
  assertEqual(b.state, "idle", "X-attack does NOT fire at 0 X-ammo (state stays idle)");
  assertTrue((b.cooldowns["special"] ?? 0) <= 0, "the special cooldown was not consumed on the blocked shot");
}

/** (b) A borg WITHOUT weapon-1 data is unchanged: X still fires (cooldown-only) and cell 1
 *  stays 0 forever. This is the critical no-regression case. */
function testWithoutXAmmoUnchanged(): void {
  const stats = loadStats(WITHOUT_XAMMO_ID);
  const p: BorgProfile = buildProfile(stats);
  const profiles = new Map<string, BorgProfile>([["u1", p]]);
  const b = makeBorg({ borgId: WITHOUT_XAMMO_ID });

  stepAmmoRefill(b, p);
  const cell = xcell(b);
  assertEqual(cell.max, 0, "cell 1 has max 0 (no X-ammo)");
  assertEqual(cell.cur, 0, "cell 1 cur is 0 (no X-ammo)");

  // Fire many times: the X-attack always works (cooldown-only), and cell 1 never changes.
  for (let i = 0; i < 5; i++) {
    readyForNextX(b);
    const before = { ...xcell(b) };
    stepAttacks(b, p, false, true, noEnemies, profiles);
    assertEqual(b.state, "special", `X-attack fires cooldown-only on shot ${i + 1} (no ammo gate)`);
    assertEqual(xcell(b).cur, before.cur, `cell 1 cur unchanged on shot ${i + 1}`);
    assertEqual(xcell(b).max, 0, `cell 1 max stays 0 on shot ${i + 1}`);
  }
}

/** (c) Cell-1 refill works: after draining, stepAmmoRefill (the SAME path that refills cell 0)
 *  restores cell 1 toward max. */
function testCellOneRefills(): void {
  const stats = loadStats(WITH_XAMMO_ID);
  const p: BorgProfile = buildProfile(stats);
  const profiles = new Map<string, BorgProfile>([["u1", p]]);
  const b = makeBorg({ borgId: WITH_XAMMO_ID });

  stepAmmoRefill(b, p);
  const cell = xcell(b);
  const startMax = cell.max;

  // Drain to 0.
  stepAttacks(b, p, false, true, noEnemies, profiles);
  for (let i = startMax - 1; i > 0; i--) {
    readyForNextX(b);
    stepAttacks(b, p, false, true, noEnemies, profiles);
  }
  assertEqual(xcell(b).cur, 0, "drained cell 1 to 0 before testing refill");

  // Advance frames: cooldowns + refill run together, mirroring the real per-frame loop. The
  // refill grant lives entirely in stepAmmoRefill (all-at-once cells wait out refillParam frames
  // then jump to max; gradual cells accrue fractionally) — either way cur climbs back above 0.
  const refillBudget = Math.max(cell.refillParam, 1) + 60;
  for (let i = 0; i < refillBudget; i++) {
    stepCooldowns(b);
    stepAmmoRefill(b, p);
  }
  assertTrue(xcell(b).cur > 0, "cell 1 refilled above 0 via stepAmmoRefill");
  assertEqual(xcell(b).cur, startMax, "cell 1 refilled back to max");

  // And it can fire again after refilling.
  readyForNextX(b);
  stepAttacks(b, p, false, true, noEnemies, profiles);
  assertEqual(b.state, "special", "X-attack fires again after cell 1 refills");
  assertEqual(xcell(b).cur, startMax - 1, "firing after refill consumes 1 again");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testDataPreconditions();
  testWithXAmmoConsumesAndGates();
  testWithoutXAmmoUnchanged();
  testCellOneRefills();

  if (failures > 0) {
    console.error(`xammo.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`xammo.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
