/**
 * Gets — the post-Results Borg GET / Gotcha-Box drop presentation.
 *
 * DERIVED/TUNED (research/decomp/items-evidence-inventory-2026-07-05.md §2e): the real DOL
 * post-battle GETS screen (FUN_80180598) rolls one drop at a time and runs a full box-open
 * cinematic per drop, with debug strings "UNIT GET !! : %04X %d" / "PARTS GET !! : %04X %d
 * %d" identifying the presentation's two drop kinds. That full box UI (gets00..06_mdl.arc
 * cinematics, box open animation) is future work — this is a minimal, deliberately simple
 * recreation (TUNED layout): a single static list of every drop rolled this battle, reusing
 * the getStrip texture (`ASSETS.getStrip`, gets00_mdl) as a backdrop and the real ascii.tpl
 * bitmap font (bitmapText, same as PauseMenu/Results) for the "UNIT GET"/"PARTS GET" rows.
 *
 * Never blocks the flow: it is entirely skippable via the shared menu-input bus's "confirm"
 * action (same bus as every other screen — subscribeMenuInput), and the caller decides what
 * "advance" means (next battle / menu), matching Results' onAdvance convention.
 */

import { ASSETS } from "../assets.js";
import { bitmapText, setBitmapText } from "../bitmapText.js";
import { el } from "../dom.js";
import { subscribeMenuInput, type MenuAction } from "../menuInput.js";

export interface GetsRow {
  /** Display name (borgs.json name), e.g. "SHURIKEN NINJA". */
  name: string;
  kind: "unit" | "parts";
  /** 1-based part index for a parts drop (unused for a unit drop). */
  partIndex?: number;
  /** Total part count (N) for a parts drop. */
  partsCount?: number;
}

export interface GetsOptions {
  /** Fired on confirm/start/back — the screen never blocks the flow either way. */
  onAdvance?: () => void;
}

export interface GetsHandle {
  render: (rows: readonly GetsRow[]) => void;
  destroy: () => void;
}

function rowLabel(row: GetsRow): string {
  if (row.kind === "unit") return `UNIT GET  ${row.name}`;
  return `PARTS GET  ${row.name} (${row.partIndex ?? 1}/${row.partsCount ?? 1})`;
}

export function createGets(container: HTMLElement, opts: GetsOptions = {}): GetsHandle {
  const root = el("div", { class: "gf-screen gf-gets" });

  const backdrop = el("img", {
    class: "gf-gets-backdrop",
    attrs: { src: ASSETS.getStrip, alt: "", "aria-hidden": "true" },
  });
  root.appendChild(backdrop);

  const title = bitmapText("gf-gets-title-text");
  setBitmapText(title, "GET!");
  root.appendChild(el("div", { class: "gf-gets-title" }, [title]));

  const rowsHost = el("div", { class: "gf-gets-rows" });
  root.appendChild(rowsHost);

  const prompt = el("div", { class: "gf-gets-prompt", text: "PRESS A TO CONTINUE" });
  root.appendChild(prompt);

  function render(rows: readonly GetsRow[]): void {
    rowsHost.replaceChildren(
      ...rows.map((row) => {
        const label = bitmapText("gf-gets-row-text");
        setBitmapText(label, rowLabel(row));
        return el("div", { class: `gf-gets-row gf-gets-row-${row.kind}` }, [label]);
      }),
    );
  }

  function onMenuAction(action: MenuAction): void {
    if (action === "confirm" || action === "start" || action === "back") {
      opts.onAdvance?.();
    }
  }

  container.appendChild(root);
  const unsubscribeMenuInput = subscribeMenuInput((event) => onMenuAction(event.action));

  return {
    render,
    destroy: () => {
      unsubscribeMenuInput();
      root.remove();
    },
  };
}
