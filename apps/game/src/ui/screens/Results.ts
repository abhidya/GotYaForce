/**
 * Results — end-of-battle scoring, per `challenge-11-WIN-results.png` /
 * `challenge-10-LOSE-results.png`.
 *
 * Blue rounded pill rows over the borg model, label on the left, value on the
 * right. Canonical Challenge rows (in capture order):
 *   ATTACK, HIT RATIO, DODGE RATIO, ENEMY BORGS DEFEATED, TOTAL COST,
 *   PLAYER BORGS DEFEATED, TOTAL COST, ALLY BORGS DEFEATED, GRAND TOTAL.
 * A big gold "WIN" (or grey "LOSE") verdict overlays the rows. GRAND TOTAL is
 * positive on a win (e.g. 7000) and negative on a loss (e.g. -300). START prompt
 * bottom-right advances (next battle on win, title on lose — the caller decides).
 *
 * Surface: the exported rpot20 (win) / rpot23 (lose) podium scenes are the
 * PRIMARY surface (mounted at full opacity, not a faint backdrop). The row
 * LABELS ("ATTACK", "HIT RATIO", ...) are always the same fixed strings on
 * every Challenge result, so — same convention as SelectDifficulty's fixed
 * pad labels — they render as ONE captureCropImg crop of the real baked pill
 * stack (`reference/captures/challenge-11-WIN-results.png`), not a
 * CSS/bitmap-font recreation. Only the per-battle VALUES (which vary every
 * fight) render in the real exported ascii.tpl bitmap font.
 */

import { bitmapText, setBitmapText } from "../bitmapText.js";
import { captureCropImg } from "../captureCrop.js";
import { el } from "../dom.js";
import type { MenuAction, MenuInputTarget } from "../menuInput.js";
import { UI_SCENE_LAYOUTS } from "../layout.generated.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

const CAPTURE = new URL("../../../reference/captures/challenge-11-WIN-results.png", import.meta.url).href;
/** Native capture is 2560x1966; crop box below is in that pixel space. */
const CAPTURE_W = 2560;
/**
 * All 9 row LABEL pills stacked as one real crop (fixed text, identical on
 * every result — win or lose share the same label set/order). Values are
 * cropped OUT (this box ends where the borg's foot/number column begins) so
 * bitmapText numbers render cleanly to the right of each pill.
 */
const LABELS_CROP = { x: 375, y: 275, w: 785, h: 1355 };

export interface ResultStats {
  attack: number;
  /** percentages as numbers, e.g. 54.96 -> shown "54.96%" */
  hitRatio: number;
  dodgeRatio: number;
  enemyBorgsDefeated: number;
  /** TOTAL COST tied to the enemy-defeated block (capture shows two TOTAL COST rows). */
  enemyTotalCost: number;
  playerBorgsDefeated: number;
  /** TOTAL COST tied to the player block. */
  playerTotalCost: number;
  allyBorgsDefeated: number;
  grandTotal: number;
}

export interface ResultsOptions {
  /** Fired on START / confirm to advance. */
  onAdvance?: () => void;
}

export interface ResultsHandle extends MenuInputTarget {
  /** Render or re-render the panel for a win/lose with the given stats. */
  render: (result: "win" | "lose", stats: ResultStats) => void;
  destroy: () => void;
}

interface RowDef {
  value: string;
  grand?: boolean;
  neg?: boolean;
}

const RESULT_SCENES = {
  win: {
    sceneId: "rpot20",
    modelPath: "/ui/scenes/rpot20/model_00.glb",
    layout: UI_SCENE_LAYOUTS.rpot20.semantics.results,
  },
  lose: {
    sceneId: "rpot23",
    modelPath: "/ui/scenes/rpot23/model_00.glb",
    layout: UI_SCENE_LAYOUTS.rpot23.semantics.results,
  },
} as const;

function pct(n: number): string {
  return `${n.toFixed(2)}%`;
}

export function createResults(container: HTMLElement, opts: ResultsOptions = {}): ResultsHandle {
  const root = el("div", { class: "gf-screen gf-results" });
  let mountedSceneId: string | null = null;
  let stopScene: (() => void) | null = null;

  const scene = createUiSceneHost("gf-ui-scene gf-results-real-scene");
  root.appendChild(scene);

  const labelsCrop = el(
    "div",
    { class: "gf-results-labels-crop", attrs: { "aria-hidden": "true" } },
    [captureCropImg(CAPTURE, CAPTURE_W, LABELS_CROP)],
  );
  root.appendChild(labelsCrop);

  const rows = el("div", { class: "gf-results-rows" });
  root.appendChild(rows);

  const verdictText = bitmapText("gf-results-verdict-text");
  const verdict = el("div", { class: "gf-results-verdict" }, [verdictText]);
  root.appendChild(verdict);

  const startLabel = bitmapText("gf-results-start-text");
  setBitmapText(startLabel, "START", { bold: true, scale: 1 });
  const start = el("div", { class: "gf-results-start" }, [startLabel]);
  root.appendChild(start);

  function onMenuAction(action: MenuAction): void {
    if (action === "confirm" || action === "start") {
      opts.onAdvance?.();
    }
  }

  function render(result: "win" | "lose", s: ResultStats): void {
    mountResultScene(result);

    const defs: RowDef[] = [
      { value: String(s.attack) },
      { value: pct(s.hitRatio) },
      { value: pct(s.dodgeRatio) },
      { value: String(s.enemyBorgsDefeated) },
      { value: String(s.enemyTotalCost) },
      { value: String(s.playerBorgsDefeated) },
      { value: String(s.playerTotalCost) },
      { value: String(s.allyBorgsDefeated) },
      { value: String(s.grandTotal), grand: true, neg: s.grandTotal < 0 },
    ];

    rows.replaceChildren(
      ...defs.map((d) => {
        const valText = bitmapText("gf-result-val-text");
        if (d.neg) setBitmapText(valText, d.value, { bold: true, scale: d.grand ? 4 : 3, tint: "#ff5a4f" });
        else setBitmapText(valText, d.value, { bold: true, scale: d.grand ? 4 : 3 });
        return el("div", { class: `gf-result-row${d.grand ? " gf-result-grand" : ""}` }, [
          el("div", { class: "gf-result-label-spacer" }),
          el("div", { class: "gf-result-val" }, [valText]),
        ]);
      }),
    );

    setBitmapText(verdictText, result === "win" ? "WIN" : "LOSE", {
      bold: true,
      scale: 4,
      tint: result === "win" ? "#ffd21e" : "#c8ccd6",
    });
    verdict.className = `gf-results-verdict gf-verdict-${result}`;
  }

  function mountResultScene(result: "win" | "lose"): void {
    const next = RESULT_SCENES[result];
    if (mountedSceneId === next.sceneId) return;
    stopScene?.();
    mountedSceneId = next.sceneId;
    scene.dataset["sourceModel"] = next.modelPath;
    applyResultLayoutVars(next.layout);
    stopScene = mountUiSceneModels(scene, {
      sceneId: next.sceneId,
      fitSize: result === "win" ? 900 : 840,
      camera: { fov: 31, position: [0, 110, 760], lookAt: [0, 20, -180] },
      rotation: [-0.08, 0, 0],
    });
  }

  /**
   * Scene-derived positioning for the score rows, following the SelectForce
   * CSS-var pattern. The rpot20/rpot23 anchors are normalized against the
   * scenes' 640x480 screen quad; only the rows' horizontal extent is trusted
   * (the export is a rest pose - see the anchor caveat), vertical placement
   * stays hand-tuned in CSS. CSS fallbacks cover a missing anchor.
   */
  function applyResultLayoutVars(layout: (typeof RESULT_SCENES)[keyof typeof RESULT_SCENES]["layout"]): void {
    const rowsLayout = layout?.rows;
    if (!rowsLayout) {
      root.style.removeProperty("--gf-results-rows-left");
      root.style.removeProperty("--gf-results-rows-width");
      return;
    }
    root.style.setProperty("--gf-results-rows-left", `${rowsLayout.left}%`);
    root.style.setProperty("--gf-results-rows-width", `${rowsLayout.width}%`);
  }

  container.appendChild(root);
  return {
    render,
    handleMenuInput: (event) => onMenuAction(event.action),
    destroy: () => {
      stopScene?.();
      root.remove();
    },
  };
}
