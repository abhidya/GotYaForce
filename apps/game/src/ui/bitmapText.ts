/**
 * Bitmap text rendered from the REAL `ascii.tpl` font atlas
 * (`/ui/tpl/ascii/image_00_IA4.png`, 128x128, 16x16 grid of 8px cells).
 *
 * Measured atlas layout (verified pixel-by-pixel; see scripts/assert-ascii-glyphs.mjs):
 *   row  0     : blank
 *   row  1     : hex header row "0123456789ABCDEF"       (thin style)
 *   rows 2..7  : THIN  ASCII block, chars 0x20..0x7E, 16 per row
 *   row  8     : blank
 *   row  9     : hex header row "0123456789ABCDEF"       (bold style)
 *   rows 10..15: BOLD  ASCII block, chars 0x20..0x7E, 16 per row
 *
 * The in-battle HUD uses the BOLD block (white core + baked black outline),
 * tinted per element (mint ally number, pink enemy number, yellow labels,
 * yellow-green HP/ammo digits) exactly like the real game tints its font quads.
 *
 * BUG HISTORY: a previous revision mapped `row = floor((code-0x20)/16)` with no
 * row offset, i.e. it assumed the ASCII block began at atlas row 0. Because the
 * block actually begins at row 2 (blank row + hex header first), every glyph
 * rendered two rows too high — "ENEMY" showed as "%.%-9", "ALLY" as "!,,9".
 * The fix is the ASCII_THIN_ROW_OFFSET / ASCII_BOLD_ROW_OFFSET below.
 */

import { ASSETS } from "./assets.js";
import { el } from "./dom.js";

export const ASCII_CELL = 8;
export const ASCII_COLS = 16;
export const ASCII_ATLAS_SIZE = 128;
/** First atlas row of the thin ASCII block (rows 0..1 are blank + hex header). */
export const ASCII_THIN_ROW_OFFSET = 2;
/** First atlas row of the bold ASCII block (row 8 blank, row 9 hex header). */
export const ASCII_BOLD_ROW_OFFSET = 10;

export interface AtlasCell {
  col: number;
  row: number;
}

/** Map a printable ASCII char to its atlas cell, or null when unprintable. */
export function asciiAtlasCell(char: string, bold = false): AtlasCell | null {
  const code = char.charCodeAt(0);
  if (Number.isNaN(code) || code < 0x20 || code > 0x7e) return null;
  const idx = code - 0x20;
  return {
    col: idx % ASCII_COLS,
    row: Math.floor(idx / ASCII_COLS) + (bold ? ASCII_BOLD_ROW_OFFSET : ASCII_THIN_ROW_OFFSET),
  };
}

export interface BitmapTextOptions {
  /** Use the bold outlined half of ascii.tpl (rows 10..15) — the battle-HUD style. */
  bold?: boolean;
  /** Integer glyph scale; 1 = native 8px cells. HUD numerals are 2..3. */
  scale?: number;
  /**
   * Tint color (CSS hex). The atlas glyphs are white-core/black-outline; the
   * tint recolors ONLY the white core (like the game's vertex-colored font
   * quads) and keeps the baked outline. Omit for the untinted white glyphs.
   */
  tint?: string;
  /** Preserve case; by default text is uppercased like the original HUD. */
  keepCase?: boolean;
  /**
   * Horizontal advance in px between glyph origins (the game packs its font
   * quads tighter than the 8px cell grid). Defaults to the scaled cell size.
   */
  advance?: number;
}

export function bitmapText(className = ""): HTMLSpanElement {
  const classes = ["gf-bitmap-text", className].filter(Boolean).join(" ");
  const node = el("span", { class: classes });
  node.setAttribute("aria-hidden", "true");
  return node;
}

// ---------------------------------------------------------------------------
// Tinted atlas variants. We recolor the white glyph cores on a canvas once per
// tint color and cache the data URL, preserving the baked black outline that a
// CSS mask would flatten away.
// ---------------------------------------------------------------------------

const tintedAtlasCache = new Map<string, string>(); // color -> data URL (once ready)
const tintInFlight = new Map<string, Promise<string>>();
let atlasImagePromise: Promise<HTMLImageElement> | null = null;

function loadAtlasImage(): Promise<HTMLImageElement> {
  if (!atlasImagePromise) {
    atlasImagePromise = new Promise((resolve, reject) => {
      const img = new Image();
      img.onload = () => resolve(img);
      img.onerror = () => reject(new Error(`failed to load ${ASSETS.fontAscii}`));
      img.src = ASSETS.fontAscii;
    });
  }
  return atlasImagePromise;
}

function parseHexColor(hex: string): [number, number, number] {
  const m = /^#?([0-9a-f]{6})$/i.exec(hex.trim());
  const v = m?.[1] !== undefined ? parseInt(m[1], 16) : 0xffffff;
  return [(v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff];
}

/** Build (and cache) a copy of the atlas with white cores recolored to `color`. */
function tintedAtlasUrl(color: string): Promise<string> {
  const hit = tintInFlight.get(color);
  if (hit) return hit;
  const p = loadAtlasImage().then((img) => {
    const canvas = document.createElement("canvas");
    canvas.width = img.naturalWidth;
    canvas.height = img.naturalHeight;
    const ctx = canvas.getContext("2d");
    if (!ctx) return ASSETS.fontAscii;
    ctx.drawImage(img, 0, 0);
    const data = ctx.getImageData(0, 0, canvas.width, canvas.height);
    const [tr, tg, tb] = parseHexColor(color);
    const px = data.data;
    for (let i = 0; i < px.length; i += 4) {
      if ((px[i + 3] ?? 0) === 0) continue;
      // Blend toward the tint by the pixel's intensity: white core -> tint,
      // black outline stays black, antialiased edges blend proportionally.
      const k = (px[i] ?? 0) / 255;
      px[i] = Math.round(tr * k);
      px[i + 1] = Math.round(tg * k);
      px[i + 2] = Math.round(tb * k);
    }
    ctx.putImageData(data, 0, 0);
    const url = canvas.toDataURL("image/png");
    tintedAtlasCache.set(color, url);
    return url;
  });
  tintInFlight.set(color, p);
  return p;
}

/**
 * Replace `node`'s children with atlas glyph spans spelling `value`.
 * Backwards compatible: existing 2-arg callers get the thin white 1x glyphs.
 */
export function setBitmapText(node: HTMLElement, value: string, opts: BitmapTextOptions = {}): void {
  const scale = Math.max(1, opts.scale ?? 1);
  const cellPx = ASCII_CELL * scale;
  const sheetPx = ASCII_ATLAS_SIZE * scale;
  const advance = opts.advance ?? cellPx;
  const overlap = advance - cellPx; // negative = tighter-than-cell packing
  const text = opts.keepCase ? value : value.toUpperCase();
  const tint = opts.tint;
  const readyTint = tint ? tintedAtlasCache.get(tint) : undefined;
  if (opts.advance !== undefined) node.style.gap = "0px";

  const chars = [...text];
  const glyphs = chars.map((char, i) => {
    const marginRight = overlap !== 0 && i < chars.length - 1 ? `${overlap}px` : "";
    if (char === " ") {
      return el("span", {
        class: "gf-bitmap-space",
        style: { width: `${cellPx}px`, height: `${cellPx}px`, marginRight },
      });
    }
    const cell = asciiAtlasCell(char, opts.bold);
    if (!cell) return el("span", { class: "gf-bitmap-fallback", text: char });
    const span = el("span", {
      class: "gf-bitmap-glyph",
      style: {
        width: `${cellPx}px`,
        height: `${cellPx}px`,
        marginRight,
        backgroundImage: `url(${readyTint ?? ASSETS.fontAscii})`,
        backgroundSize: `${sheetPx}px ${sheetPx}px`,
        backgroundPosition: `-${cell.col * cellPx}px -${cell.row * cellPx}px`,
      },
    });
    return span;
  });
  node.replaceChildren(...glyphs);
  node.setAttribute("aria-label", value);

  // If a tint was requested but not cached yet, swap the sheets in once ready.
  if (tint && !readyTint) {
    void tintedAtlasUrl(tint).then((url) => {
      if (!node.isConnected && node.childElementCount === 0) return;
      for (const child of Array.from(node.children)) {
        if (child instanceof HTMLElement && child.classList.contains("gf-bitmap-glyph")) {
          child.style.backgroundImage = `url(${url})`;
        }
      }
    });
  }
}
