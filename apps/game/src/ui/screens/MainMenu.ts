/**
 * MainMenu - the mode hub, per reference `challenge-1-main-menu.png`.
 *
 * The real game renders this as a 3D desk diorama where each mode is a physical
 * object on the desk. The extracted `optn00_mdl.arc` model is identified as the
 * source menu scene, but the DAE export is still blocked, so this component uses
 * the live reference captures as the desk layer and exposes click/keyboard
 * hotspots over the real objects.
 */

import { el } from "../dom.js";

export type MainMenuMode =
  | "story"
  | "versus"
  | "action"
  | "challenge"
  | "edit-force"
  | "collection"
  | "trade"
  | "option";

interface MenuEntry {
  mode: MainMenuMode;
  label: string;
  x: number;
  y: number;
  w: number;
  h: number;
}

const CHALLENGE_MENU_CAPTURE = new URL(
  "../../../reference/captures/challenge-1-main-menu.png",
  import.meta.url,
).href;
const STORY_MENU_CAPTURE = new URL("../../../reference/captures/title-main-menu.png", import.meta.url).href;

/** Navigation order follows the physical object ring around the captured desk. */
const ENTRIES: readonly MenuEntry[] = [
  { mode: "story", label: "STORY", x: 64, y: 61, w: 18, h: 24 },
  { mode: "versus", label: "VERSUS", x: 34, y: 56, w: 18, h: 18 },
  { mode: "action", label: "ACTION", x: 15, y: 33, w: 17, h: 18 },
  { mode: "collection", label: "COLLECTION", x: 27, y: 34, w: 18, h: 15 },
  { mode: "trade", label: "TRADE", x: 42, y: 28, w: 18, h: 16 },
  { mode: "challenge", label: "CHALLENGE", x: 58, y: 35, w: 25, h: 26 },
  { mode: "edit-force", label: "EDIT FORCE", x: 80, y: 43, w: 21, h: 20 },
  { mode: "option", label: "OPTION", x: 81, y: 13, w: 18, h: 14 },
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
  const frame = el("div", { class: "gf-mainmenu-frame" });
  const desk = el("div", {
    class: "gf-mainmenu-desk",
    style: { backgroundImage: `url(${captureFor(selected, opts.deskImage)})` },
  });
  frame.appendChild(desk);

  const ring = el("div", { class: "gf-mainmenu-ring" });
  const cursor = el("div", { class: "gf-menu-cursor", attrs: { "aria-hidden": "true" } });
  const itemNodes = new Map<MainMenuMode, HTMLButtonElement>();

  ENTRIES.forEach((entry) => {
    const node = el(
      "button",
      {
        class: "gf-menu-item",
        style: {
          left: `${entry.x}%`,
          top: `${entry.y}%`,
          width: `${entry.w}%`,
          height: `${entry.h}%`,
        },
        attrs: { type: "button", "data-mode": entry.mode, "aria-label": entry.label },
        onClick: () => {
          if (selected === entry.mode) opts.onSelect(entry.mode);
          else setSelected(entry.mode);
        },
      },
    );
    itemNodes.set(entry.mode, node);
    ring.appendChild(node);
  });

  ring.appendChild(cursor);
  frame.appendChild(ring);
  root.appendChild(frame);

  function setSelected(mode: MainMenuMode): void {
    selected = mode;
    desk.style.backgroundImage = `url(${captureFor(mode, opts.deskImage)})`;
    const entry = ENTRIES.find((candidate) => candidate.mode === mode) ?? ENTRIES[0]!;
    cursor.style.left = `${entry.x}%`;
    cursor.style.top = `${entry.y}%`;
    cursor.style.width = `${entry.w}%`;
    cursor.style.height = `${entry.h}%`;
    cursor.setAttribute("data-mode", mode);
    for (const [m, node] of itemNodes) {
      node.classList.toggle("gf-selected", m === mode);
      node.setAttribute("aria-pressed", String(m === mode));
    }
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
  window.addEventListener("keydown", onKey);

  return {
    setSelected,
    getSelected: () => selected,
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}

function captureFor(mode: MainMenuMode, override: string | undefined): string {
  if (override) return override;
  return mode === "story" ? STORY_MENU_CAPTURE : CHALLENGE_MENU_CAPTURE;
}
