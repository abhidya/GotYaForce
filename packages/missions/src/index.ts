// @gf/missions — story/mission progression and the gacha/GET economy. JSON state machine
// for mission -> win/lose -> flags -> unlock/GET, plus weighted GET RNG enforcing the
// 2000-borg / 1000-crystal caps (caps "exact", rates "close"). Sources: mission *.bin/*.mdt
// data + RE wiki GET section. (PHASE0 §7 mission/gacha, §8.)

export type AdventureStageId = string | number;

export type AdventureStage = {
  stage: AdventureStageId;
  name: string;
  arena: string;
  enemies: readonly string[];
  boss?: string | null;
  confidence?: string | null;
};

export type AdventureStagesData = readonly AdventureStage[] | {
  stages: readonly AdventureStage[];
};

export type AdventureBorg = {
  id: string;
  name: string;
  energy?: number | null;
  hasModel?: boolean;
  model?: string | null;
};

export type AdventureBorgData = readonly AdventureBorg[] | {
  borgs: readonly AdventureBorg[];
};

export type ResolvedAdventureEnemy = {
  name: string;
  id: string | null;
  energy: number | null;
  modelAvailable: boolean;
};

export type ResolvedAdventureStage = {
  id: string;
  name: string;
  arena: string;
  boss: string | null;
  confidence: string | null;
  enemies: ResolvedAdventureEnemy[];
  enemyForceEnergy: number;
};

type BorgMatch = AdventureBorg | null;

export function resolveAdventureStage(
  stagesData: AdventureStagesData,
  borgData: AdventureBorgData,
  stageId: AdventureStageId,
): ResolvedAdventureStage | null {
  const stage = readStages(stagesData).find((item) => String(item.stage) === String(stageId));
  if (!stage) return null;

  return resolveAdventureStageEntry(stage, borgData);
}

export function resolveAdventureStageEntry(
  stage: AdventureStage,
  borgData: AdventureBorgData,
): ResolvedAdventureStage {
  const index = buildAdventureBorgIndex(borgData);
  const enemies = stage.enemies.map((name) => resolveAdventureEnemy(name, index));

  return {
    id: String(stage.stage),
    name: stage.name,
    arena: stage.arena,
    boss: stage.boss ?? null,
    confidence: stage.confidence ?? null,
    enemies,
    enemyForceEnergy: enemies.reduce((total, enemy) => total + (enemy.energy ?? 0), 0),
  };
}

export function resolveAdventureEnemy(
  name: string,
  index: AdventureBorgIndex,
): ResolvedAdventureEnemy {
  const borg = findAdventureBorg(name, index);

  return {
    name,
    id: borg?.id ?? null,
    energy: borg?.energy ?? null,
    modelAvailable: borg ? borg.hasModel === true || Boolean(borg.model) : false,
  };
}

export type AdventureBorgIndex = {
  exactNames: ReadonlyMap<string, BorgMatch>;
  normalizedNames: ReadonlyMap<string, BorgMatch>;
};

export function buildAdventureBorgIndex(borgData: AdventureBorgData): AdventureBorgIndex {
  const exactNames = new Map<string, BorgMatch>();
  const normalizedNames = new Map<string, BorgMatch>();

  for (const borg of readBorgs(borgData)) {
    addUnique(exactNames, borg.name.trim().toLocaleLowerCase(), borg);
    addUnique(normalizedNames, normalizeAdventureName(borg.name), borg);
  }

  return { exactNames, normalizedNames };
}

export function findAdventureBorg(name: string, index: AdventureBorgIndex): AdventureBorg | null {
  const exact = index.exactNames.get(name.trim().toLocaleLowerCase());
  if (exact !== undefined) return exact;

  const normalized = index.normalizedNames.get(normalizeAdventureName(name));
  return normalized ?? null;
}

export function normalizeAdventureName(name: string): string {
  return name
    .normalize("NFKD")
    .replace(/[\u0300-\u036f]/g, "")
    .replace(/[^\p{Letter}\p{Number}]+/gu, " ")
    .trim()
    .replace(/\s+/g, " ")
    .toLocaleLowerCase();
}

function readStages(stagesData: AdventureStagesData): readonly AdventureStage[] {
  return "stages" in stagesData ? stagesData.stages : stagesData;
}

function readBorgs(borgData: AdventureBorgData): readonly AdventureBorg[] {
  return "borgs" in borgData ? borgData.borgs : borgData;
}

function addUnique(map: Map<string, BorgMatch>, key: string, borg: AdventureBorg): void {
  if (!key) return;
  map.set(key, map.has(key) ? null : borg);
}
