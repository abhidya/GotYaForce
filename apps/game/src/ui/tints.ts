/**
 * Shared bitmap-font tint colors for the rebuilt menu screens.
 *
 * The ascii.tpl atlas ships white-core / black-outline glyphs; setBitmapText recolors only
 * the core, exactly like the game's vertex-colored font quads (see bitmapText.ts). The
 * values below are the palette those quads are tinted with across the Challenge front end,
 * collected here so a screen cannot drift a shade away from its neighbours.
 *
 * TUNED (sampled from the reference captures in apps/game/reference/captures/, not read
 * from a decoded material block).
 *
 * NOT the HUD palette: apps/game/src/ui/hud/BattleHud.ts keeps its own TINT_* constants
 * sampled from the in-battle captures, and its label yellow (#ffd428) is measurably a
 * different shade from the menus' #ffd21e. That divergence is real capture data, not a
 * typo, so the two palettes stay separate rather than being averaged into one.
 */

/** Menu headline / emphasis yellow ("SELECT A FORCE", COST, force name, active slot). */
export const TINT_MENU_YELLOW = "#ffd21e";
/** Plain readable value text (numbers, names) on the menu screens. */
export const TINT_MENU_WHITE = "#ffffff";
/** Cool blue-white used for secondary/derived readouts (REMAIN, cost sub-lines). */
export const TINT_MENU_COOL = "#dff6ff";
/** Over-budget / negative-total red (Force Builder REMAIN, a negative GRAND TOTAL). */
export const TINT_MENU_ALERT = "#ff5a4f";
