// SAMURAI cluster — 1:1 port of the shared + per-family phase-table machines used by
// 6 families / 13 borgs (DOL pointer-table dumps confirm every boundary below):
//   NORMAL SAMURAI   pl0700 / pl0709 MUSASHI          (ctor 0x800c7c80)
//   DEMON SAMURAI    pl0701 / pl0708 AKUMA / pl070c/pl070d DEATH BORG ZETA III/IV
//                                                     (ctor 0x801223c0)
//   VAMPIRE KNIGHT   pl0702 / pl070a VLAD             (ctor 0x80143b7c)
//   SONIC SAMURAI    pl0703                           (ctor 0x80164324)
//   SAMURAI SHOGUN   pl0704 / pl0707 CHRONO SAMURAI   (ctor 0x80174d88)
//   DEATH BORG ZETA  pl0705 / pl070b                  (ctor 0x8019c510)
//
// SHARED core machines (decomp: research/decomp/ghidra-export/chunk_0038.c):
//   Table S-A @0x8033ed0c — action 0 (B ranged dash-slash), 5 phases (DOL dump:
//     [FUN_80148874 :1824, FUN_80148968 :1867, FUN_80148ab0 :1904, FUN_80148ba0 :1942,
//      FUN_80148cb0 :1987]; entries 5/6 are the S-B table start = past end).
//     Engine dispatcher FUN_80148838 :1813; action-0 wrapper FUN_801487c4 :1798
//     (steerYaw ×0.9 decay, variant table PTR_FUN_8033ecf8 @0x8033ecf8 = 5×FUN_80148838
//     — every variant identical, DOL-confirmed).
//   Table S-B @0x8033ed20 — action 1 v0/v1 (B close slash), 3 phases (DOL dump:
//     [FUN_80148dc4 :2032, FUN_80148ea8 :2068, FUN_80148f4c :2093]; entries 3/4 are the
//     zz_0149178_ lunge table @0x8033ed2c = past end). Dispatcher zz_0148d74_ :2018.
//     CONFIG-DRIVEN (param_2): per-family blocks, all byte-identical (DOL-read):
//       v0 (seed 0): 0x8030800c / 0x8032c7a4 / 0x8033c36c / 0x8034d558 / 0x803737dc /
//                    0x803518f4 → [0, 150.0, 0.05, 0.92, 0.80]
//       v1 (seed 4): 0x80308038 / 0x8032c7d0 / 0x8033c398 / 0x8034d584 / 0x80373808
//                    → [4, 150.0, 0.05, 0.95, 0.50]
//
// OVERLAP VERDICT vs families/melee-samurai.ts (zz_0149178_ @0x80149178, table
// 0x8033ed2c): DIFFERENT machine — S-B is a 3-phase in-place combo slash (retap loop
// stays in phase 2, stream-authored +0x1d0f dash bytes); zz_0149178_ is the 4-phase
// blink-reposition lunge. Both are used by these borgs: S-B at action-1 v0/v1,
// zz_0149178_ at v3/v4. The lunge is REUSED (createMeleeSamurai) with the REAL config
// (SAMURAI_LUNGE_ROM_CONFIG below, DOL-read — replaces the TUNED default).
//
// PER-FAMILY action-1 v2 machines (boundaries all DOL-delta-confirmed):
//   NORMAL  @0x8030804c 6 ph: FUN_800c8124/81e0/82d4/8388/8404/848c (chunk_0020.c:4930)
//   ZETA    @0x8037381c 6 ph: FUN_8019cba0/cc5c/cd50/ce04/ce80/cf08 (chunk_0048.c:4600)
//     — instruction-level CODE CLONE of NORMAL at a different float bank; values differ
//     in ONE constant (leap gravity −2.3703704 @0x80438850 vs −4.0 @0x8043b45c) →
//     ported ONCE parameterized (createRisingSlash).
//   SHOGUN  @0x80351924 6 ph: FUN_80175a70/75b2c/75c20/75cd4/75d58/75e00 (chunk_0044.c)
//     — same 6-phase shape, third float bank (leap 40 / −3, extra rise-timer seed +
//     timer-gated fall) → same parameterized machine.
//   DEMON   @0x8032c7e4 7 ph: FUN_80122dec/22ea8/22fd4/230fc/231b8/23254/23318
//     (chunk_0033.c:1333; entries 7/8 = X leaf 0x801233cc = past end)
//   VAMPIRE @0x8033c3ac 5 ph: FUN_801440e8/441a4/442a4/44344/443e4 (chunk_0037.c:3782;
//     0x80144504 repeats = past end)
//   SONIC   @0x8034d598 4 ph: FUN_801647a0/64878/64968/64a14 (chunk_0042.c:2076;
//     0x80164b4c repeats = past end)
//   SHOGUN v1 @0x80351914 4 ph: FUN_8017570c/757c8/758c8/7597c
//   SHOGUN v3/v4 @0x80351908 3 ph: FUN_80175270 / zz_0175380_ / FUN_80175508
//     (phase 0 TAIL-CALLS the phase-1 body in the same frame)
//
// PER-FAMILY X (action 2):
//   NORMAL/DEMON/VAMPIRE/ZETA → shared lance-flight engine zz_0149708_ @0x80149708
//     (families/shared-flight-x.ts, ALREADY PORTED — reused, not re-transcribed).
//     Configs: FAMILY1 @0x80308078, FAMILY2A @0x8032c814 (pl0701/pl0708),
//     FAMILY2B @0x8032c838 (pl070c/pl070d), FAMILY3 @0x8033c3d4, FAMILY4 @0x80373848.
//   SONIC  OWN table @0x8034d5bc 6 ph: FUN_80164b9c/64ce0/64dac/64e8c/64f98/650a8
//     (chunk_0042.c:2204; entries 6/7 = 0 / junk = past end)
//   SHOGUN OWN table @0x80351950 4 ph: FUN_80175ee8/75ffc/760b4/76170
//     (chunk_0044.c; entries 4/5 = junk = past end)
//
// Float constants — every value DOL-read from user-data/GG4E/disc/sys/boot.dol; the
// 0x43300000 CONCAT44 idiom (DOUBLE_8043a368/80438828/8043a268/8043a980/8043ad60/
// 80438860/80439b18) is the s16→f32 conversion sentinel, NOT gameplay data.
//   Shared bank: FLOAT_8043a360=0.9 (steer decay)  FLOAT_8043a370=20 (a0 window)
//     FLOAT_8043a374=0  FLOAT_8043a378=1 (gravity)  FLOAT_8043a37c=-1 (stream rate)
//     FLOAT_8043a380=3 (afterimage gate)  FLOAT_8043a384=60 (face budget)
//     FLOAT_8043a388=8 (cooldown)  FLOAT_8043a38c=0.95 (recovery drag)
//     FLOAT_8043a390=0.0625 (dash-byte scale)
//   (per-family banks are cited inline at each machine)
//
// Idle-return cues use the CORRECTED valkrie.ts mappings (decomp-verified against
// zz_006a474_/zz_006a4f4_/zz_006a5a4_ themselves):
//   zz_006a474_ = ground idle return (upper cue 0 + velocity zeroing)
//   zz_006a5a4_ = airborne knock-out return (upper cue 6, +0x5e0 &= 0xff0041 arm)
//   zz_006a750_(a, 7) = landing cue 7

import type { RomActor } from "../rom/actor.js";
import { dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { createMeleeSamurai, type MeleeSamuraiConfig } from "./melee-samurai.js";
import {
  createSharedFlightX,
  FLIGHT_X_FAMILY1_CONFIG,
  FLIGHT_X_FAMILY2A_CONFIG,
  FLIGHT_X_FAMILY2B_CONFIG,
  FLIGHT_X_FAMILY3_CONFIG,
  FLIGHT_X_FAMILY4_CONFIG,
} from "./shared-flight-x.js";

/** Shared-core constants (FLOAT_8043a3xx bank, DOL-read — see header). */
export const SAMURAI = {
  STEER_DECAY: 0.9,        // FLOAT_8043a360 (action-0/1 wrapper pitch decay; the
                           // per-family action-1 wrappers read their own banks —
                           // FLOAT_80438820/80439b20/8043a260/8043a978/8043ad58 — all
                           // DOL-read 0.9, so one constant serves every wrapper)
  A0_WINDOW: 20.0,         // FLOAT_8043a370 (+0x560 dash-slash window)
  ZERO: 0.0,               // FLOAT_8043a374
  GRAVITY: 1.0,            // FLOAT_8043a378
  STREAM_RATE: -1.0,       // FLOAT_8043a37c
  AFTERIMAGE_MIN: 3.0,     // FLOAT_8043a380 (zz_00b22f4_ gate — FX no-op here)
  FACE_BUDGET: 60.0,       // FLOAT_8043a384
  COOLDOWN: 8.0,           // FLOAT_8043a388 (+0x694 landing seed)
  RECOVERY_DRAG: 0.95,     // FLOAT_8043a38c
  DASH_BYTE_SCALE: 0.0625, // FLOAT_8043a390 ((s8)+0x1d0f strength scale)
  RANGED_GROUP: 2,
  MELEE_GROUP: 3,
  X_GROUP: 4,
  PART_MASK: 0xf,
  /** actor+0x868 3-row range table (column 0; +0x86c = column 1) — copied from the
   *  borg data page at ctor time (writer not yet extracted for this cluster). TUNED
   *  fallback until the data-page extractor lands (shared-aerial-dive-x RANGE_ROWS
   *  precedent used its family's DOL rows; the samurai rows are unread). */
  DEFAULT_RANGE_ROW: 1000.0,
  /** (s8)+0x1d0f dash-strength byte default when the host hasn't stamped the field
   *  (stream-authored; the byte writer is unmodeled). 16 × 0.0625 = 1.0 → S-B dash
   *  speed = dist × cfg.dashScale, and the rising-slash phase-3 leap gate fires
   *  instead of deadlocking. TUNED fallback — valkrie.ts DEFAULT_DASH_STRENGTH
   *  precedent. */
  DEFAULT_DASH_STRENGTH: 16,
  /** (s8)+0x1cf0 swing-event byte default when unstamped: −1 = "swing fired /
   *  re-armed", so the VAMPIRE phase-3 and SHOGUN-X phase-2 event waits advance and
   *  a host-stamped B retap can still combo in S-B phase 2 instead of the machine
   *  waiting forever on an unmodeled stream byte. TUNED fallback (labeled). */
  DEFAULT_SWING_EVENT: -1,
} as const;

/** ROM spawner addresses routed through ctx.onFamilyProjectile. */
export const SAMURAI_SPAWNERS = {
  /** zz_00b2190_ @0x800b2190 — melee trail/FX child (valkrie MELEE_FX precedent). */
  MELEE_FX: 0x800b2190,
  /** zz_0092dcc_ @0x80092dcc — dive FX child (valkrie DIVE_FX precedent). */
  DIVE_FX: 0x80092dcc,
  /** zz_01a5e88_ @0x801a5e88 — SHOGUN X trail child (record kind 0x26, chunk_0050.c). */
  SHOGUN_X_TRAIL: 0x801a5e88,
  /** zz_018eea4_ @0x8018eea4 — SHOGUN X strike child (record kind 0x37, chunk_0047.c). */
  SHOGUN_X_CHILD: 0x8018eea4,
} as const;

/** Host hooks beyond the base StreamContext. */
export interface SamuraiFamilyCtx extends StreamContext {
  /** zz_0067f98_(actor, frames) @0x80067f98 — CHRONO SAMURAI's time-stop: writes the
   *  global freeze table (PTR_DAT_80433934: bit |= actor's +0x3e5 slot bit; slot-word
   *  = frame count 300). Host wires this to the battle-level status system; UNWIRED
   *  FALLBACK: no-op (labeled — the X strike simply lacks its freeze payload). */
  onTimeStop?: (actor: RomActor, frames: number) => void;
}

/** Table S-B config block (the zz_0148d74_ leaves' hidden r4 — raw-word verified:
 *  e.g. FUN_800c805c = lis r4,0x8031; addi r4,-0x7ff4 → 0x8030800c). Layout:
 *  +0x00 s32 seedSlot, +0x04 f32 fxRange, +0x08 f32 dashScale, +0x0c f32 drag,
 *  +0x10 f32 nearDrag. */
export interface SamuraiCloseSlashConfig {
  seedSlot: number;
  fxRange: number;
  dashScale: number;
  drag: number;
  nearDrag: number;
}

/** v0 config — DOL-read @0x8030800c/0x8032c7a4/0x8033c36c/0x8034d558/0x803737dc/
 *  0x803518f4 (byte-identical across all 6 families). */
export const SAMURAI_CLOSE_V0_CONFIG: SamuraiCloseSlashConfig = {
  seedSlot: 0, fxRange: 150.0, dashScale: 0.05, drag: 0.92, nearDrag: 0.8,
};

/** v1 config — DOL-read @0x80308038/0x8032c7d0/0x8033c398/0x8034d584/0x80373808
 *  (byte-identical across the 5 families that wire v1 to S-B; SHOGUN's v1 is its
 *  own machine). */
export const SAMURAI_CLOSE_V1_CONFIG: SamuraiCloseSlashConfig = {
  seedSlot: 4, fxRange: 150.0, dashScale: 0.05, drag: 0.95, nearDrag: 0.5,
};

/** The REAL zz_0149178_ lunge config for action-1 v3/v4 — DOL-read @0x80308020/
 *  0x8032c7b8/0x8033c380/0x8034d56c/0x803737f0 (byte-identical across the 5 families).
 *  Replaces melee-samurai.ts's TUNED SAMURAI_MELEE_DEFAULT_CONFIG for these borgs. */
export const SAMURAI_LUNGE_ROM_CONFIG: MeleeSamuraiConfig = {
  seedSlot: 3,
  timerFrames: 20,
  proximityRange: 150.0,
  velocityScale: 0.25,
  decel: 0.92,
  repositionScale: 0.95,
};

/** Per-actor scratch fields (ROM offsets not surfaced as named RomActor fields).
 *  Host-set inputs are stamped by the bridge / tests each frame. */
interface SamuraiScratch {
  // ---- host-set inputs ----
  /** +0x5d4 & 0x40 — B button edge this frame. */
  bRetapInput?: boolean;
  /** +0x1b03 — stream-tick gate (anim hold byte). */
  streamTickGate?: boolean;
  /** +0x1d9 — hit-react/impact status byte (SONIC X p3 masks 0x90/0x10; DEMON p5 and
   *  VAMPIRE p4 test != 0). Stream/hit-system authored; host-set. */
  hitReact?: number;
  grounded?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  /** actor+0x868 row (column 0) override — see SAMURAI.DEFAULT_RANGE_ROW. */
  rangeRow868?: number;
  /** actor+0x86c row (column 1) override (SHOGUN sky-dive setup). */
  rangeRow86c?: number;
  /** descriptor(+0x4b0)+0x54 — per-borg max dash speed clamp (S-B phase 2). Not
   *  surfaced on RomDescriptor; UNWIRED FALLBACK: no clamp (Infinity). */
  descMaxSpeed54?: number;
  // ---- machine state ----
  /** +0x746 — B-retap latch. */
  bRetap?: boolean;
  /** +0x560 — action-0 dash-slash window timer. */
  dashWindow?: number;
  /** +0x54a — action-0 yaw snapshot (u16 copy of +0x5ae in phase 0; ALL S-A physics
   *  integrate against it — NOT the aim-complete flag other engines keep at +0x54a). */
  volleyYawSnap?: number;
  /** +0x54e — DEMON rising-slash pitch/yaw offset (0 or 0x8000, added to +0x5ae). */
  pitchOffset54e?: number;
  /** +0x544 — movement/upper sub-phase byte (S-A phase 2's airborne arm stamps 1;
   *  the valkrie.ts `moveSubPhase` convention for the same offset). Distinct from
   *  fbPhaseSlots[1] = +0x541, the lock-clear latch. */
  moveSubPhase?: number;
  /** (s8)+0x1d0f — stream-authored dash-strength byte. Unstamped (host stamps only
   *  grounded/lockTarget today) → SAMURAI.DEFAULT_DASH_STRENGTH at the sites that
   *  would otherwise deadlock (dashByte below). */
  dashStrength?: number;
  /** +0x1d10 — face re-seek gate byte. */
  faceGate?: number;
  /** (s8)+0x1cf0 — part-0 swing event byte (< 0 = combo re-arm). Unstamped →
   *  SAMURAI.DEFAULT_SWING_EVENT at the stream-event waits (swingEventByte below). */
  swingEvent?: number;
  /** +0x1cf2 — follow-up stream event byte (SONIC v2 p3 re-fire). */
  followUpEvent?: boolean;
  /** +0x760 / +0x764 — engine-maintained distance-to-target scalars (the cluster reads
   *  BOTH: S-B/SONIC use +0x764, the v2 machines +0x760; one horizontal-distance cache
   *  mirrors them — valkrie targetDistance precedent, stale after lock drop). */
  curTargetDist?: number;
}

type SActor = RomActor & SamuraiScratch;

/** s16 wrap for BAM16 fields. */
function s16(v: number): number {
  return (v << 16) >> 16;
}

/** +0x760/+0x764 mirror — refresh on every locked read, serve the stale cache when
 *  unlocked (valkrie.ts targetDistance precedent). */
function targetDistance(a: SActor): number {
  const t = a.lockTarget;
  if (t) {
    a.curTargetDist = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
    return a.curTargetDist;
  }
  return a.curTargetDist ?? 0;
}

/** FUN_80066838(range, actor) — horizontal-distance range gate (verify-pass reading,
 *  shared-aerial-dive-x.ts:291): −1 with no lock (+0xcc == 0), 1 when |Δxz| ≤ range,
 *  0 beyond. Callers differ on the comparison: setup phases test `< 1` (invalidate on
 *  no-lock OR out-of-range), mid-phase gates test `!= 0` (no-lock −1 ALSO advances) or
 *  `> 0` (in-range only) — each site transcribes its own comparison. */
function rangeCheck(a: SActor, range: number): number {
  if (!a.lockTarget) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

/** actor+0x868 row float ((prevActionIndex % 3) × 0xc + 0x868, column 0). */
function rangeRow868(a: SActor): number {
  return a.rangeRow868 ?? SAMURAI.DEFAULT_RANGE_ROW;
}

/** actor+0x86c row float (column 1 — SHOGUN sky dive / valkrie table-C precedent). */
function rangeRow86c(a: SActor): number {
  return a.rangeRow86c ?? SAMURAI.DEFAULT_RANGE_ROW;
}

/** zz_006d144_(actor, 0xc0/0xc1) — face the lock target; nonzero = facing complete.
 *  The bridge pre-aims lockYaw each frame (shared-melee-gred precedent). */
function faceComplete(a: SActor): boolean {
  return a.lockTarget != null;
}

/** (s8)+0x1d0f read with the liveness fallback — the stream authors this byte in the
 *  ROM; an unstamped field falls back to SAMURAI.DEFAULT_DASH_STRENGTH (16) so the
 *  event-gated dash/leap sites fire instead of deadlocking (labeled TUNED). Sites
 *  that merely BRAKE or REFRESH on the byte keep the plain `?? 0` read. */
function dashByte(a: SActor): number {
  return a.dashStrength ?? SAMURAI.DEFAULT_DASH_STRENGTH;
}

/** (s8)+0x1cf0 read with the liveness fallback — unstamped → −1 ("swing fired") so
 *  the stream-event waits advance (labeled TUNED; SAMURAI.DEFAULT_SWING_EVENT). */
function swingEventByte(a: SActor): number {
  return a.swingEvent ?? SAMURAI.DEFAULT_SWING_EVENT;
}

/** zz_006ed8c_(scale, actor) — velocity drag on +0x44/+0x48. */
function applyDrag(a: SActor, scale: number): void {
  a.hSpeed *= scale;
  a.yVel *= scale;
}

/** dataPage(+0x4ac)+0x6c — gravityCoeff restore (valkrie gravityRestore precedent). */
function gravityRestore(a: SActor): number {
  return a.descriptor?.handlerData6c ?? 1.0;
}

/** The shared setup-phase lock-invalidate idiom: FUN_80066838(row868) < 1 →
 *  +0x541 = 1, +0xcc = 0, +0x5ac = +0x72 (active yaw snaps to heading). Returns true
 *  when invalidated. `alsoLockYaw` covers SHOGUN sky-dive's extra +0x5ae = +0x72;
 *  `activeFromLock` covers DEMON's +0x5ac = +0x5ae variant. */
function setupLockGate(
  a: SActor,
  row: number,
  opts?: { alsoLockYaw?: boolean; activeFromLock?: boolean },
): void {
  if (rangeCheck(a, row) < 1) {
    a.fbPhaseSlots[1] = 1;                  // +0x541 = 1
    a.lockTarget = null;                    // +0xcc = 0
    if (opts?.activeFromLock) {
      a.activeYaw = a.lockYaw;              // DEMON: +0x5ac = +0x5ae
    } else {
      if (opts?.alsoLockYaw) a.lockYaw = a.heading; // SHOGUN sky: +0x5ae = +0x72
      a.activeYaw = a.heading;              // +0x5ac = +0x72
    }
  }
}

/** zz_006a474_ ground idle return — every cluster call site first does +0x73f = 0
 *  (bridge-side flag) and +0x5e0 &= ~3, then bl zz_006a474_; the verified helper
 *  body lives in shared-idle-return.ts (upper cue 0 + velocity zeroing). */
function groundIdleReturn(a: SActor): void {
  a.controlWord &= ~0x3;                    // +0x5e0 &= 0xfffffffc (caller arm)
  romGroundIdleReturn(a);                   // zz_006a474_ @ chunk_0009.c:708
}

/** zz_006a5a4_ airborne knock-out return — same caller arm; the (+0x5e0 & 3) == 3
 *  freeze branch inside is unreachable here (bits 0..1 just cleared). */
function airKnockReturn(a: SActor): void {
  a.controlWord &= ~0x3;                    // +0x5e0 &= 0xfffffffc (caller arm)
  romAirKnockoutReturn(a);                  // zz_006a5a4_ @ chunk_0009.c:770
}

// ============================================================================
// Table S-A — action 0, B ranged dash-slash (dispatcher FUN_80148838 @0x80148838,
// wrapper FUN_801487c4; table PTR_FUN_8033ed0c @0x8033ed0c, chunk_0038.c:1822-2011).
// Group-2 streams; every physics step integrates against the +0x54a yaw snapshot.
// ============================================================================

// Phase 0 — FUN_80148874 @ chunk_0038.c:1824.
function rangedPhase0(a: SActor): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.dashWindow = SAMURAI.A0_WINDOW;          // +0x560 = FLOAT_8043a370 (20)
  if (a.variantIndex === 0) {                // +0x581 == 0 → zero +0x4c/+0x44
    a.hDecel = SAMURAI.ZERO;
    a.hSpeed = SAMURAI.ZERO;
  }
  a.volleyYawSnap = a.lockYaw & 0xffff;      // +0x54a = +0x5ae (u16 yaw snapshot)
  integratePhysics(SAMURAI.GRAVITY, a, s16(a.volleyYawSnap)); // FUN_80067310(1.0, +0x54a)
  // zz_00677b0_(actor) — ground collide (bridge owns the clamp).
  if (!a.lockTarget) a.activeYaw = a.heading; // +0xcc == 0 → +0x5ac = +0x72
  // zz_006d144_(0xc1) face + zz_006e1ac_(0xc1, 1) pitch seek — bridge pre-aims.
  a.streamSlot = 0;                          // +0x6ea = 0
  if ((a.controlWord & 0x40) !== 0) {        // hover latch → air slot 3
    a.streamSlot = 3;
  }
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  // zz_004beb8_(-1.0, actor, 0xf, 2, slot, -1, -1).
  startStream(a, SAMURAI.PART_MASK, SAMURAI.RANGED_GROUP, slot, SAMURAI.STREAM_RATE);
  // +0x80c = 0 — anim-rate housekeeping (not surfaced; labeled no-op).
}

// Phase 1 — FUN_80148968 @ chunk_0038.c:1867. Aim window → slash arm.
function rangedPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  integratePhysics(SAMURAI.GRAVITY, a, s16(a.volleyYawSnap ?? 0)); // FUN_80067310(1.0, +0x54a)
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, SAMURAI.PART_MASK, ctx);     // zz_004cd24_(actor, 0xf)
  // zz_006e1ac_(0xc1, 1) — pitch seek (bridge aim channel).
  const facing = faceComplete(a);            // iVar4 = zz_006d144_(0xc1)
  // Stay while ((not facing && window still > 0) || part-0 event byte +0x1cee clear);
  // note the window only decrements on the not-facing path (&& short-circuit order).
  let hold = false;
  if (!facing) {
    a.dashWindow = (a.dashWindow ?? 0) - a.dt;         // +0x560 -= dt
    if ((a.dashWindow ?? 0) > SAMURAI.ZERO) hold = true;
  }
  if (hold || a.wallContact === 0) {
    // FLOAT_8043a380 (3) < +0x44 → zz_00b22f4_ afterimage (renderer-side no-op).
    return;
  }
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  startStream(a, SAMURAI.PART_MASK, SAMURAI.RANGED_GROUP, slot, SAMURAI.STREAM_RATE);
}

// Phase 2 — FUN_80148ab0 @ chunk_0038.c:1904. Active slash; air/ground fork.
function rangedPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  integratePhysics(SAMURAI.GRAVITY, a, s16(a.volleyYawSnap ?? 0));
  const grounded = a.grounded === true;      // iVar3 = zz_00677b0_(actor)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (a.wallContact !== 0) {                 // +0x1cee != 0 (stream end event)
    if (!grounded) {
      // Airborne → phase 3 (air fall recovery).
      a.fbPhaseSlots[0] += 1;                // +0x540++
      a.moveSubPhase = 1;                    // +0x544 = 1 (movement sub-phase byte —
                                             // valkrie.ts moveSubPhase convention;
                                             // NOT the +0x541 lock-clear latch)
      a.handlerTimer = SAMURAI.FACE_BUDGET;  // +0x558 = FLOAT_8043a384 (60)
      a.gravityCoeff = gravityRestore(a);    // +0x50 = dataPage(+0x4ac)+0x6c
    } else {
      // Grounded → SKIP to phase 4 (+0x540 += 2) with the recovery stream.
      a.fbPhaseSlots[0] += 2;
      const slot = a.streamSlot;             // cVar1 = +0x6ea
      a.streamSlot = slot + 1;               // +0x6ea++
      startStream(a, SAMURAI.PART_MASK, SAMURAI.RANGED_GROUP, slot, SAMURAI.STREAM_RATE);
      a.controlWord &= ~0x40;                // +0x5e0 &= 0xffffffbf (hover latch off)
    }
  }
  // +0x44 > 3 → zz_00b22f4_ afterimage (no-op).
}

// Phase 3 — FUN_80148ba0 @ chunk_0038.c:1942. Air fall recovery.
function rangedPhase3(a: SActor): void {
  // +0x18da = (s16)((f32)(s16)+0x18da × FLOAT_8043a360) — steer decay ×0.9.
  a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * SAMURAI.STEER_DECAY));
  integratePhysics(SAMURAI.GRAVITY, a, s16(a.volleyYawSnap ?? 0));
  const grounded = a.grounded === true;      // iVar3 = zz_00677b0_(actor)
  if (!grounded) {
    a.handlerTimer -= a.dt;                  // +0x558 -= dt
    if (a.handlerTimer > SAMURAI.ZERO) {
      // +0x44 > 3 → afterimage (no-op).
      return;
    }
    a.hDecel = SAMURAI.ZERO;                 // +0x4c = 0
    a.hSpeed = SAMURAI.ZERO;                 // +0x44 = 0
    airKnockReturn(a);                       // +0x73f = 0; &= ~3; zz_006a5a4_
    return;
  }
  a.controlWord &= ~0x3;                     // +0x73f = 0; +0x5e0 &= 0xfffffffc
  dispatchUpperBodyCue(a, 7);                // zz_006a750_(actor, 7)
  a.stateTimer = SAMURAI.COOLDOWN + a.dt;    // +0x694 = FLOAT_8043a388 (8) + dt
}

// Phase 4 — FUN_80148cb0 @ chunk_0038.c:1987. Ground recovery.
function rangedPhase4(a: SActor, ctx: SamuraiFamilyCtx): void {
  a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * SAMURAI.STEER_DECAY));
  applyDrag(a, SAMURAI.RECOVERY_DRAG);       // zz_006ed8c_(FLOAT_8043a38c = 0.95)
  integratePhysics(SAMURAI.GRAVITY, a, s16(a.volleyYawSnap ?? 0));
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    a.steerYaw = 0;                          // +0x18da = 0
    a.hDecel = SAMURAI.ZERO;                 // +0x4c = 0
    a.hSpeed = SAMURAI.ZERO;                 // +0x44 = 0
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
  }
}

/** Build the table S-A handler (dispatcher FUN_80148838). All 5 action-0 variants of
 *  every cluster borg route here (variant table 0x8033ecf8 is 5× the same wrapper). */
export function createSamuraiRangedDash(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8033ed0c[+0x540]
      case 0: rangedPhase0(a); break;
      case 1: rangedPhase1(a, ctx); break;
      case 2: rangedPhase2(a, ctx); break;
      case 3: rangedPhase3(a); break;
      case 4: rangedPhase4(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// Table S-B — action 1 v0/v1, B close slash (dispatcher zz_0148d74_ @0x80148d74,
// table PTR_FUN_8033ed20 @0x8033ed20, chunk_0038.c:2016-2154). Config-driven.
// ============================================================================

// Phase 0 — FUN_80148dc4 @ chunk_0038.c:2032.
function closePhase0(a: SActor, cfg: SamuraiCloseSlashConfig): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.handlerTimer = SAMURAI.FACE_BUDGET;      // +0x558 = FLOAT_8043a384 (60)
  a.bRetap = false;                          // +0x746 = 0
  a.streamSlot = cfg.seedSlot;               // +0x6ea = (char)cfg[0]
  a.hSpeed = SAMURAI.ZERO;                   // +0x44 = 0
  a.hDecel = SAMURAI.ZERO;                   // +0x4c = 0
  setupLockGate(a, rangeRow868(a));          // FUN_80066838(row868) < 1 → invalidate
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  // zz_004beb8_(-1.0, actor, 0xf, 3, slot, -1, -1).
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, slot, SAMURAI.STREAM_RATE);
}

// Phase 1 — FUN_80148ea8 @ chunk_0038.c:2068. Face budget → first slash.
function closePhase1(a: SActor, cfg: SamuraiCloseSlashConfig, ctx: SamuraiFamilyCtx): void {
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SAMURAI.ZERO || faceComplete(a)) { // timer OR zz_006d144_(0xc0)
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    if (cfg.fxRange < targetDistance(a)) {   // cfg+4 < +0x764
      // zz_00b2190_(actor, 0) — melee trail FX child.
      ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0);
    }
  }
}

// Phase 2 — FUN_80148f4c @ chunk_0038.c:2093. Slash loop + stream-driven dash.
function closePhase2(a: SActor, cfg: SamuraiCloseSlashConfig, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);     // zz_004cd24_(actor, 0xf)
  if (a.bRetapInput) a.bRetap = true;        // +0x5d4 & 0x40 → +0x746 = 1
  // COMBO: (s8)+0x1cf0 < 0 (swing re-arm) AND +0x746 — stays in phase 2 (no phase
  // decrement, unlike the valkrie 3→2 loop) and restarts the next g3 slot.
  if (swingEventByte(a) < 0 && a.bRetap) {   // unstamped +0x1cf0 → −1 (TUNED fallback)
    a.bRetap = false;                        // +0x746 = 0
    if (cfg.fxRange < targetDistance(a)) {   // cfg+4 < +0x764
      ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
    const slot = a.streamSlot;               // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                 // +0x6ea++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, slot, SAMURAI.STREAM_RATE);
    return;
  }
  if ((a.faceGate ?? 0) !== 0) {             // +0x1d10 != 0 → re-face (bridge)
    // zz_006d144_(actor, 0xc0).
  }
  const strength = dashByte(a);              // (s8)+0x1d0f — stream-authored;
                                             // unstamped → 16 (TUNED fallback)
  if (strength > 0) {
    if (!a.lockTarget) {                     // +0xcc == 0 → row float stands in
      a.hSpeed = rangeRow868(a);             // +0x44 = row868
    } else {
      // +0x44 = +0x764 × (f32)(s8)+0x1d0f × FLOAT_8043a390 (0.0625).
      a.hSpeed = targetDistance(a) * strength * SAMURAI.DASH_BYTE_SCALE;
    }
    a.hSpeed *= cfg.dashScale;               // +0x44 *= cfg+8 (0.05)
    const max = a.descMaxSpeed54 ?? Infinity; // descriptor(+0x4b0)+0x54 clamp
    if (max < a.hSpeed) a.hSpeed = max;
    a.dashStrength = 0;                      // +0x1d0f = 0
  }
  if ((a.dashStrength ?? 0) < 0) {           // negative byte → decel arm
    a.hDecel = a.hSpeed * (a.dashStrength ?? 0) * SAMURAI.DASH_BYTE_SCALE; // +0x4c
    a.dashStrength = 0;                      // +0x1d0f = 0
  }
  if (targetDistance(a) < cfg.fxRange) {     // +0x764 < cfg+4 → near brake
    applyDrag(a, cfg.nearDrag);              // zz_006ed8c_(cfg+0x10)
  }
  applyDrag(a, cfg.drag);                    // zz_006ed8c_(cfg+0xc)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae) — yaw-only
  if (a.wallContact !== 0) {                 // +0x1cee != 0 → end the move
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
  }
}

/** Build the table S-B handler (dispatcher zz_0148d74_). */
export function createSamuraiCloseSlash(
  cfg: SamuraiCloseSlashConfig,
  ctx: SamuraiFamilyCtx,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) {    // +0x541 != 0 → +0xcc = 0
      a.lockTarget = null;
    }
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8033ed20[+0x540]
      case 0: closePhase0(a, cfg); break;
      case 1: closePhase1(a, cfg, ctx); break;
      case 2: closePhase2(a, cfg, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// 6-phase RISING SLASH — the NORMAL SAMURAI / DEATH BORG ZETA / SHOGUN-v2 machine.
// NORMAL @0x8030804c (chunk_0020.c:4930, floats FLOAT_804388xx), ZETA @0x8037381c
// (chunk_0048.c, floats FLOAT_8043b4xx — instruction-level clone), SHOGUN v2
// @0x80351924 (chunk_0044.c, floats FLOAT_8043adxx + two structural deltas).
// Stream slots slotBase/+1/+2 (literal — +0x6ea untouched).
// ============================================================================

export interface RisingSlashConfig {
  /** Phase-table address + float bank (documentation). */
  romTable: number;
  /** Literal g3 stream slot base (6 for all three). */
  slotBase: number;
  /** p0 face budget: FLOAT_80438830 / 8043b43c / 8043ada8 = 60. */
  faceBudget: number;
  /** p1 dash window + speed divisor: FLOAT_8043883c / 8043b448 / 8043ad6c = 20. */
  dashWindow: number;
  /** p1 FX gate + p2 range gate: FLOAT_80438840 / 8043b44c / 8043adac = 200. */
  fxRange: number;
  /** p2/p4/p5 drag: FLOAT_80438844 / 8043b450 / 8043adb0 = 0.95. */
  dashDrag: number;
  /** p3 drag: FLOAT_80438848 / 8043b454 / 8043adb4 = 0.99. */
  leapDrag: number;
  /** p3 +0x48 seed: FLOAT_8043884c / 8043b458 = 32; SHOGUN FLOAT_8043adb8 = 40. */
  leapYVel: number;
  /** p3 +0x50 seed: FLOAT_80438850 = −2.3703704 / FLOAT_8043b45c = −4 /
   *  FLOAT_8043adbc = −3 — the ONE NORMAL↔ZETA clone delta. */
  leapGravity: number;
  /** p4 gravity param: FLOAT_80438854 / 8043b460 / 8043ad7c = 1. */
  fallGravity: number;
  /** SHOGUN p3 extra +0x558 seed (FLOAT_8043ada8 = 60); NORMAL/ZETA don't seed. */
  riseTimerSeed: number | null;
  /** SHOGUN p4 gate is (timer ≤ 0 || grounded); NORMAL/ZETA grounded-only. */
  fallTimerGate: boolean;
}

/** NORMAL SAMURAI v2 @0x8030804c (FUN_800c8124..848c). */
export const NORMAL_RISING_CONFIG: RisingSlashConfig = {
  romTable: 0x8030804c, slotBase: 6, faceBudget: 60, dashWindow: 20, fxRange: 200,
  dashDrag: 0.95, leapDrag: 0.99, leapYVel: 32, leapGravity: -2.3703704,
  fallGravity: 1.0, riseTimerSeed: null, fallTimerGate: false,
};

/** DEATH BORG ZETA v2 @0x8037381c (FUN_8019cba0..cf08 — NORMAL clone, own bank). */
export const ZETA_RISING_CONFIG: RisingSlashConfig = {
  romTable: 0x8037381c, slotBase: 6, faceBudget: 60, dashWindow: 20, fxRange: 200,
  dashDrag: 0.95, leapDrag: 0.99, leapYVel: 32, leapGravity: -4.0,
  fallGravity: 1.0, riseTimerSeed: null, fallTimerGate: false,
};

/** SAMURAI SHOGUN v2 @0x80351924 (FUN_80175a70..75e00). */
export const SHOGUN_RISING_CONFIG: RisingSlashConfig = {
  romTable: 0x80351924, slotBase: 6, faceBudget: 60, dashWindow: 20, fxRange: 200,
  dashDrag: 0.95, leapDrag: 0.99, leapYVel: 40, leapGravity: -3.0,
  fallGravity: 1.0, riseTimerSeed: 60, fallTimerGate: true,
};

// Phase 0 — FUN_800c8124 / FUN_8019cba0 / FUN_80175a70.
function risingPhase0(a: SActor, cfg: RisingSlashConfig): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  setupLockGate(a, rangeRow868(a));          // FUN_80066838(row868) < 1 → invalidate
  a.handlerTimer = cfg.faceBudget;           // +0x558 = 60
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  // zz_004beb8_(-1.0, actor, 0xf, 3, slotBase, -1, -1) — literal slot, no +0x6ea.
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, cfg.slotBase, SAMURAI.STREAM_RATE);
}

// Phase 1 — FUN_800c81e0 / FUN_8019cc5c / FUN_80175b2c. Face budget → dash arm.
function risingPhase1(a: SActor, cfg: RisingSlashConfig, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SAMURAI.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = cfg.dashWindow;         // +0x558 = 20
    let f = rangeRow868(a);                  // row868 default
    if (a.lockTarget && f < targetDistance(a)) { // +0xcc != 0 && row < +0x760
      f = targetDistance(a);
    }
    a.hSpeed = f / cfg.dashWindow;           // +0x44 = f / 20
    a.hDecel = SAMURAI.ZERO;                 // +0x4c = 0
    if (cfg.fxRange < targetDistance(a)) {   // 200 < +0x760
      ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
  }
}

// Phase 2 — FUN_800c82d4 / FUN_8019cd50 / FUN_80175c20. Dash-in.
function risingPhase2(a: SActor, cfg: RisingSlashConfig, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  applyDrag(a, cfg.dashDrag);                // zz_006ed8c_(0.95)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_80066838(200) != 0 (no-lock −1 ALSO advances).
  if (a.handlerTimer <= SAMURAI.ZERO || rangeCheck(a, cfg.fxRange) !== 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, cfg.slotBase + 1, SAMURAI.STREAM_RATE);
  }
}

// Phase 3 — FUN_800c8388 / FUN_8019ce04 / FUN_80175cd4. Wait for the leap byte.
function risingPhase3(a: SActor, cfg: RisingSlashConfig, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  applyDrag(a, cfg.leapDrag);                // zz_006ed8c_(0.99)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (dashByte(a) !== 0) {                   // +0x1d0f != 0 (NOT consumed here;
                                             // unstamped → 16 TUNED fallback so the
                                             // leap fires instead of deadlocking)
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    if (cfg.riseTimerSeed !== null) {        // SHOGUN: +0x558 = FLOAT_8043ada8 (60)
      a.handlerTimer = cfg.riseTimerSeed;
    }
    a.yVel = cfg.leapYVel;                   // +0x48 = 32 / 40
    a.gravityCoeff = cfg.leapGravity;        // +0x50 = −2.37 / −4 / −3
  }
}

// Phase 4 — FUN_800c8404 / FUN_8019ce80 / FUN_80175d58. Rising slash → fall.
function risingPhase4(a: SActor, cfg: RisingSlashConfig, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  applyDrag(a, cfg.dashDrag);                // zz_006ed8c_(0.95)
  integratePhysics(cfg.fallGravity, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  const grounded = a.grounded === true;      // zz_00677b0_(actor)
  let advance: boolean;
  if (cfg.fallTimerGate) {
    a.handlerTimer -= a.dt;                  // SHOGUN: +0x558 -= dt
    advance = a.handlerTimer <= SAMURAI.ZERO || grounded;
  } else {
    advance = grounded;                      // NORMAL/ZETA: landing only
  }
  if (advance) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, cfg.slotBase + 2, SAMURAI.STREAM_RATE);
  }
}

// Phase 5 — FUN_800c848c / FUN_8019cf08 / FUN_80175e00. Recovery.
function risingPhase5(a: SActor, cfg: RisingSlashConfig, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  applyDrag(a, cfg.dashDrag);                // zz_006ed8c_(0.95)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
  }
}

/** Build the 6-phase rising-slash handler. */
export function createRisingSlash(
  cfg: RisingSlashConfig,
  ctx: SamuraiFamilyCtx,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null; // +0x541 → +0xcc = 0
    switch (a.fbPhaseSlots[0] ?? 0) {
      case 0: risingPhase0(a, cfg); break;
      case 1: risingPhase1(a, cfg, ctx); break;
      case 2: risingPhase2(a, cfg, ctx); break;
      case 3: risingPhase3(a, cfg, ctx); break;
      case 4: risingPhase4(a, cfg, ctx); break;
      case 5: risingPhase5(a, cfg, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// DEMON SAMURAI v2 — 7-phase rising demon slash @0x8032c7e4 (chunk_0033.c:1333).
// Float bank FLOAT_80439bxx: b10=0, b20=0.9, b54=60, b58=−1, b5c=20, b60=200,
// b64=1, b68=500, b6c=10, b70=−40; DOUBLE_80439b30=0.5, DOUBLE_80439b78=0.25.
// Physics yaw = +0x5ae + +0x54e (the 0/0x8000 flip seeded in phase 1).
// ============================================================================

const DEMON = {
  ZERO: 0.0,        // FLOAT_80439b10
  DRAG: 0.9,        // FLOAT_80439b20
  FACE_BUDGET: 60,  // FLOAT_80439b54
  RISE_GRAVITY: -1, // FLOAT_80439b58 (float doubles as the stream rate)
  RISE_WINDOW: 20,  // FLOAT_80439b5c (timer + speed divisor + yVel seed)
  FLIP_RANGE: 200,  // FLOAT_80439b60
  GRAVITY: 1.0,     // FLOAT_80439b64
  PASS_RANGE: 500,  // FLOAT_80439b68
  HANG_WINDOW: 10,  // FLOAT_80439b6c
  DIVE_YVEL: -40,   // FLOAT_80439b70
  RISE_SCALE: 0.5,  // DOUBLE_80439b30
  HIT_BRAKE: 0.25,  // DOUBLE_80439b78
  SLOT_BASE: 6,
} as const;

// Phase 0 — FUN_80122dec @ chunk_0033.c:1333.
function demonPhase0(a: SActor): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  // Invalidate arm sets +0x5ac = +0x5AE (lock yaw — NOT +0x72; the DEMON delta).
  setupLockGate(a, rangeRow868(a), { activeFromLock: true });
  a.handlerTimer = DEMON.FACE_BUDGET;        // +0x558 = 60
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, DEMON.SLOT_BASE, SAMURAI.STREAM_RATE);
}

// Phase 1 — FUN_80122ea8 @ chunk_0033.c:1356. Face budget → rising launch.
function demonPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= DEMON.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = DEMON.RISE_WINDOW;      // +0x558 = 20
    a.hSpeed = rangeRow868(a) / DEMON.RISE_WINDOW; // +0x44 = row868 / 20
    a.hDecel = DEMON.ZERO;                   // +0x4c = 0
    a.yVel = DEMON.RISE_WINDOW;              // +0x48 = 20 (FLOAT_80439b5c reuse)
    a.gravityCoeff = DEMON.RISE_GRAVITY;     // +0x50 = −1 (FLOAT_80439b58 reuse)
    const max = a.descMaxSpeed54 ?? Infinity; // descriptor(+0x4b0)+0x54 clamp
    if (max < a.hSpeed) a.hSpeed = max;
    a.pitchOffset54e = 0;                    // +0x54e = 0
    if (rangeCheck(a, DEMON.FLIP_RANGE) > 0) { // FUN_80066838(200) > 0 (in range ONLY)
      a.pitchOffset54e = 0x8000;             // +0x54e = 0x8000 — rush PAST the target
    }
    // zz_0066530_(actor, 0x2d) — hover-mode latch ON: +0x5e4 = 0x2d, +0x5e0 |= 0x40
    // (shared-flight-x.ts:375 precedent; +0x87 byte not surfaced — no-op).
    a.ubCue = 0x2d;
    a.controlWord |= 0x40;
    // +0x80c = 0 — housekeeping (not surfaced; no-op).
    ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
  }
}

// Phase 2 — FUN_80122fd4 @ chunk_0033.c:1442. Rising rush (yaw + 0x54e offset).
function demonPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  if (a.lockTarget) {                        // +0xcc != 0 → speed refresh
    a.hSpeed = targetDistance(a) / DEMON.RISE_WINDOW; // +0x44 = +0x764 / 20
    const max = a.descMaxSpeed54 ?? Infinity;
    if (max < a.hSpeed) a.hSpeed = max;
  }
  // FUN_80067310(1.0, actor, +0x5ae + +0x54e) — the flip offset steers the rush.
  integratePhysics(DEMON.GRAVITY, a, s16(a.lockYaw + (a.pitchOffset54e ?? 0)));
  // zz_00677b0_(actor) — bridge clamp.
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_80066838(500) > 0 (in-range ONLY — no-lock keeps rushing).
  if (a.handlerTimer <= DEMON.ZERO || rangeCheck(a, DEMON.PASS_RANGE) > 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = DEMON.HANG_WINDOW;      // +0x558 = 10
    a.hSpeed *= DEMON.RISE_SCALE;            // ×0.5 (DOUBLE_80439b30) on all four
    a.hDecel *= DEMON.RISE_SCALE;
    a.yVel *= DEMON.RISE_SCALE;
    a.gravityCoeff *= DEMON.RISE_SCALE;
  }
  // zz_00b22f4_(actor) — afterimage (renderer-side no-op).
}

// Phase 3 — FUN_801230fc @ chunk_0033.c:1499. Hang → next swing stream.
function demonPhase3(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  // zz_006d144_(0xc0) — face.
  if (a.yVel < DEMON.ZERO) {                 // +0x48 < 0 → hold altitude
    a.yVel = DEMON.ZERO;                     // +0x48 = 0
    a.gravityCoeff = DEMON.ZERO;             // +0x50 = 0
  }
  integratePhysics(DEMON.GRAVITY, a, s16(a.lockYaw + (a.pitchOffset54e ?? 0)));
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= DEMON.ZERO) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, DEMON.SLOT_BASE + 1, SAMURAI.STREAM_RATE);
  }
}

// Phase 4 — FUN_801231b8 @ chunk_0033.c:1533. Wait for contact → dive.
function demonPhase4(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  // zz_006d144_(0xc0) — face.
  if (a.yVel < DEMON.ZERO) {                 // altitude hold (same clamp)
    a.yVel = DEMON.ZERO;
    a.gravityCoeff = DEMON.ZERO;
  }
  integratePhysics(DEMON.GRAVITY, a, s16(a.lockYaw + (a.pitchOffset54e ?? 0)));
  if (a.contactP0 !== 0) {                   // +0x1cef != 0 → hit connected
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.yVel = DEMON.DIVE_YVEL;                // +0x48 = −40 (FLOAT_80439b70)
    a.gravityCoeff = gravityRestore(a);      // +0x50 = dataPage(+0x4ac)+0x6c
  }
}

// Phase 5 — FUN_80123254 @ chunk_0033.c:1573. Slam dive → landing.
function demonPhase5(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if ((a.hitReact ?? 0) !== 0) {             // +0x1d9 != 0 → hit-react brake
    a.hSpeed *= DEMON.HIT_BRAKE;             // +0x44 ×= 0.25 (DOUBLE_80439b78)
    a.fbPhaseSlots[1] = 0xff;                // +0x541 = 0xff (lock stays cleared)
  }
  integratePhysics(DEMON.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  const grounded = a.grounded === true;      // iVar1 = zz_00677b0_(actor)
  if (grounded && a.wallContact !== 0) {     // landed + +0x1cee != 0
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    // zz_0066530_(actor, 0x2c) — landing latch: +0x5e4 = 0x2c, clears +0x5e0 bits
    // 0x40 AND 0x80 (shared-aerial-dive-x.ts:452 verify-pass correction).
    a.ubCue = 0x2c;
    a.controlWord &= ~0xc0;
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, DEMON.SLOT_BASE + 2, SAMURAI.STREAM_RATE);
    // +0x80c = 0 — housekeeping no-op.
  }
}

// Phase 6 — FUN_80123318 @ chunk_0033.c:1601. Recovery.
function demonPhase6(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  applyDrag(a, DEMON.DRAG);                  // zz_006ed8c_(0.9, FLOAT_80439b20)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
  }
  // zz_00b22f4_(actor) — afterimage no-op.
}

/** Build the DEMON SAMURAI v2 handler (dispatcher FUN_80122d9c @ chunk_0033.c:1319). */
export function createDemonRisingSlash(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null; // +0x541 → +0xcc = 0
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8032c7e4[+0x540]
      case 0: demonPhase0(a); break;
      case 1: demonPhase1(a, ctx); break;
      case 2: demonPhase2(a, ctx); break;
      case 3: demonPhase3(a, ctx); break;
      case 4: demonPhase4(a, ctx); break;
      case 5: demonPhase5(a, ctx); break;
      case 6: demonPhase6(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// VAMPIRE KNIGHT v2 — 5-phase leap slash @0x8033c3ac (chunk_0037.c:3782).
// Float bank FLOAT_8043a2xx: a270=60, a274=−1, a278=0, a27c=20, a280=200,
// a284=0.95, a288=0.5, a28c=30, a290=1.
// ============================================================================

const VAMPIRE = {
  FACE_BUDGET: 60,  // FLOAT_8043a270 (also the p3 rise timer)
  RISE_GRAVITY: -1, // FLOAT_8043a274 (float doubles as the stream rate)
  ZERO: 0.0,        // FLOAT_8043a278
  DASH_WINDOW: 20,  // FLOAT_8043a27c
  FX_RANGE: 200,    // FLOAT_8043a280
  DASH_DRAG: 0.95,  // FLOAT_8043a284
  HIT_SCALE: 0.5,   // FLOAT_8043a288
  RISE_YVEL: 30,    // FLOAT_8043a28c
  GRAVITY: 1.0,     // FLOAT_8043a290 (p4 gravity + landing +0x694 seed)
  SLOT_BASE: 5,
} as const;

// Phase 0 — FUN_801440e8 @ chunk_0037.c:3782.
function vampPhase0(a: SActor): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  setupLockGate(a, rangeRow868(a));          // invalidate → +0x5ac = +0x72
  a.handlerTimer = VAMPIRE.FACE_BUDGET;      // +0x558 = 60
  // zz_006d144_(0xc0) — face.
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, VAMPIRE.SLOT_BASE, SAMURAI.STREAM_RATE);
}

// Phase 1 — FUN_801441a4 @ chunk_0037.c:3805. Face budget → dash arm.
function vampPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= VAMPIRE.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = VAMPIRE.DASH_WINDOW;    // +0x558 = 20
    let f = rangeRow868(a);
    if (a.lockTarget && f < targetDistance(a)) f = targetDistance(a); // max(row, +0x760)
    a.hSpeed = f / VAMPIRE.DASH_WINDOW;      // +0x44 = f / 20
    a.hDecel = VAMPIRE.ZERO;                 // +0x4c = 0
    if (VAMPIRE.FX_RANGE < targetDistance(a)) { // 200 < +0x760
      ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
  }
}

// Phase 2 — FUN_801442a4 @ chunk_0037.c:3842. Dash-in (stream held on contact).
function vampPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) — face.
  applyDrag(a, VAMPIRE.DASH_DRAG);           // zz_006ed8c_(0.95)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  if (a.contactP0 === 0) {                   // +0x1cef == 0 → stream advances
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_80066838(200) != 0 (no-lock −1 ALSO advances).
  if (a.handlerTimer <= VAMPIRE.ZERO || rangeCheck(a, VAMPIRE.FX_RANGE) !== 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
  }
}

// Phase 3 — FUN_80144344 @ chunk_0037.c:3868. Swing event → rising carry.
function vampPhase3(a: SActor, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) — face.
  applyDrag(a, VAMPIRE.DASH_DRAG);           // zz_006ed8c_(0.95)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (swingEventByte(a) !== 0) {             // +0x1cf0 != 0 (unstamped → −1 TUNED
                                             // fallback — no stream-event deadlock)
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = VAMPIRE.FACE_BUDGET;    // +0x558 = 60 (FLOAT_8043a270 reuse)
    a.hSpeed *= VAMPIRE.HIT_SCALE;           // +0x44 ×= 0.5
    a.hDecel *= VAMPIRE.HIT_SCALE;           // +0x4c ×= 0.5
    a.yVel = VAMPIRE.RISE_YVEL;              // +0x48 = 30
    a.gravityCoeff = VAMPIRE.RISE_GRAVITY;   // +0x50 = −1 (FLOAT_8043a274 reuse)
  }
}

// Phase 4 — FUN_801443e4 @ chunk_0037.c:3898. Rise/fall recovery.
function vampPhase4(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if ((a.hitReact ?? 0) !== 0) {             // +0x1d9 != 0 → kill the carry
    a.hDecel = VAMPIRE.ZERO;                 // +0x4c = 0
    a.hSpeed = VAMPIRE.ZERO;                 // +0x44 = 0
  }
  integratePhysics(VAMPIRE.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  const grounded = a.grounded === true;      // iVar3 = zz_00677b0_(actor)
  if (!grounded || a.wallContact === 0) {    // airborne OR no ground event
    a.handlerTimer -= a.dt;                  // +0x558 -= dt
    if (a.handlerTimer <= VAMPIRE.ZERO) {
      airKnockReturn(a);                     // +0x73f = 0; &= ~3; zz_006a5a4_
    }
    return;
  }
  a.controlWord &= ~0x3;                     // +0x73f = 0; +0x5e0 &= 0xfffffffc
  dispatchUpperBodyCue(a, 7);                // zz_006a750_(actor, 7)
  a.stateTimer = VAMPIRE.GRAVITY + a.dt;     // +0x694 = 1.0 (FLOAT_8043a290) + dt
}

/** Build the VAMPIRE KNIGHT v2 handler (dispatcher FUN_80144098 @ chunk_0037.c:3768). */
export function createVampireLeapSlash(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8033c3ac[+0x540]
      case 0: vampPhase0(a); break;
      case 1: vampPhase1(a, ctx); break;
      case 2: vampPhase2(a, ctx); break;
      case 3: vampPhase3(a, ctx); break;
      case 4: vampPhase4(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// SONIC SAMURAI v2 — 4-phase multi-slash @0x8034d598 (chunk_0042.c:2076).
// Float bank FLOAT_8043a9xx: a988=60, a98c=−1, a990=0, a994=20, a998=500,
// a99c=40, a9a0=0.15, a9a4=0.98.
// ============================================================================

const SONIC = {
  FACE_BUDGET: 60,   // FLOAT_8043a988
  ZERO: 0.0,         // FLOAT_8043a990
  DASH_WINDOW: 20,   // FLOAT_8043a994
  PASS_RANGE: 500,   // FLOAT_8043a998
  PASS_SPEED: 40,    // FLOAT_8043a99c
  HIT_BRAKE: 0.15,   // FLOAT_8043a9a0
  GLIDE_DRAG: 0.98,  // FLOAT_8043a9a4
  // ---- X bank ----
  X_REPOS: 0.95,     // FLOAT_8043a9a8
  X_DASH_SPEED: 100, // FLOAT_8043a9ac
  X_GRAVITY: 1.0,    // FLOAT_8043a9b0
  X_BRAKE_WINDOW: 30,// FLOAT_8043a9b4
  X_BRAKE: 0.5,      // DOUBLE_8043a9b8
  X_POP_YVEL: 3,     // FLOAT_8043a9c0
  X_COOLDOWN: 4,     // FLOAT_8043a9c4
  STEER_DECAY: 0.9,  // FLOAT_8043a978
  SLOT_BASE: 6,
} as const;

// Phase 0 — FUN_801647a0 @ chunk_0042.c:2076.
function sonicPhase0(a: SActor): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  setupLockGate(a, rangeRow868(a));
  a.handlerTimer = SONIC.FACE_BUDGET;        // +0x558 = 60
  // zz_006d144_(0xc0) — face.
  a.streamSlot = SONIC.SLOT_BASE;            // +0x6ea = 6
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++ (the p3 re-fire reads 7)
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, slot, SAMURAI.STREAM_RATE);
  // +0x80c = 0 (FLOAT_8043a990) — housekeeping no-op.
}

// Phase 1 — FUN_80164878 @ chunk_0042.c:2106. Face budget → dash (FX unconditional).
function sonicPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  if (a.contactP0 === 0) {                   // +0x1cef == 0 → stream advances
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SONIC.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = SONIC.DASH_WINDOW;      // +0x558 = 20
    let f = rangeRow868(a);
    if (a.lockTarget && f < targetDistance(a)) f = targetDistance(a);
    a.hSpeed = f / SONIC.DASH_WINDOW;        // +0x44 = f / 20
    a.hDecel = SONIC.ZERO;                   // +0x4c = 0
    ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // UNCONDITIONAL here
  }
}

// Phase 2 — FUN_80164968 @ chunk_0042.c:2139. Pass-through dash.
function sonicPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) — face.
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  if (a.contactP0 === 0) {                   // +0x1cef == 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_80066838(500) != 0 (no-lock −1 ALSO advances).
  if (a.handlerTimer <= SONIC.ZERO || rangeCheck(a, SONIC.PASS_RANGE) !== 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = SONIC.DASH_WINDOW;      // +0x558 = 20
    a.hSpeed = SONIC.PASS_SPEED;             // +0x44 = 40 (FLOAT_8043a99c)
  }
  // zz_00b22f4_(actor) — afterimage no-op.
}

// Phase 3 — FUN_80164a14 @ chunk_0042.c:2169. Glide-out + follow-up re-fire.
function sonicPhase3(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if ((a.dashStrength ?? 0) !== 0) {         // +0x1d0f != 0 → hit brake
    a.dashStrength = 0;                      // +0x1d0f = 0
    a.hSpeed *= SONIC.HIT_BRAKE;             // +0x44 ×= 0.15 (FLOAT_8043a9a0)
  }
  applyDrag(a, SONIC.GLIDE_DRAG);            // zz_006ed8c_(0.98)
  if (a.handlerTimer > SONIC.ZERO) {         // FLOAT_8043a990 < +0x558
    a.handlerTimer -= a.dt;                  // +0x558 -= dt
  }
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  if (a.followUpEvent && a.handlerTimer <= SONIC.ZERO) { // +0x1cf2 && timer done
    // Re-fire the CURRENT slot ((s8)+0x6ea, no increment — repeats slot 7).
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, a.streamSlot, SAMURAI.STREAM_RATE);
  }
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
  }
  // zz_00b22f4_(actor) — afterimage no-op.
}

/** Build the SONIC SAMURAI v2 handler (dispatcher FUN_80164750 @ chunk_0042.c:2062). */
export function createSonicMultiSlash(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8034d598[+0x540]
      case 0: sonicPhase0(a); break;
      case 1: sonicPhase1(a, ctx); break;
      case 2: sonicPhase2(a, ctx); break;
      case 3: sonicPhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// SONIC SAMURAI X — 6-phase blink-flurry @0x8034d5bc (chunk_0042.c:2204).
// ============================================================================

// Phase 0 — FUN_80164b9c @ chunk_0042.c:2228. Blink-away + g4 stream.
function sonicXPhase0(a: SActor): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.handlerTimer = SONIC.DASH_WINDOW;        // +0x558 = 20 (FLOAT_8043a994)
  a.streamSlot = 0;                          // +0x6ea = 0
  if ((a.controlWord & 0x40) !== 0) {        // hover latch → air slot 3
    a.streamSlot = 3;
  }
  setupLockGate(a, rangeRow868(a));          // FUN_80066838(row868) < 1 → invalidate
  // zz_006d144_(0xc0) — face.
  a.gravityCoeff = SONIC.ZERO;               // +0x50 = 0
  a.yVel = SONIC.ZERO;                       // +0x48 = 0
  a.hDecel = SONIC.ZERO;                     // +0x4c = 0
  a.hSpeed = SONIC.ZERO;                     // +0x44 = 0
  // +0x80/+0x7e/+0x7c = 0 — aim-rate accumulators (not surfaced; no-ops).
  if (a.lockTarget) {
    // Reposition: motion = (pos − target@+0x5e8) × 0.95; pos += motion.
    vecSubtract(a.pos, a.lockTarget, a.motion);
    vecScale(SONIC.X_REPOS, a.motion, a.motion); // FLOAT_8043a9a8
    vecAdd(a.pos, a.motion, a.pos);
  } else {
    // The ROM blinks UNCONDITIONALLY from the +0x5e8 target cache (which holds the
    // last aimed point even lockless — cache re-seed unmodeled). Zero the motion so
    // phases 1-2 don't drift along the PREVIOUS move's vector (stands in for the
    // cache re-seed; labeled approximation).
    a.motion.x = 0; a.motion.y = 0; a.motion.z = 0;
  }
  // zz_00677b0_(actor) — bridge clamp.
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  // zz_004beb8_(-1.0, actor, 0xf, 4, slot, 6, 1) — trailing (6,1) args are the parts
  // re-resolve pair (valkrie precedent: not consumed by the port's startStream).
  startStream(a, SAMURAI.PART_MASK, SAMURAI.X_GROUP, slot, SAMURAI.STREAM_RATE);
}

// Phase 1 — FUN_80164ce0 @ chunk_0042.c:2276. Drift + wind-up.
function sonicXPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) face + zz_006e1ac_(0xc0, 1) pitch — bridge pre-aims.
  vecScale(SONIC.X_REPOS, a.motion, a.motion); // drift ×0.95
  vecAdd(a.pos, a.motion, a.pos);
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, SAMURAI.PART_MASK, ctx);
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SONIC.ZERO) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    const slot = a.streamSlot;               // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                 // +0x6ea++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.X_GROUP, slot, SAMURAI.STREAM_RATE);
  }
}

// Phase 2 — FUN_80164dac @ chunk_0042.c:2310. Contact event → steered dash.
function sonicXPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  vecScale(SONIC.X_REPOS, a.motion, a.motion); // drift ×0.95
  vecAdd(a.pos, a.motion, a.pos);
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (a.contactP0 !== 0) {                   // +0x1cef != 0
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = SONIC.DASH_WINDOW;      // +0x558 = 20
    const pitch = s16(a.steerYaw);           // +0x18da
    a.hSpeed = SONIC.X_DASH_SPEED * projectZ(pitch);  // +0x44 = 100 × cos (zz_0045238_)
    a.yVel = SONIC.X_DASH_SPEED * -projectX(pitch);   // +0x48 = 100 × −sin (zz_0045204_)
    a.hDecel = SONIC.ZERO;                   // +0x4c = 0
    a.gravityCoeff = SONIC.ZERO;             // +0x50 = 0
    // +0x272 |= 4 — render/status halfword bit (not surfaced; labeled no-op).
    ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    // +0x80c = 0 — housekeeping no-op.
    // FUN_800061a8(actor, 0x11) → zz_00061f0_ — voice/subtitle script pointer set
    // (PTR_DAT_802c3770[0x11]; presentation-side — labeled no-op).
  }
}

// Phase 3 — FUN_80164e8c @ chunk_0042.c:2352. Dash → braked follow-through.
function sonicXPhase3(a: SActor, ctx: SamuraiFamilyCtx): void {
  integratePhysics(SONIC.X_GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, SAMURAI.PART_MASK, ctx);
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Gate: timer ≤ 0 OR (+0x1d9 & 0x90) — hit-react bits.
  if (a.handlerTimer <= SONIC.ZERO || ((a.hitReact ?? 0) & 0x90) !== 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = SONIC.X_BRAKE_WINDOW;   // +0x558 = 30 (FLOAT_8043a9b4)
    a.hSpeed *= SONIC.X_BRAKE;               // +0x44 ×= 0.5 (DOUBLE_8043a9b8)
    a.yVel *= SONIC.X_BRAKE;                 // +0x48 ×= 0.5
    if (((a.hitReact ?? 0) & 0x10) !== 0) {  // heavy-hit arm
      a.handlerTimer += SONIC.X_BRAKE_WINDOW; // +0x558 += 30
      a.hSpeed *= SONIC.X_BRAKE;             // ×0.5 again
      a.yVel *= SONIC.X_BRAKE;
      a.yVel += SONIC.X_POP_YVEL;            // +0x48 += 3 (FLOAT_8043a9c0)
      // zz_00107a0_(actor, 0xd) — despawn the kind-0xd hitboxes (star-hero.ts
      // precedent: reset the armed stream parts). The bridge owns armed-hit records;
      // labeled no-op at the actor level.
    }
  }
  // zz_00b22f4_(actor) — afterimage no-op.
}

// Phase 4 — FUN_80164f98 @ chunk_0042.c:2394. Wind-down → finisher stream.
function sonicXPhase4(a: SActor, ctx: SamuraiFamilyCtx): void {
  a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * SONIC.STEER_DECAY)); // ×0.9 (a978)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  applyDrag(a, SONIC.STEER_DECAY);           // zz_006ed8c_(0.9 — FLOAT_8043a978 reuse)
  integratePhysics(SONIC.X_GRAVITY, a, s16(a.lockYaw));
  // zz_00677b0_(actor) — bridge clamp.
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SONIC.ZERO) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    // +0x272 &= ~4 — render bit clear (no-op).
    a.yVel = SONIC.ZERO;                     // +0x48 = 0
    a.hDecel = SONIC.ZERO;                   // +0x4c = 0
    a.hSpeed = SONIC.ZERO;                   // +0x44 = 0
    a.gravityCoeff = gravityRestore(a);      // +0x50 = dataPage(+0x4ac)+0x6c
    const slot = a.streamSlot;               // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                 // +0x6ea++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.X_GROUP, slot, SAMURAI.STREAM_RATE);
  }
  // zz_00b22f4_(actor) — afterimage no-op.
}

// Phase 5 — FUN_801650a8 @ chunk_0042.c:2434. Landing / air-out.
function sonicXPhase5(a: SActor, ctx: SamuraiFamilyCtx): void {
  a.steerYaw = s16(a.steerYaw) >> 1;         // +0x18da >>= 1 (arithmetic)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  integratePhysics(SONIC.X_GRAVITY, a, s16(a.lockYaw));
  const grounded = a.grounded === true;      // iVar1 = zz_00677b0_(actor)
  if (grounded && a.contactP0 < 0) {         // landed + (s8)+0x1cef < 0
    a.steerYaw = 0;                          // +0x18da = 0
    a.controlWord &= ~0x3;                   // +0x73f = 0; +0x5e0 &= 0xfffffffc
    dispatchUpperBodyCue(a, 7);              // zz_006a750_(actor, 7)
    a.stateTimer = SONIC.X_COOLDOWN + a.dt;  // +0x694 = 4 (FLOAT_8043a9c4) + dt
    return;
  }
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    a.steerYaw = 0;                          // +0x18da = 0
    airKnockReturn(a);                       // +0x73f = 0; &= ~3; zz_006a5a4_
    a.stateTimer = SONIC.X_COOLDOWN + a.dt;  // +0x694 = 4 + dt
  }
}

/** Build the SONIC SAMURAI X handler (leaf FUN_80164b4c @ chunk_0042.c:2216; all 5
 *  variants of the a2 variant table 0x8034d5a8 point here). */
export function createSonicXSpecial(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null; // leaf's +0x541 arm
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_8034d5bc[+0x540]
      case 0: sonicXPhase0(a); break;
      case 1: sonicXPhase1(a, ctx); break;
      case 2: sonicXPhase2(a, ctx); break;
      case 3: sonicXPhase3(a, ctx); break;
      case 4: sonicXPhase4(a, ctx); break;
      case 5: sonicXPhase5(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// SAMURAI SHOGUN — three bespoke machines (chunk_0044.c). Float bank FLOAT_8043adxx:
// ad58=0.9, ad68=0, ad6c=20, ad70=−1, ad74=50, ad78=12, ad7c=1, ad80=150,
// ada0=0.8, ada4=0.92, ada8=60, adac=200, adb0=0.95, adb4=0.99, adb8=40,
// adbc=−3, adc0=8; DOUBLE_8043ad88=0.25, ad90=2.5, ad98=20.
// ============================================================================

const SHOGUN = {
  ZERO: 0.0,          // FLOAT_8043ad68
  DASH_WINDOW: 20,    // FLOAT_8043ad6c
  AIM_HEIGHT: 50,     // FLOAT_8043ad74 (target-Y lead, × (f32)+0xb4)
  AIM_Y_DIV: 12,      // FLOAT_8043ad78
  GRAVITY: 1.0,       // FLOAT_8043ad7c
  NEAR_RANGE: 150,    // FLOAT_8043ad80
  DIVE_SCALE: 0.25,   // DOUBLE_8043ad88
  REFRESH_NUM: 2.5,   // DOUBLE_8043ad90
  REFRESH_DEN: 20,    // DOUBLE_8043ad98
  NEAR_DRAG: 0.8,     // FLOAT_8043ada0
  DRAG: 0.92,         // FLOAT_8043ada4
  FACE_BUDGET: 60,    // FLOAT_8043ada8
  FX_RANGE: 200,      // FLOAT_8043adac
  DASH_DRAG: 0.95,    // FLOAT_8043adb0
  STEER_DECAY: 0.9,   // FLOAT_8043ad58
  X_COOLDOWN: 8,      // FLOAT_8043adc0
  CHRONO_FREEZE_FRAMES: 300, // zz_0067f98_(actor, 300) literal
} as const;

// --- v3/v4 SKY DIVE @0x80351908 (3 phases) ---

// Phase 1 body — zz_0175380_ @ chunk_0044.c (also tail-called by phase 0).
function shogunDivePhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  if (a.lockTarget) {                        // +0xcc != 0 → bone-relative re-aim
    // Aim origin = mainHandBone world column (+0x8e0/+0x8f0/+0x900) — bone transforms
    // are renderer-side; PORT APPROXIMATION: actor pos stands in for the hand bone.
    // Aim point = (+0x518, +0x51c + FLOAT_8043ad74 (50) × (f32)+0xb4, +0x520) — the
    // lock-target cache; the +0xb4 param-tier scale is unsurfaced (×1.0 approximation,
    // shared-aerial-dive-x precedent).
    const t = a.lockTarget;
    a.yVel = (t.y + SHOGUN.AIM_HEIGHT - a.pos.y) / SHOGUN.AIM_Y_DIV; // +0x48 = Δy / 12
    const hd = Math.hypot(t.x - a.pos.x, t.z - a.pos.z); // PSVECMag with y zeroed
    a.hSpeed = hd / SHOGUN.DASH_WINDOW;      // +0x44 = |Δxz| / 20 (FLOAT_8043ad6c)
  }
  // zz_006d144_(0xc0) — face (bridge pre-aims).
  integratePhysics(SHOGUN.GRAVITY, a, s16(a.activeYaw)); // FUN_80067310(1.0, +0x5AC)
  // zz_00677b0_(actor) — bridge clamp.
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_80066838(150) != 0 (no-lock −1 ALSO advances).
  if (a.handlerTimer <= SHOGUN.ZERO || rangeCheck(a, SHOGUN.NEAR_RANGE) !== 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.hSpeed *= SHOGUN.DIVE_SCALE;           // ×0.25 (DOUBLE_8043ad88) on all four
    a.hDecel *= SHOGUN.DIVE_SCALE;
    a.yVel *= SHOGUN.DIVE_SCALE;
    a.gravityCoeff *= SHOGUN.DIVE_SCALE;
  }
}

// Phase 0 — FUN_80175270 @ chunk_0044.c. Launch + SAME-FRAME phase-1 tail-call.
function shogunDivePhase0(a: SActor, ctx: SamuraiFamilyCtx): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  // Invalidate arm (row86c — column 1!) sets BOTH +0x5ae AND +0x5ac = +0x72.
  setupLockGate(a, rangeRow86c(a), { alsoLockYaw: true });
  a.yVel = SHOGUN.ZERO;                      // +0x48 = 0
  a.gravityCoeff = SHOGUN.ZERO;              // +0x50 = 0
  a.hSpeed = rangeRow86c(a) / SHOGUN.DASH_WINDOW; // +0x44 = row86c / 20
  a.hDecel = SHOGUN.ZERO;                    // +0x4c = 0
  a.handlerTimer = SHOGUN.DASH_WINDOW;       // +0x558 = 20 (FLOAT_8043ad6c reuse)
  ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.DIVE_FX, 0); // zz_0092dcc_(actor, 0)
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, 3, SAMURAI.STREAM_RATE); // slot 3
  shogunDivePhase1(a, ctx);                  // zz_0175380_(param_1) — tail call
}

// Phase 2 — FUN_80175508 @ chunk_0044.c. Dive-in + landing.
function shogunDivePhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if ((a.faceGate ?? 0) !== 0) {             // +0x1d10 != 0 → re-face (bridge)
    // zz_006d144_(actor, 0xc0).
  }
  const strength = a.dashStrength ?? 0;      // (s8)+0x1d0f
  if (strength > 0) {
    a.dashStrength = 0;                      // +0x1d0f = 0
    if (!a.lockTarget) {                     // +0xcc == 0
      a.hSpeed = rangeRow868(a) / SHOGUN.DASH_WINDOW; // +0x44 = row868 / 20
    } else {
      // +0x44 = (2.5 × +0x760) / 20 = dist × 0.125 (DOUBLE_8043ad90 / ad98).
      a.hSpeed = (SHOGUN.REFRESH_NUM * targetDistance(a)) / SHOGUN.REFRESH_DEN;
    }
  }
  if ((a.dashStrength ?? 0) < 0) {           // negative byte → altitude cap
    a.dashStrength = 0;                      // +0x1d0f = 0
    if (a.yVel > SHOGUN.ZERO) a.yVel = SHOGUN.ZERO; // +0x48 clamp ≤ 0
    a.gravityCoeff = gravityRestore(a);      // +0x50 = dataPage(+0x4ac)+0x6c
  }
  if (targetDistance(a) < SHOGUN.NEAR_RANGE) { // +0x760 < 150
    applyDrag(a, SHOGUN.NEAR_DRAG);          // zz_006ed8c_(0.8)
  }
  applyDrag(a, SHOGUN.DRAG);                 // zz_006ed8c_(0.92)
  integratePhysics(SHOGUN.GRAVITY, a, s16(a.activeYaw)); // FUN_80067310(1.0, +0x5AC)
  const grounded = a.grounded === true;      // iVar2 = zz_00677b0_(actor)
  if (grounded && a.contactP0 < 0) {         // landed + (s8)+0x1cef < 0
    a.gravityCoeff = gravityRestore(a);      // +0x50 = dataPage(+0x4ac)+0x6c
    a.controlWord &= ~0x3;                   // +0x73f = 0; +0x5e0 &= 0xfffffffc
    dispatchUpperBodyCue(a, 7);              // zz_006a750_(actor, 7)
    a.stateTimer = SHOGUN.GRAVITY + a.dt;    // +0x694 = 1.0 (FLOAT_8043ad7c) + dt
    return;
  }
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    airKnockReturn(a);                       // +0x73f = 0; &= ~3; zz_006a5a4_
  }
}

/** Build the SHOGUN v3/v4 sky-dive handler (dispatcher FUN_80175220). */
export function createShogunSkyDive(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_80351908[+0x540]
      case 0: shogunDivePhase0(a, ctx); break;
      case 1: shogunDivePhase1(a, ctx); break;
      case 2: shogunDivePhase2(a, ctx); break;
      default: break;
    }
  };
}

// --- v1 HEAVY SLASH @0x80351914 (4 phases) ---

// Phase 0 — FUN_8017570c @ chunk_0044.c.
function shogunHeavyPhase0(a: SActor): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  setupLockGate(a, rangeRow868(a));
  a.handlerTimer = SHOGUN.FACE_BUDGET;       // +0x558 = 60 (FLOAT_8043ada8)
  // zz_006d144_(0xc0) — face.
  startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, 5, SAMURAI.STREAM_RATE); // slot 5
}

// Phase 1 — FUN_801757c8 @ chunk_0044.c. Face budget → dash arm.
function shogunHeavyPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SHOGUN.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    a.handlerTimer = SHOGUN.DASH_WINDOW;     // +0x558 = 20 (FLOAT_8043ad6c)
    let f = rangeRow868(a);
    if (a.lockTarget && f < targetDistance(a)) f = targetDistance(a);
    a.hSpeed = f / SHOGUN.DASH_WINDOW;       // +0x44 = f / 20
    a.hDecel = SHOGUN.ZERO;                  // +0x4c = 0
    if (SHOGUN.FX_RANGE < targetDistance(a)) { // 200 < +0x760
      ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
  }
}

// Phase 2 — FUN_801758c8 @ chunk_0044.c. Dash-in → slam stream.
function shogunHeavyPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) — face.
  applyDrag(a, SHOGUN.DASH_DRAG);            // zz_006ed8c_(0.95, FLOAT_8043adb0)
  integratePhysics(0, a, s16(a.lockYaw));    // zz_00670dc_(actor, +0x5ae)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SHOGUN.ZERO || rangeCheck(a, SHOGUN.FX_RANGE) !== 0) {
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    startStream(a, SAMURAI.PART_MASK, SAMURAI.MELEE_GROUP, 4, SAMURAI.STREAM_RATE); // slot 4
  }
}

// Phase 3 — FUN_8017597c @ chunk_0044.c. Recovery.
function shogunHeavyPhase3(a: SActor, ctx: SamuraiFamilyCtx): void {
  if ((a.faceGate ?? 0) > 0) {               // (s8)+0x1d10 > 0 → re-face (bridge)
    // zz_006d144_(actor, 0xc0).
  }
  if (targetDistance(a) <= SHOGUN.FX_RANGE) { // +0x760 ≤ 200
    // +0x1d9b = 0 — stream-authored launch-block byte (not surfaced; labeled no-op).
  } else {
    applyDrag(a, SHOGUN.DASH_DRAG);          // zz_006ed8c_(0.95)
    integratePhysics(0, a, s16(a.lockYaw));  // zz_00670dc_(actor, +0x5ae)
  }
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
  }
}

/** Build the SHOGUN v1 heavy-slash handler (dispatcher FUN_801756bc). */
export function createShogunHeavySlash(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_80351914[+0x540]
      case 0: shogunHeavyPhase0(a); break;
      case 1: shogunHeavyPhase1(a, ctx); break;
      case 2: shogunHeavyPhase2(a, ctx); break;
      case 3: shogunHeavyPhase3(a, ctx); break;
      default: break;
    }
  };
}

// --- X SPECIAL @0x80351950 (4 phases; borg-switched payload) ---

// Phase 0 — FUN_80175ee8 @ chunk_0044.c. Blink + g4 stream (slot 0; CHRONO slot 1).
function shogunXPhase0(a: SActor, ctx: SamuraiFamilyCtx): void {
  a.fbPhaseSlots[0] += 1;                    // +0x540++
  a.streamSlot = 0;                          // +0x6ea = 0
  if (a.borgNumber === 0x707) {              // +0x3e8 == 0x707 (CHRONO SAMURAI)
    a.streamSlot = 1;                        // +0x6ea = 1
  }
  a.handlerTimer = SHOGUN.FACE_BUDGET;       // +0x558 = 60 (FLOAT_8043ada8)
  // zz_006d144_(0xc0) face + zz_006e1ac_(0xc0, 1) pitch — bridge pre-aims.
  a.gravityCoeff = SHOGUN.ZERO;              // +0x50 = 0
  a.yVel = SHOGUN.ZERO;                      // +0x48 = 0
  a.hDecel = SHOGUN.ZERO;                    // +0x4c = 0
  a.hSpeed = SHOGUN.ZERO;                    // +0x44 = 0
  // +0x80/+0x7e/+0x7c = 0 — aim-rate accumulators (not surfaced; no-ops).
  if (a.lockTarget) {
    // Reposition: motion = (pos − target@+0x5e8) × 0.95; pos += motion.
    vecSubtract(a.pos, a.lockTarget, a.motion);
    vecScale(SHOGUN.DASH_DRAG, a.motion, a.motion); // FLOAT_8043adb0 (0.95)
    vecAdd(a.pos, a.motion, a.pos);
  } else {
    // The ROM blinks UNCONDITIONALLY from the +0x5e8 target cache (chunk_0044.c:
    // 1709-1712 — cache re-seed unmodeled). Zero the motion so phases 1-2 don't
    // drift along the PREVIOUS move's vector (stands in for the cache re-seed;
    // labeled approximation).
    a.motion.x = 0; a.motion.y = 0; a.motion.z = 0;
  }
  // zz_00677b0_(actor) — bridge clamp.
  const slot = a.streamSlot;                 // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                   // +0x6ea++
  startStream(a, SAMURAI.PART_MASK, SAMURAI.X_GROUP, slot, SAMURAI.STREAM_RATE);
  if (a.borgNumber === 0x704) {              // SAMURAI SHOGUN only
    // zz_01a5e88_(actor, 0) — X trail child (record kind 0x26).
    ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.SHOGUN_X_TRAIL, 0);
  }
}

// Phase 1 — FUN_80175ffc @ chunk_0044.c. Drift + wind-up.
function shogunXPhase1(a: SActor, ctx: SamuraiFamilyCtx): void {
  vecScale(SHOGUN.DASH_DRAG, a.motion, a.motion); // drift ×0.95
  vecAdd(a.pos, a.motion, a.pos);
  // zz_00677b0_(actor) — bridge clamp.
  if (a.streamTickGate) {                    // +0x1b03 != 0
    tickStream(a, SAMURAI.PART_MASK, ctx);
  }
  // zz_006e1ac_(0xc0, 1) — pitch seek (bridge).
  a.handlerTimer -= a.dt;                    // +0x558 -= dt
  if (a.handlerTimer <= SHOGUN.ZERO || faceComplete(a)) { // timer OR zz_006d144_(0xc0)
    a.fbPhaseSlots[0] += 1;                  // +0x540++
  }
}

// Phase 2 — FUN_801760b4 @ chunk_0044.c. Swing event → borg-switched payload.
function shogunXPhase2(a: SActor, ctx: SamuraiFamilyCtx): void {
  // zz_006d144_(0xc0) face + zz_006e1ac_(0xc0, 1) pitch — bridge.
  vecScale(SHOGUN.DASH_DRAG, a.motion, a.motion); // drift ×0.95
  vecAdd(a.pos, a.motion, a.pos);
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if (swingEventByte(a) !== 0) {             // +0x1cf0 != 0 (unstamped → −1 TUNED
                                             // fallback — no stream-event deadlock)
    a.fbPhaseSlots[0] += 1;                  // +0x540++
    if (a.borgNumber === 0x704) {
      // zz_018eea4_(actor, 0) — SHOGUN strike child (record kind 0x37).
      ctx.onFamilyProjectile?.(a, SAMURAI_SPAWNERS.SHOGUN_X_CHILD, 0);
    } else if (a.borgNumber === 0x707) {
      // zz_0067f98_(actor, 300) — CHRONO time-stop (global freeze table write).
      ctx.onTimeStop?.(a, SHOGUN.CHRONO_FREEZE_FRAMES);
    }
  }
}

// Phase 3 — FUN_80176170 @ chunk_0044.c. Fall-out / landing.
function shogunXPhase3(a: SActor, ctx: SamuraiFamilyCtx): void {
  a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * SHOGUN.STEER_DECAY)); // ×0.9 (ad58)
  tickStream(a, SAMURAI.PART_MASK, ctx);
  if ((a.dashStrength ?? 0) < 0) {           // (s8)+0x1d0f < 0
    a.dashStrength = 0;                      // +0x1d0f = 0
    a.gravityCoeff = gravityRestore(a);      // +0x50 = dataPage(+0x4ac)+0x6c
  }
  integratePhysics(SHOGUN.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  const grounded = a.grounded === true;      // iVar1 = zz_00677b0_(actor)
  if (!grounded && a.contactP0 < 0) {        // airborne + (s8)+0x1cef < 0
    a.steerYaw = 0;                          // +0x18da = 0
    airKnockReturn(a);                       // +0x73f = 0; &= ~3; zz_006a5a4_
    a.stateTimer = SHOGUN.X_COOLDOWN + a.dt; // +0x694 = 8 (FLOAT_8043adc0) + dt
    return;
  }
  if (a.wallContact !== 0) {                 // +0x1cee != 0
    a.steerYaw = 0;                          // +0x18da = 0
    groundIdleReturn(a);                     // +0x73f = 0; &= ~3; zz_006a474_
    a.stateTimer = SHOGUN.X_COOLDOWN + a.dt; // +0x694 = 8 + dt
  }
}

/** Build the SHOGUN X handler (leaf FUN_80175eac — NOTE: no +0x541 lock-clear arm,
 *  unlike every other dispatcher in the cluster). */
export function createShogunXSpecial(ctx: SamuraiFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as SActor;
    switch (a.fbPhaseSlots[0] ?? 0) {        // PTR_FUN_80351950[+0x540]
      case 0: shogunXPhase0(a, ctx); break;
      case 1: shogunXPhase1(a, ctx); break;
      case 2: shogunXPhase2(a, ctx); break;
      case 3: shogunXPhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// Per-borg wiring.
// ============================================================================

export type SamuraiClusterBorgId =
  | "pl0700" | "pl0701" | "pl0702" | "pl0703" | "pl0704" | "pl0705"
  | "pl0707" | "pl0708" | "pl0709" | "pl070a" | "pl070b" | "pl070c" | "pl070d";

type SamuraiFamilyKey = "normal" | "demon" | "vampire" | "sonic" | "shogun" | "zeta";

const SAMURAI_BORGS: Record<SamuraiClusterBorgId, { num: number; family: SamuraiFamilyKey }> = {
  pl0700: { num: 0x700, family: "normal" },
  pl0701: { num: 0x701, family: "demon" },
  pl0702: { num: 0x702, family: "vampire" },
  pl0703: { num: 0x703, family: "sonic" },
  pl0704: { num: 0x704, family: "shogun" },
  pl0705: { num: 0x705, family: "zeta" },
  pl0707: { num: 0x707, family: "shogun" },
  pl0708: { num: 0x708, family: "demon" },
  pl0709: { num: 0x709, family: "normal" },
  pl070a: { num: 0x70a, family: "vampire" },
  pl070b: { num: 0x70b, family: "zeta" },
  pl070c: { num: 0x70c, family: "demon" },
  pl070d: { num: 0x70d, family: "demon" },
};

/** The family's action-1 v2 machine. */
function createV2Machine(family: SamuraiFamilyKey, ctx: SamuraiFamilyCtx): (a: RomActor) => void {
  switch (family) {
    case "normal": return createRisingSlash(NORMAL_RISING_CONFIG, ctx);
    case "zeta": return createRisingSlash(ZETA_RISING_CONFIG, ctx);
    case "shogun": return createRisingSlash(SHOGUN_RISING_CONFIG, ctx);
    case "demon": return createDemonRisingSlash(ctx);
    case "vampire": return createVampireLeapSlash(ctx);
    case "sonic": return createSonicMultiSlash(ctx);
  }
}

/** The family's action-2 X machine (per-borg for the demon config split). */
function createXMachine(borgId: SamuraiClusterBorgId, family: SamuraiFamilyKey, ctx: SamuraiFamilyCtx): (a: RomActor) => void {
  switch (family) {
    case "normal":  // wrapper FUN_800c8538 → zz_0149708_ cfg @0x80308078
      return createSharedFlightX(FLIGHT_X_FAMILY1_CONFIG, ctx);
    case "demon":   // wrapper FUN_801233cc (borg-switched cfg @0x8032c814 / 0x8032c838)
      return createSharedFlightX(
        borgId === "pl070c" || borgId === "pl070d" ? FLIGHT_X_FAMILY2B_CONFIG : FLIGHT_X_FAMILY2A_CONFIG,
        ctx,
      );
    case "vampire": // wrapper FUN_80144504 → zz_0149708_ cfg @0x8033c3d4
      return createSharedFlightX(FLIGHT_X_FAMILY3_CONFIG, ctx);
    case "zeta":    // wrapper FUN_8019cfb4 → zz_0149708_ cfg @0x80373848
      return createSharedFlightX(FLIGHT_X_FAMILY4_CONFIG, ctx);
    case "sonic":   // OWN table @0x8034d5bc
      return createSonicXSpecial(ctx);
    case "shogun":  // OWN table @0x80351950
      return createShogunXSpecial(ctx);
  }
}

/**
 * Configure a samurai-cluster borg. Wires (per the actionStreamTables audit +
 * per-family variant tables 0x80307ff8 / 0x8032c790 / 0x8033c358 / 0x8034d544 /
 * 0x803518e0 / 0x803737c8):
 *   action 0 → table S-A ranged dash-slash (all 5 variants — table 0x8033ecf8)
 *   action 1 v0 → table S-B close slash (seed 0) ─ SHOGUN included
 *            v1 → table S-B close slash (seed 4) ─ SHOGUN: own heavy slash
 *            v2 → per-family bespoke machine
 *            v3/v4 → zz_0149178_ lunge (melee-samurai.ts, ROM config) ─ SHOGUN: sky dive
 *   action 2 → shared lance flight zz_0149708_ ─ SONIC/SHOGUN: own X machines
 */
export function configureSamuraiClusterFamily(
  actor: RomActor,
  borgId: SamuraiClusterBorgId,
  ctx: SamuraiFamilyCtx,
): void {
  const entry = SAMURAI_BORGS[borgId];
  actor.borgNumber = entry.num;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  const family = entry.family;
  const rangedDash = createSamuraiRangedDash(ctx);
  const closeV0 = createSamuraiCloseSlash(SAMURAI_CLOSE_V0_CONFIG, ctx);
  const closeV1 = family === "shogun" ? null : createSamuraiCloseSlash(SAMURAI_CLOSE_V1_CONFIG, ctx);
  const heavyV1 = family === "shogun" ? createShogunHeavySlash(ctx) : null;
  const v2 = createV2Machine(family, ctx);
  const v34 = family === "shogun"
    ? createShogunSkyDive(ctx)
    : createMeleeSamurai(ctx, SAMURAI_LUNGE_ROM_CONFIG); // zz_0149178_ w/ ROM config
  const xSpecial = createXMachine(borgId, family, ctx);
  actor.rootAction = (ra: RomActor) => {
    const a = ra as SActor;
    switch (a.actionIndex) {
      case 0:
        // Wrapper FUN_801487c4: +0x18da ×= 0.9 (FLOAT_8043a360) then the variant
        // table 0x8033ecf8 (5× FUN_80148838 — variant-independent).
        a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * SAMURAI.STEER_DECAY));
        rangedDash(a);
        break;
      case 1: {
        // Per-family wrapper (FUN_800c7fe8 / FUN_80122cb0 / FUN_80143fac /
        // FUN_80164664 / FUN_80175184 / FUN_8019ca64): +0x18da ×= 0.9 (their banks
        // all DOL-read 0.9) then the family variant table by +0x581.
        a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * SAMURAI.STEER_DECAY));
        const v = a.variantIndex;
        if (v >= 3) v34(a);
        else if (v === 2) v2(a);
        else if (v === 1) (heavyV1 ?? closeV1!)(a);
        else closeV0(a);
        break;
      }
      case 2:
        // Family a2 handlers (FUN_800c84fc etc.) dispatch the variant table directly
        // (no steer decay); all 5 entries are the same leaf.
        xSpecial(a);
        break;
      default:
        break;
    }
  };
}
