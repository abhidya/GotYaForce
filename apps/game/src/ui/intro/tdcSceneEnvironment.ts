/**
 * tdcSceneEnvironment — fog + light environment for the title desk montage.
 *
 * Extracted from TitleIntro.ts so the per-archive HSD SOBJ environment (fog flag +
 * authored tl00 lights) is owned by one module and TitleIntro's core render loop is
 * left to the camera-matrix work. TitleIntro imports {@link applyTdcFog} /
 * {@link applyTdcLights} and calls them from its `applyTdcFrame` section.
 *
 * Source provenance:
 *  - research/decomp/tl00-scene-camera-2026-07-04.md §"Authored lights" + §"Authored fog"
 *    (the three tl00_mdl.arc HSD SOBJ lights + the HSD_FogDesc bytes).
 *  - research/decomp/tdc-archives-decode-2026-07-05.md (tdc00..09 carry camera
 *    AOBJ/eye/target tracks ONLY — no FOBJ light tracks).
 *  - research/decomp/ptl-format-notes-2026-07-04.md §1b (scene_data word3 presence bit
 *    is the HSD SOBJ fog flag -> bank+0x19).
 */

import * as THREE from "three";

/**
 * Per-archive TDC scene state. Fields are the decoded HSD SOBJ records: camera
 * eye/target/fov from tdc00..09 (tdc-archives-decode-2026-07-05.md), `fog` is the SOBJ
 * fog-presence bit, `lightProfile` is the per-archive light-bank selection (the profile
 * ID is source-derived; the non-base profile PARAMETERS are not exported — see
 * {@link INVENTED_CHARACTER_LIGHTS_GAP}).
 */
export interface TdcSceneState {
  archive: string;
  resourceSlot: number;
  eye: readonly [number, number, number];
  target: readonly [number, number, number];
  fov: number;
  endFrame: number;
  lightProfile: "base" | "character-base" | "character";
  /** HSD SOBJ fog-presence bit (scene_data word3 -> bank+0x19). tdc00/05/07 carry it. */
  fog: boolean;
}

/**
 * SOURCE-DERIVED: tl00_mdl.arc's authored HSD SOBJ ambient light, decoded in
 * research/decomp/tl00-scene-camera-2026-07-04.md §"Authored lights" light[0]:
 * AMBIENT rgba(152, 140, 178) — cool lavender room ambient.
 */
export const TL00_AUTHORED_AMBIENT = { r: 152, g: 140, b: 178 } as const;

/**
 * SOURCE-DERIVED: tl00_mdl.arc's two authored HSD SOBJ infinite lights, decoded in
 * research/decomp/tl00-scene-camera-2026-07-04.md §"Authored lights" light[1..2]:
 *   light[1] INFINITE diffuse+specular rgba(128,128,128) dir (-2.781, 1.967, 1.141).
 *   light[2] INFINITE diffuse+specular rgba(128,128,128) dir ( 0.962, 2.037,-0.699).
 * Direction vectors share the exported GLBs' world convention (handedness note, same
 * doc). These two entries are the source backing for the prior TitleIntro
 * `BASE_DIRECTIONS[0..1]` constants.
 */
export const TL00_AUTHORED_INFINITE = [
  { color: [128, 128, 128] as const, position: [-2.7812777, 1.9665543, 1.140989] as const },
  { color: [128, 128, 128] as const, position: [0.9624716, 2.0371425, -0.698656] as const },
] as const;

/**
 * INVENTED GAP — NOT source-derived. The prior TitleIntro `BASE_DIRECTIONS[2..3]` fill
 * lights. Retained to preserve the base profile's prior visual fill level, but the
 * tl00 HSD SOBJ light walk (tl00-scene-camera-2026-07-04.md) found ONLY THREE authored
 * lights (1 ambient + 2 infinite = {@link TL00_AUTHORED_AMBIENT} +
 * {@link TL00_AUTHORED_INFINITE}); these two extra fills have no source backing.
 * Replace when a fuller LOBJ track export lands.
 */
export const INVENTED_BASE_FILL_LIGHTS_GAP = [
  { color: [255, 255, 255] as const, position: [1, 1, 1] as const },
  { color: [153, 153, 153] as const, position: [-1, -1, -1] as const },
] as const;

/**
 * INVENTED GAP — NOT source-derived. The prior TitleIntro `CHARACTER_DIRECTIONS`
 * pair, applied for the `character*` light profiles (tdc03/06/07/08 close-ups).
 * research/decomp/tdc-archives-decode-2026-07-05.md establishes the tdc00..09 archives
 * carry camera AOBJ/eye/target tracks ONLY — there are NO FOBJ light tracks in the tdc
 * archives, so the per-archive character-close-up light parameters are NOT exported.
 * The profile SELECTION (`lightProfile: "character*"` in {@link TdcSceneState}) is
 * source-derived, but these position/color values are invented to keep the close-ups
 * lit; replace when the tl00/tdc LOBJ track export queued in
 * research/decomp/CHALLENGE-1TO1-PROMPT.md §5 (`scripts/export-stage-render-state.mjs`)
 * lands.
 */
export const INVENTED_CHARACTER_LIGHTS_GAP = [
  { color: [255, 255, 255] as const, position: [0.5, 1, 1] as const },
  { color: [128, 128, 153] as const, position: [-0.5, -1, -1] as const },
] as const;

/** The base-profile directional set: source-derived authored pair + invented fills. */
const BASE_PROFILE_DIRECTIONS = [...TL00_AUTHORED_INFINITE, ...INVENTED_BASE_FILL_LIGHTS_GAP];

/**
 * Apply HSD SOBJ fog per the TDC scene state.
 *
 * Source: the per-archive `fog` flag is the HSD SOBJ fog-presence bit decoded in
 * research/decomp/ptl-format-notes-2026-07-04.md §1b (scene_data word3 -> bank+0x19);
 * tdc00/05/07 carry fog=true, the rest do not.
 *
 * The tl00_mdl.arc base scene's own HSD_FogDesc (bytes `00000002|00000000|1e6|2e6|
 * rgba(42,196,188,255)`, range 1e6..2e6 — far beyond the 32768 far clip) is authored
 * OFF per tl00-scene-camera-2026-07-04.md, so the base (index < 0) scene renders with
 * no fog.
 *
 * Fog color matches the scene's authored ambient ({@link TL00_AUTHORED_AMBIENT}, the
 * cool lavender room ambient) so the haze blends with the key fill. Density is
 * FogExp2-tuned for the tdc far clip: the tdc COBJ records all carry `far: 32768`
 * (apps/game/public/ui/scenes/tl00/tdc-camera-anims.json), with subject distances
 * (eye->target) of ~5,000..9,000 units. At `FOG_DENSITY = 1e-4`, the FogExp2 factor
 * `exp(-(d*dist)^2)` is ~0.78 at 5k (light haze), ~0.44 at 9k (mid fog), and ~2e-5 at
 * the 32768 far plane (full occlusion) — the light exponential fog the spec calls for.
 */
const FOG_DENSITY = 1e-4;
const FOG_COLOR = new THREE.Color(
  TL00_AUTHORED_AMBIENT.r / 255,
  TL00_AUTHORED_AMBIENT.g / 255,
  TL00_AUTHORED_AMBIENT.b / 255,
);

export function applyTdcFog(scene: THREE.Scene, state: TdcSceneState): void {
  if (!state.fog) {
    scene.fog = null;
    return;
  }
  // Clone so callers can safely mutate scene.fog later without touching the shared
  // module-level color instance.
  scene.fog = new THREE.FogExp2(FOG_COLOR.clone(), FOG_DENSITY);
}

/**
 * Apply the per-archive light rig. Mirrors the prior TitleIntro `setTdcLights` behavior
 * (ambient + profile-selected directionals) so visual output is unchanged, but with the
 * constants split into source-derived ({@link TL00_AUTHORED_AMBIENT} +
 * {@link TL00_AUTHORED_INFINITE}) and invented-gap ({@link INVENTED_BASE_FILL_LIGHTS_GAP}
 * + {@link INVENTED_CHARACTER_LIGHTS_GAP}) sets — see each const's docstring.
 *
 * The rig is cleared and rebuilt on every call (matches the prior implementation), so
 * a profile switch between tdc archives fully replaces the active lights.
 */
export function applyTdcLights(lightRig: THREE.Group, state: TdcSceneState): void {
  lightRig.clear();
  lightRig.add(
    new THREE.AmbientLight(
      new THREE.Color(
        TL00_AUTHORED_AMBIENT.r / 255,
        TL00_AUTHORED_AMBIENT.g / 255,
        TL00_AUTHORED_AMBIENT.b / 255,
      ),
      1,
    ),
  );
  const directions =
    state.lightProfile === "base"
      ? BASE_PROFILE_DIRECTIONS
      : state.lightProfile === "character"
        ? INVENTED_CHARACTER_LIGHTS_GAP
        : [...INVENTED_CHARACTER_LIGHTS_GAP, ...BASE_PROFILE_DIRECTIONS];
  for (const source of directions) {
    const [r, g, b] = source.color;
    const [x, y, z] = source.position;
    const light = new THREE.DirectionalLight(new THREE.Color(r / 255, g / 255, b / 255), 1);
    light.position.set(x, y, z);
    lightRig.add(light);
  }
}
