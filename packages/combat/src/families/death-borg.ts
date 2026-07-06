// DEATH BORG ALPHA family (ctor 0x8019e9a4 = zz_019e9a4_) — pl0008 (DEATH BORG ALPHA)
// and pl000c (DEATH BORG ALPHA II). Third family on the SHARED X machine zz_00ff2bc_
// (families/shared-x-special.ts), config block @0x80435750 = {groundSlot 0, airSlot 1,
// onHit zz_01a0458_}. Source: wave-a-shared-engines-digs-2026-07-06.json
// `fam-8019e9a4-ff2bc-config` — ALL 10 claims dual-lens verified (the one Wave-A dig
// whose verify pass completed before the session limit).
//
// COMMAND REACHABILITY (verified): descriptor +0xb8 mode bytes — pl0008 @0x80376698 =
// `01 00 ff ...` (X-special DISABLED, the whole action-2 path is dead code for it);
// pl000c @0x803767b0 = `01 00 01 ...` (X live). The port therefore registers ONLY
// pl000c; pl0008 keeps the generic fallback exactly as the ROM keeps it X-less.

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";

/** zz_01a0458_ @0x801a0458 constants — byte-identical backflip pop to ninja's callback
 *  (10/15/0/−1) from different literal-pool addresses (FLOAT_8043b51c/_8043b538/
 *  _8043b4d0/_8043b4cc, all DOL-read + verified). */
export const DEATH_BORG_X = {
  POP_HSPEED: 10.0,   // FLOAT_8043b51c → +0x44
  POP_YVEL: 15.0,     // FLOAT_8043b538 → +0x48
  POP_HDECEL: 0.0,    // FLOAT_8043b4d0 → +0x4c
  POP_GRAVITY: -1.0,  // FLOAT_8043b4cc → +0x50
  /** zz_007db5c_(actor, 5) — record 5 of the shot table 0x802d6d68 @0x802d6e80
   *  (texId 2, kind 1, bone 11, muzzle (55,0,0)); borg-gated s16+0x2e == 0xc. */
  SHURIKEN_SPAWNER_ADDR: 0x8007db5c,
  SHOT_TYPE: 5,
} as const;

/** The family on-hit callback zz_01a0458_: face-away pop (on the +0x1d0f stream-event
 *  gate — modeled unconditionally-on-hit like ninja.ts's precedent) + ammo-gated type-5
 *  shot for borg 0xc ONLY (pl0008 runs the ammo gate but spawns nothing — verified). */
export function deathBorgXOnHit(actor: RomActor, ctx: StreamContext): void {
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = DEATH_BORG_X.POP_HSPEED;
  actor.hDecel = DEATH_BORG_X.POP_HDECEL;
  actor.yVel = DEATH_BORG_X.POP_YVEL;
  actor.gravityCoeff = DEATH_BORG_X.POP_GRAVITY;
  if (actor.borgNumber === 0x00c) {
    ctx.onFamilyProjectile?.(actor, DEATH_BORG_X.SHURIKEN_SPAWNER_ADDR, DEATH_BORG_X.SHOT_TYPE);
  }
}

export function createDeathBorgRootAction(ctx: StreamContext): (actor: RomActor) => void {
  const xConfig: SharedXConfig = { groundSlot: 0, airSlot: 1, onHit: deathBorgXOnHit };
  const xSpecial = createSharedXSpecial(xConfig, ctx);
  // Root dispatcher zz_019edbc_ @0x8019edbc, action table @0x8037643c. Only action 2
  // (X, live for pl000c) is ported; others keep the generic fallback.
  const actionTable: Array<((actor: RomActor) => void) | null> = [null, null, xSpecial, null, null];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a DEATH BORG ALPHA II actor. Only pl000c registers (pl0008's X command is
 *  descriptor-disabled in the ROM — mode byte 0xff at +0xba). */
export function configureDeathBorgFamily(actor: RomActor, borgId: "pl000c", ctx: StreamContext): void {
  actor.borgNumber = 0x00c;
  actor.rootAction = createDeathBorgRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  void borgId;
}
