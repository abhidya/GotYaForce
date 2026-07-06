// VALKRIE cluster — 1:1 port of the four shared phase-table machines used by 7
// families / 8 borgs (DOL-fingerprint verified, stride 0x10 = 4 pointers):
//   QUICK VALKRIE   pl0b00 (ctor 0x800de190)
//   ICE VALKRIE     pl0b01 (ctor 0x8015d288)
//   TORNADO VALKRIE pl0b02 (ctor 0x80160820)
//   WIND VALKRIE    pl0b03 (ctor 0x80160be4)
//   RING VALKRIE    pl0b04 (ctor 0x80160ffc)
//   SLOW VALKRIE    pl0b06 (ctor 0x801a51cc)
//   DEATH BORG LAMBDA / LAMBDA II pl0b05 + pl0b07 (ctor 0x8019e414; tables A-C only)
//
// Machines (decomp: research/decomp/ghidra-export/chunk_0038.c unless noted):
//   Table A @0x8033ed68 — action 0 (B ranged volley), engine zz_014a200_ (:2754):
//     [FUN_8014a284 :2767, FUN_8014a308 :2792, FUN_8014a3bc :2818, FUN_8014a534 :2874]
//     plus the +0x544 movement sub-table PTR_FUN_804346b0 @0x804346b0 =
//     [FUN_8014a6a0 :2922, zz_014a700_ :2945] and the per-frame prelude
//     zz_014a7f8_ (:2990). Config block per borg: [s16 volleyCount, s16 volleyTimer,
//     ptr chainCallback] (invoked via zz_014a890_ :3019).
//   Table B @0x8033ed78 — action 1 v0-3 (B melee mash), engine zz_014a8c0_ (:3032):
//     [FUN_8014a91c :3047, FUN_8014a9f0 :3078, FUN_8014aa88 :3105, FUN_8014ab64 :3139]
//     with the dash-velocity helper FUN_8014acdc (:3194).
//   Table C @0x8033ed88 — action 1 v4 (air/lunge dive melee), engine zz_014ad94_ (:3224):
//     [FUN_8014ade4 :3238, FUN_8014aef8 :3275, FUN_8014afd8 :3309, FUN_8014b130 :3358]
//   Table D @0x804346b8 — action 2 (X special, valkries only, NOT death borg lambda),
//     engine zz_014b22c_ (:3390): [FUN_8014b278 :3404, FUN_8014b378 :3445, ...]. The
//     DOL dump shows slots 2/3 = 0x8014fb70 (FUN_8014fb70, chunk_0039.c:1544 — the
//     NEXT engine's dispatcher; the fingerprinter's stride-4 read overlaps the adjacent
//     PTR_FUN_804346c0 variant table). FUN_8014b378 never advances +0x540 past 1, so
//     phases 2/3 are UNREACHABLE — the machine is a 2-phase loop ended by wall contact.
//
// Action-0 variant 4 routes through zz_0149ec8_ (:2630): unless the +0x7ce state byte
// is 0xf/0x10 it stamps +0x581 = 2 / +0x540 = 0 and enters table A (one-shot redirect
// to variant 2). The 0xf/0x10 branch (alt table PTR_FUN_8033ed58 @0x8033ed58) is a
// TODO (see valkrieVolleyV4 below).
//
// Float constants — DOL-read from user-data/GG4E/disc/sys/boot.dol (.sdata2):
//   FLOAT_8043a3a8 = -1.0   (stream rate; ALSO the strafe fall yVel)
//   FLOAT_8043a3ac = 15.0   (alt-table 8033ed58 only; unused here)
//   FLOAT_8043a3b0 =  1.0   (FUN_80067310 gravity param)
//   FLOAT_8043a3b4 = 30.0   (volley aim window +0x560; ALSO the table-C dive speed)
//   DOUBLE_8043a3b8 = 0x4330000080000000 (int→float conversion sentinel, NOT gameplay)
//   FLOAT_8043a3c0 =  0.0   (timer floor / zero scalar)
//   FLOAT_8043a3c4 = 60.0   (melee face budget; volley recovery timer +0x55c)
//   FLOAT_8043a3c8 =  0.95  (strafe/recovery drag; table-C reposition scale)
//   FLOAT_8043a3cc = 20.0   (melee dash window +0x558; dash-speed divisor)
//   FLOAT_8043a3d0 = 200.0  (melee proximity gate FUN_800668cc / extra-drag range)
//   FLOAT_8043a3d4 =  0.9   (melee recovery drag; table-C pitch decay)
//   FLOAT_8043a3d8 =  0.5   (near-target extra drag)
//   FLOAT_8043a3dc =  0.0625 (dash strength scale: dist × (s8)+0x1d0f × 0.0625)
//   FLOAT_8043a3e0 = 29.0   (table-C dive window)
//   FLOAT_8043a3e4 =  0.98  (table-D reposition scale + drift decay)
//
// Per-borg config blocks (DOL-read; [s16 volleyCount, s16 volleyTimer, ptr chainCb]):
//   pl0b00 @0x80433bb0/b8: 5, 4, 0x800de4d8 → zz_0082824_(a, 0x1a)   (chunk_0023.c:4088)
//   pl0b01 @0x80434700/08: 5, 4, 0x8015d5a8 → zz_0082824_(a, 0x3d)   (chunk_0041.c)
//   pl0b02 @0x80434710/18: 5, 4, 0x80160b18 → zz_0082824_(a, 0x3e)   (chunk_0041.c)
//   pl0b03 @0x80434720/28: 5, 4, 0x80160f30 → zz_0082824_(a, 0x3f)   (chunk_0041.c)
//   pl0b04 @0x80434730/38: 1, 20, 0x80161308 → 5× zz_016ddb0_(a, 0..4) (chunk_0041.c)
//   pl0b05/07 @0x80435740/48: 5, 4, 0x8019e89c → borg switch: 0xb05 →
//     zz_0082824_(a, 0x40); 0xb07 → zz_0082824_(a, 0x71) + parts glow
//     (+0x168..+0x16b |= 0x80)                                        (chunk_0049.c)
//   pl0b06 @0x80435768/70: 5, 4, 0x801a5514 → zz_0082824_(a, 0x41)   (chunk_0050.c)

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Machine constants — every value DOL-read (see header). */
export const VALKRIE = {
  STREAM_RATE: -1.0,        // FLOAT_8043a3a8
  STRAFE_FALL_VEL: -1.0,    // FLOAT_8043a3a8 (yVel while strafing, hover bit clear)
  GRAVITY_PARAM: 1.0,       // FLOAT_8043a3b0
  VOLLEY_AIM_WINDOW: 30.0,  // FLOAT_8043a3b4 (+0x560 seed in volley phase 0)
  DIVE_SPEED: 30.0,         // FLOAT_8043a3b4 (table-C phase-2 dive magnitude)
  TIMER_FLOOR: 0.0,         // FLOAT_8043a3c0
  FACE_BUDGET: 60.0,        // FLOAT_8043a3c4 (melee phase-0 face budget)
  VOLLEY_RECOVERY: 60.0,    // FLOAT_8043a3c4 (+0x55c seed in volley phase 2→3)
  DRAG: 0.95,               // FLOAT_8043a3c8 (zz_006ed8c_ scale; table-C reposition)
  DASH_WINDOW: 20.0,        // FLOAT_8043a3cc (melee active window + dash divisor)
  PROXIMITY: 200.0,         // FLOAT_8043a3d0 (FUN_800668cc gate + extra-drag range)
  RECOVERY_DRAG: 0.9,       // FLOAT_8043a3d4 (melee phase-3 drag; table-C pitch decay)
  NEAR_DRAG: 0.5,           // FLOAT_8043a3d8 (extra drag when dist < 200)
  DASH_STRENGTH_SCALE: 0.0625, // FLOAT_8043a3dc
  DIVE_WINDOW: 29.0,        // FLOAT_8043a3e0 (table-C phase-2 timer)
  DIVE_PITCH_SEED: 0xf,     // table-C phase 1→2 +0x54e seed (immediate 15)
  X_REPOSITION: 0.98,       // FLOAT_8043a3e4 (table-D reposition + drift decay)
  VOLLEY_GROUP: 2,          // volley strafe/fire anims stream group
  MELEE_GROUP: 3,           // melee swings stream group
  X_GROUP: 4,               // X special stream group
  PART_MASK: 0xf,
  /** (s8)+0x1d0f dash-strength byte default. The byte is stream-authored (part-1
   *  state byte, op writer not yet decoded); 16 × 0.0625 = 1.0 → dash speed =
   *  dist / 20 (reaches the target over the 20f window). LABELED APPROXIMATION. */
  DEFAULT_DASH_STRENGTH: 16,
  /** dataPage(+0x4ac)+0x2c — per-borg minimum strafe hSpeed (zz_014a700_:2960-2963).
   *  TUNED fallback until the data-page extractor lands. */
  DEFAULT_STRAFE_SPEED: 10.0,
  /** dataPage(+0x4ac)+0x6c — per-borg gravityCoeff restore (FUN_8014afd8:3349,
   *  FUN_8014b378:3464). Falls back to descriptor.handlerData6c (sword-knight
   *  precedent), then 1.0. */
  DEFAULT_GRAVITY_RESTORE: 1.0,
} as const;

/** ROM spawner addresses routed through ctx.onFamilyProjectile. */
export const VALKRIE_SPAWNERS = {
  /** zz_0082824_ @0x80082824 — generic blast-record child spawner (volley shot). */
  GENERIC_SHOT: 0x80082824,
  /** zz_016ddb0_ @0x8016ddb0 — RING VALKRIE ring-child spawner (5 per volley). */
  RING_CHILD: 0x8016ddb0,
  /** zz_00b2190_ @0x800b2190 — melee trail/FX child spawner (both dash arms:
   *  phase 1→2 @ chunk_0038.c:3098 + phase-3 combo re-arm @ :3163). */
  MELEE_FX: 0x800b2190,
  /** zz_0092dcc_ @0x80092dcc — table-C dive FX child spawner (kind 8). */
  DIVE_FX: 0x80092dcc,
} as const;

/** Host hooks beyond the base StreamContext (Series3FamilyCtx precedent). */
export interface ValkrieFamilyCtx extends StreamContext {
  /** zz_006dbe0_(actor, 0, 1, 1) — atomic ammo check+deduct gating every volley shot
   *  and the phase-3 re-fire. UNWIRED FALLBACK: success (labeled approximation — the
   *  ROM skips the shot and, in phase 2, advances to recovery on empty). */
  tryConsumeAmmo?: (actor: RomActor, slot: number, cost: number) => boolean;
}

/** Volley (table A) config block — the [s16, s16, ptr] struct zz_014a200_'s param_2
 *  points at (e.g. DAT_80433bb0). */
export interface ValkrieVolleyConfig {
  /** +0x0: volley count seed (→ +0x6ec). */
  volleyCount: number;
  /** +0x2: per-shot frame timer (→ +0x558, via the CONCAT44 s16→f32 idiom). */
  volleyTimerFrames: number;
  /** +0x4: chain callback — the per-borg shot spawner (zz_014a890_ invokes it). */
  chainCallback?: (actor: RomActor) => void;
}

/** Per-actor scratch fields (ROM offsets the foundation hasn't surfaced as named
 *  fields). Host-set inputs are stamped by the bridge / tests each frame. */
interface ValkrieScratch {
  // ---- host-set inputs ----
  /** +0x5d4 & 0x40 — B button edge this frame. */
  bRetapInput?: boolean;
  /** +0x5d8 & 0xf0 — cancel input mask (jump/dash cancel). */
  cancelInput?: boolean;
  /** zz_0066ac0_(actor, 0) != 0 — analog stick held (chunk_0008.c). */
  stickInputPresent?: boolean;
  /** +0x5aa — stick yaw relative to heading (BAM16; written by zz_0066ac0_). */
  stickYaw?: number;
  /** +0x5b4 & 0x100 — hover/rise input bit (zz_014a700_:2967-2972). */
  hoverInput?: boolean;
  /** +0x5bc & 0x200 — the table-D combo-suppress input (FUN_8014b378:3475). */
  xComboSuppressInput?: boolean;
  grounded?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  // ---- machine state ----
  /** +0x560 — volley aim-window timer (prelude decrements). */
  volleyWindow?: number;
  /** +0x55c — volley recovery timer. */
  volleyRecoveryTimer?: number;
  /** +0x54a — facing-complete result from zz_006d0dc_(actor, 0x81, 0). */
  aimComplete?: boolean;
  /** +0x54c — strafe-anim slot base (0 aim / 5 fire / 10 recovery). */
  strafeAnimBase?: number;
  /** +0x6eb — strafe direction quadrant (0 = none, 1..4). */
  strafeDir?: number;
  /** +0x6ec — volleys remaining. */
  volleysLeft?: number;
  /** +0x745 — buffered-B latch (volley re-fire / table-D combo suppress). */
  bBuffered?: boolean;
  /** +0x746 — B-retap latch (melee combo loop). */
  bRetap?: boolean;
  /** +0x54e — melee aim pitch (BAM16; zz_006e514_ output / table-C dive countdown). */
  meleeAimPitch?: number;
  /** +0x544 — table-A movement sub-machine phase. */
  moveSubPhase?: number;
  /** (s8)+0x1d0f — stream-authored dash-strength byte (FUN_8014acdc input). */
  dashStrength?: number;
  /** +0x1d10 — face/pitch re-seek gate bits (bit 0 face, bit 1 pitch). */
  faceGate?: number;
  /** (s8)+0x1cf0 — part-0 swing event byte (<0 = re-arm; !=0 in table D). */
  swingEvent?: number;
  /** +0x1cf2 — table-D follow-up stream event byte. */
  followUpEvent?: boolean;
  /** +0x1b03 — stream-tick gate (anim hold byte). */
  streamTickGate?: boolean;
  /** +0x1b01 — table-C dive-end anim byte. UNWIRED FALLBACK: treated as set once the
   *  29f dive window expires (labeled approximation — anim layer owns the byte). */
  diveEndGate?: boolean;
  /** +0x6f2/+0x6f3 — table-D hit-counter bytes (WIND VALKRIE combo bookkeeping). */
  comboHitsA?: number;
  comboHitsB?: number;
  /** dataPage(+0x4ac)+0x2c — per-borg minimum strafe speed override. */
  strafeMinSpeed?: number;
  /** +0x760 — distance-to-target scalar cache. Refreshed on every locked read
   *  (targetDistance); goes STALE — not cleared — when the lock drops, mirroring the
   *  engine-maintained field. */
  curTargetDist?: number;
}

type VActor = RomActor & ValkrieScratch;

/** +0x760 — distance to the lock target. The ROM engine refreshes the scalar every
 *  frame a lock exists and leaves it STALE (not cleared) when the lock drops (e.g.
 *  the melee air check's +0xcc = 0). PORT-SIDE CACHING (new; the engine owns the
 *  +0x760 write): refresh curTargetDist on every locked read, serve the stale cache
 *  when unlocked so post-lock-drop reads match the ROM (e.g. the meleePhase3 brake). */
function targetDistance(a: VActor): number {
  const t = a.lockTarget;
  if (t) {
    a.curTargetDist = Math.hypot(t.x - a.pos.x, t.z - a.pos.z); // +0x760 mirror
    return a.curTargetDist;
  }
  return a.curTargetDist ?? 0;
}

/** s16 wrap helper for the BAM16 fields (+0x18da, +0x54e). */
function s16(v: number): number {
  return (v << 16) >> 16;
}

/** zz_006e514_(actor, 0xc0, &+0x54e) — aim-pitch seek toward the lock target
 *  (chunk_0009.c). No target → the ROM decays the pitch toward 0; with a target it
 *  rate-limits toward the target elevation. PORT APPROXIMATION: snap to the target
 *  pitch (the bridge pre-aims yaw the same way); decay-to-zero without a target.
 *  Sign convention: +0x48 (yVel) = mag × -sin(pitch), so pitch < 0 aims UP. */
function seekMeleeAimPitch(a: VActor): void {
  const t = a.lockTarget;
  if (!t) {
    a.meleeAimPitch = s16(Math.trunc((a.meleeAimPitch ?? 0) * VALKRIE.RECOVERY_DRAG));
    return;
  }
  const hd = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
  const pitchRad = Math.atan2(-(t.y - a.pos.y), Math.max(hd, 1e-6));
  a.meleeAimPitch = s16(Math.round((pitchRad / (Math.PI * 2)) * 0x10000));
}

/** zz_006d144_(actor, 0xc0/0xc1) — face the lock target; nonzero return = facing
 *  complete. The bridge pre-aims lockYaw each frame, so facing completes on the first
 *  tick a target exists (shared-melee-gred precedent). */
function faceLockTargetComplete(a: VActor): boolean {
  return a.lockTarget != null;
}

/** zz_006dbe0_(actor, 0, 1, 1) — ammo check+deduct (slot 0, cost 1). */
function tryConsumeShotAmmo(a: VActor, ctx: ValkrieFamilyCtx): boolean {
  return ctx.tryConsumeAmmo ? ctx.tryConsumeAmmo(a, 0, 1) : true;
}

/** dataPage(+0x4ac)+0x6c — gravityCoeff restore value. */
function gravityRestore(a: VActor): number {
  return a.descriptor?.handlerData6c ?? VALKRIE.DEFAULT_GRAVITY_RESTORE;
}

/** The universal end-of-move teardown. Every exit arm (volley cancel
 *  chunk_0038.c:2857-2867, volley recovery end :2908-2916, melee wall :3179-3187,
 *  X wall :3489-3500) does +0x73f = 0 (bridge-side flag); +0x5e0 &= ~3; then picks
 *  zz_006a474_ (ground) / zz_006a4f4_ (air) on the zz_00677b0_/zz_0067a28_ result.
 *  NOTE: deliberately diverges from the cyber-girl.ts:245-253 precedent (full cue 0 +
 *  upper 6 / upper 7) — decomp-verified against zz_006a474_/zz_006a4f4_ themselves. */
function valkrieReturnToIdle(a: VActor, grounded: boolean): void {
  a.controlWord = a.controlWord & ~0x3;      // caller arm: +0x5e0 &= 0xfffffffc
  if (grounded) {
    // zz_006a474_ @ chunk_0009.c:708-729 — ground idle return.
    a.controlWord &= 0xff0003;               // +0x5e0 &= 0xff0003
    // +0x1d9c = 0, +0x1db2 = 0, +0x4a1 = 0, +0x71b = 0, +0x80c = 0 — anim-rate /
    // housekeeping bytes (not surfaced on RomActor — labeled no-ops).
    a.gravityCoeff = 0;                      // +0x50 = FLOAT_8043762c (0.0)
    a.yVel = 0;                              // +0x48 = 0
    a.hDecel = 0;                            // +0x4c = 0
    a.hSpeed = 0;                            // +0x44 = 0
    // +0x80 = +0x7e = +0x7c = 0 — aim-rate accumulators (renderer-side; not
    // surfaced on RomActor — labeled no-ops; xPhase0 precedent).
    dispatchUpperBodyCue(a, 0);              // zz_006a750_(a, 0) — upper cue 0 ONLY
  } else {
    // zz_006a4f4_ @ chunk_0009.c:735-746 — air idle return.
    a.controlWord &= 0xff0843;               // +0x5e0 &= 0xff0843
    // +0x1d9c = 0, +0x71b = 0 — not surfaced (labeled no-ops).
    dispatchUpperBodyCue(a, 0x12);           // zz_006a750_(a, 0x12) — row 18 → state 24
  }
}

// ============================================================================
// Table A — B ranged volley (engine zz_014a200_ @0x8014a200, chunk_0038.c:2754).
// Per frame: prelude zz_014a7f8_, movement sub-table PTR_FUN_804346b0[+0x544],
// volley table PTR_FUN_8033ed68[+0x540].
// ============================================================================

// Prelude zz_014a7f8_ @ chunk_0038.c:2990.
function volleyPrelude(a: VActor): void {
  a.volleyWindow = (a.volleyWindow ?? 0) - a.dt;      // +0x560 -= +0x1dc8
  // +0x54a = zz_006d0dc_(actor, 0x81, 0) — face target, result = facing complete.
  a.aimComplete = faceLockTargetComplete(a);
  // zz_006e1ac_(actor, 0xc1, 1) — aim-pitch seek (+0x18da channel; bridge-side aim).
  // Strafe direction (chunk_0038.c:3005-3013): stick held (zz_0066ac0_(actor,0)) →
  // quadrant of +0x5aa: ((yaw + 0x2000) >> 14 & 3) + 1; else 0.
  if (a.stickInputPresent) {
    const yaw = (a.stickYaw ?? 0) & 0xffff;
    a.strafeDir = (((yaw + 0x2000) >>> 14) & 3) + 1;  // 1..4
  } else {
    a.strafeDir = 0;
  }
}

// Movement sub-phase 0 — FUN_8014a6a0 @ chunk_0038.c:2922 (PTR_FUN_804346b0[0]).
function volleyMoveInit(a: VActor, ctx: ValkrieFamilyCtx): void {
  a.moveSubPhase = 1;                        // +0x544++
  a.streamSlot = -1;                         // +0x6ea = 0xff (forces the first re-arm)
  a.volleyWindow = VALKRIE.TIMER_FLOOR;      // +0x560 = 0.0
  a.aimComplete = false;                     // +0x54a = 0
  a.strafeAnimBase = 10;                     // +0x54c = 10
  if (a.variantIndex === 0) {                // +0x581 == 0 → zero +0x4c / +0x44
    a.hDecel = VALKRIE.TIMER_FLOOR;
    a.hSpeed = VALKRIE.TIMER_FLOOR;
  }
  volleyMoveTick(a, ctx);                    // tail-call zz_014a700_
}

// Movement sub-phase 1 — zz_014a700_ @ chunk_0038.c:2945 (PTR_FUN_804346b0[1]).
function volleyMoveTick(a: VActor, ctx: ValkrieFamilyCtx): void {
  const dir = a.strafeDir ?? 0;              // +0x6eb
  if (dir === 0) {
    // zz_006ed8c_(FLOAT_8043a3c8, actor) — velocity drag 0.95.
    a.hSpeed *= VALKRIE.DRAG;
    a.yVel *= VALKRIE.DRAG;
  } else {
    // Strafe: hSpeed = max(hSpeed, dataPage+0x2c); +0x4c = 0; +0x5ae = +0x5ac
    // (the stick-relative yaw zz_0066ac0_ wrote into +0x5ac).
    const minSpeed = a.strafeMinSpeed ?? VALKRIE.DEFAULT_STRAFE_SPEED;
    if (a.hSpeed < minSpeed) a.hSpeed = minSpeed;
    a.hDecel = VALKRIE.TIMER_FLOOR;
    a.lockYaw = a.activeYaw;
  }
  // +0x5b4 & 0x100 clear → +0x48 = FLOAT_8043a3a8 (-1.0 gentle fall); set → 0.0.
  a.yVel = a.hoverInput ? VALKRIE.TIMER_FLOOR : VALKRIE.STRAFE_FALL_VEL;
  integratePhysics(VALKRIE.GRAVITY_PARAM, a, a.lockYaw); // FUN_80067310(1.0, a, +0x5ae)
  // zz_0067a28_(actor) — ground collide + airborne-bit upkeep (bridge owns the clamp).
  // Strafe-anim latch (chunk_0038.c:2975-2984): +0x6ea doubles as the dir latch here.
  if (a.streamSlot === dir) {
    tickStream(a, VALKRIE.PART_MASK, ctx);   // zz_004cd24_(actor, 0xf)
  } else {
    if (a.streamSlot >= 0) {
      // rate = *(float*)(+0x1ae0) — per-actor anim rate; STREAM_RATE stands in.
      startStream(a, VALKRIE.PART_MASK, VALKRIE.VOLLEY_GROUP,
        (a.strafeAnimBase ?? 0) + dir, VALKRIE.STREAM_RATE);
    }
    a.streamSlot = dir;                      // +0x6ea = +0x6eb
  }
}

// Volley phase 0 — FUN_8014a284 @ chunk_0038.c:2767.
function volleyPhase0(a: VActor, cfg: ValkrieVolleyConfig): void {
  a.fbPhaseSlots[0] = 1;                     // +0x540 = 1 (direct store)
  a.bBuffered = false;                       // +0x745 = 0
  a.volleyWindow = VALKRIE.VOLLEY_AIM_WINDOW; // +0x560 = FLOAT_8043a3b4 (30)
  a.aimComplete = false;                     // port-side reset; the ROM's u16 store at
                                             // +0x54c does NOT touch +0x54a (inert —
                                             // the prelude rewrites +0x54a each frame)
  a.strafeAnimBase = 0;                      // +0x54c = 0
  a.volleysLeft = cfg.volleyCount;           // +0x6ec = (char)cfg[0]
  a.handlerTimer = cfg.volleyTimerFrames;    // +0x558 = (f32)cfg[1] (CONCAT44 idiom)
  // zz_004beb8_(-1.0, actor, 0xf, 2, (s8)+0x6ea, 4, 2) — the movement init just set
  // +0x6ea = -1, so the first resolve is the no-slot path (parts reset).
  startStream(a, VALKRIE.PART_MASK, VALKRIE.VOLLEY_GROUP, a.streamSlot, VALKRIE.STREAM_RATE);
}

// Volley phase 1 — FUN_8014a308 @ chunk_0038.c:2792. Aim; fire the first shot.
function volleyPhase1(a: VActor, cfg: ValkrieVolleyConfig, ctx: ValkrieFamilyCtx): void {
  a.strafeAnimBase = 0;                      // +0x54c = 0
  // Fire gate: aim window expired (+0x560 < 0.0) OR (anim fire event +0x1cef != 0
  // AND facing complete +0x54a != 0).
  if ((a.volleyWindow ?? 0) < VALKRIE.TIMER_FLOOR ||
      (a.contactP0 !== 0 && a.aimComplete)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.volleysLeft = (a.volleysLeft ?? cfg.volleyCount) - 1; // +0x6ec--
    a.cmdChargedRanged = 0;                  // +0x587 = 0
    if (tryConsumeShotAmmo(a, ctx)) {        // zz_006dbe0_(actor, 0, 1, 1)
      cfg.chainCallback?.(a);                // zz_014a890_ → *(cfg+4)
    }
    a.strafeAnimBase = 5;                    // +0x54c = 5 (fire strafe anims)
  }
}

// Volley phase 2 — FUN_8014a3bc @ chunk_0038.c:2818. Repeat fire / advance.
function volleyPhase2(a: VActor, cfg: ValkrieVolleyConfig, ctx: ValkrieFamilyCtx): void {
  if (a.bRetapInput) a.bBuffered = true;     // +0x5d4 & 0x40 → +0x745 = 1
  a.strafeAnimBase = 0;                      // +0x54c = 0
  if ((a.handlerTimer ?? 0) <= VALKRIE.TIMER_FLOOR) {
    let fired = false;
    if ((a.volleysLeft ?? 0) > 0) {
      a.volleysLeft = (a.volleysLeft ?? 0) - 1;      // +0x6ec--
      a.handlerTimer = cfg.volleyTimerFrames;        // +0x558 = (f32)cfg[1]
      a.cmdChargedRanged = 0;                        // +0x587 = 0
      if (tryConsumeShotAmmo(a, ctx)) {
        // zz_006bf80_(actor) — global reticle-alert bookkeeping (targeting UI
        // side-effect on all 6 actors' +0x5e6; cosmetic — labeled no-op).
        cfg.chainCallback?.(a);                      // zz_014a890_
        fired = true;                                // goto LAB_8014a4c8
      }
    }
    if (!fired) {
      // Advance to recovery (also the ammo-failure path — the ROM falls through).
      a.fbPhaseSlots[0] += 1;                        // +0x540++
      a.volleyRecoveryTimer = VALKRIE.VOLLEY_RECOVERY; // +0x55c = 60.0
      a.strafeAnimBase = 10;                         // +0x54c = 10
      // zz_004beb8_(-1.0, actor, 0xf, 2, +0x6ea + 10, 4, 2) — recovery strafe anim.
      startStream(a, VALKRIE.PART_MASK, VALKRIE.VOLLEY_GROUP,
        (a.streamSlot ?? 0) + 10, VALKRIE.STREAM_RATE);
    }
  } else {
    a.handlerTimer = (a.handlerTimer ?? 0) - a.dt;   // +0x558 -= dt
  }
  // LAB_8014a4c8 — cancel gate, runs on EVERY phase-2 frame.
  if (a.cancelInput) {                       // +0x5d8 & 0xf0
    valkrieReturnToIdle(a, a.grounded === true);     // zz_00677b0_ → 474/4f4
    a.stateTimer = (a.handlerTimer ?? 0) + a.dt;     // +0x694 = +0x558 + dt
  }
}

// Volley phase 3 — FUN_8014a534 @ chunk_0038.c:2874. Recovery + buffered re-fire.
function volleyPhase3(a: VActor, cfg: ValkrieVolleyConfig, ctx: ValkrieFamilyCtx): void {
  if (a.bRetapInput) a.bBuffered = true;     // +0x5d4 & 0x40 → +0x745 = 1
  a.strafeAnimBase = 10;                     // +0x54c = 10
  // Buffered B + ammo → loop BACK to phase 2 (the +0x540 -= 1 backward combo).
  if (a.bBuffered && tryConsumeShotAmmo(a, ctx)) {
    a.fbPhaseSlots[0] -= 1;                  // +0x540 += -1 (3 → 2)
    a.bBuffered = false;                     // +0x745 = 0
    a.volleysLeft = cfg.volleyCount - 1;     // +0x6ec = (char)cfg[0] - 1
    a.handlerTimer = cfg.volleyTimerFrames;  // +0x558 = (f32)cfg[1]
    // zz_006bf80_(actor) — reticle-alert bookkeeping (labeled no-op).
    cfg.chainCallback?.(a);                  // zz_014a890_
    // zz_004beb8_(-1.0, actor, 0xf, 2, +0x6ea + 5, -1, -1) — fire strafe anim.
    startStream(a, VALKRIE.PART_MASK, VALKRIE.VOLLEY_GROUP,
      (a.streamSlot ?? 0) + 5, VALKRIE.STREAM_RATE);
    return;
  }
  // Recovery hold: while no cancel input AND the 60f timer is running AND no wall
  // contact, stay in phase 3 (early return). Note the timer only decrements on the
  // no-cancel path (the ROM's && short-circuit).
  if (!a.cancelInput) {
    a.volleyRecoveryTimer = (a.volleyRecoveryTimer ?? 0) - a.dt; // +0x55c -= dt
    if ((a.volleyRecoveryTimer ?? 0) > VALKRIE.TIMER_FLOOR && a.wallContact === 0) {
      return;
    }
  }
  valkrieReturnToIdle(a, a.grounded === true); // +0x73f = 0; +0x5e0 &= ~3; 474/4f4
}

/** Build the table-A volley handler (engine zz_014a200_). `cfg` is the per-borg
 *  config block. */
export function createValkrieVolley(
  cfg: ValkrieVolleyConfig,
  ctx: ValkrieFamilyCtx,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as VActor;
    // Cue dispatch resets +0x540 AND +0x544 together (zz_006a6fc_/zz_006a750_); the
    // port mirrors by re-seeding the movement sub-phase whenever phase 0 re-enters.
    if ((a.fbPhaseSlots[0] ?? 0) === 0) a.moveSubPhase = 0;
    volleyPrelude(a);                                  // zz_014a7f8_
    if ((a.moveSubPhase ?? 0) === 0) volleyMoveInit(a, ctx); // PTR_FUN_804346b0[0]
    else volleyMoveTick(a, ctx);                       // PTR_FUN_804346b0[1]
    switch (a.fbPhaseSlots[0] ?? 0) {                  // PTR_FUN_8033ed68[+0x540]
      case 0: volleyPhase0(a, cfg); break;
      case 1: volleyPhase1(a, cfg, ctx); break;
      case 2: volleyPhase2(a, cfg, ctx); break;
      case 3: volleyPhase3(a, cfg, ctx); break;
      default: break;
    }
  };
}

/** Action-0 variant 4 wrapper — port of zz_0149ec8_ @ chunk_0038.c:2630. Unless the
 *  +0x7ce state byte is 0xf/0x10 (the alt machine PTR_FUN_8033ed58 — a group-2
 *  slot-0xf/0x10/0x11 roll sequence; TODO @0x80149ec8: +0x7ce writer not yet decoded,
 *  branch unobserved in the corpus emulation) it redirects to variant 2 of table A. */
export function createValkrieVolleyV4(
  cfg: ValkrieVolleyConfig,
  ctx: ValkrieFamilyCtx,
): (actor: RomActor) => void {
  const volley = createValkrieVolley(cfg, ctx);
  return (actor: RomActor) => {
    actor.variantIndex = 2;      // +0x581 = 2 (next frame dispatches variant 2's leaf)
    actor.fbPhaseSlots[0] = 0;   // +0x540 = 0
    volley(actor);               // zz_014a200_(actor, cfg)
  };
}

// ============================================================================
// Table B — B melee mash (engine zz_014a8c0_ @0x8014a8c0, chunk_0038.c:3032).
// ============================================================================

// Dash-velocity helper FUN_8014acdc @ chunk_0038.c:3194.
function valkrieComputeDash(a: VActor): void {
  let f = VALKRIE.TIMER_FLOOR;               // FLOAT_8043a3c0
  if (a.lockTarget) {                        // +0xcc != 0
    // fVar1 = +0x760 × (s8)+0x1d0f × FLOAT_8043a3dc (0.0625).
    const strength = a.dashStrength ?? VALKRIE.DEFAULT_DASH_STRENGTH;
    f = targetDistance(a) * strength * VALKRIE.DASH_STRENGTH_SCALE;
  }
  a.motion.x = f / VALKRIE.DASH_WINDOW;      // +0x38 = f / FLOAT_8043a3cc (20)
  const pitch = a.meleeAimPitch ?? 0;        // +0x54e
  a.hSpeed = a.motion.x * projectZ(pitch);   // +0x44 = +0x38 × cos (zz_0045238_)
  a.yVel = a.motion.x * -projectX(pitch);    // +0x48 = +0x38 × -sin (zz_0045204_)
  a.dashStrength = 0;                        // +0x1d0f = 0
}

// Phase 0 — FUN_8014a91c @ chunk_0038.c:3047. Stream start + air check.
function meleePhase0(a: VActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.bRetap = false;                          // +0x746 = 0
  a.streamSlot = seedSlot;                   // +0x6ea = param_2
  // Air check FUN_80066838((+0x584 % 3)-row float @+0x868, actor) < 1 → airborne:
  // +0x541 = 1, +0xcc = 0, +0x5ae = +0x5ac = +0x72 (yaw snapshot to heading).
  if (!a.grounded) {
    a.fbPhaseSlots[1] = 1;                   // +0x541 = 1
    a.lockTarget = null;                     // +0xcc = 0
    a.lockYaw = a.heading;
    a.activeYaw = a.heading;
  } else {
    a.activeYaw = a.lockYaw;                 // bridge pre-aim (shared-melee-gred precedent)
  }
  a.handlerTimer = VALKRIE.FACE_BUDGET;      // +0x558 = FLOAT_8043a3c4 (60)
  a.meleeAimPitch = 0;                       // +0x54e = 0
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  // zz_004beb8_(-1.0, actor, 0xf, 3, slot, 5, 1).
  startStream(a, VALKRIE.PART_MASK, VALKRIE.MELEE_GROUP, slot, VALKRIE.STREAM_RATE);
}

// Phase 1 — FUN_8014a9f0 @ chunk_0038.c:3078. Face budget → dash arm.
function meleePhase1(a: VActor, ctx: ValkrieFamilyCtx): void {
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, VALKRIE.PART_MASK, ctx);   // zz_004cd24_(actor, 0xf)
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Transition: timer <= 0.0 OR zz_006d144_(actor, 0xc0) facing complete.
  if (a.handlerTimer <= VALKRIE.TIMER_FLOOR || faceLockTargetComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = VALKRIE.DASH_WINDOW;    // +0x558 = FLOAT_8043a3cc (20)
    valkrieComputeDash(a);                   // FUN_8014acdc
    // zz_00b2190_(actor, 0) — melee trail FX child (chunk_0038.c:3098;
    // shared-aerial-dive-x.ts:458 precedent).
    ctx.onFamilyProjectile?.(a, VALKRIE_SPAWNERS.MELEE_FX, 0);
  }
}

// Phase 2 — FUN_8014aa88 @ chunk_0038.c:3105. Active dash frames.
function meleePhase2(a: VActor, ctx: ValkrieFamilyCtx): void {
  // zz_006d144_(actor, 0xc0) — face target (bridge pre-aims lockYaw).
  seekMeleeAimPitch(a);                      // zz_006e514_(actor, 0xc0, &+0x54e)
  const pitch = a.meleeAimPitch ?? 0;
  a.hSpeed = a.motion.x * projectZ(pitch);   // +0x44 = +0x38 × cos(+0x54e)
  a.yVel = a.motion.x * -projectX(pitch);    // +0x48 = +0x38 × -sin(+0x54e)
  integratePhysics(VALKRIE.GRAVITY_PARAM, a, a.lockYaw); // FUN_80067310(1.0, a, +0x5ae)
  // zz_00677b0_(actor) — ground collide (bridge clamp).
  if (a.contactP0 === 0) {                   // +0x1cef == 0 → stream advances
    tickStream(a, VALKRIE.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Transition: timer <= 0.0 OR FUN_800668cc(FLOAT_8043a3d0=200, actor) in range.
  const dist = targetDistance(a);
  const inProximity = a.lockTarget != null && dist <= VALKRIE.PROXIMITY;
  if (a.handlerTimer <= VALKRIE.TIMER_FLOOR || inProximity) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
  }
}

// Phase 3 — FUN_8014ab64 @ chunk_0038.c:3139. Combo loop / recovery.
function meleePhase3(a: VActor, ctx: ValkrieFamilyCtx): void {
  if (a.bRetapInput) a.bRetap = true;        // +0x5d4 & 0x40 → +0x746 = 1
  tickStream(a, VALKRIE.PART_MASK, ctx);     // zz_004cd24_(actor, 0xf)
  // COMBO: (s8)+0x1cf0 < 0 (swing re-arm event) AND +0x746 (B retap latched).
  if ((a.swingEvent ?? 0) < 0 && a.bRetap) {
    a.fbPhaseSlots[0] -= 1;                  // +0x540 += -1 (3 → 2, backward loop)
    a.bRetap = false;                        // +0x746 = 0
    a.handlerTimer = VALKRIE.DASH_WINDOW;    // +0x558 = FLOAT_8043a3cc (20)
    const slot = a.streamSlot;               // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                 // +0x6ea++
    // zz_004beb8_(-1.0, actor, 0xf, 3, slot, -1, -1).
    startStream(a, VALKRIE.PART_MASK, VALKRIE.MELEE_GROUP, slot, VALKRIE.STREAM_RATE);
    valkrieComputeDash(a);                   // FUN_8014acdc
    // zz_00b2190_(actor, 0) — melee trail FX child (chunk_0038.c:3163).
    ctx.onFamilyProjectile?.(a, VALKRIE_SPAWNERS.MELEE_FX, 0);
    return;
  }
  if ((a.faceGate ?? 0) !== 0) {             // +0x1d10 != 0 → re-face + re-pitch
    // zz_006d144_(actor, 0xc0) — bridge pre-aims.
    seekMeleeAimPitch(a);                    // zz_006e514_(actor, 0xc0, &+0x54e)
  }
  if ((a.dashStrength ?? 0) !== 0) {         // +0x1d0f != 0 → re-apply dash velocity
    valkrieComputeDash(a);                   // FUN_8014acdc (consumes the byte)
  }
  // zz_006ed8c_(FLOAT_8043a3d4 = 0.9, actor) — recovery drag.
  a.hSpeed *= VALKRIE.RECOVERY_DRAG;
  a.yVel *= VALKRIE.RECOVERY_DRAG;
  // +0x760 < FLOAT_8043a3d0 → zz_006ed8c_(FLOAT_8043a3d8 = 0.5) extra brake.
  // UNCONDITIONAL in the ROM (chunk_0038.c:3174) — no +0xcc lock guard; the stale
  // +0x760 scalar still brakes after a lock drop (targetDistance serves the cache).
  if (targetDistance(a) < VALKRIE.PROXIMITY) {
    a.hSpeed *= VALKRIE.NEAR_DRAG;
    a.yVel *= VALKRIE.NEAR_DRAG;
  }
  integratePhysics(VALKRIE.GRAVITY_PARAM, a, a.activeYaw); // FUN_80067310(1.0, a, +0x5ac)
  const grounded = a.grounded === true;      // iVar3 = zz_00677b0_(actor)
  if (a.wallContact !== 0) {                 // +0x1cee != 0 → end the move
    valkrieReturnToIdle(a, grounded);        // +0x73f = 0; +0x5e0 &= ~3; 474/4f4
  }
}

/** Build the table-B melee handler (engine zz_014a8c0_). */
export function createValkrieMelee(
  ctx: ValkrieFamilyCtx,
  seedSlot = 0,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as VActor;
    // +0x18da >>= 1 — arithmetic s16 halving of the steering pitch each frame.
    a.steerYaw = s16(a.steerYaw) >> 1;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) {    // +0x541 != 0 → +0xcc = 0
      a.lockTarget = null;
    }
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8033ed78[+0x540]
      case 0: meleePhase0(a, seedSlot); break;
      case 1: meleePhase1(a, ctx); break;
      case 2: meleePhase2(a, ctx); break;
      case 3: meleePhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// Table C — air/lunge dive melee (engine zz_014ad94_ @0x8014ad94, chunk_0038.c:3224).
// ============================================================================

// Phase 0 — FUN_8014ade4 @ chunk_0038.c:3238. Blink-away + stream start.
function airMeleePhase0(a: VActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.handlerTimer = VALKRIE.FACE_BUDGET;      // +0x558 = FLOAT_8043a3c4 (60)
  a.streamSlot = seedSlot;                   // +0x6ea = param_2
  // Air check FUN_80066838((+0x584 % 3)-row float @+0x86c, actor) < 1 → airborne:
  // +0x541 = 1, +0xcc = 0, +0x5ac = +0x5ae (NOTE: reversed vs table B — active yaw
  // snaps to the LOCK yaw here).
  if (!a.grounded) {
    a.fbPhaseSlots[1] = 1;                   // +0x541 = 1
    a.lockTarget = null;                     // +0xcc = 0
    a.activeYaw = a.lockYaw;                 // +0x5ac = +0x5ae
  }
  // zz_006d144_(actor, 0xc0) face + zz_006e1ac_(actor, 0xc0, 1) pitch seek — the
  // bridge pre-aims lockYaw; the pitch channel (+0x18da) is seeded by the dive.
  // Reposition (chunk_0038.c:3261-3264): motion = (pos − target@+0x5e8) × 0.95;
  // pos += motion (the ninja-style blink-away).
  if (a.lockTarget) {
    vecSubtract(a.pos, a.lockTarget, a.motion);
    vecScale(VALKRIE.DRAG, a.motion, a.motion);      // FLOAT_8043a3c8 (0.95)
    vecAdd(a.pos, a.motion, a.pos);
  }
  // zz_00677b0_(actor) — ground collide (bridge clamp).
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  // zz_004beb8_(-1.0, actor, 0xf, 3, slot, -1, -1).
  startStream(a, VALKRIE.PART_MASK, VALKRIE.MELEE_GROUP, slot, VALKRIE.STREAM_RATE);
}

// Phase 1 — FUN_8014aef8 @ chunk_0038.c:3275. Drift-back + dive arm.
function airMeleePhase1(a: VActor, ctx: ValkrieFamilyCtx): void {
  // motion ×= 0.95; pos += motion (continued drift-away).
  vecScale(VALKRIE.DRAG, a.motion, a.motion);
  vecAdd(a.pos, a.motion, a.pos);
  // zz_00677b0_(actor) — ground collide (bridge clamp).
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, VALKRIE.PART_MASK, ctx);
  }
  // zz_006e1ac_(actor, 0xc0, 1) — pitch seek (bridge-side aim channel).
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Transition: timer <= 0.0 OR zz_006d144_(actor, 0xc0) facing complete.
  if (a.handlerTimer <= VALKRIE.TIMER_FLOOR || faceLockTargetComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = VALKRIE.DIVE_WINDOW;    // +0x558 = FLOAT_8043a3e0 (29)
    a.meleeAimPitch = VALKRIE.DIVE_PITCH_SEED; // +0x54e = 0xf
    a.hDecel = VALKRIE.TIMER_FLOOR;          // +0x4c = 0
    a.gravityCoeff = VALKRIE.TIMER_FLOOR;    // +0x50 = 0
    // zz_0092dcc_(actor, 0) — dive FX child spawn.
    ctx.onFamilyProjectile?.(a, VALKRIE_SPAWNERS.DIVE_FX, 0);
  }
}

// Phase 2 — FUN_8014afd8 @ chunk_0038.c:3309. The 30-speed dive.
function airMeleePhase2(a: VActor, ctx: ValkrieFamilyCtx): void {
  // Hit-pause extension: uVar3 = zz_006de44_(actor, 0xf0f00) hit frames; burn
  // min(uVar3, +0x54e) off the pitch countdown and add it to the timer. Without
  // byte-loaded stream data the helper returns 0 (shared-charge precedent) — no-op.
  tickStream(a, VALKRIE.PART_MASK, ctx);     // zz_004cd24_(actor, 0xf)
  // zz_006d144_(actor, 0xc0) face + zz_006e1ac_(actor, 0xc0, 1) pitch seek.
  const pitch = s16(a.steerYaw);             // +0x18da (the aim-pitch channel)
  a.hSpeed = VALKRIE.DIVE_SPEED * projectZ(pitch);  // +0x44 = 30 × cos(+0x18da)
  a.yVel = VALKRIE.DIVE_SPEED * -projectX(pitch);   // +0x48 = 30 × -sin(+0x18da)
  integratePhysics(VALKRIE.GRAVITY_PARAM, a, a.lockYaw); // FUN_80067310(1.0, a, +0x5ae)
  // zz_00677b0_(actor) — ground collide (bridge clamp).
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= VALKRIE.TIMER_FLOOR) {
    a.handlerTimer = VALKRIE.TIMER_FLOOR;    // +0x558 = 0.0
    // +0x1b01 != 0 (anim dive-end byte) → recovery. UNWIRED FALLBACK: treat the
    // expired window as the end event (anim layer owns the byte).
    if (a.diveEndGate !== false) {
      a.fbPhaseSlots[0] += 1;                // +0x540++
      a.gravityCoeff = gravityRestore(a);    // +0x50 = dataPage(+0x4ac)+0x6c
      // zz_004beb8_(-1.0, actor, 0xf, 3, (s8)+0x6ea, -1, -1) — recovery swing (the
      // CURRENT slot, no increment).
      startStream(a, VALKRIE.PART_MASK, VALKRIE.MELEE_GROUP, a.streamSlot, VALKRIE.STREAM_RATE);
    }
  }
}

// Phase 3 — FUN_8014b130 @ chunk_0038.c:3358. Landing recovery.
function airMeleePhase3(a: VActor, ctx: ValkrieFamilyCtx): void {
  // +0x18da = (s16)((f32)(s16)+0x18da × FLOAT_8043a3d4 (0.9)) — pitch decay.
  a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * VALKRIE.RECOVERY_DRAG));
  tickStream(a, VALKRIE.PART_MASK, ctx);     // zz_004cd24_(actor, 0xf)
  // zz_006ed8c_(FLOAT_8043a3c8 = 0.95, actor) — drag.
  a.hSpeed *= VALKRIE.DRAG;
  a.yVel *= VALKRIE.DRAG;
  integratePhysics(VALKRIE.GRAVITY_PARAM, a, a.lockYaw); // FUN_80067310(1.0, a, +0x5ae)
  const grounded = a.grounded === true;      // iVar1 = zz_00677b0_(actor)
  if (grounded && a.contactP0 < 0) {         // landed + (s8)+0x1cef < 0
    a.controlWord = a.controlWord & ~0x3;    // +0x73f = 0; +0x5e0 &= ~3
    dispatchUpperBodyCue(a, 7);              // zz_006a750_(actor, 7)
    a.stateTimer = VALKRIE.GRAVITY_PARAM + a.dt; // +0x694 = FLOAT_8043a3b0 (1) + dt
    return;
  }
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    a.controlWord = a.controlWord & ~0x3;    // +0x73f = 0; +0x5e0 &= 0xfffffffc
    // zz_006a5a4_ @ chunk_0009.c:770-797 — airborne knock-out return:
    // +0x590 = 1, +0x690 = 0.0, +0x71b = 0 — not surfaced on RomActor (labeled
    // no-ops). The (+0x5e0 & 3) == 3 arm (freeze-release zz_005c080_ + 30f +0x694
    // floor, FLOAT_80437648) is unreachable here — the caller just cleared bits
    // 0..1 — so the else arm applies:
    a.controlWord &= 0xff0041;               // +0x5e0 &= 0xff0041
    // +0x1d9b != 0 stream-authored launch block (+0x5ae = +0x1db0 + +0x72;
    // +0x44 = +0x1dac) — stream bytes not surfaced (labeled no-op).
    dispatchUpperBodyCue(a, 6);              // zz_006a750_(a, 6)
  }
}

/** Build the table-C air/lunge melee handler (engine zz_014ad94_). */
export function createValkrieAirMelee(
  ctx: ValkrieFamilyCtx,
  seedSlot = 3,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as VActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) {    // +0x541 != 0 → +0xcc = 0
      a.lockTarget = null;
    }
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8033ed88[+0x540]
      case 0: airMeleePhase0(a, seedSlot); break;
      case 1: airMeleePhase1(a, ctx); break;
      case 2: airMeleePhase2(a, ctx); break;
      case 3: airMeleePhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// Table D — X special (engine zz_014b22c_ @0x8014b22c, chunk_0038.c:3390).
// Valkries only — DEATH BORG LAMBDA has no action 2.
// ============================================================================

// Phase 0 — FUN_8014b278 @ chunk_0038.c:3404. Reposition + g4 stream start.
function xPhase0(a: VActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.streamSlot = seedSlot;                   // +0x6ea = param_2
  a.comboHitsA = 0;                          // +0x6f2 = 0
  a.comboHitsB = 0;                          // +0x6f3 = 0
  a.bBuffered = false;                       // +0x745 = 0
  if (!a.lockTarget) {                       // +0xcc == 0 → +0x5ac = +0x72
    a.activeYaw = a.heading;
  }
  // zz_006d144_(actor, 0xc1) face + zz_006e1ac_(actor, 0xc1, 1) pitch seek (bridge).
  a.gravityCoeff = VALKRIE.TIMER_FLOOR;      // +0x50 = 0
  a.yVel = VALKRIE.TIMER_FLOOR;              // +0x48 = 0
  a.hDecel = VALKRIE.TIMER_FLOOR;            // +0x4c = 0
  a.hSpeed = VALKRIE.TIMER_FLOOR;            // +0x44 = 0
  // +0x80 = +0x7e = +0x7c = 0 — aim-rate accumulators (renderer-side; not surfaced).
  // Reposition (chunk_0038.c:3431-3434): motion = (pos − target@+0x5e8) × 0.98;
  // pos += motion.
  if (a.lockTarget) {
    vecSubtract(a.pos, a.lockTarget, a.motion);
    vecScale(VALKRIE.X_REPOSITION, a.motion, a.motion); // FLOAT_8043a3e4 (0.98)
    vecAdd(a.pos, a.motion, a.pos);
  }
  // zz_0067a28_(actor) — ground collide + airborne-bit upkeep (bridge clamp).
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  // zz_004beb8_(-1.0, actor, 0xf, 4, slot, -1, -1).
  startStream(a, VALKRIE.PART_MASK, VALKRIE.X_GROUP, slot, VALKRIE.STREAM_RATE);
}

// Phase 1 — FUN_8014b378 @ chunk_0038.c:3445. Drift loop + WIND VALKRIE combo.
function xPhase1(a: VActor, ctx: ValkrieFamilyCtx): void {
  tickStream(a, VALKRIE.PART_MASK, ctx);     // zz_004cd24_(actor, 0xf)
  const gate = a.faceGate ?? 0;              // +0x1d10 bitfield
  if ((gate & 1) !== 0) {
    // zz_006d144_(actor, 0xc1) — re-face (bridge pre-aims).
  }
  if ((gate & 2) !== 0) {
    // zz_006e1ac_(actor, 0xc1, 1) — re-pitch (bridge aim channel).
  }
  if (a.contactP0 < 0) {                     // (s8)+0x1cef < 0 → gravity restore
    a.contactP0 = 0;                         // +0x1cef = 0
    a.gravityCoeff = gravityRestore(a);      // +0x50 = dataPage(+0x4ac)+0x6c
  }
  integratePhysics(VALKRIE.GRAVITY_PARAM, a, a.lockYaw); // FUN_80067310(1.0, a, +0x5ae)
  // Drift decay: motion ×= 0.98; pos += motion.
  vecScale(VALKRIE.X_REPOSITION, a.motion, a.motion);
  vecAdd(a.pos, a.motion, a.pos);
  const grounded = a.grounded === true;      // iVar3 = zz_0067a28_(actor)
  // WIND VALKRIE (borg 0xb03 @ +0x3e8) combo block (chunk_0038.c:3470-3488).
  if (a.borgNumber === 0xb03) {
    if ((a.swingEvent ?? 0) !== 0) {         // +0x1cf0 != 0 → hit landed
      a.comboHitsA = 2;                      // +0x6f2 = 2
      a.comboHitsB = 2;                      // +0x6f3 = 2
    }
    if (a.xComboSuppressInput) {             // +0x5bc & 0x200 → +0x745 = 1
      a.bBuffered = true;
    }
    if (a.followUpEvent) {                   // +0x1cf2 != 0 → follow-up stream event
      if (!a.bBuffered) {                    // +0x745 == 0 → chain the next g4 slot
        const slot = a.streamSlot;           // cVar1 = +0x6ea
        a.streamSlot = slot + 1;             // +0x6ea++
        // zz_004beb8_(-1.0, actor, 0xf, 4, slot, -1, -1).
        startStream(a, VALKRIE.PART_MASK, VALKRIE.X_GROUP, slot, VALKRIE.STREAM_RATE);
        return;
      }
      a.bBuffered = false;                   // +0x745 = 0 (suppressed one follow-up)
    }
  }
  if (a.wallContact !== 0) {                 // +0x1cee != 0 → end the move
    a.hDecel = VALKRIE.TIMER_FLOOR;          // +0x4c = 0
    a.hSpeed = VALKRIE.TIMER_FLOOR;          // +0x44 = 0
    // chunk_0038.c:3490-3500 — same teardown + zz_006a474_/zz_006a4f4_ pick.
    valkrieReturnToIdle(a, grounded);
  }
}

/** Build the table-D X-special handler (engine zz_014b22c_). Phases 2/3 of the DOL
 *  table are the adjacent-table overlap (see header) — unreachable, not ported. */
export function createValkrieXSpecial(
  ctx: ValkrieFamilyCtx,
  seedSlot = 0,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as VActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) {    // +0x541 != 0 → +0xcc = 0
      a.lockTarget = null;
    }
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_804346b8[+0x540]
      case 0: xPhase0(a, seedSlot); break;
      case 1: xPhase1(a, ctx); break;
      default: break;                        // slots 2/3 = table overlap (unreachable)
    }
  };
}

// ============================================================================
// Per-borg wiring.
// ============================================================================

export type ValkrieBorgId =
  | "pl0b00" | "pl0b01" | "pl0b02" | "pl0b03" | "pl0b04" | "pl0b05" | "pl0b06" | "pl0b07";

const VALKRIE_BORG_NUMBERS: Record<ValkrieBorgId, number> = {
  pl0b00: 0xb00, pl0b01: 0xb01, pl0b02: 0xb02, pl0b03: 0xb03,
  pl0b04: 0xb04, pl0b05: 0xb05, pl0b06: 0xb06, pl0b07: 0xb07,
};

/** Volley shot record per borg (the zz_0082824_ record argument). */
const VOLLEY_SHOT_RECORD: Partial<Record<ValkrieBorgId, number>> = {
  pl0b00: 0x1a, // FUN_800de4d8 @ chunk_0023.c:4088
  pl0b01: 0x3d, // FUN_8015d5a8 @ chunk_0041.c
  pl0b02: 0x3e, // FUN_80160b18 @ chunk_0041.c
  pl0b03: 0x3f, // FUN_80160f30 @ chunk_0041.c
  pl0b05: 0x40, // zz_019e89c_ @ chunk_0049.c (borg 0xb05 arm)
  pl0b06: 0x41, // zz_01a5514_ @ chunk_0050.c
  pl0b07: 0x71, // zz_019e89c_ @ chunk_0049.c (borg 0xb07 arm)
};

/** Build the per-borg volley chain callback (the config-block +0x4 pointer). */
export function valkrieChainCallback(
  borgId: ValkrieBorgId,
  ctx: ValkrieFamilyCtx,
): (actor: RomActor) => void {
  if (borgId === "pl0b04") {
    // FUN_80161308 @ chunk_0041.c — RING VALKRIE: 5× zz_016ddb0_(actor, 0..4).
    return (actor) => {
      for (let i = 0; i < 5; i++) {
        ctx.onFamilyProjectile?.(actor, VALKRIE_SPAWNERS.RING_CHILD, i);
      }
    };
  }
  const record = VOLLEY_SHOT_RECORD[borgId]!;
  return (actor) => {
    // zz_019e89c_ is borg-switched at runtime; the registration resolves it per id.
    ctx.onFamilyProjectile?.(actor, VALKRIE_SPAWNERS.GENERIC_SHOT, record);
    // pl0b07 extra: +0x168..+0x16b |= 0x80 — part-glow flag bytes (renderer-side;
    // not surfaced on RomActor — labeled no-op).
  };
}

/** DOL-read volley config per borg (see header table). */
export function valkrieVolleyConfig(
  borgId: ValkrieBorgId,
  ctx: ValkrieFamilyCtx,
): ValkrieVolleyConfig {
  return {
    volleyCount: borgId === "pl0b04" ? 1 : 5,        // cfg s16[0]
    volleyTimerFrames: borgId === "pl0b04" ? 20 : 4, // cfg s16[2]
    chainCallback: valkrieChainCallback(borgId, ctx),
  };
}

/**
 * Configure a valkrie-cluster borg. Wires:
 *   action 0 → table A volley (v0-3 direct; v4 via the zz_0149ec8_ redirect)
 *   action 1 → table B melee (v0-3) / table C air-lunge melee (v4, seed slot 3)
 *   action 2 → table D X special (valkries only — pl0b05/pl0b07 have no action 2)
 */
export function configureValkrieFamily(
  actor: RomActor,
  borgId: ValkrieBorgId,
  ctx: ValkrieFamilyCtx,
): void {
  actor.borgNumber = VALKRIE_BORG_NUMBERS[borgId];
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  const isLambda = borgId === "pl0b05" || borgId === "pl0b07";
  const cfg = valkrieVolleyConfig(borgId, ctx);
  const volley = createValkrieVolley(cfg, ctx);
  const volleyV4 = createValkrieVolleyV4(cfg, ctx);
  const melee = createValkrieMelee(ctx, 0);      // a1 v0-3: seed slot 0
  const airMelee = createValkrieAirMelee(ctx, 3); // a1 v4: seed slot 3
  const xSpecial = isLambda ? null : createValkrieXSpecial(ctx, 0); // a2: seed slot 0
  actor.rootAction = (a: RomActor) => {
    switch (a.actionIndex) {
      case 0: (a.variantIndex >= 4 ? volleyV4 : volley)(a); break;
      case 1: (a.variantIndex >= 4 ? airMelee : melee)(a); break;
      case 2: if (xSpecial) xSpecial(a); break;
      default: break; // other actions → generic fallback
    }
  };
}
