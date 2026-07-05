// Gauge-based stagger data — the original's per-borg balance/down gauge init values and the
// per-hit 0x18-stride damage-record table, both extracted from the ROM (see the JSON files'
// own "provenance" blocks and research/decomp/data/*).
//
// DERIVED mechanism (the reason this module exists): Gotcha Force has NO flat per-hit hitstun.
// A hit interrupts the victim ONLY when (a) the victim's down gauge (+0x6c6) drops below 1,
// (b) the balance gauge (+0x6c2) is depleted (flag bits 0x6fd |= 0xa6 -> forced stagger), or
// (c) the move's damage-record reaction flags (byte +0x0b, bits 2|0x80) force it. Otherwise
// the victim keeps acting normally — chunk_0003.c:6255-6263 routes non-staggering hits
// straight to dispatch_slot_action_update with no state change.

import gaugeInitData from "./data/gaugeInit.json" with { type: "json" };
import damageRecordsData from "./data/damageRecords.json" with { type: "json" };

/** Per-borg gauge init values (chunk_0007.c:47-52): u16[0]/u16[1] of the borg's pl####data.bin. */
export interface BorgGaugeInit {
  /** Balance gauge max AND initial value (+0x6be/+0x6c2). VERIFIED per-borg data. */
  balanceGaugeMax: number;
  /** Down gauge base AND initial value (+0x6c4/+0x6c6). VERIFIED per-borg data. */
  downGaugeBase: number;
}

type GaugeInitFile = {
  provenance: Record<string, string>;
  borgs: Record<string, BorgGaugeInit>;
};

/**
 * One 0x18-stride damage record from the borg-family table DAT_802d46e0 (bound to borg actors
 * via actor+0x27c by zz_0072048_ @0x80072048, chunk_0010.c:139). Field offsets/consumers are
 * cited in the JSON's provenance block (hit-bin agent census; chunk_0003.c/chunk_0004.c).
 */
export interface DamageRecord {
  index: number;
  /** u16 +0x00 — HP damage consumed by damageFormula.ts / zz_003cd5c_ port. */
  hpDamage: number;
  /** u16 +0x02 — down-gauge damage, scaled x(1+0.5*(attackerLevel-1)); level 0/1 -> x1. */
  downGaugeDamage: number;
  /** u8 +0x04 — balance-gauge damage. */
  balanceGaugeDamage: number;
  /** u8 +0x05 — combo score added to the victim's combo accumulator (+0x6c8, clamped 0-99). */
  comboScoreValue: number;
  /** u8 +0x06 — attacker HP-ratio curve selector. */
  attackerHpCurveIndex: number;
  /** u8 +0x07 — attacker force-gauge curve selector. */
  forceGaugeCurveIndex: number;
  /**
   * u8 +0x08 — hit-strength byte (status-effects-decode-2026-07-04.md §A/report field
   * "hitStrength"; NOT the knockback-strength byte, see reactionAnimVariant +0x0d below for
   * that one). On a normal-reaction hit ((flagsB & 0xfc0) === 0), this is the freeze/hitstop
   * frame count max-merged onto BOTH attacker and victim's `freezeFrames` (chunk_0003.c:
   * 7621-7625, 7633-7640).
   */
  hitStrength: number;
  /**
   * u8 +0x09 — impactEffectId: contact-effect selector (DERIVED, research/decomp/
   * impact-effect-id-decode-2026-07-04.md). resolve_hitbox_target_effects_and_damage gates
   * the impact-spark spawn on this byte != 0xff (chunk_0003.c:8087) and passes it to
   * zz_0019550_ (:8154), which indexes the 4-byte effect-definition table at 0x802c7ed0
   * (id -> [_, variantHandler, subVariant, kind]). Real table ids are 0..8 (+0xff = none);
   * id 1 (attacker-team-colored particle burst) covers 66.7% of family records. Consumed by
   * the renderer via applyHit's victim.lastHitImpactEffectId / Projectile.lastImpactEffectId.
   */
  impactEffectId: number;
  /** u8 +0x0b — reaction flags; bits 2|0x80 force a stagger regardless of gauges. */
  reactionFlags: number;
  /**
   * u8 +0x0d — hit-severity byte (behavior-notes (bc)/(bd)). Dual role: it selects the reaction-
   * anim variant AND is the KNOCKBACK-MAGNITUDE index — chunk_0003.c:8047 copies it to the victim's
   * actor+0x702, which then indexes DAT_802dd8a0[s]=s*7 (horizontal launch, zz_005ec20_) and
   * DAT_802d3664[s]=(s+1)*8 (velocity, FUN_8005ed38). See KNOCKBACK_STRENGTH_TABLE below. The
   * port's knockback APPLICATION stays anchored-TUNED (flat per-attack magnitude in applyHit)
   * pending a model restructure to single-base × strength — PORT-1TO1-STATUS §1 knockback row.
   */
  reactionAnimVariant: number;
  /** u16 +0x10 — formula/guard flags. */
  flagsA: number;
  /** u16 +0x12 — formula/guard flags. */
  flagsB: number;
  /**
   * u8 +0x14 — knockback YAW trim (signed, T8 combat-feel-gaps-decode-2026-07-05.md). Added to
   * the computed launch yaw as `trim * -256` BAM units (1 unit = 256 BAM = 1.40625 degrees).
   * Rare/nonzero mostly at +-128 (180 degrees, "launch away-side"). Already extracted into
   * damageRecords.json / familyDamageRecords.json; this field just exposes it on the type.
   */
  knockbackYawTrim?: number;
  /**
   * u8 +0x15 — knockback PITCH trim (signed, T8). Same `trim * -256` BAM conversion; pitch is
   * itself stored negated in FUN_8005ed38's `sin(-pitch)` sense, so a positive pitch-trim value
   * pitches the launch UP. Census: (0,24)=893/1530 records (~33.75 degrees up) is the modal
   * nonzero pitch trim. NET SIGN is trace-gated per the doc — see knockbackPitchTrimRadians()
   * in combat.ts for the assumption this port takes (labeled, not Confirmed).
   */
  knockbackPitchTrim?: number;
  /** s8 +0x16 — re-hit interval frames (chunk_0013.c:1173). Not consumed by the port yet. */
  rehitIntervalFrames: number;
}

type DamageRecordsFile = {
  provenance: Record<string, string>;
  records: DamageRecord[];
};

const GAUGE_INIT = gaugeInitData as GaugeInitFile;
const DAMAGE_RECORDS_FILE = damageRecordsData as unknown as DamageRecordsFile;

/** The 9 borg-family damage records (DAT_802d46e0), VERIFIED extraction. */
export const DAMAGE_RECORDS: readonly DamageRecord[] = DAMAGE_RECORDS_FILE.records;

/**
 * DERIVED_ROM knockback-magnitude tables (behavior-notes (bc), verified chunk_0007.c:5568/5630).
 * Indexed by a hit's strength byte (the damage record's `reactionAnimVariant` = record+0xd, copied
 * to actor+0x702 and clamped 0..15):
 *   - HORIZONTAL[s] = DAT_802dd8a0[s] = s*7   (launch h-speed factor, zz_005ec20_)
 *   - VELOCITY[s]   = DAT_802d3664[s] = (s+1)*8 (velocity magnitude, FUN_8005ed38)
 * These are the real ROM values (T9 resolved statically). WIRED (2026-07-04): applyHit now derives
 * its magnitude as single-base × strength — knockbackVelocityForRecord(record) × KNOCKBACK.PORT_SCALE
 * × the caller's per-move multiplier — replacing the old flat MELEE/SHOT/SPECIAL.KNOCKBACK scalars.
 * Only PORT_SCALE (one anchor preserving the old melee base) remains TUNED; see constants.ts.
 */
export const KNOCKBACK_STRENGTH_TABLE = {
  /** DAT_802dd8a0[s] = s*7, s∈0..15 — horizontal launch factor. */
  HORIZONTAL: Object.freeze(Array.from({ length: 16 }, (_, s) => s * 7)) as readonly number[],
  /** DAT_802d3664[s] = (s+1)*8, s∈0..15 — velocity magnitude. */
  VELOCITY: Object.freeze(Array.from({ length: 16 }, (_, s) => (s + 1) * 8)) as readonly number[],
} as const;

/** Clamp a strength byte to 0..15 (the ROM clamps actor+0x702 to the 16-entry tables). */
export function knockbackStrengthClamp(strength: number): number {
  const s = Math.trunc(strength);
  return s < 0 ? 0 : s > 15 ? 15 : s;
}

/**
 * DERIVED knockback velocity magnitude for a hit record (ROM u/f): the record's +0x0d severity
 * byte (`reactionAnimVariant`) is copied to the victim's actor+0x702 (chunk_0003.c:8047) and
 * FUN_8005ed38 reads the velocity from DAT_802d3664[s]=(s+1)*8. Yields melee(rec 1, s=6)=56 >
 * shot(rec 0, s=4)=40 > charge/special(rec 2, s=2)=24. Consumed by combat.ts applyHit as the
 * single base, scaled by KNOCKBACK.PORT_SCALE (constants.ts) × the caller's per-move multiplier.
 */
export function knockbackVelocityForRecord(record: DamageRecord): number {
  return KNOCKBACK_STRENGTH_TABLE.VELOCITY[knockbackStrengthClamp(record.reactionAnimVariant)] ?? 8;
}

/**
 * DERIVED (T6 combat-feel-gaps-decode-2026-07-05.md §"Knockback magnitude — zz_005ec20_"):
 * the GROUND-reaction knockback horizontal speed, distinct from the LAUNCH-reaction velocity
 * above. `zz_005ec20_` @0x8005ec20 (chunk_0007.c:5546-5573):
 *   idx = clamp(|victim.reactionAnimVariant|, 0..15)
 *   ratio = attackerScale / victimScale        (T5 — see below; now WIRED end-to-end)
 *   h-speed = ratio * DAT_802dd8a0[idx]         (= idx * 7.0, KNOCKBACK_STRENGTH_TABLE.HORIZONTAL)
 *   h-accel = -speed / 20.0                     (stops in 20 frames — see reactionGroundDecel)
 * This is the table the STAGGER-family reaction handlers (FUN_8005db44/FUN_8005dc24/FUN_8005df2c,
 * anim slots 0xd/0xe) use; the LAUNCH handler (FUN_8005ed38, knockdown/get-up family, anim
 * 0x13+dir/0x17+dir) uses the VELOCITY table with a pitch split instead (see
 * combat.ts's launch-vs-ground selection and knockbackPitchTrimRadians for the pitch half).
 */
export function knockbackGroundSpeedForRecord(
  record: DamageRecord,
  scaleRatio = 1,
): number {
  const idx = knockbackStrengthClamp(Math.abs(record.reactionAnimVariant));
  return scaleRatio * (KNOCKBACK_STRENGTH_TABLE.HORIZONTAL[idx] ?? 0);
}

/**
 * DERIVED (T5 combat-feel-gaps-decode-2026-07-05.md): the knockback scale-ratio multiplier —
 * `attacker+0xc4 (attacker render scale) / victim+0xb4 (victim render scale)`. NOW WIRED
 * end-to-end: combat.ts applyHit feeds `tierSizeScale(attacker) / tierSizeScale(victim)`
 * (timescale.ts), which is the full +0xb4/+0xc4 chain — the param-tier table row sizeScale
 * (data/paramTierTables.json 0x802dd5a0) at the effective tier (paramTier.tier + sizeTierDelta).
 * ×1.0/×1.0 (ratio 1.0) at the default tier 16 for every borg at spawn; diverges under
 * grow/shrink hit-status or the hero X +4-tier buff. (No per-borg base size-scale data file is
 * needed — the decode proves the base is uniformly 1.0; actor+0x3ec is the LEVEL byte, not a
 * size class.)
 */
export function knockbackScaleRatio(attackerScale = 1, victimScale = 1): number {
  if (victimScale === 0) return 1;
  return attackerScale / victimScale;
}

/**
 * DERIVED fallback for borg ids missing from the extracted table: 500/100 are the modal
 * values (142 of 198 extracted borgs), not a ROM-cited default — the original always reads
 * the per-borg pl####data.bin, so a missing id only happens for port-side synthetic borgs.
 */
const GAUGE_INIT_FALLBACK: BorgGaugeInit = { balanceGaugeMax: 500, downGaugeBase: 100 };

/** Per-borg gauge init (VERIFIED extraction), or the DERIVED modal fallback for unknown ids. */
export function gaugeInitForBorgId(id: string): BorgGaugeInit {
  return GAUGE_INIT.borgs[id.toLowerCase()] ?? GAUGE_INIT_FALLBACK;
}

/**
 * DERIVED hit-kind -> damage-record mapping. The original selects records per hitbox (hitbox
 * u16 +0x04 indexes the bound table); the port has no per-hitbox data yet, so each sim hit
 * kind is mapped to the table's matching archetype:
 *   - melee        -> record 1 (hp 30, down 100, balance 100, hitStrength 4, reactionFlags 2
 *                     = forced stagger — melee always interrupts);
 *   - normal shot  -> record 0 (hp 10, down 25, balance 25, hitStrength 1, reactionFlags 1 —
 *                     the light-hit archetype; shots only interrupt via gauge depletion).
 *                     NOT record 4: record 4's downGaugeDamage (100) equals the modal
 *                     downGaugeBase (100), and the ROM subtracts down damage unconditionally
 *                     on an out-of-reaction victim (chunk_0003.c:8002) before the <1 gate
 *                     (chunk_0003.c:6255), so every record-4 shot would stagger a standard
 *                     borg on the FIRST hit — i.e. record 4 is a heavy flinching shot, not
 *                     the rapid-fire "shots don't interrupt" archetype;
 *   - charge shot / special / sword beam -> record 2 (hp 20, down 100, balance 50,
 *                     hitStrength 4, reactionFlags 1 — heavy: staggers standard 100-down-base
 *                     borgs via down depletion, resisted by high-down-base tanks/bosses).
 */
export const DAMAGE_RECORD_INDEX = {
  MELEE: 1,
  SHOT: 0,
  CHARGE_OR_SPECIAL: 2,
} as const;

/** Reaction-flag mask that forces a stagger (damage-record byte +0x0b bits 2|0x80,
 *  chunk_0003.c:7524/7636). */
export const REACTION_FORCE_STAGGER_MASK = 0x82;

export function damageRecordByIndex(index: number): DamageRecord {
  const rec = DAMAGE_RECORDS[index];
  if (!rec) throw new RangeError(`damageRecordByIndex: no record ${index}`);
  return rec;
}
