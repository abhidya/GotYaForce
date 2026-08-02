/**
 * MainMenu — the physical seven-node desk menu owned by 0x800bf8d4.
 *
 * Navigation comes from DAT_80301cf0 and dispatch from PTR_FUN_802cfdc4. The visible
 * objects are the exact stff base/selection/label triplets in DAT_8038a760, rendered by
 * the recovered FUN_801cd90c task boundary in ../intro/physicalMenuScene.ts.
 */

import { el } from "../dom.js";
import { createPhysicalMenuController } from "../intro/physicalMenuController.js";
import {
  mountPhysicalMenuScene,
  type PhysicalMenuProjection,
} from "../intro/physicalMenuScene.js";
import type { MenuAction, MenuInputTarget } from "../menuInput.js";
import { createUiSceneHost } from "../sceneModel.js";

export type MainMenuMode =
  | "story"
  | "versus"
  | "challenge"
  | "edit-force"
  | "collection"
  | "trade"
  | "option";

interface MenuEntry {
  mode: MainMenuMode;
  label: string;
  sourceIndex: number;
}

// Index 1 is statically proven Challenge by PTR_FUN_802cfdc4[1] = 0x80195f2c.
// The remaining labels follow the native capture's authored model art; their controller
// indices, models, and direction edges are source-exact even where semantic function names
// are still generic in the decompile.
const ENTRIES: readonly MenuEntry[] = [
  { mode: "story", label: "STORY", sourceIndex: 0 },
  { mode: "challenge", label: "CHALLENGE", sourceIndex: 1 },
  { mode: "versus", label: "VERSUS", sourceIndex: 2 },
  { mode: "edit-force", label: "EDIT FORCE", sourceIndex: 3 },
  { mode: "trade", label: "TRADE", sourceIndex: 4 },
  { mode: "option", label: "OPTION", sourceIndex: 5 },
  { mode: "collection", label: "COLLECTION", sourceIndex: 6 },
];

export interface MainMenuOptions {
  onSelect: (mode: MainMenuMode) => void;
  initial?: MainMenuMode;
}

export interface MainMenuHandle extends MenuInputTarget {
  setSelected: (mode: MainMenuMode) => void;
  getSelected: () => MainMenuMode;
  destroy: () => void;
}

export function createMainMenu(container: HTMLElement, opts: MainMenuOptions): MainMenuHandle {
  let selected: MainMenuMode = opts.initial ?? "story";
  const initialEntry = ENTRIES.find((entry) => entry.mode === selected) ?? ENTRIES[0]!;
  const controller = createPhysicalMenuController(initialEntry.sourceIndex);
  const itemNodes = new Map<MainMenuMode, HTMLButtonElement>();

  const root = el("div", {
    class: "gf-screen gf-mainmenu",
    attrs: {
      role: "menu",
      "aria-label": "Main menu",
      "data-controller-evidence": "source-0x800bf8d4",
      "data-presentation-evidence": "source-DAT_8038a760",
    },
  });
  const frame = el("div", { class: "gf-mainmenu-frame" });
  const scene = createUiSceneHost("gf-ui-scene gf-mainmenu-source-scene");
  const ring = el("div", { class: "gf-mainmenu-ring" });

  function applyProjection(projection: PhysicalMenuProjection): void {
    const entry = ENTRIES.find((candidate) => candidate.sourceIndex === projection.menuIndex);
    if (!entry) return;
    const node = itemNodes.get(entry.mode);
    if (!node) return;
    node.style.left = `${projection.xPercent}%`;
    node.style.top = `${projection.yPercent}%`;
    node.style.pointerEvents = "auto";
    node.dataset["sourceProjection"] = "stff-camera";
  }

  const menuScene = mountPhysicalMenuScene(scene, initialEntry.sourceIndex, applyProjection);
  frame.appendChild(scene);

  for (const entry of ENTRIES) {
    const node = el("button", {
      class: "gf-menu-item gf-source-menu-hit",
      style: {
        left: "50%",
        top: "50%",
        width: "18%",
        height: "18%",
        pointerEvents: "none",
      },
      attrs: {
        type: "button",
        "data-mode": entry.mode,
        "data-source-menu-index": String(entry.sourceIndex),
        "aria-label": entry.label,
        role: "menuitem",
      },
      onClick: () => {
        if (selected === entry.mode) opts.onSelect(entry.mode);
        else setSelected(entry.mode);
      },
    });
    node.addEventListener("pointerenter", () => setSelected(entry.mode));
    itemNodes.set(entry.mode, node);
    ring.appendChild(node);
  }

  frame.appendChild(ring);
  root.appendChild(frame);

  function setSelected(mode: MainMenuMode): void {
    selected = mode;
    const entry = ENTRIES.find((candidate) => candidate.mode === mode) ?? ENTRIES[0]!;
    controller.setIndex(entry.sourceIndex);
    menuScene.setSelected(entry.sourceIndex);
    root.dataset["mode"] = mode;
    root.dataset["sourceMenuIndex"] = String(controller.index);
    root.dataset["sourceDispatch"] = controller.dispatchAddress;
    for (const [candidate, node] of itemNodes) {
      node.classList.toggle("gf-selected", candidate === mode);
      node.setAttribute("aria-pressed", String(candidate === mode));
    }
  }

  function moveBySourceTable(direction: "up" | "down" | "left" | "right"): void {
    const sourceIndex = controller.move(direction);
    const entry = ENTRIES.find((candidate) => candidate.sourceIndex === sourceIndex);
    if (entry) setSelected(entry.mode);
  }

  function onMenuAction(action: MenuAction): void {
    if (action === "right" || action === "left" || action === "down" || action === "up") {
      moveBySourceTable(action);
    } else if (action === "confirm") {
      opts.onSelect(selected);
    }
  }

  setSelected(selected);
  container.appendChild(root);
  return {
    setSelected,
    getSelected: () => selected,
    handleMenuInput: (event) => onMenuAction(event.action),
    destroy: () => {
      menuScene.destroy();
      root.remove();
    },
  };
}
