// Bespoke B-melee engine zz_010c220_ @0x8010c220 — the STANDING 4-phase melee machine
// shared by 12 "girl"/"death-borg-delta" borgs (variant 1 of action 1). Source:
//   research/decomp/ghidra-export/chunk_0030.c:1695 (dispatcher zz_010c220_)
//   chunk_0030.c:1709 (phase 0 setup FUN_8010c270)
//   chunk_0030.c:1740 (phase 1 pre-active FUN_8010c354)
//   chunk_0030.c:1774 (phase 2 active FUN_8010c43c)
//   chunk_0030.c:1807 (phase 3 recovery FUN_8010c508)
//
// The dispatcher is structurally identical to the shared melee zz_0177dd8_ (the
// `if (+0x541) +0xcc=0; PTR_FUN_<phaseTable>[+0x540]()` shape) but references a
// DISTINCT phase table PTR_FUN_80325a98 whose handlers are bespoke to this cluster.
// Differences from shared-melee-gred:
//   - NO combo chain (phase 3 is a straight recovery, no +0x1cf0/+0x746 loop-back).
//   - Phase 2 sets +0x541=0xff on the proximity transition (re-arms the air-clear).
//   - Phase 1 derives hSpeed from the +0x868 row / +0x764 current-speed scalar.
//
// Borgs covered (action 1 variant 1): pl0300, pl0301, pl0302, pl0304, pl0305, pl0307,
// pl0308, pl0309, pl030a, pl030b, pl030c, pl030d.
//
// Float constants (FLOAT_804395xx bank, DOL-read):
//   FLOAT_8043956c = timer seed (phase 0 +0x558)
//   FLOAT_80439568 = active-window timer (phase 1 transition writes this)
//   FLOAT_80439558 = 0.0 floor / zero scalar
//   FLOAT_80439554 = -1.0 stream rate
//   FLOAT_8043955c = active-frame decel
//   FLOAT_80439580 = proximity range (FUN_80066838 gate)
//   FLOAT_80439560 = speed threshold (zz_00b22f4_ gate)
//   FLOAT_80439540 = recovery decel

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { computeLungeSpeed } from "./shared-engine.js";

export const MELEE_GIRL_STANDING = {
  TIMER_SEED: 60.0,     // FLOAT_8043956c
  ACTIVE_TIMER: 30.0,   // FLOAT_80439568
  STREAM_RATE: -1.0,    // FLOAT_80439554
  TIMER_FLOOR: 0.0,     // FLOAT_80439558
  DECEL: 1.0,           // FLOAT_8043955c (default 1.0 = no decel)
  RECOVERY_DECEL: 1.0,  // FLOAT_80439540
  PROXIMITY: 100.0,     // FLOAT_80439580
  SPEED_THRESHOLD: 0.0, // FLOAT_80439560
  STREAM_GROUP: 3,
  PART_MASK: 0xf,
  STATE_FACE: 0xc0,
} as const;

export interface MeleeGirlStandingConfig {
  seedSlot?: number;
  activeTimer?: number;
}

interface MeleeScratch {
  bRetapInput?: boolean;
  altInputPresent?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
}

function targetDistance(actor: RomActor & MeleeScratch): number | null {
  const t = actor.lockTarget;
  if (!t) return null;
  return Math.hypot(t.x - actor.pos.x, t.z - actor.pos.z);
}

// Phase 0 — FUN_8010c270 @ chunk_0030.c:1709.
function phase0(actor: RomActor & MeleeScratch, cfg: Required<MeleeGirlStandingConfig>): void {
  actor.fbPhaseSlots[0] += 1;
  actor.streamSlot = cfg.seedSlot;
  // Air-check FUN_80066838(+0x868 row, actor): airborne → +0x541=1, +0xcc=0, yaw→heading.
  if (!actor.grounded) {
    actor.activeYaw = actor.heading;
    actor.lockYaw = actor.heading;
  } else {
    actor.activeYaw = actor.lockYaw;
  }
  actor.handlerTimer = MELEE_GIRL_STANDING.TIMER_SEED;
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(
    actor,
    MELEE_GIRL_STANDING.PART_MASK,
    MELEE_GIRL_STANDING.STREAM_GROUP,
    slot,
    MELEE_GIRL_STANDING.STREAM_RATE,
  );
}

// Phase 1 — FUN_8010c354 @ chunk_0030.c:1740.
function phase1(actor: RomActor & MeleeScratch, cfg: Required<MeleeGirlStandingConfig>): void {
  actor.handlerTimer -= actor.dt;
  const facingComplete = actor.lockTarget != null;
  if (actor.handlerTimer <= MELEE_GIRL_STANDING.TIMER_FLOOR || facingComplete) {
    actor.fbPhaseSlots[0] += 1;
    actor.handlerTimer = cfg.activeTimer;
    computeLungeSpeed(actor, cfg.activeTimer);
  }
}

// Phase 2 — FUN_8010c43c @ chunk_0030.c:1774.
function phase2(actor: RomActor & MeleeScratch, ctx: StreamContext): void {
  integratePhysics(0, actor, actor.activeYaw);
  if (actor.contactP0 === 0) {
    tickStream(actor, MELEE_GIRL_STANDING.PART_MASK, ctx);
  }
  actor.handlerTimer -= actor.dt;
  const dist = targetDistance(actor);
  const inProximity = dist !== null && dist <= MELEE_GIRL_STANDING.PROXIMITY;
  if (actor.handlerTimer <= MELEE_GIRL_STANDING.TIMER_FLOOR || (inProximity && !actor.altInputPresent)) {
    actor.fbPhaseSlots[0] += 1;
  }
}

// Phase 3 — FUN_8010c508 @ chunk_0030.c:1807.
function phase3(actor: RomActor & MeleeScratch, ctx: StreamContext): void {
  tickStream(actor, MELEE_GIRL_STANDING.PART_MASK, ctx);
  const decel = MELEE_GIRL_STANDING.RECOVERY_DECEL;
  if (decel !== 1.0) {
    actor.hSpeed *= decel;
    actor.yVel *= decel;
  }
  integratePhysics(0, actor, actor.activeYaw);
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    dispatchUpperBodyCue(actor, 0);
  }
}

export function createMeleeGirlStanding(
  ctx: StreamContext,
  cfg: MeleeGirlStandingConfig = {},
): (actor: RomActor) => void {
  const resolved: Required<MeleeGirlStandingConfig> = {
    seedSlot: cfg.seedSlot ?? 0,
    activeTimer: cfg.activeTimer ?? MELEE_GIRL_STANDING.ACTIVE_TIMER,
  };
  return (actor: RomActor) => {
    const a = actor as RomActor & MeleeScratch;
    switch (actor.fbPhaseSlots[0] ?? 0) {
      case 0: phase0(a, resolved); break;
      case 1: phase1(a, resolved); break;
      case 2: phase2(a, ctx); break;
      case 3: phase3(a, ctx); break;
      default: break;
    }
  };
}
