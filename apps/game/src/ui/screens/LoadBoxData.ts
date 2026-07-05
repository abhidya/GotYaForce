/**
 * LoadBoxData — Challenge flow screen #4, per `challenge-4-load-box-data.png`.
 *
 * The original asks for Memory Card Slot A and lets START skip. The browser port
 * has local extracted roster data already loaded, so A/START advance to the same
 * next Challenge state while preserving the native UX step.
 *
 * The title/rules copy previously here was handwritten CSS gold text. The real
 * export has a baked text plate for exactly this screen: `vsel00_mdl` texture_004
 * ("LOAD BOX DATA" / "Insert Memory Card into Slot A" / "and press the (A) Button.")
 * is a shared multi-line label sheet used across several vsel/box screens (see
 * ASSETS.vsSelectLabels, already used by BattleIntro.ts), so it is shown here as
 * the real screen art instead of recreated copy. The real box00 DAE/GLB scene is
 * unchanged.
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
  root.appendChild(
    el("img", {
      class: "gf-load-label-sheet",
      attrs: { src: ASSETS.vsSelectLabels, alt: "Load Box Data — Insert Memory Card into Slot A and press the A Button." },
    }),
  );
  root.appendChild(
    el("img", {
      class: "gf-load-memory-icon",
      attrs: { src: ASSETS.memoryCardSlot, alt: "", "aria-hidden": "true" },
    }),
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
