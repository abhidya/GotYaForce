# Gotcha Force `plXXXXmot.bin` — animation container format

> **Status:** DECODED and VALIDATED end-to-end (2026-06-30). Container structure decoded, per-joint FOBJ keyframe tracks extracted via HSDRaw, baked onto the model skeleton, and **playing/looping in the browser** (pl0615 "G RED", idle clip). See `apps/slice/index.html` + `apps/slice/models/pl0615/`.

## Summary

Each borg ships a model (`plXXXX_mdl.arc`, HSD DAT) and an animation file (`plXXXXmot.bin`). The `mot.bin` is **NOT itself a single DAT** — it is a custom Gotcha Force container holding many independent HSD DAT blobs (one per animation clip), indexed by a two-level big-endian offset table at the front. Each clip-blob is a self-contained HSD DAT whose roots are **`HSD_AnimJoint`** trees (the same `pl****_bNN_animjoint` structure as Melee character animations), and HSDRaw parses them with zero modification.

All multi-byte integers are **big-endian** (GameCube).

## Container layout

```
0x000  master table : 6 × u32  -> offsets of 6 "banks"   (categories of animation)
       (e.g. pl0615: 0x40, 0xAC, 0x11C, 0x188, 0x218, 0x230)
0x040  bank tables begin. Each bank = a list of u32 clip-blob offsets,
       terminated by 0xFFFFFFFF. A 0x00000000 entry = empty/missing clip slot
       (the index is reserved but no animation present).
0x240  first clip-blob (HSD DAT). All blobs are packed contiguously from here
       to EOF. A blob's length = (next blob/table entry offset) - (this offset).
```

- **Master table (6 entries):** 6 animation *banks* / categories. Counts vary per borg. (Bank semantics not yet fully labelled, but bank 0 holds the core locomotion set — entry 0 is a 60-frame full-body idle.)
- **Bank table:** sequence of u32 offsets into the blob region. `0x00000000` = empty slot, `0xFFFFFFFF` = end of bank. The non-zero, non-terminator entries are clip-blob offsets.
- Verified on `pl0615mot.bin` (size 0x56BC0) and `pl0000mot.bin` (size 0x59E20). **Confidence: Confirmed.**

Example (pl0615):
| Bank | Table off | Clip-blob offsets (non-empty) |
|---|---|---|
| 0 | 0x40 | 0x240, 0x1A40, 0x3680, 0x5200, 0x6D80, 0x8980, 0xA520, 0xBA00, 0xCFE0, 0xE3A0, 0xFB20, 0x10D00, 0x12860 |
| 1 | 0xAC | 0x13A40 … 0x37AC0 (23 clips) |
| 2 | 0x11C | (all empty) |
| 3 | 0x188 | 0x396A0 … 0x48460 (12 clips, interleaved with empty slots) |
| 4 | 0x218 | 0x49720, 0x4BA20, 0x4D560, 0x4F280, 0x512E0 |
| 5 | 0x230 | 0x52DA0, 0x55280 |

## Clip-blob = HSD DAT with AnimJoint roots

Each blob is a standard HSD DAT (HAL Sysdolphin), header at blob+0:
```
+0x00 u32 fileSize     (e.g. 0x17F0; ~= blob span rounded)
+0x04 u32 dataBlockSize
+0x08 u32 relocCount   (e.g. 0xCF = 207)
+0x0C u32 rootCount    (e.g. 0x14 = 20)
+0x10 u32 externalRefCount (0)
... [0x20 header][data block][reloc table][root entries][symbol table]
```
- **Roots:** typically **20** roots named `plXXXX_b00_animjoint` … `plXXXX_b19_animjoint`. Each root's data type is **`HSD_AnimJoint`** (confirmed by HSDRaw typing + symbol names).
- The 20 roots are **progressively-truncated views of the same skeleton**: `b00` is the FULL skeleton AnimJoint tree (its `TreeList` length == the model's main-body JOBJ count), `b01` drops the first node (25 vs 26), `b02` drops two, etc. **For playback you want `b00`** (= model_00, the main rigged body). The truncated variants are presumably for partial/attached sub-models or LOD.
  - pl0615: model_00 = **26** JOBJ; anim `b00` = **26** AnimJoint nodes → **exact 1:1 match**. (Best test case.)
  - pl0000: model_00 = 20 JOBJ; anim `b00` = 23 nodes → 3-node mismatch (anim tree has 3 extra trailing/effector nodes; bake clamps to min(20,23)=20).

## Per-joint tracks (HSD_AnimJoint → HSD_AOBJ → HSD_FOBJ)

Walking `HSD_AnimJoint.TreeList` (depth-first) gives one node per skeleton joint, in the **same depth-first order** as the model's `HSD_JOBJ` tree (and as `ModelExporter`'s `JOBJ_i` bone naming). Each animated joint has:
- `AOBJ.Flags`, `AOBJ.EndFrame` (clip length in frames; idle = 60).
- `AOBJ.FObjDesc.List` = list of `HSD_FOBJDesc` tracks. Each track has a **TrackType** (`JointTrackType`):
  `1=ROTX 2=ROTY 3=ROTZ`, `5=TRAX 6=TRAY 7=TRAZ`, `8=SCAX 9=SCAY 10=SCAZ` (and SETBYTE/SETFLOAT/PTCL etc. for non-transform tracks).
- Decode keys with HSDRaw's `FOBJ_Player(fobjDesc)` → `.GetValue(frame)` evaluates the compressed key stream (CON/LIN/SPL/SLP/KEY interpolation, Hermite splines) at any frame. Rotations are **radians**; translations in model units; scale unitless.

Rotation→matrix convention (from `HSDRawViewer Math3D.CreateMatrix4FromEuler`): **R = Rx·Ry·Rz** (intrinsic X then Y then Z). When baking to quaternions, build that matrix and convert (done in the C# baker), so the browser can apply quaternions directly with no Euler-order ambiguity.

**Confidence: Confirmed** (HSDRaw parses; `FOBJ_Player.GetValue` yields sane radian/unit values; baked onto skeleton it renders a correct, smoothly looping idle in three.js).

## Tooling / pipeline (this work)

- **Decode + bake:** `user-data/GG4E/anim-test/` (`anim-test.csproj` refs HSDRawViewer; `Bake.cs`, `Scan.cs`, `Probe.cs`).
  - `animtest.exe scan` — dumps model JOBJ counts vs anim root tree-node counts.
  - `animtest.exe exportmodel <arc> <skip> <modelIdx> <out.dae>` — exports rigged+skinned+textured Collada (bones named `JOBJ_i`).
  - `animtest.exe <mot.bin> <arc> <skip> <blobOffHex> <modelIdx> <out.json>` — extracts a clip-blob, loads with HSDRaw, bakes per-bone TRS **per frame** (rest pose overridden by FOBJ tracks), emits JSON: `{frameCount, fps:60, rotFormat:"quat_xyzw", bones:[{i, pos:[xyz…], rot:[xyzw…], scl:[xyz…]}]}`. Bone `i` ↔ Collada node `JOBJ_i`.
- **Repeatable repo script:** `node scripts/export-borg-animation-hsd.mjs GG4E pl0615` regenerates `apps/game/public/models/pl0615/anim_b00_idle.json` from blob `0x240` and `anim_b00_clip1.json` from blob `0x1a40`. Additional clips use `offset[:filename]`, for example `node scripts/export-borg-animation-hsd.mjs GG4E pl0615 0x240:idle.json`.
- **Browser:** `apps/slice/index.html` builds a `THREE.AnimationClip` (Quaternion/VectorKeyframeTrack per `JOBJ_i.{quaternion,position,scale}`) and plays it on the loaded Collada skeleton via `THREE.AnimationMixer`, looping. Keys 1/2 switch clips.

## Remaining / not yet done
- Bank/clip semantic labels (which index is walk vs each attack) — only verified bank0[0] is a full-body 60-frame idle by inspection.
- pl0000-style 3-extra-node anim trees: confirm whether the extra nodes are effectors to skip or map to hidden JOBJs. (pl0615 has none — exact match.)
- Material/texture (`HSD_A_J_NODE`/MatAnim) and PTCL tracks are present in the enum but not consumed (transform-only playback).
- Frame-rate assumed 60 fps (GameCube NTSC); EndFrame is in frames.
