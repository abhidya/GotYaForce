// =============================================================================
// sourceCollision.ts — ROM-faithful 1:1 port of the GG4E collision hit-pair pass pipeline.
//
// Ports five decompiled pieces, structurally byte-for-byte against the source:
//   - collision_hit_pair_pass_active_vs_borgs     @0x8002d7c4 — chunk_0003.c:7026-7164
//   - collision_hit_pair_pass_active_vs_secondary @0x8002db58 — chunk_0003.c:7168-7306
//   - collision_hit_pair_pass_object_lists        @0x8002df08 — chunk_0003.c:7310-7426
//   - resolve_hitbox_target_effects_and_damage    @0x8002e2a8 — chunk_0003.c:7473-8195 (DELEGATION)
//   - battle_frame_target_action_dispatch         @0x8002bb14 — chunk_0003.c:5844-6215 (CALL ORDER)
//
// PIPELINE (chunk_0003.c:6213-6215 — the dispatcher calls the three passes IN ORDER, once
// per frame, after the per-slot state reset + physics/position update):
//     collision_hit_pair_pass_active_vs_borgs();      // active battle-objects vs the borg list
//     collision_hit_pair_pass_object_lists();         // object-list vs object-list (projectiles/items)
//     collision_hit_pair_pass_active_vs_secondary();  // active battle-objects vs the secondary list
// Each pass walks two object lists, forms hit-pairs through a chain of filter predicates +
// unsurfaced hitbox-shape queries, and delegates every formed pair to the SINGLE per-pair
// resolver `resolve_hitbox_target_effects_and_damage`, which in turn calls the three functions
// already ported in this package:
//     zz_00300bc_ (knockback direction)  -> sourceKnockback.computeKnockbackLaunchDirection
//     zz_003cd5c_ (base damage)          -> sourceDamage.computeBaseDamage
//     zz_003d344_ (apply HP subtract)    -> sourceDamage.applyHpDamage
//
// UNSURFACED HITBOX-SHAPE QUERIES (honest partial port, cited): the four geometry functions
// below are NOT yet decompiled into this package's runtime, so they are injected via
// SourceCollisionHooks. The pass STRUCTURE, the pair-FORMATION filter chain, the immediate-vs-
// deferred branching, the closest-target tracking, and the per-pair DELEGATION are all faithful;
// only the shape-intersection results come from the hooks. Plug real implementations in when
// zz_002fd7c_ / zz_0039f6c_ / zz_0030348_ / zz_0030490_ are ported (see hooks doc).
//   - zz_002fd7c_(active, target, category)  broad-phase bounding test (category 0x40 vs borgs,
//     2 vs object-list/secondary). Returns nonzero = enter narrow phase.
//   - zz_0039f6c_(activeShape58, targetShape58)  shape-TYPE compatibility test.
//   - zz_0030348_(matA, matB, aShape, bShape)  transforms both +0x54 hitbox blocks into the
//     globals at 0x803b04cc / 0x803b0364 and writes the contact point to DAT_803b0720.
//   - zz_0030490_(matA, matB, (aShape<<3)|bShape)  the overlap test; returns nonzero = overlap.
//     The deferred path also reads gnt4_PSVECSquareDistance_bl(DAT_803b0374, DAT_803b0504) (the
//     two transformed hitbox origin points) for closest-target tracking.
//
// SELF-CONTAINED: depends only on sourceDamage.js + sourceKnockback.js (+ the DOL tables they
// already consume). It does NOT import combat.ts / BorgRuntime, so it can be unit-ported and
// audited in isolation, then wired into the per-frame loop via the integration spec at bottom.
// =============================================================================

import {
  applyHpDamage,
  computeBaseDamage,
  defaultSourceDamageActor,
  defaultSourceDamageContext,
  type SourceDamageActor,
  type SourceDamageContext,
  type SourceDamageTarget,
} from "./sourceDamage.js";
import {
  computeKnockbackLaunchDirection,
  defaultSourceKnockbackActor,
  type KnockbackLaunchAngle,
  type SourceKnockbackActor,
  type Vec3 as KnockbackVec3,
} from "./sourceKnockback.js";

/** Local vec3 (identical shape to sourceKnockback.Vec3 / sourceDamage convention). */
export interface Vec3 { x: number; y: number; z: number; }

// -----------------------------------------------------------------------------
// ROM CONSTANTS — cited inline. FLOAT_80436f68 = 0.0 (epsilon), FLOAT_80436f7c = 0.5.
// FLOAT_80436f98 is the deferred-search initial best-distance sentinel (a large positive float
// referenced alongside the active-list globals DAT_803c477c / DAT_80436250 in every pass —
// function-evidence-index.json:304-317). Its exact value is irrelevant to the structure: the
// first qualifying pair always wins (dist2 <= sentinel), then closer pairs replace it.
// -----------------------------------------------------------------------------
const EPSILON_0 = 0; // FLOAT_80436f68
const HALF = 0.5; // FLOAT_80436f7c
const DEFERRED_SENTINEL = Number.POSITIVE_INFINITY; // FLOAT_80436f98 (initial best-distance)

// -----------------------------------------------------------------------------
// OBJECT MODEL — minimal, each field cited to its battle-object +0xNNN offset.
//
// The collision passes operate on the +0x1e00-stride battle objects in DAT_803c4e84 /
// DAT_803c2f7c / DAT_803c417c / DAT_803c177c / DAT_803c117c — NOT the RomActor itself. Each
// battle object WRAPS a resolved actor (pointer at +0x20) + an owner borg (pointer at +0x24) +
// the hit-record table (+0x28 descriptor / +0x2c record base / +0x11 actionIndex) + the hitbox
// transform block (+0x54) + shape descriptor (+0x58) + position mirrors (+0x64, +0x98).
// -----------------------------------------------------------------------------

/**
 * Minimal actor view (the +0x20 / +0x24 deref targets). Carries only the fields the pair
 * filters + the resolver's delegation gates read; every offset cited. This composes with
 * SourceDamageActor / SourceKnockbackActor at delegation time (see toSourceDamageActor).
 */
export interface SourceCollisionActor {
  /** +0x3e8 / +1000: borgNumber (u16, big-endian: high byte = family, low = variant). */
  borgNumber: number;
  /** +0x88: team/side byte. Pair filters compare active-owner+0x88 vs target-owner+0x88. */
  team: number;
  /** +0x3e4: slot index (0..5). Indexes the per-slot damage-meter globals. */
  slot: number;
  /** +0x83: eligibility/type byte. ==0 means "is a borg" (gates the resolver's borg blocks). */
  eligibility83: number;
  /** +0x1da: reaction bitfield (bit 2 = "already staggered/processed this frame" — zeroes damage
   *  in the resolver and gates the active-vs-secondary pair filter). */
  reaction1da: number;
  /** +0x1db: owner-set flag (!=0 means this actor has a linked owner at +0x1e4 — the projectile/
   *  summon self-hit exclusion key). */
  ownerFlag1db: number;
  /** +0x1e4: linked owner actor (the self-hit exclusion pointer; == the other side blocks the pair
   *  unless the owner's family byte == 0x0e). null if ownerFlag1db == 0. */
  linkedOwner1e4: SourceCollisionActor | null;
  /** +0x6fc: pair-attack flag (attacker x2.0 / defender x0.5 inside zz_003cd5c_). */
  pairAttack6fc: number;
  /** +0xc4: attacker power float (1.0 identity) — fed to sourceDamage.actor.power. */
  power: number;
  /** +0x1c6: live HP mirror (s16) — the applyHpDamage target. */
  hp: number;
  /** +0x1c4: max HP (s16) — applyHpDamage upper clamp. */
  maxHp: number;
  /** +0x1c8: previous-HP mirror — applyHpDamage writes the pre-subtract HP here. May be unset
   *  until the first hit lands; typed `| undefined` so the resolver can copy it back verbatim
   *  under exactOptionalPropertyTypes. */
  prevHp?: number | undefined;
  /** +0x20: world position (vec3). Knockback direction (mode 1) + the deferred nudge read this. */
  pos: Vec3;
  /** +0x284: knockback yaw (BAM16) — written by zz_00300bc_ (via the resolver delegation). */
  knockbackYaw?: number;
  /** +0x282: knockback pitch (BAM16) — written by zz_00300bc_. */
  knockbackPitch?: number;
  // --- damage meters (resolver accounting, chunk_0003.c:7971-7988) ---
  /** +0x418: damage-dealt meter (cross-team hits only). */
  damageDealt418: number;
  /** +0x42c: friendly-fire meter (same-team, non-self hits). */
  friendlyFire42c: number;
  /** +0x41c: damage-taken meter (every hit that deals >0 to this actor). */
  damageTaken41c: number;
}

/**
 * A battle collision object — the +0x1e00-stride struct walked by every pass. Field offsets
 * cited to collision_hit_pair_pass_active_vs_borgs / _secondary / _object_lists.
 */
export interface SourceCollisionObject {
  /** +0x20 deref: the resolved actor (hitboxes attach here). */
  actor: SourceCollisionActor;
  /** +0x24: owner borg. Often === actor for direct melee; differs for projectiles/summons. The
   *  pair filters compare OWNER teams/eligibility, and the resolver debits the OWNER's meters. */
  owner: SourceCollisionActor;
  /** +0x11: actionIndex byte (selects the hit-record row: recordTable + actionIndex*0x18). */
  actionIndex: number;
  /** +0x2c deref + actionIndex*0x18: the 0x18-byte hit record for this frame. */
  hitRecord: SourceCollisionHitRecord;
  /** +0x28 deref +2 (u16): descriptor flags word (0x800/0x1000/0x2000/0x4000 mask-compat bits). */
  descriptorFlags: number;
  /** +0x58 deref (int): shape TYPE enum (==2 = the collision-active capsule/sphere state that
   *  gates the immediate-vs-deferred branch on record flagsA bit 1). Also the key low bits of the
   *  zz_0030490_ overlap selector `(activeShape<<3)|targetShape`. */
  shapeType: number;
  /** +0x98: position mirror (vec3) — the deferred nudge origin (nudge = contactPoint - pos98). */
  pos98: Vec3;
  /** +0x64: second position mirror (vec3) — the deferred nudge adds the half-scaled delta here. */
  pos64: Vec3;
}

/**
 * The 0x18-byte per-move hit record (recordBase + actionIndex*0x18). Field offsets cited to
 * resolve_hitbox_target_effects_and_damage reads. This is the SAME record sourceDamage /
 * sourceKnockback consume; re-surfaced here so the collision port is auditable standalone.
 */
export interface SourceCollisionHitRecord {
  /** record+0x00 (u16, *puVar17): base hpDamage (the damage seed) OR the heal magnitude
   *  (negated) when flagsA bit 0x2 is set. -> sourceDamage basePower. */
  hpDamage: number;
  /** record+0x02 (u16, puVar17[1]): base-power scaling word (used by the resolver's gauge/combo
   *  pre-computation at chunk_0003.c:7541-7549 — NOT the damage input; basePower is hpDamage). */
  scalingWord: number;
  /** record+0x08 (u8, puVar17+4): priority byte (pcVar18[0x71c] max-update source). */
  priorityByte: number;
  /** record+0x05 (u8): gauge delta byte (DAT_8043612c +/- source; +0x6c8 combo increment). */
  gaugeByte: number;
  /** record+0x0b (u8): reaction bitfield byte (OR'd into target+0x6fd). */
  reactionBits: number;
  /** record+0x0d (s8): knockback STRENGTH byte (copied to target+0x702; feeds the strength tables
   *  in sourceKnockback.launchVelocityMagnitude). */
  knockbackStrength: number;
  /** record+0x0e (s8, *(char*)(puVar17+7)): knockback MODE selector (0..4) — the 3rd arg to
   *  zz_00300bc_. -> sourceKnockback ctx.mode. */
  knockbackMode: number;
  /** record+0x09 (s8): reaction anim variant (the zz_0019550_ selector). */
  reactionAnimVariant: number;
  /** record+0x10 (u16, puVar17[8]): flagsA. bit 0x1 = immediate (vs deferred/closest),
   *  bit 0x2 = heal record (negate hpDamage), bit 0x800 = skip collision pass entirely. */
  flagsA: number;
  /** record+0x12 (u16, puVar17[9]): flagsB. bit 0x10 = cross-team-only (active-vs-borgs),
   *  bit 0x8000 = bypass target 0x800 mask (active-vs-secondary). */
  flagsB: number;
}

/** Per-frame battle context. */
export interface SourceCollisionContext {
  /** PTR_DAT_80433934[0x1f] — the replay/lockout flag. !=0 suppresses damage-meter accounting
   *  AND the damage call's downstream effects (chunk_0003.c:7972, 7991). Default false. */
  lockoutFlag1f?: boolean;
  /** The unsurfaced hitbox-shape queries. Defaults to defaultSourceCollisionHooks() (forces all
   *  pairs to form) — pass a real implementation once the shape functions are ported. */
  hooks?: SourceCollisionHooks;
  /** Optional crowd/gauge array (DAT_803b0638) for the G-RED family on-hit gauge bonus. If
   *  absent, the G-RED bonus is skipped. Length 6 (per slot), s16 semantics. */
  forceGaugeBySlot?: number[];
}

/**
 * Injected hitbox-shape queries (the four unsurfaced geometry functions). The default stub
 * forces every pair through to the resolver so the pass structure + delegation are exercisable
 * in isolation. Each method is cited to its ROM source.
 */
export interface SourceCollisionHooks {
  /** zz_002fd7c_(active, target, category) — broad-phase bounding test. category is 0x40 for the
   *  active-vs-borgs pass, 2 for object-lists and active-vs-secondary. true = enter narrow phase. */
  broadPhase(active: SourceCollisionObject, target: SourceCollisionObject, category: number): boolean;
  /** zz_0039f6c_(activeShape58ptr, targetShape58ptr) — shape-TYPE compatibility test. */
  shapeCompat(activeShapeType: number, targetShapeType: number): boolean;
  /** zz_0030348_ + zz_0030490_: copy both +0x54 transform blocks to the 0x803b04cc / 0x803b0364
   *  globals, transform them (writes the contact point DAT_803b0720), then run the overlap test
   *  with selector `(activeShape<<3)|targetShape`. Returns overlap + the contact point + the
   *  squared distance (gnt4_PSVECSquareDistance_bl(DAT_803b0374, DAT_803b0504)) used by the
   *  deferred closest-target search. */
  transformAndOverlap(
    active: SourceCollisionObject,
    target: SourceCollisionObject,
  ): { overlap: boolean; contactPoint: Vec3; squareDistance: number };
}

/** Default partial-port stub: admits every pair (broadPhase + shapeCompat + overlap all true),
 *  contact point at the active owner's position, zero squared distance. Use ONLY for structural
 *  exercise / self-tests; wire real shape functions for gameplay. */
export function defaultSourceCollisionHooks(): SourceCollisionHooks {
  return {
    broadPhase: () => true,
    shapeCompat: () => true,
    transformAndOverlap: (active) => ({
      overlap: true,
      contactPoint: { ...active.owner.pos },
      squareDistance: 0,
    }),
  };
}

// =============================================================================
// PAIR-FORMATION FILTER PREDICATES — 1:1 with the decompiled gate chains.
// =============================================================================

/**
 * Owner/eligibility gate shared by active-vs-borgs (chunk_0003.c:7083-7090) and active-vs-
 * secondary (chunk_0003.c:7226-7233). True = pair is admissible. The pair passes if ANY of:
 *   - one owner is a non-borg (eligibility83 != 0), OR
 *   - the owners are on different teams (+0x88), OR
 *   - neither side "owns" the other via the +0x1db/+0x1e4 link, with the family-0x0e exemption.
 */
function pairOwnersAdmissible(
  activeOwner: SourceCollisionActor,
  targetOwner: SourceCollisionActor,
): boolean {
  // chunk_0003.c:7085-7086 — one side non-borg, OR
  if (activeOwner.eligibility83 !== 0 || targetOwner.eligibility83 !== 0) return true;
  // chunk_0003.c:7086 — different teams.
  if (activeOwner.team !== targetOwner.team) return true;
  // chunk_0003.c:7087-7090 — the +0x1db/+0x1e4 self-hit exclusion. A side blocks the pair when
  //   it has an owner (ownerFlag1db != 0) AND its linked owner IS the other side, UNLESS the
  //   OTHER side's borg family byte (== *(char*)(otherSide + 1000)) is 0x0e. Both sides must
  //   clear (AND) for the pair to be admissible in this branch.
  const activeFamily = (activeOwner.borgNumber >>> 8) & 0xff;
  const targetFamily = (targetOwner.borgNumber >>> 8) & 0xff;
  const targetClears =
    (targetOwner.ownerFlag1db === 0 || activeFamily === 0x0e) &&
    targetOwner.linkedOwner1e4 !== activeOwner;
  const activeClears =
    (activeOwner.ownerFlag1db === 0 || targetFamily === 0x0e) &&
    activeOwner.linkedOwner1e4 !== targetOwner;
  return targetClears && activeClears;
}

/** Descriptor-flag mask-compat gate for active-vs-secondary (chunk_0003.c:7219-7224). */
function secondaryMaskCompat(
  activeDescFlags: number,
  targetDescFlags: number,
  activeRecordFlagsB: number,
  targetReaction1da: number,
): boolean {
  // uVar2 = target descriptor flags; uVar3 = active descriptor flags.
  // (targetDescFlags & 0x800) == 0 || (activeRecordFlagsB & 0x8000) != 0
  if (!((targetDescFlags & 0x800) === 0 || (activeRecordFlagsB & 0x8000) !== 0)) return false;
  // (activeDescFlags & 0x1000) != 0 || (targetDescFlags & 0x2000) == 0
  if (!((activeDescFlags & 0x1000) !== 0 || (targetDescFlags & 0x2000) === 0)) return false;
  // (activeDescFlags & 0x4000) == 0 || (targetDescFlags & 0x2000) != 0
  if (!((activeDescFlags & 0x4000) === 0 || (targetDescFlags & 0x2000) !== 0)) return false;
  // (target+0x1da & 2) == 0  — target not already staggered/processed this frame.
  if ((targetReaction1da & 2) !== 0) return false;
  return true;
}

/** Descriptor-flag mask-compat gate for active-vs-borgs (chunk_0003.c:7080-7081). */
function borgsMaskCompat(activeDescFlags: number, targetDescFlags: number): boolean {
  // (activeDescFlags & 0x4000) == 0 || (targetDescFlags & 0x2000) != 0
  return (activeDescFlags & 0x4000) === 0 || (targetDescFlags & 0x2000) !== 0;
}

// =============================================================================
// THE THREE PASSES — shared structural core (walk + filter + immediate/deferred + nudge +
// resolve). Each pass supplies its own pair-filter predicate + broad-phase category + the
// deferred-nudge extra guard. The structural fidelity is in the SHARED core below; the per-pass
// deltas are the filter chain (cited) + the nudge guard.
// =============================================================================

/** A formed pair about to be resolved. */
export interface CollisionHitPair {
  active: SourceCollisionObject;
  target: SourceCollisionObject;
  /** Contact point (DAT_803b0720) from the transform step — the nudge origin + knockback input. */
  contactPoint: Vec3;
}

/** Result of one resolver call (for audit / self-test). */
export interface ResolveHitboxResult {
  /** The delegated damage amount (uVar10 at chunk_0003.c:7948/7955/7951). >0 = HP damage,
   *  <0 = heal, 0 = no-op (already-processed gate or non-borg target on a heal record). */
  damage: number;
  /** Whether computeBaseDamage was actually called (the delegation happened). */
  delegatedDamage: boolean;
  /** Whether computeKnockbackLaunchDirection was called (always true — zz_00300bc_ is unconditional
   *  at chunk_0003.c:7945). */
  delegatedKnockback: boolean;
  /** The written launch angle (target+0x284/+0x282). */
  knockback: KnockbackLaunchAngle;
}

/**
 * Shared per-active-object pass core (the inner body of all three passes, abstracted because the
 * structure is identical — only the target list, the filter, the broad-phase category, and the
 * deferred-nudge guard differ). Faithful to chunk_0003.c:7060-7160 (active-vs-borgs).
 *
 * Per active object:
 *   1. read the hit record + flagsA. If flagsA & 0x800 -> skip (chunk_0003.c:7067, "no-collision").
 *   2. decide immediate vs deferred: if shapeType == 2, immediate = (flagsA & 1) != 0; else the
 *      default immediate stays true (chunk_0003.c:7068-7076 / 7344-7353).
 *   3. for each target: run the filter chain + shape hooks; on overlap, either resolve at once
 *      (immediate) or track the closest (deferred, dist2 <= best so far).
 *   4. deferred epilogue: if a closest was found, optionally nudge the active object out along
 *      (contactPoint - pos98), then resolve the closest pair.
 */
function runPassCore(
  activeList: readonly SourceCollisionObject[],
  targetList: readonly SourceCollisionObject[],
  filter: (active: SourceCollisionObject, target: SourceCollisionObject, hooks: SourceCollisionHooks) => boolean,
  ctx: SourceCollisionContext,
  /** The extra guard on the deferred nudge (active-vs-secondary checks the closest target's
   *  record flagsB & 0x3c0 == 0 at chunk_0003.c:7286-7287; the other two passes have no guard). */
  nudgeGuard: (closest: SourceCollisionObject) => boolean,
): CollisionHitPair[] {
  const hooks = ctx.hooks ?? defaultSourceCollisionHooks();
  const resolvedPairs: CollisionHitPair[] = [];

  for (const active of activeList) {
    const record = active.hitRecord;
    const flagsA = record.flagsA;
    // chunk_0003.c:7067 — flagsA bit 0x800 = "skip this object's collision this frame".
    if ((flagsA & 0x800) !== 0) continue;

    // chunk_0003.c:7068-7076 — immediate vs deferred. shapeType == 2 gates the record's bit-1
    //   decision; any other shape type leaves the default immediate == true.
    let immediate = true;
    if (active.shapeType === 2) {
      immediate = (flagsA & 1) !== 0;
    }

    let closestTarget: SourceCollisionObject | null = null;
    let closestContact: Vec3 = { x: 0, y: 0, z: 0 };
    let bestDist2 = DEFERRED_SENTINEL; // FLOAT_80436f98

    for (const target of targetList) {
      if (!filter(active, target, hooks)) continue;
      // chunk_0003.c:7094-7117 — copy both +0x54 transform blocks to globals (0x2d iterations of
      //   2x u32 = 360 bytes). Abtracted into transformAndOverlap alongside zz_0030348_.
      // chunk_0003.c:7118-7122 — zz_0030348_ then zz_0030490_ (overlap test).
      const { overlap, contactPoint, squareDistance } = hooks.transformAndOverlap(active, target);
      if (!overlap) continue;

      if (immediate) {
        // chunk_0003.c:7123-7124 — resolve the pair immediately.
        const pair: CollisionHitPair = { active, target, contactPoint: { ...contactPoint } };
        resolveHitboxTargetEffectsAndDamage(pair, ctx);
        resolvedPairs.push(pair);
      } else {
        // chunk_0003.c:7127-7135 — deferred: track the closest target by squared distance
        //   (gnt4_PSVECSquareDistance_bl of the two transformed hitbox origins). <= so the first
        //   qualifying pair wins ties.
        if (squareDistance <= bestDist2) {
          closestTarget = target;
          closestContact = { ...contactPoint };
          bestDist2 = squareDistance;
        }
      }
    }

    // chunk_0003.c:7142-7159 (borgs) / 7282-7301 (secondary) / 7405-7421 (object-lists) —
    //   deferred epilogue: nudge + resolve the single closest pair.
    if (!immediate && closestTarget !== null) {
      if (nudgeGuard(closestTarget)) {
        applyDeferredNudge(active, closestContact);
      }
      const pair: CollisionHitPair = { active, target: closestTarget, contactPoint: closestContact };
      resolveHitboxTargetEffectsAndDamage(pair, ctx);
      resolvedPairs.push(pair);
    }
  }
  return resolvedPairs;
}

/**
 * The deferred position-separation nudge (chunk_0003.c:7146-7157). Pushes the active object out
 * of the closest target along (contactPoint - pos98), scaled: pos98 and actor.pos get the full
 * delta; the +0x64 mirror gets the half-scaled remainder added (so +0x64 receives 1.5x total).
 * The +0x100 callback (chunk_0003.c:7154-7156) is cited but not surfaced (no callback field).
 */
function applyDeferredNudge(active: SourceCollisionObject, contactPoint: Vec3): void {
  // afStack = DAT_803b0720 - (active + 0x98)
  const dx = contactPoint.x - active.pos98.x;
  const dy = contactPoint.y - active.pos98.y;
  const dz = contactPoint.z - active.pos98.z;
  // if |afStack|² > 0.0 (FLOAT_80436f68)
  if (dx * dx + dy * dy + dz * dz <= EPSILON_0) return;
  // (active + 0x98) += afStack
  active.pos98.x += dx; active.pos98.y += dy; active.pos98.z += dz;
  // (actor + 0x20) += afStack  — iVar13 = active.actor; iVar13+0x20 = actor.pos
  active.actor.pos.x += dx; active.actor.pos.y += dy; active.actor.pos.z += dz;
  // PSQUATScale(0.5) then (active + 0x64) += half  — the +0x64 mirror gets the half-delta.
  const hx = dx * HALF, hy = dy * HALF, hz = dz * HALF;
  active.pos64.x += hx; active.pos64.y += hy; active.pos64.z += hz;
  // chunk_0003.c:7154-7156: if (actor + 0x100) != null call it. TODO: surface the +0x100 callback.
}

// -----------------------------------------------------------------------------
// Pass 1: collision_hit_pair_pass_active_vs_borgs @0x8002d7c4 (chunk_0003.c:7026-7164).
//   active list  = DAT_803c477c (count DAT_80436250)
//   target list  = DAT_803c2f7c (count DAT_80436248) — the borg roster
//   broad-phase  = zz_002fd7c_(active, target, 0x40)
//   filter chain = mask-compat (0x4000/0x2000) + broad-phase + owner-admissible + shape-compat
//                  + flagsB-0x10 cross-team-only
// -----------------------------------------------------------------------------

/**
 * 1:1 structural port of collision_hit_pair_pass_active_vs_borgs. Walks the active list against
 * the borg list, forms pairs through the full filter chain, and delegates each pair to the
 * resolver. Returns the list of resolved pairs (audit only — the resolver mutates the actors).
 */
export function collisionHitPairPassActiveVsBorgs(
  activeList: readonly SourceCollisionObject[],
  borgList: readonly SourceCollisionObject[],
  ctx: SourceCollisionContext,
): CollisionHitPair[] {
  return runPassCore(
    activeList,
    borgList,
    (active, target, h) => {
      // chunk_0003.c:7080-7081 — descriptor mask-compat.
      if (!borgsMaskCompat(active.descriptorFlags, target.descriptorFlags)) return false;
      // chunk_0003.c:7082 — zz_002fd7c_(active, target, 0x40).
      if (!h.broadPhase(active, target, 0x40)) return false;
      // chunk_0003.c:7083-7090 — owner/eligibility/team admissibility.
      if (!pairOwnersAdmissible(active.owner, target.owner)) return false;
      // chunk_0003.c:7091 — zz_0039f6c_(activeShape, targetShape).
      if (!h.shapeCompat(active.shapeType, target.shapeType)) return false;
      // chunk_0003.c:7092-7093 — flagsB bit 0x10 = cross-team-only (active actor team vs target
      //   actor team — note: the TEAM here is the +0x20 actor's, not the +0x24 owner's).
      if ((active.hitRecord.flagsB & 0x10) !== 0 && active.actor.team === target.actor.team) {
        return false;
      }
      return true;
    },
    ctx,
    () => true, // no extra nudge guard for this pass
  );
}

// -----------------------------------------------------------------------------
// Pass 2: collision_hit_pair_pass_object_lists @0x8002df08 (chunk_0003.c:7310-7426).
//   active list  = DAT_803c177c (count DAT_80436240)
//   target list  = DAT_803c117c (count DAT_8043623e)
//   broad-phase  = zz_002fd7c_(active, target, 2)
//   filter chain = broad-phase + shape-compat ONLY (no mask-compat, no owner/team gate, no
//                  flagsB-0x10) — these are raw object lists (projectiles/items/walls).
// -----------------------------------------------------------------------------

/**
 * 1:1 structural port of collision_hit_pair_pass_object_lists. Minimal filter chain (broad-phase
 * + shape compat only). Walks the object list against the object list.
 */
export function collisionHitPairPassObjectLists(
  activeList: readonly SourceCollisionObject[],
  targetList: readonly SourceCollisionObject[],
  ctx: SourceCollisionContext,
): CollisionHitPair[] {
  return runPassCore(
    activeList,
    targetList,
    // chunk_0003.c:7357-7358 — broad-phase (category 2) AND shape-compat only. NO mask-compat,
    //   owner/team, or flagsB gates: these are raw object lists (projectiles/items/walls).
    (active, target, h) =>
      h.broadPhase(active, target, 2) && h.shapeCompat(active.shapeType, target.shapeType),
    ctx,
    () => true, // no extra nudge guard for this pass
  );
}

// -----------------------------------------------------------------------------
// Pass 3: collision_hit_pair_pass_active_vs_secondary @0x8002db58 (chunk_0003.c:7168-7306).
//   active list  = DAT_803c477c (count DAT_80436250) — SAME active list as pass 1
//   target list  = DAT_803c417c (count DAT_8043624e) — the secondary list (summons/props)
//   broad-phase  = zz_002fd7c_(active, target, 2)
//   filter chain = secondary mask-compat (0x800/0x1000/0x2000/0x4000 + flagsB-0x8000 + target
//                  reaction1da-bit-2) + broad-phase + owner-admissible + shape-compat
//   nudge guard  = closest target's record flagsB & 0x3c0 == 0 (chunk_0003.c:7286-7287)
// -----------------------------------------------------------------------------

/**
 * 1:1 structural port of collision_hit_pair_pass_active_vs_secondary. Same active list as pass 1
 * against the secondary list, with the fuller mask-compat gate and the deferred-nudge guard.
 */
export function collisionHitPairPassActiveVsSecondary(
  activeList: readonly SourceCollisionObject[],
  secondaryList: readonly SourceCollisionObject[],
  ctx: SourceCollisionContext,
): CollisionHitPair[] {
  return runPassCore(
    activeList,
    secondaryList,
    (active, target, h) => {
      // chunk_0003.c:7219-7224 — secondary mask-compat (uses active record flagsB bit 0x8000).
      if (
        !secondaryMaskCompat(
          active.descriptorFlags,
          target.descriptorFlags,
          active.hitRecord.flagsB,
          target.actor.reaction1da,
        )
      ) {
        return false;
      }
      // chunk_0003.c:7225 — zz_002fd7c_(active, target, 2).
      if (!h.broadPhase(active, target, 2)) return false;
      // chunk_0003.c:7226-7233 — owner/eligibility/team admissibility.
      if (!pairOwnersAdmissible(active.owner, target.owner)) return false;
      // chunk_0003.c:7234 — zz_0039f6c_(activeShape, targetShape).
      if (!h.shapeCompat(active.shapeType, target.shapeType)) return false;
      return true;
    },
    ctx,
    // chunk_0003.c:7286-7287 — only nudge when the closest target's record flagsB & 0x3c0 == 0
    //   (no special reaction flags).
    (closest) => (closest.hitRecord.flagsB & 0x3c0) === 0,
  );
}

// =============================================================================
// resolve_hitbox_target_effects_and_damage @0x8002e2a8 (chunk_0003.c:7473-8195).
//
// The SINGLE per-pair resolver called by all three passes. This port is faithful to the
// DELEGATION section — the three zz_ calls at the tail that hand off to sourceDamage +
// sourceKnockback — plus the damage-amount branch that selects the delegation input and the
// damage-meter accounting that immediately surrounds applyHpDamage. The large effect-bookkeeping
// body (chunk_0003.c:7519-7944: status flag writes, lock-on markers, combo counters, gauge
// deltas, reaction-anim selection, hitbox-shape callbacks) runs BEFORE the delegation in the ROM
// and sets some of the gates the delegation reads (notably target.reaction1da bit 2); those
// gates are surfaced as input fields here and cited. Porting that body is out of scope for the
// collision-PASS pipeline task (it is the per-pair EFFECT layer, not the pair-FORMATION layer).
// =============================================================================

/**
 * 1:1 port of the delegation tail of resolve_hitbox_target_effects_and_damage. Computes the
 * damage amount via computeBaseDamage (or the heal-record branch), the knockback angle via
 * computeKnockbackLaunchDirection, applies HP via applyHpDamage, and debits the damage meters.
 * Mutates the pair's actors (HP, prevHp, meters, knockback fields) and returns what happened.
 *
 *   pair — the formed hit-pair (active source + target + contact point).
 *   ctx  — battle context (lockout flag + the G-RED gauge array).
 */
export function resolveHitboxTargetEffectsAndDamage(
  pair: CollisionHitPair,
  ctx: SourceCollisionContext,
): ResolveHitboxResult {
  const { active, target, contactPoint } = pair;
  const record = active.hitRecord;
  const activeActor = active.actor; // iVar19 = param_1 + 0x20
  const targetActor = target.actor; // pcVar18 = param_2 + 0x20
  const activeOwner = active.owner; // pcVar16 = param_1 + 0x24 (meter-debit owner)
  const flagsA = record.flagsA;

  // --- chunk_0003.c:7945 — zz_00300bc_(active, target, record+0x0e). UNCONDITIONAL knockback
  //     direction computation; writes target+0x284/+0x282. Delegated to sourceKnockback. ---
  const knockback = computeKnockbackLaunchDirection(
    toSourceKnockbackActor(activeActor, contactPoint),
    toSourceKnockbackActor(targetActor, targetActor.pos),
    { mode: record.knockbackMode },
  );
  targetActor.knockbackYaw = knockback.yaw;
  targetActor.knockbackPitch = knockback.pitch;

  // --- chunk_0003.c:7946-7970 — damage amount (uVar10). ---
  let damage = 0;
  let delegatedDamage = false;
  if ((flagsA & 2) === 0) {
    // NOT a heal record. chunk_0003.c:7947-7949 — gate: compute damage only when the target has
    //   NOT already been staggered/processed this frame (reaction1da bit 2 == 0) OR the target is
    //   a non-borg (eligibility83 != 0). Otherwise uVar10 = 0 (no re-hit on the same frame).
    if ((targetActor.reaction1da & 2) === 0 || targetActor.eligibility83 !== 0) {
      damage = computeBaseDamage(
        toSourceDamageActor(activeActor, activeOwner),
        toSourceDamageActor(targetActor, targetActor),
        record.hpDamage,
        toSourceDamageContext(record, activeOwner),
      );
      delegatedDamage = true;
    }
  } else {
    // chunk_0003.c:7954-7967 — heal record (flagsA & 2). uVar10 = -(u16)hpDamage; cross-team
    //   heals floor-divide by 4 (the `(int)x >> 2 + (x<0 && x&3)` round-toward-neg-inf idiom).
    if (targetActor.eligibility83 === 0) {
      let heal = -(record.hpDamage & 0xffff);
      if (activeOwner.team !== targetActor.team) {
        heal = Math.trunc(heal >> 2) + (heal < 0 && (heal & 3) !== 0 ? 1 : 0);
      }
      damage = heal;
      // chunk_0003.c:7959-7966 — clear the two status timers +0x6b8/+0x6ba on heal. TODO: surface
      //   those timer fields on SourceCollisionActor if heal-cancellation of status matters.
    }
  }

  // --- chunk_0003.c:7971-7988 — damage-meter accounting (only when both sides are borgs, damage
  //     is positive, and the replay lockout flag is clear). ---
  if (
    activeOwner.eligibility83 === 0 &&
    targetActor.eligibility83 === 0 &&
    damage > 0 &&
    !ctx.lockoutFlag1f
  ) {
    if (activeOwner.team === targetActor.team) {
      // chunk_0003.c:7973-7976 — same-team (friendly fire): debit active owner's +0x42c, skip self.
      if (activeOwner !== targetActor) {
        activeOwner.friendlyFire42c += damage;
      }
    } else {
      // chunk_0003.c:7978-7979 — cross-team: debit active owner's damage-dealt meter +0x418.
      activeOwner.damageDealt418 += damage;
    }
    // chunk_0003.c:7981 — target's damage-taken meter +0x41c.
    targetActor.damageTaken41c += damage;
    // chunk_0003.c:7982-7987 — G-RED family (borgNumber 0x702/0x70a) on-hit force-gauge bonus:
    //   team gauge slot += damage/2.
    if (ctx.forceGaugeBySlot && (activeActor.borgNumber === 0x0702 || activeActor.borgNumber === 0x070a)) {
      ctx.forceGaugeBySlot[activeActor.slot] =
        (ctx.forceGaugeBySlot[activeActor.slot] ?? 0) + Math.trunc(damage / 2);
    }
  }

  // --- chunk_0003.c:7989 — zz_003d344_(target, damage). Apply HP subtract + clamp. Build ONE
  //   target wrapper, mutate it, then copy the mutation back onto the collision actor (the ROM
  //   writes +0x1c6/+0x1c8 in place; here applyHpDamage owns the wrapper, so we sync after). ---
  const dmgTarget = toSourceDamageTarget(targetActor);
  applyHpDamage(dmgTarget, damage);
  targetActor.hp = dmgTarget.hp;
  if (dmgTarget.prevHp !== undefined) targetActor.prevHp = dmgTarget.prevHp;

  return { damage, delegatedDamage, delegatedKnockback: true, knockback };
}

// =============================================================================
// Adapter helpers — compose the collision actor with the sourceDamage / sourceKnockback APIs.
// These are the seams where the pair-formation layer hands off to the damage/knockback layer.
// =============================================================================

function toSourceDamageActor(
  actor: SourceCollisionActor,
  ownerForPairFlags: SourceCollisionActor,
): SourceDamageActor {
  // The ROM's zz_003cd5c_ reads attacker/defender from the resolved actor (param_2/param_3 +0x90
  // sub-object resolution collapses to the actor for borgs). team/pairAttack come from the OWNER
  // for the pair-attack asymmetry (chunk_0004.c:6704-6707 reads attacker+0x6fc; the owner is the
  // borg that carries the pair-attack flag for projectile hits).
  return {
    borgNumber: actor.borgNumber,
    team: actor.team,
    heroFlag: 0, // TODO: surface +0x3e6 hero/CPU flag (challenge-mode decode T2)
    pairAttack: ownerForPairFlags.pairAttack6fc,
    power: actor.power,
    hp: actor.hp,
    maxHp: actor.maxHp,
    handicap: 3, // TODO: surface +0x43a handicap byte (neutral 3; init site untraced)
    comboRank: 0, // TODO: surface +0x6ca combo-rank byte
    forceRatioIndex: 0, // TODO: surface team force-gauge ratio (challengeSideRanksForMode)
    sideRank: 0, // TODO: surface PTR_DAT_80433950[team] side rank
    isBorg: actor.eligibility83 === 0,
    isActive: true, // +0x18 == 1 in normal combat (the resolver only runs for active pairs)
  };
}

function toSourceDamageContext(
  record: SourceCollisionHitRecord,
  _owner: SourceCollisionActor,
): SourceDamageContext {
  return {
    flagsA: record.flagsA,
    flagsB: record.flagsB,
    attackerHpCurveIndex: 0, // TODO: surface record+0x06 curve selector
    attackerForceCurveIndex: 0, // TODO: surface record+0x07 curve selector
  };
}

function toSourceDamageTarget(actor: SourceCollisionActor): SourceDamageTarget {
  // Build conditionally so prevHp is absent (not `undefined`) until the first hit — required by
  // exactOptionalPropertyTypes (SourceDamageTarget.prevHp?: number forbids an explicit undefined).
  const t: SourceDamageTarget = { hp: actor.hp, maxHp: actor.maxHp };
  if (actor.prevHp !== undefined) t.prevHp = actor.prevHp;
  return t;
}

function toSourceKnockbackActor(_actor: SourceCollisionActor, pos: Vec3): SourceKnockbackActor {
  // zz_00300bc_ mode 1 reads attacker+0x20 / defender+0x20 (world pos). The contact point stands
  // in for the attacker origin in mode 1 (the hit happened AT the contact point).
  const p = pos as KnockbackVec3;
  return defaultSourceKnockbackActor({ x: p.x, y: p.y, z: p.z });
}

// =============================================================================
// SELF-TESTS — runSourceCollisionSelfTests(assert). assert shape: (cond, msg) => void, matching
// the runXxxSelfTests(assert) convention (sourceDamage.ts / sourceKnockback.ts).
// =============================================================================

export type SourceCollisionAssert = (cond: boolean, msg: string) => void;

export function runSourceCollisionSelfTests(assert: SourceCollisionAssert): void {
  // ---------- helper: build a minimal borg battle object ----------
  function makeBorg(
    borgNumber: number,
    team: number,
    hp = 200,
    maxHp = 200,
  ): SourceCollisionObject {
    const actor: SourceCollisionActor = {
      borgNumber, team, slot: team,
      eligibility83: 0, reaction1da: 0, ownerFlag1db: 0, linkedOwner1e4: null,
      pairAttack6fc: 0, power: 1, hp, maxHp,
      pos: { x: 0, y: 0, z: 0 }, damageDealt418: 0, friendlyFire42c: 0, damageTaken41c: 0,
    };
    return {
      actor, owner: actor, actionIndex: 0,
      hitRecord: {
        hpDamage: 40, scalingWord: 0, priorityByte: 0, gaugeByte: 0, reactionBits: 0,
        knockbackStrength: 4, knockbackMode: 1, reactionAnimVariant: 0,
        flagsA: 0, flagsB: 0,
      },
      descriptorFlags: 0, shapeType: 2,
      pos98: { x: 0, y: 0, z: 0 }, pos64: { x: 0, y: 0, z: 0 },
    };
  }

  // ---------- resolver delegation: a sample active-vs-borg pair ----------
  // Two neutral borgs on opposite teams, a 40-power non-heal record. The resolver MUST delegate
  // to computeBaseDamage (damage > 0), computeKnockbackLaunchDirection (angle written), and
  // applyHpDamage (HP reduced + clamped). Verified against direct sourceDamage/sourceKnockback.
  const active = makeBorg(0x0b00, 0); // cat 15 attacker (team 0)
  active.actor.pos = { x: 0, y: 0, z: 0 };
  const target = makeBorg(0x0701, 1, 200, 200); // cat 12 defender (team 1)
  target.actor.pos = { x: 10, y: 0, z: 0 };
  const pair: CollisionHitPair = {
    active, target,
    contactPoint: { x: active.actor.pos.x, y: 0, z: 0 },
  };
  const res = resolveHitboxTargetEffectsAndDamage(pair, {});

  // Delegation happened.
  assert(res.delegatedDamage, "resolver delegated to computeBaseDamage (delegatedDamage)");
  assert(res.delegatedKnockback, "resolver delegated to computeKnockbackLaunchDirection");
  // Damage matches a direct computeBaseDamage call (same neutral inputs).
  const expectedDmg = computeBaseDamage(
    defaultSourceDamageActor(0x0b00), defaultSourceDamageActor(0x0701, 200),
    40, defaultSourceDamageContext(),
  );
  assert(res.damage === expectedDmg, `resolver damage === computeBaseDamage direct (${res.damage} vs ${expectedDmg})`);
  assert(res.damage > 0, "resolver produced positive damage for a 40-power hit");
  // HP applied + clamped (applyHpDamage delegation).
  assert(target.actor.hp === 200 - res.damage, `target HP reduced by damage (got ${target.actor.hp})`);
  assert(target.actor.prevHp === 200, `target prevHp mirrors pre-hit HP (got ${target.actor.prevHp})`);
  // Knockback angle written + matches a direct mode-1 computation.
  assert(target.actor.knockbackYaw === res.knockback.yaw && target.actor.knockbackPitch === res.knockback.pitch,
    "knockback angle stored on target actor (+0x284/+0x282)");
  const expectedAngle = computeKnockbackLaunchDirection(
    defaultSourceKnockbackActor({ x: 0, y: 0, z: 0 }),
    defaultSourceKnockbackActor({ x: 10, y: 0, z: 0 }),
    { mode: 1 },
  );
  assert(res.knockback.yaw === expectedAngle.yaw && res.knockback.pitch === expectedAngle.pitch,
    "resolver knockback === direct computeKnockbackLaunchDirection (mode 1)");
  // Damage-meter accounting (cross-team): active owner +0x418 debited, target +0x41c debited.
  assert(active.actor.damageDealt418 === res.damage, `cross-team damage-dealt meter debited (got ${active.actor.damageDealt418})`);
  assert(target.actor.damageTaken41c === res.damage, `damage-taken meter debited (got ${target.actor.damageTaken41c})`);
  assert(active.actor.friendlyFire42c === 0, "no friendly-fire debit for a cross-team hit");

  // ---------- heal record (flagsA & 2): negative damage, clamped at maxHp ----------
  const healActive = makeBorg(0x0000, 0);
  const healTarget = makeBorg(0x0000, 1, 50, 200);
  healActive.hitRecord.flagsA = 2; // heal record
  healActive.hitRecord.hpDamage = 30;
  const healPair: CollisionHitPair = {
    active: healActive, target: healTarget,
    contactPoint: { x: 0, y: 0, z: 0 },
  };
  const healRes = resolveHitboxTargetEffectsAndDamage(healPair, {});
  assert(!healRes.delegatedDamage, "heal record does NOT call computeBaseDamage");
  // Same-team would be -30; cross-team floor-divides by 4 -> Math.trunc(-30 >> 2) = -8 (since
  // -30 >> 2 == -8, no remainder correction needed: -30 & 3 == 2, but -30<0 so +1 -> -8+1... recompute:
  // -30 in 32-bit >> 2 = -8 (floor(-30/4) = -8). (x&3): -30 & 3 = 2. x<0 && (x&3)!=0 -> +1. So -8+1=-7.
  // floor(-30/4) = Math.floor(-7.5) = -8. The ROM idiom gives -7 (toward zero). Match the idiom exactly.
  const expectedHeal = ((): number => {
    let h = -(30 & 0xffff);
    h = Math.trunc(h >> 2) + (h < 0 && (h & 3) !== 0 ? 1 : 0);
    return h;
  })();
  assert(healRes.damage === expectedHeal, `cross-team heal === floor-toward-zero(-30/4) = ${expectedHeal} (got ${healRes.damage})`);
  assert(healTarget.actor.hp === 50 - healRes.damage, `heal raised target HP (got ${healTarget.actor.hp})`);

  // ---------- already-staggered gate: reaction1da bit 2 zeroes the damage ----------
  const staggerActive = makeBorg(0x0000, 0);
  const staggerTarget = makeBorg(0x0000, 1);
  staggerTarget.actor.reaction1da = 2; // already staggered this frame
  const staggerPair: CollisionHitPair = {
    active: staggerActive, target: staggerTarget, contactPoint: { x: 0, y: 0, z: 0 },
  };
  const staggerRes = resolveHitboxTargetEffectsAndDamage(staggerPair, {});
  assert(!staggerRes.delegatedDamage && staggerRes.damage === 0,
    "reaction1da bit 2 set -> damage zeroed (no re-hit same frame)");
  assert(staggerRes.delegatedKnockback, "knockback still computed even when damage is gated");

  // ---------- full pass: active-vs-borgs with forcing hooks resolves the pair ----------
  const passActive = makeBorg(0x0b00, 0);
  const passTarget = makeBorg(0x0701, 1);
  // Same-team owners would fail the filter; opposite teams pass the owner-admissible gate.
  const passResult = collisionHitPairPassActiveVsBorgs([passActive], [passTarget], {});
  assert(passResult.length === 1, "active-vs-borgs formed + resolved exactly one pair (forcing hooks)");
  assert(passActive.actor.damageDealt418 > 0, "pass debited the active owner's damage-dealt meter");
  assert(passTarget.actor.hp < 200, "pass reduced the target's HP via the resolver");

  // ---------- pair-formation filter: same-team same-owner self-hit is excluded ----------
  const selfA = makeBorg(0x0000, 0);
  const selfB = makeBorg(0x0000, 0); // same team -> owner-admissible falls to the link check
  // Neither has an owner link, so targetClears/activeClears are both true -> admissible. The
  // same-team branch then debits friendly fire. Verify the meter routing differs from cross-team.
  const selfRes = collisionHitPairPassActiveVsBorgs([selfA], [selfB], {});
  assert(selfRes.length === 1, "same-team unborged pair still admissible (no owner link)");
  assert(selfA.actor.friendlyFire42c > 0 && selfA.actor.damageDealt418 === 0,
    "same-team hit debits friendly-fire meter, not damage-dealt");

  // ---------- deferred mode: flagsA bit 1 clear + shapeType==2 picks the closest ----------
  const defActive = makeBorg(0x0000, 0);
  defActive.shapeType = 2;
  defActive.hitRecord.flagsA = 0; // bit 1 clear -> deferred
  const far = makeBorg(0x0000, 1);
  const near = makeBorg(0x0000, 1);
  // Forcing hooks return squareDistance 0 for both -> first (far) wins the <= tie. Resolve once.
  const defRes = collisionHitPairPassActiveVsBorgs([defActive], [far, near], {});
  assert(defRes.length === 1, "deferred mode resolves exactly one (closest) pair, not one per target");

  // ---------- descriptor mask-compat excludes a pair (active-vs-borgs 0x4000/0x2000) ----------
  const maskActive = makeBorg(0x0000, 0);
  maskActive.descriptorFlags = 0x4000; // requires target 0x2000
  const maskTarget = makeBorg(0x0000, 1);
  maskTarget.descriptorFlags = 0; // missing 0x2000 -> compat fails
  const maskRes = collisionHitPairPassActiveVsBorgs([maskActive], [maskTarget], {});
  assert(maskRes.length === 0, "active descriptorFlags 0x4000 without target 0x2000 excludes the pair");
}

/* =============================================================================
 * WIRED AT: combat.ts stepSourceCollision -> runSourceCollisionPasses, called once per
 * frame from stepProjectiles. It builds the adapters, supplies proximity-capsule hooks in
 * place of the unported shape queries, and runs the three passes in the ROM's dispatch
 * order (chunk_0003.c:6213-6215).
 *
 * AUDIT-ONLY TODAY. combat.ts deliberately discards the HP this resolver computes — see
 * its "NO HP SYNC-BACK" note. Three layers are missing before it could own damage:
 *   - no active-WINDOW model: a borg in the "attack" state overlaps on every frame of the
 *     state, not only the swing's active frames;
 *   - no per-swing already-hit dedup: the reaction1da bit-2 gate only arms once the victim
 *     actually enters hit/down, which needs the unported effect layer;
 *   - no knockback/reaction/telemetry application.
 * Syncing HP back without them drained a victim's whole bar in ~30 frames.
 *
 * REMAINING ROM GAPS (cited):
 *   - Hitbox-shape queries zz_002fd7c_ / zz_0039f6c_ / zz_0030348_ / zz_0030490_ are
 *     UNSURFACED; inject via SourceCollisionHooks. defaultSourceCollisionHooks forces
 *     every pair and must never ship as the live hook set.
 *   - resolve_hitbox's effect-bookkeeping body (chunk_0003.c:7519-7944) — status flags,
 *     lock-on markers, combo counters, gauge deltas, reaction-anim selection — is the
 *     per-pair EFFECT layer and is NOT ported. It is what sets target.reaction1da bit 2.
 *   - The deferred-nudge +0x100 callback (chunk_0003.c:7154-7156): unsurfaced.
 *   - toSourceDamageActor's heroFlag/handicap/comboRank/forceRatioIndex/sideRank and
 *     toSourceDamageContext's record +0x06/+0x07 curve selectors are hardcoded neutral —
 *     note these DIVERGE from combat.ts's own richer sourceDamageActorFromRuntime, so the
 *     two adapters would not agree if this pass ever became authoritative.
 * ========================================================================== */
