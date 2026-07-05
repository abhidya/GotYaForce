import type { BorgProfile } from "./stats.js";
import type { BorgRuntime } from "./types.js";
import type { DamageRecord } from "./gauges.js";
import { typeDamageMultiplier } from "./typeDamage.js";
import damageFormulaData from "./data/damageFormula.json" with { type: "json" };

type CurveSet = { ptr: string; curves: number[][] };
type FlatSet = { ptr: string; values: number[] };

type DamageFormulaData = {
  scalars: {
    half_80436f7c: number;
    // NAMING (T4 item 7): despite the name, this is the x2.0 PAIR-ATTACK BONUS applied to the
    // ATTACKER side (formula step 3, ×2.0 when attackerPairAttack — see burst.ts/T3's side-wide
    // "Power Burst" flag, which is what actually sets pair-attack today), not a nerf. Kept as
    // pairNerf_80436f9c for JSON/generator continuity (renaming the generated data key is out of
    // scope here); read it as "pair-attack BONUS, value 2.0".
    pairNerf_80436f9c: number;
    sameTeam_80437024: number;
    blockDiv_80437028: number;
  };
  attackRankBySideRank_804335e0: FlatSet[];
  attackerHpCurves_804335e8: CurveSet[];
  attackerForceCurves_804335f0: CurveSet[];
  attackHandicap_804335f8: FlatSet[];
  defenseRankCurves_80433600: CurveSet[];
  defenderHpCurves_80433608: CurveSet[];
  defenderForceCurves_80433610: CurveSet[];
  defenseHandicap_80433618: FlatSet[];
  comboRankScale_802c7ca0: number[];
  challengeSideRankBytes_804356e4: {
    normal: [number, number];
    tuff: [number, number];
    insane: [number, number];
  };
  defenseCurveSelectors_pldata_9c9d9e: Record<string, [number, number, number]>;
};

const DATA = damageFormulaData as unknown as DamageFormulaData;
// NAMING (T4 item 7): "heroTable"/HERO_TABLE_DEFAULT (retired) named this after the old (wrong)
// "hero flag" reading of actor+0x3e6 — T2 decoded it as the CPU-CONTROLLED flag instead. The
// `hero` local variable name is kept below for minimal diff against the generated data's own
// table-set axis naming, but its true meaning is now `heroTableFor(ownerPlayer)` — see that
// function's doc.
const HANDICAP_DEFAULT_INDEX = 3;

export interface SourceDamageContext {
  attacker: BorgRuntime;
  attackerProfile: BorgProfile;
  victim: BorgRuntime;
  victimProfile: BorgProfile;
  record: DamageRecord;
  /** Port-side stand-in for unmapped hitbox records/charge tiers; default is exact record damage. */
  damageScale?: number | undefined;
  /**
   * Source table set selected by actor+0x3e6 — DECODED as the CPU-CONTROLLED flag, not "hero"
   * (T2, combat-feel-gaps-decode-2026-07-05.md): `+0x3e6 = 1` when NO human controls the actor
   * (battle spawn tests the active human-player bitmask against the actor's player-index bit).
   * `heroTableFor()` below derives this from BorgRuntime.ownerPlayer (null = CPU) so callers
   * don't need to compute the table index by hand; still accepted directly for callers that
   * want to override it (e.g. selfchecks pinning a specific table).
   */
  heroTable?: 0 | 1 | undefined;
  /** Source side-rank bytes. Defaults to Challenge NORMAL: side 0 = 0, side 1 = 31. */
  attackerSideRank?: number | undefined;
  defenderSideRank?: number | undefined;
  /**
   * Source level/power floats default to 1.0 until actor level init sites are ported.
   * ATK-020: the borg LEVEL byte itself (actor+0x3ec) IS plumbed now (BorgProfile.level,
   * stats.ts/sourceBorgStats.ts row selection) and does drive HP/ammo row selection — but the
   * damage-formula floats read here (ctx+0xc4 attacker / +0xb4 victim, behavior-notes.md ah
   * steps 2/13) are a SEPARATE, still-unfound init site (behavior-notes.md ak: "STILL NOT
   * FOUND as writes"). Do NOT feed BorgProfile.level into attackerPower/defenderPower —
   * these params stay defaulted to 1.0 until that init rule is found.
   */
  attackerPower?: number | undefined;
  defenderPower?: number | undefined;
  /** Pair-attack flags are not modeled yet; defaults preserve normal battle damage. */
  attackerPairAttack?: boolean | undefined;
  defenderPairAttack?: boolean | undefined;
  /** Source handicap byte defaults to 0, which indexes the neutral 1.0 slot. */
  attackerHandicapIndex?: number | undefined;
  defenderHandicapIndex?: number | undefined;
  /**
   * FORCE-GAUGE ratio index — DECODED (T4): input is the SIDE's shared GF/force energy gauge
   * (BattleState.energy[team] / energyMax[team], the team pool that pays for deaths), NOT any
   * per-borg gauge. Recipe (chunk_0004.c:6733-6737/6796-6800): `idx = clamp(32 -
   * floor(energy*32/energyMax), 0, 31)` — cur==max gives 0 (full gauge, neutral), an empty
   * gauge gives 31 (max comeback bonus). `forceGaugeRatioIndex()` below computes this from
   * BattleState; defaults to 0 (full gauge / no bonus) when absent, same as before T4.
   */
  attackerForceRatioIndex?: number | undefined;
  defenderForceRatioIndex?: number | undefined;
  /**
   * CPU-side halvings — DECODED (T2/T4 item 3, chunk_0004.c:6713-6716/6769-6772): in Challenge
   * modes 0/1, a CPU-controlled (BorgRuntime.ownerPlayer === null) attacker on SIDE 0 deals
   * ×0.5, and a CPU-controlled victim on SIDE 0 takes ×0.5. This is keyed on the actor's OWN
   * CPU flag (not heroTable, which is a formula-TABLE selector reusing the same +0x3e6 read) —
   * kept as separate booleans so callers that don't model Challenge mode/side-0-CPU semantics
   * (most selfchecks, all non-Challenge battles) can leave them false/absent and get unchanged
   * output.
   */
  attackerIsCpuSide0?: boolean | undefined;
  defenderIsCpuSide0?: boolean | undefined;
  /**
   * GUARD/40 DATA RULE — DERIVED, combat-feel-gaps-decode-2026-07-05.md T1 (retraction of the
   * earlier "guard state" reading — there is NO hold-to-block state in the ROM). `zz_003cd5c_`
   * (chunk_0004.c:6814-6817): `victim is a borg && (rec.flagsA & 0x1000) && (victim pldata+0xa8
   * mask & 0x1000) -> dmg /= 40`. This is the victim's STATIC per-borg resistance mask (u16 @
   * pldata+0xa8, movementData.ts statusImmunityMasksForBorgId(...).immunityA — the SAME +0xa8
   * word the port already extracts for status-immunity gating, VERIFIED same field per the
   * doc's own "VERIFY the doc means the same +0xa8 word" instruction), NOT a caller-supplied
   * flag — the old `blockDivisorActive` boolean (a guard-state stand-in that nothing ever
   * wired) is retired in favor of this real per-borg data value. Census: 29/198 borgs carry bit
   * 0x1000 (dragons, tanks/fortress family 6, some family 0a/0e borgs); only 2 real flagsA&0x1000
   * records exist (hpDamage 5000 nuke rows), so 5000/40 = 125 vs those borgs — the "nuke
   * one-shots everything except fortresses" lore.
   */
  victimStatusImmunityA?: number | undefined;
  /** ATK-010: formula step 1 — the victim's per-status immunity bit for the incoming hit's
   *  status also zeroes HP damage for that hit (chunk_0004.c:6693-6699). No caller wires this
   *  yet (status.ts's immunity gate isn't fed a real per-hit status id); default/absent = no
   *  change to existing damage output. */
  victimStatusImmune?: boolean | undefined;
  /**
   * Formula step 17 — DOCUMENTED, NOT REPRESENTABLE (T4 item 4): `victim +0x5e0 & 0x4000000 ->
   * ×0.5` (chunk_0004.c:6807-6809). The doc's own honest gap: "the bit's writer wasn't chased
   * this pass — UNKNOWN which state sets it (candidate: a spawn/drop-in protection)". The port
   * has no BorgRuntime field for ROM's +0x5e0 status-flags word at all, so there is nothing to
   * read here even in principle yet — left as a labeled no-op (never true) rather than invented.
   * Revisit once +0x5e0's bit is traced to a real port-side state.
   */
  victimSpawnProtection5e0_4000000?: boolean | undefined;
}

export const damageFormulaSummary = {
  source: "research/decomp/data/damage-formula-tables-804335e0.json",
  consumer: "zz_003cd5c_ @0x8003cd5c",
};

export type ChallengeDamageMode = 0 | 1 | 2;

export function challengeSideRanksForMode(mode: ChallengeDamageMode = 0): readonly [number, number] {
  if (mode === 1) return DATA.challengeSideRankBytes_804356e4.tuff;
  if (mode === 2) return DATA.challengeSideRankBytes_804356e4.insane;
  return DATA.challengeSideRankBytes_804356e4.normal;
}

/**
 * T2 DECODED: actor+0x3e6 (the formula's "hero" table selector) is the CPU-CONTROLLED flag —
 * 1 when NO human controls the actor. Derives the table index straight from
 * BorgRuntime.ownerPlayer (null = CPU) so callers don't have to compute it by hand; `undefined`
 * ownerPlayer (shouldn't happen on a real BorgRuntime, but keeps this total) reads as CPU too
 * (fails toward the CPU table, matching "no proven human owner").
 */
export function heroTableFor(ownerPlayer: string | null | undefined): 0 | 1 {
  return ownerPlayer === null || ownerPlayer === undefined ? 1 : 0;
}

/**
 * T4 DECODED: the force-gauge ratio index feeding attackerForceRatioIndex/defenderForceRatioIndex
 * above. `idx = clamp(32 - floor(energy*32/energyMax), 0, 31)` (chunk_0004.c:6733-6737/6796-6800)
 * — cur==max (full gauge) gives 0 (neutral), an empty gauge gives 31 (max comeback bonus).
 * Returns 0 (full-gauge/neutral) when energyMax is absent or non-positive so callers without the
 * side-gauge-max snapshot (BattleState.energyMax, only recently added — see battle.ts) get the
 * exact pre-T4 default instead of a divide-by-zero.
 */
export function forceGaugeRatioIndex(energy: number, energyMax: number | undefined): number {
  if (!energyMax || energyMax <= 0) return 0;
  return clampIndex(32 - Math.trunc((Math.max(0, energy) * 32) / energyMax), 32);
}

export function computeSourceDamage(ctx: SourceDamageContext): number {
  // ATK-010 formula step 1 (chunk_0004.c:6693-6699): the victim's per-status immunity bit for
  // the incoming hit's status zeroes HP damage for that hit. No caller sets this yet (default/
  // absent = false) — existing damage output is unchanged.
  if (ctx.victimStatusImmune) return 0;
  const recordBase = ctx.record.hpDamage * (ctx.damageScale ?? 1);
  if (recordBase <= 0) return 0;

  const hero = ctx.heroTable ?? heroTableFor(ctx.attacker.ownerPlayer);
  const attackerRank = clampIndex(
    ctx.attackerSideRank ?? defaultChallengeNormalSideRank(ctx.attacker.team),
    32,
  );
  const defenderRank = clampIndex(
    ctx.defenderSideRank ?? defaultChallengeNormalSideRank(ctx.victim.team),
    32,
  );
  const selectors = DATA.defenseCurveSelectors_pldata_9c9d9e[ctx.victimProfile.id.toLowerCase()] ?? [0, 0, 0];

  let dmg = recordBase;
  dmg *= sourcePowerMultiplier(ctx.attackerPower ?? 1);
  if (ctx.attackerPairAttack) dmg *= DATA.scalars.pairNerf_80436f9c;
  dmg *= flatValue(DATA.attackRankBySideRank_804335e0, hero, attackerRank);
  // HP-curve SKIP GATE — DOCUMENTED discrepancy (T4 item 2, chunk_0004.c:6718): the ROM skips
  // the attacker HP-ratio multiplier ENTIRELY when the (mirror) HP value >= 201
  // (`if ((int)uVar9 < 0xc9)`), rather than clamping the curve index to a saturated end. The
  // port instead clamps hpRatioIndex's output to 0..32 via curveValue's own clampIndex, which is
  // EQUIVALENT ONLY because every extracted curve[0] == 1.0 (verified — see the doc). If curves
  // are ever re-extracted with a non-1.0 index-0 entry, this multiply would need the real
  // "skip when HP >= 201" gate instead of relying on the clamp coincidence.
  dmg *= curveValue(
    DATA.attackerHpCurves_804335e8,
    hero,
    ctx.record.attackerHpCurveIndex,
    hpRatioIndex(ctx.attacker.hp, ctx.attacker.maxHp),
  );
  dmg *= curveValue(
    DATA.attackerForceCurves_804335f0,
    hero,
    ctx.record.forceGaugeCurveIndex,
    ctx.attackerForceRatioIndex ?? 0,
  );
  dmg *= flatValue(DATA.attackHandicap_804335f8, hero, handicapIndex(ctx.attackerHandicapIndex));
  dmg *= typeDamageMultiplier(ctx.attackerProfile.id, ctx.victimProfile.id);
  // CPU-side halving, attacker half (T4 item 3 / T2, chunk_0004.c:6713-6716): Challenge modes
  // 0/1, a CPU-controlled attacker on side 0 deals x0.5. Caller-gated (attackerIsCpuSide0) since
  // most callers don't model Challenge-mode/side semantics; absent = unchanged output.
  if (ctx.attackerIsCpuSide0) dmg *= 0.5;

  if (ctx.defenderPairAttack) dmg *= DATA.scalars.half_80436f7c;
  dmg *= curveValue(DATA.defenseRankCurves_80433600, hero, selectors[0] ?? 0, defenderRank);
  dmg *= 1 / sourcePowerMultiplier(ctx.defenderPower ?? 1);
  // Defender post-hit HP index — FIXED discrepancy (T4 item 5, chunk_0004.c:6773-6779): the ROM
  // indexes the defender HP curve with `mirrorHP - rec.hpDamage` (the RECORD'S OWN RAW u16, not
  // damageScale-multiplied), floored at 0. The port previously used `victim.hp - recordBase`
  // (recordBase = record.hpDamage * damageScale), which diverges from the ROM whenever
  // damageScale != 1 (chargeShots/combo-step multipliers etc.). Now uses the raw record value.
  dmg *= curveValue(
    DATA.defenderHpCurves_80433608,
    hero,
    selectors[1] ?? 0,
    hpRatioIndex(Math.max(0, ctx.victim.hp - ctx.record.hpDamage), ctx.victim.maxHp),
  );
  dmg *= curveValue(
    DATA.defenderForceCurves_80433610,
    hero,
    selectors[2] ?? 0,
    ctx.defenderForceRatioIndex ?? 0,
  );
  dmg *= flatValue(DATA.defenseHandicap_80433618, hero, handicapIndex(ctx.defenderHandicapIndex));
  // CPU-side halving, defender half (T4 item 3 / T2, chunk_0004.c:6769-6772): a CPU-controlled
  // victim on side 0 takes x0.5. Same caller-gated shape as the attacker half above.
  if (ctx.defenderIsCpuSide0) dmg *= 0.5;
  // Formula step 17 (T4 item 4) — see victimSpawnProtection5e0_4000000's doc: documented but
  // never true today (no port-side +0x5e0 field exists), so this is a structural no-op, not a
  // silently-skipped ROM behavior.
  if (ctx.victimSpawnProtection5e0_4000000) dmg *= 0.5;
  // ATK-013: the wiki's "hidden per-target damage resistance" is NOT a separate mechanic —
  // it IS this already-ported combo-rank falloff. ROM: dmg *= DAT_802c7ca0[victim+0x6ca]
  // (comboRankScale_802c7ca0 above) unless record flagsB & 0x4000 (zz_003cd5c_ step 16,
  // behavior-notes.md (ah), chunk_0004.c:6804-6806); accumulator/rank chunk_0003.c:8021-8030;
  // 60-frame window reset chunk_0006.c:8009-8010. See research/tasks/attack-port/
  // ATK-013-resistance-falloff-audit-note.md. Do NOT add a second resistance/falloff layer —
  // that would double-apply the same ROM mechanic.
  if ((ctx.record.flagsB & 0x4000) === 0) {
    dmg *= DATA.comboRankScale_802c7ca0[clampIndex(ctx.victim.comboRank, DATA.comboRankScale_802c7ca0.length)] ?? 1;
  }
  if (ctx.attacker.team === ctx.victim.team && (ctx.record.flagsA & 0x1000) === 0) {
    dmg *= DATA.scalars.sameTeam_80437024;
  }
  // GUARD/40 DATA RULE (T1) — see victimStatusImmunityA's doc above. Data-driven, not a
  // caller-supplied flag: gated on the record's blast flag AND the victim's own static
  // per-borg resistance mask both carrying bit 0x1000.
  if ((ctx.record.flagsA & 0x1000) !== 0 && ((ctx.victimStatusImmunityA ?? 0) & 0x1000) !== 0) {
    dmg /= DATA.scalars.blockDiv_80437028;
  }

  return Math.max(1, Math.trunc(dmg));
}

function sourcePowerMultiplier(power: number): number {
  return 1 + 0.5 * (power - 1);
}

function hpRatioIndex(currentHp: number, maxHp: number): number {
  const denom = Math.min(Math.max(1, maxHp), 200);
  const clampedCurrent = Math.max(0, currentHp);
  return clampIndex(32 - Math.trunc((clampedCurrent * 32) / denom), 32);
}

function defaultChallengeNormalSideRank(team: number): number {
  return team === 0
    ? DATA.challengeSideRankBytes_804356e4.normal[0]
    : DATA.challengeSideRankBytes_804356e4.normal[1];
}

function handicapIndex(index: number | undefined): number {
  if (index === undefined) return HANDICAP_DEFAULT_INDEX;
  return clampIndex(index + HANDICAP_DEFAULT_INDEX, 16);
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
