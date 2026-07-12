// FLAME DRAGON family (ctor 0x80075658) — bespoke X-special port.
// Covers pl0500 (FLAME DRAGON), pl0509, pl050a, pl050c, pl0515, pl0516. Source:
// `research/decomp/ghidra-export/chunk_0010.c:2561-3015` (root dispatcher FUN_80075a2c
// @0x80075a2c → action table PTR_FUN_802d56d4 → X-special chain FUN_80075eb4 →
// variant table PTR_FUN_802d5760 → bespoke engines FUN_80075ef0 / FUN_80076088 /
// FUN_80076244).
//
// The X-special (actionIndex 2) is a BESPOKE three-variant phase machine — the engine
// addresses live in the family code block (0x80075xxx), NOT in the shared-engine
// ranges (0x80177xxx/0x80178xxx the majority of the roster tail-calls). Each variant
// is a directional flame breath:
//   v0 (ground):  stationary, g4 s0→s1, returns to ground idle (zz_006a474_).
//   v1 (air):     airborne w/ velocity drag + physics, g4 s2→s3, returns to air idle
//                 (zz_006a5a4_). 3× per-frame contact spawns in phase 1.
//   v2 (charged): conditional entry (+0x5dd == 0x11), physics, g4 s4→s5, transitions
//                 to upper-body cue 0x10 (a follow-up breath state, NOT idle).
// The per-frame contact bookkeeping (zz_0076408_) spawns a borg-id-switched flame
// child on each connecting frame via zz_00be948_ @0x800be948.
//
// Float constants read from boot.dol this session (dump-dragon-floats.mjs):
//   FLOAT_80437814 = 0.0   (zero scalar)    FLOAT_80437830 = 180.0 (breath window seed)
//   FLOAT_80437824 = -1.0  (stream rate)    FLOAT_80437834 = 0.95  (v1 velocity drag)
//   FLOAT_8043782c = 1.0   (physics gravity)

import type { RomActor } from "../rom/actor.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { dispatchUpperBodyCue, dispatchFullBodyCue } from "../rom/dispatch.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

/** Every value read from boot.dol this session (dump-dragon-floats.mjs). */
export const DRAGON_X = {
  ZERO: 0.0,            // FLOAT_80437814 — base scalar (zeros launch vel / gravityCoeff)
  STREAM_RATE: -1.0,    // FLOAT_80437824 — zz_004beb8_ playback rate
  GRAVITY: 1.0,         // FLOAT_8043782c — physics integration gravity (airborne phases)
  BREATH_WINDOW: 180.0, // FLOAT_80437830 — phase-1 active-breath timer seed (+0x558)
  AIR_DRAG: 0.95,       // FLOAT_80437834 — zz_006ed8c_ velocity scale (v1 per-frame)
  /** FLOAT_80437820 — dash timer seed (+0x560). Value not yet extracted from boot.dol. */
  DASH_TIMER: 8.0,
  /** FLOAT_80437828 — air dash velocity drag coefficient. Value not yet extracted. */
  DASH_AIR_DRAG: 0.98,
  /** zz_00be948_ @0x800be948 — the on-contact flame-child spawner. Borg-id-switched
   *  record-select (zz_0076408_:3034-3040): 0x500→0, 0x509→1, 0x50a→2, 0x50c→3,
   *  0x515→4, 0x516→5. The host (bridge) resolves the record via the family table. */
  FLAME_SPAWNER_ADDR: 0x800be948,
  /** Stream mask for ground dash phase-2 stream start (mask==3 vs normal 0xf). */
  AIR_DASH_PHASE2_MASK: 3,
} as const;

/** Phase-2 recovery floor — the ROM polls +0x1cee (stream-end) which our stream VM
 *  doesn't surface as an actor field; we approximate by counting down from the breath
 *  window and then clearing the attack state. The bridge's specialMaxFrames caps the
 *  total duration independently. */
const RECOVERY_FRAMES = 30;

/** Borg-id → flame-child record index (zz_0076408_:3034-3040 switch on +0x3e8). */
function flameChildType(borgNumber: number): number {
  switch (borgNumber) {
    case 0x509: return 1;
    case 0x50a: return 2;
    case 0x50c: return 3;
    case 0x515: return 4;
    case 0x516: return 5;
    default: return 0; // 0x500 FLAME DRAGON + any other family member
  }
}

export interface DragonFamilyCtx extends StreamContext {
  /** Face the lock target. Port of zz_006d144_(mask). Returns true when facing complete. */
  onFaceComplete?: (actor: RomActor, mask: number) => boolean;
  /** Allocate resource. Port of zz_006dbe0_(0,1,1). Returns true if resource available. */
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
  /** Exit full-body to idle. */
  onExitFb?: (actor: RomActor) => void;
}

/** Port of zz_0076408_ @ chunk_0010.c:3019 — per-frame contact bookkeeping shared by
 *  all three breath variants. Sets the stream-state byte, ticks the stream, and on a
 *  part-0 contact (+0x1cef) spawns the borg-id-switched flame child via zz_00be948_.
 *  The flame spawn is the on-hit burst (the breath's primary damage comes from the
 *  stream-armed hitbox; this child is the connecting-frame FX). */
function dragonContactBookkeeping(actor: RomActor, ctx: DragonFamilyCtx): void {
  // +0x6f7 = 4 (stream-state byte for the flame FX; visual — not surfaced).
  tickStream(actor, 0xf, ctx);
  // +0x1cef contact flag — set by op 0x02 when the breath hitbox connects.
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0; // the ROM clears +0x1cef after consuming it.
    ctx.onFamilyProjectile?.(actor, DRAGON_X.FLAME_SPAWNER_ADDR, flameChildType(actor.borgNumber));
  }
}

// ============================================================================
// Scratch fields — non-RomActor fields accessed at ROM offsets.
// ============================================================================
interface DragonScratch {
  /** +0x560: dash move timer (float). */
  moveTimer: number;
  /** +0x80: u16 anim offset slot 2. */
  animOffset2: number;
  /** +0x7e: u16 anim offset slot 1. */
  animOffset1: number;
  /** +0x7c: u16 anim offset slot 0. */
  animOffset0: number;
  /** +0x587: cmdChargedRanged byte — cleared on contact during dash phase 2. */
  cmdChargedRanged: number;
  /** +0x73f: ub active byte — cleared on stream-end. */
  ubActiveByte: number;
}

function scratchOf(actor: RomActor): RomActor & DragonScratch {
  return actor as RomActor & DragonScratch;
}

// ============================================================================
// Dash (action 0) — 5 variants, 2 phase tables.
//   FUN_80075a68 → PTR_FUN_802d56e0[variant]:
//     [0] FUN_80075aa4 (ground): PTR_FUN_802d56ec[fbPhase] (6 phases)
//     [1] FUN_80075d20 (air):    PTR_FUN_802d5754[fbPhase] + drag + gravity.
// ============================================================================

/** Dash phase 0 (ground) — FUN_80075ae0. Zeroes physics, sets timer, faces, plays stream. */
function dashGroundPhase0(actor: RomActor, ctx: DragonFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.moveTimer = DRAGON_X.DASH_TIMER;
  actor.gravityCoeff = DRAGON_X.ZERO;
  actor.yVel = DRAGON_X.ZERO;
  actor.hDecel = DRAGON_X.ZERO;
  actor.hSpeed = DRAGON_X.ZERO;
  s.animOffset2 = 0;
  s.animOffset1 = 0;
  s.animOffset0 = 0;
  ctx.onFaceComplete?.(actor, 0xc1);
  startStream(actor, 0xf, 0, 0x2a, DRAGON_X.STREAM_RATE);
}

/** Dash phase 1 (ground) — FUN_80075b68. Ticks stream, decays timer, advances on expiry. */
function dashGroundPhase1(actor: RomActor, ctx: DragonFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= DRAGON_X.ZERO || (ctx.onFaceComplete?.(actor, 0xc1) ?? false)) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0xf, 2, 0, DRAGON_X.STREAM_RATE);
  }
}

/** Dash phase 2 (shared by ground+air) — FUN_80075bf8. On contact: spawns flame child
 *  via zz_00be948_. On stream-end: tri-state idle return (ground/air/charged). */
function dashPhase2(actor: RomActor, ctx: DragonFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  if (actor.contactP0 > 0) {
    actor.contactP0 = 0;
    const ok = ctx.onAllocateResource?.(actor, 0, 1, 1) ?? true;
    if (ok) {
      s.cmdChargedRanged = 0;
      ctx.onFamilyProjectile?.(actor, DRAGON_X.FLAME_SPAWNER_ADDR, flameChildType(actor.borgNumber));
    }
  }
  if (actor.wallContact !== 0) {
    s.ubActiveByte = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    if ((actor.controlWord & 0x40) === 0) {
      if ((actor.controlWord & 0x80) === 0) romGroundIdleReturn(actor);
      else {
        dispatchUpperBodyCue(actor, 0x10);
        // zz_006a668_(...) — unported shared-engine call; labeled no-op.
      }
    } else {
      romAirKnockoutReturn(actor);
    }
  }
}

/** Dash recovery phase — FUN_80075c74 (43 bytes, not in C export). Ticks stream and
 *  waits for wall-contact to exit. Multiple instances fill PTR_FUN_802d56ec phases 3-6. */
function dashRecoveryPhase(actor: RomActor, ctx: DragonFamilyCtx): void {
  tickStream(actor, 0xf, ctx);
  if (actor.wallContact !== 0) {
    scratchOf(actor).ubActiveByte = 0;
    actor.controlWord = actor.controlWord & ~0x3;
    romGroundIdleReturn(actor);
  }
}

// ============================================================================
// Air dash (variant 1): FUN_80075d20 → PTR_FUN_802d5754[fbPhase] + drag + gravity.
// Phases: FUN_80075d8c (p0), FUN_80075df0 (p1), FUN_80075bf8 (p2, shared).
// ============================================================================

/** Dash phase 0 (air) — FUN_80075d8c. Sets timer, faces (mask 0x81), plays stream slot 15. */
function dashAirPhase0(actor: RomActor, ctx: DragonFamilyCtx): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1;
  s.moveTimer = DRAGON_X.DASH_TIMER;
  ctx.onFaceComplete?.(actor, 0x81);
  startStream(actor, 0xf, 0, 0xf, DRAGON_X.STREAM_RATE);
}

/** Dash phase 1 (air) — FUN_80075df0. Ticks stream, decays timer, advances on expiry. */
function dashAirPhase1(actor: RomActor, ctx: DragonFamilyCtx): void {
  const s = scratchOf(actor);
  tickStream(actor, 0xf, ctx);
  s.moveTimer -= actor.dt;
  if (s.moveTimer <= DRAGON_X.ZERO || (ctx.onFaceComplete?.(actor, 0x81) ?? false)) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, DRAGON_X.AIR_DASH_PHASE2_MASK, 2, 1, DRAGON_X.STREAM_RATE);
  }
}

// ============================================================================
// Variant 0 — ground flame breath. Engine FUN_80075ef0 @ chunk_0010.c:2786 =
//   PTR_FUN_802d576c[+0x540]() (3 phases, NO per-frame physics — stationary).
// Phases: FUN_80075f2c (P0 setup) → FUN_80075fa4 (P1 active) → FUN_80076028 (P2 end).
// ============================================================================
function dragonGroundPhase0(actor: RomActor, ctx: DragonFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++
  actor.handlerTimer = DRAGON_X.BREATH_WINDOW; // +0x558 = 180.0
  // +0x54a = 0x78 (120 — part-anim blend; visual, not surfaced).
  actor.gravityCoeff = DRAGON_X.ZERO; // +0x50 = 0.0
  actor.yVel = DRAGON_X.ZERO;         // +0x48 = 0.0
  actor.hDecel = DRAGON_X.ZERO;       // +0x4c = 0.0
  actor.hSpeed = DRAGON_X.ZERO;       // +0x44 = 0.0
  // +0x80/+0x7e/+0x7c = 0 (u16 anim offsets; visual, not surfaced).
  startStream(actor, 0xf, 4, 0, DRAGON_X.STREAM_RATE); // g4 s0 (FUN_80075f2c:2817)
  void ctx;
}

function dragonGroundPhase1(actor: RomActor, ctx: DragonFamilyCtx): void {
  dragonContactBookkeeping(actor, ctx); // zz_0076408_ + zz_0066e40_(0)
  // zz_0066e40_(actor, 0) is a heading-steer toward the target (reads +0x664 turn
  // speed, +0x4ac descriptor table) — unsurfaced fields; left as a labeled no-op.
  // The breath fires forward along the current heading.
  actor.handlerTimer -= actor.dt; // +0x558 -= +0x1dc8
  if (actor.handlerTimer <= DRAGON_X.ZERO) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    startStream(actor, 0xf, 4, 1, DRAGON_X.STREAM_RATE); // g4 s1 (FUN_80075fa4:2840)
  }
}

function dragonGroundPhase2(actor: RomActor, ctx: DragonFamilyCtx): void {
  // FUN_80076028: +0x6f7=4, tick stream, on +0x1cee → clear bits + zz_006a474_.
  tickStream(actor, 0xf, ctx);
  // +0x1cee (stream-end) isn't surfaced; approximate with a short recovery countdown.
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= -RECOVERY_FRAMES) {
    actor.controlWord = actor.controlWord & ~0x3; // +0x5e0 &= ~0xfffffffc
    romGroundIdleReturn(actor); // zz_006a474_ (real call @chunk_0010.c:2857)
  }
}

// ============================================================================
// Variant 1 — air flame breath. Engine FUN_80076088 @ chunk_0010.c:2866 =
//   PTR_FUN_802d5778[+0x540]() THEN zz_006ed8c_(0.95) + zz_0067458_(1.0) + zz_00677b0_.
// Phases: FUN_800760f4 (P0) → FUN_80076148 (P1, 3× flame spawn) → FUN_800761e4 (P2).
// ============================================================================
function dragonAirPhase0(actor: RomActor, ctx: DragonFamilyCtx): void {
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = DRAGON_X.BREATH_WINDOW;
  // +0x54a = 0x78 (visual).
  startStream(actor, 0xf, 4, 2, DRAGON_X.STREAM_RATE); // g4 s2 (FUN_800760f4:2891)
  void ctx;
}

function dragonAirPhase1(actor: RomActor, ctx: DragonFamilyCtx): void {
  dragonContactBookkeeping(actor, ctx); // zz_0076408_
  // zz_0066e40_(actor, 0) ×3 — three heading-steer samples per frame (triple flame
  // row); modeled as one contact pass (the steer is visual aim refinement).
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= DRAGON_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0xf, 4, 3, DRAGON_X.STREAM_RATE); // g4 s3 (FUN_80076148:2916)
  }
}

function dragonAirPhase2(actor: RomActor, ctx: DragonFamilyCtx): void {
  // FUN_800761e4: +0x6f7=4, tick, on +0x1cee → clear bits + zz_006a5a4_ (air idle).
  tickStream(actor, 0xf, ctx);
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= -RECOVERY_FRAMES) {
    actor.controlWord = actor.controlWord & ~0x3;
    romAirKnockoutReturn(actor); // zz_006a5a4_ (real call @chunk_0010.c:2933)
  }
}

// ============================================================================
// Variant 2 — charged/special flame breath. Engine FUN_80076244 @ chunk_0010.c:2942 =
//   PTR_FUN_802d5784[+0x540]() THEN FUN_80067310(1.0) + zz_00677b0_.
// Phases: FUN_800762a4 (P0, +0x5dd==0x11 gate) → FUN_80076318 (P1) → FUN_800763a4 (P2).
// ============================================================================
/** +0x5dd gate byte — set by the host when the breath is entered via the charged-X
 *  path (the ROM checks prevUbState == 0x11). Surfaced as `xChargeGate` on the actor. */
function xChargeGate(actor: RomActor): number {
  return (actor as RomActor & { xChargeGate?: number }).xChargeGate ?? 0;
}

function dragonChargedPhase0(actor: RomActor, ctx: DragonFamilyCtx): void {
  if (xChargeGate(actor) !== 0x11) {
    // FUN_800762a4 else-branch: zz_006a3d0_(actor, 2, 3, 0) — re-issue command. The
    // bridge/command layer owns re-dispatch; the port bails to idle (labeled).
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    return;
  }
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = DRAGON_X.BREATH_WINDOW;
  // +0x54a = 0x78.
  startStream(actor, 0x7, 4, 4, DRAGON_X.STREAM_RATE); // mask 7, g4 s4 (FUN_800762a4:2967)
  void ctx;
}

function dragonChargedPhase1(actor: RomActor, ctx: DragonFamilyCtx): void {
  dragonContactBookkeeping(actor, ctx); // zz_0076408_ + zz_0066e40_(2)
  // FUN_80076318:2989 — copy heading (+0x72) into lockYaw (+0x5ae) so the physics
  // integrator projects along the facing direction.
  actor.lockYaw = actor.heading;
  actor.activeYaw = actor.heading;
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= DRAGON_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
    startStream(actor, 0x3, 4, 5, DRAGON_X.STREAM_RATE); // mask 3, g4 s5 (FUN_80076318:2995)
  }
}

function dragonChargedPhase2(actor: RomActor, ctx: DragonFamilyCtx): void {
  // FUN_800763a4: +0x6f7=4, tick, on +0x1cee → clear bits + zz_006a750_(0x10).
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

/** Variant phase tables (PTR_FUN_802d576c / _76c / _778 / _784, 3 entries each). */
const VARIANT_PHASES: Record<number, Array<(a: RomActor, ctx: DragonFamilyCtx) => void>> = {
  0: [dragonGroundPhase0, dragonGroundPhase1, dragonGroundPhase2],
  1: [dragonAirPhase0, dragonAirPhase1, dragonAirPhase2],
  2: [dragonChargedPhase0, dragonChargedPhase1, dragonChargedPhase2],
};

/** The per-variant engine wrapper. v0 has NO per-frame physics; v1 applies velocity
 *  drag + gravity integration + ground clamp; v2 applies gravity integration + ground
 *  clamp. Returns true if the variant index is known. */
function runDragonVariant(actor: RomActor, ctx: DragonFamilyCtx): boolean {
  const variant = actor.variantIndex;
  const phases = VARIANT_PHASES[variant];
  if (!phases) return false;
  const phase = actor.fbPhaseSlots[0] ?? 0;
  const fn = phases[phase];
  if (fn) fn(actor, ctx);
  // Per-variant per-frame physics (the post-dispatch tail of each engine wrapper).
  if (variant === 1) {
    // FUN_80076088:2870-2872 — zz_006ed8c_(0.95) then zz_0067458_(1.0) then ground.
    // zz_006ed8c_ with dt==FLOAT_80437670 (1.0): hSpeed *= 0.95; yVel *= 0.95 (drag).
    actor.hSpeed *= DRAGON_X.AIR_DRAG;
    actor.yVel *= DRAGON_X.AIR_DRAG;
    integratePhysics(DRAGON_X.GRAVITY, actor, actor.activeYaw);
  } else if (variant === 2) {
    // FUN_80076244:2946 — FUN_80067310(1.0, actor, +0x5ae) then ground.
    integratePhysics(DRAGON_X.GRAVITY, actor, actor.activeYaw);
  }
  // v0: no per-frame physics (stationary ground breath).
  return true;
}

// ============================================================================
// Action 2 entry — FUN_80075eb4 @ chunk_0010.c:2775 = variant dispatch.
// ============================================================================
function dragonXSpecial(actor: RomActor, ctx: DragonFamilyCtx): void {
  runDragonVariant(actor, ctx);
}

// ============================================================================
// Root action dispatcher — port of FUN_80075a2c @ chunk_0010.c:2563.
// ============================================================================
/** Action-index table (PTR_FUN_802d56d4, 3 entries). Action 0 (dash) ported — 2 variants.
 *  Action 1 (B melee) and action 2 (X-special) remain as before. */
export function createDragonRootAction(ctx: DragonFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    if (actor.actionIndex === 0) {
      // FUN_80075a68 → PTR_FUN_802d56e0[variantIndex]
      if (actor.variantIndex === 0) runDashGroundEngine(actor, ctx);
      else runDashAirEngine(actor, ctx);
    } else if (actor.actionIndex === 1) {
      dragonBMeleeCancel(actor);
    } else if (actor.actionIndex === 2) {
      dragonXSpecial(actor, ctx);
    }
  };
}

/** FUN_80075aa4 — ground dash engine dispatcher (PTR_FUN_802d56ec[fbPhase]).
 *  Phase 2 is the shared contact+wall handler; phases 3-5 are recovery. */
function runDashGroundEngine(actor: RomActor, ctx: DragonFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) dashGroundPhase0(actor, ctx);
  else if (phase === 1) dashGroundPhase1(actor, ctx);
  else if (phase === 2) dashPhase2(actor, ctx);
  else dashRecoveryPhase(actor, ctx);
}

/** FUN_80075d20 — air dash engine dispatcher (PTR_FUN_802d5754[fbPhase]).
 *  Includes per-frame physics: velocity drag + gravity integration + ground clamp. */
function runDashAirEngine(actor: RomActor, ctx: DragonFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (phase === 0) dashAirPhase0(actor, ctx);
  else if (phase === 1) dashAirPhase1(actor, ctx);
  else dashPhase2(actor, ctx);
  // Per-frame physics tail (FUN_80075d20:2705-2710)
  actor.hSpeed *= DRAGON_X.DASH_AIR_DRAG;
  actor.yVel *= DRAGON_X.DASH_AIR_DRAG;
  integratePhysics(DRAGON_X.GRAVITY, actor, actor.lockYaw);
}

/** Port of FUN_80075e80 @ chunk_0010.c:2762 — the Dragon B-melee no-op. Clears the
 *  upper-body active byte (+0x73f), the attack bits (+0x5e0 &= ~3), and returns to
 *  ground idle (zz_006a474_). The Dragon's B button is a shot; this action is reached
 *  only via stale command records and cancels cleanly. */
function dragonBMeleeCancel(actor: RomActor): void {
  actor.controlWord = actor.controlWord & ~0x3;
  dispatchFullBodyCue(actor, 0);
}

/** Configure a freshly-spawned Flame Dragon-family actor (pl0500/pl0509/pl050a/
 *  pl050c/pl0515/pl0516). Stamps the borg-number switch the contact bookkeeping reads
 *  and wires the root action dispatcher. */
export function configureDragonFamily(
  actor: RomActor,
  borgId: "pl0500" | "pl0509" | "pl050a" | "pl050c" | "pl0515" | "pl0516",
  ctx: DragonFamilyCtx,
): void {
  const numMap: Record<typeof borgId, number> = {
    pl0500: 0x500,
    pl0509: 0x509,
    pl050a: 0x50a,
    pl050c: 0x50c,
    pl0515: 0x515,
    pl0516: 0x516,
  };
  actor.borgNumber = numMap[borgId];
  actor.rootAction = createDragonRootAction(ctx);
  // cueTable + familyStreamBank are set by the spawn layer (familyCueTablesFull.json
  // entry "0x80075658", cue table @0x802d5a58). Defaults matching power-on state:
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
