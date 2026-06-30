/**
 * Injectable copy of styles.css for runtime use (no CSS bundler loader needed).
 * GENERATED from styles.css via scripts; keep in sync if you edit the CSS.
 * ui/index.ts ensureStyles() injects this into a <style> tag once per document.
 */

export const GF_UI_CSS = `/*
 * Gotcha Force — shared UI styles for the 1-to-1 recreation component library.
 *
 * All classes are prefixed \`gf-\` to stay scoped. Palette + type feel are pulled
 * from the real captured reference screens in apps/game/reference/captures/.
 * Reference real extracted art via /ui/... public paths (see ASSETS const in TS).
 *
 * Injected automatically by ui/index.ts (ensureStyles); also importable directly
 * by a bundler that handles CSS imports.
 */

:root {
  /* Core palette sampled from the reference captures. */
  --gf-yellow: #ffd21e;          /* SELECT DIFFICULTY title fill */
  --gf-yellow-deep: #f5a800;     /* WIN gold */
  --gf-outline: #2a2150;         /* dark title/text outline (purple-navy) */
  --gf-green: #46c828;           /* ALLY meter / FIGHT ALONE ring / A button */
  --gf-green-deep: #1f8a14;
  --gf-red: #e8231b;             /* ENEMY meter / B button / INSANE pad */
  --gf-red-deep: #a40d0d;
  --gf-blue-pill: #5b9bd5;       /* results row pills */
  --gf-blue-pill-deep: #2f6db0;
  --gf-orange: #ff7a18;          /* TUFF pad / value numbers */
  --gf-cyan: #34e0d8;            /* reload bar */
  --gf-panel: #d9d9d9;           /* light HUD panel */
  --gf-edit-purple: #6b4ad0;     /* pause box border / force ring */
  --gf-text-cream: #fff4d8;
  --gf-text-light: #eef4ff;
}

/* Generic full-screen menu surface that hosts a screen component. */
.gf-screen {
  position: relative;
  width: 100%;
  height: 100%;
  min-height: 100%;
  box-sizing: border-box;
  overflow: hidden;
  color: var(--gf-text-light);
  font-family: "Trebuchet MS", "Segoe UI", Arial, sans-serif;
  font-weight: 800;
  letter-spacing: 0.02em;
  user-select: none;
  -webkit-user-select: none;
}

/* Gridded radial backdrop used by the menu screens (difficulty/players/force). */
.gf-grid-bg {
  position: absolute;
  inset: 0;
  background:
    radial-gradient(circle at 50% 42%, rgba(255, 255, 255, 0.35), transparent 60%),
    repeating-linear-gradient(0deg, rgba(255, 255, 255, 0.08) 0 1px, transparent 1px 34px),
    repeating-linear-gradient(90deg, rgba(255, 255, 255, 0.08) 0 1px, transparent 1px 34px);
  background-color: var(--gf-screen-bg, #2f7fd0);
}
.gf-grid-bg.gf-bg-blue { --gf-screen-bg: #2f7fd0; }
.gf-grid-bg.gf-bg-green { --gf-screen-bg: #4caa2f; }
.gf-grid-bg.gf-bg-purple { --gf-screen-bg: #8b4fb5; }

/* Chunky outlined arcade title (SELECT DIFFICULTY, SELECT A FORCE, ...). */
.gf-title {
  position: relative;
  z-index: 2;
  text-align: center;
  margin: 0;
  padding-top: 0.6em;
  font-size: clamp(22px, 4.4vw, 40px);
  color: var(--gf-yellow);
  letter-spacing: 0.06em;
  text-transform: uppercase;
  -webkit-text-stroke: 2px var(--gf-outline);
  paint-order: stroke fill;
  text-shadow: 0 4px 0 rgba(0, 0, 0, 0.35);
}

.gf-row {
  position: relative;
  z-index: 2;
  display: flex;
  align-items: center;
  justify-content: center;
  gap: clamp(16px, 5vw, 64px);
}

/* Bottom button legend shared by menu screens. */
.gf-legend {
  position: absolute;
  left: 0;
  right: 0;
  bottom: 18px;
  z-index: 3;
  display: flex;
  align-items: center;
  justify-content: center;
  gap: clamp(20px, 6vw, 64px);
  font-size: clamp(13px, 2vw, 18px);
}
.gf-legend-item {
  display: inline-flex;
  align-items: center;
  gap: 8px;
  color: #ffffff;
  text-shadow: 0 2px 0 rgba(0, 0, 0, 0.45);
}

/* The round face-button glyphs (A green / B red / X grey / Y / START). */
.gf-btn {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  width: 1.7em;
  height: 1.7em;
  border-radius: 50%;
  font-size: 0.9em;
  color: #ffffff;
  font-weight: 900;
  box-shadow: inset 0 -3px 0 rgba(0, 0, 0, 0.35), 0 2px 3px rgba(0, 0, 0, 0.4);
}
.gf-btn-a { background: radial-gradient(circle at 35% 30%, #6fe24a, var(--gf-green-deep)); }
.gf-btn-b { background: radial-gradient(circle at 35% 30%, #ff5a4f, var(--gf-red-deep)); }
.gf-btn-x { background: radial-gradient(circle at 35% 30%, #cfd3da, #7d828c); color: #2a2150; }
.gf-btn-y { background: radial-gradient(circle at 35% 30%, #6fc3ff, #2f6db0); }
.gf-btn-start { background: radial-gradient(circle at 35% 30%, #cfd3da, #7d828c); color: #2a2150; font-size: 0.62em; }

/* Generic option tile used by difficulty + players screens. */
.gf-option {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 6px;
  cursor: pointer;
  background: none;
  border: none;
  color: inherit;
  font: inherit;
  padding: 8px;
  transition: transform 0.12s ease;
}
.gf-option:hover { transform: translateY(-2px); }
.gf-option.gf-selected { transform: scale(1.06); }

/* The colored oval "pad" that selected items sit on. */
.gf-pad {
  position: relative;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  width: clamp(110px, 22vw, 170px);
  height: clamp(110px, 22vw, 170px);
  border-radius: 50%;
}
.gf-option.gf-selected .gf-pad {
  box-shadow: 0 0 0 6px rgba(0, 0, 0, 0.85), 0 0 0 10px rgba(255, 255, 255, 0.25);
}

.gf-energy-label { font-size: 0.7em; color: #ffffff; text-shadow: 0 1px 0 #000; }
.gf-energy-num {
  font-size: clamp(26px, 6vw, 44px);
  line-height: 0.9;
  color: #ffffff;
  -webkit-text-stroke: 1.5px var(--gf-outline);
  paint-order: stroke fill;
}
.gf-energy-name {
  font-size: clamp(13px, 2.4vw, 20px);
  -webkit-text-stroke: 1px var(--gf-outline);
  paint-order: stroke fill;
}
.gf-name-normal { color: var(--gf-red); }
.gf-name-tuff { color: #ffffff; }
.gf-name-insane { color: #ffffff; }

/* Label pill under the player-count silhouettes. */
.gf-pill {
  margin-top: 6px;
  padding: 4px 18px;
  border-radius: 999px;
  background: linear-gradient(#7fc1f0, var(--gf-blue-pill-deep));
  color: #ffffff;
  font-size: clamp(13px, 2.2vw, 18px);
  -webkit-text-stroke: 0.6px var(--gf-outline);
  paint-order: stroke fill;
  box-shadow: inset 0 -2px 0 rgba(0, 0, 0, 0.3);
}
.gf-option.gf-selected .gf-pill { background: linear-gradient(#9ad4ff, #2f6db0); }

/* ============================ MAIN MENU ============================ */
.gf-mainmenu { background: linear-gradient(#bfe3ff 0%, #7fb8e8 45%, #d9b98a 46%, #c79a63 100%); }
.gf-mainmenu-desk {
  position: absolute;
  inset: 0;
  background-image: var(--gf-desk-img, none);
  background-size: cover;
  background-position: center;
}
.gf-mainmenu-ring {
  position: absolute;
  inset: 0;
  z-index: 2;
}
.gf-menu-item {
  position: absolute;
  transform: translate(-50%, -50%);
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 4px;
  cursor: pointer;
  background: none;
  border: none;
  color: inherit;
  font: inherit;
  transition: transform 0.18s ease, filter 0.18s ease;
}
.gf-menu-gear {
  width: 56px;
  height: 56px;
  border-radius: 12px;
  display: grid;
  place-items: center;
  font-size: 26px;
  background: radial-gradient(circle at 35% 30%, #6fb6ff, #2f6db0);
  box-shadow: inset 0 -4px 0 rgba(0, 0, 0, 0.3), 0 4px 6px rgba(0, 0, 0, 0.4);
  filter: drop-shadow(0 2px 2px rgba(0, 0, 0, 0.4));
}
.gf-menu-label {
  font-size: 18px;
  color: var(--gf-yellow);
  text-transform: uppercase;
  -webkit-text-stroke: 1.4px var(--gf-outline);
  paint-order: stroke fill;
  letter-spacing: 0.04em;
}
.gf-menu-item.gf-selected { transform: translate(-50%, -50%) scale(1.5); z-index: 5; }
.gf-menu-item.gf-selected .gf-menu-label { color: #fff; -webkit-text-stroke: 2px var(--gf-outline); }
.gf-menu-item.gf-selected .gf-menu-gear {
  background: radial-gradient(circle at 35% 30%, #ff8a4a, var(--gf-red));
  box-shadow: inset 0 -4px 0 rgba(0, 0, 0, 0.35), 0 0 0 6px rgba(232, 35, 27, 0.35);
  animation: gf-gear-spin 6s linear infinite;
}
@keyframes gf-gear-spin { to { transform: rotate(360deg); } }
.gf-mainmenu-logo {
  position: absolute;
  left: 50%;
  bottom: 6%;
  transform: translateX(-50%);
  z-index: 4;
  font-size: clamp(26px, 6vw, 54px);
  color: var(--gf-yellow);
  letter-spacing: 0.08em;
  -webkit-text-stroke: 3px var(--gf-green-deep);
  paint-order: stroke fill;
  text-shadow: 0 4px 0 rgba(0, 0, 0, 0.4);
}
.gf-mainmenu-approx {
  position: absolute;
  right: 8px;
  bottom: 4px;
  z-index: 6;
  font-size: 10px;
  font-weight: 600;
  color: rgba(255, 255, 255, 0.7);
  letter-spacing: 0;
}

/* ============================ FORCE BUILDER ============================ */
.gf-force { display: grid; grid-template-columns: 1fr minmax(280px, 42%); gap: 12px; padding: 12px; box-sizing: border-box; height: 100%; }
.gf-force-edit-tab {
  display: inline-flex;
  align-items: center;
  gap: 14px;
  align-self: start;
  padding: 6px 22px;
  border-radius: 999px;
  background: linear-gradient(#5f96d8, #2f6db0);
  border: 2px solid #9fc8f0;
  color: #fff;
  font-size: 18px;
  letter-spacing: 0.08em;
}
.gf-force-left { display: flex; flex-direction: column; gap: 10px; min-height: 0; }
.gf-force-grid {
  flex: 1;
  min-height: 0;
  overflow-y: auto;
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(58px, 1fr));
  gap: 6px;
  padding: 10px;
  border-radius: 10px;
  background: linear-gradient(#1d3a63, #12263f);
  border: 2px solid #2f5e96;
}
.gf-borg-cell {
  position: relative;
  aspect-ratio: 1;
  display: grid;
  place-items: center;
  border-radius: 8px;
  background: #e9eef5;
  border: 2px solid #b9c4d3;
  cursor: pointer;
  overflow: hidden;
  padding: 0;
}
.gf-borg-cell img { width: 100%; height: 100%; object-fit: contain; image-rendering: pixelated; }
.gf-borg-cell.gf-in-force { border-color: var(--gf-yellow); box-shadow: 0 0 0 2px var(--gf-yellow) inset; }
.gf-borg-cell.gf-disabled { opacity: 0.35; cursor: not-allowed; }
.gf-borg-cell .gf-cost-tag {
  position: absolute;
  bottom: 0;
  right: 0;
  font-size: 9px;
  background: rgba(0, 0, 0, 0.7);
  color: #ffd21e;
  padding: 0 3px;
  border-top-left-radius: 4px;
}
.gf-borg-cell .gf-new-badge {
  position: absolute;
  top: 0;
  left: 0;
  font-size: 8px;
  color: var(--gf-yellow);
  background: var(--gf-red);
  padding: 0 3px;
  border-bottom-right-radius: 4px;
  -webkit-text-stroke: 0.4px var(--gf-outline);
}

.gf-force-right {
  position: relative;
  display: flex;
  flex-direction: column;
  align-items: center;
  border-radius: 10px;
  background: radial-gradient(circle at 60% 50%, #3a2a6e, #1c1340);
  border: 3px solid var(--gf-edit-purple);
  padding: 10px;
  min-height: 0;
}
.gf-force-banner {
  align-self: stretch;
  display: flex;
  align-items: center;
  gap: 8px;
  padding: 4px 10px;
  border-radius: 999px;
  background: linear-gradient(#cfd3da, #9aa0ab);
  border: 2px solid #eef2f7;
  margin-bottom: 8px;
}
.gf-force-banner img { height: 26px; image-rendering: pixelated; }
.gf-force-banner .gf-force-banner-name {
  font-size: 16px;
  color: #2f6db0;
  -webkit-text-stroke: 0.6px #fff;
  paint-order: stroke fill;
  letter-spacing: 0.06em;
}
.gf-force-ring {
  position: relative;
  width: 100%;
  flex: 1;
  min-height: 200px;
}
.gf-slot {
  position: absolute;
  width: 30px;
  height: 34px;
  transform: translate(-50%, -50%);
  display: grid;
  place-items: center;
  cursor: pointer;
  clip-path: polygon(50% 0, 100% 25%, 100% 75%, 50% 100%, 0 75%, 0 25%);
  background: linear-gradient(#ffd86b, #f5a800);
  border: 0;
  font-size: 11px;
  color: var(--gf-outline);
  font-weight: 900;
}
.gf-slot.gf-slot-empty { background: linear-gradient(#5a4a8a, #34265f); color: rgba(255, 255, 255, 0.5); }
.gf-slot.gf-slot-filled { box-shadow: 0 0 0 1px #fff; }
.gf-slot.gf-slot-active { box-shadow: 0 0 0 2px var(--gf-red); }
.gf-slot img { width: 88%; height: 88%; object-fit: contain; image-rendering: pixelated; }

.gf-cost-panel {
  position: absolute;
  right: 6%;
  top: 38%;
  width: 46%;
  background: linear-gradient(#e9eef5, #c6cedb);
  border: 2px solid #fff;
  border-radius: 8px;
  padding: 6px 8px;
  color: var(--gf-outline);
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.5);
}
.gf-cost-panel .gf-cost-line {
  display: flex;
  justify-content: space-between;
  align-items: baseline;
  gap: 8px;
  font-size: 13px;
}
.gf-cost-panel .gf-cost-total {
  border-bottom: 2px solid #9aa0ab;
  padding-bottom: 4px;
  margin-bottom: 4px;
}
.gf-cost-panel .gf-cost-val { font-size: 18px; -webkit-text-stroke: 0.4px #fff; paint-order: stroke fill; }
.gf-cost-panel.gf-over .gf-cost-val.gf-remain { color: var(--gf-red); }

/* ============================ BATTLE HUD ============================ */
.gf-hud {
  position: absolute;
  inset: 0;
  pointer-events: none;
  font-family: "Trebuchet MS", "Segoe UI", Arial, sans-serif;
  font-weight: 800;
  color: #fff;
  z-index: 10;
}
.gf-hud-meters { position: absolute; top: 12px; left: 12px; display: flex; flex-direction: column; gap: 8px; }
.gf-meter { position: relative; width: 220px; height: 18px; display: flex; align-items: center; }
.gf-meter-tab {
  position: relative;
  z-index: 2;
  min-width: 38px;
  height: 100%;
  display: grid;
  place-items: center;
  padding: 0 6px;
  font-size: 13px;
  color: #fff;
  -webkit-text-stroke: 0.5px #000;
  paint-order: stroke fill;
}
.gf-meter-ally .gf-meter-tab { background: var(--gf-green-deep); border-radius: 4px 0 0 4px; }
.gf-meter-enemy .gf-meter-tab { background: var(--gf-red-deep); border-radius: 4px 0 0 4px; }
.gf-meter-track {
  position: relative;
  flex: 1;
  height: 100%;
  background: rgba(0, 0, 0, 0.55);
  /* zigzag/torn right end */
  clip-path: polygon(0 0, 100% 0, 96% 25%, 100% 50%, 96% 75%, 100% 100%, 0 100%);
  overflow: hidden;
}
.gf-meter-fill { position: absolute; inset: 0; transform-origin: left center; transition: transform 0.25s ease; }
.gf-meter-ally .gf-meter-fill { background: linear-gradient(#7be85a, var(--gf-green)); }
.gf-meter-enemy .gf-meter-fill { background: linear-gradient(#ff6a5f, var(--gf-red)); }
.gf-meter-name {
  position: absolute;
  right: 8px;
  top: 50%;
  transform: translateY(-50%);
  z-index: 2;
  font-size: 12px;
  letter-spacing: 0.1em;
  -webkit-text-stroke: 0.5px #000;
  paint-order: stroke fill;
}
.gf-hud-alert {
  position: absolute;
  top: 14px;
  left: 244px;
  width: 26px;
  height: 26px;
  display: grid;
  place-items: center;
  border-radius: 50%;
  background: var(--gf-yellow);
  color: var(--gf-outline);
  font-size: 18px;
  border: 2px solid #fff;
}
.gf-hud-alert.gf-hidden { display: none; }

/* center lock-on reticle */
.gf-hud-reticle {
  position: absolute;
  top: 44%;
  left: 50%;
  width: 78px;
  height: 78px;
  transform: translate(-50%, -50%);
  display: grid;
  place-items: center;
  transition: opacity 0.15s ease;
}
.gf-hud-reticle.gf-hidden { opacity: 0; }
.gf-reticle-ring {
  position: absolute;
  inset: 0;
  border: 4px solid var(--gf-orange);
  border-radius: 50%;
  box-shadow: 0 0 0 2px rgba(0, 0, 0, 0.4);
  animation: gf-reticle-spin 4s linear infinite;
}
@keyframes gf-reticle-spin { to { transform: rotate(360deg); } }
.gf-reticle-tri { position: absolute; width: 0; height: 0; color: #3a7bd5; }

/* bottom-left HP gauge */
.gf-hud-hp {
  position: absolute;
  bottom: 16px;
  left: 16px;
  width: 92px;
  height: 60px;
  display: grid;
  place-items: center;
}
.gf-hp-ring { position: absolute; inset: 0; }
.gf-hp-num {
  position: relative;
  z-index: 2;
  font-size: 26px;
  color: var(--gf-yellow);
  -webkit-text-stroke: 1.4px var(--gf-outline);
  paint-order: stroke fill;
}
.gf-hud-hp.gf-critical .gf-hp-num { color: #fff; }

/* bottom-right weapon prompts */
.gf-hud-weapon { position: absolute; bottom: 16px; right: 16px; display: flex; align-items: flex-end; gap: 14px; }
.gf-weapon-x { display: grid; place-items: center; width: 56px; height: 56px; }
.gf-weapon-x .gf-x-glyph {
  position: relative;
  z-index: 2;
  width: 26px;
  height: 26px;
  display: grid;
  place-items: center;
  border-radius: 50%;
  background: radial-gradient(circle at 35% 30%, #cfd3da, #7d828c);
  color: var(--gf-outline);
  font-size: 14px;
  font-weight: 900;
}
.gf-cooldown-ring { position: absolute; inset: 0; }
.gf-weapon-b { display: flex; align-items: center; gap: 6px; }
.gf-b-track {
  position: relative;
  width: 70px;
  height: 16px;
  border-radius: 999px;
  background: rgba(0, 0, 0, 0.55);
  overflow: hidden;
  display: flex;
  align-items: center;
  padding-left: 8px;
}
.gf-b-reload { position: absolute; left: 0; top: 0; bottom: 0; background: var(--gf-cyan); transition: width 0.2s ease; }
.gf-b-ammo { position: relative; z-index: 2; color: var(--gf-yellow); font-size: 15px; -webkit-text-stroke: 1px var(--gf-outline); paint-order: stroke fill; }
.gf-b-glyph {
  width: 26px;
  height: 26px;
  display: grid;
  place-items: center;
  border-radius: 50%;
  background: radial-gradient(circle at 35% 30%, #ff5a4f, var(--gf-red-deep));
  color: #fff;
  font-size: 14px;
  font-weight: 900;
}

/* ============================ RESULTS ============================ */
.gf-results { background: linear-gradient(#b9744c, #6a3f2a); }
.gf-results-sky { position: absolute; inset: 0; background: linear-gradient(#d99c79 0%, #b06a4a 55%, #7a4a32 100%); }
.gf-results-rows {
  position: absolute;
  left: 6%;
  top: 10%;
  width: 56%;
  display: flex;
  flex-direction: column;
  gap: 8px;
  z-index: 2;
}
.gf-result-row { display: flex; align-items: center; }
.gf-result-pill {
  flex: 1;
  display: flex;
  align-items: center;
  padding: 6px 14px;
  border-radius: 999px;
  background: linear-gradient(#7fb4e6, var(--gf-blue-pill-deep));
  border: 2px solid #bcdcff;
  color: #fff;
  font-size: clamp(11px, 1.8vw, 17px);
  letter-spacing: 0.04em;
  -webkit-text-stroke: 0.5px var(--gf-outline);
  paint-order: stroke fill;
  box-shadow: inset 0 -2px 0 rgba(0, 0, 0, 0.25);
  text-transform: uppercase;
}
.gf-result-sub { background: linear-gradient(#9ec3e8, #4f7fb0); }
.gf-result-grand .gf-result-pill { background: linear-gradient(#ffe27a, var(--gf-orange)); color: var(--gf-outline); }
.gf-result-val {
  margin-left: 12px;
  min-width: 4ch;
  text-align: right;
  font-size: clamp(16px, 3vw, 26px);
  color: #fff;
  -webkit-text-stroke: 1px var(--gf-outline);
  paint-order: stroke fill;
}
.gf-result-val.gf-neg { color: var(--gf-red); }
.gf-results-verdict {
  position: absolute;
  left: 42%;
  top: 44%;
  transform: translate(-50%, -50%) rotate(-6deg);
  z-index: 3;
  font-size: clamp(48px, 12vw, 110px);
  letter-spacing: 0.04em;
}
.gf-verdict-win { color: var(--gf-yellow); -webkit-text-stroke: 4px var(--gf-red); paint-order: stroke fill; text-shadow: 0 6px 0 rgba(0, 0, 0, 0.4); }
.gf-verdict-lose { color: #cfd3da; -webkit-text-stroke: 4px var(--gf-outline); paint-order: stroke fill; text-shadow: 0 6px 0 rgba(0, 0, 0, 0.4); }
.gf-results-start {
  position: absolute;
  right: 18px;
  bottom: 18px;
  z-index: 4;
  display: inline-flex;
  align-items: center;
  gap: 8px;
  font-size: 14px;
}

/* ============================ PAUSE MENU ============================ */
.gf-pause-overlay {
  position: absolute;
  inset: 0;
  display: grid;
  place-items: center;
  background: rgba(0, 0, 0, 0.18);
  z-index: 20;
}
.gf-pause-box {
  min-width: 260px;
  border-radius: 16px;
  background: linear-gradient(#cfd3da, #aeb4c0);
  border: 4px solid var(--gf-edit-purple);
  box-shadow: 0 8px 24px rgba(0, 0, 0, 0.5);
  overflow: hidden;
}
.gf-pause-title {
  text-align: center;
  padding: 8px 0;
  font-size: 22px;
  color: var(--gf-outline);
  letter-spacing: 0.1em;
}
.gf-pause-items { padding: 8px 14px 16px; display: flex; flex-direction: column; gap: 8px; }
.gf-pause-item {
  display: flex;
  align-items: center;
  gap: 10px;
  padding: 6px 12px;
  border-radius: 999px;
  background: rgba(255, 255, 255, 0.4);
  color: var(--gf-outline);
  font-size: 18px;
  cursor: pointer;
  border: none;
  font-family: inherit;
  font-weight: 800;
  letter-spacing: 0.06em;
}
.gf-pause-item.gf-selected {
  background: linear-gradient(#6f9bd8, #2f6db0);
  color: #fff;
}
.gf-pause-item .gf-pause-bullet { width: 1.4em; }
`;
