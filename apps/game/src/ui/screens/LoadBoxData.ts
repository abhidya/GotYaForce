/**
 * LoadBoxData — Challenge flow screen #4, per `challenge-4-load-box-data.png`.
 *
 * The original asks for Memory Card Slot A and lets START skip. The browser port
 * has local extracted roster data already loaded, so A/START advance to the same
 * next Challenge state while preserving the native UX step.
 */

import { ASSETS } from "../assets.js";
import { el, legendItem } from "../dom.js";
import { subscribeMenuInput, type MenuAction } from "../menuInput.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

export interface LoadBoxDataOptions {
  onConfirm: () => void;
  onBack?: () => void;
  onSkip?: () => void;
}

export interface LoadBoxDataHandle {
  destroy: () => void;
}

export function createLoadBoxData(
  container: HTMLElement,
  opts: LoadBoxDataOptions,
): LoadBoxDataHandle {
  const root = el("div", { class: "gf-screen gf-load-box" });
  root.appendChild(el("div", { class: "gf-grid-bg gf-bg-gold" }));
  root.appendChild(el("h1", { class: "gf-title gf-load-title", text: "LOAD BOX DATA" }));
  root.appendChild(el("div", { class: "gf-load-rule" }));
  root.appendChild(
    el("div", { class: "gf-load-copy" }, [
      el("img", {
        class: "gf-load-memory-icon",
        attrs: { src: ASSETS.memoryCardSlot, alt: "", "aria-hidden": "true" },
      }),
      el("div", { text: "Insert Memory Card into Slot A" }),
      el("div", {}, ["and press the ", el("span", { class: "gf-inline-a", text: "A" }), " Button."]),
    ]),
  );

  const box = createBoxHost();
  root.appendChild(box);

  const legend = el("div", { class: "gf-legend" }, [
    legendItem("start", "SKIP"),
    legendItem("b", "BACK"),
    legendItem("a", "CONFIRM"),
  ]);
  root.appendChild(legend);

  function confirm(): void {
    opts.onConfirm();
  }

  function onMenuAction(action: MenuAction): void {
    if (action === "confirm") {
      confirm();
    } else if (action === "start") {
      (opts.onSkip ?? opts.onConfirm)();
    } else if (action === "back") {
      opts.onBack?.();
    }
  }

  container.appendChild(root);
  const stopBoxRender = mountGotchaBoxModel(box);
  const unsubscribeMenuInput = subscribeMenuInput((event) => onMenuAction(event.action));
  return {
    destroy: () => {
      unsubscribeMenuInput();
      stopBoxRender();
      root.remove();
    },
  };
}

function createBoxHost(): HTMLDivElement {
  return createUiSceneHost("gf-box-model");
}

function mountGotchaBoxModel(host: HTMLElement): () => void {
  return mountUiSceneModels(host, { sceneId: "box00", fitSize: 360 });
}
