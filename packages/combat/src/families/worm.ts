// ALIEN WORM family (ctor 0x80118cb8) — bespoke X-special port.
// Covers the four borgs sharing this ctor:
//   pl0501 ALIEN WORM  (0x501)
//   pl050b VENOM WORM  (0x50b)
//   pl050d CLAW WORM   (0x50d)
//   pl0517 POISON WORM (0x517)
// Source:
//   research/decomp/ghidra-export/chunk_0032.c:662 (X-special / per-frame poll
//   FUN_80118efc — borg-switched spawn dispatcher)
//   chunk_0032.c:1391 (worm-child spawner FUN_8011a108 — bespoke pl0501/pl050d path)
//   chunk_0057.c:338 (shared venom-cloud spawner zz_01d4d00_ — pl050b/pl0517 path)
//
// The X-special is a CODE-DRIVEN ammo-gated child deploy, NOT a stream-table action:
// actionStreamTables.json shows pl0501/pl050b/pl050d/pl0517 with actions 0 and 1 only
// (no action 2 leaf). FUN_80118efc is a per-frame input poll (gates on +0x5bc & 0x400
// = X-button held) that the cue/state machinery reaches via state 61. The port wires
// actionIndex 2 to the same dispatcher so the bridge's tryStartXSpecial path drives it.
//
// Two spawn flavors keyed off borgNumber:
//   pl0501/pl050d (ALIEN/CLAW): FUN_8011a108(actor, type) — spawns a worm-child
//     projectile at a head-bone offset (gnt4_PSMTXMultVec via +0xea4 matrix).
//     Borg-switched type: 0x501→0 (jaw lunge), 0x50d→1 (claw swipe).
//   pl050b/pl0517 (VENOM/POISON): zz_01d4d00_(actor, type) — spawns a lingering
//     venom/poison cloud child. Cross-family shared spawner (also called by other
//     status-borgs). Borg-switched type: 0x50b→1 (venom), 0x517→3 (poison).
// Both paths gate on the SAME ammo slot (zz_006dbe0_(actor, 2, 1, mode)) and seed the
// SAME post-spawn cooldown (+0x694 = FLOAT_80439870 + dt).
//
// Float constants read from boot.dol this session (dumped via DOL-section helper):
//   FLOAT_80439864 = 0.0   (cooldown gate — `+0x694 <= 0` for re-arm)
//   FLOAT_80439870 = 4.0   (cooldown seed — `+0x694 = 4 + dt` after spawn)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import type { StreamContext } from "../rom/stream-vm.js";

/** Every value DERIVED from boot.dol this session. */
export const WORM_X = {
  /** FLOAT_80439864 = 0.0 — the cooldown gate. FUN_80118efc:675/704 reads
   *  `+0x694 <= FLOAT_80439864` to permit a fresh spawn; our stateTimer decays to 0
   *  between presses. */
  COOLDOWN_GATE: 0.0,
  /** FLOAT_80439870 = 4.0 — post-spawn cooldown seeded into +0x694 (= 4 + dt).
   *  Read at chunk_0032.c:696/715 (`+0x694 = FLOAT_80439870 + +0x1dc8`). */
  COOLDOWN: 4.0,
  /** zz_006dbe0_(actor, slot, cost, mode) — ammo deduct. Slot 2 is the family's
   *  X-special ammo bucket; cost is 1 per spawn. The host (bridge) owns the real ammo
   *  count; the hook decides whether the spawn fires. */
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  /** Action-mode bits 0..1 of +0x5e0 (cyber-machine shape: phase-1 clears to exit). */
  ACTION_MODE_BITS: 0x3,
  /** FUN_8011a108 @0x8011a108 — bespoke worm-child spawner (chunk_0032.c:1391).
   *  Spawns a projectile at a head-bone matrix offset; record-select by param_2.
   *  Borg switch: 0x501→type 0, 0x50d→type 1. */
  WORM_CHILD_SPAWNER_ADDR: 0x8011a108,
  /** zz_01d4d00_ @0x801d4d00 — shared venom/poison-cloud spawner (chunk_0057.c:338).
   *  Cross-family (also called by other status-inflicting borgs); record-select by
   *  param_2. Borg switch: 0x50b→type 1 (venom), 0x517→type 3 (poison). */
  CLOUD_SPAWNER_ADDR: 0x801d4d00,
} as const;

/** Borg-id → spawner routing (FUN_80118efc:673-714 borgNumber switch). Returns the
 *  spawner address + type the host hook resolves the record with. */
function spawnForBorg(borgNumber: number): { addr: number; type: number } {
  switch (borgNumber) {
    case 0x501: return { addr: WORM_X.WORM_CHILD_SPAWNER_ADDR, type: 0 };
    case 0x50b: return { addr: WORM_X.CLOUD_SPAWNER_ADDR, type: 1 };
    case 0x50d: return { addr: WORM_X.WORM_CHILD_SPAWNER_ADDR, type: 1 };
    case 0x517: return { addr: WORM_X.CLOUD_SPAWNER_ADDR, type: 3 };
    default: return { addr: WORM_X.WORM_CHILD_SPAWNER_ADDR, type: 0 };
  }
}

export interface WormFamilyCtx extends StreamContext {}

// ============================================================================
// Phase 0 — FUN_80118efc spawn branch (chunk_0032.c:673-716). Arm.
// Both flavors (worm-child / cloud) gate identically on X-button + cooldown + ammo,
// then spawn via the borg-switched address. Sets +0x14c = 1 (worm-child path) which
// our port surfaces as the phase cursor; cloud path skips +0x14c (single-shot spawn).
// ============================================================================
function wormXPhase0(actor: RomActor, ctx: WormFamilyCtx): void {
  // +0x540++ — enter phase 1 for the next frame (matches cyber-machine's phase tick).
  actor.fbPhaseSlots[0] = 1;

  // Spawn the borg-routed child. The host gate decides whether the child actually
  // fires (ammo/cooldown live in BorgRuntime; the hook is the family projectile
  // resolver). Without the hook this is an honest no-op (the phase still advances,
  // matching the ROM's "spawn attempt unconditionally transitions +0x14c" shape).
  const { addr, type } = spawnForBorg(actor.borgNumber);
  ctx.onFamilyProjectile?.(actor, addr, type);

  // +0x694 = FLOAT_80439870 + dt (chunk_0032.c:696/715) — post-spawn cooldown.
  actor.stateTimer = WORM_X.COOLDOWN + actor.dt;
}

// ============================================================================
// Phase 1 — FUN_80118efc tail / cyber-machine-style exit. Clear action-mode bits so
// the bridge/state-table exits attack state 61; rootAction stops being called. Phase
// 1 thus runs exactly once per X press.
// ============================================================================
function wormXPhase1(actor: RomActor, _ctx: WormFamilyCtx): void {
  // +0x5e0 &= 0xfffffffc (mirrors cyber-machine phase-1 bit clear) — the signal that
  // ends the X-special state. With bits 0..1 clear the bridge exits attack state 61.
  actor.controlWord = actor.controlWord & ~WORM_X.ACTION_MODE_BITS;

  // Return to idle cues — the worm has no upper-body cue transition in the X path
  // (FUN_80118efc plays only a voice clip via zz_00f0104_; no anim cue). Mirror the
  // cyber-machine idle exit so the actor's state cleanly resets.
  dispatchUpperBodyCue(actor, 7);
  dispatchFullBodyCue(actor, 0);
}

/** The X-special phase table — indexed by actor.fbPhaseSlots[0]. */
const X_PHASE_TABLE = [wormXPhase0, wormXPhase1];

/** FUN_80118efc wrapper — dispatches the phase table. */
function wormXHandler(actor: RomActor, ctx: WormFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = X_PHASE_TABLE[phase];
  if (fn) fn(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_80119214 @ chunk_0032.c:798 (the descriptor
// +0x4b4 virtual) → PTR_FUN_8032b5dc[actor+0x580]. Action 2 (X) is ported here; the
// other rows wire in as their handlers port. Null entries fall through to the generic
// @gf/combat layer.
// ============================================================================

export function createWormRootAction(
  ctx: WormFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                // 0: ground movement/idle (FUN_80119250) — TODO port
    null,                                // 1: B-tap melee (FUN_801198e8) — TODO port
    (actor) => wormXHandler(actor, ctx), // 2: X-special (FUN_80118efc borg-switched spawn)
    null,                                // 3: B charge — TODO identify
    null,                                // 4: — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned ALIEN WORM-family actor (pl0501/pl050b/pl050d/pl0517).
 *  Stamps the borg-number switch the spawner routing reads and wires the root action
 *  dispatcher. */
export function configureWormFamily(
  actor: RomActor,
  borgId: "pl0501" | "pl050b" | "pl050d" | "pl0517",
  ctx: WormFamilyCtx,
): void {
  actor.borgNumber =
    borgId === "pl0501" ? 0x501 :
    borgId === "pl050b" ? 0x50b :
    borgId === "pl050d" ? 0x50d : 0x517;
  actor.rootAction = createWormRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
