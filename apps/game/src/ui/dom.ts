/**
 * Tiny framework-free DOM helpers shared by the Gotcha Force UI components.
 * No dependencies; keeps each screen/HUD component self-contained.
 */

/** Attribute / property bag accepted by {@link el}. */
export interface ElOpts {
  class?: string;
  text?: string;
  html?: string;
  title?: string;
  /** Inline style fragments merged onto element.style. */
  style?: Partial<CSSStyleDeclaration>;
  /** Arbitrary attributes (e.g. src, alt, type, aria-*). */
  attrs?: Record<string, string>;
  /** click handler convenience. */
  onClick?: (ev: MouseEvent) => void;
}

/** Create an element with the common options applied. */
export function el<K extends keyof HTMLElementTagNameMap>(
  tag: K,
  opts: ElOpts = {},
  children: readonly (Node | string)[] = [],
): HTMLElementTagNameMap[K] {
  const node = document.createElement(tag);
  if (opts.class) node.className = opts.class;
  if (opts.text !== undefined) node.textContent = opts.text;
  if (opts.html !== undefined) node.innerHTML = opts.html;
  if (opts.title !== undefined) node.title = opts.title;
  if (opts.style) Object.assign(node.style, opts.style);
  if (opts.attrs) {
    for (const [k, v] of Object.entries(opts.attrs)) node.setAttribute(k, v);
  }
  if (opts.onClick) {
    const handler = opts.onClick;
    node.addEventListener("click", (ev) => handler(ev as MouseEvent));
  }
  for (const child of children) {
    node.append(typeof child === "string" ? document.createTextNode(child) : child);
  }
  return node;
}

/** Convenience: a face-button glyph span (A/B/X/Y/START). */
export function faceButton(kind: "a" | "b" | "x" | "y" | "start"): HTMLSpanElement {
  const label = kind === "start" ? "START" : kind.toUpperCase();
  return el("span", { class: `gf-btn gf-btn-${kind}`, text: label });
}

/** A bottom-legend entry: a face button followed by an action label. */
export function legendItem(kind: "a" | "b" | "x" | "y" | "start", label: string): HTMLSpanElement {
  return el("span", { class: "gf-legend-item" }, [faceButton(kind), el("span", { text: label })]);
}

/** Build an inline SVG node from raw markup (so we can ship vector reticles/gauges). */
export function svg(markup: string): SVGElement {
  const wrap = document.createElement("div");
  wrap.innerHTML = markup.trim();
  const node = wrap.firstElementChild;
  if (!(node instanceof SVGElement)) throw new Error("svg() expected an <svg> root");
  return node;
}

/** Clamp a 0..1 progress value. */
export function clamp01(v: number): number {
  return v < 0 ? 0 : v > 1 ? 1 : v;
}

/** Remove all children from a node. */
export function clear(node: Element): void {
  while (node.firstChild) node.removeChild(node.firstChild);
}
