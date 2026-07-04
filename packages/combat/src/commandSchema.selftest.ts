// Self-test for ATK-001 (attack-command schema) and ATK-004 (movement-context capture).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// this is its own entry point with its own runner (scripts/run-attack-schema-tests.mjs), per
// ATK-001/ATK-004's coordination note. Does not import or modify selfcheck.ts.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-attack-schema-tests.mjs
// main()/runSelfTest() return an exit code (0 = pass).

import {
  AttackCommandSubtype,
  AttackCommandType,
  COMMAND_FAMILY,
  COMMAND_INPUT_BITS,
  inputRequestsBurst,
  resolveCommandType,
} from "./command.js";
import {
  commandInputWord,
  contextualBGatesForBorgId,
  resolveLiveCommand,
  selectCommandRecord,
} from "./commandDispatch.js";
import { commandMoveRecordsForBorgButton } from "./commandMoveTables.js";
import { stepCooldowns } from "./combat.js";
import { DASH, JUMP, MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES } from "./constants.js";
import { movementContextOf } from "./movement.js";
import { stepMovement, type MoveContext } from "./movement.js";
import { emptyInput, type BorgRuntime, type RectStageBounds } from "./types.js";
import type { BorgProfile } from "./stats.js";

/** One simulated frame: movement + the same cooldown tick the real battle loop applies
 *  (battle.ts calls stepCooldowns once/frame, separately from stepMovement) — needed here so
 *  cooldowns["landedFrames"]/["dashActive"] actually decay across the frame-scripted tests. */
function stepFrame(b: BorgRuntime, p: BorgProfile, input: ReturnType<typeof emptyInput>, ctx: MoveContext): void {
  stepMovement(b, p, input, ctx);
  stepCooldowns(b);
}

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

const BOUNDS: RectStageBounds = { minX: -4000, maxX: 4000, minZ: -4000, maxZ: 4000 };
const CTX: MoveContext = { lockTargetPos: null, bounds: BOUNDS, collision: null };

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

// --- ATK-001: command schema tests --------------------------------------------------------

function testCommandFamilyTable(): void {
  // Ticket-specified literal assertions.
  assertEqual(COMMAND_FAMILY[AttackCommandType.Melee1], "melee", "COMMAND_FAMILY[1] === melee");
  assertEqual(COMMAND_FAMILY[AttackCommandType.Ranged5], "ranged", "COMMAND_FAMILY[5] === ranged");

  // Full table: 1/2 melee, 3 charged, 4/5/6 ranged.
  assertEqual(COMMAND_FAMILY[AttackCommandType.Melee2], "melee", "COMMAND_FAMILY[2] === melee");
  assertEqual(COMMAND_FAMILY[AttackCommandType.Charged3], "charged", "COMMAND_FAMILY[3] === charged");
  assertEqual(COMMAND_FAMILY[AttackCommandType.Ranged4], "ranged", "COMMAND_FAMILY[4] === ranged");
  assertEqual(COMMAND_FAMILY[AttackCommandType.Ranged6], "ranged", "COMMAND_FAMILY[6] === ranged");

  // Unmapped values must stay unmapped — no invented family assignments.
  assertEqual(COMMAND_FAMILY[AttackCommandType.Unmapped0], "unmapped", "COMMAND_FAMILY[0] === unmapped");
  assertEqual(COMMAND_FAMILY[AttackCommandType.Unmapped7], "unmapped", "COMMAND_FAMILY[7] === unmapped");
}

function testCommandEnumValuesMatchRom(): void {
  // Enum numeric values must mirror the ROM byte exactly (0-7).
  assertEqual(AttackCommandType.Unmapped0, 0, "AttackCommandType.Unmapped0 === 0");
  assertEqual(AttackCommandType.Melee1, 1, "AttackCommandType.Melee1 === 1");
  assertEqual(AttackCommandType.Melee2, 2, "AttackCommandType.Melee2 === 2");
  assertEqual(AttackCommandType.Charged3, 3, "AttackCommandType.Charged3 === 3");
  assertEqual(AttackCommandType.Unmapped3, AttackCommandType.Charged3, "AttackCommandType.Unmapped3 alias === Charged3");
  assertEqual(AttackCommandType.Ranged4, 4, "AttackCommandType.Ranged4 === 4");
  assertEqual(AttackCommandType.Ranged5, 5, "AttackCommandType.Ranged5 === 5");
  assertEqual(AttackCommandType.Ranged6, 6, "AttackCommandType.Ranged6 === 6");
  assertEqual(AttackCommandType.Unmapped7, 7, "AttackCommandType.Unmapped7 === 7");

  // Subtype range 0-5 (actor+0x586, chunk_0009.c:500-587).
  assertEqual(AttackCommandSubtype.Unmapped0, 0, "AttackCommandSubtype.Unmapped0 === 0");
  assertEqual(AttackCommandSubtype.AirElevated4, 4, "AttackCommandSubtype.AirElevated4 === 4");
  assertEqual(AttackCommandSubtype.ChargedRanged5, 5, "AttackCommandSubtype.ChargedRanged5 === 5");
  assertEqual(
    AttackCommandSubtype.Unmapped5,
    AttackCommandSubtype.ChargedRanged5,
    "AttackCommandSubtype.Unmapped5 alias === ChargedRanged5",
  );
}

function testAttackCommandShape(): void {
  // Construct an AttackCommand literal — pure type-level smoke test that the interface compiles
  // and is usable with the enum values (schema only; nothing in the sim builds one of these yet).
  const cmd = { type: AttackCommandType.Melee1, subtype: AttackCommandSubtype.AirElevated4 };
  assertEqual(cmd.type, 1, "AttackCommand.type literal matches enum value");
  assertEqual(cmd.subtype, 4, "AttackCommand.subtype literal matches enum value");
}

function testResolveCommandType(): void {
  // Single-bit selection (behavior-notes (bd), verified chunk_0009.c tester bits).
  assertEqual(resolveCommandType(COMMAND_INPUT_BITS.RANGED), AttackCommandType.Ranged5, "bit 0x1000 -> Ranged5");
  assertEqual(resolveCommandType(COMMAND_INPUT_BITS.CHARGED), AttackCommandType.Charged3, "bit 0x400 -> charged type 3");
  assertEqual(resolveCommandType(COMMAND_INPUT_BITS.SECONDARY), AttackCommandType.Melee2, "bit 0x80 -> type 2 (X)");
  assertEqual(resolveCommandType(COMMAND_INPUT_BITS.MELEE_A), AttackCommandType.Melee1, "bit 0x20 -> Melee1");
  assertEqual(resolveCommandType(COMMAND_INPUT_BITS.MELEE_B), AttackCommandType.Melee1, "bit 0x40 -> Melee1");
  assertEqual(resolveCommandType(0), null, "no attack bit -> null");
  assertEqual(resolveCommandType(COMMAND_INPUT_BITS.BURST), null, "only Y-burst bit -> null (not a +0x585 type)");

  // Tester PRIORITY (FUN_800699d8:228-238, first non-zero wins): RANGED > CHARGED > SECONDARY > MELEE.
  assertEqual(
    resolveCommandType(COMMAND_INPUT_BITS.RANGED | COMMAND_INPUT_BITS.MELEE_A),
    AttackCommandType.Ranged5,
    "ranged+melee -> Ranged5 (ranged tester wins)",
  );
  assertEqual(
    resolveCommandType(COMMAND_INPUT_BITS.CHARGED | COMMAND_INPUT_BITS.SECONDARY | COMMAND_INPUT_BITS.MELEE_B),
    AttackCommandType.Charged3,
    "charged+secondary+melee -> charged (charged beats secondary/melee)",
  );
  assertEqual(
    resolveCommandType(COMMAND_INPUT_BITS.SECONDARY | COMMAND_INPUT_BITS.MELEE_A),
    AttackCommandType.Melee2,
    "secondary+melee -> type 2 (secondary beats melee)",
  );

  // Burst is a separate path, and coexists with an attack type.
  assertEqual(inputRequestsBurst(COMMAND_INPUT_BITS.BURST), true, "Y bit -> burst requested");
  assertEqual(inputRequestsBurst(COMMAND_INPUT_BITS.RANGED), false, "ranged bit alone -> no burst");
  assertEqual(
    resolveCommandType(COMMAND_INPUT_BITS.BURST | COMMAND_INPUT_BITS.MELEE_A),
    AttackCommandType.Melee1,
    "burst+melee -> Melee1 type still resolves (burst is separate)",
  );
}

// --- ATK-004: movement-context tests -------------------------------------------------------

function testStandingContext(): void {
  const b = makeBorg();
  assertEqual(movementContextOf(b), "standing", "grounded, idle, no dash -> standing");
}

function testGroundDashContext(): void {
  const b = makeBorg({ grounded: true, cooldowns: { dashActive: DASH.DURATION } });
  assertEqual(movementContextOf(b), "ground_dash", "grounded + dashActive -> ground_dash");
}

function testAirDashContext(): void {
  const b = makeBorg({ grounded: false, vel: { x: 0, y: -1, z: 0 }, cooldowns: { dashActive: DASH.DURATION } });
  assertEqual(movementContextOf(b), "air_dash", "airborne + dashActive -> air_dash");
}

function testFlyingContext(): void {
  const b = makeBorg({ grounded: false, state: "fly" });
  assertEqual(movementContextOf(b), "flying", 'state "fly" -> flying');
}

function testJumpRiseAndNeutralAir(): void {
  const rising = makeBorg({ grounded: false, vel: { x: 0, y: 2, z: 0 } });
  assertEqual(movementContextOf(rising), "jump_rise", "airborne + vel.y > 0 -> jump_rise");

  const falling = makeBorg({ grounded: false, vel: { x: 0, y: -2, z: 0 } });
  assertEqual(movementContextOf(falling), "neutral_air", "airborne + vel.y <= 0 -> neutral_air");

  const apex = makeBorg({ grounded: false, vel: { x: 0, y: 0, z: 0 } });
  assertEqual(movementContextOf(apex), "neutral_air", "airborne + vel.y === 0 -> neutral_air (apex)");
}

function testLandingContext(): void {
  const b = makeBorg({ grounded: false, cooldowns: { landedFrames: MOVEMENT_CONTEXT_LANDING_WINDOW_FRAMES } });
  assertEqual(movementContextOf(b), "landing", "landedFrames > 0 -> landing regardless of grounded/vel");

  const grounded = makeBorg({ grounded: true, cooldowns: { landedFrames: 1 } });
  assertEqual(movementContextOf(grounded), "landing", "landing takes precedence over standing");
}

/**
 * Frame-scripted sequence: jump -> context sequence standing -> jump_rise -> neutral_air ->
 * landing -> standing, per the ATK-004 "Tests to add" section. Uses a flat-ground MoveContext
 * (no collision mesh) so groundYAt falls back to JUMP.GROUND_Y.
 */
function testJumpSequence(): void {
  const p = makeProfile({ flyer: false });
  const b = makeBorg();
  const seq: string[] = [];

  assertEqual(movementContextOf(b), "standing", "frame 0: standing before jump");

  // Frame 1: press jump on the ground -> rising edge.
  stepFrame(b, p, { ...emptyInput(), jump: true }, CTX);
  seq.push(movementContextOf(b));
  assertTrue(!b.grounded, "frame 1: airborne immediately after jump");
  assertEqual(movementContextOf(b), "jump_rise", "frame 1: jump_rise (vel.y > 0 from JUMP.VELOCITY)");

  // Release jump so the latch re-arms, then step until apex/fall begins (neutral_air).
  let sawNeutralAir = false;
  let sawLanding = false;
  let sawStandingAfterLanding = false;
  const noInput = emptyInput();
  for (let i = 0; i < 200; i++) {
    stepFrame(b, p, noInput, CTX);
    const ctx = movementContextOf(b);
    seq.push(ctx);
    if (ctx === "neutral_air") sawNeutralAir = true;
    if (sawNeutralAir && ctx === "landing") sawLanding = true;
    if (sawLanding && ctx === "standing") {
      sawStandingAfterLanding = true;
      break;
    }
  }

  assertTrue(sawNeutralAir, `jump sequence reaches neutral_air (seq: ${seq.join(",")})`);
  assertTrue(sawLanding, `jump sequence reaches landing after neutral_air (seq: ${seq.join(",")})`);
  assertTrue(
    sawStandingAfterLanding,
    `jump sequence returns to standing after the landing window (seq: ${seq.join(",")})`,
  );
}

/** A borg well above the ground plane so one frame of falling/dashing doesn't land it. */
function makeAirborneBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return makeBorg({
    grounded: false,
    pos: { x: 0, y: JUMP.GROUND_Y + 500, z: 0 },
    ...overrides,
  });
}

/** Flyer boosting sustained flight -> "flying". */
function testFlyerBoostSequence(): void {
  const p = makeProfile({ flyer: true });
  const b = makeAirborneBorg({ vel: { x: 0, y: 0, z: 0 }, state: "jump" });
  const boostInput = { ...emptyInput(), jump: true };

  stepFrame(b, p, boostInput, CTX);
  assertEqual(b.state, "fly", "flyer holding jump in air enters fly state");
  assertEqual(movementContextOf(b), "flying", "flyer boosting -> flying context");
}

/** Dash while airborne -> "air_dash" (vs. ground_dash when grounded). */
function testDashContextsViaStepMovement(): void {
  const p = makeProfile();

  const grounded = makeBorg({ grounded: true });
  stepFrame(grounded, p, { ...emptyInput(), dash: true, moveZ: 1 }, CTX);
  assertEqual(movementContextOf(grounded), "ground_dash", "dash while grounded -> ground_dash");

  const airborne = makeAirborneBorg({ vel: { x: 0, y: -1, z: 0 }, state: "jump" });
  stepFrame(airborne, p, { ...emptyInput(), dash: true, moveZ: 1 }, CTX);
  assertEqual(movementContextOf(airborne), "air_dash", "dash while airborne -> air_dash");
}

// --- ATK-003: live command dispatch (commandDispatch.ts) -----------------------------------

function testCommandInputWord(): void {
  assertEqual(commandInputWord({ attackHeld: true, specialHeld: false, chargeRelease: false, xChargeRelease: false }), COMMAND_INPUT_BITS.MELEE_A, "B held -> MELEE_A bit");
  assertEqual(commandInputWord({ attackHeld: false, specialHeld: true, chargeRelease: false, xChargeRelease: false }), COMMAND_INPUT_BITS.SECONDARY, "X held -> SECONDARY bit");
  assertEqual(commandInputWord({ attackHeld: false, specialHeld: false, chargeRelease: true, xChargeRelease: false }), COMMAND_INPUT_BITS.CHARGED, "B charge release -> CHARGED bit");
  assertEqual(commandInputWord({ attackHeld: false, specialHeld: false, chargeRelease: false, xChargeRelease: true }), COMMAND_INPUT_BITS.RANGED, "X charge release -> RANGED bit");
}

function testLiveCommandDispatch(): void {
  // G RED (pl0615): exact decoded records for B Shot, B Attack, B Charge, and X.
  const ground = { meleeEngaged: false, airborne: false };
  const close = { meleeEngaged: true, airborne: false };
  const bFar = resolveLiveCommand("pl0615", { attackHeld: true, specialHeld: false, chargeRelease: false, xChargeRelease: false }, ground);
  assertEqual(bFar?.button ?? null, "B Shot", "G RED B far -> B Shot row");
  assertTrue(bFar?.exact === true, "G RED B Shot resolves an exact ROM record");
  const bClose = resolveLiveCommand("pl0615", { attackHeld: true, specialHeld: false, chargeRelease: false, xChargeRelease: false }, close);
  assertEqual(bClose?.button ?? null, "B Attack", "G RED B close -> B Attack row");
  assertTrue(bClose?.exact === true, "G RED B Attack resolves an exact ROM record");
  const bCharge = resolveLiveCommand("pl0615", { attackHeld: false, specialHeld: false, chargeRelease: true, xChargeRelease: false }, ground);
  assertEqual(bCharge?.type ?? null, AttackCommandType.Charged3, "G RED charge release -> type 3");
  assertEqual(bCharge?.button ?? null, "B Charge", "G RED charge release -> B Charge row");
  assertTrue(bCharge?.exact === true, "G RED B Charge resolves an exact ROM record");
  const x = resolveLiveCommand("pl0615", { attackHeld: false, specialHeld: true, chargeRelease: false, xChargeRelease: false }, ground);
  assertEqual(x?.type ?? null, AttackCommandType.Melee2, "G RED X -> type 2");
  assertEqual(x?.button ?? null, "X", "G RED X -> X row");
  assertTrue(x?.exact === true, "G RED X resolves an exact ROM record");

  // ROM priority on combined input: charge release + X held -> charged (type 3) wins.
  const chargedOverX = resolveLiveCommand("pl0615", { attackHeld: false, specialHeld: true, chargeRelease: true, xChargeRelease: false }, ground);
  assertEqual(chargedOverX?.type ?? null, AttackCommandType.Charged3, "charge release preempts X (type 3 > type 2)");

  // Magnet Robot (+/-), Angel Nurse, Beam Satellite: exact records for their main B/X rows.
  for (const id of ["pl0405", "pl0409", "pl0900", "pl0e01"]) {
    const far = resolveLiveCommand(id, { attackHeld: true, specialHeld: false, chargeRelease: false, xChargeRelease: false }, ground);
    assertTrue(far?.exact === true, `${id} B Shot resolves an exact ROM record`);
    const xRow = resolveLiveCommand(id, { attackHeld: false, specialHeld: true, chargeRelease: false, xChargeRelease: false }, ground);
    assertTrue(xRow?.exact === true, `${id} X resolves an exact ROM record`);
  }

  // Contextual-B gates: G RED has both rows live; unknown ids have no decoded table.
  const gredGates = contextualBGatesForBorgId("pl0615");
  assertTrue(gredGates?.melee === true && gredGates?.shot === true, "G RED gates: both B rows live");
  assertEqual(contextualBGatesForBorgId("plzzzz"), null, "unknown borg -> no gates (compat path)");

  // Airborne record selection prefers the DERIVED air/elevated subtype-4 row where present.
  const records = commandMoveRecordsForBorgButton("pl0615", "B Shot");
  const hasAir = records.some((record) => record.subtype === 4);
  const airPick = selectCommandRecord(records, { meleeEngaged: false, airborne: true });
  if (hasAir) {
    assertEqual(airPick?.subtype ?? null, 4, "airborne selection picks the subtype-4 row");
  } else {
    assertTrue(airPick !== null, "airborne selection still returns a record without a subtype-4 row");
  }
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testCommandFamilyTable();
  testCommandEnumValuesMatchRom();
  testAttackCommandShape();
  testResolveCommandType();
  testCommandInputWord();
  testLiveCommandDispatch();

  testStandingContext();
  testGroundDashContext();
  testAirDashContext();
  testFlyingContext();
  testJumpRiseAndNeutralAir();
  testLandingContext();
  testJumpSequence();
  testFlyerBoostSequence();
  testDashContextsViaStepMovement();

  if (failures > 0) {
    console.error(`commandSchema.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`commandSchema.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
