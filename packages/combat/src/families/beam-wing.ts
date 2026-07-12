import type { RomActor } from "../rom/actor.js";
import { projectX, projectZ } from "../rom/physics.js";
import { vecSubtract, vecScale, vecAdd } from "../rom/physics.js";

const ZERO = 0;
const ONE = 1.0;
const HALF = 0.5;
const DECAY_95 = 0.95;
const THREE = 3.0;
const SIX = 6.0;
const FIFTEEN = 15.0;
const TWELVE = 12.0;
const FIVE = 5.0;
const AIM_TYPE_C1 = 0xc1;
const AIM_TYPE_C0 = 0xc0;
const STREAM_GROUP_F = 0xf;
const STREAM_GROUP_3 = 3;

function scratchOf(actor: RomActor): RomActor & BeamWingScratch {
  return actor as RomActor & BeamWingScratch;
}

interface BeamWingScratch {
  // +0xcc: target lock
  targetLock?: number;
  // +0x54a: aim yaw (lock-yaw copy for steering)
  aimYaw?: number;
  // +0x54c: frame timer
  frameTimer?: number;
  // +0x54e: short aim timer
  aimTimer?: number;
  // +0x55c: state timer B (separate from RomActor.handlerTimer at +0x558)
  timerB?: number;
  // +0x560: beam health timer (separate from RomActor.stateTimer at +0x694)
  beamTimer?: number;
  // +0x5d4: status flags (bit 0x40 = hit flag)
  statusFlags?: number;
  // +0x5d8: collision flags (bit 0xf0 = wall contact)
  collisionFlags?: number;
  // +0x5e8: target position (Vec3)
  targetPos?: { x: number; y: number; z: number };
  // +0x6eb: beam direction
  beamDir?: number;
  // +0x6ec: anim state counter
  animCounter?: number;
  // +0x6f7: damage byte
  damageByte?: number;
  // +0x73f: control flag (clear on contact)
  ctrlFlag73f?: number;
  // +0x745: root engine hit flag
  rootHitFlag?: number;
  // +0x746: melee hit flag
  meleeHitFlag?: number;
  // +0x760: range/reference value
  rangeRef?: number;
  // +0x1ae0: frame/sound rate
  soundRate?: number;
  // +0x1af8: sound counter
  soundCounter?: number;
  // +0x1b03: contact flag
  contactFlag?: number;
  // +0x1cf0: ground hit flag
  groundHit?: number;
  // +0x1d0f: power flag
  powerFlag?: number;
  // +0x1d10: contact B flag
  contactB?: number;
  // +0x1d9: collision hit flag
  collisionHit?: number;
  // +0x542: X-special sub-phase
  xSubPhase?: number;
  // +0x587: anim flag B
  animFlagB?: number;
  // +0x588: anim state
  animState?: number;
  // +0x541: target lost flag
  targetLost?: number;
}

export interface BeamWingCtx {
  onTickStream?: (actor: RomActor, group: number) => void;
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  onSpawnChild?: (actor: RomActor, childType: number) => boolean;
  onSpawnFX?: (actor: RomActor, fxId: number) => void;
  onFaceTarget?: (actor: RomActor, aimType: number) => void;
  onFrameUpdate?: (actor: RomActor) => void;
  onCheckCollision?: (actor: RomActor) => number;
  onExitFb?: (actor: RomActor) => void;
  onExitUb?: (actor: RomActor) => void;
  onClearAction?: (actor: RomActor) => void;
  onStopStream?: (actor: RomActor, group: number) => void;
  onGroundSnap?: (actor: RomActor) => void;
}

// ===== HELPERS =====

function pos(actor: RomActor) { return actor.pos; }
function motion(actor: RomActor) { return actor.motion; }
function target(actor: RomActor) {
  const s = scratchOf(actor);
  if (!s.targetPos) s.targetPos = { x: 0, y: 0, z: 0 };
  return s.targetPos;
}

function blinkTowardTarget(actor: RomActor, scale: number): void {
  const p = pos(actor);
  const t = target(actor);
  vecSubtract(p, t, motion(actor));
  vecScale(scale, motion(actor), motion(actor));
  vecAdd(p, motion(actor), p);
}

function zeroSpeed(actor: RomActor): void {
  actor.hSpeed = ZERO;
  actor.yVel = ZERO;
  actor.hDecel = ZERO;
  actor.gravityCoeff = ZERO;
}

function resetBeamOnCollision(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  s.animCounter = (s.animCounter ?? SIX) - 1;
  actor.handlerTimer = FIFTEEN;
  s.rootHitFlag = 0;
  s.animFlagB = 0;
  const ok = ctx.onAllocateResource?.(actor, 0, 1, 1);
  if (ok) {
    const borg = actor.borgNumber;
    if (borg === 0xa03) {
      ctx.onSpawnFX?.(actor, 2);
      ctx.onSpawnFX?.(actor, 3);
    } else if (borg === 0xa06) {
      ctx.onSpawnFX?.(actor, 2);
      ctx.onSpawnFX?.(actor, 3);
    }
  }
}

// ===== ROOT ENGINE PRE (zz_00fa6f4_) =====
function preTick(actor: RomActor): void {
  const s = scratchOf(actor);
  s.beamTimer = (s.beamTimer ?? THREE) - actor.dt;
  s.aimYaw = actor.heading;
}

// ===== ROOT ENGINE +0x544 SUB (PTR_FUN_80434478) =====
function movePhase0(_actor: RomActor): void {
  // default — no special movement
}

function movePhase1(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[1] = (actor.fbPhaseSlots[1] ?? 0) + 1;
  s.soundRate = 0xff;
  s.beamTimer = ZERO;
  s.animState = 0;
  if ((s.animFlagB ?? 0) === 0) {
    actor.hDecel = ZERO;
    actor.gravityCoeff = ZERO;
  }
  ctx.onPlayCue?.(actor, 2 + STREAM_GROUP_3);
  // zz_00fa5a8_ — stream + motion
  ctx.onStopStream?.(actor, STREAM_GROUP_3);
  s.animCounter = (s.animCounter ?? SIX) + 0x15;
}

// zz_00fa5a8_ — post-tick switch
function postMoveSwitch(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  const dir = s.beamDir ?? 0;
  if (dir === 0) {
    ctx.onStopStream?.(actor, 2);
  } else {
    if (actor.hSpeed < (actor.descriptor?.maxHSpeed ?? THREE)) {
      actor.hSpeed = actor.descriptor?.maxHSpeed ?? THREE;
    }
    actor.gravityCoeff = ZERO;
    actor.lockYaw = actor.activeYaw;
  }
  if ((actor.controlWord & 0x100) === 0) {
    actor.yVel = ONE;
  } else {
    actor.yVel = ZERO;
  }
  ctx.onGroundSnap?.(actor);
  if ((s.soundRate ?? 0) === dir) {
    ctx.onStopStream?.(actor, 3);
  } else {
    if ((s.soundRate ?? 0xff) >= 0) {
      ctx.onPlayCue?.(actor, (s.soundCounter ?? FIVE) + dir);
      ctx.onPlayCue?.(actor, 2);
    }
    s.soundRate = dir;
  }
}

// ===== ROOT ENGINE +0x540 MAIN (PTR_FUN_8031d410) =====
function rootPh0(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.beamTimer = THREE;
  s.rootHitFlag = 0;
  s.animCounter = SIX;
  ctx.onPlayCue?.(actor, 1);
}

function rootPh1(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  const expired = (s.beamTimer ?? THREE) < ZERO;
  const contacted = actor.wallContact !== 0 && (s.aimYaw ?? 0) !== 0;
  if (expired || contacted) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    resetBeamOnCollision(actor, ctx);
  }
}

function rootPh2(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  if ((s.statusFlags ?? 0) & 0x40) {
    s.rootHitFlag = 1;
  }
  if ((s.handlerTimer ?? ZERO) > ZERO) {
    s.handlerTimer = (s.handlerTimer ?? ZERO) - actor.dt;
  }
  if (actor.wallContact !== 0) {
    if ((s.rootHitFlag ?? 0) !== 0) {
      const ok = ctx.onAllocateResource?.(actor, 0, 1, 0);
      if (!ok) {
        ctx.onExitFb?.(actor);
        resetBeamOnCollision(actor, ctx);
        return;
      }
    }
    s.timerB = SIX;
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    ctx.onPlayCue?.(actor, 7);
  }
  if (s.collisionFlags ?? 0 & 0xf0) {
    actor.controlWord &= ~0x3;
    const col = ctx.onCheckCollision?.(actor) ?? 0;
    if (col === 0) ctx.onExitFb?.(actor);
    else ctx.onExitUb?.(actor);
    s.handlerTimer = (s.handlerTimer ?? ZERO) + actor.dt;
  }
}

function rootPh3(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  if ((s.statusFlags ?? 0) & 0x40) s.rootHitFlag = 1;
  if ((s.rootHitFlag ?? 0) !== 0) {
    const ok = ctx.onAllocateResource?.(actor, 0, 1, 0);
    if (!ok) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1;
      s.rootHitFlag = 0;
      s.animCounter = SIX;
      ctx.onExitFb?.(actor);
      resetBeamOnCollision(actor, ctx);
      return;
    }
  }
  const noCollision = (s.collisionFlags ?? 0 & 0xf0) === 0;
  if (noCollision) s.timerB = (s.timerB ?? SIX) - actor.dt;
  const expired = (s.timerB ?? SIX) <= ZERO;
  if (!noCollision || expired || actor.wallContact !== 0) {
    actor.controlWord &= ~0x3;
    const col = ctx.onCheckCollision?.(actor) ?? 0;
    if (col === 0) ctx.onExitFb?.(actor);
    else ctx.onExitUb?.(actor);
  }
}

function rootHalfSteer(actor: RomActor, ctx: BeamWingCtx): void {
  actor.steerYaw = actor.steerYaw >> 1;
  ctx.onClearAction?.(actor);
}

// ===== ROOT ENGINE +0x545 ANIM SUB (PTR_FUN_80434480) =====
function animPh1(actor: RomActor, ctx: BeamWingCtx): void {
  actor.fbPhaseSlots[2] = (actor.fbPhaseSlots[2] ?? 0) + 1;
  ctx.onPlayCue?.(actor, 4);
}

function animPh2(actor: RomActor, ctx: BeamWingCtx): void {
  ctx.onStopStream?.(actor, 4);
}

// ===== ACTION 1 — melee (PTR_FUN_8031d434) =====
function meleePh0(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.handlerTimer = SIX;
  const ok = ctx.onAllocateResource?.(actor, 0, 1, 0);
  if (!ok) {
    s.targetLost = 1;
    actor.controlWord = 0;
    actor.lockYaw = actor.heading;
    actor.activeYaw = actor.heading;
  }
  ctx.onFaceTarget?.(actor, AIM_TYPE_C0);
  blinkTowardTarget(actor, HALF);
  ctx.onGroundSnap?.(actor);
  ctx.onCheckCollision?.(actor);
  ctx.onPlayCue?.(actor, STREAM_GROUP_F);
}

function meleePh1(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  if ((s.contactFlag ?? 0) !== 0) ctx.onStopStream?.(actor, STREAM_GROUP_F);
  ctx.onGroundSnap?.(actor);
  s.handlerTimer = (s.handlerTimer ?? SIX) - actor.dt;
  if ((s.handlerTimer ?? SIX) <= ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  }
}

function meleePh2(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  ctx.onStopStream?.(actor, STREAM_GROUP_F);
  ctx.onFaceTarget?.(actor, AIM_TYPE_C0);
  ctx.onGroundSnap?.(actor);
  if (actor.contactP0 !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    s.handlerTimer = SIX;
    zeroSpeed(actor);
    if ((s.rangeRef ?? ZERO) < TWELVE) {
      ctx.onSpawnFX?.(actor, 0);
    }
  }
}

function meleePh3(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  if (actor.contactP0 >= 0) ctx.onStopStream?.(actor, STREAM_GROUP_F);
  ctx.onFaceTarget?.(actor, AIM_TYPE_C0);
  const sinY = projectZ(actor.steerYaw);
  actor.hSpeed = THREE * sinY;
  const cosY = projectX(actor.steerYaw);
  actor.yVel = THREE * -cosY;
  ctx.onGroundSnap?.(actor);
  s.handlerTimer = (s.handlerTimer ?? SIX) - actor.dt;
  if ((s.handlerTimer ?? SIX) <= ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff;
  }
}

function meleePh4(actor: RomActor, ctx: BeamWingCtx): void {
  if (actor.contactP0 >= 0) {
    actor.steerYaw = Math.floor(actor.steerYaw * HALF);
  }
  ctx.onStopStream?.(actor, STREAM_GROUP_F);
  ctx.onGroundSnap?.(actor);
  const col = ctx.onCheckCollision?.(actor) ?? 0;
  if (actor.wallContact !== 0) {
    actor.controlWord &= ~0x3;
    if (col === 0) ctx.onExitFb?.(actor);
    else ctx.onExitUb?.(actor);
  }
}

// ===== ACTION 1 — chunk_0038.c melee (PTR_FUN_8033ecb8) =====
function melee38Ph0(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.meleeHitFlag = 0;
  const ok = ctx.onAllocateResource?.(actor, 0, 1, 0);
  if (!ok) {
    s.targetLost = 1;
    actor.controlWord = 0;
    actor.lockYaw = actor.heading;
    actor.activeYaw = actor.heading;
  }
  s.handlerTimer = SIX;
  ctx.onPlayCue?.(actor, STREAM_GROUP_F);
}

function melee38Ph1(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  if ((s.contactFlag ?? 0) !== 0) ctx.onStopStream?.(actor, STREAM_GROUP_F);
  s.handlerTimer = (s.handlerTimer ?? SIX) - actor.dt;
  if ((s.handlerTimer ?? SIX) <= ZERO) {
    s.handlerTimer = SIX;
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    ctx.onSpawnChild?.(actor, 0);
  }
}

function melee38Ph2(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  ctx.onFaceTarget?.(actor, AIM_TYPE_C0);
  const sinY = projectZ(s.aimTimer ?? 0);
  actor.hSpeed = (actor.motion?.x ?? THREE) * sinY;
  const cosY = projectX(s.aimTimer ?? 0);
  actor.yVel = (actor.motion?.x ?? THREE) * -cosY;
  ctx.onGroundSnap?.(actor);
  if ((s.contactFlag ?? 0) !== 0) ctx.onStopStream?.(actor, STREAM_GROUP_F);
  s.handlerTimer = (s.handlerTimer ?? SIX) - actor.dt;
  if ((s.handlerTimer ?? SIX) <= ZERO) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff;
  }
}

function melee38Ph3(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  if ((s.statusFlags ?? 0) & 0x40) s.meleeHitFlag = 1;
  ctx.onStopStream?.(actor, STREAM_GROUP_F);
  if ((s.targetLost ?? 0) !== 0) actor.controlWord = 0;
  if ((s.groundHit ?? 0) < 0 && (s.meleeHitFlag ?? 0) !== 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 1;
    s.meleeHitFlag = 0;
    s.handlerTimer = SIX;
    ctx.onPlayCue?.(actor, STREAM_GROUP_F);
    ctx.onSpawnChild?.(actor, 0);
    return;
  }
  if ((s.contactB ?? 0) !== 0) ctx.onFaceTarget?.(actor, AIM_TYPE_C0);
  if ((s.powerFlag ?? 0) !== 0) ctx.onSpawnChild?.(actor, 0);
  ctx.onGroundSnap?.(actor);
  const col = ctx.onCheckCollision?.(actor) ?? 0;
  if (actor.wallContact !== 0) {
    actor.controlWord &= ~0x3;
    if (col === 0) ctx.onExitFb?.(actor);
    else ctx.onExitUb?.(actor);
  }
}

// ===== ACTION 2 — X-special (PTR_FUN_804346a0 + PTR_FUN_8031d448) =====
function xSetup(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  if (actor.controlWord === 0) {
    actor.activeYaw = actor.heading;
  }
  ctx.onFaceTarget?.(actor, AIM_TYPE_C1);
  zeroSpeed(actor);
  blinkTowardTarget(actor, DECAY_95);
  ctx.onGroundSnap?.(actor);
  s.streamSlot = (s.streamSlot ?? 0) + 1;
  ctx.onPlayCue?.(actor, s.streamSlot ?? 0);
}

function xRecovery(actor: RomActor, ctx: BeamWingCtx): void {
  ctx.onStopStream?.(actor, STREAM_GROUP_F);
  if (actor.contactP0 < 1) return;
  actor.contactP0 = 0;
  ctx.onSpawnChild?.(actor, 0);
  ctx.onFaceTarget?.(actor, AIM_TYPE_C1);
  blinkTowardTarget(actor, DECAY_95);
  ctx.onGroundSnap?.(actor);
  if (actor.wallContact !== 0) {
    actor.controlWord &= ~0x3;
    actor.hDecel = ZERO;
    actor.gravityCoeff = ZERO;
    const col = ctx.onCheckCollision?.(actor) ?? 0;
    if (col === 0) ctx.onExitFb?.(actor);
    else ctx.onExitUb?.(actor);
  }
}

function xPh0(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  s.animState = actor.lockYaw;
  s.beamTimer = ZERO;
  s.streamSlot = 1;
  s.damageByte = 0;
  if (actor.controlWord === 0) actor.activeYaw = actor.heading;
  ctx.onFaceTarget?.(actor, AIM_TYPE_C1);
  zeroSpeed(actor);
  blinkTowardTarget(actor, DECAY_95);
  ctx.onGroundSnap?.(actor);
  const slot = s.streamSlot ?? 1;
  s.streamSlot = slot + 1;
  ctx.onPlayCue?.(actor, slot);
}

function xPh1(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  ctx.onStopStream?.(actor, STREAM_GROUP_F);
  ctx.onFaceTarget?.(actor, AIM_TYPE_C1);
  blinkTowardTarget(actor, DECAY_95);
  ctx.onGroundSnap?.(actor);
  if (actor.contactP0 > 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
    s.xSubPhase = 0;
    s.damageByte = 2;
    ctx.onSpawnFX?.(actor, 10);
  }
}

function xPh2(actor: RomActor, ctx: BeamWingCtx): void {
  const s = scratchOf(actor);
  s.damageByte = 2;
  // damage distribution from contact
  if ((s.contactFlag ?? 0) > 0) {
    const dmg = s.animState ?? 30;
    const cap = Math.min(s.contactFlag ?? 0, dmg);
    s.animState = dmg - cap;
    s.beamTimer = (s.beamTimer ?? ZERO) + cap;
  }
  ctx.onFaceTarget?.(actor, AIM_TYPE_C1);
  if ((s.powerFlag ?? 0) < 0) {
    s.powerFlag = 0;
    actor.gravityCoeff = actor.descriptor?.handlerData6c ?? actor.gravityCoeff;
  }
  ctx.onGroundSnap?.(actor);
  if ((s.beamTimer ?? ZERO) <= ZERO) {
    ctx.onStopStream?.(actor, STREAM_GROUP_F);
    if (actor.contactP0 < 0) {
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
      s.damageByte = 0;
    }
  } else {
    s.beamTimer = (s.beamTimer ?? ZERO) - actor.dt;
  }
}

function xPh3(actor: RomActor, ctx: BeamWingCtx): void {
  actor.steerYaw = Math.floor(actor.steerYaw * HALF);
  ctx.onGroundSnap?.(actor);
  ctx.onStopStream?.(actor, STREAM_GROUP_F);
  if (actor.wallContact !== 0) {
    actor.controlWord &= ~0x3;
    actor.hDecel = ZERO;
    actor.gravityCoeff = ZERO;
    const col = ctx.onCheckCollision?.(actor) ?? 0;
    if (col === 0) ctx.onExitFb?.(actor);
    else ctx.onExitUb?.(actor);
  }
}

// ===== DISPATCHERS =====

function createRootEngineHandler(ctx: BeamWingCtx): (actor: RomActor) => void {
  return (actor) => {
    preTick(actor);
    // +0x545 anim sub-dispatch
    const aPh = actor.fbPhaseSlots[2] ?? 0;
    if (aPh === 1) animPh1(actor, ctx);
    else if (aPh >= 2) animPh2(actor, ctx);
    // +0x544 move sub-dispatch
    const mPh = actor.fbPhaseSlots[1] ?? 0;
    if (mPh === 0) movePhase0(actor);
    else movePhase1(actor, ctx);
    // +0x540 main dispatch
    const ph = actor.fbPhaseSlots[0] ?? 0;
    switch (ph) {
      case 0: rootPh0(actor, ctx); break;
      case 1: rootPh1(actor, ctx); break;
      case 2: rootPh2(actor, ctx); break;
      case 3: rootPh3(actor, ctx); break;
      default: rootHalfSteer(actor, ctx); break;
    }
    // post-tick
    postMoveSwitch(actor, ctx);
  };
}

function createMeleeHandler(ctx: BeamWingCtx): (actor: RomActor) => void {
  return (actor) => {
    const ph = actor.fbPhaseSlots[0] ?? 0;
    switch (ph) {
      case 0: meleePh0(actor, ctx); break;
      case 1: meleePh1(actor, ctx); break;
      case 2: meleePh2(actor, ctx); break;
      case 3: meleePh3(actor, ctx); break;
      case 4: meleePh4(actor, ctx); break;
      default: rootHalfSteer(actor, ctx); break;
    }
  };
}

function createMelee38Handler(ctx: BeamWingCtx): (actor: RomActor) => void {
  return (actor) => {
    const ph = actor.fbPhaseSlots[0] ?? 0;
    switch (ph) {
      case 0: melee38Ph0(actor, ctx); break;
      case 1: melee38Ph1(actor, ctx); break;
      case 2: melee38Ph2(actor, ctx); break;
      case 3: melee38Ph3(actor, ctx); break;
      default: break;
    }
  };
}

function createXSpecialHandler(ctx: BeamWingCtx): (actor: RomActor) => void {
  return (actor) => {
    const ph = actor.fbPhaseSlots[0] ?? 0;
    switch (ph) {
      case 0: xSetup(actor, ctx); break;
      case 1: xRecovery(actor, ctx); break;
      case 2: xPh0(actor, ctx); break;
      case 3: xPh1(actor, ctx); break;
      case 4: xPh2(actor, ctx); break;
      case 5: xPh3(actor, ctx); break;
    }
  };
}

// ===== PUBLIC API =====

export function createBeamWingRootAction(ctx: BeamWingCtx): (actor: RomActor) => void {
  const rootHandler = createRootEngineHandler(ctx);
  const meleeHandler = createMeleeHandler(ctx);
  const melee38Handler = createMelee38Handler(ctx);
  const xHandler = createXSpecialHandler(ctx);
  return (actor) => {
    switch (actor.actionIndex) {
      case 0: rootHandler(actor); break;
      case 1: meleeHandler(actor); break;
      case 2: xHandler(actor); break;
      case 3: melee38Handler(actor); break;
    }
  };
}

export function configureBeamWingFamily(actor: RomActor, borgId: "pl0a03" | "pl0a06", ctx: BeamWingCtx): void {
  actor.borgNumber = borgId === "pl0a03" ? 0xa03 : 0xa06;
  actor.rootAction = createBeamWingRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  const s = scratchOf(actor);
  s.beamTimer = THREE;
  s.streamSlot = 0;
  s.beamDir = 0;
  s.animFlagB = 0;
}
