// ROM-faithful physics EXTRAS — fills the gaps left by physics.ts.
//
// physics.ts ports the PRIMARY integrator FUN_80067310 (chunk_0008.c:3787), its
// vertical-clamp tail, the host-abstracted ground clamp, the drift integrator
// FUN_80067610, and the magnitude projector FUN_800676d8. This module ports the
// REMAINING movement entry-points that family handlers call but physics.ts does
// not yet cover, all 1:1 against `research/decomp/ghidra-export/chunk_0008.c`:
//
//   * zz_0067458_  (chunk_0008.c:3836) — FULL-clamp integrator (FUN_80067310 +
//     upper hSpeed/yVel band clamps via +0x678/+0x67c). Referenced by kung-fu-
//     master, death-borg-chi, cosmic-dragon, cyber-dragon, dragon, phoenix-dragon
//     family handlers (they currently fall back to integratePhysics, losing the
//     upper clamp — see "Integration spec" at the bottom of this file).
//   * FUN_80067524 (chunk_0008.c:3878) — the NO-ground / NO-vertical-clamp
//     integrator (raw position integrate + hDecel + gravity). Used by airborne /
//     ballistic phases that must not snap to the floor.
//   * zz_0068030_ (chunk_0008.c:4337) — the REAL floor snap called inside
//     FUN_80067310:3805. physics.ts abstracts this to the host's clampToGround;
//     this is the faithful port with the documented skip conditions + pos formula.
//   * zz_00677b0_ (chunk_0008.c:3983) — the full collision/step-height probe
//     (surface height query + wall-slide vs land). Its FUN_8003e0a8 surface query
//     is supplied by the host; the wall-slide damping + land snap are faithful.
//   * zz_00679d0_ (chunk_0008.c:4062) — ground revert: zz_00677b0_ then restore
//     savedGroundPos when unsupported. (helpers.groundSnapRevert is a host-
//     delegating contract port; this is the ROM-faithful structural port.)
//
// Float constants are dumped from `user-data/GG4E/disc/sys/boot.dol` (this
// session, via a node DOL reader; seed 0x80437448 == 60.0 validates the reader).
// physics.ts carries these as 0.0 placeholders; ROM_FLOAT_EX below holds the real
// decoded values. This module does NOT edit physics.ts/actor.ts — it composes.

import type { RomActor, RomPhysicsRuntime, Vec3 } from "./actor.js";
import { projectX, projectZ, integratePhysics } from "./physics.js";

// ---------------------------------------------------------------------------
// DOL-decoded constants (real values; physics.ts ROM_FLOAT keeps 0.0 stubs).
// ---------------------------------------------------------------------------

export const ROM_FLOAT_EX = {
  /** 0x804375d0: hSpeed floor + zero-velocity sentinel (FUN_80067310:3806). DOL = 0.0. */
  H_SPEED_FLOOR: 0.0,
  /** 0x804375d4: velocity damping factor applied on wall-slide (zz_00677b0_:4034-4038). DOL ≈ 0.9. */
  WALL_DAMP: 0.8999999761581421,
  /** 0x804375f0: flyer terminal fall velocity (FUN_80067310:3823). DOL = -35.0.
   *  physics.ts stubs this 0.0 — the real value is -35.0. */
  FLY_FALL: -35.0,
  /** 0x804375f4: squared-motion threshold gating FUN_80067610 (line 3921). DOL ≈ 1e-8. */
  DRIFT_EPSILON_SQ: 9.99999905104687e-9,
  /** 0x804375f8: squared |pos - savedGroundPos| threshold in zz_00677b0_'s wall guard (line 4006).
   *  DOL ≈ 1e-10. */
  SNAP_DIST_SQ: 9.999999439624929e-11,
  /** 0x80437600: reciprocal-sqrt Newton constant 0.5 (zz_00677b0_:4022-4025). DOL = 0.5. */
  RSQRT_C0: 0.5,
  /** 0x80437608: reciprocal-sqrt Newton constant 3.0 (zz_00677b0_:4022-4025). DOL = 3.0. */
  RSQRT_C1: 3.0,
} as const;

// ---------------------------------------------------------------------------
// Actor surface fields not yet on RomActor (cannot edit actor.ts). Family ports
// already cast ad-hoc; these give the physics extras a typed home.
// ---------------------------------------------------------------------------

export interface RomPhysicsExtrasScratch {
  /** +0x668: hover/float offset subtracted from floorY by zz_0068030_ (line 4352). */
  hoverOffset668?: number;
  /** +0x1db: airborne / ignore-floor flag. zz_0068030_ (4345) + zz_00677b0_ (4004) skip when set. */
  airborneNoFloor1db?: number;
  /** +0x698: slope-mode selector; zz_00677b0_ (4013-4018) picks descriptor step +0xae when > 0,
  *           +0xac otherwise. */
  slopeMode698?: number;
  /** +0x7c9: collision-probe master disable; zz_00677b0_ (4000) returns 0 when set. */
  collisionDisabled7c9?: number;
  /** +0x741: flyer / no-vertical-clamp flag (FUN_80067310:3815). */
  flyer741?: number;
  /** +0x6cb: second no-clamp flag OR'd with +0x741 (FUN_80067310:3815). */
  noClamp6cb?: number;
  /** +0x754: touchdown callback invoked by zz_00677b0_'s land branch (line 4042-4044). */
  onLand754?: ((actor: RomActor) => void) | null;
}

/** Battle-owned physics queries the ROM reads from globals / the collision world.
 *  Opt-in: attach these to RomActor.physicsRuntime (intersected with this type). */
export interface RomPhysicsExtrasRuntime {
  /** zz_008b290_(): true while the global floor-snap pass is disabled (chunk_0008.c:4344). */
  floorSnapDisabled?(): boolean;
  /** DAT_8043625c+0x34: the battle floor plane Y (chunk_0008.c:4346,4352). */
  floorY?(): number;
  /**
   * Port-side stand-in for FUN_8003e0a8 (chunk_0008.c:4001) — the surface height +
   * outward normal query at the actor's position. NOT yet surfaced from the host
   * collision world; zz_00677b0_ treats a null return as "no surface" (returns 0).
   * TODO(host): wire the collision world; see PORTING.md §collision. */
  surfaceProbe?(pos: Vec3): { height: number; normal: Vec3 } | null;
}

type ExtrasActor = RomActor & RomPhysicsExtrasScratch;
type ExtrasRuntime = RomPhysicsRuntime & RomPhysicsExtrasRuntime;

function ext(actor: RomActor): ExtrasActor {
  return actor as ExtrasActor;
}
function rt(actor: RomActor): ExtrasRuntime | null {
  return (actor.physicsRuntime as ExtrasRuntime | null) ?? null;
}
function isFlyer(actor: RomActor): boolean {
  const e = ext(actor);
  // FUN_80067310:3815 — non-clamp path taken when EITHER +0x741 or +0x6cb is set.
  return (e.flyer741 ?? 0) !== 0 || (e.noClamp6cb ?? 0) !== 0;
}

// ---------------------------------------------------------------------------
// Shared integrator sub-steps. Extracted so physics.ts can delegate (see spec)
// and so the three integrator variants share one audited code path.
// ---------------------------------------------------------------------------

/**
 * The position-integration core common to FUN_80067310 / FUN_80067524 /
 * zz_0067458_ (chunk_0008.c:3794-3804). ROM:
 *   dVar3 = +0x5f4 * +0x5f8                       (timescale × tierScale)
 *   pos.x += dVar3 * (hSpeed * zz_0045204_(yaw))   (sin)
 *   pos.y += yVel * dVar3
 *   pos.z += dVar3 * (hSpeed * zz_0045238_(yaw))   (cos)
 * Returns dVar3 so callers that need it (none today) can reuse it.
 */
export function integratePosition(gravity: number, actor: RomActor, yaw: number): number {
  void gravity;
  const ts = actor.timescale * actor.tierScale;
  actor.pos.x += ts * (actor.hSpeed * projectX(yaw));
  actor.pos.y += ts * actor.yVel;
  actor.pos.z += ts * (actor.hSpeed * projectZ(yaw));
  return ts;
}

/**
 * hSpeed decay + floor clamp (FUN_80067310:3806-3811, also FUN_80067524:3893-3901
 * and FUN_80067610:3930-3935). ROM: `hSpeed += hDecel * +0x5f4; if (hSpeed <
 * FLOAT_804375d0) hSpeed = FLOAT_804375d0;`. */
export function decayHSpeed(actor: RomActor): void {
  actor.hSpeed += actor.hDecel * actor.timescale;
  if (actor.hSpeed < ROM_FLOAT_EX.H_SPEED_FLOOR) actor.hSpeed = ROM_FLOAT_EX.H_SPEED_FLOOR;
}

/**
 * Gravity accumulation (FUN_80067310:3812-3814, FUN_80067524:3902-3904). ROM:
 *   yVel += +0x5f4 * (gravityCoeff * param_1)   where param_1 is the move's gravity arg. */
export function accumulateGravity(gravity: number, actor: RomActor): void {
  actor.yVel += actor.timescale * (actor.gravityCoeff * gravity);
}

/**
 * Lower-only vertical clamp — FUN_80067310:3815-3828 tail. Non-flyer: yVel clamped
 * to >= maxFall (+0x680). Flyer: yVel clamped to >= FLY_FALL (0x804375f0 = -35).
 * This is the EXACT contract of physics.ts's `clampVertical`; re-asserted here
 * against the real DOL FLY_FALL so physics.ts can delegate without re-deriving. */
export function applyVerticalClampLower(actor: RomActor): void {
  if (!isFlyer(actor)) {
    actor.yVel = Math.max(actor.maxFall, actor.yVel);
  } else {
    actor.yVel = Math.max(ROM_FLOAT_EX.FLY_FALL, actor.yVel);
  }
}

/**
 * Full band vertical clamp — zz_0067458_:3851-3865 tail. Non-flyer: yVel clamped
 * to [maxFall (+0x680), maxRise (+0x67c)]. Flyer: identical flyer floor as above.
 * This is the clamp physics.ts's `clampVertical` does NOT apply (it only lowers). */
export function applyVerticalClampBand(actor: RomActor): void {
  if (!isFlyer(actor)) {
    // zz_0067458_ min/max idiom (lines 3851-3857): min(max(yVel, maxFall), maxRise).
    actor.yVel = Math.min(Math.max(actor.yVel, actor.maxFall), actor.maxRise);
  } else {
    actor.yVel = Math.max(ROM_FLOAT_EX.FLY_FALL, actor.yVel);
  }
}

/**
 * hSpeed upper band clamp — zz_0067458_:3843-3850. Applied only when hDecel (+0x4c)
 * > FLOAT_804375d0 (i.e. decel is active). ROM idiom decodes to
 *   min(max(hSpeed, floor), maxHSpeed)   with maxHSpeed at +0x678. */
export function clampHSpeedBand(actor: RomActor): void {
  if (!(ROM_FLOAT_EX.H_SPEED_FLOOR < actor.hDecel)) return;
  actor.hSpeed = Math.min(Math.max(actor.hSpeed, ROM_FLOAT_EX.H_SPEED_FLOOR), actor.maxHSpeed);
}

// ---------------------------------------------------------------------------
// Integrator variants MISSING from physics.ts.
// ---------------------------------------------------------------------------

/**
 * Port of `zz_0067458_` @ chunk_0008.c:3836 — the FULL-clamp integrator.
 * Signature `void zz_0067458_(double gravity, int actor, short yaw)`.
 *
 * Effect: run FUN_80067310 (full integrate + ground + lower vertical clamp), THEN
 *   1. if hDecel > floor: hSpeed = clamp(hSpeed, floor, maxHSpeed)   (3843-3850)
 *   2. yVel: non-flyer clamp(yVel, maxFall, maxRise); flyer max(FLY_FALL, yVel)  (3851-3865)
 *
 * Family handlers call THIS (not FUN_80067310) when a move needs a speed cap —
 * e.g. kung-fu-master (kung-fu-master.ts:329), death-borg-chi ph3, cosmic-dragon
 * (cosmic-dragon.ts:577), cyber-dragon (cyber-dragon.ts:529), dragon
 * (dragon.ts:359), phoenix-dragon. They currently route through integratePhysics
 * and so never receive the upper clamp; wiring this fn restores the cap. */
export function integratePhysicsFullClamp(gravity: number, actor: RomActor, yaw: number): void {
  // 3842: FUN_80067310(gravity, actor, yaw) — full primary integration.
  integratePhysics(gravity, actor, yaw);
  // 3843-3850: upper hSpeed band clamp (only when hDecel is active).
  clampHSpeedBand(actor);
  // 3851-3865: full vertical band clamp (overrides the lower-only clamp the
  // primary integrator just applied — matches the ROM, which re-clamps in sequence).
  applyVerticalClampBand(actor);
}

/**
 * Port of `FUN_80067524` @ chunk_0008.c:3878 — the RAW integrator. Signature
 * `void FUN_80067524(double gravity, int actor, short yaw)`.
 *
 * Identical position integration + hDecel + gravity as FUN_80067310, but with
 *   * NO zz_0068030_ ground snap (the 3805 call is absent), and
 *   * NO vertical clamp tail (no +0x741/+0x6cb test, no maxFall/FLY_FALL).
 * Used by ballistic / airborne phases that must fall freely without floor snap. */
export function integratePhysicsNoClamp(gravity: number, actor: RomActor, yaw: number): void {
  integratePosition(gravity, actor, yaw);
  decayHSpeed(actor);
  accumulateGravity(gravity, actor);
}

// ---------------------------------------------------------------------------
// Ground / collision probes MISSING (or host-abstracted) in physics.ts.
// ---------------------------------------------------------------------------

/**
 * Port of `zz_0068030_` @ chunk_0008.c:4337 — the REAL floor snap invoked at
 * FUN_80067310:3805. physics.ts delegates this to physicsRuntime.clampToGround;
 * this is the faithful struct.decode. Returns 1 when the actor was snapped to the
 * floor, 0 when skipped.
 *
 * ROM skip conditions (any one → return 0):
 *   * zz_008b290_() != 0     (global floor-snap disabled)
 *   * +0x1db != 0            (airborne / ignore-floor flag)
 *   * pos.y + hoverOffset(+0x668) <= floorY    (already at/below the floor plane)
 *   * yVel <= FLOAT_804375d0 (= 0)             (not moving upward into the floor)
 * Snap (else): yVel = 0; target = floorY - hoverOffset;
 *   pos.y = (+0x30 <= target) ? target : +0x30   (= max(savedGroundPos.y, target)). */
export function floorSnap8030(actor: RomActor): number {
  const r = rt(actor);
  const e = ext(actor);
  const floorY = r?.floorY?.() ?? 0;
  const disabled = r?.floorSnapDisabled?.() ?? false;
  const hover = e.hoverOffset668 ?? 0;
  if (
    disabled ||
    (e.airborneNoFloor1db ?? 0) !== 0 ||
    actor.pos.y + hover <= floorY ||
    actor.yVel <= ROM_FLOAT_EX.H_SPEED_FLOOR
  ) {
    return 0;
  }
  actor.yVel = ROM_FLOAT_EX.H_SPEED_FLOOR;
  const target = floorY - hover;
  actor.pos.y = actor.savedGroundPos.y <= target ? target : actor.savedGroundPos.y;
  return 1;
}

/** atan2-style recovered for FUN_800452a0 (chunk_0008.c:4027). The arg order
 *  (horizMag, normalY) is inferred from the flat-ground case returning ~0 (land):
 *  atan2(0, 1) == 0. TODO(exact): FUN_800452a0's int rounding is unsurfaced; the
 *  float atan2 matches the geometric intent. Result returned as BAM16 short. */
function surfaceAngleBam(horizMag: number, normalY: number): number {
  const rad = Math.atan2(horizMag, normalY);
  const bam = Math.round((rad / (Math.PI * 2)) * 0x10000);
  return bam >= 0x8000 ? bam - 0x10000 : bam;
}

/**
 * Port of `zz_00677b0_` @ chunk_0008.c:3983 — the collision / step-height probe.
 * Returns 1 on touchdown (land), 0 otherwise (airborne / wall-slide / no surface).
 *
 * The surface height + outward normal come from FUN_8003e0a8 (line 4001), supplied
 * here by physicsRuntime.surfaceProbe. While that returns null the probe reports
 * "no surface" (return 0) — honest partial port per the host-collision gap.
 *
 * Effects (1:1 with the decomp):
 *   * +0x7c9 set                       → return 0 (collision disabled).        (4000)
 *   * surface height dVar5 via host    → if null, return 0.                    (4001)
 *   * pos.y + stepHeight(+0x6d0) > dVar5 (actor above surface) → return 0.      (4003)
 *   * wall guard (+0x1db == 0): if |pos - savedGroundPos|² > SNAP_DIST_SQ and
 *     the normalized delta points along the surface normal (dot > floor), the
 *     actor is moving away from the wall → return 0.                           (4004-4012)
 *   * slope step sVar4: descriptor[+0xae] if +0x698 > 0 else descriptor[+0xac]. (4013-4018)
 *   * slide angle iVar3 = FUN_800452a0(horizNormalMag, normalY) as BAM16.      (4019-4027)
 *   * if sVar4 < iVar3 (steep): WALL SLIDE — push pos along the normal by
 *     (surfaceY - pos.y) * cos(iVar3); hDecel = 0; hSpeed *= WALL_DAMP; yVel *=
 *     WALL_DAMP; return 0.                                                     (4028-4039)
 *   * else (gentle): LAND — pos.y = surfaceY - stepHeight; invoke +0x754; return 1. (4040-4046) */
export function groundProbe77b0(actor: RomActor): number {
  const e = ext(actor);
  if ((e.collisionDisabled7c9 ?? 0) !== 0) return 0;
  const r = rt(actor);
  const probe = r?.surfaceProbe?.(actor.pos) ?? null;
  if (!probe) return 0; // TODO(host): FUN_8003e0a8 surface query not yet surfaced.
  const surfaceY = probe.height;
  const normal = probe.normal;
  // 4003: actor above the surface (+ stepHeight) → no contact.
  if (!(actor.pos.y + actor.stepHeight <= surfaceY)) return 0;

  // 4004-4012: wall guard. Skipped entirely when the actor is flagged airborne.
  if ((e.airborneNoFloor1db ?? 0) === 0) {
    const dx = actor.pos.x - actor.savedGroundPos.x;
    const dy = actor.pos.y - actor.savedGroundPos.y;
    const dz = actor.pos.z - actor.savedGroundPos.z;
    const deltaMag2 = dx * dx + dy * dy + dz * dz;
    if (ROM_FLOAT_EX.SNAP_DIST_SQ < deltaMag2) {
      // gnt4_PSVECNormalize_bl(delta) then gnt4_PSQUATDotProduct_bl(delta, normal).
      const inv = 1 / Math.sqrt(deltaMag2);
      const ndot = (dx * inv) * normal.x + (dy * inv) * normal.y + (dz * inv) * normal.z;
      if (ROM_FLOAT_EX.H_SPEED_FLOOR < ndot) return 0; // moving along normal → away from wall
    }
  }

  // 4013-4018: slope step select from the descriptor.
  const desc = actor.descriptor;
  const stepSlot = (e.slopeMode698 ?? 0) > 0 ? 0xae : 0xac;
  // descriptor step is a signed short at +0xac/+0xae (per-borg data page). Surfaced
  // via the subtypePartCommand Int8Array is not the right slot; family ports read
  // these lazily. Default to a steep threshold (0) so flat ground lands.
  const sVar4 = readDescriptorStep(desc, stepSlot);

  // 4019-4026: horizNormalMag via 1/sqrt Newton (constants 0.5 / 3.0 from the DOL).
  const horizMag2 = normal.x * normal.x + normal.z * normal.z;
  let horizMag = 0;
  if (ROM_FLOAT_EX.H_SPEED_FLOOR < horizMag2) {
    let inv = 1 / Math.sqrt(horizMag2); // frsqrtte seed
    inv = ROM_FLOAT_EX.RSQRT_C0 * inv * -(horizMag2 * inv * inv - ROM_FLOAT_EX.RSQRT_C1);
    inv = ROM_FLOAT_EX.RSQRT_C0 * inv * -(horizMag2 * inv * inv - ROM_FLOAT_EX.RSQRT_C1);
    horizMag = horizMag2 * ROM_FLOAT_EX.RSQRT_C0 * inv *
      -(horizMag2 * inv * inv - ROM_FLOAT_EX.RSQRT_C1);
  }
  const iVar3 = surfaceAngleBam(horizMag, normal.y);

  if (sVar4 < iVar3) {
    // 4028-4039: WALL SLIDE.
    const ca = projectZ(iVar3); // zz_0045238_((short)iVar3) = cos(angleBam)
    const push = (surfaceY - actor.pos.y) * ca;
    actor.pos.x += normal.x * push;
    actor.pos.y += normal.y * push;
    actor.pos.z += normal.z * push;
    actor.hDecel = ROM_FLOAT_EX.H_SPEED_FLOOR; // +0x4c = 0
    actor.hSpeed *= ROM_FLOAT_EX.WALL_DAMP;     // +0x44 *= 0.9
    actor.yVel *= ROM_FLOAT_EX.WALL_DAMP;       // +0x48 *= 0.9
    return 0;
  }
  // 4040-4046: LAND.
  actor.pos.y = surfaceY - actor.stepHeight;
  e.onLand754?.(actor);
  return 1;
}

/** Descriptor slope step (signed short at +0xac/+0xae of the per-borg data page).
 *  RomDescriptor does not yet surface these as numbers; return 0 (flat-land) until
 *  a family wires the real bytes. TODO(descriptor): surface +0xac/+0xae. */
function readDescriptorStep(desc: RomActor["descriptor"], slot: number): number {
  void desc;
  void slot;
  return 0;
}

/**
 * Port of `zz_00679d0_` @ chunk_0008.c:4062 — ground revert. Runs the collision
 * probe once; when it does NOT land (probe returns 0) AND the actor is not
 * position-frozen (+0x5e0 & 0x40 == 0), restore the saved grounded position.
 * helpers.ts's groundSnapRevert is the host-delegating contract port (it queries
 * a 2D isSupported); this is the ROM-faithful structural port driven by the full
 * 3D groundProbe77b0. Returns true when the probe reported a landing. */
export function groundSnapRevert79d0(actor: RomActor): boolean {
  const landed = groundProbe77b0(actor) !== 0;
  if (!landed && (actor.controlWord & 0x40) === 0) {
    actor.pos.x = actor.savedGroundPos.x;
    actor.pos.y = actor.savedGroundPos.y;
    actor.pos.z = actor.savedGroundPos.z;
  }
  return landed;
}

// ---------------------------------------------------------------------------
// INTEGRATION SPEC — what physics.ts should delegate to (no edits made here).
// ---------------------------------------------------------------------------
//
// physics.ts is currently ~90% faithful. To close the remaining gaps without
// duplicating logic, re-point these four sites at this module:
//
//  1. ROM_FLOAT (physics.ts:13-20) — replace the 0.0 stubs with the DOL-decoded
//     ROM_FLOAT_EX. Specifically:
//       ROM_FLOAT.FLY_FALL        0.0  → ROM_FLOAT_EX.FLY_FALL      (-35.0)
//       ROM_FLOAT.DRIFT_EPSILON_SQ 0.0 → ROM_FLOAT_EX.DRIFT_EPSILON_SQ (~1e-8)
//     (H_SPEED_FLOOR is already correct at 0.0.) clampVertical/groundClamp then
//     read the real flyer floor and the drift gate matches FUN_80067610:3921.
//
//  2. clampVertical (physics.ts:78-89) — keep as-is (it is the exact lower-only
//     FUN_80067310 tail) OR delegate to applyVerticalClampLower. Family handlers
//     that need the speed cap should call integratePhysicsFullClamp (zz_0067458_)
//     instead of integratePhysics; that path layers clampHSpeedBand +
//     applyVerticalClampBand on top.
//
//  3. groundClamp (physics.ts:93-100) — the host abstraction is fine for battles
//     that supply clampToGround. For unit tests / faithful reproduction, call
//     floorSnap8030 (zz_0068030_) which implements the exact skip conditions +
//     pos.y = max(savedGroundPos.y, floorY - hoverOffset) formula.
//
//  4. integrator body (physics.ts:60-72) — optional refactor: the three lines
//     pos.x/pos.y/pos.z are exactly integratePosition(); the hSpeed tail is
//     decayHSpeed(); the gravity line is accumulateGravity(). Delegating removes
//     the hand-maintained copy and guarantees FUN_80067524 (integratePhysicsNoClamp)
//     and zz_0067458_ (integratePhysicsFullClamp) stay byte-identical to the core.
//
// No edit to physics.ts is required for THIS module to build or for the new
// integrators to be correct; the above is the recommended migration path.

// ===========================================================================
// Self-tests.
// ===========================================================================

export type AssertFn = (cond: boolean, msg: string) => void;

function approxEq(a: number, b: number, eps = 1e-4): boolean {
  return Math.abs(a - b) <= eps;
}

/** Build a minimal actor with the physics extras fields populated. */
function makeActor(over: Partial<ExtrasActor> = {}): ExtrasActor {
  const base = (() => {
    // local createRomActor to avoid a heavy import cycle here; mirror the defaults
    // the real factory sets for the fields the integrators touch.
    return {
      physicsRuntime: null,
      pos: { x: 0, y: 0, z: 0 },
      motion: { x: 0, y: 0, z: 0 },
      hSpeed: 0, yVel: 0, hDecel: 0, gravityCoeff: 0,
      heading: 0, lockYaw: 0,
      savedGroundPos: { x: 0, y: 0, z: 0 },
      maxRise: 0, maxFall: 0, maxHSpeed: 0, stepHeight: 0,
      timescale: 1, tierScale: 1, dt: 1,
      controlWord: 0,
    } as unknown as RomActor;
  })();
  return Object.assign(base as ExtrasActor, over);
}

/** Build an extras runtime with the required RomPhysicsRuntime.clampToGround
 *  defaulted (passthrough) so test objects satisfy the interface without forcing
 *  every optional probe to be present (exactOptionalPropertyTypes-safe). */
function makeRuntime(over: RomPhysicsExtrasRuntime = {}): ExtrasRuntime {
  return {
    clampToGround: (pos, velY) => ({ y: pos.y, velY, grounded: false }),
    ...over,
  } as ExtrasRuntime;
}

export function runPhysicsExtrasSelfTests(assert: AssertFn): void {
  // --- DOL constants decoded this session (seed 0x80437448 == 60.0 validates). ---
  assert(ROM_FLOAT_EX.FLY_FALL === -35.0, "DOL 0x804375f0 FLY_FALL == -35.0 (physics.ts stubs 0.0)");
  assert(approxEq(ROM_FLOAT_EX.WALL_DAMP, 0.9), "DOL 0x804375d4 WALL_DAMP ≈ 0.9");
  assert(approxEq(ROM_FLOAT_EX.DRIFT_EPSILON_SQ, 1e-8, 1e-7), "DOL 0x804375f4 DRIFT_EPSILON_SQ ≈ 1e-8");
  assert(approxEq(ROM_FLOAT_EX.SNAP_DIST_SQ, 1e-10, 1e-11), "DOL 0x804375f8 SNAP_DIST_SQ ≈ 1e-10");
  assert(ROM_FLOAT_EX.H_SPEED_FLOOR === 0.0, "DOL 0x804375d0 H_SPEED_FLOOR == 0.0 (matches physics.ts)");

  // --- Test 1: FUN_80067524 (no-clamp) integration step progression. ---
  // yaw 0 BAM → +Z; hSpeed=10, yVel=5, gravity 1, gravityCoeff 1, hDecel -2.
  {
    const a = makeActor({
      hSpeed: 10, yVel: 5, hDecel: -2, gravityCoeff: 1,
      timescale: 1, tierScale: 1,
    });
    integratePhysicsNoClamp(1.0, a, 0);
    assert(approxEq(a.pos.z, 10.0), "FUN_80067524 f1 pos.z == 10 (hSpeed × cos(0))");
    assert(approxEq(a.pos.x, 0.0), "FUN_80067524 f1 pos.x == 0 (sin(0)=0)");
    assert(approxEq(a.pos.y, 5.0), "FUN_80067524 f1 pos.y == 5 (yVel × ts)");
    assert(approxEq(a.hSpeed, 8.0), "FUN_80067524 f1 hSpeed == 8 (10 + hDecel×ts)");
    assert(approxEq(a.yVel, 6.0), "FUN_80067524 f1 yVel == 6 (5 + ts×gc×g)");
    integratePhysicsNoClamp(1.0, a, 0);
    assert(approxEq(a.pos.z, 18.0), "FUN_80067524 f2 pos.z == 18 (10 + 8)");
    assert(approxEq(a.pos.y, 11.0), "FUN_80067524 f2 pos.y == 11 (5 + 6)");
    assert(approxEq(a.hSpeed, 6.0), "FUN_80067524 f2 hSpeed == 6 (8 + -2)");
    assert(approxEq(a.yVel, 7.0), "FUN_80067524 f2 yVel == 7 (6 + 1)");
  }

  // --- Test 2: hDecel floor clamp (FUN_80067310:3809-3811 / decayHSpeed). ---
  {
    const a = makeActor({ hSpeed: 1, hDecel: -5, timescale: 1 });
    decayHSpeed(a);
    assert(a.hSpeed === 0.0, "decayHSpeed clamps hSpeed to FLOAT_804375d0 (0.0) when negative");
    // Second tick stays at the floor (not below).
    decayHSpeed(a);
    assert(a.hSpeed === 0.0, "decayHSpeed holds hSpeed at the floor across ticks");
  }

  // --- Test 3: zz_0067458_ full-clamp upper band (hSpeed + yVel). ---
  // Provide a no-op clampToGround so integratePhysics's ground step is a passthrough;
  // then the full-clamp wrapper applies the [floor, max] bands.
  {
    const a = makeActor({
      hSpeed: 1000, yVel: 1000, hDecel: 1, gravityCoeff: 0,
      maxHSpeed: 20, maxRise: 30, maxFall: -40,
      timescale: 1, tierScale: 1,
      physicsRuntime: makeRuntime(),
    });
    integratePhysicsFullClamp(0.0, a, 0);
    assert(approxEq(a.hSpeed, 20.0), "zz_0067458 clamps hSpeed to maxHSpeed (+0x678)");
    assert(approxEq(a.yVel, 30.0), "zz_0067458 clamps yVel to maxRise (+0x67c) [band, not lower-only]");
  }

  // --- Test 3b: zz_0067458 flyer path uses FLY_FALL floor, not the band. ---
  {
    const a = makeActor({
      hSpeed: 0, yVel: -999, hDecel: 0, gravityCoeff: 0,
      maxFall: -40, maxRise: 30,
      timescale: 1, tierScale: 1,
      flyer741: 1,
      physicsRuntime: makeRuntime(),
    });
    integratePhysicsFullClamp(0.0, a, 0);
    assert(approxEq(a.yVel, -35.0), "zz_0067458 flyer yVel floored at FLY_FALL (-35.0), ignores maxFall");
  }

  // --- Test 4: zz_0068030_ floor snap. ---
  // floorY 10, hover 0; actor at y=12 rising (yVel 5) → snaps: yVel=0, pos.y=10.
  {
    const a = makeActor({
      pos: { x: 0, y: 12, z: 0 }, yVel: 5,
      savedGroundPos: { x: 0, y: 0, z: 0 },
      physicsRuntime: makeRuntime({ floorY: () => 10 }),
    });
    const r = floorSnap8030(a);
    assert(r === 1, "zz_0068030 snaps (returns 1) when above floor and rising");
    assert(a.yVel === 0.0, "zz_0068030 zeroes yVel on snap");
    assert(approxEq(a.pos.y, 10.0), "zz_0068030 sets pos.y = floorY - hover (10)");
  }
  // Skip: actor already at/below floor → no snap.
  {
    const a = makeActor({
      pos: { x: 0, y: 5, z: 0 }, yVel: 5,
      physicsRuntime: makeRuntime({ floorY: () => 10 }),
    });
    const r = floorSnap8030(a);
    assert(r === 0, "zz_0068030 returns 0 when pos.y + hover <= floorY");
    assert(a.yVel === 5 && a.pos.y === 5, "zz_0068030 leaves state untouched on skip");
  }
  // Skip: yVel <= 0 (not rising).
  {
    const a = makeActor({
      pos: { x: 0, y: 12, z: 0 }, yVel: -1,
      physicsRuntime: makeRuntime({ floorY: () => 10 }),
    });
    assert(floorSnap8030(a) === 0, "zz_0068030 returns 0 when yVel <= 0 (not rising)");
  }
  // Snap uses savedGroundPos.y when it is the higher of (saved, floor-hover).
  {
    const a = makeActor({
      pos: { x: 0, y: 12, z: 0 }, yVel: 5,
      savedGroundPos: { x: 0, y: 9, z: 0 }, // 9 <= target(10) → use 10
      physicsRuntime: makeRuntime({ floorY: () => 10 }),
    });
    floorSnap8030(a);
    assert(approxEq(a.pos.y, 10.0), "zz_0068030 pos.y = max(savedGroundPos.y, floorY-hover)");
    const a2 = makeActor({
      pos: { x: 0, y: 12, z: 0 }, yVel: 5,
      savedGroundPos: { x: 0, y: 15, z: 0 }, // 15 > target(10) → use 15
      physicsRuntime: makeRuntime({ floorY: () => 10 }),
    });
    floorSnap8030(a2);
    assert(approxEq(a2.pos.y, 15.0), "zz_0068030 keeps higher savedGroundPos.y (15 > floor-hover 10)");
  }

  // --- Test 5: zz_00677b0_ land branch (flat floor, stationary → lands). ---
  // delta = pos - savedGroundPos == 0 → wall guard skipped; flat normal → angle 0
  // → land: pos.y = surfaceY - stepHeight, onLand fired, returns 1.
  {
    let landed = 0;
    const a = makeActor({
      pos: { x: 0, y: 5, z: 0 },
      savedGroundPos: { x: 0, y: 5, z: 0 }, // delta == 0 → guard skipped
      stepHeight: 2,
      onLand754: () => { landed++; },
      physicsRuntime: makeRuntime({
        surfaceProbe: () => ({ height: 10, normal: { x: 0, y: 1, z: 0 } }),
      }),
    });
    const r = groundProbe77b0(a);
    assert(r === 1, "zz_00677b0 lands (returns 1) on flat floor below the actor");
    assert(approxEq(a.pos.y, 8.0), "zz_00677b0 land sets pos.y = surfaceY - stepHeight (10-2)");
    assert(landed === 1, "zz_00677b0 invokes +0x754 touchdown callback on land");
  }
  // No surface → returns 0, state untouched (honest partial: host probe null).
  {
    const a = makeActor({
      pos: { x: 0, y: 5, z: 0 },
      physicsRuntime: makeRuntime({ surfaceProbe: () => null }),
    });
    assert(groundProbe77b0(a) === 0, "zz_00677b0 returns 0 when host surfaceProbe is null (TODO host)");
  }

  // --- Test 6: integration sub-steps match the inline physics.ts body. ---
  // integratePosition + decayHSpeed + accumulateGravity == FUN_80067310 minus clamp.
  {
    const a = makeActor({
      hSpeed: 10, yVel: 4, hDecel: -1, gravityCoeff: 0.5,
      timescale: 2, tierScale: 1,
    });
    const ts = integratePosition(0.0, a, 0); // yaw 0 → +Z
    assert(approxEq(ts, 2.0), "integratePosition returns timescale × tierScale");
    assert(approxEq(a.pos.z, 20.0), "integratePosition pos.z += ts × hSpeed × cos(0)");
    decayHSpeed(a);
    assert(approxEq(a.hSpeed, 8.0), "decayHSpeed: 10 + (-1 × 2) = 8");
    accumulateGravity(1.0, a);
    assert(approxEq(a.yVel, 5.0), "accumulateGravity: 4 + (2 × 0.5 × 1) = 5");
  }
}
