// damageFormula.ts — BorgRuntime-shaped ADAPTER onto the single ROM damage implementation.
//
// HISTORY / WHY THIS FILE NO LONGER COMPUTES ANYTHING: this module used to carry a SECOND,
// independently-written implementation of zz_003cd5c_ (@0x8003cd5c, chunk_0004.c:6667-6828)
// alongside damage/sourceDamage.ts's 1:1 port. The two disagreed in four places, and a direct
// read of the decompiled function settles every one of them against this file:
//
//   1. DEFENDER HP-CURVE INPUT — chunk_0004.c:6773
//        sVar12 = (&DAT_803b069c)[pcVar10[0x3e4]] - *param_1;
//      The subtrahend is `*param_1`, the SAME record word that seeded fVar1 at :6693. The ROM
//      uses one value in both places. This file used the raw record byte for the curve while
//      seeding the formula with record x damageScale — a split the ROM does not have.
//      sourceDamage.ts keeps the ROM's single-value invariant (its `basePower` IS *param_1),
//      which is also exactly what the oracle-verified damage-core wasm unit implements.
//   2. HANDICAP INDEX — chunk_0004.c:6741 / :6803
//        *(float *)(<table> + pcVar13[0x43a] * 4)
//      The +0x43a byte indexes the table DIRECTLY. This file added a +3 port-side offset on
//      top of the byte; sourceDamage.ts indexes directly (byte 3 == the neutral 1.0 slot).
//   3. ATTACKER HP-CURVE SKIP GATE — chunk_0004.c:6718
//        if ((int)uVar9 < 0xc9) { ...curve... }
//      HP >= 201 skips the multiply ENTIRELY. This file relied on "every curve[0] == 1.0" to
//      make an index clamp coincidentally equivalent; sourceDamage.ts ports the real gate.
//   4. DEFENDER TABLE-SET SELECTOR — chunk_0004.c:6753
//        cVar2 = pcVar10[0x3e6];   // the DEFENDER's own CPU flag
//      The defender block selects its table set from the DEFENDER's +0x3e6. This file reused
//      the attacker-derived `hero` index for both sides; sourceDamage.ts reads each side's own.
//
// It also bypassed the ROM-wasm seam: `setRomDamageImplementation` swaps
// computeBaseDamage/lookupTypeCategory wholesale, and a second TS formula (plus typeDamage.ts's
// own matrix read) silently left that verified path. Everything below now routes through
// sourceDamage.ts's exports, so the wasm unit owns these numbers when it is installed.
//
// What remains here is the ADAPTER: BorgRuntime/BorgProfile in, SourceDamageActor out. The
// per-caller Challenge/force-gauge/handicap plumbing documented below is the port's own
// bookkeeping, not a second formula.

import type { BorgProfile } from "./stats.js";
import type { BorgRuntime } from "./types.js";
import type { DamageRecord } from "./gauges.js";
import {
  computeBaseDamage,
  forceGaugeRatioIndex as sourceForceGaugeRatioIndex,
  type SourceDamageActor,
  type SourceDamageContext as RomDamageContext,
} from "./damage/sourceDamage.js";
import damageFormulaData from "./data/damageFormula.json" with { type: "json" };

type DamageFormulaData = {
  challengeSideRankBytes_804356e4: {
    normal: [number, number];
    tuff: [number, number];
    insane: [number, number];
  };
};

const DATA = damageFormulaData as unknown as DamageFormulaData;

/** ROM neutral-handicap byte: actor+0x43a == 3 selects the 1.0 slot of both handicap tables
 *  (chunk_0004.c:6741 / :6803 index the table with the raw byte). */
const HANDICAP_NEUTRAL_BYTE = 3;

export interface SourceDamageContext {
  attacker: BorgRuntime;
  attackerProfile: BorgProfile;
  victim: BorgRuntime;
  victimProfile: BorgProfile;
  record: DamageRecord;
  /** Port-side stand-in for unmapped hitbox records/charge tiers; default is exact record damage.
   *  Multiplied into the record word BEFORE the formula runs, so it feeds both the damage seed
   *  and the defender post-hit HP index — the ROM's single-`*param_1` invariant (see header). */
  damageScale?: number | undefined;
  /**
   * Source table set selected by actor+0x3e6 — DECODED as the CPU-CONTROLLED flag, not "hero"
   * (T2, combat-feel-gaps-decode-2026-07-05.md): `+0x3e6 = 1` when NO human controls the actor.
   * `heroTableFor()` below derives this from BorgRuntime.ownerPlayer (null = CPU). Supplying it
   * PINS BOTH sides' selector (selfchecks that want one fixed table set); leave it absent and
   * each side reads its own owner, which is what the ROM does (chunk_0004.c:6708 attacker /
   * :6753 defender).
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
  /** actor+0x6fc pair-attack flag: attacker x2.0 (chunk_0004.c:6704-6707), defender x0.5
   *  (:6761-6763). Runtime hits read BorgRuntime.burstPaired instead (combat.ts). */
  attackerPairAttack?: boolean | undefined;
  defenderPairAttack?: boolean | undefined;
  /** actor+0x43a handicap BYTE — indexes the handicap tables directly (no port-side offset).
   *  Absent = HANDICAP_NEUTRAL_BYTE (3), the 1.0 slot. */
  attackerHandicapIndex?: number | undefined;
  defenderHandicapIndex?: number | undefined;
  /**
   * FORCE-GAUGE ratio index — DECODED (T4): input is the SIDE's shared GF/force energy gauge
   * (BattleState.energy[team] / energyMax[team], the team pool that pays for deaths), NOT any
   * per-borg gauge. Recipe (chunk_0004.c:6733-6737/6796-6800): `idx = clamp(32 -
   * floor(energy*32/energyMax), 0, 31)`. `forceGaugeRatioIndex()` below computes this from
   * BattleState; defaults to 0 (full gauge / no bonus) when absent.
   */
  attackerForceRatioIndex?: number | undefined;
  defenderForceRatioIndex?: number | undefined;
  /**
   * CPU-side halvings — DECODED (T2/T4 item 3, chunk_0004.c:6713-6716/6769-6772): in Challenge
   * modes 0/1, a CPU-controlled attacker on SIDE 0 deals x0.5 and a CPU-controlled victim on
   * SIDE 0 takes x0.5. Either flag ENABLES the Challenge gate; the per-side condition
   * (own +0x3e6 CPU flag AND own +0x88 == 0) is then evaluated by the ROM formula itself, so
   * the two booleans can no longer disagree with the actors they describe.
   */
  attackerIsCpuSide0?: boolean | undefined;
  defenderIsCpuSide0?: boolean | undefined;
  /**
   * GUARD/40 DATA RULE — DERIVED, combat-feel-gaps-decode-2026-07-05.md T1 (retraction of the
   * earlier "guard state" reading — there is NO hold-to-block state in the ROM). `zz_003cd5c_`
   * (chunk_0004.c:6814-6817): `victim is a borg && (rec.flagsA & 0x1000) && (victim pldata+0xa8
   * mask & 0x1000) -> dmg /= 40`. This is the victim's STATIC per-borg resistance mask (u16 @
   * pldata+0xa8, movementData.ts statusImmunityMasksForBorgId(...).immunityA). Census: 29/198
   * borgs carry bit 0x1000 (dragons, tanks/fortress family 6, some family 0a/0e borgs); only 2
   * real flagsA&0x1000 records exist (hpDamage 5000 nuke rows), so 5000/40 = 125 vs those borgs.
   */
  victimStatusImmunityA?: number | undefined;
  /** ATK-010: the victim's per-status immunity bit for the incoming hit's status zeroes HP
   *  damage for that hit (chunk_0004.c:6693-6699). No caller wires a real per-hit status id
   *  yet; absent = no change. */
  victimStatusImmune?: boolean | undefined;
  /**
   * Formula step 17 — `victim +0x5e0 & 0x4000000 -> x0.5` (chunk_0004.c:6807-6809). The bit's
   * WRITER is untraced ("UNKNOWN which state sets it (candidate: a spawn/drop-in protection)"),
   * and BorgRuntime has no +0x5e0 field, so nothing sets this today. Kept as a labeled,
   * never-true parameter rather than an invented state.
   */
  victimSpawnProtection5e0_4000000?: boolean | undefined;
}

export const damageFormulaSummary = {
  source: "research/decomp/data/damage-formula-tables-804335e0.json",
  consumer: "zz_003cd5c_ @0x8003cd5c",
  implementation: "packages/combat/src/damage/sourceDamage.ts (+ the ROM-wasm override seam)",
};

export type ChallengeDamageMode = 0 | 1 | 2;

export function challengeSideRanksForMode(mode: ChallengeDamageMode = 0): readonly [number, number] {
  if (mode === 1) return DATA.challengeSideRankBytes_804356e4.tuff;
  if (mode === 2) return DATA.challengeSideRankBytes_804356e4.insane;
  return DATA.challengeSideRankBytes_804356e4.normal;
}

/**
 * T2 DECODED: actor+0x3e6 (the formula's table selector) is the CPU-CONTROLLED flag — 1 when NO
 * human controls the actor. Derives the flag straight from BorgRuntime.ownerPlayer (null = CPU);
 * `undefined` ownerPlayer (shouldn't happen on a real BorgRuntime, but keeps this total) reads as
 * CPU too (fails toward "no proven human owner").
 */
export function heroTableFor(ownerPlayer: string | null | undefined): 0 | 1 {
  return ownerPlayer === null || ownerPlayer === undefined ? 1 : 0;
}

/**
 * T4 DECODED force-gauge ratio index (chunk_0004.c:6733-6737/6796-6800). Re-exported from
 * damage/sourceDamage.ts rather than re-implemented — the two copies of this three-line recipe
 * were a second place for it to drift.
 */
export const forceGaugeRatioIndex = sourceForceGaugeRatioIndex;

/** Parse a "pl####" profile id to the ROM's +0x3e8 borgNumber (family high byte, variant low).
 *  attackHitData.ts:141-142 documents the identity: the id's hex digits ARE the borgNumber.
 *  Returns 0 (the neutral matrix row) for a synthetic/non-hex id. */
function borgNumberFromProfileId(id: string): number {
  const n = Number.parseInt(id.slice(2), 16);
  return Number.isFinite(n) ? n : 0;
}

function defaultChallengeNormalSideRank(team: number): number {
  return team === 0
    ? DATA.challengeSideRankBytes_804356e4.normal[0]
    : DATA.challengeSideRankBytes_804356e4.normal[1];
}

function actorFrom(
  runtime: BorgRuntime,
  profile: BorgProfile,
  opts: {
    pinnedHeroFlag: 0 | 1 | undefined;
    pairAttack: boolean | undefined;
    power: number | undefined;
    handicapByte: number | undefined;
    forceRatioIndex: number | undefined;
    sideRank: number | undefined;
  },
): SourceDamageActor {
  return {
    borgNumber: borgNumberFromProfileId(profile.id),           // +0x3e8
    team: runtime.team,                                        // +0x88
    heroFlag: opts.pinnedHeroFlag ?? heroTableFor(runtime.ownerPlayer), // +0x3e6
    pairAttack: opts.pairAttack ? 1 : 0,                       // +0x6fc
    power: opts.power ?? 1,                                    // +0xc4 / +0xb4 (init untraced)
    hp: runtime.hp,                                            // +0x1c6 mirror
    maxHp: runtime.maxHp,                                      // +0x1c4
    handicap: opts.handicapByte ?? HANDICAP_NEUTRAL_BYTE,      // +0x43a
    comboRank: runtime.comboRank,                              // +0x6ca
    forceRatioIndex: opts.forceRatioIndex ?? 0,
    sideRank: opts.sideRank ?? defaultChallengeNormalSideRank(runtime.team),
    isBorg: true,                                              // +0x83 == 0
    isActive: true,                                            // +0x18 == 1
  };
}

/**
 * Adapter entry point: BorgRuntime-shaped hit -> the ROM formula. Delegates to
 * sourceDamage.computeBaseDamage, which is the single implementation of zz_003cd5c_ and the
 * ROM-wasm interception point (setRomDamageImplementation). No arithmetic happens here.
 */
export function computeSourceDamage(ctx: SourceDamageContext): number {
  const attacker = actorFrom(ctx.attacker, ctx.attackerProfile, {
    pinnedHeroFlag: ctx.heroTable,
    pairAttack: ctx.attackerPairAttack,
    power: ctx.attackerPower,
    handicapByte: ctx.attackerHandicapIndex,
    forceRatioIndex: ctx.attackerForceRatioIndex,
    sideRank: ctx.attackerSideRank,
  });
  const defender = actorFrom(ctx.victim, ctx.victimProfile, {
    pinnedHeroFlag: ctx.heroTable,
    pairAttack: ctx.defenderPairAttack,
    power: ctx.defenderPower,
    handicapByte: ctx.defenderHandicapIndex,
    forceRatioIndex: ctx.defenderForceRatioIndex,
    sideRank: ctx.defenderSideRank,
  });
  // basePower IS the ROM's `*param_1`: one value that seeds the formula AND indexes the
  // defender post-hit HP curve (chunk_0004.c:6693 / :6773).
  const basePower = ctx.record.hpDamage * (ctx.damageScale ?? 1);
  const romCtx: RomDamageContext = {
    flagsA: ctx.record.flagsA,                                  // record +0x10
    flagsB: ctx.record.flagsB,                                  // record +0x12
    attackerHpCurveIndex: ctx.record.attackerHpCurveIndex,      // record +0x06
    attackerForceCurveIndex: ctx.record.forceGaugeCurveIndex,   // record +0x07
    victimStatusImmune: ctx.victimStatusImmune === true,
    victimResistanceMask: ctx.victimStatusImmunityA ?? 0,
    victimSpawnProtection: ctx.victimSpawnProtection5e0_4000000 === true,
    // Challenge-mode gate only; the per-side CPU/side-0 conditions live in the formula.
    cpuHalvingEnabled: ctx.attackerIsCpuSide0 === true || ctx.defenderIsCpuSide0 === true,
  };
  return computeBaseDamage(attacker, defender, basePower, romCtx);
}
