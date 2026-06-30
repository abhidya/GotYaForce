/**
 * Real extracted-asset path helpers for the Gotcha Force UI.
 *
 * All paths are PUBLIC paths served from apps/game/public, so they resolve at
 * `/ui/...` in the browser. Mapping mirrors main.ts's borgUiCode():
 *   borg id  "pl0000"  ->  ui code "0000"
 *   banner  /ui/tpl/bn<code>/image_00_CI4.png   (448x64 per-borg name plate)
 *   mini    /ui/tpl/mn<code>/image_00_CI4.png   (borg mini icon)
 */

/** Convert a borgs.json id ("pl0000") to the 4-char UI art code ("0000"). */
export function borgUiCode(id: string): string {
  return id.replace(/^pl/i, "").padStart(4, "0");
}

/** Per-borg name banner (the real `bn<code>` plate). */
export function borgBannerPath(id: string): string {
  return `/ui/tpl/bn${borgUiCode(id)}/image_00_CI4.png`;
}

/** Per-borg mini icon (the real `mn<code>` icon). */
export function borgMiniPath(id: string): string {
  return `/ui/tpl/mn${borgUiCode(id)}/image_00_CI4.png`;
}

/** Per-borg portrait face texture (real `face<code>_mdl`). Not every borg has one. */
export function borgFacePath(id: string): string {
  return `/ui/hsd/face${borgUiCode(id)}_mdl/texture_000_CI8.png`;
}

/** Named real menu textures used as decoration where they map cleanly. */
export const ASSETS = {
  /** Main-menu option screen texture (384x224). */
  mainMenuOption: "/ui/hsd/optn00_mdl/texture_000_CI4.png",
  /** Gotcha box texture (force setup). */
  gotchaBox: "/ui/hsd/box00_mdl/texture_000_CMP.png",
  /** GET strip (force setup, 448x64). */
  getStrip: "/ui/hsd/gets00_mdl/texture_000_CI4.png",
  /** Bitmap font sheet. */
  font: "/ui/tpl/font_00/image_00_CI4.png",
} as const;
