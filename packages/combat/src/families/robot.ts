// BUILD ROBOT family (ctor 0x80112b44) — bespoke X-special port.
// Covers the three borgs sharing this ctor:
//   pl0402 BUILD ROBOT   (0x402)
//   pl0407 MEGATON ROBOT (0x407)
//   pl0408 ARMY ROBOT    (0x408)
// Source:
//   research/decomp/ghidra-export/chunk_0031.c:1245 (engine FUN_801132f8 —
//   PTR_FUN_80327f98[+0x540] phase dispatch)
//   chunk_0031.c:1258 (phase 0 FUN_80113334 — setup + blink-reposition + stream start)
//   chunk_0031.c:1294 (phase 1 FUN_8011340c — tick + contact-gated child deploy +
//   physics + ground transition)
//   chunk_0031.c:1356 (phase 2 FUN_8011359c — tick + physics + timer/ground exit)
//   chunk_0031.c:1497 (family child-deploy spawner zz_01138c0_ — pl0402/pl0408 path)
//   chunk_0053.c:2818 (MEGATON spawner FUN_801b8b6c — pl0407 path)
//
// The X-special is a 3-phase "dive-bomb deploy": the borg blinks away from its lock
// target (phase 0), dives forward ticking its group-4 stream (phase 1); on the
// stream's part-0 contact byte (+0x1cef) going positive it deducts 1 ammo from slot 2
// and spawns a borg-switched child (the "build"/"deploy"), then continues the dive.
// On grounding it advances to recovery (phase 2); recovery ticks until a second
// grounding or the active-window timer (+0x558, seeded 120.0) expires.
//
// Borg-switched spawn (FUN_8011340c:1306-1326, gated on +0x1cef > 0 + ammo):
//   0x402 (BUILD ROBOT):  zz_01138c0_(actor, 0, 0) — child deploy type 0
//   0x407 (MEGATON ROBOT): +0x150 one-shot latch → FUN_801b8b6c(actor, 0) — heavy deploy
//   0x408 (ARMY ROBOT):   zz_01138c0_(actor, 1, 1) — child deploy type 1
// zz_01138c0_ allocates a child entity (zz_0088aa0_(actor, 3, 0x20, 0, 1)), wires its
// callbacks to FUN_80113a04 + FUN_80114340, and copies the parent's transform/stats —
// the spawned construct then runs its own AI. The host hook decides whether the child
// actually spawns (ammo/team/budget live in BorgRuntime); without the hook the spawn
// is an honest no-op (the phase still advances, matching the ROM's unconditional
// +0x540++ on the contact transition).
//
// Float constants read from boot.dol this session (dumped via the DOL-section helper
// documented in scripts/gen-camera-mode1-constants.mjs):
//   FLOAT_804396e0 = 0.0    (scalar zero / timer floor)
//   FLOAT_804396e4 = 4.0    (cooldown seed — `+0x694 = 4 + dt` on recovery exit)
//   FLOAT_804396f8 = 0.95   (blink-reposition scale — motion ×= 0.95 each phase)
//   FLOAT_804396fc = -1.0   (stream playback rate)
//   FLOAT_80439700 = 1.0    (physics integrator gravity param)
//   FLOAT_80439704 = 120.0  (phase-1 → phase-2 active-window timer seed)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Motion constants — every value DERIVED from boot.dol this session. */
export const ROBOT_X = {
  /** FLOAT_804396e0 = 0.0 — scalar zero (velocity reset) + timer floor. */
  ZERO: 0.0,
  /** FLOAT_804396e4 = 4.0 — post-recovery cooldown seeded into +0x694 (= 4 + dt).
   *  Read at chunk_0031.c:1382 (`+0x694 = FLOAT_804396e4 + +0x1dc8`). */
  COOLDOWN: 4.0,
  /** FLOAT_804396f8 = 0.95 — blink-reposition scale (motion ×= 0.95; pos += motion).
   *  Same shape as G RED's G Crash + the shared X-special windup. */
  REPOSITION_SCALE: 0.95,
  /** FLOAT_804396fc = -1.0 — group-4 stream playback rate (zz_004beb8_ param_1). */
  STREAM_RATE: -1.0,
  /** FLOAT_80439700 = 1.0 — physics integrator gravity param (FUN_80067310 param_1). */
  GRAVITY: 1.0,
  /** FLOAT_80439704 = 120.0 — phase-1 active-window timer seed (+0x558). Counts down
   *  in phase 2 when airborne; expiry exits the special via zz_006a5a4_. */
  ACTIVE_WINDOW: 120.0,
  /** zz_006dbe0_(actor, slot, cost, mode) — ammo deduct. Slot 2 is the family's
   *  X-special ammo bucket; cost is 1 per deploy. The host (bridge) owns the real
   *  ammo count; the hook decides whether the spawn fires. */
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  /** Sound cue played on ammo-empty contact (zz_00f036c_(actor, 0x24)). Routed via
   *  onPlayCue so the host's voice/sound layer can surface the "empty click". */
  EMPTY_CUE: 0x24,
  /** Action-mode bits 0..1 of +0x5e0 (cyber-machine/worm shape: recovery clears to exit). */
  ACTION_MODE_BITS: 0x3,
  /** zz_01138c0_ @0x801138c8 — family child-deploy spawner (chunk_0031.c:1497).
   *  Allocates a construct child via zz_0088aa0_(actor, 3, 0x20, 0, 1), wires its
   *  callbacks (FUN_80113a04 + FUN_80114340), copies the parent transform. Borg switch:
   *  0x402→(0,0), 0x408→(1,1). (param_2/param_3 = record-select + deploy mode.) */
  CHILD_DEPLOY_SPAWNER_ADDR: 0x801138c0,
  /** FUN_801b8b6c @0x801b8b6c — MEGATON ROBOT heavy-deploy spawner (chunk_0053.c:2818).
   *  pl0407 routes here through a +0x150 one-shot latch (FUN_8011340c:1318-1321):
   *  the latch ensures only ONE heavy deploy per X-special entry, even on repeated
   *  contact frames. Type 0 (matches the (actor, 0) call site). */
  MEGATON_DEPLOY_SPAWNER_ADDR: 0x801b8b6c,
  /** +0x150 one-shot latch value the MEGATON path sets on first contact (FUN_8011340c:1319).
   *  Stored on the actor as `robotDeployLatch` so subsequent contact frames skip the
   *  spawn (the ROM reads +0x150 == 0 to permit, then writes 1). */
  MEGATON_LATCH_FIELD: "robotDeployLatch",
} as const;

/** Borg-id → spawner routing (FUN_8011340c:1313-1325 borgNumber switch). Returns the
 *  spawner address + type the host hook resolves the record with. */
function spawnForBorg(borgNumber: number): { addr: number; type: number } {
  switch (borgNumber) {
    case 0x402: return { addr: ROBOT_X.CHILD_DEPLOY_SPAWNER_ADDR, type: 0 };
    case 0x407: return { addr: ROBOT_X.MEGATON_DEPLOY_SPAWNER_ADDR, type: 0 };
    case 0x408: return { addr: ROBOT_X.CHILD_DEPLOY_SPAWNER_ADDR, type: 1 };
    default: return { addr: ROBOT_X.CHILD_DEPLOY_SPAWNER_ADDR, type: 0 };
  }
}

/** The lock-target position the phase handlers read at actor+0x5e8 (bridge-synced). */
function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  return t ?? null;
}

/** Airborne test — the ROM reads +0x5e0 & 0x40 (position-frozen/air control bit). The
 *  bridge mirrors BorgRuntime.grounded onto the actor; prefer that live value. */
function isAirborne(actor: RomActor): boolean {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

export interface RobotFamilyCtx extends StreamContext {}

// ============================================================================
// Phase 0 — FUN_80113334 @ chunk_0031.c:1258. Setup + blink-reposition + stream start.
// ============================================================================
function robotXPhase0(actor: RomActor, _ctx: RobotFamilyCtx): void {
  // +0x540++ (chunk_0031.c:1266) — enter phase 1 for the next frame.
  actor.fbPhaseSlots[0] = 1;

  // Zero the velocity scalars +0x44/+0x48/+0x4c/+0x50 = FLOAT_804396e0 (chunk_0031.c:1267-
  // 1270). The dive starts from standstill; gravity/hSpeed are re-seeded by phase 1/2's
  // integrator. Also clear the +0x150 deploy latch so the MEGATON path can fire once
  // on the new contact.
  actor.hSpeed = ROBOT_X.ZERO;
  actor.yVel = ROBOT_X.ZERO;
  actor.hDecel = ROBOT_X.ZERO;
  actor.gravityCoeff = ROBOT_X.ZERO;
  (actor as RomActor & { [ROBOT_X.MEGATON_LATCH_FIELD]?: number })[ROBOT_X.MEGATON_LATCH_FIELD] = 0;

  // Blink-reposition: motion = pos − lockTargetPos; motion ×= 0.95; pos += motion —
  // the signature "blink away to double distance" windup (identical shape to G Crash
  // and the shared X-special). chunk_0031.c:1274-1277 via gnt4_PSVECSubtract/Scale/Add.
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(ROBOT_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // zz_00677b0_(actor) — ground/wall collide runs in the ROM right after the reposition;
  // the bridge applies the host's bounds clamp + off-mesh revert in tryStartXSpecial,
  // so the wall/walk collision itself is the host's responsibility (skipped here).

  // Stream slot select (chunk_0031.c:1279-1285): +0x6ea = 0 grounded / 1 airborne
  // (+0x5e0 & 0x40); the cursor then ++'s for the combo follow-up convention.
  const slot = isAirborne(actor) ? 1 : 0;
  actor.streamSlot = slot + 1; // combo cursor ++ (the ROM's cVar1 + 1 shape)
  // zz_004beb8_(rate −1.0, actor, mask 0xf, group 4, slot, −1, −1) — startStream.
  startStream(actor, 0xf, 4, slot, ROBOT_X.STREAM_RATE);
}

// ============================================================================
// Phase 1 — FUN_8011340c @ chunk_0031.c:1294. Tick + contact deploy + physics +
// ground transition.
// ============================================================================
function robotXPhase1(actor: RomActor, ctx: RobotFamilyCtx): void {
  // zz_004cd24_(actor, 0xf) — advance the group-4 stream (anim + hitbox + contact flags).
  tickStream(actor, 0xf, ctx);

  // MEGATON ROBOT (0x407) turns toward lock target each active frame (zz_006d144_ with
  // mode 0xc0). The bridge pre-computes lockYaw from the live target; face it here so
  // the dive tracks the lock.
  if (actor.borgNumber === 0x407) {
    actor.activeYaw = actor.lockYaw;
  }

  // CONTACT TRANSITION: part-0 contact byte +0x1cef went positive → deduct ammo +
  // spawn the borg-routed child (chunk_0031.c:1306-1328).
  if (actor.contactP0 > 0) {
    // Clear the contact byte (chunk_0031.c:1307) — one spawn per contact rise.
    actor.contactP0 = 0;

    // zz_006dbe0_(actor, 2, 1, 1) — attempt the ammo deduct. The host gate decides
    // whether the child actually spawns; without the hook the spawn is skipped (the
    // phase still advances, matching the ROM's unconditional +0x540++ on grounding
    // below — the ammo gate only controls the child, NOT the phase transition).
    // On ammo-empty: zz_00f036c_(actor, 0x24) — play the "empty click" voice cue.
    // On success: borg-switched spawn (chunk_0031.c:1313-1326).
    const { addr, type } = spawnForBorg(actor.borgNumber);
    // MEGATON one-shot latch: only fire on the first contact of this X entry. The ROM
    // gates with `if (+0x150 == 0) { +0x150 = 1; FUN_801b8b6c(actor, 0); }`.
    const latchActor = actor as RomActor & { [ROBOT_X.MEGATON_LATCH_FIELD]?: number };
    if (actor.borgNumber === 0x407) {
      if ((latchActor[ROBOT_X.MEGATON_LATCH_FIELD] ?? 0) === 0) {
        latchActor[ROBOT_X.MEGATON_LATCH_FIELD] = 1;
        ctx.onFamilyProjectile?.(actor, addr, type);
      }
    } else {
      // pl0402/pl0408 — spawn every contact (no latch; the construct-record table
      // itself rate-limits via ammo).
      ctx.onFamilyProjectile?.(actor, addr, type);
    }

    // +0x50 = descriptor[+0x6c] (chunk_0031.c:1327) — re-seed the gravityCoeff from
    // the per-borg data page. The host owns the real value via BorgRuntime; skipped.
  }

  // FUN_80067310_(gravity 1.0, actor, +0x5ae) — integrate physics (chunk_0031.c:1329).
  integratePhysics(ROBOT_X.GRAVITY, actor, actor.lockYaw);

  // Reposition continuation (chunk_0031.c:1330-1331): motion ×= 0.95; pos += motion
  // (decaying slide-away — same shape as phase 0 + the shared X-special).
  vecScale(ROBOT_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // Ground/wall contact check (chunk_0031.c:1332-1348). +0x1cee is the wall/ground
  // contact flag; zz_00677b0_ returns 0 when airborne (no ground under the borg).
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded === true;
  if (actor.wallContact !== 0 || grounded) {
    if (!grounded) {
      // Airborne with wall contact: advance to phase 2 + seed the active-window timer
      // (chunk_0031.c:1337-1339). +0x558 = FLOAT_80439704 (120.0).
      actor.fbPhaseSlots[0] = 2;
      actor.handlerTimer = ROBOT_X.ACTIVE_WINDOW;
    } else {
      // Grounded on contact: clear the housekeeping flag + action-mode bits and exit
      // (chunk_0031.c:1342-1346). zz_006a474_ is the ROM's ground-idle reset; the
      // cue dispatch below mirrors its full-body idle reset (cue 0).
      actor.controlWord = actor.controlWord & ~ROBOT_X.ACTION_MODE_BITS;
      dispatchUpperBodyCue(actor, 7);
      dispatchFullBodyCue(actor, 0);
    }
  }
}

// ============================================================================
// Phase 2 — FUN_8011359c @ chunk_0031.c:1356. Recovery (tick + physics + timer/ground
// exit).
// ============================================================================
function robotXPhase2(actor: RomActor, ctx: RobotFamilyCtx): void {
  // zz_004cd24_(actor, 0xf) — keep ticking the recovery tail of the group-4 stream.
  tickStream(actor, 0xf, ctx);

  // FUN_80067310_(gravity 1.0, actor, +0x5ae) — integrate physics (chunk_0031.c:1364).
  integratePhysics(ROBOT_X.GRAVITY, actor, actor.lockYaw);

  // Reposition continuation (chunk_0031.c:1365-1366).
  vecScale(ROBOT_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // Exit check (chunk_0031.c:1367-1384). zz_00677b0_ returns 0 when still airborne.
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded === true;
  if (!grounded) {
    // Airborne: count down the active-window timer (chunk_0031.c:1370-1376).
    // +0x558 -= dt; on <= 0.0 exit via zz_006a5a4_ (air-fall completion).
    actor.handlerTimer -= actor.dt;
    if (actor.handlerTimer <= ROBOT_X.ZERO) {
      actor.controlWord = actor.controlWord & ~ROBOT_X.ACTION_MODE_BITS;
      // zz_006a5a4_ — air-fall exit (no cue change; the bridge's completion path
      // transitions the actor out of attack state 61).
    }
  } else {
    // Grounded: clear bits, upper-body cue 7, ground-idle reset (zz_006a750_(actor, 7)
    // + zz_006a474_ shape), and seed the post-special cooldown +0x694 = 4.0 + dt
    // (chunk_0031.c:1379-1382).
    actor.controlWord = actor.controlWord & ~ROBOT_X.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7);
    dispatchFullBodyCue(actor, 0);
    actor.stateTimer = ROBOT_X.COOLDOWN + actor.dt;
  }
}

/** The X-special phase table — indexed by actor.fbPhaseSlots[0]. Mirrors
 *  PTR_FUN_80327f98 = [FUN_80113334, FUN_8011340c, FUN_8011359c]. */
const X_PHASE_TABLE = [robotXPhase0, robotXPhase1, robotXPhase2];

/** FUN_801132f8 wrapper — dispatches the phase table (chunk_0031.c:1250). */
function robotXHandler(actor: RomActor, ctx: RobotFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_80112e90 @ chunk_0031.c:1023 (the descriptor
// +0x4b4 virtual) → PTR_FUN_80327f38[actor+0x580]. Action 2 (X) is ported here; the
// other rows wire in as their handlers port. Null entries fall through to the generic
// @gf/combat layer.
// ============================================================================

export function createRobotRootAction(
  ctx: RobotFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                // 0: dash attack (FUN_80112ecc → zz_00f1e30_) — TODO port
    null,                                // 1: B-tap melee (FUN_80113128 → PTR_FUN_80327f70) — TODO port
    (actor) => robotXHandler(actor, ctx), // 2: X-special (FUN_801132f8 dive-bomb deploy)
    null,                                // 3: B charge — TODO identify
    null,                                // 4: — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned BUILD ROBOT-family actor (pl0402/pl0407/pl0408).
 *  Stamps the borg-number switch the spawner routing reads and wires the root action
 *  dispatcher. */
export function configureRobotFamily(
  actor: RomActor,
  borgId: "pl0402" | "pl0407" | "pl0408",
  ctx: RobotFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0402" ? 0x402 :
    borgId === "pl0407" ? 0x407 : 0x408;
  actor.rootAction = createRobotRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
