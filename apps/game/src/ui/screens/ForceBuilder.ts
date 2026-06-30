/**
 * ForceBuilder — the Edit Force builder, per `challenge-6-edit-force.png`.
 *
 * Layout matches the capture:
 *  - top-left  : "EDIT" tab with L/R arrows
 *  - top-right : active-borg name banner (real `bn<code>` plate) + mini icon
 *  - left      : a scrollable borg grid built from the real `mn<code>` icons
 *  - right     : a 30-slot force ring of yellow hexagons (slot 1..30)
 *  - panel     : TOTAL COST / LIMIT / REMAIN  (TOTAL must stay <= LIMIT)
 *  - legend    : CHANGE FORCE / QUIT / TURN / MENU / HOLD / SPEC
 *
 * Budget rule (confirmed): LIMIT = chosen difficulty energy; TOTAL COST = sum of
 * force borg energy; REMAIN = LIMIT - TOTAL; a borg can't be added if it would
 * push TOTAL over LIMIT or the force already holds 30. Click a grid cell to
 * add/remove; click a filled slot to remove it.
 */

import { el, legendItem, clear } from "../dom.js";
import { borgBannerPath, borgMiniPath } from "../assets.js";

/** Minimal borg shape the builder needs (subset of borgs.json). */
export interface ForceBorg {
  id: string;
  name: string;
  energy: number;
  /** optional: mark a freshly-collected borg with the "NEW" badge */
  isNew?: boolean;
}

export interface ForceBuilderOptions {
  /** Full catalog to pick from (already filtered/sorted by the caller). */
  catalog: readonly ForceBorg[];
  /** Energy budget = the LIMIT (from SelectDifficulty). */
  limit: number;
  /** Initial force (borg ids). Defaults to empty. */
  initialForce?: readonly string[];
  /** Max slots in the ring. Defaults to 30 (the real game's count). */
  maxSlots?: number;
  /** Fired when the force changes (add/remove). */
  onChange?: (force: string[], totalCost: number, remain: number) => void;
  /** Fired on confirm (A / HOLD). Only fires when TOTAL <= LIMIT. */
  onConfirm: (force: string[]) => void;
  /** Fired on quit/back (START / B). */
  onQuit?: () => void;
}

export interface ForceBuilderHandle {
  getForce: () => string[];
  totalCost: () => number;
  destroy: () => void;
}

export function createForceBuilder(
  container: HTMLElement,
  opts: ForceBuilderOptions,
): ForceBuilderHandle {
  const maxSlots = opts.maxSlots ?? 30;
  const byId = new Map(opts.catalog.map((b) => [b.id, b] as const));
  const force: string[] = [...(opts.initialForce ?? [])].filter((id) => byId.has(id)).slice(0, maxSlots);

  const root = el("div", { class: "gf-screen", style: { background: "#0e2138" } });
  const layout = el("div", { class: "gf-force" });

  // ---- left column: EDIT tab + grid ----
  const left = el("div", { class: "gf-force-left" });
  left.appendChild(
    el("div", { class: "gf-force-edit-tab" }, [
      el("span", { text: "◄" }),
      el("span", { text: "EDIT" }),
      el("span", { text: "►" }),
    ]),
  );
  const grid = el("div", { class: "gf-force-grid" });
  left.appendChild(grid);

  // ---- right column: banner + ring + cost panel ----
  const right = el("div", { class: "gf-force-right" });
  const banner = el("div", { class: "gf-force-banner" });
  const bannerImg = el("img", { attrs: { alt: "", "aria-hidden": "true" } }) as HTMLImageElement;
  bannerImg.addEventListener("error", () => (bannerImg.style.visibility = "hidden"));
  const bannerName = el("span", { class: "gf-force-banner-name", text: "FORCE" });
  banner.append(bannerImg, bannerName);
  right.appendChild(banner);

  const ring = el("div", { class: "gf-force-ring" });
  right.appendChild(ring);

  const panel = el("div", { class: "gf-cost-panel" });
  const totalVal = el("span", { class: "gf-cost-val", text: "0" });
  const limitVal = el("span", { class: "gf-cost-val", text: String(opts.limit) });
  const remainVal = el("span", { class: "gf-cost-val gf-remain", text: String(opts.limit) });
  panel.append(
    el("div", { class: "gf-cost-line gf-cost-total" }, [el("span", { text: "TOTAL COST" }), totalVal]),
    el("div", { class: "gf-cost-line" }, [el("span", { text: "LIMIT" }), limitVal]),
    el("div", { class: "gf-cost-line" }, [el("span", { text: "REMAIN" }), remainVal]),
  );
  ring.appendChild(panel);

  layout.append(left, right);
  root.appendChild(layout);

  // ---- bottom legend ----
  root.appendChild(
    el("div", { class: "gf-legend" }, [
      el("span", { class: "gf-legend-item" }, [el("span", { class: "gf-btn gf-btn-x", text: "+" }), el("span", { text: "CHANGE FORCE" })]),
      legendItem("start", "QUIT"),
      legendItem("y", "MENU"),
      legendItem("a", "HOLD"),
      legendItem("x", "SPEC"),
    ]),
  );

  // ---------- logic ----------
  function totalCost(): number {
    return force.reduce((sum, id) => sum + (byId.get(id)?.energy ?? 0), 0);
  }
  function remain(): number {
    return opts.limit - totalCost();
  }
  function canAdd(id: string): boolean {
    if (force.includes(id)) return true; // already in -> toggle off allowed
    if (force.length >= maxSlots) return false;
    return totalCost() + (byId.get(id)?.energy ?? 0) <= opts.limit;
  }

  function renderGrid(): void {
    clear(grid);
    for (const borg of opts.catalog) {
      const inForce = force.includes(borg.id);
      const disabled = !inForce && !canAdd(borg.id);
      const cell = el(
        "button",
        {
          class: `gf-borg-cell${inForce ? " gf-in-force" : ""}${disabled ? " gf-disabled" : ""}`,
          title: `${borg.name} — ${borg.energy}`,
          attrs: { type: "button", "data-id": borg.id },
          onClick: () => toggle(borg.id),
        },
      );
      if (borg.isNew) cell.appendChild(el("span", { class: "gf-new-badge", text: "NEW" }));
      const img = el("img", { attrs: { src: borgMiniPath(borg.id), alt: borg.name } }) as HTMLImageElement;
      img.addEventListener("error", () => {
        img.style.display = "none";
        cell.appendChild(el("span", { style: { fontSize: "9px", color: "#2a2150", padding: "2px" }, text: borg.name.slice(0, 6) }));
      });
      cell.appendChild(img);
      cell.appendChild(el("span", { class: "gf-cost-tag", text: String(borg.energy) }));
      grid.appendChild(cell);
    }
  }

  function renderRing(): void {
    // keep the panel, rebuild only slots
    for (const old of Array.from(ring.querySelectorAll(".gf-slot"))) old.remove();
    const cx = 50;
    const cy = 50;
    const rx = 44;
    const ry = 44;
    for (let i = 0; i < maxSlots; i++) {
      // start at bottom, go clockwise so slot 1 sits bottom-ish like the capture
      const angle = (90 + (360 / maxSlots) * i) * (Math.PI / 180);
      const x = cx + Math.cos(angle) * rx;
      const y = cy + Math.sin(angle) * ry;
      const id = force[i];
      const filled = id !== undefined;
      const slot = el(
        "button",
        {
          class: `gf-slot ${filled ? "gf-slot-filled" : "gf-slot-empty"}${i === 0 && filled ? " gf-slot-active" : ""}`,
          style: { left: `${x}%`, top: `${y}%` },
          attrs: { type: "button", "data-slot": String(i + 1), "aria-label": `slot ${i + 1}` },
          onClick: () => {
            if (id !== undefined) toggle(id);
          },
        },
      );
      if (filled) {
        const img = el("img", { attrs: { src: borgMiniPath(id), alt: byId.get(id)?.name ?? id } }) as HTMLImageElement;
        img.addEventListener("error", () => {
          img.style.display = "none";
          slot.textContent = String(i + 1);
        });
        slot.appendChild(img);
      } else {
        slot.textContent = String(i + 1);
      }
      ring.appendChild(slot);
    }
  }

  function renderBanner(): void {
    const lead = force[0];
    if (lead !== undefined) {
      bannerImg.style.visibility = "visible";
      bannerImg.src = borgBannerPath(lead);
      bannerName.textContent = (byId.get(lead)?.name ?? "FORCE") + " FORCE";
    } else {
      bannerImg.style.visibility = "hidden";
      bannerName.textContent = "EMPTY FORCE";
    }
  }

  function renderPanel(): void {
    const total = totalCost();
    const rem = remain();
    totalVal.textContent = String(total);
    limitVal.textContent = String(opts.limit);
    remainVal.textContent = String(rem);
    panel.classList.toggle("gf-over", rem < 0);
  }

  function renderAll(): void {
    renderGrid();
    renderRing();
    renderBanner();
    renderPanel();
  }

  function toggle(id: string): void {
    const at = force.indexOf(id);
    if (at >= 0) {
      force.splice(at, 1);
    } else if (canAdd(id)) {
      force.push(id);
    } else {
      return; // can't add (budget/slots)
    }
    renderAll();
    opts.onChange?.([...force], totalCost(), remain());
  }

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      if (remain() >= 0 && force.length > 0) opts.onConfirm([...force]);
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key === "Backspace") {
      opts.onQuit?.();
      ev.preventDefault();
    }
  }

  renderAll();
  container.appendChild(root);
  window.addEventListener("keydown", onKey);

  return {
    getForce: () => [...force],
    totalCost,
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}
