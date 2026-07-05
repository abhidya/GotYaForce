/**
 * ForceBuilder — the Edit Force builder, per `challenge-6-edit-force.png`.
 *
 * Layout matches the capture:
 *  - top-left  : "EDIT" tab with L/R arrows (real captured plate)
 *  - top-right : active-borg name banner (real captured plate) + name in bitmap font
 *  - left      : a scrollable borg grid built from the real `mn<code>` icons over
 *                the real captured checkered-floor backdrop
 *  - right     : a 30-slot force ring of yellow hexagons (real captured hex tile
 *                as each slot's texture; the purple ring band itself is a
 *                sampled-color CSS backdrop — see the ring section comment for
 *                why the full ring isn't a single capture crop)
 *  - panel     : TOTAL COST / LIMIT / REMAIN in bitmap font, on a plate built
 *                from the real captured bar colors (the baked capture always
 *                shows one instance's numbers burned in, so the bars are
 *                reproduced as sampled-color CSS rather than cropped with
 *                someone else's cost baked into the pixels)
 *  - legend    : CHANGE FORCE / QUIT / TURN / MENU / HOLD / SPEC
 *
 * Budget rule (confirmed): LIMIT = chosen difficulty energy; TOTAL COST = sum of
 * force borg energy; REMAIN = LIMIT - TOTAL; a borg can't be added if it would
 * push TOTAL over LIMIT or the force already holds 30. Click OR keyboard/gamepad
 * (via the shared menu-input bus) navigate both the grid and the ring.
 *
 * COMPROMISE (documented per task instructions): the real capture's 30-slot ring
 * is rendered by the original game in true 3D with each hex following the ring's
 * curvature and perspective; the capture itself only shows slots 1-8 and 30 (the
 * rest are off-frame at this camera angle), so there is no single real texture
 * covering all 30 positions. Reproducing the full ring pixel-for-pixel would
 * require either (a) fabricating the missing 21 slots' art from whole cloth, or
 * (b) constraining the ring to a fixed camera/rotation that would break the
 * click/keyboard/gamepad navigation this screen must keep fully interactive.
 * Usability wins here per the task brief: every slot is a real DOM button (full
 * keyboard/gamepad/mouse access), textured with the one real captured hex-plate
 * crop (flat, unrotated — the perspective foreshortening is not reproduced), laid
 * out on a ring whose band color is sampled from the capture rather than an image
 * crop of it.
 */

import { bitmapText, setBitmapText } from "../bitmapText.js";
import { captureCropImg } from "../captureCrop.js";
import { el, clear } from "../dom.js";
import { borgMiniPath } from "../assets.js";
import { subscribeMenuInput, type MenuAction } from "../menuInput.js";
import { UI_SCENE_LAYOUTS } from "../layout.generated.js";
import { createUiSceneHost, mountUiSceneModels } from "../sceneModel.js";

const CAPTURE = new URL("../../../reference/captures/challenge-6-edit-force.png", import.meta.url).href;
/** Native capture is 2560x1966; crop boxes below are in that pixel space. */
const CAPTURE_W = 2560;
/** "EDIT [L] ... [R]" tab pill, top-left. Static chrome (label never changes). */
const EDIT_TAB_CROP = { x: 140, y: 15, w: 900, h: 210 };
/** Active-force name banner plate (roundel + rounded bar), top-right. Text painted over it. */
const NAME_BANNER_CROP = { x: 1370, y: 10, w: 1190, h: 230 };
/** One real yellow/red hex slot tile, cropped flat (no ring-curvature rotation reproduced). */
const HEX_TILE_CROP = { x: 1651, y: 1139, w: 269, h: 179 };
/** Blue checkered inventory floor, left panel backdrop. */
const FLOOR_CROP = { x: 0, y: 220, w: 1350, h: 1630 };

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

/** Which side currently owns the keyboard/gamepad cursor. */
type FocusSide = "grid" | "ring";

export function createForceBuilder(
  container: HTMLElement,
  opts: ForceBuilderOptions,
): ForceBuilderHandle {
  const maxSlots = opts.maxSlots ?? 30;
  const byId = new Map(opts.catalog.map((b) => [b.id, b] as const));
  const force: string[] = [...(opts.initialForce ?? [])].filter((id) => byId.has(id)).slice(0, maxSlots);
  const teardown: Array<() => void> = [];

  // Keyboard/gamepad cursor state: a grid index (into opts.catalog) and a ring
  // index (0..maxSlots-1). The bus is LIFO/single-owner per screen (see
  // menuInput.ts), so within THIS screen up/down/left/right must do double duty
  // for both panels; "switch" (L/R, the real game's actual panel-swap input,
  // per the capture's own "CHANGE FORCE"/+ legend) toggles which side is active.
  let focusSide: FocusSide = "grid";
  let gridCursor = 0;
  let ringCursor = 0;

  const root = el("div", { class: "gf-screen gf-force-screen" });
  const unitAllScene = createUiSceneHost("gf-ui-scene gf-force-unitall-scene");
  root.appendChild(unitAllScene);
  teardown.push(
    mountUiSceneModels(unitAllScene, {
      sceneId: "unitall",
      fitSize: 900,
      camera: { fov: 31, position: [0, 0, 980], lookAt: [0, 0, 0] },
      rotation: [0, 0, 0],
      maxModels: UI_SCENE_LAYOUTS.unitall.modelCount,
    }),
  );
  const layout = el("div", { class: "gf-force" });

  // ---- left column: EDIT tab (real plate) + grid over real floor backdrop ----
  const left = el("div", { class: "gf-force-left" });
  const editTab = el(
    "div",
    { class: "gf-force-edit-tab-crop", attrs: { role: "img", "aria-label": "EDIT" } },
    [captureCropImg(CAPTURE, CAPTURE_W, EDIT_TAB_CROP)],
  );
  left.appendChild(editTab);
  const grid = el("div", { class: "gf-borg-grid", attrs: { role: "listbox", "aria-label": "Borg roster" } });
  const floorBackdrop = el(
    "div",
    { class: "gf-force-floor-crop", attrs: { "aria-hidden": "true" } },
    [captureCropImg(CAPTURE, CAPTURE_W, FLOOR_CROP), grid],
  );
  left.appendChild(floorBackdrop);

  // ---- right column: banner (real plate) + ring + cost panel ----
  const right = el("div", { class: "gf-force-right" });
  const banner = el("div", { class: "gf-force-banner" });
  const bannerCrop = el(
    "div",
    { class: "gf-force-banner-crop", attrs: { "aria-hidden": "true" } },
    [captureCropImg(CAPTURE, CAPTURE_W, NAME_BANNER_CROP)],
  );
  const bannerMini = el("img", { class: "gf-force-banner-mini", attrs: { alt: "", "aria-hidden": "true" } }) as HTMLImageElement;
  bannerMini.addEventListener("error", () => (bannerMini.style.visibility = "hidden"));
  const bannerName = bitmapText("gf-force-banner-name");
  banner.append(bannerCrop, bannerMini, bannerName);
  right.appendChild(banner);

  const ring = el("div", { class: "gf-borg-ring", attrs: { role: "listbox", "aria-label": "Force slots" } });
  right.appendChild(ring);

  const panel = el("div", { class: "gf-cost-panel" });
  const totalLabel = bitmapText("gf-cost-label");
  setBitmapText(totalLabel, "TOTAL COST", { bold: true, scale: 1 });
  const totalVal = bitmapText("gf-cost-val");
  const limitLabel = bitmapText("gf-cost-label");
  setBitmapText(limitLabel, "LIMIT", { bold: true, scale: 1 });
  const limitVal = bitmapText("gf-cost-val");
  const remainLabel = bitmapText("gf-cost-label");
  setBitmapText(remainLabel, "REMAIN", { bold: true, scale: 1 });
  const remainVal = bitmapText("gf-cost-val gf-remain");
  panel.append(
    el("div", { class: "gf-cost-line gf-cost-total" }, [totalLabel, totalVal]),
    el("div", { class: "gf-cost-line" }, [limitLabel, limitVal]),
    el("div", { class: "gf-cost-line" }, [remainLabel, remainVal]),
  );
  ring.appendChild(panel);

  layout.append(left, right);
  root.appendChild(layout);

  // ---- bottom legend (bitmap font; the real capture's own button-glyph legend) ----
  const legend = el("div", { class: "gf-legend gf-force-legend" });
  const legendDefs: Array<[string, string]> = [
    ["+", "CHANGE FORCE"],
    ["START", "QUIT"],
    ["C", "TURN"],
    ["Y", "MENU"],
    ["A", "HOLD"],
    ["X", "SPEC"],
  ];
  for (const [glyph, label] of legendDefs) {
    const glyphSpan = bitmapText("gf-legend-glyph");
    setBitmapText(glyphSpan, glyph, { bold: true, scale: 1 });
    const labelSpan = bitmapText("gf-legend-label");
    setBitmapText(labelSpan, label, { bold: true, scale: 1 });
    legend.appendChild(el("span", { class: "gf-legend-item" }, [glyphSpan, labelSpan]));
  }
  root.appendChild(legend);

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
    opts.catalog.forEach((borg, index) => {
      const inForce = force.includes(borg.id);
      const disabled = !inForce && !canAdd(borg.id);
      const focused = focusSide === "grid" && index === gridCursor;
      const attrs: Record<string, string> = { type: "button", "data-id": borg.id, role: "option" };
      if (disabled) {
        attrs["disabled"] = "";
        attrs["aria-disabled"] = "true";
      }
      if (focused) attrs["aria-selected"] = "true";
      const cell = el(
        "button",
        {
          class: `gf-borg-cell${inForce ? " gf-in-force" : ""}${disabled ? " gf-disabled" : ""}${focused ? " gf-cursor" : ""}`,
          title: `${borg.name} — ${borg.energy}`,
          attrs,
          onClick: () => {
            focusSide = "grid";
            gridCursor = index;
            toggle(borg.id);
          },
        },
      );
      if (borg.isNew) {
        const badge = bitmapText("gf-new-badge");
        setBitmapText(badge, "NEW", { bold: true, scale: 1 });
        cell.appendChild(badge);
      }
      // The real `mn<code>` art is the borg's name plate (224x32). Borgs without an
      // exported plate (e.g. pl0507/pl0513) fall back to a plain text name so every
      // borgs.json entry stays a visible, selectable option.
      const img = el("img", { attrs: { src: borgMiniPath(borg.id), alt: borg.name } }) as HTMLImageElement;
      img.addEventListener("error", () => {
        img.remove();
        const nameFallback = bitmapText("gf-borg-cell-name");
        setBitmapText(nameFallback, borg.name, { bold: true, scale: 1 });
        cell.insertBefore(nameFallback, cell.querySelector(".gf-cost-tag"));
      });
      cell.appendChild(img);
      const costTag = bitmapText("gf-cost-tag");
      setBitmapText(costTag, String(borg.energy), { bold: true, scale: 1, tint: "#ffd21e" });
      cell.appendChild(costTag);
      grid.appendChild(cell);
    });
    if (focusSide === "grid") {
      grid.querySelector(".gf-cursor")?.scrollIntoView({ block: "nearest" });
    }
  }

  function renderRing(): void {
    // keep the panel, rebuild only slots
    for (const old of Array.from(ring.querySelectorAll(".gf-hexcell"))) old.remove();
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
      const focused = focusSide === "ring" && i === ringCursor;
      const slot = el(
        "button",
        {
          class: `gf-hexcell ${filled ? "gf-hexcell-filled" : "gf-hexcell-empty"}${i === 0 && filled ? " gf-hexcell-active" : ""}${focused ? " gf-cursor" : ""}`,
          style: { left: `${x}%`, top: `${y}%` },
          title: filled ? (byId.get(id)?.name ?? id) : `slot ${i + 1}`,
          attrs: {
            type: "button",
            "data-slot": String(i + 1),
            "aria-label": `slot ${i + 1}`,
            role: "option",
            ...(focused ? { "aria-selected": "true" } : {}),
          },
          onClick: () => {
            focusSide = "ring";
            ringCursor = i;
            if (id !== undefined) toggle(id);
          },
        },
      );
      const hexTile = captureCropImg(CAPTURE, CAPTURE_W, HEX_TILE_CROP);
      hexTile.className = "gf-hexcell-hex-tile";
      slot.appendChild(hexTile);
      const slotNo = bitmapText("gf-hexcell-no");
      setBitmapText(slotNo, String(i + 1), { bold: true, scale: 1 });
      slot.appendChild(slotNo);
      if (filled) {
        const img = el("img", { class: "gf-hexcell-img", attrs: { src: borgMiniPath(id), alt: byId.get(id)?.name ?? id } }) as HTMLImageElement;
        img.addEventListener("error", () => {
          img.style.display = "none";
        });
        slot.appendChild(img);
      }
      ring.appendChild(slot);
    }
  }

  function renderBanner(): void {
    const lead = force[0];
    if (lead !== undefined) {
      bannerMini.style.visibility = "visible";
      bannerMini.src = borgMiniPath(lead);
      setBitmapText(bannerName, `${(byId.get(lead)?.name ?? "FORCE")} FORCE`, { bold: true, scale: 1, tint: "#bcdcff" });
    } else {
      bannerMini.style.visibility = "hidden";
      setBitmapText(bannerName, "EMPTY FORCE", { bold: true, scale: 1, tint: "#bcdcff" });
    }
  }

  function renderPanel(): void {
    const total = totalCost();
    const rem = remain();
    setBitmapText(totalVal, String(total), { bold: true, scale: 2 });
    setBitmapText(limitVal, String(opts.limit), { bold: true, scale: 2 });
    if (rem < 0) setBitmapText(remainVal, String(rem), { bold: true, scale: 2, tint: "#ff5a4f" });
    else setBitmapText(remainVal, String(rem), { bold: true, scale: 2 });
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

  // ---------- keyboard/gamepad navigation ----------
  // Grid is a 1D scroll of opts.catalog (wrap-around); ring is a 1D loop of
  // maxSlots. "switch" (L/R shoulder / [ ]) swaps which panel the cursor
  // controls — the real screen's own "CHANGE FORCE"-adjacent panel toggle.
  function onMenuAction(action: MenuAction): void {
    if (action === "switch") {
      focusSide = focusSide === "grid" ? "ring" : "grid";
      renderGrid();
      renderRing();
      return;
    }
    if (focusSide === "grid") {
      const count = opts.catalog.length;
      if (count === 0) return;
      if (action === "down" || action === "right") {
        gridCursor = (gridCursor + 1) % count;
        renderGrid();
      } else if (action === "up" || action === "left") {
        gridCursor = (gridCursor - 1 + count) % count;
        renderGrid();
      } else if (action === "confirm") {
        const borg = opts.catalog[gridCursor];
        if (borg) toggle(borg.id);
      } else if (action === "back" || action === "start") {
        opts.onQuit?.();
      }
      return;
    }
    // focusSide === "ring"
    if (action === "down" || action === "right") {
      ringCursor = (ringCursor + 1) % maxSlots;
      renderRing();
    } else if (action === "up" || action === "left") {
      ringCursor = (ringCursor - 1 + maxSlots) % maxSlots;
      renderRing();
    } else if (action === "confirm") {
      const id = force[ringCursor];
      if (id !== undefined) toggle(id);
    } else if (action === "back" || action === "start") {
      opts.onQuit?.();
    }
  }

  renderAll();
  container.appendChild(root);
  const unsubscribeMenuInput = subscribeMenuInput((event) => onMenuAction(event.action));

  return {
    getForce: () => [...force],
    totalCost,
    destroy: () => {
      for (const stop of teardown) stop();
      unsubscribeMenuInput();
      root.remove();
    },
  };
}
