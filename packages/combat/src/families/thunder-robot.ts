import type { RomActor } from "../rom/actor.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";

export const THUNDER_X = {
  STREAM_GROUP: 1,
  /** FLOAT_80438d70 = 60.0 — setup timer. */
  SETUP_TIMER: 60.0,
  /** FLOAT_80438d78 = 0.0 — timer floor. */
  TIMER_FLOOR: 0.0,
  /** FLOAT_80438d7c = 0.9 — spin-down decay factor. */
  SPIN_DECAY: 0.9,
  SOUND_DEFAULT: 1,
  SOUND_VARIANT_ALT: 0xf,
} as const;

export interface ThunderFamilyCtx {
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  /** Allocate resource (port of zz_006dbe0_). */
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
  /** Spawn child projectile for index 0-3 (port of zz_00e058c_). */
  onThunderChild?: (actor: RomActor, index: number) => boolean;
  /** Spawn FX (port of zz_00f036c_). */
  onSpawnFX?: (actor: RomActor, fxType: number) => void;
  /** Stream ticker (port of zz_004cd24_). */
  onTickStream?: (actor: RomActor, group: number) => void;
}

export interface ThunderXConfig {
  /** Minimum required resource count (+0x784). If <1, X-special fails. */
  minResourceCount: number;
}

const DEFAULT_THUNDER_CONFIG: ThunderXConfig = {
  minResourceCount: 1,
};

interface ThunderScratch {
  /** +0x541: fail flag. */
  thunderFailFlag?: boolean;
  /** +0x6ea: phase-internal hit counter (byte). */
  thunderHitCount?: number;
  /** +0x543: sound/cue variant. */
  thunderCueVariant?: number;
  /** +0x5db: robot variant (1 → alt cue). */
  thunderRobotVariant?: number;
  /** +0x18e2: spin-down animation short. */
  spinField?: number;
  /** +0x146[0..3]: per-child flags. */
  childFlags?: [number, number, number, number];
}

function scratchOf(actor: RomActor): RomActor & ThunderScratch {
  return actor as RomActor & ThunderScratch;
}

function toS16(v: number): number {
  let s = Math.trunc(v) & 0xffff;
  if (s >= 0x8000) s -= 0x10000;
  return s;
}

// Phase 0 — FUN_800e01c4: Setup timer + resource check + init + sound.
function thunderPhase0(actor: RomActor, cfg: ThunderXConfig, ctx: ThunderFamilyCtx): void {
  const s = scratchOf(actor);
  actor.handlerTimer = THUNDER_X.SETUP_TIMER;
  s.thunderHitCount = 0;

  if (cfg.minResourceCount < 1) {
    s.thunderFailFlag = true;
  }

  s.thunderCueVariant = THUNDER_X.SOUND_DEFAULT;
  if (s.thunderRobotVariant === 1) {
    s.thunderCueVariant = THUNDER_X.SOUND_VARIANT_ALT;
  }
  ctx.onPlayCue?.(actor, s.thunderCueVariant);
  s.thunderHitCount = (s.thunderHitCount ?? 0) + 1;

  actor.fbPhaseSlots[0] = 1;
}

// Phase 1 — FUN_800e0274: Wait for timer.
function thunderPhase1(actor: RomActor, ctx: ThunderFamilyCtx): void {
  ctx.onTickStream?.(actor, THUNDER_X.STREAM_GROUP);

  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= THUNDER_X.TIMER_FLOOR) {
    actor.fbPhaseSlots[0] = 2;
  }
}

// Phase 2 — FUN_800e02e0: Hit check → advance to 4 (ok) or 3 (fail).
function thunderPhase2(actor: RomActor, ctx: ThunderFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, THUNDER_X.STREAM_GROUP);

  if (actor.wallContact) {
    const ok = ctx.onAllocateResource?.(actor, 0, 1, 0) ?? false;
    const hitCount = s.thunderHitCount ?? 0;
    if (ok) {
      actor.fbPhaseSlots[0] = 4;
      s.thunderCueVariant = THUNDER_X.SOUND_DEFAULT;
      ctx.onPlayCue?.(actor, s.thunderCueVariant);
      s.thunderHitCount = hitCount + 1;
    } else {
      actor.fbPhaseSlots[0] = 3;
      s.thunderCueVariant = THUNDER_X.SOUND_DEFAULT;
      if (s.thunderRobotVariant === 1) {
        s.thunderCueVariant = THUNDER_X.SOUND_VARIANT_ALT;
      }
      ctx.onPlayCue?.(actor, s.thunderCueVariant);
      s.thunderHitCount = hitCount + 1;
    }
  }
}

// Phase 3 — FUN_800e03ec: Contact → spawn 4 children. Hit → advance to 4.
function thunderPhase3(actor: RomActor, ctx: ThunderFamilyCtx): void {
  const s = scratchOf(actor);
  ctx.onTickStream?.(actor, THUNDER_X.STREAM_GROUP);

  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    const ok = ctx.onAllocateResource?.(actor, 0, 1, 1) ?? false;
    if (ok) {
      ctx.onSpawnFX?.(actor, 0xeb);
      for (let i = 0; i < 4; i++) {
        if (s.childFlags) s.childFlags[i] = 1;
        ctx.onThunderChild?.(actor, i);
      }
    }
  }

  if (actor.wallContact) {
    actor.fbPhaseSlots[0] = 4;
    s.thunderCueVariant = THUNDER_X.SOUND_DEFAULT;
    if (s.thunderRobotVariant !== 1) {
      s.thunderCueVariant = THUNDER_X.SOUND_DEFAULT;
    }
    ctx.onPlayCue?.(actor, s.thunderCueVariant);
    s.thunderHitCount = (s.thunderHitCount ?? 0) + 1;
  }
}

// Phase 4 — FUN_800e04f8: Spin-down + exit.
function thunderPhase4(actor: RomActor, ctx: ThunderFamilyCtx): void {
  const s = scratchOf(actor);
  s.spinField = toS16(Math.trunc((s.spinField ?? 0) * THUNDER_X.SPIN_DECAY));

  ctx.onTickStream?.(actor, THUNDER_X.STREAM_GROUP);

  if (actor.wallContact) {
    s.thunderHitCount = 0;
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor);
  }
}

function createThunderXHandler(cfg: ThunderXConfig, ctx: ThunderFamilyCtx): (actor: RomActor) => void {
  return (actor) => {
    const s = scratchOf(actor);
    if (s.thunderFailFlag) {
      s.thunderFailFlag = false;
    }
    switch (actor.fbPhaseSlots[0]) {
      case 0: thunderPhase0(actor, cfg, ctx); break;
      case 1: thunderPhase1(actor, ctx); break;
      case 2: thunderPhase2(actor, ctx); break;
      case 3: thunderPhase3(actor, ctx); break;
      case 4: thunderPhase4(actor, ctx); break;
    }
  };
}

export function createThunderRootAction(
  ctx: ThunderFamilyCtx,
  cfg?: Partial<ThunderXConfig>,
): (actor: RomActor) => void {
  const config = { ...DEFAULT_THUNDER_CONFIG, ...cfg };
  const xHandler = createThunderXHandler(config, ctx);
  return (actor) => {
    if (actor.actionIndex === 2) {
      xHandler(actor);
    }
  };
}

export function configureThunderFamily(
  actor: RomActor,
  _borgId: "pl0404",
  ctx: ThunderFamilyCtx,
  cfg?: Partial<ThunderXConfig>,
): void {
  actor.borgNumber = 0x404;
  actor.rootAction = createThunderRootAction(ctx, cfg);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
