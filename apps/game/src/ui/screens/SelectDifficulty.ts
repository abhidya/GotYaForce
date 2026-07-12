/**
 * SelectDifficulty — per reference `challenge-2-select-difficulty.png`.
 *
 * Three gears on colored oval pads = the GF-energy budget that becomes the force
 * LIMIT: NORMAL 1500 / TUFF 2000 / INSANE 2500.
 *
 * Surface: the exported `vsel00` scene GLB is mounted as atmospheric backdrop
 * decoration (its pad/gear/backdrop geometry — see
 * UI_SCENE_LAYOUTS.vsel00.semantics.difficulty — shares one 165-model archive
 * with every other vsel/challenge-select sub-menu and 40 unrelated stage-preview
 * dioramas, with no per-sub-menu model grouping recoverable from the export
 * metadata, so isolating just the difficulty cluster for a crisp full-opacity
 * render was not reliable). The three pad tiles themselves use the REAL
 * captured native frame (`reference/captures/challenge-2-select-difficulty.png`
 * — the same "real exported/captured asset" convention MainMenu.ts already
 * uses for its desk backdrop) cropped per-tile, since that frame already has
 * the authentic baked "GF ENERGY <n> <NAME>" art pixel-for-pixel — there is no
 * separate 2D pad/gear texture in the export distinct from the 3D geometry, and
 * the value/name is fixed per difficulty (not runtime-dynamic data), so a
 * static real capture is a more faithful surface than a CSS/bitmap-font
 * reconstruction. The title uses the real exported ascii.tpl bitmap font (see
 * bitmapText.ts). Selection highlight + motion system + menu-input wiring are
 * unchanged.
 */

import { bitmapText, setBitmapText } from "../bitmapText.js";
import { captureCropImg } from "../captureCrop.js";
import { el, legendItem } from "../dom.js";
import { mountChallengeMenuMotion, type ChallengeMenuMotionHandle } from "../challengeMenuMotion.js";
import type { MenuAction, MenuInputTarget } from "../menuInput.js";
import { UI_SCENE_LAYOUTS } from "../layout.generated.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

const DIFFICULTY_LAYOUT = UI_SCENE_LAYOUTS.vsel00.semantics.difficulty;

const CAPTURE = new URL(
  "../../../reference/captures/challenge-2-select-difficulty.png",
  import.meta.url,
).href;
/** Native capture is 2560x1966; crop boxes below are in that pixel space. */
const CAPTURE_W = 2560;

export type Difficulty = "normal" | "tuff" | "insane";

interface DiffEntry {
  key: Difficulty;
  energy: number;
  name: string;
  /** Pixel crop box (native capture space) isolating this pad/gear tile. */
  crop: { x: number; y: number; w: number; h: number };
}

const ENTRIES: readonly DiffEntry[] = [
  { key: "normal", energy: 1500, name: "NORMAL", crop: { x: 90, y: 640, w: 825, h: 845 } },
  { key: "tuff", energy: 2000, name: "TUFF", crop: { x: 964, y: 787, w: 687, h: 698 } },
  { key: "insane", energy: 2500, name: "INSANE", crop: { x: 1668, y: 768, w: 764, h: 717 } },
];

export interface SelectDifficultyOptions {
  /** Fired on confirm with the chosen GF-energy budget (1500/2000/2500). */
  onSelect: (budget: number, difficulty: Difficulty) => void;
  /** Fired on B / back. */
  onBack?: () => void;
  initial?: Difficulty;
}

export interface SelectDifficultyHandle extends MenuInputTarget {
  getSelected: () => Difficulty;
  destroy: () => void;
}

export function createSelectDifficulty(
  container: HTMLElement,
  opts: SelectDifficultyOptions,
): SelectDifficultyHandle {
  let selected: Difficulty = opts.initial ?? "normal";
  let motion: ChallengeMenuMotionHandle | null = null;
  let choosing = false;

  const root = el("div", {
    class: "gf-screen gf-vsel-screen gf-select-difficulty",
    style: difficultyLayoutVars(),
  });
  const frame = el("div", { class: "gf-vsel-frame" });
  root.appendChild(frame);
  const selectScene = createUiSceneHost("gf-ui-scene gf-vsel-real-scene gf-vsel-difficulty-scene");
  frame.appendChild(selectScene);
  const title = bitmapText("gf-vsel-title-text");
  setBitmapText(title, "SELECT DIFFICULTY", { bold: true, scale: 3, tint: "#ffd21e" });
  frame.appendChild(el("h1", { class: "gf-title gf-vsel-title", attrs: { "aria-label": "SELECT DIFFICULTY" } }, [title]));

  const row = el("div", { class: "gf-row gf-vsel-options" });
  const tiles = new Map<Difficulty, HTMLButtonElement>();
  const motionItems: Array<{ element: HTMLElement; delayFrames: number; fromX: number; fromY: number }> = [];

  for (const [index, e] of ENTRIES.entries()) {
    const pad = el(
      "div",
      {
        class: "gf-diff-pad-crop",
        style: { aspectRatio: `${e.crop.w} / ${e.crop.h}` } as Partial<CSSStyleDeclaration>,
        attrs: { role: "img", "aria-label": `GF ENERGY ${e.energy} ${e.name}` },
      },
      [captureCropImg(CAPTURE, CAPTURE_W, e.crop)],
    );

    const tile = el(
      "button",
      {
        class: `gf-option gf-diff-option gf-diff-${e.key}`,
        attrs: { type: "button", "data-diff": e.key, "aria-label": `${e.name} ${e.energy}` },
        onClick: () => {
          if (!canInteract()) return;
          if (selected === e.key) void chooseSelected();
          else select(e.key);
        },
      },
      [pad],
    );
    tiles.set(e.key, tile);
    motionItems.push({
      element: tile,
      delayFrames: index * 2,
      fromX: e.key === "normal" ? -56 : e.key === "insane" ? 56 : 0,
      fromY: 74,
    });
    row.appendChild(tile);
  }
  frame.appendChild(row);

  const legend = el("div", { class: "gf-legend" }, [
    legendItem("b", "BACK"),
    legendItem("a", "CONFIRM"),
  ]);
  frame.appendChild(legend);

  function select(key: Difficulty): void {
    selected = key;
    let selectedNode: HTMLElement | null = null;
    for (const [k, node] of tiles) {
      const isSelected = k === key;
      node.classList.toggle("gf-selected", isSelected);
      if (isSelected) selectedNode = node;
    }
    motion?.pulseSelected(selectedNode);
  }

  function canInteract(): boolean {
    return Boolean(motion?.isReady()) && !choosing;
  }

  async function chooseSelected(): Promise<void> {
    if (!canInteract()) return;
    choosing = true;
    const e = ENTRIES.find((x) => x.key === selected)!;
    await motion?.finish();
    opts.onSelect(e.energy, e.key);
  }

  async function goBack(): Promise<void> {
    if (!opts.onBack || !canInteract()) return;
    choosing = true;
    await motion?.finish();
    opts.onBack();
  }

  function onMenuAction(action: MenuAction): void {
    if (!canInteract()) return;
    const order = ENTRIES.map((e) => e.key);
    const idx = order.indexOf(selected);
    if (action === "right") {
      select(order[Math.min(idx + 1, order.length - 1)]!);
    } else if (action === "left") {
      select(order[Math.max(idx - 1, 0)]!);
    } else if (action === "confirm") {
      void chooseSelected();
    } else if (action === "back") {
      void goBack();
    }
  }

  motion = mountChallengeMenuMotion(root, motionItems);
  select(selected);
  container.appendChild(root);
  const stopScene = mountUiSceneModels(selectScene, {
    sceneId: "vsel00",
    fitSize: 760,
    camera: { fov: 31, position: [0, 130, 900], lookAt: [0, 22, 0] },
    rotation: [-0.12, 0, 0],
  });
  return {
    getSelected: () => selected,
    handleMenuInput: (event) => onMenuAction(event.action),
    destroy: () => {
      motion?.destroy();
      stopScene();
      root.remove();
    },
  };
}

/**
 * Scene-derived positioning for the difficulty option row, following the
 * SelectForce CSS-var pattern. The vsel00 export only yields the shared option
 * stage (see the anchor's caveat: per-difficulty X offsets are runtime JOBJ
 * placement and are not in the geometry), so only the row's center X/Y is
 * derived; the pad spread stays hand-tuned in CSS, and CSS fallbacks cover a
 * missing anchor.
 */
function difficultyLayoutVars(): Partial<CSSStyleDeclaration> {
  const stage = DIFFICULTY_LAYOUT?.optionStage;
  if (!stage) return {};
  return {
    "--gf-diff-row-top": `${stage.centerY}%`,
    "--gf-diff-center-x": `${stage.centerX}%`,
  } as Partial<CSSStyleDeclaration>;
}
