// Power Burst fusion pair table — RUNTIME data layer (ATK-018 wiring).
//
// DERIVED_ROM data: the pair table at DAT_802d352c, DOL-extracted by
// scripts/gen_fusion_pairs.py into research/decomp/data/fusion-pairs-802d352c.json
// (behavior-notes.md (aj)), reshaped for runtime by scripts/gen-fusion-pairs-runtime.mjs
// into data/fusionPairs.json. The table has 17 family slots; ONLY families 5 and 6 are
// non-null. Each populated variant carries a -1-terminated sub-list of directed
// (partner -> result) spawn-id pairs, so this module exposes exactly that: which borg
// pairs can fuse, and which borg the fusion produces. The 12 directed entries:
//
//   pl0505 DEATH HEAD     + pl0506 CYBER DRAGON       -> pl0507 CYBER DEATH DRAGON
//   pl0511 MACHINE HEAD   + pl0512 MECHANICAL DRAGON  -> pl0513 MACHINE DRAGON
//   pl0600 MACHINE RED    + pl0601 MACHINE BLUE       -> pl0602 CYBER MACHINE SEIRYU
//   pl0600 MACHINE RED    + pl0609 CYBER ATLAS        -> pl060c CYBER MACHINE BYAKKO
//   pl0601 MACHINE BLUE   + pl0608 CYBER MARS         -> pl060e CYBER MACHINE GENBU
//   pl0608 CYBER MARS     + pl0609 CYBER ATLAS        -> pl060a CYBER MACHINE SUZAKU
// (plus the reverse direction of each, listed explicitly in the ROM table.)
//
// WHAT IS NOT WIRED (still trace-blocked, do not invent): the ACTIVATION path — the
// simultaneous-burst trigger, the co-op control split (which player drives the fused
// borg), and the fusion state machine behind BorgRuntime.fusionPartnerUid/fusionState
// (ROM +0x4a4/+0x4a1, with the +0x6fb timer read in both the burst and fusion loops).
// Those semantics need trace T3 to reconcile (see types.ts on fusionPartnerUid and
// burst.ts's header note). battle.ts therefore does not consume this module yet; it is
// the data layer that activation work will gate on — the same staging commandMoveTables
// went through before commandDispatch consumed it.

import fusionPairsData from "./data/fusionPairs.json" with { type: "json" };

/** One directed fusion entry: `self` borg + `partner` borg fuse into `result` borg.
 *  Ids are roster borg ids (pl<family:02x><variant:02x>), matching the ROM spawn-id
 *  packing family << 8 | variant (behavior-notes.md (n)). */
export interface FusionPair {
  self: string;
  partner: string;
  result: string;
}

/** All directed fusion pairs from the ROM table, in table order (12 entries). */
export const FUSION_PAIRS: readonly FusionPair[] = fusionPairsData.pairs as readonly FusionPair[];

const resultByPairKey = new Map<string, string>();
const pairsBySelf = new Map<string, FusionPair[]>();
const resultIds = new Set<string>();
for (const pair of FUSION_PAIRS) {
  resultByPairKey.set(`${pair.self}+${pair.partner}`, pair.result);
  const list = pairsBySelf.get(pair.self) ?? [];
  list.push(pair);
  pairsBySelf.set(pair.self, list);
  resultIds.add(pair.result);
}

/**
 * The borg produced when `selfId` fuses with `partnerId`, or null when the ROM pair
 * table has no such entry (including borgs from families with empty table slots).
 * Directional like the table: a hit requires the entry on `selfId`'s own sub-list —
 * every fusable pair in the ROM data happens to be listed in both directions, but this
 * lookup does not assume symmetry the table does not state.
 */
export function fusionResultForPair(selfId: string, partnerId: string): string | null {
  return resultByPairKey.get(`${selfId.toLowerCase()}+${partnerId.toLowerCase()}`) ?? null;
}

/** Every directed fusion entry carried by `id`'s own sub-list (empty for non-fusable borgs). */
export function fusionPairsForBorgId(id: string): readonly FusionPair[] {
  return pairsBySelf.get(id.toLowerCase()) ?? [];
}

/** Partner borg ids `id` can fuse with (from its own sub-list; empty for non-fusable borgs). */
export function fusionPartnerIdsForBorgId(id: string): readonly string[] {
  return fusionPairsForBorgId(id).map((pair) => pair.partner);
}

/** True when `id` is the product of at least one fusion in the ROM table. */
export function isFusionResultBorgId(id: string): boolean {
  return resultIds.has(id.toLowerCase());
}

export interface FusionPairCoverage {
  /** Directed (self, partner) entries in the table. */
  pairCount: number;
  /** Distinct borgs that carry at least one fusion entry. */
  selfBorgCount: number;
  /** Distinct borgs produced by a fusion. */
  resultBorgCount: number;
}

/** Coverage summary of the wired pair table (ATK-018 audits/tests). */
export function fusionPairCoverage(): FusionPairCoverage {
  return {
    pairCount: FUSION_PAIRS.length,
    selfBorgCount: pairsBySelf.size,
    resultBorgCount: resultIds.size,
  };
}
