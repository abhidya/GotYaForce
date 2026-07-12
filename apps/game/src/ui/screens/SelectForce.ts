/**
 * SelectForce — Challenge flow screen #5, per `challenge-5-select-a-force.png`.
 *
 * The real screen selects a saved force, shows the lead borg, force number/name,
 * total COST, and exposes X = EDIT FORCE. This component presents the current
 * force slot from browser-local roster data; the edit screen owns the 30-slot
 * force mutation.
 *
 * Surface: the green force-display platform is the REAL captured native frame
 * (`reference/captures/challenge-5-select-a-force.png`) cropped to just the pad
 * + its ground shadow — the same "real captured asset" convention MainMenu.ts /
 * SelectDifficulty.ts / SelectPlayers.ts already use, since the pad's baked
 * lighting/bevel/shadow has no separate flat 2D texture in the export distinct
 * from the 3D geometry. The entry00 scene mounts as an atmospheric backdrop
 * behind it (same rationale as the vsel00/01 sub-menus: the archive bundles all
 * entry00 sub-screens' geometry with no recoverable per-screen grouping — see
 * UI_SCENE_LAYOUTS.entry00.semantics.selectForce's own caveat). COST / No. /
 * force name / REMAIN are runtime-dynamic (per saved slot), so unlike the fixed
 * difficulty/player-count labels they render in the real exported ascii.tpl
 * bitmap font (see bitmapText.ts) rather than a capture crop of one baked value.
 */

import { createPublicAssetCatalog } from "@gf/assets";
import { bitmapText, setBitmapText } from "../bitmapText.js";
import { borgBannerPath, borgMiniPath } from "../assets.js";
import { captureCropImg } from "../captureCrop.js";
import { clear, el, legendItem } from "../dom.js";
import type { MenuAction, MenuInputTarget } from "../menuInput.js";
import { UI_SCENE_LAYOUTS } from "../layout.generated.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";
import type { ForceBorg } from "./ForceBuilder.js";

const SELECT_FORCE_LAYOUT = UI_SCENE_LAYOUTS.entry00.semantics.selectForce;
const assetCatalog = createPublicAssetCatalog();

const CAPTURE = new URL(
  "../../../reference/captures/challenge-5-select-a-force.png",
  import.meta.url,
).href;
/** Native capture is 2560x1966; crop box below is in that pixel space. */
const CAPTURE_W = 2560;
/** Green force platform only (no baked COST/No./name/legend text below it, no standing borg). */
const PLATFORM_CROP = { x: 150, y: 1050, w: 2410, h: 300 };

export interface ForceSlot {
  no: number;
  name: string;
  borgIds: string[];
}

// ---------------------------------------------------------------------------
// Force-slot persistence (browser stand-in for the memory-card "BOX DATA").
//
// The Load Box Data step advertises loading saved forces, but the flow state in
// main.ts is rebuilt from defaults on every page load, so edited forces used to
// vanish on refresh. SelectForce owns the slot list UI, so it restores saved
// slots into the caller's array on the first mount after a page load and saves
// them back on every later mount / selection / confirm.
// ---------------------------------------------------------------------------

const FORCE_SLOTS_STORAGE_KEY = "gf-force-slots-v1";
let restoredThisPageLoad = false;

function loadStoredForceSlots(): ForceSlot[] | null {
  try {
    const raw = window.localStorage.getItem(FORCE_SLOTS_STORAGE_KEY);
    if (!raw) return null;
    const parsed: unknown = JSON.parse(raw);
    if (!Array.isArray(parsed)) return null;
    const slots: ForceSlot[] = [];
    for (const entry of parsed) {
      if (typeof entry !== "object" || entry === null) return null;
      const slot = entry as Partial<ForceSlot>;
      if (typeof slot.no !== "number" || typeof slot.name !== "string" || !Array.isArray(slot.borgIds)) return null;
      slots.push({
        no: slot.no,
        name: slot.name,
        borgIds: slot.borgIds.filter((id): id is string => typeof id === "string"),
      });
    }
    return slots;
  } catch {
    return null;
  }
}

function saveForceSlots(slots: readonly ForceSlot[]): void {
  try {
    window.localStorage.setItem(FORCE_SLOTS_STORAGE_KEY, JSON.stringify(slots));
  } catch {
    // Storage may be unavailable (private mode); the in-memory slots still work.
  }
}

/** Restore once per page load, then persist on every later visit. */
function syncForceSlots(slots: ForceSlot[]): void {
  if (!restoredThisPageLoad) {
    restoredThisPageLoad = true;
    const stored = loadStoredForceSlots();
    if (stored) {
      for (let i = 0; i < slots.length; i++) {
        const saved = stored.find((s) => s.no === slots[i]!.no);
        if (saved) slots[i] = { ...slots[i]!, name: saved.name, borgIds: [...saved.borgIds] };
      }
      return;
    }
  }
  saveForceSlots(slots);
}

// ---------------------------------------------------------------------------
// Lead-borg 3D model lookup: any borg with an exported library model renders as
// its real model on the platform (not just the pl0615 special path).
// ---------------------------------------------------------------------------

let modelManifestPromise: Promise<ReadonlyMap<string, string>> | null = null;

function libraryModelPaths(): Promise<ReadonlyMap<string, string>> {
  if (!modelManifestPromise) {
    modelManifestPromise = assetCatalog.loadModelLibraryPaths();
  }
  return modelManifestPromise;
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

export interface SelectForceHandle extends MenuInputTarget {
  destroy: () => void;
}

export function createSelectForce(
  container: HTMLElement,
  opts: SelectForceOptions,
): SelectForceHandle {
  const byId = new Map(opts.catalog.map((b) => [b.id, b] as const));
  const slots: ForceSlot[] =
    opts.slots.length > 0 ? (opts.slots as ForceSlot[]) : [{ no: 1, name: "GOTCHA FORCE", borgIds: [] }];
  // Restore saved BOX DATA on the first mount after a page load; persist after.
  syncForceSlots(slots);
  let selectedSlot = clampSlot(opts.selectedSlot, slots.length);
  let stopLeadModel: (() => void) | null = null;
  let leadModelToken = 0;

  const root = el("div", {
    class: "gf-screen gf-select-force",
    style: selectForceLayoutVars(),
  });
  const entryScene = createUiSceneHost("gf-ui-scene gf-select-entry-scene");
  root.appendChild(entryScene);
  const title = bitmapText("gf-select-title-text");
  setBitmapText(title, "SELECT A FORCE", { bold: true, scale: 3, tint: "#ffd21e" });
  root.appendChild(el("h1", { class: "gf-title gf-select-title", attrs: { "aria-label": "SELECT A FORCE" } }, [title]));

  const platformCrop = el(
    "div",
    { class: "gf-select-pad-crop", attrs: { role: "img", "aria-hidden": "true" } },
    [captureCropImg(CAPTURE, CAPTURE_W, PLATFORM_CROP)],
  );
  root.appendChild(platformCrop);
  const platform = el("div", { class: "gf-select-pad" });
  root.appendChild(platform);

  const costRoot = el("div", { class: "gf-select-cost" });
  root.appendChild(costRoot);
  const nameRoot = el("div", { class: "gf-select-name" });
  root.appendChild(nameRoot);

  const lrLabel = bitmapText("gf-legend-lr-label");
  setBitmapText(lrLabel, "L/R CHANGE FORCE", { bold: true, scale: 1 });
  root.appendChild(
    el("div", { class: "gf-legend" }, [
      el("span", { class: "gf-legend-item" }, [lrLabel]),
      legendItem("b", "BACK"),
      legendItem("a", "CONFIRM"),
      legendItem("x", "EDIT FORCE"),
    ]),
  );

  function onMenuAction(action: MenuAction, dir?: -1 | 1): void {
    if (action === "left") {
      selectSlot(selectedSlot - 1);
    } else if (action === "right") {
      selectSlot(selectedSlot + 1);
    } else if (action === "switch") {
      // L/R force cycling: dir carries which shoulder/dpad-edge fired (see menuInput.ts).
      selectSlot(selectedSlot + (dir ?? 1));
    } else if (action === "confirm") {
      opts.onConfirm(currentSlot());
    } else if (action === "edit") {
      opts.onEdit(currentSlot());
    } else if (action === "back") {
      opts.onBack?.();
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
    leadModelToken += 1;
    const token = leadModelToken;
    clear(platform);
    if (lead === "pl0615") {
      mountLeadModel("/models/pl0615/model_00.glb");
    } else if (lead) {
      // Any lead with an exported library model renders as its real 3D model;
      // otherwise fall back to the extracted name plate, then plain text, so a
      // force led by ANY borgs.json entry still shows something sensible.
      mountLeadFallback(lead, leadBorg?.name ?? lead);
      void libraryModelPaths().then((paths) => {
        const modelPath = paths.get(lead);
        if (!modelPath || token !== leadModelToken) return;
        clear(platform);
        mountLeadModel(modelPath);
      });
    }

    function mountLeadModel(modelPath: string): void {
      const modelHost = createUiSceneHost("gf-select-borg-scene");
      platform.appendChild(modelHost);
      stopLeadModel = mountUiSceneModels(modelHost, {
        modelPaths: [modelPath],
        fitSize: 270,
        camera: { fov: 29, position: [0, 80, 520], lookAt: [0, 62, 0] },
        rotation: [-0.1, 0.32, 0],
      });
    }

    function mountLeadFallback(leadId: string, fallbackText: string): void {
      const mini = el("img", {
        class: "gf-select-mini",
        attrs: { src: borgMiniPath(leadId), alt: fallbackText },
      }) as HTMLImageElement;
      const fallback = bitmapText("gf-select-mini gf-select-mini-fallback");
      setBitmapText(fallback, fallbackText, { bold: true, scale: 2, tint: "#ffd21e" });
      fallback.style.display = "none";
      mini.addEventListener("error", () => {
        mini.style.display = "none";
        fallback.style.display = "flex";
      });
      platform.append(mini, fallback);
    }

    clear(costRoot);
    const costLabel = bitmapText("gf-select-cost-label");
    setBitmapText(costLabel, "COST", { bold: true, scale: 2, tint: "#ffd21e" });
    const costValue = bitmapText("gf-select-cost-value");
    setBitmapText(costValue, String(cost), { bold: true, scale: 4, tint: "#ffffff" });
    costRoot.append(costLabel, costValue);

    clear(nameRoot);
    const noText = bitmapText("gf-select-no");
    setBitmapText(noText, `NO. ${slot.no}`, { bold: true, scale: 2, tint: "#ffffff" });
    const forceNameText = bitmapText("gf-select-force-name");
    setBitmapText(forceNameText, slot.name, { bold: true, scale: 3, tint: "#ffd21e" });
    const limitText = bitmapText("gf-select-limit");
    setBitmapText(limitText, `${Math.max(0, opts.limit - cost)} REMAIN`, { bold: true, scale: 2, tint: "#dff6ff" });
    nameRoot.append(noText, forceBanner(lead, leadBorg?.name ?? slot.name), forceNameText, limitText);
  }

  renderSlot();
  container.appendChild(root);
  const stopEntryScene = mountUiSceneModels(entryScene, {
    sceneId: "entry00",
    fitSize: 780,
    camera: { fov: 31, position: [0, 130, 900], lookAt: [0, 20, 0] },
    rotation: [-0.12, 0, 0],
    maxModels: UI_SCENE_LAYOUTS.entry00.modelCount,
  });
  return {
    handleMenuInput: (event) => onMenuAction(event.action, event.dir),
    destroy: () => {
      leadModelToken += 1; // cancel any in-flight async lead-model mount
      stopLeadModel?.();
      stopEntryScene();
      root.remove();
    },
  };
}

function selectForceLayoutVars(): Partial<CSSStyleDeclaration> {
  const platform = SELECT_FORCE_LAYOUT.platform;
  const title = SELECT_FORCE_LAYOUT.title;
  const vars: Record<string, string> = {
    "--gf-select-pad-left": `${platform.left}%`,
    "--gf-select-pad-top": `${platform.top}%`,
    "--gf-select-pad-width": `${platform.width}%`,
    "--gf-select-pad-height": `${platform.height}%`,
  };
  if (title) {
    vars["--gf-select-title-left"] = `${title.left}%`;
    vars["--gf-select-title-top"] = `${title.top}%`;
    vars["--gf-select-title-width"] = `${title.width}%`;
  }
  return vars as Partial<CSSStyleDeclaration>;
}

function forceBanner(borgId: string, fallbackText: string): HTMLElement {
  const image = el("img", { class: "gf-select-banner", attrs: { src: borgBannerPath(borgId), alt: "" } }) as HTMLImageElement;
  image.addEventListener("error", () => {
    const fallback = bitmapText("gf-select-banner gf-select-banner-fallback");
    setBitmapText(fallback, fallbackText, { bold: true, scale: 2, tint: "#ffd21e" });
    image.replaceWith(fallback);
  });
  return image;
}

function clampSlot(index: number, count: number): number {
  if (count <= 0) return 0;
  if (!Number.isFinite(index)) return 0;
  return Math.min(Math.max(Math.trunc(index), 0), count - 1);
}
