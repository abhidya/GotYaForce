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
 *
 * `left`/`width` percentages resolve against the container's WIDTH while
 * `top` resolves against the container's HEIGHT (CSS percentage-offset
 * semantics for absolutely-positioned elements) — so the horizontal offset
 * scales by `box.w` and the vertical offset must scale by `box.h`, NOT
 * `box.w` again. A previous revision used a single `box.w`-based denominator
 * for both axes; that only looked correct for the near-square crop boxes it
 * happened to ship with (ratio ~0.83-1.07) and produced a badly wrong
 * vertical offset for any wide/short or tall/narrow box (e.g. a 2410x916 box
 * was off by several hundred px of source content vertically).
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
  // Container height derives from `aspect-ratio: box.w / box.h`, so the
  // vertical offset (a % of container height) scales by box.h, not box.w.
  const topPct = -(box.y / box.h) * 100;
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
