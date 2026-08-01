/**
 * globalMenuDispatcher — 1:1 TypeScript port of the GG4E per-frame global-menu
 * mode dispatcher that owns every front-end screen transition.
 *
 * Source (all addresses are GG4E/NTSC-U boot.dol, decompiled in
 * `research/decomp/ghidra-export/chunk_0013.c` + `chunk_0014.c`):
 *
 *   - `dispatch_global_menu_mode` @0x8008c3ac (chunk_0013.c:2617) — per-frame:
 *        menu_mode = PTR_DAT_80433930[0x3e];
 *        (*(code *)(&PTR_FUN_802da780)[menu_mode])();
 *        zz_009752c_();
 *     i.e. read the mode byte, call the matching entry of the 11-fn render
 *     table, then commit the frame. This port's `tick()` is that function.
 *
 *   - `set_global_menu_mode` @0x8008c3a0 (chunk_0013.c:2606) — writes
 *        PTR_DAT_80433930[0x3e] = menu_mode. This port's `setMode()` is that.
 *
 *   - The 11-entry mode render table `PTR_FUN_802da780` (reviewed in
 *     `research/decomp/index/title-main-menu-flow.md`):
 *
 *       | mode | address    | reviewed name                              |
 *       | ---: | ---------- | ------------------------------------------ |
 *       |    0 | 0x8008cb64 | global_menu_mode_00_render                 |
 *       |    1 | 0x8008cec8 | global_menu_mode_01_render                 |
 *       |    2 | 0x8008cf20 | global_menu_mode_02_render                 |
 *       |    3 | 0x8008d050 | global_menu_mode_03_render                 |
 *       |    4 | 0x8008d1c4 | global_menu_mode_04_render                 |
 *       |    5 | 0x8008d2e8 | global_menu_mode_05_render                 |
 *       |    6 | 0x8008d35c | global_menu_mode_06_render                 |
 *       |    7 | 0x8008d468 | global_menu_mode_07_render                 |
 *       |    8 | 0x8008d524 | global_menu_mode_08_render                 |
 *       |    9 | 0x8008d5d0 | global_menu_mode_09_title_menu_render      |
 *       |   10 | 0x8008d64c | global_menu_mode_10_frontend_transition_render |
 *
 *   - The shared desk-menu composite `zz_008cbd4_` @0x8008cbd4
 *     (chunk_0013.c:3086) — branched render recipe used by modes 1 and 3; it
 *     reads `[0x29]` selectionIndex, `[0x33]` transitionDimFlag, `[0x3d]`
 *     sceneAuxMode and `[0x31]` animCounter, draws scene objects + overlays,
 *     commits the overlay batch, and increments `[0x31]` at the end. Ported
 *     inline below as `drawCompositeDeskMenu()`.
 *
 * Engine-effect boundary: every render primitive the ROM implements as a big
 * GX/HSD call (`zz_008c440_` 3D scene draw, `zz_008c62c_` camera-variant 3D
 * draw, `zz_008c88c_` overlay draw, `zz_008c9d4_` 2D HUD draw, `zz_008c3f0_`
 * render-order sync, `zz_002ab70_` overlay-batch commit, `zz_009752c_` frame
 * commit) is delegated to a `GlobalMenuEffectSink` so the renderer can map it
 * to three.js at the boundary. Each delegation is cited at the ROM call it
 * replaces. The render-object allocators `zz_002a888_` / `zz_002acd0_` only
 * thread an opaque HSD JObj handle between calls (never inspected by the
 * recipe), so the sink owns render-object lifecycle and they are folded out
 * of the control flow (cited at each call site they appeared).
 *
 * The state layout mirrors the ROM `PTR_DAT_80433930` block (field offsets
 * preserved as `_ofs0xNN` comments so this file is auditable against the
 * decompile). Renderers do NOT poll input or set modes themselves — the ROM
 * dispatchers are pure draw recipes that read shared state; transitions are
 * driven by external controllers (boot dispatcher `0x80017918`, physical desk
 * controller `0x800bf8d4` → see `physicalMenuController.ts`) calling
 * `set_global_menu_mode`. This port mirrors that: `setMode` is the only
 * transition primitive; the sink/host writes the selection/aux fields the
 * renderers read.
 */

import type { GameScreen } from "../../gameSession.js";

// ---------------------------------------------------------------------------
// ROM mode table (PTR_FUN_802da780). Addresses + reviewed names straight from
// research/decomp/index/title-main-menu-flow.md. `screen` is the documented
// correspondence to the source-shaped GameScreen enum (gameSession.ts); see
// ROM_MODE_TO_GAME_SCREEN below for the rationale.
// ---------------------------------------------------------------------------

export interface GlobalMenuModeEntry {
  /** Index into PTR_FUN_802da780 (and PTR_DAT_80433930[0x3e]). */
  readonly mode: number;
  /** boot.dol virtual address of the render fn. */
  readonly address: number;
  /** Reviewed decompile name. */
  readonly name: string;
  /** What this mode draws / owns. */
  readonly purpose: string;
  /** Corresponding source-shaped GameScreen (null = transition, not a screen). */
  readonly screen: GameScreen | null;
  /** How well the screen mapping is established. */
  readonly confidence: "confirmed" | "inferred";
}

export const GLOBAL_MENU_MODE_TABLE: readonly GlobalMenuModeEntry[] = [
  {
    mode: 0,
    address: 0x8008cb64,
    name: "global_menu_mode_00_render",
    purpose:
      "Boot/splash idle render. One 3D scene object (obj 0, preset 0/0) + its overlay + the default HUD layer. The minimal fallback frame drawn before the title sequence takes over.",
    screen: "loading",
    confidence: "inferred",
  },
  {
    mode: 1,
    address: 0x8008cec8,
    name: "global_menu_mode_01_render",
    purpose:
      "Desk-menu base render. Runs the shared composite desk recipe (zz_008cbd4_) then the default HUD layer. The desk diorama with no option highlighted (overview / idle menu).",
    screen: "menu",
    confidence: "confirmed",
  },
  {
    mode: 2,
    address: 0x8008cf20,
    name: "global_menu_mode_02_render",
    purpose:
      "Desk overview: draws all four desk scene objects (indices 0..3, preset 2, materials 3/5/4/6) + the base object (index 4, preset 0), each with a paired overlay, then the HUD layer. The 'all menu items visible' wide shot of the desk.",
    screen: "menu",
    confidence: "inferred",
  },
  {
    mode: 3,
    address: 0x8008d050,
    name: "global_menu_mode_03_render",
    purpose:
      "Physical desk menu (interactive). Runs the composite desk recipe, then draws the option-highlight HUD whose layout branches on selectionIndex [0x29] (==2 → four-option cursor set 6/3,6/5,6/4,6/6; ==1|3 → pair 5/7,5/8; ==0 or dimmed → plain 3/0). The physicalMenuController drives [0x29] here.",
    screen: "menu",
    confidence: "confirmed",
  },
  {
    mode: 4,
    address: 0x8008d1c4,
    name: "global_menu_mode_04_render",
    purpose:
      "Detail close-up. Draws a multi-object scene with presets 3 and 7, including one camera-variant object via zz_008c62c_ (slot 2), then the HUD layer. A zoomed detail/edit view of a desk item.",
    screen: "select-force",
    confidence: "inferred",
  },
  {
    mode: 5,
    address: 0x8008d2e8,
    name: "global_menu_mode_05_render",
    purpose:
      "Minimal render. A single HUD layer (0/0), one 3D scene object (preset 0/0) + its overlay, a render-order sync, then a closing HUD layer. Sparse frame used by peripheral screens (e.g. memory-card / load-box prompt).",
    screen: "load-box",
    confidence: "inferred",
  },
  {
    mode: 6,
    address: 0x8008d35c,
    name: "global_menu_mode_06_render",
    purpose:
      "Four-item list. Draws scene object 0 (preset 3) into four consecutive slots (0..3) then object 1 (preset 3) into slots 4 and 6, then the HUD layer. A 4-option selectable list (matches the difficulty/budget tier pick).",
    screen: "difficulty",
    confidence: "inferred",
  },
  {
    mode: 7,
    address: 0x8008d468,
    name: "global_menu_mode_07_render",
    purpose:
      "Three-item render. Draws scene object 0 (preset 0) three times (slots 0..2) with one paired overlay on slot 0, then the HUD layer. A short option list (matches the player-count pick 1P/2P).",
    screen: "players",
    confidence: "inferred",
  },
  {
    mode: 8,
    address: 0x8008d524,
    name: "global_menu_mode_08_render",
    purpose:
      "Preset-8 special. Draws two objects under lighting preset 8 (materials 1 then 2), one base object (preset 3), then the HUD layer. A distinct full-screen recipe (results / get-items stinger family).",
    screen: "results",
    confidence: "inferred",
  },
  {
    mode: 9,
    address: 0x8008d5d0,
    name: "global_menu_mode_09_title_menu_render",
    purpose:
      "Title 'Press Start' render. Draws three 3D scene objects only (slots 1/0/2; objs 1&1 preset 3, obj 2 preset 0) — the title logo scene. No HUD layer, no overlay, no render-order sync. Confirmed by research/decomp/index/title-main-menu-flow.md.",
    screen: "title",
    confidence: "confirmed",
  },
  {
    mode: 10,
    address: 0x8008d64c,
    name: "global_menu_mode_10_frontend_transition_render",
    purpose:
      "Front-end transition. A HUD-only recipe whose overlay set branches on selectionIndex [0x29] (==1|3 → transition pair 5/7,5/8; otherwise plain 3/0), framed by a leading slot-2 and trailing slot-4 HUD commit. The wipe/slide used between front-end screens; not itself a screen. Confirmed by title-main-menu-flow.md.",
    screen: null,
    confidence: "confirmed",
  },
];

/** Flat ROM mode → GameScreen lookup (index = mode). null = transition / not a screen. */
export const ROM_MODE_TO_GAME_SCREEN: readonly (GameScreen | null)[] =
  GLOBAL_MENU_MODE_TABLE.map((entry) => entry.screen);

/**
 * Mode 10 is the front-end transition; its *target* screen is selected by the
 * composite selectionIndex [0x29] that the transition reads. This maps that
 * index to the source-shaped GameScreen the transition is sliding toward, so
 * `gameSession.ts` can resolve the post-transition screen. Indices follow the
 * same option order the physical desk menu exposes (see physicalMenuController
 * + the recovered Challenge handoff at index 1).
 */
export function frontendTransitionTargetScreen(selectionIndex: number): GameScreen | null {
  switch (selectionIndex) {
    case 0:
      return "menu";
    case 1:
      return "difficulty";
    case 2:
      return "select-force";
    case 3:
      return "force";
    default:
      return null;
  }
}

// ---------------------------------------------------------------------------
// State (slice of PTR_DAT_80433930 the dispatcher + its renderers read/write).
// Offsets preserved as comments for audit against the decompile.
// ---------------------------------------------------------------------------

export interface GlobalMenuDispatcherState {
  /** +0x3e — the mode byte: index into PTR_FUN_802da780. Written by
   *  set_global_menu_mode; read first thing every frame by the dispatcher. */
  mode: number;
  /** +0x34 — render-list slot cursor. Every renderer writes this immediately
   *  before each draw primitive (the engine's frame builder consumes it to
   *  pick which render slot the next draw targets). Mirrored faithfully here
   *  and passed as the first arg to each sink draw call. */
  activeRenderSlot: number;
  /** +0x29 — signed selection index. Drives the composite desk recipe (mode 1/3)
   *  and the transition recipe (mode 10). Meaningful values 0..3; <0 or >3
   *  select the "no option" branch. Set by the physical desk controller. */
  selectionIndex: number;
  /** +0x33 — transition/dim flag. Nonzero → the composite draws only the plain
   *  fallback object (the desk is dimmed / hidden behind a transition). */
  transitionDimFlag: number;
  /** +0x31 — animation frame counter. Incremented once per composite call;
   *  bit 0 toggles between the two alt render roots inside the composite
   *  (e.g. selectionIndex==2 even→objs 0/1, odd→objs 2/3). */
  animCounter: number;
  /** +0x3d — scene aux mode (same field the titleVm opcode 0x0c writes).
   *  In the composite, selectionIndex==1 switches its branch on this byte. */
  sceneAuxMode: number;
}

// ---------------------------------------------------------------------------
// Engine-effect boundary.
// ---------------------------------------------------------------------------

/**
 * Render-effect sink. Each method is one ROM render primitive, cited at its
 * call site. The renderer implements this to map onto three.js.
 */
export interface GlobalMenuEffectSink {
  /** zz_008c440_(p9=sceneObjIndex, p10=lightPreset, p11=matPreset) @0x8008c440
   *  — draw one 3D scene object (camera + matrix + HSD CObj setup). `slot`
   *  is PTR_DAT_80433930[0x34] written just before the call. */
  drawScene3D(slot: number, sceneObjIndex: number, lightPreset: number, matPreset: number): void;
  /** zz_008c62c_(p9,p10,p11) @0x8008c62c — the camera-variant 3D draw (uses a
   *  different C_MTXLookAt eye/up than drawScene3D). Used once, by mode 4. */
  drawScene3DCameraVariant(
    slot: number,
    sceneObjIndex: number,
    lightPreset: number,
    matPreset: number,
  ): void;
  /** zz_008c88c_(p9,p10,p11) @0x8008c88c — overlay/widget draw: same scene
   *  object index space but rendered through the 4-light overlay pass
   *  (DAT_802da7ac) via zz_008c278_. */
  drawOverlay(slot: number, sceneObjIndex: number, lightPreset: number, matPreset: number): void;
  /** zz_008c9d4_(p9=layer, p10=matPreset) @0x8008c9d4 — 2D ortho HUD layer
   *  draw (menu chrome, cursors, prompts). */
  drawHud(slot: number, layer: number, matPreset: number): void;
  /** zz_002ab70_ @0x8002ab70 — flush/commit the current overlay sub-tree. The
   *  composite calls this after drawing the multi-object overlay branches. */
  commitOverlayBatch(): void;
  /** zz_008c3f0_ @0x8008c3f0 — resolve render order for the current field
   *  (reads zz_002b024_; swaps the two commit calls for double-buffer modes).
   *  The renderers call this between the 3D pass and the HUD pass. */
  syncRenderOrder(): void;
  /** zz_009752c_ @0x8009752c — per-frame HSD render commit. The dispatcher
   *  calls this last, unconditionally, after the mode handler returns. */
  commitFrame(): void;
}

export interface GlobalMenuDispatcher {
  readonly state: GlobalMenuDispatcherState;
  /** Port of set_global_menu_mode @0x8008c3a0: writes PTR_DAT_80433930[0x3e]. */
  setMode(mode: number): void;
  /** Port of dispatch_global_menu_mode @0x8008c3ac: reads mode, calls
   *  PTR_FUN_802da780[mode](), then zz_009752c_(). Call once per fixed frame. */
  tick(): void;
}

export function createGlobalMenuDispatcher(sink: GlobalMenuEffectSink): GlobalMenuDispatcher {
  const state: GlobalMenuDispatcherState = {
    mode: 0, // PTR_DAT_80433930[0x3e]; ROM boots into mode 0
    activeRenderSlot: 0, // [0x34]
    selectionIndex: 0, // [0x29]
    transitionDimFlag: 0, // [0x33]
    animCounter: 0, // [0x31]
    sceneAuxMode: 0, // [0x3d]
  };

  // Draw helpers: each writes [0x34] (faithful global write) then delegates to
  // the matching ROM primitive. The zz_002a888_ / zz_002acd0_ render-object
  // allocs that thread an opaque HSD JObj handle between ROM calls are folded
  // (sink owns render-object lifecycle); they are cited at each site below.

  const scene3d = (slot: number, obj: number, light: number, mat: number): void => {
    state.activeRenderSlot = slot; // PTR_DAT_80433930[0x34] = slot
    sink.drawScene3D(slot, obj, light, mat); // zz_008c440_(..., obj, light, mat)
  };
  const scene3dCam = (slot: number, obj: number, light: number, mat: number): void => {
    state.activeRenderSlot = slot; // [0x34] = slot
    sink.drawScene3DCameraVariant(slot, obj, light, mat); // zz_008c62c_(..., obj, light, mat)
  };
  const overlay = (slot: number, obj: number, light: number, mat: number): void => {
    state.activeRenderSlot = slot; // [0x34] = slot
    sink.drawOverlay(slot, obj, light, mat); // zz_008c88c_(..., obj, light, mat)
  };
  const hud = (slot: number, layer: number, mat: number): void => {
    state.activeRenderSlot = slot; // [0x34] = slot
    sink.drawHud(slot, layer, mat); // zz_008c9d4_(..., layer, mat)
  };

  // ========================================================================
  // zz_008cbd4_ @0x8008cbd4 (chunk_0013.c:3086) — shared composite desk render.
  // Two passes (3D via zz_008c440_, overlay via zz_008c88c_) over the SAME
  // branch tree keyed on selectionIndex [0x29] (signed), gated by
  // transitionDimFlag [0x33], with selectionIndex==1 further branched on
  // sceneAuxMode [0x3d] and the even/odd animCounter [0x31]. The overlay pass
  // commits its multi-object branches with zz_002ab70_, then [0x31] increments.
  // Used by modes 1 and 3.
  // ========================================================================
  const drawCompositeDeskMenu = (): void => {
    const dim = state.transitionDimFlag !== 0; // PTR_DAT_80433930[0x33]
    const si = state.selectionIndex | 0; // (char)[0x29] — signed semantics
    const even = (state.animCounter & 1) === 0; // ([0x31] & 1) == 0
    const auxZero = state.sceneAuxMode === 0; // [0x3d] == 0

    // ---- 3D pass (zz_008c440_ calls) ----
    if (dim) {
      // else-branch: zz_008c440_(param_1, ..., 0,0,0)
      scene3d(state.activeRenderSlot, 0, 0, 0);
    } else if (si === 2) {
      // zz_002acd0_() (alloc, folded); even→objs 0/1, odd→objs 2/3, preset 2
      if (even) {
        scene3d(state.activeRenderSlot, 0, 2, 3);
        scene3d(state.activeRenderSlot, 1, 2, 5);
      } else {
        scene3d(state.activeRenderSlot, 2, 2, 4);
        scene3d(state.activeRenderSlot, 3, 2, 6);
      }
    } else if (si < 2) {
      if (si === 0) {
        scene3d(state.activeRenderSlot, 0, 0, 0); // to param_1 root
      } else if (si > -1) {
        // si === 1
        if (auxZero) {
          scene3d(state.activeRenderSlot, 0, 1, 1);
          scene3d(state.activeRenderSlot, 1, 1, 2);
        } else {
          // zz_002acd0_() (alloc, folded); even→obj 0, odd→obj 1, preset 4
          if (even) scene3d(state.activeRenderSlot, 0, 4, 7);
          else scene3d(state.activeRenderSlot, 1, 4, 8);
        }
      }
      // si < 0 (e.g. -1): no 3D draw
    } else if (si < 4) {
      // si === 3 (==2 handled, <2 handled): zz_002acd0_() folded
      if (even) scene3d(state.activeRenderSlot, 0, 4, 7);
      else scene3d(state.activeRenderSlot, 1, 4, 8);
    }
    // si >= 4: no 3D draw

    // ---- overlay pass (zz_008c88c_ calls) ----
    sink.syncRenderOrder(); // uVar2 = zz_008c3f0_()
    if (dim) {
      overlay(state.activeRenderSlot, 0, 0, 0); // else-branch fallback
    } else if (si === 2) {
      if (even) {
        overlay(state.activeRenderSlot, 0, 2, 3);
        overlay(state.activeRenderSlot, 1, 2, 5);
      } else {
        overlay(state.activeRenderSlot, 2, 2, 4);
        overlay(state.activeRenderSlot, 3, 2, 6);
      }
      sink.commitOverlayBatch(); // zz_002ab70_()
    } else if (si < 2) {
      if (si === 0) {
        overlay(state.activeRenderSlot, 0, 0, 0);
      } else if (si > -1) {
        // si === 1
        if (auxZero) {
          overlay(state.activeRenderSlot, 0, 1, 1);
          overlay(state.activeRenderSlot, 1, 1, 2);
        } else if (even) {
          overlay(state.activeRenderSlot, 0, 4, 7);
        } else {
          overlay(state.activeRenderSlot, 1, 4, 8);
        }
        sink.commitOverlayBatch(); // zz_002ab70_()
      }
    } else if (si < 4) {
      // si === 3
      if (even) overlay(state.activeRenderSlot, 0, 4, 7);
      else overlay(state.activeRenderSlot, 1, 4, 8);
      sink.commitOverlayBatch(); // zz_002ab70_()
    }

    state.animCounter = (state.animCounter + 1) & 0xff; // PTR_DAT_80433930[0x31] += 1
  };

  // ========================================================================
  // The 11-entry mode handler table — port of PTR_FUN_802da780. Each handler
  // transcribes its decompile body line-for-line.
  // ========================================================================

  // mode 0 — FUN_8008cb64 @0x8008cb64 (chunk_0013.c:3059)
  const mode_00_render = (): void => {
    scene3d(0, 0, 0, 0); // zz_008c440_(..., 0,0,0)
    overlay(0, 0, 0, 0); // zz_008c88c_(uVar1, ..., 0,0,0)
    sink.syncRenderOrder(); // uVar1 = zz_008c3f0_()
    hud(0, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)  ([0x34] still 0)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 1 — zz_008cec8_ @0x8008cec8 (chunk_0013.c:3221)
  const mode_01_render = (): void => {
    state.activeRenderSlot = 0; // [0x34] = 0
    drawCompositeDeskMenu(); // zz_008cbd4_(param_1, ...)
    // zz_002a888_() (alloc, folded). [0x34] = whatever the composite left.
    hud(state.activeRenderSlot, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
    // zz_002a888_() (alloc, folded)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 2 — zz_008cf20_ @0x8008cf20 (chunk_0013.c:3241)
  const mode_02_render = (): void => {
    scene3d(0, 0, 2, 3); // zz_008c440_(..., 0,2,3)
    overlay(0, 0, 2, 3); // zz_008c88c_(..., 0,2,3)
    scene3d(1, 1, 2, 5); // zz_008c440_(..., 1,2,5)
    overlay(1, 1, 2, 5); // zz_008c88c_(..., 1,2,5)
    scene3d(2, 2, 2, 4); // zz_008c440_(..., 2,2,4)
    overlay(2, 2, 2, 4); // zz_008c88c_(..., 2,2,4)
    scene3d(3, 3, 2, 6); // zz_008c440_(..., 3,2,6)
    overlay(3, 3, 2, 6); // zz_008c88c_(..., 3,2,6)
    // zz_002a888_() (alloc, folded)
    scene3d(4, 4, 0, 0); // zz_008c440_(uVar1, ..., 4,0,0)
    overlay(4, 4, 0, 0); // zz_008c88c_(..., 4,0,0)
    sink.syncRenderOrder(); // uVar1 = zz_008c3f0_()
    hud(0, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 3 — zz_008d050_ @0x8008d050 (chunk_0013.c:3290)
  const mode_03_render = (): void => {
    state.activeRenderSlot = 0; // [0x34] = 0
    drawCompositeDeskMenu(); // zz_008cbd4_(param_1, ...)
    // zz_002a888_() (alloc, folded)
    if (state.transitionDimFlag !== 0) {
      // PTR_DAT_80433930[0x33] != 0 → plain HUD only
      hud(0, 3, 0); // zz_008c9d4_(uVar2, ..., 3,0)
    } else {
      const si = state.selectionIndex | 0; // (char)[0x29]
      if (si === 2) {
        hud(0, 6, 3); // zz_008c9d4_(..., 6,3)
        hud(1, 6, 5); // zz_008c9d4_(..., 6,5)
        hud(2, 6, 4); // zz_008c9d4_(..., 6,4)
        hud(3, 6, 6); // zz_008c9d4_(..., 6,6)
        hud(4, 3, 0); // zz_008c9d4_(..., 3,0)
      } else if (si === 0) {
        hud(0, 3, 0); // zz_008c9d4_(..., 3,0)
        hud(4, 3, 0); // zz_008c9d4_(..., 3,0)
      } else if (si > 0 && si < 4) {
        // si === 1 or si === 3
        hud(0, 5, 7); // zz_008c9d4_(..., 5,7)
        hud(1, 5, 8); // zz_008c9d4_(..., 5,8)
        hud(4, 3, 0); // zz_008c9d4_(..., 3,0)
      }
      // si < 0 or si > 3: the ROM returns with no extra HUD (cVar1<0 / >3 paths).
    }
  };

  // mode 4 — zz_008d1c4_ @0x8008d1c4 (chunk_0013.c:3349)
  const mode_04_render = (): void => {
    scene3d(0, 0, 3, 0); // zz_008c440_(param_1, ..., 0,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(4, 1, 7, 0); // zz_008c440_(uVar1, ..., 1,7,0)
    scene3d(5, 0, 3, 0); // zz_008c440_(uVar1, ..., 0,3,0)
    scene3d(1, 1, 7, 0); // zz_008c440_(uVar1, ..., 1,7,0)
    // zz_002a888_() (alloc, folded)
    scene3dCam(2, 2, 7, 0); // zz_008c62c_(uVar1, ..., 2,7,0)
    // zz_002a888_() (alloc, folded)
    scene3d(3, 3, 3, 0); // zz_008c440_(uVar1, ..., 3,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(6, 3, 3, 0); // zz_008c440_(uVar1, ..., 3,3,0)
    // zz_002a888_() (alloc, folded)
    hud(0, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 5 — zz_008d2e8_ @0x8008d2e8 (chunk_0013.c:3396)
  const mode_05_render = (): void => {
    hud(1, 0, 0); // zz_008c9d4_(param_1, ..., 0,0)
    // zz_002a888_() (alloc, folded)
    scene3d(0, 0, 0, 0); // zz_008c440_(uVar1, ..., 0,0,0)
    overlay(0, 0, 0, 0); // zz_008c88c_(uVar1, ..., 0,0,0)
    sink.syncRenderOrder(); // uVar1 = zz_008c3f0_()
    hud(0, 0, 0); // zz_008c9d4_(uVar1, ..., 0,0)  ([0x34] still 0)
  };

  // mode 6 — zz_008d35c_ @0x8008d35c (chunk_0013.c:3424)
  const mode_06_render = (): void => {
    scene3d(0, 0, 3, 0); // zz_008c440_(param_1, ..., 0,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(1, 0, 3, 0); // zz_008c440_(uVar1, ..., 0,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(2, 0, 3, 0); // zz_008c440_(uVar1, ..., 0,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(3, 0, 3, 0); // zz_008c440_(uVar1, ..., 0,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(4, 1, 3, 0); // zz_008c440_(uVar1, ..., 1,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(6, 1, 3, 0); // zz_008c440_(uVar1, ..., 1,3,0)
    // zz_002a888_() (alloc, folded)
    hud(0, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 7 — zz_008d468_ @0x8008d468 (chunk_0013.c:3470)
  const mode_07_render = (): void => {
    scene3d(0, 0, 0, 0); // zz_008c440_(param_1, ..., 0,0,0)
    overlay(0, 0, 0, 0); // zz_008c88c_(uVar1, ..., 0,0,0)
    // zz_002a888_() (alloc, folded)
    scene3d(1, 0, 0, 0); // zz_008c440_(uVar1, ..., 0,0,0)
    // zz_002a888_() (alloc, folded)
    scene3d(2, 0, 0, 0); // zz_008c440_(uVar1, ..., 0,0,0)
    // zz_002a888_() (alloc, folded)
    hud(0, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 8 — zz_008d524_ @0x8008d524 (chunk_0013.c:3506)
  const mode_08_render = (): void => {
    scene3d(0, 0, 8, 1); // zz_008c440_(param_1, ..., 0,8,1)
    scene3d(1, 0, 8, 2); // zz_008c440_(uVar1, ..., 0,8,2)
    // zz_002a888_() (alloc, folded)
    scene3d(2, 0, 3, 0); // zz_008c440_(uVar1, ..., 0,3,0)
    // zz_002a888_() (alloc, folded)
    hud(0, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
    // zz_002a888_() (alloc, folded)
    hud(4, 3, 0); // zz_008c9d4_(uVar1, ..., 3,0)
  };

  // mode 9 — zz_008d5d0_ @0x8008d5d0 (chunk_0013.c:3540)  title_menu_render
  const mode_09_title_menu_render = (): void => {
    scene3d(1, 1, 3, 0); // zz_008c440_(param_1, ..., 1,3,0)
    // zz_002a888_() (alloc, folded)
    scene3d(0, 2, 0, 0); // zz_008c440_(uVar1, ..., 2,0,0)
    // zz_002a888_() (alloc, folded)
    scene3d(2, 1, 3, 0); // zz_008c440_(uVar1, ..., 1,3,0)
    // zz_002a888_() (return unused)
  };

  // mode 10 — zz_008d64c_ @0x8008d64c (chunk_0013.c:3570)  frontend_transition_render
  const mode_10_frontend_transition_render = (): void => {
    // zz_002a888_() (alloc, folded)
    hud(2, 3, 0); // zz_008c9d4_(uVar2, ..., 3,0)
    const si = state.selectionIndex | 0; // (char)cVar1 = PTR_DAT_80433930[0x29]
    // ROM control flow: si==2 → goto LAB_end (no middle draw); si<2 → if si==0
    // draw hud(0,3,0) then goto end, else if si<0 goto end; si>3 → goto end;
    // fall-through (si==1 or si==3) draws the 5/7,5/8 transition pair.
    if (si === 0) {
      hud(0, 3, 0); // zz_008c9d4_(uVar2, ..., 3,0)  (si==0 plain hud, then goto end)
    } else if (si === 1 || si === 3) {
      hud(0, 5, 7); // zz_008c9d4_(uVar2, ..., 5,7)
      hud(1, 5, 8); // zz_008c9d4_(uVar2, ..., 5,8)
    }
    // si==2, si<0, si>3: reach LAB_end with no middle draw.
    // LAB_8008d6ec:
    hud(4, 3, 0); // zz_008c9d4_(uVar2, ..., 3,0)
  };

  // PTR_FUN_802da780 — 11-entry mode handler table.
  const MODE_HANDLERS: readonly (() => void)[] = [
    mode_00_render, // 0  @0x8008cb64
    mode_01_render, // 1  @0x8008cec8
    mode_02_render, // 2  @0x8008cf20
    mode_03_render, // 3  @0x8008d050
    mode_04_render, // 4  @0x8008d1c4
    mode_05_render, // 5  @0x8008d2e8
    mode_06_render, // 6  @0x8008d35c
    mode_07_render, // 7  @0x8008d468
    mode_08_render, // 8  @0x8008d524
    mode_09_title_menu_render, // 9  @0x8008d5d0
    mode_10_frontend_transition_render, // 10 @0x8008d64c
  ];

  const setMode = (mode: number): void => {
    // set_global_menu_mode @0x8008c3a0: PTR_DAT_80433930[0x3e] = menu_mode.
    // ROM does no bounds-checking (an OOB mode reads off the table). The port
    // accepts the value as-is to stay faithful; tick() will throw below if it
    // has no handler when dispatched.
    state.mode = mode;
  };

  const tick = (): void => {
    // dispatch_global_menu_mode @0x8008c3ac.
    const mode = state.mode; // (char)PTR_DAT_80433930[0x3e]
    const handler = MODE_HANDLERS[mode]; // (*(code *)(&PTR_FUN_802da780)[menu_mode])
    if (handler === undefined) {
      throw new RangeError(`global menu mode ${mode} is outside the 11-entry PTR_FUN_802da780 table`);
    }
    handler();
    sink.commitFrame(); // zz_009752c_()
  };

  return { state, setMode, tick };
}

// ---------------------------------------------------------------------------
// Integration spec (for gameSession.ts — do NOT edit gameSession.ts here).
// ---------------------------------------------------------------------------
//
// The current `gameSession.ts` owns the source-shaped `GameScreen` reducer and
// emits `{ type: "render"; screen }` effects. The ROM global-menu dispatcher
// owns the SAME front-end surface at a finer grain (11 modes vs 12 screens).
// To delegate, the host wires the dispatcher alongside the session like this:
//
//   const menu = createGlobalMenuDispatcher(threeJsMenuSink);
//   // boot: ROM starts in mode 0 (boot/splash) then set_global_menu_mode(9)
//   // for the title, mirroring session "loading" -> "title":
//   menu.setMode(9); // when session dispatches { type: "boot-ready" } -> "title"
//
//   // Each animation frame, after forwarding session events, drive the menu:
//   menu.tick(); // draws the current mode's recipe + commits the frame
//
//   // Screen <-> mode binding (use ROM_MODE_TO_GAME_SCREEN):
//   //   session screen "title"   <-> menu mode 9  (title_menu_render)
//   //   session screen "menu"    <-> menu modes 1/2/3 (desk menu base/overview/cursor)
//   //   session screen "loading" <-> menu mode 0  (boot/splash idle)
//   //   session screen "difficulty" <-> menu mode 6 (4-item list)
//   //   session screen "players" <-> menu mode 7 (3-item render)
//   //   session screen "select-force" <-> menu mode 4 (detail close-up)
//   //   session screen "load-box" <-> menu mode 5 (minimal render)
//   //   session screen "results"  <-> menu mode 8 (preset-8 special)
//   //   (briefing/battle/gets are runtime, not front-end menu modes)
//
//   // When the session transitions between front-end screens, route through the
//   // ROM's transition by entering mode 10 for one or more frames, with
//   // state.selectionIndex set to the target (see frontendTransitionTargetScreen
//   // for the inverse map), then settle into the destination mode. The
//   // physicalMenuController (physicalMenuController.ts) drives selectionIndex
//   // for the desk-menu modes 1/3.
//
//   // The dispatcher never mutates the session; the host reads session.screen,
//   // maps it to a mode (or a mode-10 transition), and calls menu.setMode +
//   // menu.tick each frame. Menu state fields the renderers read
//   // (selectionIndex / transitionDimFlag / sceneAuxMode) are written by the
//   // host/controllers, not by the dispatcher — exactly as the ROM does.

// ---------------------------------------------------------------------------
// Self-tests.
// ---------------------------------------------------------------------------

export type GlobalMenuAssertFn = (cond: boolean, msg: string) => void;

/** Recording sink used by the self-tests. Captures the exact call sequence so
 *  each mode's draw recipe can be asserted against the transcribed ROM body. */
interface RecordingSink extends GlobalMenuEffectSink {
  readonly calls: readonly MenuCall[];
  reset(): void;
}

type MenuCall =
  | { readonly kind: "scene3d"; readonly slot: number; readonly obj: number; readonly light: number; readonly mat: number }
  | { readonly kind: "scene3dCam"; readonly slot: number; readonly obj: number; readonly light: number; readonly mat: number }
  | { readonly kind: "overlay"; readonly slot: number; readonly obj: number; readonly light: number; readonly mat: number }
  | { readonly kind: "hud"; readonly slot: number; readonly layer: number; readonly mat: number }
  | { readonly kind: "overlayBatch" }
  | { readonly kind: "syncOrder" }
  | { readonly kind: "commitFrame" };

function createRecordingSink(): RecordingSink {
  const calls: MenuCall[] = [];
  const sink: RecordingSink = {
    get calls() {
      return calls;
    },
    reset() {
      calls.length = 0;
    },
    drawScene3D(slot, obj, light, mat) {
      calls.push({ kind: "scene3d", slot, obj, light, mat });
    },
    drawScene3DCameraVariant(slot, obj, light, mat) {
      calls.push({ kind: "scene3dCam", slot, obj, light, mat });
    },
    drawOverlay(slot, obj, light, mat) {
      calls.push({ kind: "overlay", slot, obj, light, mat });
    },
    drawHud(slot, layer, mat) {
      calls.push({ kind: "hud", slot, layer, mat });
    },
    commitOverlayBatch() {
      calls.push({ kind: "overlayBatch" });
    },
    syncRenderOrder() {
      calls.push({ kind: "syncOrder" });
    },
    commitFrame() {
      calls.push({ kind: "commitFrame" });
    },
  };
  return sink;
}

/** Count calls of a given kind in the recorded sequence. */
function countKind(calls: readonly MenuCall[], kind: MenuCall["kind"]): number {
  return calls.reduce((n, c) => (c.kind === kind ? n + 1 : n), 0);
}

/**
 * Self-tests for the global-menu dispatcher. Mirrors the
 * `runXxxSelfTests(assert)` convention from packages/combat. Covers setMode +
 * tick dispatch routing, the unconditional frame commit, each mode's draw
 * recipe signature, the composite desk-menu branch tree (all selectionIndex
 * cases + dim flag), the transition (mode 10) branch tree, animCounter
 * increment, and the ROM mode → GameScreen table completeness.
 */
export function runGlobalMenuDispatcherSelfTests(assert: GlobalMenuAssertFn): void {
  // --- setMode writes [0x3e] and tick reads it (set_global_menu_mode/dispatch). ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    assert(d.state.mode === 0, "dispatcher boots in mode 0");
    d.setMode(9);
    assert(d.state.mode === 9, "setMode writes state.mode ([0x3e])");
    sink.reset();
    d.tick();
    assert(sink.calls.at(-1)?.kind === "commitFrame", "tick ends with zz_009752c_ (commitFrame)");
    // mode 9 draws only 3 scene3d calls (no hud/overlay).
    assert(countKind(sink.calls, "scene3d") === 3, "mode 9 title renders exactly 3 scene objects");
    assert(countKind(sink.calls, "hud") === 0, "mode 9 title renders no HUD layer");
  }

  // --- every mode 0..10 dispatches its own handler (table routing). ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    for (let mode = 0; mode <= 10; mode++) {
      sink.reset();
      d.setMode(mode);
      d.tick();
      assert(
        sink.calls.length > 0 && sink.calls.at(-1)?.kind === "commitFrame",
        `mode ${mode} dispatches its handler and commits the frame`,
      );
    }
  }

  // --- OOB mode throws (defensive; ROM would read off the table). ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.setMode(11);
    let threw = false;
    try {
      d.tick();
    } catch {
      threw = true;
    }
    assert(threw, "mode 11 (OOB) throws a RangeError on tick");
  }

  // --- mode 0 body (FUN_8008cb64): scene3d(0,0,0,0) + overlay + sync + hud(3,0)x2. ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.setMode(0);
    d.tick();
    const c = sink.calls;
    assert(c[0]?.kind === "scene3d" && c[0].slot === 0 && c[0].obj === 0 && c[0].light === 0 && c[0].mat === 0, "mode 0 opens with scene3d slot0 obj0 preset0/0");
    assert(c[1]?.kind === "overlay" && c[1].slot === 0, "mode 0 draws the paired overlay at slot 0");
    assert(c[2]?.kind === "syncOrder", "mode 0 calls zz_008c3f0_ (syncRenderOrder) before HUD");
    const huds = c.filter((x) => x.kind === "hud");
    assert(huds.length === 2, "mode 0 draws two HUD layers");
    assert(huds[0]?.kind === "hud" && huds[0].slot === 0 && huds[0].layer === 3, "mode 0 first HUD at slot 0 layer 3");
    assert(huds[1]?.kind === "hud" && huds[1].slot === 4 && huds[1].layer === 3, "mode 0 second HUD at slot 4 layer 3");
    assert(d.state.activeRenderSlot === 4, "mode 0 leaves [0x34] = 4");
  }

  // --- mode 9 body (title_menu_render): three scene3d only, slots 1/0/2. ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.setMode(9);
    d.tick();
    const objs = sink.calls.filter((x) => x.kind === "scene3d");
    assert(objs.length === 3, "mode 9 draws exactly 3 scene objects");
    assert(objs[0]?.slot === 1 && objs[0].obj === 1 && objs[0].light === 3, "mode 9 obj 0: slot1 obj1 preset3");
    assert(objs[1]?.slot === 0 && objs[1].obj === 2 && objs[1].light === 0, "mode 9 obj 1: slot0 obj2 preset0");
    assert(objs[2]?.slot === 2 && objs[2].obj === 1 && objs[2].light === 3, "mode 9 obj 2: slot2 obj1 preset3");
  }

  // --- mode 4 body: uses the camera-variant draw (zz_008c62c_) exactly once. ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.setMode(4);
    d.tick();
    const cams = sink.calls.filter((x) => x.kind === "scene3dCam");
    assert(cams.length === 1, "mode 4 draws exactly one camera-variant object (zz_008c62c_)");
    assert(cams[0]?.slot === 2 && cams[0].obj === 2 && cams[0].light === 7, "mode 4 camera variant: slot2 obj2 preset7");
  }

  // --- mode 3 (physical desk menu) composite + selection HUD branches. ---
  // selectionIndex 0: composite draws fallback pair, then plain HUD 3/0 x2.
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.state.selectionIndex = 0;
    d.state.transitionDimFlag = 0;
    d.state.sceneAuxMode = 0;
    d.setMode(3);
    d.tick();
    const huds = sink.calls.filter((x) => x.kind === "hud");
    // composite (si==0) draws scene3d(0,0,0) + overlay(0,0,0); then mode 3 HUDs:
    // slot0 (3,0) + slot4 (3,0).
    assert(huds.every((h) => h.kind === "hud" && h.layer === 3 && h.mat === 0), "mode 3 si==0 draws only plain layer-3 HUDs");
    assert(huds.length === 2 && huds[0]?.slot === 0 && huds[1]?.slot === 4, "mode 3 si==0 HUD slots are 0 then 4");
  }
  // selectionIndex 2: four-option cursor set 6/3,6/5,6/4,6/6 + closing 3/0.
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.state.selectionIndex = 2;
    d.state.transitionDimFlag = 0;
    d.setMode(3);
    d.tick();
    const huds = sink.calls.filter((x) => x.kind === "hud");
    assert(huds.length === 5, "mode 3 si==2 draws five HUD layers (four cursor + closing)");
    assert(huds[0]?.slot === 0 && huds[0].layer === 6 && huds[0].mat === 3, "mode 3 si==2 cursor 0: slot0 layer6 mat3");
    assert(huds[1]?.slot === 1 && huds[1].layer === 6 && huds[1].mat === 5, "mode 3 si==2 cursor 1: slot1 layer6 mat5");
    assert(huds[2]?.slot === 2 && huds[2].layer === 6 && huds[2].mat === 4, "mode 3 si==2 cursor 2: slot2 layer6 mat4");
    assert(huds[3]?.slot === 3 && huds[3].layer === 6 && huds[3].mat === 6, "mode 3 si==2 cursor 3: slot3 layer6 mat6");
    assert(huds[4]?.slot === 4 && huds[4].layer === 3, "mode 3 si==2 closing HUD: slot4 layer3");
  }
  // selectionIndex 1 & 3: pair 5/7,5/8 + closing 3/0.
  {
    for (const si of [1, 3]) {
      const sink = createRecordingSink();
      const d = createGlobalMenuDispatcher(sink);
      d.state.selectionIndex = si;
      d.state.transitionDimFlag = 0;
      d.setMode(3);
      d.tick();
      const huds = sink.calls.filter((x) => x.kind === "hud");
      assert(huds.length === 3, `mode 3 si==${si} draws three HUD layers`);
      assert(huds[0]?.slot === 0 && huds[0].layer === 5 && huds[0].mat === 7, `mode 3 si==${si} pair a: slot0 layer5 mat7`);
      assert(huds[1]?.slot === 1 && huds[1].layer === 5 && huds[1].mat === 8, `mode 3 si==${si} pair b: slot1 layer5 mat8`);
      assert(huds[2]?.slot === 4 && huds[2].layer === 3, `mode 3 si==${si} closing HUD: slot4 layer3`);
    }
  }
  // transitionDimFlag != 0: composite draws fallback, mode 3 draws a single plain HUD.
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.state.selectionIndex = 2; // would normally draw 4 cursors
    d.state.transitionDimFlag = 1;
    d.setMode(3);
    d.tick();
    const huds = sink.calls.filter((x) => x.kind === "hud");
    assert(huds.length === 1 && huds[0]?.slot === 0 && huds[0].layer === 3, "mode 3 dimmed draws a single plain HUD regardless of selectionIndex");
  }

  // --- composite (zz_008cbd4_) selectionIndex==2 even/odd alternation. ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.state.selectionIndex = 2;
    d.state.transitionDimFlag = 0;
    d.state.animCounter = 0; // even
    d.setMode(1); // mode 1 runs the composite then HUD; no selection HUD override
    d.tick();
    const objs = sink.calls.filter((x) => x.kind === "scene3d");
    assert(objs.length === 2 && objs[0]?.obj === 0 && objs[1]?.obj === 1, "composite si==2 even draws objects 0 and 1");
    assert(sink.calls.some((x) => x.kind === "overlayBatch"), "composite si==2 commits the overlay batch (zz_002ab70_)");

    sink.reset();
    d.state.animCounter = 1; // odd (note: a prior tick already incremented it; reset explicitly)
    d.state.selectionIndex = 2;
    d.tick();
    const objsOdd = sink.calls.filter((x) => x.kind === "scene3d");
    assert(objsOdd.length === 2 && objsOdd[0]?.obj === 2 && objsOdd[1]?.obj === 3, "composite si==2 odd draws objects 2 and 3");
  }

  // --- composite animCounter increments once per call ([0x31] += 1). ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.state.selectionIndex = 0;
    d.state.transitionDimFlag = 0;
    d.setMode(1);
    const before = d.state.animCounter;
    d.tick();
    d.tick();
    assert(d.state.animCounter === ((before + 2) & 0xff), "composite increments animCounter once per tick");
  }

  // --- mode 10 (frontend transition) selectionIndex branch tree. ---
  {
    // si==0: (2,3,0) + (0,3,0) + (4,3,0)
    const sink0 = createRecordingSink();
    const d0 = createGlobalMenuDispatcher(sink0);
    d0.state.selectionIndex = 0;
    d0.setMode(10);
    d0.tick();
    const h0 = sink0.calls.filter((x) => x.kind === "hud");
    assert(h0.length === 3 && h0[0]?.slot === 2 && h0[1]?.slot === 0 && h0[2]?.slot === 4, "mode 10 si==0: slots 2,0,4 (no 5/7,5/8 pair)");

    // si==2: (2,3,0) + (4,3,0) only
    const sink2 = createRecordingSink();
    const d2 = createGlobalMenuDispatcher(sink2);
    d2.state.selectionIndex = 2;
    d2.setMode(10);
    d2.tick();
    const h2 = sink2.calls.filter((x) => x.kind === "hud");
    assert(h2.length === 2 && h2[0]?.slot === 2 && h2[1]?.slot === 4, "mode 10 si==2: slots 2,4 only");

    // si==1 & si==3: (2,3,0) + (0,5,7) + (1,5,8) + (4,3,0)
    for (const si of [1, 3]) {
      const sink = createRecordingSink();
      const d = createGlobalMenuDispatcher(sink);
      d.state.selectionIndex = si;
      d.setMode(10);
      d.tick();
      const h = sink.calls.filter((x) => x.kind === "hud");
      assert(h.length === 4, `mode 10 si==${si} draws four HUD layers`);
      assert(h[0]?.slot === 2 && h[0].layer === 3, `mode 10 si==${si} opens slot2 layer3`);
      assert(h[1]?.slot === 0 && h[1].layer === 5 && h[1].mat === 7, `mode 10 si==${si} transition pair a slot0 layer5 mat7`);
      assert(h[2]?.slot === 1 && h[2].layer === 5 && h[2].mat === 8, `mode 10 si==${si} transition pair b slot1 layer5 mat8`);
      assert(h[3]?.slot === 4 && h[3].layer === 3, `mode 10 si==${si} closes slot4 layer3`);
    }

    // si out of range (<0 or >3): same as si==2 (slots 2,4 only)
    const sinkNeg = createRecordingSink();
    const dNeg = createGlobalMenuDispatcher(sinkNeg);
    dNeg.state.selectionIndex = -1;
    dNeg.setMode(10);
    dNeg.tick();
    const hNeg = sinkNeg.calls.filter((x) => x.kind === "hud");
    assert(hNeg.length === 2 && hNeg[0]?.slot === 2 && hNeg[1]?.slot === 4, "mode 10 si==-1: slots 2,4 only (no pair)");
  }

  // --- mode 2 (desk overview) draws all four desk objects + base + overlays. ---
  {
    const sink = createRecordingSink();
    const d = createGlobalMenuDispatcher(sink);
    d.setMode(2);
    d.tick();
    const objs = sink.calls.filter((x) => x.kind === "scene3d");
    const overlays = sink.calls.filter((x) => x.kind === "overlay");
    assert(objs.length === 5, "mode 2 draws five 3D scene objects (four desk items + base)");
    assert(overlays.length === 5, "mode 2 pairs each 3D object with an overlay");
    // objects are (0,2,3),(1,2,5),(2,2,4),(3,2,6),(4,0,0)
    assert(objs[0]?.obj === 0 && objs[0].light === 2 && objs[0].mat === 3, "mode 2 obj0 preset2 mat3");
    assert(objs[3]?.obj === 3 && objs[3].mat === 6, "mode 2 obj3 preset2 mat6");
    assert(objs[4]?.obj === 4 && objs[4].light === 0, "mode 2 base obj4 preset0");
  }

  // --- ROM mode → GameScreen table completeness + confirmed anchors. ---
  {
    assert(GLOBAL_MENU_MODE_TABLE.length === 11, "mode table has exactly 11 entries (PTR_FUN_802da780)");
    assert(ROM_MODE_TO_GAME_SCREEN.length === 11, "screen lookup has exactly 11 entries");
    assert(ROM_MODE_TO_GAME_SCREEN[9] === "title", "mode 9 ↔ title (confirmed)");
    assert(ROM_MODE_TO_GAME_SCREEN[10] === null, "mode 10 ↔ null (transition, not a screen)");
    assert(GLOBAL_MENU_MODE_TABLE[3]?.confidence === "confirmed", "mode 3 mapping is confirmed (physical desk menu)");
    assert(frontendTransitionTargetScreen(1) === "difficulty", "transition target index 1 ↔ difficulty");
    assert(frontendTransitionTargetScreen(2) === "select-force", "transition target index 2 ↔ select-force");
    assert(frontendTransitionTargetScreen(99) === null, "transition target OOB ↔ null");
    // every entry has a unique ROM address
    const addrs = new Set(GLOBAL_MENU_MODE_TABLE.map((e) => e.address));
    assert(addrs.size === 11, "all 11 mode entries have distinct ROM addresses");
  }
}
