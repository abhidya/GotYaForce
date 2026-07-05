// Selfcheck for the ROM-faithful actor runtime foundation.
// Run: pnpm build (combat) then node scripts/run-rom-tests.mjs
//
// Verifies the three foundation pieces compose correctly:
//  1. physics.integratePhysics reproduces the ROM's scalar-speed integration
//  2. dispatch.dispatchCommandRecord transitions state 61 → rootAction
//  3. The G RED family's phase-0 launch produces the documented upward impulse (Y=+4.0)

import { createRomActor } from "./actor.js";
import { integratePhysics } from "./physics.js";
import { dispatchCommandRecord, createDefaultStateTable, stepActor } from "./dispatch.js";
import { configureGRedFamily, type GRedFamilyCtx } from "../families/gred.js";
import { createRomStateTables, stepRomActor } from "./state-tables.js";
import type { StreamContext } from "./stream-vm.js";
import { RomDriverBridge } from "../bridge.js";
import type { BorgRuntime } from "../types.js";

const G_RED_LAUNCH_Y = 4.0;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

let failures = 0;
function assert(cond: boolean, msg: string): void {
  if (cond) {
    console.log(`  ok  ${msg}`);
  } else {
    console.error(`  FAIL  ${msg}`);
    failures++;
  }
}

export function runSelfTest(): number {
  failures = 0;

  // Test 1: physics integrator — upward impulse with no gravity produces linear rise.
  console.log("[rom.selfcheck] physics.integratePhysics — Y=+4 impulse, no gravity:");
  {
    const a = createRomActor();
    a.yVel = 4.0;
    a.hDecel = 0;
    a.gravityCoeff = 0;
    a.timescale = 1;
    a.tierScale = 1;
    a.dt = 1;
    a.maxFall = -9999;
    integratePhysics(1.0, a, 0);
    assert(approxEq(a.pos.y, 4.0), "frame 1 pos.y == 4.0 (linear rise)");
    assert(approxEq(a.yVel, 4.0), "yVel unchanged (gravityCoeff=0 → no decay)");
    integratePhysics(1.0, a, 0);
    assert(approxEq(a.pos.y, 8.0), "frame 2 pos.y == 8.0 (continues linearly)");
  }

  // Test 2: physics integrator — hSpeed projects via yaw.
  console.log("\n[rom.selfcheck] physics.integratePhysics — hSpeed × cos/sin(yaw):");
  {
    const a = createRomActor();
    a.hSpeed = 10.0;
    a.hDecel = 0;
    a.gravityCoeff = 0;
    a.timescale = 1;
    a.tierScale = 1;
    a.dt = 1;
    a.maxFall = -9999;
    integratePhysics(1.0, a, 0); // yaw 0 BAM = facing +Z
    assert(approxEq(a.pos.z, 10.0), "yaw 0 → pos.z += 10 (cos×hSpeed)");
    assert(approxEq(a.pos.x, 0.0), "yaw 0 → pos.x unchanged (sin=0)");
  }

  // Test 3: dispatch — command record cue 44 transitions to state 61 + runs family.
  console.log("\n[rom.selfcheck] dispatch — cue 44 → state 61 → rootAction:");
  {
    const a = createRomActor();
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.cueTable[44 * 2 + 1] = 0;
    let ran = false;
    a.rootAction = () => {
      ran = true;
    };
    const ok = dispatchCommandRecord(a, { cueId: 44, stateMode: 3, actionIndex: 2, variantIndex: 0 });
    assert(ok, "dispatchCommandRecord returned true for cue 44");
    assert(a.fbState === 61, "fbState transitioned to 61 (attack)");
    assert(a.actionIndex === 2, "actionIndex stamped to 2 (X / air-B)");
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(ran, "rootAction was invoked via state 61");
  }

  // Test 4: G RED family — phase 0 launch sets the documented impulse.
  console.log("\n[rom.selfcheck] families/gred — phase 0 launch impulse (Y=+4.0):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = {
      onArmHit: () => {},
      onPlayAnim: () => {},
      onFireChild: () => {},
    };
    configureGRedFamily(a, "pl0615", ctx);
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(approxEq(a.yVel, G_RED_LAUNCH_Y), `yVel == ${G_RED_LAUNCH_Y} (documented launch impulse)`);
    assert(approxEq(a.hSpeed, 0.0), "hSpeed == 0 (vertical-only launch)");
    assert(approxEq(a.gravityCoeff, 0.0), "gravityCoeff == 0 (no gravity during launch)");
    assert(a.fbPhaseSlots[0] === 1, "phase advanced to 1 (air-dash) for next frame");
  }

  if (failures > 0) {
    console.error(`\n[rom.selfcheck] ${failures} FAILURES`);
    return 1;
  }
  console.log("\n[rom.selfcheck] ALL PASS — foundation composes correctly.");
  return 0;
}

// Test 5: state tables — full-body state 1 (idle-stream) ticks without error and
// state 0 (noop) is a bare no-op. Confirms the table is populated + dispatches.
runStateTableTests();

// Test 6: bridge — pressing X on a G RED BorgRuntime triggers the ROM phase machine
// and produces the documented upward launch via the BorgRuntime-level sync path.
runBridgeTest();

function makeMinimalGRedBorg(): BorgRuntime {
  // Minimal BorgRuntime sufficient for the bridge — only the fields bridge.syncIn /
  // tryStartXSpecial read. Mirrors the shape battle.ts spawns.
  return {
    uid: "test-gred",
    borgId: "pl0615",
    team: 0,
    ownerPlayer: "p1",
    hp: 200, maxHp: 200,
    pos: { x: 0, y: 0, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: false,
    airJumps: 0,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 5,
    cooldowns: { boostFuel: 90, jumpHeld: 0 },
    invincTimer: 0,
    balanceGauge: 100, balanceGaugeMax: 100,
    downGauge: 100, downGaugeBase: 100,
    balanceRefillDelay: 0, downResetDelay: 0,
    comboWindow: 0, comboAccum: 0, comboRank: 0,
    paramTier: { tier: 0x10, deltaAccum: 0, timerFrames: 0 },
    statusId: 0, statusTimer: 0, statusImmunityMask: 0,
    lockTarget: null, allyLockTarget: null,
    burstArmFrames: 0, burstActive: false, burstPaired: false,
    fusionPartnerUid: null, fusionState: 0,
    defeatAccounted: false, alive: true,
    romDriver: null,
  } as unknown as BorgRuntime;
}

function runBridgeTest(): void {
  console.log("\n[rom.selfcheck] bridge — BorgRuntime-level X press triggers ROM launch:");
  const b = makeMinimalGRedBorg();
  const driver = RomDriverBridge.attach(b, {});
  assert(driver !== null, "RomDriverBridge.attach returned a driver for pl0615");
  if (!driver) return;
  b.romDriver = driver;
  // Simulate the combat.ts X-special branch calling tryStartXSpecial.
  const handled = b.romDriver!.tryStartXSpecial(b, [b]);
  assert(handled, "tryStartXSpecial returned true (ROM family handled the X press)");
  // Phase 0 ARMS the impulse (sets yVel=4.0) but the bridge now COMPOSES with
  // normal movement (returns false from tick) rather than taking over. The G RED
  // custom handler still sets velocity via syncOut.
  assert(b.vel.y > 0, `bridge syncOut produced upward vel.y (got ${b.vel.y.toFixed(3)})`);
  assert((b.cooldowns["romSpecialActive"] ?? 0) === 1, "romSpecialActive cooldown flag set");
  // Tick now returns false (composes with normal movement, doesn't skip it).
  const owned = b.romDriver!.tick(b, 1, [b]);
  assert(!owned, "tick returns false (bridge composes with normal movement, not replacing it)");
}

function runStateTableTests(): void {
  console.log("\n[rom.selfcheck] state-tables — populated table dispatches by state value:");
  {
    const tables = createRomStateTables();
    const a = createRomActor();
    const ctx: StreamContext = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    // State 0 = noop — should not throw, should not mutate.
    a.fbState = 0;
    a.ubState = 0;
    const before = JSON.stringify({ hs: a.hSpeed, yv: a.yVel, p: a.pos });
    stepRomActor(a, tables, ctx);
    const after = JSON.stringify({ hs: a.hSpeed, yv: a.yVel, p: a.pos });
    assert(before === after, "state 0 (noop) did not mutate actor");
    // Every state index in the dumped table (0..63) must resolve to a handler.
    let resolved = 0;
    for (let s = 0; s < 64; s++) {
      if (tables.fullBody[s] && tables.upperBody[s]) resolved++;
    }
    assert(resolved === 64, `all 64 state slots have handlers (got ${resolved})`);
    // State 61 still routes to the family virtual via runState61.
    let ran = false;
    a.fbState = 61;
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    configureGRedFamily(a, "pl0615", ctx);
    // Capture phase-0 launch via the state-table path (not the direct stepActor path).
    const prevY = a.yVel;
    stepRomActor(a, tables, ctx);
    ran = a.yVel !== prevY || a.fbPhaseSlots[0] === 1;
    assert(ran, "state 61 still routes to the G RED family virtual via the state table");
  }
}
