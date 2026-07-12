// Shared low-level actor helpers recovered from chunk_0008.c/chunk_0009.c.
// These keep family ports on the actual ROM contracts instead of host booleans.

import type { RomActor, Vec3 } from "./actor.js";
import type { StreamContext } from "./stream-vm.js";

export interface RomHelperScratch {
  lockTarget?: Vec3 | null;
  /** +0x18e0/+0x18e2: dual-axis aim accumulators used by zz_006ea9c_. */
  aimPitch18e0?: number;
  aimYaw18e2?: number;
  /** +0x1dfc: single-axis target-relative aim accumulator used by zz_006dee8_. */
  aimRoll1dfc?: number;
  /** +0x70: actor base pitch used by zz_006e848_. */
  basePitch70?: number;
  /** +0x1b03: stream/animation update enable. */
  streamTickEnabled?: boolean;
}

export function toS16(value: number): number {
  const u = Math.trunc(value) & 0xffff;
  return u >= 0x8000 ? u - 0x10000 : u;
}

export function targetDistance(actor: RomActor): number | null {
  const target = (actor as RomActor & RomHelperScratch).lockTarget;
  if (!target) return null;
  return Math.hypot(target.x - actor.pos.x, target.y - actor.pos.y, target.z - actor.pos.z);
}

function targetAngles(actor: RomActor): { yaw: number; pitch: number } | null {
  const target = (actor as RomActor & RomHelperScratch).lockTarget;
  if (!target) return null;
  const dx = target.x - actor.aimOrigin518.x;
  const dy = target.y - actor.aimOrigin518.y;
  const dz = target.z - actor.aimOrigin518.z;
  const horizontal = Math.hypot(dx, dz);
  return {
    yaw: toS16(Math.round(Math.atan2(dx, dz) / (Math.PI * 2) * 0x10000)),
    pitch: toS16(Math.round(Math.atan2(dy, horizontal) / (Math.PI * 2) * 0x10000)),
  };
}

export function targetPitchBam(actor: RomActor): number | null {
  return targetAngles(actor)?.pitch ?? null;
}

function turnStep(actor: RomActor, aimType: number): number {
  const index = aimType & 0xf;
  const raw = index === 0 ? actor.descriptor?.turnStep0 : actor.descriptor?.turnStep1;
  // Real roster actors receive both values from pl####data.bin. The fallback is only for
  // synthetic unit actors with no descriptor and matches the common 0x800 step.
  return Math.max(1, Math.abs(toS16(raw ?? 0x800)) * actor.dt);
}

/** Port of zz_006660c_ + FUN_800669d0/FUN_80066a30 for aim masks c0/c1/81. */
export function stepTargetYaw(
  actor: RomActor,
  aimType: number,
  offset = 0,
  preserveActiveYawOnTargetLoss = false,
): boolean {
  const angles = targetAngles(actor);
  // zz_006d0dc_ runs zz_006660c_, which clears a lost target and settles to the
  // current heading. zz_006d144_ instead rebuilds +0x5aa from the retained +0x5ac.
  const desired = angles
    ? toS16(angles.yaw - offset)
    : preserveActiveYawOnTargetLoss ? toS16(actor.activeYaw) : actor.heading;
  let error = toS16(desired - actor.heading);
  actor.activeYaw = desired;
  actor.turnErrorYaw = error;
  const step = turnStep(actor, aimType);
  let ready = false;
  if (Math.abs(error) <= step) {
    actor.heading = desired;
    actor.turnErrorYaw = 0;
    ready = true;
  } else {
    const delta = error < 0 ? -step : step;
    actor.heading = toS16(actor.heading + delta);
    error = toS16(error - delta);
    actor.turnErrorYaw = error;
  }
  if ((aimType & 0x40) !== 0) actor.lockYaw = actor.heading;
  if ((aimType & 0x80) !== 0) actor.heading = toS16(actor.heading);
  return ready;
}

/** Exact zz_006e514_(actor, aimType, out): descriptor-rate BAM16 pitch convergence.
 * Returns -1 without a target, 0 while converging, and 1 on exact settlement. */
export function stepTargetPitch(actor: RomActor, aimType: number, current: number): {
  value: number;
  result: -1 | 0 | 1;
} {
  const angles = targetAngles(actor);
  if (!angles) {
    return { value: toS16(Math.trunc(toS16(current) * 0.8999999761581421)), result: -1 };
  }
  const desired = Math.max(-0x4000, Math.min(0x4000,
    toS16(-toS16(actor.bodyPitch) - angles.pitch)));
  const descriptorRate = aimType & 0xf
    ? actor.descriptor?.turnStep1
    : actor.descriptor?.turnStep0;
  const step = toS16(Math.trunc(toS16(descriptorRate ?? 0) * actor.dt));
  const value = toS16(current);
  const diff = toS16(desired - value);
  if (Math.abs(diff) <= step) return { value: desired, result: 1 };
  return { value: toS16(value + (diff < 0 ? -step : step)), result: 0 };
}

/** zz_006e1ac_(actor, aimType, part=1): the +0x18da part-pitch channel uses
 * +0x768 rather than +0x1dc8 for its descriptor-rate step. The recovered host
 * target/aim-origin surface feeds the same signed BAM16 settle and target-loss rules. */
export function stepPartTargetPitch(actor: RomActor, aimType: number): -1 | 0 | 1 {
  const current = toS16(actor.steerYaw);
  const target = (actor as RomActor & RomHelperScratch).lockTarget;
  if (!target) {
    actor.steerYaw = toS16(Math.trunc(current * 0.8999999761581421));
    return -1;
  }
  // The renderer/world-cache owns +0x8e0/+0x8f0/+0x900. Until it supplies row 1,
  // unclassified handlers deterministically fall back to the actor root.
  const anchor = actor.partAimAnchors[1] ?? actor.pos;
  const dx = target.x - anchor.x;
  const dy = target.y - anchor.y;
  const dz = target.z - anchor.z;
  const pitch = toS16(Math.round(Math.atan2(dy, Math.hypot(dx, dz)) / (Math.PI * 2) * 0x10000));
  const desired = Math.max(-0x4000, Math.min(0x4000,
    toS16(-toS16(actor.bodyPitch) - pitch)));
  const descriptorRate = aimType & 0xf
    ? actor.descriptor?.turnStep1
    : actor.descriptor?.turnStep0;
  const step = toS16(Math.trunc(toS16(descriptorRate ?? 0) * actor.aimRateScale));
  const diff = toS16(desired - current);
  if (Math.abs(diff) <= step) {
    actor.steerYaw = desired;
    return 1;
  }
  actor.steerYaw = toS16(current + (diff < 0 ? -step : step));
  return 0;
}

/** Zero the exact signed animation/pose housekeeping triplet. */
export function resetPoseHousekeeping(actor: RomActor): void {
  actor.poseAccum80 = 0;
  actor.poseAccum7e = 0;
  actor.poseAccum7c = 0;
}

/** Port of zz_00b22f4_. Returns true exactly when the variant-1 trail child is emitted. */
export function stepAfterimage(actor: RomActor): boolean {
  let emit = true;
  if (actor.accumulator80c !== 0 && actor.accumulator80c < 8) {
    const distance = Math.hypot(
      actor.pos.x - actor.afterimageSamplePos.x,
      actor.pos.y - actor.afterimageSamplePos.y,
      actor.pos.z - actor.afterimageSamplePos.z,
    );
    emit = distance >= 100 * actor.modelScale * actor.sizeScale;
  }
  if (emit) {
    actor.accumulator80c = 0;
    actor.afterimageSamplePos.x = actor.pos.x;
    actor.afterimageSamplePos.y = actor.pos.y;
    actor.afterimageSamplePos.z = actor.pos.z;
    actor.afterimageSerial = (actor.afterimageSerial + 1) >>> 0;
  }
  actor.accumulator80c += actor.aimRateScale;
  return emit;
}

/** Port of zz_00679d0_: battle floor probe plus no-surface saved-position revert. */
export function groundSnapRevert(actor: RomActor): boolean {
  const floor = actor.physicsRuntime;
  if (!floor) return (actor as RomActor & { grounded?: boolean }).grounded === true;
  const supported = floor.isSupported?.(actor.pos.x, actor.pos.z) ?? true;
  if (!supported) {
    if ((actor.controlWord & 0x40) === 0) {
      actor.pos.x = actor.savedGroundPos.x;
      actor.pos.y = actor.savedGroundPos.y;
      actor.pos.z = actor.savedGroundPos.z;
    }
    (actor as RomActor & { grounded?: boolean }).grounded = false;
    return false;
  }
  const result = floor.clampToGround(actor.pos, actor.yVel);
  actor.pos.y = result.y;
  actor.yVel = result.velY;
  (actor as RomActor & { grounded?: boolean }).grounded = result.grounded;
  return result.grounded;
}

/** Port of zz_006ea9c_: independently converge +0x18e0 pitch and +0x18e2 yaw. */
export function stepDualTargetAim(actor: RomActor): number {
  const scratch = actor as RomActor & RomHelperScratch;
  const angles = targetAngles(actor);
  if (!angles) return -1;
  const step = turnStep(actor, 1);
  const desiredPitch = Math.max(-0x2000,
    Math.min(0x2000, toS16(-(scratch.basePitch70 ?? 0) - angles.pitch)));
  const desiredYaw = toS16(angles.yaw - actor.heading);
  const approach = (current: number, desired: number): [number, boolean] => {
    const diff = toS16(desired - current);
    if (Math.abs(diff) <= step) return [desired, true];
    return [toS16(current + (diff < 0 ? -step : step)), false];
  };
  const [pitch, pitchReady] = approach(toS16(scratch.aimPitch18e0 ?? 0), desiredPitch);
  const [yaw, yawReady] = approach(toS16(scratch.aimYaw18e2 ?? 0), desiredYaw);
  scratch.aimPitch18e0 = pitch;
  scratch.aimYaw18e2 = yaw;
  return pitchReady && yawReady ? 1 : 0;
}

/** Port of zz_006dee8_: clamp target-relative yaw to ±0x4000 and converge +0x1dfc
 * by exactly 0x800 BAM units per call. Returns -1 invalid, 0 moving, 1 ready. */
export function stepTargetRoll(actor: RomActor, clearInvalidTarget = true): number {
  const scratch = actor as RomActor & RomHelperScratch;
  const angles = targetAngles(actor);
  if (!angles) return -1;
  const raw = toS16(angles.yaw - actor.heading);
  if (raw <= -0x4801 || raw >= 0x4801) {
    if (clearInvalidTarget) scratch.lockTarget = null;
    scratch.aimRoll1dfc = toS16((scratch.aimRoll1dfc ?? 0) * 0.5);
    return -1;
  }
  const desired = Math.max(-0x4000, Math.min(0x4000, raw));
  const current = toS16(scratch.aimRoll1dfc ?? 0);
  const diff = desired - current;
  if (diff > 0x800) {
    scratch.aimRoll1dfc = toS16(current + 0x800);
    return 0;
  }
  if (diff < -0x800) {
    scratch.aimRoll1dfc = toS16(current - 0x800);
    return 0;
  }
  scratch.aimRoll1dfc = desired;
  return 1;
}

/** Exact zz_006dbe0_ host contract: check a weapon cell, optionally consume it. */
export function allocateWeapon(
  actor: RomActor,
  ctx: StreamContext,
  weaponIndex: number,
  count = 1,
  consume = true,
): boolean {
  return ctx.onAllocateResource?.(actor, weaponIndex, count, consume ? 1 : 0) ?? true;
}

export function isStreamTickEnabled(actor: RomActor): boolean {
  const explicit = (actor as RomActor & RomHelperScratch).streamTickEnabled;
  if (explicit !== undefined) return explicit;
  return actor.parts.some((part) => part.streamPtr >= 0);
}

export function partState(actor: RomActor, part: number): number {
  return actor.parts[part]?.stateByte ?? 0;
}

export function partStreamEnded(actor: RomActor, part = 0): boolean {
  return (actor.parts[part]?.streamPtr ?? -1) < 0;
}
