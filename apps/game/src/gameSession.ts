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
  type BattleResults,
  type ChallengeRun,
  type ChallengeRunOptions,
  type CombatStageCatalog,
  type GetDrop,
  type MissionBattleConfig,
} from "@gf/missions";

export type GameScreen =
  | "loading"
  | "title"
  | "menu"
  | "difficulty"
  | "players"
  | "load-box"
  | "select-force"
  | "force"
  | "briefing"
  | "battle"
  | "results"
  | "gets";

export interface SessionForceSlot {
  no: number;
  name: string;
  borgIds: string[];
}

export interface ResultStats {
  attack: number;
  hitRatio: number;
  dodgeRatio: number;
  enemyBorgsDefeated: number;
  enemyTotalCost: number;
  playerBorgsDefeated: number;
  playerTotalCost: number;
  allyBorgsDefeated: number;
  grandTotal: number;
}

export type DeepReadonly<T> =
  T extends (...args: never[]) => unknown ? T
    : T extends readonly (infer Item)[] ? readonly DeepReadonly<Item>[]
      : T extends object ? { readonly [Key in keyof T]: DeepReadonly<T[Key]> }
        : T;

export interface PostBattleSnapshot {
  readonly result: "win" | "lose";
  readonly stats: DeepReadonly<ResultStats>;
  readonly battleResults: DeepReadonly<BattleResults>;
  readonly drops: readonly DeepReadonly<GetDrop>[];
}

export interface GameSessionSnapshot {
  readonly screen: GameScreen;
  readonly budget: number;
  readonly playerCount: number;
  readonly selectedForceSlot: number;
  readonly forceSlots: readonly DeepReadonly<SessionForceSlot>[];
  readonly forceEditorReturnTarget: "menu" | "select-force";
  readonly menuMode: "challenge" | "edit-force";
  readonly pendingBattleConfig: DeepReadonly<MissionBattleConfig> | null;
  readonly postBattle: PostBattleSnapshot | null;
  readonly run: DeepReadonly<Pick<ChallengeRun, "current" | "total" | "score" | "ended">> | null;
}

export type GameSessionEvent =
  | { type: "boot-ready" }
  | { type: "title-enter" }
  | { type: "menu-select"; mode: "challenge" | "edit-force" }
  | { type: "back" }
  | { type: "difficulty-select"; budget: number }
  | { type: "players-select"; playerCount: number }
  | { type: "box-continue" }
  | { type: "force-slots-synced"; slots: readonly SessionForceSlot[] }
  | { type: "force-slot-selected"; slotIndex: number }
  | { type: "force-slot-confirm"; slot: SessionForceSlot }
  | { type: "force-slot-edit"; slot: SessionForceSlot }
  | { type: "force-editor-confirm"; borgIds: readonly string[] }
  | { type: "force-editor-quit" }
  | { type: "briefing-confirm" }
  | { type: "battle-started" }
  | { type: "battle-preparation-failed" }
  | { type: "battle-abandoned" }
  | { type: "battle-resolved"; battleResults: BattleResults; stats: ResultStats; drops: readonly GetDrop[] }
  | { type: "advance" };

export type GameSessionEffect =
  | { type: "render"; screen: GameScreen }
  | { type: "prepare-battle" }
  | { type: "teardown-battle" };

export interface PreparedBattle<TStageRenderState> {
  battle: Battle;
  config: MissionBattleConfig;
  stageId: string;
  stageAssets: StageAssets<TStageRenderState>;
  stageBounds: RectStageBounds;
  localPlayerId: string;
  localPlayerIds: string[];
}

interface PostBattleState {
  result: "win" | "lose";
  stats: ResultStats;
  battleResults: BattleResults;
  drops: GetDrop[];
}

export interface GameSessionDependencies<TStageRenderState> {
  initialForceSlots: readonly SessionForceSlot[];
  forceFromSlot(slot: SessionForceSlot): string[];
  validForce(borgIds: readonly string[]): string[];
  createRun(options: ChallengeRunOptions): ChallengeRun;
  borgs: ChallengeRunOptions["borgs"];
  stageCatalog: CombatStageCatalog;
  borgStats: readonly BorgStats[];
  loadStageAssets(stageId: string): Promise<StageAssets<TStageRenderState>>;
}

export interface GameSession<TStageRenderState> {
  dispatch(event: GameSessionEvent): readonly GameSessionEffect[];
  snapshot(): GameSessionSnapshot;
  prepareBattle(): Promise<PreparedBattle<TStageRenderState>>;
}

export class InvalidSessionEventError extends Error {
  constructor(eventType: GameSessionEvent["type"], screen: GameScreen) {
    super(`Game session event "${eventType}" is invalid while on "${screen}"`);
    this.name = "InvalidSessionEventError";
  }
}

/** Challenge navigation/progression module. Browser and battle-runtime work stay at its seam. */
export function createGameSession<TStageRenderState>(
  dependencies: GameSessionDependencies<TStageRenderState>,
): GameSession<TStageRenderState> {
  let screen: GameScreen = "loading";
  let budget = 2000;
  let playerCount = 1;
  let selectedForceSlot = 0;
  let forceSlots = cloneSlots(dependencies.initialForceSlots);
  let forceEditorReturnTarget: "menu" | "select-force" = "select-force";
  let menuMode: "challenge" | "edit-force" = "challenge";
  let run: ChallengeRun | null = null;
  let pendingBattleConfig: MissionBattleConfig | null = null;
  let postBattle: PostBattleState | null = null;

  function render(next: GameScreen): readonly GameSessionEffect[] {
    screen = next;
    return [{ type: "render", screen: next }];
  }

  function reject(event: GameSessionEvent): never {
    throw new InvalidSessionEventError(event.type, screen);
  }

  function selectedSlot(): SessionForceSlot {
    const fallback = dependencies.initialForceSlots[0];
    const slot = forceSlots[selectedForceSlot] ?? forceSlots[0] ?? fallback;
    if (!slot) throw new Error("Game session requires at least one force slot");
    return slot;
  }

  function selectSlotByNo(slot: SessionForceSlot): void {
    const index = forceSlots.findIndex((candidate) => candidate.no === slot.no);
    selectedForceSlot = index >= 0 ? index : 0;
    if (forceSlots[selectedForceSlot]) forceSlots[selectedForceSlot] = cloneSlot(slot);
  }

  function updateSelectedForce(borgIds: readonly string[]): void {
    const slot = selectedSlot();
    forceSlots[selectedForceSlot] = { ...slot, borgIds: dependencies.validForce(borgIds) };
  }

  function beginRun(): readonly GameSessionEffect[] {
    const humanPlayerCount = Math.max(1, Math.min(playerCount, 2));
    const playerForces = Array.from({ length: humanPlayerCount }, (_, player) => {
      const slot = player === 0
        ? selectedSlot()
        : forceSlots[(selectedForceSlot + player) % forceSlots.length] ?? selectedSlot();
      return { player, borgIds: dependencies.forceFromSlot(slot) };
    });
    updateSelectedForce(playerForces[0]?.borgIds ?? []);
    run = dependencies.createRun({
      budget,
      playerCount: humanPlayerCount,
      playerForces,
      borgs: dependencies.borgs,
    });
    pendingBattleConfig = cloneMissionBattleConfigOrNull(run.getCurrentBattle());
    postBattle = null;
    if (!pendingBattleConfig) {
      menuMode = "challenge";
      return render("menu");
    }
    return render("briefing");
  }

  function advanceRun(): readonly GameSessionEffect[] {
    const effects: GameSessionEffect[] = [{ type: "teardown-battle" }];
    const last = postBattle ? cloneBattleResults(postBattle.battleResults) : null;
    postBattle = null;
    if (!run || !last) {
      pendingBattleConfig = null;
      menuMode = "challenge";
      screen = "menu";
      return [...effects, { type: "render", screen }];
    }
    const progress = run.next(last);
    pendingBattleConfig = progress.action === "advance"
      ? cloneMissionBattleConfigOrNull(progress.nextBattle)
      : null;
    if (pendingBattleConfig) {
      screen = "briefing";
    } else {
      menuMode = "challenge";
      screen = "menu";
    }
    return [...effects, { type: "render", screen }];
  }

  return {
    dispatch(event) {
      switch (event.type) {
        case "boot-ready":
          return screen === "loading" ? render("title") : reject(event);
        case "title-enter":
          if (screen !== "title") return reject(event);
          menuMode = "challenge";
          return render("menu");
        case "menu-select":
          if (screen !== "menu") return reject(event);
          if (event.mode === "challenge") {
            menuMode = "challenge";
            return render("difficulty");
          }
          forceEditorReturnTarget = "menu";
          menuMode = "edit-force";
          return render("force");
        case "back":
          if (screen === "difficulty") return render("menu");
          if (screen === "players") return render("difficulty");
          if (screen === "load-box") return render("players");
          if (screen === "select-force") return render("load-box");
          if (screen === "briefing") {
            pendingBattleConfig = null;
            return render("select-force");
          }
          return reject(event);
        case "difficulty-select":
          if (screen !== "difficulty") return reject(event);
          budget = event.budget;
          return render("players");
        case "players-select":
          if (screen !== "players") return reject(event);
          playerCount = Math.max(1, Math.min(event.playerCount, 2));
          return render("load-box");
        case "box-continue":
          return screen === "load-box" ? render("select-force") : reject(event);
        case "force-slots-synced":
          if (screen !== "select-force") return reject(event);
          forceSlots = cloneSlots(event.slots);
          selectedForceSlot = Math.min(selectedForceSlot, Math.max(0, forceSlots.length - 1));
          return [];
        case "force-slot-selected":
          if (screen !== "select-force") return reject(event);
          if (!Number.isInteger(event.slotIndex) || event.slotIndex < 0 || event.slotIndex >= forceSlots.length) {
            throw new RangeError(`Invalid force slot index: ${event.slotIndex}`);
          }
          selectedForceSlot = event.slotIndex;
          return [];
        case "force-slot-confirm":
          if (screen !== "select-force") return reject(event);
          selectSlotByNo(event.slot);
          return beginRun();
        case "force-slot-edit":
          if (screen !== "select-force") return reject(event);
          selectSlotByNo(event.slot);
          forceEditorReturnTarget = "select-force";
          return render("force");
        case "force-editor-confirm":
          if (screen !== "force") return reject(event);
          updateSelectedForce(event.borgIds);
          return render(forceEditorReturnTarget === "menu" ? "menu" : "select-force");
        case "force-editor-quit":
          return screen === "force"
            ? render(forceEditorReturnTarget === "menu" ? "menu" : "select-force")
            : reject(event);
        case "briefing-confirm":
          if (screen !== "briefing" || !pendingBattleConfig) return reject(event);
          screen = "loading";
          return [{ type: "render", screen }, { type: "prepare-battle" }];
        case "battle-started":
          return screen === "loading" && pendingBattleConfig ? render("battle") : reject(event);
        case "battle-preparation-failed":
          if (screen === "select-force") return render("select-force");
          if (screen !== "loading") return reject(event);
          pendingBattleConfig = null;
          return render("select-force");
        case "battle-abandoned":
          if (screen !== "battle") return reject(event);
          pendingBattleConfig = null;
          postBattle = null;
          menuMode = "challenge";
          return [{ type: "teardown-battle" }, ...render("menu")];
        case "battle-resolved":
          if (screen !== "battle") return reject(event);
          postBattle = {
            result: event.battleResults.outcome === "WIN" ? "win" : "lose",
            stats: { ...event.stats },
            battleResults: cloneBattleResults(event.battleResults),
            drops: event.drops.map((drop) => ({ ...drop })),
          };
          return render("results");
        case "advance":
          if (screen === "results" && (postBattle?.drops.length ?? 0) > 0) return render("gets");
          if (screen === "results" || screen === "gets") return advanceRun();
          return reject(event);
      }
    },

    snapshot() {
      return {
        screen,
        budget,
        playerCount,
        selectedForceSlot,
        forceSlots: cloneSlots(forceSlots),
        forceEditorReturnTarget,
        menuMode,
        pendingBattleConfig: cloneMissionBattleConfigOrNull(pendingBattleConfig),
        postBattle: postBattle
          ? {
              ...postBattle,
              stats: { ...postBattle.stats },
              battleResults: cloneBattleResults(postBattle.battleResults),
              drops: postBattle.drops.map((drop) => ({ ...drop })),
            }
          : null,
        run: run ? { current: run.current, total: run.total, score: run.score, ended: run.ended } : null,
      };
    },

    async prepareBattle() {
      if (screen !== "loading" || !pendingBattleConfig) {
        throw new InvalidSessionEventError("briefing-confirm", screen);
      }
      const config = cloneMissionBattleConfig(pendingBattleConfig);
      try {
        const stageId = stageIdForBattleConfig(config, dependencies.stageCatalog);
        const stageAssets = await dependencies.loadStageAssets(stageId);
        const stageBounds = stageAssets.bounds ?? defaultStageBounds();
        const combatConfig = toCombatBattleConfig(config, {
          stageId,
          bounds: stageBounds,
          ...(stageAssets.collision ? { collision: stageAssets.collision } : {}),
        });
        const battle = createBattle(combatConfig, dependencies.borgStats);
        const humanPlayerCount = Math.max(1, Math.min(playerCount, 2));
        const localPlayerIds = Array.from({ length: humanPlayerCount }, (_, player) => playerIdFor(player));
        return {
          battle,
          config: cloneMissionBattleConfig(config),
          stageId,
          stageAssets,
          stageBounds,
          localPlayerId: localPlayerIds[0] ?? playerIdFor(0),
          localPlayerIds,
        };
      } catch (error) {
        pendingBattleConfig = null;
        screen = "select-force";
        throw error;
      }
    },
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

function cloneSlot(slot: SessionForceSlot): SessionForceSlot {
  return { ...slot, borgIds: [...slot.borgIds] };
}

function cloneSlots(slots: readonly SessionForceSlot[]): SessionForceSlot[] {
  return slots.map(cloneSlot);
}

function cloneBattleResults(results: BattleResults): BattleResults {
  return { ...results };
}

function cloneMissionBattleConfigOrNull(config: MissionBattleConfig | null): MissionBattleConfig | null {
  return config ? cloneMissionBattleConfig(config) : null;
}

function cloneMissionBattleConfig(config: MissionBattleConfig): MissionBattleConfig {
  return {
    arena: config.arena,
    forces: config.forces.map((force) => ({ ...force, borgIds: [...force.borgIds] })),
    ...(config.timeLimitFrames !== undefined ? { timeLimitFrames: config.timeLimitFrames } : {}),
    ...(config.timerFrozen !== undefined ? { timerFrozen: config.timerFrozen } : {}),
    ...(config.label !== undefined ? { label: config.label } : {}),
    ...(config.meta ? { meta: cloneMissionBattleMeta(config.meta) } : {}),
  };
}

function cloneMissionBattleMeta(meta: NonNullable<MissionBattleConfig["meta"]>): NonNullable<MissionBattleConfig["meta"]> {
  return {
    ...meta,
    ...(meta.enemySlotForceEnergy ? { enemySlotForceEnergy: [...meta.enemySlotForceEnergy] } : {}),
    ...(meta.enemySlotBudgetCharge ? { enemySlotBudgetCharge: [...meta.enemySlotBudgetCharge] } : {}),
    ...(meta.enemyGroupChoices ? { enemyGroupChoices: [...meta.enemyGroupChoices] } : {}),
    ...(meta.enemyPickedGroupCodes ? { enemyPickedGroupCodes: [...meta.enemyPickedGroupCodes] } : {}),
    ...(meta.allyGroupChoices ? { allyGroupChoices: [...meta.allyGroupChoices] } : {}),
    ...(meta.allyPickedGroupCodes ? { allyPickedGroupCodes: [...meta.allyPickedGroupCodes] } : {}),
    ...(meta.unresolvedEnemies ? { unresolvedEnemies: [...meta.unresolvedEnemies] } : {}),
  };
}
