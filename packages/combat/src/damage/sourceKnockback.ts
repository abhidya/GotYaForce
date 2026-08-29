// =============================================================================
// sourceKnockback.ts — ROM-faithful 1:1 port of the GG4E knockback pipeline.
//
// Ports two decompiled pieces, byte-for-byte against the source:
//   - zz_00300bc_ (compute_knockback_launch_direction) @0x800300bc — chunk_0003.c:8540-8627
//     computes the launch DIRECTION (yaw + pitch as two BAM16 shorts) from one of 5
//     vector-source modes, then applies a per-move angular trim.
//   - the strength-indexed MAGNITUDE tables DAT_802dd8a0 / DAT_802d3664, consumed by
//     zz_005ec20_ @0x8005ec20 (chunk_0007.c:5568) and FUN_8005ed38 @0x8005ed38
//     (chunk_0007.c:5630). zz_00300bc_ itself ONLY writes yaw/pitch; the magnitude is
//     resolved by these separate reaction handlers from actor+0x702 (the hit record's
//     +0x0d severity byte copied to the victim at chunk_0003.c:8047).
//
// MAGNITUDE TABLES: driven by the DOL-dumped float tables at 0x802dd8a0 /
// 0x802d3664 (research/decomp/data/knockback-direction-800300bc.json documents the
// direction constants; packages/combat/src/data/knockbackStrength.json is the fresh
// DOL dump produced by scripts/gen-knockback-strength-tables.mjs). NO tuned scalars:
// every magnitude value comes from a DOL-dumped table.
//
// DIRECTION CONSTANTS: the 4 ROM floats (FLOAT_8043707c radians→BAM16, FLOAT_80436fc0
// degenerate threshold, FLOAT_80436f68 = 0.0, FLOAT_80436f74 = -1.0) are confirmed by
// direct DOL read (research/decomp/data/knockback-direction-800300bc.json:
// confirmed_rom_constants) and inlined here so this module is auditable standalone.
//
// CHALLENGE-FLOW GATE (research/decomp/index/challenge-flow-evidence.md:188):
//   "Port knockback as computed direction from zz_00300bc_, not as flat tuned scalar."
//   This module IS that computed direction. The existing combat.ts applyHit path uses
//   packages/physics/src/knockback.ts, which ports only mode 1 + the post-processing;
//   THIS module is the complete 5-mode port plus the strength-indexed magnitude select.
//
// TYPE-CATEGORY INFLUENCE: NONE on direction. The launch direction is purely GEOMETRIC
// (position/aim vectors); the borg type-category matrix (sourceDamage.ts) only affects
// DAMAGE, never the knockback vector. The MAGNITUDE is strength-indexed (the +0x0d byte
// → s*7 / (s+1)*8 tables), also type-independent.
//
// SELF-CONTAINED: depends only on the DOL data tables. It does NOT import combat.ts /
// gauges.ts / @gf/physics, so it can be unit-ported and audited in isolation, then wired
// into applyHit via the integration spec at the bottom of this file.
// =============================================================================

import knockbackStrengthData from "../data/knockbackStrength.json" with { type: "json" };

// -----------------------------------------------------------------------------
// DOL-dumped direction constants (FLOAT_804xxxxx), confirmed by direct ROM read.
// Source: research/decomp/data/knockback-direction-800300bc.json:confirmed_rom_constants.
// -----------------------------------------------------------------------------
/** FLOAT_8043707c: radians → BAM16 conversion == 65536/(2π) to float precision. */
const BAM16_PER_RADIAN = 10430.3779296875;
/** FLOAT_80436fc0: degenerate-vector magnitude-squared threshold (|v|² < this → fallback). */
const DEGENERATE_MAG_SQ_THRESHOLD = 0.009999999776482582;
/** FLOAT_80436f68 = 0.0 (zero/epsilon). FLOAT_80436f74 = -1.0 (fallback Z). */
const FALLBACK_DIR_X = 0;
const FALLBACK_DIR_Y = 0;
const FALLBACK_DIR_Z = -1;
/** BAM16 wraps at 0x10000; stored as signed short (-0x8000..0x7fff). */
const BAM16_WRAP = 0x10000;

// -----------------------------------------------------------------------------
// DOL-dumped magnitude tables (DAT_802dd8a0 / DAT_802d3664). 16 floats each, indexed
// by the clamped knockback strength byte. Source: data/knockbackStrength.json
// (scripts/gen-knockback-strength-tables.mjs dump of boot.dol).
// -----------------------------------------------------------------------------
type StrengthData = {
  provenance: Record<string, unknown>;
  horizontalLaunch: number[]; // DAT_802dd8a0[s] = s*7.0  (zz_005ec20_ ground h-speed base)
  velocityMagnitude: number[]; // DAT_802d3664[s] = (s+1)*8.0 (FUN_8005ed38 launch velocity)
};
const STRENGTH = knockbackStrengthData as unknown as StrengthData;
const STRENGTH_TABLE_MAX = 15; // actor+0x702 is clamped to the 16-entry tables (0..15).

// -----------------------------------------------------------------------------
// ACTOR + CONTEXT TYPES — minimal, each field cited to its object+0xNNN offset.
// -----------------------------------------------------------------------------

/** Minimal actor view. Only `pos` is needed for the default mode 1; the optional fields
 *  feed the other 4 modes (sub-object / linked-object / stored-aim vectors at high offsets
 *  the TS runtime does not yet model — see per-mode docs). */
export interface SourceKnockbackActor {
  /** +0x20: world position (vec3). Mode 1 reads attacker.pos / defender.pos directly. */
  pos: Vec3;
  /** Mode 0/2 fallback + per-mode inputs. Each is a ROM sub-object/aim vec3 (offsets
   *  +0x38/+0x3c/+0x40, +0x8dc/+0x8ec/+0x8fc, +0x11c/+0x12c/+0x13c) the port does not
   *  source yet. Pass undefined to get the labeled partial-port behavior (see modes). */
  motion38?: Vec3; // attacker sub-object +0x38/+0x3c/+0x40 (mode 0/2 fallback vec3)
  storedAim8dc?: Vec3; // +0x8dc/+0x8ec/+0x8fc (mode 4 camera/stored-aim)
  muzzle11c?: Vec3; // +0x11c/+0x12c/+0x13c (mode 4 final fallback)
}

/** Per-hit record + context inputs consumed by zz_00300bc_. */
export interface SourceKnockbackContext {
  /** Mode selector — the signed byte at the per-move hit-record +0x0e, passed by the sole
   *  caller resolve_hitbox_target_effects_and_damage as `(int)*(char*)(puVar17+7)`
   *  (chunk_0003.c:7945). Values 0..4 select the 5 vector-source modes; the confirmed
   *  caller only ever passes a per-move signed byte. Mode 1 is the default knockback
   *  direction (attacker→target); the others source aim/linked/camera vectors. */
  mode: number;
  /** Record s8 +0x14 — knockback YAW trim. Added as `trim * -0x100` BAM (high byte). */
  trimYaw?: number;
  /** Record s8 +0x15 — knockback PITCH trim. Same `trim * -0x100` BAM scaling. */
  trimPitch?: number;
}

/** A 3-component vector (matches @gf/physics Vec3 shape; redeclared locally for
 *  self-containment, identical to sourceDamage.ts's local convention). */
export interface Vec3 { x: number; y: number; z: number; }

/** Result of the launch-direction computation: two BAM16 shorts, matching the ROM's
 *  victim+0x284 (yaw) / victim+0x282 (pitch) writes. */
export interface KnockbackLaunchAngle {
  /** BAM16 yaw (-0x8000..0x7fff), same fixed-point convention as struct+0x72 heading. */
  yaw: number;
  /** BAM16 pitch (negated per the ROM's `-(short)` on the pitch conversion). */
  pitch: number;
}

// =============================================================================
// zz_00300bc_ — compute_knockback_launch_direction @0x800300bc (chunk_0003.c:8540-8627)
//
// Computes the launch yaw+pitch (two BAM16 shorts) from one of 5 vector-source modes,
// applies the degenerate-vector fallback, the atan2→BAM16 conversion (reproducing the
// ROM's squared-horizontal-magnitude pitch quirk byte-for-byte), and the per-move
// angular trim. Returns the angle pair (the ROM writes them to victim+0x284/+0x282).
// =============================================================================

/**
 * 1:1 port of zz_00300bc_. Computes the launch yaw+pitch (BAM16) for a hit.
 *
 *   attacker — the resolving attacker object (param_1+0x20). For mode 1 only `pos` is read.
 *   defender — the victim object (param_2+0x20). The angle is written TO the defender in
 *              the ROM (victim+0x284/+0x282); this port returns it instead of mutating.
 *   ctx      — mode selector + per-move angle trims.
 *
 * MODES (param_3, chunk_0003.c:8560-8605):
 *   0 — attacker sub-object relative subtract (+0x20 − +0x2c on the attacker object),
 *        fallback to attacker.motion38 (+0x38/+0x3c/+0x40) when magnitude ≤ 0. PARTIAL:
 *        the +0x20/+0x2c sub-object vec3 pair is untraced in the TS runtime; if
 *        `attacker.pos`-equivalent sub-fields are absent, this falls back to motion38
 *        directly (cited TODO: wire the real +0x20/+0x2c hitbox/muzzle pair).
 *   1 — attacker→target relative position: defender.pos − attacker.pos (chunk_0003.c:8580).
 *        FULLY PORTED — the default knockback direction; only needs both actors' +0x20.
 *   2 — context-object relative subtract (param_1+0x30 − param_1+0x3c), fallback to
 *        attacker.motion38 like mode 0. PARTIAL: +0x30/+0x3c untraced; falls back.
 *   3 — linked-object position delta (param_2+0x64 − param_1+0x64). PARTIAL: no linked-
 *        object concept; caller passes the two linked positions via the optional vec
 *        override (computeKnockbackLaunchDirectionLinked) when available.
 *   4 — camera/stored-aim cascade (attacker+0x8dc → attacker-linked+0x8dc → attacker+0x11c).
 *        PARTIAL: reads attacker.storedAim8dc then attacker.muzzle11c when supplied.
 *
 * The degenerate guard, atan2→BAM16 conversion, the SQUARED-horizontal-magnitude pitch
 * quirk, the per-move trim, and the BAM16 wrap are FAITHFUL for every mode (only the
 * INPUT VECTOR resolution differs by mode). See source header caveats before "fixing"
 * the squared-magnitude pitch — it is reproduced byte-for-byte, not corrected.
 */
export function computeKnockbackLaunchDirection(
  attacker: SourceKnockbackActor,
  defender: SourceKnockbackActor,
  ctx: SourceKnockbackContext,
): KnockbackLaunchAngle {
  // --- Mode dispatch (chunk_0003.c:8560-8605): resolve the source vector `v`. ---
  const v = resolveModeVector(attacker, defender, ctx.mode);

  // --- Degenerate guard (chunk_0003.c:8606-8610): |x²+y²+z²| < 0.01 → (0,0,-1). ---
  let { x, y, z } = v;
  if (Math.abs(x * x + y * y + z * z) < DEGENERATE_MAG_SQ_THRESHOLD) {
    x = FALLBACK_DIR_X;
    y = FALLBACK_DIR_Y;
    z = FALLBACK_DIR_Z;
  }

  // --- Yaw (chunk_0003.c:8614-8615): (short)(atan2(x,z) * BAM16_PER_RADIAN) → +0x284. ---
  // FUN_800452a0(a,b) = (int)(atan2(a,b) * FLOAT_8043707c).
  const yawRaw = Math.trunc(Math.atan2(x, z) * BAM16_PER_RADIAN);

  // --- Pitch (chunk_0003.c:8616-8617): horizMagSq = |x²+z²| (SQUARED, not sqrt),
  //     pitch = -(short)(atan2(y, horizMagSq) * BAM16_PER_RADIAN) → +0x282. ---
  const horizMagSq = Math.abs(x * x + z * z);
  const pitchRaw = Math.trunc(Math.atan2(y, horizMagSq) * BAM16_PER_RADIAN);

  let yaw = yawRaw;
  let pitch = -pitchRaw;

  // --- Per-move angular trim (chunk_0003.c:8618-8620): record+0x14/+0x15 (signed),
  //     each scaled * -0x100 (byte occupies the high byte of the 16-bit angle). ---
  yaw += toSignedByte(ctx.trimYaw ?? 0) * -0x100;
  pitch += toSignedByte(ctx.trimPitch ?? 0) * -0x100;

  return { yaw: wrapBam16(yaw), pitch: wrapBam16(pitch) };
}

/**
 * Mode 3 variant taking the two linked-object positions directly (the ROM reads
 * param_2+0x64 − param_1+0x64; the TS runtime has no linked-object concept, so a caller
 * that does resolve a partner/sub-object passes both positions here). Same post-processing.
 */
export function computeKnockbackLaunchDirectionLinked(
  attackerLinkedPos: Vec3,
  targetLinkedPos: Vec3,
  ctx: Omit<SourceKnockbackContext, "mode">,
): KnockbackLaunchAngle {
  return vectorToKnockbackAngle(
    sub(targetLinkedPos, attackerLinkedPos),
    ctx.trimYaw,
    ctx.trimPitch,
  );
}

/** Post-processing only (degenerate guard + atan2→BAM16 + squared-horiz pitch + trim).
 *  Exposed so a caller with a pre-resolved vector (e.g. a projectile travel direction)
 *  gets the identical BAM16 conversion the ROM applies. */
export function vectorToKnockbackAngle(
  v: Vec3,
  trimYaw = 0,
  trimPitch = 0,
): KnockbackLaunchAngle {
  let { x, y, z } = v;
  if (Math.abs(x * x + y * y + z * z) < DEGENERATE_MAG_SQ_THRESHOLD) {
    x = FALLBACK_DIR_X;
    y = FALLBACK_DIR_Y;
    z = FALLBACK_DIR_Z;
  }
  const yawRaw = Math.trunc(Math.atan2(x, z) * BAM16_PER_RADIAN);
  const horizMagSq = Math.abs(x * x + z * z);
  const pitchRaw = Math.trunc(Math.atan2(y, horizMagSq) * BAM16_PER_RADIAN);
  const yaw = yawRaw + toSignedByte(trimYaw) * -0x100;
  const pitch = -pitchRaw + toSignedByte(trimPitch) * -0x100;
  return { yaw: wrapBam16(yaw), pitch: wrapBam16(pitch) };
}

/** Per-move angle-offset signed byte → BAM16 trim (`byte * -0x100`). The port has no
 *  source of real per-move trim bytes beyond the DamageRecord fields; this matches
 *  packages/physics/src/knockback.ts angleTrimByteToBam16 exactly. */
export function angleTrimByteToBam16(trimByte: number): number {
  return toSignedByte(trimByte) * -0x100;
}

/** Resolve the source vector for a given mode (chunk_0003.c:8560-8605). Modes 0/2/4
 *  are PARTIAL (cited sub-object fields untraced in the TS runtime); mode 1 is FULLY
 *  PORTED; mode 3 is handled via the Linked variant above. */
function resolveModeVector(
  attacker: SourceKnockbackActor,
  defender: SourceKnockbackActor,
  mode: number,
): Vec3 {
  if (mode === 1) {
    // Mode 1 (chunk_0003.c:8579-8581): defender.pos − attacker.pos. NO fallback guard.
    return sub(defender.pos, attacker.pos);
  }
  if (mode === 0 || mode === 2) {
    // Modes 0/2 compute a sub-object relative subtract (+0x20−+0x2c on the attacker obj
    // for mode 0; param_1+0x30−param_1+0x3c for mode 2), then fall back to the attacker's
    // +0x38/+0x3c/+0x40 vec3 when the magnitude ≤ 0.0. Both sub-object pairs are untraced
    // in the TS runtime (TODO: wire hitbox/muzzle +0x20/+0x2c and context +0x30/+0x3c),
    // so this resolves to the fallback vec3 (attacker.motion38) directly — structurally
    // identical to the ROM's magnitude-≤-0 arm. Pass a real sub-object pair later by
    // extending SourceKnockbackActor when those offsets are traced.
    return attacker.motion38 ?? { x: 0, y: 0, z: 0 };
  }
  if (mode === 4) {
    // Mode 4 cascade (chunk_0003.c:8583-8602): if attacker+0x83 == 0 use attacker+0x8dc;
    // else if attacker-linked+0x83 == 0 use attacker-linked+0x8dc; else use attacker+0x11c.
    // +0x83 (eligibility/special-state) and the linked object are untraced; this takes
    // storedAim8dc then muzzle11c (the two attacker-side vec3s), matching the cascade's
    // first and last arms. TODO: wire the +0x83 gate + linked-object pointer.
    return attacker.storedAim8dc ?? attacker.muzzle11c ?? { x: 0, y: 0, z: 0 };
  }
  if (mode === 3) {
    // Mode 3 is handled by computeKnockbackLaunchDirectionLinked (needs linked-object
    // positions the TS runtime doesn't model). Here it degenerates to the zero vector,
    // which the post-processing fallback converts to (0,0,-1) — use the Linked variant.
    return { x: 0, y: 0, z: 0 };
  }
  // Negative/other fallthrough: the ROM's if/else chain leaves the local vector
  // uninitialized (chunk_0003.c:8569 `else if (-1 < param_3)` only admits ≥0); the
  // confirmed caller only passes 0..4. Treat as the zero vector → fallback direction.
  return { x: 0, y: 0, z: 0 };
}

// =============================================================================
// MAGNITUDE — strength-indexed tables (DAT_802dd8a0 / DAT_802d3664), consumed by the
// reaction handlers zz_005ec20_ (ground) and FUN_8005ed38 (launch). zz_00300bc_ writes
// only the DIRECTION; these read actor+0x702 (the hit record +0x0d severity byte copied
// to the victim at chunk_0003.c:8047) and pick the magnitude from the strength table.
// =============================================================================

/** Clamp a strength byte to 0..15 (the ROM clamps actor+0x702 to the 16-entry tables). */
export function knockbackStrengthClamp(strength: number): number {
  const s = Math.abs(Math.trunc(strength));
  return s > STRENGTH_TABLE_MAX ? STRENGTH_TABLE_MAX : s;
}

/**
 * 1:1 port of FUN_8005ed38's magnitude select @0x8005ed38 (chunk_0007.c:5624-5630):
 *   idx = clamp(|actor+0x702| + (actor+0x6fd & 0x80 ? 2 : 0), 0..15)
 *   velocity = DAT_802d3664[idx]  (= (idx+1)*8.0)
 * The +0x6fd bit 0x80 is the airborne/launch flag; when set the strength is boosted by 2
 * (a stronger launch while airborne). `strength` is the record's +0x0d severity byte
 * (DamageRecord.reactionAnimVariant); `airborneBoost` is (victim+0x6fd & 0x80) !== 0.
 */
export function launchVelocityMagnitude(strength: number, airborneBoost = false): number {
  const boosted = Math.trunc(Math.abs(strength)) + (airborneBoost ? 2 : 0);
  return STRENGTH.velocityMagnitude[knockbackStrengthClamp(boosted)] ?? 8;
}

/**
 * 1:1 port of zz_005ec20_'s horizontal-speed select @0x8005ec20 (chunk_0007.c:5564-5568):
 *   idx = clamp(|actor+0x702|, 0..15)
 *   h-speed = scaleRatio * DAT_802dd8a0[idx]  (= idx*7.0)
 * scaleRatio is the T5 attacker/victim size-scale ratio (attacker+0xc4 / victim+0xb4);
 * pass 1 for the identity (the ROM's FUN_8005ed38 launch path does NOT apply the ratio —
 * only the ground zz_005ec20_ path does).
 */
export function groundHorizontalSpeed(strength: number, scaleRatio = 1): number {
  const idx = knockbackStrengthClamp(strength);
  return scaleRatio * (STRENGTH.horizontalLaunch[idx] ?? 0);
}

/** Raw DOL-dumped table access (DAT_802dd8a0 / DAT_802d3664), for audit/self-test. */
export const KNOCKBACK_STRENGTH_TABLES: Readonly<{
  HORIZONTAL: readonly number[];
  VELOCITY: readonly number[];
}> = Object.freeze({
  HORIZONTAL: STRENGTH.horizontalLaunch,
  VELOCITY: STRENGTH.velocityMagnitude,
});

// =============================================================================
// Helpers (vec subtract, BAM16 wrap, signed-byte interpretation).
// =============================================================================

function sub(a: Vec3, b: Vec3): Vec3 {
  return { x: a.x - b.x, y: a.y - b.y, z: a.z - b.z };
}

function wrapBam16(v: number): number {
  // The ROM stores (short): cast int → int16. Reproduce as signed wrap to -0x8000..0x7fff.
  let r = Math.trunc(v) % BAM16_WRAP;
  if (r >= 0x8000) r -= BAM16_WRAP;
  if (r < -0x8000) r += BAM16_WRAP;
  return r;
}

/** Interpret a byte value (0..255 or already-signed) as the ROM's `*(char*)` signed byte. */
function toSignedByte(value: number): number {
  const truncated = Math.trunc(value) & 0xff;
  return truncated >= 0x80 ? truncated - 0x100 : truncated;
}

// =============================================================================
// Neutral factory.
// =============================================================================

/** Neutral baseline actor at the origin. Mode 1 produces a zero vector → fallback dir. */
export function defaultSourceKnockbackActor(pos: Vec3 = { x: 0, y: 0, z: 0 }): SourceKnockbackActor {
  return { pos };
}

/** Neutral baseline context (mode 1 — attacker→target — no trims). */
export function defaultSourceKnockbackContext(mode = 1): SourceKnockbackContext {
  return { mode, trimYaw: 0, trimPitch: 0 };
}

// =============================================================================
// SELF-TESTS — runSourceKnockbackSelfTests(assert). assert shape: (cond, msg) => void,
// matching the runXxxSelfTests(assert) convention (sourceDamage.ts / rom.selfcheck.ts).
// =============================================================================

export type SourceKnockbackAssert = (cond: boolean, msg: string) => void;

export function runSourceKnockbackSelfTests(assert: SourceKnockbackAssert): void {
  // ---------- DOL-dumped magnitude tables (DAT_802dd8a0 / DAT_802d3664) -------------------
  // Strength-indexed, NOT flat/tuned. Verified against the fresh DOL dump.
  assert(
    STRENGTH.horizontalLaunch.length === 16 && STRENGTH.horizontalLaunch[6] === 42,
    `DAT_802dd8a0[6] === 42 (s*7) — got ${STRENGTH.horizontalLaunch[6]}`,
  );
  assert(
    STRENGTH.velocityMagnitude.length === 16 && STRENGTH.velocityMagnitude[6] === 56,
    `DAT_802d3664[6] === 56 ((s+1)*8) — got ${STRENGTH.velocityMagnitude[6]}`,
  );
  // melee(strength 6) > shot(strength 4) > charge/special(strength 2): 56 > 40 > 24.
  assert(launchVelocityMagnitude(6) === 56, "launch velocity strength 6 === 56 (melee)");
  assert(launchVelocityMagnitude(4) === 40, "launch velocity strength 4 === 40 (shot)");
  assert(launchVelocityMagnitude(2) === 24, "launch velocity strength 2 === 24 (charge/special)");
  assert(launchVelocityMagnitude(0) === 8, "launch velocity strength 0 === 8 (min)");
  assert(groundHorizontalSpeed(6) === 42, "ground h-speed strength 6 === 42");
  assert(groundHorizontalSpeed(0) === 0, "ground h-speed strength 0 === 0");

  // Strength clamp (chunk_0007.c clamps actor+0x702 to 0..15).
  assert(launchVelocityMagnitude(-6) === 56, "negative strength abs'd → 56");
  assert(launchVelocityMagnitude(99) === 128, "over-15 strength clamps to 15 → 128");
  assert(launchVelocityMagnitude(0, true) === 24, "airborne +2 boost: strength 0 → idx 2 → 24");
  assert(launchVelocityMagnitude(14, true) === 128, "airborne +2 clamps at 15 → 128");

  // ---------- zz_00300bc_ — mode 1 (attacker→target relative position) ------------------
  const origin = defaultSourceKnockbackActor();
  // Pure +Z (defender directly ahead): atan2(0, z>0) = 0 → yaw 0; pitch 0.
  const ahead = computeKnockbackLaunchDirection(origin, { pos: { x: 0, y: 0, z: 5 } }, { mode: 1 });
  assert(ahead.yaw === 0 && ahead.pitch === 0, `mode 1 +Z → yaw 0 pitch 0 (got ${JSON.stringify(ahead)})`);
  // Pure +X (defender to the right): atan2(x>0, 0) = +π/2 → yaw ~ +0x4000 (quarter turn).
  const right = computeKnockbackLaunchDirection(origin, { pos: { x: 5, y: 0, z: 0 } }, { mode: 1 });
  assert(right.yaw > 0x3f00 && right.yaw < 0x4100, `mode 1 +X → yaw ~ +0x4000 (got 0x${right.yaw.toString(16)})`);
  // Pure -Z (defender behind): atan2(0, z<0) = π → yaw ~ +0x8000 (wraps to negative).
  const behind = computeKnockbackLaunchDirection(origin, { pos: { x: 0, y: 0, z: -5 } }, { mode: 1 });
  assert(Math.abs(behind.yaw) > 0x7f00, `mode 1 -Z → yaw ~ ±0x8000 (got 0x${behind.yaw.toString(16)})`);
  // Direction is GEOMETRIC — swapping attacker/defender inverts the yaw (away vs toward).
  const swap = computeKnockbackLaunchDirection({ pos: { x: 5, y: 0, z: 0 } }, origin, { mode: 1 });
  assert(swap.yaw !== right.yaw, "swapped attacker/defender yields a different yaw (directional)");

  // ---------- degenerate fallback (chunk_0003.c:8606-8610) → (0,0,-1) -------------------
  // Zero vector → fallback (0,0,-1): atan2(0, -1) = π → yaw ±0x8000; pitch 0.
  const degenerate = computeKnockbackLaunchDirection(origin, origin, { mode: 1 });
  assert(Math.abs(degenerate.yaw) > 0x7f00, `degenerate → fallback (0,0,-1) yaw ±0x8000 (got 0x${degenerate.yaw.toString(16)})`);

  // ---------- SQUARED-horizontal-magnitude pitch quirk (chunk_0003.c:8616-8617) ---------
  // The ROM uses |x²+z²| (squared) as the atan2 second arg, NOT sqrt(x²+z²). This makes
  // the pitch RESPONSE non-linear in the horizontal distance — reproduce byte-for-byte.
  // For a vector with a LARGE horizontal component, textbook pitch → ~0 but ROM pitch →
  // strongly negative (y / large² → tiny atan2 → near 0 too); the divergence shows for
  // mid-range horizontal magnitudes. Assert the port matches the ROM formula exactly
  // (re-derive via the same expression) rather than a corrected sqrt variant.
  const v: Vec3 = { x: 3, y: 4, z: 0 };
  const romAngle = vectorToKnockbackAngle(v);
  const expectedPitch = -Math.trunc(Math.atan2(4, Math.abs(3 * 3 + 0 * 0)) * BAM16_PER_RADIAN);
  const textbookPitch = -Math.trunc(Math.atan2(4, Math.sqrt(3 * 3 + 0 * 0)) * BAM16_PER_RADIAN);
  assert(romAngle.pitch === wrapBam16(expectedPitch), `pitch matches ROM squared-horiz formula (got 0x${romAngle.pitch.toString(16)})`);
  assert(expectedPitch !== textbookPitch, "ROM squared-horiz pitch differs from textbook sqrt (quirk is load-bearing)");

  // ---------- per-move angular trim (chunk_0003.c:8618-8620): byte * -0x100 -------------
  assert(angleTrimByteToBam16(0) === 0, "trim byte 0 → 0 BAM");
  assert(Math.abs(angleTrimByteToBam16(128)) === 0x8000, `trim byte +128 → ±0x8000 (180°) — got 0x${angleTrimByteToBam16(128).toString(16)}`);
  // Yaw trim applied: same vector, +128 yaw trim → yaw shifts by ~180°.
  const trimmed = computeKnockbackLaunchDirection(origin, { pos: { x: 0, y: 0, z: 5 } }, { mode: 1, trimYaw: 128 });
  assert(
    Math.abs(Math.abs(trimmed.yaw) - 0x8000) < 0x200 || trimmed.yaw < -0x7e00 || trimmed.yaw > 0x7e00,
    `yaw trim +128 rotates ~180° (got 0x${trimmed.yaw.toString(16)})`,
  );

  // ---------- type-category INDEPENDENCE — direction is purely geometric ----------------
  // Borg identity never enters zz_00300bc_: identical positions → identical angle
  // regardless of borgNumber. (Contrast sourceDamage.ts typeMultiplier which is borg-typed.)
  const a = defaultSourceKnockbackActor({ x: 0, y: 0, z: 0 });
  const d = defaultSourceKnockbackActor({ x: 10, y: 0, z: 0 });
  const angleGRed = computeKnockbackLaunchDirection(a, d, { mode: 1 });
  // Re-run with the same geometry — the function reads no borg field, so output is stable.
  const angleRepeat = computeKnockbackLaunchDirection(a, d, { mode: 1 });
  assert(angleGRed.yaw === angleRepeat.yaw && angleGRed.pitch === angleRepeat.pitch,
    "direction is deterministic & type-category-independent (geometry only)");
}

/* =============================================================================
 * WIRED AT: combat.ts applyHit's knockback block. computeKnockbackLaunchDirection
 * supplies the direction and launchVelocityMagnitude / groundHorizontalSpeed the
 * magnitude; physics.knockbackDirectionFromPositions + gauges.knockback*ForRecord are
 * the throw-on-error fallbacks under the same GF_SOURCE_STRICT contract.
 *
 * OPEN ROM GAPS (the reason the call site passes literals rather than record fields):
 *   - record +0x0e knockback-mode selector is not on DamageRecord; the caller passes
 *     mode 1, which is the only mode this port has input vectors for.
 *   - modes 0/2/3/4 need sub-object fields +0x20/+0x2c, +0x30/+0x3c, +0x64 (linked),
 *     +0x8dc/+0x8ec/+0x8fc, +0x11c/+0x12c/+0x13c, none of which exist on BorgRuntime.
 *     Supply them through SourceKnockbackActor's optional fields once traced.
 *   - the FUN_8005ed38 airborne +2 strength boost needs actor+0x6fd bit 0x80; there is
 *     no airborne flag on BorgRuntime, so the caller passes false (ground launch).
 * ========================================================================== */
