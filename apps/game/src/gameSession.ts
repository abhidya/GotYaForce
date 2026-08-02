import type { StageAssets } from "@gf/assets";
import {
  createBattle,
  DEFAULT_BOUNDS,
  type Battle,
  type BorgStats,
  type RectStageBounds,
} from "@gf/combat";
import {
  CHALLENGE_GROUP_ROSTERS,
  challengeBattleCount,
  challengeStageId,
  playerIdFor,
  selectChallengeStage,
  stageIdForBattleConfig,
  toCombatBattleConfig,
  type BattleResults,
  type ChallengeRun,
  type ChallengeRunOptions,
  type CombatStageCatalog,
  type GetDrop,
  type MissionBattleConfig,
  type MissionBattleForce,
} from "@gf/missions";
import {
  createChallengeFlowVm,
  CHALLENGE_FLOW_MODE,
  type ChallengeBattleSetup,
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
// EVENT-driven (discrete dispatch() calls); the VM is PER-FRAME. The VM is
// wired here as the Challenge mode→screen AUTHORITY AND the battle-roster /
// win-counter authority: on each battle-build transition the host TICKS the
// VM's mode 3 (build_challenge_battle_setup) so it rolls the per-slot CPU
// rosters into vm.state.lastSetup, which applyVmBattleBuild() converts into
// the MissionBattleConfig.forces prepareBattle consumes (PRIMARY roster
// source). On each win, advanceVmWin() ticks the VM's mode-4 post-battle gate
// so vm.state.battleIndex/battleTotal drives the rebuild-vs-clear decision.
// @gf/missions' createChallengeRun stays as the SCORING owner and the roster
// FALLBACK (when the VM is absent or throws, gated by GF_SOURCE_STRICT). The
// per-frame battle loop still lives in main.ts. See
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

/** ROM numeric borg id (family<<8|variant, e.g. 0x0615 G RED) → pl#### string id
 *  used by @gf/missions/@gf/combat. Round-trips with parseInt(id.slice(2),16). */
function borgIdToString(borgId: number): string {
  return `pl${(borgId >>> 0).toString(16).padStart(4, "0")}`;
}

/** Mutable stage selection stashed by the sink's rerollStage (zz_0196dac_) so
 *  buildBattleConfigFromVmSetup can populate meta.stageByte/stageSubtable for
 *  stage-id family resolution in stageIdForBattleConfig. */
interface SessionChallengeStageState {
  stageByte: number;
  stageSubtable: number;
  stageVariant: number;
}

/** Sink for the Challenge VM. The session is event-driven and does NOT own the
 *  per-frame battle loop (main.ts); the VM is consulted for mode→screen mapping
 *  AND, on mode 3, rolls the authoritative CPU roster via drawBorgFromPool/
 *  borgCost bridging to @gf/missions' CHALLENGE_GROUP_ROSTERS + the borg energy
 *  table. spawnBattleSetup records the build on vm.state.lastSetup, which the
 *  session converts into the battle's MissionBattleConfig.forces (primary roster
 *  source); @gf/missions' own roster stays as fallback when the VM is absent or
 *  throws (gated by GF_SOURCE_STRICT). */
function createSessionChallengeSink(deps: {
  borgEnergyById: ReadonlyMap<string, number>;
  stage: SessionChallengeStageState;
}): ChallengeFlowEffectSink {
  return {
    onEnterChallenge() { /* title/scene stinger owned by main.ts */ },
    onChallengeWorkInit() { /* @gf/missions owns ChallengeRun scoring seeding */ },
    pollMenuResult() { return 0; /* host drives mode via setChallengeVmMode */ },
    onMenuOpened(_selectedIndex) { /* cursor SFX owned by main.ts */ },
    buildBoxPreview(_boxIndex) { /* SelectForce/ForceBuilder render owned by main.ts */ },
    isBoxPreviewReady() { return true; },
    spawnBattleSetup(_setup) { /* recorded on vm.state.lastSetup; consumed by applyVmBattleBuild */ },
    isBattleSceneReady() { return true; /* main.ts loads stage assets */ },
    stepBattleFrame() { /* main.ts owns the fixed-step battle loop */ },
    isBattleEnded() { return false; /* main.ts resolves battles via events */ },
    getWinnerMask() { return 1; /* side-0 win; battle-resolved(win) advances the VM */ },
    rerollStage(prev) {
      // zz_0196dac_: draw a stage byte != prev from the 11-entry CHALLENGE_STAGE_BYTES pool.
      const sel = selectChallengeStage(Math.random, prev);
      deps.stage.stageByte = sel.stageByte;
      deps.stage.stageSubtable = sel.stageSubtable;
      deps.stage.stageVariant = sel.stageVariant;
      return sel.stageByte;
    },
    loadBattleScene(_stageId) { /* main.ts loads stage assets */ },
    drawBorgFromPool(poolGroupId) {
      // zz_0196eb8_: draw a borg id from PTR_DAT_80380804[group] (CHALLENGE_GROUP_ROSTERS).
      const pool = (CHALLENGE_GROUP_ROSTERS as Readonly<Record<number, readonly string[]>>)[poolGroupId];
      if (!pool || pool.length === 0) return 0;
      const id = pool[Math.floor(Math.random() * pool.length)] ?? "pl0008";
      return Number.parseInt(id.slice(2), 16);
    },
    borgCost(borgId) {
      // zz_0066168_: raw force-energy cost; the VM applies floor(cost*2/3) itself.
      return deps.borgEnergyById.get(borgIdToString(borgId)) ?? 0;
    },
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
  // Stage selection stashed by the VM sink's rerollStage (mutated, not replaced,
  // so the sink and builder share one reference); read by buildBattleConfigFromVmSetup.
  let challengeStageState: SessionChallengeStageState = { stageByte: 0xff, stageSubtable: 0, stageVariant: 0 };

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

  /** Human players' chosen forces (ordered by player index), shared by beginRun
   *  (@gf/missions seeding) and the VM roster converter. Human side-0 slots carry
   *  no VM-rolled roster — the VM only rolls CPU slots — so their borg ids come
   *  from the player's selected force. */
  function humanPlayerForces(): { player: number; borgIds: string[] }[] {
    const humanPlayerCount = Math.max(1, Math.min(playerCount, 2));
    return Array.from({ length: humanPlayerCount }, (_, player) => {
      const slot = player === 0
        ? selectedSlot()
        : forceSlots[(selectedForceSlot + player) % forceSlots.length] ?? selectedSlot();
      return { player, borgIds: dependencies.forceFromSlot(slot) };
    });
  }

  /** Convert the VM's mode-3 ChallengeBattleSetup (per-slot sides + CPU rosters)
   *  into the MissionBattleConfig.forces shape prepareBattle/toCombatBattleConfig
   *  expect. Human side-0 slots pull from the players' chosen force; CPU ally
   *  (side 0, non-human) and CPU enemy (side 1) slots pull from the VM roster. */
  function buildBattleConfigFromVmSetup(setup: ChallengeBattleSetup): MissionBattleConfig {
    const humanForces = humanPlayerForces();
    const forces: MissionBattleForce[] = [];
    let humanIndex = 0;
    for (const slot of setup.slots) {
      if (!slot.active) continue;
      const isHuman = (setup.controllerMask & (1 << slot.slot)) !== 0;
      if (slot.side === 0 && isHuman) {
        const pf = humanForces[humanIndex];
        humanIndex += 1;
        forces.push({
          team: "player",
          ownerPlayer: pf?.player ?? 0,
          borgIds: pf ? [...pf.borgIds] : [],
        });
      } else if (slot.side === 0) {
        forces.push({
          team: "player",
          ownerPlayer: null,
          borgIds: slot.roster.map((m) => borgIdToString(m.borgId)),
          cpuAlly: true,
        });
      } else if (slot.side === 1) {
        forces.push({
          team: "enemy",
          ownerPlayer: null,
          borgIds: slot.roster.map((m) => borgIdToString(m.borgId)),
        });
      }
    }
    return {
      arena: challengeStageId(setup.stageId),
      forces,
      timeLimitFrames: setup.timeLimitFrames,
      timerFrozen: setup.timerFrozen,
      label: `BATTLE ${setup.battleIndex + 1} VS`,
      meta: {
        mode: "challenge",
        index: setup.battleIndex,
        challengeMode: setup.difficulty as 0 | 1 | 2,
        stageByte: challengeStageState.stageByte,
        stageSubtable: challengeStageState.stageSubtable,
        stageVariant: challengeStageState.stageVariant,
        timeLimitFrames: setup.timeLimitFrames,
      },
    };
  }

  /** Tick the VM through mode 3 (build_challenge_battle_setup) so it rolls the
   *  per-slot CPU rosters into vm.state.lastSetup, then convert that into the
   *  pending battle config — PRIMARY roster source. Returns false (caller falls
   *  back to the @gf/missions config left by beginRun) when the VM is absent,
   *  lastSetup is null, or the tick throws. */
  function applyVmBattleBuild(): boolean {
    if (!challengeVm) return false;
    try {
      challengeVm.state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD;
      challengeVm.state.subFlag = 0;
      challengeVm.tick(); // mode_buildBattle → lastSetup populated, mode→IN_BATTLE
    } catch (error) {
      if (GF_SOURCE_STRICT) throw error;
      console.warn("[challenge-flow] VM battle build failed; using @gf/missions roster", error);
      return false;
    }
    const setup = challengeVm.state.lastSetup;
    if (!setup) return false;
    pendingBattleConfig = buildBattleConfigFromVmSetup(setup);
    return true;
  }

  /** Tick the VM's mode-4 post-battle gate (sub 2) on a win so it increments
   *  vm.state.battleIndex and transitions to mode 3 (more battles) or mode 5
   *  (clear, reached battleTotal). Returns the resulting mode, or null when no
   *  VM is active (caller uses the @gf/missions results-on-any-win fallback). */
  function advanceVmWin(): number | null {
    if (!challengeVm) return null;
    try {
      challengeVm.state.battleTotal = challengeBattleCount(challengeVm.state.difficulty as 0 | 1 | 2);
      challengeVm.state.mode = CHALLENGE_FLOW_MODE.IN_BATTLE;
      challengeVm.state.subMode = 2; // sub_postBattle gate
      challengeVm.tick();
      return challengeVm.state.mode;
    } catch (error) {
      if (GF_SOURCE_STRICT) throw error;
      console.warn("[challenge-flow] VM win-counter advance failed; falling back", error);
      return null;
    }
  }

  /** Construct + enter the Challenge VM (INIT → MENU_POLL via one genuine
   *  VM-driven tick). On failure: strict rethrows; default warns + nulls the VM
   *  so the rest of the Challenge path uses the hardcoded fallback. */
  function enterChallengeVm(): void {
    try {
      const difficulty = budgetToDifficulty(budget);
      const borgEnergyById = new Map(dependencies.borgStats.map((b) => [b.id, b.energy] as const));
      challengeStageState.stageByte = 0xff;
      challengeStageState.stageSubtable = 0;
      challengeStageState.stageVariant = 0;
      challengeVm = createChallengeFlowVm(
        createSessionChallengeSink({ borgEnergyById, stage: challengeStageState }),
        {
          controllerMask: playerCountToControllerMask(playerCount),
          difficulty,
        },
      );
      challengeVm.state.battleTotal = challengeBattleCount(difficulty as 0 | 1 | 2);
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
          if (challengeVm) {
            const difficulty = budgetToDifficulty(budget);
            challengeVm.state.menu.difficulty = difficulty;
            challengeVm.state.difficulty = difficulty;
            challengeVm.state.battleTotal = challengeBattleCount(difficulty as 0 | 1 | 2);
          }
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
            if (target === "briefing") {
              // VM roster is PRIMARY; beginRun already seeded the @gf/missions
              // fallback config, overridden here when the VM build succeeds.
              applyVmBattleBuild();
              setChallengeVmMode(CHALLENGE_FLOW_MODE.BATTLE_BUILD);
            } else {
              setChallengeVmMode(CHALLENGE_FLOW_MODE.EXIT);
            }
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
          if (postBattle.result === "win") {
            // Route the win through the VM's mode-4 post-battle gate so the VM's
            // battleIndex/battleTotal counter is the progression authority.
            const nextMode = advanceVmWin();
            if (nextMode !== CHALLENGE_FLOW_MODE.CLEAR) {
              // null = no VM active → keep the original results-on-any-win UX.
              if (nextMode === null) {
                setChallengeVmMode(CHALLENGE_FLOW_MODE.CLEAR);
                return render(resolveChallengeScreen("results"));
              }
              // VM says rebuild (mode 3): an intermediate win. Score via the run,
              // tear the battle down, rebuild the next config (VM primary), and go
              // straight to briefing — the ROM shows no per-battle results here.
              const progress = run ? run.next(postBattle.battleResults) : null;
              const effects: GameSessionEffect[] = [{ type: "teardown-battle" }];
              postBattle = null;
              const vmBuilt = applyVmBattleBuild();
              if (!vmBuilt && progress?.action === "advance") {
                pendingBattleConfig = cloneMissionBattleConfigOrNull(progress.nextBattle);
              }
              if (pendingBattleConfig) {
                setChallengeVmMode(CHALLENGE_FLOW_MODE.BATTLE_BUILD);
                screen = "briefing";
                return [...effects, { type: "render", screen: "briefing" }];
              }
              menuMode = "challenge";
              screen = "menu";
              return [...effects, { type: "render", screen }];
            }
            // VM reached battleTotal → mode 5 (clear): show the end-of-run results.
            setChallengeVmMode(CHALLENGE_FLOW_MODE.CLEAR);
            return render(resolveChallengeScreen("results"));
          }
          setChallengeVmMode(CHALLENGE_FLOW_MODE.FAIL);
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
