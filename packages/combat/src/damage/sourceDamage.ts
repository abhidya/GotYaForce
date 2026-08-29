// =============================================================================
// sourceDamage.ts — ROM-faithful 1:1 port of the GG4E damage pipeline.
//
// Ports three decompiled functions, byte-for-byte against the source:
//   - zz_003cd5c_ (compute_base_damage_formula) @0x8003cd5c — chunk_0004.c:6667-6828
//   - zz_003d344_ (apply_hp_damage_subtract_clamp) @0x8003d344 — chunk_0004.c:6832-6860
//   - zz_0066298_ (lookup_type_category_table)   @0x80066298 — chunk_0008.c:2976-2982
//
// TYPE-MULTIPLIER MATRIX: this module is driven by the DOL-dumped float matrix at
// 0x802c5d60 (research/decomp/data/type-multiplier-matrix-802c5d60.json) and the family/
// variant -> canonical-category remap at 0x802f2e28 (type-category-remap-802f2e28.json),
// consumed here via the verbatim-codegen tables in typeDamage.generated.ts. NO tuned
// scalars: every multiplier comes from a DOL-dumped table or is the source's own float
// constant (cited inline).
//
// CHALLENGE-FLOW GATE (research/decomp/index/challenge-flow-evidence.md:187):
//   "Port damage from zz_003cd5c_ only after table inputs and object+1000 category source
//    are confirmed." Both prerequisites are now met:
//     - object+1000 == object+0x3e8 == borgNumber (rom/actor.ts:139; 1000 decimal == 0x3e8),
//       high byte = family, low byte = variant -> feeds zz_0066298_ exactly.
//     - the matrix + remap tables are DOL-dumped and verbatim-codegen'd.
//
// RANDOM FACTOR: NONE. zz_003cd5c_ is fully deterministic — there is no PRNG read anywhere
// in the formula (audited chunk_0004.c:6667-6828). The only per-hit variance comes from the
// record's own bytes (hpDamage, curve selectors, flags) and the actors' live state.
//
// SELF-CONTAINED: depends only on the DOL data tables + the verbatim type tables. It does
// NOT import combat.ts / damageFormula.ts / BorgRuntime, so it can be unit-ported and audited
// in isolation, then wired into applyHit via the integration spec at the bottom of this file.
// =============================================================================

import { TYPE_CATEGORY_REMAP, TYPE_MULTIPLIER_MATRIX } from "../typeDamage.generated.js";
import damageFormulaData from "../data/damageFormula.json" with { type: "json" };

// -----------------------------------------------------------------------------
// DOL data tables (research/decomp/data/damage-formula-tables-804335e0.json, codegen-consumed
// verbatim by packages/combat/src/data/damageFormula.json). These are the same tables
// damageFormula.ts consumes; re-cited here so this module is auditable as a standalone port.
// -----------------------------------------------------------------------------
type CurveSet = { ptr: string; curves: number[][] };
type FlatSet = { ptr: string; values: number[] };
type FormulaData = {
  scalars: {
    half_80436f7c: number;     // 0.5  — defender pair-attack nerf, CPU halving, spawn-prot
    pairNerf_80436f9c: number; // 2.0  — attacker pair-attack BONUS (misleading Ghidra name)
    sameTeam_80437024: number; // 0.25 — same-team friendly-fire divisor
    blockDiv_80437028: number; // 40.0 — guard/reflect divisor vs blast records
  };
  attackRankBySideRank_804335e0: FlatSet[];   // chunk_0004.c:6711-6712
  attackerHpCurves_804335e8: CurveSet[];       // chunk_0004.c:6717-6732
  attackerForceCurves_804335f0: CurveSet[];    // chunk_0004.c:6733-6737
  attackHandicap_804335f8: FlatSet[];          // chunk_0004.c:6741
  defenseRankCurves_80433600: CurveSet[];      // chunk_0004.c:6764-6768
  defenderHpCurves_80433608: CurveSet[];       // chunk_0004.c:6777-6795
  defenderForceCurves_80433610: CurveSet[];    // chunk_0004.c:6796-6802
  defenseHandicap_80433618: FlatSet[];         // chunk_0004.c:6803
  comboRankScale_802c7ca0: number[];           // chunk_0004.c:6804-6806
  defenseCurveSelectors_pldata_9c9d9e: Record<string, [number, number, number]>;
};
const DATA = damageFormulaData as unknown as FormulaData;


/** Per-hero curve/table counts — the valid selector domain for each curve family.
 *  Index 0 = player tables, 1 = CPU tables (heroFlag != 0). */
export function sourceDamageCurveCounts() {
  return {
    attHp: [DATA.attackerHpCurves_804335e8[0]!.curves.length, DATA.attackerHpCurves_804335e8[1]!.curves.length],
    attForce: [DATA.attackerForceCurves_804335f0[0]!.curves.length, DATA.attackerForceCurves_804335f0[1]!.curves.length],
    defRank: [DATA.defenseRankCurves_80433600[0]!.curves.length, DATA.defenseRankCurves_80433600[1]!.curves.length],
    defHp: [DATA.defenderHpCurves_80433608[0]!.curves.length, DATA.defenderHpCurves_80433608[1]!.curves.length],
    defForce: [DATA.defenderForceCurves_80433610[0]!.curves.length, DATA.defenderForceCurves_80433610[1]!.curves.length],
  } as const;
}

/** ROM neutral-handicap table index. The +0x43a byte is 3 for "no handicap" (table[3]==1.0). */
const HANDICAP_NEUTRAL_BYTE = 3;

// -----------------------------------------------------------------------------
// ACTOR + CONTEXT TYPES — minimal, each field cited to its object+0xNNN offset.
// -----------------------------------------------------------------------------

/**
 * Minimal actor view consumed by computeBaseDamage. Every field maps 1:1 to a ROM offset
 * read inside zz_003cd5c_. Use defaultSourceDamageActor() for a neutral baseline.
 */
export interface SourceDamageActor {
  /** +0x3e8 / object+1000: borgNumber. High byte = family, low byte = variant -> lookupTypeCategory. */
  borgNumber: number;
  /** +0x88: team/slot byte. attacker+0x88 == defender+0x88 -> x0.25 same-team (chunk_0004.c:6811). */
  team: number;
  /** +0x3e6: hero/CPU flag (signed char). !=0 selects the CPU table set and gates CPU-side0 halving. */
  heroFlag: number;
  /** +0x6fc: pair-attack flag. Attacker *=2.0 (6704-6707); defender *=0.5 (6761-6763). */
  pairAttack: number;
  /** +0xc4 (attacker) / +0xb4 (defender): power float, 1.0 baseline.
   *  INIT SITE UNCONFIRMED (behavior-notes.md ak: "STILL NOT FOUND as writes"). Default 1.0 is
   *  the neutral IDENTITY (sourcePowerMultiplier(1)==1), NOT a tuned scalar — pass the real value
   *  if/when the +0xc4/+0xb4 writer is traced. */
  power: number;
  /** +0x1c6 (live HP mirror, also at 0x803b069c[slot]): current HP. Drives the HP-ratio curve. */
  hp: number;
  /** +0x1c4: max HP (s16). HP-ratio curve denominator (capped at 200 in the source) + applyHpDamage clamp. */
  maxHp: number;
  /** +0x43a: handicap byte. Indexes attackHandicap/defenseHandicap directly; 3 = neutral. */
  handicap: number;
  /** +0x6ca: combo-rank byte. comboRankScale_802c7ca0 falloff unless record flagsB & 0x4000. */
  comboRank: number;
  /** Force-gauge ratio index (0..31), precomputed from side energy via forceGaugeRatioIndex(). */
  forceRatioIndex: number;
  /** Resolved Challenge side-rank byte (0..31) for this actor's team. Source resolves it via
   *  PTR_DAT_80433950[team]; the caller resolves team+mode -> rank (challengeSideRanksForMode). */
  sideRank: number;
  /** +0x83: eligibility. ==0 means "is a borg" (gates both attacker and defender borg blocks). */
  isBorg: boolean;
  /** +0x18: state byte. ==1 means active (both borg blocks require ==1). */
  isActive: boolean;
}

/** Per-hit record + battle context. All flags/curve-selectors come from the ROM hit record. */
export interface SourceDamageContext {
  /** Record u16 +0x10 (formula/guard flags). bit 0x1000 = blast record (guard/40, skips same-team). */
  flagsA: number;
  /** Record u16 +0x12. bit 0x4000 = skip combo-rank falloff (chunk_0004.c:6804). */
  flagsB: number;
  /** Record u8 +0x06 — attacker HP-ratio curve selector. */
  attackerHpCurveIndex: number;
  /** Record u8 +0x07 — attacker force-gauge curve selector. */
  attackerForceCurveIndex: number;
  /** Defender descriptor +0x9c/+0x9d/+0x9e defense-curve selectors (rank/hp/force). Optional
   *  override; when absent, resolved from defender.borgNumber via defenseCurveSelectors_pldata_9c9d9e. */
  defenderDefenseCurveSelectors?: [number, number, number];
  /** ATK-010 (chunk_0004.c:6696-6699): defender borg + status-immunity bit for the incoming
   *  status -> damage zeroes. */
  victimStatusImmune?: boolean;
  /** Defender resistance mask (actor +0x59c, mapped by the port to pldata+0xa8 — T1 decode).
   *  bit 0x1000 vs a blast record -> /40 guard divisor. */
  victimResistanceMask?: number;
  /** Actor +0x5e0 bit 0x4000000 spawn/drop-in protection -> x0.5 (chunk_0004.c:6807-6809).
   *  Writer untraced; default false = structural no-op. */
  victimSpawnProtection?: boolean;
  /** Challenge-modes-0/1 gate for the CPU-side0 halvings (chunk_0004.c:6713-6716 / 6769-6772). */
  cpuHalvingEnabled?: boolean;
}

/** Minimal HP target for applyHpDamage (the subtract+clamp site at object+0x1c6). */
export interface SourceDamageTarget {
  /** +0x1c6: current HP (s16). Subtracted from and clamped. */
  hp: number;
  /** +0x1c4: max HP (s16). Upper clamp. */
  maxHp: number;
  /** +0x1c8: previous-HP mirror. zz_003d344_ writes the pre-subtract HP here before subtracting. */
  prevHp?: number;
}

// =============================================================================
// zz_0066298_ — lookup_type_category_table @0x80066298 (chunk_0008.c:2976-2982)
//
//   int zz_0066298_(char *param_1) {
//     return (int)*(short *)((&PTR_DAT_802f2e28)[*param_1] + (uint)(byte)param_1[1] * 2);
//   }
//
// param_1 points at object+1000 (== borgNumber at +0x3e8): byte 0 = family, byte 1 = variant.
// On big-endian PowerPC, *(u16*)borgNumber has the family in the HIGH byte, variant in LOW.
// Returns the canonical category 0..19 used to index the type-multiplier matrix.
// =============================================================================

// =============================================================================
// ROM-wasm override seam. When the app boots with the ported damage-core wasm
// (packages/combat/src/rom/wasmDamageCore.ts — oracle-verified byte-exact over
// 26,232 cases), it installs the implementation here and every call site below
// runs the ROM's own compiled code instead of the TS port. Absent an override,
// behaviour is bit-identical to before this seam existed.
// =============================================================================
export interface SourceDamageImplementation {
  computeBaseDamage(
    attacker: SourceDamageActor,
    defender: SourceDamageActor,
    basePower: number,
    ctx: SourceDamageContext,
  ): number;
  lookupTypeCategory(borgNumber: number): number;
  applyHpDamage(target: SourceDamageTarget, amount: number): void;
}

let romDamageImpl: SourceDamageImplementation | null = null;

/** Install (or clear, with null) the ROM-wasm damage implementation. */
export function setRomDamageImplementation(impl: SourceDamageImplementation | null): void {
  romDamageImpl = impl;
}

/** Whether the ROM-wasm implementation is live. */
export function romDamageActive(): boolean {
  return romDamageImpl !== null;
}

/** Convert a borgNumber (0x3e8/+1000) to its "pl####" id (family/variant hex). 0x0615 -> "pl0615". */
export function borgNumberToBorgId(borgNumber: number): string {
  const family = (borgNumber >>> 8) & 0xff;
  const variant = borgNumber & 0xff;
  return "pl" + family.toString(16).padStart(2, "0") + variant.toString(16).padStart(2, "0");
}

/**
 * 1:1 port of zz_0066298_: family/variant bytes of `borgNumber` -> canonical category 0..19 via
 * the DOL remap table 0x802f2e28. Out-of-range family/variant (impossible for real borgs, whose
 * family byte is 0..15) falls back to 0 (the all-1.0 neutral matrix row).
 */
export function lookupTypeCategory(borgNumber: number): number {
  if (romDamageImpl) return romDamageImpl.lookupTypeCategory(borgNumber);
  const family = (borgNumber >>> 8) & 0xff;
  const variant = borgNumber & 0xff;
  const row = TYPE_CATEGORY_REMAP[family];
  return row != null && variant >= 0 && variant < row.length ? (row[variant] ?? 0) : 0;
}

/**
 * 1:1 port of the matrix read inside zz_003cd5c_ (chunk_0004.c:6742-6749):
 *   `dVar14 *= *(float *)(0x802c5d60 + defenderCat*0x50 + attackerCat*4)`
 * i.e. matrix[defenderCategory][attackerCategory] — defender selects the ROW (20-float stride
 * 0x50), attacker selects the COLUMN (4-byte stride). Confirmed by the matrix JSON description
 * (behavior-notes.md s4o) and by selfcheck.ts assertTypeDamageMatrixWired (pl0b00 vs pl0701 == 1.25).
 */
export function typeMultiplier(attackerBorgNumber: number, defenderBorgNumber: number): number {
  const attackerCategory = lookupTypeCategory(attackerBorgNumber);
  const defenderCategory = lookupTypeCategory(defenderBorgNumber);
  return TYPE_MULTIPLIER_MATRIX[defenderCategory]?.[attackerCategory] ?? 1;
}

// =============================================================================
// zz_003cd5c_ — compute_base_damage_formula @0x8003cd5c (chunk_0004.c:6667-6828)
//
// Returns the integer HP damage for one hit. Every step is cited to its source line range.
// =============================================================================

/**
 * Force-gauge ratio index (chunk_0004.c:6733-6737 attacker / 6796-6800 defender):
 *   `idx = 32 - floor(sideEnergy*32 / sideEnergyMax)`, clamped to 0..31. cur==max -> 0 (neutral,
 *   full gauge); empty gauge -> 31 (max comeback bonus). Returns 0 when energyMax is absent.
 */
export function forceGaugeRatioIndex(energy: number, energyMax: number | undefined): number {
  if (!energyMax || energyMax <= 0) return 0;
  return clampIndex(32 - Math.trunc((Math.max(0, energy) * 32) / energyMax), 32);
}

/**
 * 1:1 port of zz_003cd5c_. Computes the integer HP damage for a single hit.
 *
 *   basePower  — record u16 +0x00 (the *param_1 value; the formula's fVar1 seed).
 *   attacker   — resolving borg (for projectile hits, pass the OWNER borg, which is what the
 *                source dereferences at param_2+0x90; the type matrix reads the owner's +1000).
 *   defender   — victim borg.
 *   ctx        — record flags + curve selectors + battle gates.
 */
export function computeBaseDamage(
  attacker: SourceDamageActor,
  defender: SourceDamageActor,
  basePower: number,
  ctx: SourceDamageContext,
): number {
  // The ROM record field at +0x00 is a 16-bit integer (the verified spec writes
  // it with wU16 and reads 2 bytes), so `(float)*param_1` sees a u16 on hardware.
  // combat.ts forms basePower as a FLOAT (record.hpDamage * damageScale, with
  // fractional combo/charge/projectile scales), so coerce to the u16 record width
  // here: the TS port and the ROM wasm unit (which writes wU16) then compute on
  // the identical value, and both match the console. No-op for every integer
  // caller, including the verified damage-core oracle (basePower 1..1000).
  // Realistic damage is < 32768; the >32767 wrap/sign edge is out of the
  // reachable domain and not modeled here.
  basePower = basePower & 0xffff;
  if (romDamageImpl) return romDamageImpl.computeBaseDamage(attacker, defender, basePower, ctx);
  // Step 0 (6693-6695): fVar1 = (float)*param_1 = record hpDamage; gate `> FLOAT_80436f68` (0.0).
  if (!(basePower > 0)) return 0;

  // ATK-010 immunity (6696-6699): defender borg whose control word (+0x5a0) carries the immunity
  // bit for its current status id (+0x71a) -> damage zeroed. Caller summarizes as victimStatusImmune.
  if (ctx.victimStatusImmune) return 0;

  const hero = attacker.heroFlag !== 0 ? 1 : 0;

  // Step 1 (6701-6703): acc = base + base*0.5*(attackerPower - 1.0) = base*sourcePowerMultiplier.
  //   FLOAT_80436f7c=0.5, FLOAT_80436f78=1.0, attackerPower = attacker+0xc4. UNCONDITIONAL (runs
  //   before the attacker-borg sub-object check). Power init site unconfirmed — see actor.power doc.
  let acc = basePower * sourcePowerMultiplier(attacker.power);

  // --- ATTACKER borg block (6704-6749): only when the attacker sub-object (param_2+0x90) is an
  //     active borg (pcVar13[0x83]==0 && *pcVar13!=0 && pcVar13[0x18]==1). ---
  if (attacker.isBorg && attacker.isActive) {
    // Step 2 (6704-6707): pair-attack BONUS x2.0 (FLOAT_80436f9c, mislabeled "pairNerf" by Ghidra).
    if (attacker.pairAttack !== 0) acc *= DATA.scalars.pairNerf_80436f9c;

    // Step 3 (6711-6712): acc *= attackRankBySideRank[hero][sideRank].
    acc *= flatValue(DATA.attackRankBySideRank_804335e0, hero, attacker.sideRank);

    // Step 3b (6713-6716): CPU-side0 attacker halving. Challenge-mode byte is 0 or 1 AND
    //   heroFlag(+0x3e6)!=0 (CPU) AND team(+0x88)==0 -> *0.5 (FLOAT_80436f7c).
    if (ctx.cpuHalvingEnabled && attacker.heroFlag !== 0 && attacker.team === 0) acc *= DATA.scalars.half_80436f7c;

    // Step 4 (6717-6732): attacker HP-ratio curve. SKIPPED entirely when mirrorHP >= 201
    //   (`if ((int)uVar9 < 0xc9)`). index = clamp(32 - floor(hp*32/min(maxHp,200)), 0, 31).
    if (attacker.hp < 201) {
      acc *= curveValue(DATA.attackerHpCurves_804335e8, hero,
        ctx.attackerHpCurveIndex, hpRatioIndex(attacker.hp, attacker.maxHp));
    }

    // Step 5 (6733-6741): attacker force-gauge curve, then attacker handicap.
    //   force index from team-level energy; handicap byte = attacker+0x43a (indexes the table
    //   DIRECTLY — no port-side +3 offset; +0x43a==3 is neutral).
    acc *= curveValue(DATA.attackerForceCurves_804335f0, hero,
      ctx.attackerForceCurveIndex, clampIndex(attacker.forceRatioIndex, 32));
    acc *= flatValue(DATA.attackHandicap_804335f8, hero, attacker.handicap);

    // Step 6 (6742-6749): TYPE-MULTIPLIER MATRIX — the DOL float table 0x802c5d60. Applied only
    //   when the DEFENDER is also an active borg (param_3[0x83]==0 && *param_3!=0 && [0x18]==1).
    //   attCat = lookupTypeCategory(attacker+1000); defCat = lookupTypeCategory(defender+1000);
    //   acc *= matrix[defCat][attCat].  (address = 0x802c5d60 + defCat*0x50 + attCat*4)
    if (defender.isBorg && defender.isActive) {
      acc *= typeMultiplier(attacker.borgNumber, defender.borgNumber);
    }
  }
  let dmg = acc;

  // --- DEFENDER borg block (6751-6809): resolves the defender actor (param_3, or its sub-object
  //     at param_3+0x90 when param_3 is a non-borg carrying a borg). The port receives the
  //     already-resolved borg defender, so the resolution (6751-6757) collapses to this guard. ---
  if (defender.isBorg && defender.isActive) {
    const defHero = defender.heroFlag !== 0 ? 1 : 0;
    let f = dmg;

    // Step 7 (6761-6763): defender pair-attack NERF x0.5 (FLOAT_80436f7c). (Asymmetric with the
    //   attacker's x2.0 BONUS — same flag, opposite effect on the defending side.)
    if (defender.pairAttack !== 0) f *= DATA.scalars.half_80436f7c;

    // Step 8 (6764-6768): defense rank curve. selector = defender descriptor +0x9c, sideRank byte.
    const selectors = ctx.defenderDefenseCurveSelectors
      ?? DATA.defenseCurveSelectors_pldata_9c9d9e[borgNumberToBorgId(defender.borgNumber)]
      ?? ([0, 0, 0] as [number, number, number]);
    f *= curveValue(DATA.defenseRankCurves_80433600, defHero, selectors[0], defender.sideRank);

    // Step 8b (6769-6772): CPU-side0 defender halving (same gate shape as the attacker half).
    if (ctx.cpuHalvingEnabled && defender.heroFlag !== 0 && defender.team === 0) f *= DATA.scalars.half_80436f7c;

    // Step 9 (6773-6776): defender POWER DIVISOR = 1.0/(1.0+0.5*(defenderPower-1.0)) at defender+0xb4.
    //   Also computes sVar12 = mirrorHP - record.hpDamage (the post-hit HP for the curve below).
    f *= 1 / sourcePowerMultiplier(defender.power);

    // Step 10 (6777-6795): defender HP-ratio curve. Uses post-hit HP (mirrorHP - record.hpDamage),
    //   floored at 0; SKIPPED when that value >= 201.
    const postHitHp = Math.max(0, defender.hp - basePower);
    if (postHitHp < 201) {
      f *= curveValue(DATA.defenderHpCurves_80433608, defHero,
        selectors[1], hpRatioIndex(postHitHp, defender.maxHp));
    }

    // Step 11 (6796-6803): defender force curve (descriptor +0x9e) + defender handicap (+0x43a).
    f *= curveValue(DATA.defenderForceCurves_80433610, defHero,
      selectors[2], clampIndex(defender.forceRatioIndex, 32));
    f *= flatValue(DATA.defenseHandicap_80433618, defHero, defender.handicap);

    // Step 12 (6804-6806): combo-rank falloff (comboRankScale_802c7ca0[defender+0x6ca]) unless the
    //   record carries flagsB & 0x4000 (the "skip falloff" bit). This is the wiki's "hidden per-target
    //   resistance" — NOT a separate mechanic (ATK-013 audit).
    if ((ctx.flagsB & 0x4000) === 0) {
      f *= DATA.comboRankScale_802c7ca0[clampIndex(defender.comboRank, DATA.comboRankScale_802c7ca0.length)] ?? 1;
    }

    // Step 13 (6807-6809): defender +0x5e0 bit 0x4000000 spawn/drop-in protection -> x0.5.
    if (ctx.victimSpawnProtection) f *= DATA.scalars.half_80436f7c;

    dmg = f;
  }

  // Step 14 (6811-6813): SAME-TEAM x0.25 (FLOAT_80437024) when attacker+0x88 == defender+0x88 AND
  //   the record does NOT carry flagsA & 0x1000 (blast records bypass friendly-fire reduction).
  if (attacker.team === defender.team && (ctx.flagsA & 0x1000) === 0) {
    dmg *= DATA.scalars.sameTeam_80437024;
  }

  // Step 15 (6814-6817): GUARD /40 (FLOAT_80437028) — blast record (flagsA & 0x1000) hitting a borg
  //   whose resistance mask (actor +0x59c) carries bit 0x1000 -> /40. The "nuke one-shots everything
  //   except fortresses" rule (5000/40 = 125 vs resistant borgs).
  if ((ctx.flagsA & 0x1000) !== 0 && ((ctx.victimResistanceMask ?? 0) & 0x1000) !== 0) {
    dmg /= DATA.scalars.blockDiv_80437028;
  }

  // Step 16 (6818-6821): floor at 1.0 (FLOAT_80436f78), then truncate to int ((int)dVar14).
  if (dmg < 1) dmg = 1;
  return Math.trunc(dmg);
}

/** 1 + 0.5*(power-1) — the source power multiplier (FLOAT_80436f78=1.0, FLOAT_80436f7c=0.5). */
function sourcePowerMultiplier(power: number): number {
  return 1 + 0.5 * (power - 1);
}

/** HP-ratio curve index: 32 - floor(hp*32 / min(maxHp,200)), clamped 0..31. Source upper-clamps
 *  at 31 only (chunk_0004.c:6727/6789); this also lower-clamps at 0 to keep array access safe for
 *  hp>maxHp inputs (a non-issue in practice since the curve is skipped once hp>=201). */
function hpRatioIndex(currentHp: number, maxHp: number): number {
  const denom = Math.min(Math.max(1, maxHp), 200);
  const clampedCurrent = Math.max(0, currentHp);
  return clampIndex(32 - Math.trunc((clampedCurrent * 32) / denom), 32);
}

function curveValue(sets: CurveSet[], hero: number, selector: number, index: number): number {
  const curves = sets[hero]?.curves;
  const curve = curves?.[clampIndex(selector, curves.length)];
  return curve?.[clampIndex(index, curve.length)] ?? 1;
}

function flatValue(sets: FlatSet[], hero: number, index: number): number {
  const values = sets[hero]?.values;
  return values?.[clampIndex(index, values.length)] ?? 1;
}

function clampIndex(value: number, length: number): number {
  if (length <= 0) return 0;
  return Math.max(0, Math.min(length - 1, Math.trunc(value)));
}

// =============================================================================
// zz_003d344_ — apply_hp_damage_subtract_clamp @0x8003d344 (chunk_0004.c:6832-6860)
//
//   uint zz_003d344_(int param_1, short param_2) {
//     if (*(short *)(param_1 + 0x1c6) == 0) return 0;            // already dead -> no-op
//     *(short *)(param_1 + 0x1c8) = *(short *)(param_1 + 0x1c6); // +0x1c8 = pre-subtract HP
//     *(short *)(param_1 + 0x1c6) -= param_2;                    // HP -= damage
//     if (*(short *)(param_1 + 0x1c6) < 0) *(short *)(param_1 + 0x1c6) = 0;       // clamp >= 0
//     else if (*(short *)(param_1 + 0x1c4) < HP) HP = +0x1c4;    // clamp <= maxHp
//     // (mirror to linked object at +0x4a4 if this is a borg with +0x4a0==1)
//     return countLeadingZeros((int)HP) >> 5;                    // 1 iff HP==0 (lethal)
//   }
//
// NOTE: the source RETURNS a lethal flag (1 if the subtract brought HP to 0). The task spec asks
// for `: void`; this port mutates the target and drops the flag. The source's +0x4a4 linked-object
// mirror is omitted (no linked-object concept on SourceDamageTarget).
// =============================================================================

/**
 * 1:1 port of zz_003d344_ (void per spec). Subtracts `amount` from target.hp, mirroring the
 * pre-subtract HP to target.prevHp (+0x1c8), then clamps to [0, maxHp]. A target already at 0 HP
 * is a no-op (source returns early). Negative `amount` heals, clamped at maxHp.
 */
export function applyHpDamage(target: SourceDamageTarget, amount: number): void {
  if (romDamageImpl) return romDamageImpl.applyHpDamage(target, amount);
  // Already-dead guard (6839-6841): HP == 0 -> no-op.
  if (target.hp === 0) return;
  // +0x1c8 = pre-subtract HP mirror (6847).
  target.prevHp = target.hp;
  // HP -= damage (6848). Operate in 16-bit-signed space to match the s16 field at +0x1c6.
  let hp = target.hp - amount;
  // Clamp at 0 (6849-6851).
  if (hp < 0) hp = 0;
  // Clamp at maxHp (6852-6854) — bounds the result against the neighboring +0x1c4 field.
  else if (target.maxHp < hp) hp = target.maxHp;
  target.hp = hp;
}

// =============================================================================
// Neutral factory — sane defaults so a caller (or self-test) only sets what it cares about.
// =============================================================================

/** Neutral baseline actor: power 1.0 (identity), handicap 3 (neutral table slot), full HP, no
 *  pair/hero/combo, full force gauge (index 0), side rank 0, active borg. None of these are tuned
 *  gameplay values — each is the ROM field's neutral/identity state. */
export function defaultSourceDamageActor(borgNumber: number, maxHp = 200): SourceDamageActor {
  return {
    borgNumber,
    team: 0,
    heroFlag: 0,
    pairAttack: 0,
    power: 1,
    hp: maxHp,
    maxHp,
    handicap: HANDICAP_NEUTRAL_BYTE,
    comboRank: 0,
    forceRatioIndex: 0,
    sideRank: 0,
    isBorg: true,
    isActive: true,
  };
}

/** Neutral baseline context (no flags, no immunity, record curve selectors at 0). */
export function defaultSourceDamageContext(): SourceDamageContext {
  return {
    flagsA: 0,
    flagsB: 0,
    attackerHpCurveIndex: 0,
    attackerForceCurveIndex: 0,
  };
}

// =============================================================================
// SELF-TESTS — runSourceDamageSelfTests(assert). assert shape: (cond, msg) => void, matching the
// runXxxSelfTests(assert) convention used by the family handlers and rom.selfcheck.ts.
// =============================================================================

export type SourceDamageAssert = (cond: boolean, msg: string) => void;

export function runSourceDamageSelfTests(assert: SourceDamageAssert): void {
  // ---------- zz_0066298_ — lookupTypeCategory (borgNumber family/variant -> category) ----------
  // pl0b00 = borgNumber 0x0b00, family 0x0b row 11, variant 0 -> 15 (selfcheck.ts-confirmed).
  assert(lookupTypeCategory(0x0b00) === 15, "lookupTypeCategory(0x0b00/pl0b00) === 15");
  // pl0701 = 0x0701, family 7 variant 1 -> row[1]=12 (selfcheck.ts-confirmed).
  assert(lookupTypeCategory(0x0701) === 12, "lookupTypeCategory(0x0701/pl0701) === 12");
  // pl0615 = G RED = 0x0615, family 6 variant 0x15=21 -> row6[21]=4.
  assert(lookupTypeCategory(0x0615) === 4, "lookupTypeCategory(0x0615/pl0615 G RED) === 4");
  assert(borgNumberToBorgId(0x0615) === "pl0615", "borgNumberToBorgId(0x0615) === pl0615");

  // ---------- type-multiplier matrix — SE / NVE / neutral (DOL-dumped 0x802c5d60) -------------
  // pl0b00 (cat 15) attacks pl0701 (cat 12): matrix[12][15] = 1.25 (super-effective).
  assert(typeMultiplier(0x0b00, 0x0701) === 1.25, "typeMultiplier pl0b00->pl0701 === 1.25 (SE)");
  // Reverse: pl0701 (cat 12) attacks pl0b00 (cat 15): matrix[15][12] = 0.75 (not-very-effective).
  assert(typeMultiplier(0x0701, 0x0b00) === 0.75, "typeMultiplier pl0701->pl0b00 === 0.75 (NVE)");
  // Same category (cat 0 vs cat 0): matrix[0][0] = 1.0 (neutral). pl0000 = 0x0000 -> cat 0.
  assert(typeMultiplier(0x0000, 0x0000) === 1, "typeMultiplier same-cat neutral === 1.0");
  // Raw matrix spot-checks (defender-row, attacker-col convention).
  assert(TYPE_MULTIPLIER_MATRIX[12][15] === 1.25, "matrix[12][15] === 1.25 (defender-row/attacker-col)");
  assert(TYPE_MULTIPLIER_MATRIX[15][12] === 0.75, "matrix[15][12] === 0.75");
  assert(TYPE_MULTIPLIER_MATRIX[0][0] === 1, "matrix[0][0] === 1.0");

  // ---------- zz_003cd5c_ — computeBaseDamage structural invariants ---------------------------
  const neutralCtx = defaultSourceDamageContext();

  // basePower <= 0 -> 0 (the FLOAT_80436f68 gate, chunk_0004.c:6695/6824-6826).
  const a0 = defaultSourceDamageActor(0x0000);
  const d0 = defaultSourceDamageActor(0x0000, 200);
  assert(computeBaseDamage(a0, d0, 0, neutralCtx) === 0, "basePower 0 -> 0 damage");
  // A NEGATIVE basePower is not a ROM state and must not read as one. `param_1` is a `ushort *`
  // (chunk_0004.c:6673) and the formula seeds from `(uint)*param_1` (:6692) — a zero-extended
  // u16 — so the record word 0xfffb is 65531, not -5. The port's `basePower & 0xffff` coercion
  // at the top of computeBaseDamage reproduces that, and the ROM-wasm unit (which writes the
  // record with wU16) sees the identical value. This assertion previously expected -5 -> 0,
  // which is the pre-coercion behaviour and contradicts the record's declared width; it was
  // never executed, so nothing caught the drift.
  assert(
    computeBaseDamage(a0, d0, -5, neutralCtx) === computeBaseDamage(a0, d0, 0xfffb, neutralCtx),
    "negative basePower reads as its u16 record word (-5 == 0xfffb), not as <= 0",
  );

  // victimStatusImmune -> 0 (ATK-010, chunk_0004.c:6696-6699).
  assert(
    computeBaseDamage(a0, d0, 1000, { ...neutralCtx, victimStatusImmune: true }) === 0,
    "victimStatusImmune -> 0 damage",
  );

  // Type matrix is wired into the pipeline: SE categories beat NVE categories for IDENTICAL
  // actors (all other factors cancel). pl0b00 attacker vs pl0701 defender (1.25) vs the reverse
  // swap using identical neutral stats — compare a SE pairing against an NVE pairing.
  const seAtt = defaultSourceDamageActor(0x0b00);   // cat 15
  const seDef = defaultSourceDamageActor(0x0701);   // cat 12  -> matrix[12][15]=1.25 (SE)
  const nveAtt = defaultSourceDamageActor(0x0701);  // cat 12
  const nveDef = defaultSourceDamageActor(0x0b00);  // cat 15  -> matrix[15][12]=0.75 (NVE)
  const seDmg = computeBaseDamage(seAtt, seDef, 10000, neutralCtx);
  const nveDmg = computeBaseDamage(nveAtt, nveDef, 10000, neutralCtx);
  assert(seDmg > nveDmg, `SE damage (${seDmg}) > NVE damage (${nveDmg}) — type matrix wired`);
  assert(seDmg > 0 && nveDmg > 0, "both SE and NVE produce positive damage");

  // Same-team x0.25: identical actors, same categories, only the team byte differs.
  const teamAtt = defaultSourceDamageActor(0x0000);
  teamAtt.team = 0;
  const teamDefSame = defaultSourceDamageActor(0x0000);
  teamDefSame.team = 0; // same team -> x0.25
  const teamDefDiff = defaultSourceDamageActor(0x0000);
  teamDefDiff.team = 1; // diff team -> no divisor
  const sameTeamDmg = computeBaseDamage(teamAtt, teamDefSame, 10000, neutralCtx);
  const diffTeamDmg = computeBaseDamage(teamAtt, teamDefDiff, 10000, neutralCtx);
  assert(
    sameTeamDmg <= diffTeamDmg && sameTeamDmg * 4 <= diffTeamDmg + 4,
    `same-team (${sameTeamDmg}) ~= diff-team/4 (${diffTeamDmg}) — 0.25x friendly-fire`,
  );

  // Floor at 1: a tiny basePower that would underflow is clamped to 1 (chunk_0004.c:6818-6820).
  const floored = computeBaseDamage(teamAtt, teamDefSame, 1, neutralCtx);
  assert(floored >= 1, `floored damage >= 1 (got ${floored})`);

  // Attacker power multiplier: power 3 -> 1+0.5*2 = 2.0x base contribution. With identical
  // defenders, the power-3 hit must strictly exceed the power-1 hit (holding type neutral).
  const weakAtt = defaultSourceDamageActor(0x0000);
  weakAtt.power = 1;
  const strongAtt = defaultSourceDamageActor(0x0000);
  strongAtt.power = 3;
  const neutralDef = defaultSourceDamageActor(0x0000);
  const weakDmg = computeBaseDamage(weakAtt, neutralDef, 1000, neutralCtx);
  const strongDmg = computeBaseDamage(strongAtt, neutralDef, 1000, neutralCtx);
  assert(strongDmg > weakDmg, `attacker power multiplier wired (power3 ${strongDmg} > power1 ${weakDmg})`);

  // ---------- zz_003d344_ — applyHpDamage subtract + clamp -----------------------------------
  // Normal subtract mirrors pre-HP to prevHp.
  const t1: SourceDamageTarget = { hp: 100, maxHp: 100 };
  applyHpDamage(t1, 30);
  assert(t1.hp === 70, `applyHpDamage 100-30 -> 70 (got ${t1.hp})`);
  assert(t1.prevHp === 100, `applyHpDamage mirrors pre-HP to prevHp (got ${t1.prevHp})`);

  // Lethal overkill clamps at 0 (chunk_0004.c:6849-6851).
  const t2: SourceDamageTarget = { hp: 20, maxHp: 100 };
  applyHpDamage(t2, 50);
  assert(t2.hp === 0, `applyHpDamage overkill clamps at 0 (got ${t2.hp})`);

  // Heal (negative amount) clamps at maxHp (chunk_0004.c:6852-6854 upper bound).
  const t3: SourceDamageTarget = { hp: 90, maxHp: 100 };
  applyHpDamage(t3, -30);
  assert(t3.hp === 100, `applyHpDamage heal clamps at maxHp (got ${t3.hp})`);

  // Already-dead is a no-op (chunk_0004.c:6839-6841 early return).
  const t4: SourceDamageTarget = { hp: 0, maxHp: 100 };
  applyHpDamage(t4, 50);
  assert(t4.hp === 0 && t4.prevHp === undefined, `applyHpDamage on 0-HP target is a no-op`);
}

/* =============================================================================
 * WIRED AT: combat.ts applyHit. sourceDamageActorFromRuntime adapts BorgRuntime to
 * SourceDamageActor, computeBaseDamage is the primary damage path, and applyHpDamage
 * replaces the bare `victim.hp -= dmg`. damageFormula.computeSourceDamage / mitigate are
 * the throw-on-error fallbacks under the GF_SOURCE_STRICT contract. The exported
 * functions above are ALSO the ROM-wasm interception points — see
 * setRomDamageImplementation; anything that bypasses them silently leaves the wasm path.
 *
 * OPEN ROM GAPS (the reason the adapter passes neutral identities, not tuned values):
 *   - actor.power (+0xc4/+0xb4): init site STILL NOT FOUND (behavior-notes.md ak);
 *     defaults to 1.0. damageFormula.ts has the same gap, so this is not a regression.
 *   - actor.handicap (+0x43a): neutral byte 3 assumed; per-borg init site untraced.
 *   - victimSpawnProtection (+0x5e0 bit 0x4000000): writer untraced; stays false.
 *   - The defender descriptor +0x9c/+0x9d/+0x9e curve selectors resolve by borgId via
 *     defenseCurveSelectors_pldata_9c9d9e; pass ctx.defenderDefenseCurveSelectors to
 *     override once a real descriptor read is wired.
 * ========================================================================== */
