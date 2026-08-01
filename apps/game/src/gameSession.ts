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
import {
  createChallengeFlowVm,
  CHALLENGE_FLOW_MODE,
  type ChallengeFlowEffectSink,
  type ChallengeFlowVm,
} from "./ui/intro/challengeFlowVm.js";
import { ROM_MODE_TO_GAME_SCREEN } from "./ui/intro/globalMenuDispatcher.js";

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

// ------------------------------------------------------------------------------------------
// Source-owned Challenge flow + global-menu screen authority
// ------------------------------------------------------------------------------------------
//
// The Challenge flow VM (ui/intro/challengeFlowVm.ts) is the 1:1 port of
// dispatch_challenge_flow_state @0x80195f2c and its 8-entry mode table. The
// global-menu dispatcher (ui/intro/globalMenuDispatcher.ts) owns the 11-entry
// front-end ROM mode→screen table (ROM_MODE_TO_GAME_SCREEN). This session is
// EVENT-driven (discrete dispatch() calls); the VM is PER-FRAME. The per-frame
// battle loop lives in main.ts and @gf/missions owns roster generation, so the
// VM is wired here as the Challenge mode→screen AUTHORITY: at each Challenge-
// path transition the host sets the VM mode to the matching ROM phase and
// resolveChallengeScreen() maps it to a GameScreen. Per-frame VM battle
// stepping (mode-4 sub-dispatch) and VM-owned roster rolling are documented
// future wirings — the sink below stubs them honestly (returns defaults /
// records the build on vm.state.lastSetup without consuming it as the battle
// roster, since @gf/missions is the verified roster source). See
// research/decomp/index/challenge-flow-vm-integration.md.

const GF_SOURCE_STRICT: boolean = readSourceStrictFlag();

/** Opt-in enforcement. When true, the VM/dispatcher mappings become authoritative
 *  (an unmapped mode or unrecognized front-end screen throws instead of warning +
 *  falling back). Read via Vite's import.meta.env (GF_SOURCE_STRICT /
 *  VITE_GF_SOURCE_STRICT). Off by default so the port's extra HLE screens stay
 *  playable. */
function readSourceStrictFlag(): boolean {
  try {
    const env = (import.meta as unknown as { env?: Record<string, unknown> }).env;
    return env?.GF_SOURCE_STRICT === "1" || env?.VITE_GF_SOURCE_STRICT === "1";
  } catch {
    return false;
  }
}

/** ROM Challenge-flow mode → source-shaped GameScreen. null = no direct screen
 *  (INIT internal, or a host phase with no ROM equivalent handled by the port). */
const CHALLENGE_VM_MODE_TO_GAME_SCREEN: Readonly<Record<number, GameScreen | null>> = {
  [CHALLENGE_FLOW_MODE.INIT]: null,
  [CHALLENGE_FLOW_MODE.MENU_POLL]: "difficulty",
  [CHALLENGE_FLOW_MODE.BOX_LOAD]: "load-box",
  [CHALLENGE_FLOW_MODE.BATTLE_BUILD]: "briefing",
  [CHALLENGE_FLOW_MODE.IN_BATTLE]: "battle",
  [CHALLENGE_FLOW_MODE.CLEAR]: "results",
  [CHALLENGE_FLOW_MODE.FAIL]: "results",
  [CHALLENGE_FLOW_MODE.EXIT]: "menu",
};

/** GF-energy budget → ROM difficulty index (DAT_804356d0 row: 5/10/15 battles).
 *  1500=Normal(0), 2000=Tuff(1), 2500=Insane(2). */
function budgetToDifficulty(budget: number): number {
  if (budget <= 1500) return 0;
  if (budget <= 2000) return 1;
  return 2;
}

/** Human player count → ROM controller slot bitmask (bit s = slot s is human). */
function playerCountToControllerMask(playerCount: number): number {
  return playerCount >= 2 ? 0x03 : 0x01;
}

/** Sink for the Challenge VM. The session is event-driven and does NOT own the
 *  per-frame battle loop (main.ts) or roster generation (@gf/missions); the VM
 *  is consulted for mode→screen mapping, so battle-runtime methods return
 *  sensible defaults and the VM's rolled setup is recorded on vm.state.lastSetup
 *  but not consumed as the battle roster (documented partial-port gap). */
function createSessionChallengeSink(): ChallengeFlowEffectSink {
  return {
    onEnterChallenge() { /* title/scene stinger owned by main.ts */ },
    onChallengeWorkInit() { /* @gf/missions owns ChallengeRun seeding */ },
    pollMenuResult() { return 0; /* host drives mode via setChallengeVmMode */ },
    onMenuOpened(_selectedIndex) { /* cursor SFX owned by main.ts */ },
    buildBoxPreview(_boxIndex) { /* SelectForce/ForceBuilder render owned by main.ts */ },
    isBoxPreviewReady() { return true; },
    spawnBattleSetup(_setup) { /* recorded on vm.state.lastSetup; battle uses @gf/missions */ },
    isBattleSceneReady() { return true; /* main.ts loads stage assets */ },
    stepBattleFrame() { /* main.ts owns the fixed-step battle loop */ },
    isBattleEnded() { return false; /* main.ts resolves battles via events */ },
    getWinnerMask() { return 1; /* side-0 win default; host maps outcomes via events */ },
    rerollStage(prev) { return (prev + 1) & 0xff; },
    loadBattleScene(_stageId) { /* main.ts loads stage assets */ },
    drawBorgFromPool(_poolGroupId) { return 0; /* @gf/missions owns roster draw */ },
    borgCost(_borgId) { return 0; /* @gf/combat stats own force-energy cost */ },
    showResultsScreen(_mode) { /* Results screen rendered by main.ts */ },
    isResultsDismissed() { return true; /* host advance event drives dismiss */ },
    exitToMenu() { /* host renders the menu screen */ },
  };
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
  // Source-owned Challenge flow VM. Constructed on entering Challenge mode; null
  // on non-Challenge paths or when VM entry failed (fallback to hardcoded flow).
  let challengeVm: ChallengeFlowVm | null = null;

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

  /** Build the Challenge run + pending battle. Returns the screen the caller
   *  should render ("briefing" when a battle is queued, "menu" otherwise) so the
   *  force-slot-confirm handler can route it through the Challenge VM. */
  function beginRun(): GameScreen {
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
      return "menu";
    }
    return "briefing";
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

  /** Construct + enter the Challenge VM (INIT → MENU_POLL via one genuine
   *  VM-driven tick). On failure: strict rethrows; default warns + nulls the VM
   *  so the rest of the Challenge path uses the hardcoded fallback. */
  function enterChallengeVm(): void {
    try {
      const difficulty = budgetToDifficulty(budget);
      challengeVm = createChallengeFlowVm(createSessionChallengeSink(), {
        controllerMask: playerCountToControllerMask(playerCount),
        difficulty,
      });
      challengeVm.tick(); // onEnterChallenge + mode-0 init → MENU_POLL
    } catch (error) {
      if (GF_SOURCE_STRICT) throw error;
      console.warn("[challenge-flow] VM entry failed; using hardcoded fallback", error);
      challengeVm = null;
    }
  }

  /** Set the VM mode to reflect the host's current Challenge phase. */
  function setChallengeVmMode(mode: number): void {
    if (challengeVm) challengeVm.state.mode = mode;
  }

  /** Map the current Challenge VM mode to a GameScreen (the VM is the ROM-faithful
   *  authority for Challenge screen selection). Unmapped mode → fallback (strict:
   *  throw). Returns the fallback unchanged when no VM is active. */
  function resolveChallengeScreen(fallback: GameScreen): GameScreen {
    if (!challengeVm) return fallback;
    try {
      const mode = challengeVm.state.mode;
      const mapped = CHALLENGE_VM_MODE_TO_GAME_SCREEN[mode] ?? null;
      if (mapped === null) {
        if (GF_SOURCE_STRICT) {
          throw new Error(`challenge VM mode ${mode} has no GameScreen binding`);
        }
        console.warn(`[challenge-flow] VM mode ${mode} unmapped; falling back to "${fallback}"`);
        return fallback;
      }
      return mapped;
    } catch (error) {
      if (GF_SOURCE_STRICT) throw error;
      console.warn("[challenge-flow] VM screen resolution failed; falling back to", fallback, error);
      return fallback;
    }
  }

  /** Advisory: confirm the front-end screen is one the ROM global-menu
   *  dispatcher recognizes (ROM_MODE_TO_GAME_SCREEN). Used for title/menu
   *  transitions only — runtime screens (briefing/battle/gets/force/loading) are
   *  NOT routed here. Strict: throw on an unrecognized front-end screen. */
  function resolveGlobalMenuScreen(fallback: GameScreen): GameScreen {
    if (!ROM_MODE_TO_GAME_SCREEN.includes(fallback)) {
      if (GF_SOURCE_STRICT) {
        throw new Error(`global-menu dispatcher has no ROM mode for front-end screen "${fallback}"`);
      }
      console.warn(`[global-menu] no ROM mode maps to "${fallback}"; using hardcoded fallback`);
    }
    return fallback;
  }

  return {
    dispatch(event) {
      switch (event.type) {
        case "boot-ready":
          return screen === "loading" ? render(resolveGlobalMenuScreen("title")) : reject(event);
        case "title-enter":
          if (screen !== "title") return reject(event);
          menuMode = "challenge";
          return render(resolveGlobalMenuScreen("menu"));
        case "menu-select":
          if (screen !== "menu") return reject(event);
          if (event.mode === "challenge") {
            menuMode = "challenge";
            enterChallengeVm(); // construct + INIT → MENU_POLL (VM-driven entry)
            return render(resolveChallengeScreen("difficulty"));
          }
          forceEditorReturnTarget = "menu";
          menuMode = "edit-force";
          return render("force");
        case "back":
          if (screen === "difficulty") { setChallengeVmMode(CHALLENGE_FLOW_MODE.EXIT); return render(resolveGlobalMenuScreen("menu")); }
          if (screen === "players") return render(resolveGlobalMenuScreen("difficulty"));
          if (screen === "load-box") return render(resolveGlobalMenuScreen("players"));
          if (screen === "select-force") { setChallengeVmMode(CHALLENGE_FLOW_MODE.BOX_LOAD); return render(resolveGlobalMenuScreen("load-box")); }
          if (screen === "briefing") {
            pendingBattleConfig = null;
            setChallengeVmMode(CHALLENGE_FLOW_MODE.BOX_LOAD);
            return render("select-force");
          }
          return reject(event);
        case "difficulty-select":
          if (screen !== "difficulty") return reject(event);
          budget = event.budget;
          if (challengeVm) challengeVm.state.menu.difficulty = budgetToDifficulty(budget);
          // "players" is a port-only screen (ROM has no player-count pick;
          // controllerMask comes from the menu) — render directly, no VM consult.
          return render("players");
        case "players-select":
          if (screen !== "players") return reject(event);
          playerCount = Math.max(1, Math.min(event.playerCount, 2));
          if (challengeVm) challengeVm.state.controllerMask = playerCountToControllerMask(playerCount);
          setChallengeVmMode(CHALLENGE_FLOW_MODE.BOX_LOAD);
          return render(resolveChallengeScreen("load-box"));
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
          {
            const target = beginRun();
            setChallengeVmMode(target === "briefing" ? CHALLENGE_FLOW_MODE.BATTLE_BUILD : CHALLENGE_FLOW_MODE.EXIT);
            return render(resolveChallengeScreen(target));
          }
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
          setChallengeVmMode(CHALLENGE_FLOW_MODE.IN_BATTLE);
          screen = "loading";
          return [{ type: "render", screen }, { type: "prepare-battle" }];
        case "battle-started":
          return screen === "loading" && pendingBattleConfig ? render(resolveChallengeScreen("battle")) : reject(event);
        case "battle-preparation-failed":
          if (screen === "select-force") { setChallengeVmMode(CHALLENGE_FLOW_MODE.BOX_LOAD); return render("select-force"); }
          if (screen !== "loading") return reject(event);
          pendingBattleConfig = null;
          setChallengeVmMode(CHALLENGE_FLOW_MODE.BOX_LOAD);
          return render("select-force");
        case "battle-abandoned":
          if (screen !== "battle") return reject(event);
          pendingBattleConfig = null;
          postBattle = null;
          menuMode = "challenge";
          setChallengeVmMode(CHALLENGE_FLOW_MODE.EXIT);
          return [{ type: "teardown-battle" }, ...render(resolveChallengeScreen("menu"))];
        case "battle-resolved":
          if (screen !== "battle") return reject(event);
          postBattle = {
            result: event.battleResults.outcome === "WIN" ? "win" : "lose",
            stats: { ...event.stats },
            battleResults: cloneBattleResults(event.battleResults),
            drops: event.drops.map((drop) => ({ ...drop })),
          };
          setChallengeVmMode(postBattle.result === "win" ? CHALLENGE_FLOW_MODE.CLEAR : CHALLENGE_FLOW_MODE.FAIL);
          return render(resolveChallengeScreen("results"));
        case "advance":
          if (screen === "results" && (postBattle?.drops.length ?? 0) > 0) return render("gets");
          if (screen === "results" || screen === "gets") {
            const effects = advanceRun();
            // advanceRun rendered "briefing" (next battle) or "menu" (run ended);
            // sync the VM mode to match (they agree, so no override needed). Cast:
            // advanceRun reassigns `screen` as a side effect TS control-flow can't see.
            const next = screen as GameScreen;
            setChallengeVmMode(next === "briefing" ? CHALLENGE_FLOW_MODE.BATTLE_BUILD : CHALLENGE_FLOW_MODE.EXIT);
            return effects;
          }
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
