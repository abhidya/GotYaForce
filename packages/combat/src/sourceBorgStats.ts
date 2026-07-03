import borgSourceStatsData from "./data/borgSourceStats.json" with { type: "json" };

export interface BorgSourceWeaponSlot {
  ammoType: number;
  ammoCount: number;
  chargeType: number;
  chargeCount: number;
}

export interface BorgSourceStats {
  maxHp: number;
  weaponSlots: [BorgSourceWeaponSlot, BorgSourceWeaponSlot];
}

type BorgSourceStatsFile = {
  schema: string;
  verification: {
    borgsJsonRows: number;
    runtimeProfiles: number;
    missingRows: string[];
    hpMismatches: Array<{ id: string; catalogHp: number | null; sourceHp: number }>;
  };
  profiles: Record<string, BorgSourceStats>;
};

const DATA = borgSourceStatsData as unknown as BorgSourceStatsFile;

export const borgSourceStatsSummary = DATA.verification;

export function sourceStatsForBorgId(id: string): BorgSourceStats | null {
  return DATA.profiles[id.toLowerCase()] ?? null;
}
