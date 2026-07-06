// JELLY DIVER family (ctor 0x80114838) — bespoke X-special port.
// Covers the three borgs sharing this ctor:
//   pl0805 JELLY DIVER (0x805)
//   pl080d TAR DIVER   (0x80d)
//   pl080e JACK        (0x80e)
// Source:
//   research/decomp/ghidra-export/chunk_0031.c:3373 (X-special wrapper FUN_80116808)
//   chunk_0031.c:3387 (phase 0 setup FUN_80116854)
//   chunk_0031.c:3427 (phase 1 active/hit/exit FUN_80116944)
//   chunk_0031.c:3487 (phase 2 recovery FUN_80116bc8 — FX/charge, not ported)
//
// The X-special is a 2-phase ammo-gated borg-switched child deploy:
//   phase 0 (FUN_80116854): yaw snapshot, velocity zero/scale by variant, start stream
//     group 4 slot 0, integrate physics (gravity 1.0), ground collide.
//   phase 1 (FUN_80116944): tick stream, on contact (+0x1cef > 0): deduct ammo slot 2,
//     on success spawn the borg-switched child via zz_01213bc_(actor, type). Borg switch:
//       0x805 → type 0, 0x80d → type 2, 0x80e → type 1.
//     On stream end (+0x1cee != 0): clear action bits, zero velocity, return to idle.
//
// Float constants read from boot.dol this session (dumped via DOL-section helper):
//   FLOAT_80439750 = 0.0   (hSpeed/hDecel/gravityCoeff zero-out)
//   FLOAT_80439770 = 1.0   (physics integrator gravity param)
//   FLOAT_8043977c = -1.0  (stream playback rate)
//   FLOAT_80439780 = 0.95  (variant-1 velocity multiplier)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

export const JELLY_DIVER_X = {
  ZERO: 0.0,
  GRAVITY: 1.0,
  STREAM_RATE: -1.0,
  VEL_MULT: 0.95,
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  ACTION_MODE_BITS: 0x3,
  CHILD_SPAWNER_ADDR: 0x80113bc,
} as const;

function childTypeForBorg(borgNumber: number): number {
  switch (borgNumber) {
    case 0x805: return 0;
    case 0x80d: return 2;
    case 0x80e: return 1;
    default: return 0;
  }
}

export interface JellyDiverFamilyCtx extends StreamContext {}

function jellyDiverXPhase0(actor: RomActor, ctx: JellyDiverFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;
  actor.activeYaw = actor.lockYaw;
  actor.streamSlot = 0;
  const variant = (actor as RomActor & { variantIndex?: number }).variantIndex ?? 0;
  if (variant === 0) {
    actor.hDecel = JELLY_DIVER_X.ZERO;
    actor.hSpeed = JELLY_DIVER_X.ZERO;
  } else {
    actor.hSpeed *= JELLY_DIVER_X.VEL_MULT;
    actor.hDecel *= JELLY_DIVER_X.VEL_MULT;
  }
  actor.yVel *= JELLY_DIVER_X.VEL_MULT;
  actor.gravityCoeff = JELLY_DIVER_X.ZERO;
  integratePhysics(JELLY_DIVER_X.GRAVITY, actor, actor.activeYaw);
  startStream(actor, 0xf, 4, 0, JELLY_DIVER_X.STREAM_RATE);
  actor.streamSlot = 1;
  void ctx;
}

function jellyDiverXPhase1(actor: RomActor, ctx: JellyDiverFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    ctx.onFamilyProjectile?.(actor, JELLY_DIVER_X.CHILD_SPAWNER_ADDR, childTypeForBorg(actor.borgNumber));
  }
  integratePhysics(JELLY_DIVER_X.GRAVITY, actor, actor.activeYaw);
  const streamEnded = (actor as RomActor & { streamEnded?: number }).streamEnded ?? 0;
  if (streamEnded !== 0) {
    actor.hDecel = JELLY_DIVER_X.ZERO;
    actor.hSpeed = JELLY_DIVER_X.ZERO;
    actor.controlWord = actor.controlWord & ~JELLY_DIVER_X.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7);
    dispatchFullBodyCue(actor, 0);
  }
}

const X_PHASE_TABLE = [jellyDiverXPhase0, jellyDiverXPhase1];

function jellyDiverXHandler(actor: RomActor, ctx: JellyDiverFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

export function createJellyDiverRootAction(
  ctx: JellyDiverFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,
    null,
    (actor) => jellyDiverXHandler(actor, ctx),
    null,
    null,
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

export function configureJellyDiverFamily(
  actor: RomActor,
  borgId: "pl0805" | "pl080d" | "pl080e",
  ctx: JellyDiverFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0805" ? 0x805 :
    borgId === "pl080d" ? 0x80d : 0x80e;
  actor.rootAction = createJellyDiverRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
