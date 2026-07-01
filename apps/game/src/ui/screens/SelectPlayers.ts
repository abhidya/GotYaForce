/**
 * SelectPlayers — per reference `challenge-3-select-players.png`.
 *
 * Real game: FIGHT ALONE (1P) vs TEAM UP (2P co-op), person silhouettes in a
 * selection ring with blue label pills + GameCube controllers underneath, on a
 * green gridded backdrop, B BACK / A CONFIRM legend. Our online build extends the
 * count to 1..4 (`maxPlayers`): 1 => FIGHT ALONE, 2+ => TEAM UP with that many
 * silhouettes. Each selectable count is its own option so 3P/4P are reachable.
 */

import { el, legendItem } from "../dom.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

export interface SelectPlayersOptions {
  /** Fired on confirm with the chosen player count (1..maxPlayers). */
  onSelect: (playerCount: number) => void;
  onBack?: () => void;
  /** Highest selectable count. Original game = 2; our online build = 4. */
  maxPlayers?: number;
  initial?: number;
}

export interface SelectPlayersHandle {
  getSelected: () => number;
  destroy: () => void;
}

function personSilhouette(label: string): HTMLElement {
  return el("div", { class: "gf-person" }, [
    el("div", {
      style: {
        width: "46px",
        height: "62px",
        margin: "0 auto",
        borderRadius: "22px 22px 8px 8px",
        background: "rgba(255,255,255,0.92)",
        display: "grid",
        placeItems: "center",
        color: "#2a2150",
        fontSize: "26px",
        position: "relative",
      },
      text: label,
    }),
  ]);
}

export function createSelectPlayers(
  container: HTMLElement,
  opts: SelectPlayersOptions,
): SelectPlayersHandle {
  const max = Math.max(1, Math.min(opts.maxPlayers ?? 2, 4));
  let selected = Math.min(Math.max(opts.initial ?? 1, 1), max);

  const root = el("div", { class: "gf-screen" });
  root.appendChild(el("div", { class: "gf-grid-bg gf-bg-green" }));
  const selectScene = createUiSceneHost("gf-ui-scene gf-vsel-real-scene gf-vsel-players-scene");
  root.appendChild(selectScene);
  root.appendChild(el("h1", { class: "gf-title", text: "SELECT NUMBER OF PLAYERS" }));

  const row = el("div", { class: "gf-row", style: { marginTop: "5%" } });
  const tiles = new Map<number, HTMLButtonElement>();

  for (let count = 1; count <= max; count++) {
    const people = el("div", { style: { display: "flex", gap: "6px", justifyContent: "center" } });
    for (let p = 1; p <= count; p++) people.appendChild(personSilhouette(String(p)));

    const label = count === 1 ? "FIGHT ALONE" : count === 2 ? "TEAM UP" : `TEAM UP ${count}P`;
    const tile = el(
      "button",
      {
        class: "gf-option",
        attrs: { type: "button", "data-count": String(count), "aria-label": `${count} player ${label}` },
        onClick: () => {
          if (selected === count) opts.onSelect(count);
          else select(count);
        },
      },
      [
        el("div", { class: "gf-pad", style: { width: "auto", height: "auto", padding: "14px 22px" } }, [people]),
        el("div", { class: "gf-pill", text: label }),
      ],
    );
    tiles.set(count, tile);
    row.appendChild(tile);
  }
  root.appendChild(row);

  root.appendChild(
    el("div", { class: "gf-legend" }, [legendItem("b", "BACK"), legendItem("a", "CONFIRM")]),
  );

  function select(count: number): void {
    selected = count;
    for (const [c, node] of tiles) node.classList.toggle("gf-selected", c === count);
  }

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "ArrowRight") {
      select(Math.min(selected + 1, max));
      ev.preventDefault();
    } else if (ev.key === "ArrowLeft") {
      select(Math.max(selected - 1, 1));
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      opts.onSelect(selected);
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      opts.onBack?.();
      ev.preventDefault();
    }
  }

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
      stopScene();
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}
