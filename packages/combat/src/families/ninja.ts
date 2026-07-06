// NORMAL NINJA family (ctor 0x8006f4f8) — the second ROM-faithful family port.
// Covers pl0000 (NORMAL NINJA) and pl000a (SASUKE): the ctor gives both the SAME
// vtable/anim banks/tables and differs ONLY in the +0x4b0 descriptor (0x802d3dc8 vs
// 0x802d3ee0), so one family module covers both. Source:
// research/decomp/nn-family-decode-2026-07-06.md (adversarially verified, 14/16 claims
// dual-confirmed + 2 constant corrections applied here from the verify pass).
//
// Root dispatcher FUN_8006facc @0x8006facc:
//   `(*(code *)(&PTR_FUN_802d3b68)[*(char *)(actor+0x580)])();`
// Action table PTR_FUN_802d3b68 @0x802d3b68 (5 entries):
//   [0] 0x8006fb08  B-tap ground/dash/air sword-combo driver   — TODO port
//   [1] 0x80070604  contextual-B lunge driver (borg-switched)  — TODO port
//   [2] 0x80071598  X-special driver                           — PORTED here
//   [3] 0x800716d8  X-charge dash — DEAD for pl0000/pl000a (descriptor +0xb8 modes
//       `01 00 01 ff ff ff`: command types 3/4/5 disabled; live only for pl0003)
//   [4] 0x80071a84  B-charge shuriken toss — DEAD for pl0000/pl000a (same gate; its
//       zz_0071ac0_ machine is reachable for SASUKE via action-1 variants 1/2)
//
// The X-special (actionIndex 2) delegates ALL 5 variants to the SHARED engine machine
// zz_00ff2bc_ (families/shared-x-special.ts) with the family config block @0x80433868:
// {ground slot 0, air slot 1, on-hit callback zz_00715f8_}. The callback is the ninja
// signature move: on connect, BACKFLIP away and throw a shuriken.

import type { RomActor } from "../rom/actor.js";
import type { StreamContext } from "../rom/stream-vm.js";
import { createSharedXSpecial, type SharedXConfig } from "./shared-x-special.js";

/** zz_00715f8_ @0x800715f8 constants — every value read from boot.dol. */
export const NINJA_X = {
  BACKFLIP_HSPEED: 10.0,  // FLOAT_80437748 → +0x44
  BACKFLIP_YVEL: 15.0,    // FLOAT_80437768 → +0x48 (vertical impulse)
  BACKFLIP_HDECEL: 0.0,   // FLOAT_804376e4 → +0x4c
  BACKFLIP_GRAVITY: -1.0, // FLOAT_804376e0 → +0x50 (gravity accel — NEGATIVE coefficient)
  /** Shuriken spawner zz_007db5c_ @0x8007db5c record-select by borgNumber (+0x3e8):
   *  borg 0x000 → type 0; borg 0x00a (SASUKE) → type 3. (DOUBLE NINJA borg 0x003 →
   *  types 1+2, not covered by this module's registration.) Table 0x802d6d68. */
  SHURIKEN_SPAWNER_ADDR: 0x8007db5c,
} as const;

/** Ground/air stream slots from the family X config block @0x80433868 (u16[0]/u16[1]). */
const NINJA_X_GROUND_SLOT = 0;
const NINJA_X_AIR_SLOT = 1;

function shurikenTypeFor(borgNumber: number): number {
  return borgNumber === 0x00a ? 3 : 0;
}

/**
 * The family on-hit callback zz_00715f8_ @0x800715f8 (cfg ptr[+4]), invoked by the
 * shared machine's phase-1 contact transition:
 *  (a) BACKFLIP — on the stream-event flag +0x1d0f: face away 180° (+0x5ae = +0x72 −
 *      0x8000) and set the launch scalars. Our decoded stream events don't surface
 *      +0x1d0f, so the backflip applies unconditionally on hit (the flag is armed by
 *      the same streams that arm the hit — labeled approximation).
 *  (b) SHURIKEN — ammo-gated (zz_006dbe0_ slot 2, cost 1; ammo is owned by BorgRuntime,
 *      surfaced through the host hook) spawn via zz_007db5c_(actor, typeByBorg).
 */
export function ninjaXOnHit(actor: RomActor, ctx: StreamContext): void {
  // (a) Backflip: +0x5ae = +0x72 − 0x8000 (face directly away), then the four scalars.
  actor.lockYaw = (actor.heading - 0x8000) & 0xffff;
  actor.activeYaw = actor.lockYaw;
  actor.hSpeed = NINJA_X.BACKFLIP_HSPEED;
  actor.hDecel = NINJA_X.BACKFLIP_HDECEL;
  actor.yVel = NINJA_X.BACKFLIP_YVEL;
  actor.gravityCoeff = NINJA_X.BACKFLIP_GRAVITY;
  // (b) Shuriken. The host resolves the family table (0x802d6d68) + ammo gate; when the
  // hook is unwired this is an honest no-op (the melee contact is the ported payload).
  ctx.onFamilyProjectile?.(actor, NINJA_X.SHURIKEN_SPAWNER_ADDR, shurikenTypeFor(actor.borgNumber));
}

export interface NinjaFamilyCtx extends StreamContext {}

export function createNinjaRootAction(ctx: NinjaFamilyCtx): (actor: RomActor) => void {
  const xConfig: SharedXConfig = {
    groundSlot: NINJA_X_GROUND_SLOT,
    airSlot: NINJA_X_AIR_SLOT,
    onHit: ninjaXOnHit,
  };
  const xSpecial = createSharedXSpecial(xConfig, ctx);
  // PTR_FUN_802d3b68 — null entries fall back to the existing generic @gf/combat logic.
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,     // 0: B-tap sword combo (FUN_8006fb08) — TODO port
    null,     // 1: contextual-B lunge (FUN_80070604) — TODO port
    xSpecial, // 2: X-special (zz_0071598_ → shared zz_00ff2bc_, cfg 0x80433868)
    null,     // 3: X-charge dash — command-disabled for this family's two borgs
    null,     // 4: B-charge toss — command-disabled for this family's two borgs
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned ninja-family actor (pl0000/pl000a). */
export function configureNinjaFamily(
  actor: RomActor,
  borgId: "pl0000" | "pl000a",
  ctx: NinjaFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl000a" ? 0x00a : 0x000;
  actor.rootAction = createNinjaRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
