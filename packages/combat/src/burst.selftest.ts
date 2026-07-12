// Self-test for ATK-011/012 (Hyper/Power Burst input, activation, drain, speed effect) and
// the per-player Power Burst METER (Q4 RESOLVED 2026-07-03 — fill/clamp/charged-delay,
// see burst.ts).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// own entry point, own runner (scripts/run-burst-tests.mjs), per the commandSchema.selftest.ts /
// fusionPairs.selftest.ts precedent. Does not import or modify selfcheck.ts/battle.ts (the
// meter tests exercise combat.ts applyHit read-only via import).
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-burst-tests.mjs

import {
  canActivateBurst,
  createBurstMeter,
  creditBurstFill,
  stepActiveBurst,
  stepBurst,
  sweepBurstCharged,
  tryActivateBurst,
} from "./burst.js";
import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { applyHit } from "./combat.js";
import { BURST } from "./constants.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex } from "./gauges.js";
import { stepMovement } from "./movement.js";
import type { BorgProfile, BorgStats } from "./stats.js";
import { emptyInput, type BorgRuntime, type BurstMeterState } from "./types.js";

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

/** Arming alone samples the Y edge only; activation needs a charged per-player meter. */
function testArmingAloneDoesNotActivate(): void {
  assertEqual(BURST.ENABLED, true, "BURST.ENABLED is true for the ATK-012 core slice");
  const b = makeBorg();
  stepBurst(b, true);
  assertEqual(b.burstActive, false, "stepBurst only arms; it does not activate without a charged meter");
  assertEqual(b.burstPaired, false, "stepBurst alone does not mark paired");
}

function testActivationRequiresChargedMeter(): void {
  const b = makeBorg();
  stepBurst(b, true);
  assertEqual(canActivateBurst(b, createBurstMeter()), false, "empty meter cannot activate");

  const fullUncharged: BurstMeterState = { meter: BURST.METER_MAX, unclamped: BURST.METER_MAX, charged: false };
  assertEqual(canActivateBurst(b, fullUncharged), false, "full but not-yet-charged meter cannot activate");

  const charged: BurstMeterState = { meter: BURST.METER_MAX, unclamped: BURST.METER_MAX, charged: true };
  assertEqual(canActivateBurst(b, charged), true, "armed + charged full meter can activate");
  assertEqual(tryActivateBurst(b, charged, false), true, "tryActivateBurst succeeds when gate holds");
  assertEqual(b.burstActive, true, "activation sets burstActive");
  assertEqual(b.burstPaired, false, "solo activation leaves burstPaired false");
  assertEqual(charged.charged, false, "activation consumes the charged flag");
  assertEqual(tryActivateBurst(b, charged, false), false, "already-active burst cannot re-activate");
}

function testPairedActivationFlag(): void {
  const b = makeBorg();
  const meter: BurstMeterState = { meter: BURST.METER_MAX, unclamped: BURST.METER_MAX, charged: true };
  stepBurst(b, true);
  assertEqual(tryActivateBurst(b, meter, true), true, "paired activation succeeds when gate holds");
  assertEqual(b.burstActive, true, "paired activation sets burstActive");
  assertEqual(b.burstPaired, true, "paired activation records the simultaneous-team shape");
}

function testActiveBurstDrainsAndEnds(): void {
  const b = makeBorg({ burstActive: true, burstPaired: true });
  const meter: BurstMeterState = { meter: 12, unclamped: 12, charged: true };

  stepActiveBurst(b, meter);
  assertEqual(meter.meter, 7, "active burst drains -5 meter per frame");
  assertEqual(meter.charged, false, "active drain clears charged");
  assertEqual(b.burstActive, true, "burst stays active while meter remains");

  stepActiveBurst(b, meter);
  assertEqual(meter.meter, 2, "drain continues at -5/frame");
  assertEqual(b.burstActive, true, "burst stays active above zero");

  stepActiveBurst(b, meter);
  assertEqual(meter.meter, 0, "meter floors at zero");
  assertEqual(b.burstActive, false, "burst ends when meter empties");
  assertEqual(b.burstPaired, false, "paired flag clears when burst ends");
}

/** stepBurst itself has no direct side effects: it does not touch hp/pos/state/ammo/etc. */
function testBurstInputHasNoDirectSideEffects(): void {
  const b = makeBorg({ hp: 77, ammo: 3, state: "idle" });
  const before = JSON.stringify({ hp: b.hp, ammo: b.ammo, state: b.state, pos: b.pos, vel: b.vel });
  stepBurst(b, true);
  stepBurst(b, true);
  stepBurst(b, false);
  const after = JSON.stringify({ hp: b.hp, ammo: b.ammo, state: b.state, pos: b.pos, vel: b.vel });
  assertEqual(after, before, "stepBurst never mutates hp/ammo/state/pos/vel");
}

function testBurstSpeedMultiplierAffectsMovement(): void {
  const input = { ...emptyInput(), moveZ: 1 };
  const bounds = { minX: -10000, maxX: 10000, minZ: -10000, maxZ: 10000 };
  const profile = makeProfile("pl0615", { speed: 6 });

  const normal = makeBorg();
  for (let i = 0; i < 10; i++) {
    stepMovement(normal, profile, input, { lockTargetPos: null, bounds, collision: null });
  }

  const burst = makeBorg({ burstActive: true });
  for (let i = 0; i < 10; i++) {
    stepMovement(burst, profile, input, { lockTargetPos: null, bounds, collision: null });
  }

  // 2026-07-04 raw migration: pl0615's DERIVED run speed is its page+0x2c = 12.0 u/f raw
  // (movementData.ts groundRunSpeedForBorgId; the old 22.0 anchor is retired — see
  // research/decomp/movement-hit-decode-2026-07-04.md §1). Burst x1.5 is unchanged.
  assertEqual(Math.hypot(normal.vel.x, normal.vel.z), 12, "pl0615 baseline reaches its DERIVED 12 u/f run speed");
  assertEqual(Math.hypot(burst.vel.x, burst.vel.z), 18, "active burst applies x1.5 movement speed");
}

function testBattleStepActivatesAndDrainsBurst(): void {
  const stats: BorgStats[] = [
    {
      id: "pl0615",
      name: "G RED",
      energy: 10,
      hp: 100,
      defense: 1,
      shot: 1,
      attack: 1,
      speed: 6,
      jump: "Air jump level 1",
      type: "Short range",
    },
  ];
  const battle = createBattle(
    {
      stageId: "test",
      bounds: { x: 10000, z: 10000 },
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: null, borgIds: ["pl0615"] },
      ],
    },
    stats,
  );
  const mutable = battleStateForSelfcheck(battle);
  const playerUid = mutable.activeUidByPlayer["p1"];
  const player = mutable.borgs.find((b) => b.uid === playerUid);
  const meter = mutable.burstMeterByPlayer["p1"];
  if (!player || !meter) {
    assertTrue(false, "test battle creates a player borg and meter");
    return;
  }

  player.state = "idle";
  player.stateTime = 0;
  player.invincTimer = 0;
  meter.meter = BURST.METER_MAX;
  meter.unclamped = BURST.METER_MAX;
  meter.charged = true;

  const input = { ...emptyInput(), hyper: true, moveZ: 1 };
  for (let i = 0; i < 10; i++) battle.step(1 / 60, { p1: input });

  assertEqual(player.burstActive, true, "Battle.step activates Power Burst from charged Y input");
  assertEqual(player.burstPaired, false, "single-human battle activation is solo, not paired");
  assertEqual(meter.meter, BURST.METER_MAX - BURST.DRAIN_PER_FRAME * 10, "Battle.step drains active burst each frame");
  assertEqual(meter.charged, false, "Battle.step clears charged during active burst");
  // 12 u/f DERIVED run speed (raw migration, see testBurstSpeedMultiplierAffectsMovement) x1.5.
  assertEqual(Math.hypot(player.vel.x, player.vel.z), 18, "Battle.step movement sees active burst speed");
}

// --- Per-player burst METER tests (Q4 RESOLVED 2026-07-03 — open-questions Q4 lines 51-79,
// findings §S; fill rule from the T3 live traces: +50 per hit connection, attacker only) ------

/** Synthetic profile — the meter fill is damage-independent, so no roster stats are needed. */
function makeProfile(id: string, overrides: Partial<BorgProfile> = {}): BorgProfile {
  return {
    id,
    name: id.toUpperCase(),
    energy: 10,
    maxHp: 100,
    defense: 1,
    shot: 1,
    attack: 1,
    speed: 1,
    airJumpLevel: 0,
    flyer: false,
    hasShot: true,
    hasMelee: true,
    rangePref: "melee",
    ...overrides,
  };
}

/** One applyHit connection with an attacker context = +FILL_PER_HIT on the ATTACKER'S meter.
 *  Clears the victim's reaction/i-frames first so each call is a guaranteed fresh CONNECTION
 *  (a melee hit balance-breaks and grants stagger i-frames, under which a follow-up would be
 *  a non-connection — correctly filling nothing, but not what these tests exercise). */
function hitOnce(
  meters: Record<string, BurstMeterState>,
  attacker: BorgRuntime,
  victim: BorgRuntime,
): number {
  victim.invincTimer = 0;
  victim.state = "idle";
  victim.stateTime = 0;
  return applyHit(
    victim,
    makeProfile(victim.borgId),
    0,
    0,
    { x: 0, y: 0, z: 0 },
    { x: victim.pos.x, y: victim.pos.y, z: victim.pos.z - 10 },
    false,
    damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
    { attacker, attackerProfile: makeProfile(attacker.borgId) },
    { burstMeters: meters },
  );
}

/** Pins the Q4 ROM constants so they can't silently drift. */
function testMeterConstants(): void {
  assertEqual(BURST.METER_MAX, 3000, "BURST.METER_MAX is 3000 (player struct +0x124, Q4/§S)");
  assertEqual(BURST.FILL_PER_HIT, 50, "BURST.FILL_PER_HIT is 50 (T3 live traces, Q4 lines 59-74)");
  assertEqual(BURST.DRAIN_PER_FRAME, 5, "BURST.DRAIN_PER_FRAME is 5 (Q5 live trace)");
  assertEqual(BURST.SPEED_MULTIPLIER, 1.5, "BURST.SPEED_MULTIPLIER is x1.5 (Q5 live trace)");
}

/** A landed hit credits the ATTACKER'S player meter +50, and the victim's meter never moves. */
function testFillOnAttackerHitOnly(): void {
  const meters: Record<string, BurstMeterState> = { p1: createBurstMeter(), p2: createBurstMeter() };
  const attacker = makeBorg({ uid: "a", ownerPlayer: "p1", team: 0, state: "attack" });
  const victim = makeBorg({ uid: "v", ownerPlayer: "p2", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0 });
  const dmg = hitOnce(meters, attacker, victim);
  assertTrue(dmg > 0, "the test hit actually connects and deals damage");
  assertEqual(meters["p1"]?.meter, 50, "attacker's player meter fills +50 on a hit connection");
  assertEqual(meters["p1"]?.unclamped, 50, "attacker's unclamped accumulator also gains +50");
  assertEqual(meters["p2"]?.meter, 0, "victim's meter NEVER fills (Q4: no other player's meter moved)");
  assertEqual(meters["p2"]?.unclamped, 0, "victim's unclamped accumulator never moves either");

  // Per-connection semantics: a second connection credits another flat +50 (damage-independent).
  hitOnce(meters, attacker, victim);
  assertEqual(meters["p1"]?.meter, 100, "each hit CONNECTION credits a flat +50 (dead-husk trace: 3x50)");
}

/** +0x126 clamps at METER_MAX while +0x12a keeps accumulating past it (live: 2929->3079->3129). */
function testClampAndUnclampedPastMax(): void {
  const meters: Record<string, BurstMeterState> = { p1: { meter: 2975, unclamped: 2975, charged: false } };
  creditBurstFill(meters, "p1");
  assertEqual(meters["p1"]?.meter, 3000, "meter clamps at METER_MAX (3000), not 3025");
  assertEqual(meters["p1"]?.unclamped, 3025, "unclamped keeps counting past max");
  creditBurstFill(meters, "p1");
  assertEqual(meters["p1"]?.meter, 3000, "meter stays clamped on further fills");
  assertEqual(meters["p1"]?.unclamped, 3075, "unclamped keeps climbing (+50 per connection)");
}

/** Charged flag (+0x103) flips EXACTLY one frame after the meter reaches max — battle.ts's
 *  check-before-fill ordering: sweep at top of frame N+1 sees frame N's maxed meter. */
function testChargedFlipsOneFrameLate(): void {
  const meters: Record<string, BurstMeterState> = { p1: { meter: 2950, unclamped: 2950, charged: false } };
  // Frame N: sweep first (meter 2950 < max -> no charge), then this frame's fill maxes it.
  sweepBurstCharged(meters);
  creditBurstFill(meters, "p1");
  assertEqual(meters["p1"]?.meter, 3000, "meter reaches max on frame N");
  assertEqual(meters["p1"]?.charged, false, "charged is still false at the end of frame N (one-frame delay)");
  // Frame N+1: the sweep now sees the maxed meter and flips the flag.
  sweepBurstCharged(meters);
  assertEqual(meters["p1"]?.charged, true, "charged flips true on frame N+1 (ROM +0x103, one frame late)");
}

/** Source-less legacy applyHit paths (no attacker context) must NEVER fill any meter. */
function testSourcelessDamageNeverFills(): void {
  const meters: Record<string, BurstMeterState> = { p1: createBurstMeter() };
  const victim = makeBorg({ uid: "v", ownerPlayer: "p1", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0 });
  const dmg = applyHit(
    victim,
    makeProfile(victim.borgId),
    25,
    0,
    { x: 0, y: 0, z: 0 },
    { x: victim.pos.x, y: victim.pos.y, z: victim.pos.z - 10 },
    false,
    damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
    undefined, // no source (legacy path)
    { burstMeters: meters },
  );
  assertTrue(dmg > 0, "source-less legacy hit still deals damage");
  assertEqual(meters["p1"]?.meter, 0, "source-less damage never fills any meter (no attacker to credit)");
  assertEqual(Object.keys(meters).length, 1, "no meter record is invented by a source-less hit");
}

/** CPU-owned attackers (ownerPlayer === null) are not credited — documented wave-1 decision
 *  (see creditBurstFill in burst.ts). */
function testCpuAttackerNotCredited(): void {
  const meters: Record<string, BurstMeterState> = {};
  const cpu = makeBorg({ uid: "c", ownerPlayer: null, team: 0, state: "attack" });
  const victim = makeBorg({ uid: "v", ownerPlayer: "p2", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0 });
  hitOnce(meters, cpu, victim);
  assertEqual(Object.keys(meters).length, 0, "a CPU attacker (ownerPlayer null) credits no meter");
}

/** The meter is PER-PLAYER (ROM player struct +i*0x3c), NOT per-borg: it survives the borg's
 *  death and keeps accumulating through the same player's next deployed borg. */
function testMeterPersistsAcrossRedeploy(): void {
  const meters: Record<string, BurstMeterState> = { p1: createBurstMeter() };
  const first = makeBorg({ uid: "b1", ownerPlayer: "p1", team: 0, state: "attack" });
  const victim = makeBorg({ uid: "v", ownerPlayer: "p2", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0 });
  hitOnce(meters, first, victim);
  assertEqual(meters["p1"]?.meter, 50, "first borg's hit fills the player meter");

  // First borg dies — nothing in the borg lifecycle touches the per-player map.
  first.hp = 0;
  first.alive = false;
  first.state = "death";
  assertEqual(meters["p1"]?.meter, 50, "meter untouched by the borg's death");

  // The same player's NEXT deployed borg keeps accumulating on the same record.
  const second = makeBorg({ uid: "b2", ownerPlayer: "p1", team: 0, state: "attack" });
  hitOnce(meters, second, victim);
  assertEqual(meters["p1"]?.meter, 100, "same player's redeployed borg accumulates on the SAME meter");
  assertEqual(meters["p1"]?.unclamped, 100, "unclamped accumulator persists across redeploy too");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testPressEdgeArmsSixFrames();
  testWindowDecrementsPerFrame();
  testRePressReArms();
  testArmingAloneDoesNotActivate();
  testActivationRequiresChargedMeter();
  testPairedActivationFlag();
  testActiveBurstDrainsAndEnds();
  testBurstInputHasNoDirectSideEffects();
  testBurstSpeedMultiplierAffectsMovement();
  testBattleStepActivatesAndDrainsBurst();
  testMeterConstants();
  testFillOnAttackerHitOnly();
  testClampAndUnclampedPastMax();
  testChargedFlipsOneFrameLate();
  testSourcelessDamageNeverFills();
  testCpuAttackerNotCredited();
  testMeterPersistsAcrossRedeploy();

  if (failures > 0) {
    console.error(`burst.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`burst.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
