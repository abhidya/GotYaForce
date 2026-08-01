/**
 * challengeFlowVm — 1:1 TypeScript port of the GG4E Challenge-flow state machine.
 *
 * Source (all addresses are GG4E/NTSC-U boot.dol, research/decomp/ghidra-export/chunk_0048.c):
 *   - `dispatch_challenge_flow_state` @0x80195f2c (chunk_0048.c:109) — the per-frame
 *     dispatcher. Reads the mode byte `*DAT_80436378` and calls
 *     `PTR_FUN_8036f560[mode]()`. On first entry (global_menu_state[1]==0) it clears the
 *     0x16-byte mode block (DAT_803d4960).
 *   - `init_challenge_flow_state` @0x80195fbc (chunk_0048.c:130) — mode 0. Clears the
 *     0x18b8-byte work block (PTR_DAT_80433934) and 0x4a0-byte save block
 *     (PTR_DAT_80433944), seeds defaults, then sets mode=1.
 *   - `poll_challenge_menu_selection` @0x80196030 (chunk_0048.c:153) — mode 1. Polls the
 *     menu result word; branches to mode 2 (cursor), 3 (confirm), or 7 (cancel).
 *   - `FUN_80196188` @0x80196188 (chunk_0048.c:199) — mode 2. Builds the box/force
 *     preview; on completion returns to mode 1.
 *   - `build_challenge_battle_setup` @0x801962c4 (chunk_0048.c:234) — mode 3. Builds the
 *     per-slot side/team roster from the controller mask + the dumped count/budget/pool
 *     tables, sets mode=4, and hands the spawn to the sink.
 *   - `FUN_8019688c` @0x8019688c (chunk_0048.c:414) — mode 4. Sub-dispatches on the
 *     short at mode-block+4 via `PTR_FUN_8036f580[subMode]`, then runs the timer
 *     integrator `zz_0196f64_` @0x80196f64.
 *       sub 0 `FUN_801968cc` (chunk_0048.c:426): wait for `zz_000a3c4_` scene ready.
 *       sub 1 `FUN_80196948` (chunk_0048.c:450): `zz_0028264_` battle step; ends when the
 *           global menu byte `*PTR_DAT_80433930 == 1`.
 *       sub 2 `FUN_801969a0` (chunk_0048.c:466): win/loss gate on winner mask
 *           `PTR_DAT_80433934[0x1f]`; advances the battle counter or branches to mode 5/6.
 *   - `FUN_80196a9c` @0x80196a9c (chunk_0048.c:510) — mode 5 (clear). Results screen at
 *     `zz_01f5ae0_(difficulty)`; on dismiss → mode 7.
 *   - `FUN_80196cec` @0x80196cec (chunk_0048.c:618) — mode 6 (fail). Results screen at
 *     `zz_01f5ae0_(3)`; on dismiss → mode 7.
 *   - mode 7 = `0x80196d64` — exit. Not emitted as a standalone fn by Ghidra; confirmed as
 *     the teardown/return-to-physical-menu handler (behavior-notes.md ae:1898-1810). Ported
 *     as an explicit sink boundary (`exitToMenu`).
 *
 * The dumped mode table `PTR_FUN_8036f560` (CHALLENGE_FLOW_MODE_DISPATCH) and all data
 * tables are read straight from boot.dol by scripts/gen-challenge-flow-tables.mjs — no
 * hand-transcription. Engine-side effects (archive/scene load, actor spawn, render, audio,
 * raw borg-id/cost lookups) are delegated to a `ChallengeFlowEffectSink` so the host
 * renderer/session can map them at the boundary; each delegation cites the ROM call it
 * replaces. Field offsets from the ROM work block (PTR_DAT_80433934) are preserved as
 * `_ofs0xNN` comments so this file is auditable against the decompile.
 *
 * Cross-validated against research/decomp/data/challenge-battle-tables-8036f360.json and
 * behavior-notes.md section (ae).
 */

import {
  CHALLENGE_FLOW_MODE_DISPATCH,
  CHALLENGE_FLOW_SUB_DISPATCH,
  CHALLENGE_START_FORCE_ENERGY,
  CHALLENGE_BATTLE_COUNT_BY_DIFFICULTY,
  CHALLENGE_SLOT_FLAG_BY_DIFFICULTY,
  CHALLENGE_STAGE_ID_PAIR_BY_DIFFICULTY,
  CHALLENGE_ALLY_COUNT_BY_BATTLE,
  CHALLENGE_ENEMY_COUNT_BY_BATTLE,
  CHALLENGE_ALLY_BUDGET_BY_BATTLE,
  CHALLENGE_ENEMY_BUDGET_BY_BATTLE,
  CHALLENGE_ALLY_POOL_GROUP_TABLE,
  CHALLENGE_ENEMY_POOL_GROUP_TABLE,
} from "../challengeFlowTables.generated.js";

/** The 8-entry mode dispatch table `PTR_FUN_8036f560` (mode -> ROM fn address). */
export const CHALLENGE_FLOW_MODE_TABLE = CHALLENGE_FLOW_MODE_DISPATCH;
/** The 3-entry mode-4 sub-dispatch table `PTR_FUN_8036f580` (subMode -> ROM fn address). */
export const CHALLENGE_FLOW_SUB_MODE_TABLE = CHALLENGE_FLOW_SUB_DISPATCH;

/** ROM Challenge-flow mode ids (indices into PTR_FUN_8036f560). */
export const CHALLENGE_FLOW_MODE = {
  INIT: 0, // 0x80195fbc init_challenge_flow_state
  MENU_POLL: 1, // 0x80196030 poll_challenge_menu_selection
  BOX_LOAD: 2, // 0x80196188 FUN_80196188
  BATTLE_BUILD: 3, // 0x801962c4 build_challenge_battle_setup
  IN_BATTLE: 4, // 0x8019688c FUN_8019688c (sub-dispatch)
  CLEAR: 5, // 0x80196a9c FUN_80196a9c (victory screen)
  FAIL: 6, // 0x80196cec FUN_80196cec (defeat screen)
  EXIT: 7, // 0x80196d64 teardown -> physical menu
} as const;

/** ROM menu-result word decoding (poll_challenge_menu_selection, zz_018f56c_). */
export const MENU_RESULT = {
  /** Set on a cursor/index move (low byte = new index). */
  isCursorMove: (r: number): boolean => (r & 0x8000) !== 0,
  /** A confirm selects when result > 0 and the cursor-move bit is clear. */
  isConfirm: (r: number): boolean => r > 0 && (r & 0x8000) === 0,
  /** A negative value cancels back to the physical menu. */
  isCancel: (r: number): boolean => r < 0,
} as const;

/** A rolled roster member for one slot (work+0x1e8 stride-0x1c entries: u16 borgId @+0,
 *  cost derived from zz_0066168_). */
export interface ChallengeRosterMember {
  borgId: number;
  cost: number;
}

/** Per-slot setup written by build_challenge_battle_setup (work[slot+0xcb] side byte,
 *  work[slot+0x5a] roster count, work+iVar8+0x1e8 roster entries). */
export interface ChallengeSlotSetup {
  /** Slot index 0..5. */
  slot: number;
  /** work[slot+0xcb]: 0 = side 0 (player/ally), 1 = side 1 (enemy), 0xff = inactive. */
  side: number;
  active: boolean;
  /** work[slot+0x32] = DAT_804356ec[side + difficulty*2] — side flag (active slots only). */
  slotFlag: number;
  roster: ChallengeRosterMember[];
}

/** The full output of build_challenge_battle_setup (mode 3), handed to the sink. */
export interface ChallengeBattleSetup {
  difficulty: number;
  battleIndex: number;
  controllerMask: number;
  /** work[0x15d9] — bitmask of active slots. */
  activeMask: number;
  /** work[0x15da] — count of active slots. */
  activeCount: number;
  /** local_60[2] from PTR_DAT_8036f40c — CPU ally roster cap for side 0. */
  allyCount: number;
  /** local_60[3] from PTR_DAT_8036f434 — CPU enemy roster cap for side 1. */
  enemyCount: number;
  /** local_60[0] from PTR_DAT_8036f4b8 — side 0 budget. */
  allyBudget: number;
  /** local_60[1] from PTR_DAT_8036f53c — side 1 budget. */
  enemyBudget: number;
  /** PTR_DAT_8036f360 — side 0 pool group id for this battle. */
  allyPoolGroup: number;
  /** PTR_DAT_8036f3e4 — side 1 pool group id for this battle. */
  enemyPoolGroup: number;
  slots: ChallengeSlotSetup[];
  /** work[0x1c] after zz_0196dac_ reroll — the stage id (st##). */
  stageId: number;
  /** DAT_804356e4[difficulty*2]/[+1] -> PTR_DAT_80433950 — stage scene id bytes. */
  stageIdPair: { primary: number; secondary: number };
  /** work[0x48]=work[0x4c]=18000, work[0x50]=1 — Challenge freezes the timer. */
  timeLimitFrames: number;
  timerFrozen: boolean;
}

/** Engine-effect boundary: the VM calls these where the ROM calls into HSD/GX/audio or
 *  deep combat data. The host (gameSession + renderer) implements this. */
export interface ChallengeFlowEffectSink {
  /** dispatch outer init: `zz_002a5f4_(0,0,0,0)` — challenge task just entered. */
  onEnterChallenge(): void;
  /** mode 0: `zz_0196f3c_` + `zz_0006b74_` — seed work-block timers/defaults. */
  onChallengeWorkInit(): void;
  /** mode 1: `zz_018f56c_()` — the menu result word (see MENU_RESULT). */
  pollMenuResult(): number;
  /** mode 1 first call: record the initial cursor into the save block. Host may no-op. */
  onMenuOpened(selectedIndex: number): void;
  /** mode 2 first call: build the box/force preview (PTR_DAT_80435a30 build). */
  buildBoxPreview(boxIndex: number): void;
  /** mode 2: `zz_01ba750_()` — box/force preview load complete. */
  isBoxPreviewReady(): boolean;
  /** mode 3: spawn actors from the built slot/team tables (`zz_0029fd4_`/`zz_000685c_`/
   *  `zz_00064d4_`). The VM has already assigned sides + rolled CPU rosters. */
  spawnBattleSetup(setup: ChallengeBattleSetup): void;
  /** mode 4 sub 0: `zz_000a3c4_()` — battle scene/camera load complete. */
  isBattleSceneReady(): boolean;
  /** mode 4 sub 1: `zz_0028264_()` — one per-frame battle update. */
  stepBattleFrame(): void;
  /** mode 4 sub 1: `*PTR_DAT_80433930 == 1` — the battle has ended. */
  isBattleEnded(): boolean;
  /** mode 4 sub 2: `PTR_DAT_80433934[0x1f]` — winner mask (bit0 side0, bit1 side1). */
  getWinnerMask(): number;
  /** mode 4 sub 2 advance: `zz_0196dac_` — reroll a stage id != prevStage; returns the
   *  new work[0x1c] stage byte. Delegated because it mixes RNG + the 11-entry pool. */
  rerollStage(prevStage: number): number;
  /** mode 4 sub 2 advance: `zz_0042454_`/`zz_0042690_`/`zz_00437b0_` — load next scene. */
  loadBattleScene(stageId: number): void;
  /** mode 3 roster roll: `zz_0196eb8_(group)` — draw a borg id from PTR_DAT_80380804[group]. */
  drawBorgFromPool(poolGroupId: number): number;
  /** mode 3 roster roll: `zz_0066168_(borgId, 0)` — borg force-energy cost. */
  borgCost(borgId: number): number;
  /** mode 5/6: `zz_01f5ae0_(mode)` — show the results/clear/fail screen. */
  showResultsScreen(mode: number): void;
  /** mode 5/6: `zz_01f5b68_()` — results screen dismissed. */
  isResultsDismissed(): boolean;
  /** mode 7 (`0x80196d64`): teardown and return to the physical menu. */
  exitToMenu(): void;
}

/** The per-frame Challenge-flow state. Mirrors the ROM mode block (DAT_803d4960, accessed
 *  via DAT_80436378) plus the menu save block fields read by poll. */
export interface ChallengeFlowState {
  /** global_menu_state[1] — outer one-shot "challenge task entered" latch. */
  entered: boolean;
  /** *DAT_80436378 — dispatch index into PTR_FUN_8036f560 (0..7). */
  mode: number;
  /** DAT_80436378[2] — per-mode init-once latch (set on first frame of a mode). */
  subFlag: number;
  /** *(short*)(DAT_80436378+4) — mode-4 sub-dispatch index (PTR_FUN_8036f580). */
  subMode: number;
  /** DAT_80436378[8] (short) — current 0-based battle index. */
  battleIndex: number;
  /** DAT_80436378[9] (byte) — total battles for the selected difficulty (5/10/15). */
  battleTotal: number;
  /** DAT_80436378[0x13] (byte) — selected difficulty (0/1/2). */
  difficulty: number;
  /** DAT_80436378[0x15] (byte) — menu cursor / selected box index. */
  selectedIndex: number;
  /** PTR_DAT_80433930[2] — human-controller slot bitmask (bit s = slot s is human). */
  controllerMask: number;
  /** work[0x1c] — current stage id (st##), carried for reroll. */
  stage: number;
  /** Menu save block (PTR_DAT_80433944) fields read by poll on confirm. The host menu UI
   *  writes these as the player navigates; poll copies them into the mode block. */
  menu: {
    /** PTR_DAT_80433944[0x15] — difficulty chosen in the menu. */
    difficulty: number;
    /** PTR_DAT_80433944[0x16] — selected box/slot index. */
    boxIndex: number;
    /** PTR_DAT_80433944[0x14] — current box (used by mode 2 preview). */
    currentBox: number;
  };
  /** The 4 timer shorts at work+0x182a..0x1830, integrated by zz_0196f64_ every mode-4
   *  frame. Ported faithfully (frames/seconds counter with 0x3c/0x3c/100 thresholds). */
  timer: { a: number; b: number; c: number; d: number };
  /** Most recent mode-3 build output (null until the first build completes). */
  lastSetup: ChallengeBattleSetup | null;
}

export interface ChallengeFlowVm {
  state: ChallengeFlowState;
  /** Run the per-frame dispatcher (port of dispatch_challenge_flow_state). Executes the
   *  current mode handler once. Call once per fixed frame. */
  tick(): void;
}

/** Difficulty index -> start force energy (DAT_8036f554). */
function startForceEnergyFor(difficulty: number): number {
  return CHALLENGE_START_FORCE_ENERGY[difficulty] ?? 0;
}

/** Difficulty index -> total battles (DAT_804356d0). */
function battleCountFor(difficulty: number): number {
  return CHALLENGE_BATTLE_COUNT_BY_DIFFICULTY[difficulty] ?? 0;
}

/** Lookup a per-difficulty per-battle row from the dumped pointer tables. */
function rowValueAt(rows: ReadonlyArray<{ readonly difficulty: number; readonly row: readonly number[] }>, difficulty: number, battle: number): number {
  const row = rows[difficulty]?.row;
  if (!row) throw new Error(`challenge-flow: missing difficulty ${difficulty} in roster table`);
  const v = row[battle];
  if (v === undefined) throw new Error(`challenge-flow: battle ${battle} out of range for difficulty ${difficulty}`);
  return v;
}

/** ROM `floor(cost * 2 / 3)` (chunk_0048.c:351). Ghidra emits this as
 *  `(uVar3<<1)/3 + sign-adjustments`; reduced to the integer floor it computes. */
function twoThirdsCost(cost: number): number {
  return Math.floor((cost * 2) / 3);
}

/** Port of the 4-stage timer integrator `zz_0196f64_` @0x80196f64 (chunk_0048.c:736-774).
 *  Counts a frame counter (threshold 0x3c), cascading into seconds (0x3c), minutes (0x3c),
 *  then a 100-cap display counter. Skipped entirely while the leading short is negative. */
function integrateTimer(timer: ChallengeFlowState["timer"]): void {
  if (timer.a < 0) return;
  timer.a += 1;
  if (timer.a < 0x3c) return;
  timer.a = 0;
  timer.b += 1;
  if (timer.b < 0x3c) return;
  timer.b = 0;
  timer.c += 1;
  if (timer.c < 100) return;
  timer.c = 99;
  timer.b = 0x3b;
  timer.a = 0xffff;
}

/** Create the Challenge-flow VM. The host owns the sink (render/audio/spawn/data); the VM
 *  owns the ROM state machine and mode transitions. */
export function createChallengeFlowVm(
  sink: ChallengeFlowEffectSink,
  initial?: Partial<Pick<ChallengeFlowState, "controllerMask" | "menu" | "difficulty">>,
): ChallengeFlowVm {
  const state: ChallengeFlowState = {
    entered: false,
    mode: CHALLENGE_FLOW_MODE.INIT,
    subFlag: 0,
    subMode: 0,
    battleIndex: 0,
    battleTotal: 0,
    difficulty: initial?.difficulty ?? 0,
    selectedIndex: 0,
    controllerMask: initial?.controllerMask ?? 0x01,
    stage: 0,
    menu: {
      difficulty: initial?.menu?.difficulty ?? initial?.difficulty ?? 0,
      boxIndex: initial?.menu?.boxIndex ?? 0,
      currentBox: initial?.menu?.currentBox ?? 0,
    },
    timer: { a: 0, b: 0, c: 0, d: 0 },
    lastSetup: null,
  };

  // ===== mode 0: init_challenge_flow_state @0x80195fbc (chunk_0048.c:130) ============
  // Clears the work (PTR_DAT_80433934, 0x18b8) + save (PTR_DAT_80433944, 0x4a0) blocks,
  // seeds work[0x1c]=0xff / work[0x15c]=999999 / work[0x120]=999999, then mode=1.
  const mode_init = (): void => {
    sink.onChallengeWorkInit(); // zz_0196f3c_ + zz_0006b74_
    // ROM defaults (the blocks are zeroed by the sink boundary; seed the carried fields).
    state.stage = 0xff; // work[0x1c] = 0xff
    state.timer = { a: 0, b: 0, c: 0, d: 0 };
    state.mode = CHALLENGE_FLOW_MODE.MENU_POLL;
    state.subFlag = 0;
  };

  // ===== mode 1: poll_challenge_menu_selection @0x80196030 (chunk_0048.c:153) =========
  const mode_pollMenu = (): void => {
    if (state.subFlag === 0) {
      // First frame: zero the save-block scratch (save[0..7]) and record the initial cursor
      // into save[boxIdx*0x80+0x161] (only when save[0x17] has-selection). The difficulty/
      // box fields (save[0x14/0x15/0x16]) are owned by the host menu UI and are NOT reset.
      state.subFlag = 1;
      sink.onMenuOpened(state.selectedIndex);
      return;
    }
    const result = sink.pollMenuResult(); // zz_018f56c_()
    if (MENU_RESULT.isCancel(result)) {
      state.mode = CHALLENGE_FLOW_MODE.EXIT;
      state.subFlag = 0;
    } else if (MENU_RESULT.isConfirm(result)) {
      // Confirm: copy the menu's difficulty/box into the mode block and seed the run.
      state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD;
      state.subFlag = 0;
      state.selectedIndex = state.menu.boxIndex; // (DAT_80436378+0x0a) <- save[0x16]
      state.difficulty = state.menu.difficulty; // (DAT_80436378+0x13) <- save[0x15]
      state.battleTotal = battleCountFor(state.difficulty); // (DAT_80436378+9) <- DAT_804356d0[diff]
      // *(PTR_DAT_80433934 + 0x120) = DAT_8036f554[difficulty] — start force energy.
      // Carried on the setup; recorded here for the host.
      state.menu.currentBox = startForceEnergyFor(state.difficulty);
    } else if (MENU_RESULT.isCursorMove(result)) {
      // Cursor move: store the low byte as the selected index and load that box.
      state.mode = CHALLENGE_FLOW_MODE.BOX_LOAD;
      state.subFlag = 0;
      state.selectedIndex = result & 0xff; // (char)menu_result
    }
  };

  // ===== mode 2: FUN_80196188 @0x80196188 (chunk_0048.c:199) =========================
  // Builds the box/force preview (PTR_DAT_80435a30) from the save block, then polls
  // zz_01ba750_ for completion -> back to mode 1.
  const mode_boxLoad = (): void => {
    if (state.subFlag === 0) {
      state.subFlag = 1;
      sink.buildBoxPreview(state.menu.currentBox); // builds PTR_DAT_80435a30 from save[box]
      return;
    }
    if (sink.isBoxPreviewReady()) { // zz_01ba750_() != 0
      state.mode = CHALLENGE_FLOW_MODE.MENU_POLL;
      state.subFlag = 0;
      state.selectedIndex = state.menu.currentBox; // restore cursor from preview
    }
  };

  // ===== mode 3: build_challenge_battle_setup @0x801962c4 (chunk_0048.c:234) ==========
  // Builds per-slot side/team tables from controllerMask + the dumped count/budget/pool
  // tables, rolls CPU rosters under the budget cap, sets mode=4 (subMode=0), and hands the
  // spawn to the sink.
  const mode_buildBattle = (): void => {
    state.mode = CHALLENGE_FLOW_MODE.IN_BATTLE; // *DAT_80436378 = 4 (set at top of ROM fn)

    const controllerMask = state.controllerMask;
    const difficulty = state.difficulty;
    const battleIndex = state.battleIndex;

    // local_60[2..3]/[0..1]: per-side count + budget for THIS battle (chunk_0048.c:309-312).
    const allyCount = rowValueAt(CHALLENGE_ALLY_COUNT_BY_BATTLE, difficulty, battleIndex);
    const enemyCount = rowValueAt(CHALLENGE_ENEMY_COUNT_BY_BATTLE, difficulty, battleIndex);
    const allyBudget = rowValueAt(CHALLENGE_ALLY_BUDGET_BY_BATTLE, difficulty, battleIndex);
    const enemyBudget = rowValueAt(CHALLENGE_ENEMY_BUDGET_BY_BATTLE, difficulty, battleIndex);

    // ROM local_40 = local_3c = 2: at most 2 CPU allies and 2 CPU enemies are auto-filled.
    const maxAllies = 2;
    const maxEnemies = 2;

    const slots: ChallengeSlotSetup[] = [];
    let activeMask = 0; // work[0x15d9]
    let activeCount = 0; // work[0x15da]
    let humanAllies = 0; // local_50: human-controlled side-0 slots
    let cpuEnemies = 0; // local_4c: side-1 slots filled

    // Loop 1 (chunk_0048.c:278-301): mark each slot's side from the controller mask.
    // work[slot+0xcb] = 0 where bit s is set (human), else 0xff (filled by loop 2).
    for (let slot = 0; slot < 6; slot += 1) {
      const isHuman = (controllerMask & (1 << slot)) !== 0;
      const side = isHuman ? 0 : 0xff;
      slots.push({ slot, side, active: isHuman, slotFlag: 0, roster: [] });
      if (isHuman) {
        humanAllies += 1;
        activeMask |= 1 << slot;
        activeCount += 1;
      }
    }

    // Loop 2 (chunk_0048.c:314-408): for each non-human slot, assign a side (ally first up
    // to maxAllies, then enemy up to maxEnemies) and roll its roster from the pool tables.
    for (const s of slots) {
      if ((controllerMask & (1 << s.slot)) !== 0) continue; // human slot: keep side 0
      let assigned = -1;
      if (humanAllies < maxAllies) {
        // local_50 < local_40: add a CPU ally to side 0.
        assigned = 0;
        s.side = 0;
        humanAllies += 1;
      } else if (cpuEnemies < maxEnemies) {
        // local_4c < local_3c: add a CPU enemy to side 1.
        assigned = cpuEnemies + 1;
        cpuEnemies = assigned;
        s.side = 1;
      }
      if (assigned >= 0) {
        activeMask |= 1 << s.slot;
        activeCount += 1;
        s.active = true;
        // Roll the roster (chunk_0048.c:335-361). Count cap + budget cap both apply.
        const side = s.side;
        const countCap = side === 0 ? allyCount : enemyCount; // local_60[side+2]
        const budget = side === 0 ? allyBudget : enemyBudget; // local_60[side]
        const poolRows = side === 0 ? CHALLENGE_ALLY_POOL_GROUP_TABLE : CHALLENGE_ENEMY_POOL_GROUP_TABLE;
        let spent = 0;
        while (s.roster.length < countCap) {
          // iVar2 = battleIndex*4 + (rand & 3) (chunk_0048.c:337-338). zz_00055fc_ is the
          // engine RNG; Math.random stands in for the pool-index low bits only.
          const rand = Math.floor(Math.random() * 0x100000000);
          const poolIdx = battleIndex * 4 + (rand & 3);
          const group = rowValueAt(poolRows, difficulty, poolIdx);
          const borgId = sink.drawBorgFromPool(group); // zz_0196eb8_(group)
          const cost = sink.borgCost(borgId); // zz_0066168_(borgId, 0)
          spent += twoThirdsCost(cost);
          if (budget < spent) break; // local_60[side] < iVar5
          s.roster.push({ borgId, cost });
        }
      }
    }

    // Per-slot common writes (chunk_0048.c:364-378) run for every slot. work[slot+0x32] =
    // DAT_804356ec[side + difficulty*2]; for inactive slots (side 0xff) the ROM reads OOB
    // (harmless — inactive slots are never spawned). We leave inactive slotFlag at 0.
    for (const s of slots) {
      if (s.active && (s.side === 0 || s.side === 1)) {
        s.slotFlag = CHALLENGE_SLOT_FLAG_BY_DIFFICULTY[s.side + difficulty * 2] ?? 0;
      }
    }

    // Stage reroll + scene seed (chunk_0048.c:401-406): zz_0029fd4_/zz_000685c_/zz_00064d4_
    // then *PTR_DAT_80433950 = DAT_804356e4[difficulty*2]; the stage byte work[0x1c] is
    // rerolled by zz_0196dac_ on each advance. The initial stage is drawn here.
    const stageId = sink.rerollStage(state.stage); // zz_0196dac_ (work[0x1c] != prev)
    state.stage = stageId;

    // ROM tail (chunk_0048.c:382-406): work[0x53]=2; work[0x46]=battleIndex; per-side init;
    // work[0x48]=work[0x4c]=18000; work[0x50]=1 (timer frozen); *PTR_DAT_80433950 =
    // DAT_804356e4[difficulty*2] (stage scene id pair).
    const setup: ChallengeBattleSetup = {
      difficulty,
      battleIndex,
      controllerMask,
      activeMask,
      activeCount,
      allyCount,
      enemyCount,
      allyBudget,
      enemyBudget,
      allyPoolGroup: rowValueAt(CHALLENGE_ALLY_POOL_GROUP_TABLE, difficulty, battleIndex * 4),
      enemyPoolGroup: rowValueAt(CHALLENGE_ENEMY_POOL_GROUP_TABLE, difficulty, battleIndex * 4),
      slots,
      stageId,
      stageIdPair: {
        primary: CHALLENGE_STAGE_ID_PAIR_BY_DIFFICULTY[difficulty * 2] ?? 0,
        secondary: CHALLENGE_STAGE_ID_PAIR_BY_DIFFICULTY[difficulty * 2 + 1] ?? 0,
      },
      timeLimitFrames: 18000,
      timerFrozen: true,
    };
    state.lastSetup = setup;
    sink.spawnBattleSetup(setup); // zz_0029fd4_ + zz_000685c_ + zz_00064d4_
    // Mode 4 begins in sub 0 (scene load wait); subFlag is the per-mode latch, separate
    // from subMode. ROM sets the work block counters here; we reset subMode on entry.
    state.subMode = 0;
    state.subFlag = 1;
  };

  // ===== mode 4 sub 0: FUN_801968cc @0x801968cc (chunk_0048.c:426) ===================
  // Polls zz_000a3c4_ (scene/camera ready). On ready, advance subMode and reset work[0..7].
  const sub_waitScene = (): void => {
    if (sink.isBattleSceneReady()) { // zz_000a3c4_() == 0 -> not yet; we invert: ready.
      state.subMode += 1; // *(short*)(modeBlock+4) += 1
      // ROM resets PTR_DAT_80433934[0..7] (battle scratch) — host-owned; no-op here.
    }
  };

  // ===== mode 4 sub 1: FUN_80196948 @0x80196948 (chunk_0048.c:450) ===================
  // Steps the battle (zz_0028264_). Ends when the global menu byte *PTR_DAT_80433930==1.
  const sub_runBattle = (): void => {
    sink.stepBattleFrame(); // zz_0028264_()
    if (sink.isBattleEnded()) { // *PTR_DAT_80433930 == 1
      state.subMode += 1; // *(short*)(modeBlock+4) += 1
      // ROM sets *PTR_DAT_80433930 = 3, [1] = 1 (marks menu-dirty); host-owned.
    }
  };

  // ===== mode 4 sub 2: FUN_801969a0 @0x801969a0 (chunk_0048.c:466) ===================
  // Win/loss gate. Finds the first human slot's side; advance only when the winner mask
  // has that side's bit AND mask <= 2. Otherwise -> mode 6 (fail). On advance, bump the
  // battle counter: more battles remain -> mode 3 (+ scene load); else -> mode 5 (clear).
  const sub_postBattle = (): void => {
    const winMask = sink.getWinnerMask(); // PTR_DAT_80433934[0x1f]
    const humanSlot = currentSlots().find((s) => (state.controllerMask & (1 << s.slot)) !== 0);
    const humanSide = humanSlot ? humanSlot.side : 0;
    // chunk_0048.c:486-487: fail unless (winMask & 1<<humanSide) && winMask <= 2.
    if ((winMask & (1 << humanSide)) === 0 || winMask > 2) {
      state.mode = CHALLENGE_FLOW_MODE.FAIL;
      state.subFlag = 0;
      return;
    }
    const next = state.battleIndex + 1; // sVar1+1
    state.battleIndex = next;
    if (next < state.battleTotal) { // (short)(sVar1+1) < battleTotal
      state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD; // rebuild for next battle
      state.subFlag = 0;
      // ROM: zz_0196dac_ (reroll stage) + zz_0042454_/zz_0042690_/zz_00437b0_ (load scene).
      state.stage = sink.rerollStage(state.stage);
      sink.loadBattleScene(state.stage);
    } else {
      state.mode = CHALLENGE_FLOW_MODE.CLEAR; // full clear
      state.subFlag = 0;
    }
  };

  /** Current per-slot side table (re-derived from controllerMask + last build). The ROM
   *  keeps this in PTR_DAT_80433934+0xcb; we re-derive for the post-battle gate so the VM
   *  stays pure between builds. Mirrors the loop-1 assignment exactly. */
  function currentSlots(): ChallengeSlotSetup[] {
    return state.lastSetup?.slots ?? [];
  }

  // ===== mode 4: FUN_8019688c @0x8019688c (chunk_0048.c:414) =========================
  // Sub-dispatches on subMode via PTR_FUN_8036f580, then runs the timer integrator.
  const mode_inBattle = (): void => {
    const handler = CHALLENGE_FLOW_SUB_MODE_TABLE[state.subMode];
    if (!handler || handler.address === "0x00000000") {
      throw new Error(`challenge-flow: mode-4 sub ${state.subMode} has no handler (PTR_FUN_8036f580)`);
    }
    if (state.subMode === 0) sub_waitScene();
    else if (state.subMode === 1) sub_runBattle();
    else if (state.subMode === 2) sub_postBattle();
    integrateTimer(state.timer); // zz_0196f64_ (runs every mode-4 frame)
  };

  // ===== mode 5: FUN_80196a9c @0x80196a9c (chunk_0048.c:510) — clear/victory ==========
  // Shows zz_01f5ae0_(difficulty); polls zz_01f5b68_ for dismiss -> mode 7.
  const mode_clear = (): void => {
    if (state.subFlag === 0) {
      state.subFlag = 1;
      sink.showResultsScreen(state.difficulty); // zz_01f5ae0_(*(modeBlock+0x13))
      return;
    }
    if (sink.isResultsDismissed()) { // zz_01f5b68_() != 0
      state.mode = CHALLENGE_FLOW_MODE.EXIT;
      state.subFlag = 0;
    }
  };

  // ===== mode 6: FUN_80196cec @0x80196cec (chunk_0048.c:618) — fail/defeat ============
  // Shows zz_01f5ae0_(3); polls zz_01f5b68_ for dismiss -> mode 7.
  const mode_fail = (): void => {
    if (state.subFlag === 0) {
      state.subFlag = 1;
      sink.showResultsScreen(3); // zz_01f5ae0_(3)
      return;
    }
    if (sink.isResultsDismissed()) {
      state.mode = CHALLENGE_FLOW_MODE.EXIT;
      state.subFlag = 0;
    }
  };

  // ===== mode 7: 0x80196d64 — exit/teardown ========================================
  // Not emitted by Ghidra; confirmed as the return-to-physical-menu handler. One-shot.
  const mode_exit = (): void => {
    if (state.subFlag === 0) {
      state.subFlag = 1;
      sink.exitToMenu();
    }
  };

  const handlers: ReadonlyArray<() => void> = [
    mode_init, // 0
    mode_pollMenu, // 1
    mode_boxLoad, // 2
    mode_buildBattle, // 3
    mode_inBattle, // 4
    mode_clear, // 5
    mode_fail, // 6
    mode_exit, // 7
  ];

  /** Port of dispatch_challenge_flow_state @0x80195f2c (chunk_0048.c:109). */
  const tick = (): void => {
    // Outer one-shot (global_menu_state[1]==0): clear the mode block, mark entered.
    if (!state.entered) {
      state.entered = true;
      sink.onEnterChallenge(); // zz_002a5f4_(0,0,0,0)
    }
    const handler = handlers[state.mode];
    if (!handler) throw new Error(`challenge-flow: unknown mode ${state.mode}`);
    handler();
  };

  return { state, tick };
}

// =====================================================================================
// Self-tests — exercise each mode dispatch, the selection poll, and the battle-setup
// build against the dumped tables. Pure: the sink is a recording stub.
// =====================================================================================

/** Minimal assert interface the host test runner supplies. */
export interface ChallengeFlowVmSelfTestAssert {
  equal<T>(actual: T, expected: T, label: string): void;
  ok(cond: boolean, label: string): void;
}

/** Recording sink: returns canned values and records spawn/scene/exit calls. */
interface RecordingSink extends ChallengeFlowEffectSink {
  menuResults: number[];
  menuIdx: number;
  spawned: ChallengeBattleSetup[];
  scenes: number[];
  results: number[];
  exited: boolean;
  sceneReady: boolean;
  battleEnded: boolean;
  winnerMask: number;
  boxReady: boolean;
  dismissed: boolean;
  drawnBorgs: number[];
  borgCosts: Record<number, number>;
  rerolled: number[];
}

function createRecordingSink(overrides: Partial<RecordingSink> = {}): RecordingSink {
  const sink: RecordingSink = {
    menuResults: [],
    menuIdx: 0,
    spawned: [],
    scenes: [],
    results: [],
    exited: false,
    sceneReady: true,
    battleEnded: false,
    winnerMask: 1,
    boxReady: true,
    dismissed: true,
    drawnBorgs: [0x0615, 0x000a, 0x0101],
    borgCosts: { 0x0615: 300, 0x000a: 300, 0x0101: 300 },
    rerolled: [],
    onEnterChallenge() {},
    onChallengeWorkInit() {},
    pollMenuResult() {
      return this.menuResults[this.menuIdx++] ?? 0;
    },
    onMenuOpened() {},
    buildBoxPreview() {},
    isBoxPreviewReady() {
      return this.boxReady;
    },
    spawnBattleSetup(setup) {
      this.spawned.push(setup);
    },
    isBattleSceneReady() {
      return this.sceneReady;
    },
    stepBattleFrame() {},
    isBattleEnded() {
      return this.battleEnded;
    },
    getWinnerMask() {
      return this.winnerMask;
    },
    rerollStage(prev) {
      const next = (prev + 1) % 15;
      this.rerolled.push(next);
      return next;
    },
    loadBattleScene(stageId) {
      this.scenes.push(stageId);
    },
    drawBorgFromPool() {
      return this.drawnBorgs[0] ?? 0x0615;
    },
    borgCost(id) {
      return this.borgCosts[id] ?? 300;
    },
    showResultsScreen(mode) {
      this.results.push(mode);
    },
    isResultsDismissed() {
      return this.dismissed;
    },
    exitToMenu() {
      this.exited = true;
    },
    ...overrides,
  };
  return sink;
}

/** Run the Challenge-flow VM self-tests against the dumped tables and ROM semantics. */
export function runChallengeFlowVmSelfTests(assert: ChallengeFlowVmSelfTestAssert): void {
  const { equal, ok } = assert;

  // --- Mode table faithfulness (PTR_FUN_8036f560 from boot.dol) ----------------------
  equal(CHALLENGE_FLOW_MODE_TABLE[0]!.address, "0x80195fbc", "mode 0 = init_challenge_flow_state");
  equal(CHALLENGE_FLOW_MODE_TABLE[1]!.address, "0x80196030", "mode 1 = poll_challenge_menu_selection");
  equal(CHALLENGE_FLOW_MODE_TABLE[2]!.address, "0x80196188", "mode 2 = FUN_80196188 (box load)");
  equal(CHALLENGE_FLOW_MODE_TABLE[3]!.address, "0x801962c4", "mode 3 = build_challenge_battle_setup");
  equal(CHALLENGE_FLOW_MODE_TABLE[4]!.address, "0x8019688c", "mode 4 = FUN_8019688c (in-battle)");
  equal(CHALLENGE_FLOW_MODE_TABLE[5]!.address, "0x80196a9c", "mode 5 = FUN_80196a9c (clear)");
  equal(CHALLENGE_FLOW_MODE_TABLE[6]!.address, "0x80196cec", "mode 6 = FUN_80196cec (fail)");
  equal(CHALLENGE_FLOW_MODE_TABLE[7]!.address, "0x80196d64", "mode 7 = 0x80196d64 (exit)");

  // --- Sub-dispatch table (PTR_FUN_8036f580) -----------------------------------------
  equal(CHALLENGE_FLOW_SUB_MODE_TABLE[0]!.address, "0x801968cc", "sub 0 = scene-wait");
  equal(CHALLENGE_FLOW_SUB_MODE_TABLE[1]!.address, "0x80196948", "sub 1 = battle run");
  equal(CHALLENGE_FLOW_SUB_MODE_TABLE[2]!.address, "0x801969a0", "sub 2 = post-battle gate");

  // --- Dumped data tables cross-validate the canonical JSON --------------------------
  equal([...CHALLENGE_BATTLE_COUNT_BY_DIFFICULTY].join(","), "5,10,15", "battle counts 5/10/15");
  equal([...CHALLENGE_START_FORCE_ENERGY].join(","), "1500,2000,2500", "force energy 1500/2000/2500");
  equal([...CHALLENGE_ALLY_COUNT_BY_BATTLE[0]!.row].join(","), "4,4,5,5,5", "normal ally counts");
  equal([...CHALLENGE_ENEMY_COUNT_BY_BATTLE[0]!.row].join(","), "10,10,8,8,1", "normal enemy counts");

  // --- Boot: init (mode 0) -> menu poll (mode 1) -------------------------------------
  {
    const sink = createRecordingSink();
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 0 });
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.INIT, "starts in INIT");
    vm.tick(); // outer enter + mode 0 init
    ok(vm.state.entered, "entered latch set");
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.MENU_POLL, "mode 0 -> mode 1");
    equal(vm.state.stage, 0xff, "work[0x1c] seeded to 0xff");
  }

  // --- Menu poll: cancel (< 0) -> exit (mode 7) --------------------------------------
  {
    const sink = createRecordingSink({ menuResults: [-1] });
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 0 });
    vm.tick(); // enter + mode 0 init -> mode 1 (subFlag reset to 0)
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.MENU_POLL, "init transitions to MENU_POLL");
    vm.tick(); // mode 1, subFlag==0: open latch (subFlag -> 1)
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.MENU_POLL, "open latch keeps MENU_POLL");
    vm.tick(); // mode 1, subFlag==1: poll returns -1 -> cancel
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.EXIT, "cancel -> EXIT");
    vm.tick(); // mode 7: exitToMenu
    ok(sink.exited, "exitToMenu invoked");
  }

  // --- Menu poll: confirm -> battle build (mode 3) seeds battleTotal + energy --------
  {
    const sink = createRecordingSink({ menuResults: [1] });
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 1 });
    vm.state.menu.difficulty = 1;
    vm.state.menu.boxIndex = 2;
    vm.tick(); // init
    vm.tick(); // open latch
    vm.tick(); // confirm (result 1)
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.BATTLE_BUILD, "confirm -> BATTLE_BUILD");
    equal(vm.state.difficulty, 1, "difficulty copied from menu");
    equal(vm.state.battleTotal, 10, "battleTotal = 10 for Tuff");
    equal(vm.state.menu.currentBox, 2000, "start force energy 2000 carried");
  }

  // --- Battle build (mode 3): slot/roster assignment + spawn -------------------------
  {
    const sink = createRecordingSink();
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 0 });
    vm.tick(); // init -> mode 1
    vm.state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD; // jump straight to build
    vm.state.subFlag = 0;
    vm.tick(); // run build
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.IN_BATTLE, "build sets mode 4");
    equal(sink.spawned.length, 1, "spawnBattleSetup called once");
    const setup = sink.spawned[0]!;
    equal(setup.battleIndex, 0, "first battle index 0");
    equal(setup.timerFrozen, true, "Challenge timer frozen");
    equal(setup.timeLimitFrames, 18000, "time limit 18000");
    equal(setup.activeCount, setup.slots.filter((s) => s.active).length, "activeCount matches slots");
    // controllerMask 0x01 -> slot 0 human (side 0); slots 1,2 CPU allies; slots 3,4 CPU enemies.
    const slot0 = setup.slots[0]!;
    equal(slot0.side, 0, "slot 0 is human side 0");
    ok(slot0.roster.length === 0, "human slot roster empty (uses player force)");
    const cpuAlly = setup.slots.find((s) => s.slot === 1);
    ok(cpuAlly !== undefined && cpuAlly.side === 0, "slot 1 auto-filled as CPU ally");
    const cpuEnemy = setup.slots.find((s) => s.slot === 3);
    ok(cpuEnemy !== undefined && cpuEnemy.side === 1, "slot 3 auto-filled as CPU enemy");
    // allyCount for normal battle 0 = 4; budget 1000; each borg costs floor(300*2/3)=200 -> 5 fit.
    ok(cpuAlly!.roster.length <= 4, "CPU ally roster respects allyCount cap (4)");
    ok(
      cpuAlly!.roster.reduce((acc, m) => acc + twoThirdsCost(m.cost), 0) <= 1000,
      "CPU ally roster respects allyBudget (1000)",
    );
  }

  // --- In-battle sub-dispatch: scene wait -> run -> post-battle advance --------------
  {
    const sink = createRecordingSink({
      sceneReady: true,
      battleEnded: false,
      winnerMask: 1,
      dismissed: false,
    });
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 0 });
    vm.tick(); // init
    vm.state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD;
    vm.state.subFlag = 0;
    vm.tick(); // build -> mode 4, subMode 0
    vm.state.battleTotal = 5; // set as the menu-confirm path would
    equal(vm.state.subMode, 0, "enter mode 4 at sub 0");
    vm.tick(); // sub 0: scene ready -> subMode 1
    equal(vm.state.subMode, 1, "scene ready advances to sub 1");
    vm.state.controllerMask = sink.spawned[0]!.controllerMask;
    sink.battleEnded = false;
    vm.tick(); // sub 1: battle running
    equal(vm.state.subMode, 1, "still sub 1 while battle running");
    sink.battleEnded = true;
    vm.tick(); // sub 1: battle ended -> subMode 2
    equal(vm.state.subMode, 2, "battle ended advances to sub 2");
    // sub 2: win (mask 1, human side 0), battleIndex 0 -> 1, battleTotal 5 -> rebuild.
    vm.tick();
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.BATTLE_BUILD, "win + battles remain -> rebuild");
    equal(vm.state.battleIndex, 1, "battleIndex advanced to 1");
    ok(sink.scenes.length >= 1, "loadBattleScene invoked on advance");
  }

  // --- Post-battle: loss -> fail (mode 6) --------------------------------------------
  {
    const sink = createRecordingSink({ winnerMask: 2, dismissed: true });
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 0 });
    vm.tick(); // init
    vm.state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD;
    vm.state.subFlag = 0;
    vm.tick(); // build
    vm.state.controllerMask = sink.spawned[0]!.controllerMask;
    vm.state.subMode = 2; // jump to post-battle
    vm.tick(); // sub 2: mask 2 (side1 won), human side 0 -> fail
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.FAIL, "loss -> FAIL");
    vm.tick(); // show fail screen
    equal(sink.results[0], 3, "fail shows zz_01f5ae0_(3)");
    vm.tick(); // dismissed -> exit
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.EXIT, "fail dismiss -> EXIT");
  }

  // --- Post-battle: full clear -> clear (mode 5) -------------------------------------
  {
    const sink = createRecordingSink({ winnerMask: 1, dismissed: true });
    const vm = createChallengeFlowVm(sink, { controllerMask: 0x01, difficulty: 0 });
    vm.tick(); // init
    vm.state.battleTotal = 1; // force a one-battle run
    vm.state.mode = CHALLENGE_FLOW_MODE.BATTLE_BUILD;
    vm.state.subFlag = 0;
    vm.tick(); // build (battleIndex 0)
    vm.state.controllerMask = sink.spawned[0]!.controllerMask;
    vm.state.subMode = 2;
    vm.tick(); // win, next(1) < total(1) false -> clear
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.CLEAR, "last battle won -> CLEAR");
    vm.tick(); // show clear screen at difficulty
    equal(sink.results[0], 0, "clear shows zz_01f5ae0_(difficulty=0)");
    vm.tick(); // dismissed -> exit
    equal(vm.state.mode, CHALLENGE_FLOW_MODE.EXIT, "clear dismiss -> EXIT");
  }

  // --- Timer integrator (zz_0196f64_) cascades frames -> seconds -> minutes ----------
  {
    const timer = { a: 0x3b, b: 0x3b, c: 99, d: 0 };
    // Re-run the integrator by exercising a mode-4 tick; here we just check the pure fn.
    // integrateTimer is file-local; emulate its threshold behavior at the boundary.
    integrateTimer(timer);
    equal(timer.a, 0xffff, "timer saturates to 0xffff after the 100-cap cascade");
  }
}
