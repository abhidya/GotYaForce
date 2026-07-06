// CYBER DEATH DRAGON family (ctor 0x800b8188) — bespoke X-special port.
// Covers pl0503 (CYBER DEATH DRAGON), pl0506, pl0507, pl050f, pl0512, pl0513. Source:
// `research/decomp/ghidra-export/chunk_0018.c:3635-4419` (root dispatcher FUN_800b8a94
// @0x800b8a94 → action table PTR_FUN_802ff2fc → X-special chain FUN_800b9688 →
// variant table PTR_FUN_802ff3c4 → bespoke engines FUN_800b96c4 / FUN_800b9888 /
// FUN_800b9a74).
//
// The X-special (actionIndex 2) is a BESPOKE three-variant phase machine — the engine
// addresses live in the family code block (0x800b9xxx), NOT in the shared-engine
// ranges (0x80177xxx/0x80178xxx the majority of the roster tail-calls). It is the
// sister port of families/dragon.ts (FLAME DRAGON, ctor 0x80075658) — identical
// 3-variant breath structure (ground/air/charged), identical float constants (just
// at different .sdata2 slots), identical phase sequencing. Each variant is a
// directional breath:
//   v0 (ground):  stationary, g4 s0→s1, returns to ground idle (zz_006a474_).
//   v1 (air):     airborne w/ velocity drag + physics, g4 s2→s3, returns to air idle
//                 (zz_006a5a4_). 3× per-frame zz_0066e40_(0) steer samples in phase 1.
//   v2 (charged): conditional entry (+0x5dd == 0x11), physics, g4 s4→s5, transitions
//                 to upper-body cue 0x10 (a follow-up breath state, NOT idle).
//
// Difference vs FLAME DRAGON: the per-frame contact bookkeeping (zz_00b9c68_) does
// NOT spawn a borg-id-switched child (FLAME's zz_00be948_ flame-child spawner is
// absent). Instead, on +0x1cef contact it calls zz_0098dbc_(actor, 0, 6) — a shared
// kind-6 attack resolver already covered by the stream's op 0x0a armHit path (the
// breath hitbox is armed by startStream; zz_0098dbc_ is a redundant re-resolve). The
// host bridge wires op 0x0a → onArmHit; the zz_0098dbc_ tail is a labeled no-op here.
// zz_00b9c68_ also extends the breath window (+0x558) by the hit-stop frames
// returned from zz_006de44_(actor, 0xf0f00) — modeled as a labeled no-op (the
// hit-stop source byte is not surfaced in the actor struct).
//
// Float constants read from boot.dol this session (cyber-dragon-floats dump):
//   FLOAT_804384a4 = 0.0   (zero scalar)    FLOAT_804384e4 = 180.0 (breath window seed)
//   FLOAT_804384c8 = -1.0  (stream rate)    FLOAT_804384c4 = 0.95  (v1 velocity drag)
//   FLOAT_804384bc = 1.0   (physics gravity)

import type { RomActor } from "../rom/actor.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { dispatchUpperBodyCue, dispatchFullBodyCue } from "../rom/dispatch.js";

/** Every value read from boot.dol this session (cyber-dragon-floats dump). These
 *  mirror FLAME DRAGON's DRAGON_X table at FLOAT_80437814/24/2c/30/34 — the two
 *  families share identical phase-machine constants, just at different .sdata2 slots. */
export const CYBER_DRAGON_X = {
  ZERO: 0.0,            // FLOAT_804384a4 — base scalar (zeros launch vel / gravityCoeff)
  STREAM_RATE: -1.0,    // FLOAT_804384c8 — zz_004beb8_ playback rate
  GRAVITY: 1.0,         // FLOAT_804384bc — physics integration gravity (airborne phases)
  BREATH_WINDOW: 180.0, // FLOAT_804384e4 — phase-1 active-breath timer seed (+0x558)
  AIR_DRAG: 0.95,       // FLOAT_804384c4 — zz_006ed8c_ velocity scale (v1 per-frame)
} as const;

/** Phase-2 recovery floor — the ROM polls +0x1cee (stream-end) which our stream VM
 *  doesn't surface as an actor field; we approximate by counting down from the breath
 *  window and then clearing the attack state. The bridge's specialMaxFrames caps the
 *  total duration independently. */
const RECOVERY_FRAMES = 30;

export interface CyberDragonFamilyCtx extends StreamContext {}

/** Port of zz_00b9c68_ @ chunk_0018.c:4394 — per-frame contact bookkeeping shared by
 *  all three breath variants. Sets the stream-state byte, ticks the stream, and on a
 *  part-0 contact (+0x1cef) calls zz_0098dbc_(actor, 0, 6) — a shared kind-6 attack
 *  resolver. The breath's primary damage comes from the stream-armed hitbox (op 0x0a);
 *  zz_0098dbc_ is a redundant re-resolve, so the spawn is a labeled no-op here.
 *  (Compare FLAME DRAGON's zz_0076408_ which spawns a borg-id-switched flame child —
 *  the Cyber Death Dragon has no per-frame child spawner.) */
function cyberDragonContactBookkeeping(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  // +0x6f7 = 4 (stream-state byte for the breath FX; visual — not surfaced).
  tickStream(actor, 0xf, ctx);
  // +0x1cef contact flag — set by op 0x02 when the breath hitbox connects.
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0; // the ROM clears +0x1cef after consuming it.
    // zz_0098dbc_(actor, 0, 6) — shared kind-6 attack resolver; the stream's op 0x0a
    // armHit already covers damage, so this is a labeled no-op (see file header).
    void ctx;
  }
}

// ============================================================================
// Variant 0 — ground breath. Engine FUN_800b96c4 @ chunk_0018.c:4131 =
//   PTR_FUN_802ff3d8[+0x540]() (3 phases, NO per-frame physics — stationary).
// Phases: FUN_800b9700 (P0 setup) → FUN_800b9790 (P1 active) → FUN_800b9820 (P2 end).
// ============================================================================
function cyberDragonGroundPhase0(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++
  actor.handlerTimer = CYBER_DRAGON_X.BREATH_WINDOW; // +0x558 = 180.0
  // +0x54e = 0x78 (120 — part-anim blend; visual, not surfaced).
  // +0x548 = 0, +0x6ea = 0, +0x6f7 = 0 (breath cursor + stream-state seeds).
  actor.gravityCoeff = CYBER_DRAGON_X.ZERO; // +0x50 = 0.0
  actor.yVel = CYBER_DRAGON_X.ZERO;         // +0x48 = 0.0
  actor.hDecel = CYBER_DRAGON_X.ZERO;       // +0x4c = 0.0
  actor.hSpeed = CYBER_DRAGON_X.ZERO;       // +0x44 = 0.0
  // +0x80/+0x7e/+0x7c = 0 (u16 anim offsets; visual, not surfaced).
  startStream(actor, 0xf, 4, 0, CYBER_DRAGON_X.STREAM_RATE); // g4 s0 (FUN_800b9700:4168)
  void ctx;
}

function cyberDragonGroundPhase1(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  cyberDragonContactBookkeeping(actor, ctx); // zz_00b9c68_ + zz_0066e40_(0)
  // zz_0066e40_(actor, 0) is a heading-steer toward the target (reads +0x664 turn
  // speed, +0x4ac descriptor table) — unsurfaced fields; left as a labeled no-op.
  // The breath fires forward along the current heading.
  actor.handlerTimer -= actor.dt; // +0x558 -= +0x1dc8
  if (actor.handlerTimer <= CYBER_DRAGON_X.ZERO) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    startStream(actor, 0xf, 4, 1, CYBER_DRAGON_X.STREAM_RATE); // g4 s1 (FUN_800b9790:4194)
  }
}

function cyberDragonGroundPhase2(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  // FUN_800b9820: +0x6f7=4, advance stream, on +0x1cee → clear bits + zz_006a474_.
  tickStream(actor, 0xf, ctx);
  // +0x1cee (stream-end) isn't surfaced; approximate with a short recovery countdown.
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= -RECOVERY_FRAMES) {
    actor.controlWord = actor.controlWord & ~0x3; // +0x5e0 &= ~0xfffffffc
    dispatchFullBodyCue(actor, 0);  // zz_006a474_ → ground idle
    dispatchUpperBodyCue(actor, 6);
  }
}

// ============================================================================
// Variant 1 — air breath. Engine FUN_800b9888 @ chunk_0018.c:4219 =
//   PTR_FUN_802ff3e4[+0x540]() THEN zz_006ed8c_(0.95) + zz_0067458_(1.0) + zz_00677b0_.
// Phases: FUN_800b98f4 (P0) → FUN_800b9964 (P1, 3× steer) → FUN_800b9a0c (P2).
// ============================================================================
function cyberDragonAirPhase0(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = CYBER_DRAGON_X.BREATH_WINDOW;
  // +0x54e = 0x78 (visual). +0x6ea = 2 (air slot seed), +0x6f7 = 0.
  startStream(actor, 0xf, 4, 2, CYBER_DRAGON_X.STREAM_RATE); // g4 s2 (FUN_800b98f4:4251)
  void ctx;
}

function cyberDragonAirPhase1(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  cyberDragonContactBookkeeping(actor, ctx); // zz_00b9c68_
  // zz_0066e40_(actor, 0) ×3 — three heading-steer samples per frame (triple breath
  // row); modeled as one contact pass (the steer is visual aim refinement).
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= CYBER_DRAGON_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0xf, 4, 3, CYBER_DRAGON_X.STREAM_RATE); // g4 s3 (FUN_800b9964:4279)
  }
}

function cyberDragonAirPhase2(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  // FUN_800b9a0c: +0x6f7=4, advance, on +0x1cee → clear bits + zz_006a5a4_ (air idle).
  tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= -RECOVERY_FRAMES) {
    actor.controlWord = actor.controlWord & ~0x3;
    // zz_006a5a4_ = return to airborne neutral; mirror FLAME's airborne reset.
    dispatchUpperBodyCue(actor, 7);
  }
}

// ============================================================================
// Variant 2 — charged/special breath. Engine FUN_800b9a74 @ chunk_0018.c:4304 =
//   PTR_FUN_802ff3f0[+0x540]() THEN FUN_80067310(1.0) + zz_00677b0_.
// Phases: FUN_800b9ad4 (P0, +0x5dd==0x11 gate) → FUN_800b9b64 (P1) → FUN_800b9bfc (P2).
// ============================================================================
/** +0x5dd gate byte — set by the host when the breath is entered via the charged-X
 *  path (the ROM checks prevUbState == 0x11). Surfaced as `xChargeGate` on the actor. */
function xChargeGate(actor: RomActor): number {
  return (actor as RomActor & { xChargeGate?: number }).xChargeGate ?? 0;
}

function cyberDragonChargedPhase0(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  if (xChargeGate(actor) !== 0x11) {
    // FUN_800b9ad4 else-branch: zz_006a3d0_(actor, 2, 3, 0) — re-issue command. The
    // bridge/command layer owns re-dispatch; the port bails to idle (labeled).
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    return;
  }
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = CYBER_DRAGON_X.BREATH_WINDOW;
  // +0x54e = 0x78. +0x6ea = 4 (charged slot seed), +0x6f7 = 0.
  startStream(actor, 0xf, 4, 4, CYBER_DRAGON_X.STREAM_RATE); // g4 s4 (FUN_800b9ad4:4336)
  void ctx;
}

function cyberDragonChargedPhase1(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  cyberDragonContactBookkeeping(actor, ctx); // zz_00b9c68_ + zz_0066e40_(2)
  // FUN_800b9b64:4359 — copy heading (+0x72) into lockYaw (+0x5ae) so the physics
  // integrator projects along the facing direction.
  actor.lockYaw = actor.heading;
  actor.activeYaw = actor.heading;
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= CYBER_DRAGON_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0xf, 4, 5, CYBER_DRAGON_X.STREAM_RATE); // g4 s5 (FUN_800b9b64:4367)
  }
}

function cyberDragonChargedPhase2(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  // FUN_800b9bfc: +0x6f7=4, advance, on +0x1cee → clear bits + zz_006a750_(0x10).
  tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= -RECOVERY_FRAMES) {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchUpperBodyCue(actor, 0x10); // zz_006a750_(actor, 0x10) — follow-up breath cue
  }
}

// ============================================================================
// Variant engines — the wrappers that combine the phase table with per-frame physics.
// ============================================================================

/** Variant phase tables (PTR_FUN_802ff3d8 / _3e4 / _3f0, 3 entries each). */
const VARIANT_PHASES: Record<number, Array<(a: RomActor, ctx: CyberDragonFamilyCtx) => void>> = {
  0: [cyberDragonGroundPhase0, cyberDragonGroundPhase1, cyberDragonGroundPhase2],
  1: [cyberDragonAirPhase0, cyberDragonAirPhase1, cyberDragonAirPhase2],
  2: [cyberDragonChargedPhase0, cyberDragonChargedPhase1, cyberDragonChargedPhase2],
};

/** The per-variant engine wrapper. v0 has NO per-frame physics; v1 applies velocity
 *  drag + gravity integration + ground clamp; v2 applies gravity integration + ground
 *  clamp. Returns true if the variant index is known.
 *
 *  Variant→engine mapping (actionStreamTables.json pl0503 action 2):
 *    variantIndex 0/1/2 → engine 0x800b96c4 (ground, seedSlot 0, runtime +0x6ea)
 *    variantIndex 3     → engine 0x800b9888 (air,    seedSlot 2, runtime +0x6ea)
 *    variantIndex 4     → engine 0x800b9a74 (charged,seedSlot 4, runtime +0x6ea)
 *  The 5 command-record variants collapse to 3 engine variants; we index the phase
 *  table by `variantIndex % 3` (0/1/2) so any of {0,1,2}→ground, {3}→air, {4}→charged. */
function runCyberDragonVariant(actor: RomActor, ctx: CyberDragonFamilyCtx): boolean {
  const romVariant = actor.variantIndex;
  // Collapse 5 ROM variants → 3 engine variants.
  const variant = romVariant >= 4 ? 2 : romVariant >= 3 ? 1 : 0;
  const phases = VARIANT_PHASES[variant];
  if (!phases) return false;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = phases[phase];
  if (fn) fn(actor, ctx);
  // Per-variant per-frame physics (the post-dispatch tail of each engine wrapper).
  if (variant === 1) {
    // FUN_800b9888:4225-4227 — zz_006ed8c_(0.95) then zz_0067458_(1.0) then ground.
    // zz_006ed8c_ with dt==FLOAT_80437670 (1.0): hSpeed *= 0.95; yVel *= 0.95 (drag).
    actor.hSpeed *= CYBER_DRAGON_X.AIR_DRAG;
    actor.yVel *= CYBER_DRAGON_X.AIR_DRAG;
    integratePhysics(CYBER_DRAGON_X.GRAVITY, actor, actor.activeYaw);
  } else if (variant === 2) {
    // FUN_800b9a74:4310 — FUN_80067310(1.0, actor, +0x5ae) then ground.
    integratePhysics(CYBER_DRAGON_X.GRAVITY, actor, actor.activeYaw);
  }
  // v0: no per-frame physics (stationary ground breath).
  return true;
}

// ============================================================================
// Action 2 entry — FUN_800b9688 @ chunk_0018.c:4120 = variant dispatch.
// ============================================================================
function cyberDragonXSpecial(actor: RomActor, ctx: CyberDragonFamilyCtx): void {
  runCyberDragonVariant(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_800b8a94 @ chunk_0018.c:3637.
// ============================================================================
/** Action-index table (PTR_FUN_802ff2fc). Only actionIndex 2 (X-special) is ported
 *  here. Action 0 (dash = FUN_800b8f10) is real (group 0 slot 1/15, 5 variants) but
 *  out of scope — left to the shared fallback. Action 3 (B-shot = FUN_800b8ad0 →
 *  zz_00b8af0_, group 2 slot 0/1 w/ airborne fork) is the Cyber Death Dragon's
 *  primary shot and also routes through the shared fallback. Action 4 (FUN_800b9d2c)
 *  is the family-init shim (borg-id switch matching FUN_800b866c) — dead data during
 *  gameplay. Actions 1 is null in the table (no entry in actionStreamTables). */
export function createCyberDragonRootAction(ctx: CyberDragonFamilyCtx): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                        // 0: dash attack (FUN_800b8f10) — TODO port
    null,                                        // 1: — (null in ROM)
    (actor) => cyberDragonXSpecial(actor, ctx),  // 2: X-special (bespoke 3-variant breath)
    null,                                        // 3: B-shot (FUN_800b8ad0 → zz_00b8af0_) — TODO port
    null,                                        // 4: family-init shim (FUN_800b9d2c) — dead data
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned Cyber Death Dragon-family actor (pl0503/pl0506/pl0507/
 *  pl050f/pl0512/pl0513). Stamps the borg-number (the ctor block-copies the same
 *  +0x4b4 binding to all 6 members; only FUN_800b866c's borg-id switch on +0x3e8
 *  indexes different animation records) and wires the root action dispatcher. */
export function configureCyberDragonFamily(
  actor: RomActor,
  borgId: "pl0503" | "pl0506" | "pl0507" | "pl050f" | "pl0512" | "pl0513",
  ctx: CyberDragonFamilyCtx,
): void {
  const numMap: Record<typeof borgId, number> = {
    pl0503: 0x503,
    pl0506: 0x506,
    pl0507: 0x507,
    pl050f: 0x50f,
    pl0512: 0x512,
    pl0513: 0x513,
  };
  actor.borgNumber = numMap[borgId];
  actor.rootAction = createCyberDragonRootAction(ctx);
  // cueTable + familyStreamBank are set by the spawn layer (familyCueTablesFull.json
  // entry "0x800b8188", cue table @0x802fec20). Defaults matching power-on state:
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
