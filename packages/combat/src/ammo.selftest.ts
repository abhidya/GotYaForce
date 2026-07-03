// Self-test for ATK-009 (ROM-shaped ammo/refill model — weapon cells + refill types).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// this is its own entry point with its own runner (scripts/run-ammo-tests.mjs), following the
// same pattern as commandSchema.selftest.ts (ATK-001/ATK-004). Does not import or modify
// selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-ammo-tests.mjs
// main()/runSelfTest() return an exit code (0 = pass).

import { grantAmmo, stepAmmoRefill } from "./combat.js";
import { AMMO, SHOT } from "./constants.js";
import {
  actionProfileForProfile,
  startingAmmoForProfile,
  weaponOneCellSourceForBorgId,
} from "./actionProfiles.js";
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

function assertTrue(cond: boolean, label: string): void {
  checks++;
  if (!cond) {
    failures++;
    console.error(`FAIL: ${label}`);
  }
}

function makeProfile(overrides: Partial<BorgProfile> = {}): BorgProfile {
  return {
    id: "zzammo_generic",
    name: "Test",
    energy: 1,
    maxHp: 100,
    defense: 0,
    shot: 5,
    attack: 0,
    speed: 5,
    airJumpLevel: 1,
    flyer: false,
    hasShot: true,
    hasMelee: false,
    rangePref: "ranged",
    ...overrides,
  };
}

function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "zzammo_generic",
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

// --- G RED live-verified anchor (ATK-009 required behavior) ------------------------------

function testGRedAnchorAmmoFive(): void {
  // research/decomp/data/borg-hp-stat-rows-802f2988.json / borgSourceStats.json: G RED
  // (pl0615) weapon-0 ammoCount == 5, live-verified against the captured HUD value
  // (behavior-notes.md ag). This is the ticket's mandated anchor.
  const gRed = makeProfile({ id: "pl0615", hasMelee: true, hasShot: true, rangePref: "mixed" });
  const shot = actionProfileForProfile(gRed).shot;
  assertTrue(shot !== null, "G RED resolves a shot action def");
  assertEqual(shot?.ammoMax, 5, "G RED (pl0615) ammoMax === 5 (live-verified anchor)");
  assertEqual(startingAmmoForProfile(gRed), 5, "startingAmmoForProfile(pl0615) === 5");
  // G RED's weapon-0 is all-at-once (refillType 0), param 180 — behavior-notes.md (am)
  // cross-check row [200, 5,5, 0,180, 0,0, 1,180].
  assertEqual(shot?.refillType, 0, "G RED weapon-0 refillType === 0 (all-at-once, (am) cross-check)");
  assertEqual(shot?.refillParam, 180, "G RED weapon-0 refillParam === 180 ((am) cross-check)");
}

// --- behavior-notes.md (am) cross-checked row anchors (weapon-0 AND weapon-1) --------------

function testFlameDragonGradualAnchor(): void {
  // FLAME DRAGON (pl0500) row [1000, 5,5, 1,300, 1,1, 1,300] (am): weapon-0 ammo 5 gradual
  // (type 1, param 300), weapon-1 ammo 1 gradual (type 1, param 300) — guide "B ammo 5 / X
  // ammo 1", both gradual.
  const dragon = makeProfile({ id: "pl0500", hasMelee: true, hasShot: true, rangePref: "mixed" });
  const shot = actionProfileForProfile(dragon).shot;
  assertTrue(shot !== null, "Flame Dragon resolves a shot action def");
  assertEqual(shot?.ammoMax, 5, "Flame Dragon (pl0500) weapon-0 ammoMax === 5 ((am) cross-check)");
  assertEqual(shot?.refillType, 1, "Flame Dragon weapon-0 refillType === 1 (gradual, (am) cross-check)");
  assertEqual(shot?.refillParam, 300, "Flame Dragon weapon-0 refillParam === 300 ((am) cross-check)");

  const weapon1 = weaponOneCellSourceForBorgId("pl0500");
  assertTrue(weapon1 !== null, "Flame Dragon resolves a weapon-1 cell source");
  assertEqual(weapon1?.max, 1, "Flame Dragon weapon-1 max === 1 ((am) cross-check, guide 'X ammo 1')");
  assertEqual(weapon1?.refillType, 1, "Flame Dragon weapon-1 refillType === 1 (gradual, (am) cross-check)");
  assertEqual(weapon1?.refillParam, 300, "Flame Dragon weapon-1 refillParam === 300 ((am) cross-check)");
}

function testCyberDeathDragonWeaponOneAnchor(): void {
  // CYBER DEATH DRAGON (pl0503) row [2500, 5,5, 0,300, 8,8, 0,300] (am): guide "X ammo 8".
  const weapon1 = weaponOneCellSourceForBorgId("pl0503");
  assertTrue(weapon1 !== null, "Cyber Death Dragon resolves a weapon-1 cell source");
  assertEqual(weapon1?.max, 8, "Cyber Death Dragon weapon-1 max === 8 ((am) cross-check, guide 'X ammo 8')");
  assertEqual(weapon1?.refillType, 0, "Cyber Death Dragon weapon-1 refillType === 0 (all-at-once, (am) cross-check)");
}

function testDeathHeadWeaponZeroAnchor(): void {
  // DEATH HEAD (pl0505) row [500, 10,10, 0,180, 1,1, 0,180] (am): guide's level-glitch lore
  // says 10 B ammo.
  const deathHead = makeProfile({ id: "pl0505", hasMelee: true, hasShot: true, rangePref: "mixed" });
  const shot = actionProfileForProfile(deathHead).shot;
  assertEqual(shot?.ammoMax, 10, "Death Head (pl0505) weapon-0 ammoMax === 10 ((am) cross-check, guide's 10 B ammo lore)");
}

// --- Gradual refill ------------------------------------------------------------------------

function testGradualRefillStepwise(): void {
  const p = makeProfile({ id: "zzammo_gradual" });
  // Force a small, fast-to-observe magazine + gradual refill type so the test doesn't need
  // hundreds of frames.
  const b = makeBorg({ ammo: 3 });
  b.weaponCells = [
    { cur: 0, max: 3, refillType: 1, refillParam: 1, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
  ];
  b.ammo = 0;

  assertEqual(b.ammo, 0, "gradual borg starts empty (fired to empty)");

  // Step until cur first reaches >= 1 — firing should be allowed as soon as this happens,
  // not gated behind a full-magazine wait (AMMO.REFILL_RATE_PER_FRAME per frame).
  let framesToFirstShot = -1;
  for (let f = 0; f < 200; f++) {
    stepAmmoRefill(b, p);
    if (b.weaponCells[0]!.cur >= 1) {
      framesToFirstShot = f;
      break;
    }
  }
  assertTrue(framesToFirstShot >= 0, "gradual borg's cur reaches >= 1 within 200 frames");
  assertTrue(
    framesToFirstShot <= Math.ceil(1 / AMMO.REFILL_RATE_PER_FRAME) + 1,
    `gradual borg reaches cur>=1 within ~1/rate frames (got ${framesToFirstShot})`,
  );

  // Continue stepping: cur should climb monotonically toward max without ever exceeding it,
  // and without ever jumping straight to max in one frame (that's the all-at-once shape).
  let prevCur = b.weaponCells[0]!.cur;
  let sawIntermediateStep = false;
  for (let f = 0; f < 200; f++) {
    stepAmmoRefill(b, p);
    const cur = b.weaponCells[0]!.cur;
    assertTrue(cur >= prevCur, `gradual cur is monotonically non-decreasing (frame ${f})`);
    assertTrue(cur <= 3, `gradual cur never exceeds max (frame ${f}, cur=${cur})`);
    if (cur > prevCur && cur < 3) sawIntermediateStep = true;
    prevCur = cur;
    if (cur >= 3) break;
  }
  assertTrue(sawIntermediateStep, "gradual refill passes through an intermediate (non-0, non-max) value");
  assertEqual(b.weaponCells[0]!.cur, 3, "gradual borg eventually reaches max");
}

// --- All-at-once refill --------------------------------------------------------------------

function testAllAtOnceStaysEmptyThenJumps(): void {
  const p = makeProfile({ id: "zzammo_allatonce" });
  const b = makeBorg({ ammo: 0 });
  const TIMER_FRAMES = 10;
  b.weaponCells = [
    { cur: 0, max: 4, refillType: 0, refillParam: TIMER_FRAMES, timer: TIMER_FRAMES },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
  ];

  for (let f = 0; f < TIMER_FRAMES - 1; f++) {
    stepAmmoRefill(b, p);
    assertEqual(b.weaponCells[0]!.cur, 0, `all-at-once cur stays 0 while timer runs (frame ${f})`);
  }
  // One more frame expires the timer -> jump straight to max.
  stepAmmoRefill(b, p);
  assertEqual(b.weaponCells[0]!.cur, 4, "all-at-once cur jumps straight to max on timer expiry");
  assertEqual(b.ammo, 4, "b.ammo mirrors the post-jump weapon-0 cur");
}

// --- Infinite ammo (max === 0) --------------------------------------------------------------

function testInfiniteAmmoNeverBlocked(): void {
  const p = makeProfile({ id: "zzammo_infinite" });
  const b = makeBorg({ ammo: 0 });
  b.weaponCells = [
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
  ];

  for (let i = 0; i < 1000; i++) {
    stepAmmoRefill(b, p);
    assertTrue(b.ammo > 0, `infinite borg's fire-gate alias stays > 0 (iteration ${i})`);
    assertEqual(b.weaponCells[0]!.max, 0, `infinite cell's max stays 0 (iteration ${i})`);
    assertEqual(b.weaponCells[0]!.cur, 0, `infinite cell's cur is never decremented below 0 (iteration ${i})`);
  }
  assertEqual(b.ammo, Number.POSITIVE_INFINITY, "infinite borg's b.ammo alias reads as Infinity");
}

function testInfiniteAmmoNeverBlockedAcrossFireCycles(): void {
  // Interleave "firing" (the fire-gate check every real caller uses: `b.ammo > 0`) with
  // stepAmmoRefill across 1000 shot attempts for an infinite (max 0) weapon-0, matching
  // startShotAttack's own early-return-on-infinite shape (combat.ts: `cell.max > 0` guards
  // the decrement) without needing to export the private function.
  const p = makeProfile({ id: "zzammo_infinite_fire", hasMelee: false });
  const b = makeBorg({ ammo: 0 });
  b.weaponCells = [
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
  ];

  let blockedShots = 0;
  for (let i = 0; i < 1000; i++) {
    stepAmmoRefill(b, p);
    if (!(b.ammo > 0)) {
      blockedShots++;
      continue;
    }
    // Simulate startShotAttack's own guard: max<=0 cells are never decremented.
    const cell = b.weaponCells[0]!;
    if (cell.max > 0) cell.cur = Math.max(0, cell.cur - 1);
  }
  assertEqual(blockedShots, 0, "infinite borg is never gate-blocked across 1000 fire attempts");
}

// --- grantAmmo clamps at max -----------------------------------------------------------------

function testGrantAmmoClampsAtMax(): void {
  const p = makeProfile({ id: "zzammo_grant" });
  const b = makeBorg({ ammo: 2 });
  b.weaponCells = [
    { cur: 2, max: 3, refillType: 0, refillParam: 10, timer: 10 },
    { cur: 0, max: 5, refillType: 1, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
  ];

  grantAmmo(b, 0, p);
  assertEqual(b.weaponCells[0]!.cur, 3, "grantAmmo(+1) on weapon 0 below max increments cur");
  assertEqual(b.ammo, 3, "grantAmmo on weapon 0 mirrors into b.ammo");

  grantAmmo(b, 0, p);
  assertEqual(b.weaponCells[0]!.cur, 3, "grantAmmo(+1) on weapon 0 at max clamps (no overflow)");
  assertEqual(b.ammo, 3, "b.ammo stays clamped too");

  // Weapon-1 cell: grantAmmo should work identically (nothing calls it in gameplay yet, but
  // the exposed helper must behave correctly for any weaponIdx per the ticket).
  grantAmmo(b, 1, p);
  assertEqual(b.weaponCells[1]!.cur, 1, "grantAmmo(+1) on weapon 1 increments its own cur");
  assertEqual(b.ammo, 3, "grantAmmo on weapon 1 does not touch the weapon-0 b.ammo alias");

  // Infinite cell (max 0): grantAmmo is a no-op (nothing to grant toward).
  grantAmmo(b, 2, p);
  assertEqual(b.weaponCells[2]!.cur, 0, "grantAmmo on an infinite (max 0) cell is a no-op");
}

// --- Regression: default borg shots-per-minute stays in the pre-change envelope ------------

function testDefaultBorgShotsPerMinuteEnvelope(): void {
  // Pre-ATK-009 baseline (ATK-002-era model): AMMO_MAX shots at FIRE_COOLDOWN spacing, then an
  // instant refill after RELOAD_FRAMES once empty. Reproduce that cadence as the reference.
  const magSize = SHOT.AMMO_MAX;
  const fireCooldown = SHOT.FIRE_COOLDOWN;
  const reloadFrames = SHOT.RELOAD_FRAMES;
  const cycleFramesBaseline = magSize * fireCooldown + reloadFrames;
  const baselineShotsPerMinute = (magSize * 60 * 60) / cycleFramesBaseline;

  // New model: an all-at-once default-fallback borg (actionProfiles.ts DEFAULT_SHOT — no
  // stat-row override) with AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES seeded from RELOAD_FRAMES.
  const p = makeProfile({ id: "zzammo_envelope_default" });
  const shotDef = actionProfileForProfile(p).shot;
  assertTrue(shotDef !== null, "default-fallback profile resolves a shot def");
  if (!shotDef) return;
  assertEqual(shotDef.refillType, 0, "default-fallback shot def is all-at-once (TUNED_EXISTING)");
  assertEqual(
    shotDef.refillParam,
    AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES,
    "default-fallback refillParam derives from RELOAD_FRAMES",
  );

  const b = makeBorg({ ammo: shotDef.ammoMax });
  let framesUntilFull = 0;
  // Empty the magazine instantly (equivalent to "fired to 0") and time the all-at-once refill.
  b.weaponCells = [
    { cur: 0, max: shotDef.ammoMax, refillType: shotDef.refillType, refillParam: shotDef.refillParam, timer: shotDef.refillParam },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
    { cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 },
  ];
  for (let f = 0; f < 10_000; f++) {
    stepAmmoRefill(b, p);
    framesUntilFull++;
    if (b.weaponCells[0]!.cur >= shotDef.ammoMax) break;
  }
  const cycleFramesNew = shotDef.ammoMax * fireCooldown + framesUntilFull;
  const newShotsPerMinute = (shotDef.ammoMax * 60 * 60) / cycleFramesNew;

  // "Stays within the pre-change envelope": allow generous slack (2x either direction) since
  // the exact ROM rate is still TUNED (Q7); the intent is no order-of-magnitude regression.
  assertTrue(
    newShotsPerMinute >= baselineShotsPerMinute / 2 && newShotsPerMinute <= baselineShotsPerMinute * 2,
    `default borg shots/min (${newShotsPerMinute.toFixed(1)}) stays within 2x of the ATK-002 baseline (${baselineShotsPerMinute.toFixed(1)})`,
  );
}

// --- Compat: b.ammo alias stays readable/writable for existing callers ---------------------

function testAmmoAliasCompat(): void {
  const p = makeProfile({ id: "zzammo_compat" });
  const b = makeBorg({ ammo: 4 });
  // A caller that only knows about `b.ammo` (no weaponCells) must keep working: stepAmmoRefill
  // self-heals weaponCells from the existing `b.ammo` value on first call.
  assertEqual(b.weaponCells, undefined, "fresh borg has no weaponCells until first ammo helper call");
  stepAmmoRefill(b, p);
  assertTrue(Array.isArray(b.weaponCells), "stepAmmoRefill lazily initializes weaponCells");
  assertEqual(b.weaponCells?.length, 3, "weaponCells has exactly 3 entries (ROM models 3 cells)");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testGRedAnchorAmmoFive();
  testFlameDragonGradualAnchor();
  testCyberDeathDragonWeaponOneAnchor();
  testDeathHeadWeaponZeroAnchor();
  testGradualRefillStepwise();
  testAllAtOnceStaysEmptyThenJumps();
  testInfiniteAmmoNeverBlocked();
  testInfiniteAmmoNeverBlockedAcrossFireCycles();
  testGrantAmmoClampsAtMax();
  testDefaultBorgShotsPerMinuteEnvelope();
  testAmmoAliasCompat();

  if (failures > 0) {
    console.error(`ammo.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`ammo.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
