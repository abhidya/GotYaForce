/**
 * GG4E NTSC-U front-end physical-menu WIDGET SYSTEM — a 1:1 lifecycle port of
 * `FUN_801cd90c` (research/decomp/ghidra-export/chunk_0056.c:1156) and the four
 * byte-verified kind-handler function tables documented in
 * research/decomp/index/title-main-menu-flow.md "Physical Menu Drawables".
 *
 * The ROM owns a small widget runtime: `FUN_801cd90c` walks 15 four-byte
 * descriptors at `DAT_8038a720` and allocates one widget struct per descriptor.
 * Each widget carries two fixed callbacks installed at construction:
 *   +0x0c -> `FUN_801cd9a8`  (think / task-state dispatch)
 *   +0x10c -> `FUN_801cdab0` (draw / draw-by-kind dispatch)
 * The think callback dispatches `PTR_FUN_8038a79c[+0x18]` (task-state); the
 * draw callback dispatches `PTR_FUN_8038a7c4[+0x11]` (draw-by-kind). Both the
 * init-by-kind (`PTR_FUN_8038a7ac[+0x11]`) and update-by-kind
 * (`PTR_FUN_8038a7b8[+0x11]`) tables are reached through the task-state[0]
 * handler `FUN_801cd9e4`, which on the first think tick flips +0x18 (0->1),
 * runs init-by-kind, then runs update-by-kind once before going steady.
 *
 * This module formalises that lifecycle without touching three.js: the factory
 * performs the `FUN_801cd90c` construction walk, and `init/update/draw`
 * reproduce the task-state + kind-handler dispatch exactly. Render side-effects
 * (model binding, matrix application) are routed through `MenuWidgetEffectSink`,
 * so `physicalMenuScene.ts` retains ownership of the WebGL objects while
 * delegating the ROM's widget ownership here.
 *
 * All descriptor/table data is consumed from `titleIntroScript.generated.ts`,
 * itself DOL-dumped from `user-data/GG4E/disc/sys/boot.dol` (sha1
 * 91b32873d62ae25c0a9b08d665e1e8c19ae38a5f) — i.e. DAT_8038a720,
 * DAT_8038a760, DAT_8038a78c, and the four handler tables.
 */

import {
  PHYSICAL_MENU_WIDGET_DESCRIPTORS,
  PHYSICAL_MENU_MODEL_TRIPLETS,
  PHYSICAL_MENU_ANGULAR_STEPS,
  PHYSICAL_MENU_HANDLERS,
  PHYSICAL_MENU_CURSOR_MODEL_ID,
} from "../titleIntroScript.generated.js";

// ---------------------------------------------------------------------------
// ROM constants (cited from chunk_0056.c decompile + title-main-menu-flow.md)
// ---------------------------------------------------------------------------

/** zz_01cdf08_ (chunk_0056.c:1456): cursor spin `*(short*)(+0x74) += 0x400`. */
const CURSOR_BAM_STEP = 0x400;
/** FUN_801cdaec (chunk_0056.c:1287): kind-0 `*(short*)(+0x7e) = 0xfe00` seed
 *  (i16 = -512). Only feeds the +0x16c pulse path in FUN_801cdbe0, never the
 *  base spin (the spin lives in +0x72). */
const ENTRY_PULSE_SEED_BAM = 0xfe00;
/** FUN_801cde10 / FUN_801ce0dc: `zz_00097b4_(+0xe0, 0x47)` — the material
 *  preset every kind-0/kind-2 draw call issues. */
const DRAW_MATERIAL_PRESET = 0x47;

/** ROM axis codes passed to gnt4_PSMTXRotRad_bl: 0x78='x', 0x79='y', 0x7a='z'.
 *  FUN_801cdcd0 spins the kind-0 base on 0x79 (Y); FUN_801cdf84 spins the
 *  cursor on 0x7a (Z). Documented for the sink implementor. */
export const MENU_WIDGET_AXIS_X = 0x78;
export const MENU_WIDGET_AXIS_Y = 0x79;
export const MENU_WIDGET_AXIS_Z = 0x7a;

/** Provenance re-exports of the four byte-verified handler tables
 *  (title-main-menu-flow.md), so callers/tests can cite ROM addresses. */
export const MENU_WIDGET_TASK_STATE_TABLE = PHYSICAL_MENU_HANDLERS.taskState; // 0x8038a79c
export const MENU_WIDGET_INIT_BY_KIND_TABLE = PHYSICAL_MENU_HANDLERS.initByKind; // 0x8038a7ac
export const MENU_WIDGET_UPDATE_BY_KIND_TABLE = PHYSICAL_MENU_HANDLERS.updateByKind; // 0x8038a7b8
export const MENU_WIDGET_DRAW_BY_KIND_TABLE = PHYSICAL_MENU_HANDLERS.drawByKind; // 0x8038a7c4

// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

export type MenuWidgetKind = 0 | 1 | 2;

export interface ReadonlyVec3 {
  readonly x: number;
  readonly y: number;
  readonly z: number;
}

const ZERO_VEC3: ReadonlyVec3 = { x: 0, y: 0, z: 0 };

/** One widget = one `zz_008893c_(2, 0x28, 1, priority)` allocation in
 *  `FUN_801cd90c`. Field offsets mirror the ROM struct so the dispatch
 *  provenance stays auditable. */
export interface MenuWidget {
  /** Descriptor slot in DAT_8038a720 (0..14). */
  readonly descriptorIndex: number;
  /** `puVar2[0x11] = *pcVar1` — descriptor byte 0 (kind). */
  readonly kind: MenuWidgetKind;
  /** `puVar2[0x12] = pcVar1[1]` — descriptor byte 1 (menu index). */
  readonly menuIndex: number;
  /** `*(short*)(pcVar1 + 2)` low byte — allocator priority argument. */
  readonly allocPriority: number;
  /** `*(short*)(pcVar1 + 2)` high byte — allocator layer argument. */
  readonly allocLayer: number;
  /** `*(char*)(+0x18)` task-state: 0 = init pending, 1 = steady update. */
  taskState: number;
  /** `*puVar2 = 1` active flag (construction default). */
  active: boolean;
  /** `puVar2[0x82]` visibility/active flag written by update-by-kind. */
  visible: boolean;
  /** kind 0: `*(short*)(+0x72)` base Y-spin accumulator.
   *  kind 1: `*(short*)(+0x74)` cursor Z-spin accumulator. */
  rotationBam: number;
  /** kind 0: `*(float*)(+0x16c)` pulse accumulator (FUN_801cdbe0 path). */
  pulseAccumulator: number;
  /** kind 0: DAT_8038a760 triplet[0] (base) — bound by FUN_801cdaec. */
  baseModelId: number;
  /** kind 0: DAT_8038a760 triplet[1] (selection) — bound by FUN_801cdaec. */
  selectionModelId: number;
  /** kind 2: DAT_8038a760 triplet[2] (label) — bound by FUN_801ce01c. */
  labelModelId: number;
  /** kind 1: literal model 0x38 (56) — bound by FUN_801cde60. */
  cursorModelId: number;
  /** kind 0: entry+0x144..14c (base world translation). kind 1: cursor+0x20..28
   *  (copied from the selected entry each update). */
  basePosition: ReadonlyVec3;
}

/** Global inputs the ROM reads from PTR_DAT_80433930 / PTR_DAT_80433940. */
export interface MenuWidgetSystemState {
  /** `PTR_DAT_80433930[0x32]` — signed current menu selection (cursor follow). */
  selectionIndex: number;
  /** `*(short*)PTR_DAT_80433940` — 0 normal, 2 = special hide (entry 5 only). */
  globalState: number;
  /** `PTR_DAT_80433940[0x1a]` — trigger/confirm flag gating selection visibility. */
  triggerActive: boolean;
}

/**
 * Render side-channel owned by `physicalMenuScene.ts`. Each method is one ROM
 * effect; the system computes every argument (BAM angles, positions, visibility)
 * faithfully and the sink only applies it to three.js objects.
 */
export interface MenuWidgetEffectSink {
  /** FUN_801cdaec (init kind 0): bind base (triplet[0]) + selection (triplet[1]).
   *  MUST return the base model's world translation — entry+0x144..14c — which
   *  `zz_01cdf08_` copies into the cursor each frame. */
  initEntry(menuIndex: number, baseModelId: number, selectionModelId: number): ReadonlyVec3;
  /** FUN_801cde60 (init kind 1): bind cursor model 0x38 (56). */
  initCursor(cursorModelId: number): void;
  /** FUN_801ce01c (init kind 2): bind label model triplet[2]. */
  initLabel(menuIndex: number, labelModelId: number): void;

  /** FUN_801cdbe0 (update kind 0): apply base Y-spin (`rotationBam` on axis
   *  0x79) and write the selection-model visibility (entry+0xe4 -> +0x10). */
  updateEntry(menuIndex: number, rotationBam: number, selectionVisible: boolean): void;
  /** zz_01cdf08_ (update kind 1): move the cursor to the selected entry's base
   *  position and apply the Z-spin (`rotationBam` on axis 0x7a). */
  updateCursor(position: ReadonlyVec3, rotationBam: number, cursorVisible: boolean): void;
  /** FUN_801ce084 (update kind 2): label per-frame update.
   *  [Partial: body absent from ghidra-export; only the visibility flag is
   *  modelled here. TODO dump FUN_801ce084.] */
  updateLabel(menuIndex: number): void;

  /** FUN_801cde10 (draw kind 0): draw base + selection (loop iVar1<2) with the
   *  given material preset (0x47). */
  drawEntry(menuIndex: number, materialPreset: number): void;
  /** FUN_801cdf84 (draw kind 1): draw the cursor (Z-rotated, at +0x20). */
  drawCursor(materialPreset: number): void;
  /** FUN_801ce0dc (draw kind 2): draw the label with the given material (0x47). */
  drawLabel(menuIndex: number, materialPreset: number): void;
}

export interface MenuWidgetSystem {
  /** The 15 widgets in DAT_8038a720 descriptor order. */
  readonly widgets: readonly MenuWidget[];
  /** Global menu inputs (selection / global state / trigger flag). */
  readonly state: MenuWidgetSystemState;
  /** First think tick (task-state[0] = FUN_801cd9e4) for every widget: flip
   *  +0x18 0->1, run init-by-kind[kind] (model binding), then run
   *  update-by-kind[kind] once. Descriptor order guarantees kind-0 entries bind
   *  before kind-1 builds its cursor lookup. NOTE: kind-1 init (FUN_801cde60)
   *  internally calls its update once, so the cursor ticks twice here — that
   *  double-tick is faithful to the ROM (cursor +0x74 = 0x800 after init). */
  init(): void;
  /** Steady think tick (task-state[1] = zz_01cda40_) for every widget: run
   *  update-by-kind[kind]. Call once per fixed frame after `init()`. */
  update(): void;
  /** `FUN_801cdab0` for every widget: run draw-by-kind[kind] via the sink. */
  draw(): void;
  /** Write PTR_DAT_80433930[0x32] (selection). Drives cursor follow + visibility. */
  setSelected(menuIndex: number): void;
  /** Write PTR_DAT_80433940[0x1a] (trigger/confirm flag). */
  setTriggerActive(active: boolean): void;
  /** Write *(short*)PTR_DAT_80433940 (0 normal / 2 special-hide). */
  setGlobalState(value: number): void;
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

/** Sign-extend a value into the i16 range, matching the ROM short arithmetic
 *  used on every BAM accumulator (+0x72, +0x74). Mirrors the `wrapI16` in
 *  physicalMenuScene.ts / titlePropController.ts. */
function wrapI16(value: number): number {
  return (value << 16) >> 16;
}

/** Compose the little-endian allocator short the ROM passes to
 *  `zz_008893c_(2, 0x28, 1, *(short*)(desc+2))` = (layer << 8) | priority. */
function composeAllocShort(layer: number, priority: number): number {
  return ((layer & 0xff) << 8) | (priority & 0xff);
}

// ---------------------------------------------------------------------------
// Factory — the FUN_801cd90c construction walk + dispatch tables
// ---------------------------------------------------------------------------

export function createMenuWidgetSystem(sink: MenuWidgetEffectSink): MenuWidgetSystem {
  // === FUN_801cd90c: walk DAT_8038a720, allocate one widget per descriptor ===
  // ROM loop: `for (pcVar1 = &DAT_8038a720; -1 < *pcVar1; pcVar1 += 4)`. The
  // generated table already excludes the terminating sentinel byte (kind < 0).
  const widgets: MenuWidget[] = PHYSICAL_MENU_WIDGET_DESCRIPTORS.map((desc) => {
    const widget: MenuWidget = {
      descriptorIndex: desc.index,
      kind: desc.kind as MenuWidgetKind,
      menuIndex: desc.menuIndex,
      allocPriority: desc.priority,
      allocLayer: desc.layer,
      taskState: 0, // +0x18: allocator zeroes -> state 0 (init pending)
      active: true, // *puVar2 = 1
      visible: true, // +0x82 (written by update-by-kind)
      rotationBam: 0, // +0x72 (kind 0) / +0x74 (kind 1)
      pulseAccumulator: 0, // +0x16c (kind 0)
      baseModelId: -1,
      selectionModelId: -1,
      labelModelId: -1,
      cursorModelId: -1,
      basePosition: ZERO_VEC3,
    };
    // ROM also installs the two fixed callbacks (+0x0c = FUN_801cd9a8 think,
    // +0x10c = FUN_801cdab0 draw) and +0x54 = &descriptor. These are constant
    // per widget and encoded by our dispatch tables below, so they are not
    // stored on the struct.
    return widget;
  });

  const state: MenuWidgetSystemState = {
    selectionIndex: 0, // PTR_DAT_80433930[0x32]
    globalState: 0, // *(short*)PTR_DAT_80433940
    triggerActive: true, // PTR_DAT_80433940[0x1a] (menu interactive at boot)
  };

  // === FUN_801cde60 builds cursor+0x144[index] = &entry from the entry linked
  //     list. We pre-index entries by menuIndex (entries always exist before
  //     the cursor thanks to descriptor order). ===
  const entriesByMenuIndex = new Map<number, MenuWidget>();
  for (const w of widgets) {
    if (w.kind === 0) entriesByMenuIndex.set(w.menuIndex, w);
  }

  const tripletFor = (menuIndex: number) => PHYSICAL_MENU_MODEL_TRIPLETS[menuIndex]!;
  const bamStepFor = (menuIndex: number): number =>
    PHYSICAL_MENU_ANGULAR_STEPS[menuIndex]?.bamStep ?? 0;

  // ====================================================== update-by-kind ====
  // PTR_FUN_8038a7b8: [0]=FUN_801cdbe0, [1]=zz_01cdf08_, [2]=FUN_801ce084.
  // Defined before init-by-kind because FUN_801cde60 calls zz_01cdf08_ directly.
  const updateByKind: Record<MenuWidgetKind, (w: MenuWidget) => void> = {
    0: (w) => {
      // FUN_801cdbe0: +0x72 += DAT_8038a78c[index] (all 0x200).
      w.rotationBam = wrapI16(w.rotationBam + bamStepFor(w.menuIndex));
      const isSelected = w.menuIndex === state.selectionIndex;
      const selectionVisible = isSelected && state.triggerActive;
      // +0x16c pulse: ROM adds (double)(i16)(+0x7e ^ sign) - DOUBLE_8043bd60 each
      // frame when not selected. +0x7e is the constant 0xfe00 seed (-512). The
      // DOUBLE_8043bd60 offset unit is unpinned -> stored as the raw i16 delta
      // (TODO: pin DOUBLE_8043bd60 for the exact sweep; sink owns the visual).
      if (!selectionVisible) {
        w.pulseAccumulator += wrapI16(ENTRY_PULSE_SEED_BAM);
      }
      // +0x82: globalState==2 deactivates every entry except index 5.
      w.visible = !(state.globalState === 2 && w.menuIndex !== 5);
      sink.updateEntry(w.menuIndex, w.rotationBam, selectionVisible);
    },
    1: (w) => {
      // zz_01cdf08_: cursor+0x20/24/28 = entry[selection]+0x144/148/14c; +0x74 += 0x400.
      const target = entriesByMenuIndex.get(state.selectionIndex);
      const pos = target ? target.basePosition : ZERO_VEC3;
      w.basePosition = pos;
      w.rotationBam = wrapI16(w.rotationBam + CURSOR_BAM_STEP);
      // +0x82: globalState<2 -> 0x21 (visible); else 0. triggerActive gates final hide.
      const cursorVisible = state.globalState < 2 && state.triggerActive;
      w.visible = cursorVisible;
      sink.updateCursor(pos, w.rotationBam, cursorVisible);
    },
    2: (w) => {
      // FUN_801ce084: [Partial — body not in ghidra-export.] The label has no
      // per-frame rotation; only its +0x82 visibility flag is reproduced here.
      // TODO: dump FUN_801ce084 for any additional recipe steps.
      w.visible = !(state.globalState === 2 && w.menuIndex !== 5);
      sink.updateLabel(w.menuIndex);
    },
  };

  // ========================================================= init-by-kind ===
  // PTR_FUN_8038a7ac: [0]=FUN_801cdaec, [1]=FUN_801cde60, [2]=FUN_801ce01c.
  const initByKind: Record<MenuWidgetKind, (w: MenuWidget) => void> = {
    // ---- FUN_801cdaec: bind base+selection from DAT_8038a760[index*6]; the
    //      loop reads 2 of the 3 triplet shorts (base, selection). Seed +0x7e.
    0: (w) => {
      const t = tripletFor(w.menuIndex);
      w.baseModelId = t.baseModelId;
      w.selectionModelId = t.selectionModelId;
      // entry+0x144..14c = base world translation (sink owns the GLB read).
      w.basePosition = sink.initEntry(w.menuIndex, w.baseModelId, w.selectionModelId);
      // *(short*)(+0x7e) = 0xfe00; *(short*)(+0x72) = 0 (rotationBam already 0).
      // +0x7e only feeds the +0x16c pulse path in update-by-kind[0] below.
    },
    // ---- FUN_801cde60: cursor. Build entry lookup, bind model 0x38, +0x74 = 0,
    //      then the explicit `zz_01cdf08_(param_9)` call at end of FUN_801cde60.
    1: (w) => {
      w.cursorModelId = PHYSICAL_MENU_CURSOR_MODEL_ID;
      sink.initCursor(w.cursorModelId);
      // *(short*)(+0x74) = 0 (rotationBam already 0). Then the explicit update:
      updateByKind[1](w);
    },
    // ---- FUN_801ce01c: bind label triplet[2]; +0x82 = 2.
    2: (w) => {
      const t = tripletFor(w.menuIndex);
      w.labelModelId = t.labelModelId;
      sink.initLabel(w.menuIndex, w.labelModelId);
      w.visible = false; // +0x82 = 2 (nonzero state flag; sink owns actual visibility)
    },
  };

  // ======================================================== draw-by-kind ====
  // PTR_FUN_8038a7c4: [0]=FUN_801cde10, [1]=FUN_801cdf84, [2]=FUN_801ce0dc.
  const drawByKind: Record<MenuWidgetKind, (w: MenuWidget) => void> = {
    // FUN_801cde10: loop iVar1<2 -> zz_00097b4_(+0xe0, 0x47) over base+selection.
    0: (w) => sink.drawEntry(w.menuIndex, DRAW_MATERIAL_PRESET),
    // FUN_801cdf84: cursor at +0x20, Z-rotated by +0x74.
    1: (_w) => sink.drawCursor(DRAW_MATERIAL_PRESET),
    // FUN_801ce0dc: zz_00097b4_(+0xe0, 0x47) for the label.
    2: (w) => sink.drawLabel(w.menuIndex, DRAW_MATERIAL_PRESET),
  };

  // ===================================== task-state dispatch (FUN_801cd9a8) ===
  // PTR_FUN_8038a79c[+0x18](): [0]=FUN_801cd9e4, [1]=zz_01cda40_, [2]/[3] unused.
  const think = (w: MenuWidget): void => {
    if (w.taskState === 0) {
      // FUN_801cd9e4: +0x18 = 1; +0x82 = 1; init-by-kind[kind]; zz_01cda40_().
      w.taskState = 1;
      w.visible = true;
      initByKind[w.kind](w);
      updateByKind[w.kind](w); // zz_01cda40_ -> update-by-kind[kind]
    } else {
      // zz_01cda40_ (state 1 steady): update-by-kind[kind].
      updateByKind[w.kind](w);
    }
  };

  return {
    widgets,
    state,
    init() {
      // First think tick for every widget (state 0 -> 1). Descriptor order
      // guarantees kind-0 entries bind their base translation before the
      // kind-1 cursor reads entry[selection].basePosition.
      for (const w of widgets) think(w);
    },
    update() {
      for (const w of widgets) updateByKind[w.kind](w);
    },
    draw() {
      // FUN_801cdab0: PTR_FUN_8038a7c4[+0x11]() for every widget.
      for (const w of widgets) drawByKind[w.kind](w);
    },
    setSelected(menuIndex) {
      state.selectionIndex = menuIndex;
    },
    setTriggerActive(active) {
      state.triggerActive = active;
    },
    setGlobalState(value) {
      state.globalState = value;
    },
  };
}

// ===========================================================================
// Self-tests
// ===========================================================================

export type MenuWidgetAssertFn = (cond: boolean, msg: string) => void;

interface RecordedCall {
  readonly fn: string;
  readonly args: readonly unknown[];
}

/** Recording sink for tests. Returns a distinct synthetic base translation per
 *  menuIndex so cursor-follow is observable without three.js. */
interface RecordingSink extends MenuWidgetEffectSink {
  readonly calls: readonly RecordedCall[];
  readonly basePositions: ReadonlyMap<number, ReadonlyVec3>;
  reset(): void;
}

function createRecordingSink(): RecordingSink {
  const calls: RecordedCall[] = [];
  const basePositions = new Map<number, ReadonlyVec3>();
  const posFor = (i: number): ReadonlyVec3 => ({ x: 100 + i, y: 200 + i, z: 300 + i });
  const rec = (fn: string, args: readonly unknown[]): void => {
    calls.push({ fn, args });
  };
  const sink: RecordingSink = {
    get calls() {
      return calls;
    },
    get basePositions() {
      return basePositions;
    },
    reset() {
      calls.length = 0;
    },
    initEntry(menuIndex, baseModelId, selectionModelId) {
      rec("initEntry", [menuIndex, baseModelId, selectionModelId]);
      const p = posFor(menuIndex);
      basePositions.set(menuIndex, p);
      return p;
    },
    initCursor(cursorModelId) {
      rec("initCursor", [cursorModelId]);
    },
    initLabel(menuIndex, labelModelId) {
      rec("initLabel", [menuIndex, labelModelId]);
    },
    updateEntry(menuIndex, rotationBam, selectionVisible) {
      rec("updateEntry", [menuIndex, rotationBam, selectionVisible]);
    },
    updateCursor(position, rotationBam, cursorVisible) {
      rec("updateCursor", [position, rotationBam, cursorVisible]);
    },
    updateLabel(menuIndex) {
      rec("updateLabel", [menuIndex]);
    },
    drawEntry(menuIndex, materialPreset) {
      rec("drawEntry", [menuIndex, materialPreset]);
    },
    drawCursor(materialPreset) {
      rec("drawCursor", [materialPreset]);
    },
    drawLabel(menuIndex, materialPreset) {
      rec("drawLabel", [menuIndex, materialPreset]);
    },
  };
  return sink;
}

const countFn = (calls: readonly RecordedCall[], fn: string): number =>
  calls.reduce((n, c) => (c.fn === fn ? n + 1 : n), 0);

/**
 * Self-tests for the physical-menu widget system. Mirrors the
 * `runXxxSelfTests(assert)` convention used by globalMenuDispatcher.ts and
 * challengeFlowVm.ts. Covers: DAT_8038a720 instantiation of all 15 widgets
 * (7 kind-0 / 1 kind-1 / 7 kind-2), the allocator priority short, kind-0
 * base/selection binding from DAT_8038a760, kind-2 label binding, the kind-1
 * cursor model (0x38) + its entry lookup, cursor position copy from the
 * selected entry, and the DAT_8038a78c / 0x400 BAM rotation increments
 * (including the ROM's faithful kind-1 init double-tick).
 */
export function runMenuWidgetSystemSelfTests(assert: MenuWidgetAssertFn): void {
  // --- FUN_801cd90c instantiation: 15 widgets, descriptor-order kinds. ---
  {
    const sink = createRecordingSink();
    const sys = createMenuWidgetSystem(sink);
    const kind0 = sys.widgets.filter((w) => w.kind === 0);
    const kind1 = sys.widgets.filter((w) => w.kind === 1);
    const kind2 = sys.widgets.filter((w) => w.kind === 2);
    assert(sys.widgets.length === 15, "FUN_801cd90c walks 15 descriptors at DAT_8038a720");
    assert(kind0.length === 7, "seven kind-0 entry descriptors (indices 0..6)");
    assert(kind1.length === 1, "one kind-1 cursor descriptor");
    assert(kind2.length === 7, "seven kind-2 label descriptors (indices 0..6)");
    // Descriptor order is DAT_8038a720 walk order: entries, then cursor, then labels.
    assert(
      sys.widgets[0]!.kind === 0 &&
        sys.widgets[6]!.kind === 0 &&
        sys.widgets[7]!.kind === 1 &&
        sys.widgets[8]!.kind === 2 &&
        sys.widgets[14]!.kind === 2,
      "descriptor order = 7 entries, cursor, 7 labels",
    );
    // Every widget boots in task-state 0 (init pending), active, BAM 0.
    assert(
      sys.widgets.every((w) => w.taskState === 0 && w.active && w.rotationBam === 0),
      "construction zeroes +0x18/+0x72 and sets *puVar2 = 1",
    );
    // Allocator priority short = (layer<<8)|priority per descriptor byte 2..3.
    assert(
      sys.widgets
        .slice(0, 7)
        .every((w) => w.allocPriority === 2 && composeAllocShort(w.allocLayer, w.allocPriority) === 2),
      "kind-0 descriptors carry alloc priority 2 (zz_008893c_ short = 2)",
    );
    assert(
      sys.widgets
        .slice(7)
        .every((w) => w.allocPriority === 1 && composeAllocShort(w.allocLayer, w.allocPriority) === 1),
      "kind-1/kind-2 descriptors carry alloc priority 1",
    );
  }

  // --- init(): kind-0 base/selection + kind-2 label binding from DAT_8038a760. ---
  {
    const sink = createRecordingSink();
    const sys = createMenuWidgetSystem(sink);
    sys.init();
    const entries = sys.widgets.filter((w) => w.kind === 0);
    for (const w of entries) {
      const t = PHYSICAL_MENU_MODEL_TRIPLETS[w.menuIndex]!;
      assert(
        w.baseModelId === t.baseModelId && w.selectionModelId === t.selectionModelId,
        `kind-0 init (FUN_801cdaec) binds base+selection for menu ${w.menuIndex}`,
      );
      assert(
        w.basePosition === sink.basePositions.get(w.menuIndex),
        `kind-0 entry ${w.menuIndex} stores base translation at +0x144 (cursor follow source)`,
      );
    }
    const labels = sys.widgets.filter((w) => w.kind === 2);
    for (const w of labels) {
      const t = PHYSICAL_MENU_MODEL_TRIPLETS[w.menuIndex]!;
      assert(
        w.labelModelId === t.labelModelId,
        `kind-2 init (FUN_801ce01c) binds label triplet[2] for menu ${w.menuIndex}`,
      );
    }
    const cursor = sys.widgets.find((w) => w.kind === 1)!;
    assert(cursor.cursorModelId === PHYSICAL_MENU_CURSOR_MODEL_ID, "kind-1 binds cursor model 0x38 (56)");
    assert(countFn(sink.calls, "initEntry") === 7, "init walks 7 initEntry calls (FUN_801cdaec)");
    assert(countFn(sink.calls, "initLabel") === 7, "init walks 7 initLabel calls (FUN_801ce01c)");
    assert(countFn(sink.calls, "initCursor") === 1, "init walks 1 initCursor call (FUN_801cde60)");
    // init() runs the state-0 transition for every widget -> all now steady.
    assert(sys.widgets.every((w) => w.taskState === 1), "init() flips +0x18 0->1 for all widgets");
  }

  // --- kind-1 cursor position copy (zz_01cdf08_): follows selected entry base. ---
  {
    const sink = createRecordingSink();
    const sys = createMenuWidgetSystem(sink);
    sys.init();
    const cursor = sys.widgets.find((w) => w.kind === 1)!;

    for (let i = 0; i < 7; i++) {
      sys.setSelected(i);
      sys.update();
      const expected = sink.basePositions.get(i)!;
      assert(
        cursor.basePosition.x === expected.x &&
          cursor.basePosition.y === expected.y &&
          cursor.basePosition.z === expected.z,
        `zz_01cdf08_ copies entry[${i}].+0x144 into cursor +0x20`,
      );
      const last = sink.calls.filter((c) => c.fn === "updateCursor").at(-1)!;
      const passedPos = last.args[0] as ReadonlyVec3;
      assert(
        passedPos.x === expected.x && passedPos.y === expected.y && passedPos.z === expected.z,
        `updateCursor receives entry[${i}] base translation`,
      );
    }
  }

  // --- BAM rotation increments: DAT_8038a78c (0x200) + cursor 0x400. ---
  {
    const sink = createRecordingSink();
    const sys = createMenuWidgetSystem(sink);
    sys.init();
    const entry = sys.widgets.find((w) => w.kind === 0 && w.menuIndex === 0)!;
    const cursor = sys.widgets.find((w) => w.kind === 1)!;

    // init() already ran update-by-kind once for entries (state-0 trailing tick).
    // entry +0x72 = 0 + 0x200; cursor +0x74 = 0x800 (FUN_801cde60's explicit
    // zz_01cdf08_ PLUS the state-0 trailing tick = two increments).
    assert(entry.rotationBam === 0x200, "kind-0 entry +0x72 = 0x200 after init (one DAT_8038a78c step)");
    assert(
      cursor.rotationBam === 0x800,
      "kind-1 cursor double-ticks on init (FUN_801cde60 explicit zz_01cdf08_ + state-0 tick) -> +0x74 = 0x800",
    );

    // One steady update() adds exactly one step per widget.
    sys.update();
    assert(entry.rotationBam === wrapI16(0x200 + 0x200), "update() advances entry +0x72 by one 0x200 step");
    assert(cursor.rotationBam === wrapI16(0x800 + 0x400), "update() advances cursor +0x74 by one 0x400 step");

    // After N updates, accumulator stays i16-wrapped (ROM short arithmetic).
    for (let i = 0; i < 200; i++) sys.update();
    let acc = 0x200; // post-init
    for (let i = 0; i < 201; i++) acc = wrapI16(acc + 0x200);
    assert(entry.rotationBam === acc, "entry +0x72 stays i16-wrapped over many updates");
  }

  // --- selection visibility (FUN_801cdbe0): only the selected entry shows. ---
  {
    const sink = createRecordingSink();
    const sys = createMenuWidgetSystem(sink);
    sys.init();
    sink.reset(); // isolate the steady update() calls from init's trailing tick
    sys.setSelected(3);
    sys.update();
    // Exactly one updateEntry call with selectionVisible=true (menu 3).
    const selCalls = sink.calls.filter((c) => c.fn === "updateEntry" && c.args[2] === true);
    assert(selCalls.length === 1 && selCalls[0]!.args[0] === 3, "only the selected entry's selection model is visible");
    // triggerActive=false hides all selection models (PTR_DAT_80433940[0x1a] gate).
    sink.reset();
    sys.setTriggerActive(false);
    sys.update();
    const anyVisible = sink.calls.some((c) => c.fn === "updateEntry" && c.args[2] === true);
    assert(!anyVisible, "triggerActive=false forces selectionVisible=false for every entry");
  }

  // --- draw() dispatches draw-by-kind once per widget with material 0x47. ---
  {
    const sink = createRecordingSink();
    const sys = createMenuWidgetSystem(sink);
    sys.init();
    sink.reset();
    sys.draw();
    assert(countFn(sink.calls, "drawEntry") === 7, "FUN_801cde10 draws 7 entries");
    assert(countFn(sink.calls, "drawCursor") === 1, "FUN_801cdf84 draws 1 cursor");
    assert(countFn(sink.calls, "drawLabel") === 7, "FUN_801ce0dc draws 7 labels");
    assert(
      sink.calls.every((c) => (c.args.at(-1) as number) === 0x47),
      "every draw call issues material preset 0x47 (zz_00097b4_)",
    );
  }
}
