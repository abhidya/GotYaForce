import actorDataStatsData from "./data/actorDataStats.json" with { type: "json" };

export interface ActorDataCombatStats {
  /**
   * Borg-type enum from actor data byte 0x1a0 (DERIVED, verified bijective against
   * borgs.json "type" for all 190 borgs with metadata):
   * 0=long range, 1=short range, 2=speed, 3=almighty, 4=support.
   */
  typeCode: number;
  /**
   * Raw air-jump count byte 0x1a3 (DERIVED on its verifiable domain: equals N for all
   * "Air jump level N" borgs, 0 for all "Boost jump" borgs; 0xff observed for most
   * "N/A" flyers and normalized to no discrete air jumps by buildProfile.
   */
  airJump: number;
  defense: number;
  shot: number;
  attack: number;
  speed: number;
  sourcePath: string;
  sourceSha1: string;
}

type ActorDataStatsFile = {
  verification: {
    matchedMetadataRows: number;
    exactMatches: Record<string, number>;
    mismatches: unknown[];
  };
  profiles: Record<string, ActorDataCombatStats>;
};

const DATA = actorDataStatsData as ActorDataStatsFile;

export const actorDataCombatStatsSummary = DATA.verification;

export function actorDataCombatStatsForBorgId(id: string): ActorDataCombatStats | null {
  return DATA.profiles[id.toLowerCase()] ?? null;
}
