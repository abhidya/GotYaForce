/**
 * BattleHud — the in-battle HUD, rebuilt 1:1 against the real Dolphin captures
 * `apps/game/reference/captures/challenge-8-in-battle-hud.png` (normal state)
 * and `challenge-9-battle-critical-hp.png` (critical state).
 *
 * Layout model: everything is authored on a 640x480 design stage (the game's
 * native frame) and the whole stage is scaled to the container with a
 * ResizeObserver, so each element below can be placed at the exact pixel
 * position measured from the captures (measured % of frame in comments).
 *
 * Real extracted art used:
 *  - ascii.tpl bold glyph block (`/ui/tpl/ascii/image_00_IA4.png`) for every
 *    HUD label/number, tinted per element like the game's vertex-colored font
 *    quads (mint ally number, pink enemy number, yellow ALLY/ENEMY, chunky
 *    yellow-green HP/ammo digits, black button letters).
 *  - `bn<code>` name banner (optional slot, real per-borg plate).
 * Per research/asset-inventory/ui-hud-assets.md + public/ui/hud/manifest.json
 * the meter frames, gauge rings, button discs, gear and reticle are GAME-DRAWN
 * GX geometry with no source sprite, so they are rebuilt as vector geometry
 * matched to the captures (colors/shape measured). See
 * research/game-design/HUD-FIDELITY-PLAN.md for the full measurement table.
 *
 * Elements (challenge-8 measurements, % of 640x480 frame):
 *  - GF-energy meters top-left→center: green ally bar (left-anchored, fixed
 *    torn-zigzag lead-in on its left) over red enemy bar (right-anchored,
 *    fixed black torn zigzag on its right); "300 ALLY" arrow tab above,
 *    "ENEMY 1267" arrow tab below.
 *  - yellow "!" alert roundel right of the ally tab.
 *  - dark gear + cyan ring top-right: the Power Burst gauge (re-identified
 *    2026-07-03 from the captures — see the BURST GEAR block), with the TUNED
 *    boost-fuel readout demoted to a small secondary arc in the gear hub.
 *  - green ring HP gauge + chunky digits bottom-left; red capsule variant when
 *    critical (challenge-9).
 *  - bottom-right: X special prompt with dashed cooldown ring, cyan reload
 *    pill + ammo digits + white B disc over a dark-red arc.
 * Lock-on is a world-space marker owned by battleScene (not drawn here).
 */

import { ASSETS, borgBannerPath } from "../assets.js";
import { bitmapText, setBitmapText } from "../bitmapText.js";
import { el, clamp01 } from "../dom.js";

/** Native GameCube frame the HUD is authored against. */
const FRAME_W = 640;
const FRAME_H = 480;

export interface TeammateMarker {
  /** Short plate label, e.g. "CPU" or "ALLY". */
  label: string;
  /** Teammate HP fraction 0..1 (green segment of the mini bar). */
  hp01: number;
  /** Normalized screen position of the plate (0..1 of frame width/height). */
  x01: number;
  y01: number;
}

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
  /** Ammo count shown next to the B prompt. */
  ammo: number;
  /** Reload/charge progress 0..1 (cyan pill under the ammo count). */
  reload01: number;
  /** Special cooldown progress 0..1 (dashed ring on X; 1 = ready). */
  cooldown01: number;
  /** Active borg id (for the name banner art). */
  borgId: string;
  /** Lock-on flag (world-space reticle is drawn by battleScene, not the HUD). */
  lockOn: boolean;
  /** Remaining battle timer frames, or null when untimed. */
  timeRemainingFrames?: number | null;
  /** Optional: show the yellow "!" alert roundel. Defaults to false. */
  alert?: boolean;
  /**
   * Optional boost/dash fuel 0..1. DEMOTED to a small secondary arc inside the top-right gear
   * (2026-07-03): the gear's big cyan ring is the Power Burst gauge (see burst01) per capture
   * re-examination — challenge-8 shows the ring only part-filled while the borg stands GROUNDED
   * (boost fuel refills on landing, so a fuel reading would be full), and challenge-9 (late
   * battle, heavy inflicted damage) shows it complete, matching the manual/StrategyWiki
   * "circle fills with inflicted damage" burst description. boostFuel itself stays TUNED
   * (movement.ts drain/refill, no ROM timing).
   */
  boost01?: number;
  /**
   * Optional Power Burst gauge 0..1 (the big cyan ring in the top-right gear). Q4 RESOLVED
   * (research/decomp/attack-mechanics-open-questions.md Q4, findings §S): per-player meter,
   * ROM player struct +0x126 over +0x124 max (BURST.METER_MAX = 3000), +50 per attacker hit
   * connection. Undefined = empty.
   */
  burst01?: number;
  /**
   * Optional Power Burst "charged" flag (ROM player struct +0x103 — flips one frame AFTER the
   * meter reaches max, Q4/findings §S). Flashes the burst ring bright as the "press Y when the
   * burst gauge is at max" cue (official NA manual, behavior-notes (ao), CONFIRMED_MANUAL).
   */
  burstCharged?: boolean;
  /**
   * Optional DEFEATED banner flag: the local player's active borg is dead/absent while awaiting
   * redeploy, or the battle is lost (presentation.ts battleHudState). Placement/styling is
   * TUNED — no capture of the real banner exists yet (see HUD-FIDELITY-PLAN.md follow-ups).
   */
  defeated?: boolean;
  /**
   * Optional player tag ("1P"/"2P") for future multi-viewport work. Hidden when undefined
   * (the single-viewport captures show no player tag). Placement TUNED — no 2P quadrant-HUD
   * capture exists yet.
   */
  playerLabel?: string;
  /**
   * Optional hold-B charge gauge 0..1 (small meter by the ammo/cooldown block).
   * Sourced from the TUNED `chargeFrames` accumulator (combat.ts stepAttacks) over the
   * charge cap; only non-zero while the player is holding B to charge a shot. 0/absent = hidden.
   */
  charge01?: number;
  /**
   * Optional "melee/battle mode" flag: true when the focus borg's locked enemy is within melee
   * reach. Per the NA instruction manual (behavior-notes (ao)) the target cursor flips
   * yellow -> red in this state. The world-space reticle color is driven by battleScene; this
   * field just surfaces the same sim signal on the HudState. Defaults to false.
   */
  meleeRange?: boolean;
  /**
   * Optional X-attack ("X Bullets") ammo count, shown next to the X prompt. Per the NA
   * instruction manual (behavior-notes (ao), CONFIRMED_MANUAL) the game keeps SEPARATE B and X
   * ammo counters: weapon 0 = B-attack ammo (see `ammo`), weapon 1 = X-attack ammo. Sourced from
   * the focus borg's weapon cell 1 (combat.ts consumes it on the X/special attack). Undefined =
   * this borg has no X-ammo (cell max 0, cooldown-only special) -> the X-ammo readout stays
   * hidden. Back-compatible/optional like charge01/meleeRange.
   */
  xAmmo?: number;
  /** Optional X-ammo fill 0..1 (weapon cell 1 cur/max); paired with `xAmmo`. Undefined = hidden. */
  xReload01?: number;
  /**
   * Optional Jump Gauge: max mid-air jumps for the focus borg (CONFIRMED_MANUAL, behavior-notes
   * (ao): "a Jump Gauge showing multi-level jumps"). Undefined = borg has no air jumps or is a
   * sustained-flight flyer (covered by the boost gauge) -> the pips stay hidden. Back-compatible.
   */
  jumpsMax?: number;
  /** Optional mid-air jumps REMAINING (0..jumpsMax); paired with `jumpsMax`. Undefined = hidden. */
  jumpsRemaining?: number;
  /** Optional floating teammate plates ("CPU"/"ALLY" + mini HP bar). */
  teammates?: readonly TeammateMarker[];
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

// HUD font tints sampled from challenge-8/-9 captures.
const TINT_ALLY_NUM = "#c8ffd4"; // mint "300"
const TINT_ENEMY_NUM = "#ff9ed8"; // pink "1267"
const TINT_LABEL = "#ffd428"; // yellow "ALLY"/"ENEMY"
const TINT_DIGITS = "#cde23c"; // chunky yellow-green HP/ammo digits
const TINT_BLACK = "#161616"; // button letters / "!"

function svgEl<K extends keyof SVGElementTagNameMap>(
  tag: K,
  attrs: Record<string, string | number>,
): SVGElementTagNameMap[K] {
  const node = document.createElementNS(NS, tag);
  for (const [k, v] of Object.entries(attrs)) node.setAttribute(k, String(v));
  return node;
}

/** Horizontal torn/zigzag path from x0..x1 around centerline y. */
function zigzagPath(x0: number, y: number, x1: number, amp: number, period: number): string {
  let d = `M ${x0} ${y}`;
  let up = true;
  for (let x = x0 + period / 2; x < x1; x += period / 2) {
    d += ` L ${x.toFixed(1)} ${(up ? y - amp : y + amp).toFixed(1)}`;
    up = !up;
  }
  d += ` L ${x1} ${y}`;
  return d;
}

/** Absolutely positioned bitmap-text span on the 640x480 stage. */
function hudText(className: string, left: number, top: number): HTMLSpanElement {
  const node = bitmapText(`gf-hud-text ${className}`);
  node.style.left = `${left}px`;
  node.style.top = `${top}px`;
  return node;
}

export function createBattleHud(container: HTMLElement, opts: BattleHudOptions = {}): BattleHudHandle {
  const critFrac = opts.criticalFraction ?? 0.25;
  const root = el("div", { class: "gf-hud" });

  // One full-frame vector layer for all game-drawn geometry.
  const svg = svgEl("svg", {
    class: "gf-hud-vector",
    viewBox: `0 0 ${FRAME_W} ${FRAME_H}`,
    preserveAspectRatio: "none",
    "aria-hidden": "true",
  });
  root.appendChild(svg);

  // ======================= GF-ENERGY METERS (top-left) =======================
  // challenge-8: ally fill track x 80..293 (12.5%..45.8%W), y 37..50 (7.7%..10.4%H)
  const ALLY_X = 80;
  const ALLY_W = 213;
  // enemy fill right-anchored at x 226 (35.3%W), full length 198, y 59..71 (12.3%..14.8%H)
  const ENEMY_RIGHT = 226;
  const ENEMY_W = 198;

  // Fixed torn lead-in left of the ally bar: x 29..80 (4.5%..12.5%W), centerline y 43.
  svg.appendChild(
    svgEl("path", { d: zigzagPath(29, 43, 80, 5, 12), fill: "none", stroke: "#33261a", "stroke-width": 4 }),
  );
  // Ally track shadow (thin dark line under the green fill, visible when depleted).
  svg.appendChild(svgEl("rect", { x: ALLY_X, y: 46, width: ALLY_W + 4, height: 6, fill: "rgba(0,0,0,0.42)" }));
  // Ally fill: two-tone green (top half lighter), left-anchored, depletes from the right.
  const allyFillHi = svgEl("rect", { x: ALLY_X, y: 37, width: ALLY_W, height: 7, fill: "#8aff54" });
  const allyFillLo = svgEl("rect", { x: ALLY_X, y: 44, width: ALLY_W, height: 6, fill: "#2ce518" });
  svg.appendChild(allyFillHi);
  svg.appendChild(allyFillLo);

  // Fixed black torn zigzag between the rows: x 226..294 (35.3%..45.9%W), y ~55..62.
  svg.appendChild(
    svgEl("path", { d: zigzagPath(226, 60, 294, 6, 13), fill: "none", stroke: "#0e0e0e", "stroke-width": 5 }),
  );
  // Enemy fill: two-tone red, right-anchored at x 226, depletes from the left.
  const enemyFillHi = svgEl("rect", { x: ENEMY_RIGHT - ENEMY_W, y: 59, width: ENEMY_W, height: 6, fill: "#ff7a52" });
  const enemyFillLo = svgEl("rect", { x: ENEMY_RIGHT - ENEMY_W, y: 65, width: ENEMY_W, height: 6, fill: "#f2200a" });
  svg.appendChild(enemyFillHi);
  svg.appendChild(enemyFillLo);

  // --- Ally tab "300 < ALLY": x 186..298 (29.1%..46.5%W), y 8..30 (1.7%..6.3%H) ---
  svg.appendChild(
    svgEl("polygon", {
      points: "186,19 197,8 298,8 298,30 197,30",
      fill: "#17671f",
      stroke: "#06300a",
      "stroke-width": 2,
    }),
  );
  // Brighter right segment with the left-pointing chevron divider before "ALLY".
  svg.appendChild(svgEl("polygon", { points: "254,8 298,8 298,30 254,30 243,19", fill: "#2f9e33" }));
  const allyNum = hudText("gf-ally-num", 196, 11); // mint number, centered over x 196..242
  const allyLabel = hudText("gf-ally-label", 252, 11);
  root.appendChild(allyNum);
  root.appendChild(allyLabel);
  setBitmapText(allyLabel, "ALLY", { bold: true, scale: 2, advance: 11, tint: TINT_LABEL });

  // --- Enemy tab "ENEMY > 1267": x 27..133 (4.3%..20.8%W), y 78..98 (16.3%..20.4%H) ---
  svg.appendChild(
    svgEl("polygon", {
      points: "27,78 120,78 133,88 120,98 27,98",
      fill: "#801b12",
      stroke: "#400a05",
      "stroke-width": 2,
    }),
  );
  svg.appendChild(svgEl("polygon", { points: "84,78 120,78 133,88 120,98 84,98 94,88", fill: "#b52d1c" }));
  const enemyLabel = hudText("gf-enemy-label", 31, 81);
  const enemyNum = hudText("gf-enemy-num", 88, 81);
  root.appendChild(enemyLabel);
  root.appendChild(enemyNum);
  setBitmapText(enemyLabel, "ENEMY", { bold: true, scale: 2, advance: 11, tint: TINT_LABEL });

  // ===================== "!" ALERT (right of the ally tab) ====================
  // challenge-8: yellow roundel center (318, 47) (49.7%W, 9.8%H), dia ~30px.
  const alertG = svgEl("g", { class: "gf-hidden" });
  alertG.appendChild(svgEl("circle", { cx: 318, cy: 47, r: 15, fill: "#ffdf1d", stroke: "#101010", "stroke-width": 3 }));
  alertG.appendChild(svgEl("circle", { cx: 318, cy: 47, r: 11, fill: "none", stroke: "#ffffff", "stroke-width": 2 }));
  svg.appendChild(alertG);
  const alertGlyph = hudText("gf-alert-glyph gf-hidden", 310, 39);
  root.appendChild(alertGlyph);
  setBitmapText(alertGlyph, "!", { bold: true, scale: 2, tint: TINT_BLACK });

  // ========================= TIMER (top-center pill) =========================
  const timerText = bitmapText("gf-hud-timer-text");
  const timer = el("div", { class: "gf-hud-timer gf-hidden" }, [timerText]);
  root.appendChild(timer);

  // ============ BURST GEAR (top-right: Power Burst gauge, cyan ring) =========
  // challenge-8: gear center (483, 48) (75.5%W, 10.0%H), outer dia ~70px.
  // RE-IDENTIFIED 2026-07-03 (was "boost gauge"): the big cyan ring is the Power Burst gauge.
  // Capture evidence — challenge-8 shows the ring only ~20-25% filled, anchored at the BOTTOM
  // of the gear, while the borg stands GROUNDED (boost fuel refills on landing, so a fuel ring
  // would read full); challenge-9 (late battle, heavy inflicted damage, enemy 1267 -> 564)
  // shows the ring complete. That matches the official manual / StrategyWiki description of
  // the burst gauge as a circle that fills with inflicted damage (behavior-notes (ao),
  // CONFIRMED_MANUAL: "press Y when the burst gauge is at max"), and the ported per-player
  // meter (Q4 RESOLVED — findings §S: +0x126 / +0x124 max 3000, +50 per attacker hit).
  // Fill starts at 6 o'clock per the challenge-8 arc position (rotate 90); the fill DIRECTION
  // (cw vs ccw) is unmeasurable from a single frame — clockwise is TUNED.
  const gearG = svgEl("g", { transform: "translate(483 48)", opacity: 0.85 });
  for (let i = 0; i < 8; i++) {
    gearG.appendChild(
      svgEl("rect", { x: -7, y: -38, width: 14, height: 12, rx: 2.5, fill: "#1d1d1d", transform: `rotate(${i * 45})` }),
    );
  }
  gearG.appendChild(svgEl("circle", { r: 31, fill: "#1d1d1d" }));
  gearG.appendChild(svgEl("circle", { r: 22, fill: "#0c0c0c" }));
  svg.appendChild(gearG);
  const BURST_R = 15;
  const BURST_C = 2 * Math.PI * BURST_R;
  const burstArc = svgEl("circle", {
    cx: 483,
    cy: 48,
    r: BURST_R,
    fill: "none",
    stroke: "#3fe8c4",
    "stroke-width": 7,
    "stroke-dasharray": BURST_C,
    "stroke-dashoffset": BURST_C,
    transform: "rotate(90 483 48)",
  });
  svg.appendChild(burstArc);

  // Boost fuel, DEMOTED to a small secondary arc INSIDE the gear hub (the space left of the
  // burst ring). TUNED placement — the captures show no separate boost element (the gear hub
  // reads empty at rest), so this indicator is shown ONLY while fuel is actually draining/
  // refilling (boost01 < 1) and hidden at rest to keep the at-rest HUD capture-faithful.
  // boostFuel itself is a TUNED cooldown (movement.ts), not a ROM-timed value.
  const BOOST_R = 7;
  const BOOST_C = 2 * Math.PI * BOOST_R;
  const boostArc = svgEl("circle", {
    cx: 483,
    cy: 48,
    r: BOOST_R,
    fill: "none",
    stroke: "#2a9c86",
    "stroke-width": 3,
    "stroke-dasharray": BOOST_C,
    "stroke-dashoffset": 0,
    transform: "rotate(-90 483 48)",
    class: "gf-hidden",
  });
  svg.appendChild(boostArc);

  // ===================== JUMP GAUGE (multi-level jump pips) ===================
  // CONFIRMED_MANUAL (behavior-notes (ao)): "a Jump Gauge showing multi-level jumps". A short row
  // of pips under the boost gear — one per max air jump (airJumpLevel), lit for jumps remaining,
  // dim for spent. Whole group hidden unless HudState.jumpsMax is defined (air-jumpers only;
  // sustained-flight flyers use the boost gauge). Capped at MAX_JUMP_PIPS so the row never
  // overflows; a borg with more levels than that still reads "full" at the cap.
  const MAX_JUMP_PIPS = 4;
  const JUMP_PIP_R = 3.2;
  const JUMP_PIP_GAP = 10;
  const jumpG = svgEl("g", { class: "gf-hidden" });
  const jumpPips: SVGElement[] = [];
  for (let i = 0; i < MAX_JUMP_PIPS; i++) {
    const pip = svgEl("circle", {
      cx: 483 - ((MAX_JUMP_PIPS - 1) * JUMP_PIP_GAP) / 2 + i * JUMP_PIP_GAP,
      cy: 74,
      r: JUMP_PIP_R,
      fill: "#3fe8c4",
    });
    jumpPips.push(pip);
    jumpG.appendChild(pip);
  }
  svg.appendChild(jumpG);

  // ===================== optional real bn<code> name banner ===================
  let bannerImg: HTMLImageElement | null = null;
  if (opts.showBanner) {
    bannerImg = el("img", {
      class: "gf-hud-banner",
      attrs: { alt: "", "aria-hidden": "true" },
    }) as HTMLImageElement;
    bannerImg.addEventListener("error", () => (bannerImg!.style.visibility = "hidden"));
    root.appendChild(bannerImg);
  }

  // ================== HP GAUGE (bottom-left ring / red capsule) ==============
  // challenge-8: glossy green ring center (49, 398) (7.7%W, 82.9%H), outer dia ~64px,
  // chunky digits overlapping to the right (digit height ~26px).
  const HP_R = 25;
  const HP_C = 2 * Math.PI * HP_R;
  const hpRingG = svgEl("g", {});
  hpRingG.appendChild(svgEl("circle", { cx: 49, cy: 398, r: 17.5, fill: "rgba(6,36,4,0.5)" }));
  hpRingG.appendChild(
    svgEl("circle", { cx: 49, cy: 398, r: HP_R, fill: "none", stroke: "rgba(10,46,8,0.62)", "stroke-width": 14 }),
  );
  const hpArc = svgEl("circle", {
    cx: 49,
    cy: 398,
    r: HP_R,
    fill: "none",
    stroke: "#35d41c",
    "stroke-width": 14,
    "stroke-dasharray": HP_C,
    "stroke-dashoffset": 0,
    transform: "rotate(-90 49 398)",
  });
  hpRingG.appendChild(hpArc);
  // Dark rim + white specular highlight (the ring reads glossy in the capture).
  hpRingG.appendChild(svgEl("circle", { cx: 49, cy: 398, r: 32.5, fill: "none", stroke: "#10380a", "stroke-width": 2.5 }));
  hpRingG.appendChild(svgEl("circle", { cx: 49, cy: 398, r: 17.5, fill: "none", stroke: "#10380a", "stroke-width": 2 }));
  hpRingG.appendChild(
    svgEl("circle", {
      cx: 49,
      cy: 398,
      r: 29,
      fill: "none",
      stroke: "rgba(255,255,255,0.55)",
      "stroke-width": 4,
      "stroke-linecap": "round",
      "stroke-dasharray": `24 ${HP_C * 2}`,
      transform: "rotate(150 49 398)",
    }),
  );
  svg.appendChild(hpRingG);

  // Critical capsule (challenge-9): red pill x 26..141 (4.1%..22.0%W), y 405..430 (84.4%..89.5%H).
  const hpCritG = svgEl("g", { class: "gf-hidden" });
  hpCritG.appendChild(
    svgEl("rect", { x: 26, y: 405, width: 115, height: 25, rx: 12.5, fill: "#e8341a", stroke: "#6d0f06", "stroke-width": 2.5 }),
  );
  hpCritG.appendChild(svgEl("rect", { x: 38, y: 409, width: 94, height: 6, rx: 3, fill: "rgba(255,255,255,0.28)" }));
  hpCritG.appendChild(svgEl("circle", { cx: 43, cy: 417.5, r: 13, fill: "none", stroke: "#b0220f", "stroke-width": 6 }));
  hpCritG.appendChild(svgEl("rect", { x: 50, y: 414, width: 13, height: 7, fill: "#ffd428" }));
  svg.appendChild(hpCritG);

  const hpNum = hudText("gf-hp-num", 60, 384); // digits start x ~60 (9.4%W), cap-height 24px
  root.appendChild(hpNum);

  // ============== WEAPON PROMPTS (bottom-right: X ring, B + reload) ==========
  // X special: button center (600, 355) (93.8%W, 74.0%H), dashed cooldown ring dia ~48px.
  const DASH_R = 24;
  const dashRing = svgEl("circle", {
    cx: 600,
    cy: 355,
    r: DASH_R,
    fill: "none",
    stroke: "#8a8071",
    "stroke-width": 5,
    "stroke-dasharray": "5 7.57",
  });
  svg.appendChild(dashRing);
  const dashReady = svgEl("circle", {
    cx: 600,
    cy: 355,
    r: DASH_R,
    fill: "none",
    stroke: "#f5f0e2",
    "stroke-width": 5,
    "stroke-dasharray": "5 7.57",
    opacity: 0,
  });
  svg.appendChild(dashReady);
  svg.appendChild(svgEl("circle", { cx: 600, cy: 355, r: 13.5, fill: "#f2f2f2", stroke: "#101010", "stroke-width": 2 }));
  svg.appendChild(svgEl("circle", { cx: 596, cy: 350.5, r: 4.5, fill: "rgba(255,255,255,0.85)" }));
  const xLetter = hudText("gf-button-letter", 592, 347);
  root.appendChild(xLetter);
  setBitmapText(xLetter, "X", { bold: true, scale: 2, tint: TINT_BLACK });

  // ===================== X-AMMO READOUT ("X Bullets") =========================
  // Separate B/X ammo counters are OFFICIAL (behavior-notes (ao), CONFIRMED_MANUAL): weapon 0 =
  // B-attack ammo (the reload pill + ammoNum above the B disc), weapon 1 = X-attack ammo. This is
  // a small companion readout by the X disc — a short cyan fill pill + a digit — mirroring the
  // B-ammo pill/digit style. Hidden (whole group) unless HudState.xAmmo is defined, i.e. only for
  // borgs whose weapon cell 1 has ammo (max>0); cooldown-only specials show nothing here, keeping
  // the HUD unchanged for them.
  const xAmmoG = svgEl("g", { class: "gf-hidden" });
  xAmmoG.appendChild(
    svgEl("rect", { x: 626, y: 349, width: 48, height: 12, rx: 6, fill: "rgba(8,42,40,0.55)", stroke: "rgba(0,0,0,0.4)", "stroke-width": 1.5 }),
  );
  const X_RELOAD_W = 44;
  const xReloadFill = svgEl("rect", { x: 628, y: 351, width: X_RELOAD_W, height: 8, rx: 4, fill: "#3fe8cf" });
  xAmmoG.appendChild(xReloadFill);
  svg.appendChild(xAmmoG);
  const xAmmoNum = hudText("gf-xammo-num", 638, 322);
  root.appendChild(xAmmoNum);

  // Dark-red arc swooshing under the B disc: from (487,448) to (585,420).
  svg.appendChild(
    svgEl("path", {
      d: "M 487 448 Q 560 456 585 420",
      fill: "none",
      stroke: "#8c1710",
      "stroke-width": 8,
      "stroke-linecap": "round",
    }),
  );
  // Cyan reload pill: x 486..566 (76.0%..88.4%W), y 413..429 (86.0%..89.3%H).
  svg.appendChild(
    svgEl("rect", { x: 486, y: 413, width: 80, height: 16, rx: 8, fill: "rgba(8,42,40,0.55)", stroke: "rgba(0,0,0,0.4)", "stroke-width": 1.5 }),
  );
  const RELOAD_W = 76;
  const reloadFill = svgEl("rect", { x: 488, y: 415, width: RELOAD_W, height: 12, rx: 6, fill: "#3fe8cf" });
  const reloadHi = svgEl("rect", { x: 490, y: 416.5, width: RELOAD_W - 4, height: 3.5, rx: 1.75, fill: "rgba(255,255,255,0.6)" });
  svg.appendChild(reloadFill);
  svg.appendChild(reloadHi);
  // White B disc: center (565, 435) (88.3%W, 90.6%H), dia ~28px.
  svg.appendChild(svgEl("circle", { cx: 565, cy: 435, r: 14, fill: "#f2f2f2", stroke: "#101010", "stroke-width": 2 }));
  svg.appendChild(svgEl("circle", { cx: 561, cy: 430.5, r: 4.5, fill: "rgba(255,255,255,0.85)" }));
  const bLetter = hudText("gf-button-letter", 557, 427);
  root.appendChild(bLetter);
  setBitmapText(bLetter, "B", { bold: true, scale: 2, tint: TINT_BLACK });
  // Ammo digits above the pill's right half: "5" center ~ (518, 398) (81%W, 83%H).
  const ammoNum = hudText("gf-ammo-num", 506, 380);
  root.appendChild(ammoNum);

  // ===================== CHARGE GAUGE (hold-B charge meter) ==================
  // TUNED-faithful-to-sim: reads the `chargeFrames` accumulator (a TUNED hold-B counter, no
  // ROM value) surfaced as HudState.charge01. Reuses the reload-pill gauge style (filled bar +
  // specular). Placed just above the reload pill so it reads as a second, distinct meter, and is
  // shown only while actually charging (charge01 > 0). Behavior-notes (ao): "hold B to fill, at
  // max release for super".
  const chargeG = svgEl("g", { class: "gf-hidden" });
  chargeG.appendChild(
    svgEl("rect", { x: 486, y: 393, width: 80, height: 12, rx: 6, fill: "rgba(46,12,42,0.55)", stroke: "rgba(0,0,0,0.4)", "stroke-width": 1.5 }),
  );
  const CHARGE_W = 76;
  const chargeFill = svgEl("rect", { x: 488, y: 395, width: 0, height: 8, rx: 4, fill: "#ffb02e" });
  const chargeHi = svgEl("rect", { x: 490, y: 396, width: 0, height: 2.5, rx: 1.25, fill: "rgba(255,255,255,0.6)" });
  chargeG.appendChild(chargeFill);
  chargeG.appendChild(chargeHi);
  svg.appendChild(chargeG);

  // ======================== DEFEATED banner (center) =========================
  // Shown while HudState.defeated is true (local borg dead/awaiting redeploy, or battle lost —
  // presentation.ts battleHudState). Bold ascii.tpl bitmap text, red-tinted, scale 3 like the
  // chunky HP digits. Placement TUNED: centered on the 640x480 stage ("DEFEATED" = 8 glyphs x
  // 21px advance ≈ 168px wide, 24px tall -> left 236, top 228); no capture of the real banner
  // exists yet (HUD-FIDELITY-PLAN.md capture follow-ups), so both the position and the exact
  // wording/art are stand-ins until one is taken.
  const TINT_DEFEATED = "#ff2f1a"; // TUNED red, echoing the critical-capsule palette
  const defeatedText = hudText("gf-defeated-text gf-hidden", 236, 228);
  root.appendChild(defeatedText);
  setBitmapText(defeatedText, "DEFEATED", { bold: true, scale: 3, advance: 21, tint: TINT_DEFEATED });

  // ================== player tag ("1P"/"2P", multi-viewport slot) ============
  // Hidden unless HudState.playerLabel is set (single-viewport captures show no player tag).
  // Placement TUNED (top-left corner of the viewport quadrant) — no 2P quadrant-HUD capture
  // exists yet; revisit when one is taken (HUD-FIDELITY-PLAN.md capture follow-ups).
  const playerLabelText = hudText("gf-player-label gf-hidden", 8, 8);
  root.appendChild(playerLabelText);

  // ================= floating teammate plates ("CPU" + mini bar) =============
  // challenge-8: "CPU" label x 56..60%W y 21.5..23.5%H, mini bar x 56.2..66%W
  // y 25.2..26.4%H (bar ~63x6px). Positions are supplied per-frame via state.
  const matesLayer = el("div", { class: "gf-hud-mates" });
  root.appendChild(matesLayer);

  container.appendChild(root);

  // ---- scale the 640x480 stage to the container (non-uniform, like the game
  // stretching its frame to the viewport) ----
  function fit(): void {
    const w = container.clientWidth || FRAME_W;
    const h = container.clientHeight || FRAME_H;
    root.style.transform = `scale(${w / FRAME_W}, ${h / FRAME_H})`;
  }
  fit();
  const ro = typeof ResizeObserver !== "undefined" ? new ResizeObserver(fit) : null;
  ro?.observe(container);

  // -------------------------------- update ----------------------------------
  let lastAlly = Number.NaN;
  let lastEnemy = Number.NaN;
  let lastHp = Number.NaN;
  let lastAmmo = Number.NaN;
  let lastXAmmo = Number.NaN;
  let lastPlayerLabel: string | undefined;
  // Burst-charged flash phase, advanced once per HUD update (one sim frame at 60fps). The
  // flash EXISTENCE is the manual's "press Y when the burst gauge is at max" readiness cue
  // (behavior-notes (ao)); its period (8 frames bright / 8 dim) is TUNED — no capture of the
  // charged state exists yet.
  let burstFlashFrame = 0;

  function update(s: HudState): void {
    // GF-energy fills (value-proportional widths, anchored per the captures).
    const allyFrac = s.allyMax > 0 ? clamp01(s.allyEnergy / s.allyMax) : 0;
    const aw = Math.round(ALLY_W * allyFrac);
    allyFillHi.setAttribute("width", String(aw));
    allyFillLo.setAttribute("width", String(aw));
    const enemyFrac = s.enemyMax > 0 ? clamp01(s.enemyEnergy / s.enemyMax) : 0;
    const ew = Math.round(ENEMY_W * enemyFrac);
    enemyFillHi.setAttribute("x", String(ENEMY_RIGHT - ew));
    enemyFillHi.setAttribute("width", String(ew));
    enemyFillLo.setAttribute("x", String(ENEMY_RIGHT - ew));
    enemyFillLo.setAttribute("width", String(ew));

    const allyVal = Math.max(0, Math.round(s.allyEnergy));
    if (allyVal !== lastAlly) {
      lastAlly = allyVal;
      setBitmapText(allyNum, String(allyVal), { bold: true, scale: 2, advance: 12, tint: TINT_ALLY_NUM });
    }
    const enemyVal = Math.max(0, Math.round(s.enemyEnergy));
    if (enemyVal !== lastEnemy) {
      lastEnemy = enemyVal;
      setBitmapText(enemyNum, String(enemyVal), { bold: true, scale: 2, advance: 11, tint: TINT_ENEMY_NUM });
    }

    const showAlert = Boolean(s.alert);
    alertG.classList.toggle("gf-hidden", !showAlert);
    alertGlyph.classList.toggle("gf-hidden", !showAlert);

    const hasTimer = s.timeRemainingFrames !== undefined && s.timeRemainingFrames !== null;
    timer.classList.toggle("gf-hidden", !hasTimer);
    if (hasTimer) {
      setBitmapText(timerText, formatFramesAsClock(s.timeRemainingFrames ?? 0), { bold: true, scale: 2 });
    }

    // HP ring / critical capsule.
    const hpFrac = s.maxHp > 0 ? clamp01(s.hp / s.maxHp) : 0;
    hpArc.setAttribute("stroke-dashoffset", String(HP_C * (1 - hpFrac)));
    const critical = hpFrac <= critFrac;
    hpRingG.classList.toggle("gf-hidden", critical);
    hpCritG.classList.toggle("gf-hidden", !critical);
    hpNum.classList.toggle("gf-critical", critical);
    const hpVal = Math.max(0, Math.round(s.hp));
    if (hpVal !== lastHp) {
      lastHp = hpVal;
      setBitmapText(hpNum, String(hpVal), { bold: true, scale: 3, advance: 21, tint: TINT_DIGITS });
    }

    // Power Burst ring (Q4/findings §S — see the BURST GEAR block above for the capture
    // evidence). Empty when not driven; flashes bright while charged (+0x103 set) as the
    // manual's "press Y when the burst gauge is at max" cue (behavior-notes (ao)).
    const burst = clamp01(s.burst01 ?? 0);
    burstArc.setAttribute("stroke-dashoffset", String(BURST_C * (1 - burst)));
    if (s.burstCharged) {
      burstFlashFrame += 1;
      burstArc.setAttribute("stroke", burstFlashFrame % 16 < 8 ? "#eafff8" : "#3fe8c4");
    } else {
      burstFlashFrame = 0;
      burstArc.setAttribute("stroke", "#3fe8c4");
    }

    // Boost fuel mini-arc (demoted secondary indicator): visible only while fuel is not full,
    // keeping the at-rest gear hub empty like the captures.
    const boost = clamp01(s.boost01 ?? 1);
    boostArc.classList.toggle("gf-hidden", boost >= 1);
    boostArc.setAttribute("stroke-dashoffset", String(BOOST_C * (1 - boost)));

    // Weapon prompts.
    dashReady.setAttribute("opacity", String(clamp01(s.cooldown01)));
    const rw = Math.round(RELOAD_W * clamp01(s.reload01));
    reloadFill.setAttribute("width", String(Math.max(0, rw)));
    reloadHi.setAttribute("width", String(Math.max(0, rw - 4)));
    const ammoVal = Math.max(0, Math.round(s.ammo));
    if (ammoVal !== lastAmmo) {
      lastAmmo = ammoVal;
      setBitmapText(ammoNum, String(ammoVal), { bold: true, scale: 3, advance: 21, tint: TINT_DIGITS });
    }

    // Charge gauge (only visible while holding B to charge; flares white at full = "release super").
    const charge = clamp01(s.charge01 ?? 0);
    chargeG.classList.toggle("gf-hidden", charge <= 0);
    if (charge > 0) {
      const cw = Math.round(CHARGE_W * charge);
      chargeFill.setAttribute("width", String(Math.max(0, cw)));
      chargeHi.setAttribute("width", String(Math.max(0, cw - 4)));
      // At/near full the meter goes bright to cue the super release.
      chargeFill.setAttribute("fill", charge >= 1 ? "#fff2b0" : "#ffb02e");
    }

    // X-ammo readout (behavior-notes (ao): separate B/X counters). Shown only when the focus
    // borg actually has X-ammo (HudState.xAmmo defined = weapon cell 1 max>0); hidden otherwise
    // so cooldown-only specials keep the HUD unchanged.
    const hasXAmmo = s.xAmmo !== undefined;
    xAmmoG.classList.toggle("gf-hidden", !hasXAmmo);
    xAmmoNum.classList.toggle("gf-hidden", !hasXAmmo);
    if (hasXAmmo) {
      const xrw = Math.round(X_RELOAD_W * clamp01(s.xReload01 ?? 0));
      xReloadFill.setAttribute("width", String(Math.max(0, xrw)));
      const xAmmoVal = Math.max(0, Math.round(s.xAmmo ?? 0));
      if (xAmmoVal !== lastXAmmo) {
        lastXAmmo = xAmmoVal;
        setBitmapText(xAmmoNum, String(xAmmoVal), { bold: true, scale: 2, advance: 14, tint: TINT_DIGITS });
      }
    }

    // Jump Gauge pips (behavior-notes (ao)). Shown only for air-jumper borgs (jumpsMax defined);
    // the first `jumpsMax` pips are visible, lit for jumps remaining, dim for spent.
    const hasJump = s.jumpsMax !== undefined && s.jumpsMax >= 1;
    jumpG.classList.toggle("gf-hidden", !hasJump);
    if (hasJump) {
      const shown = Math.min(MAX_JUMP_PIPS, Math.max(0, Math.round(s.jumpsMax ?? 0)));
      const lit = Math.min(shown, Math.max(0, Math.round(s.jumpsRemaining ?? 0)));
      for (let i = 0; i < MAX_JUMP_PIPS; i++) {
        const pip = jumpPips[i];
        if (!pip) continue;
        if (i >= shown) {
          pip.setAttribute("opacity", "0");
        } else {
          pip.setAttribute("opacity", "1");
          pip.setAttribute("fill", i < lit ? "#3fe8c4" : "#22403c");
        }
      }
    }

    // DEFEATED banner (placement TUNED — see the element block above).
    defeatedText.classList.toggle("gf-hidden", !s.defeated);

    // Player tag ("1P"/"2P") — hidden unless supplied (future multi-viewport work).
    const hasPlayerLabel = s.playerLabel !== undefined && s.playerLabel.length > 0;
    playerLabelText.classList.toggle("gf-hidden", !hasPlayerLabel);
    if (hasPlayerLabel && s.playerLabel !== lastPlayerLabel) {
      lastPlayerLabel = s.playerLabel;
      setBitmapText(playerLabelText, s.playerLabel ?? "", { bold: true, scale: 2, advance: 12, tint: TINT_LABEL });
    }

    // Floating teammate plates.
    syncTeammates(matesLayer, s.teammates ?? []);

    if (bannerImg && s.borgId) {
      bannerImg.style.visibility = "visible";
      bannerImg.src = borgBannerPath(s.borgId);
    }
  }

  return {
    update,
    destroy: () => {
      ro?.disconnect();
      root.remove();
    },
  };
}

/** Reconcile the floating "CPU"/"ALLY" plates against the current state. */
function syncTeammates(layer: HTMLElement, mates: readonly TeammateMarker[]): void {
  while (layer.childElementCount > mates.length) layer.lastElementChild?.remove();
  while (layer.childElementCount < mates.length) {
    const roundel = el("img", {
      class: "gf-mate-roundel",
      attrs: { src: ASSETS.faceMarkerRoundel, alt: "", "aria-hidden": "true" },
    });
    const label = bitmapText("gf-mate-label");
    const fill = el("div", { class: "gf-mate-fill" });
    const bar = el("div", { class: "gf-mate-bar" }, [fill]);
    layer.appendChild(el("div", { class: "gf-mate" }, [roundel, label, bar]));
  }
  mates.forEach((mate, i) => {
    const plate = layer.children[i] as HTMLElement;
    plate.style.left = `${(mate.x01 * FRAME_W).toFixed(1)}px`;
    plate.style.top = `${(mate.y01 * FRAME_H).toFixed(1)}px`;
    const label = plate.querySelector(".gf-mate-label") as HTMLElement;
    if (label.getAttribute("aria-label") !== mate.label) {
      setBitmapText(label, mate.label, { bold: true, scale: 2, advance: 12 });
    }
    const fill = plate.querySelector(".gf-mate-fill") as HTMLElement;
    fill.style.width = `${(clamp01(mate.hp01) * 100).toFixed(1)}%`;
  });
}

function formatFramesAsClock(frames: number): string {
  const seconds = Math.max(0, Math.ceil(frames / 60));
  const minutes = Math.floor(seconds / 60);
  const rest = seconds % 60;
  return `${minutes}:${String(rest).padStart(2, "0")}`;
}
