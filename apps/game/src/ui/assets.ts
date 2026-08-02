/**
 * Real extracted-asset path helpers for the Gotcha Force UI.
 *
 * All paths are PUBLIC paths served from apps/game/public, so they resolve at
 * `/ui/...` in the browser. Mapping mirrors main.ts's borgUiCode():
 *   borg id  "pl0000"  ->  ui code "0000"
 *   banner  /ui/tpl/bn<code>/image_00_CI4.png   (448x64 per-borg name plate)
 *   mini    /ui/tpl/mn<code>/image_00_CI4.png   (borg mini icon)
 */

import { publicUrl } from "../publicUrl.js";

/** Convert a borgs.json id ("pl0000") to the 4-char UI art code ("0000"). */
export function borgUiCode(id: string): string {
  return id.replace(/^pl/i, "").padStart(4, "0");
}

/** Per-borg name banner (the real `bn<code>` plate). */
export function borgBannerPath(id: string): string {
  return publicUrl(`/ui/tpl/bn${borgUiCode(id)}/image_00_CI4.png`);
}

/** Per-borg mini icon (the real `mn<code>` icon). */
export function borgMiniPath(id: string): string {
  return publicUrl(`/ui/tpl/mn${borgUiCode(id)}/image_00_CI4.png`);
}

/** Per-borg portrait face texture (real `face<code>_mdl`). Not every borg has one. */
export function borgFacePath(id: string): string {
  return publicUrl(`/ui/hsd/face${borgUiCode(id)}_mdl/texture_000_CI8.png`);
}

/** Named real menu textures used as decoration where they map cleanly. */
export const ASSETS = {
  /** Main-menu option screen texture (384x224). */
  mainMenuOption: publicUrl("/ui/hsd/optn00_mdl/texture_000_CI4.png"),
  /** Gotcha box source textures (force setup / Load Box Data). */
  gotchaBoxLens: publicUrl("/ui/hsd/box00_mdl/texture_000_CMP.png"),
  gotchaBoxCross: publicUrl("/ui/hsd/box00_mdl/texture_001_CMP.png"),
  gotchaBoxScrew: publicUrl("/ui/hsd/box00_mdl/texture_002_CMP.png"),
  gotchaBoxButton: publicUrl("/ui/hsd/box00_mdl/texture_003_CMP.png"),
  /** GET strip (force setup, 448x64). */
  getStrip: publicUrl("/ui/hsd/gets00_mdl/texture_000_CI4.png"),
  /** Force-entry/control texture sheets. */
  entryControls: publicUrl("/ui/hsd/entry00_mdl/texture_002_CI8.png"),
  /** Slot-A memory-card icon from `as_icon.tpl` (used by Load Box Data). */
  memoryCardSlot: publicUrl("/ui/tpl/as_icon/image_00_CI8.png"),
  /** Edit-force/unit collection atlas from `unitall_mdl.arc`. */
  unitAllAtlas: publicUrl("/ui/hsd/unitall_mdl/texture_008_CI8.png"),
  /** Battle briefing / VS source texture sheets. */
  briefingVs: publicUrl("/ui/hsd/brif00_mdl/texture_000_IA4.png"),
  briefingNames: publicUrl("/ui/hsd/brif00_mdl/texture_001_CI4.png"),
  vsSelectLabels: publicUrl("/ui/hsd/vsel00_mdl/texture_004_CI8.png"),
  /**
   * Generic glossy roundel disc from the vsel00 menu-select export. No original
   * pause-menu archive/data is known (see PauseMenu.ts), so this reuses an
   * existing exported plate/roundel texture as the pause box's backing plate
   * instead of a pure CSS box.
   */
  menuRoundelPlate: publicUrl("/ui/hsd/vsel00_mdl/texture_009_CMP.png"),
  /** Results/podium exported scene texture sheets. */
  resultsWin: publicUrl("/ui/hsd/rpot20_mdl/texture_000_RGBA8.png"),
  resultsLose: publicUrl("/ui/hsd/rpot23_mdl/texture_000_RGBA8.png"),
  resultsStartPrompt: publicUrl("/ui/hsd/rpot20_mdl/texture_003_CI8.png"),
  resultsGameOver: publicUrl("/ui/hsd/rpot23_mdl/texture_004_CI8.png"),
  /** In-battle face marker/roundel texture from `fmg00_mdl.arc`. */
  faceMarkerRoundel: publicUrl("/ui/hsd/fmg00_mdl/texture_001_CI8.png"),
  /** Monospaced ASCII HUD/font atlas from `ascii.tpl`. */
  fontAscii: publicUrl("/ui/tpl/ascii/image_00_IA4.png"),
  /** Bitmap font sheet. */
  font: publicUrl("/ui/tpl/font_00/image_00_CI4.png"),
} as const;
