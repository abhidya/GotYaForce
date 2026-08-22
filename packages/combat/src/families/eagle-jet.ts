// EAGLE JET (pl061b) code-driven handlers — action 0 (aimed dual shot) + action 1.
// @audit-ported pl061b action=0 variants=0,1,2,3,4
//
// ROM chain:
//   ctor 0x8012ae74 -> root FUN_8012b14c -> action[0] FUN_8012b188
//                                          -> action[1] FUN_8012b458
//   research/decomp/ghidra-export/chunk_0034.c:1712-1860
//
// ACTION 0 — FUN_8012b188 @chunk_0034.c:1723, a single-function machine (no phase
// table). On first entry (+0x540 == 0) seeds +0x558 = 10.0. Each tick computes the
// target yaw from +0x518−pos; while the target sits inside the ±0x2001 facing cone it
// seeks the two turret-pivot channels (+0x197a/+0x1980, clamped ±0x1000, 0.96 decay),
// decrements +0x558, and returns while +0x558 > 0. Once the timer expires OR the
// target leaves the cone it refreshes visibility, runs the weapon-cell cost gate
// (consume) and spawns the borg-switched dual shot via zz_00c3be0_ (0x607 →
// {0x20,0x21}; 0x61b → {0x53,0x54}), then exits zz_006a53c_(0x10).
//
// All five command variants for action 1 resolve directly to FUN_8012b458; there is
// no stream or phase table. The move holds state for 45 frames, then exits through
// zz_006a53c_(actor, 0x10): cooldown=16+dt, clear action bits, full-body cue 0x1b.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon, toS16 } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";
import {
  tryStepFun8012b458,
  type GeneratedEagleJetActor,
  type GeneratedEagleJetHost,
} from "../generated/oghidra/fn_8012b458.generated.js";
import { OGHIDRA_PROMOTED_PORTS } from "../generated/oghidra/promotion-registry.generated.js";

/** Action-0 machine constants — every value read from boot.dol (sdata2
 *  @0x80439d68.., r2-relative with r2=0x8043ea20). */
export const EAGLE_JET_ACTION0 = {
  /** FLOAT_80439d78 = 10.0 — +0x558 seed (the aim window). */
  AIM_WINDOW: 10.0,
  /** FLOAT_80439d7c = 0.0 — timer expiry compare. */
  ZERO: 0.0,
  /** FLOAT_80439d68 = 0.96 — turret-pivot channel decay when out of the cone. */
  PIVOT_DECAY: 0.96,
  /** DOUBLE_80439d70 = 176.0 — s16→float coercion sentinel (unused in port). */
  COERCION_BASE: 176.0,
  /** +0x72 facing-cone half-width for the aim gate (±0x2001). */
  CONE_HALF: 0x2001,
  /** turret-pivot clamp ±0x1000 (both channels). */
  PIVOT_CLAMP: 0x1000,
  /** Exit kind passed to zz_006a53c_; also the +0x694 cooldown it writes. */
  EXIT_KIND: 0x10,
  /** zz_006a53c_ dispatches zz_006a6fc_(actor, 0x1b) -- a LITERAL. The +0x5e4
   *  read belongs to a different helper (zz_006a668_, chunk_0009.c:830). */
  EXIT_CUE: 0x1b,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
} as const;

/** Effect spawner zz_00c3be0_ @0x800c3be0 — kind-2 effect child (+0x10 = 2,
 *  +0x11 = type). ACTION-0 dual-shot type pairs by borg. */
export const EAGLE_JET_SHOT_SPAWNER = 0x800c3be0;

export const EAGLE_JET_ACTION1 = {
  DURATION: 45.0,          // FLOAT_80439d80 (DOL-read)
  TIMER_FLOOR: 0.0,       // FLOAT_80439d7c
  FX_MODE: 0x83,          // actor+0x6e8, written every tick
  HITBOX_KIND: 0x7f,      // zz_00107a0_(actor, 0x7f)
  SOUND_CUE: 0x20,        // zz_00f036c_(actor, 0x20)
  EXIT_COOLDOWN: 0x10,    // zz_006a53c_ parameter
  EXIT_CUE: 0x1b,         // zz_006a53c_ -> zz_006a6fc_(actor, 0x1b)
  /** zz_016c7ec_ slots by borg (chunk_0034.c:1837-1844). An unmatched borg gets
   *  NO call, so its previous slots must be left alone rather than overwritten. */
  PREPARED_PARTS_607: [1, 2] as const,
  PREPARED_PARTS: [4, 5] as const, // borg 0x61b
} as const;

/** Port-side mirrors for ROM fields/helpers not yet first-class on RomActor. */
export interface EagleJetScratch {
  /** actor+0x6e8 effect/action mode byte. */
  effectMode6e8?: number;
  /** actor+0x73f housekeeping byte cleared by zz_006a53c_. */
  housekeeping73f?: number;
  /** Records the two part slots reset by zz_016c7ec_; renderer/part host may consume it. */
  preparedPartSlots?: readonly number[];
  /** Hitbox kinds retired through zz_00107a0_; the bridge hitbox host may consume it. */
  retiredHitboxKind?: number;
  /** +0x197a/+0x1980 turret-pivot channels written by action-0's aim. */
  ejPivotL197a?: number;
  ejPivotR1980?: number;
  /** +0x5e8 lock target (aimed-shot machines). */
  lockTarget?: { x: number; y: number; z: number } | null;
}

function pivotChannelTarget(actor: RomActor): number | null {
  const target = (actor as RomActor & EagleJetScratch).lockTarget;
  if (!target) return null;
  return Math.round((Math.atan2(target.x - actor.pos.x, target.z - actor.pos.z) / (Math.PI * 2)) * 0x10000);
}

/** ACTION 0 — FUN_8012b188 @chunk_0034.c:1723. Aimed dual shot. */
function eagleJetAction0(actor: RomActor, ctx: StreamContext): void {
  const s = actor as RomActor & EagleJetScratch;

  // On first entry: +0x540 = 1, +0x558 = 10.0 (aim window).
  if (actor.fbPhaseSlots[0] === 0) {
    actor.fbPhaseSlots[0] = 1;
    actor.handlerTimer = EAGLE_JET_ACTION0.AIM_WINDOW;
  }

  // Facing gate: `(short)(yawToTarget) - heading` inside ±0x2001.
  const targetYaw = pivotChannelTarget(actor);
  const cone =
    targetYaw === null ? 0 : toS16(toS16(targetYaw - actor.heading));
  // chunk_0034.c:1746 is `(sVar2 < 0x2001) && (-0x2001 < sVar2)` -- strict on
  // both sides, so the accepted range is [-0x2000, 0x2000]. Inclusive bounds
  // kept aiming at exactly +/-0x2001, where the ROM drops out of the cone.
  const inCone =
    targetYaw !== null && cone > -EAGLE_JET_ACTION0.CONE_HALF && cone < EAGLE_JET_ACTION0.CONE_HALF;

  if (inCone) {
    // Seek the two turret-pivot channels toward the target bearing (zz_017a6e0_ on
    // +0x1978/+0x197e), clamped ±0x1000; out-of-cone decay 0.96. The exact per-part
    // matrix reads (+0x8dc/+0xdf0/+0xe20 rows) are host-facing renderer state —
    // modeled as cone+decay on the branch-relevant channels (labeled approximation).
    const desired = toS16(targetYaw - actor.heading);
    for (const key of ["ejPivotL197a", "ejPivotR1980"] as const) {
      const cur = s[key] ?? 0;
      const delta = Math.max(-EAGLE_JET_ACTION0.PIVOT_CLAMP, Math.min(EAGLE_JET_ACTION0.PIVOT_CLAMP, toS16(desired - cur)));
      s[key] = toS16(cur + delta);
    }

    // +0x558 -= dt; return while the aim window is still open.
    actor.handlerTimer -= actor.dt;
    if (actor.handlerTimer > EAGLE_JET_ACTION0.ZERO) return;
  }

  // Fire + exit: zz_006bf80_ refresh, weapon-cell cost gate (consume) → borg-switched
  // zz_00c3be0_ dual shot (0x607 → {0x20,0x21}; 0x61b → {0x53,0x54}), then
  // zz_006a53c_(0x10).
  if (allocateWeapon(actor, ctx, 0, 1, true)) {
    const types: readonly [number, number] = actor.borgNumber === 0x607 ? [0x20, 0x21] : [0x53, 0x54];
    ctx.onFamilyProjectile?.(actor, EAGLE_JET_SHOT_SPAWNER, types[0]);
    ctx.onFamilyProjectile?.(actor, EAGLE_JET_SHOT_SPAWNER, types[1]);
  }
  // zz_006a53c_(actor, 0x10), chunk_0009.c:752-765. The parameter is positive,
  // so +0x694 is written first, then the common cleanup, then the literal cue.
  // Action 1 already does this; action 0 skipped the timer and passed ubCue.
  actor.stateTimer = EAGLE_JET_ACTION0.EXIT_KIND + actor.dt;
  actor.housekeeping73f = 0;
  actor.controlWord &= ~EAGLE_JET_ACTION0.ACTION_MODE_BITS;
  dispatchFullBodyCue(actor, EAGLE_JET_ACTION0.EXIT_CUE);
}

export function createEagleJetAction1Reference(ctx: StreamContext): (actor: RomActor) => void {
  return (actor: RomActor): void => {
    const a = actor as RomActor & EagleJetScratch;
    a.effectMode6e8 = EAGLE_JET_ACTION1.FX_MODE;

    if ((actor.fbPhaseSlots[0] ?? 0) === 0) {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = EAGLE_JET_ACTION1.DURATION;
      a.retiredHitboxKind = EAGLE_JET_ACTION1.HITBOX_KIND;
      if (actor.borgNumber === 0x607) {
        a.preparedPartSlots = EAGLE_JET_ACTION1.PREPARED_PARTS_607;
      } else if (actor.borgNumber === 0x61b) {
        a.preparedPartSlots = EAGLE_JET_ACTION1.PREPARED_PARTS;
      }
      ctx.onPlayCue?.(actor, EAGLE_JET_ACTION1.SOUND_CUE);
      return;
    }

    actor.handlerTimer -= actor.dt;
    if (actor.handlerTimer > EAGLE_JET_ACTION1.TIMER_FLOOR) return;

    // zz_006a53c_(actor, 0x10): the integer parameter is positive, so +0x694 is
    // written before the common cleanup and cue dispatch.
    actor.stateTimer = EAGLE_JET_ACTION1.EXIT_COOLDOWN + actor.dt;
    a.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    dispatchFullBodyCue(actor, EAGLE_JET_ACTION1.EXIT_CUE);
  };
}

function createEagleJetAction1Generated(ctx: StreamContext): (actor: RomActor) => void {
  return (actor: RomActor): void => {
    const scratch = actor as RomActor & EagleJetScratch;
    const generatedActor: GeneratedEagleJetActor = {
      borgNumber: actor.borgNumber,
      phase: actor.fbPhaseSlots[0] ?? 0,
      timer: actor.handlerTimer,
      dt: actor.dt,
      effectMode: scratch.effectMode6e8 ?? 0,
      cooldown: actor.stateTimer,
      housekeeping: scratch.housekeeping73f ?? 0,
      controlWord: actor.controlWord,
    };
    const prepared: number[] = [];
    const host: GeneratedEagleJetHost = {
      retireHitbox(_generatedActor, kind) {
        scratch.retiredHitboxKind = kind;
      },
      playCue(_generatedActor, cue) {
        ctx.onPlayCue?.(actor, cue);
      },
      preparePart(_generatedActor, slot) {
        prepared.push(slot);
      },
      dispatchFullBodyCue(_generatedActor, cue) {
        dispatchFullBodyCue(actor, cue);
        generatedActor.phase = actor.fbPhaseSlots[0] ?? 0;
      },
    };

    tryStepFun8012b458(generatedActor, host);
    actor.fbPhaseSlots[0] = generatedActor.phase;
    actor.handlerTimer = generatedActor.timer;
    actor.stateTimer = generatedActor.cooldown;
    actor.controlWord = generatedActor.controlWord;
    scratch.effectMode6e8 = generatedActor.effectMode;
    scratch.housekeeping73f = generatedActor.housekeeping;
    if (prepared.length > 0) scratch.preparedPartSlots = prepared;
  };
}

export function createEagleJetAction1(ctx: StreamContext): (actor: RomActor) => void {
  return OGHIDRA_PROMOTED_PORTS["0x8012b458"]
    ? createEagleJetAction1Generated(ctx)
    : createEagleJetAction1Reference(ctx);
}

export function configureEagleJetFamily(actor: RomActor, ctx: StreamContext): void {
  const action0 = eagleJetAction0;
  const action1 = createEagleJetAction1(ctx);
  actor.borgNumber = 0x61b;
  actor.rootAction = (a: RomActor): void => {
    if (a.actionIndex === 0) action0(a, ctx);
    else if (a.actionIndex === 1) action1(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — action 0 aimed dual shot (mirror the tank-module style).
// ============================================================================

type AssertFn = (cond: boolean, msg: string) => void;

export function runEagleJetAction0SelfTests(assert: AssertFn): void {
  console.log("\n[eagle-jet.selfcheck] pl061b action 0 — aimed dual shot (FUN_8012b188):");

  {
    const shots: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
      onAllocateResource: () => true,
    };
    const a = createRomActor() as RomActor & EagleJetScratch;
    a.actionIndex = 0;
    a.borgNumber = 0x61b;
    a.controlWord = 0x3;
    a.dt = 1;
    a.heading = 0;
    a.pos = { x: 0, y: 0, z: 0 };
    a.lockTarget = { x: 0, y: 0, z: 100 }; // target ahead (+z, heading 0) → yaw 0, inside cone
    const ej0 = createEagleJetAction0ForTest(ctx);
    ej0(a);
    assert(a.fbPhaseSlots[0] === 1, "action-0 init advances +0x540");
    assert(a.handlerTimer === 9.0, "action-0 seeds +0x558 = 10.0 then decrements (9.0)");
    assert(shots.length === 0, "action-0 in-cone aim does not fire");

    // Drain the 10-frame window → fire the 0x53/0x54 dual shot + exit.
    for (let i = 0; i < 8; i += 1) ej0(a);
    assert(shots.length === 0, "action-0 still aiming at timer 1");
    ej0(a);
    assert(shots.length === 2, "action-0 fires the dual shot on timer expiry");
    assert(shots[0]!.addr === EAGLE_JET_SHOT_SPAWNER && shots[0]!.type === 0x53,
      "action-0 shot[0] = EFFECT_SPAWNER type 0x53 (borg 0x61b)");
    assert(shots[1]!.addr === EAGLE_JET_SHOT_SPAWNER && shots[1]!.type === 0x54,
      "action-0 shot[1] = EFFECT_SPAWNER type 0x54 (borg 0x61b)");
    assert((a.controlWord & EAGLE_JET_ACTION0.ACTION_MODE_BITS) === 0,
      "action-0 exit strips action-mode bits");
  }

  {
    const shots: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
      onAllocateResource: () => true,
    };
    const a = createRomActor() as RomActor & EagleJetScratch;
    a.actionIndex = 0;
    a.borgNumber = 0x607;
    a.controlWord = 0x3;
    a.dt = 1;
    a.heading = 0;
    a.pos = { x: 0, y: 0, z: 0 };
    a.lockTarget = { x: 0, y: 0, z: 100 }; // target ahead → yaw 0, inside cone
    const ej0 = createEagleJetAction0ForTest(ctx);
    for (let i = 0; i < 11; i += 1) ej0(a);
    assert(shots[0]!.type === 0x20 && shots[1]!.type === 0x21,
      "action-0 borg 0x607 fires the 0x20/0x21 pair");
  }
}

/** Internal re-export for tests — avoids double-configure side effects. */
function createEagleJetAction0ForTest(ctx: StreamContext): (actor: RomActor) => void {
  return (actor: RomActor) => eagleJetAction0(actor, ctx);
}
