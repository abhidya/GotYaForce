import actorDataStatsData from "./data/actorDataStats.json" with { type: "json" };

export interface ActorDataCombatStats {
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
    exactMatches: Record<"defense" | "shot" | "attack" | "speed", number>;
    mismatches: unknown[];
  };
  profiles: Record<string, ActorDataCombatStats>;
};

const DATA = actorDataStatsData as ActorDataStatsFile;

export const actorDataCombatStatsSummary = DATA.verification;

export function actorDataCombatStatsForBorgId(id: string): ActorDataCombatStats | null {
  return DATA.profiles[id.toLowerCase()] ?? null;
}
