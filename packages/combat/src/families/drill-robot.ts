import type { RomActor } from "../rom/actor.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

export const DRILL_X = {
  STREAM_GROUP: 1,
  /** FLOAT_80438bc8 = 60.0 — setup timer. */
  SETUP_TIMER: 60.0,
  /** FLOAT_80438bd0 = 0.0 — timer floor. */
  TIMER_FLOOR: 0.0,
  /** FLOAT_80438bd4 = 0.9 — spin-down decay factor. */
  SPIN_DECAY: 0.9,
  SOUND_DEFAULT: 1,
  SOUND_VARIANT_ALT: 0xf,
} as const;

export interface DrillFamilyCtx {
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  /** Allocate resource slot (port of zz_006dbe0_). Returns true if ok. */
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
  /** Spawn child projectile (port of zz_00d9fbc_). */
  onDrillProjectile?: (actor: RomActor) => boolean;
  /** Stream ticker (port of zz_004cd24_). */
  onTickStream?: (actor: RomActor, group: number) => void;
}

interface DrillScratch {
  /** +0x541: fail flag — when set, dispatcher clears lock pointer + skips. */
  drillFailFlag?: boolean;
  /** +0x6ea: phase‑internal hit counter (byte). */
  drillHitCount?: number;
  /** +0x543: sound/cue variant byte. */
  drillCueVariant?: number;
  /** +0x5db: robot variant selector (1 → alt cue variant). */
  drillRobotVariant?: number;
  /** +0x18e0: animation spin-down field (short). */
  spinField0?: number;
  /** +0x18e2: animation spin-down field (short). */
  spinField1?: number;
}

function scratchOf(actor: RomActor): RomActor & DrillScratch {
  return actor as RomActor & DrillScratch;
}

function toS16(v: number): number {
  let s = Math.trunc(v) & 0xffff;
  if (s >= 0x8000) s -= 0x10000;
  return s;
}

// Phase 0 — FUN_800d8248: Setup timer + allocate + sound + advance to 1.
function drillPhase0(actor: RomActor, ctx: DrillFamilyCtx): void {
  const s = scratchOf(actor);
  actor.handlerTimer = DRILL_X.SETUP_TIMER;
  s.drillHitCount = 0;

  const ok = ctx.onAllocateResource?.(actor, 0, 1) ?? true;
  if (!ok) {
    s.drillFailFlag = true;
  }

  s.drillCueVariant = DRILL_X.SOUND_DEFAULT;
  if (s.drillRobotVariant === 1) {
    s.drillCueVariant = DRILL_X.SOUND_VARIANT_ALT;
  }
  ctx.onPlayCue?.(actor, s.drillCueVariant);

  actor.fbPhaseSlots[0] = 1;
}

// Phase 1 — FUN_800d8300: Stream tick + timer countdown. Advance to 2 when expired.
function drillPhase1(actor: RomActor, ctx: DrillFamilyCtx): void {
  ctx.onTickStream?.(actor, DRILL_X.STREAM_GROUP);

  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= DRILL_X.TIMER_FLOOR) {
    actor.fbPhaseSlots[0] = 2;
  }
}

// Phase 2 — FUN_800d836c: Hit check → allocate → advance to 4 (ok) or 3 (fail).
function drillPhase2(actor: RomActor, ctx: DrillFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, DRILL_X.STREAM_GROUP);

  if (actor.wallContact) {
    const ok = ctx.onAllocateResource?.(actor, 0, 1) ?? false;
    const hitCount = s.drillHitCount ?? 0;
    if (ok) {
      actor.fbPhaseSlots[0] = 4;
      s.drillCueVariant = DRILL_X.SOUND_DEFAULT;
      ctx.onPlayCue?.(actor, s.drillCueVariant);
      s.drillHitCount = hitCount + 2;
    } else {
      actor.fbPhaseSlots[0] = 3;
      s.drillCueVariant = DRILL_X.SOUND_DEFAULT;
      if (s.drillRobotVariant === 1) {
        s.drillCueVariant = DRILL_X.SOUND_VARIANT_ALT;
      }
      ctx.onPlayCue?.(actor, s.drillCueVariant);
      s.drillHitCount = hitCount + 1;
    }
  }
}

// Phase 3 — FUN_800d8470: Contact → spawn child. Hit → advance to 4.
function drillPhase3(actor: RomActor, ctx: DrillFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, DRILL_X.STREAM_GROUP);

  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    const ok = ctx.onAllocateResource?.(actor, 0, 1) ?? false;
    if (ok) {
      ctx.onDrillProjectile?.(actor);
    }
  }

  if (actor.wallContact) {
    actor.fbPhaseSlots[0] = 4;
    s.drillCueVariant = DRILL_X.SOUND_DEFAULT;
    if (s.drillRobotVariant !== 1) {
      s.drillCueVariant = DRILL_X.SOUND_DEFAULT;
    }
    ctx.onPlayCue?.(actor, s.drillCueVariant);
  }
}

// Phase 4 — FUN_800d8538: Spin‑down animation + stream + exit on hit confirm.
function drillPhase4(actor: RomActor, ctx: DrillFamilyCtx): void {
  const s = scratchOf(actor);
  // Spin‑down short animation fields 0x18e0 / 0x18e2 by decay factor.
  s.spinField0 = toS16(Math.trunc((s.spinField0 ?? 0) * DRILL_X.SPIN_DECAY));
  s.spinField1 = toS16(Math.trunc((s.spinField1 ?? 0) * DRILL_X.SPIN_DECAY));

  ctx.onTickStream?.(actor, DRILL_X.STREAM_GROUP);

  if (actor.wallContact) {
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor);
  }
}

function createDrillXHandler(ctx: DrillFamilyCtx): (actor: RomActor) => void {
  return (actor) => {
    const s = scratchOf(actor);
    if (s.drillFailFlag) {
      s.drillFailFlag = false;
    }
    switch (actor.fbPhaseSlots[0]) {
      case 0: drillPhase0(actor, ctx); break;
      case 1: drillPhase1(actor, ctx); break;
      case 2: drillPhase2(actor, ctx); break;
      case 3: drillPhase3(actor, ctx); break;
      case 4: drillPhase4(actor, ctx); break;
    }
  };
}

export function createDrillRootAction(ctx: DrillFamilyCtx): (actor: RomActor) => void {
  const xHandler = createDrillXHandler(ctx);
  return (actor) => {
    if (actor.actionIndex === 2) {
      xHandler(actor);
    }
  };
}

export function configureDrillFamily(
  actor: RomActor,
  _borgId: "pl0401",
  ctx: DrillFamilyCtx,
): void {
  actor.borgNumber = 0x401;
  actor.rootAction = createDrillRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
