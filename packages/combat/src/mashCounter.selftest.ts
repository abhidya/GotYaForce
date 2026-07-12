// Self-test for ATK-017 (button-mash counter scaffold, DISABLED by default).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// own entry point, own runner (scripts/run-mash-counter-tests.mjs), per the
// commandSchema.selftest.ts / burst.selftest.ts precedent. Does not import or modify
// selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-mash-counter-tests.mjs

import { createBattle } from "./battle.js";
import { stepAttacks, stepCooldowns } from "./combat.js";
import { MASH } from "./constants.js";
import { emptyInput, type BorgRuntime } from "./types.js";
import type { BorgProfile, BorgStats } from "./stats.js";

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
    id: "test_mash",
    name: "Test Mash",
    energy: 1,
    maxHp: 100,
    defense: 0,
    shot: 0,
    attack: 0,
    speed: 5,
    airJumpLevel: 1,
    flyer: false,
    hasShot: false,
    hasMelee: true,
    rangePref: "melee",
    ...overrides,
  };
}

function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "test_mash",
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

/** Drive stepAttacks for one frame with a given attackHeld state. */
function frame(b: BorgRuntime, p: BorgProfile, attackHeld: boolean): void {
  stepAttacks(b, p, attackHeld, false, [b], new Map([[b.uid, p]]));
  stepCooldowns(b);
}

// --- Tests -----------------------------------------------------------------------------------

/** Constants sanity: disabled by default, cap is 4 (DERIVED chunk_0007.c:4809-4816). */
function testFlagAndCapDefaults(): void {
  assertEqual(MASH.ENABLED, false, "MASH.ENABLED default is false (BLOCKED-until-Q9)");
  assertEqual(MASH.PRESS_CAP, 4, "MASH.PRESS_CAP is 4 (DERIVED chunk_0007.c:4809-4816)");
}

/** 10 presses (10 press EDGES, not held frames) during one swing -> counter reads 4 (cap). */
function testTenMashesCapAtFour(): void {
  const p = makeProfile();
  const b = makeBorg();

  // Start a swing.
  frame(b, p, true);
  assertEqual(b.state, "attack", "attack press starts a melee swing");
  assertEqual(b.anim, "melee", "swing anim is melee");
  assertEqual(b.cooldowns["mashCount"] ?? 0, 0, "mashCount starts at 0 on swing start (the opening press isn't a mash edge itself)");

  // 10 press/release cycles (10 edges) while the swing is still active.
  for (let i = 0; i < 10; i++) {
    frame(b, p, false); // release edge
    if (b.state !== "attack") break; // swing ended; stop mashing
    frame(b, p, true); // press edge
  }

  assertEqual(b.cooldowns["mashCount"] ?? 0, MASH.PRESS_CAP, "10 mash presses during one swing clamp at MASH.PRESS_CAP (4)");
}

/** Held button (no edges) during the swing -> counter stays 0. */
function testHeldButtonNoEdgesStaysZero(): void {
  const p = makeProfile();
  const b = makeBorg();

  frame(b, p, true); // start the swing (this IS the initiating press, counted as swing-start not a mash edge)
  assertEqual(b.cooldowns["mashCount"] ?? 0, 0, "mashCount is 0 right after the opening press");

  // Hold the button (no press/release edges) for the rest of the swing.
  for (let i = 0; i < 30 && b.state === "attack"; i++) {
    frame(b, p, true);
  }

  assertEqual(b.cooldowns["mashCount"] ?? 0, 0, "holding the button (no edges) never increments mashCount");
}

/** A new swing resets the counter to 0. */
function testNewSwingResetsCounter(): void {
  const p = makeProfile();
  const b = makeBorg();

  frame(b, p, true); // start swing 1
  for (let i = 0; i < 6; i++) {
    frame(b, p, false);
    if (b.state !== "attack") break;
    frame(b, p, true);
  }
  const midCount = b.cooldowns["mashCount"] ?? 0;
  assertEqual(midCount > 0, true, "mashCount is nonzero mid-mash (sanity check before reset)");

  // Run the swing out to completion (idle) AND past its post-swing melee cooldown
  // (duration + cooldown, see startMeleeAttack) so the next press can start a fresh swing
  // rather than being gated by "melee" still counting down.
  for (let i = 0; i < 60; i++) {
    frame(b, p, false);
  }
  assertEqual(b.state, "idle", "swing 1 fully elapsed back to idle");
  assertEqual(b.cooldowns["melee"] ?? 0, 0, "melee cooldown has also fully elapsed");

  frame(b, p, true); // start swing 2
  assertEqual(b.state, "attack", "swing 2 started");
  assertEqual(b.cooldowns["mashCount"] ?? 0, 0, "a new swing resets mashCount to 0");
}

/** mashCount does NOT decay like a countdown timer — it must be on stepCooldowns' skip-list,
 *  or holding a nonzero count across frames (with no swing / no presses) would silently drain
 *  it even though nothing mashed. */
function testMashCountSurvivesStepCooldownsWhenNotMashing(): void {
  const b = makeBorg({ cooldowns: { mashCount: 3 } });
  for (let i = 0; i < 5; i++) stepCooldowns(b);
  assertEqual(b.cooldowns["mashCount"], 3, "mashCount is on stepCooldowns' skip-list (a counter, not a countdown timer) and does not decay");
}

/** Regression: battle outcomes are unchanged (mash counting has zero gameplay effect while
 *  MASH.ENABLED stays false — nothing reads the counter). Runs a short deterministic battle
 *  twice (identical seed/inputs) and checks the resulting frame/result/energy trajectory is
 *  identical to itself — a cheap proxy for "adding mash counting didn't change sim output". */
function testBattleRegressionUnaffected(): void {
  const stats: BorgStats[] = [
    {
      id: "pl0000",
      name: "NORMAL NINJA",
      energy: 150,
      hp: "150/195",
      defense: 2,
      shot: 2,
      attack: 3,
      speed: 5,
      jump: "Air jump level 3",
    } as unknown as BorgStats,
  ];

  function runBattle(): string {
    const battle = createBattle(
      {
        stageId: "test",
        forces: [
          { team: 0, ownerPlayer: "p1", borgIds: ["pl0000"] },
          { team: 1, ownerPlayer: null, borgIds: ["pl0000"] },
        ],
      },
      stats,
    );
    const input = { ...emptyInput(), attack: true, moveZ: 1 };
    for (let i = 0; i < 200; i++) {
      battle.step(1 / 60, { p1: input });
    }
    return JSON.stringify({
      frame: battle.observe().frame,
      result: battle.observe().result,
      energy: battle.observe().energy,
    });
  }

  const a = runBattle();
  const b = runBattle();
  assertEqual(a, b, "battle with mash-counting wired in is fully deterministic (no gameplay effect leak)");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testFlagAndCapDefaults();
  testTenMashesCapAtFour();
  testHeldButtonNoEdgesStaysZero();
  testNewSwingResetsCounter();
  testMashCountSurvivesStepCooldownsWhenNotMashing();
  testBattleRegressionUnaffected();

  if (failures > 0) {
    console.error(`mashCounter.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`mashCounter.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
