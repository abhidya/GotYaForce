/**
 * BattleHud — the in-battle HUD, per `challenge-8-in-battle-hud.png` (+ -9 critical).
 *
 * Mounts as a pointer-events:none overlay over the 3D arena. Layout matches the
 * capture exactly:
 *  - top-left  : green "<n> ALLY" meter stacked over red "ENEMY <n>" meter, both
 *                with zigzag/torn ends, numeric tabs, depleting fills. A yellow
 *                "!" alert sits to their right when triggered.
 *  - center    : orange lock-on reticle (gear ring + 4 inward blue triangles).
 *  - bottom-left: green circular HP gauge with the HP number (turns red when low).
 *  - bottom-right: X special button with a circular cooldown ring, and a B attack
 *                  button with ammo count + cyan reload bar.
 * The active borg's real `bn<code>` name banner can be shown (optional slot).
 *
 * Drive it with update(state); nothing animates on its own except the reticle/
 * gear CSS spins.
 */

import { el, clamp01 } from "../dom.js";
import { ASSETS, borgBannerPath } from "../assets.js";

export interface HudState {
  /** Remaining ally GF-energy (sum of alive ally borg energy). */
  allyEnergy: number;
  /** Ally GF-energy at battle start (full bar). */
  allyMax: number;
  /** Remaining enemy GF-energy. */
  enemyEnergy: number;
  /** Enemy GF-energy at battle start. */
  enemyMax: number;
  /** Active borg current HP. */
  hp: number;
  /** Active borg max HP (for the gauge fill). */
  maxHp: number;
  /** Ammo count shown on the B prompt. */
  ammo: number;
  /** Reload/charge progress 0..1 (cyan bar on B). */
  reload01: number;
  /** Special cooldown progress 0..1 (ring on X; 1 = ready). */
  cooldown01: number;
  /** Active borg id (for the name banner art). */
  borgId: string;
  /** Whether the lock-on reticle is visible. */
  lockOn: boolean;
  /** Remaining battle timer frames, or null when untimed. */
  timeRemainingFrames?: number | null;
  /** Optional: show the yellow "!" alert. Defaults to false. */
  alert?: boolean;
}

export interface BattleHudOptions {
  /** Show the active borg's `bn<code>` name banner (top-center). Default false. */
  showBanner?: boolean;
  /** Treat HP at or below this fraction of max as "critical" (red). Default 0.25. */
  criticalFraction?: number;
}

export interface BattleHudHandle {
  update: (state: HudState) => void;
  destroy: () => void;
}

const NS = "http://www.w3.org/2000/svg";
const ASCII_CELL = 8;

function svgEl<K extends keyof SVGElementTagNameMap>(
  tag: K,
  attrs: Record<string, string | number>,
): SVGElementTagNameMap[K] {
  const node = document.createElementNS(NS, tag);
  for (const [k, v] of Object.entries(attrs)) node.setAttribute(k, String(v));
  return node;
}

function bitmapText(className: string): HTMLSpanElement {
  const node = el("span", { class: `gf-bitmap-text ${className}` });
  node.setAttribute("aria-hidden", "true");
  return node;
}

function setBitmapText(node: HTMLElement, value: string): void {
  node.replaceChildren(
    ...[...value.toUpperCase()].map((char) => {
      if (char === " ") return el("span", { class: "gf-bitmap-space" });
      // ascii.tpl atlas is ASCII-ordered from 0x20 (space), 16 glyphs per row, 8px cells:
      // row0 punctuation, row1 digits, rows2-3 uppercase, rows4-5 lowercase.
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

/** A C-shaped ring gauge (used for HP and X cooldown). Returns the arc + a setter. */
function ringGauge(
  size: number,
  color: string,
  track: string,
): { node: SVGSVGElement; set: (p01: number) => void } {
  const r = size / 2 - 6;
  const c = 2 * Math.PI * r;
  const svg = svgEl("svg", { viewBox: `0 0 ${size} ${size}`, width: size, height: size });
  svg.appendChild(svgEl("circle", { cx: size / 2, cy: size / 2, r, fill: "none", stroke: track, "stroke-width": 6 }));
  const arc = svgEl("circle", {
    cx: size / 2,
    cy: size / 2,
    r,
    fill: "none",
    stroke: color,
    "stroke-width": 6,
    "stroke-linecap": "round",
    "stroke-dasharray": c,
    "stroke-dashoffset": 0,
    transform: `rotate(-90 ${size / 2} ${size / 2})`,
  });
  svg.appendChild(arc);
  return {
    node: svg,
    set: (p01: number) => arc.setAttribute("stroke-dashoffset", String(c * (1 - clamp01(p01)))),
  };
}

export function createBattleHud(container: HTMLElement, opts: BattleHudOptions = {}): BattleHudHandle {
  const critFrac = opts.criticalFraction ?? 0.25;
  const root = el("div", { class: "gf-hud" });

  // ----- energy meters -----
  const allyFill = el("div", { class: "gf-meter-fill" });
  const allyTab = el("span", { class: "gf-meter-tab" }, [bitmapText("gf-meter-tab-text")]);
  const allyMeter = el("div", { class: "gf-meter gf-meter-ally" }, [
    allyTab,
    el("div", { class: "gf-meter-track" }, [allyFill, el("span", { class: "gf-meter-name" }, [bitmapText("gf-meter-label-text")])]),
  ]);

  const enemyFill = el("div", { class: "gf-meter-fill" });
  const enemyTab = el("span", { class: "gf-meter-tab" }, [bitmapText("gf-meter-tab-text")]);
  const enemyMeter = el("div", { class: "gf-meter gf-meter-enemy" }, [
    enemyTab,
    el("div", { class: "gf-meter-track" }, [enemyFill, el("span", { class: "gf-meter-name" }, [bitmapText("gf-meter-label-text")])]),
  ]);

  const meters = el("div", { class: "gf-hud-meters" }, [allyMeter, enemyMeter]);
  root.appendChild(meters);

  const alert = el("div", { class: "gf-hud-alert gf-hidden", text: "!" });
  root.appendChild(alert);

  const timerText = bitmapText("gf-hud-timer-text");
  const timer = el("div", { class: "gf-hud-timer gf-hidden" }, [timerText]);
  root.appendChild(timer);

  // ----- optional name banner -----
  let bannerImg: HTMLImageElement | null = null;
  if (opts.showBanner) {
    bannerImg = el("img", {
      attrs: { alt: "", "aria-hidden": "true" },
      style: { position: "absolute", top: "8px", left: "50%", transform: "translateX(-50%)", height: "28px", imageRendering: "pixelated" },
    }) as HTMLImageElement;
    bannerImg.addEventListener("error", () => (bannerImg!.style.visibility = "hidden"));
    root.appendChild(bannerImg);
  }

  // ----- lock-on reticle -----
  const reticle = el("div", { class: "gf-hud-reticle gf-hidden" });
  reticle.appendChild(el("div", { class: "gf-reticle-ring" }));
  // four inward-pointing triangles
  const triPos: Array<Partial<CSSStyleDeclaration>> = [
    { top: "2px", left: "50%", transform: "translateX(-50%)", borderLeft: "8px solid transparent", borderRight: "8px solid transparent", borderTop: "12px solid currentColor" },
    { bottom: "2px", left: "50%", transform: "translateX(-50%)", borderLeft: "8px solid transparent", borderRight: "8px solid transparent", borderBottom: "12px solid currentColor" },
    { left: "2px", top: "50%", transform: "translateY(-50%)", borderTop: "8px solid transparent", borderBottom: "8px solid transparent", borderLeft: "12px solid currentColor" },
    { right: "2px", top: "50%", transform: "translateY(-50%)", borderTop: "8px solid transparent", borderBottom: "8px solid transparent", borderRight: "12px solid currentColor" },
  ];
  for (const p of triPos) reticle.appendChild(el("span", { class: "gf-reticle-tri", style: p }));
  root.appendChild(reticle);

  // ----- HP gauge (bottom-left) -----
  const hpGauge = ringGauge(60, "#46c828", "rgba(0,0,0,0.4)");
  const hpNum = bitmapText("gf-hp-num");
  const hpWrap = el("div", { class: "gf-hud-hp" }, [
    el("img", { class: "gf-hp-face-marker", attrs: { src: ASSETS.faceMarkerRoundel, alt: "", "aria-hidden": "true" } }),
    el("div", { class: "gf-hp-ring" }, [hpGauge.node]),
    hpNum,
  ]);
  root.appendChild(hpWrap);

  // ----- weapon prompts (bottom-right) -----
  const cooldown = ringGauge(56, "#cfd3da", "rgba(0,0,0,0.35)");
  const weaponX = el("div", { class: "gf-weapon-x" }, [
    el("div", { class: "gf-cooldown-ring" }, [cooldown.node]),
    el("div", { class: "gf-x-glyph" }, [bitmapText("gf-button-letter")]),
  ]);

  const bReload = el("div", { class: "gf-b-reload", style: { width: "0%" } });
  const bAmmo = bitmapText("gf-b-ammo");
  const weaponB = el("div", { class: "gf-weapon-b" }, [
    el("div", { class: "gf-b-track" }, [bReload, bAmmo]),
    el("div", { class: "gf-b-glyph" }, [bitmapText("gf-button-letter")]),
  ]);

  root.appendChild(el("div", { class: "gf-hud-weapon" }, [weaponX, weaponB]));

  container.appendChild(root);
  setBitmapText(allyMeter.querySelector(".gf-meter-label-text") as HTMLElement, "ALLY");
  setBitmapText(enemyMeter.querySelector(".gf-meter-label-text") as HTMLElement, "ENEMY");
  setBitmapText(weaponX.querySelector(".gf-button-letter") as HTMLElement, "X");
  setBitmapText(weaponB.querySelector(".gf-button-letter") as HTMLElement, "B");

  function setMeter(fill: HTMLElement, tab: HTMLElement, value: number, max: number): void {
    const frac = max > 0 ? clamp01(value / max) : 0;
    fill.style.transform = `scaleX(${frac})`;
    const text = tab.querySelector(".gf-bitmap-text") as HTMLElement | null;
    if (text) setBitmapText(text, String(Math.max(0, Math.round(value))));
  }

  function update(s: HudState): void {
    setMeter(allyFill, allyTab, s.allyEnergy, s.allyMax);
    setMeter(enemyFill, enemyTab, s.enemyEnergy, s.enemyMax);

    alert.classList.toggle("gf-hidden", !s.alert);
    const hasTimer = s.timeRemainingFrames !== undefined && s.timeRemainingFrames !== null;
    timer.classList.toggle("gf-hidden", !hasTimer);
    if (hasTimer) setBitmapText(timerText, formatFramesAsClock(s.timeRemainingFrames ?? 0));

    reticle.classList.toggle("gf-hidden", !s.lockOn);

    const hpFrac = s.maxHp > 0 ? clamp01(s.hp / s.maxHp) : 0;
    hpGauge.set(hpFrac);
    setBitmapText(hpNum, String(Math.max(0, Math.round(s.hp))));
    const critical = hpFrac <= critFrac;
    hpWrap.classList.toggle("gf-critical", critical);
    hpGauge.node.querySelector("circle:nth-child(2)")?.setAttribute("stroke", critical ? "#e8231b" : "#46c828");

    cooldown.set(s.cooldown01);
    bReload.style.width = `${clamp01(s.reload01) * 100}%`;
    setBitmapText(bAmmo, String(Math.max(0, Math.round(s.ammo))));

    if (bannerImg && s.borgId) {
      bannerImg.style.visibility = "visible";
      bannerImg.src = borgBannerPath(s.borgId);
    }
  }

  return {
    update,
    destroy: () => root.remove(),
  };
}

function formatFramesAsClock(frames: number): string {
  const seconds = Math.max(0, Math.ceil(frames / 60));
  const minutes = Math.floor(seconds / 60);
  const rest = seconds % 60;
  return `${minutes}:${String(rest).padStart(2, "0")}`;
}
