// Stage lighting / render-state module.
//
// Owns the translation from the per-stage exported HSD scene render state
// (apps/game/public/stages/<stXX>/render-state.json, produced by
// scripts/export-stage-render-state.mjs from the stage-archive scan in
// research/asset-inventory/stage-lighting-render-state.{md,json}) into
// three.js scene state: ambient + directional lights, linear fog, background
// (clear) color, and camera fov/near/far.
//
// Every stage archive (40/40 scanned) carries the same scene_data layout:
// one CObj camera, one flags=0x40000 LObj with no position (ambient/global
// channel color), one or two flags=0xd0000 positioned LObjs (diffuse/specular
// lights), and one FogDesc (all stages use HSD/GX fog type 2 = GX_FOG_LIN,
// i.e. linear fog — an exact match for THREE.Fog). Example DERIVED values:
//   st00: ambient #d8d0c2, light #fff0e6 @ (-385.5, 956.0, -378.0),
//         fog #fff6e5 900..40000, fov 43.191872, near 10, far 80000
//   st07: ambient #a39380, light #ffffff @ (-1139, 4763, -1977),
//         fog #371a3d 2000..40000, fov 38.03
//   stff: ambient #988cb2, TWO gray #808080 directionals @ (-3,2,1)/(1,2,-1)
// The per-stage values are read from render-state.json at stage mount; the
// constants below are only the st00-derived fallback for stages whose JSON
// fails to load.

import * as THREE from "three";

// ------------------------------------------------------------------------------------------
// Shape of apps/game/public/stages/<stXX>/render-state.json (exporter output).
// Only the fields the renderer consumes are typed; provenance/raw fields are ignored.
// ------------------------------------------------------------------------------------------

export type StageRenderStateColor = {
  rgbHex?: string;
  rgba?: number[];
  normalized?: number[];
};

export type StageRenderStateWObj = {
  position?: number[];
} | null;

export type StageRenderStateLight = {
  index?: number;
  role?: string;
  flags?: string;
  color?: StageRenderStateColor;
  /** WObj world position; null/absent for the ambient (global channel color) LObj. */
  position?: StageRenderStateWObj;
  interestOrParam?: StageRenderStateWObj;
};

export type StageRenderStateFog = {
  /** HSD/GX fog type. 0 = none; 2 = GX_FOG_LIN (all 40 exported stages use 2). */
  type?: number;
  start?: number;
  end?: number;
  color?: StageRenderStateColor;
  /** Legacy flat field kept for older exports. */
  colorRgbHex?: string;
};

export type StageRenderStateCamera = {
  fovDegrees?: number;
  near?: number;
  far?: number;
};

export type StageRenderState = {
  stageId?: string;
  camera?: StageRenderStateCamera;
  lights?: StageRenderStateLight[];
  fog?: StageRenderStateFog;
};

// ------------------------------------------------------------------------------------------
// Resolved (renderer-ready) lighting state.
// ------------------------------------------------------------------------------------------

export type StageVec3 = [number, number, number];

export type ResolvedStageLighting = {
  /** Scene background / clear color (the game clears to the fog color). */
  background: number;
  /** Linear fog, or null when the stage disables fog (HSD fog type 0). */
  fog: { color: number; near: number; far: number } | null;
  camera: { fovDegrees: number; near: number; far: number };
  ambient: { color: number; intensity: number };
  /** One or more positioned diffuse/specular lights (stff has two). */
  directionals: Array<{ color: number; intensity: number; position: StageVec3 }>;
};

// TUNED: single global calibration factor applied to ambient + directional
// intensities. The HSD LObj descriptors carry colors but no scalar intensity
// (GX light contribution is color * channel math), and the exported DAE
// materials were authored against that model. With three.js r169 defaults
// (physically-based light intensities off for Ambient/Directional color
// multipliers) intensity 1.0 reproduces a readable image across all 40
// stages, so the factor stays at 1.0. Adjust HERE — never per stage — if a
// future material/color-space change makes stages uniformly too dark/bright.
export const STAGE_LIGHT_CALIBRATION = 1.0;

// DERIVED from the st00_mdl.arc scene scan (research/asset-inventory/
// stage-lighting-render-state.md): CObj @0x75278 (fov 43.191872, near 10,
// far 80000), LObj0 @0x75234 ambient #d8d0c2, LObj1 @0x75218 #fff0e6 at
// (-385.512512, 956.0448, -377.986603), FogDesc @0x752b0 type 2 start 900
// end 40000 color #fff6e5. Used only when a stage's render-state.json is
// missing or unparseable.
export const DEFAULT_STAGE_LIGHTING: ResolvedStageLighting = {
  background: 0xfff6e5,
  fog: { color: 0xfff6e5, near: 900, far: 40000 },
  camera: { fovDegrees: 43.191872, near: 10, far: 80000 },
  ambient: { color: 0xd8d0c2, intensity: STAGE_LIGHT_CALIBRATION },
  directionals: [
    {
      color: 0xfff0e6,
      intensity: STAGE_LIGHT_CALIBRATION,
      position: [-385.512512, 956.0448, -377.986603],
    },
  ],
};

// ------------------------------------------------------------------------------------------
// Resolution: exported JSON -> renderer-ready values (pure; no three.js objects touched).
// ------------------------------------------------------------------------------------------

function parseHexColor(value: string | undefined, fallback: number): number {
  if (!value || !/^#[0-9a-f]{6}$/i.test(value)) return fallback;
  return Number.parseInt(value.slice(1), 16);
}

function finiteVec3(value: number[] | undefined | null): StageVec3 | undefined {
  if (!value || value.length < 3) return undefined;
  const [x, y, z] = value;
  if (x === undefined || y === undefined || z === undefined) return undefined;
  return Number.isFinite(x) && Number.isFinite(y) && Number.isFinite(z) ? [x, y, z] : undefined;
}

function lightPosition(light: StageRenderStateLight): StageVec3 | undefined {
  return finiteVec3(light.position?.position);
}

/**
 * Resolve a stage's exported render state into renderer-ready lighting values.
 * Falls back field-by-field to the st00-derived defaults, so a partial or
 * missing render-state.json still yields a fully populated result.
 */
export function resolveStageLighting(rs: StageRenderState | null | undefined): ResolvedStageLighting {
  const lights = Array.isArray(rs?.lights) ? rs.lights : [];

  // Ambient = the LObj without a world position (flags 0x40000 in every
  // scanned stage); role text is a secondary hint for older exports.
  const ambient =
    lights.find((light) => !lightPosition(light)) ??
    lights.find((light) => /ambient|global/i.test(light.role ?? ""));

  // Directionals = every positioned LObj. HSD points these lights at their
  // interest (0,0,0 in all scanned stages), which matches a three.js
  // DirectionalLight at `position` with its default origin target.
  const directionals = lights
    .map((light) => ({ light, position: lightPosition(light) }))
    .filter((entry): entry is { light: StageRenderStateLight; position: StageVec3 } => entry.position !== undefined)
    .map(({ light, position }) => ({
      color: parseHexColor(light.color?.rgbHex, DEFAULT_STAGE_LIGHTING.directionals[0]?.color ?? 0xffffff),
      intensity: STAGE_LIGHT_CALIBRATION,
      position,
    }));

  const fogColor = parseHexColor(
    rs?.fog?.color?.rgbHex ?? rs?.fog?.colorRgbHex,
    DEFAULT_STAGE_LIGHTING.fog?.color ?? 0xfff6e5,
  );
  // HSD fog type 0 = GX_FOG_NONE. Every exported stage uses type 2
  // (GX_FOG_LIN); any other nonzero exponential type is approximated linearly.
  const fogEnabled = rs?.fog === undefined || (rs.fog.type ?? 2) !== 0;

  return {
    background: fogColor,
    fog: fogEnabled
      ? {
          color: fogColor,
          near: rs?.fog?.start ?? DEFAULT_STAGE_LIGHTING.fog?.near ?? 900,
          far: rs?.fog?.end ?? DEFAULT_STAGE_LIGHTING.fog?.far ?? 40000,
        }
      : null,
    camera: {
      fovDegrees: rs?.camera?.fovDegrees ?? DEFAULT_STAGE_LIGHTING.camera.fovDegrees,
      near: rs?.camera?.near ?? DEFAULT_STAGE_LIGHTING.camera.near,
      far: rs?.camera?.far ?? DEFAULT_STAGE_LIGHTING.camera.far,
    },
    ambient: {
      color: parseHexColor(ambient?.color?.rgbHex, DEFAULT_STAGE_LIGHTING.ambient.color),
      intensity: STAGE_LIGHT_CALIBRATION,
    },
    directionals: directionals.length > 0 ? directionals : DEFAULT_STAGE_LIGHTING.directionals.map((d) => ({ ...d })),
  };
}

/** Fetch a stage's exported render state; null when absent (fallback lighting applies). */
export async function fetchStageRenderState(stageId: string): Promise<StageRenderState | null> {
  try {
    const response = await fetch(`/stages/${stageId}/render-state.json`);
    if (!response.ok) return null;
    return (await response.json()) as StageRenderState;
  } catch {
    return null;
  }
}

// ------------------------------------------------------------------------------------------
// Scene rig: owns the three.js light objects and applies resolved state at stage mount.
// ------------------------------------------------------------------------------------------

export type StageLightingRig = {
  readonly ambient: THREE.AmbientLight;
  /** Grows on demand for stages with more than one positioned LObj (stff). */
  readonly directionals: THREE.DirectionalLight[];
};

/** Create the stage light objects (st00 fallback values) and attach them to the scene. */
export function createStageLightingRig(scene: THREE.Scene): StageLightingRig {
  const rig: StageLightingRig = {
    ambient: new THREE.AmbientLight(DEFAULT_STAGE_LIGHTING.ambient.color, DEFAULT_STAGE_LIGHTING.ambient.intensity),
    directionals: [],
  };
  scene.add(rig.ambient);
  applyResolvedStageLighting(scene, rig, DEFAULT_STAGE_LIGHTING);
  return rig;
}

/**
 * Apply resolved per-stage lighting to the scene: ambient + directional light
 * colors/intensities/positions, linear fog, and background/clear color.
 * Camera fov/near/far are returned in the resolved value for the camera owner
 * to apply (the battle camera rig owns the THREE.PerspectiveCamera).
 */
export function applyResolvedStageLighting(
  scene: THREE.Scene,
  rig: StageLightingRig,
  resolved: ResolvedStageLighting,
): void {
  scene.background = new THREE.Color(resolved.background);
  scene.fog = resolved.fog ? new THREE.Fog(resolved.fog.color, resolved.fog.near, resolved.fog.far) : null;

  rig.ambient.color.setHex(resolved.ambient.color);
  rig.ambient.intensity = resolved.ambient.intensity;

  for (const [index, source] of resolved.directionals.entries()) {
    let light = rig.directionals[index];
    if (!light) {
      light = new THREE.DirectionalLight(source.color, source.intensity);
      rig.directionals.push(light);
      scene.add(light);
    }
    light.color.setHex(source.color);
    light.intensity = source.intensity;
    light.position.set(source.position[0], source.position[1], source.position[2]);
    light.visible = true;
  }
  // Stages with fewer lights than a previously mounted stage: hide the extras.
  for (let index = resolved.directionals.length; index < rig.directionals.length; index += 1) {
    const light = rig.directionals[index];
    if (light) light.visible = false;
  }
}

/** Convenience wrapper: resolve exported JSON and apply it in one call at stage mount. */
export function applyStageRenderStateLighting(
  scene: THREE.Scene,
  rig: StageLightingRig,
  rs: StageRenderState | null | undefined,
): ResolvedStageLighting {
  const resolved = resolveStageLighting(rs);
  applyResolvedStageLighting(scene, rig, resolved);
  return resolved;
}
