/**
 * SelectForce — Challenge flow screen #5, per `challenge-5-select-a-force.png`.
 *
 * The real screen selects a saved force, shows the lead borg, force number/name,
 * total COST, and exposes X = EDIT FORCE. This component presents the current
 * force slot from browser-local roster data; the edit screen owns the 30-slot
 * force mutation.
 */

import { ASSETS, borgBannerPath, borgFacePath, borgMiniPath } from "../assets.js";
import { el, legendItem } from "../dom.js";
import type { ForceBorg } from "./ForceBuilder.js";

export interface SelectForceOptions {
  catalog: readonly ForceBorg[];
  force: readonly string[];
  limit: number;
  onConfirm: (force: string[]) => void;
  onEdit: (force: string[]) => void;
  onBack?: () => void;
}

export interface SelectForceHandle {
  destroy: () => void;
}

export function createSelectForce(
  container: HTMLElement,
  opts: SelectForceOptions,
): SelectForceHandle {
  const byId = new Map(opts.catalog.map((b) => [b.id, b] as const));
  const force = opts.force.filter((id) => byId.has(id));
  const lead = force[0] ?? opts.catalog[0]?.id ?? "";
  const leadBorg = byId.get(lead);
  const cost = force.reduce((sum, id) => sum + (byId.get(id)?.energy ?? 0), 0);
  const forceName = `${leadBorg?.name ?? "GOTCHA"} FORCE`;

  const root = el("div", { class: "gf-screen gf-select-force" });
  root.appendChild(el("div", { class: "gf-grid-bg gf-bg-purple" }));
  root.appendChild(el("h1", { class: "gf-title", text: "SELECT A FORCE" }));
  root.appendChild(
    el("img", { class: "gf-select-entry-sheet", attrs: { src: ASSETS.entryControls, alt: "", "aria-hidden": "true" } }),
  );

  const platform = el("div", { class: "gf-select-platform" });
  const face = el("img", { class: "gf-select-face", attrs: { src: borgFacePath(lead), alt: leadBorg?.name ?? "" } }) as HTMLImageElement;
  const mini = el("img", { class: "gf-select-mini", attrs: { src: borgMiniPath(lead), alt: leadBorg?.name ?? "" } }) as HTMLImageElement;
  face.addEventListener("error", () => {
    face.style.display = "none";
    mini.style.display = "block";
  });
  mini.style.display = "none";
  platform.append(face, mini);
  root.appendChild(platform);

  root.appendChild(
    el("div", { class: "gf-select-cost" }, [
      el("span", { class: "gf-select-cost-label", text: "COST" }),
      el("span", { class: "gf-select-cost-value", text: String(cost) }),
    ]),
  );
  root.appendChild(
    el("div", { class: "gf-select-name" }, [
      el("span", { class: "gf-select-no", text: "No. 1" }),
      el("img", { class: "gf-select-banner", attrs: { src: borgBannerPath(lead), alt: "" } }),
      el("span", { class: "gf-select-force-name", text: forceName }),
      el("span", { class: "gf-select-limit", text: `${Math.max(0, opts.limit - cost)} REMAIN` }),
    ]),
  );

  root.appendChild(
    el("div", { class: "gf-legend" }, [
      legendItem("b", "BACK"),
      legendItem("a", "CONFIRM"),
      legendItem("x", "EDIT FORCE"),
    ]),
  );

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      opts.onConfirm([...force]);
      ev.preventDefault();
    } else if (ev.key.toLowerCase() === "x") {
      opts.onEdit([...force]);
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      opts.onBack?.();
      ev.preventDefault();
    }
  }

  container.appendChild(root);
  window.addEventListener("keydown", onKey);

  return {
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}
