/**
 * MainMenu — the mode hub, per reference `title-main-menu.png`.
 *
 * APPROXIMATION (the one documented deviation): the real game renders this as a
 * 3D desk diorama (a kid's room) where each mode is a physical object ringed by a
 * spinning gear cursor. We reproduce the *selection model* faithfully — modes are
 * laid out as gear-mounted labels in a ring, the selected one enlarges front-center
 * with a spinning red-gear cursor, the game's yellow-outlined font/colors and the
 * "GOTCHA FORCE" logo plate are matched — but as a flat re-skin rather than a live
 * 3D scene. An optional `deskImage` lets the integrator drop the real desk render
 * behind it. This is the only screen that is not pixel-faithful by design.
 *
 * Modes match the labels seen on the desk: STORY, VERSUS, CHALLENGE, EDIT FORCE,
 * COLLECTION, TRADE, OPTION.
 */

import { el } from "../dom.js";

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
  /** decorative glyph standing in for the desk object */
  glyph: string;
}

/** Ring order roughly matches the desk layout in the reference. */
const ENTRIES: readonly MenuEntry[] = [
  { mode: "story", label: "STORY", glyph: "📖" },
  { mode: "challenge", label: "CHALLENGE", glyph: "⏰" },
  { mode: "edit-force", label: "EDIT FORCE", glyph: "⚙️" },
  { mode: "option", label: "OPTION", glyph: "🎮" },
  { mode: "trade", label: "TRADE", glyph: "🔁" },
  { mode: "collection", label: "COLLECTION", glyph: "🗂️" },
  { mode: "versus", label: "VERSUS", glyph: "⚔️" },
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
        el("span", { class: "gf-menu-gear", text: entry.glyph }),
        el("span", { class: "gf-menu-label", text: entry.label }),
      ],
    );
    itemNodes.set(entry.mode, node);
    ring.appendChild(node);
  });

  root.appendChild(ring);
  root.appendChild(el("div", { class: "gf-mainmenu-logo", text: "GOTCHA FORCE" }));
  root.appendChild(
    el("div", { class: "gf-mainmenu-approx", text: "flat re-skin of the 3D desk menu" }),
  );

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
