// Shared-engine 7-phase AIMED AERIAL DIVE/LEAP-SHOT X machine — 1:1 port of
// `zz_00f41c4_` @0x800f41c4 and its phase table @0x8031b92c = [0x800f4214 setup+blink,
// 0x800f4340 turn/windup, 0x800f43f8 aim/fire-window, 0x800f44e0 launch flight,
// 0x800f4610 ballistic descend, 0x800f4730 skid gate, 0x800f47a4 ground skid/recover]
// (table entries 0x8031b948..0x8031b95c are NULL padding — max reachable phase is 6).
//
// Third shared machine after zz_00ff2bc_ (shared-x-special.ts) and zz_00fed6c_
// (shared-melee-lunge.ts). Unlike both, this machine is CONFIG-BLOCK-LESS: the engine's
// only parameter is r4 = the group-4 stream SLOT BASE (both known wrappers emit
// `li r4, 0`), stored by phase 0 into the stream cursor +0x6ea. The engine dispatch
// prologue passes r4 through UNTOUCHED (only r0/r5/r12 clobbered before bctrl). All
// other per-family variation is (a) the wrapper's pre-dispatch decay of the part-2 aim
// shorts +0x18e0/+0x18e2 and (b) ctor-bound per-actor data (movement page +0x4ac, anim
// bank +0x1d80).
//
// Families served (registration = actionTable[2], root-table index 2 for both ctors):
//   Family A — ctor 0x80074940 (pl0400 CLAW ROBOT, pl040a ISAAC), wrapper FUN_80074f38
//              @0x80074f38: li r4,0; +0x18e0/+0x18e2 ×= 0.9 (FLOAT_804377f8, fctiwz
//              s16 round-trip via DOUBLE_80437800); bl 0x800f41c4.
//   Family B — ctor 0x801854f8 (pl0406 DEATH BORG OMEGA), wrapper FUN_80185814
//              @0x80185814: li r4,0; +0x18e0 >>= 1; +0x18e2 >>= 1 (srawi); bl 0x800f41c4.
//
// Source: scratchpad dig wav-eng-800f41c4.json — 14/14 claims CONFIRMED by both
// adversarial lenses (2026-07-06). Verify-pass corrections applied in this port:
//   * FUN_80066838's range check zeroes the Y component before PSVECMag — the phase-0
//     range gate compares HORIZONTAL (XZ) distance, not 3D distance.
//   * zz_0066530_'s cue-0x2c landing latch clears BOTH +0x5e0 bits 0x40 AND 0x80
//     (&= 0xffffff3f), not just the 0x40 position-frozen bit.
//   * FUN_800452a0 IS decompiled (chunk_0005.c): atan2 in BAM —
//     `(s16)(FLOAT_8043707c × gnt4_atan2_bl(dy, dist))` with FLOAT_8043707c =
//     10430.3779296875 = 65536/2π. The aim-pitch formula is exact:
//     desired = clamp(−(s16)actor+0x70 − atan2BAM(muzzleYdelta, horizDist), ±0x4000).
//   * zz_006d144_ is Ghidra-typed void; its usable "return" is FUN_80066a30's r3
//     surviving the tail-call chain (engine cmpwi r3,0 @0x800f43d0) — returns 1 when
//     the remaining yaw delta fits in one turn step.
//
// Gameplay shape: blink-away windup + stream slot 0 → face target (≤60f) → aim window;
// on the stream's contact byte (+0x1cef) launch at 40 u/f along the part-1 aim pitch
// (+0x18da: hSpeed = 40·cos, yVel = −40·sin, ZERO gravity) → ≥20f homing flight
// (stream window +0x1d10, canceled by damage byte +0x1d9), then stream slot 1 +
// gravityCoeff = the borg page's gravityFall (−0.6 for all three members) → ballistic
// descend ≤60f → land (stream slot 2, cue-0x2c latch, FX) or air-fall exit → skid
// (slot 3, 0.95 decel) → ground-idle exit below speed 5. NO +0x694 attack-cooldown
// seed anywhere (verified by grep of the whole engine range — do NOT copy
// shared-x-special's 4.0+dt).

import type { RomActor, Vec3 } from "../rom/actor.js";
import { integratePhysics, projectXzMagnitude } from "../rom/physics.js";
import { vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

/** Machine constants — every value DOL-read (dig claim M3, dual-lens verified). */
export const SHARED_AERIAL_X = {
  /** FLOAT_8043907c = −1.0 — group-4 stream playback rate (zz_004beb8_ param_1). */
  STREAM_RATE: -1.0,
  /** FLOAT_80439088 = 0.0 — scalar zero (velocity resets / timer floor). */
  ZERO: 0.0,
  /** FLOAT_80439090 = 60.0 — phase-0 face-target budget +0x558 AND the phase-3→4
   *  ballistic-descend budget (same literal reused at both seeds). */
  SETUP_TIMER: 60.0,
  DESCEND_TIMER: 60.0,
  /** FLOAT_80439094 = 20.0 — phase-2→3 minimum powered-flight timer seed. */
  LAUNCH_TIMER: 20.0,
  /** FLOAT_804390a0 = 0.9 — steer-pitch decay (+0x18da ×= 0.9, s16 fctiwz round-trip,
   *  applied in phases 4 and 6). */
  STEER_DECAY: 0.9,
  /** FLOAT_804390ac = 250.0 — the +0x760 gate for the phase-2 FX child (subtype 0). */
  FX_DIST_GATE: 250.0,
  /** FLOAT_804390b0 = 0.95 — blink-reposition scale (phases 0/1/2) AND the phase-6
   *  zz_006ed8c_ skid-decel factor. */
  REPOSITION_SCALE: 0.95,
  SKID_DECEL: 0.95,
  /** FLOAT_804390d4 = 1.0 — FUN_80067310 gravity param (phases 3/4). */
  GRAVITY_PARAM: 1.0,
  /** FLOAT_804390dc = 10.0 — phase-5 skid-gate: advance to phase 6 when +0x44 < 10. */
  SKID_ENTER_SPEED: 10.0,
  /** FLOAT_804390e4 = 40.0 — launch speed K: hSpeed = K·cos(pitch), yVel = −K·sin(pitch). */
  LAUNCH_SPEED: 40.0,
  /** FLOAT_804390e8 = 5.0 — phase-6 ground-idle exit: +0x44 < 5 → zz_006a474_. */
  EXIT_SPEED: 5.0,
  /** FLOAT_80437078 = 9.58738019107841e-05 = 2π/65536 — the BAM→radian scale inside
   *  zz_0045238_/zz_0045204_ (cos/sin of a BAM16 angle). */
  BAM_TO_RAD: (Math.PI * 2) / 65536,
  /** FLOAT_8043707c = 10430.3779296875 = 65536/2π — the radian→BAM scale inside
   *  FUN_800452a0 (the atan2-BAM pitch solver; verify-pass extra finding). */
  RAD_TO_BAM: 65536 / (Math.PI * 2),
  /** FLOAT_804376d8 = 0.9 — zz_006e1d0_'s no-target aim-record decay. */
  NO_TARGET_PITCH_DECAY: 0.9,
  /** ±0x4000 — the aim-pitch clamp zz_006e1ac_ passes to zz_006e1d0_ (param_4). */
  PITCH_CLAMP: 0x4000,
  /** zz_00b2190_ @0x800b2190 — trail/FX child spawner (class-0xb child via
   *  zz_0088aa0_(actor,2,0x18,0,1), callbacks FUN_800b26cc/FUN_800b2ce4). Called with
   *  subtype 0 at the phase-2 fire (gated +0x760 > 250.0) and subtype 2 on landing.
   *  NOT a projectile-table spawner — routed through onFamilyProjectile so hosts can
   *  attach the visual; skipping it is an honest no-op. */
  FX_SPAWNER_ADDR: 0x800b2190,
  FX_SUBTYPE_FIRE: 0,
  FX_SUBTYPE_LAND: 2,
  /** Landing upper-cue latch value (zz_0066530_(actor, 0x2c)). */
  LANDING_CUE: 0x2c,
} as const;

/** Per-family movement-page values the engine consumes — dumped from the borg pages
 *  pl0400data.bin / pl040adata.bin / pl0406data.bin (dig claim C4: IDENTICAL for all
 *  three members). The page→actor copy is chunk_0007.c:31-38 (+0x868..+0x888 =
 *  page+0x134..+0x154 — this dig closed that open question). */
export const AERIAL_X_PAGE = {
  /** page+0x6c → gravityCoeff +0x50 at the phase-3→4 transition (disasm 800f45dc-45e4). */
  GRAVITY_FALL: -0.6000000238418579,
  /** page+0xac row 0 (s16) — turn-rate consumed by zz_006d144_/zz_006e1ac_ mask 0xc0,
   *  in BAM per frame-unit. */
  TURN_RATE_ROW0: 2560,
  /** page+0x134 column 0 of rows 0..2 (→ actor+0x868 rows) — the phase-0 range gate,
   *  indexed prevActionIndex(+0x584) % 3: 1000 after actions 0/1, 2500 after action 2. */
  RANGE_ROWS: [1000.0, 1000.0, 2500.0],
} as const;

/** Per-family config — the ROM's ONLY parameters: the r4 slot base plus the wrapper's
 *  pre-dispatch aim-recovery decay (dig claims C1/C2/C3). */
export interface SharedAerialDiveXConfig {
  /** r4 seed for the stream cursor +0x6ea (phase 0: `stb r4,0x6ea` @0x800f423c).
   *  Both known wrappers pass 0. Four group-4 slots are consumed sequentially:
   *  base+0 (P0 windup), +1 (P3 flight-end), +2 (P4 landing), +3 (P5 skid). */
  slotBase: number;
  /** Wrapper pre-decay of the part-2 aim shorts +0x18e0/+0x18e2, run every tick before
   *  phase dispatch (that IS the wrapper body). Family A: ×0.9 with s16 fctiwz
   *  truncation (FLOAT_804377f8/DOUBLE_80437800); family B: arithmetic >>1 (srawi). */
  aimRecover: { kind: "mul"; k: number } | { kind: "shift"; n: number };
  /** page+0x6c gravityFall written to gravityCoeff at P3→4. −0.6 for all three known
   *  members (DERIVED, per-borg page dump). */
  gravityFall?: number;
  /** Whiff fallback: frames before phase 2 launches without the stream's contact byte
   *  (+0x1cef). The ROM has NO timeout — the fire is stream-timed and always arrives in
   *  real banks; our banks aren't byte-loaded (same approximation gred.ts /
   *  shared-x-special.ts document), so a frame budget stands in. TUNED (default 60). */
  whiffFrames?: number;
}

const DEFAULT_WHIFF_FRAMES = 60;

/** Family A wrapper FUN_80074f38 @0x80074f38 effective config (pl0400 CLAW ROBOT,
 *  pl040a ISAAC — memberships proven by the series-4 ctor table @0x802d2f70). */
export const AERIAL_X_FAMILY_A_CONFIG: SharedAerialDiveXConfig = {
  slotBase: 0, // li r4,0 @0x80074f44
  aimRecover: { kind: "mul", k: 0.9 }, // FLOAT_804377f8 = 0.9 @0x80074f50
  gravityFall: AERIAL_X_PAGE.GRAVITY_FALL,
};

/** Family B wrapper FUN_80185814 @0x80185814 effective config (pl0406 DEATH BORG
 *  OMEGA — series-4 ctor table idx 0x06 = 0x801854f8). */
export const AERIAL_X_FAMILY_B_CONFIG: SharedAerialDiveXConfig = {
  slotBase: 0, // li r4,0 @0x8018581c
  aimRecover: { kind: "shift", n: 1 }, // srawi r0,r0,1 @0x80185828/80185834
  gravityFall: AERIAL_X_PAGE.GRAVITY_FALL,
};

/** Host-synced scratch fields (same casting convention as shared-x-special.ts /
 *  shared-melee-lunge.ts — the bridge mirrors these each frame). */
interface AerialXScratch {
  /** +0x5e8-derived lock target position (bridge-synced). */
  lockTarget?: Vec3 | null;
  /** zz_00677b0_ ground-snap result (bridge/physics-synced). */
  grounded?: boolean;
  /** +0x541: target-invalid flag. Phase 0's failed range gate sets it; the engine
   *  prologue then drops the lock pointer (+0xcc = 0) every tick — modeled by
   *  effLockTarget() returning null while set. */
  aerialXTargetInvalid?: boolean;
  /** +0x1d9: damage-event bitmask byte (writers OR bits 0x02/0x04/0x10/0x20/0x40/0x80
   *  in the damage-resolution code, chunk_0003). Not surfaced by the port's damage
   *  path yet — host sets this boolean when the actor took a hit this frame. Cancels
   *  the phase-3 homing window. LABELED APPROXIMATION: defaults to false (homing runs
   *  the full window) when the host doesn't wire it. */
  aerialXDamaged?: boolean;
  /** +0x18e0/+0x18e2: the part-2 aim-record shorts (stride-6 records @+0x18d4; part 2
   *  base +0x18e0). This machine never READS them — the wrapper decays them as
   *  bookkeeping for the families' other (shooter-cluster) actions. Ported faithfully
   *  so the decay shape is preserved once those actions land. */
  aimPitchP2a?: number;
  aimPitchP2b?: number;
}

function scratchOf(actor: RomActor): RomActor & AerialXScratch {
  return actor as RomActor & AerialXScratch;
}

/** The effective lock target: null once phase 0's range gate invalidated it (+0x541 →
 *  the engine prologue's per-tick `+0xcc = 0`). */
function effLockTarget(actor: RomActor): Vec3 | null {
  const s = scratchOf(actor);
  if (s.aerialXTargetInvalid) return null;
  return s.lockTarget ?? null;
}

/** Airborne test — the ROM reads +0x5e0 & 0x40 (position-frozen/air control bit). The
 *  bridge mirrors BorgRuntime.grounded onto the actor; prefer that live value. */
function isAirborne(actor: RomActor): boolean {
  const grounded = scratchOf(actor).grounded;
  if (typeof grounded === "boolean") return !grounded;
  return (actor.controlWord & 0x40) !== 0;
}

/** s16 wrap + truncation — the fctiwz→sth round-trip every steer/aim decay uses. */
function toS16(v: number): number {
  let s = Math.trunc(v) & 0xffff;
  if (s >= 0x8000) s -= 0x10000;
  return s;
}

/**
 * Port of the aim-pitch seek `zz_006e1ac_(actor, 0xc0, part 1)` = `zz_006e1d0_(actor,
 * 0xc0, 1, clamp 0x4000)` — writes the part-1 aim-pitch short at +0x18da (stride-6
 * record base +0x18d4; +0x18d4 + 1×6). Mapped to actor.steerYaw per the established
 * +0x18da convention (rom/actor.ts:61-63).
 *
 * ROM formula (dig S1, atan2 CONFIRMED by the verify pass):
 *   desired = clamp(−(s16)actor+0x70 − atan2BAM(muzzleYdelta, horizDist), ±0x4000)
 *   step    = pageTurnRate × (f32)actor+0x768 per tick
 *   no-target: record ×= 0.9 (FLOAT_804376d8)
 *
 * PORT APPROXIMATIONS (each labeled):
 *  - actor+0x70 (body-pitch base) is not surfaced on RomActor → treated as 0.
 *  - the muzzle row (actor + part×0x30 + 0x8e0/0x8f0/0x900) is not surfaced → dy is
 *    measured from actor.pos instead of the part-1 muzzle point.
 *  - the (f32)actor+0x768 step scalar is not surfaced → actor.dt stands in (the yaw
 *    analog FUN_800669d0 uses +0x1dc8 = dt, so this is the same frame-unit shape).
 */
function seekAimPitch(actor: RomActor): void {
  const target = effLockTarget(actor);
  let pitch = toS16(actor.steerYaw);
  if (!target) {
    // No-target path: decay the record by FLOAT_804376d8 = 0.9 (s16 round-trip).
    actor.steerYaw = toS16(pitch * SHARED_AERIAL_X.NO_TARGET_PITCH_DECAY);
    return;
  }
  const dx = target.x - actor.pos.x;
  const dz = target.z - actor.pos.z;
  const dy = target.y - actor.pos.y;
  // zz_006e1d0_ zeroes the vector's Y before PSVECMag — horizontal distance only.
  const horizDist = Math.hypot(dx, dz);
  // FUN_800452a0: (s16)(FLOAT_8043707c × atan2(dy, dist)).
  const atanBam = toS16(SHARED_AERIAL_X.RAD_TO_BAM * Math.atan2(dy, horizDist));
  let desired = -atanBam; // −(s16)+0x70 − atan2BAM with the +0x70≈0 approximation above
  if (desired > SHARED_AERIAL_X.PITCH_CLAMP) desired = SHARED_AERIAL_X.PITCH_CLAMP;
  if (desired < -SHARED_AERIAL_X.PITCH_CLAMP) desired = -SHARED_AERIAL_X.PITCH_CLAMP;
  const step = AERIAL_X_PAGE.TURN_RATE_ROW0 * actor.dt;
  const delta = desired - pitch;
  if (Math.abs(delta) <= step) pitch = desired;
  else pitch += Math.sign(delta) * step;
  actor.steerYaw = toS16(pitch);
}

/** Face the lock target — `zz_006d144_(actor, 0xc0)` writes BOTH +0x5ae (lockYaw) and
 *  +0x72 (heading) toward the target at page-rate×dt. The bridge pre-computes lockYaw
 *  from the live target each frame (melee-lunge precedent), so facing is applied
 *  directly; with no/invalid target the yaws hold. Returns the ROM's implicit r3
 *  pass-through from FUN_80066a30: 1 when aligned (instantaneous here — labeled). */
function faceLockTarget(actor: RomActor): boolean {
  const target = effLockTarget(actor);
  if (!target) return false;
  actor.heading = actor.lockYaw; // mask 0x80 → +0x72
  actor.activeYaw = actor.lockYaw; // integration target follows the lock
  return true; // bridge pre-aims → aligned within one step
}

/** Launch-velocity re-derivation from the part-1 aim pitch (disasm 800f4478-44a8 /
 *  800f4530-4560): hSpeed(+0x44) = 40·cos(pitch), yVel(+0x48) = −40·sin(pitch) — the
 *  fneg @0x800f4494 puts positive pitch (target below) into downward yVel. BAM via
 *  FLOAT_80437078 = 2π/65536. */
function deriveLaunchVelocity(actor: RomActor): void {
  const rad = toS16(actor.steerYaw) * SHARED_AERIAL_X.BAM_TO_RAD;
  actor.hSpeed = SHARED_AERIAL_X.LAUNCH_SPEED * Math.cos(rad);
  actor.yVel = -SHARED_AERIAL_X.LAUNCH_SPEED * Math.sin(rad);
}

/** Blink/reposition tail shared by phases 0/1/2: motion ×= 0.95; pos += motion. */
function repositionTail(actor: RomActor): void {
  vecScale(SHARED_AERIAL_X.REPOSITION_SCALE, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);
}

// ============================================================================
// Phase 0 — @0x800f4214. Setup + range gate + blink + stream slot base+0.
// ============================================================================
function aerialXPhase0(actor: RomActor, cfg: SharedAerialDiveXConfig, ctx: StreamContext): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = 1; // +0x540++
  s.aerialXTargetInvalid = false; // fresh activation (the +0x541 flag re-evaluates below)
  actor.streamSlot = cfg.slotBase; // stb r4,0x6ea @0x800f423c — the r4 slot base

  // Range gate FUN_80066838(range, actor): range = RANGE_ROWS[prevActionIndex % 3]
  // (actor+0x868 row, column 0) × (f32)actor+0xb4. Verify-pass correction: the check
  // zeroes Y before PSVECMag — HORIZONTAL distance only. Returns −1 with no lock
  // (+0xcc == 0); the engine treats < 1 (both 0 and −1, signed cmpwi) as invalidate:
  // +0x541 = 1, +0xcc = 0, +0x5ac = +0x5ae (hold current lock yaw). The machine still
  // runs targetless — it flies straight at current yaw/pitch (lock invalidation, not a
  // move gate). PORT APPROXIMATION: the +0xb4 param-tier scale is not surfaced on
  // RomActor; the range is compared unscaled (×1.0).
  const rowIndex = ((actor.prevActionIndex % 3) + 3) % 3;
  const range = AERIAL_X_PAGE.RANGE_ROWS[rowIndex] ?? AERIAL_X_PAGE.RANGE_ROWS[0]!;
  const target = s.lockTarget ?? null;
  const inRange =
    target !== null &&
    Math.hypot(target.x - actor.pos.x, target.z - actor.pos.z) <= range;
  if (!inRange) {
    s.aerialXTargetInvalid = true; // +0x541 = 1 (prologue drops +0xcc every tick)
    actor.activeYaw = actor.lockYaw; // +0x5ac = +0x5ae — hold current lock yaw
  }

  actor.handlerTimer = SHARED_AERIAL_X.SETUP_TIMER; // +0x558 = 60.0

  faceLockTarget(actor); // zz_006d144_(actor, 0xc0)
  seekAimPitch(actor); // zz_006e1ac_(actor, 0xc0, 1) → +0x18da, clamp ±0x4000

  // Blink AWAY from the target: motion(+0x38) = pos − lockTargetPos; ×0.95; pos +=
  // motion (the shared blink-windup shape; verify note: "away", not "past").
  const blinkTarget = effLockTarget(actor);
  if (blinkTarget) {
    vecSubtract(actor.pos, blinkTarget, actor.motion);
    vecScale(SHARED_AERIAL_X.REPOSITION_SCALE, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }
  // zz_00677b0_(actor) — ground snap; owned by the actor's battle-local physics runtime.

  // STREAM START — slot = +0x6ea, cursor++. Airborne fork (+0x5e0 & 0x40) changes ONLY
  // header args (10, 2) vs (−1, −1) to zz_004beb8_, NOT the slot (unlike zz_00ff2bc_'s
  // ground/air slot fork). The header-arg pair's effect is UNRESOLVED (dig X1: forwarded
  // into the PTR_FUN_802d0da0 header opcodes; start-frame/blend hypothesis) — treated as
  // a no-op passthrough until decoded.
  void isAirborne(actor);
  const slot = actor.streamSlot;
  actor.streamSlot = slot + 1;
  startStream(actor, 0xf, 4, slot, SHARED_AERIAL_X.STREAM_RATE);
  void ctx;
}

// ============================================================================
// Phase 1 — @0x800f4340. Turn/windup: face target ≤60f, then advance.
// ============================================================================
function aerialXPhase1(actor: RomActor, cfg: SharedAerialDiveXConfig, ctx: StreamContext): void {
  repositionTail(actor); // motion ×= 0.95; pos += motion
  // zz_00677b0_ ground snap — bridge-owned.

  // ROM gates the stream tick on +0x1b03 != 0 (part-0 anim hold byte inside the
  // 0x40-stride part block @+0x1ae0+0x23 — writer not located, dig S2). LABELED
  // APPROXIMATION: not surfaced by the VM → tick unconditionally (shared-melee-lunge
  // precedent, line 94).
  tickStream(actor, 0xf, ctx);

  seekAimPitch(actor); // zz_006e1ac_(actor, 0xc0, 1)

  actor.handlerTimer -= actor.dt; // +0x558 -= +0x1dc8
  // Advance when 60f elapse OR facing aligned — zz_006d144_'s implicit r3 (from
  // FUN_80066a30) is 1 when |+0x5aa| fits one step; instantaneous here (bridge pre-aims).
  const aligned = faceLockTarget(actor);
  if (actor.handlerTimer <= 0 || aligned) {
    actor.fbPhaseSlots[0] = 2; // +0x540++
    actor.handlerTimer = 0; // (port bookkeeping: phase 2 reuses +0x558 as whiff budget)
  }
  void cfg;
}

// ============================================================================
// Phase 2 — @0x800f43f8. Aim/fire-window: launch on the stream contact byte.
// ============================================================================
function aerialXPhase2(actor: RomActor, cfg: SharedAerialDiveXConfig, ctx: StreamContext): void {
  faceLockTarget(actor); // zz_006d144_(actor, 0xc0)
  seekAimPitch(actor); // zz_006e1ac_(actor, 0xc0, 1)
  repositionTail(actor); // motion ×= 0.95; pos += motion
  // zz_00677b0_ ground snap — bridge-owned.
  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)

  // WHIFF fallback (port approximation — the ROM has no timeout here; the fire is
  // stream-timed via op 0x02's +0x1cef and always arrives in real banks; without
  // byte-loaded banks a labeled frame budget launches anyway).
  actor.handlerTimer += actor.dt;
  const whiffed = actor.handlerTimer >= (cfg.whiffFrames ?? DEFAULT_WHIFF_FRAMES);

  // FIRE TRIGGER: part-0 stream contact byte +0x1cef (op 0x02 b2) != 0.
  if (actor.contactP0 !== 0 || whiffed) {
    actor.fbPhaseSlots[0] = 3; // +0x540++
    actor.handlerTimer = SHARED_AERIAL_X.LAUNCH_TIMER; // +0x558 = 20.0
    deriveLaunchVelocity(actor); // +0x44 = 40·cos(+0x18da); +0x48 = −40·sin(+0x18da)
    actor.hDecel = SHARED_AERIAL_X.ZERO; // +0x4c = 0.0
    actor.gravityCoeff = SHARED_AERIAL_X.ZERO; // +0x50 = 0.0 — gravity OFF during launch
    // FX child (subtype 0): the ROM gates on +0x760 > 250.0 (FLOAT_804390ac); +0x760's
    // writer is un-located (dig open question, FX-only impact). LABELED APPROXIMATION:
    // fire unconditionally — zz_00b2190_ is a cosmetic trail/FX child spawner and hosts
    // without the hook no-op it.
    ctx.onFamilyProjectile?.(actor, SHARED_AERIAL_X.FX_SPAWNER_ADDR, SHARED_AERIAL_X.FX_SUBTYPE_FIRE);
  }
}

// ============================================================================
// Phase 3 — @0x800f44e0. Launch flight: ≥20f powered flight with homing window.
// ============================================================================
function aerialXPhase3(actor: RomActor, cfg: SharedAerialDiveXConfig, ctx: StreamContext): void {
  const s = scratchOf(actor);

  // HOMING WINDOW: the ROM tracks (face + aim-seek) while the stream's op-0x03 window
  // byte +0x1d10 is set, and a damage event (+0x1d9 != 0) clears it. NEITHER byte is
  // surfaced by the VM/damage path (dig S2). LABELED APPROXIMATION: the window is open
  // for the whole ≥20f flight unless the host set the damaged flag this activation
  // (aerialXDamaged — sticky until the next phase-0 entry would matter, but phase 3 is
  // the only consumer).
  const homing = s.aerialXDamaged !== true;
  if (homing) {
    faceLockTarget(actor); // zz_006d144_(actor, 0xc0)
    seekAimPitch(actor); // zz_006e1ac_(actor, 0xc0, 1)
  }

  // Velocity RE-DERIVED from the aim pitch EVERY tick (frozen only at the 3→4 handoff).
  deriveLaunchVelocity(actor);
  integratePhysics(SHARED_AERIAL_X.GRAVITY_PARAM, actor, actor.lockYaw); // FUN_80067310(1.0, actor, +0x5ae)
  // zz_00677b0_ ground snap — bridge-owned (groundClamp inside integratePhysics).
  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)

  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  if (actor.handlerTimer <= 0) {
    actor.handlerTimer = 0; // +0x558 = 0.0
    // ROM gates the advance on +0x1b01 != 0 (part-0 segment-complete latch — writer not
    // located, dig S2/open questions). LABELED APPROXIMATION: treat the latch as set
    // once the 20f minimum elapses (handlerTimer frame-budget stand-in for the
    // stream-end signal, same stance as gred.ts/shared-x-special.ts).
    actor.fbPhaseSlots[0] = 4; // +0x540++
    actor.handlerTimer = SHARED_AERIAL_X.DESCEND_TIMER; // +0x558 = 60.0
    // gravityCoeff(+0x50) = movement-page gravityFall (page+0x6c; disasm 800f45dc-45e4).
    actor.gravityCoeff = cfg.gravityFall ?? AERIAL_X_PAGE.GRAVITY_FALL;
    const slot = actor.streamSlot; // slot base+1
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, SHARED_AERIAL_X.STREAM_RATE);
  }
}

// ============================================================================
// Phase 4 — @0x800f4610. Ballistic descend: land or air-fall exit after 60f.
// ============================================================================
function aerialXPhase4(actor: RomActor, ctx: StreamContext): void {
  // Steer-pitch decay: +0x18da = (s16)((f32)+0x18da × 0.9) — s16 float round-trip.
  actor.steerYaw = toS16(toS16(actor.steerYaw) * SHARED_AERIAL_X.STEER_DECAY);

  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)
  integratePhysics(SHARED_AERIAL_X.GRAVITY_PARAM, actor, actor.lockYaw); // FUN_80067310(1.0, actor, +0x5ae)

  // zz_00677b0_(actor) != 0 → LANDED (bridge-synced grounded flag).
  const grounded = scratchOf(actor).grounded === true;
  if (grounded) {
    actor.fbPhaseSlots[0] = 5; // +0x540++
    const slot = actor.streamSlot; // slot base+2 (landing stream)
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, SHARED_AERIAL_X.STREAM_RATE);
    // zz_0066530_(actor, 0x2c) — upper-cue LATCH (raw field writes, not a cue-table
    // dispatch): +0x5e4 = 0x2c, +0x87 = 0 (byte not surfaced — no-op), +0x69c = 0.0
    // (not surfaced — no-op). Verify-pass correction applied: clears BOTH +0x5e0 bits
    // 0x40 AND 0x80 (&= 0xffffff3f), not just the 0x40 position-frozen bit.
    actor.ubCue = SHARED_AERIAL_X.LANDING_CUE;
    actor.controlWord &= ~0xc0;
    ctx.onFamilyProjectile?.(actor, SHARED_AERIAL_X.FX_SPAWNER_ADDR, SHARED_AERIAL_X.FX_SUBTYPE_LAND); // zz_00b2190_(actor, 2)
    return;
  }
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
  if (actor.handlerTimer <= 0) {
    // AIR-FALL EXIT after 60f without landing: +0x4c = 0, +0x44 = 0, +0x73f = 0 (per-
    // actor housekeeping byte, not surfaced — no-op), +0x5e0 &= ~3, then the real
    // zz_006a5a4_ call (chunk_0026.c:3618 — dispatches upper cue 6; the old
    // "no cue change" reading was wrong).
    actor.hDecel = SHARED_AERIAL_X.ZERO;
    actor.hSpeed = SHARED_AERIAL_X.ZERO;
    actor.controlWord &= ~0x3;
    romAirKnockoutReturn(actor);
  }
}

// ============================================================================
// Phase 5 — @0x800f4730. Skid gate — then FALLS THROUGH into phase 6 same tick.
// ============================================================================
function aerialXPhase5(actor: RomActor, ctx: StreamContext): void {
  if (actor.hSpeed < SHARED_AERIAL_X.SKID_ENTER_SPEED) {
    actor.fbPhaseSlots[0] = 6; // +0x540++
    const slot = actor.streamSlot; // slot base+3 (skid stream)
    actor.streamSlot = slot + 1;
    startStream(actor, 0xf, 4, slot, SHARED_AERIAL_X.STREAM_RATE);
  }
  // Unconditional fall-through into the phase-6 body (bl 0x800f47a4 @0x800f478c) — the
  // skid stream starts AND the decel/exit check still runs this same tick (frame parity).
  aerialXPhase6(actor, ctx);
}

// ============================================================================
// Phase 6 — @0x800f47a4. Ground skid/recover: decay to a stop, then ground idle.
// ============================================================================
function aerialXPhase6(actor: RomActor, ctx: StreamContext): void {
  // Steer-pitch decay (same s16 float round-trip as phase 4).
  actor.steerYaw = toS16(toS16(actor.steerYaw) * SHARED_AERIAL_X.STEER_DECAY);

  tickStream(actor, 0xf, ctx); // zz_004cd24_(actor, 0xf)

  // zz_006ed8c_(0.95, actor) — dt-corrected exponential decay of +0x44 AND +0x48:
  // dt == 1 → v ×= k; else v −= v×(1−k)×dt (FLOAT_80437670 = 1.0). The general form
  // below equals v×k at dt = 1.
  const loss = (1 - SHARED_AERIAL_X.SKID_DECEL) * actor.dt;
  actor.hSpeed -= actor.hSpeed * loss;
  actor.yVel -= actor.yVel * loss;

  // zz_00670dc_(actor, +0x5ae) — yaw-only ground physics, NO gravity. LABELED
  // APPROXIMATION: zz_00670dc_ itself is unported; the FUN_800676d8-shaped XZ
  // projection (projectXzMagnitude) reproduces its yaw-only position advance from
  // hSpeed without touching yVel/gravity.
  projectXzMagnitude(actor.hSpeed, actor, actor.lockYaw);

  if (actor.hSpeed < SHARED_AERIAL_X.EXIT_SPEED) {
    // GROUND-IDLE EXIT: +0x73f = 0 (housekeeping byte, not surfaced — no-op),
    // +0x5e0 &= ~3, then the real zz_006a474_ call (chunk_0026.c:3671 —
    // decomp-verified helper). NO +0x694 attack-cooldown seed — this machine
    // seeds NO cooldown anywhere (verified; do not copy shared-x-special's 4.0+dt).
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor);
  }
}

/**
 * Build the shared aerial-dive X handler for one family config — the port of the
 * wrapper (FUN_80074f38 / FUN_80185814 shape) + the zz_00f41c4_ dispatch. Wire the
 * result as actionTable[2] in the family's root action dispatcher (root-table index 2
 * for both ctors: 0x802d4e9c[2] = 0x80074f38, 0x8035d120[2] = 0x80185814).
 */
export function createSharedAerialDiveX(
  cfg: SharedAerialDiveXConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    // ===== WRAPPER BODY (runs every tick BEFORE the engine dispatch) =====
    // Family aim-recovery decay of the part-2 aim shorts +0x18e0/+0x18e2:
    //   A: (s16)((f32)v × 0.9) fctiwz round-trip; B: (s16)v >> 1 (srawi).
    const s = scratchOf(actor);
    const a = toS16(s.aimPitchP2a ?? 0);
    const b = toS16(s.aimPitchP2b ?? 0);
    if (cfg.aimRecover.kind === "mul") {
      s.aimPitchP2a = toS16(a * cfg.aimRecover.k);
      s.aimPitchP2b = toS16(b * cfg.aimRecover.k);
    } else {
      s.aimPitchP2a = a >> cfg.aimRecover.n;
      s.aimPitchP2b = b >> cfg.aimRecover.n;
    }

    // ===== ENGINE PROLOGUE zz_00f41c4_ =====
    // `if ((s8)+0x541 != 0) +0xcc = 0;` — while the invalid flag is set, the lock
    // pointer is dropped every tick. Modeled by effLockTarget() returning null while
    // aerialXTargetInvalid is set (phase 0 owns the flag).
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: aerialXPhase0(actor, cfg, ctx); break;
      case 1: aerialXPhase1(actor, cfg, ctx); break;
      case 2: aerialXPhase2(actor, cfg, ctx); break;
      case 3: aerialXPhase3(actor, cfg, ctx); break;
      case 4: aerialXPhase4(actor, ctx); break;
      case 5: aerialXPhase5(actor, ctx); break;
      case 6: aerialXPhase6(actor, ctx); break;
      // Table entries [7..12] @0x8031b948..0x8031b95c are NULL in the ROM.
      default: break;
    }
  };
}

// ============================================================================
// Family registrations. Root dispatchers: family A = FUN_80074ccc → root table
// @0x802d4e9c = [FUN_80074d08, FUN_80074e48, FUN_80074f38]; family B = FUN_801856e8 →
// @0x8035d120 = [FUN_80185724, FUN_80185724, FUN_80185814]. Only index 2 (the X
// wrapper → this machine) is ported; indices 0/1 route to the unported shared-shooter
// cluster (zz_00f1e30_/zz_00f2374_/…) and keep the generic fallback.
// ============================================================================

function createAerialXRootAction(
  cfg: SharedAerialDiveXConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  const xSpecial = createSharedAerialDiveX(cfg, ctx);
  const actionTable: Array<((actor: RomActor) => void) | null> = [null, null, xSpecial];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a CLAW ROBOT-family actor (ctor 0x80074940: pl0400 CLAW ROBOT 0x400,
 *  pl040a ISAAC 0x40a — series-4 ctor table @0x802d2f70 idx 0x00/0x0a, no other borgs
 *  share this ctor). */
export function configureClawRobotFamily(
  actor: RomActor,
  borgId: "pl0400" | "pl040a",
  ctx: StreamContext,
): void {
  actor.borgNumber = borgId === "pl0400" ? 0x400 : 0x40a;
  actor.rootAction = createAerialXRootAction(AERIAL_X_FAMILY_A_CONFIG, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a DEATH BORG OMEGA actor (ctor 0x801854f8: pl0406 0x406 only — series-4
 *  ctor table idx 0x06, the pointer occurs nowhere else in the DOL). */
export function configureDeathBorgOmegaFamily(
  actor: RomActor,
  borgId: "pl0406",
  ctx: StreamContext,
): void {
  actor.borgNumber = 0x406;
  actor.rootAction = createAerialXRootAction(AERIAL_X_FAMILY_B_CONFIG, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  void borgId;
}
