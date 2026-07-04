import type {
  BattleConfig as CombatBattleConfig,
  StageBounds,
  StageCollision,
} from "@gf/combat";
import type { MissionBattleConfig } from "./battle-config.js";

export interface CombatStageCatalog {
  defaultStageId: string;
  hasStageCollision(stageId: string): boolean;
}

export interface CombatBattleConfigOptions {
  stageCatalog?: CombatStageCatalog;
  stageId?: string;
  bounds?: StageBounds;
  collision?: StageCollision;
}

export function playerIdFor(playerIndex: number): string {
  return `p${playerIndex}`;
}

export function stageIdForArena(arena: string | undefined, catalog: CombatStageCatalog): string {
  const normalized = arena?.trim().toLowerCase() ?? "";
  if (normalized && catalog.hasStageCollision(normalized)) return normalized;
  if (normalized === "challenge") return catalog.defaultStageId;
  return catalog.defaultStageId;
}

export function stageIdForBattleConfig(cfg: MissionBattleConfig, catalog: CombatStageCatalog): string {
  const meta = cfg.meta;
  const stageByte = meta?.stageByte;
  const stageSubtable = meta?.stageSubtable;
  if (Number.isInteger(stageByte) && Number.isInteger(stageSubtable)) {
    const familyByte = (stageSubtable as number) * 0x20 + (stageByte as number);
    const familyId = stageIdFromByte(familyByte);
    if (catalog.hasStageCollision(familyId)) return familyId;

    const baseId = stageIdFromByte(stageByte as number);
    if (catalog.hasStageCollision(baseId)) return baseId;
  }

  return stageIdForArena(cfg.arena, catalog);
}

export function toCombatBattleConfig(
  cfg: MissionBattleConfig,
  options: CombatBattleConfigOptions = {},
): CombatBattleConfig {
  const stageId = options.stageId ?? resolveStageId(cfg, options.stageCatalog);
  return {
    stageId,
    ...(options.bounds ? { bounds: options.bounds } : {}),
    ...(options.collision ? { collision: options.collision } : {}),
    ...(cfg.timeLimitFrames !== undefined ? { timeLimitFrames: cfg.timeLimitFrames } : {}),
    ...(cfg.timerFrozen !== undefined ? { timerFrozen: cfg.timerFrozen } : {}),
    ...(cfg.meta?.challengeMode !== undefined ? { challengeMode: cfg.meta.challengeMode } : {}),
    forces: cfg.forces.map((force) => ({
      team: force.team === "player" ? 0 : 1,
      ownerPlayer: force.ownerPlayer == null ? null : playerIdFor(force.ownerPlayer),
      borgIds: [...force.borgIds],
    })),
  };
}

function resolveStageId(cfg: MissionBattleConfig, catalog: CombatStageCatalog | undefined): string {
  if (!catalog) {
    throw new Error("toCombatBattleConfig: pass stageId or stageCatalog");
  }
  return stageIdForBattleConfig(cfg, catalog);
}

function stageIdFromByte(byte: number): string {
  return `st${Math.max(0, byte).toString(16).padStart(2, "0")}`;
}
