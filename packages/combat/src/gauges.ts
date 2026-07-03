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
 * These are the real ROM values (T9 resolved statically). NOT yet wired into applyHit — the port
 * keeps its anchored-TUNED flat knockback until the model is restructured to single-base × strength
 * with a scale reconciled to the port's ~4× world rescale (see the knockback-port task / §1). This
 * export makes the DERIVED model available to that port and to tests without changing gameplay.
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
