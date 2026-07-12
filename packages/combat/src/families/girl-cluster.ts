// GIRL cluster — 1:1 port of the shared + per-family phase-table machines used by
// 8 families / 14 borgs (DOL pointer-table dumps confirm every boundary below):
//   BATTLE GIRL          pl0300 / pl030b KEI            (ctor 0x800c04c0, root 0x800c086c)
//   WIRE GIRL            pl0301                         (ctor 0x80106e3c, root 0x80107278)
//   BARRIER GIRL         pl0302 / pl0306                (ctor 0x80107e7c, root 0x801080e4)
//   DEATH BORG DELTA II  pl0303                         (ctor 0x8019c380, root 0x8019c4d4)
//   KILLER GIRL          pl0304 / pl0308 SHADOW GIRL    (ctor 0x80134078, root 0x80134580)
//   CYBER GIRL SUPER     pl0305 / pl0309 / pl030a       (ctor 0x8012f204, root 0x8012f5bc)
//   SPINNER GIRL         pl0307 / pl030d                (ctor 0x801ba020, root 0x801ba33c)
//   DEATH BORG DELTA     pl030c                         (ctor 0x801d429c, root 0x801d447c)
//
// SHARED action-0 B-ranged system (decomp: chunk_0030.c:601-1131):
//   Handler FUN_8010a508 (+0x18da >>= 1; +0x1900 ×0.96) → variant table @0x80325a00
//   (DOL dump: [FUN_8010a588, FUN_8010a9b4 ×3, FUN_8010ade8] — v0 → G-A, v1..v3 → G-B,
//   v4 → G-C).
//   G-A @0x80325a14 — 3 phases [FUN_8010a5d0 :634, FUN_8010a6b0 :667, FUN_8010a78c
//     :702] (next word 0x80325a20 = G-B start = past end). Dispatcher FUN_8010a588
//     (+0x1dfc >>= 1).
//   G-B @0x80325a20 — 3 phases [FUN_8010a9f0 :793, FUN_8010aa98 :821, FUN_8010ab78
//     :857]. Dispatcher FUN_8010a9b4 (no prelude).
//   G-C @0x80325a2c — 3 phases [FUN_8010ae30 :960, FUN_8010af04 :984, FUN_8010ab78]
//     — CONFIRMED: shares the G-B phase-2 body. Dispatcher FUN_8010ade8 (+0x1dfc >>= 1).
//   Volley fire FUN_8010b02c :1035 (borg-switched spawn) + state seeder zz_010afd0_
//   :1016. Per-borg data tables indexed by the borg LOW byte (+0x3e9), ALL DOL-read:
//     counts   @0x80325980 (u8):  [5,3,3,3,5,100,3,3,5,100,100,5,3,3]
//     interval @0x80325990 (f32): [5,5,5,5,5,20,5,5,5,20,20,5,5,5]
//     tick-dly @0x803259c8 (f32): all 0.0
//
// SHARED action-1 melee tables (leaf thunks pass the +0x6ea seed slot in r4):
//   M-1 @0x80325a68 — 4 phases [FUN_8010b344 :1148, FUN_8010b400 :1179, FUN_8010b51c
//     :1224, FUN_8010b610 :1261] (next word = M-2 start). Dispatcher zz_010b2f4_ :1134.
//     Seed 0 for every family (r4 immediates verified).
//   M-2 @0x80325a78 — melee-girl-lunge.ts (rewritten this batch).
//   M-3 @0x80325a88 — 4 phases [FUN_8010bd60 :1527, FUN_8010be74 :1565, FUN_8010bfbc
//     :1610, FUN_8010c074 :1641] (next word = M-4 start). Dispatcher zz_010bd10_ :1513.
//   M-4 @0x80325a98 — melee-girl-standing.ts (rewritten this batch).
//   M-5 @0x80325aa8 — 4 phases [FUN_8010c5e0 :1842, FUN_8010c720 :1883, FUN_8010c7e8
//     :1913, FUN_8010c8e0 :1949] (next word 0x80325ab8 = the series-3 variant table
//     5×0x8010ce60 = past end — the "0x8010ce60 repeats" in the batch brief was the
//     NEXT table, not an M-5 overread).
//   Per-family variant map (actionStreamTables.json emulated r4 seeds): v0 → M-1(0),
//   v1 → M-4, v2 → M-3, v3 → M-2(4), v4 → M-5. Seeds: girls M-4=8/M-3=5/M-5=7;
//   KILLER M-4=9/M-3=6/M-5=8; DELTA (pl030c) v1/v2 → M-4(6), v3 → M-2(4), v4 → M-2(5).
//
// SHARED X (actions 2) — table @0x80434508, dispatcher zz_010c9d8_ :1986. BOUNDARY
// CORRECTION vs the batch brief: the table has TWO live phases [FUN_8010ca10 :1997,
// FUN_8010cb48 :2038]; entry [2] (0x800a4000) is dead — 0x800a4000 is not a function
// start in the corpus index and NOTHING writes +0x540 = 2 (phase 1 has no increment).
// CONFIG-DRIVEN (the leaf thunks' r4): {s32 seedSlot, f32 driftScale, f32 groundSpeed,
// fnptr payload}. Configs (raw-word verified thunk loads + DOL dumps):
//   KILLER pl0304  @0x80336d94: {0, 0.95, 6.0932398, FUN_80134714}  (thunk zz_01346ec_)
//   BARRIER pl0306 @0x8032411c: {2, 0.95, 6.0932398, FUN_80108530}  (thunk FUN_80108508)
// Payloads: zz_006dbe0_(a,2,1,1) ammo deduct → zz_016cc24_(a, 1 / 0xf) armed-shot
// deploy (cyber-machine.ts EFFECT_SPAWNER precedent).
//
// PER-FAMILY X (action 2):
//   BATTLE GIRL @0x80433b18 — BOUNDARY CORRECTION: TWO actor phases [FUN_800c0a2c
//     chunk_0019.c:4417, FUN_800c0b44 chunk_0020.c:1]; the remaining 6 pointers are
//     CHILD-OBJECT update tables (@0x80433b20/28/30, dispatched by child+0x19 —
//     FUN_800c30f8/FUN_800c344c read PTR_LAB_80433b20/PTR_FUN_80433b28) belonging to
//     the zz_00fe668_ X child, not the actor machine.
//   BARRIER GIRL pl0302 @0x804344d8 — BOUNDARY CORRECTION: TWO actor phases
//     [FUN_80108294 chunk_0029.c:2820, FUN_80108344 :2850] (phase 0 tail-calls phase 1;
//     phase 1 never increments +0x540); the pointer run 0x804344e0..0x80434504 belongs
//     to the barrier child object, not this machine. Engine FUN_80108250 (+0x18da >>= 1),
//     borg-switch leaf FUN_8010821c :2792 (0x306 → shared X; else bespoke).
//   KILLER GIRL pl0308 @0x80336da4 — 5 phases CONFIRMED [FUN_801347c0 chunk_0035.c:2603,
//     FUN_8013490c :2651, FUN_801349c4 :2678, FUN_80134af8 :2724, FUN_80134c38 :2772]
//     (next word 0x80336db8 = 0x000c0101 data). Engine zz_0134770_ :2589, borg-switch
//     leaf FUN_801346b8 :2541 (0x308 → bespoke; else shared X).
//   CYBER GIRL @0x80333a80 / @0x804345c0 — families/cyber-girl.ts (REUSED).
//   SPINNER / DELTA-II / WIRE / BARRIER action 2/3 → series-3 X @0x80325acc
//     (families/shared-series3-x.ts, REUSED; per-borg slot layout preserved).
//
// Float constants — every value DOL-read from user-data/GG4E/disc/sys/boot.dol; the
// 0x43300000 CONCAT44 idiom (DOUBLE_80439548/80439f60) is the int→float sentinel,
// NOT gameplay data. Shared bank FLOAT_804395xx: 540=0.9, 550=0.96, 554=−1, 558=0,
// 55c=0.95, 560=3, 564=1, 568=20, 56c=60, 570=0.0625, 574=200, 578=0.5, 57c=30,
// 580=150, 588(dbl)=2.5, 590(dbl)=20, 598=0.98. Battle-girl bank FLOAT_804386xx:
// 618=0, 61c=0.95, 620=−1, 624=1. Barrier bank FLOAT_804394xx: e8=0, ec=−1, f0=1,
// f4=0.95, f8=8. Killer bank FLOAT_80439fxx: 30=0, 34=60, 38=0.95, 3c=−1, 40=10,
// 44=1, 48=20, 4c=100, 50=0.9, 54=16, 58=4.
//
// Idle-return: exits transcribed per-arm against the decomp — zz_006a474_/zz_006a5a4_
// via shared-idle-return.ts; the ranged exits additionally run zz_006a668_'s tail
// (zz_006a6fc_(a, +0x5e4) full-body cue re-dispatch — chunk_0009.c:801-828; the +0x694
// floor arm is dead because the caller clears bits 0..1 first); landing arms dispatch
// zz_006a750_(a, 7) directly.

import type { RomActor, RomPartState, Vec3 } from "../rom/actor.js";
import { dispatchFullBodyCue, dispatchUpperBodyCue } from "../rom/dispatch.js";
import { integratePhysics, projectX, projectZ, vecAdd, vecScale, vecSubtract } from "../rom/physics.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";
import { startStream, tickStream } from "../rom/stream-vm.js";
import { createMeleeGirlLunge } from "./melee-girl-lunge.js";
import { createMeleeGirlStanding } from "./melee-girl-standing.js";
import { createSeries3XSpecial, series3XActionSlots, type Series3FamilyCtx } from "./shared-series3-x.js";
import { createCyberGirlRootAction } from "./cyber-girl.js";
import {
  groundSnapRevert,
  resetPoseHousekeeping,
  stepAfterimage,
  stepTargetPitch,
  stepTargetRoll,
  stepTargetYaw,
} from "../rom/helpers.js";

/** Shared-cluster constants (FLOAT_804395xx bank, DOL-read — see header). */
export const GIRL = {
  RECOVERY_DRAG: 0.9,       // FLOAT_80439540
  METER_DECAY: 0.96,        // FLOAT_80439550 (+0x1900 ×0.96 per handler frame)
  STREAM_RATE: -1.0,        // FLOAT_80439554
  ZERO: 0.0,                // FLOAT_80439558
  DRAG: 0.95,               // FLOAT_8043955c (blink scale + active drag)
  AFTERIMAGE_MIN: 3.0,      // FLOAT_80439560 (zz_00b22f4_ gate — renderer no-op)
  GRAVITY: 1.0,             // FLOAT_80439564
  ACTIVE_WINDOW: 20.0,      // FLOAT_80439568 (dash divisor + volley re-fire window)
  FACE_BUDGET: 60.0,        // FLOAT_8043956c
  DASH_BYTE_SCALE: 0.0625,  // FLOAT_80439570 ((s8)+0x1d0f strength scale)
  FX_RANGE: 200.0,          // FLOAT_80439574 (M-1/M-3 melee-FX + proximity gate)
  SWING_BRAKE: 0.5,         // FLOAT_80439578 (M-1 phase 2→3 speed halving)
  RUSH_WINDOW: 30.0,        // FLOAT_8043957c (M-3 dash window; M-5/M-2 dive magnitude;
                            //  shared-X payload-fail cooldown)
  PROXIMITY: 150.0,         // FLOAT_80439580 (M-4/M-5 range gate)
  BLINK_SOFT: 0.98,         // FLOAT_80439598 (M-3/M-5 blink-reposition scale)
  RANGED_GROUP: 2,
  MELEE_GROUP: 3,
  X_GROUP: 4,
  PART_MASK: 0xf,
} as const;

/** ROM spawner/helper addresses routed through ctx.onFamilyProjectile. */
export const GIRL_SPAWNERS = {
  /** zz_0082824_ @0x80082824 — blast-record child (series3 BLAST_SPAWNER precedent). */
  BLAST: 0x80082824,
  /** zz_00c3be0_ @0x800c3be0 — kind-2 child (series3 CHILD_SPAWNER precedent). */
  KIND2_CHILD: 0x800c3be0,
  /** zz_00b2190_ @0x800b2190 — melee trail FX child. */
  MELEE_FX: 0x800b2190,
  /** zz_0092dcc_ @0x80092dcc — dive FX child. */
  DIVE_FX: 0x80092dcc,
  /** zz_016cc24_ @0x8016cc24 — armed-shot deploy (shared-X payload; cyber-machine
   *  EFFECT_SPAWNER precedent). The `type` argument carries the ROM part mask. */
  ARMED_SHOT: 0x8016cc24,
  /** zz_00fe668_ @0x800fe668 — BATTLE GIRL X child (variant 0 = pl0300, 1 = pl030b;
   *  the child runs its own +0x19-indexed update tables @0x80433b20/28/30). */
  BATTLE_X_CHILD: 0x800fe668,
  /** FUN_800a6108 @0x800a6108 — BARRIER GIRL barrier-field child. */
  BARRIER_CHILD: 0x800a6108,
  /** FUN_8016c810 @0x8016c810 — KILLER GIRL X ring-burst child (called once per
   *  +0x55c tick with the decrementing +0x560 float as r4 — the float parameter is
   *  not carried by the hook signature; labeled). */
  KILLER_RING_CHILD: 0x8016c810,
} as const;

/** BATTLE GIRL X bank (FLOAT_804386xx, DOL-read). */
const BATTLE_X = {
  ZERO: 0.0,       // FLOAT_80438618
  BLINK: 0.95,     // FLOAT_8043861c
  RATE: -1.0,      // FLOAT_80438620
  COOLDOWN: 1.0,   // FLOAT_80438624 (landing cue-7 +0x694 seed)
} as const;

/** BARRIER GIRL X bank (FLOAT_804394xx, DOL-read). */
const BARRIER_X = {
  ZERO: 0.0,       // FLOAT_804394e8
  RATE: -1.0,      // FLOAT_804394ec
  GRAVITY: 1.0,    // FLOAT_804394f0
  DRIFT: 0.95,     // FLOAT_804394f4
  COOLDOWN: 8.0,   // FLOAT_804394f8
} as const;

/** KILLER GIRL X bank (FLOAT_80439fxx, DOL-read). */
const KILLER_X = {
  ZERO: 0.0,        // FLOAT_80439f30
  FACE_BUDGET: 60,  // FLOAT_80439f34
  DRIFT: 0.95,      // FLOAT_80439f38
  RATE: -1.0,       // FLOAT_80439f3c
  SPIN_WINDOW: 10,  // FLOAT_80439f40 (phase-3 +0x558 seed)
  GRAVITY: 1.0,     // FLOAT_80439f44 (also the ring-tick interval + cue-7 seed base)
  RING_COUNT: 20,   // FLOAT_80439f48 (phase-3 +0x560 seed — one child per tick)
  SPIN_SPEED: 100,  // FLOAT_80439f4c (phase-2 +0x18da-projected launch magnitude)
  STEER_DECAY: 0.9, // FLOAT_80439f50
  COOLDOWN_LAND: 16, // FLOAT_80439f54
  COOLDOWN_END: 4,  // FLOAT_80439f58
} as const;

/** Per-borg volley data, indexed by the borg LOW byte (+0x3e9). ALL DOL-read:
 *  counts @0x80325980, intervals @0x80325990, tick delays @0x803259c8 (all 0.0). */
const VOLLEY_COUNTS: ReadonlyArray<number> = [5, 3, 3, 3, 5, 100, 3, 3, 5, 100, 100, 5, 3, 3];
const VOLLEY_INTERVALS: ReadonlyArray<number> = [5, 5, 5, 5, 5, 20, 5, 5, 5, 20, 20, 5, 5, 5];
const VOLLEY_TICK_DELAY = 0.0;

/** Host hooks beyond the base StreamContext. Extends the series-3 ctx so the reused
 *  series-3 X machine shares the same ammo hooks. */
export interface GirlFamilyCtx extends Series3FamilyCtx {
  /** zz_006a3d0_(actor, button, subtype, charged) — command re-dispatch through the
   *  +0x4ec command table (the ranged machines' aim-fail / air-retrigger arms).
   *  UNWIRED FALLBACK: ground/air idle return via shared-idle-return.ts (labeled —
   *  the move simply ends instead of chaining into the redirected command). */
  onCommandRedispatch?: (actor: RomActor, button: number, subtype: number, charged: number) => void;
}

/** Per-actor scratch fields (ROM offsets not surfaced as named RomActor fields). */
interface GirlScratch {
  // ---- host-set inputs ----
  /** +0x5d4 & 0x40 — B button edge this frame. */
  bRetapInput?: boolean;
  /** +0x5d4 uint — raw input-edge word (bit 0 gates the G-A phase-2 exit). */
  inputEdge5d4?: number;
  /** +0x5d8 ushort — held-input word (& 0xf0 gates the ranged phase-2 exits). */
  inputHeld5d8?: number;
  /** +0x1b03 — stream-tick gate (anim hold byte). */
  streamTickGate?: boolean;
  /** +0x1d9 — hit-react/impact status byte (M-3/M-4/M-5 phase-2 advance; killer X
   *  phase-4 & 0x10 ack). */
  hitReact?: number;
  /** +0x1dd — hit-react status byte (M-1 phase-2 & 0x80 motion freeze). */
  hitReact1dd?: number;
  /** +0x5b4 uint — status word (& 0x200 gates the cyber/barrier volley re-trigger). */
  statusWord5b4?: number;
  grounded?: boolean;
  lockTarget?: { x: number; y: number; z: number } | null;
  /** actor+0x868 / +0x86c range rows. */
  rangeRow868?: number;
  rangeRow86c?: number;
  // ---- machine state ----
  /** +0x746 — B-retap latch. */
  bRetap?: boolean;
  /** +0x560 — ranged aim-window timer. */
  window560?: number;
  /** +0x55c — ranged stream-tick delay timer. */
  tickDelay55c?: number;
  /** +0x6ee — volley slot-base / "has fired" latch (persists across moves, ROM). */
  volleySlotBase?: number;
  /** +0x6ef — volleys remaining. */
  volleysLeft?: number;
  /** +0x1900 — meter/aim-pitch s16 (series3 meter1900 — same offset). */
  meter1900?: number;
  /** +0x1dfc — ranged aim-yaw offset (halved by the G-A/G-C dispatchers). */
  aimYawTrack?: number;
  /** +0x54e — melee aim pitch (valkrie meleeAimPitch — same offset). */
  meleeAimPitch?: number;
  /** (s8)+0x1d0f — stream-authored dash-strength byte. */
  dashStrength?: number;
  /** +0x1d10 — face re-seek gate byte (ALSO the G-B slot-select offset). */
  faceGate?: number;
  /** (s8)+0x1cf0 — part-0 swing event byte (< 0 = combo re-arm). */
  swingEvent?: number;
  /** +0x146 — BARRIER GIRL child-link mode byte (1 = barrier alive → re-arm). */
  barrierMode146?: number;
  /** +0x760/+0x764 distance mirror. */
  curTargetDist?: number;
}

type GActor = RomActor & GirlScratch;

function s16(v: number): number {
  return (v << 16) >> 16;
}

/** +0x760/+0x764 mirror — refresh on locked reads, stale cache when unlocked. */
function targetDistance(a: GActor): number {
  const t = a.lockTarget;
  if (t) {
    a.curTargetDist = Math.hypot(t.x - a.pos.x, t.z - a.pos.z);
    return a.curTargetDist;
  }
  return a.curTargetDist ?? 0;
}

/** FUN_80066838 / FUN_800668cc — range gate: −1 no lock, 1 in range, 0 beyond. */
function rangeCheck(a: GActor, range: number): number {
  if (!a.lockTarget) return -1;
  return targetDistance(a) <= range ? 1 : 0;
}

function rangeRow868(a: GActor): number {
  return a.actionSpeedRows[0];
}
function rangeRow86c(a: GActor): number {
  return a.actionSpeedRows[1];
}

/** zz_006d144_(0xc0) / zz_006d0dc_(0xc1, 0) — face the lock target; nonzero = facing
 *  complete (bridge pre-aims lockYaw — shared-melee-gred precedent). */
function faceComplete(a: GActor): boolean {
  return stepTargetYaw(a, 0xc0);
}

/** zz_006e514_(actor, 0xc0, &+0x54e) — aim-pitch seek (valkrie seekMeleeAimPitch
 *  approximation: snap with a target, decay without). */
function seekAimPitch(a: GActor): void {
  const next = stepTargetPitch(a, 0xc0, a.meleeAimPitch ?? 0);
  a.meleeAimPitch = next.value;
}

/** zz_006dee8_(actor, mode) — rate-limited yaw track toward the target bearing
 *  (+0x1dfc channel, ±0x800/frame, cone ±0x4800). PORT APPROXIMATION: no lock →
 *  −1 (out of cone); locked in-cone → snap +0x1dfc and return 0x8444 "aligned"
 *  (the bridge pre-aims — rate limit modeled as instant). */
function aimTrack(a: GActor): number {
  const helper = a as GActor & { aimRoll1dfc?: number };
  helper.aimRoll1dfc = a.aimYawTrack ?? 0;
  const result = stepTargetRoll(helper, true);
  a.aimYawTrack = helper.aimRoll1dfc ?? 0;
  return result;
}

/** (s8)+0x1d0f read with the liveness/gameplay fallback (samurai dashByte precedent
 *  — labeled TUNED; sites that merely test the SIGN keep the plain `?? 0` read). */
function dashByte(a: GActor): number {
  return a.dashStrength1d0f;
}

/** zz_006ed8c_(scale, actor) — velocity drag on +0x44/+0x48. */
function applyDrag(a: GActor, scale: number): void {
  a.hSpeed *= scale;
  a.yVel *= scale;
}

function vecMagnitude(v: Vec3): number {
  return Math.hypot(v.x, v.y, v.z);
}

/** dataPage(+0x4ac)+0x6c — gravityCoeff restore. */
function gravityRestore(a: GActor): number {
  return a.descriptor?.handlerData6c ?? 1.0;
}

/** The setup-phase lock-invalidate idiom: FUN_80066838(row) < 1 → +0x541 = 1,
 *  +0xcc = 0, +0x5ac = source (samurai setupLockGate precedent). */
function setupLockGate(a: GActor, row: number, activeFrom: "heading" | "lockYaw"): void {
  if (rangeCheck(a, row) < 1) {
    a.fbPhaseSlots[1] = 1;                        // +0x541 = 1
    a.lockTarget = null;                          // +0xcc = 0
    a.activeYaw = activeFrom === "heading" ? a.heading : a.lockYaw;
  }
}

/** Blink-reposition from the +0x5e8 target cache: motion = pos − target; ×scale;
 *  pos += motion. No lock → zero the motion (blink rule — never a stale vector). */
function blinkReposition(a: GActor, scale: number): void {
  vecSubtract(a.pos, a.targetCache5e8, a.motion);
  vecScale(scale, a.motion, a.motion);
  vecAdd(a.pos, a.motion, a.pos);
}

/** motion ×= scale; pos += motion (the per-frame drift continuation). */
function driftMotion(a: GActor, scale: number): void {
  vecScale(scale, a.motion, a.motion);
  vecAdd(a.pos, a.motion, a.pos);
}

/** zz_006a3d0_(actor, button, subtype, charged) — command re-dispatch. UNWIRED
 *  FALLBACK: end the move via the grounded-appropriate idle return (labeled). */
function commandRedispatch(a: GActor, ctx: GirlFamilyCtx, button: number, subtype: number, charged: number): void {
  if (ctx.onCommandRedispatch) {
    ctx.onCommandRedispatch(a, button, subtype, charged);
    return;
  }
  a.controlWord &= ~0x3;
  if (a.grounded === true) romGroundIdleReturn(a);
  else romAirKnockoutReturn(a);
}

/** zz_006a668_ tail @ chunk_0009.c:801-828 — with bits 0..1 just cleared the +0x694
 *  floor arm is skipped; zz_0048d54_ (armed shot-channel release — bridge-owned
 *  no-op) then zz_006a6fc_(a, +0x5e4): re-dispatch the FULL-BODY cue from the
 *  current upper cue id. */
function shotStateRelease(a: GActor): void {
  dispatchFullBodyCue(a, a.ubCue);
}

// ============================================================================
// SHARED action 0 — B ranged volley (handler FUN_8010a508 @0x8010a508, variant
// table @0x80325a00; chunk_0030.c:601-1131).
// ============================================================================

/** zz_010afd0_ @ chunk_0030.c:1016 — volley state seeder (per-borg tables). */
function seedVolleyState(a: GActor): void {
  a.window560 = GIRL.ACTIVE_WINDOW;               // +0x560 = FLOAT_80439568 (20)
  const low = a.borgNumber & 0xff;                // +0x3e9 (borg low byte)
  a.handlerTimer = VOLLEY_INTERVALS[low] ?? 5;    // +0x558 = DAT_80325990[low]
  a.tickDelay55c = VOLLEY_TICK_DELAY;             // +0x55c = DAT_803259c8[low] (0.0)
  if ((a.volleySlotBase ?? 0) === 0) {            // +0x6ee == 0 (first entry)
    a.volleysLeft = VOLLEY_COUNTS[low] ?? 3;      // +0x6ef = DAT_80325980[low]
  }
}

/** FUN_8010b02c @ chunk_0030.c:1035 — the volley FIRE (borg-switched spawn). */
function volleyFire(a: GActor, ctx: GirlFamilyCtx): void {
  a.window560 = GIRL.ACTIVE_WINDOW;               // +0x560 = 20
  const low = a.borgNumber & 0xff;
  a.handlerTimer = VOLLEY_INTERVALS[low] ?? 5;    // +0x558 = interval[low]
  a.tickDelay55c = VOLLEY_TICK_DELAY;             // +0x55c = 0
  a.volleySlotBase = 1;                           // +0x6ee = 1
  if ((a.volleysLeft ?? 0) <= 0) return;          // '\0' < +0x6ef gate
  a.meter1900 = 0;                                // +0x1900 = 0
  // zz_0046698_ / FUN_800452a0 / zz_0046dd4_ — the +0x1900 shot-pitch aim solver
  // (reads the +0xa24 part-transform bank). Bridge owns aiming — labeled no-op.
  const ok = ctx.onAllocateResource?.(a, 0, 1, 1) ?? false; // zz_006dbe0_(a,0,1,1)
  if (ok) {
    switch (a.borgNumber) {                       // (s16)+0x3e8 switch
      case 0x300: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BLAST, 0x0b); break;
      case 0x301: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BLAST, 0x1b); break;
      case 0x302: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BLAST, 0x1c); break;
      case 0x303: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BLAST, 0x3a); break;
      case 0x304: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BLAST, 0x23); break;
      case 0x305:
        for (const rec of [0x0e, 0x0f, 0x10, 0x11]) ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.KIND2_CHILD, rec);
        break;
      case 0x306: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.KIND2_CHILD, 0x5a); break;
      case 0x309:
        for (const rec of [0x46, 0x47, 0x48, 0x49]) ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.KIND2_CHILD, rec);
        break;
      case 0x30a:
        for (const rec of [0x4a, 0x4b, 0x4c, 0x4d]) ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.KIND2_CHILD, rec);
        break;
      case 0x30b: ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BLAST, 0x7e); break;
      default: break;                             // 0x307/0x308/0x30c/0x30d: no arm
    }
    a.volleysLeft = (a.volleysLeft ?? 0) - 1;     // +0x6ef--
  }
  // (s16)+0x774 (slot-0 ammo count, raw read) < 1 → +0x6ef = 0.
  if (!(ctx.onAllocateResource?.(a, 0, 1, 0) ?? false)) a.volleysLeft = 0;
}

/** Exact ROM fire-event gate: `(s8)+0x1cef != 0 && +0x1b03 == 0`. */
function volleyFireEvent(a: GActor): boolean {
  if (a.streamHold1b03 !== 0) return false;        // +0x1b03 != 0 holds the fire
  return a.contactP0 !== 0;                       // (s8)+0x1cef != 0
}

// --- G-A (variant 0, table @0x80325a14) ---

// Phase 0 — FUN_8010a5d0 @ chunk_0030.c:634.
function rangedAPhase0(a: GActor): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  // zz_004beb8_(-1.0, actor, 0xf, 2, (s8)+0x6ee, 7, 1) — slot = the +0x6ee latch.
  startStream(a, GIRL.PART_MASK, GIRL.RANGED_GROUP, a.volleySlotBase ?? 0, GIRL.STREAM_RATE);
  // zz_006d0dc_(actor, 0xc1, 0) — face (bridge pre-aims).
  a.controlWord &= 0xffffff4f;                    // +0x5e0 &= ~0xb0
  seedVolleyState(a);                             // zz_010afd0_
  a.gravityCoeff = GIRL.ZERO;                     // +0x50 = 0 (FLOAT_80439558)
  a.yVel = GIRL.ZERO;                             // +0x48 = 0
  a.hDecel = GIRL.ZERO;                           // +0x4c = 0
  a.hSpeed = GIRL.ZERO;                           // +0x44 = 0
  resetPoseHousekeeping(a);
  blinkReposition(a, GIRL.DRAG);                  // motion = pos − +0x5e8; ×0.95; pos +=
  groundSnapRevert(a);
  a.accumulator80c = 0;
}

// Phase 1 — FUN_8010a6b0 @ chunk_0030.c:667. Aim window → first fire.
function rangedAPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  const faced = faceComplete(a);                  // iVar3 = zz_006d0dc_(0xc1, 0)
  let skipFire = false;
  if (!faced) {
    a.window560 = (a.window560 ?? 0) - a.dt;      // +0x560 -= dt
    if ((a.window560 ?? 0) > GIRL.ZERO) skipFire = true; // goto LAB_8010a734
  }
  if (!skipFire && volleyFireEvent(a)) {          // +0x1cef != 0 && +0x1b03 == 0
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    volleyFire(a, ctx);                           // FUN_8010b02c
  }
  driftMotion(a, GIRL.DRAG);                      // motion ×0.95; pos += motion
  groundSnapRevert(a);
  if (vecMagnitude(a.motion) > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
}

// Phase 2 — FUN_8010a78c @ chunk_0030.c:702. Volley loop / recovery / exit.
function rangedAPhase2(a: GActor, ctx: GirlFamilyCtx): void {
  if ((a.tickDelay55c ?? 0) <= GIRL.ZERO) {
    tickStream(a, GIRL.PART_MASK, ctx);           // zz_004cd24_(actor, 0xf)
  } else {
    a.tickDelay55c = (a.tickDelay55c ?? 0) - a.dt; // +0x55c -= dt
  }
  let exit = false;
  if (a.handlerTimer <= GIRL.ZERO) {              // +0x558 ≤ 0 — re-fire point
    const ok = ctx.onAllocateResource?.(a, 0, 1, 0) ?? false; // zz_006dbe0_(a,0,1,0) peek
    if (!ok) {
      exit = true;                                // goto LAB_8010a8f8
    } else {
      const borg = a.borgNumber;
      let loop = false;
      if (borg === 0x305 || borg === 0x309 || borg === 0x30a) {
        loop = a.wallContact !== 0 && ((a.statusWord5b4 ?? 0) & 0x200) !== 0;
      } else if (borg === 0x306) {
        loop = (a.volleysLeft ?? 0) > 0 && a.wallContact !== 0
          && ((a.statusWord5b4 ?? 0) & 0x200) !== 0;
      } else {
        loop = (a.volleysLeft ?? 0) > 0;
      }
      if (loop) {                                 // LAB_8010a878
        if ((a.controlWord & 0x40) !== 0) {       // airborne → re-issue the command
          commandRedispatch(a, ctx, 0, 3, 0);     // zz_006a3d0_(a, 0, 3, 0)
          return;
        }
        // zz_006bf80_(actor) — reticle-alert bookkeeping (valkrie no-op precedent).
        a.fbPhaseSlots[0] -= 1;                   // +0x540-- (back to phase 1)
        startStream(a, GIRL.PART_MASK, GIRL.RANGED_GROUP, 1, GIRL.STREAM_RATE); // slot 1
        return;
      }
    }
  } else {
    a.handlerTimer -= a.dt;                       // +0x558 -= dt
  }
  if (!exit) {
    // Keep drifting while no held input (+0x5d8 & 0xf0), no edge bit (+0x5d4 & 1),
    // and no stream end (+0x1cee).
    if (((a.inputHeld5d8 ?? 0) & 0xf0) === 0 && ((a.inputEdge5d4 ?? 0) & 1) === 0
      && a.wallContact === 0) {
      driftMotion(a, GIRL.DRAG);                  // motion ×0.95; pos += motion
      groundSnapRevert(a);
      if (vecMagnitude(a.motion) > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
      return;
    }
  }
  // LAB_8010a8f8 — exit: +0x73f = 0; +0x5e0 &= ~3; zz_006a474_; zz_006a668_ tail;
  // +0x694 = (float)(int)+0x558 + dt.
  a.controlWord &= ~0x3;
  romGroundIdleReturn(a);                         // zz_006a474_
  shotStateRelease(a);                            // zz_006a668_(a, 0x10)
  a.stateTimer = Math.trunc(a.handlerTimer) + a.dt;
}

// --- G-B (variants 1..3, table @0x80325a20) ---

// Phase 0 — FUN_8010a9f0 @ chunk_0030.c:793. Directional slot select.
function rangedBPhase0(a: GActor): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  const cw = a.controlWord;
  let slot = 4;
  if ((cw & 0x80) !== 0) slot = 6;
  if ((cw & 0x10) !== 0) slot = 2;
  if ((cw & 0x20) !== 0) {
    slot = a.faceGate1d10 + 8;                    // (s8)+0x1d10 + 8
    if (a.ubState === 0x0f) slot = 0;             // +0x5db == 0xf
  }
  // zz_004beb8_(-1.0, actor, 1, 2, slot + (s8)+0x6ee, 7, 1) — part-0 mask ONLY.
  startStream(a, 0x1, GIRL.RANGED_GROUP, slot + (a.volleySlotBase ?? 0), GIRL.STREAM_RATE);
  seedVolleyState(a);                             // zz_010afd0_
}

// Phase 1 — FUN_8010aa98 @ chunk_0030.c:821. Yaw track → fire.
function rangedBPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  const track = aimTrack(a);                      // iVar3 = zz_006dee8_(a, 1)
  tickStream(a, 0x1, ctx);                        // zz_004cd24_(actor, 1)
  if (track < 0) {                                // out of cone → re-issue command
    if ((a.controlWord & 0x40) === 0) {
      commandRedispatch(a, ctx, 0, 0, 2);         // zz_006a3d0_(a, 0, 0, 2) — ground
    } else {
      commandRedispatch(a, ctx, 0, 4, 2);         // zz_006a3d0_(a, 0, 4, 2) — air
    }
    return;
  }
  if (track < 1) {                                // still turning → window burn
    a.window560 = (a.window560 ?? 0) - a.dt;      // +0x560 -= dt
    if ((a.window560 ?? 0) > GIRL.ZERO) return;
  }
  if (volleyFireEvent(a)) {                       // +0x1cef != 0 && +0x1b03 == 0
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    volleyFire(a, ctx);                           // FUN_8010b02c
  }
}

// Phase 2 — FUN_8010ab78 @ chunk_0030.c:857 (SHARED by G-B and G-C).
function rangedBCPhase2(a: GActor, ctx: GirlFamilyCtx): void {
  if ((a.tickDelay55c ?? 0) <= GIRL.ZERO) {
    tickStream(a, 0x1, ctx);                      // zz_004cd24_(actor, 1)
  } else {
    a.tickDelay55c = (a.tickDelay55c ?? 0) - a.dt;
  }
  let exit = false;
  if (a.handlerTimer <= GIRL.ZERO) {
    const ok = ctx.onAllocateResource?.(a, 0, 1, 0) ?? false; // ammo peek
    if (!ok) {
      exit = true;                                // goto LAB_8010ad7c
    } else {
      const borg = a.borgNumber;
      let loop = false;
      if (borg === 0x305 || borg === 0x309 || borg === 0x30a) {
        loop = a.wallContact !== 0 && ((a.statusWord5b4 ?? 0) & 0x200) !== 0;
      } else if (borg === 0x306) {
        loop = (a.volleysLeft ?? 0) > 0 && a.wallContact !== 0
          && ((a.statusWord5b4 ?? 0) & 0x200) !== 0;
      } else {
        loop = (a.volleysLeft ?? 0) > 0;
      }
      if (loop) {                                 // LAB_8010ac64
        // zz_006bf80_(actor) — reticle bookkeeping (no-op).
        a.fbPhaseSlots[0] -= 1;                   // +0x540-- (back to phase 1)
        const cw = a.controlWord;
        if ((cw & 0x40) !== 0 || a.ubCue === 4) { // hover latch OR upper cue 4
          a.variantIndex = 3;                     // +0x581 = 3
          const slot = (cw & 0x80) !== 0 ? 7 : 5;
          startStream(a, 0x1, GIRL.RANGED_GROUP, slot, GIRL.STREAM_RATE);
          return;
        }
        if ((cw & 0x10) !== 0) {
          a.variantIndex = 1;                     // +0x581 = 1
          startStream(a, 0x1, GIRL.RANGED_GROUP, 3, GIRL.STREAM_RATE);
          return;
        }
        if ((cw & 0x20) !== 0) {
          a.variantIndex = 2;                     // +0x581 = 2
          let slot = a.faceGate1d10 + 9;          // (s8)+0x1d10 + 9
          if (a.ubState === 0x0f) slot = 1;       // +0x5db == 0xf
          startStream(a, 0x1, GIRL.RANGED_GROUP, slot, GIRL.STREAM_RATE);
          return;
        }
        commandRedispatch(a, ctx, 0, 0, 2);       // zz_006a3d0_(a, 0, 0, 2)
        return;
      }
    }
  } else {
    a.handlerTimer -= a.dt;                       // +0x558 -= dt
  }
  if (!exit) {
    // Keep holding while no held input (+0x5d8 & 0xf0) and no stream end (+0x1cee).
    if (((a.inputHeld5d8 ?? 0) & 0xf0) === 0 && a.wallContact === 0
    ) {
      return;
    }
  }
  // LAB_8010ad7c — exit: +0x73f = 0; +0x5e0 &= ~3; zz_006a668_ tail (NO zz_006a474_
  // here — the G-A exit is the only arm that runs the ground idle return first).
  a.controlWord &= ~0x3;
  shotStateRelease(a);                            // zz_006a668_(a, 0x10)
  a.stateTimer = Math.trunc(a.handlerTimer) + a.dt; // +0x694 = (float)(int)+0x558 + dt
}

// --- G-C (variant 4, table @0x80325a2c) ---

// Phase 0 — FUN_8010ae30 @ chunk_0030.c:960. Air volley setup.
function rangedCPhase0(a: GActor): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  // zz_006d0dc_(actor, 0x81, 0) — face (bridge).
  a.controlWord &= ~0x80;                         // +0x5e0 &= 0xffffff7f
  integratePhysics(GIRL.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  // zz_00677b0_(actor) — bridge clamp.
  // zz_004beb8_(-1.0, actor, 1, 2, (s8)+0x6ee + 4, 7, 1).
  startStream(a, 0x1, GIRL.RANGED_GROUP, (a.volleySlotBase ?? 0) + 4, GIRL.STREAM_RATE);
  // Part-1 idle-anim upkeep: if part 1 isn't already playing group 0 slot 0xd
  // (+0x1d0c/+0x1d0d check) → zz_004beb8_(-1.0, actor, 2, 0, 0xd, 7, 1).
  const p1 = a.parts[1] as RomPartState & { group?: number; slot?: number };
  if (p1.group !== 0 || p1.slot !== 0xd) {
    startStream(a, 0x2, 0, 0xd, GIRL.STREAM_RATE);
  }
  seedVolleyState(a);                             // zz_010afd0_
  a.accumulator80c = 0;
}

// Phase 1 — FUN_8010af04 @ chunk_0030.c:984. Air aim → fire + knock-out arm.
function rangedCPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  integratePhysics(GIRL.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  // zz_00677b0_(actor) — bridge clamp.
  const faced = faceComplete(a);                  // iVar3 = zz_006d0dc_(0x81, 0)
  let skipFire = false;
  if (!faced) {
    a.window560 = (a.window560 ?? 0) - a.dt;      // +0x560 -= dt
    if ((a.window560 ?? 0) > GIRL.ZERO) skipFire = true; // goto LAB_8010afb4
  }
  if (!skipFire && volleyFireEvent(a)) {          // +0x1cef != 0 && +0x1b03 == 0
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    volleyFire(a, ctx);                           // FUN_8010b02c
    a.controlWord &= ~0x2;                        // +0x5e0 &= 0xfffffffd (bit 1 ONLY)
    romAirKnockoutReturn(a);                      // zz_006a5a4_ — NO +0x73f/~3 arm here
  }
  stepAfterimage(a);
}

/** Build the shared action-0 handler (FUN_8010a508 → variant table @0x80325a00). */
export function createGirlRangedVolley(ctx: GirlFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    // Handler FUN_8010a508: +0x18da >>= 1; +0x1900 = trunc(+0x1900 × 0.96).
    a.steerYaw = s16(a.steerYaw) >> 1;
    a.meter1900 = Math.trunc((a.meter1900 ?? 0) * GIRL.METER_DECAY) | 0;
    const v = a.variantIndex;
    const phase = a.fbPhaseSlots[0] ?? 0;
    if (v === 0) {
      // G-A dispatcher FUN_8010a588: +0x1dfc >>= 1.
      a.aimYawTrack = s16(a.aimYawTrack ?? 0) >> 1;
      switch (phase) {                            // PTR_FUN_80325a14[+0x540]
        case 0: rangedAPhase0(a); break;
        case 1: rangedAPhase1(a, ctx); break;
        case 2: rangedAPhase2(a, ctx); break;
        default: break;
      }
    } else if (v === 4) {
      // G-C dispatcher FUN_8010ade8: +0x1dfc >>= 1.
      a.aimYawTrack = s16(a.aimYawTrack ?? 0) >> 1;
      switch (phase) {                            // PTR_FUN_80325a2c[+0x540]
        case 0: rangedCPhase0(a); break;
        case 1: rangedCPhase1(a, ctx); break;
        case 2: rangedBCPhase2(a, ctx); break;    // FUN_8010ab78 (shared with G-B)
        default: break;
      }
    } else {
      // G-B dispatcher FUN_8010a9b4 (variants 1..3; no prelude).
      switch (phase) {                            // PTR_FUN_80325a20[+0x540]
        case 0: rangedBPhase0(a); break;
        case 1: rangedBPhase1(a, ctx); break;
        case 2: rangedBCPhase2(a, ctx); break;
        default: break;
      }
    }
  };
}

// ============================================================================
// M-1 — action 1 v0, B combo swings (dispatcher zz_010b2f4_ @0x8010b2f4, table
// @0x80325a68, chunk_0030.c:1134-1313). Seed slot 0 for every family.
// ============================================================================

// Phase 0 — FUN_8010b344 @ chunk_0030.c:1148. Setup (NO stream start).
function swingsPhase0(a: GActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  a.handlerTimer = GIRL.FACE_BUDGET;              // +0x558 = 60 (FLOAT_8043956c)
  a.bRetap = false;                               // +0x746 = 0
  a.streamSlot = seedSlot;                        // +0x6ea = r4 seed (0)
  a.hSpeed = GIRL.ZERO;                           // +0x44 = 0
  a.hDecel = GIRL.ZERO;                           // +0x4c = 0
  setupLockGate(a, rangeRow868(a), "heading");    // FUN_80066838(row868) < 1 → invalidate
  faceComplete(a);
  a.accumulator80c = 0;
}

// Phase 1 — FUN_8010b400 @ chunk_0030.c:1179. Face budget → first swing.
function swingsPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  if (a.handlerTimer <= GIRL.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    const slot = a.streamSlot;                    // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                      // +0x6ea++
    startStream(a, GIRL.PART_MASK, GIRL.MELEE_GROUP, slot, GIRL.STREAM_RATE);
    a.hDecel = GIRL.ZERO;                         // +0x4c = 0
    if (!a.lockTarget) {                          // +0xcc == 0
      a.handlerTimer = GIRL.ZERO;                 // +0x558 = 0
      a.hSpeed = GIRL.ZERO;                       // +0x44 = 0
    } else {
      a.handlerTimer = GIRL.ACTIVE_WINDOW;        // +0x558 = 20 (FLOAT_80439568)
      // +0x44 = +0x764 × (f32)(s8)+0x1d0f × 0.0625 (FLOAT_80439570) — the byte is
      // stream-authored; unstamped → 16 (TUNED fallback, samurai dashByte precedent).
      a.hSpeed = targetDistance(a) * dashByte(a) * GIRL.DASH_BYTE_SCALE;
    }
    a.hSpeed /= GIRL.ACTIVE_WINDOW;               // +0x44 /= 20
    if (GIRL.FX_RANGE < targetDistance(a)) {      // 200 < +0x764
      ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
  }
}

// Phase 2 — FUN_8010b51c @ chunk_0030.c:1224. Swing dash-in.
function swingsPhase2(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  // zz_006d144_(0xc0) — face (bridge).
  if (((a.hitReact1dd ?? 0) & 0x80) === 0) {      // +0x1dd & 0x80 → motion freeze
    applyDrag(a, GIRL.DRAG);                      // zz_006ed8c_(0.95, FLOAT_8043955c)
    integratePhysics(0, a, s16(a.lockYaw));       // zz_00670dc_(actor, +0x5ae)
  }
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  // Gate: timer ≤ 0 OR FUN_80066838(200 = FLOAT_80439574) > 0 (in range ONLY).
  if (a.handlerTimer <= GIRL.ZERO || rangeCheck(a, GIRL.FX_RANGE) > 0) {
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    a.hSpeed *= GIRL.SWING_BRAKE;                 // +0x44 ×= 0.5 (FLOAT_80439578)
    const slot = a.streamSlot;                    // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                      // +0x6ea++
    startStream(a, GIRL.PART_MASK, GIRL.MELEE_GROUP, slot, GIRL.STREAM_RATE);
  }
  if (a.hSpeed > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
}

// Phase 3 — FUN_8010b610 @ chunk_0030.c:1261. Combo loop (stays in phase 3).
function swingsPhase3(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  if (a.bRetapInput) a.bRetap = true;             // +0x5d4 & 0x40 → +0x746 = 1
  // COMBO: (s8)+0x1cf0 < 0 (swing re-arm) AND +0x746 — restarts the next g3 slot
  // and STAYS in phase 3 (no phase change, samurai S-B shape).
  if (a.contactP1 < 0 && a.bRetap) {
    a.bRetap = false;                             // +0x746 = 0
    if (GIRL.FX_RANGE < targetDistance(a)) {      // 200 < +0x764
      ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
    const slot = a.streamSlot;                    // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                      // +0x6ea++
    startStream(a, GIRL.PART_MASK, GIRL.MELEE_GROUP, slot, GIRL.STREAM_RATE);
    return;
  }
  if (a.faceGate1d10 !== 0) {                     // +0x1d10 != 0 → re-face
    // zz_006d144_(actor, 0xc0).
  }
  // Dash refresh: +0x1b03 == 0 && (s8)+0x1d0f != 0 → recompute +0x44, clear the byte.
  if (a.streamHold1b03 === 0 && dashByte(a) !== 0) {
    if (!a.lockTarget) {                          // +0xcc == 0
      a.hSpeed = GIRL.ZERO;                       // +0x44 = 0
    } else {
      a.hSpeed = targetDistance(a) * dashByte(a) * GIRL.DASH_BYTE_SCALE;
    }
    a.hSpeed /= GIRL.ACTIVE_WINDOW;               // +0x44 /= 20
    a.dashStrength1d0f = 0;                       // +0x1d0f = 0
  }
  applyDrag(a, GIRL.DRAG);                        // zz_006ed8c_(0.95)
  integratePhysics(0, a, s16(a.lockYaw));         // zz_00670dc_(actor, +0x5ae)
  if (a.wallContact !== 0) {                      // +0x1cee != 0
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    romGroundIdleReturn(a);                       // zz_006a474_
  }
  if (a.hSpeed > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
}

/** Build the M-1 combo-swings handler (dispatcher zz_010b2f4_; seed 0 fleet-wide). */
export function createGirlComboSwings(ctx: GirlFamilyCtx, seedSlot = 0): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null; // +0x541 → +0xcc = 0
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_80325a68[+0x540]
      case 0: swingsPhase0(a, seedSlot); break;
      case 1: swingsPhase1(a, ctx); break;
      case 2: swingsPhase2(a, ctx); break;
      case 3: swingsPhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// M-3 — action 1 v2, B rush combo (dispatcher zz_010bd10_ @0x8010bd10, table
// @0x80325a88, chunk_0030.c:1513-1691). Seed 5 girls / 6 killer.
// ============================================================================

// Phase 0 — FUN_8010bd60 @ chunk_0030.c:1527. Blink + first rush stream.
function rushPhase0(a: GActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  a.handlerTimer = GIRL.FACE_BUDGET;              // +0x558 = 60
  a.bRetap = false;                               // +0x746 = 0
  a.streamSlot = seedSlot;                        // +0x6ea = r4 seed
  setupLockGate(a, rangeRow868(a), "lockYaw");    // invalidate arm: +0x5ac = +0x5AE
  // zz_006d144_(0xc0) — face (bridge).
  blinkReposition(a, GIRL.BLINK_SOFT);            // ×0.98 (FLOAT_80439598)
  // zz_00677b0_(actor) — bridge clamp.
  const slot = a.streamSlot;                      // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                        // +0x6ea++
  startStream(a, GIRL.PART_MASK, GIRL.MELEE_GROUP, slot, GIRL.STREAM_RATE);
  a.accumulator80c = 0;
}

// Phase 1 — FUN_8010be74 @ chunk_0030.c:1565. Face budget → rush arm.
function rushPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  driftMotion(a, GIRL.BLINK_SOFT);                // motion ×0.98; pos += motion
  // zz_00677b0_(actor) — bridge clamp.
  if (a.contactP0 < 1) {                          // (s8)+0x1cef < 1 → tick
    tickStream(a, GIRL.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  if (a.handlerTimer <= GIRL.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    a.handlerTimer = GIRL.RUSH_WINDOW;            // +0x558 = 30 (FLOAT_8043957c)
    let f = rangeRow868(a);                       // row868 default
    if (a.lockTarget && f < targetDistance(a)) f = targetDistance(a);
    a.hSpeed = f / GIRL.RUSH_WINDOW;              // +0x44 = f / 30
    a.hDecel = GIRL.ZERO;                         // +0x4c = 0
    if (GIRL.FX_RANGE < targetDistance(a)) {      // 200 < +0x764
      ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
  }
  if (vecMagnitude(a.motion) > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
}

// Phase 2 — FUN_8010bfbc @ chunk_0030.c:1610. Rush-in.
function rushPhase2(a: GActor, ctx: GirlFamilyCtx): void {
  // zz_006d144_(0xc0) — face (bridge).
  integratePhysics(0, a, s16(a.lockYaw));         // zz_00670dc_(actor, +0x5ae) — NO drag
  if (a.contactP0 < 1) {                          // (s8)+0x1cef < 1 → tick
    tickStream(a, GIRL.PART_MASK, ctx);
  }
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  // Advance when: timer ≤ 0 OR FUN_80066838(200) ≥ 1 OR hit-react +0x1d9 != 0.
  if (a.handlerTimer > GIRL.ZERO && rangeCheck(a, GIRL.FX_RANGE) < 1
    && (a.hitReact ?? 0) === 0) {
    if (a.hSpeed > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
    return;                                       // LAB_8010c048
  }
  a.fbPhaseSlots[0] += 1;                         // +0x540++
}

// Phase 3 — FUN_8010c074 @ chunk_0030.c:1641. Combo loop (stays in phase 3).
function rushPhase3(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  if (a.bRetapInput) a.bRetap = true;             // +0x5d4 & 0x40 → +0x746 = 1
  if (a.contactP1 < 0 && a.bRetap) {              // combo re-arm
    a.bRetap = false;                             // +0x746 = 0
    if (GIRL.FX_RANGE < targetDistance(a)) {      // 200 < +0x764
      ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    }
    if (!a.lockTarget) {                          // +0xcc == 0
      a.hSpeed = rangeRow868(a);                  // +0x44 = row868 (raw copy)
    } else {
      // +0x44 = +0x764 × (f32)(s8)+0x1d0f × 0.0625 (unstamped → 16, TUNED fallback).
      a.hSpeed = targetDistance(a) * dashByte(a) * GIRL.DASH_BYTE_SCALE;
    }
    a.hSpeed /= GIRL.ACTIVE_WINDOW;               // +0x44 /= 20 (FLOAT_80439568)
    const slot = a.streamSlot;                    // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                      // +0x6ea++
    startStream(a, GIRL.PART_MASK, GIRL.MELEE_GROUP, slot, GIRL.STREAM_RATE);
    return;
  }
  if (a.faceGate1d10 !== 0) {                     // +0x1d10 != 0 → re-face
    // zz_006d144_(actor, 0xc0).
  }
  applyDrag(a, GIRL.DRAG);                        // zz_006ed8c_(0.95)
  integratePhysics(0, a, s16(a.lockYaw));         // zz_00670dc_(actor, +0x5ae)
  if (a.wallContact !== 0) {                      // +0x1cee != 0
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    romGroundIdleReturn(a);                       // zz_006a474_
  }
  if (a.hSpeed > GIRL.AFTERIMAGE_MIN) stepAfterimage(a);
}

/** Build the M-3 rush-combo handler (dispatcher zz_010bd10_). */
export function createGirlRushCombo(ctx: GirlFamilyCtx, seedSlot: number): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_80325a88[+0x540]
      case 0: rushPhase0(a, seedSlot); break;
      case 1: rushPhase1(a, ctx); break;
      case 2: rushPhase2(a, ctx); break;
      case 3: rushPhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// M-5 — action 1 v4, B pitch-dive (dispatcher zz_010c590_ @0x8010c590, table
// @0x80325aa8, chunk_0030.c:1828-1982). Seed 7 girls / 8 killer.
// ============================================================================

// Phase 0 — FUN_8010c5e0 @ chunk_0030.c:1842.
function divePhase0(a: GActor, seedSlot: number): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  // FUN_80066838(row86c — COLUMN 1) < 1 → invalidate: +0x5ac = +0x5AE.
  setupLockGate(a, rangeRow86c(a), "lockYaw");
  a.handlerTimer = GIRL.FACE_BUDGET;              // +0x558 = 60
  a.meleeAimPitch = 0;                            // +0x54e = 0
  a.streamSlot = seedSlot;                        // +0x6ea = r4 seed
  a.gravityCoeff = GIRL.ZERO;                     // +0x50 = 0
  a.yVel = GIRL.ZERO;                             // +0x48 = 0
  a.hDecel = GIRL.ZERO;                           // +0x4c = 0
  a.hSpeed = GIRL.ZERO;                           // +0x44 = 0
  resetPoseHousekeeping(a);
  faceComplete(a);
  seekAimPitch(a);
  blinkReposition(a, GIRL.BLINK_SOFT);            // ×0.98 (FLOAT_80439598)
  // zz_00677b0_(actor) — bridge clamp.
  // zz_004beb8_(-1.0, actor, 0xf, 3, (s8)+0x6ea) — NO +0x6ea increment in M-5 P0.
  startStream(a, GIRL.PART_MASK, GIRL.MELEE_GROUP, a.streamSlot, GIRL.STREAM_RATE);
}

// Phase 1 — FUN_8010c720 @ chunk_0030.c:1883. Face budget → dive start.
function divePhase1(a: GActor, ctx: GirlFamilyCtx): void {
  if (a.streamHold1b03 !== 0) {                   // +0x1b03 != 0
    tickStream(a, GIRL.PART_MASK, ctx);
  }
  driftMotion(a, GIRL.BLINK_SOFT);                // motion ×0.98; pos += motion
  // zz_00677b0_(actor) — bridge clamp.
  seekAimPitch(a);                                // zz_006e514_(0xc0, &+0x54e)
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  if (a.handlerTimer <= GIRL.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    a.handlerTimer = GIRL.RUSH_WINDOW;            // +0x558 = 30 (FLOAT_8043957c)
    ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.DIVE_FX, 0); // zz_0092dcc_(a, 0)
  }
}

// Phase 2 — FUN_8010c7e8 @ chunk_0030.c:1913. Pitch-projected dive.
function divePhase2(a: GActor, ctx: GirlFamilyCtx): void {
  if (a.contactP0 === 0 || a.streamHold1b03 !== 0) { // +0x1cef == 0 || +0x1b03 != 0
    tickStream(a, GIRL.PART_MASK, ctx);
  }
  // zz_006d144_(0xc0) face + zz_006e514_ pitch seek.
  seekAimPitch(a);
  const pitch = a.meleeAimPitch ?? 0;
  a.hSpeed = GIRL.RUSH_WINDOW * projectZ(pitch);  // +0x44 = 30 × cos(+0x54e)
  a.yVel = GIRL.RUSH_WINDOW * -projectX(pitch);   // +0x48 = 30 × -sin(+0x54e)
  integratePhysics(GIRL.GRAVITY, a, s16(a.activeYaw)); // FUN_80067310(1.0, +0x5ac)
  // zz_00677b0_(actor) — bridge clamp.
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  // Stay while: timer > 0 AND FUN_800668cc(150) < 1 AND hit-react +0x1d9 == 0.
  if (a.handlerTimer > GIRL.ZERO && rangeCheck(a, GIRL.PROXIMITY) < 1
    && (a.hitReact ?? 0) === 0) {
    return;
  }
  a.fbPhaseSlots[0] += 1;                         // +0x540++
}

// Phase 3 — FUN_8010c8e0 @ chunk_0030.c:1949. Recovery / landing.
function divePhase3(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  if (a.dashStrength1d0f < 0) {                   // (s8)+0x1d0f < 0 → altitude cap
    a.dashStrength1d0f = 0;                       // +0x1d0f = 0
    if (a.yVel > GIRL.ZERO) a.yVel = GIRL.ZERO;   // +0x48 clamp ≤ 0
    a.gravityCoeff = gravityRestore(a);           // +0x50 = dataPage(+0x4ac)+0x6c
  }
  applyDrag(a, GIRL.RECOVERY_DRAG);               // zz_006ed8c_(0.9, FLOAT_80439540)
  integratePhysics(GIRL.GRAVITY, a, s16(a.activeYaw)); // FUN_80067310(1.0, +0x5ac)
  const grounded = a.grounded === true;           // iVar2 = zz_00677b0_(actor)
  if (grounded && a.contactP0 < 0) {              // landed + (s8)+0x1cef < 0
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    dispatchUpperBodyCue(a, 7);                   // zz_006a750_(actor, 7)
    a.stateTimer = GIRL.GRAVITY + a.dt;           // +0x694 = 1.0 (FLOAT_80439564) + dt
    return;
  }
  if (a.wallContact !== 0) {                      // +0x1cee != 0
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    romAirKnockoutReturn(a);                      // zz_006a5a4_
  }
}

/** Build the M-5 pitch-dive handler (dispatcher zz_010c590_). */
export function createGirlPitchDive(ctx: GirlFamilyCtx, seedSlot: number): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null;
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_80325aa8[+0x540]
      case 0: divePhase0(a, seedSlot); break;
      case 1: divePhase1(a, ctx); break;
      case 2: divePhase2(a, ctx); break;
      case 3: divePhase3(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// SHARED X — 2-phase config-driven backdash volley (dispatcher zz_010c9d8_
// @0x8010c9d8, table @0x80434508, chunk_0030.c:1986-2131). Used by KILLER GIRL
// pl0304 (cfg @0x80336d94) and BARRIER GIRL pl0306 (cfg @0x8032411c).
// ============================================================================

export interface GirlSharedXConfig {
  /** Config block address (documentation). */
  romConfig: number;
  /** cfg+0x0 s32 — g4 seed slot (+1 airborne). */
  seedSlot: number;
  /** cfg+0x4 f32 — per-frame motion drift scale. */
  driftScale: number;
  /** cfg+0x8 f32 — grounded backdash +0x44 seed. */
  groundSpeed: number;
  /** cfg+0xc fnptr — once-per-move payload; returns nonzero on success (0x8444). */
  payload?: (actor: RomActor, ctx: GirlFamilyCtx) => boolean;
}

/** FUN_80134714 @ chunk_0035.c:2568 — zz_006dbe0_(a,2,1,1) ammo deduct →
 *  zz_016cc24_(a, 1) armed-shot deploy (part mask 1). */
function killerSharedXPayload(actor: RomActor, ctx: GirlFamilyCtx): boolean {
  const ok = ctx.onAllocateResource?.(actor, 2, 1, 1) ?? false;
  if (!ok) return false;
  ctx.onFamilyProjectile?.(actor, GIRL_SPAWNERS.ARMED_SHOT, 1);
  return true;
}

/** FUN_80108530 @ chunk_0029.c:2919 — same shape, zz_016cc24_(a, 0xf) (all parts). */
function barrierSharedXPayload(actor: RomActor, ctx: GirlFamilyCtx): boolean {
  const ok = ctx.onAllocateResource?.(actor, 2, 1, 1) ?? false;
  if (!ok) return false;
  ctx.onFamilyProjectile?.(actor, GIRL_SPAWNERS.ARMED_SHOT, 0xf);
  return true;
}

/** KILLER GIRL pl0304 config — DOL-read @0x80336d94 (thunk zz_01346ec_ r4). */
export const KILLER_SHARED_X_CONFIG: GirlSharedXConfig = {
  romConfig: 0x80336d94, seedSlot: 0, driftScale: 0.949999988079071,
  groundSpeed: 6.093239784240723, payload: killerSharedXPayload,
};

/** BARRIER GIRL pl0306 config — DOL-read @0x8032411c (thunk FUN_80108508 r4). */
export const BARRIER_SHARED_X_CONFIG: GirlSharedXConfig = {
  romConfig: 0x8032411c, seedSlot: 2, driftScale: 0.949999988079071,
  groundSpeed: 6.093239784240723, payload: barrierSharedXPayload,
};

// Phase 0 — FUN_8010ca10 @ chunk_0030.c:1997.
function sharedXPhase0(a: GActor, cfg: GirlSharedXConfig): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  if (!a.lockTarget) a.activeYaw = a.heading;     // +0xcc == 0 → +0x5ac = +0x72
  a.streamSlot = cfg.seedSlot;                    // +0x6ea = cfg[0]
  if ((a.controlWord & 0x40) !== 0) {             // airborne → +0x6ea++
    a.streamSlot += 1;
  }
  // zz_006d144_(0xc0) — face (bridge).
  blinkReposition(a, cfg.driftScale);             // motion = pos−target; ×cfg[1]; pos +=
  a.gravityCoeff = GIRL.ZERO;                     // +0x50 = 0
  a.yVel = GIRL.ZERO;                             // +0x48 = 0
  a.hDecel = GIRL.ZERO;                           // +0x4c = 0
  a.hSpeed = GIRL.ZERO;                           // +0x44 = 0
  resetPoseHousekeeping(a);
  if ((a.controlWord & 0x40) === 0) {             // grounded → backdash seed
    a.hSpeed = cfg.groundSpeed;                   // +0x44 = cfg[2]
  }
  // FUN_80067310(1.0, actor, +0x72 − 0x8000) — BACKWARD projection off the heading.
  integratePhysics(GIRL.GRAVITY, a, s16(a.heading - 0x8000));
  // zz_00677b0_(actor) — bridge clamp.
  // zz_004beb8_(-1.0, actor, 0xf, 4, (s8)+0x6ea, 8, 1).
  a.accumulator80c = 0;
  startStream(a, GIRL.PART_MASK, GIRL.X_GROUP, a.streamSlot, GIRL.STREAM_RATE);
  a.fbPhaseSlots[2] = 0;                          // +0x542 payload latch (fresh move)
}

// Phase 1 — FUN_8010cb48 @ chunk_0030.c:2038.
function sharedXPhase1(a: GActor, cfg: GirlSharedXConfig, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  // Once-per-move payload: +0x1b03 == 0 && +0x542 == 0 → +0x542 = 0xff, then
  // cfg+0xc(actor) != 0 → +0x542 = 1.
  if (a.streamHold1b03 === 0 && (a.fbPhaseSlots[2] ?? 0) === 0) {
    a.fbPhaseSlots[2] = -1;                       // +0x542 = 0xff
    if (cfg.payload && cfg.payload(a, ctx)) {
      a.fbPhaseSlots[2] = 1;                      // +0x542 = 1
    }
  }
  // Payload-failed cancel: (s8)+0x1cef ≥ 1 AND +0x542 < 0 → cooldown 30 + exit.
  if (a.contactP0 >= 1 && (a.fbPhaseSlots[2] ?? 0) < 0) {
    a.stateTimer = GIRL.RUSH_WINDOW + a.dt;       // +0x694 = 30 (FLOAT_8043957c) + dt
  } else {
    if (a.contactP1 < 0) {                        // (s8)+0x1cf0 < 0 → gravity restore
      a.contactP1 = 0;                            // +0x1cf0 = 0
      a.gravityCoeff = gravityRestore(a);         // +0x50 = dataPage+0x6c
    }
    if (a.faceGate1d10 === 0) {                   // +0x1d10 == 0 → meter decay
      a.steerYaw = s16(a.steerYaw) >> 1;          // +0x18da >>= 1
      a.meter1900 = s16(a.meter1900 ?? 0) >> 1;   // +0x1900 >>= 1
    } else {
      // zz_006d144_(0xc0) face; grounded → +0x1900 = clamp(pitch-to-target, ±0x2000)
      // (FUN_800452a0 aim solve — bridge-owned; labeled approximation: clamp only);
      // airborne → zz_006e1ac_(0xc1, 1) (bridge aim channel).
      if ((a.controlWord & 0x40) === 0) {
        const m = Math.max(-0x2000, Math.min(0x2000, s16(a.meter1900 ?? 0)));
        a.meter1900 = m;
      }
    }
    if (a.streamHold1b03 === 0) {                 // +0x1b03 == 0 → kill the dash
      a.hSpeed = GIRL.ZERO;                       // +0x44 = 0
    }
    integratePhysics(GIRL.GRAVITY, a, s16(a.heading - 0x8000)); // backward drift
    driftMotion(a, cfg.driftScale);               // motion ×cfg[1]; pos += motion
    const grounded = a.grounded === true;         // iVar1 = zz_00677b0_(actor)
    if (grounded && a.contactP0 < 0 && (a.controlWord & 0x40) !== 0) {
      a.controlWord &= ~0x3;                      // +0x73f = 0; +0x5e0 &= ~3
      dispatchUpperBodyCue(a, 7);                 // zz_006a750_(actor, 7)
      a.stateTimer = GIRL.GRAVITY + a.dt;         // +0x694 = 1.0 (FLOAT_80439564) + dt
      return;
    }
    if (a.wallContact === 0) {                    // +0x1cee == 0 → keep recovering
      stepAfterimage(a);
      return;
    }
  }
  // Exit: +0x73f = 0; +0x5e0 &= ~3; ground → zz_006a474_, air → zz_006a5a4_.
  a.controlWord &= ~0x3;
  if ((a.controlWord & 0x40) === 0) romGroundIdleReturn(a);
  else romAirKnockoutReturn(a);
}

/** Build the shared 2-phase X handler (dispatcher zz_010c9d8_; entry [2] of the ROM
 *  table — 0x800a4000 — is dead: nothing writes +0x540 = 2). */
export function createGirlSharedX(cfg: GirlSharedXConfig, ctx: GirlFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_80434508[+0x540]
      case 0: sharedXPhase0(a, cfg); break;
      case 1: sharedXPhase1(a, cfg, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// BATTLE GIRL X — 2 actor phases (leaf FUN_800c09e0 → table @0x80433b18;
// FUN_800c0a2c chunk_0019.c:4417, FUN_800c0b44 chunk_0020.c:1). The payload is
// the zz_00fe668_ child (its own +0x19-indexed machines @0x80433b20/28/30).
// ============================================================================

// Phase 0 — FUN_800c0a2c.
function battleXPhase0(a: GActor): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  if (!a.lockTarget) a.activeYaw = a.heading;     // +0xcc == 0 → +0x5ac = +0x72
  a.streamSlot = (a.controlWord & 0x40) !== 0 ? 1 : 0; // +0x6ea = 0 / 1 air
  // zz_006d144_(0xc0) face; borg 0x30b airborne also zz_006e1ac_(0xc1, 1) (bridge).
  a.gravityCoeff = BATTLE_X.ZERO;                 // +0x50 = 0 (FLOAT_80438618)
  a.yVel = BATTLE_X.ZERO;                         // +0x48 = 0
  a.hDecel = BATTLE_X.ZERO;                       // +0x4c = 0
  a.hSpeed = BATTLE_X.ZERO;                       // +0x44 = 0
  resetPoseHousekeeping(a);
  blinkReposition(a, BATTLE_X.BLINK);             // ×0.95 (FLOAT_8043861c)
  // zz_00679d0_(actor) — ground snap (bridge).
  // zz_004beb8_(-1.0 FLOAT_80438620, actor, 0xf, 4, (s8)+0x6ea, 8, 1).
  startStream(a, GIRL.PART_MASK, GIRL.X_GROUP, a.streamSlot, BATTLE_X.RATE);
}

// Phase 1 — FUN_800c0b44.
function battleXPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  if (a.faceGate1d10 !== 0) {                     // +0x1d10 != 0 → re-face;
    // borg 0x30b airborne also zz_006e1ac_(0xc1, 1).
  }
  if (a.contactP0 > 0) {                          // (s8)+0x1cef > 0 — fire event
    a.contactP0 = 0;                              // +0x1cef = 0
    const ok = ctx.onAllocateResource?.(a, 2, 1, 1) ?? false; // zz_006dbe0_(a,2,1,1)
    if (!ok) {                                    // no ammo → LAB_800c0cc4 exit
      battleXExit(a);
      return;
    }
    if (a.borgNumber === 0x300) {
      ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BATTLE_X_CHILD, 0); // zz_00fe668_(a,0,0)
    } else if (a.borgNumber === 0x30b) {
      ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BATTLE_X_CHILD, 1); // zz_00fe668_(a,1,1)
    }
  }
  if (a.dashStrength1d0f < 0) {                   // (s8)+0x1d0f < 0 → altitude cap
    a.dashStrength1d0f = 0;                       // +0x1d0f = 0
    if (a.yVel > BATTLE_X.ZERO) a.yVel = BATTLE_X.ZERO; // +0x48 clamp ≤ 0
    a.gravityCoeff = gravityRestore(a);           // +0x50 = dataPage+0x6c
  }
  driftMotion(a, BATTLE_X.BLINK);                 // motion ×0.95; pos += motion
  const landed = a.grounded === true;             // iVar2 = zz_00679d0_(actor)
  if (landed && a.contactP0 < 0 && (a.controlWord & 0x40) !== 0) {
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    dispatchUpperBodyCue(a, 7);                   // zz_006a750_(actor, 7)
    a.stateTimer = BATTLE_X.COOLDOWN + a.dt;      // +0x694 = 1.0 (FLOAT_80438624) + dt
    return;
  }
  if (a.wallContact === 0) return;                // +0x1cee == 0 → keep holding
  battleXExit(a);                                 // LAB_800c0cc4
}

function battleXExit(a: GActor): void {
  a.controlWord &= ~0x3;                          // +0x73f = 0; +0x5e0 &= ~3
  if ((a.controlWord & 0x40) === 0) romGroundIdleReturn(a); // zz_006a474_
  else romAirKnockoutReturn(a);                   // zz_006a5a4_
}

/** Build the BATTLE GIRL X handler (leaf FUN_800c09e0 — variant-independent:
 *  table @0x803029a8 is 5× the same leaf). */
export function createBattleGirlX(ctx: GirlFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null; // +0x541 → +0xcc = 0
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_80433b18[+0x540]
      case 0: battleXPhase0(a); break;
      case 1: battleXPhase1(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// BARRIER GIRL X (pl0302) — 2 actor phases (engine FUN_80108250 → table
// @0x804344d8; FUN_80108294 chunk_0029.c:2820 tail-calls FUN_80108344 :2850).
// ============================================================================

// Phase 0 — FUN_80108294.
function barrierXPhase0(a: GActor, ctx: GirlFamilyCtx): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  a.gravityCoeff = BARRIER_X.ZERO;                // +0x50 = 0 (FLOAT_804394e8)
  a.yVel = BARRIER_X.ZERO;                        // +0x48 = 0
  a.hDecel = BARRIER_X.ZERO;                      // +0x4c = 0
  a.hSpeed = BARRIER_X.ZERO;                      // +0x44 = 0
  resetPoseHousekeeping(a);
  // motion = pos − target(+0x5e8) — SUBTRACT ONLY (no scale/apply in phase 0; the
  // vector feeds phase 1's ×0.95 drift). No lock → zero motion (blink rule).
  if (a.lockTarget) {
    vecSubtract(a.pos, a.lockTarget, a.motion);
  } else {
    a.motion.x = 0; a.motion.y = 0; a.motion.z = 0;
  }
  a.streamSlot = (a.controlWord & 0x40) !== 0 ? 1 : 0; // +0x6ea = 0 / 1 air
  // zz_004beb8_(-1.0 FLOAT_804394ec, actor, 0xf, 4, (s8)+0x6ea, -1, -1).
  startStream(a, GIRL.PART_MASK, GIRL.X_GROUP, a.streamSlot, BARRIER_X.RATE);
  barrierXPhase1(a, ctx);                         // FUN_80108344 — same-frame tail call
}

// Phase 1 — FUN_80108344.
function barrierXPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  integratePhysics(BARRIER_X.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  driftMotion(a, BARRIER_X.DRIFT);                // motion ×0.95 (FLOAT_804394f4)
  const grounded = a.grounded === true;           // iVar2 = zz_00677b0_(actor)
  if (grounded && (a.controlWord & 0x40) !== 0 && a.contactP0 < 0) {
    // Air-landing arm: +0x73f = 0; +0x5e0 &= ~3; cue 7; +0x694 = 8 (FLOAT_804394f8).
    a.controlWord &= ~0x3;
    dispatchUpperBodyCue(a, 7);                   // zz_006a750_(actor, 7)
    a.stateTimer = BARRIER_X.COOLDOWN + a.dt;
    return;
  }
  if (a.contactP0 > 0) {                          // (s8)+0x1cef > 0 — barrier event
    a.contactP0 = 0;                              // +0x1cef = 0
    const mode = a.barrierMode146 ?? 0;           // (s8)+0x146 child-link byte
    if (mode === 1) {
      // Barrier alive → re-arm it: ammo deduct then +0x146 = 2.
      const ok = ctx.onAllocateResource?.(a, 2, 1, 1) ?? false;
      if (ok) {
        a.barrierMode146 = 2;                     // +0x146 = 2
        // FUN_800061a8(actor, 0x11) — screen/rumble FX helper @0x800061a8 (unported,
        // labeled no-op).
      }
    } else if (mode === 0) {
      const ok = ctx.onAllocateResource?.(a, 2, 1, 1) ?? false;
      if (ok) {
        ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.BARRIER_CHILD, 0); // FUN_800a6108(a, 0)
        // FUN_800061a8(actor, 0x11) — labeled no-op.
      }
    }
  }
  if (a.dashStrength1d0f < 0) {                   // (s8)+0x1d0f < 0
    a.dashStrength1d0f = 0;                       // +0x1d0f = 0
    a.gravityCoeff = gravityRestore(a);           // +0x50 = dataPage+0x6c
  }
  if (a.wallContact !== 0) {                      // +0x1cee != 0 → exit
    a.gravityCoeff = gravityRestore(a);           // +0x50 = dataPage+0x6c
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    if ((a.controlWord & 0x40) === 0) romGroundIdleReturn(a); // zz_006a474_
    else romAirKnockoutReturn(a);                 // zz_006a5a4_
  }
}

/** Build the BARRIER GIRL bespoke X (engine FUN_80108250: +0x18da >>= 1 prelude). */
export function createBarrierGirlX(ctx: GirlFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    a.steerYaw = s16(a.steerYaw) >> 1;            // FUN_80108250 prelude
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_804344d8[+0x540]
      case 0: barrierXPhase0(a, ctx); break;
      case 1: barrierXPhase1(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// KILLER GIRL X (pl0308) — 5 phases (engine zz_0134770_ → table @0x80336da4,
// chunk_0035.c:2589-2809). Spin-launch + ring-burst volley.
// ============================================================================

// Phase 0 — FUN_801347c0 @ chunk_0035.c:2603.
function killerXPhase0(a: GActor): void {
  a.fbPhaseSlots[0] += 1;                         // +0x540++
  a.handlerTimer = KILLER_X.FACE_BUDGET;          // +0x558 = 60 (FLOAT_80439f34)
  a.streamSlot = (a.controlWord & 0x40) !== 0 ? 4 : 2; // +0x6ea = 2 (4 air)
  setupLockGate(a, rangeRow868(a), "heading");    // FUN_80066838(row868) < 1 → invalidate
  // zz_006d144_(0xc0) — face (bridge).
  a.gravityCoeff = KILLER_X.ZERO;                 // +0x50 = 0 (FLOAT_80439f30)
  a.yVel = KILLER_X.ZERO;                         // +0x48 = 0
  a.hDecel = KILLER_X.ZERO;                       // +0x4c = 0
  a.hSpeed = KILLER_X.ZERO;                       // +0x44 = 0
  resetPoseHousekeeping(a);
  blinkReposition(a, KILLER_X.DRIFT);             // ×0.95 (FLOAT_80439f38)
  // zz_00677b0_(actor) — bridge clamp.
  const slot = a.streamSlot;                      // cVar1 = +0x6ea
  a.streamSlot = slot + 1;                        // +0x6ea++
  startStream(a, GIRL.PART_MASK, GIRL.X_GROUP, slot, KILLER_X.RATE);
  // +0x1d9b = 0 — stream-authored launch-block byte (not surfaced; labeled no-op).
}

// Phase 1 — FUN_8013490c @ chunk_0035.c:2651. Face budget.
function killerXPhase1(a: GActor, ctx: GirlFamilyCtx): void {
  driftMotion(a, KILLER_X.DRIFT);                 // motion ×0.95; pos += motion
  // zz_00677b0_(actor) — bridge clamp.
  if (a.streamHold1b03 !== 0) {                   // +0x1b03 != 0
    tickStream(a, GIRL.PART_MASK, ctx);
  }
  // zz_006e1ac_(0xc0, 1) — pitch seek (bridge aim channel).
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  if (a.handlerTimer <= KILLER_X.ZERO || faceComplete(a)) {
    a.fbPhaseSlots[0] += 1;                       // +0x540++
  }
}

// Phase 2 — FUN_801349c4 @ chunk_0035.c:2678. Wind-up → spin launch.
function killerXPhase2(a: GActor, ctx: GirlFamilyCtx): void {
  // zz_006d144_(0xc0) face + zz_006e1ac_(0xc0, 1) pitch (bridge).
  driftMotion(a, KILLER_X.DRIFT);                 // motion ×0.95; pos += motion
  // zz_00677b0_(actor) — bridge clamp.
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  if (a.contactP1 !== 0) {                        // +0x1cf0 != 0 — swing event
    // +0x272 |= 2 — status halfword (not surfaced; labeled no-op).
    // FUN_800061a8(actor, 9) — screen/rumble FX (unported, labeled no-op).
  }
  if (a.wallContact !== 0) {                      // +0x1cee != 0 — wind-up stream end
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    a.handlerTimer = KILLER_X.SPIN_WINDOW;        // +0x558 = 10 (FLOAT_80439f40)
    a.tickDelay55c = KILLER_X.GRAVITY;            // +0x55c = 1 (FLOAT_80439f44)
    a.window560 = KILLER_X.RING_COUNT;            // +0x560 = 20 (FLOAT_80439f48)
    // Launch projected off the +0x18da steer pitch: +0x44 = 100 × cos, +0x48 = −100 × sin.
    a.hSpeed = KILLER_X.SPIN_SPEED * projectZ(s16(a.steerYaw));
    a.yVel = KILLER_X.SPIN_SPEED * -projectX(s16(a.steerYaw));
    a.hDecel = KILLER_X.ZERO;                     // +0x4c = 0
    a.gravityCoeff = KILLER_X.ZERO;               // +0x50 = 0
    // +0x272 |= 4 and +0x82 = 0 remain renderer flags.
    a.accumulator80c = 0;
    ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.MELEE_FX, 0); // zz_00b2190_(a, 0)
    ctx.onPlayCue?.(a, 0xf2);                     // zz_00f036c_(actor, 0xf2)
  }
}

// Phase 3 — FUN_80134af8 @ chunk_0035.c:2724. Spin flight + ring bursts.
function killerXPhase3(a: GActor, ctx: GirlFamilyCtx): void {
  // +0x272 |= 2; +0x82 = 0 (no-ops).
  applyDrag(a, KILLER_X.DRIFT);                   // zz_006ed8c_(0.95, FLOAT_80439f38)
  integratePhysics(KILLER_X.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  // zz_00677b0_(actor) — bridge clamp.
  a.tickDelay55c = (a.tickDelay55c ?? 0) - a.dt;  // +0x55c -= dt
  if ((a.tickDelay55c ?? 0) <= KILLER_X.ZERO) {
    // FUN_8016c810((f32)+0x560, actor, 7, 0) — ring-burst child; the decrementing
    // +0x560 float rides r4 (not carried by the hook signature — labeled).
    ctx.onFamilyProjectile?.(a, GIRL_SPAWNERS.KILLER_RING_CHILD, 7);
    a.tickDelay55c = KILLER_X.GRAVITY;            // +0x55c = 1 (FLOAT_80439f44)
    a.window560 = (a.window560 ?? 0) - KILLER_X.GRAVITY; // +0x560 -= 1
  }
  a.handlerTimer -= a.dt;                         // +0x558 -= dt
  if (a.handlerTimer <= KILLER_X.ZERO) {
    a.fbPhaseSlots[0] += 1;                       // +0x540++
    a.hDecel = KILLER_X.ZERO;                     // +0x4c = 0
    a.hSpeed = KILLER_X.ZERO;                     // +0x44 = 0
    a.yVel = KILLER_X.ZERO;                       // +0x48 = 0
    a.gravityCoeff = gravityRestore(a);           // +0x50 = dataPage+0x6c
    // +0x272 = 0 (no-op).
    const slot = a.streamSlot;                    // cVar1 = +0x6ea
    a.streamSlot = slot + 1;                      // +0x6ea++
    startStream(a, GIRL.PART_MASK, GIRL.X_GROUP, slot, KILLER_X.RATE);
    // +0x82 = +0x96 + 'A' (anim letter — no-op); FUN_800061a8(a, 10) — no-op.
    ctx.onPlayCue?.(a, 0xf2);                     // zz_00f036c_(actor, 0xf2)
  }
}

// Phase 4 — FUN_80134c38 @ chunk_0035.c:2772. Fall-out / landing.
function killerXPhase4(a: GActor, ctx: GirlFamilyCtx): void {
  // +0x18da = (s16)trunc((f32)(s16)+0x18da × 0.9) (FLOAT_80439f50).
  a.steerYaw = s16(Math.trunc(s16(a.steerYaw) * KILLER_X.STEER_DECAY));
  if (((a.hitReact ?? 0) & 0x10) !== 0) {         // +0x1d9 & 0x10
    // zz_00107a0_(actor, 0x10) — hit-react acknowledge (unported, labeled no-op).
  }
  tickStream(a, GIRL.PART_MASK, ctx);             // zz_004cd24_(actor, 0xf)
  integratePhysics(KILLER_X.GRAVITY, a, s16(a.lockYaw)); // FUN_80067310(1.0, +0x5ae)
  const grounded = a.grounded === true;           // iVar1 = zz_00677b0_(actor)
  if (grounded && a.contactP0 < 0) {              // landed + (s8)+0x1cef < 0
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    dispatchUpperBodyCue(a, 7);                   // zz_006a750_(actor, 7)
    a.stateTimer = KILLER_X.COOLDOWN_LAND + a.dt; // +0x694 = 16 (FLOAT_80439f54) + dt
    return;
  }
  if (a.wallContact !== 0) {                      // +0x1cee != 0
    a.controlWord &= ~0x3;                        // +0x73f = 0; +0x5e0 &= ~3
    a.steerYaw = 0;                               // +0x18da = 0
    if (grounded) romGroundIdleReturn(a);         // zz_006a474_
    else romAirKnockoutReturn(a);                 // zz_006a5a4_
    a.stateTimer = KILLER_X.COOLDOWN_END + a.dt;  // +0x694 = 4 (FLOAT_80439f58) + dt
  }
}

/** Build the KILLER GIRL bespoke X (engine zz_0134770_). */
export function createKillerGirlX(ctx: GirlFamilyCtx): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const a = actor as GActor;
    if ((a.fbPhaseSlots[1] ?? 0) !== 0) a.lockTarget = null; // +0x541 → +0xcc = 0
    switch (a.fbPhaseSlots[0] ?? 0) {             // PTR_FUN_80336da4[+0x540]
      case 0: killerXPhase0(a); break;
      case 1: killerXPhase1(a, ctx); break;
      case 2: killerXPhase2(a, ctx); break;
      case 3: killerXPhase3(a, ctx); break;
      case 4: killerXPhase4(a, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// Per-borg wiring.
// ============================================================================

export type GirlClusterBorgId =
  | "pl0300" | "pl0301" | "pl0302" | "pl0303" | "pl0304" | "pl0305" | "pl0306"
  | "pl0307" | "pl0308" | "pl0309" | "pl030a" | "pl030b" | "pl030c" | "pl030d";

const GIRL_BORG_NUMBERS: Record<GirlClusterBorgId, number> = {
  pl0300: 0x300, pl0301: 0x301, pl0302: 0x302, pl0303: 0x303, pl0304: 0x304,
  pl0305: 0x305, pl0306: 0x306, pl0307: 0x307, pl0308: 0x308, pl0309: 0x309,
  pl030a: 0x30a, pl030b: 0x30b, pl030c: 0x30c, pl030d: 0x30d,
};

/** Exact command-derived live routing. Slots outside this matrix stay on the host's
 * generic fallback and must never enter a Girl handler. */
export function isGirlClusterLiveSlot(
  borgId: GirlClusterBorgId,
  actionIndex: number,
  variantIndex: number,
): boolean {
  const baseVariant = variantIndex >= 0 && variantIndex <= 4;
  switch (borgId) {
    case "pl0300": case "pl030b":
      return baseVariant && actionIndex >= 0 && actionIndex <= 2;
    case "pl0301":
      return baseVariant && (actionIndex === 0 || actionIndex === 1 || actionIndex === 3);
    case "pl0302":
      return baseVariant && actionIndex >= 0 && actionIndex <= 3;
    case "pl0306":
      return (baseVariant && (actionIndex === 0 || actionIndex === 2))
        || (actionIndex === 3 && (variantIndex === 7 || variantIndex === 13));
    case "pl0305": case "pl0309": case "pl030a":
      return baseVariant && actionIndex >= 0 && actionIndex <= 2;
    case "pl0304":
      return baseVariant && actionIndex >= 0 && actionIndex <= 2;
    case "pl0308":
      return baseVariant && (actionIndex === 1 || actionIndex === 2);
    case "pl0303":
      return baseVariant && (actionIndex === 0 || actionIndex === 3);
    case "pl0307": case "pl030d":
      return baseVariant && (actionIndex === 1 || actionIndex === 2);
    case "pl030c":
      return baseVariant && actionIndex === 1;
  }
}

/** Per-family melee seed slots (the leaf thunks' r4 immediates — see header). */
interface GirlMeleeSeeds { standing: number; rush: number; lunge: number; dive: number; }
const GIRL_MELEE_SEEDS: GirlMeleeSeeds = { standing: 8, rush: 5, lunge: 4, dive: 7 };
const KILLER_MELEE_SEEDS: GirlMeleeSeeds = { standing: 9, rush: 6, lunge: 4, dive: 8 };

/** The standard action-1 dispatcher: family handler (+0x18da >>= 1) → variant table
 *  (v0 → M-1(0), v1 → M-4, v2 → M-3, v3 → M-2, v4 → M-5). */
function createGirlMeleeAction(seeds: GirlMeleeSeeds, ctx: GirlFamilyCtx): (a: RomActor) => void {
  const swings = createGirlComboSwings(ctx, 0);
  const standing = createMeleeGirlStanding(ctx, { seedSlot: seeds.standing });
  const rush = createGirlRushCombo(ctx, seeds.rush);
  const lunge = createMeleeGirlLunge(ctx, { seedSlot: seeds.lunge });
  const dive = createGirlPitchDive(ctx, seeds.dive);
  return (a: RomActor) => {
    a.steerYaw = s16(a.steerYaw) >> 1;            // family handler prelude
    switch (a.variantIndex) {
      case 1: standing(a); break;
      case 2: rush(a); break;
      case 3: lunge(a); break;
      case 4: dive(a); break;
      default: swings(a); break;                  // v0
    }
  };
}

/** DEATH BORG DELTA (pl030c) action-1 dispatcher (handler 0x801d44b8): v0 → M-1(0),
 *  v1/v2 → M-4(6), v3 → M-2(4), v4 → M-2(5) (thunk r4 immediates raw-word verified). */
function createDeltaMeleeAction(ctx: GirlFamilyCtx): (a: RomActor) => void {
  const swings = createGirlComboSwings(ctx, 0);
  const standing6 = createMeleeGirlStanding(ctx, { seedSlot: 6 });
  const lunge4 = createMeleeGirlLunge(ctx, { seedSlot: 4 });
  const lunge5 = createMeleeGirlLunge(ctx, { seedSlot: 5 });
  return (a: RomActor) => {
    a.steerYaw = s16(a.steerYaw) >> 1;
    switch (a.variantIndex) {
      case 1: case 2: standing6(a); break;
      case 3: lunge4(a); break;
      case 4: lunge5(a); break;
      default: swings(a); break;
    }
  };
}

/**
 * Configure a girl-cluster borg. Wires (per the actionStreamTables.json emulated
 * per-borg action maps + the family root/action tables cited in the header):
 *   action 0 → shared B-ranged volley (families with the 0x8010a508 handler)
 *   action 1 → per-variant melee (M-1..M-5 with per-family seeds)
 *   action 2 → per-family X (battle/barrier/killer bespoke; shared cfg X;
 *              cyber-girl.ts reuse; series-3 X reuse for spinner)
 *   action 3 → series-3 X reuse (wire/barrier/delta-II slot layouts preserved)
 */
export function configureGirlClusterFamily(
  actor: RomActor,
  borgId: GirlClusterBorgId,
  ctx: GirlFamilyCtx,
): void {
  const num = GIRL_BORG_NUMBERS[borgId];
  actor.borgNumber = num;
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  const ranged = createGirlRangedVolley(ctx);

  // Action-1 melee per family (null = the family has no melee row).
  let melee: ((a: RomActor) => void) | null = null;
  if (num === 0x30c) melee = createDeltaMeleeAction(ctx);
  else if (num === 0x304 || num === 0x308) melee = createGirlMeleeAction(KILLER_MELEE_SEEDS, ctx);
  else if (num !== 0x303 && num !== 0x306) melee = createGirlMeleeAction(GIRL_MELEE_SEEDS, ctx);

  // Whether the family root's action table has the shared ranged handler at row 0
  // (actionStreamTables: spinner @0x801ba33c and delta @0x801d447c lack it).
  const hasRanged = num !== 0x307 && num !== 0x30d && num !== 0x30c && num !== 0x308;

  // Action 2 (X) per borg.
  let x2: ((a: RomActor) => void) | null = null;
  const cyberRoot = (num === 0x305 || num === 0x309 || num === 0x30a)
    ? createCyberGirlRootAction(ctx) : null; // families/cyber-girl.ts REUSE
  if (num === 0x300 || num === 0x30b) x2 = createBattleGirlX(ctx);
  else if (num === 0x302) x2 = createBarrierGirlX(ctx);       // FUN_8010821c else-arm
  else if (num === 0x306) x2 = createGirlSharedX(BARRIER_SHARED_X_CONFIG, ctx);
  else if (num === 0x304) x2 = createGirlSharedX(KILLER_SHARED_X_CONFIG, ctx); // zz_01346ec_
  else if (num === 0x308) x2 = createKillerGirlX(ctx);        // zz_0134770_
  else if (cyberRoot) x2 = cyberRoot;                          // dispatches action 2 itself

  // Series-3 X reuse (families/shared-series3-x.ts) with the per-borg slot layout
  // (series3XActionSlots: 0x303/0x307/0x30d → [2,3]; 0x301/0x302/0x306 → [3]).
  const series3Borgs = [0x301, 0x302, 0x303, 0x306, 0x307, 0x30d];
  let x3: ((a: RomActor) => void) | null = null;
  if (series3Borgs.includes(num)) {
    const s3 = createSeries3XSpecial(ctx);
    const slots = series3XActionSlots(num);
    if (slots.includes(2) && !x2) x2 = s3;
    if (slots.includes(3)) x3 = s3;
  }

  actor.rootAction = (ra: RomActor) => {
    if (!isGirlClusterLiveSlot(borgId, ra.actionIndex, ra.variantIndex)) return;
    switch (ra.actionIndex) {
      case 0: if (hasRanged) ranged(ra); break;
      case 1: melee?.(ra); break;
      case 2: x2?.(ra); break;
      case 3: x3?.(ra); break;
      default: break;
    }
  };
}
