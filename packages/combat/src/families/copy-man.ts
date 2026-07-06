// COPY MAN family (ctor 0x8015613c) — bespoke X-special port.
// Covers the three borgs sharing this ctor:
//   pl0806 COPY MAN        (0x806)
//   pl0809 WALKING BOMB    (0x809)
//   pl080f DEATH BORG OMICRON (0x80f)
// Source:
//   research/decomp/ghidra-export/chunk_0040.c:1215 (X-special wrapper FUN_80156460)
//   chunk_0040.c:1229 (phase 0 setup FUN_801564b0)
//   chunk_0040.c:1268 (phase 1 active/hit FUN_801565cc)
//   chunk_0040.c:1313 (phase 2 recovery FUN_801566f0)
//
// The X-special is a 3-phase ammo-gated borg-switched child deploy:
//   phase 0 (FUN_801564b0): yaw snapshot, zero velocity, integrate physics (gravity 1.0),
//     ground collide; start stream group 4 slot 0 (ground) / 1 (air), rate -1.0.
//   phase 1 (FUN_801565cc): tick stream, ground collide; on contact (+0x1cef==1 &&
//     +0x1cf0==1): borg-switched child spawn:
//       0x809 (WALKING BOMB)    → zz_00c4704_(actor, 1, &+0x144) — bomb deploy
//       0x806 (COPY MAN)        → zz_01639c0_(actor, 0) — copy-child spawn
//       0x80f (DEATH BORG OMICRON) → zz_01639c0_(actor, 1) — copy-child variant
//   phase 2 (FUN_801566f0): tick stream, ground collide; stream-end or variant-1 collide
//     → clear action bits, zero velocity, return to idle.
//
// Float constants read from boot.dol this session:
//   FLOAT_8043a5f0 = 0.0   (hSpeed/hDecel zero-out)
//   FLOAT_8043a5f4 = 1.0   (physics integrator gravity param)
//   FLOAT_8043a5f8 = -1.0  (stream playback rate)
//   FLOAT_8043a5fc = 4.0   (variant-1 air-exit cooldown seed)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

export const COPY_MAN_X = {
  ZERO: 0.0,
  GRAVITY: 1.0,
  STREAM_RATE: -1.0,
  AIR_EXIT_COOLDOWN: 4.0,
  ACTION_MODE_BITS: 0x3,
  BOMB_SPAWNER_ADDR: 0x80c4704,
  COPY_SPAWNER_ADDR: 0x801639c0,
} as const;

function spawnForBorg(borgNumber: number): { addr: number; type: number } {
  switch (borgNumber) {
    case 0x809: return { addr: COPY_MAN_X.BOMB_SPAWNER_ADDR, type: 1 };
    case 0x806: return { addr: COPY_MAN_X.COPY_SPAWNER_ADDR, type: 0 };
    case 0x80f: return { addr: COPY_MAN_X.COPY_SPAWNER_ADDR, type: 1 };
    default: return { addr: COPY_MAN_X.COPY_SPAWNER_ADDR, type: 0 };
  }
}

function isAirborne(actor: RomActor): boolean {
  const grounded = (actor as RomActor & { grounded?: boolean }).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

export interface CopyManFamilyCtx extends StreamContext {}

function copyManXPhase0(actor: RomActor, ctx: CopyManFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;
  actor.activeYaw = actor.lockYaw;
  actor.hDecel = COPY_MAN_X.ZERO;
  actor.hSpeed = COPY_MAN_X.ZERO;
  actor.gravityCoeff = COPY_MAN_X.ZERO;
  integratePhysics(COPY_MAN_X.GRAVITY, actor, actor.activeYaw);
  const slot = isAirborne(actor) ? 1 : 0;
  startStream(actor, 0xf, 4, slot, COPY_MAN_X.STREAM_RATE);
  actor.streamSlot = slot + 1;
  void ctx;
}

function copyManXPhase1(actor: RomActor, ctx: CopyManFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  integratePhysics(COPY_MAN_X.GRAVITY, actor, actor.activeYaw);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    actor.fbPhaseSlots[0] = 2;
    const { addr, type } = spawnForBorg(actor.borgNumber);
    ctx.onFamilyProjectile?.(actor, addr, type);
  }
}

function copyManXPhase2(actor: RomActor, ctx: CopyManFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  integratePhysics(COPY_MAN_X.GRAVITY, actor, actor.activeYaw);
  const variant = (actor as RomActor & { variantIndex?: number }).variantIndex ?? 0;
  const streamEnded = (actor as RomActor & { streamEnded?: number }).streamEnded ?? 0;
  if (streamEnded !== 0) {
    actor.hDecel = COPY_MAN_X.ZERO;
    actor.hSpeed = COPY_MAN_X.ZERO;
    actor.controlWord = actor.controlWord & ~COPY_MAN_X.ACTION_MODE_BITS;
    dispatchUpperBodyCue(actor, 7);
    dispatchFullBodyCue(actor, 0);
  }
  void variant;
}

const X_PHASE_TABLE = [copyManXPhase0, copyManXPhase1, copyManXPhase2];

function copyManXHandler(actor: RomActor, ctx: CopyManFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

export function createCopyManRootAction(
  ctx: CopyManFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,
    null,
    (actor) => copyManXHandler(actor, ctx),
    null,
    null,
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

export function configureCopyManFamily(
  actor: RomActor,
  borgId: "pl0806" | "pl0809" | "pl080f",
  ctx: CopyManFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0806" ? 0x806 :
    borgId === "pl0809" ? 0x809 : 0x80f;
  actor.rootAction = createCopyManRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
