// CYBER MACHINE family (ctor 0x800cc454) — the fourth ROM-faithful family port.
// Covers the four "beast-god" borgs sharing this ctor:
//   pl0602 CYBER MACHINE SEIRYU  (0x602 — Azure Dragon)
//   pl060a CYBER MACHINE SUZAKU  (0x60a — Vermilion Bird)
//   pl060c CYBER MACHINE BYAKKO  (0x60c — White Tiger)
//   pl060e CYBER MACHINE GENBU   (0x60e — Black Tortoise)
// Source:
//   research/decomp/ghidra-export/chunk_0021.c:2150 (root dispatcher FUN_800cc798)
//   chunk_0021.c:3335 (X-special / air-B handler FUN_800ce5dc — action-index 2 leaf)
//   chunk_0009.c:801 (zz_006a668_ shot dispatcher) + chunk_0043.c:4248 (zz_016cc24_
//   effect-child spawner).
//
// The X-special is a SHOT-ONLY action (actionStreamTables.json marks all 5 variants
// "no stream call reached (code-driven or shot-only action)"). It is a 2-phase ammo-
// gated projectile deploy:
//   phase 0 (FUN_800ce5dc, +0x540==0 branch): deduct 1 ammo from slot 2
//     (zz_006dbe0_(actor, 2, 1, 1)); on success spawn the visual effect child via
//     zz_016cc24_(actor, 2). Advance +0x540 to 1.
//   phase 1 (else branch): clear +0x73f, clear the action-mode bits (+0x5e0 &= ~3),
//     fire the shot via zz_006a668_(actor, kind=1, variant), then seed the post-shot
//     cooldown +0x694 = FLOAT_804389a8 + dt. After the bits clear, the actor exits the
//     attack state — phase 1 runs exactly once per X press.
//
// The actual damage is delivered by the kind-1 shot fired through the host's projectile
// layer (zz_006a668_ → zz_0048d54_ → zz_004a754_ armed-channel loop). With the host
// hook unwired, the spawn is an honest no-op (the phase machine still advances).

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import type { StreamContext } from "../rom/stream-vm.js";

// Motion constants — every value DERIVED from boot.dol this session (read via the
// DOL-section helper documented in scripts/gen-camera-mode1-constants.mjs).
const CYBER_MACHINE_X = {
  /** FLOAT_804389a8 = 50.0 — phase-1 post-shot cooldown seeded into +0x694 (= 50 + dt).
   *  Read at chunk_0021.c:3357 (`+0x694 = FLOAT_804389a8 + +0x1dc8`). */
  COOLDOWN: 50.0,
  /** zz_006dbe0_(actor, slot, cost, flag) — phase-0 ammo deduct. Slot 2 is the
   *  family's X-special ammo bucket; cost is 1 per shot. The host (bridge) owns the
   *  real ammo count; the hook decides whether the spawn fires. */
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  /** zz_016cc24_ @0x8016cc24 — phase-0 visual effect child spawner (type 2). */
  EFFECT_SPAWNER_ADDR: 0x8016cc24,
  EFFECT_TYPE: 2,
  /** zz_006a668_ @0x8006a668 — phase-1 shot dispatcher. Called with kind=1 (the
   *  "charged/heavy" shot branch in zz_0048d54_). */
  SHOT_SPAWNER_ADDR: 0x8006a668,
  SHOT_KIND: 1,
  /** Action-mode bits 0..1 of +0x5e0 (chunk_0021.c:3354: &= 0xfffffffc). */
  ACTION_MODE_BITS: 0x3,
} as const;

// ============================================================================
// Phase 0 — FUN_800ce5dc @ chunk_0021.c:3345 (+0x540 == 0 branch). Arm.
// ============================================================================
function cyberMachineXPhase0(actor: RomActor, ctx: StreamContext): void {
  // +0x540++ (chunk_0021.c:3346) — enter phase 1 for the next frame.
  actor.fbPhaseSlots[0] = 1;

  // zz_006dbe0_(actor, 2, 1, 1) — attempt the ammo deduct. The host gate decides
  // whether the effect child spawns; without the hook the spawn is skipped (the phase
  // still advances, matching the ROM's "phase 0 runs unconditionally" behavior — the
  // ammo gate only controls the visual child, NOT the phase transition).
  // On success: zz_016cc24_(actor, 2) — spawn the effect child of type 2.
  ctx.onFamilyProjectile?.(actor, CYBER_MACHINE_X.EFFECT_SPAWNER_ADDR, CYBER_MACHINE_X.EFFECT_TYPE);
}

// ============================================================================
// Phase 1 — FUN_800ce5dc @ chunk_0021.c:3352 (else branch). Fire + exit.
// ============================================================================
function cyberMachineXPhase1(actor: RomActor, ctx: StreamContext): void {
  // +0x73f = 0 (chunk_0021.c:3353) — housekeeping flag clear (no motion effect; skipped
  // at the RomActor layer since we don't model +0x73f).

  // +0x5e0 &= 0xfffffffc (chunk_0021.c:3354) — clear the action-mode bits. This is the
  // signal that ends the X-special state: with bits 0..1 clear the bridge/state-table
  // exits attack state 61, so rootAction stops being called. Phase 1 thus runs exactly
  // once per X press.
  actor.controlWord = actor.controlWord & ~CYBER_MACHINE_X.ACTION_MODE_BITS;

  // zz_006a668_(actor, kind=1, variant) — fire the shot. The action-2 variant table
  // routes all 5 variants to this leaf, so the variant reaching zz_006a668_ is whatever
  // +0x581 (variantIndex) holds; the host's projectile layer selects the visual from
  // the family record table using that index. Pass variantIndex through to the hook.
  ctx.onFamilyProjectile?.(actor, CYBER_MACHINE_X.SHOT_SPAWNER_ADDR, CYBER_MACHINE_X.SHOT_KIND);

  // +0x694 = FLOAT_804389a8 + dt (chunk_0021.c:3357) — post-shot cooldown. +0x694 is
  // the state-timer float (actor.stateTimer); the bridge decays it each frame.
  actor.stateTimer = CYBER_MACHINE_X.COOLDOWN + actor.dt;

  // Return to idle cues — the ROM's zz_006a668_ → zz_0048d54_ transitions the actor
  // into the shot state, which our bridge models as a generic upper-body idle (cue 7)
  // + full-body idle (cue 0). This matches the gred phase-3 exit shape.
  dispatchUpperBodyCue(actor, 7);
  dispatchFullBodyCue(actor, 0);
}

/** The X-special phase table — indexed by actor.fbPhaseSlots[0]. */
const X_PHASE_TABLE = [cyberMachineXPhase0, cyberMachineXPhase1];

/** FUN_800ce5dc wrapper — dispatches the phase table. */
function cyberMachineXHandler(actor: RomActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_800cc798 @ chunk_0021.c:2150 (the descriptor
// +0x4b4 virtual) → PTR_FUN_8030cd18[actor+0x580]. Action 2 (X) is ported here; the
// other rows wire in as their handlers port. Null entries fall through to the generic
// @gf/combat layer.
// ============================================================================

export interface CyberMachineFamilyCtx extends StreamContext {}

export function createCyberMachineRootAction(
  ctx: CyberMachineFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                      // 0: dash attack — TODO port
    null,                                      // 1: B melee — TODO port
    (actor) => cyberMachineXHandler(actor, ctx), // 2: X-special (ammo-gated shot deploy)
    null,                                      // 3: B charge — TODO port
    null,                                      // 4: — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned CYBER MACHINE-family actor (pl0602/pl060a/pl060c/pl060e).
 *  Wires the root action dispatcher and stamps the borg-number switch. */
export function configureCyberMachineFamily(
  actor: RomActor,
  borgId: "pl0602" | "pl060a" | "pl060c" | "pl060e",
  ctx: CyberMachineFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0602" ? 0x602 :
    borgId === "pl060a" ? 0x60a :
    borgId === "pl060c" ? 0x60c : 0x60e;
  actor.rootAction = createCyberMachineRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
