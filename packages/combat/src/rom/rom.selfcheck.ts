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
import { configureNinjaFamily, NINJA_X } from "../families/ninja.js";
import { configureStarHeroFamily } from "../families/star-hero.js";
import { configureCyberMachineFamily } from "../families/cyber-machine.js";
import { configureSwordKnightFamily } from "../families/sword-knight.js";
import { configureDragonFamily, DRAGON_X } from "../families/dragon.js";
import { configureWormFamily, WORM_X } from "../families/worm.js";
import { createSharedMeleeLunge, NINJA_LUNGE_CONFIG } from "../families/shared-melee-lunge.js";
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
  // (ctor 0x801223c0, cue table @0x8032d4d8). SHARED registration: the X-special
  // routes through zz_0149708_ (shared group-4 engine, phaseTable 0x8033ed3c); no
  // bespoke family module. Verify each member attaches, gets the family cue table,
  // and resolves rootAction via the shared-engine config.
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
        assert(bridge.actor.rootAction !== null, `${id}: shared-engine rootAction configured`);
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
