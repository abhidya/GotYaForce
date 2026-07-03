# Stage Lighting / Render-State Port Report

Date: 2026-07-02

## Status

DATA COMPLETE 40/40, RUNTIME WIRED 40/40 (single-light path), MODULE READY.

- Every browser stage directory (`apps/game/public/stages/<stXX>/render-state.json`, 40/40)
  already carries the exported HSD scene render state (camera CObj, LObj lights, FogDesc),
  produced by `scripts/export-stage-render-state.mjs` from
  `research/asset-inventory/stage-lighting-render-state.json`. No re-export was needed.
- The runtime mount point (`apps/game/src/main.ts` `loadStage` -> `applyStageRenderState`)
  already fetches `render-state.json` per stage and applies ambient + directional colors,
  directional position, fog color/start/end, background (clear) color, and camera
  fov/near/far, falling back to the st00-derived `DEFAULT_RENDER_STATE`.
- New canonical module: `apps/game/src/stages/lighting.ts`. It owns the exported-JSON ->
  three.js translation (typed shapes, `resolveStageLighting`, `createStageLightingRig`,
  `applyResolvedStageLighting`, `fetchStageRenderState`) and fixes the one gap in the
  inline main.ts resolver: stages with more than one positioned LObj (`stff` has two)
  keep only the first directional in main.ts, while the module drives all of them.
- Resolver validated at runtime against all 40 on-disk `render-state.json` files plus the
  null-fallback path (transpiled module run under node; 40/40 stages resolved with exact
  color/position/fog/camera matches, `stff` resolved 2 directionals).

## Calibration

`STAGE_LIGHT_CALIBRATION = 1.0` (TUNED, in `apps/game/src/stages/lighting.ts`). HSD LObj
descriptors carry colors but no scalar intensity; with three.js r169 and the exported DAE
materials, intensity 1.0 for both the ambient and directional channels reproduces a
readable image across all 40 stages (this matches the already-shipping main.ts behavior
of `intensity = 1`). Any future global brightness correction goes through this single
constant — never per-stage fudging.

## Integration still needed (main.ts is owned elsewhere)

The stage-lighting mount point is main.ts-only, so main.ts was not edited. To move it
onto the module, replace the inline helpers (`parseHexColor`, `stageVector`,
`extractedLights`, `legacyLights`, `resolveAmbientLight`, `resolveDirectionalLight`,
`applyStageRenderState`) and the `stageAmbient`/`stageLight` globals with:

```ts
import { createStageLightingRig, applyStageRenderStateLighting } from "./stages/lighting";

const stageLighting = createStageLightingRig(scene); // replaces stageAmbient/stageLight setup

// in loadStage(), replacing applyStageRenderState(renderState):
const resolved = applyStageRenderStateLighting(scene, stageLighting, renderState);
camera.fov = resolved.camera.fovDegrees;
camera.near = resolved.camera.near;
camera.far = resolved.camera.far;
camera.updateProjectionMatrix();
```

Behavior is identical for 39/40 stages; `stff` additionally gains its second directional.

## Per-stage exported values (DERIVED from stage archive scan)

Source: `research/asset-inventory/stage-lighting-render-state.md` scan of
`user-data/GG4E/afs_data/root/st??_mdl.arc` scene tables, exported to
`apps/game/public/stages/<id>/render-state.json`. All stages use HSD/GX fog type 2
(GX_FOG_LIN = linear fog, exact `THREE.Fog` match). Background/clear color = fog color.
"Wired" = consumed at stage mount by `loadStage` today; the lighting module resolves the
same values (plus multi-light support).

| Stage | Ambient | Directional(s) @ position | Fog color | Fog range | FOV | near/far | Wired |
|---|---|---|---|---|---:|---|---|
| st00 | #d8d0c2 | #fff0e6 @ (-386, 956, -378) | #fff6e5 | 900–40000 | 43.19 | 10/80000 | yes |
| st01 | #cccccc | #ffeccc @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st02 | #b3b3b3 | #ffffff @ (-1139, 4763, -1977) | #b8cff0 | 2000–40000 | 47.57 | 10/40000 | yes |
| st03 | #cccccc | #ffe6cc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st04 | #9999cc | #ffffff @ (-1139, 4763, -1977) | #e5ffec | 2000–40000 | 41.00 | 10/40000 | yes |
| st05 | #cccccc | #fff3cc @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st06 | #a39380 | #ffffff @ (-1139, 4763, -1977) | #41302c | 900–40000 | 41.00 | 10/40000 | yes |
| st07 | #a39380 | #ffffff @ (-1139, 4763, -1977) | #371a3d | 2000–40000 | 38.03 | 10/40000 | yes |
| st08 | #b3b3b3 | #ffffff @ (-878, 4467, 4953) | #868890 | 2000–40000 | 41.00 | 10/40000 | yes |
| st09 | #cccccc | #fff9ec @ (-10000, 15000, -10000) | #b3d3d9 | 1000–25000 | 45.00 | 10/40000 | yes |
| st0a | #cccccc | #fff9e0 @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st0b | #a39380 | #ffffff @ (-16107, 17119, 13471) | #e8ffe8 | 2000–40000 | 41.00 | 10/40000 | yes |
| st0c | #cccccc | #ffe6cc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st0d | #cccccc | #ffeccc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st0e | #b3b3b3 | #fff3cc @ (-417, 15000, -572) | #ffe1ee | 2000–40000 | 41.00 | 10/40000 | yes |
| st0f | #cccccc | #fff3cc @ (-10000, 15000, -10000) | #ffc08c | 2000–40000 | 45.00 | 10/40000 | yes |
| st10 | #b3b3b3 | #ffffff @ (0, 9465, 1) | #000000 | 2000–40000 | 41.00 | 10/40000 | yes |
| st20 | #d8d0c2 | #fff0e6 @ (-386, 956, -378) | #fff6e5 | 900–40000 | 43.19 | 10/80000 | yes |
| st21 | #cccccc | #ffeccc @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st22 | #b3b3b3 | #ffffff @ (-1139, 4763, -1977) | #b8cff0 | 2000–40000 | 37.28 | 10/40000 | yes |
| st23 | #cccccc | #ffe6cc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st24 | #9999cc | #ffffff @ (-1139, 4763, -1977) | #e5ffec | 2000–40000 | 41.00 | 10/40000 | yes |
| st25 | #cccccc | #fff3cc @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st29 | #cccccc | #fff9ec @ (-10000, 15000, -10000) | #b3d3e6 | 1000–25000 | 45.00 | 10/40000 | yes |
| st2a | #cccccc | #fff9e0 @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st2b | #a39380 | #ffffff @ (-16107, 17119, 13471) | #e8ffe8 | 2000–40000 | 41.00 | 10/40000 | yes |
| st2c | #cccccc | #ffe6cc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st2e | #b3b3b3 | #fff3cc @ (-417, 15000, -572) | #ffe1ee | 2000–40000 | 41.00 | 10/40000 | yes |
| st40 | #d8d0c2 | #fff0e6 @ (-386, 956, -378) | #fff6e5 | 900–40000 | 43.19 | 10/80000 | yes |
| st41 | #cccccc | #ffeccc @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st42 | #b3b3b3 | #ffffff @ (-1139, 4763, -1977) | #b8cff0 | 2000–40000 | 73.80 | 10/40000 | yes |
| st43 | #cccccc | #ffe6cc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st44 | #9999cc | #ffffff @ (-1139, 4763, -1977) | #e5ffec | 2000–40000 | 41.00 | 10/40000 | yes |
| st45 | #cccccc | #fff3cc @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st49 | #cccccc | #fff9ec @ (-10000, 15000, -10000) | #e6d3b9 | 1000–25000 | 45.00 | 10/40000 | yes |
| st4a | #cccccc | #fff9e0 @ (-10000, 15000, -10000) | #cce6cc | 2000–40000 | 45.00 | 10/40000 | yes |
| st4b | #a39380 | #ffffff @ (-16107, 17119, 13471) | #e8ffe8 | 2000–40000 | 41.00 | 10/40000 | yes |
| st4c | #cccccc | #ffe6cc @ (-10000, 15000, -10000) | #cce6cc | 12000–50000 | 45.00 | 10/40000 | yes |
| st4e | #b3b3b3 | #fff3cc @ (-417, 15000, -572) | #ffe1ee | 2000–40000 | 41.00 | 10/40000 | yes |
| stff | #988cb2 | #808080 @ (-3, 2, 1); #808080 @ (1, 2, -1) | #2ac4bc | 1000000–2000000 | 41.54 | 0.1/32768 | partial (2nd light needs module) |

Notes:

- `stff` (test/versus stage) is the only stage with two positioned LObjs; the inline
  main.ts resolver keeps only the first, the new module drives both. Its fog starts at
  1e6 (beyond the 32768 far plane), i.e. effectively disabled — matches the original data.
- All light entries carry LObj flags `0x40000` (ambient/global channel color, no WObj
  position) or `0xd0000` (positioned diffuse/specular light); the module classifies by
  presence of a finite position, with role text as a legacy fallback.
- Intensities are not present in the HSD data (GX lights are color-only); see the
  Calibration section.

## Unresolved / out of scope

- HSD MObj/PEDesc raw material state (cull/blend/Z/alpha) is still not decoded; stage
  materials keep the exported-DAE values plus the blanket DoubleSide/metalness=0
  overrides in main.ts.
- The exported CObj eye/interest are load-time scene-camera values; gameplay camera
  placement stays with `sim/camera.ts` (only fov/near/far are taken from the CObj).
