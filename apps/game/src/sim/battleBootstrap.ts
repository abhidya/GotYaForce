import type { StageAssets } from "@gf/assets";
import {
  createBattle,
  DEFAULT_BOUNDS,
  type Battle,
  type BorgStats,
  type RectStageBounds,
} from "@gf/combat";
import {
  playerIdFor,
  stageIdForBattleConfig,
  toCombatBattleConfig,
  type BattleConfig as MissionBattleConfig,
  type CombatStageCatalog,
} from "@gf/missions";

export interface BattleBootstrapOptions<TStageRenderState> {
  config: MissionBattleConfig;
  playerCount: number;
  stageCatalog: CombatStageCatalog;
  borgStats: readonly BorgStats[];
  loadStageAssets(stageId: string): Promise<StageAssets<TStageRenderState>>;
}

export interface BattleBootstrapResult<TStageRenderState> {
  battle: Battle;
  stageId: string;
  stageAssets: StageAssets<TStageRenderState>;
  stageBounds: RectStageBounds;
  localPlayerId: string;
  localPlayerIds: string[];
}

export async function createBattleBootstrap<TStageRenderState>(
  options: BattleBootstrapOptions<TStageRenderState>,
): Promise<BattleBootstrapResult<TStageRenderState>> {
  const humanPlayerCount = Math.max(1, Math.min(options.playerCount, 2));
  const stageId = stageIdForBattleConfig(options.config, options.stageCatalog);
  const stageAssets = await options.loadStageAssets(stageId);
  const stageBounds = stageAssets.bounds ?? defaultStageBounds();
  const combatCfg = toCombatBattleConfig(options.config, {
    stageId,
    bounds: stageBounds,
    ...(stageAssets.collision ? { collision: stageAssets.collision } : {}),
  });
  const battle = createBattle(combatCfg, options.borgStats);
  const localPlayerIds = Array.from({ length: humanPlayerCount }, (_, player) => playerIdFor(player));
  const localPlayerId = localPlayerIds[0] ?? playerIdFor(0);

  return {
    battle,
    stageId,
    stageAssets,
    stageBounds,
    localPlayerId,
    localPlayerIds,
  };
}

function defaultStageBounds(): RectStageBounds {
  return {
    minX: -DEFAULT_BOUNDS.x,
    maxX: DEFAULT_BOUNDS.x,
    minZ: -DEFAULT_BOUNDS.z,
    maxZ: DEFAULT_BOUNDS.z,
  };
}
