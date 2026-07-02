/**
 * SelectDifficulty — per reference `challenge-2-select-difficulty.png`.
 *
 * Three gears on colored oval pads = the GF-energy budget that becomes the force
 * LIMIT: NORMAL 1500 / TUFF 2000 / INSANE 2500. Blue gridded backdrop, gold
 * outlined "SELECT DIFFICULTY" title, B BACK / A CONFIRM legend. The selected pad
 * is ringed in black (matching the capture's dark selection ring).
 */

import { el, legendItem } from "../dom.js";
import { mountChallengeMenuMotion, type ChallengeMenuMotionHandle } from "../challengeMenuMotion.js";
import { UI_SCENE_LAYOUTS } from "../layout.generated.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

const DIFFICULTY_LAYOUT = UI_SCENE_LAYOUTS.vsel00.semantics.difficulty;

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
  let motion: ChallengeMenuMotionHandle | null = null;
  let choosing = false;

  const root = el("div", {
    class: "gf-screen gf-vsel-screen gf-select-difficulty",
    style: difficultyLayoutVars(),
  });
  const frame = el("div", { class: "gf-vsel-frame" });
  root.appendChild(frame);
  frame.appendChild(el("div", { class: "gf-grid-bg gf-bg-blue" }));
  const selectScene = createUiSceneHost("gf-ui-scene gf-vsel-real-scene gf-vsel-difficulty-scene");
  frame.appendChild(selectScene);
  frame.appendChild(el("h1", { class: "gf-title gf-vsel-title", text: "SELECT DIFFICULTY" }));

  const row = el("div", { class: "gf-row gf-vsel-options" });
  const tiles = new Map<Difficulty, HTMLButtonElement>();
  const motionItems: Array<{ element: HTMLElement; delayFrames: number; fromX: number; fromY: number }> = [];

  for (const [index, e] of ENTRIES.entries()) {
    const tile = el(
      "button",
      {
        class: `gf-option gf-diff-option gf-diff-${e.key}`,
        attrs: { type: "button", "data-diff": e.key, "aria-label": `${e.name} ${e.energy}` },
        onClick: () => {
          if (!canInteract()) return;
          if (selected === e.key) void chooseSelected();
          else select(e.key);
        },
      },
      [
        el("div", { class: "gf-pad", style: { background: e.pad } }, [
          el("div", { class: "gf-menu-gear", style: { background: e.gear } }),
          el("div", { class: "gf-energy-label", text: "GF ENERGY" }),
          el("div", { class: "gf-energy-num", text: String(e.energy) }),
        ]),
        el("div", { class: `gf-energy-name gf-name-${e.key}`, text: e.name }),
      ],
    );
    tiles.set(e.key, tile);
    motionItems.push({
      element: tile,
      delayFrames: index * 2,
      fromX: e.key === "normal" ? -56 : e.key === "insane" ? 56 : 0,
      fromY: 74,
    });
    row.appendChild(tile);
  }
  frame.appendChild(row);

  const legend = el("div", { class: "gf-legend" }, [
    legendItem("b", "BACK"),
    legendItem("a", "CONFIRM"),
  ]);
  frame.appendChild(legend);

  function select(key: Difficulty): void {
    selected = key;
    let selectedNode: HTMLElement | null = null;
    for (const [k, node] of tiles) {
      const isSelected = k === key;
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
    const e = ENTRIES.find((x) => x.key === selected)!;
    await motion?.finish();
    opts.onSelect(e.energy, e.key);
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
    const order = ENTRIES.map((e) => e.key);
    const idx = order.indexOf(selected);
    if (ev.key === "ArrowRight") {
      select(order[Math.min(idx + 1, order.length - 1)]!);
      ev.preventDefault();
    } else if (ev.key === "ArrowLeft") {
      select(order[Math.max(idx - 1, 0)]!);
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
    sceneId: "vsel00",
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

/**
 * Scene-derived positioning for the difficulty option row, following the
 * SelectForce CSS-var pattern. The vsel00 export only yields the shared option
 * stage (see the anchor's caveat: per-difficulty X offsets are runtime JOBJ
 * placement and are not in the geometry), so only the row's center X/Y is
 * derived; the pad spread stays hand-tuned in CSS, and CSS fallbacks cover a
 * missing anchor.
 */
function difficultyLayoutVars(): Partial<CSSStyleDeclaration> {
  const stage = DIFFICULTY_LAYOUT?.optionStage;
  if (!stage) return {};
  return {
    "--gf-diff-row-top": `${stage.centerY}%`,
    "--gf-diff-center-x": `${stage.centerX}%`,
  } as Partial<CSSStyleDeclaration>;
}
