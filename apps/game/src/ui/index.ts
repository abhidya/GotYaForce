/**
 * Gotcha Force UI component library — barrel export.
 *
 * Framework-free TypeScript DOM components that reproduce the REAL game screens
 * (Challenge-mode flow) from the captured references in
 * apps/game/reference/captures/. Each component mounts into a container
 * HTMLElement and returns a handle with update()/destroy() (and per-screen
 * getters); selections are surfaced via callbacks.
 *
 * Quick start:
 *   import { ensureStyles, createMainMenu } from "./ui/index.js";
 *   ensureStyles();                       // inject the scoped gf- styles once
 *   const menu = createMainMenu(root, { onSelect: (mode) => ... });
 *
 * Styles: ensureStyles() injects the scoped `gf-` CSS. If your bundler handles
 * CSS imports you can instead `import "./ui/styles.css"`.
 */

import { GF_UI_CSS } from "./styles.generated.js";

const STYLE_ID = "gf-ui-styles";

/** Inject the scoped `gf-` stylesheet into the document once. Idempotent. */
export function ensureStyles(doc: Document = document): void {
  if (doc.getElementById(STYLE_ID)) return;
  const style = doc.createElement("style");
  style.id = STYLE_ID;
  style.textContent = GF_UI_CSS;
  doc.head.appendChild(style);
}

export { GF_UI_CSS };

// ---- asset helpers ----
export { borgUiCode, borgBannerPath, borgMiniPath, borgFacePath, ASSETS } from "./assets.js";

// ---- screens ----
export { createMainMenu } from "./screens/MainMenu.js";
export type { MainMenuMode, MainMenuOptions, MainMenuHandle } from "./screens/MainMenu.js";

export { createSelectDifficulty } from "./screens/SelectDifficulty.js";
export type { Difficulty, SelectDifficultyOptions, SelectDifficultyHandle } from "./screens/SelectDifficulty.js";

export { createSelectPlayers } from "./screens/SelectPlayers.js";
export type { SelectPlayersOptions, SelectPlayersHandle } from "./screens/SelectPlayers.js";

export { createLoadBoxData } from "./screens/LoadBoxData.js";
export type { LoadBoxDataOptions, LoadBoxDataHandle } from "./screens/LoadBoxData.js";

export { createSelectForce } from "./screens/SelectForce.js";
export type { ForceSlot, SelectForceOptions, SelectForceHandle } from "./screens/SelectForce.js";

export { createForceBuilder } from "./screens/ForceBuilder.js";
export type { ForceBorg, ForceBuilderOptions, ForceBuilderHandle } from "./screens/ForceBuilder.js";

export { createBattleIntro } from "./screens/BattleIntro.js";
export type { BattleIntroOptions, BattleIntroHandle } from "./screens/BattleIntro.js";

export { createResults } from "./screens/Results.js";
export type { ResultStats, ResultsOptions, ResultsHandle } from "./screens/Results.js";

export { createPauseMenu } from "./screens/PauseMenu.js";
export type { PauseAction, PauseMenuOptions, PauseMenuHandle } from "./screens/PauseMenu.js";

// ---- HUD ----
export { createBattleHud } from "./hud/BattleHud.js";
export type { HudState, BattleHudOptions, BattleHudHandle } from "./hud/BattleHud.js";
