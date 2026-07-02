// Knockback DIRECTION calc — ported from the decompiled ROM function `zz_00300bc_`
// @ 0x800300bc (research/decomp/ghidra-export/chunk_0003.c:8540-8627).
//
// Full analysis: research/decomp/behavior-notes.md section (p).
// Raw constants + mode table: research/decomp/data/knockback-direction-800300bc.json
//
// CONFIRMED (DERIVED) from the ROM:
//   - The real game computes knockback as a full 3D DIRECTION (yaw + pitch, stored as two
//     BAM16 shorts, 0x10000 = 360 degrees — same fixed-point convention as borg heading at
//     struct+0x72, behavior-notes.md section 3), not a flat scalar magnitude.
//   - There are exactly 5 vector-source modes, selected by a per-move signed byte
//     (`puVar17[7]` in the ROM, a field on the same per-move hit-record the base-damage
//     formula reads — see behavior-notes.md section (o)/(p)).
//   - The yaw/pitch conversion is `atan2(...) * (65536 / (2*PI))`, confirmed by reading the
//     ROM float constant FLOAT_8043707c = 10430.3779296875 directly out of boot.dol
//     (exactly 65536/(2*pi) to float precision).
//   - After the base direction, a per-move angular TRIM is added: two more signed bytes on
//     the SAME per-move hit-record (offsets 0x14/0x15), scaled by *256 (placed in the high
//     byte of the 16-bit angle). This is the "angle-offset table" from HANDOFF-PROMPT.md —
//     it isn't a separate fixed ROM table, just two more fields on the per-move record.
//   - The degenerate-vector fallback constants (magnitude-squared threshold 0.01, fallback
//     vector (0,0,-1)) are confirmed exact ROM float reads.
//
// WHAT'S PORTED vs. TUNED-FALLBACK, mode by mode (see behavior-notes.md section (p) for the
// exact ROM field sourcing of every mode):
//   - Mode 1 ("attacker to target" straight relative-position vector) is FULLY DERIVED and
//     fully portable: it only needs the attacker's and target's world positions, both of
//     which this port already tracks on BorgRuntime.pos. This is the mode wired as the
//     default in combat.ts's applyHit() seam.
//   - Mode 3 ("linked object" position delta, ROM offset+100/0x64 on the hit-context wrapper
//     objects) is DERIVED in mechanism (a straight position subtract between two objects) but
//     the port has no equivalent "linked object" concept (partner/sub-object pointers) to
//     source it from yet — exposed here as computeLinkedObjectDirection() taking two
//     caller-supplied positions so it's usable once/if the port grows a linked-object model,
//     but NOT wired into combat.ts's default path.
//   - Modes 0, 2, and 4 all read fields the TS runtime does not model at all (attacker
//     "muzzle point" sub-object vectors at ROM +0x38/+0x3c/+0x40 and +0x11c/+0x12c/+0x13c, a
//     hit-context "aim" vector pair at +0x30/+0x3c, and a camera/stored-aim vector at
//     +0x8dc/+0x8ec/+0x8fc). There is no source data in the port to compute these from, so
//     they are NOT ported — callers needing those modes should keep using the pre-existing
//     flat-vector TUNED behavior (attacker-to-target or a caller-supplied direction) rather
//     than silently mislabeling a guess as one of these modes.
//   - The per-move angular trim (angle-offset "table") mechanism is fully DERIVED, but the
//     actual per-move trim VALUES are authored move data living in the still-undecoded
//     plxxxxhit.bin/comhit.bin per-move record format (research/format-specs/hit-bin-format.md).
//     Until that format is cracked, callers pass trimYaw/trimPitch = 0 (TUNED default, i.e.
//     "no trim" rather than a guessed nonzero value).
//   - The actual KNOCKBACK MAGNITUDE (how far/hard the target launches once the direction is
//     known) is NOT computed by this ROM function at all — it only ever writes angle fields.
//     MELEE.KNOCKBACK / SHOT.KNOCKBACK / SPECIAL.KNOCKBACK in constants.ts remain TUNED flat
//     scalars; only the DIRECTION those scalars get multiplied into is upgraded here.

import {
  BAM16_PER_RADIAN,
  BAM16_WRAP,
  DEGENERATE_MAG_SQ_THRESHOLD,
  FALLBACK_DIR_COMPONENTS,
} from "./knockback.generated.js";
import { sub, type Vec3 } from "./index.js";

/** Radians-to-BAM16 angle conversion. FLOAT_8043707c, confirmed == 65536/(2*PI) via direct
 *  ROM float read (research/decomp/data/knockback-direction-800300bc.json). */
export { BAM16_PER_RADIAN };

/** Degenerate-vector magnitude-squared threshold. FLOAT_80436fc0, confirmed 0.01 via direct
 *  ROM float read. Below this, the ROM substitutes the fixed fallback vector (0,0,-1). */

/** Fixed fallback direction when the source vector is degenerate (near-zero). FLOAT_80436f74
 *  = -1.0 confirmed via direct ROM float read; x/y = 0.0 (FLOAT_80436f68). */
const FALLBACK_DIR: Vec3 = FALLBACK_DIR_COMPONENTS;

export interface KnockbackAngle {
  /** BAM16 yaw, wrapped to a signed 16-bit range (-0x8000..0x7fff), same convention as
   *  struct+0x72 heading. */
  yaw: number;
  /** BAM16 pitch (negated per the ROM's `-(short)` on the pitch conversion), same range. */
  pitch: number;
}

function wrapBam16(v: number): number {
  let r = Math.trunc(v) % BAM16_WRAP;
  if (r >= 0x8000) r -= BAM16_WRAP;
  if (r < -0x8000) r += BAM16_WRAP;
  return r;
}

/**
 * Core direction->BAM16(yaw,pitch) conversion, byte-for-byte port of the ROM's post-processing
 * (degenerate guard, atan2*BAM16-const, the squared-not-sqrt horizontal-magnitude quirk in the
 * pitch term reproduced exactly rather than "corrected" — see behavior-notes.md section (p)
 * caveats on why this asymmetry is kept as-is).
 *
 * `trimYaw`/`trimPitch` are the per-move angle-offset-table bytes (already pre-scaled by the
 * caller to BAM16 units, i.e. `signedByte * 256` — see applyAngleTrim() below). Pass 0 when the
 * per-move trim value isn't known (current default; see file header).
 */
export function vectorToKnockbackAngle(v: Vec3, trimYaw = 0, trimPitch = 0): KnockbackAngle {
  let { x, y, z } = v;
  const magSq = Math.abs(x * x + y * y + z * z);
  if (magSq < DEGENERATE_MAG_SQ_THRESHOLD) {
    x = FALLBACK_DIR.x;
    y = FALLBACK_DIR.y;
    z = FALLBACK_DIR.z;
  }
  const yaw = Math.trunc(Math.atan2(x, z) * BAM16_PER_RADIAN);
  // ROM quirk, reproduced exactly: horizontal term is (x*x + z*z), NOT sqrt(x*x+z*z) — see
  // behavior-notes.md section (p) caveats before "fixing" this to a textbook atan2(y, dist).
  const horizMagSq = Math.abs(x * x + z * z);
  const pitchRaw = Math.trunc(Math.atan2(y, horizMagSq) * BAM16_PER_RADIAN);
  const pitch = -pitchRaw;
  return {
    yaw: wrapBam16(yaw + trimYaw),
    pitch: wrapBam16(pitch + trimPitch),
  };
}

/**
 * Mode 1 ("attacker to target" straight relative-position vector) — FULLY DERIVED, the only
 * one of the 5 ROM modes this port has enough data to compute from BorgRuntime.pos alone.
 * ROM: `gnt4_PSVECSubtract_bl(defenderObj+0x20, attackerObj+0x20)` i.e. target.pos - attacker.pos.
 */
export function computeAttackerToTargetDirection(attackerPos: Vec3, targetPos: Vec3): Vec3 {
  return sub(targetPos, attackerPos);
}

/**
 * Mode 3 ("linked object" position delta) — DERIVED mechanism (plain position subtract between
 * two linked/partner objects), but NOT wired into combat.ts by default: this port doesn't yet
 * model a "linked object" (partner/sub-object) concept on BorgRuntime. Exposed for future use
 * once/if that concept exists. ROM: `targetLinkedPos - attackerLinkedPos` (offset 0x64 on the
 * hit-context wrapper objects, not the resolved attacker/defender sub-objects used by mode 1).
 */
export function computeLinkedObjectDirection(attackerLinkedPos: Vec3, targetLinkedPos: Vec3): Vec3 {
  return sub(targetLinkedPos, attackerLinkedPos);
}

/**
 * Convert a per-move angle-offset-table signed byte (range -128..127) to the BAM16 trim value
 * the ROM adds (`byte * -0x100`, i.e. the byte occupies the high byte of the 16-bit angle).
 * The port has no source of real per-move trim bytes yet (still-undecoded hit.bin format), so
 * callers currently pass 0 (see file header) — this helper exists so wiring up real per-move
 * trim data later is a one-line change, not a re-derivation.
 */
export function angleTrimByteToBam16(trimByte: number): number {
  return trimByte * -0x100;
}

/**
 * BAM16 angle -> unit direction vector on the XZ plane (yaw only; ignores pitch — matches how
 * combat.ts currently only consumes the horizontal knockback direction, since vertical "pop-up"
 * is handled separately as a TUNED constant in applyHit()).
 */
export function bam16YawToXZ(yaw: number): Vec3 {
  const rad = yaw / BAM16_PER_RADIAN;
  return { x: Math.sin(rad), y: 0, z: Math.cos(rad) };
}

/**
 * Full ROM-accurate direction for a melee/shot/special hit, given only attacker and target
 * positions (mode 1 — the only mode fully computable from data this port tracks). Returns a
 * normalized-ish XZ direction vector ready to multiply by a (still-TUNED) knockback magnitude
 * scalar in combat.ts's applyHit().
 *
 * `trimYaw` defaults to 0 (see angleTrimByteToBam16 — no real per-move trim data ported yet).
 */
export function knockbackDirectionFromPositions(
  attackerPos: Vec3,
  targetPos: Vec3,
  trimYaw = 0,
): Vec3 {
  const raw = computeAttackerToTargetDirection(attackerPos, targetPos);
  const angle = vectorToKnockbackAngle(raw, trimYaw, 0);
  return bam16YawToXZ(angle.yaw);
}
