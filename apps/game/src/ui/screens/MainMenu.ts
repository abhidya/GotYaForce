/**
 * MainMenu - the mode hub, per reference `challenge-1-main-menu.png`.
 *
 * The real game renders this as a 3D desk diorama where each mode is a physical
 * object on the desk. `tl00_mdl.arc` and `optn00_mdl.arc` are exported as DAE
 * pieces, while the captured native frames remain the exact visual keyframes for
 * STORY and CHALLENGE. Ghidra shows the menu-mode byte dispatch and 10-frame
 * object tween; this component mirrors that UX with source-backed scene layers
 * plus captured frame fallbacks for the selected native states we have.
 */

import { ASSETS } from "../assets.js";
import { el } from "../dom.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

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
  nativeCapture?: string;
}

const CHALLENGE_MENU_CAPTURE = new URL(
  "../../../reference/captures/challenge-1-main-menu.png",
  import.meta.url,
).href;
const STORY_MENU_CAPTURE = new URL("../../../reference/captures/title-main-menu.png", import.meta.url).href;
const NATIVE_TWEEN_MS = 167; // 10 frames at 60 Hz, matching the decompiled object intro/update tween.

/** Navigation order follows the physical object ring around the captured desk. */
const ENTRIES: readonly MenuEntry[] = [
  { mode: "story", label: "STORY", x: 64, y: 61, w: 18, h: 24, nativeCapture: STORY_MENU_CAPTURE },
  { mode: "versus", label: "VERSUS", x: 34, y: 56, w: 18, h: 18 },
  { mode: "action", label: "ACTION", x: 15, y: 33, w: 17, h: 18 },
  { mode: "collection", label: "COLLECTION", x: 27, y: 34, w: 18, h: 15 },
  { mode: "trade", label: "TRADE", x: 42, y: 28, w: 18, h: 16 },
  { mode: "challenge", label: "CHALLENGE", x: 58, y: 35, w: 25, h: 26, nativeCapture: CHALLENGE_MENU_CAPTURE },
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
  let transitionTimer = 0;
  const teardown: Array<() => void> = [];

  const root = el("div", {
    class: "gf-screen gf-mainmenu",
    attrs: { role: "menu", "aria-label": "Main menu" },
    style: { "--gf-native-tween-ms": `${NATIVE_TWEEN_MS}ms` } as Partial<CSSStyleDeclaration>,
  });
  const frame = el("div", { class: "gf-mainmenu-frame" });

  const scene = createUiSceneHost("gf-ui-scene gf-mainmenu-scene gf-mainmenu-hub-scene");
  frame.appendChild(scene);
  teardown.push(
    mountUiSceneModels(scene, {
      sceneId: "tl00",
      fitSize: 540,
      camera: { fov: 30, position: [420, 260, 610], lookAt: [0, 30, 0] },
      rotation: [-0.22, -0.34, 0.03],
    }),
  );
  const optionScene = createUiSceneHost("gf-ui-scene gf-mainmenu-scene gf-mainmenu-option-scene");
  frame.appendChild(optionScene);
  teardown.push(
    mountUiSceneModels(optionScene, {
      sceneId: "optn00",
      fitSize: 440,
      camera: { fov: 29, position: [330, 250, 520], lookAt: [0, 22, 0] },
      rotation: [-0.16, -0.28, 0.02],
    }),
  );

  const desk = el("div", {
    class: "gf-mainmenu-desk",
    style: { backgroundImage: `url(${captureFor(selected, opts.deskImage)})` },
  });
  frame.appendChild(desk);

  const ring = el("div", { class: "gf-mainmenu-ring" });
  const cursor = el("div", { class: "gf-menu-cursor", attrs: { "aria-hidden": "true" } });
  const selectedProxy = el("div", { class: "gf-mainmenu-selected-proxy", attrs: { "aria-hidden": "true" } }, [
    el("span", { class: "gf-mainmenu-selected-label" }),
  ]);
  const optionTexture = el("img", {
    class: "gf-mainmenu-option-texture",
    attrs: { src: ASSETS.mainMenuOption, alt: "" },
  });
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
        attrs: { type: "button", "data-mode": entry.mode, "aria-label": entry.label, role: "menuitem" },
        onClick: () => {
          if (selected === entry.mode) opts.onSelect(entry.mode);
          else setSelected(entry.mode);
        },
      },
    );
    node.addEventListener("pointerenter", () => setSelected(entry.mode));
    itemNodes.set(entry.mode, node);
    ring.appendChild(node);
  });

  ring.appendChild(selectedProxy);
  ring.appendChild(cursor);
  ring.appendChild(optionTexture);
  frame.appendChild(ring);
  root.appendChild(frame);

  function setSelected(mode: MainMenuMode): void {
    if (selected !== mode) {
      root.dataset["transitioning"] = "true";
      window.clearTimeout(transitionTimer);
      transitionTimer = window.setTimeout(() => {
        delete root.dataset["transitioning"];
      }, NATIVE_TWEEN_MS);
    }
    selected = mode;
    desk.style.backgroundImage = `url(${captureFor(mode, opts.deskImage)})`;
    const entry = ENTRIES.find((candidate) => candidate.mode === mode) ?? ENTRIES[0]!;
    const hasNativeCapture = Boolean(entry.nativeCapture || opts.deskImage);
    root.dataset["mode"] = mode;
    root.dataset["menuScene"] = mode === "option" ? "option" : "hub";
    root.dataset["nativeCapture"] = String(hasNativeCapture);
    cursor.style.left = `${entry.x}%`;
    cursor.style.top = `${entry.y}%`;
    cursor.style.width = `${entry.w}%`;
    cursor.style.height = `${entry.h}%`;
    cursor.setAttribute("data-mode", mode);
    selectedProxy.style.left = `${entry.x}%`;
    selectedProxy.style.top = `${entry.y}%`;
    selectedProxy.style.width = `${entry.w}%`;
    selectedProxy.style.height = `${entry.h}%`;
    selectedProxy.querySelector(".gf-mainmenu-selected-label")!.textContent = entry.label;
    for (const [m, node] of itemNodes) {
      node.classList.toggle("gf-selected", m === mode);
      node.setAttribute("aria-pressed", String(m === mode));
    }
  }

  function onKey(ev: KeyboardEvent): void {
    const key = ev.key.toLowerCase();
    if (ev.key === "ArrowRight" || key === "d") {
      moveOnRing(1);
      ev.preventDefault();
    } else if (ev.key === "ArrowLeft" || key === "a") {
      moveOnRing(-1);
      ev.preventDefault();
    } else if (ev.key === "ArrowDown" || key === "s") {
      moveByDirection(0, 1);
      ev.preventDefault();
    } else if (ev.key === "ArrowUp" || key === "w") {
      moveByDirection(0, -1);
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key === " " || key === "j") {
      opts.onSelect(selected);
      ev.preventDefault();
    }
  }

  function moveOnRing(delta: -1 | 1): void {
    const order = ENTRIES.map((e) => e.mode);
    const idx = order.indexOf(selected);
    setSelected(order[(idx + delta + order.length) % order.length]!);
  }

  function moveByDirection(dx: -1 | 0 | 1, dy: -1 | 0 | 1): void {
    const current = ENTRIES.find((entry) => entry.mode === selected) ?? ENTRIES[0]!;
    const candidate = ENTRIES.filter((entry) => entry.mode !== current.mode)
      .map((entry) => {
        const vx = entry.x - current.x;
        const vy = entry.y - current.y;
        const distance = Math.hypot(vx, vy) || 1;
        const dot = (vx * dx + vy * dy) / distance;
        return { entry, score: dot * 100 - distance * 0.25 };
      })
      .filter((item) => item.score > 0)
      .sort((a, b) => b.score - a.score)[0]?.entry;
    if (candidate) setSelected(candidate.mode);
  }

  setSelected(selected);
  container.appendChild(root);
  window.addEventListener("keydown", onKey);

  return {
    setSelected,
    getSelected: () => selected,
    destroy: () => {
      window.clearTimeout(transitionTimer);
      window.removeEventListener("keydown", onKey);
      for (const fn of teardown) fn();
      root.remove();
    },
  };
}

function captureFor(mode: MainMenuMode, override: string | undefined): string {
  if (override) return override;
  return ENTRIES.find((entry) => entry.mode === mode)?.nativeCapture ?? CHALLENGE_MENU_CAPTURE;
}
