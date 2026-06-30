# Stage Lighting And Render State Inventory

Generated: `2026-06-30T07:47:27.124Z`
Scanner: `scripts/inventory-stage-lighting.mjs`

## Inputs

- Disc root: `user-data/GG4E/afs_data/root`
- Browser stages: `apps/game/public/stages`
- Format specs: `research/format-specs/arc-hsd-format.md`, `research/format-specs/mot-animation-format.md`, `research/format-specs/re-wiki-gotcha-force.md`
- Symbol map: `research/symbols/GG4E-CSM-20220412.map`
- Boot DOL: `user-data/GG4E/disc/sys/boot.dol` (3888928 bytes)

## Summary

- Stage ARC files scanned: 40
- Same scene pointer pattern: 40/40
- st00 JOBJDesc/model count: 40
- st00 camera candidates: 1
- st00 light candidates: 2
- st00 fog candidates: 1
- st00 POBJ draw-state candidates: 72
- st00 exported DAE materials: 70

## st00 Scene Evidence

`user-data/GG4E/afs_data/root/st00_mdl.arc` root `scene_data` is at data offset `0x7571c` / file offset `0x7573c`. Its four relocation-marked fields point to JOBJDesc, CObj, LObj, and Fog table candidates.

| Field | Target data offset | Target file offset | Interpretation |
|---:|---:|---:|---|
| 0 | `0x7561c` | `0x7563c` | JOBJDesc table |
| 1 | `0x756c8` | `0x756e8` | CObj/camera table |
| 2 | `0x756f0` | `0x75710` | LObj/light table |
| 3 | `0x75704` | `0x75724` | Fog table |

## Camera

Source: `user-data/GG4E/afs_data/root/st00_mdl.arc` data `0x75278` / file `0x75298`.

| Field | Value |
|---|---:|
| Projection | perspective |
| Viewport/scissor | 640x480 / 640x480 |
| Eye | [10087.730469, 9489.730469, 9746.232422] |
| Interest | [578.34082, -1718.759033, 452.259888] |
| Near | 10 |
| Far | 80000 |
| FOV degrees | 43.191872 |
| Aspect | 1.333333 |

## Lights

| Index | Role | Flags | Color | Position | Source |
|---:|---|---:|---|---|---|
| 0 | ambient/global color candidate | `0x40000` | `#d8d0c2` [216,208,194,0] | not present | `0x75234` / `0x75254` |
| 1 | positioned diffuse/specular light candidate | `0xd0000` | `#fff0e6` [255,240,230,0] | [-385.512512, 956.0448, -377.986603] | `0x75218` / `0x75238` |

## Fog

Source: `user-data/GG4E/afs_data/root/st00_mdl.arc` data `0x752b0` / file `0x752d0`.

| Field | Value |
|---|---:|
| Type | 2 |
| Start | 900 |
| End | 40000 |
| Color | `#fff6e5` [255,246,229,255] |

## Materials And Draw State

The scanner found 72 HSD_POBJ draw-state candidates in `st00_mdl.arc` by the confirmed VtxDescList + GX display-list signature. These include raw POBJ flags and display-list counts; raw MObj/PEDesc material offsets remain unresolved.

| POBJ data | POBJ file | Flags | Display lists | First opcode |
|---:|---:|---:|---:|---|
| `0x9a0` | `0x9c0` | `0x8000` | 15 | GX_TRIANGLESTRIP `0x98` |
| `0x1d40` | `0x1d60` | `0x0000` | 24 | GX_TRIANGLESTRIP `0x98` |
| `0x23c0` | `0x23e0` | `0x0000` | 13 | GX_QUADS `0x80` |
| `0x3440` | `0x3460` | `0x8000` | 10 | GX_TRIANGLES `0x90` |
| `0x34a0` | `0x34c0` | `0x8000` | 1 | GX_TRIANGLESTRIP `0x98` |
| `0x3840` | `0x3860` | `0x8000` | 27 | GX_TRIANGLES `0x90` |
| `0x4900` | `0x4920` | `0x8000` | 11 | GX_TRIANGLES `0x90` |
| `0x4960` | `0x4980` | `0x8000` | 1 | GX_TRIANGLESTRIP `0x98` |

Exported Collada material evidence exists in `apps/game/public/stages/st00/model`: 40 DAE files, 70 materials.

- Distinct ambient values: `0.8 0.68235296 0.5019608 1` (18), `1 1 1 1` (16), `0.6 0.5803922 0.5803922 1` (8), `0.5019608 0.5019608 0.5019608 1` (6), `0.7529412 0.6509804 0.5019608 1` (4), `0.8392157 0.7372549 0.5882353 1` (4), `0 0 0 1` (2), `0.6 0.5411765 0.5019608 1` (2)
- Distinct diffuse textures: `Texture_0_I4-image_sampler` (23), `Texture_0_CMP-image_sampler` (14), `Texture_1_CMP-image_sampler` (8), `Texture_0_I4-image_0_sampler` (4), `Texture_1_CMP-image_0_sampler` (3), `Texture_0_CMP-image_0_sampler` (2), `Texture_2_CMP-image_sampler` (2), `Texture_2_I4-image_sampler` (2)
- Distinct specular values: `1 1 1 1` (70)
- Distinct transparency values: `1` (52), `0.999` (17), `0.660606` (1)

## Browser Fakes To Replace

- PerspectiveCamera uses hard-coded fov/near/far and position.
- HemisphereLight and two DirectionalLight objects are hand-tuned browser lighting.
- Stage/player materials are forced DoubleSide and metalness=0.
- Browser main.ts has no scene.fog assignment.

| Line | Code |
|---:|---|
| 178 | `scene.background = new THREE.Color(0x0d1724);` |
| 180 | `const camera = new THREE.PerspectiveCamera(48, window.innerWidth / window.innerHeight, 1, 80000);` |
| 181 | `camera.position.set(950, 520, 1320);` |
| 187 | `scene.add(new THREE.HemisphereLight(0xd8ecff, 0x243446, 2.1));` |
| 188 | `const key = new THREE.DirectionalLight(0xffffff, 1.6);` |
| 191 | `const fill = new THREE.DirectionalLight(0x9fc8ff, 0.85);` |
| 424 | `material.side = THREE.DoubleSide;` |
| 425 | `if ("metalness" in material) material.metalness = 0;` |
| 434 | `camera.position.set(950, 520, 1320);` |
| 463 | `material.side = THREE.DoubleSide;` |
| 464 | `if ("metalness" in material) material.metalness = 0;` |

## Replacement Targets

- Replace `THREE.PerspectiveCamera(48, aspect, 1, 80000) and camera.position.set(950, 520, 1320)`: Use CObj fov 43.191872, near 10, far 80000, aspect 1.333333; eye [10087.730469, 9489.730469, 9746.232422] and interest [578.34082, -1718.759033, 452.259888] need runtime camera-override confirmation. Confidence: high for load-time CObj, medium for gameplay camera replacement.
- Replace `HemisphereLight and two DirectionalLight browser fakes`: Use HSD LObj descriptors: L0 ambient/global color candidate #d8d0c2; L1 positioned diffuse/specular light candidate #fff0e6. Confidence: high.
- Replace `absence of scene fog in apps/game/src/main.ts`: Use HSD FogDesc type 2, start 900, end 40000, color #fff6e5. Confidence: high.
- Replace `material.side = THREE.DoubleSide and material.metalness = 0 blanket overrides`: Use original HSD MObj/PEDesc cull/blend/Z/alpha/material fields after raw offsets are decoded; exported DAE material colors/textures are available now as medium-confidence material evidence. Confidence: medium.

## Other Stage Pattern

st00 follows the same scene_data root pattern as the other scanned stage arcs.

| Stage | JOBJDesc | Cameras | Lights | Fogs | POBJ | DAE materials |
|---|---:|---:|---:|---:|---:|---:|
| `st00` | 40 | 1 | 2 | 1 | 72 | 70 |
| `st01` | 78 | 1 | 2 | 1 | 117 | 87 |
| `st02` | 51 | 1 | 2 | 1 | 77 | 0 |
| `st03` | 43 | 1 | 2 | 1 | 65 | 0 |
| `st04` | 52 | 1 | 2 | 1 | 108 | 0 |
| `st05` | 28 | 1 | 2 | 1 | 56 | 0 |
| `st06` | 4 | 1 | 2 | 1 | 9 | 0 |
| `st07` | 4 | 1 | 2 | 1 | 8 | 0 |
| `st08` | 52 | 1 | 2 | 1 | 104 | 0 |
| `st09` | 9 | 1 | 2 | 1 | 15 | 0 |
| `st0a` | 43 | 1 | 2 | 1 | 64 | 0 |
| `st0b` | 28 | 1 | 2 | 1 | 112 | 0 |
| `st0c` | 20 | 1 | 2 | 1 | 41 | 0 |
| `st0d` | 17 | 1 | 2 | 1 | 31 | 0 |
| `st0e` | 43 | 1 | 2 | 1 | 132 | 0 |
| `st0f` | 13 | 1 | 2 | 1 | 25 | 0 |
| `st10` | 7 | 1 | 2 | 1 | 8 | 0 |
| `st20` | 40 | 1 | 2 | 1 | 72 | 0 |
| `st21` | 78 | 1 | 2 | 1 | 117 | 0 |
| `st22` | 51 | 1 | 2 | 1 | 77 | 0 |
| `st23` | 43 | 1 | 2 | 1 | 65 | 0 |
| `st24` | 52 | 1 | 2 | 1 | 108 | 0 |
| `st25` | 28 | 1 | 2 | 1 | 56 | 0 |
| `st29` | 9 | 1 | 2 | 1 | 15 | 0 |
| `st2a` | 43 | 1 | 2 | 1 | 64 | 0 |
| `st2b` | 28 | 1 | 2 | 1 | 112 | 0 |
| `st2c` | 20 | 1 | 2 | 1 | 41 | 0 |
| `st2e` | 43 | 1 | 2 | 1 | 132 | 0 |
| `st40` | 40 | 1 | 2 | 1 | 72 | 0 |
| `st41` | 78 | 1 | 2 | 1 | 117 | 0 |
| `st42` | 51 | 1 | 2 | 1 | 77 | 0 |
| `st43` | 43 | 1 | 2 | 1 | 65 | 0 |
| `st44` | 52 | 1 | 2 | 1 | 108 | 0 |
| `st45` | 28 | 1 | 2 | 1 | 56 | 0 |
| `st49` | 9 | 1 | 2 | 1 | 15 | 0 |
| `st4a` | 43 | 1 | 2 | 1 | 64 | 0 |
| `st4b` | 28 | 1 | 2 | 1 | 112 | 0 |
| `st4c` | 20 | 1 | 2 | 1 | 41 | 0 |
| `st4e` | 43 | 1 | 2 | 1 | 132 | 0 |
| `stff` | 83 | 1 | 3 | 1 | 184 | 0 |

## Runtime Symbols

Relevant render-state symbols in the map:

- `0x8022a310` size `0x00000224` gnt4-GXSetFog-bl
- `0x8022a6e4` size `0x00000124` gnt4-GXSetFogRangeAdj-bl
- `0x80240f90` size `0x0000023c` gnt4-HSD_SetupChannelMode-bl
- `0x802411cc` size `0x000001d0` gnt4-HSD_SetupRenderModeWithCustomPE-bl
- `0x8024139c` size `0x00000074` gnt4-HSD_SetMaterialColor-bl
- `0x80241410` size `0x00000010` gnt4-HSD_SetMaterialShininess-bl
- `0x80241420` size `0x0000003c` gnt4-HSD_StateSetCullMode-bl
- `0x8024145c` size `0x000000a0` gnt4-HSD_StateSetBlendMode-bl
- `0x802414fc` size `0x00000090` gnt4-HSD_StateSetZMode-bl
- `0x8024158c` size `0x000000b0` gnt4-HSD_StateSetAlphaCompare-bl
- `0x8024163c` size `0x00000048` gnt4-HSD_StateSetColorUpdate-bl
- `0x80241684` size `0x00000048` gnt4-HSD_StateSetAlphaUpdate-bl
- `0x802416cc` size `0x0000006c` gnt4-HSD_StateSetDstAlpha-bl
- `0x80241738` size `0x00000048` gnt4-HSD_StateSetZCompLoc-bl
- `0x80241780` size `0x00000048` gnt4-HSD_StateSetDither-bl
- `0x80241918` size `0x000003a4` gnt4-HSD_SetupChannel-bl
- `0x80241cbc` size `0x000000f8` gnt4-HSD_DisableChannelLighting-bl
- `0x80241db4` size `0x00000040` gnt4-HSD_StateSetNumChans-bl
- `0x80241e24` size `0x00000030` gnt4-HSD_StateSetNumTexGens-bl
- `0x80241e94` size `0x00000030` gnt4-HSD_StateSetNumTevStages-bl
- `0x80243ffc` size `0x00000008` gnt4-HSD_LObjGetLightMaskDiffuse-bl
- `0x80244004` size `0x00000008` gnt4-HSD_LObjGetLightMaskAlpha-bl
- `0x8024400c` size `0x00000008` gnt4-HSD_LObjGetLightMaskSpecular-bl
- `0x80244014` size `0x00000008` gnt4-HSD_LObjGetNbActive-bl
- `0x8024401c` size `0x00000048` gnt4-HSD_LObjGetActiveByID-bl
- `0x80244064` size `0x0000002c` gnt4-HSD_LObjGetActiveByIndex-bl
- `0x802442dc` size `0x00000124` gnt4-HSD_LObjGetLightVector-bl
- `0x80244400` size `0x00000164` gnt4-HSD_LObjSetup-bl
- `0x80244564` size `0x00000278` gnt4-HSD_LObjSetupSpecularInit-bl
- `0x802447dc` size `0x00000bbc` gnt4-HSD_LObjSetupInit-bl
- `0x802456d8` size `0x00000034` gnt4-HSD_LObjGetCurrentByType-bl
- `0x80245868` size `0x0000020c` gnt4-HSD_LObjRemoveAll-bl
- `0x80245a74` size `0x0000000c` gnt4-HSD_LObjSetColor
- `0x80245a8c` size `0x00000040` gnt4-HSD_LObjGetPosition-bl
- `0x80245acc` size `0x00000040` gnt4-HSD_LObjGetInterest-bl
- `0x80245f20` size `0x000000f0` gnt4-HSD_LObjLoadDesc-bl
- `0x80246ab8` size `0x000000cc` gnt4-HSD_CObjSetupViewingMtx-bl
- `0x80246b84` size `0x00000504` gnt4-HSD_CObjSetCurrent-bl
- `0x80247088` size `0x00000024` gnt4-HSD_CObjEndCurrent-bl
- `0x802470ac` size `0x00000040` gnt4-HSD_CObjGetInterestWObj-bl
- ... 34 more entries in JSON.

## Unresolved Questions

- Raw HSD MObj/PEDesc material and cull/blend/Z-mode offsets were not fully decoded here; use HSDRaw or a focused parser pass before importing those fields.
- Scene LObj flag bit names need confirmation against HSD headers or a small runtime HSD_LObjSetup capture; this report records raw flags and colors.
- Camera eye/interest descriptors look like original CObj/WObj data, but in-game battle camera may override them after scene load; confirm with the existing CObj breakpoints before replacing gameplay camera behavior.
- No broad Dolphin logs were run. If runtime proof is needed, use one-frame breakpoints on HSD_CObjSet*, HSD_LObjSetup, HSD_FogSet, HSD_SetMaterialColor, and HSD_StateSet* only.
