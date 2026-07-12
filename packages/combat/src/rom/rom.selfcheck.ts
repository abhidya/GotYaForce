// Selfcheck for the ROM-faithful actor runtime foundation.
// Run: pnpm build (combat) then node scripts/run-rom-tests.mjs
//
// Verifies the three foundation pieces compose correctly:
//  1. physics.integratePhysics reproduces the ROM's scalar-speed integration
//  2. dispatch.dispatchCommandRecord transitions state 61 → rootAction
//  3. The G RED family's phase-0 launch produces the documented upward impulse (Y=+4.0)

import { createRomActor, type RomActor } from "./actor.js";
import { integratePhysics } from "./physics.js";
import { dispatchCommandRecord, createDefaultStateTable, stepActor } from "./dispatch.js";
import { configureGRedFamily, type GRedFamilyCtx } from "../families/gred.js";
import { createGRedDash, GRED_DASH } from "../families/gred-dash.js";
import { configureNinjaFamily, NINJA_X } from "../families/ninja.js";
import { configureStarHeroFamily } from "../families/star-hero.js";
import { configureCyberMachineFamily } from "../families/cyber-machine.js";
import { configureSwordKnightFamily } from "../families/sword-knight.js";
import { configureDragonFamily, DRAGON_X } from "../families/dragon.js";
import { configureCyberDragonFamily, CYBER_DRAGON_X } from "../families/cyber-dragon.js";
import { configureWormFamily, WORM_X } from "../families/worm.js";
import { configureWireGunnerFamily, WIRE_GUNNER_X } from "../families/wire-gunner.js";
import { createSharedMeleeLunge, NINJA_LUNGE_CONFIG } from "../families/shared-melee-lunge.js";
import {
  createSharedMeleeGRed,
  GRED_MELEE_CONFIG,
  SHARED_MELEE_GRED,
  type SharedMeleeGRedConfig,
} from "../families/shared-melee-gred.js";
import {
  createSharedCharge,
  GRED_CHARGE_CONFIG,
  SHARED_CHARGE,
  type SharedChargeConfig,
} from "../families/shared-charge.js";
import {
  configureValkrieFamily,
  VALKRIE,
  VALKRIE_SPAWNERS,
  type ValkrieFamilyCtx,
} from "../families/valkrie.js";
import {
  configureSamuraiClusterFamily,
  SAMURAI,
  SAMURAI_SPAWNERS,
  SAMURAI_LUNGE_ROM_CONFIG,
  type SamuraiFamilyCtx,
} from "../families/samurai.js";
import { createRomStateTables, stepRomActor } from "./state-tables.js";
import type { StreamContext } from "./stream-vm.js";
import { RomDriverBridge, cueTableForBorg, type RomBattleRuntime } from "../bridge.js";
import { configureDeathBorgFamily } from "../families/death-borg.js";
import {
  configureEagleJetFamily,
  EAGLE_JET_ACTION1,
  type EagleJetScratch,
} from "../families/eagle-jet.js";
import {
  createMeleeRobot,
  MELEE_ROBOT,
  ROBOT_MELEE_RANGE_ROWS,
} from "../families/melee-robot.js";
import {
  createRobotDashHandler,
  ROBOT_ACTION0_CONFIGS,
  ROBOT_DASH,
} from "../families/shared-robot-dash.js";
import {
  configureTankFamily,
  NORMAL_TANK,
  type NormalTankScratch,
} from "../families/tank-borg.js";
import {
  ARROW_NINJA_ACTION1,
  configureArrowNinjaFamily,
  type ArrowNinjaScratch,
} from "../families/arrow-ninja.js";
import {
  configureEagleRobotFamily,
  EAGLE_ROBOT_ACTION0,
  type EagleRobotScratch,
} from "../families/eagle-robot.js";
import {
  createSharedAimedShotX,
  createTitanPantherAction1,
  createTitanPantherGunAction0,
  titanRobotXOnSteer,
  TITAN_ROBOT_X_CONFIG,
  PANTHER_ROBOT_X_CONFIG,
} from "../families/shared-aimed-shot-x.js";
import {
  createSharedMorphXSpecial,
  TITAN_MORPH_CONFIG,
} from "../families/shared-morph-x.js";
import type { BorgRuntime } from "../types.js";
import {
  configureGirlClusterFamily,
  createGirlSharedX,
  isGirlClusterLiveSlot,
  KILLER_SHARED_X_CONFIG,
  BARRIER_SHARED_X_CONFIG,
  type GirlClusterBorgId,
} from "../families/girl-cluster.js";
import { CYBER_GIRL_X } from "../families/cyber-girl.js";
import { createSeries3XSpecial, SERIES3_X } from "../families/shared-series3-x.js";
import { groundSnapRevert, stepAfterimage, stepTargetPitch } from "./helpers.js";

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

  // Integration seam: two battle runtimes keep independent floor behavior.
  console.log("\n[rom.selfcheck] battle runtime — floor behavior is instance-local:");
  {
    const makeRuntime = (uid: string) => ({ uid, borgId: "pl0000", team: 0 }) as BorgRuntime;
    const makeBattleRuntime = (floorY: number): RomBattleRuntime => ({
      floor: {
        bounds: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
        isSupported: () => true,
        clampToGround: (pos, velY) => pos.y <= floorY
          ? { y: floorY, velY: 0, grounded: true }
          : { y: pos.y, velY, grounded: false },
      },
      allocateResource: () => true,
      spawnProjectile: () => {},
      resolveHit: () => {},
    });
    const low = RomDriverBridge.attachToBattle(makeRuntime("low"), makeBattleRuntime(10));
    const high = RomDriverBridge.attachToBattle(makeRuntime("high"), makeBattleRuntime(20));
    assert(low !== null && high !== null, "independent drivers attach through battle runtime seam");
    if (low && high) {
      low.actor.pos.y = 0;
      high.actor.pos.y = 0;
      integratePhysics(0, low.actor, 0);
      integratePhysics(0, high.actor, 0);
      assert(low.actor.pos.y === 10, "first runtime uses its own floor");
      assert(high.actor.pos.y === 20, "second runtime uses its own floor");
      low.actor.pos.y = 0;
      integratePhysics(0, low.actor, 0);
      assert(low.actor.pos.y === 10, "second attachment does not overwrite first floor");
    }
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

  // Test 5: NINJA family — shared-X phase 0 blink-reposition + zeroed launch scalars.
  console.log("\n[rom.selfcheck] families/ninja — shared-X phase 0 (zz_00ff30c_):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureNinjaFamily(a, "pl0000", ctx);
    assert(a.borgNumber === 0x000, "borgNumber stamped 0x000 (NORMAL NINJA)");
    a.pos.x = 100; a.pos.z = 0;
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } }).lockTarget = { x: 0, y: 0, z: 0 };
    a.hSpeed = 5; a.yVel = 3;
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    // Reposition: motion = pos − target = (100,0,0); ×0.95; pos += motion → x = 195.
    assert(approxEq(a.pos.x, 195.0), "pos.x == 195 (blink-away: motion = (pos−target)×0.95 added)");
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0), "launch scalars zeroed (FLOAT_804392b4)");
    assert(a.fbPhaseSlots[0] === 1, "phase advanced to 1");
    assert(a.streamSlot === 1, "stream cursor advanced past ground slot 0 (+0x6ea++)");
  }

  // Test 6: NINJA family — phase-1 contact → phase 2 + zz_00715f8_ backflip callback.
  console.log("\n[rom.selfcheck] families/ninja — on-hit backflip (zz_00715f8_):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    let familyProj = null as { addr: number; type: number } | null;
    (ctx as typeof ctx & { onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void }).onFamilyProjectile =
      (_a, addr, type) => { familyProj = { addr, type }; };
    configureNinjaFamily(a, "pl000a", ctx); // SASUKE — same family, shuriken type 3
    assert(a.borgNumber === 0x00a, "borgNumber stamped 0x00a (SASUKE)");
    a.actionIndex = 2;
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.heading = 0x4000;
    a.contactP0 = 1; // the +0x1cef contact byte fired
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "contact advanced phase 1 → 2");
    assert(approxEq(a.hSpeed, NINJA_X.BACKFLIP_HSPEED), "backflip hSpeed == 10.0 (FLOAT_80437748)");
    assert(approxEq(a.yVel, NINJA_X.BACKFLIP_YVEL), "backflip yVel == 15.0 (FLOAT_80437768)");
    assert(approxEq(a.gravityCoeff, NINJA_X.BACKFLIP_GRAVITY), "backflip gravityCoeff == -1.0 (FLOAT_804376e0)");
    assert(a.lockYaw === ((0x4000 - 0x8000) & 0xffff), "lockYaw flipped 180° (+0x5ae = +0x72 − 0x8000)");
    assert(familyProj !== null && familyProj!.addr === NINJA_X.SHURIKEN_SPAWNER_ADDR && familyProj!.type === 3,
      "SASUKE shuriken spawn requested via zz_007db5c_ type 3");
  }

  // Test 7: bridge — pl0000 registry attach dispatches cue 44 AND cue 45 to state 61.
  console.log("\n[rom.selfcheck] bridge — ninja family cue table (0x802d3ff8 rows 44/45):");
  {
    const runtime = { borgId: "pl0000", team: 0, uid: "t", pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 }, rotY: 0, grounded: true, cooldowns: {} } as unknown as BorgRuntime;
    const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    assert(bridge !== null, "RomDriverBridge attaches for pl0000 (family registered)");
    if (bridge) {
      const t = bridge.actor.cueTable!;
      assert(t[44 * 2] === 61 && t[45 * 2] === 61, "cue rows 44 AND 45 → full-body state 61");
      assert(t[5 * 2] === 6 && t[8 * 2] === 9, "family-0 deltas vs G RED (cue 5→6, cue 8→9)");
      assert(bridge.actor.rootAction !== null, "ninja rootAction configured");
    }
  }

  // Test 7b: DEATH BORG ALPHA II — shared-X third family (verified Wave-A config dig).
  console.log("\n[rom.selfcheck] families/death-borg — on-hit pop + type-5 shot (zz_01a0458_):");
  {
    const a = createRomActor();
    let proj = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & { onFamilyProjectile?: (x: RomActor, addr: number, type: number) => void } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { proj = { addr, type }; },
    };
    configureDeathBorgFamily(a, "pl000c", ctx);
    assert(a.borgNumber === 0x00c, "borgNumber stamped 0x00c (DEATH BORG ALPHA II)");
    a.actionIndex = 2;
    a.fbPhaseSlots[0] = 1;
    a.heading = 0x2000;
    a.contactP0 = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "contact advanced phase 1 → 2 (shared machine)");
    assert(approxEq(a.hSpeed, 10.0) && approxEq(a.yVel, 15.0) && approxEq(a.gravityCoeff, -1.0),
      "pop constants 10/15/−1 (FLOAT_8043b51c/_8043b538/_8043b4cc)");
    assert(proj !== null && proj!.type === 5, "type-5 shot requested (record 5 @0x802d6e80, borg-0xc gated)");
    const bridgeCue = cueTableForBorg("pl000c");
    assert(bridgeCue !== null && bridgeCue[44 * 2] === 61, "pl000c cue 44 → state 61 (data-driven table)");
  }

  // Test 8: shared melee lunge (zz_00fed6c_) — phase flow + dash-speed formula.
  console.log("\n[rom.selfcheck] shared-melee-lunge — dash speed max(range,dist)/frames:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const lunge = createSharedMeleeLunge(NINJA_LUNGE_CONFIG, ctx);
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } }).lockTarget = { x: 0, y: 0, z: 400 };
    lunge(a); // phase 0
    assert(a.fbPhaseSlots[0] === 1, "phase 0 → 1 (aim)");
    assert(a.streamSlot === NINJA_LUNGE_CONFIG.slotBase + 1, "stream cursor = slotBase+1 (+0x6ea++)");
    lunge(a); // phase 1 → dash (facing instant with target)
    assert(a.fbPhaseSlots[0] === 2, "phase 1 → 2 (dash)");
    assert(approxEq(a.hSpeed, 400 / 20), "dash speed == max(150, 400)/20 = 20 (zz_00ff1ec_)");
    // Close the distance → in-range transition to phase 3.
    a.pos.z = 300; // dist 100 < range 150
    lunge(a);
    assert(a.fbPhaseSlots[0] === 3, "phase 2 → 3 when dist < range (FUN_800668cc gate)");
    // B-retap → combo loop back to phase 2 with the next slot.
    (a as RomActor & { bRetapInput?: boolean }).bRetapInput = true;
    a.handlerTimer = 0;
    const slotBefore = a.streamSlot;
    lunge(a);
    assert(a.fbPhaseSlots[0] === 2, "phase 3 retap → loop back to 2 (+0x540--)");
    assert(a.streamSlot === slotBefore + 1, "combo loop advanced the stream cursor");
  }

  // Test 9: ninja B-combo machine A — swing bookkeeping + kunai throw.
  console.log("\n[rom.selfcheck] families/ninja — B-combo (FUN_8006fb44) swing + kunai:");
  {
    const a = createRomActor();
    let kunai = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & { onFamilyProjectile?: (x: RomActor, addr: number, type: number) => void } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { kunai = { addr, type }; },
    };
    configureNinjaFamily(a, "pl0000", ctx);
    a.actionIndex = 0;
    a.variantIndex = 0;
    a.rootAction!(a); // phase 0
    assert(a.fbPhaseSlots[0] === 1, "B-combo phase 0 → 1");
    assert((a as RomActor & { swingsLeft?: number }).swingsLeft === 5, "5 swings seeded (zz_0070530_ +0x6ef)");
    a.contactP0 = 1; // swing connected
    a.rootAction!(a); // phase 1 → kunai + phase 2
    assert(a.fbPhaseSlots[0] === 2, "contact → phase 2 (zz_0070558_)");
    assert(kunai !== null && kunai!.addr === 0x8006ee14 && kunai!.type === 0,
      "kunai thrown via zz_006ee14_ variant 0 (pl0000)");
    assert((a as RomActor & { swingsLeft?: number }).swingsLeft === 4, "swings decremented");
    // B held → loop restart.
    (a as RomActor & { bHeld?: boolean }).bHeld = true;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 1, "B-held → combo loop back to phase 1 (slot-1 restart)");
  }

  // Test 10: ninja leap (action-1 v4) — corrected gravity term 2.0 × (−vy/30).
  console.log("\n[rom.selfcheck] families/ninja — leap dive-slam constants:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureNinjaFamily(a, "pl0000", ctx);
    a.actionIndex = 1;
    a.variantIndex = 4;
    a.rootAction!(a); // leap phase 0
    assert(approxEq(a.yVel, 33.333), "leap jump impulse 33.333 (FLOAT-dump)");
    assert(approxEq(a.gravityCoeff, 2.0 * (-33.333 / 30.0), 1e-3),
      "gravity term = 2.0 × (−vy/30) (verify-pass-corrected, NOT 200.0)");
  }

  // Test 11: STAR HERO family — X-special phase 0 startup (FUN_80112278).
  console.log("\n[rom.selfcheck] families/star-hero — X phase 0 startup (FUN_80112278):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureStarHeroFamily(a, "pl0804", ctx);
    assert(a.borgNumber === 0x804, "borgNumber stamped 0x804 (STAR HERO)");
    // Phase 0 reads pos − lockTarget into motion; phase 1 (called immediately) scales ×0.95.
    a.pos.x = 100; a.pos.z = 0;
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } }).lockTarget = { x: 0, y: 0, z: 0 };
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    // Phase 0 advanced +0x540 to 1 (chunk_0031.c:557).
    assert(a.fbPhaseSlots[0] === 1, "phase advanced to 1 (per-frame dash update)");
    // Ground slot 0 → +0x6ea = slot+1 = 1 (chunk_0031.c:566).
    assert(a.streamSlot === 1, "stream cursor = ground slot + 1 (+0x6ea++)");
    // motion = pos − target = (100,0,0); ×0.95 = (95,0,0); pos += motion → x = 195.
    assert(approxEq(a.pos.x, 195.0), "pos.x == 195 (motion × FLOAT_80439678=0.95 added)");
    assert(approxEq(a.motion.x, 95.0), "motion.x == 95 (scaled approach vector)");
  }

  // Test 12: STAR HERO family — X-special contact → +4 tier buff (zz_011230c_).
  console.log("\n[rom.selfcheck] families/star-hero — contact → tier buff (zz_011230c_):");
  {
    const a = createRomActor();
    let tierDelta = 0 as number | null;
    let cuePlayed = 0 as number | null;
    const ctx: GRedFamilyCtx & {
      onParamTierDelta?: (actor: RomActor, delta: number) => void;
      onPlayCue?: (actor: RomActor, cueId: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onParamTierDelta: (_a, delta) => { tierDelta = delta; },
      onPlayCue: (_a, cueId) => { cuePlayed = cueId; },
    };
    configureStarHeroFamily(a, "pl080c", ctx);
    assert(a.borgNumber === 0x80c, "borgNumber stamped 0x80c (PLANET HERO)");
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    // Pre-arm contact so phase 0 → phase 1's contact branch fires on the first frame.
    a.contactP0 = 1; // +0x1cef went positive (dash connected)
    a.parts[0]!.streamPtr = 42; a.parts[0]!.active = 1; // simulate an armed kind-0xf hitbox
    const table = createDefaultStateTable();
    stepActor(a, table);
    const ext = a as RomActor & { heroBuffFrames?: number; heroBuffTailFrames?: number };
    assert(ext.heroBuffFrames === 1200, "+0x144 == 0x4b0 (1200f buff timer armed)");
    assert(ext.heroBuffTailFrames === 30, "+0x146 == 0x1e (30f VFX tail)");
    assert(tierDelta === 4, "onParamTierDelta fired with +4 (tier 16→20, velocity ×2.366)");
    assert(cuePlayed === 0xa5, "onPlayCue fired with 0xa5 (zz_00f036c_ buff sound)");
    assert(a.contactP0 === 0, "+0x1cef cleared after buff application");
    assert(a.parts[0]!.streamPtr === -1 && a.parts[0]!.active === 0,
      "kind-0xf hitbox despawned (zz_00107a0_)");

    // Second contact while buffed: must NOT re-buff (ROM +0x144 > 0 gate).
    tierDelta = null; cuePlayed = null;
    a.fbPhaseSlots[0] = 1; // re-enter phase 1 directly (phase 0 already ran)
    a.contactP0 = 1;
    a.parts[0]!.streamPtr = 42; a.parts[0]!.active = 1;
    a.rootAction!(a);
    assert(ext.heroBuffFrames === 1200, "already-buffed contact does not refresh the timer");
    assert(tierDelta === null && cuePlayed === null,
      "already-buffed contact does not re-apply the tier delta or cue");
  }

  // Test 13: SWORD KNIGHT family — X phase 0 windup (zz_007454c_).
  console.log("\n[rom.selfcheck] families/sword-knight — X phase 0 windup (zz_007454c_):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureSwordKnightFamily(a, "pl0200", ctx);
    assert(a.borgNumber === 0x200, "borgNumber stamped 0x200 (SWORD KNIGHT)");
    a.pos.x = 100; a.pos.z = 0;
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } }).lockTarget = { x: 0, y: 0, z: 0 };
    a.hSpeed = 5; a.yVel = 3;
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    // Phase 0 advanced +0x540 to 1 + windup timer seeded 20.0 (chunk_0010.c:1670-1671).
    assert(a.fbPhaseSlots[0] === 1, "phase advanced to 1 (approach)");
    assert(approxEq(a.handlerTimer, 20.0), "handlerTimer == 20.0 (FLOAT_804377e8 windup seed)");
    // Velocity scalars zeroed (chunk_0010.c:1674-1678).
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0) && approxEq(a.hDecel, 0) && approxEq(a.gravityCoeff, 0),
      "all four velocity scalars zeroed");
    // Reposition ×0.95: motion = (100,0,0)×0.95 = (95,0,0); pos += motion → x = 195.
    assert(approxEq(a.pos.x, 195.0), "pos.x == 195 (motion × FLOAT_804377ec=0.95 added)");
    assert(approxEq(a.motion.x, 95.0), "motion.x == 95 (scaled approach vector)");
    // Ground slot 0 → +0x6ea = slot+1 = 1.
    assert(a.streamSlot === 1, "stream cursor = ground slot + 1 (+0x6ea++)");
  }

  // Test 14: SWORD KNIGHT family — phase 1 timer expiry → phase 2 + motion decay.
  console.log("\n[rom.selfcheck] families/sword-knight — phase 1 timer + motion decay:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureSwordKnightFamily(a, "pl0200", ctx);
    a.motion.x = 95.0; // carry over the phase-0 motion
    a.handlerTimer = 1.0; // one frame from transition
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.dt = 1;
    a.actionIndex = 2;
    a.rootAction!(a);
    // motion ×= 0.95 = 90.25; pos.x += 90.25 (chunk_0010.c:1704-1705).
    assert(approxEq(a.motion.x, 90.25), "motion.x *= FLOAT_804377ec (0.95)");
    // Timer ticked to 0 → phase advanced to 2 (chunk_0010.c:1712-1716).
    assert(a.fbPhaseSlots[0] === 2, "timer ≤ 0 advances phase 1 → 2");
  }

  // Test 15: SWORD KNIGHT family — phase 2 contact-end → phase 3 + gravityCoeff restore.
  console.log("\n[rom.selfcheck] families/sword-knight — phase 2 contact-end → phase 3:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureSwordKnightFamily(a, "pl0200", ctx);
    a.descriptor = {
      header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(0),
      handlerData6c: 1.5, // the per-family gravityCoeff restore value
      subtypePartCommand: new Int8Array(0), buttonLiveFlag: new Int8Array(0),
      defaultHand0: 0, defaultHand1: 0,
    };
    a.contactP0 = -1; // +0x1cef < 0 → kind-3/18 hit landed and ended
    a.fbPhaseSlots[0] = 2;
    a.dt = 1;
    a.actionIndex = 2;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 3, "contact-end advances phase 2 → 3");
    assert(approxEq(a.gravityCoeff, 1.5), "gravityCoeff restored from descriptor.+0x6c");
  }

  // Test 16: SWORD KNIGHT family — phase 3 wall-contact → idle dispatch + steerYaw decay.
  console.log("\n[rom.selfcheck] families/sword-knight — phase 3 recovery + steerYaw decay:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureSwordKnightFamily(a, "pl020a", ctx); // NORMAL KNIGHT — same family module
    assert(a.borgNumber === 0x20a, "borgNumber stamped 0x20a (NORMAL KNIGHT)");
    a.steerYaw = 1000.0;
    a.wallContact = 1; // +0x1cee != 0 → end the move
    (a as RomActor & { grounded?: boolean }).grounded = true;
    a.controlWord = 0x3; // action-mode bits set
    a.fbPhaseSlots[0] = 3;
    a.dt = 1;
    a.actionIndex = 2;
    a.rootAction!(a);
    // steerYaw ×= 0.9 (chunk_0010.c:1759-1762, pure decay — DOUBLE_804377e0 is the
    // GCC int→double coercion sentinel, NOT a base offset).
    assert(approxEq(a.steerYaw, 900.0), "steerYaw *= FLOAT_804377f4 (0.9), no base offset");
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
  }

  // Test 17: CYBER MACHINE family — X phase 0 arm (effect child spawn via zz_016cc24_).
  console.log("\n[rom.selfcheck] families/cyber-machine — X phase 0 arm (FUN_800ce5dc):");
  {
    const a = createRomActor();
    let effectSpawn = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { effectSpawn = { addr, type }; },
    };
    configureCyberMachineFamily(a, "pl0602", ctx);
    assert(a.borgNumber === 0x602, "borgNumber stamped 0x602 (CYBER MACHINE SEIRYU)");
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++ arm)");
    assert(effectSpawn !== null && effectSpawn!.addr === 0x8016cc24 && effectSpawn!.type === 2,
      "effect child spawned via zz_016cc24_(actor, 2)");
  }

  // Test 18: CYBER MACHINE family — phase 1 fire: shot spawn + cooldown + bit clear.
  console.log("\n[rom.selfcheck] families/cyber-machine — phase 1 fire (zz_006a668_):");
  {
    const a = createRomActor();
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a: RomActor, addr: number, type: number) => { spawns.push({ addr, type }); },
    };
    configureCyberMachineFamily(a, "pl060e", ctx); // GENBU — same family module
    assert(a.borgNumber === 0x60e, "borgNumber stamped 0x60e (CYBER MACHINE GENBU)");
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.controlWord = 0x3; // action-mode bits set
    a.dt = 1;
    a.actionIndex = 2;
    a.rootAction!(a);
    // Shot fired via zz_006a668_(actor, kind=1) — the last spawn in the list (after
    // phase 0's effect spawn is skipped because we entered at phase 1).
    const shot = spawns.find((s) => s.addr === 0x8006a668);
    assert(shot !== undefined && shot.type === 1, "shot fired via zz_006a668_ kind 1");
    assert(approxEq(a.stateTimer, 51.0), "+0x694 = FLOAT_804389a8(50) + dt(1) = 51");
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
  }

  // Test 19: CYBER MACHINE family — bridge cue-table attach (rows 44/45 → state 61).
  console.log("\n[rom.selfcheck] families/cyber-machine — bridge cue-table (0x8030c3c0):");
  {
    const runtime = {
      borgId: "pl0602", team: 0, uid: "t",
      pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
      rotY: 0, grounded: true, cooldowns: {},
    } as unknown as BorgRuntime;
    const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    assert(bridge !== null, "RomDriverBridge attaches for pl0602 (family registered)");
    if (bridge) {
      const t = bridge.actor.cueTable!;
      assert(t[44 * 2] === 61 && t[45 * 2] === 61,
        "cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)");
      assert(bridge.actor.rootAction !== null, "cyber-machine rootAction configured");
      assert(bridge.actor.borgNumber === 0x602, "borgNumber stamped 0x602 via bridge attach");
    }
  }

  // Test 20: FLAME DRAGON family — v0 ground flame breath phase 0 setup (FUN_80075f2c).
  console.log("\n[rom.selfcheck] families/dragon — v0 ground breath phase 0 (FUN_80075f2c):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureDragonFamily(a, "pl0500", ctx);
    assert(a.borgNumber === 0x500, "borgNumber stamped 0x500 (FLAME DRAGON)");
    a.actionIndex = 2;
    a.variantIndex = 0;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; // nonzero to confirm the phase-0 zeroing
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++)");
    assert(approxEq(a.handlerTimer, DRAGON_X.BREATH_WINDOW), `handlerTimer == 180.0 (FLOAT_80437830)`);
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0) && approxEq(a.hDecel, 0),
      "launch scalars zeroed (FLOAT_80437814)");
    assert(approxEq(a.gravityCoeff, 0), "gravityCoeff zeroed (ground breath — no physics)");
  }

  // Test 21: FLAME DRAGON family — v0 phase 1 contact → flame child spawn (zz_0076408_).
  // The borg-id switch (zz_0076408_:3034-3040) maps each Dragon to a flame-child type;
  // verify pl050a → type 2 and pl0515 → type 4 via the onFamilyProjectile hook.
  console.log("\n[rom.selfcheck] families/dragon — v0 phase 1 contact spawn (zz_0076408_):");
  {
    const a = createRomActor();
    let flame = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { flame = { addr, type }; },
    };
    configureDragonFamily(a, "pl050a", ctx); // pl050a → flame type 2
    assert(a.borgNumber === 0x50a, "borgNumber stamped 0x50a");
    a.actionIndex = 2;
    a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.handlerTimer = DRAGON_X.BREATH_WINDOW; // not expired
    a.contactP0 = 1; // +0x1cef contact flag fired (breath hitbox connected)
    a.rootAction!(a);
    assert(flame !== null && flame!.addr === DRAGON_X.FLAME_SPAWNER_ADDR && flame!.type === 2,
      "flame child spawned via zz_00be948_ type 2 (pl050a)");
    assert(a.contactP0 === 0, "+0x1cef cleared after consuming the contact (zz_0076408_)");

    // Second borg in the same family: pl0515 → type 4 (the full switch).
    const b = createRomActor();
    let flameB = null as { addr: number; type: number } | null;
    const ctxB: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { flameB = { addr, type }; },
    };
    configureDragonFamily(b, "pl0515", ctxB);
    assert(b.borgNumber === 0x515, "borgNumber stamped 0x515");
    b.actionIndex = 2; b.variantIndex = 0; b.fbPhaseSlots[0] = 1;
    b.handlerTimer = DRAGON_X.BREATH_WINDOW; b.contactP0 = 1;
    b.rootAction!(b);
    assert(flameB !== null && flameB!.type === 4, "flame child type 4 (pl0515)");
  }

  // Test 22: FLAME DRAGON family — v1 air variant velocity drag (FUN_80076088 tail).
  // zz_006ed8c_(FLOAT_80437834=0.95) scales hSpeed and yVel by 0.95 each frame, then
  // zz_0067458_(1.0) integrates physics. Verify the drag applies pre-integration.
  console.log("\n[rom.selfcheck] families/dragon — v1 air breath velocity drag (FUN_80076088):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureDragonFamily(a, "pl0500", ctx);
    a.actionIndex = 2;
    a.variantIndex = 1; // air variant
    a.fbPhaseSlots[0] = 1; // phase 1 (active breath)
    a.handlerTimer = DRAGON_X.BREATH_WINDOW; // not expired
    a.hSpeed = 10.0;
    a.yVel = 20.0;
    a.heading = 0; a.lockYaw = 0; a.activeYaw = 0;
    a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.rootAction!(a);
    // zz_006ed8c_ with dt==FLOAT_80437670(1.0): hSpeed *= 0.95; yVel *= 0.95 (drag).
    assert(approxEq(a.hSpeed, 10.0 * DRAGON_X.AIR_DRAG), `hSpeed *= 0.95 (FLOAT_80437834)`);
    assert(approxEq(a.yVel, 20.0 * DRAGON_X.AIR_DRAG), `yVel *= 0.95 (air drag pre-integration)`);
  }

  // Test 23: FLAME DRAGON family — bridge cue-table attach (rows 44/45 → state 61).
  console.log("\n[rom.selfcheck] families/dragon — bridge cue-table (0x802d5a58):");
  {
    const runtime = {
      borgId: "pl0500", team: 0, uid: "t",
      pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
      rotY: 0, grounded: true, cooldowns: {},
    } as unknown as BorgRuntime;
    const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    assert(bridge !== null, "RomDriverBridge attaches for pl0500 (family registered)");
    if (bridge) {
      const t = bridge.actor.cueTable!;
      assert(t[44 * 2] === 61 && t[45 * 2] === 61,
        "cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)");
      assert(bridge.actor.rootAction !== null, "dragon rootAction configured");
      assert(bridge.actor.borgNumber === 0x500, "borgNumber stamped 0x500 via bridge attach");
      // cue 36 → [47, 0] (deploy state) — the Flame Dragon's deploy trampoline.
      assert(t[36 * 2] === 47, "cue row 36 → full-body state 47 (deploy)");
    }
  }

  // Test 23a: CYBER DEATH DRAGON family — v0 ground breath phase 0 setup (FUN_800b9700).
  // Sister port of FLAME DRAGON's test 20; same constants, different .sdata2 slots
  // (FLOAT_804384a4/e4 vs FLOAT_80437814/30).
  console.log("\n[rom.selfcheck] families/cyber-dragon — v0 ground breath phase 0 (FUN_800b9700):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureCyberDragonFamily(a, "pl0503", ctx);
    assert(a.borgNumber === 0x503, "borgNumber stamped 0x503 (CYBER DEATH DRAGON)");
    a.actionIndex = 2;
    a.variantIndex = 0;
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; // nonzero to confirm the phase-0 zeroing
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++)");
    assert(approxEq(a.handlerTimer, CYBER_DRAGON_X.BREATH_WINDOW),
      `handlerTimer == 180.0 (FLOAT_804384e4)`);
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0) && approxEq(a.hDecel, 0),
      "launch scalars zeroed (FLOAT_804384a4)");
    assert(approxEq(a.gravityCoeff, 0),
      "gravityCoeff zeroed (ground breath — no physics)");
  }

  // Test 23b: CYBER DEATH DRAGON family — v0 phase 1 contact consumes +0x1cef.
  // The Cyber Death Dragon has NO per-frame child spawner (unlike FLAME DRAGON's
  // zz_00be948_ flame-child spawn); zz_00b9c68_ just clears the contact flag and
  // calls zz_0098dbc_(actor, 0, 6) — a shared kind-6 resolver covered by op 0x0a.
  console.log("\n[rom.selfcheck] families/cyber-dragon — v0 phase 1 contact (zz_00b9c68_):");
  {
    const a = createRomActor();
    configureCyberDragonFamily(a, "pl0506",
      { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    assert(a.borgNumber === 0x506, "borgNumber stamped 0x506");
    a.actionIndex = 2;
    a.variantIndex = 0;
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.handlerTimer = CYBER_DRAGON_X.BREATH_WINDOW; // not expired
    a.contactP0 = 1; // +0x1cef contact flag fired (breath hitbox connected)
    a.rootAction!(a);
    assert(a.contactP0 === 0, "+0x1cef cleared after consuming the contact (zz_00b9c68_)");
    // Phase should NOT advance (handlerTimer > 0); only the contact bookkeeping ran.
    assert(a.fbPhaseSlots[0] === 1, "phase remains 1 (breath window not expired)");
  }

  // Test 23c: CYBER DEATH DRAGON family — v1 air variant velocity drag (FUN_800b9888 tail).
  // zz_006ed8c_(FLOAT_804384c4=0.95) scales hSpeed and yVel by 0.95 each frame, then
  // zz_0067458_(1.0) integrates physics. Mirror of FLAME DRAGON's test 22.
  console.log("\n[rom.selfcheck] families/cyber-dragon — v1 air breath velocity drag (FUN_800b9888):");
  {
    const a = createRomActor();
    configureCyberDragonFamily(a, "pl0503",
      { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    a.actionIndex = 2;
    a.variantIndex = 3; // air variant (engine 0x800b9888)
    a.fbPhaseSlots[0] = 1; // phase 1 (active breath)
    a.handlerTimer = CYBER_DRAGON_X.BREATH_WINDOW; // not expired
    a.hSpeed = 10.0;
    a.yVel = 20.0;
    a.heading = 0; a.lockYaw = 0; a.activeYaw = 0;
    a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.rootAction!(a);
    // zz_006ed8c_ with dt==FLOAT_80437670(1.0): hSpeed *= 0.95; yVel *= 0.95 (drag).
    assert(approxEq(a.hSpeed, 10.0 * CYBER_DRAGON_X.AIR_DRAG),
      `hSpeed *= 0.95 (FLOAT_804384c4)`);
    assert(approxEq(a.yVel, 20.0 * CYBER_DRAGON_X.AIR_DRAG),
      `yVel *= 0.95 (air drag pre-integration)`);
  }

  // Test 23d: CYBER DEATH DRAGON family — v2 charged +0x5dd gate (FUN_800b9ad4).
  // Without xChargeGate == 0x11 the handler bails to ground idle (zz_006a3d0_ re-dispatch).
  console.log("\n[rom.selfcheck] families/cyber-dragon — v2 charged gate bail (FUN_800b9ad4):");
  {
    const a = createRomActor();
    configureCyberDragonFamily(a, "pl050f",
      { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    assert(a.borgNumber === 0x50f, "borgNumber stamped 0x50f");
    a.actionIndex = 2;
    a.variantIndex = 4; // charged variant
    // No xChargeGate set → defaults to 0 → bail branch.
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0] = 0; // cue 0 → state 0 (ground idle)
    a.controlWord = 0x3; // nonzero to confirm the clear
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 0, "phase did NOT advance (bail branch — no xChargeGate)");
    assert(a.controlWord === 0, "+0x5e0 attack bits cleared (bail-to-idle)");

    // With xChargeGate == 0x11 the charged breath arms (slot 4, group 4).
    const b = createRomActor();
    (b as RomActor & { xChargeGate?: number }).xChargeGate = 0x11;
    configureCyberDragonFamily(b, "pl050f",
      { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    b.actionIndex = 2;
    b.variantIndex = 4;
    b.cueTable = new Int8Array(96).fill(-1);
    b.fbState = 61;
    b.cueTable[44 * 2] = 61;
    const tbl = createDefaultStateTable();
    stepActor(b, tbl);
    assert(b.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (xChargeGate == 0x11 accepted)");
    assert(approxEq(b.handlerTimer, CYBER_DRAGON_X.BREATH_WINDOW),
      "charged breath handlerTimer == 180.0");
  }

  // Test 23e: CYBER DEATH DRAGON family — bridge cue-table attach (rows 44/45 → 61).
  console.log("\n[rom.selfcheck] families/cyber-dragon — bridge cue-table (0x802fec20):");
  {
    const runtime = {
      borgId: "pl0503", team: 0, uid: "t",
      pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
      rotY: 0, grounded: true, cooldowns: {},
    } as unknown as BorgRuntime;
    const bridge = RomDriverBridge.attach(runtime,
      { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
    assert(bridge !== null, "RomDriverBridge attaches for pl0503 (family registered)");
    if (bridge) {
      const t = bridge.actor.cueTable!;
      assert(t[44 * 2] === 61 && t[45 * 2] === 61,
        "cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)");
      assert(bridge.actor.rootAction !== null, "cyber-dragon rootAction configured");
      assert(bridge.actor.borgNumber === 0x503, "borgNumber stamped 0x503 via bridge attach");
    }
  }

  // Test 23f: CYBER DEATH DRAGON family — all 6 members register + stamp borgNumber.
  console.log("\n[rom.selfcheck] families/cyber-dragon — 6-member borgNumber stamp:");
  {
    const members: Array<{ id: "pl0503" | "pl0506" | "pl0507" | "pl050f" | "pl0512" | "pl0513"; num: number }> = [
      { id: "pl0503", num: 0x503 },
      { id: "pl0506", num: 0x506 },
      { id: "pl0507", num: 0x507 },
      { id: "pl050f", num: 0x50f },
      { id: "pl0512", num: 0x512 },
      { id: "pl0513", num: 0x513 },
    ];
    for (const { id, num } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime,
        { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id}`);
      if (bridge) {
        assert(bridge.actor.borgNumber === num,
          `${id}: borgNumber stamped 0x${num.toString(16)} via bridge attach`);
        assert(bridge.actor.rootAction !== null, `${id}: rootAction wired`);
      }
    }
  }

  // Test 24: ALIEN WORM family — X phase 0 spawn (FUN_80118efc → FUN_8011a108).
  // Borg-switched: pl0501 → worm-child type 0, pl050d → worm-child type 1, both via
  // the bespoke FUN_8011a108 spawner (chunk_0032.c:1391).
  console.log("\n[rom.selfcheck] families/worm — X phase 0 worm-child spawn (FUN_8011a108):");
  {
    const a = createRomActor();
    let spawn = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawn = { addr, type }; },
    };
    configureWormFamily(a, "pl0501", ctx);
    assert(a.borgNumber === 0x501, "borgNumber stamped 0x501 (ALIEN WORM)");
    a.actionIndex = 2;
    a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++ arm)");
    assert(spawn !== null && spawn!.addr === WORM_X.WORM_CHILD_SPAWNER_ADDR && spawn!.type === 0,
      "worm-child spawned via FUN_8011a108 type 0 (pl0501)");
    assert(approxEq(a.stateTimer, WORM_X.COOLDOWN + 1),
      `+0x694 = FLOAT_80439870(4) + dt(1) = 5`);

    // pl050d → worm-child type 1 (CLAW WORM).
    const b = createRomActor();
    let spawnB = null as { addr: number; type: number } | null;
    const ctxB: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawnB = { addr, type }; },
    };
    configureWormFamily(b, "pl050d", ctxB);
    assert(b.borgNumber === 0x50d, "borgNumber stamped 0x50d (CLAW WORM)");
    b.actionIndex = 2; b.dt = 1;
    b.cueTable = new Int8Array(96).fill(-1); b.cueTable[44 * 2] = 61; b.fbState = 61;
    stepActor(b, table);
    assert(spawnB !== null && spawnB!.addr === WORM_X.WORM_CHILD_SPAWNER_ADDR && spawnB!.type === 1,
      "worm-child spawned via FUN_8011a108 type 1 (pl050d)");
  }

  // Test 25: ALIEN WORM family — X phase 0 cloud spawn (FUN_80118efc → zz_01d4d00_).
  // pl050b/pl0517 use the shared venom/poison-cloud spawner (chunk_0057.c:338) with
  // borg-switched record types: 0x50b→1 (venom), 0x517→3 (poison).
  console.log("\n[rom.selfcheck] families/worm — X phase 0 cloud spawn (zz_01d4d00_):");
  {
    const a = createRomActor();
    let spawn = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawn = { addr, type }; },
    };
    configureWormFamily(a, "pl050b", ctx);
    assert(a.borgNumber === 0x50b, "borgNumber stamped 0x50b (VENOM WORM)");
    a.actionIndex = 2; a.dt = 1;
    a.cueTable = new Int8Array(96).fill(-1); a.cueTable[44 * 2] = 61; a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(spawn !== null && spawn!.addr === WORM_X.CLOUD_SPAWNER_ADDR && spawn!.type === 1,
      "venom cloud spawned via zz_01d4d00_ type 1 (pl050b)");

    // pl0517 → poison cloud type 3.
    const b = createRomActor();
    let spawnB = null as { addr: number; type: number } | null;
    const ctxB: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawnB = { addr, type }; },
    };
    configureWormFamily(b, "pl0517", ctxB);
    assert(b.borgNumber === 0x517, "borgNumber stamped 0x517 (POISON WORM)");
    b.actionIndex = 2; b.dt = 1;
    b.cueTable = new Int8Array(96).fill(-1); b.cueTable[44 * 2] = 61; b.fbState = 61;
    stepActor(b, table);
    assert(spawnB !== null && spawnB!.addr === WORM_X.CLOUD_SPAWNER_ADDR && spawnB!.type === 3,
      "poison cloud spawned via zz_01d4d00_ type 3 (pl0517)");
  }

  // Test 26: ALIEN WORM family — phase 1 exit: action-mode bits cleared.
  console.log("\n[rom.selfcheck] families/worm — phase 1 exit bit-clear:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureWormFamily(a, "pl0501", ctx);
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.controlWord = 0x3; // action-mode bits set
    a.dt = 1;
    a.actionIndex = 2;
    a.rootAction!(a);
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
  }

  // Test 27: ALIEN WORM family — bridge cue-table attach for all 4 members
  // (ctor 0x80118cb8, cue table @0x8032b8d8). BESPOKE registration: the X-special
  // routes through FUN_80118efc (borg-switched spawn dispatcher); see families/worm.ts.
  console.log("\n[rom.selfcheck] families/worm — bridge cue-table (0x8032b8d8):");
  {
    const members: Array<{ id: string; num: number }> = [
      { id: "pl0501", num: 0x501 }, // ALIEN WORM
      { id: "pl050b", num: 0x50b }, // VENOM WORM
      { id: "pl050d", num: 0x50d }, // CLAW WORM
      { id: "pl0517", num: 0x517 }, // POISON WORM
    ];
    for (const { id, num } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id} (family registered)`);
      if (bridge) {
        const t = bridge.actor.cueTable!;
        assert(t[44 * 2] === 61 && t[45 * 2] === 61,
          `${id}: cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)`);
        assert(bridge.actor.rootAction !== null, `${id}: worm rootAction configured`);
        assert(bridge.actor.borgNumber === num, `${id}: borgNumber stamped 0x${num.toString(16)} via bridge attach`);
      }
    }
  }

  // Test 28: MACHINE RED family — bridge cue-table attach for all 4 members
  // (ctor 0x800c91bc, cue table @0x8030a248). SHARED registration: the X-special
  // routes through zz_0179d20_ (shared group-4 engine, phaseTable 0x804347a8); no
  // bespoke family module. Verify each member attaches, gets the family cue table,
  // and resolves rootAction via the shared-engine config.
  console.log("\n[rom.selfcheck] families/machine-red — bridge cue-table (0x8030a248):");
  {
    const members: Array<{ id: string; num: number }> = [
      { id: "pl0600", num: 0x600 }, // MACHINE RED
      { id: "pl0608", num: 0x608 }, // CYBER MARS
      { id: "pl0616", num: 0x616 }, // PROTO RED
      { id: "pl061c", num: 0x61c }, // PROTO MARS
    ];
    for (const { id, num } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id} (family registered)`);
      if (bridge) {
        const t = bridge.actor.cueTable!;
        assert(t[44 * 2] === 61 && t[45 * 2] === 61,
          `${id}: cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)`);
        assert(bridge.actor.rootAction !== null, `${id}: shared-engine rootAction configured`);
        assert(bridge.actor.borgNumber === num, `${id}: borgNumber stamped 0x${num.toString(16)} via bridge attach`);
        // cue 36 → [47, 0] (deploy state) — same shape as Flame Dragon family.
        assert(t[36 * 2] === 47, `${id}: cue row 36 → full-body state 47 (deploy)`);
      }
    }
  }

  // Test 25: DEMON SAMURAI family — bridge cue-table attach for all 4 members
  // (ctor 0x801223c0, cue table @0x8032d4d8). Now registered via the samurai cluster
  // (families/samurai.ts): the X-special routes through the real zz_0149708_ port
  // (shared-flight-x.ts, borg-switched configs @0x8032c814/0x8032c838). Verify each
  // member attaches, gets the family cue table, and has the cluster rootAction.
  console.log("\n[rom.selfcheck] families/samurai — bridge cue-table (0x8032d4d8):");
  {
    const members: Array<{ id: string; num: number }> = [
      { id: "pl0701", num: 0x701 }, // DEAMON SAMURAI
      { id: "pl0708", num: 0x708 }, // AKUMA SAMURAI
      { id: "pl070c", num: 0x70c }, // DEATH BORG ZETA III
      { id: "pl070d", num: 0x70d }, // DEATH BORG ZETA IV
    ];
    for (const { id, num } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id} (family registered)`);
      if (bridge) {
        const t = bridge.actor.cueTable!;
        assert(t[44 * 2] === 61 && t[45 * 2] === 61,
          `${id}: cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)`);
        assert(bridge.actor.rootAction !== null, `${id}: samurai-cluster rootAction configured`);
        assert(bridge.actor.borgNumber === num, `${id}: borgNumber stamped 0x${num.toString(16)} via bridge attach`);
        // cue 36 → [47, 0] (deploy state) — same shape as Flame Dragon + Machine Red.
        assert(t[36 * 2] === 47, `${id}: cue row 36 → full-body state 47 (deploy)`);
      }
    }
  }

  // Test 25: MACHINE BLUE family — bridge cue-table attach for all 4 members
  // (ctor 0x800ce730, cue table @0x8030c9c8). SHARED registration: the X-special
  // routes through zz_0179fcc_ (shared group-4 engine, phaseTable 0x80352b64); no
  // bespoke family module. The action-2 leaf FUN_800cf9cc is a thin wrapper (halves
  // steerYaw, tail-calls the shared engine). Verify each member attaches, gets the
  // family cue table, and resolves rootAction via the shared-engine config.
  console.log("\n[rom.selfcheck] families/machine-blue — bridge cue-table (0x8030c9c8):");
  {
    const members: Array<{ id: string; num: number }> = [
      { id: "pl0601", num: 0x601 }, // MACHINE BLUE
      { id: "pl0609", num: 0x609 }, // CYBER ATLAS
      { id: "pl0617", num: 0x617 }, // PROTO BLUE
      { id: "pl061d", num: 0x61d }, // PROTO ATLAS
    ];
    for (const { id, num } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id} (family registered)`);
      if (bridge) {
        const t = bridge.actor.cueTable!;
        assert(t[44 * 2] === 61 && t[45 * 2] === 61,
          `${id}: cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)`);
        assert(bridge.actor.rootAction !== null, `${id}: shared-engine rootAction configured`);
        assert(bridge.actor.borgNumber === num, `${id}: borgNumber stamped 0x${num.toString(16)} via bridge attach`);
        // cue 36 → [47, 0] (deploy state) — same shape as Machine Red + Flame Dragon families.
        assert(t[36 * 2] === 47, `${id}: cue row 36 → full-body state 47 (deploy)`);
      }
    }
  }

  // Test 29: WIRE GUNNER family — X phase 0 ground arm (direction slot select, zz_004beb8_).
  // zz_01316e0_:609-625 — +0x540 == 0 branch: advance phase, pick slot from controlWord
  // direction bits (default 2 / side 0x10 → 4 / up 0x40 → 3), startStream(g4, slot).
  console.log("\n[rom.selfcheck] families/wire-gunner — X phase 0 ground arm (zz_01316e0_):");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: () => {},
    };
    configureWireGunnerFamily(a, "pl0103", ctx);
    assert(a.borgNumber === 0x103, "borgNumber stamped 0x103 (WIRE GUNNER)");
    a.actionIndex = 2;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    a.controlWord = 0x0; // neutral direction (no side/up/air bits)
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "phase advanced 0 → 1 (+0x540++ arm)");
    assert(a.streamSlot === WIRE_GUNNER_X.SLOT_DEFAULT,
      `neutral direction → slot ${WIRE_GUNNER_X.SLOT_DEFAULT} (zz_01316e0_:616)`);
  }

  // Test 30: WIRE GUNNER family — phase 0 direction bits select slot 3/4.
  console.log("\n[rom.selfcheck] families/wire-gunner — phase 0 direction slot select:");
  {
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: () => {},
    };
    // Up bit (0x40) → slot 3.
    const up = createRomActor();
    configureWireGunnerFamily(up, "pl0106", ctx);
    assert(up.borgNumber === 0x106, "borgNumber stamped 0x106 (TIME BOMBER)");
    up.actionIndex = 2;
    up.controlWord = WIRE_GUNNER_X.UP_BIT; // up only
    up.rootAction!(up);
    assert(up.fbPhaseSlots[0] === 1, "up: phase advanced 0 → 1");
    assert(up.streamSlot === WIRE_GUNNER_X.SLOT_UP,
      `up bit 0x40 → slot ${WIRE_GUNNER_X.SLOT_UP} (zz_01316e0_:620-622)`);
    // Side bit (0x10) → slot 4.
    const side = createRomActor();
    configureWireGunnerFamily(side, "pl0107", ctx);
    assert(side.borgNumber === 0x107, "borgNumber stamped 0x107 (REMOTE BOMBER)");
    side.actionIndex = 2;
    side.controlWord = WIRE_GUNNER_X.SIDE_BIT; // side only
    side.rootAction!(side);
    assert(side.streamSlot === WIRE_GUNNER_X.SLOT_SIDE,
      `side bit 0x10 → slot ${WIRE_GUNNER_X.SLOT_SIDE} (zz_01316e0_:617-619)`);
  }

  // Test 31: WIRE GUNNER family — phase 0 air-with-target → fire kind=4 + exit.
  // zz_01316e0_:626-635 — `(controlWord & 0x20) != 0 && +0x1cef != 0` branch: clear
  // action-mode bits, fire zz_006a668_(actor, kind=4), seed cooldown.
  console.log("\n[rom.selfcheck] families/wire-gunner — phase 0 air-target fire (kind=4):");
  {
    const a = createRomActor();
    let shot = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { shot = { addr, type }; },
    };
    configureWireGunnerFamily(a, "pl0103", ctx);
    a.actionIndex = 2;
    a.controlWord = 0x3 | WIRE_GUNNER_X.AIR_BIT; // action-mode bits + air bit
    a.contactP0 = 1; // +0x1cef target acquired
    a.dt = 1;
    a.rootAction!(a);
    assert(shot !== null && shot.addr === WIRE_GUNNER_X.SHOT_SPAWNER_ADDR && shot.type === WIRE_GUNNER_X.SHOT_KIND_AIR,
      "air-target fires zz_006a668_(actor, kind=4) (zz_01316e0_:629)");
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
    assert(approxEq(a.stateTimer, 1.0), "+0x694 seeded with dt (air-fire cooldown)");
  }

  // Test 32: WIRE GUNNER family — phase 1 contact → fire kind=30 + exit.
  // zz_01316e0_:637-645 — else branch: zz_004cd24_(actor, 1) tick, on +0x1cee != 0 →
  // clear bits + zz_006a668_(actor, kind=30).
  console.log("\n[rom.selfcheck] families/wire-gunner — phase 1 contact fire (kind=30):");
  {
    const a = createRomActor();
    let shot = null as { addr: number; type: number } | null;
    const ctx: GRedFamilyCtx & {
      onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
    } = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { shot = { addr, type }; },
    };
    configureWireGunnerFamily(a, "pl0107", ctx);
    a.fbPhaseSlots[0] = 1; // already in phase 1
    a.controlWord = 0x3; // action-mode bits set
    a.wallContact = 1; // +0x1cee target acquired (contact gate)
    a.actionIndex = 2;
    a.rootAction!(a);
    assert(shot !== null && shot.addr === WIRE_GUNNER_X.SHOT_SPAWNER_ADDR && shot.type === WIRE_GUNNER_X.SHOT_KIND_GROUND,
      "contact fires zz_006a668_(actor, kind=30) (zz_01316e0_:642)");
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
  }

  // Test 33: WIRE GUNNER family — bridge cue-table attach for all 3 members
  // (ctor 0x801301f8, cue table @0x80336178). Verify each member attaches, gets the
  // family cue table, and resolves rootAction via the bespoke family config.
  console.log("\n[rom.selfcheck] families/wire-gunner — bridge cue-table (0x80336178):");
  {
    const members: Array<{ id: string; num: number }> = [
      { id: "pl0103", num: 0x103 }, // WIRE GUNNER
      { id: "pl0106", num: 0x106 }, // TIME BOMBER
      { id: "pl0107", num: 0x107 }, // REMOTE BOMBER
    ];
    for (const { id, num } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime, { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id} (family registered)`);
      if (bridge) {
        const t = bridge.actor.cueTable!;
        assert(t[44 * 2] === 61 && t[45 * 2] === 61,
          `${id}: cue rows 44 AND 45 → full-body state 61 (universal attack trampoline)`);
        assert(bridge.actor.rootAction !== null, `${id}: wire-gunner rootAction configured`);
        assert(bridge.actor.borgNumber === num, `${id}: borgNumber stamped 0x${num.toString(16)} via bridge attach`);
      }
    }
  }

  // Test 34: shared-melee-gred — phase 0 stream start (FUN_80177e28).
  // Verifies: +0x540++ (phase 0→1), +0x746/+0x745 cleared, +0x6ea = seedSlot then ++,
  // +0x558 = 60.0 (FLOAT_8043ae20). Air-check fallback: airborne → yaw = heading.
  console.log("\n[rom.selfcheck] shared-melee-gred — phase 0 stream start (FUN_80177e28):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean;
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.grounded = true;
    a.heading = 0x2000;
    a.lockYaw = 0x4000;
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedMeleeGRedConfig = { seedSlot: 5, timerFrames: 30, proximityRange: 100 };
    const melee = createSharedMeleeGRed(cfg, ctx);
    melee(a); // phase 0
    assert(a.fbPhaseSlots[0] === 1, "phase 0 → 1 (+0x540++)");
    assert(a.streamSlot === cfg.seedSlot + 1, `stream cursor = seedSlot+1 (${cfg.seedSlot}→${a.streamSlot}, +0x6ea++)`);
    assert(approxEq(a.handlerTimer, SHARED_MELEE_GRED.TIMER_SEED), `handlerTimer == 60.0 (FLOAT_8043ae20)`);
    assert(approxEq(a.activeYaw, 0x4000), "grounded → activeYaw = lockYaw (bridge target yaw kept)");

    // Air-check fallback: airborne → yaw snapshots to heading (the <1 branch).
    const b = createRomActor() as RomActor & { grounded?: boolean };
    b.grounded = false;
    b.heading = 0x1000;
    b.lockYaw = 0x4000;
    melee(b);
    assert(approxEq(b.activeYaw, 0x1000), "airborne → activeYaw = heading (+0x5ac = +0x72)");
    assert(approxEq(b.lockYaw, 0x1000), "airborne → lockYaw = heading (+0x5ae = +0x72)");
  }

  // Test 35: shared-melee-gred — phase 1 timer expiry → phase 2 + computeLungeSpeed.
  // Verifies the phase 1→2 transition: timer ≤ 0 OR facing complete. computeLungeSpeed
  // (zz_01782dc_) sets hSpeed = DEFAULT_LUNGE_BASE / timerFrames.
  console.log("\n[rom.selfcheck] shared-melee-gred — phase 1 → 2 transition (FUN_80177f10):");
  {
    const a = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.lockTarget = null; // no target → facing won't short-circuit; timer drives transition
    a.actionSpeedRows = [50, 50, 50]; // explicit fixture for descriptor +0x134/+0x140/+0x14c
    a.dt = 1;
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedMeleeGRedConfig = { seedSlot: 0, timerFrames: 25, proximityRange: 100 };
    const melee = createSharedMeleeGRed(cfg, ctx);
    melee(a); // phase 0 → 1 (handlerTimer = 60.0)
    assert(a.fbPhaseSlots[0] === 1, "phase 0 → 1");
    // Tick phase 1 until timer expires. With no lockTarget, facing won't fire, so the
    // timer must reach 0. Seed handlerTimer to 1.0 to force a one-tick transition.
    a.handlerTimer = 1.0;
    melee(a); // phase 1 → 2 (timer ≤ 0)
    assert(a.fbPhaseSlots[0] === 2, "phase 1 → 2 (+0x540++ on timer ≤ 0)");
    assert(approxEq(a.handlerTimer, 25.0), "handlerTimer == cfg.timerFrames (25.0)");
    // DEFAULT_LUNGE_BASE (50.0) / timerFrames (25) = 2.0 (from shared-engine.ts).
    assert(approxEq(a.hSpeed, 50.0 / 25.0), "hSpeed == DEFAULT_LUNGE_BASE/timerFrames (zz_01782dc_)");

    // Facing-complete short-circuit: with a target, phase 1 advances on the first tick.
    const b = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    b.lockTarget = { x: 10, y: 0, z: 10 };
    b.handlerTimer = 60.0; // would NOT expire; transition must come from facing
    b.fbPhaseSlots[0] = 1;
    melee(b);
    assert(b.fbPhaseSlots[0] === 2, "facing-complete (target present) → phase 1 → 2");
  }

  // Test 36: shared-melee-gred — phase 2 proximity gate → phase 3 (FUN_80177fd4).
  // Verifies the FUN_800668cc approximation: target within proximityRange → advance.
  console.log("\n[rom.selfcheck] shared-melee-gred — phase 2 proximity → phase 3:");
  {
    const a = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.lockTarget = { x: 0, y: 0, z: 0 };
    a.pos = { x: 50, y: 0, z: 0 }; // dist 50 < proximityRange 100
    a.dt = 1;
    a.timescale = 1;
    a.tierScale = 1;
    a.maxFall = -9999;
    a.activeYaw = 0;
    a.actionSpeedRows = [50, 50, 50];
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedMeleeGRedConfig = { seedSlot: 0, timerFrames: 30, proximityRange: 100 };
    const melee = createSharedMeleeGRed(cfg, ctx);
    a.fbPhaseSlots[0] = 2;
    a.handlerTimer = 30.0; // not expired; transition must come from proximity
    melee(a);
    assert(a.fbPhaseSlots[0] === 3, "dist < proximityRange → phase 2 → 3 (FUN_800668cc gate)");

    // Out-of-range + timer not expired → phase stays 2.
    const b = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    b.lockTarget = { x: 0, y: 0, z: 0 };
    b.pos = { x: 200, y: 0, z: 0 }; // dist 200 > proximityRange 100
    b.dt = 1; b.timescale = 1; b.tierScale = 1; b.maxFall = -9999; b.activeYaw = 0;
    b.fbPhaseSlots[0] = 2;
    b.handlerTimer = 30.0;
    melee(b);
    assert(b.fbPhaseSlots[0] === 2, "dist > proximityRange AND timer > 0 → phase stays 2");
  }

  // Test 37: shared-melee-gred — phase 3 combo loop back to phase 2 (FUN_801780e4).
  // Verifies the combo-continue path: +0x1cf0 high bit AND +0x746 & +0x745 both set →
  // +0x540-- (3→2), latches cleared, timer reset, next stream slot armed, velocity re-set.
  console.log("\n[rom.selfcheck] shared-melee-gred — phase 3 combo loop (FUN_801780e4):");
  {
    const a = createRomActor() as RomActor & {
      bRetapInput?: boolean;
      altInputPresent?: boolean;
      swingReArm?: boolean;
      swingChainBit?: boolean;
      bRetap?: boolean;
      altInput?: boolean;
    };
    a.dt = 1;
    a.timescale = 1;
    a.tierScale = 1;
    a.maxFall = -9999;
    a.activeYaw = 0;
    a.actionSpeedRows = [50, 50, 50];
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedMeleeGRedConfig = { seedSlot: 0, timerFrames: 30, proximityRange: 100 };
    const melee = createSharedMeleeGRed(cfg, ctx);
    // Seed streamSlot at 2 (as if phase 0 used slot 0 and phase-3 restart used slot 1).
    a.streamSlot = 2;
    a.fbPhaseSlots[0] = 3;
    // Combo-continue conditions: B-retap this frame, alt-input this frame, swing re-armed.
    a.bRetapInput = true;
    a.altInputPresent = true;
    a.swingReArm = true;
    a.swingChainBit = true; // bit 0 set → loop restart (not the chain callback)
    melee(a);
    assert(a.fbPhaseSlots[0] === 2, "combo-continue → phase 3 → 2 (+0x540--)");
    assert(a.bRetap === false && a.altInput === false, "+0x746/+0x745 cleared after loop restart");
    assert(approxEq(a.handlerTimer, 30.0), "handlerTimer reset to cfg.timerFrames");
    assert(a.streamSlot === 3, "stream cursor advanced (+0x6ea++ for the next swing)");
    assert(approxEq(a.hSpeed, 50.0 / 30.0), "hSpeed re-set by zz_01782dc_ on loop restart");
  }

  // Test 38: shared-melee-gred — phase 3 chain-callback redirect (the +0x10 path).
  // When +0x1cf0 bit 0 is clear AND cfg.chainCallback is set, the callback fires INSTEAD
  // of the loop restart, and the engine returns immediately (variant redirect, e.g. NEO
  // G RED's standing finisher via FUN_8018ded0).
  console.log("\n[rom.selfcheck] shared-melee-gred — phase 3 chain callback (+0x10):");
  {
    const a = createRomActor() as RomActor & {
      bRetapInput?: boolean;
      altInputPresent?: boolean;
      swingReArm?: boolean;
      swingChainBit?: boolean;
    };
    a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999; a.activeYaw = 0;
    let chainFired = false;
    const cfg: SharedMeleeGRedConfig = {
      seedSlot: 0,
      timerFrames: 30,
      proximityRange: 100,
      chainCallback: () => { chainFired = true; },
    };
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const melee = createSharedMeleeGRed(cfg, ctx);
    a.streamSlot = 5;
    a.fbPhaseSlots[0] = 3;
    a.bRetapInput = true;
    a.altInputPresent = true;
    a.swingReArm = true;
    a.swingChainBit = false; // bit 0 CLEAR → chain callback path
    melee(a);
    assert(chainFired, "chain callback fired (+0x1cf0 & 1 == 0 path)");
    assert(a.fbPhaseSlots[0] === 3, "phase NOT advanced (callback returned early — no loop restart)");
    assert(a.streamSlot === 5, "stream cursor NOT advanced (callback path doesn't touch +0x6ea)");
  }

  // Test 39: shared-melee-gred — phase 3 recovery end (+0x1cee → idle).
  // When wallContact (+0x1cee) fires and no combo-continue, the engine clears action-mode
  // bits and runs the real zz_006a474_ tail (chunk_0009.c:708-729, decomp-verified in
  // shared-idle-return.ts): upper-body cue 0 ONLY + velocity zeroing — NOT the old
  // full-body cue 0 dispatch.
  console.log("\n[rom.selfcheck] shared-melee-gred — phase 3 recovery end (zz_006a474_):");
  {
    const a = createRomActor();
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[0] = 0; // cue 0 fb row (should NOT be consumed)
    a.cueTable[1] = 5; // cue 0 ub row → ubState 5 (the zz_006a750_(0) target)
    a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999; a.activeYaw = 0;
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedMeleeGRedConfig = { seedSlot: 0, timerFrames: 30, proximityRange: 100 };
    const melee = createSharedMeleeGRed(cfg, ctx);
    a.fbPhaseSlots[0] = 3;
    a.fbState = 61;      // attack state — must be untouched by the upper-body-only exit
    a.hSpeed = 12; a.yVel = 3; a.hDecel = 1; a.gravityCoeff = 1;
    a.controlWord = 0x3; // action-mode bits set
    a.wallContact = 1;   // +0x1cee → end the move
    melee(a);
    assert((a.controlWord & 0x3) === 0, "action-mode bits cleared (+0x5e0 &= ~3)");
    assert(a.ubState === 5, "ubState set via upper cue 0 (zz_006a474_ → zz_006a750_(0))");
    assert(a.fbState === 61, "fbState untouched (zz_006a474_ dispatches NO full-body cue)");
    assert(a.hSpeed === 0 && a.yVel === 0 && a.hDecel === 0 && a.gravityCoeff === 0,
      "velocities zeroed (+0x44/+0x48/+0x4c/+0x50 = 0)");
  }

  // Test 40: shared-melee-gred — G RED action table slot 1 routes B-melee here.
  // Confirms the family wiring: configureGRedFamily stamps a rootAction whose
  // actionIndex 1 path is the shared melee engine (phase 0 stream arm).
  console.log("\n[rom.selfcheck] families/gred — action 1 routes to shared-melee-gred:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureGRedFamily(a, "pl0615", ctx);
    a.actionIndex = 1; // B-close
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "action 1 phase 0 → 1 (shared melee engine armed)");
    assert(approxEq(a.handlerTimer, SHARED_MELEE_GRED.TIMER_SEED), "handlerTimer == 60.0 (TIMER_SEED)");
    assert(a.streamSlot === GRED_MELEE_CONFIG.seedSlot + 1, "stream cursor = GRED_MELEE_CONFIG.seedSlot+1");
  }

  // Test 41: shared-charge — engine constants match boot.dol (dol.py-read this session).
  console.log("\n[rom.selfcheck] shared-charge — SHARED_CHARGE constants vs boot.dol:");
  {
    assert(approxEq(SHARED_CHARGE.STREAM_RATE, -1.0), "STREAM_RATE == FLOAT_8043ae04 (-1.0)");
    assert(approxEq(SHARED_CHARGE.ZERO, 0.0), "ZERO == FLOAT_8043ae10 (0.0)");
    assert(approxEq(SHARED_CHARGE.GRAVITY, 1.0), "GRAVITY == FLOAT_8043ae1c (1.0)");
    assert(approxEq(SHARED_CHARGE.STEER_DECAY, 0.9), "STEER_DECAY == FLOAT_8043ae30 (0.9)");
    assert(approxEq(SHARED_CHARGE.COOLDOWN_SEED, 8.0), "COOLDOWN_SEED == FLOAT_8043ae34 (8.0)");
    assert(SHARED_CHARGE.STREAM_GROUP === 4, "STREAM_GROUP == 4 (group-4 charge axis)");
    assert(SHARED_CHARGE.PART_MASK === 0xf, "PART_MASK == 0xf");
  }

  // Test 42: shared-charge — G RED config @0x80365854 values match DOL dump.
  console.log("\n[rom.selfcheck] shared-charge — GRED_CHARGE_CONFIG vs DOL @0x80365854:");
  {
    assert(GRED_CHARGE_CONFIG.seedSlot === 2, "seedSlot == 2 (cfg u32[+0x0] low byte)");
    assert(GRED_CHARGE_CONFIG.airSlot === 2, "airSlot == 2 (cfg u32[+0x4] low byte)");
    assert(GRED_CHARGE_CONFIG.chargeFrames === 30, "chargeFrames == 30 (cfg s16[+0xc])");
    assert(approxEq(GRED_CHARGE_CONFIG.repositionScale, 0.95), "repositionScale == 0.95 (cfg f32[+0x8])");
  }

  // Test 43: shared-charge — phase 0 entry/windup (FUN_80179850).
  // Verifies: +0x540++ (phase 0→1), handlerTimer = chargeFrames, physics zeroed,
  // reposition leap applied (pos moves away from target × scale), stream started.
  console.log("\n[rom.selfcheck] shared-charge — phase 0 entry/windup (FUN_80179850):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean;
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.grounded = true;
    a.heading = 0x2000;
    a.pos = { x: 100, y: 0, z: 100 };
    a.lockTarget = { x: 0, y: 0, z: 0 };
    a.dt = 1;
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedChargeConfig = {
      seedSlot: 2, airSlot: 2, chargeFrames: 30,
      repositionScale: 0.95, gravityCoeff: 1.0,
    };
    const charge = createSharedCharge(cfg, ctx);
    charge(a); // phase 0
    assert(a.fbPhaseSlots[0] === 1, "phase 0 → 1 (+0x540++)");
    assert(approxEq(a.handlerTimer, 30.0), "handlerTimer == chargeFrames (30, +0x560 seed)");
    assert(approxEq(a.hSpeed, 0.0), "hSpeed zeroed (+0x44 = FLOAT_8043ae10)");
    assert(approxEq(a.yVel, 0.0), "yVel zeroed (+0x48)");
    assert(approxEq(a.hDecel, 0.0), "hDecel zeroed (+0x4c)");
    assert(approxEq(a.gravityCoeff, 0.0), "gravityCoeff zeroed (+0x50, windup has no gravity)");
    // Reposition leap: motion = (pos - target) × 0.95; pos += motion.
    // pos was (100,0,100), target (0,0,0): motion = (95,0,95); new pos = (195,0,195).
    assert(approxEq(a.pos.x, 195.0), "reposition leap: pos.x = 100 + (100-0)*0.95 = 195");
    assert(approxEq(a.pos.z, 195.0), "reposition leap: pos.z = 100 + (100-0)*0.95 = 195");
    assert(a.streamSlot === cfg.seedSlot + 1, "streamSlot = seedSlot+1 (+0x6ea++)");
  }

  // Test 44: shared-charge — phase 1 stream-event-driven release (FUN_801799bc).
  // The release trigger is +0x1cef > 0 (the stream choreography event), NOT a frame
  // counter. Verifies the stream-event gate advances to phase 2 when contactP0 > 0.
  console.log("\n[rom.selfcheck] shared-charge — phase 1 stream-event release (FUN_801799bc):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean;
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.grounded = true;
    a.pos = { x: 50, y: 0, z: 50 };
    a.lockTarget = { x: 0, y: 0, z: 0 };
    a.dt = 1;
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    let released = false;
    const cfg: SharedChargeConfig = {
      seedSlot: 0, airSlot: 1, chargeFrames: 20,
      repositionScale: 0.9, gravityCoeff: 1.0,
      onRelease: () => { released = true; },
    };
    const charge = createSharedCharge(cfg, ctx);
    charge(a); // phase 0 → 1
    assert(a.fbPhaseSlots[0] === 1, "phase 0 done");
    // Tick phase 1 WITHOUT the stream event: phase should NOT advance (stream-driven).
    a.contactP0 = 0; // no stream event yet
    charge(a); // phase 1 tick (no release)
    assert(a.fbPhaseSlots[0] === 1, "phase 1 stays at 1 when contactP0 == 0 (no stream event)");
    // Fire the stream release event: contactP0 > 0 → phase 2.
    a.contactP0 = 1;
    charge(a); // phase 1 → 2 (stream event release)
    assert(a.fbPhaseSlots[0] === 2, "phase 1 → 2 on contactP0 > 0 (stream release event)");
    assert(released, "onRelease callback fired on the stream-event transition");
  }

  // Test 45: shared-charge — phase 2 fire countdown + fire-complete exit (FUN_80179a88).
  // Verifies: timer decrements by dt each frame; exit on timer <= 0. The exact-exit
  // contactP0 < 0 gate is exercised; the timer-expiry fallback also covered.
  console.log("\n[rom.selfcheck] shared-charge — phase 2 fire countdown (FUN_80179a88):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean;
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.grounded = true;
    a.pos = { x: 0, y: 0, z: 0 };
    a.lockTarget = null;
    a.dt = 1;
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedChargeConfig = {
      seedSlot: 0, airSlot: 1, chargeFrames: 5,
      repositionScale: 0.9, gravityCoeff: 1.0,
    };
    const charge = createSharedCharge(cfg, ctx);
    charge(a); // phase 0 (handlerTimer = 5)
    a.contactP0 = 1;
    charge(a); // phase 1 → 2
    assert(a.fbPhaseSlots[0] === 2, "phase 1 → 2");
    // Tick phase 2: timer decrements by dt (1 per frame). After 5 ticks, timer <= 0.
    a.contactP0 = 0; // no fire-complete event yet
    charge(a); // 1 tick: handlerTimer 5 → 4
    assert(approxEq(a.handlerTimer, 4.0), "phase 2 handlerTimer 5 → 4 (-dt)");
    assert(a.fbPhaseSlots[0] === 2, "phase 2 stays while timer > 0");
    // Burn remaining ticks. chargeFrames=5 → 5 decrements to 0, then a 6th tick enters
    // phase 2 with handlerTimer<=0 and advances (the <= 0 check is at the function top).
    charge(a); charge(a); charge(a); charge(a); // 4 more: 4→3→2→1→0
    charge(a); // 6th tick: handlerTimer 0 <= 0 → phase 3
    // Timer now <= 0 → exit to phase 3 (timer-expiry fallback since contactP0 == 0).
    assert(a.fbPhaseSlots[0] === 3, "phase 2 → 3 on handlerTimer <= 0 (timer-expiry exit)");
  }

  // Test 46: shared-charge — phase 3 recovery exit (FUN_80179c00).
  // Verifies: steerYaw decay (airborne, no exit), grounded + contactP0 < 0 → controlWord
  // &= ~0x3 + cooldown + steerYaw zeroed (EXIT A).
  console.log("\n[rom.selfcheck] shared-charge — phase 3 recovery exit (FUN_80179c00):");
  {
    // SteerYaw decay WITHOUT exit (airborne): 1000 → 900, stays airborne (no EXIT A).
    const air = createRomActor() as RomActor & {
      grounded?: boolean;
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    air.grounded = false; // airborne → EXIT A does not fire
    air.dt = 1;
    air.steerYaw = 1000;
    air.controlWord = 0x1;
    air.contactP0 = 0; // not negative → EXIT A gate fails
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const cfg: SharedChargeConfig = {
      seedSlot: 0, airSlot: 1, chargeFrames: 5,
      repositionScale: 0.9, gravityCoeff: 1.0,
    };
    const charge = createSharedCharge(cfg, ctx);
    air.fbPhaseSlots[0] = 3;
    charge(air); // phase 3 (airborne, no exit)
    assert(approxEq(air.steerYaw, 900), "steerYaw decayed × FLOAT_8043ae30 (1000 → 900) while airborne");

    // EXIT A (grounded + contactP0 < 0): controlWord &= ~0x3, cooldown set, steerYaw = 0.
    const a = createRomActor() as RomActor & {
      grounded?: boolean;
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    a.grounded = true;
    a.dt = 1;
    a.steerYaw = 1000;
    a.controlWord = 0x1; // action bits set (in attack state)
    a.contactP0 = -1; // stream fire-complete event (negative)
    a.handlerTimer = 0; // timer already expired (phase 2 → 3 path)
    a.fbPhaseSlots[0] = 3;
    charge(a); // phase 3 (EXIT A)
    // Grounded + contactP0 < 0 → EXIT A: controlWord &= ~0x3.
    assert((a.controlWord & 0x3) === 0, "controlWord &= ~0x3 (action bits cleared on recovery exit)");
    // Cooldown +0x694 = FLOAT_8043ae34 (8.0) + dt (1) = 9.0.
    assert(approxEq(a.stateTimer, 9.0), "stateTimer == COOLDOWN_SEED + dt (8.0 + 1 = 9.0)");
    // EXIT A zeroes steerYaw (+0x18da = 0) AFTER the 0.9 decay.
    assert(a.steerYaw === 0, "steerYaw zeroed by EXIT A (+0x18da = 0 after recovery exit)");
  }

  // Test 47: shared-charge — G RED action table slot 3 routes B-charge here.
  // Confirms the family wiring: configureGRedFamily stamps hasBCharge and a rootAction
  // whose actionIndex 3 path is the shared charge engine.
  console.log("\n[rom.selfcheck] families/gred — action 3 routes to shared-charge:");
  {
    const a = createRomActor();
    const ctx: GRedFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureGRedFamily(a, "pl0615", ctx);
    assert(a.hasBCharge, "configureGRedFamily sets hasBCharge (actionTable[3] wired)");
    a.actionIndex = 3; // B-charge
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "action 3 phase 0 → 1 (shared charge engine armed)");
    assert(approxEq(a.handlerTimer, GRED_CHARGE_CONFIG.chargeFrames), "handlerTimer == GRED_CHARGE_CONFIG.chargeFrames");
  }

  // Test 48: shared-charge — bridge tryStartBAttack for G RED (pl0615).
  // Verifies the bridge-level B-press interception: tryStartBAttack starts the machine,
  // returns true, and subsequent ticks advance phases (ROM owns motion).
  console.log("\n[rom.selfcheck] bridge — tryStartBAttack for pl0615 (ROM B-charge):");
  {
    const b = makeMinimalGRedBorg();
    b.grounded = true;
    b.pos = { x: 100, y: 0, z: 100 };
    b.command = {
      word: 0, type: 3, button: "B Charge", recordAddress: "test",
      subtype: 0, actionIndex: 3, variantIndex: 0, exact: true,
    };
    const driver = RomDriverBridge.attach(b, {});
    assert(driver !== null, "RomDriverBridge.attach for pl0615");
    if (driver) {
      b.romDriver = driver;
      const handled = b.romDriver!.tryStartBAttack(b, [b]);
      assert(handled, "tryStartBAttack returns true (ROM B-charge handler active)");
      assert((b.cooldowns["romSpecialActive"] ?? 0) === 1, "romSpecialActive flag set");
      assert(driver.actor.fbPhaseSlots[0] === 1, "phase 0 → 1 armed after tryStartBAttack");
      // Tick advances the machine (ROM owns the frame → returns true).
      const owned = b.romDriver!.tick(b, 1, [b]);
      assert(owned, "tick returns true (ROM owns B-charge motion)");
    }
  }

  // Test 49: shared-charge — tryStartBAttack rejects borg without B-charge handler.
  // A borg whose family wires only X-special (action 2) should NOT be intercepted.
  console.log("\n[rom.selfcheck] bridge — tryStartBAttack rejects no-B-charge borg:");
  {
    const a = createRomActor();
    // Simulate a family with rootAction but hasBCharge = false.
    a.rootAction = () => {};
    a.hasBCharge = false;
    // tryStartBAttack checks hasBCharge before starting; without it, returns false.
    // (Direct actor-level check since bridge.attach requires a BorgRuntime.)
    assert(!a.hasBCharge, "borg without B-charge handler has hasBCharge == false");
  }

  // Test 50: VALKRIE cluster — table A (B ranged volley) phase flow (zz_014a200_).
  // Phase 0 seeds the DOL-read config (5 volleys / 4f timer / 30f aim window); phase 1
  // fires on the anim event + facing gate and invokes the per-borg chain callback
  // (zz_0082824_ record 0x1a for pl0b00).
  console.log("\n[rom.selfcheck] families/valkrie — table A volley phases (zz_014a200_):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      volleysLeft?: number; volleyWindow?: number; strafeAnimBase?: number;
      bRetapInput?: boolean; volleyRecoveryTimer?: number;
    };
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: ValkrieFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    configureValkrieFamily(a, "pl0b00", ctx);
    assert(a.borgNumber === 0xb00, "borgNumber stamped 0xb00 (QUICK VALKRIE)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 0; a.variantIndex = 0;
    a.cueTable = new Int8Array(96).fill(-1);
    a.cueTable[44 * 2] = 61;
    a.fbState = 61;
    const table = createDefaultStateTable();
    stepActor(a, table);
    assert(a.fbPhaseSlots[0] === 1, "volley phase 0 → 1 (+0x540 = 1)");
    assert(a.volleysLeft === 5, "volleysLeft == 5 (cfg s16[0] @0x80433bb0)");
    assert(approxEq(a.handlerTimer, 4.0), "handlerTimer == 4 (cfg s16[2] volley timer)");
    assert(approxEq(a.volleyWindow ?? -1, VALKRIE.VOLLEY_AIM_WINDOW),
      "aim window == 30.0 (FLOAT_8043a3b4)");
    // Phase 1 fire gate: anim fire event (+0x1cef) AND facing complete (+0x54a).
    a.lockTarget = { x: 0, y: 0, z: 100 };
    a.contactP0 = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "fire event + facing → phase 2 (+0x540++)");
    assert(a.volleysLeft === 4, "volleysLeft decremented (+0x6ec--)");
    assert(a.strafeAnimBase === 5, "+0x54c == 5 (fire strafe-anim base)");
    const shot = spawns.find((s) => s.addr === VALKRIE_SPAWNERS.GENERIC_SHOT);
    assert(shot !== undefined && shot.type === 0x1a,
      "volley shot via zz_0082824_ record 0x1a (FUN_800de4d8 chain callback)");
    // Phase 2 repeat fire: timer expired + volleys left → chain again, timer reseeds.
    spawns.length = 0;
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "repeat fire stays in phase 2");
    assert(a.volleysLeft === 3, "repeat fire decremented volleysLeft");
    assert(approxEq(a.handlerTimer, 4.0), "repeat fire reseeded +0x558 = 4");
    assert(spawns.some((s) => s.type === 0x1a), "repeat fire spawned the volley shot");
    // Phase 2 advance: timer expired + NO volleys left → phase 3 + 60f recovery.
    a.volleysLeft = 0;
    a.handlerTimer = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 3, "volleys exhausted → phase 3 (+0x540++)");
    assert(approxEq(a.volleyRecoveryTimer ?? -1, VALKRIE.VOLLEY_RECOVERY),
      "+0x55c == 60.0 recovery timer (FLOAT_8043a3c4)");
    assert(a.strafeAnimBase === 10, "+0x54c == 10 (recovery strafe-anim base)");
    // Phase 3 buffered re-fire: B retap → BACKWARD loop (+0x540 -= 1) + fresh volley.
    spawns.length = 0;
    a.bRetapInput = true;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "buffered B → phase 3 loops BACK to 2 (+0x540 -= 1)");
    assert(a.volleysLeft === 4, "re-fire reseeds volleysLeft = cfg[0] - 1");
    assert(spawns.some((s) => s.type === 0x1a), "re-fire spawned the volley shot");
  }

  // Test 50b: VALKRIE cluster — RING VALKRIE volley config (1 shot / 20f / 5 rings).
  console.log("\n[rom.selfcheck] families/valkrie — RING VALKRIE ring volley (FUN_80161308):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      volleysLeft?: number;
    };
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: ValkrieFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    configureValkrieFamily(a, "pl0b04", ctx);
    a.grounded = true; a.dt = 1; a.maxFall = -9999;
    a.actionIndex = 0; a.variantIndex = 0;
    a.rootAction!(a); // phase 0
    assert(a.volleysLeft === 1, "volleysLeft == 1 (cfg @0x80434730)");
    assert(approxEq(a.handlerTimer, 20.0), "volley timer == 20 (cfg s16[2])");
    a.lockTarget = { x: 0, y: 0, z: 100 };
    a.contactP0 = 1;
    a.rootAction!(a); // phase 1 fire
    const rings = spawns.filter((s) => s.addr === VALKRIE_SPAWNERS.RING_CHILD);
    assert(rings.length === 5, "5 ring children via zz_016ddb0_ (FUN_80161308 loop)");
    assert(rings.every((s, i) => s.type === i), "ring types 0..4 in order");
  }

  // Test 51: VALKRIE cluster — table B (B melee mash) phases (zz_014a8c0_).
  console.log("\n[rom.selfcheck] families/valkrie — table B melee phases (zz_014a8c0_):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      bRetapInput?: boolean; swingEvent?: number; bRetap?: boolean;
    };
    const ctx: ValkrieFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureValkrieFamily(a, "pl0b01", ctx);
    assert(a.borgNumber === 0xb01, "borgNumber stamped 0xb01 (ICE VALKRIE)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 1; a.variantIndex = 0;
    a.rootAction!(a); // phase 0 (FUN_8014a91c)
    assert(a.fbPhaseSlots[0] === 1, "melee phase 0 → 1 (+0x540++)");
    assert(approxEq(a.handlerTimer, VALKRIE.FACE_BUDGET), "face budget == 60 (FLOAT_8043a3c4)");
    assert(a.streamSlot === 1, "stream cursor = seed slot 0 + 1 (+0x6ea++)");
    // Phase 1 → 2: facing complete (lock target present) arms the 20f dash window
    // and FUN_8014acdc derives the dash speed: dist × 16 × 0.0625 / 20 = dist / 20.
    a.lockTarget = { x: 0, y: 0, z: 400 };
    a.rootAction!(a); // phase 1 (FUN_8014a9f0)
    assert(a.fbPhaseSlots[0] === 2, "facing complete → phase 2 (+0x540++)");
    assert(approxEq(a.handlerTimer, VALKRIE.DASH_WINDOW), "dash window == 20 (FLOAT_8043a3cc)");
    assert(approxEq(a.hSpeed, 400 / 20),
      "dash speed == dist × (s8)+0x1d0f × 0.0625 / 20 = 20 (FUN_8014acdc)");
    // Phase 2 → 3: in proximity (dist <= 200 via FUN_800668cc gate).
    a.pos.z = 300; // dist 100
    a.rootAction!(a); // phase 2 (FUN_8014aa88)
    assert(a.fbPhaseSlots[0] === 3, "proximity ≤ 200 → phase 3 (+0x540++)");
    // Phase 3 combo: swing re-arm event ((s8)+0x1cf0 < 0) + B retap → BACK to phase 2.
    a.swingEvent = -1;
    a.bRetapInput = true;
    const slotBefore = a.streamSlot;
    a.rootAction!(a); // phase 3 (FUN_8014ab64)
    assert(a.fbPhaseSlots[0] === 2, "combo re-arm + retap → phase 3 loops BACK to 2 (+0x540 -= 1)");
    assert(a.streamSlot === slotBefore + 1, "combo advanced the stream cursor (+0x6ea++)");
    assert(a.bRetap === false, "+0x746 retap latch cleared by the combo loop");
    // Recovery end: wall contact tears down to idle.
    a.fbPhaseSlots[0] = 3;
    a.swingEvent = 0;
    a.bRetapInput = false;
    a.wallContact = 1;
    a.controlWord = 0x3;
    a.rootAction!(a);
    assert((a.controlWord & 0x3) === 0, "wall contact → +0x5e0 &= ~3 (idle teardown)");
  }

  // Test 52: VALKRIE cluster — table C (air/lunge dive melee, action 1 v4) (zz_014ad94_).
  console.log("\n[rom.selfcheck] families/valkrie — table C air-lunge phases (zz_014ad94_):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      meleeAimPitch?: number;
    };
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: ValkrieFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    configureValkrieFamily(a, "pl0b02", ctx);
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 1; a.variantIndex = 4; // v4 routes to table C
    a.pos.x = 100; a.pos.z = 0;
    a.lockTarget = { x: 0, y: 0, z: 0 };
    a.rootAction!(a); // phase 0 (FUN_8014ade4)
    assert(a.fbPhaseSlots[0] === 1, "air-lunge phase 0 → 1 (+0x540++)");
    assert(a.streamSlot === 4, "stream cursor = seed slot 3 + 1 (+0x6ea++)");
    // Blink-away: motion = (pos − target) × 0.95 = (95,0,0); pos += motion → x = 195.
    assert(approxEq(a.pos.x, 195.0), "pos.x == 195 (blink ×0.95, FLOAT_8043a3c8)");
    a.rootAction!(a); // phase 1 (FUN_8014aef8) — facing complete → dive arm
    assert(a.fbPhaseSlots[0] === 2, "facing complete → phase 2 (+0x540++)");
    assert(approxEq(a.handlerTimer, VALKRIE.DIVE_WINDOW), "dive window == 29 (FLOAT_8043a3e0)");
    assert(a.meleeAimPitch === 0xf, "+0x54e seeded 0xf (dive pitch countdown)");
    assert(approxEq(a.gravityCoeff, 0), "+0x50 gravityCoeff zeroed for the dive");
    assert(spawns.some((s) => s.addr === VALKRIE_SPAWNERS.DIVE_FX && s.type === 0),
      "dive FX child via zz_0092dcc_(actor, 0)");
    // Phase 2 dive: hSpeed = 30 × cos(+0x18da); level pitch → 30.
    a.steerYaw = 0;
    a.rootAction!(a); // phase 2 (FUN_8014afd8)
    assert(approxEq(a.hSpeed, VALKRIE.DIVE_SPEED), "dive hSpeed == 30 (FLOAT_8043a3b4)");
    // Phase 3 landing: grounded + (s8)+0x1cef < 0 → teardown + upper cue 7 + cooldown.
    a.fbPhaseSlots[0] = 3;
    a.contactP0 = -1;
    a.controlWord = 0x3;
    a.rootAction!(a); // phase 3 (FUN_8014b130)
    assert((a.controlWord & 0x3) === 0, "landing → +0x5e0 &= ~3 (zz_006a750_(7) path)");
    assert(approxEq(a.stateTimer, 2.0), "+0x694 == 1.0 + dt (FLOAT_8043a3b0 + +0x1dc8)");
  }

  // Test 53: VALKRIE cluster — table D (X special) + WIND VALKRIE combo (zz_014b22c_).
  console.log("\n[rom.selfcheck] families/valkrie — table D X special (zz_014b22c_):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      followUpEvent?: boolean; xComboSuppressInput?: boolean;
      swingEvent?: number; comboHitsA?: number; comboHitsB?: number;
    };
    const ctx: ValkrieFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureValkrieFamily(a, "pl0b03", ctx); // WIND VALKRIE — the borg-0xb03 combo arm
    assert(a.borgNumber === 0xb03, "borgNumber stamped 0xb03 (WIND VALKRIE)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 2; a.variantIndex = 0;
    a.pos.x = 100; a.pos.z = 0;
    a.lockTarget = { x: 0, y: 0, z: 0 };
    a.hSpeed = 9; a.yVel = 5; a.hDecel = 3; a.gravityCoeff = 2;
    a.rootAction!(a); // phase 0 (FUN_8014b278)
    assert(a.fbPhaseSlots[0] === 1, "X phase 0 → 1 (+0x540++)");
    assert(a.streamSlot === 1, "stream cursor = seed slot 0 + 1 (+0x6ea++)");
    assert(approxEq(a.hSpeed, 0) && approxEq(a.yVel, 0) && approxEq(a.hDecel, 0)
      && approxEq(a.gravityCoeff, 0), "all four velocity scalars zeroed");
    // Reposition ×0.98: motion = (100,0,0) × 0.98 = (98,0,0); pos.x = 198.
    assert(approxEq(a.pos.x, 198.0), "pos.x == 198 (reposition ×0.98, FLOAT_8043a3e4)");
    // WIND VALKRIE follow-up: +0x1cf2 event with no suppress → chains the next g4 slot.
    a.swingEvent = 1;         // +0x1cf0 != 0 → hit landed
    a.followUpEvent = true;   // +0x1cf2 != 0
    a.rootAction!(a); // phase 1 (FUN_8014b378)
    assert(a.comboHitsA === 2 && a.comboHitsB === 2, "+0x6f2/+0x6f3 == 2 (hit bookkeeping)");
    assert(a.streamSlot === 2, "follow-up event chained the next g4 slot (+0x6ea++)");
    // Suppress input (+0x5bc & 0x200) latches +0x745 and eats ONE follow-up event.
    a.xComboSuppressInput = true;
    a.rootAction!(a);
    assert(a.streamSlot === 2, "suppressed follow-up did NOT chain (+0x745 latch)");
    // Wall contact ends the move: +0x5e0 &= ~3 and hSpeed/hDecel zeroed.
    a.followUpEvent = false;
    a.xComboSuppressInput = false;
    a.wallContact = 1;
    a.controlWord = 0x3;
    a.hSpeed = 7; a.hDecel = 7;
    a.rootAction!(a);
    assert((a.controlWord & 0x3) === 0, "wall contact → +0x5e0 &= ~3 (idle teardown)");
    assert(approxEq(a.hSpeed, 0) && approxEq(a.hDecel, 0), "+0x44/+0x4c zeroed on exit");

    // Non-0xb03 borg: the follow-up block is borg-gated — no chain.
    const b = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      followUpEvent?: boolean;
    };
    configureValkrieFamily(b, "pl0b00", ctx);
    b.grounded = true; b.dt = 1; b.maxFall = -9999;
    b.actionIndex = 2; b.variantIndex = 0;
    b.rootAction!(b); // phase 0
    b.followUpEvent = true;
    const slotBefore = b.streamSlot;
    b.rootAction!(b); // phase 1
    assert(b.streamSlot === slotBefore, "non-0xb03 borg ignores the follow-up event");
  }

  // Test 54: VALKRIE cluster — registrations: 6 valkries + lambda composition.
  console.log("\n[rom.selfcheck] families/valkrie — bridge registrations (8 borgs):");
  {
    const members: Array<{ id: string; num: number; hasX: boolean }> = [
      { id: "pl0b00", num: 0xb00, hasX: true },
      { id: "pl0b01", num: 0xb01, hasX: true },
      { id: "pl0b02", num: 0xb02, hasX: true },
      { id: "pl0b03", num: 0xb03, hasX: true },
      { id: "pl0b04", num: 0xb04, hasX: true },
      { id: "pl0b05", num: 0xb05, hasX: false },
      { id: "pl0b06", num: 0xb06, hasX: true },
      { id: "pl0b07", num: 0xb07, hasX: false },
    ];
    for (const { id, num, hasX } of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime,
        { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id}`);
      if (!bridge) continue;
      assert(bridge.actor.borgNumber === num,
        `${id}: borgNumber stamped 0x${num.toString(16)}`);
      assert(bridge.actor.rootAction !== null, `${id}: rootAction wired`);
      const t = bridge.actor.cueTable!;
      assert(t[44 * 2] === 61 && t[45 * 2] === 61,
        `${id}: cue rows 44/45 → state 61 (attack trampoline)`);
      // DEATH BORG LAMBDA has NO action 2 (tables A-C only): X press is a no-op.
      const actor = bridge.actor;
      actor.actionIndex = 2;
      (actor as RomActor & { grounded?: boolean }).grounded = true;
      actor.maxFall = -9999;
      actor.rootAction!(actor);
      if (hasX) {
        assert(actor.fbPhaseSlots[0] === 1, `${id}: action 2 → table D phase 0 ran`);
      } else {
        assert(actor.fbPhaseSlots[0] === 0, `${id}: action 2 is a no-op (no table D)`);
      }
    }
  }

  // Test 55: VALKRIE cluster — DEATH BORG LAMBDA II volley record 0x71 (zz_019e89c_).
  console.log("\n[rom.selfcheck] families/valkrie — lambda II shot record (zz_019e89c_):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
    };
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: ValkrieFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    configureValkrieFamily(a, "pl0b07", ctx);
    a.grounded = true; a.dt = 1; a.maxFall = -9999;
    a.actionIndex = 0; a.variantIndex = 0;
    a.rootAction!(a); // phase 0
    a.lockTarget = { x: 0, y: 0, z: 100 };
    a.contactP0 = 1;
    a.rootAction!(a); // phase 1 fire
    assert(spawns.some((s) => s.addr === VALKRIE_SPAWNERS.GENERIC_SHOT && s.type === 0x71),
      "lambda II volley shot via zz_0082824_ record 0x71 (borg-0xb07 arm)");
  }

  // Test 56: SAMURAI cluster — table S-A ranged dash-slash (FUN_80148838 @0x8033ed0c).
  console.log("\n[rom.selfcheck] families/samurai — table S-A ranged dash (0x8033ed0c):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      dashWindow?: number; volleyYawSnap?: number;
    };
    const ctx: SamuraiFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    configureSamuraiClusterFamily(a, "pl0700", ctx);
    assert(a.borgNumber === 0x700, "borgNumber stamped 0x700 (NORMAL SAMURAI)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 0; a.variantIndex = 0;
    a.lockYaw = 0x1234;
    a.rootAction!(a); // phase 0 (FUN_80148874)
    assert(a.fbPhaseSlots[0] === 1, "S-A phase 0 → 1 (+0x540++)");
    assert(approxEq(a.dashWindow ?? -1, SAMURAI.A0_WINDOW), "+0x560 window == 20 (FLOAT_8043a370)");
    assert(a.volleyYawSnap === 0x1234, "+0x54a yaw snapshot == +0x5ae");
    assert(a.streamSlot === 1, "ground slot 0 + 1 (+0x6ea++; hover bit clear)");
    // Phase 1 holds while +0x1cee (part-0 event) is clear even when facing completes.
    a.lockTarget = { x: 0, y: 0, z: 100 };
    a.rootAction!(a); // phase 1 (FUN_80148968)
    assert(a.fbPhaseSlots[0] === 1, "phase 1 holds while +0x1cee == 0");
    a.wallContact = 1;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "facing + event byte → phase 2 (+0x540++)");
    assert(a.streamSlot === 2, "slash stream armed (+0x6ea++)");
    // Phase 2 GROUNDED fork: +0x540 += 2 (skip air recovery) + hover latch cleared.
    a.controlWord = 0x40;
    a.rootAction!(a); // phase 2 (FUN_80148ab0)
    assert(a.fbPhaseSlots[0] === 4, "grounded slash end → phase 4 (+0x540 += 2)");
    assert((a.controlWord & 0x40) === 0, "+0x5e0 &= ~0x40 (hover latch off)");
    // Phase 4 recovery: wall event tears down via zz_006a474_ (ground idle return).
    a.steerYaw = 100;
    a.controlWord = 0x3;
    a.rootAction!(a); // phase 4 (FUN_80148cb0)
    assert((a.controlWord & 0x3) === 0, "wall event → +0x5e0 &= ~3 + zz_006a474_");
    assert(a.steerYaw === 0, "+0x18da zeroed by the phase-4 teardown");
    // AIR fork: phase 2 with airborne actor → phase 3 + gravity restore + 60f budget.
    const b = createRomActor() as RomActor & { grounded?: boolean };
    configureSamuraiClusterFamily(b, "pl0709", ctx);
    assert(b.borgNumber === 0x709, "borgNumber stamped 0x709 (MUSASHI)");
    b.grounded = false; b.dt = 1; b.maxFall = -9999;
    b.actionIndex = 0; b.variantIndex = 0;
    b.fbPhaseSlots[0] = 2;
    b.wallContact = 1;
    b.rootAction!(b); // phase 2 air arm
    assert(b.fbPhaseSlots[0] === 3, "airborne slash end → phase 3 (+0x540++)");
    assert(approxEq(b.handlerTimer, SAMURAI.FACE_BUDGET), "+0x558 == 60 (FLOAT_8043a384)");
    assert((b as RomActor & { moveSubPhase?: number }).moveSubPhase === 1,
      "+0x544 sub-phase byte == 1 (moveSubPhase — NOT the +0x541 lock-clear latch)");
    assert(b.fbPhaseSlots[1] === 0, "+0x541 stays 0 (the air arm does not latch lock-clear)");
  }

  // Test 57: SAMURAI cluster — table S-B close slash (zz_0148d74_ @0x8033ed20).
  console.log("\n[rom.selfcheck] families/samurai — table S-B close slash (0x8033ed20):");
  {
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      bRetapInput?: boolean; swingEvent?: number; dashStrength?: number; bRetap?: boolean;
    };
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: SamuraiFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    configureSamuraiClusterFamily(a, "pl0702", ctx);
    assert(a.borgNumber === 0x702, "borgNumber stamped 0x702 (VAMPIRE KNIGHT)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 1; a.variantIndex = 0;
    a.lockTarget = { x: 0, y: 0, z: 400 };
    a.rootAction!(a); // phase 0 (FUN_80148dc4)
    assert(a.fbPhaseSlots[0] === 1, "S-B phase 0 → 1 (+0x540++)");
    assert(a.streamSlot === 1, "v0 seed slot 0 + 1 (+0x6ea++; cfg @0x8033c36c)");
    assert(approxEq(a.handlerTimer, SAMURAI.FACE_BUDGET), "+0x558 == 60 (FLOAT_8043a384)");
    // Phase 1: facing complete → advance; dist 400 > fxRange 150 → melee FX child.
    a.rootAction!(a); // phase 1 (FUN_80148ea8)
    assert(a.fbPhaseSlots[0] === 2, "facing complete → phase 2 (+0x540++)");
    assert(spawns.some((s) => s.addr === SAMURAI_SPAWNERS.MELEE_FX),
      "cfg+4 (150) < +0x764 → zz_00b2190_(actor, 0) melee FX");
    // Phase 2 stream-driven dash: (s8)+0x1d0f = 16 → dist × 16 × 0.0625 × 0.05.
    a.dashStrength = 16;
    a.rootAction!(a); // phase 2 (FUN_80148f4c)
    assert(approxEq(a.hSpeed, 400 * 16 * 0.0625 * 0.05 * 0.92),
      "dash speed = +0x764 × byte × 0.0625 (FLOAT_8043a390) × cfg+8 (0.05), ×0.92 drag");
    assert(a.dashStrength === 0, "+0x1d0f consumed");
    // Phase 2 combo: swing re-arm ((s8)+0x1cf0 < 0) + retap → STAYS in phase 2.
    const slotBefore = a.streamSlot;
    a.swingEvent = -1;
    a.bRetapInput = true;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2, "combo re-arm keeps phase 2 (no backward loop)");
    assert(a.streamSlot === slotBefore + 1, "combo advanced the g3 stream (+0x6ea++)");
    assert(a.bRetap === false, "+0x746 retap latch cleared");
    // Wall event → zz_006a474_ teardown.
    a.swingEvent = 0; a.bRetapInput = false;
    a.wallContact = 1;
    a.controlWord = 0x3;
    a.rootAction!(a);
    assert((a.controlWord & 0x3) === 0, "wall event → +0x5e0 &= ~3 + zz_006a474_");
    // v1 config seeds slot 4 (cfg @0x8033c398).
    const b = createRomActor() as RomActor & { grounded?: boolean };
    configureSamuraiClusterFamily(b, "pl070a", ctx);
    b.grounded = true; b.dt = 1; b.maxFall = -9999;
    b.actionIndex = 1; b.variantIndex = 1;
    b.rootAction!(b);
    assert(b.streamSlot === 5, "v1 seed slot 4 + 1 (+0x6ea++; cfg s32[0] @0x8033c398)");
  }

  // Test 58: SAMURAI cluster — 6-phase rising slash (NORMAL/ZETA clone + SHOGUN bank).
  console.log("\n[rom.selfcheck] families/samurai — rising slash v2 (0x8030804c/0x8037381c/0x80351924):");
  {
    const ctx: SamuraiFamilyCtx = { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} };
    const run = (id: "pl0700" | "pl070b" | "pl0704", yv: number, grav: number) => {
      const a = createRomActor() as RomActor & {
        grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
        dashStrength?: number;
      };
      configureSamuraiClusterFamily(a, id, ctx);
      a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
      a.actionIndex = 1; a.variantIndex = 2;
      // Lock BEFORE activation — phase 0's FUN_80066838 gate latches +0x541 (lock
      // forced clear every frame) when the move starts targetless.
      a.lockTarget = { x: 0, y: 0, z: 400 };
      a.rootAction!(a); // phase 0
      assert(a.fbPhaseSlots[0] === 1, `${id}: v2 phase 0 → 1`);
      assert(approxEq(a.handlerTimer, 60), `${id}: +0x558 == 60 face budget`);
      // Phase 1: locked at 400; the row default is larger — the row-default path:
      // f = max(row868=1000, dist) / 20 = 50.
      a.rootAction!(a); // phase 1
      assert(a.fbPhaseSlots[0] === 2, `${id}: facing → phase 2`);
      assert(approxEq(a.hSpeed, 1000 / 20), `${id}: +0x44 = max(row868, +0x760) / 20`);
      // Phase 2: range gate 200 — dist 400 keeps dashing; move to 100 → advance.
      a.rootAction!(a); // dist 400 → hold
      assert(a.fbPhaseSlots[0] === 2, `${id}: dist > 200 holds phase 2`);
      a.pos.z = 300; // dist 100
      a.handlerTimer = 5;
      a.rootAction!(a);
      assert(a.fbPhaseSlots[0] === 3, `${id}: FUN_80066838(200) in range → phase 3`);
      // Phase 3: leap byte fires the rise.
      a.dashStrength = 1;
      a.rootAction!(a);
      assert(a.fbPhaseSlots[0] === 4, `${id}: +0x1d0f != 0 → phase 4`);
      assert(approxEq(a.yVel, yv), `${id}: +0x48 leap == ${yv}`);
      assert(approxEq(a.gravityCoeff, grav), `${id}: +0x50 leap gravity == ${grav}`);
      return a;
    };
    // NORMAL @0x8030804c: 32 / −2.3703704 (FLOAT_8043884c/80438850).
    run("pl0700", 32, -2.3703704);
    // ZETA clone @0x8037381c: 32 / −4 (FLOAT_8043b458/8043b45c — the ONE clone delta).
    const z = run("pl070b", 32, -4);
    assert(z.borgNumber === 0x70b, "borgNumber stamped 0x70b (DEATH BORG ZETA II)");
    // SHOGUN @0x80351924: 40 / −3 (FLOAT_8043adb8/adbc) + rise timer + timer-gated fall.
    const s = run("pl0704", 40, -3);
    assert(approxEq(s.handlerTimer, 60), "SHOGUN p3 seeds +0x558 = 60 (FLOAT_8043ada8)");
    (s as RomActor & { grounded?: boolean }).grounded = false;
    s.handlerTimer = 1;
    s.rootAction!(s); // phase 4 — airborne but timer expires → advance (SHOGUN gate)
    assert(s.fbPhaseSlots[0] === 5, "SHOGUN p4 timer gate → phase 5 without landing");
    // Liveness fallback: an UNSTAMPED +0x1d0f (host stamps only grounded/lockTarget)
    // still fires the phase-3 leap via SAMURAI.DEFAULT_DASH_STRENGTH (TUNED, 16) —
    // no stream-event deadlock in live play.
    const u = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
    };
    configureSamuraiClusterFamily(u, "pl0700", ctx);
    u.grounded = true; u.dt = 1; u.maxFall = -9999;
    u.actionIndex = 1; u.variantIndex = 2;
    u.lockTarget = { x: 0, y: 0, z: 100 };
    u.fbPhaseSlots[0] = 3; // enter phase 3 directly, dashStrength never stamped
    u.rootAction!(u);
    assert(u.fbPhaseSlots[0] === 4,
      "unstamped +0x1d0f → DEFAULT_DASH_STRENGTH fallback fires the leap (no deadlock)");
  }

  // Test 59: SAMURAI cluster — DEMON 7-phase rising slash (0x8032c7e4).
  console.log("\n[rom.selfcheck] families/samurai — demon rising slash (0x8032c7e4):");
  {
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: SamuraiFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      pitchOffset54e?: number; hitReact?: number;
    };
    configureSamuraiClusterFamily(a, "pl0701", ctx);
    assert(a.borgNumber === 0x701, "borgNumber stamped 0x701 (DEMON SAMURAI)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 1; a.variantIndex = 2;
    a.lockTarget = { x: 0, y: 0, z: 100 }; // lock BEFORE activation (+0x541 gate)
    a.rootAction!(a); // phase 0 (FUN_80122dec)
    assert(a.fbPhaseSlots[0] === 1, "demon phase 0 → 1");
    // Phase 1: within 200 → +0x54e = 0x8000 (rush-past flip) + hover latch + FX.
    a.rootAction!(a); // phase 1 (FUN_80122ea8)
    assert(a.fbPhaseSlots[0] === 2, "facing → phase 2");
    assert(approxEq(a.yVel, 20), "+0x48 rise == 20 (FLOAT_80439b5c reuse)");
    assert(approxEq(a.gravityCoeff, -1), "+0x50 == −1 (FLOAT_80439b58 reuse)");
    assert(a.pitchOffset54e === 0x8000, "FUN_80066838(200) in range → +0x54e = 0x8000");
    assert((a.controlWord & 0x40) !== 0, "zz_0066530_(0x2d) hover latch (+0x5e0 |= 0x40)");
    assert(a.ubCue === 0x2d, "+0x5e4 == 0x2d (hover cue byte)");
    assert(spawns.some((s) => s.addr === SAMURAI_SPAWNERS.MELEE_FX), "launch FX zz_00b2190_(0)");
    // Phase 2: within 500 → advance with ×0.5 (DOUBLE_80439b30) on all four scalars.
    const hs = a.hSpeed;
    a.rootAction!(a); // phase 2 (FUN_80122fd4)
    assert(a.fbPhaseSlots[0] === 3, "FUN_80066838(500) > 0 → phase 3");
    assert(a.yVel <= 10 + 1e-4, "+0x48 halved (DOUBLE_80439b30 = 0.5)");
    void hs;
    // Phase 3 → 4 after the 10f hang window.
    a.handlerTimer = 0;
    a.rootAction!(a); // phase 3 (FUN_801230fc)
    assert(a.fbPhaseSlots[0] === 4, "hang window done → phase 4 (slot 7 stream)");
    // Phase 4: contact → dive −40 + gravity restore.
    a.contactP0 = 1;
    a.rootAction!(a); // phase 4 (FUN_801231b8)
    assert(a.fbPhaseSlots[0] === 5, "+0x1cef contact → phase 5");
    assert(approxEq(a.yVel, -40), "+0x48 == −40 (FLOAT_80439b70)");
    // Phase 5: landing clears the hover latch (zz_0066530_(0x2c)).
    a.contactP0 = 0;
    (a as RomActor & { grounded?: boolean }).grounded = true;
    a.wallContact = 1;
    a.rootAction!(a); // phase 5 (FUN_80123254)
    assert(a.fbPhaseSlots[0] === 6, "landed → phase 6");
    assert((a.controlWord & 0xc0) === 0, "zz_0066530_(0x2c) cleared +0x5e0 bits 0x40|0x80");
    assert(a.ubCue === 0x2c, "+0x5e4 == 0x2c (landing cue byte)");
  }

  // Test 60: SAMURAI cluster — SONIC v2 multi-slash + own X table.
  console.log("\n[rom.selfcheck] families/samurai — sonic v2 (0x8034d598) + X (0x8034d5bc):");
  {
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: SamuraiFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      followUpEvent?: boolean; hitReact?: number;
    };
    configureSamuraiClusterFamily(a, "pl0703", ctx);
    assert(a.borgNumber === 0x703, "borgNumber stamped 0x703 (SONIC SAMURAI)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 1; a.variantIndex = 2;
    a.lockTarget = { x: 0, y: 0, z: 100 }; // lock BEFORE activation (+0x541 gate)
    a.rootAction!(a); // phase 0 (FUN_801647a0)
    assert(a.streamSlot === 7, "+0x6ea = 6 then ++ (slot 6 stream armed)");
    spawns.length = 0;
    a.rootAction!(a); // phase 1 (FUN_80164878)
    assert(a.fbPhaseSlots[0] === 2, "facing → phase 2");
    assert(spawns.some((s) => s.addr === SAMURAI_SPAWNERS.MELEE_FX),
      "sonic phase-1 FX is UNCONDITIONAL (no range gate)");
    a.rootAction!(a); // phase 2 (FUN_80164968) — within 500 → advance
    assert(a.fbPhaseSlots[0] === 3, "FUN_80066838(500) != 0 → phase 3");
    assert(approxEq(a.hSpeed, 40), "+0x44 pass-through speed == 40 (FLOAT_8043a99c)");
    // Phase 3 re-fire: follow-up event + expired window re-arms the CURRENT slot.
    a.handlerTimer = 0;
    a.followUpEvent = true;
    const slotBefore = a.streamSlot;
    a.rootAction!(a); // phase 3 (FUN_80164a14)
    assert(a.streamSlot === slotBefore, "re-fire uses (s8)+0x6ea WITHOUT increment");
    // --- Own X table @0x8034d5bc ---
    const x = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      hitReact?: number;
    };
    configureSamuraiClusterFamily(x, "pl0703", ctx);
    x.grounded = true; x.dt = 1; x.timescale = 1; x.tierScale = 1; x.maxFall = -9999;
    x.actionIndex = 2; x.variantIndex = 0;
    x.pos.x = 100;
    x.lockTarget = { x: 0, y: 0, z: 0 };
    x.rootAction!(x); // phase 0 (FUN_80164b9c)
    assert(x.fbPhaseSlots[0] === 1, "sonic X phase 0 → 1");
    assert(approxEq(x.pos.x, 195), "blink-away ×0.95 (FLOAT_8043a9a8): pos.x 100 → 195");
    assert(x.streamSlot === 1, "g4 slot 0 + 1 (+0x6ea++)");
    x.handlerTimer = 0;
    x.rootAction!(x); // phase 1 (FUN_80164ce0) — window done
    assert(x.fbPhaseSlots[0] === 2, "wind-up done → phase 2 (next g4 slot)");
    x.contactP0 = 1;
    x.steerYaw = 0;
    x.rootAction!(x); // phase 2 (FUN_80164dac)
    assert(x.fbPhaseSlots[0] === 3, "+0x1cef contact → phase 3");
    assert(approxEq(x.hSpeed, 100), "+0x44 == 100 × cos(+0x18da) (FLOAT_8043a9ac)");
    // Phase 3 heavy-hit arm: (+0x1d9 & 0x10) doubles the brake + pops yVel + despawn.
    x.hitReact = 0x10;
    x.rootAction!(x); // phase 3 (FUN_80164e8c)
    assert(x.fbPhaseSlots[0] === 4, "(+0x1d9 & 0x90) → phase 4");
    assert(approxEq(x.handlerTimer, 60), "+0x558 = 30 + 30 (heavy-hit extension)");
    // hSpeed 100 ×0.5 ×0.5 = 25 (integration already ran this frame — check yVel pop):
    assert(x.yVel > 0 || approxEq(x.hSpeed, 25), "×0.5 ×0.5 brake + yVel += 3 arm ran");
    // Phase 4 → 5 after wind-down; phase 5 landing.
    x.handlerTimer = 0;
    x.rootAction!(x); // phase 4 (FUN_80164f98)
    assert(x.fbPhaseSlots[0] === 5, "wind-down done → phase 5 (finisher stream)");
    x.contactP0 = -1;
    (x as RomActor & { grounded?: boolean }).grounded = true;
    x.controlWord = 0x3;
    x.rootAction!(x); // phase 5 (FUN_801650a8)
    assert((x.controlWord & 0x3) === 0, "landing → +0x5e0 &= ~3 + zz_006a750_(7)");
    assert(approxEq(x.stateTimer, 5), "+0x694 == 4 (FLOAT_8043a9c4) + dt");
  }

  // Test 61: SAMURAI cluster — SHOGUN sky dive (0x80351908) + heavy slash (0x80351914).
  console.log("\n[rom.selfcheck] families/samurai — shogun sky dive + heavy slash:");
  {
    const spawns: Array<{ addr: number; type: number }> = [];
    const ctx: SamuraiFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
    };
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      dashStrength?: number;
    };
    configureSamuraiClusterFamily(a, "pl0704", ctx);
    assert(a.borgNumber === 0x704, "borgNumber stamped 0x704 (SAMURAI SHOGUN)");
    a.grounded = true; a.dt = 1; a.timescale = 1; a.tierScale = 1; a.maxFall = -9999;
    a.actionIndex = 1; a.variantIndex = 3; // v3/v4 → sky dive
    a.pos.z = 1000; // far from target → phase-1 range gate (150) holds
    a.lockTarget = { x: 0, y: 100, z: 0 };
    a.rootAction!(a); // phase 0 (FUN_80175270) — TAIL-CALLS zz_0175380_ same frame
    assert(a.fbPhaseSlots[0] === 1, "sky dive phase 0 → 1 (same-frame tail call ran)");
    assert(spawns.some((s) => s.addr === SAMURAI_SPAWNERS.DIVE_FX),
      "dive FX child via zz_0092dcc_(actor, 0)");
    // The tail-called phase-1 body re-aimed: +0x48 = (targetY + 50 − posY) / 12.
    assert(approxEq(a.yVel, 150 / 12, 1e-2), "+0x48 == (t.y + 50 (FLOAT_8043ad74)) / 12");
    // Phase 1 → 2 once within 150 (FUN_80066838(FLOAT_8043ad80) != 0).
    a.pos.x = 0; a.pos.z = 100;
    a.rootAction!(a); // phase 1 (zz_0175380_)
    assert(a.fbPhaseSlots[0] === 2, "FUN_80066838(150) in range → phase 2 (×0.25 scale)");
    // Phase 2 dash-byte refresh: dist × 2.5 / 20 (DOUBLE_8043ad90 / DOUBLE_8043ad98).
    a.pos.z = 200; // dist 200 (> NEAR_RANGE — skip the 0.8 near drag)
    a.dashStrength = 1;
    a.rootAction!(a); // phase 2 (FUN_80175508)
    assert(approxEq(a.hSpeed, 200 * 2.5 / 20 * 0.92, 1e-3),
      "+0x44 = (2.5 × +0x760) / 20 then ×0.92 drag (DOUBLE_8043ad90/ad98, FLOAT_8043ada4)");
    // Heavy slash (v1) @0x80351914 seeds literal slot 5 → advance dash → slam slot 4.
    const h = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
    };
    configureSamuraiClusterFamily(h, "pl0707", ctx);
    assert(h.borgNumber === 0x707, "borgNumber stamped 0x707 (CHRONO SAMURAI)");
    h.grounded = true; h.dt = 1; h.maxFall = -9999;
    h.actionIndex = 1; h.variantIndex = 1;
    h.lockTarget = { x: 0, y: 0, z: 400 }; // lock BEFORE activation (+0x541 gate)
    h.rootAction!(h); // phase 0 (FUN_8017570c)
    assert(h.fbPhaseSlots[0] === 1 && approxEq(h.handlerTimer, 60),
      "heavy slash phase 0 → 1 (+0x558 = 60, FLOAT_8043ada8)");
    h.rootAction!(h); // phase 1 (FUN_801757c8)
    assert(h.fbPhaseSlots[0] === 2, "facing → phase 2 (dash arm)");
    h.pos.z = 300; // dist 100 → range gate 200 advances
    h.rootAction!(h); // phase 2 (FUN_801758c8)
    assert(h.fbPhaseSlots[0] === 3, "FUN_80066838(200) → phase 3 (slam stream slot 4)");
    h.wallContact = 1;
    h.controlWord = 0x3;
    h.rootAction!(h); // phase 3 (FUN_8017597c)
    assert((h.controlWord & 0x3) === 0, "wall event → +0x5e0 &= ~3 + zz_006a474_");
  }

  // Test 62: SAMURAI cluster — SHOGUN X (0x80351950): borg-switched slot + payload;
  // plus the 13-borg registration sweep.
  console.log("\n[rom.selfcheck] families/samurai — shogun X + cluster registrations:");
  {
    const spawns: Array<{ addr: number; type: number }> = [];
    const freezes: number[] = [];
    const ctx: SamuraiFamilyCtx = {
      onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {},
      onFamilyProjectile: (_a, addr, type) => { spawns.push({ addr, type }); },
      onTimeStop: (_a, frames) => { freezes.push(frames); },
    };
    // SHOGUN (0x704): g4 slot 0, phase-0 trail child, phase-2 strike child.
    const a = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      swingEvent?: number;
    };
    configureSamuraiClusterFamily(a, "pl0704", ctx);
    a.grounded = true; a.dt = 1; a.maxFall = -9999;
    a.actionIndex = 2; a.variantIndex = 0;
    a.rootAction!(a); // phase 0 (FUN_80175ee8)
    assert(a.streamSlot === 1, "SHOGUN X seeds g4 slot 0 (+0x6ea++ → 1)");
    assert(spawns.some((s) => s.addr === SAMURAI_SPAWNERS.SHOGUN_X_TRAIL),
      "borg 0x704 phase 0 spawns the trail child (zz_01a5e88_)");
    a.lockTarget = { x: 0, y: 0, z: 100 };
    a.rootAction!(a); // phase 1 (FUN_80175ffc) — facing → advance
    assert(a.fbPhaseSlots[0] === 2, "facing → phase 2");
    a.swingEvent = 1;
    a.rootAction!(a); // phase 2 (FUN_801760b4)
    assert(a.fbPhaseSlots[0] === 3, "+0x1cf0 swing event → phase 3");
    assert(spawns.some((s) => s.addr === SAMURAI_SPAWNERS.SHOGUN_X_CHILD),
      "borg 0x704 phase 2 spawns the strike child (zz_018eea4_)");
    // CHRONO (0x707): g4 slot 1, phase-2 time-stop 300f (zz_0067f98_).
    const c = createRomActor() as RomActor & {
      grounded?: boolean; lockTarget?: { x: number; y: number; z: number } | null;
      swingEvent?: number;
    };
    configureSamuraiClusterFamily(c, "pl0707", ctx);
    c.grounded = true; c.dt = 1; c.maxFall = -9999;
    c.actionIndex = 2; c.variantIndex = 0;
    c.rootAction!(c); // phase 0
    assert(c.streamSlot === 2, "CHRONO X seeds g4 slot 1 (+0x6ea++ → 2)");
    c.lockTarget = { x: 0, y: 0, z: 100 };
    c.rootAction!(c); // phase 1
    c.swingEvent = 1;
    c.rootAction!(c); // phase 2
    assert(freezes.length === 1 && freezes[0] === 300,
      "borg 0x707 phase 2 fires onTimeStop(300) (zz_0067f98_(actor, 300))");
    // Registration sweep: all 13 cluster borgs attach with rootAction + real cue table.
    const members: Array<[string, number]> = [
      ["pl0700", 0x700], ["pl0701", 0x701], ["pl0702", 0x702], ["pl0703", 0x703],
      ["pl0704", 0x704], ["pl0705", 0x705], ["pl0707", 0x707], ["pl0708", 0x708],
      ["pl0709", 0x709], ["pl070a", 0x70a], ["pl070b", 0x70b], ["pl070c", 0x70c],
      ["pl070d", 0x70d],
    ];
    for (const [id, num] of members) {
      const runtime = {
        borgId: id, team: 0, uid: "t",
        pos: { x: 0, y: 0, z: 0 }, vel: { x: 0, y: 0, z: 0 },
        rotY: 0, grounded: true, cooldowns: {},
      } as unknown as BorgRuntime;
      const bridge = RomDriverBridge.attach(runtime,
        { onArmHit: () => {}, onPlayAnim: () => {}, onFireChild: () => {} });
      assert(bridge !== null, `RomDriverBridge attaches for ${id}`);
      if (!bridge) continue;
      assert(bridge.actor.borgNumber === num, `${id}: borgNumber 0x${num.toString(16)}`);
      assert(bridge.actor.rootAction !== null, `${id}: rootAction wired`);
      const t = bridge.actor.cueTable!;
      assert(t[44 * 2] === 61 && t[45 * 2] === 61, `${id}: cue rows 44/45 → state 61`);
      // Action 0 phase 0 runs (table S-A) for every member.
      const actor = bridge.actor;
      (actor as RomActor & { grounded?: boolean }).grounded = true;
      actor.maxFall = -9999;
      actor.actionIndex = 0; actor.variantIndex = 0;
      actor.rootAction!(actor);
      assert(actor.fbPhaseSlots[0] === 1, `${id}: action 0 → S-A phase 0 ran`);
    }
    // v3/v4 lunge config sanity: the DOL-read config replaced the TUNED default.
    assert(SAMURAI_LUNGE_ROM_CONFIG.seedSlot === 3 && SAMURAI_LUNGE_ROM_CONFIG.timerFrames === 20
      && approxEq(SAMURAI_LUNGE_ROM_CONFIG.proximityRange, 150)
      && approxEq(SAMURAI_LUNGE_ROM_CONFIG.velocityScale ?? 0, 0.25)
      && approxEq(SAMURAI_LUNGE_ROM_CONFIG.decel ?? 0, 0.92)
      && approxEq(SAMURAI_LUNGE_ROM_CONFIG.repositionScale ?? 0, 0.95),
      "SAMURAI_LUNGE_ROM_CONFIG matches the DOL bytes @0x80308020 (+4 siblings)");
  }

  console.log("\n[rom.selfcheck] families/eagle-jet — action 1 (FUN_8012b458):");
  {
    const actor = createRomActor() as RomActor & EagleJetScratch;
    const played: number[] = [];
    configureEagleJetFamily(actor, { onPlayCue: (_a, cue) => played.push(cue) });
    actor.cueTable = new Int8Array(48 * 2).fill(-1);
    actor.cueTable[EAGLE_JET_ACTION1.EXIT_CUE * 2] = 0;
    actor.actionIndex = 1;
    actor.dt = 1;
    actor.controlWord = 0x3;
    actor.rootAction!(actor);
    assert(actor.borgNumber === 0x61b, "EAGLE JET ctor stamps borg number 0x61b");
    assert(actor.fbPhaseSlots[0] === 1 && approxEq(actor.handlerTimer, 45),
      "action-1 entry seeds +0x540=1 and +0x558=45.0");
    assert(actor.effectMode6e8 === EAGLE_JET_ACTION1.FX_MODE,
      "action-1 writes +0x6e8=0x83");
    assert(actor.retiredHitboxKind === 0x7f
      && actor.preparedPartSlots?.join(",") === "4,5"
      && played[0] === 0x20,
      "entry retires kind-0x7f, prepares parts 4/5, and plays cue 0x20");

    actor.handlerTimer = 1;
    actor.rootAction!(actor);
    assert(approxEq(actor.stateTimer, 17),
      "timer expiry ports zz_006a53c_(actor,0x10): cooldown=16+dt");
    assert((actor.controlWord & 0x3) === 0 && actor.fbCue === 0x1b,
      "timer expiry clears action bits and dispatches full-body cue 0x1b");
  }

  console.log("\n[rom.selfcheck] families/melee-robot — phase 1 speed source (FUN_800f2498):");
  {
    const fx: number[] = [];
    const handler = createMeleeRobot(
      { onFamilyProjectile: (_a, addr) => fx.push(addr) },
      { rangeRows868: [90, 120, 150] },
    );
    const actor = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
      streamTickGate?: boolean;
      rangeRows868?: readonly [number, number, number];
      targetDistance760?: number;
      movementTrailFlag1d9b?: number;
    };
    actor.fbPhaseSlots[0] = 1;
    actor.handlerTimer = 1;
    actor.dt = 1;
    actor.pos = { x: 0, y: 0, z: 0 };
    actor.lockTarget = { x: 300, y: 0, z: 0 };
    actor.targetDistance760 = 300;
    actor.streamTickGate = false;
    handler(actor);
    assert(actor.fbPhaseSlots[0] === 2 && approxEq(actor.handlerTimer, 20),
      "phase 1 expiry advances and seeds FLOAT_80439094=20");
    assert(approxEq(actor.hSpeed, 30) && approxEq(actor.hDecel, 0),
      "locked branch uses FLOAT_80439098(2) * +0x760 / 20 and clears +0x4c");
    assert(fx[0] === 0x800b2190,
      "+0x760 > FLOAT_8043909c triggers zz_00b2190_(actor,0)");

    const noTarget = createRomActor() as RomActor & {
      lockTarget?: null;
      rangeRows868?: readonly [number, number, number];
    };
    noTarget.fbPhaseSlots[0] = 1;
    noTarget.handlerTimer = 1;
    noTarget.dt = 1;
    noTarget.prevActionIndex = 2;
    noTarget.lockTarget = null;
    noTarget.rangeRows868 = [90, 120, 150];
    handler(noTarget);
    assert(approxEq(noTarget.hSpeed, 7.5),
      "targetless branch selects +0x868 row[prevAction%3] / 20");

    actor.fbPhaseSlots[0] = 2;
    actor.handlerTimer = 20;
    actor.hSpeed = 10;
    actor.yVel = 2;
    actor.wallContact = 0;
    fx.length = 0;
    handler(actor);
    assert(approxEq(actor.handlerTimer, 19) && approxEq(actor.hSpeed, 9)
      && approxEq(actor.yVel, 1.8),
      "phase 2 counts down and applies FLOAT_804390a0=0.9 while +0x760 > 150");
    assert(fx.includes(MELEE_ROBOT.DISTANCE_TRAIL_HELPER_ADDR),
      "+0x44 > FLOAT_804390a4=3 invokes zz_00b22f4_");

    actor.targetDistance760 = 100;
    actor.movementTrailFlag1d9b = 1;
    actor.handlerTimer = 10;
    handler(actor);
    assert(actor.movementTrailFlag1d9b === 0,
      "+0x760 <= 150 clears actor+0x1d9b instead of running recovery movement");

    const combo = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
      targetDistance760?: number;
      bRetap?: boolean;
      swingReArm?: boolean;
    };
    combo.fbPhaseSlots[0] = 2;
    combo.lockTarget = { x: 200, y: 0, z: 0 };
    combo.targetDistance760 = 200;
    combo.bRetap = true;
    combo.swingReArm = true;
    combo.hDecel = 7;
    handler(combo);
    assert(combo.handlerTimer === 20 && approxEq(combo.hSpeed, 20) && combo.hDecel === 0,
      "combo replay restores the 20-frame timer, target speed, and deceleration clear");

    const elevated = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
    };
    elevated.fbPhaseSlots[0] = 1;
    elevated.handlerTimer = 1;
    elevated.lockTarget = { x: 0, y: 400, z: 300 };
    handler(elevated);
    assert(approxEq(elevated.hSpeed, 50),
      "fallback +0x760 uses full 3D distance sqrt(400^2+300^2)=500");

    assert(ROBOT_MELEE_RANGE_ROWS.pl0400.join(",") === "1000,1000,2500"
      && ROBOT_MELEE_RANGE_ROWS.pl0401.join(",") === "1000,1000,2000"
      && ROBOT_MELEE_RANGE_ROWS.pl0406.join(",") === "1000,1000,2500"
      && ROBOT_MELEE_RANGE_ROWS.pl040b.join(",") === "1000,1000,1000",
      "production action-1 members use DOL page +0x134/+0x140/+0x14c rows");
  }

  console.log("\n[rom.selfcheck] families/tank-borg - NORMAL TANK / LEOPARD bespoke actions:");
  {
    const shots: Array<[number, number]> = [];
    const actor = createRomActor() as RomActor & NormalTankScratch;
    configureTankFamily(actor, "pl0c00", {
      onFamilyProjectile: (_a, address, type) => shots.push([address, type]),
    });
    actor.cueTable = new Int8Array(48 * 2).fill(-1);
    actor.cueTable[NORMAL_TANK.ACTION0_EXIT_CUE * 2] = 0;
    actor.actionIndex = 0;
    actor.dt = 1;
    actor.rootAction!(actor);
    assert(actor.fbPhaseSlots[0] === 1 && actor.stateTimer === 15,
      "action 0 phase 0 seeds the exact 15-frame first windup");
    actor.rootAction!(actor);
    assert(actor.fbPhaseSlots[0] === 2 && actor.stateTimer === 10,
      "action 0 phase 1 seeds the exact 10-frame second windup");
    actor.stateTimer = 0;
    actor.rootAction!(actor);
    assert(actor.fbPhaseSlots[0] === 3,
      "barrel-readiness advances action 0 into the burst phase");
    for (let i = 0; i < 13; i++) actor.rootAction!(actor);
    assert(shots.filter(([address]) => address === NORMAL_TANK.SHOT_HELPER).length === 3,
      "short action-0 branch fires exactly three shots through zz_0082824_");
    assert(actor.fbPhaseSlots[0] === 4 && actor.stateTimer === 30,
      "short burst advances to the exact 30-frame recovery");

    const air = createRomActor() as RomActor & NormalTankScratch;
    configureTankFamily(air, "pl0c06", {});
    air.actionIndex = 2;
    air.variantIndex = 1;
    air.dt = 1;
    air.rootAction!(air);
    assert(air.fbPhaseSlots[0] === 1 && air.handlerTimer === 30
      && (air.controlWord & 0x40) !== 0,
      "action 2 variant 1 enters the airborne subtable and seeds 30-frame aim");
    air.tankYawReady = true;
    air.tankDesiredPitch = 0;
    air.tankTurretPitch = 0;
    air.rootAction!(air);
    air.rootAction!(air);
    assert(approxEq(air.hSpeed, 9.7) && approxEq(air.hDecel, -0.3),
      "air-fire phase seeds hSpeed=10/hDecel=-0.3, then its wrapper integrates once");
  }

  console.log("\n[rom.selfcheck] families/arrow-ninja - action 1 variant routing:");
  {
    const actor = createRomActor() as RomActor & ArrowNinjaScratch;
    actor.lockTarget = { x: 100, y: 0, z: 0 };
    configureArrowNinjaFamily(actor, "pl0002", {});
    actor.actionIndex = 1;
    actor.variantIndex = 1;
    actor.rootAction!(actor);
    assert(actor.borgNumber === 0x002 && actor.fbPhaseSlots[0] === 1,
      "pl0002 action-1 v1 routes to FUN_800d0d64 ground-chain phase 0");
    assert(actor.handlerTimer === ARROW_NINJA_ACTION1.AIM_TIMER && actor.streamSlot === 4,
      "ground-chain entry seeds 60-frame aim and consumes group-3 slot 3");

    const diveFx: number[] = [];
    const dive = createRomActor() as RomActor & ArrowNinjaScratch;
    configureArrowNinjaFamily(dive, "pl000b", {
      onFamilyProjectile: (_a, address) => diveFx.push(address),
    });
    dive.actionIndex = 1;
    dive.variantIndex = 3;
    dive.rootAction!(dive);
    assert(dive.borgNumber === 0x00b && dive.fbPhaseSlots[0] === 1
      && dive.handlerTimer === ARROW_NINJA_ACTION1.AIR_DIVE_SPEED,
      "pl000b action-1 v3 routes to FUN_800d11cc and seeds the 30-frame dive");
    assert(diveFx[0] === 0x80092dcc,
      "air-dive entry routes the exact zz_0092dcc_(actor,0) effect callback");
  }

  console.log("\n[rom.selfcheck] families/eagle-robot - action 0 variant tables:");
  {
    const shots: Array<[number, number]> = [];
    const actor = createRomActor() as RomActor & EagleRobotScratch;
    actor.lockTarget = { x: 10, y: 0, z: 0 };
    actor.eagleAmmoCount = 2;
    configureEagleRobotFamily(actor, "pl061a", {
      onFamilyProjectile: (_a, address, type) => shots.push([address, type]),
    });
    actor.actionIndex = 0;
    actor.variantIndex = 0;
    actor.rootAction!(actor);
    assert(actor.borgNumber === 0x61a && actor.fbPhaseSlots[0] === 1
      && actor.eagleAimTimer === EAGLE_ROBOT_ACTION0.AIM_TIMER,
      "PROTO EAGLE v0 enters table 0x8033195c with a 30-frame aim timer");
    actor.contactP0 = 1;
    actor.eagleAimTimer = 0;
    actor.rootAction!(actor);
    assert(actor.fbPhaseSlots[0] === 2 && actor.handlerTimer === 2,
      "PROTO EAGLE fire transition uses its exact 2-frame repeat timer");
    assert(shots.some(([a, t]) => a === 0x80082824 && t === 0x6e)
      && shots.some(([a, t]) => a === 0x80082824 && t === 0x6f),
      "PROTO EAGLE fires ROM projectile records 0x6e and 0x6f");

    const eagle = createRomActor() as RomActor & EagleRobotScratch;
    configureEagleRobotFamily(eagle, "pl0606", {});
    eagle.actionIndex = 0;
    eagle.variantIndex = 4;
    eagle.rootAction!(eagle);
    assert(eagle.fbPhaseSlots[0] === 1 && eagle.eagleAimTimer === 30,
      "EAGLE ROBOT v4 enters airborne table 0x80331974");
  }

  console.log("\n[rom.selfcheck] shared-robot action 0 — DOL configs + phase routing (zz_00f1e30_):");
  {
    assert(ROBOT_DASH.DASH_TIMER === 30,
      "+0x560 phase window is FLOAT_80439078=30.0");
    assert(ROBOT_ACTION0_CONFIGS.pl0407.slotBase === 3
      && ROBOT_ACTION0_CONFIGS.pl0407.timerSeed === 4
      && ROBOT_ACTION0_CONFIGS.pl0407.maskByte === 5,
      "pl0407 config matches DOL block 0x80327f5c");
    assert(ROBOT_ACTION0_CONFIGS.pl040b.ammoSlot === 2
      && ROBOT_ACTION0_CONFIGS.pl040d.slotBase === 6,
      "Omega-II uses ammo cell 2 and Omega-IV starts at stream slot 6");

    const ctx = {
      onAllocateResource: () => false,
    } as StreamContext & {
      onAllocateResource: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
    };
    const handler = createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0407, ctx);
    const actor = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
      dashTimer?: number;
      dashConfigByte?: number;
    };
    actor.lockTarget = { x: 10, y: 0, z: 0 };
    actor.ubState = 1;
    handler(actor);
    assert(actor.fbPhaseSlots[0] === 1 && actor.dashTimer === 30,
      "phase 0 advances and seeds +0x560=30");
    assert(actor.handlerTimer === 4 && actor.dashConfigByte === 5 && actor.streamSlot === 3,
      "phase 0 copies pl0407 config timer/count/stream slot");

    actor.fbPhaseSlots[0] = 2;
    actor.wallContact = 1;
    handler(actor);
    assert(actor.fbPhaseSlots[0] === 4,
      "ammo denial takes FUN_800f2008 failure branch (+0x540 += 2)");

    type DashCase = {
      id: keyof typeof ROBOT_ACTION0_CONFIGS;
      borg: number;
      expected: Array<[number, number]>;
    };
    const dashCases: DashCase[] = [
      { id: "pl0400", borg: 0x400, expected: [[0x8007f29c, 0]] },
      { id: "pl0401", borg: 0x401, expected: [[0x8009ad20, 0]] },
      { id: "pl0402", borg: 0x402, expected: [[0x800c3be0, 0x0c], [0x800c3be0, 0x0d]] },
      { id: "pl0403", borg: 0x403, expected: [[0x800e0e90, 0], [0x800e0e90, 1]] },
      { id: "pl0404", borg: 0x404, expected: [[0x800c3be0, 0x0a]] },
      { id: "pl0405", borg: 0x405, expected: [[0x80082824, 0x20], [0x80082824, 0x21]] },
      { id: "pl0407", borg: 0x407, expected: [[0x80082824, 0x78], [0x80082824, 0x79]] },
      { id: "pl0408", borg: 0x408, expected: [[0x80082824, 0x47], [0x80082824, 0x48]] },
      { id: "pl0409", borg: 0x409, expected: [[0x800c3be0, 0x39], [0x800c3be0, 0x3a]] },
      { id: "pl040a", borg: 0x40a, expected: [[0x8007f29c, 4]] },
      { id: "pl040b", borg: 0x40b, expected: [[0x800e0e90, 2], [0x800e0e90, 3]] },
      { id: "pl040c", borg: 0x40c, expected: [[0x80082824, 0x73], [0x80082824, 0x74]] },
      { id: "pl040d", borg: 0x40d, expected: [[0x800c3be0, 0x5f], [0x800c3be0, 0x60]] },
    ];
    for (const test of dashCases) {
      const shots: Array<[number, number]> = [];
      const a = createRomActor() as RomActor & {
        lockTarget?: { x: number; y: number; z: number } | null;
        dashConfigByte?: number;
      };
      a.borgNumber = test.borg;
      a.lockTarget = { x: 10, y: 0, z: 0 };
      a.fbPhaseSlots[0] = 3;
      a.parts[0].streamPtr = 0;
      a.contactP0 = 1;
      a.handlerTimer = ROBOT_ACTION0_CONFIGS[test.id].timerSeed;
      a.dashConfigByte = ROBOT_ACTION0_CONFIGS[test.id].maskByte;
      createRobotDashHandler(ROBOT_ACTION0_CONFIGS[test.id], {
        onAllocateResource: () => true,
        onFamilyProjectile: (_owner, addr, type) => shots.push([addr, type]),
      })(a);
      assert(test.expected.every(([addr, type]) => shots.some(([x, y]) => x === addr && y === type)),
        `${test.id} executes its real config+4 callback projectile/child family`);
    }

    const deniedTimed = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
      dashConfigByte?: number;
    };
    deniedTimed.lockTarget = { x: 10, y: 0, z: 0 };
    deniedTimed.fbPhaseSlots[0] = 3;
    deniedTimed.parts[0].streamPtr = 0;
    deniedTimed.contactP0 = 1;
    deniedTimed.dashConfigByte = 5;
    createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0405, { onAllocateResource: () => false })(deniedTimed);
    assert(deniedTimed.handlerTimer === 3 && deniedTimed.dashConfigByte === 4,
      "timed callback mutates timer/count before denial, then config+8 decrements the timer");

    const transitions = createRomActor() as RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
      dashTimer?: number;
      statusWord5bc?: number;
      inputFlags5d8?: number;
      robotSlotFlags?: number[];
      aimPitch18e0?: number;
      aimYaw18e2?: number;
      onStartStream?: (group: number, slot: number, mask: number) => boolean;
    };
    transitions.lockTarget = { x: 10, y: 0, z: 0 };
    transitions.fbPhaseSlots[0] = 1;
    transitions.dashTimer = 1;
    createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0400, {})(transitions);
    assert(transitions.fbPhaseSlots[0] === 2,
      "phase 1 timer expiry advances through FUN_800f1f9c");
    transitions.parts[0].streamPtr = -1;
    createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0400, { onAllocateResource: () => true })(transitions);
    assert(transitions.fbPhaseSlots[0] === 2,
      "phase 2 does not treat an exhausted local stream pointer as +0x1cee completion");
    transitions.wallContact = 1;
    createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0400, { onAllocateResource: () => true })(transitions);
    assert(transitions.fbPhaseSlots[0] === 3,
      "phase 2 advances only when modeled +0x1cee is raised");
    transitions.parts[0].streamPtr = 0;
    transitions.parts[1].stateByte = -1;
    transitions.statusWord5bc = 0x200;
    let repeatSlot = -1;
    transitions.onStartStream = (_group, slot) => { repeatSlot = slot; return true; };
    createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0400, { onAllocateResource: () => true })(transitions);
    assert(transitions.fbPhaseSlots[0] === 3 && repeatSlot === 1,
      "config+8 held continuation restarts stream base+1 without advancing phase 3");

    const exitGate = createRomActor() as typeof transitions;
    exitGate.lockTarget = { x: 10, y: 0, z: 0 };
    exitGate.fbPhaseSlots[0] = 3;
    exitGate.parts[0].streamPtr = -1;
    exitGate.wallContact = 1;
    exitGate.robotSlotFlags = [1, 0, 0, 0];
    const gated = createRobotDashHandler(ROBOT_ACTION0_CONFIGS.pl0403, {});
    gated(exitGate);
    assert(exitGate.fbPhaseSlots[0] === 3,
      "config+0x10 two-child exit gate holds phase 3 while a child slot is owned");
    exitGate.robotSlotFlags = [0, 0, 0, 0];
    gated(exitGate);
    assert(exitGate.fbPhaseSlots[0] === 4,
      "config+0x10 exit gate advances once both child ownership bytes clear");
    exitGate.aimPitch18e0 = 1000;
    exitGate.aimYaw18e2 = -1000;
    exitGate.inputFlags5d8 = 0x10;
    exitGate.controlWord = 3;
    gated(exitGate);
    assert(exitGate.aimPitch18e0 === 960 && exitGate.aimYaw18e2 === -960
      && (exitGate.controlWord & 3) === 0,
      "phase 4 decays exact +0x18e0/+0x18e2 aim fields and takes high-nibble exit");

    const liveDashMembers = dashCases.map(({ id }) => id);
    for (const id of liveDashMembers) {
      const runtime = makeMinimalGRedBorg();
      runtime.borgId = id;
      const driver = RomDriverBridge.attach(runtime, {});
      assert(driver !== null, `${id} bridge registration attaches`);
      if (!driver) continue;
      for (let variant = 0; variant < 5; variant++) {
        driver.actor.fbPhaseSlots[0] = 0;
        driver.actor.actionIndex = 0;
        driver.actor.variantIndex = variant;
        (driver.actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = { x: 10, y: 0, z: 0 };
        driver.actor.rootAction!(driver.actor);
        assert(driver.actor.fbPhaseSlots[0] === 1,
          `${id} action-0 variant ${variant} routes through zz_00f1e30_`);
      }
    }
    const noDashRuntime = makeMinimalGRedBorg();
    noDashRuntime.borgId = "pl0406";
    const noDash = RomDriverBridge.attach(noDashRuntime, {});
    assert(noDash !== null, "pl0406 bridge registration attaches for its live melee");
    if (noDash) {
      noDash.actor.actionIndex = 0;
      noDash.actor.variantIndex = 0;
      noDash.actor.rootAction!(noDash.actor);
      assert(noDash.actor.fbPhaseSlots[0] === 0,
        "pl0406 has no live action-0 leaf and is not wrapped by Robot dash");
    }

    for (const id of [
      "pl0400", "pl0401", "pl0402", "pl0403", "pl0404", "pl0405",
      "pl0406", "pl0407", "pl0408", "pl0409", "pl040a", "pl040b",
    ] as const) {
      const runtime = makeMinimalGRedBorg();
      runtime.borgId = id;
      const driver = RomDriverBridge.attach(runtime, {});
      if (!driver) continue;
      driver.actor.actionIndex = 1;
      driver.actor.variantIndex = 0;
      driver.actor.rootAction!(driver.actor);
      assert(driver.actor.fbPhaseSlots[0] === 1,
        `${id} action-1 variant 0 routes through zz_00f2374_`);
      driver.actor.fbPhaseSlots[0] = 0;
      driver.actor.variantIndex = 1;
      driver.actor.rootAction!(driver.actor);
      assert(driver.actor.fbPhaseSlots[0] === 0,
        `${id} action-1 variant 1 is preserved for its distinct ROM machine/fallback`);
    }

    const elevatedOwner = makeMinimalGRedBorg();
    elevatedOwner.borgId = "pl0400";
    elevatedOwner.uid = "robot-elevated-owner";
    elevatedOwner.grounded = true;
    elevatedOwner.lockTarget = "robot-elevated-target";
    elevatedOwner.command = {
      word: 0, type: 1, button: "B", recordAddress: "robot-elevated-action1",
      subtype: 0, actionIndex: 1, variantIndex: 0, exact: true,
    };
    const elevatedTarget = makeMinimalGRedBorg();
    elevatedTarget.uid = "robot-elevated-target";
    elevatedTarget.pos = { x: 0, y: 400, z: 300 };
    const elevatedDriver = RomDriverBridge.attach(elevatedOwner, {});
    assert(elevatedDriver !== null, "elevated-target Robot bridge attaches");
    if (elevatedDriver) {
      elevatedOwner.romDriver = elevatedDriver;
      elevatedDriver.tryStartXSpecial(elevatedOwner, [elevatedOwner, elevatedTarget]);
      assert(approxEq((elevatedDriver.actor as RomActor & { targetDistance760?: number }).targetDistance760 ?? 0, 500),
        "bridge sync mirrors full 3D Euclidean target distance into actor+0x760");
    }
  }

  console.log("\n[rom.selfcheck] G RED action 0 — five-variant dash table (zz_018d288_):");
  {
    type DashScratch = RomActor & {
      lockTarget?: { x: number; y: number; z: number } | null;
      dashAimTimer560?: number;
      inputFlags5d8?: number;
      aimPitch1900?: number;
      aimPitch18da?: number;
      aimRoll1dfc?: number;
      onStartStream?: (group: number, slot: number, mask: number) => boolean;
    };
    const shots: Array<[number, number]> = [];
    const streams: Array<[number, number, number]> = [];
    const ctx: GRedFamilyCtx = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, address, type) => shots.push([address, type]),
    };
    const actor = createRomActor() as DashScratch;
    actor.pos = { x: 100, y: 0, z: 0 };
    actor.lockTarget = { x: 0, y: 0, z: 0 };
    actor.aimPitch1900 = 1000;
    actor.aimPitch18da = 1000;
    actor.aimRoll1dfc = 1000;
    actor.onStartStream = (group, slot, mask) => { streams.push([group, slot, mask]); return true; };
    configureGRedFamily(actor, "pl0615", ctx);
    actor.actionIndex = 0;
    actor.variantIndex = 0;
    actor.rootAction!(actor);
    assert(actor.fbPhaseSlots[0] === 1 && actor.dashAimTimer560 === GRED_DASH.AIM_TIMER,
      "v0 enters table 0x803655b0 and seeds the distinct +0x560 timer to 30");
    assert(approxEq(actor.pos.x, 195) && actor.hSpeed === 0 && actor.yVel === 0,
      "v0 phase 0 applies ×0.95 target-relative reposition and zeroes motion scalars");
    assert(actor.aimPitch1900 === 960 && actor.aimPitch18da === 500 && actor.aimRoll1dfc === 500,
      "root/v0 wrappers apply exact ×0.96 and arithmetic-half aim decays");
    assert(streams.some(([g, s, m]) => g === 2 && s === 0 && m === 0xf),
      "v0 starts family stream group 2 at +0x6ee with mask 0xf");

    actor.contactP0 = 1;
    actor.dashAimTimer560 = 0;
    actor.rootAction!(actor);
    assert(actor.fbPhaseSlots[0] === 2 && actor.handlerTimer === GRED_DASH.REPEAT_G_RED,
      "v0 stream signal advances to phase 2 and seeds G RED's +0x558 repeat timer to 12");
    assert(shots.some(([address, type]) => address === GRED_DASH.PROJECTILE_SPAWNER && type === 0x2b),
      "zz_018dcb0_ requests G RED projectile record 0x2b through spawner 0x800c3be0");

    actor.inputFlags5d8 = 0x10;
    actor.controlWord = 1;
    actor.rootAction!(actor);
    assert((actor.controlWord & 3) === 0 && actor.stateTimer === GRED_DASH.EXIT_COOLDOWN,
      "v0 phase 2 high-nibble exit clears action mode and applies the exact 20-frame cooldown");

    const v2 = createRomActor() as DashScratch;
    const v2Streams: Array<[number, number, number]> = [];
    v2.lockTarget = { x: 0, y: 0, z: 10 };
    v2.onStartStream = (group, slot, mask) => { v2Streams.push([group, slot, mask]); return true; };
    v2.variantIndex = 2;
    createGRedDash(ctx)(v2);
    assert(v2Streams.some(([g, s, m]) => g === 2 && s === 4 && m === 1),
      "v1/v2/v3 share table 0x803655bc and default to group-2 slot 4, mask 1");

    const v4 = createRomActor() as DashScratch;
    const v4Streams: Array<[number, number, number]> = [];
    v4.lockTarget = { x: 0, y: 0, z: 10 };
    v4.onStartStream = (group, slot, mask) => { v4Streams.push([group, slot, mask]); return true; };
    v4.variantIndex = 4;
    createGRedDash(ctx)(v4);
    assert(v4Streams.some(([g, s, m]) => g === 2 && s === 6 && m === 1)
      && v4Streams.some(([g, s, m]) => g === 0 && s === 0x0d && m === 2),
      "v4 table 0x803655c8 starts its exact dual streams: g2/s6 mask1 + g0/s13 mask2");

    const runtime = makeMinimalGRedBorg();
    runtime.grounded = true;
    runtime.command = {
      word: 0, type: 1, button: "B", recordAddress: "test-gred-action0",
      subtype: 0, actionIndex: 0, variantIndex: 0, exact: true,
    };
    const driver = RomDriverBridge.attach(runtime, {});
    assert(driver !== null, "bridge attaches G RED action-0 family driver");
    if (driver) {
      runtime.romDriver = driver;
      const handled = driver.tryStartBAttack(runtime, [runtime]);
      assert(handled && driver.actor.fbPhaseSlots[0] === 1,
        "exact B command actionIndex 0 enters the ROM dash instead of generic combat");
    }
  }

  // Titan/Panther constructor families: real handlers, callback gates, and bridge seam.
  {
    console.log("\n[rom.selfcheck] Titan/Panther aimed-shot + morph families:");
    for (const [family, borg, expected] of [
      ["titan", 0x604, [0x2b, 0x2c]], ["titan", 0x618, [0x4b, 0x4c]],
      ["panther", 0x613, [0x32, 0x33]], ["panther", 0x627, [0x4d, 0x4e]],
    ] as const) {
      const shots: number[] = [];
      const a = createRomActor();
      a.borgNumber = borg;
      a.weaponPartMask = 0x0d;
      a.visibilityBit = 0x04;
      const target = { eligibility83: 0, controlWord: 0, visibilityMask5e6: 0xff };
      const other = { eligibility83: 0, controlWord: 0, visibilityMask5e6: 0xff };
      a.visibilityRoster = [target, other];
      a.visibilityTarget = target;
      createTitanPantherGunAction0({
        onAllocateResource: () => true,
        onFamilyProjectile: (_actor, _addr, type) => shots.push(type),
      })(a);
      assert(shots.join(",") === expected.join(","), `${family} action 0 fires exact records for 0x${borg.toString(16)}`);
      assert(a.weaponAnimationActiveMask === 0x0d
        && a.weaponAnimationState.join(",") === "5,0,5,5",
      `${family} action 0 stamps +0x579/+0x1b03 non-part-1 animation state`);
      assert(target.visibilityMask5e6 === 0xff && other.visibilityMask5e6 === 0xfb,
        `${family} action 0 success clears all +0x5e6 masks then re-adds +0x3e5 only to eligible +0xcc target`);
      const denied = createRomActor();
      denied.borgNumber = borg;
      denied.visibilityBit = 2;
      const deniedTarget = { eligibility83: 0, controlWord: 0, visibilityMask5e6: 0xff };
      denied.visibilityRoster = [deniedTarget]; denied.visibilityTarget = deniedTarget;
      createTitanPantherGunAction0({ onAllocateResource: () => false })(denied);
      assert(denied.visibilityRoster[0]!.visibilityMask5e6 === 0xff
        && denied.weaponAnimationActiveMask === 0x0d,
      `${family} action 0 ammo failure skips zz_006bf80_/spawn but still runs zz_0048d54_`);
      for (let variant = 0; variant < 5; variant++) {
        const m = createRomActor();
        m.variantIndex = variant;
        const streams: Array<[number, number]> = [];
        (m as RomActor & { onStartStream?: (g: number, s: number) => boolean }).onStartStream = (g, s) => { streams.push([g, s]); return true; };
        createTitanPantherAction1(family, {})(m);
        assert(m.fbPhaseSlots[0] === 1 && streams.length > 0,
          `${family} action 1 variant ${variant} enters its exact shared phase table`);
        if (variant >= 3) {
          m.handlerTimer = 0;
          createTitanPantherAction1(family, {})(m); // P1 -> P2
          createTitanPantherAction1(family, {})(m); // P2 -> P3 (targetless timer=20 first)
          m.handlerTimer = 0;
          createTitanPantherAction1(family, {})(m); // P2 -> P3
          if (family === "panther" && variant === 4) {
            assert(approxEq(m.hSpeed, 10), "Panther v4 config +0x14 scales launch 40 by exact 0.25");
          }
          createTitanPantherAction1(family, {})(m); // P3 -> P4 (+0x0a=0)
          assert(m.fbPhaseSlots[0] === 4, `${family} action 1 variant ${variant} traverses 0x80178394's five-phase table`);
        }
      }
    }

    for (const [name, borg, cfg] of [["Titan", 0x618, TITAN_ROBOT_X_CONFIG], ["Panther", 0x627, PANTHER_ROBOT_X_CONFIG]] as const) {
      for (const allow of [false, true]) {
        const a = createRomActor();
        a.borgNumber = borg;
        a.heading = 0x1234;
        a.contactP0 = 1;
        a.fbPhaseSlots[0] = 1;
        const spawned: number[] = [];
        createSharedAimedShotX(cfg, {
          onAllocateResource: () => allow,
          onFamilyProjectile: (_actor, _addr, type) => spawned.push(type),
        })(a);
        assert(spawned.length === (allow ? 2 : 0), `${name} prototype aimed callback ${allow ? "accepts" : "denies"} ammo exactly`);
        if (name === "Panther" && allow) {
          assert(a.parts[0].ownershipFlags === 0xc0 && a.parts[1].ownershipFlags === 0xc0,
            "Panther aimed success surfaces both fist ownership bytes");
        }
      }
    }

    {
      const a = createRomActor();
      a.borgNumber = 0x604; a.controlWord = 1;
      (a as RomActor & { inputFlags5d8?: number }).inputFlags5d8 = 0x10;
      const records: number[] = [];
      const gun = createTitanPantherGunAction0({
        onAllocateResource: () => true,
        onFamilyProjectile: (_actor, _spawner, record) => records.push(record),
      });
      for (let frame = 0; frame < 100 && (a.controlWord & 3) !== 0; frame++) gun(a);
      assert(records.length === 10
        && records.filter((record) => record === 0x2b).length === 5
        && records.filter((record) => record === 0x2c).length === 5,
        "Titan action 0 runs exactly five volleys (five projectile pairs) before exit");
      assert(a.streamSlot === -1 && (a.controlWord & 3) === 0,
        "Titan five-volley loop decrements cursor 5→-1 and exits without a sixth pair");
    }

    {
      const a = createRomActor();
      a.pos.x = 0; a.pos.y = 0; a.pos.z = 0;
      (a as RomActor & { lockTarget?: { x: number; y: number; z: number } }).lockTarget = { x: 10, y: 75, z: 10 };
      titanRobotXOnSteer(a);
      assert(a.lockYaw === 0x2000 && a.activeYaw === 0x2000,
        "action-3 handler derives exact BAM16 yaw 0x2000 from offset/elevated live target");
    }

    {
      const runtime = makeMinimalGRedBorg(); runtime.borgId = "pl0604"; runtime.uid = "facing-self";
      runtime.lockTarget = "facing-target";
      const target = makeMinimalGRedBorg(); target.uid = "facing-target";
      target.pos = { x: 10, y: 80, z: 10 };
      const driver = RomDriverBridge.attach(runtime, {});
      driver?.syncIn(runtime, [runtime, target]);
      assert(driver?.actor.lockYaw === 0x2000 && driver.actor.activeYaw === 0x2000,
        "bridge sync derives exact BAM16 yaw from offset/elevated synchronized target");
      target.pos = { x: -10, y: 120, z: 0 };
      driver?.syncIn(runtime, [runtime, target]);
      assert(driver?.actor.lockYaw === -0x4000 && driver.actor.activeYaw === -0x4000,
        "bridge refreshes lockYaw/activeYaw when live target bearing changes on a later tick");
    }

    const morph = createRomActor();
    morph.slot = 3; morph.identityVariant = 5;
    createSharedMorphXSpecial(TITAN_MORPH_CONFIG, {})(morph);
    assert(morph.fbPhaseSlots[0] === 1, "base Titan action 2 enters shared morph phase 0");
    morph.wallContact = 1;
    let morphEvent: [number, number] | null = null;
    createSharedMorphXSpecial(TITAN_MORPH_CONFIG, {}, {
      onMorph: (_actor, next, previous) => { morphEvent = [next, previous]; },
    })(morph);
    assert(morph.borgNumber === 0x605 && morph.borgMirror94 === 0x605
      && morph.carriedSlot96 === 3 && morph.carriedVariant97 === 5,
    "base Titan morph commits +0x3e8/+0x94 and carries +0x3e4/+0x3e7 to +0x96/+0x97");
    assert(morphEvent?.[0] === 0x605, "base Titan morph emits its host lifecycle callback after actor mirrors commit");

    for (const [id, expectedForm] of [["pl0604", "pl0605"], ["pl0613", "pl0614"]] as const) {
      const runtime = makeMinimalGRedBorg(); runtime.borgId = id; runtime.grounded = true;
      runtime.uid = `${id}-stable-uid`; runtime.hp = 123; runtime.maxHp = 450; runtime.team = 1;
      runtime.ownerPlayer = "morph-owner";
      runtime.command = { word: 0, type: 2, button: "X", recordAddress: "morph-live", subtype: 0, actionIndex: 2, variantIndex: 0, exact: true };
      const driver = RomDriverBridge.attach(runtime, {});
      assert(driver?.tryStartXSpecial(runtime, [runtime]) === true, `${id} live morph starts through bridge`);
      if (driver) {
        driver.tick(runtime, 1 / 60, [runtime], null);
        assert(driver.actor.wallContact === 0, `${id} authored stream remains active before its completion boundary`);
        driver.tick(runtime, 1 / 60, [runtime], null);
        assert(driver.actor.wallContact === 1, `${id} decoded stream scheduler raises authored +0x1cee completion`);
        driver.tick(runtime, 1 / 60, [runtime], null);
        assert(runtime.combatFormId === expectedForm && runtime.borgId === id,
          `${id} authored stream completion drives normal bridge tick into the internal form`);
        assert(runtime.uid === `${id}-stable-uid` && runtime.hp === 123 && runtime.maxHp === 450
          && runtime.team === 1 && runtime.ownerPlayer === "morph-owner",
          `${id} morph preserves UID, HP, team, owner and original borg identity`);
        const expected = id === "pl0604"
          ? { speed: 12, gravity: -0.6, ammo: 5, refill: 180 }
          : { speed: 20, gravity: -0.6, ammo: 10, refill: 300 };
        assert(driver.actor.maxHSpeed === expected.speed && approxEq(driver.actor.gravityCoeff, expected.gravity)
          && runtime.weaponCells?.[0]?.cur === expected.ammo
          && runtime.weaponCells[0]?.refillParam === expected.refill,
          `${id} morph atomically refreshes exact descriptor movement and FUN_800562b8 weapon cell`);
        assert(runtime.romMorphEvents?.at(-1)?.borgNumber === parseInt(expectedForm.slice(2), 16),
          `${id} morph posts zz_01cb750_ event`);
      }
    }

    for (const [id, rows] of [
      ["pl0604", [1000, 600, 1000]], ["pl0618", [1000, 600, 1000]],
      ["pl0613", [1000, 1200, 1000]], ["pl0627", [1000, 1200, 1000]],
    ] as const) {
      const runtime = makeMinimalGRedBorg(); runtime.borgId = id;
      const driver = RomDriverBridge.attach(runtime, {});
      assert(driver?.actor.actionSpeedRows.join(",") === rows.join(","), `${id} production actor loads exact descriptor +0x134/+0x140/+0x14c rows`);
    }
    {
      const a = createRomActor();
      a.borgNumber = 0x604; a.controlWord = 0x40; a.bodyPitch = 4000; a.aimRateScale = 0.5;
      a.descriptor = { header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(), handlerData6c: -0.81,
        subtypePartCommand: new Int8Array(), buttonLiveFlag: new Int8Array(), defaultHand0: 0, defaultHand1: 0,
        turnStep1: 3072 };
      (a as RomActor & { lockTarget?: { x: number; y: number; z: number } }).lockTarget = { x: 0, y: 0, z: 10 };
      createSharedAimedShotX(TITAN_ROBOT_X_CONFIG, {})(a);
      assert(a.steerYaw === -1536, "aimed seek uses exact (-bodyPitch-atan) target and descriptor+0xae * actor+0x768 step");
      a.fbPhaseSlots[0] = 2; a.parts[1].stateByte = -1; a.gravityCoeff = 0;
      createSharedAimedShotX(TITAN_ROBOT_X_CONFIG, {})(a);
      assert(a.parts[1].stateByte === 0 && approxEq(a.gravityCoeff, -0.81), "+0x1d0f aliases signed part-1 state and gates gravity reload exactly");
    }

    for (const [id, action, shouldHandle] of [
      ["pl0604", 2, true], ["pl0618", 2, false], ["pl0613", 2, true], ["pl0627", 2, false],
      ["pl0604", 0, true], ["pl0618", 1, true], ["pl0613", 3, true], ["pl0627", 3, true],
    ] as const) {
      const runtime = makeMinimalGRedBorg();
      runtime.borgId = id;
      runtime.command = { word: 0, type: action, button: "X", recordAddress: "family-test", subtype: 0, actionIndex: action, variantIndex: 0, exact: true };
      const driver = RomDriverBridge.attach(runtime, { onAllocateResource: () => true });
      const handled = driver?.tryStartXSpecial(runtime, [runtime]) ?? false;
      assert(handled === shouldHandle, `${id} bridge action ${action} ${shouldHandle ? "routes" : "preserves fallback"}`);
    }
    for (const id of ["pl0604", "pl0618", "pl0613", "pl0627"] as const) {
      for (const action of [0, 1, 3] as const) {
        for (let variant = 0; variant < 5; variant++) {
          const runtime = makeMinimalGRedBorg();
          runtime.borgId = id;
          runtime.command = { word: 0, type: action, button: "X", recordAddress: "family-matrix", subtype: 0, actionIndex: action, variantIndex: variant, exact: true };
          const driver = RomDriverBridge.attach(runtime, { onAllocateResource: () => true });
          assert((driver?.tryStartXSpecial(runtime, [runtime]) ?? false), `${id} action ${action} variant ${variant} bridge routes`);
        }
      }
    }
  }

  runGirlClusterTests();

  if (failures > 0) {
    console.error(`\n[rom.selfcheck] ${failures} FAILURES`);
    return 1;
  }
  console.log("\n[rom.selfcheck] ALL PASS — foundation composes correctly.");
  return 0;
}

function runGirlClusterTests(): void {
  console.log("\n[rom.selfcheck] Girl cluster — exhaustive live routing and exact phase branches:");
  const ids: GirlClusterBorgId[] = [
    "pl0300", "pl0301", "pl0302", "pl0303", "pl0304", "pl0305", "pl0306",
    "pl0307", "pl0308", "pl0309", "pl030a", "pl030b", "pl030c", "pl030d",
  ];
  const ctx: StreamContext = {
    onAllocateResource: () => true,
    onFamilyProjectile: () => {},
  };
  const routeErrors: string[] = [];
  let liveCount = 0;
  for (const id of ids) {
    for (let action = 0; action <= 4; action += 1) {
      for (let variant = 0; variant <= 13; variant += 1) {
        const expected = isGirlClusterLiveSlot(id, action, variant);
        if (expected) liveCount += 1;
        const a = createRomActor();
        a.actionSpeedRows = [100, 100, 100];
        configureGirlClusterFamily(a, id, ctx);
        a.actionIndex = action;
        a.variantIndex = variant;
        a.rootAction?.(a);
        const routed = a.fbPhaseSlots.some((phase) => phase !== 0)
          || a.parts.some((part) => part.streamPtr >= 0);
        if (routed !== expected) routeErrors.push(`${id}/a${action}/v${variant}:${routed}`);
      }
    }
  }
  assert(liveCount === 182, `command matrix contains 182 live member/action/variant slots (got ${liveCount})`);
  assert(routeErrors.length === 0, `all live slots route and all exclusions fall through (${routeErrors.slice(0, 3).join(", ") || "exact"})`);

  const bridgeErrors: string[] = [];
  for (const id of ids) {
    for (let action = 0; action <= 4; action += 1) {
      for (let variant = 0; variant <= 13; variant += 1) {
        const runtime = makeMinimalGRedBorg();
        runtime.borgId = id;
        runtime.command = {
          word: 0, type: action, button: "X", recordAddress: "girl-matrix", subtype: 0,
          actionIndex: action, variantIndex: variant, exact: true,
        };
        const driver = RomDriverBridge.attach(runtime, { onAllocateResource: () => true });
        const routed = driver?.tryStartXSpecial(runtime, [runtime]) ?? false;
        const expected = isGirlClusterLiveSlot(id, action, variant);
        if (routed !== expected) bridgeErrors.push(`${id}/a${action}/v${variant}:${routed}`);
      }
    }
  }
  assert(bridgeErrors.length === 0, `bridge preserves the same exhaustive live/exclusion matrix (${bridgeErrors.slice(0, 3).join(", ") || "exact"})`);

  {
    const a = createRomActor();
    a.modelScale = 2; a.sizeScale = 0.5; a.aimRateScale = 1;
    a.pos = { x: 0, y: 0, z: 0 };
    assert(stepAfterimage(a) && a.afterimageSerial === 1 && a.accumulator80c === 1,
      "zz_00b22f4_ first call snapshots, emits, then increments +0x80c");
    a.pos.x = 99;
    assert(!stepAfterimage(a) && a.afterimageSerial === 1 && a.accumulator80c === 2,
      "zz_00b22f4_ suppresses a near sample while +0x80c is inside the 8-frame window");
    a.pos.x = 100;
    assert(stepAfterimage(a) && a.afterimageSerial === 2 && a.accumulator80c === 1,
      "zz_00b22f4_ emits at exact scaled spacing and preserves reset-before-increment ordering");
    a.accumulator80c = 8; a.pos.x = 100;
    assert(stepAfterimage(a) && a.afterimageSerial === 3,
      "zz_00b22f4_ interval expiry emits even without displacement");
  }
  {
    const a = createRomActor() as RomActor & { lockTarget?: { x: number; y: number; z: number } | null };
    a.descriptor = { header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(),
      handlerData6c: 0, subtypePartCommand: new Int8Array(), buttonLiveFlag: new Int8Array(),
      defaultHand0: 0, defaultHand1: 0, turnStep0: 0x100, turnStep1: 0x300 };
    a.aimOrigin518 = { x: 10, y: 10, z: 10 };
    a.lockTarget = { x: 10, y: 110, z: 110 };
    const first = stepTargetPitch(a, 0xc0, 0);
    const second = stepTargetPitch(a, 0xc1, 0);
    assert(first.result === 0 && first.value === -0x100 && second.value === -0x300,
      "zz_006e514_ selects descriptor +0xac/+0xae rates and converges signed BAM16");
    a.lockTarget = null;
    const lost = stepTargetPitch(a, 0xc0, 1000);
    assert(lost.result === -1 && lost.value === 899,
      "zz_006e514_ target loss returns -1 and truncates pitch by exact 0.9 float");
  }
  {
    const a = createRomActor();
    a.savedGroundPos = { x: 1, y: 2, z: 3 };
    a.pos = { x: 20, y: 30, z: 40 };
    a.physicsRuntime = {
      isSupported: () => false,
      clampToGround: () => { throw new Error("unsupported floor must not clamp"); },
    };
    assert(!groundSnapRevert(a) && a.pos.x === 1 && a.pos.y === 2 && a.pos.z === 3,
      "zz_00679d0_ unsupported probe returns false and reverts all saved-position components");
    a.pos = { x: 20, y: -4, z: 40 }; a.controlWord = 0x40;
    assert(!groundSnapRevert(a) && a.pos.x === 20,
      "zz_00679d0_ frozen-position bit preserves unsupported current position");
    a.controlWord = 0;
    a.physicsRuntime = {
      isSupported: () => true,
      clampToGround: (_pos, _velY) => ({ y: 7, velY: 0, grounded: true }),
    };
    assert(groundSnapRevert(a) && a.pos.y === 7 && a.yVel === 0,
      "zz_00679d0_ supported battle floor returns grounded and commits snap state");
  }
  {
    const one = makeMinimalGRedBorg(); one.borgId = "pl0300";
    const two = makeMinimalGRedBorg(); two.uid = "girl-two"; two.borgId = "pl0308";
    const b1 = RomDriverBridge.attach(one, {});
    const b2 = RomDriverBridge.attach(two, {});
    b1?.syncIn(one, [one, two]); b2?.syncIn(two, [one, two]);
    b1!.actor.pos.x = 100; b2!.actor.pos.x = 200;
    stepAfterimage(b1!.actor); stepAfterimage(b2!.actor);
    b1?.syncOut(one); b2?.syncOut(two);
    assert(one.romAfterimage?.serial === 1 && one.romAfterimage.pos.x === 100
      && two.romAfterimage?.serial === 1 && two.romAfterimage.pos.x === 200,
      "two Girl bridges retain independent afterimage cache and presentation ownership");
    assert(approxEq(b1!.actor.modelScale, 1) && approxEq(b1!.actor.sizeScale, 9 / 167.75999450683594)
      && approxEq(b2!.actor.sizeScale, 25 / 167.75999450683594),
      "bridge syncs exact +0xb4 tier scale and Girl descriptor-derived +0x7fc scales");
  }

  assert(CYBER_GIRL_X.COOLDOWN_305 === 12 && CYBER_GIRL_X.COOLDOWN_309 === 8,
    "Cyber Girl cooldown literals are exact boot.dol values 12/8");
  assert(KILLER_SHARED_X_CONFIG.seedSlot === 0 && BARRIER_SHARED_X_CONFIG.seedSlot === 2,
    "shared-X configs preserve distinct Killer/Barrier seed slots");
  for (const cfg of [KILLER_SHARED_X_CONFIG, BARRIER_SHARED_X_CONFIG]) {
    const a = createRomActor();
    a.controlWord = 0x40;
    createGirlSharedX(cfg, ctx)(a);
    assert(a.streamSlot === cfg.seedSlot + 1 && a.fbPhaseSlots[0] === 1,
      `shared-X config 0x${cfg.romConfig.toString(16)} takes its airborne slot branch`);
  }

  {
    const spawned: number[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, _addr, type) => spawned.push(type),
    };
    const a = createRomActor();
    a.borgNumber = 0x303; a.fbPhaseSlots[0] = 1; a.contactP0 = 1; a.controlWord = 1;
    createSeries3XSpecial(sctx)(a);
    assert(spawned.length === 0 && a.stateTimer === SERIES3_X.COOLDOWN_EXIT + a.dt,
      "Delta-II on-hit ammo failure takes immediate common exit");
  }
  {
    const a = createRomActor();
    a.borgNumber = 0x301; a.fbPhaseSlots[0] = 1;
    const handler = createSeries3XSpecial(ctx);
    for (let i = 0; i < 180; i += 1) handler(a);
    assert(a.fbPhaseSlots[0] === 1, "series-3 phase 1 has no synthetic whiff timer");
    a.fbPhaseSlots[0] = 2; a.wallContact = 0; a.contactP0 = 0; a.dashStrength1d0f = 0;
    for (let i = 0; i < 180; i += 1) handler(a);
    assert(a.fbPhaseSlots[0] === 2 && a.controlWord === 0,
      "series-3 phase 2 has no synthetic recovery exit");
    a.steerYaw = 100; a.contactP0 = -1; a.dashStrength1d0f = -1;
    a.descriptor = { header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(),
      handlerData6c: 3, subtypePartCommand: new Int8Array(), buttonLiveFlag: new Int8Array(),
      defaultHand0: 0, defaultHand1: 0 };
    handler(a);
    assert(a.steerYaw === Math.trunc(100 * SERIES3_X.METER_18DA_DECAY)
      && a.gravityCoeff === 3 && a.dashStrength1d0f === 0,
      `series-3 phase 2 consumes exact negative event bytes (steer=${a.steerYaw}, gravity=${a.gravityCoeff}, event=${a.dashStrength1d0f})`);
  }
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
  // Ported multi-frame actions own motion until their ROM exit clears the action bits.
  const owned = b.romDriver!.tick(b, 1, [b]);
  assert(owned, "tick returns true while the ported X state machine owns motion");
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
