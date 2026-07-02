/**
 * PauseMenu — the in-battle pause overlay, per `challenge-12-pause-menu.png`.
 *
 * A purple-bordered grey rounded box centered over the (still-visible) battle:
 * "1P PAUSE" title bar, then RESUME / QUIT. The highlighted item shows the green
 * A-button bullet and a filled blue pill. The "1P" reflects which player paused
 * (Challenge focus is 1P/2P; `playerLabel` remains for the TEAM UP branch).
 */

import { bitmapText, setBitmapText } from "../bitmapText.js";
import { el, faceButton } from "../dom.js";

export type PauseAction = "resume" | "quit";

export interface PauseMenuOptions {
  onResume: () => void;
  onQuit: () => void;
  /** Player label for the title, e.g. "1P" (default), "2P". */
  playerLabel?: string;
  initial?: PauseAction;
}

export interface PauseMenuHandle {
  getSelected: () => PauseAction;
  destroy: () => void;
}

export function createPauseMenu(container: HTMLElement, opts: PauseMenuOptions): PauseMenuHandle {
  let selected: PauseAction = opts.initial ?? "resume";
  const order: PauseAction[] = ["resume", "quit"];

  const overlay = el("div", { class: "gf-pause-overlay" });
  const box = el("div", { class: "gf-pause-box" });
  const titleLabel = `${opts.playerLabel ?? "1P"} PAUSE`;
  const titleText = bitmapText("gf-pause-title-text");
  setBitmapText(titleText, titleLabel);
  box.appendChild(el("div", { class: "gf-pause-title", attrs: { "aria-label": titleLabel } }, [titleText]));

  const items = el("div", { class: "gf-pause-items" });
  const nodes = new Map<PauseAction, HTMLButtonElement>();
  for (const action of order) {
    const label = action === "resume" ? "RESUME" : "QUIT";
    const labelText = bitmapText("gf-pause-item-text");
    setBitmapText(labelText, label);
    const bullet = el("span", { class: "gf-pause-bullet" });
    bullet.appendChild(faceButton("a"));
    const node = el(
      "button",
      {
        class: "gf-pause-item",
        attrs: { type: "button", "data-action": action, "aria-label": label },
        onClick: () => {
          select(action);
          confirm();
        },
      },
      [bullet, labelText],
    );
    nodes.set(action, node);
    items.appendChild(node);
  }
  box.appendChild(items);
  overlay.appendChild(box);

  function select(action: PauseAction): void {
    selected = action;
    for (const [a, node] of nodes) {
      const on = a === action;
      node.classList.toggle("gf-selected", on);
      const bullet = node.querySelector(".gf-pause-bullet") as HTMLElement | null;
      if (bullet) bullet.style.visibility = on ? "visible" : "hidden";
    }
  }

  function confirm(): void {
    if (selected === "resume") opts.onResume();
    else opts.onQuit();
  }

  function onKey(ev: KeyboardEvent): void {
    const idx = order.indexOf(selected);
    if (ev.key === "ArrowDown" || ev.key === "ArrowRight") {
      select(order[(idx + 1) % order.length]!);
      ev.preventDefault();
    } else if (ev.key === "ArrowUp" || ev.key === "ArrowLeft") {
      select(order[(idx - 1 + order.length) % order.length]!);
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      confirm();
      ev.preventDefault();
    } else if (ev.key === "Escape") {
      opts.onResume();
      ev.preventDefault();
    }
  }

  select(selected);
  container.appendChild(overlay);
  window.addEventListener("keydown", onKey);

  return {
    getSelected: () => selected,
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      overlay.remove();
    },
  };
}
