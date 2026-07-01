/**
 * SelectForce — Challenge flow screen #5, per `challenge-5-select-a-force.png`.
 *
 * The real screen selects a saved force, shows the lead borg, force number/name,
 * total COST, and exposes X = EDIT FORCE. This component presents the current
 * force slot from browser-local roster data; the edit screen owns the 30-slot
 * force mutation.
 */

import { ASSETS, borgBannerPath, borgFacePath, borgMiniPath } from "../assets.js";
import { clear, el, legendItem } from "../dom.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";
import type { ForceBorg } from "./ForceBuilder.js";

export interface ForceSlot {
  no: number;
  name: string;
  borgIds: string[];
}

export interface SelectForceOptions {
  catalog: readonly ForceBorg[];
  slots: readonly ForceSlot[];
  selectedSlot: number;
  limit: number;
  onSelectSlot?: (slotIndex: number) => void;
  onConfirm: (slot: ForceSlot) => void;
  onEdit: (slot: ForceSlot) => void;
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
  const slots = opts.slots.length > 0 ? opts.slots : [{ no: 1, name: "GOTCHA FORCE", borgIds: [] }];
  let selectedSlot = clampSlot(opts.selectedSlot, slots.length);
  let stopLeadModel: (() => void) | null = null;

  const root = el("div", { class: "gf-screen gf-select-force" });
  root.appendChild(el("div", { class: "gf-grid-bg gf-bg-purple" }));
  const entryScene = createUiSceneHost("gf-ui-scene gf-select-entry-scene");
  root.appendChild(entryScene);
  root.appendChild(el("h1", { class: "gf-title", text: "SELECT A FORCE" }));
  root.appendChild(
    el("img", { class: "gf-select-entry-sheet", attrs: { src: ASSETS.entryControls, alt: "", "aria-hidden": "true" } }),
  );

  const platform = el("div", { class: "gf-select-platform" });
  root.appendChild(platform);

  const costRoot = el("div", { class: "gf-select-cost" });
  root.appendChild(costRoot);
  const nameRoot = el("div", { class: "gf-select-name" });
  root.appendChild(nameRoot);

  root.appendChild(
    el("div", { class: "gf-legend" }, [
      el("span", { class: "gf-legend-item" }, [el("span", { text: "L/R" }), el("span", { text: "CHANGE FORCE" })]),
      legendItem("b", "BACK"),
      legendItem("a", "CONFIRM"),
      legendItem("x", "EDIT FORCE"),
    ]),
  );

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "ArrowLeft" || ev.key.toLowerCase() === "q") {
      selectSlot(selectedSlot - 1);
      ev.preventDefault();
    } else if (ev.key === "ArrowRight" || ev.key.toLowerCase() === "e") {
      selectSlot(selectedSlot + 1);
      ev.preventDefault();
    } else if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      opts.onConfirm(currentSlot());
      ev.preventDefault();
    } else if (ev.key.toLowerCase() === "x") {
      opts.onEdit(currentSlot());
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      opts.onBack?.();
      ev.preventDefault();
    }
  }

  function currentSlot(): ForceSlot {
    return slots[selectedSlot] ?? slots[0]!;
  }

  function selectSlot(index: number): void {
    selectedSlot = (index + slots.length) % slots.length;
    opts.onSelectSlot?.(selectedSlot);
    renderSlot();
  }

  function renderSlot(): void {
    const slot = currentSlot();
    const force = slot.borgIds.filter((id) => byId.has(id));
    const lead = force[0] ?? opts.catalog[0]?.id ?? "";
    const leadBorg = byId.get(lead);
    const cost = force.reduce((sum, id) => sum + (byId.get(id)?.energy ?? 0), 0);

    stopLeadModel?.();
    stopLeadModel = null;
    clear(platform);
    if (lead === "pl0615") {
      const modelHost = createUiSceneHost("gf-select-borg-scene");
      platform.appendChild(modelHost);
      stopLeadModel = mountUiSceneModels(modelHost, {
        modelPaths: ["/models/pl0615/model_00.dae"],
        fitSize: 270,
        camera: { fov: 29, position: [0, 80, 520], lookAt: [0, 62, 0] },
        rotation: [-0.1, 0.32, 0],
      });
    } else {
      const face = el("img", { class: "gf-select-face", attrs: { src: borgFacePath(lead), alt: leadBorg?.name ?? "" } }) as HTMLImageElement;
      const mini = el("img", { class: "gf-select-mini", attrs: { src: borgMiniPath(lead), alt: leadBorg?.name ?? "" } }) as HTMLImageElement;
      face.addEventListener("error", () => {
        face.style.display = "none";
        mini.style.display = "block";
      });
      mini.style.display = "none";
      platform.append(face, mini);
    }

    clear(costRoot);
    costRoot.append(
      el("span", { class: "gf-select-cost-label", text: "COST" }),
      el("span", { class: "gf-select-cost-value", text: String(cost) }),
    );

    clear(nameRoot);
    nameRoot.append(
      el("span", { class: "gf-select-no", text: `No. ${slot.no}` }),
      el("img", { class: "gf-select-banner", attrs: { src: borgBannerPath(lead), alt: "" } }),
      el("span", { class: "gf-select-force-name", text: slot.name }),
      el("span", { class: "gf-select-limit", text: `${Math.max(0, opts.limit - cost)} REMAIN` }),
    );
  }

  renderSlot();
  container.appendChild(root);
  const stopEntryScene = mountUiSceneModels(entryScene, {
    sceneId: "entry00",
    fitSize: 780,
    camera: { fov: 31, position: [0, 130, 900], lookAt: [0, 20, 0] },
    rotation: [-0.12, 0, 0],
    maxModels: 29,
  });
  window.addEventListener("keydown", onKey);

  return {
    destroy: () => {
      stopLeadModel?.();
      stopEntryScene();
      window.removeEventListener("keydown", onKey);
      root.remove();
    },
  };
}

function clampSlot(index: number, count: number): number {
  if (count <= 0) return 0;
  if (!Number.isFinite(index)) return 0;
  return Math.min(Math.max(Math.trunc(index), 0), count - 1);
}
