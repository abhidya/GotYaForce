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
const HERO_TABLE_DEFAULT = 0;
const HANDICAP_DEFAULT_INDEX = 3;

export interface SourceDamageContext {
  attacker: BorgRuntime;
  attackerProfile: BorgProfile;
  victim: BorgRuntime;
  victimProfile: BorgProfile;
  record: DamageRecord;
  /** Port-side stand-in for unmapped hitbox records/charge tiers; default is exact record damage. */
  damageScale?: number | undefined;
  /** Source table set selected by actor+0x3e6. Not represented in BattleState yet. */
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
  /** Force-gauge context is not threaded yet; defaults to full gauge, i.e. curve index 0. */
  attackerForceRatioIndex?: number | undefined;
  defenderForceRatioIndex?: number | undefined;
  /** Reflect/block divisor gate; no caller wires this until guard state is ported. */
  blockDivisorActive?: boolean | undefined;
  /** ATK-010: formula step 1 — the victim's per-status immunity bit for the incoming hit's
   *  status also zeroes HP damage for that hit (chunk_0004.c:6693-6699). No caller wires this
   *  yet (status.ts's immunity gate isn't fed a real per-hit status id); default/absent = no
   *  change to existing damage output. */
  victimStatusImmune?: boolean | undefined;
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

export function computeSourceDamage(ctx: SourceDamageContext): number {
  // ATK-010 formula step 1 (chunk_0004.c:6693-6699): the victim's per-status immunity bit for
  // the incoming hit's status zeroes HP damage for that hit. No caller sets this yet (default/
  // absent = false) — existing damage output is unchanged.
  if (ctx.victimStatusImmune) return 0;
  const recordBase = ctx.record.hpDamage * (ctx.damageScale ?? 1);
  if (recordBase <= 0) return 0;

  const hero = ctx.heroTable ?? HERO_TABLE_DEFAULT;
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

  if (ctx.defenderPairAttack) dmg *= DATA.scalars.half_80436f7c;
  dmg *= curveValue(DATA.defenseRankCurves_80433600, hero, selectors[0] ?? 0, defenderRank);
  dmg *= 1 / sourcePowerMultiplier(ctx.defenderPower ?? 1);
  dmg *= curveValue(
    DATA.defenderHpCurves_80433608,
    hero,
    selectors[1] ?? 0,
    hpRatioIndex(ctx.victim.hp - recordBase, ctx.victim.maxHp),
  );
  dmg *= curveValue(
    DATA.defenderForceCurves_80433610,
    hero,
    selectors[2] ?? 0,
    ctx.defenderForceRatioIndex ?? 0,
  );
  dmg *= flatValue(DATA.defenseHandicap_80433618, hero, handicapIndex(ctx.defenderHandicapIndex));
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
  if (ctx.blockDivisorActive && (ctx.record.flagsA & 0x1000) !== 0) {
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
