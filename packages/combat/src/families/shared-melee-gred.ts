// Shared-engine 4-phase MELEE (B-close) machine — 1:1 port of `zz_0177dd8_` @0x80177dd8
// and its phase table `PTR_FUN_80352b08` @0x80352b08 = [FUN_80177e28, FUN_80177f10,
// FUN_80177fd4, FUN_801780e4]. This is the STANDARD melee combo chain used by the
// MAJORITY of the roster (192 borgs' B-close swings) — distinct from the Ninja family's
// `zz_00fed6c_` lunge engine (port in shared-melee-lunge.ts).
//
// Source: research/decomp/ghidra-export/chunk_0044.c:3001-3176. Each phase handler is
// cited inline. Constants: FLOAT_8043ae20 (timer seed 60.0), FLOAT_8043ae04 (stream rate
// -1.0), FLOAT_8043ae10 (0.0 floor), FLOAT_8043ae24 (extra decel 0.0), DOUBLE_8043ae08
// (the u32→f64 coercion sentinel 4503599627370496.0).
//
// Config block layout (the struct each family's variant function loads into r4 via
// `lis r4, ...; addi r4, r4, ...; bl 0x80177dd8`):
//   s32 +0x00 = seedSlot        (→ +0x6ea, then ++ per combo swing)
//   f32 +0x04 = proximityRange  (FUN_800668cc gate for the phase 2→3 advance)
//   u32 +0x08 = timerFrames     (→ +0x558 at the phase 1→2 transition; u32→f32 coerce)
//   f32 +0x0c = decel           (zz_006ed8c_ scale per active frame)
//   fcn +0x10 = chainCallback   (phase 3, fires when +0x1cf0&1==0 and combo-continue)
//   fcn +0x14 = altChainCallback(phase 2/3, fires when +0x1dd&0x80 and not +0x745)

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { computeLungeSpeed } from "./shared-engine.js";

/** Machine constants — DOL-read (chunk_0044.c:3036,3039,3042,3166). */
export const SHARED_MELEE_GRED = {
  TIMER_SEED: 60.0,    // FLOAT_8043ae20 — phase-0 handlerTimer seed (face-target budget)
  STREAM_RATE: -1.0,   // FLOAT_8043ae04 — group-3 stream playback rate
  TIMER_FLOOR: 0.0,    // FLOAT_8043ae10 — handlerTimer floor (phase-1/2 transition gate)
  EXTRA_DECEL: 0.0,    // FLOAT_8043ae24 — phase-3 extra decel when +0x760 < proximityRange
  STREAM_GROUP: 3,     // melee stream group (all B-close streams are g3)
  PART_MASK: 0xf,      // all four parts active
  STATE_FACE: 0xc0,    // zz_006d144_ arg (face-target mode)
} as const;

export interface SharedMeleeGRedConfig {
  /** +0x00: seed slot byte — the first stream slot (config[0] → +0x6ea, then ++ per
   *  combo swing). */
  seedSlot: number;
  /** +0x08: u32 — timer seed (frames) for the active window. Copied into +0x558 at the
   *  phase 1→2 transition; decremented per frame; expiry advances the phase. */
  timerFrames: number;
  /** +0x04: float — proximity range passed to FUN_800668cc (the "is target in range"
   *  check that gates the phase 2→3 advance). */
  proximityRange: number;
  /** +0x10: chain callback — called from phase 3 when the combo-continue condition
   *  (+0x1cf0 high bit set, +0x746 & +0x745 latches both set) fires AND +0x1cf0 bit 0
   *  is clear. The callback re-issues a command via zz_006a3d0_ (variant redirect). */
  chainCallback?: (actor: RomActor) => void;
  /** +0x14: alt chain callback — called from phase 2/3 when +0x1dd & 0x80 and +0x745 == 0.
   *  Typically a per-variant redirect (e.g. NEO G RED's standing-finisher redirect). */
  altChainCallback?: (actor: RomActor) => void;
  /** +0x0c: float — decel scale applied per active frame via zz_006ed8c_. Default 1.0
   *  (no decel); families that brake near the target set this < 1.0. */
  decel?: number;
}

/** Per-actor scratch fields the engine reads/writes beyond the base RomActor. These
 *  correspond to ROM offsets the foundation hasn't surfaced as named fields yet. */
interface MeleeScratch {
  /** +0x746: B-retap latch (set when +0x5d4 & 0x40 — B button edge this frame). */
  bRetap?: boolean;
  /** +0x745: alt-input latch (set when +0x1d9 != 0 — direction/lock input this frame). */
  altInput?: boolean;
  /** Host-set: B button retap this frame (the +0x5d4 & 0x40 edge). */
  bRetapInput?: boolean;
  /** Host-set: alt input present this frame (the +0x1d9 byte). */
  altInputPresent?: boolean;
  /** Host-set: +0x1dd & 0x80 — the alt-chain-callback dispatch gate. */
  altChainGate?: boolean;
  /** +0x1cf0 high bit (sign of the byte) — set by op 0x02 when the swing re-arms. */
  swingReArm?: boolean;
  /** +0x1cf0 bit 0 — when clear, the chain callback fires instead of the loop restart. */
  swingChainBit?: boolean;
  /** +0x1d0f — velocity-refresh flag (zz_01782dc_ re-applies when set in phase 3). */
  velRefresh?: boolean;
  /** +0x1d10 — face-target flag (zz_006d144_ runs when set in phase 3). */
  faceTarget?: boolean;
  /** +0x1b03 — stream-tick gate (phase 1 ticks the stream only when this is set). */
  streamTickGate?: boolean;
  /** +0x760 — current speed scalar (compared against proximityRange in phase 3). */
  curSpeed?: number;
  /** Host-set: lock-target position (for the air-check and proximity gate approximations). */
  lockTarget?: { x: number; y: number; z: number } | null;
  /** Host-set: grounded flag (the +0x868 air-check uses it). */
  grounded?: boolean;
}

function targetDistance(actor: RomActor & MeleeScratch): number | null {
  const t = actor.lockTarget;
  if (!t) return null;
  const dx = t.x - actor.pos.x;
  const dz = t.z - actor.pos.z;
  return Math.hypot(dx, dz);
}

// ============================================================================
// Phase 0 — FUN_80177e28 @ chunk_0044.c:3017. Stream start.
// ============================================================================
function meleePhase0(actor: RomActor & MeleeScratch, cfg: SharedMeleeGRedConfig): void {
  actor.fbPhaseSlots[0] += 1;              // +0x540++
  actor.bRetap = false;                    // +0x746 = 0
  actor.altInput = false;                  // +0x745 = 0
  actor.streamSlot = cfg.seedSlot;         // +0x6ea = cfg.seedSlot
  // Air-check FUN_80066838(+0x868 row, actor): when the borg is airborne the +0x868 row
  // isn't populated (writer unlocated), so the ROM takes the <1 branch: +0x541=1,
  // +0xcc=0, +0x5ac = +0x5ae = +0x72 (yaw snapshot to heading). Port approximation:
  // gate on the grounded flag the bridge maintains from the floor-clamp. Grounded →
  // keep the bridge's lockYaw (face target); airborne → fall back to heading.
  if (!actor.grounded) {
    actor.activeYaw = actor.heading;       // +0x5ac = +0x72
    actor.lockYaw = actor.heading;         // +0x5ae = +0x72
  } else {
    actor.activeYaw = actor.lockYaw;
  }
  actor.handlerTimer = SHARED_MELEE_GRED.TIMER_SEED; // +0x558 = 60.0
  // zz_006d144_(actor, 0xc0) — face target (the bridge pre-computes lockYaw each frame).
  // Start the g3 stream: zz_004beb8_(-1.0, actor, 0xf, 3, slot, -1, -1). The ROM reads
  // +0x6ea into cVar1, ++s +0x6ea, then passes the OLD value to the stream starter.
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;             // +0x6ea++
  startStream(
    actor,
    SHARED_MELEE_GRED.PART_MASK,
    SHARED_MELEE_GRED.STREAM_GROUP,
    slot,
    SHARED_MELEE_GRED.STREAM_RATE,
  );
  // +0x80c = FLOAT_8043ae10 (0.0) — a per-move anim-blend floor write (offset not on the
  // foundation RomActor; stubbed — the renderer owns the blend floor).
}

// ============================================================================
// Phase 1 — FUN_80177f10 @ chunk_0044.c:3048. Pre-active tick + transition.
// ============================================================================
function meleePhase1(
  actor: RomActor & MeleeScratch,
  cfg: SharedMeleeGRedConfig,
  ctx: StreamContext,
): void {
  // +0x1b03 != 0 → tick the stream (the part-anim hold gate).
  if (actor.streamTickGate) {
    tickStream(actor, SHARED_MELEE_GRED.PART_MASK, ctx);
  }
  actor.handlerTimer -= actor.dt;          // +0x558 -= +0x1dc8 (dt)
  // Transition: timer <= 0.0 OR zz_006d144_(actor, 0xc0) != 0 (facing complete). The
  // bridge pre-aims lockYaw from the live target each frame, so facing completes on the
  // first phase-1 tick where the target is present — matching the ROM short-circuit.
  const facingComplete = actor.lockTarget != null;
  if (actor.handlerTimer <= SHARED_MELEE_GRED.TIMER_FLOOR || facingComplete) {
    actor.fbPhaseSlots[0] += 1;            // +0x540++
    // +0x558 = (float)cfg.timerFrames (u32→f32 via the CONCAT44/DOUBLE_8043ae08 idiom).
    actor.handlerTimer = cfg.timerFrames;
    computeLungeSpeed(actor, cfg.timerFrames); // zz_01782dc_: set forward-dash hSpeed
    // zz_00b2190_(actor, 0) — clears the stream-bank-hold flag (offset not on the
    // foundation RomActor; stubbed).
  }
}

// ============================================================================
// Phase 2 — FUN_80177fd4 @ chunk_0044.c:3077. Active frames.
// ============================================================================
function meleePhase2(
  actor: RomActor & MeleeScratch,
  cfg: SharedMeleeGRedConfig,
  ctx: StreamContext,
): void {
  // +0x5d4 & 0x40 → +0x746 = 1 (B-retap latch — the combo-loop request).
  if (actor.bRetapInput) actor.bRetap = true;
  // +0x1d9 != 0 → +0x745 = 1 (alt-input latch — direction/lock input this frame).
  if (actor.altInputPresent) actor.altInput = true;
  // +0x1dd & 0x80 AND +0x745 == 0 AND cfg.altChainCallback != null → fire alt callback.
  // The +0x745 read sees the JUST-UPDATED latch, so alt-input this frame suppresses the
  // callback (the ROM nests the +0x745 == 0 test inside the +0x1dd & 0x80 test).
  if (actor.altChainGate && !actor.altInput && cfg.altChainCallback) {
    cfg.altChainCallback(actor);
  }
  // zz_006d144_(actor, 0xc0) — face target (bridge pre-aims lockYaw).
  // zz_006ed8c_(cfg.decel, actor) — apply decel to hSpeed/yVel.
  const decel = cfg.decel ?? 1.0;
  if (decel !== 1.0) {
    actor.hSpeed *= decel;
    actor.yVel *= decel;
  }
  // zz_00670dc_(actor, +0x5ae) — yaw-only physics (gravity=0; just hSpeed projection).
  integratePhysics(0, actor, actor.activeYaw);
  // +0x1cef == 0 → tick stream (contact-suspend: when the hitbox is active the stream
  // pauses; when it clears, the stream advances).
  if (actor.contactP0 === 0) {
    tickStream(actor, SHARED_MELEE_GRED.PART_MASK, ctx);
  }
  actor.handlerTimer -= actor.dt;          // +0x558 -= dt
  // Transition: timer <= 0.0 OR FUN_800668cc(cfg.proximityRange, actor) != 0 (in range).
  // FUN_800668cc reads +0x868 rows (runtime-populated, writer unlocated) — port gates on
  // lock-target distance vs cfg.proximityRange (labeled approximation, same shape as the
  // lunge engine's range gate).
  const dist = targetDistance(actor);
  const inProximity = dist !== null && dist <= cfg.proximityRange;
  if (actor.handlerTimer <= SHARED_MELEE_GRED.TIMER_FLOOR || inProximity) {
    actor.fbPhaseSlots[0] += 1;            // +0x540++ (→ phase 3)
  }
  // zz_017a68c_(actor) — per-frame helper (animation sync; stubbed).
}

// ============================================================================
// Phase 3 — FUN_801780e4 @ chunk_0044.c:3118. Combo/recovery.
// ============================================================================
function meleePhase3(
  actor: RomActor & MeleeScratch,
  cfg: SharedMeleeGRedConfig,
  ctx: StreamContext,
): void {
  if (actor.bRetapInput) actor.bRetap = true;       // +0x5d4 & 0x40 → +0x746 = 1
  if (actor.altInputPresent) actor.altInput = true; // +0x1d9 != 0 → +0x745 = 1
  // Alt chain callback (same gate as phase 2: +0x1dd & 0x80 AND not +0x745).
  if (actor.altChainGate && !actor.altInput && cfg.altChainCallback) {
    cfg.altChainCallback(actor);
  }
  tickStream(actor, SHARED_MELEE_GRED.PART_MASK, ctx); // zz_004cd24_(actor, 0xf)

  // COMBO-CONTINUE CHECK (chunk_0044.c:3139-3156):
  //   ((char)+0x1cf0 < 0)  → high bit (0x80) of +0x1cf0 set (swing re-arm event)
  //   (+0x746 & +0x745) != 0  → BOTH latches set (B-retap AND alt-input)
  if (actor.swingReArm && actor.bRetap && actor.altInput) {
    // +0x1cf0 bit 0 clear AND cfg.chainCallback present → fire callback and bail (the
    // variant-redirect path, e.g. NEO G RED's standing finisher via FUN_8018ded0).
    if (!actor.swingChainBit && cfg.chainCallback) {
      cfg.chainCallback(actor);
      return;
    }
    // Else: loop BACK to phase 2 with the next stream slot (the standard combo chain).
    // The ROM does +0x540 += -1 (3→2), NOT a full reset — the active-frame phase
    // re-runs with a fresh timer, the next +0x6ea slot, and a re-applied dash velocity.
    actor.fbPhaseSlots[0] -= 1;            // +0x540-- (3 → 2)
    actor.bRetap = false;                  // +0x746 = 0
    actor.altInput = false;                // +0x745 = 0
    actor.handlerTimer = cfg.timerFrames;  // +0x558 = cfg.timerFrames
    const slot = actor.streamSlot;
    actor.streamSlot = slot + 1;           // +0x6ea++
    startStream(
      actor,
      SHARED_MELEE_GRED.PART_MASK,
      SHARED_MELEE_GRED.STREAM_GROUP,
      slot,
      SHARED_MELEE_GRED.STREAM_RATE,
    );
    computeLungeSpeed(actor, cfg.timerFrames); // zz_01782dc_
    // zz_00b2190_(actor, 0) — clear stream-bank-hold flag (stubbed).
    return;
  }

  // RECOVERY TAIL (chunk_0044.c:3158-3175 — no combo-continue).
  if (actor.faceTarget) {
    // zz_006d144_(actor, 0xc0) — face target (gated on +0x1d10; bridge pre-aims lockYaw).
  }
  if (actor.velRefresh) {
    computeLungeSpeed(actor, cfg.timerFrames); // zz_01782dc_ (gated on +0x1d0f)
  }
  const decel = cfg.decel ?? 1.0;
  if (decel !== 1.0) {
    actor.hSpeed *= decel;                 // zz_006ed8c_(cfg.decel, actor)
    actor.yVel *= decel;
  }
  // +0x760 < cfg.proximityRange → extra decel via FLOAT_8043ae24 (0.0 → full brake near
  // target). +0x760 is the actor's current speed scalar; fall back to hSpeed when the
  // bridge hasn't set it.
  const speed = actor.curSpeed ?? actor.hSpeed;
  if (speed < cfg.proximityRange) {
    actor.hSpeed *= SHARED_MELEE_GRED.EXTRA_DECEL;
    actor.yVel *= SHARED_MELEE_GRED.EXTRA_DECEL;
  }
  integratePhysics(0, actor, actor.activeYaw); // zz_00670dc_(actor, +0x5ae)
  // +0x1cee (wall/ground contact) != 0 → clear action bits + return to idle
  // (zz_006a474_). The +0x73f clear and +0x5e0 &= ~3 are the universal end-of-move
  // teardown; zz_006a474_ dispatches cue 0 (ground idle).
  if (actor.wallContact !== 0) {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    dispatchUpperBodyCue(actor, 0);
  }
  // zz_017a68c_(actor) — per-frame helper (stubbed).
}

/** Build the shared melee (B-close) phase handler for one family config. Wire as the
 *  family's action-1 (B-close) handler. */
export function createSharedMeleeGRed(
  cfg: SharedMeleeGRedConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as RomActor & MeleeScratch;
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: meleePhase0(a, cfg); break;
      case 1: meleePhase1(a, cfg, ctx); break;
      case 2: meleePhase2(a, cfg, ctx); break;
      case 3: meleePhase3(a, cfg, ctx); break;
      default: break;
    }
  };
}

/** G RED (pl0615) B-close config — seedSlot 0, 30-frame active window, 100-unit
 *  proximity. The exact ROM config struct lives in the variant function's r4 load
 *  (address unlocated in the current decode); these are the documented defaults from
 *  shared-engine.ts DEFAULT_CONFIGS.groundMelee until the per-family dig completes. */
export const GRED_MELEE_CONFIG: SharedMeleeGRedConfig = {
  seedSlot: 0,
  timerFrames: 30,
  proximityRange: 100,
};
