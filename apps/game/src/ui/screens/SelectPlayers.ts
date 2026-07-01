/**
 * SelectPlayers — per reference `challenge-3-select-players.png`.
 *
 * Real game: FIGHT ALONE (1P) vs TEAM UP (2P co-op), person silhouettes in a
 * selection ring with blue label pills + GameCube controllers underneath, on a
 * green gridded backdrop, B BACK / A CONFIRM legend. Challenge mode is kept to
 * the original two choices for now: 1 => FIGHT ALONE, 2 => TEAM UP.
 */

import { el, legendItem } from "../dom.js";
import { mountChallengeMenuMotion, type ChallengeMenuMotionHandle } from "../challengeMenuMotion.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

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

function personSilhouette(label: string): HTMLElement {
  return el("div", { class: "gf-person" }, [
    el("span", { class: "gf-person-head" }),
    el("span", { class: "gf-person-body" }),
    el("span", { class: "gf-person-num", text: label }),
  ]);
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
  frame.appendChild(el("div", { class: "gf-grid-bg gf-bg-green" }));
  const selectScene = createUiSceneHost("gf-ui-scene gf-vsel-real-scene gf-vsel-players-scene");
  frame.appendChild(selectScene);
  frame.appendChild(el("h1", { class: "gf-title gf-vsel-title", text: "SELECT NUMBER OF PLAYERS" }));

  const row = el("div", { class: "gf-row gf-vsel-options" });
  const tiles = new Map<number, HTMLButtonElement>();
  const motionItems: Array<{ element: HTMLElement; delayFrames: number; fromX: number; fromY: number }> = [];

  for (let count = 1; count <= max; count++) {
    const people = el("div", { class: `gf-people gf-people-${count}` });
    for (let p = 1; p <= count; p++) people.appendChild(personSilhouette(String(p)));

    const label = count === 1 ? "FIGHT ALONE" : "TEAM UP";
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
      [
        el("div", { class: "gf-pad gf-player-pad" }, [people, el("div", { class: `gf-controller-row gf-controller-row-${count}` })]),
        el("div", { class: "gf-pill", text: label }),
      ],
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

  const centerArrow = el("div", { class: "gf-player-arrow gf-motion-object", attrs: { "aria-hidden": "true" } });
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

  function onKey(ev: KeyboardEvent): void {
    if (!canInteract()) {
      ev.preventDefault();
      return;
    }
    if (ev.key === "ArrowRight") {
      select(Math.min(selected + 1, max));
      ev.preventDefault();
    } else if (ev.key === "ArrowLeft") {
      select(Math.max(selected - 1, 1));
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      void chooseSelected();
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      void goBack();
      ev.preventDefault();
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
  window.addEventListener("keydown", onKey);

  return {
    getSelected: () => selected,
    destroy: () => {
      motion?.destroy();
      stopScene();
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}
