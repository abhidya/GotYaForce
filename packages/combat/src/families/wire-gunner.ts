// WIRE GUNNER family (ctor 0x801301f8) — bespoke X-special port.
// Covers the three borgs sharing this ctor:
//   pl0103 WIRE GUNNER   (0x103)
//   pl0106 TIME BOMBER   (0x106)
//   pl0107 REMOTE BOMBER (0x107)
// Source:
//   research/decomp/ghidra-export/chunk_0034.c:4956 (root dispatcher FUN_80130788
//   → action table PTR_FUN_80335cb8[+0x580])
//   chunk_0035.c:578 (X-special wrapper FUN_80131688 → zz_01316e0_ phase machine
//   @ chunk_0035.c:601)
//   chunk_0006.c:1431 (zz_004beb8_ stream arm) + chunk_0006.c:2014 (zz_004cd24_
//   stream tick) + chunk_0009.c:801 (zz_006a668_ shot dispatcher).
//
// The X-special (actionIndex 2) is a BESPOKE 2-phase shot deploy. actionStreamTables
// marks pl0107's action-2 leaf 0x80131688 engine=null (the engine is the family code
// block, NOT a shared-engine range). The machine is a direction-gated aim→fire:
//   phase 0 ground/air-no-target (zz_01316e0_:609-625): advance +0x540 to 1, pick the
//     aim slot off the control-word direction bits (default slot 2, side 0x10 → slot 4,
//     up 0x40 → slot 3), then startStream(mask, group=4, slot) via zz_004beb8_.
//   phase 0 air-with-target (zz_01316e0_:626-635): clear +0x73f, clear action-mode bits
//     (+0x5e0 &= ~3), fire shot kind=4 via zz_006a668_, seed post-shot cooldown
//     +0x694 = dt + (s16(+0x1af8) − +0x1ae0) — the per-borg data-page cooldown pair,
//     approximated here by the stateTimer decay the bridge already runs.
//   phase 1+ (zz_01316e0_:637-645): zz_004cd24_(actor, 1) stream tick; on contact
//     (+0x1cee ≠ 0) clear bits and fire shot kind=30 (0x1e) via zz_006a668_.
//
// The actual damage is delivered by the kind-4/kind-30 shot fired through the host's
// projectile layer (zz_006a668_ → zz_0048d54_ → zz_004a754_ armed-channel loop). With
// the host hook unwired, the spawn is an honest no-op (the phase machine still advances).
//
// Float/stream constants (FLOAT_80439e90 stream rate read from boot.dol this session):
//   FLOAT_80439e90 = -1.0  (zz_004beb8_ playback rate — default-speed stream arm)

import type { RomActor } from "../rom/actor.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";

/** Every value DERIVED from boot.dol / chunk_0035.c this session. */
export const WIRE_GUNNER_X = {
  /** FLOAT_80439e90 = -1.0 — zz_004beb8_ stream playback rate (default speed). */
  STREAM_RATE: -1.0,
  /** zz_006a668_ @0x8006a668 — shot dispatcher (chunk_0009.c:801). Called with
   *  kind=4 (phase-0 air-target fire) or kind=30 (phase-1 contact fire). The host
   *  projectile layer resolves the record; without the hook the spawn is skipped. */
  SHOT_SPAWNER_ADDR: 0x8006a668,
  /** Shot kind for phase-0 air-with-target branch (zz_01316e0_:629). */
  SHOT_KIND_AIR: 4,
  /** Shot kind for phase-1 contact branch (zz_01316e0_:642). */
  SHOT_KIND_GROUND: 0x1e,
  /** Stream arm group (zz_01316e0_:624 — zz_004beb8_ group param). */
  STREAM_GROUP: 4,
  /** Aim slots indexed by the control-word direction bits (zz_01316e0_:616-622). */
  SLOT_DEFAULT: 2, // neutral/down — +0x6ea = 2
  SLOT_UP: 3,      // controlWord & 0x40 → +0x6ea = 3
  SLOT_SIDE: 4,    // controlWord & 0x10 → +0x6ea = 4
  /** Control-word bit masks (the +0x5e0 action/status word). */
  AIR_BIT: 0x20,        // air-status bit (phase-0 air-target gate)
  SIDE_BIT: 0x10,       // side-input bit (slot select)
  UP_BIT: 0x40,         // up-input bit (slot select)
  ACTION_MODE_BITS: 0x3, // bits 0..1 cleared on fire to exit attack state
} as const;

/** Resolve the aim stream slot from the control-word direction bits.
 *  Port of zz_01316e0_:616-622 (`+0x6ea = 2; if(&0x10) =4; if(&0x40) =3`).
 *  Up takes precedence over side (the ROM checks 0x10 first, then 0x40 overrides). */
function aimSlotFor(actor: RomActor): number {
  let slot: number = WIRE_GUNNER_X.SLOT_DEFAULT;
  if ((actor.controlWord & WIRE_GUNNER_X.SIDE_BIT) !== 0) slot = WIRE_GUNNER_X.SLOT_SIDE;
  if ((actor.controlWord & WIRE_GUNNER_X.UP_BIT) !== 0) slot = WIRE_GUNNER_X.SLOT_UP;
  return slot;
}

/** Resolve the stream-arm part mask. Port of zz_01316e0_:612-615
 *  (`+0x543 = 1; if +0x5db == 1 → +0x543 = 0xf`). +0x5db is the upper-body state;
 *  state 1 widens the arm to all parts (full-body aim pose). */
function armMaskFor(actor: RomActor): number {
  return actor.ubState === 1 ? 0xf : 0x1;
}

export interface WireGunnerFamilyCtx extends StreamContext {}

// ============================================================================
// Phase 0 — zz_01316e0_ @ chunk_0035.c:609-635 (+0x540 == 0 branch). Arm or air-fire.
// ============================================================================
function wireGunnerXPhase0(actor: RomActor, ctx: WireGunnerFamilyCtx): void {
  // Air-with-target gate: `(controlWord & 0x20) != 0 && contactP0 != 0` (zz_01316e0_:611
  // inverted — the else branch). On air + acquired target, skip the arm and fire
  // immediately. contactP0 is +0x1cef (part-0 contact flag).
  const airWithTarget =
    (actor.controlWord & WIRE_GUNNER_X.AIR_BIT) !== 0 && actor.contactP0 !== 0;

  if (airWithTarget) {
    // +0x73f = 0 (zz_01316e0_:627) — housekeeping flag clear (unsurfaced; no-op).
    // +0x5e0 &= ~3 (zz_01316e0_:628) — clear action-mode bits → exits attack state 61.
    actor.controlWord = actor.controlWord & ~WIRE_GUNNER_X.ACTION_MODE_BITS;
    // zz_006a668_(actor, kind=4) — fire the air shot (zz_01316e0_:629).
    ctx.onFamilyProjectile?.(actor, WIRE_GUNNER_X.SHOT_SPAWNER_ADDR, WIRE_GUNNER_X.SHOT_KIND_AIR);
    // +0x694 cooldown (zz_01316e0_:631-634) = dt + (s16(+0x1af8) − +0x1ae0). The
    // per-borg data-page pair (+0x1af8/+0x1ae0) isn't surfaced; the bridge's
    // stateTimer decay already models the cooldown window, so we seed dt to keep the
    // exit-decision shape (stateTimer > 0 ⇒ still in recovery).
    actor.stateTimer = actor.dt;
    // Idle cues — mirrors cyber-machine's fire-exit dispatch shape.
    dispatchUpperBodyCue(actor, 7);
    dispatchFullBodyCue(actor, 0);
    return;
  }

  // Ground / air-no-target ARM branch (zz_01316e0_:610-625).
  // +0x540 = 1 — enter phase 1 for the next frame.
  actor.fbPhaseSlots[0] = 1;

  // +0x6ea = direction-resolved slot (zz_01316e0_:616-622 writes the cursor itself).
  const slot = aimSlotFor(actor);
  actor.streamSlot = slot;

  // zz_004beb8_(rate, actor, mask, group=4, slot, -1, -1) — start the aim stream.
  startStream(actor, armMaskFor(actor), WIRE_GUNNER_X.STREAM_GROUP, slot, WIRE_GUNNER_X.STREAM_RATE);
}

// ============================================================================
// Phase 1+ — zz_01316e0_ @ chunk_0035.c:637-645 (else branch). Tick + contact fire.
// ============================================================================
function wireGunnerXPhase1(actor: RomActor, ctx: WireGunnerFamilyCtx): void {
  // zz_004cd24_(actor, 1) — tick the aim stream (part-0 mask=1).
  tickStream(actor, 0x1, ctx);

  // +0x1cee contact gate — wallContact != 0 means the shot acquired a target.
  if (actor.wallContact !== 0) {
    // +0x73f = 0 (zz_01316e0_:640) — housekeeping flag clear (unsurfaced; no-op).
    // +0x5e0 &= ~3 (zz_01316e0_:641) — clear action-mode bits → exits attack state 61.
    actor.controlWord = actor.controlWord & ~WIRE_GUNNER_X.ACTION_MODE_BITS;
    // zz_006a668_(actor, kind=30) — fire the ground shot (zz_01316e0_:642).
    ctx.onFamilyProjectile?.(actor, WIRE_GUNNER_X.SHOT_SPAWNER_ADDR, WIRE_GUNNER_X.SHOT_KIND_GROUND);
    // Idle cues — the shot fires and the actor returns to neutral.
    dispatchUpperBodyCue(actor, 7);
    dispatchFullBodyCue(actor, 0);
  }
}

/** The X-special phase table — indexed by actor.fbPhaseSlots[0]. */
const X_PHASE_TABLE = [wireGunnerXPhase0, wireGunnerXPhase1];

/** FUN_80131688 wrapper — dispatches the phase table. */
function wireGunnerXHandler(actor: RomActor, ctx: WireGunnerFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_80130788 @ chunk_0034.c:4956 (the descriptor
// +0x4b4 virtual) → PTR_FUN_80335cb8[actor+0x580]. Action 2 (X) is ported here; the
// other rows wire in as their handlers port. Null entries fall through to the generic
// @gf/combat layer.
// ============================================================================

export function createWireGunnerRootAction(
  ctx: WireGunnerFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                       // 0: dash attack (FUN_801307c4) — TODO port
    null,                                       // 1: B melee (FUN_80131598) — TODO port
    (actor) => wireGunnerXHandler(actor, ctx),  // 2: X-special (direction-gated shot deploy)
    null,                                       // 3: wire grab (FUN_80131834) — TODO port
    null,                                       // 4: — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned WIRE GUNNER-family actor (pl0103/pl0106/pl0107).
 *  Stamps the borg-number switch the shot dispatcher reads and wires the root action. */
export function configureWireGunnerFamily(
  actor: RomActor,
  borgId: "pl0103" | "pl0106" | "pl0107",
  ctx: WireGunnerFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0103" ? 0x103 :
    borgId === "pl0106" ? 0x106 : 0x107;
  actor.rootAction = createWireGunnerRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
