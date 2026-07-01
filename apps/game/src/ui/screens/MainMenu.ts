/**
 * MainMenu — the mode hub, per reference `title-main-menu.png`.
 *
 * The real game renders this as a 3D desk diorama where each mode is a physical
 * object ringed by a spinning gear cursor. This component keeps the Challenge
 * selection flow in place while the extracted desk/menu assets are wired.
 */

import { el } from "../dom.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

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
  tone: "red" | "blue" | "green" | "yellow" | "purple";
}

/** Ring order roughly matches the desk layout in the reference. */
const ENTRIES: readonly MenuEntry[] = [
  { mode: "story", label: "STORY", tone: "yellow" },
  { mode: "challenge", label: "CHALLENGE", tone: "red" },
  { mode: "edit-force", label: "EDIT FORCE", tone: "green" },
  { mode: "option", label: "OPTION", tone: "blue" },
  { mode: "trade", label: "TRADE", tone: "purple" },
  { mode: "collection", label: "COLLECTION", tone: "yellow" },
  { mode: "versus", label: "VERSUS", tone: "blue" },
];

export interface MainMenuOptions {
  /** Called on confirm (click or A/Enter on the highlighted item). */
  onSelect: (mode: MainMenuMode) => void;
  /** Initial highlighted mode. Defaults to "story" (the real default front item). */
  initial?: MainMenuMode;
  /** Optional real desk render to use as the backdrop (e.g. a captured frame). */
  deskImage?: string;
}

export interface MainMenuHandle {
  /** Move the highlight without confirming. */
  setSelected: (mode: MainMenuMode) => void;
  getSelected: () => MainMenuMode;
  destroy: () => void;
}

export function createMainMenu(container: HTMLElement, opts: MainMenuOptions): MainMenuHandle {
  let selected: MainMenuMode = opts.initial ?? "story";

  const root = el("div", { class: "gf-screen gf-mainmenu" });
  const titleScene = createUiSceneHost("gf-ui-scene gf-mainmenu-real-scene");
  root.appendChild(titleScene);
  if (opts.deskImage) {
    root.appendChild(
      el("div", { class: "gf-mainmenu-desk", style: { backgroundImage: `url(${opts.deskImage})` } }),
    );
  }

  const ring = el("div", { class: "gf-mainmenu-ring" });
  const itemNodes = new Map<MainMenuMode, HTMLButtonElement>();

  // Lay items out on an ellipse; the selected item additionally pops to center
  // via CSS scale. Positions approximate the desk arrangement.
  const n = ENTRIES.length;
  ENTRIES.forEach((entry, i) => {
    const angle = (-90 + (360 / n) * i) * (Math.PI / 180);
    const cx = 50 + Math.cos(angle) * 30;
    const cy = 46 + Math.sin(angle) * 30;
    const node = el(
      "button",
      {
        class: "gf-menu-item",
        style: { left: `${cx}%`, top: `${cy}%` },
        attrs: { type: "button", "data-mode": entry.mode, "aria-label": entry.label },
        onClick: () => {
          if (selected === entry.mode) opts.onSelect(entry.mode);
          else setSelected(entry.mode);
        },
      },
      [
        el("span", { class: `gf-menu-gear gf-menu-gear-${entry.tone}`, attrs: { "aria-hidden": "true" } }),
        el("span", { class: "gf-menu-label", text: entry.label }),
      ],
    );
    itemNodes.set(entry.mode, node);
    ring.appendChild(node);
  });

  root.appendChild(ring);
  root.appendChild(el("div", { class: "gf-mainmenu-logo", text: "GOTCHA FORCE" }));

  function setSelected(mode: MainMenuMode): void {
    selected = mode;
    for (const [m, node] of itemNodes) node.classList.toggle("gf-selected", m === mode);
  }

  function onKey(ev: KeyboardEvent): void {
    const order = ENTRIES.map((e) => e.mode);
    const idx = order.indexOf(selected);
    if (ev.key === "ArrowRight" || ev.key === "ArrowDown") {
      setSelected(order[(idx + 1) % order.length]!);
      ev.preventDefault();
    } else if (ev.key === "ArrowLeft" || ev.key === "ArrowUp") {
      setSelected(order[(idx - 1 + order.length) % order.length]!);
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key === " " || ev.key.toLowerCase() === "a") {
      opts.onSelect(selected);
      ev.preventDefault();
    }
  }

  setSelected(selected);
  container.appendChild(root);
  const stopTitleScene = mountUiSceneModels(titleScene, {
    sceneId: "tl00",
    fitSize: 780,
    camera: { fov: 28, position: [0, 110, 900], lookAt: [0, 20, 0] },
    rotation: [-0.1, 0, 0],
    maxModels: 37,
  });
  window.addEventListener("keydown", onKey);

  return {
    setSelected,
    getSelected: () => selected,
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      stopTitleScene();
      root.remove();
    },
  };
}
