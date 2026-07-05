/**
 * Shared helper for showing a cropped region of a real captured native frame
 * (`apps/game/reference/captures/*.png`) as a screen's actual art, instead of
 * a CSS/SVG recreation — the same "real captured asset" convention MainMenu.ts
 * established for its desk backdrop. Used by SelectDifficulty.ts / SelectPlayers.ts
 * for pad/silhouette/controller tiles that have no separate 2D texture in the
 * export (the art only exists baked into the native-rendered frame).
 *
 * Renders as an `overflow: hidden` container plus a full-size `<img>` scaled
 * and shifted so only `box` (in the capture's native pixel space) shows
 * through. Callers should size the container via CSS (e.g. `aspect-ratio:
 * ${box.w} / ${box.h}`).
 */

import { el } from "./dom.js";

export interface CaptureCropBox {
  x: number;
  y: number;
  w: number;
  h: number;
}

export function captureCropImg(captureUrl: string, captureWidth: number, box: CaptureCropBox): HTMLImageElement {
  const widthPct = (captureWidth / box.w) * 100;
  const leftPct = -(box.x / box.w) * 100;
  const topPct = -(box.y / box.w) * 100;
  return el("img", {
    class: "gf-capture-crop-img",
    style: {
      position: "absolute",
      left: `${leftPct.toFixed(3)}%`,
      top: `${topPct.toFixed(3)}%`,
      width: `${widthPct.toFixed(3)}%`,
      maxWidth: "none",
      height: "auto",
    } as Partial<CSSStyleDeclaration>,
    attrs: { src: captureUrl, alt: "", "aria-hidden": "true" },
  });
}
