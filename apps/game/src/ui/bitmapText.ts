import { ASSETS } from "./assets.js";
import { el } from "./dom.js";

const ASCII_CELL = 8;

export function bitmapText(className = ""): HTMLSpanElement {
  const classes = ["gf-bitmap-text", className].filter(Boolean).join(" ");
  const node = el("span", { class: classes });
  node.setAttribute("aria-hidden", "true");
  return node;
}

export function setBitmapText(node: HTMLElement, value: string): void {
  node.replaceChildren(
    ...[...value.toUpperCase()].map((char) => {
      if (char === " ") return el("span", { class: "gf-bitmap-space" });
      const code = char.charCodeAt(0);
      if (code < 0x20 || code > 0x7e) return el("span", { class: "gf-bitmap-fallback", text: char });
      const idx = code - 0x20;
      const col = idx % 16;
      const row = Math.floor(idx / 16);
      return el("span", {
        class: "gf-bitmap-glyph",
        style: {
          backgroundImage: `url(${ASSETS.fontAscii})`,
          backgroundPosition: `-${col * ASCII_CELL}px -${row * ASCII_CELL}px`,
        },
      });
    }),
  );
  node.setAttribute("aria-label", value);
}
