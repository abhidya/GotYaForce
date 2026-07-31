// EAGLE JET (pl061b) code-driven action-1 handler.
//
// ROM chain:
//   ctor 0x8012ae74 -> root FUN_8012b14c -> action[1] FUN_8012b458
//   research/decomp/ghidra-export/chunk_0034.c:1712-1860
//
// All five command variants for action 1 resolve directly to FUN_8012b458; there is
// no stream or phase table. The move holds state for 45 frames, then exits through
// zz_006a53c_(actor, 0x10): cooldown=16+dt, clear action bits, full-body cue 0x1b.

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import type { StreamContext } from "../rom/stream-vm.js";
import {
  tryStepFun8012b458,
  type GeneratedEagleJetActor,
  type GeneratedEagleJetHost,
} from "../generated/oghidra/fn_8012b458.generated.js";
import { OGHIDRA_PROMOTED_PORTS } from "../generated/oghidra/promotion-registry.generated.js";

export const EAGLE_JET_ACTION1 = {
  DURATION: 45.0,          // FLOAT_80439d80 (DOL-read)
  TIMER_FLOOR: 0.0,       // FLOAT_80439d7c
  FX_MODE: 0x83,          // actor+0x6e8, written every tick
  HITBOX_KIND: 0x7f,      // zz_00107a0_(actor, 0x7f)
  SOUND_CUE: 0x20,        // zz_00f036c_(actor, 0x20)
  EXIT_COOLDOWN: 0x10,    // zz_006a53c_ parameter
  EXIT_CUE: 0x1b,         // zz_006a53c_ -> zz_006a6fc_(actor, 0x1b)
  PREPARED_PARTS: [4, 5] as const, // zz_016c7ec_(actor, 4/5, 0) for borg 0x61b
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
}

export function createEagleJetAction1Reference(ctx: StreamContext): (actor: RomActor) => void {
  return (actor: RomActor): void => {
    const a = actor as RomActor & EagleJetScratch;
    a.effectMode6e8 = EAGLE_JET_ACTION1.FX_MODE;

    if ((actor.fbPhaseSlots[0] ?? 0) === 0) {
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = EAGLE_JET_ACTION1.DURATION;
      a.retiredHitboxKind = EAGLE_JET_ACTION1.HITBOX_KIND;
      a.preparedPartSlots = EAGLE_JET_ACTION1.PREPARED_PARTS;
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
  const action1 = createEagleJetAction1(ctx);
  actor.borgNumber = 0x61b;
  actor.rootAction = (a: RomActor): void => {
    if (a.actionIndex === 1) action1(a);
  };
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
