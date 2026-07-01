/**
 * SelectDifficulty — per reference `challenge-2-select-difficulty.png`.
 *
 * Three gears on colored oval pads = the GF-energy budget that becomes the force
 * LIMIT: NORMAL 1500 / TUFF 2000 / INSANE 2500. Blue gridded backdrop, gold
 * outlined "SELECT DIFFICULTY" title, B BACK / A CONFIRM legend. The selected pad
 * is ringed in black (matching the capture's dark selection ring).
 */

import { el, legendItem } from "../dom.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

export type Difficulty = "normal" | "tuff" | "insane";

interface DiffEntry {
  key: Difficulty;
  energy: number;
  name: string;
  gear: string; // gear color css
  pad: string; // oval pad color css
}

const ENTRIES: readonly DiffEntry[] = [
  { key: "normal", energy: 1500, name: "NORMAL", gear: "linear-gradient(#79d957,#2f9e2f)", pad: "linear-gradient(#3aa83a,#1f7a1f)" },
  { key: "tuff", energy: 2000, name: "TUFF", gear: "linear-gradient(#e6e9ee,#a9afba)", pad: "linear-gradient(#ff9a3c,#e06a18)" },
  { key: "insane", energy: 2500, name: "INSANE", gear: "linear-gradient(#ffd86b,#f3a800)", pad: "linear-gradient(#ff5a4f,#c41010)" },
];

export interface SelectDifficultyOptions {
  /** Fired on confirm with the chosen GF-energy budget (1500/2000/2500). */
  onSelect: (budget: number, difficulty: Difficulty) => void;
  /** Fired on B / back. */
  onBack?: () => void;
  initial?: Difficulty;
}

export interface SelectDifficultyHandle {
  getSelected: () => Difficulty;
  destroy: () => void;
}

export function createSelectDifficulty(
  container: HTMLElement,
  opts: SelectDifficultyOptions,
): SelectDifficultyHandle {
  let selected: Difficulty = opts.initial ?? "normal";

  const root = el("div", { class: "gf-screen" });
  root.appendChild(el("div", { class: "gf-grid-bg gf-bg-blue" }));
  const selectScene = createUiSceneHost("gf-ui-scene gf-vsel-real-scene gf-vsel-difficulty-scene");
  root.appendChild(selectScene);
  root.appendChild(el("h1", { class: "gf-title", text: "SELECT DIFFICULTY" }));

  const row = el("div", { class: "gf-row", style: { marginTop: "6%" } });
  const tiles = new Map<Difficulty, HTMLButtonElement>();

  for (const e of ENTRIES) {
    const tile = el(
      "button",
      {
        class: "gf-option",
        attrs: { type: "button", "data-diff": e.key, "aria-label": `${e.name} ${e.energy}` },
        onClick: () => {
          if (selected === e.key) opts.onSelect(e.energy, e.key);
          else select(e.key);
        },
      },
      [
        el("div", { class: "gf-pad", style: { background: e.pad } }, [
          el("div", { class: "gf-menu-gear", style: { background: e.gear, fontSize: "20px" }, text: "⚙" }),
          el("div", { class: "gf-energy-label", text: "GF ENERGY" }),
          el("div", { class: "gf-energy-num", text: String(e.energy) }),
        ]),
        el("div", { class: `gf-energy-name gf-name-${e.key}`, text: e.name }),
      ],
    );
    tiles.set(e.key, tile);
    row.appendChild(tile);
  }
  root.appendChild(row);

  const legend = el("div", { class: "gf-legend" }, [
    legendItem("b", "BACK"),
    legendItem("a", "CONFIRM"),
  ]);
  root.appendChild(legend);

  function select(key: Difficulty): void {
    selected = key;
    for (const [k, node] of tiles) node.classList.toggle("gf-selected", k === key);
  }

  function onKey(ev: KeyboardEvent): void {
    const order = ENTRIES.map((e) => e.key);
    const idx = order.indexOf(selected);
    if (ev.key === "ArrowRight") {
      select(order[Math.min(idx + 1, order.length - 1)]!);
      ev.preventDefault();
    } else if (ev.key === "ArrowLeft") {
      select(order[Math.max(idx - 1, 0)]!);
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      const e = ENTRIES.find((x) => x.key === selected)!;
      opts.onSelect(e.energy, e.key);
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      opts.onBack?.();
      ev.preventDefault();
    }
  }

  select(selected);
  container.appendChild(root);
  const stopScene = mountUiSceneModels(selectScene, {
    sceneId: "vsel00",
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
