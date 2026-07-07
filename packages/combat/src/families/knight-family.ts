import type { RomActor } from "../rom/actor.js";
import { integratePhysics } from "../rom/physics.js";

const GRAVITY_PARAM = 1.0;
const ZERO = 0.0;
const HSPEED_THRESHOLD = 3.0;
const DECAY_95 = 0.95;
const TIMER_30 = 30.0;
const TIMER_3600 = 3600.0;
const SPEED_MUL_2 = 2.0;
const STATE_TIMER_OFFSET = 8.0;
const AIM_TYPE = 0x81;
const STREAM_GROUP = 0xf;

function scratchOf(actor: RomActor): RomActor & KnightScratch {
  return actor as RomActor & KnightScratch;
}

interface KnightScratch {
  knightSpawned?: number;
  knightHitCount?: number;
  knightContactByte?: number;
  knightStreamF?: number;
  knightTimerShort?: number;
  knightSubPhase?: number;
  knightTimerA?: number;
  knightTimerB?: number;
  knightTimerC?: number;
  knightSubTimer?: number;
  knightLockFlag?: number;
  knightSubAnim?: number;
  knightDamageByte?: number;
  knightDamageFlag?: number;
  knightFaceFlag?: number;
  knightFlagsB?: number;
}

export const SHOT_X = {
  SOUND_CUE: 0xf,
  CHILD_SPAWN: 0xd9,
  FX_HIT: 0xda,
  RESOURCE_TYPE: 0,
  AIM_TYPE,
  STREAM_GROUP,
  GRAVITY_PARAM,
  HSPEED_THRESHOLD,
  STATE_TIMER_OFFSET,
} as const;

export const JUMP_X = {
  SOUND_CUE: 0xf,
  RESOURCE_TYPE: 2,
  STREAM_GROUP,
  GRAVITY_PARAM,
  DECAY_FACTOR: DECAY_95,
  TIMER_30,
  TIMER_3600,
  SPEED_MUL_2,
  STATE_TIMER_OFFSET,
  HSPEED_THRESHOLD,
  TIMER_SHORT: 20,
} as const;

export interface KnightFamilyCtx {
  onTickStream?: (actor: RomActor, group: number) => void;
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode: number) => boolean;
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  onSpawnChild?: (actor: RomActor, childType: number) => boolean;
  onSpawnFX?: (actor: RomActor, fxId: number) => void;
  onFaceTarget?: (actor: RomActor, aimType: number) => void;
  onFrameUpdate?: (actor: RomActor) => void;
  onCheckCollision?: (actor: RomActor) => number;
  onExitFb?: (actor: RomActor) => void;
  onExitUb?: (actor: RomActor) => void;
  onClearAction?: (actor: RomActor) => void;
}

// 5-phase
function shotPhase0(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.knightHitCount = 0;
  if (actor.variantIndex === 0) {
    actor.gravityCoeff = ZERO;
    actor.hDecel = ZERO;
    actor.yVel = ZERO;
    actor.hSpeed = ZERO;
    s.knightTimerC = ZERO;
    s.knightTimerB = ZERO;
    s.knightTimerA = ZERO;
  } else if (actor.variantIndex === 1) {
    actor.gravityCoeff = ZERO;
    actor.hDecel = ZERO;
  }
  ctx.onFaceTarget?.(actor, AIM_TYPE);
  s.knightHitCount = (s.knightHitCount ?? 0) + 1;
  ctx.onPlayCue?.(actor, SHOT_X.SOUND_CUE);
  if (!s.knightSpawned) {
    ctx.onSpawnChild?.(actor, SHOT_X.CHILD_SPAWN);
  }
  s.knightStreamF = ZERO;
}

function shotPhase1(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  if ((s.knightFaceFlag ?? 0) > 0) {
    ctx.onFaceTarget?.(actor, AIM_TYPE);
  }
  ctx.onTickStream?.(actor, STREAM_GROUP);
  integratePhysics(GRAVITY_PARAM, actor, actor.lockYaw);
  const col = ctx.onCheckCollision?.(actor) ?? 0;
  if ((s.knightContactByte ?? 0) > 0) {
    if (!s.knightSpawned) {
      const ok = ctx.onAllocateResource?.(actor, SHOT_X.RESOURCE_TYPE, 1, 1);
      if (ok) {
        s.knightContactByte = 0;
        const childType = actor.borgNumber === 0x203 ? 0 : 1;
        ctx.onSpawnChild?.(actor, childType);
        s.knightSpawned = 1;
        ctx.onSpawnFX?.(actor, SHOT_X.FX_HIT);
      }
    }
  }
  if (!actor.wallContact) {
    if (actor.hSpeed > HSPEED_THRESHOLD) {
      ctx.onFrameUpdate?.(actor);
    }
  } else if (col === 0) {
    s.knightLockFlag = 0;
    actor.controlWord &= ~0x3;
    ctx.onExitFb?.(actor);
  } else {
    actor.fbPhaseSlots[0] = 2;
    s.knightHitCount = (s.knightHitCount ?? 0) + 1;
    ctx.onPlayCue?.(actor, SHOT_X.SOUND_CUE);
  }
}

function shotPhase2(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, STREAM_GROUP);
  if (actor.wallContact) {
    s.knightLockFlag = 0;
    actor.controlWord &= ~0x3;
    ctx.onExitUb?.(actor);
    actor.stateTimer = STATE_TIMER_OFFSET + actor.dt;
  }
}

function createShotHandler(ctx: KnightFamilyCtx): (actor: RomActor) => void {
  return (actor) => {
    switch (actor.fbPhaseSlots[0]) {
      case 0: shotPhase0(actor, ctx); break;
      case 1: shotPhase1(actor, ctx); break;
      case 2: shotPhase2(actor, ctx); break;
    }
  };
}

// 7-phase
function jumpPhase0(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  const ok = ctx.onAllocateResource?.(actor, JUMP_X.RESOURCE_TYPE, 1, 1);
  if (!ok) {
    s.knightLockFlag = 0;
    actor.controlWord &= ~0x3;
    const col = ctx.onCheckCollision?.(actor) ?? 0;
    if (col === 0) {
      ctx.onExitFb?.(actor);
    } else {
      ctx.onExitUb?.(actor);
    }
    actor.stateTimer = STATE_TIMER_OFFSET + actor.dt;
  } else {
    actor.fbPhaseSlots[0] = 1;
    s.knightTimerA = TIMER_3600;
    s.knightTimerB = TIMER_30;
    s.knightTimerC = ZERO;
    s.knightTimerShort = JUMP_X.TIMER_SHORT;
    if (actor.descriptor) {
      actor.motion.x = SPEED_MUL_2 * (actor.descriptor.handlerData2c ?? 0);
    }
    actor.hSpeed = ZERO;
    actor.yVel = ZERO;
    actor.hDecel = ZERO;
    if (actor.descriptor) {
      actor.gravityCoeff = actor.descriptor.handlerData6c;
    }
    s.knightHitCount = (actor.controlWord & 0x40) !== 0 ? 4 : 2;
    s.knightHitCount = (s.knightHitCount ?? 0) + 1;
    ctx.onPlayCue?.(actor, JUMP_X.SOUND_CUE);
    s.knightStreamF = ZERO;
  }
}

function jumpPhase1(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, STREAM_GROUP);
  if ((s.knightContactByte ?? 0) > 0) {
    actor.fbPhaseSlots[0] = 2;
    ctx.onPlayCue?.(actor, 0);
  }
}

function jumpPhase2(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  const ts = s.knightTimerShort ?? JUMP_X.TIMER_SHORT;
  s.knightTimerShort = ts - 1;
  if ((s.knightDamageByte ?? 0) !== 0 || s.knightTimerShort! < 1) {
    jumpGotoPhase3(actor, s);
    return;
  }
  const subPhase = s.knightSubPhase ?? 0;
  if (subPhase === 0) {
    if (actor.descriptor) {
      s.knightSubAnim = actor.descriptor.handlerData9f ?? 0;
    }
    if (actor.variantIndex === 1) {
      s.knightSubAnim = 0;
    }
  }
  if (subPhase === 1) {
    s.knightSubAnim = 0;
    if ((s.knightFlagsB ?? 0) & 0x100) {
      s.knightSubPhase = (s.knightSubPhase ?? 0) + 1;
      if (actor.descriptor) {
        s.knightSubTimer = actor.descriptor.handlerData3d ?? 0;
        actor.gravityCoeff = actor.descriptor.handlerData68 ?? actor.descriptor.handlerData6c;
        s.knightTimerC = SPEED_MUL_2 * (actor.descriptor.handlerData48 ?? 0) - actor.gravityCoeff * (s.knightSubTimer ?? 0);
      }
    }
  }
  if (subPhase > 0) {
    s.knightSubTimer = (s.knightSubTimer ?? 0) - actor.dt;
    if ((s.knightSubTimer ?? 0) <= ZERO) {
      s.knightSubPhase = 0;
      if (actor.descriptor) {
        actor.gravityCoeff = actor.descriptor.handlerData6c;
      }
    }
  }
  actor.hSpeed = actor.motion.x;
  integratePhysics(GRAVITY_PARAM, actor, actor.lockYaw);
  const col = ctx.onCheckCollision?.(actor) ?? 0;
  if (col !== 0) {
    actor.yVel = ZERO;
    if (subPhase === 0) {
      s.knightSubPhase = 1;
      ctx.onPlayCue?.(actor, 2);
      ctx.onSpawnFX?.(actor, 10);
    }
    actor.lockYaw = actor.heading;
  }
  if ((s.knightTimerB ?? 0) > ZERO) {
    s.knightTimerB = (s.knightTimerB ?? 0) - actor.dt;
  }
  if ((s.knightTimerA ?? 0) > ZERO) {
    s.knightTimerA = (s.knightTimerA ?? 0) - actor.dt;
  }
  const timerBok = (s.knightTimerB ?? 0) > ZERO;
  const flagB400ok = ((s.knightFlagsB ?? 0) & 0x400) === 0;
  const timerAok = (s.knightTimerA ?? 0) > ZERO;
  const frameOk = (timerBok || flagB400ok) && timerAok;
  if (frameOk) {
    if (actor.hSpeed <= HSPEED_THRESHOLD) {
      return;
    }
    ctx.onFrameUpdate?.(actor);
  } else {
    jumpGotoPhase3(actor, s);
  }
}

function jumpGotoPhase3(actor: RomActor, s: RomActor & KnightScratch): void {
  actor.fbPhaseSlots[0] = 3;
  s.knightHitCount = (actor.controlWord & 0x40) !== 0 ? 3 : 5;
  s.knightHitCount = (s.knightHitCount ?? 0) + 1;
}

function jumpPhase3(actor: RomActor, ctx: KnightFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, STREAM_GROUP);
  if ((s.knightDamageFlag ?? 0) > 0) {
    s.knightDamageFlag = 0;
    actor.yVel = ZERO;
    actor.hSpeed = ZERO;
  }
  actor.hSpeed *= DECAY_95;
  actor.yVel *= DECAY_95;
  integratePhysics(GRAVITY_PARAM, actor, actor.lockYaw);
  if (!actor.wallContact) {
    if (actor.hSpeed > HSPEED_THRESHOLD) {
      ctx.onFrameUpdate?.(actor);
    }
  } else {
    s.knightLockFlag = 0;
    actor.controlWord &= ~0x3;
    const col = ctx.onCheckCollision?.(actor) ?? 0;
    if (col === 0) {
      ctx.onExitFb?.(actor);
    } else {
      ctx.onExitUb?.(actor);
    }
    actor.stateTimer = STATE_TIMER_OFFSET + actor.dt;
  }
}

function createJumpHandler(ctx: KnightFamilyCtx): (actor: RomActor) => void {
  return (actor) => {
    switch (actor.fbPhaseSlots[0]) {
      case 0: jumpPhase0(actor, ctx); break;
      case 1: jumpPhase1(actor, ctx); break;
      case 2: jumpPhase2(actor, ctx); break;
      case 3: jumpPhase3(actor, ctx); break;
    }
  };
}

export function createKnightRootAction(ctx: KnightFamilyCtx): (actor: RomActor) => void {
  const shotHandler = createShotHandler(ctx);
  const jumpHandler = createJumpHandler(ctx);
  return (actor) => {
    switch (actor.actionIndex) {
      case 2: shotHandler(actor); break;
      case 4: jumpHandler(actor); break;
    }
  };
}

export function configureKnightFamily(actor: RomActor, borgId: "pl0203" | "pl020c", ctx: KnightFamilyCtx): void {
  actor.borgNumber = borgId === "pl0203" ? 0x203 : 0x20c;
  actor.rootAction = createKnightRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  const s = scratchOf(actor);
  s.knightSpawned = 0;
}
