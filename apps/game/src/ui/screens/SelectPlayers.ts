/**
 * SelectPlayers — per reference `challenge-3-select-players.png`.
 *
 * Real game: FIGHT ALONE (1P) vs TEAM UP (2P co-op), person silhouettes in a
 * selection ring with blue label pills + GameCube controllers underneath, on a
 * green backdrop.
 *
 * Surface: the exported `vsel01` scene GLB is mounted as atmospheric backdrop
 * decoration, same rationale as SelectDifficulty.ts (vsel01 bundles every
 * vsel/challenge-select sub-menu's geometry into one 165-model archive with no
 * recoverable per-sub-menu grouping, so it cannot be reliably auto-fit to just
 * this cluster). The silhouette/pill/controller tiles themselves use the REAL
 * captured native frame (`reference/captures/challenge-3-select-players.png`)
 * cropped per-tile — the same "real captured asset" convention MainMenu.ts
 * already uses — since that frame already has the authentic baked
 * silhouette/label/controller art pixel-for-pixel, and Challenge only ever
 * offers these two fixed choices (not runtime-dynamic data). The title uses
 * the real exported ascii.tpl bitmap font (see bitmapText.ts). Challenge mode
 * is kept to the original two choices: 1 => FIGHT ALONE, 2 => TEAM UP.
 */

import { bitmapText, setBitmapText } from "../bitmapText.js";
import { captureCropImg, type CaptureCropBox } from "../captureCrop.js";
import { el, legendItem } from "../dom.js";
import { mountChallengeMenuMotion, type ChallengeMenuMotionHandle } from "../challengeMenuMotion.js";
import { subscribeMenuInput, type MenuAction } from "../menuInput.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

const CAPTURE = new URL(
  "../../../reference/captures/challenge-3-select-players.png",
  import.meta.url,
).href;
/** Native capture is 2560x1966; crop boxes below are in that pixel space. */
const CAPTURE_W = 2560;

const TILE_CROPS: Record<number, CaptureCropBox> = {
  1: { x: 300, y: 650, w: 730, h: 880 },
  2: { x: 1440, y: 650, w: 890, h: 880 },
};
const ARROW_CROP: CaptureCropBox = { x: 1107, y: 1088, w: 115, h: 115 };

export interface SelectPlayersOptions {
  /** Fired on confirm with the chosen player count (1..2 for Challenge). */
  onSelect: (playerCount: number) => void;
  onBack?: () => void;
  /** Highest selectable count. Original Challenge = 2; 3P/4P are out of scope. */
  maxPlayers?: number;
  initial?: number;
}

export interface SelectPlayersHandle {
  getSelected: () => number;
  destroy: () => void;
}

export function createSelectPlayers(
  container: HTMLElement,
  opts: SelectPlayersOptions,
): SelectPlayersHandle {
  const max = Math.max(1, Math.min(opts.maxPlayers ?? 2, 2));
  let selected = Math.min(Math.max(opts.initial ?? 1, 1), max);
  let motion: ChallengeMenuMotionHandle | null = null;
  let choosing = false;

  const root = el("div", { class: "gf-screen gf-vsel-screen gf-select-players" });
  const frame = el("div", { class: "gf-vsel-frame" });
  root.appendChild(frame);
  const selectScene = createUiSceneHost("gf-ui-scene gf-vsel-real-scene gf-vsel-players-scene");
  frame.appendChild(selectScene);
  // Shorter scale than SelectDifficulty's title: at scale 3 this 24-char string
  // (vs. "SELECT DIFFICULTY"'s 17) overflows a 4:3 frame at common viewport sizes.
  const title = bitmapText("gf-vsel-title-text");
  setBitmapText(title, "SELECT NUMBER OF PLAYERS", { bold: true, scale: 2, tint: "#ffd21e" });
  frame.appendChild(
    el("h1", { class: "gf-title gf-vsel-title", attrs: { "aria-label": "SELECT NUMBER OF PLAYERS" } }, [title]),
  );

  const row = el("div", { class: "gf-row gf-vsel-options" });
  const tiles = new Map<number, HTMLButtonElement>();
  const motionItems: Array<{ element: HTMLElement; delayFrames: number; fromX: number; fromY: number }> = [];

  for (let count = 1; count <= max; count++) {
    const label = count === 1 ? "FIGHT ALONE" : "TEAM UP";
    const crop = TILE_CROPS[count]!;
    const pad = el(
      "div",
      {
        class: "gf-player-tile-crop",
        style: { aspectRatio: `${crop.w} / ${crop.h}` } as Partial<CSSStyleDeclaration>,
        attrs: { role: "img", "aria-label": `${count} player ${label}` },
      },
      [captureCropImg(CAPTURE, CAPTURE_W, crop)],
    );

    const tile = el(
      "button",
      {
        class: `gf-option gf-player-option gf-player-${count}`,
        attrs: { type: "button", "data-count": String(count), "aria-label": `${count} player ${label}` },
        onClick: () => {
          if (!canInteract()) return;
          if (selected === count) void chooseSelected();
          else select(count);
        },
      },
      [pad],
    );
    tiles.set(count, tile);
    motionItems.push({
      element: tile,
      delayFrames: (count - 1) * 3,
      fromX: count === 1 ? -52 : 52,
      fromY: 82,
    });
    row.appendChild(tile);
  }
  frame.appendChild(row);

  const centerArrow = el(
    "div",
    {
      class: "gf-player-arrow gf-motion-object",
      style: { aspectRatio: `${ARROW_CROP.w} / ${ARROW_CROP.h}` } as Partial<CSSStyleDeclaration>,
      attrs: { "aria-hidden": "true" },
    },
    [captureCropImg(CAPTURE, CAPTURE_W, ARROW_CROP)],
  );
  motionItems.push({ element: centerArrow, delayFrames: 2, fromX: 0, fromY: 60 });
  frame.appendChild(centerArrow);

  frame.appendChild(
    el("div", { class: "gf-legend" }, [legendItem("b", "BACK"), legendItem("a", "CONFIRM")]),
  );

  function select(count: number): void {
    selected = count;
    let selectedNode: HTMLElement | null = null;
    for (const [c, node] of tiles) {
      const isSelected = c === count;
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
    const count = selected;
    await motion?.finish();
    opts.onSelect(count);
  }

  async function goBack(): Promise<void> {
    if (!opts.onBack || !canInteract()) return;
    choosing = true;
    await motion?.finish();
    opts.onBack();
  }

  function onMenuAction(action: MenuAction): void {
    if (!canInteract()) return;
    if (action === "right") {
      select(Math.min(selected + 1, max));
    } else if (action === "left") {
      select(Math.max(selected - 1, 1));
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
    sceneId: "vsel01",
    fitSize: 760,
    camera: { fov: 31, position: [0, 130, 900], lookAt: [0, 22, 0] },
    rotation: [-0.12, 0, 0],
  });
  const unsubscribeMenuInput = subscribeMenuInput((event) => onMenuAction(event.action));

  return {
    getSelected: () => selected,
    destroy: () => {
      motion?.destroy();
      stopScene();
      unsubscribeMenuInput();
      root.remove();
    },
  };
}
