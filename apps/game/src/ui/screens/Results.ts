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
 */

import { ASSETS } from "../assets.js";
import { el } from "../dom.js";

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

export interface ResultsHandle {
  /** Render or re-render the panel for a win/lose with the given stats. */
  render: (result: "win" | "lose", stats: ResultStats) => void;
  destroy: () => void;
}

interface RowDef {
  label: string;
  value: string;
  sub?: boolean;
  grand?: boolean;
  neg?: boolean;
}

function pct(n: number): string {
  return `${n.toFixed(2)}%`;
}

export function createResults(container: HTMLElement, opts: ResultsOptions = {}): ResultsHandle {
  const root = el("div", { class: "gf-screen gf-results" });
  const backdrop = el("img", {
    class: "gf-results-backdrop",
    attrs: { src: ASSETS.resultsWin, alt: "", "aria-hidden": "true" },
  }) as HTMLImageElement;
  root.appendChild(backdrop);

  const rows = el("div", { class: "gf-results-rows" });
  root.appendChild(rows);

  const verdict = el("div", { class: "gf-results-verdict" });
  root.appendChild(verdict);

  const start = el("img", {
    class: "gf-results-start",
    attrs: { src: ASSETS.resultsStartPrompt, alt: "START" },
  });
  root.appendChild(start);

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "Enter" || ev.key === " " || ev.key.toLowerCase() === "a") {
      opts.onAdvance?.();
      ev.preventDefault();
    }
  }

  function render(result: "win" | "lose", s: ResultStats): void {
    backdrop.src = result === "win" ? ASSETS.resultsWin : ASSETS.resultsLose;

    const defs: RowDef[] = [
      { label: "ATTACK", value: String(s.attack) },
      { label: "HIT RATIO", value: pct(s.hitRatio) },
      { label: "DODGE RATIO", value: pct(s.dodgeRatio) },
      { label: "ENEMY BORGS DEFEATED", value: String(s.enemyBorgsDefeated) },
      { label: "TOTAL COST", value: String(s.enemyTotalCost), sub: true },
      { label: "PLAYER BORGS DEFEATED", value: String(s.playerBorgsDefeated) },
      { label: "TOTAL COST", value: String(s.playerTotalCost), sub: true },
      { label: "ALLY BORGS DEFEATED", value: String(s.allyBorgsDefeated) },
      { label: "GRAND TOTAL", value: String(s.grandTotal), grand: true, neg: s.grandTotal < 0 },
    ];

    rows.replaceChildren(
      ...defs.map((d) =>
        el("div", { class: `gf-result-row${d.grand ? " gf-result-grand" : ""}` }, [
          el("div", { class: `gf-result-pill${d.sub ? " gf-result-sub" : ""}` }, [el("span", { text: d.label })]),
          el("div", { class: `gf-result-val${d.neg ? " gf-neg" : ""}`, text: d.value }),
        ]),
      ),
    );

    verdict.className = `gf-results-verdict gf-verdict-${result}`;
    if (result === "lose") {
      verdict.replaceChildren(
        el("img", { class: "gf-results-gameover", attrs: { src: ASSETS.resultsGameOver, alt: "GAME OVER" } }),
      );
    } else {
      verdict.textContent = "WIN";
    }
  }

  container.appendChild(root);
  window.addEventListener("keydown", onKey);

  return {
    render,
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}
