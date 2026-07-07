// CYBER MACHINE family (ctor 0x800cc454) — the fourth ROM-faithful family port.
// Covers the four "beast-god" borgs sharing this ctor:
//   pl0602 CYBER MACHINE SEIRYU  (0x602 — Azure Dragon)
//   pl060a CYBER MACHINE SUZAKU  (0x60a — Vermilion Bird)
//   pl060c CYBER MACHINE BYAKKO  (0x60c — White Tiger)
//   pl060e CYBER MACHINE GENBU   (0x60e — Black Tortoise)
// Source:
//   research/decomp/ghidra-export/chunk_0021.c:2150 (root dispatcher FUN_800cc798)
//   chunk_0021.c:3335 (X-special / air-B handler FUN_800ce5dc — action-index 2 leaf)
//   chunk_0009.c:801 (zz_006a668_ shot dispatcher) + chunk_0043.c:4248 (zz_016cc24_
//   effect-child spawner).
//
// The X-special is a SHOT-ONLY action (actionStreamTables.json marks all 5 variants
// "no stream call reached (code-driven or shot-only action)"). It is a 2-phase ammo-
// gated projectile deploy:
//   phase 0 (FUN_800ce5dc, +0x540==0 branch): deduct 1 ammo from slot 2
//     (zz_006dbe0_(actor, 2, 1, 1)); on success spawn the visual effect child via
//     zz_016cc24_(actor, 2). Advance +0x540 to 1.
//   phase 1 (else branch): clear +0x73f, clear the action-mode bits (+0x5e0 &= ~3),
//     fire the shot via zz_006a668_(actor, kind=1, variant), then seed the post-shot
//     cooldown +0x694 = FLOAT_804389a8 + dt. After the bits clear, the actor exits the
//     attack state — phase 1 runs exactly once per X press.
//
// The actual damage is delivered by the kind-1 shot fired through the host's projectile
// layer (zz_006a668_ → zz_0048d54_ → zz_004a754_ armed-channel loop). With the host
// hook unwired, the spawn is an honest no-op (the phase machine still advances).

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

const CM_X = {
  COOLDOWN: 50.0,
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  EFFECT_SPAWNER_ADDR: 0x8016cc24,
  EFFECT_TYPE: 2,
  SHOT_SPAWNER_ADDR: 0x8006a668,
  SHOT_KIND: 1,
  ACTION_MODE_BITS: 0x3,
  /** FLOAT_80438938 = 0.0 — zero constant. */
  ZERO: 0.0,
  /** FLOAT_80438940 = 0.5 — stream playback rate. */
  STREAM_RATE: 0.5,
  /** FLOAT_80438944 = 6.0 — dash timer seed (phase 0 arm). */
  DASH_TIMER: 6.0,
  /** FLOAT_80438948 = 0.08 — velocity projection scale. */
  VEL_SCALE: 0.08,
  /** FLOAT_8043894c = 0.01 — velocity magnitude gate. */
  VEL_GATE: 0.01,
  /** FLOAT_80438950 = 1.0 — gravity multiplier. */
  GRAVITY: 1.0,
  /** FLOAT_80438954 = 3.0 — phase-1 transition timer seed. */
  TRANS_TIMER: 3.0,
  /** FLOAT_80438958 = 8.0 — handlerTimer seed (zz_00cd18c_). */
  HANDLER_TIMER: 8.0,
  /** FLOAT_80438970 = 4.0 — B-melee timer seed (phase 0). */
  MELEE_TIMER: 4.0,
  /** FLOAT_80438974 = 20.0 — B-melee contact distance gate. */
  MELEE_DIST: 20.0,
  /** DOUBLE_80438978 = 0.5 — B-melee timescale multiplier (phase 3). */
  MELEE_TIMESCALE: 0.5,
  /** DOUBLE_80438960 = 8100.0 — direction angle threshold (far). */
  DIR_FAR: 8100.0,
  /** DOUBLE_80438968 = 2700.0 — direction angle threshold (near). */
  DIR_NEAR: 2700.0,
  /** FLOAT_80438988 = 60.0 — B-melee phase 4 distance gate. */
  MELEE_PHASE4_DIST: 60.0,
  /** DOUBLE_80438990 = 0.5 — B-melee timescale halving (phase 4). */
  MELEE_PHASE4_TIMESCALE: 0.5,
  /** zz_00c3be0_ @0x800c3be0 — per-borg effect spawner. */
  EFFECT_BORG_SPAWNER_ADDR: 0x800c3be0,
  /** zz_006bf80_ @0x8006bf80 — shared combo-reset. */
  COMBO_RESET_ADDR: 0x8006bf80,
} as const;

function cmBorgEffects(borgNumber: number): number[] {
  switch (borgNumber) {
    case 0x602: return [0x16, 0x17, 0x18];
    case 0x60a: return [0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e];
    case 0x60c: return [0x6f, 0x70, 0x71, 0x72, 0x73];
    case 0x60e: return [0x74, 0x75, 0x76, 0x77];
    default: return [];
  }
}

// ============================================================================
// Scratch fields.
// ============================================================================
interface CMScratch {
  moveTimer: number;
  ubActive: number;
  comboStop: number;
  animOffset2: number;
  animOffset1: number;
  animOffset0: number;
  streamCueCount: number;
  streamCueCount2: number;
  perFrameField: number;
  partActive: Int8Array;
}

function scratchOf(actor: RomActor): RomActor & CMScratch {
  return actor as RomActor & CMScratch;
}

// ============================================================================
// Action 0 — Dash attack.
// FUN_800cc7d4: steer halved + transform, dispatch PTR_FUN_8030cd28[variant].
//   v0→FUN_800cc854 → PTR_FUN_8030cd3c: ph0 arm, ph1 decay, ph2 combo-or-return.
//   v1→FUN_800ccc54 → PTR_FUN_8030cd48: ph0 arm, ph1 decay-with-dir-check, ph2.
//   v2→FUN_800ccf78 → PTR_FUN_8030cd54: ph0 arm-with-gravity, ph1 decay.
// ============================================================================

function cmAction0Wrapper(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  // steerYaw centering transform (FUN_800cc7d4:2163-2168)
  actor.steerYaw = actor.steerYaw >> 1;
  if (actor.variantIndex === 0) cmDashV0(actor, ctx);
  else if (actor.variantIndex === 1) cmDashV1(actor, ctx);
  else if (actor.variantIndex === 2) cmDashV2(actor, ctx);
}

// --- Variant 0: PTR_FUN_8030cd3c ---

function cmDashV0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) cmDashV0Ph0(actor, ctx);
  else if (phase === 1) cmDashV0Ph1(actor, ctx);
  else cmDashV0Ph2(actor, ctx);
}

function cmDashV0Ph0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  void ctx;
  actor.fbPhaseSlots[0] = 1;
  // zz_00cd3ec_ direction check → start stream
  s.moveTimer = CM_X.DASH_TIMER;
  actor.gravityCoeff = 0; actor.yVel = 0; actor.hDecel = 0; actor.hSpeed = 0;
  s.animOffset2 = 0; s.animOffset1 = 0; s.animOffset0 = 0;
  // pos += (pos - target) * VEL_SCALE (velocity projection)
  actor.pos.x += (actor.pos.x - 0) * CM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * CM_X.VEL_SCALE;
  s.perFrameField = 0;
  startStream(actor, 0xf, 0, 1, CM_X.STREAM_RATE);
}

function cmDashV0Ph1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  actor.pos.x += (actor.pos.x - 0) * CM_X.VEL_SCALE;
  actor.pos.z += (actor.pos.z - 0) * CM_X.VEL_SCALE;
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0) {
    actor.fbPhaseSlots[0] = 2;
    cmDashSharedTransition(actor, ctx);
  }
}

function cmDashV0Ph2(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    scratchOf(actor).ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
  // zz_00b22f4_ velocity continuation check
}

// --- Variant 1: PTR_FUN_8030cd48 ---

function cmDashV1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) cmDashV1Ph0(actor, ctx);
  else if (phase === 1) cmDashV1Ph1(actor, ctx);
  else cmDashV1Ph2(actor, ctx);
}

function cmDashV1Ph0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  void ctx;
  actor.fbPhaseSlots[0] = 1;
  s.streamCueCount = 1;
  startStream(actor, 0xf, 0, 1, CM_X.STREAM_RATE);
}

function cmDashV1Ph1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0 && actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = 2;
    cmDashSharedTransition(actor, ctx);
  }
}

function cmDashV1Ph2(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    scratchOf(actor).ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}

// --- Variant 2: PTR_FUN_8030cd54 ---

function cmDashV2(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) cmDashV2Ph0(actor, ctx);
  else if (phase === 1) cmDashV2Ph1(actor, ctx);
}

function cmDashV2Ph0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  ctx.onFaceComplete?.(actor, 0x81);
  // gravity + ground snap
  s.perFrameField = 0;
  startStream(actor, 0xf, 0, 1, CM_X.STREAM_RATE);
}

function cmDashV2Ph1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if ((s.moveTimer <= 0 || (ctx.onFaceComplete?.(actor, 0x81) ?? false)) && actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = 2;
    cmDashSharedTransition(actor, ctx);
  }
}

// --- Shared: FUN_800cd1a0 (borg-switched effect spawn) ---

function cmDashSharedTransition(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  s.moveTimer = CM_X.TRANS_TIMER;
  s.streamCueCount = 1;
  // zz_006dbe0_(actor, 0, 1, 1) — allocate resource for effect
  if (ctx.onAllocateResource?.(actor, 0, 1, 1) ?? true) {
    const effects = cmBorgEffects(actor.borgNumber);
    for (const e of effects) ctx.onFamilyProjectile?.(actor, CM_X.EFFECT_BORG_SPAWNER_ADDR, e);
  }
}

// ============================================================================
// X-special (FUN_800ce5dc): 2-phase ammo-gated shot deploy.
// ============================================================================

function cmXPhase0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;
  ctx.onFamilyProjectile?.(actor, CM_X.EFFECT_SPAWNER_ADDR, CM_X.EFFECT_TYPE);
}

function cmXPhase1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  actor.controlWord = actor.controlWord & ~CM_X.ACTION_MODE_BITS;
  ctx.onFamilyProjectile?.(actor, CM_X.SHOT_SPAWNER_ADDR, CM_X.SHOT_KIND);
  actor.stateTimer = CM_X.COOLDOWN + actor.dt;
  dispatchUpperBodyCue(actor, 7);
  dispatchFullBodyCue(actor, 0);
}

function cmXHandler(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) cmXPhase0(actor, ctx);
  else cmXPhase1(actor, ctx);
}

// ============================================================================
// Action 1 — B melee (FUN_800cd4cc → PTR_FUN_8030cd60[variant]).
// v0→FUN_800cd514 → PTR_FUN_8030cd74: 5 phases.
// v1→FUN_800cd988 → PTR_FUN_8030cd88: 5 phases (simplified to 3-phase).
// ============================================================================

function cmBMeleeWrapper(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  actor.steerYaw = actor.steerYaw >> 1;
  if (actor.variantIndex === 0) cmMeleeV0(actor, ctx);
  else cmMeleeV1(actor, ctx);
}

function cmMeleeV0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.fbPhaseSlots[1] !== 0) s.comboStop = 0;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) cmMeleeV0Ph0(actor, ctx);
  else if (phase === 1) cmMeleeV0Ph1(actor, ctx);
  else if (phase === 2) cmMeleeV0Ph2(actor, ctx);
  else if (phase === 3) cmMeleeV0Ph3(actor, ctx);
  else cmMeleeV0Ph4(actor, ctx);
}

function cmMeleeV0Ph0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  if (s.comboStop >= 0) {
    actor.fbPhaseSlots[1] = 1;
    s.comboStop = 0;
    actor.activeYaw = actor.heading;
  }
  s.moveTimer = CM_X.MELEE_TIMER;
  ctx.onFaceComplete?.(actor, 0xc0);
  s.streamCueCount = 2;
  const slot = s.streamCueCount;
  s.streamCueCount = slot + 1;
  startStream(actor, 0xf, 3, slot, CM_X.STREAM_RATE);
}

function cmMeleeV0Ph1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.contactP0 === 0) tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0 || (ctx.onFaceComplete?.(actor, 0xc0) ?? false)) {
    actor.fbPhaseSlots[0] = s.comboStop !== 0 ? 3 : 2;
    s.moveTimer = CM_X.TRANS_TIMER;
    const animDist = s.comboStop;
    actor.hSpeed = animDist / CM_X.TRANS_TIMER;
    actor.yVel = 0;
    if (animDist > CM_X.MELEE_DIST) {
      // zz_00b2190_ snap toward target
    }
  }
}

function cmMeleeV0Ph2(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0) {
    actor.fbPhaseSlots[0] = 3;
    s.streamCueCount2 = 6;
  }
}

function cmMeleeV0Ph3(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  const s = scratchOf(actor);
  ctx.onFaceComplete?.(actor, 0xc0);
  s.streamCueCount2 -= 1;
  if (s.streamCueCount2 < 0) {
    actor.fbPhaseSlots[0] = 4;
    s.moveTimer = 0;
  }
}

function cmMeleeV0Ph4(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  ctx.onFaceComplete?.(actor, 0xc0);
  if (actor.wallContact !== 0) {
    s.ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}

function cmMeleeV1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  if (actor.fbPhaseSlots[1] !== 0) s.comboStop = 0;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) cmMeleeV1Ph0(actor, ctx);
  else if (phase === 1) cmMeleeV1Ph1(actor, ctx);
  else cmMeleeV1Ph2(actor, ctx);
}

function cmMeleeV1Ph0(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.moveTimer = CM_X.MELEE_TIMER;
  ctx.onFaceComplete?.(actor, 0xc0);
  s.streamCueCount = 2;
  startStream(actor, 0xf, 3, 0, CM_X.STREAM_RATE);
}

function cmMeleeV1Ph1(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0) {
    actor.fbPhaseSlots[0] = 2;
    s.moveTimer = 8.0;
  }
}

function cmMeleeV1Ph2(actor: RomActor, ctx: CyberMachineFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onFaceComplete?.(actor, 0xc0);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= 0) {
    s.ubActive = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}


export interface CyberMachineFamilyCtx extends StreamContext {
  onFaceComplete?: (actor: RomActor, mask: number) => boolean;
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode: number) => boolean;
  onFamilyProjectile?: (actor: RomActor, addr: number, type: number) => void;
}

export function createCyberMachineRootAction(
  ctx: CyberMachineFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    (a) => cmAction0Wrapper(a, ctx),
    (a) => cmBMeleeWrapper(a, ctx),
    (a) => cmXHandler(a, ctx),
    null, // 3: B charge
    null, // 4:
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned CYBER MACHINE-family actor (pl0602/pl060a/pl060c/pl060e).
 *  Wires the root action dispatcher and stamps the borg-number switch. */
export function configureCyberMachineFamily(
  actor: RomActor,
  borgId: "pl0602" | "pl060a" | "pl060c" | "pl060e",
  ctx: CyberMachineFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0602" ? 0x602 :
    borgId === "pl060a" ? 0x60a :
    borgId === "pl060c" ? 0x60c : 0x60e;
  actor.rootAction = createCyberMachineRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
