// @gf/missions — adventure.ts
//
// ADVENTURE (Story) mode content layer: parses packages/assets/data/stages.json
// into an ordered campaign of `BattleConfig`s.
//
// Per stage we:
//  - resolve each enemy NAME → borg id against the roster (fuzzy name match),
//  - parse spawn COUNTS out of `notes` (e.g. "7x Beta II, 1x Omega", "8x Mu",
//    "2x each", "18 random"),
//  - carry the arena id and boss flag,
//  - expose getStage(i) / total and a simple win → next-stage progression.
//
// stages.json confidence varies (Confirmed / Likely / Speculative) and some
// enemy names are guide-transcription approximations — unresolved names are
// reported in the battle meta rather than silently dropped.

import type { BattleConfig, BattleForce } from "./battle-config.js";
import { readBorgs, type BorgData, type Borg } from "./borg-data.js";

/** A stage entry as it appears in stages.json. */
export interface AdventureStageEntry {
  stage: string | number;
  name: string;
  arena: string;
  enemies: string[];
  boss?: string | null;
  notes?: string;
  confidence?: string;
}

/** stages.json shape: { meta, stages[] } or a bare stages array. */
export type StagesData =
  | { stages: AdventureStageEntry[] }
  | readonly AdventureStageEntry[];

export function readStages(data: StagesData): readonly AdventureStageEntry[] {
  return "stages" in data ? data.stages : data;
}

/** A resolved enemy spawn: name → id (or null) with a parsed count. */
export interface ResolvedEnemy {
  name: string;
  id: string | null;
  energy: number | null;
  count: number;
}

/** A fully resolved campaign stage. */
export interface AdventureStage {
  /** Stage id as string ("1", "T1", "M3", "28b"...). */
  id: string;
  name: string;
  arena: string;
  boss: string | null;
  isBoss: boolean;
  confidence: string | null;
  enemies: ResolvedEnemy[];
  /** Names that did not resolve to a borg id. */
  unresolved: string[];
  /** Summed enemy energy (count × energy, skipping unresolved). */
  enemyForceEnergy: number;
  /** The battle the simulation should run for this stage. */
  battle: BattleConfig;
}

/** The whole campaign + progression. */
export interface AdventureCampaign {
  stages: AdventureStage[];
  total: number;
  /** Get a stage by 0-based index. */
  getStage(i: number): AdventureStage | null;
  /** Get a stage by its id ("1", "M3", "28b"...). */
  getStageById(id: string | number): AdventureStage | null;
  /** Win → the next stage index, or null if that was the last. */
  next(currentIndex: number, win: boolean): AdventureStage | null;
}

export interface AdventureOptions {
  /** A player force to embed in each generated battle (optional). */
  playerForce?: BattleForce;
  /** Default spawn count when a name has no "Nx" hint. Default 1. */
  defaultCount?: number;
}

/**
 * Parse stages.json + borgs.json into an ordered campaign of BattleConfigs.
 */
export function createAdventureCampaign(
  stagesData: StagesData,
  borgData: BorgData,
  options: AdventureOptions = {},
): AdventureCampaign {
  const index = buildNameIndex(borgData);
  const entries = readStages(stagesData);

  const stages: AdventureStage[] = entries.map((entry, i) =>
    resolveStage(entry, index, i, options),
  );

  return {
    stages,
    total: stages.length,
    getStage(i: number) {
      return stages[i] ?? null;
    },
    getStageById(id: string | number) {
      const key = String(id);
      return stages.find((s) => s.id === key) ?? null;
    },
    next(currentIndex: number, win: boolean) {
      if (!win) return null;
      return stages[currentIndex + 1] ?? null;
    },
  };
}

function resolveStage(
  entry: AdventureStageEntry,
  index: NameIndex,
  i: number,
  options: AdventureOptions,
): AdventureStage {
  const counts = parseCounts(entry.notes ?? "");
  const defaultCount = options.defaultCount ?? 1;

  const enemies: ResolvedEnemy[] = entry.enemies.map((name) => {
    const borg = matchBorg(name, index);
    const count = lookupCount(name, counts) ?? defaultCount;
    return {
      name,
      id: borg?.id ?? null,
      energy: borg?.energy ?? null,
      count,
    };
  });

  const unresolved = enemies.filter((e) => e.id === null).map((e) => e.name);
  const enemyForceEnergy = enemies.reduce(
    (sum, e) => sum + (e.energy ?? 0) * e.count,
    0,
  );

  // Expand counts into an ordered enemy borg id list (each spawn = one entry).
  const enemyBorgIds: string[] = [];
  for (const e of enemies) {
    if (e.id === null) continue;
    for (let n = 0; n < e.count; n++) enemyBorgIds.push(e.id);
  }

  const isBoss = Boolean(entry.boss);

  const forces: BattleForce[] = [];
  if (options.playerForce) forces.push(options.playerForce);
  forces.push({
    team: "enemy",
    ownerPlayer: null,
    borgIds: enemyBorgIds,
  });

  const battle: BattleConfig = {
    arena: entry.arena,
    label: entry.name,
    forces,
    meta: {
      mode: "adventure",
      index: i,
      enemyForceEnergy,
      boss: entry.boss ?? null,
      confidence: entry.confidence ?? null,
      unresolvedEnemies: unresolved,
    },
  };

  return {
    id: String(entry.stage),
    name: entry.name,
    arena: entry.arena,
    boss: entry.boss ?? null,
    isBoss,
    confidence: entry.confidence ?? null,
    enemies,
    unresolved,
    enemyForceEnergy,
    battle,
  };
}

// ---------------------------------------------------------------------------
// Spawn-count parsing from free-text notes.
// Handles: "7x Beta II, 1x Omega", "8x Mu.", "2x Drill Robot, 4x Beta II",
//          "6x ICBM Tank.", "24x Death ICBM.", "2x each", "18 random units".
// ---------------------------------------------------------------------------

interface ParsedCounts {
  /** normalized-name → count, e.g. "beta ii" → 7. */
  byName: Map<string, number>;
  /** "Nx each" applies N to every enemy with no explicit count. */
  each: number | null;
}

export function parseCounts(notes: string): ParsedCounts {
  const byName = new Map<string, number>();
  let each: number | null = null;

  // "2x each" / "2 each"
  const eachMatch = notes.match(/(\d+)\s*x?\s*each/i);
  if (eachMatch?.[1]) each = parseInt(eachMatch[1], 10);

  // "7x Beta II" / "8x Mu" / "24x Death ICBM" / "6x Ultimate Cannon"
  // Capture the count, then the trailing phrase up to a comma/period/end.
  const re = /(\d+)\s*x\s*([A-Za-z][A-Za-z0-9 .+()'\-]*?)(?=,|\.|;|$)/g;
  let m: RegExpExecArray | null;
  while ((m = re.exec(notes)) !== null) {
    const n = m[1];
    const phrase = m[2];
    if (!n || !phrase) continue;
    const key = normalizeName(phrase);
    if (key) byName.set(key, parseInt(n, 10));
  }

  return { byName, each };
}

/**
 * Resolve a stage enemy name to its parsed count. The notes often use short
 * forms ("Beta II", "Omega", "Mu") while enemies[] use full roster names
 * ("DEATH BORG BETA II"). We match if the note key is a substring of the
 * normalized enemy name (or vice-versa).
 */
function lookupCount(enemyName: string, counts: ParsedCounts): number | null {
  const norm = normalizeName(enemyName);
  // Exact first.
  const exact = counts.byName.get(norm);
  if (exact !== undefined) return exact;

  // Substring either direction (note "beta ii" ⊂ "death borg beta ii").
  for (const [key, n] of counts.byName) {
    if (norm.includes(key) || key.includes(norm)) return n;
  }

  if (counts.each !== null) return counts.each;
  return null;
}

// ---------------------------------------------------------------------------
// Name → borg matching (fuzzy). Mirrors the resolver in index.ts but local so
// adventure.ts is self-contained.
// ---------------------------------------------------------------------------

export interface NameIndex {
  byNormalized: ReadonlyMap<string, Borg | null>;
}

export function buildNameIndex(borgData: BorgData): NameIndex {
  const byNormalized = new Map<string, Borg | null>();
  for (const borg of readBorgs(borgData)) {
    const key = normalizeName(borg.name);
    if (!key) continue;
    const existing = byNormalized.get(key);
    if (existing === undefined) {
      // First borg with this normalized name.
      byNormalized.set(key, borg);
      continue;
    }
    if (existing === null) continue; // already marked ambiguous
    // Collision. Some roster names are true duplicates (e.g. two
    // "CYBER DEATH DRAGON" / "MACHINE DRAGON" entries that differ only by id /
    // model availability). Treat them as the SAME unit and prefer the entry
    // that has a model — that is the canonical, loadable one. Genuinely
    // distinct units that happen to normalize alike are kept as the first
    // (they are disambiguated by the polarity-preserving normalizer below).
    if (existing.name.trim().toLocaleLowerCase() ===
        borg.name.trim().toLocaleLowerCase()) {
      if (!hasModel(existing) && hasModel(borg)) byNormalized.set(key, borg);
    }
    // else: different display names collided — keep first; do not null.
  }
  return { byNormalized };
}

function hasModel(b: Borg): boolean {
  return b.hasModel === true || Boolean(b.model);
}

export function matchBorg(name: string, index: NameIndex): Borg | null {
  const key = normalizeName(name);
  if (!key) return null;

  const exact = index.byNormalized.get(key);
  if (exact) return exact;

  // "Random" placeholders never resolve to a single borg.
  if (key === "random") return null;

  return null;
}

export function normalizeName(name: string): string {
  return name
    .normalize("NFKD")
    .replace(/[̀-ͯ]/g, "")
    // Preserve +/- polarity markers (MAGNET ROBOT (+) vs (-)) before stripping
    // other punctuation; collapse them to a trailing " plus" / " minus" token.
    .replace(/\(\s*\+\s*\)/g, " plus")
    .replace(/\(\s*-\s*\)/g, " minus")
    .replace(/[^\p{Letter}\p{Number}]+/gu, " ")
    .trim()
    .replace(/\s+/g, " ")
    .toLocaleLowerCase();
}
