# tl00 authored scene camera (2026-07-04)

The title/desk scene's framing is AUTHORED INTO tl00_mdl.arc itself — no DOL placement
tables needed. Probed with HSDRaw (`PROBE_SCENE` mode added to
user-data/GG4E/gltf-export/Program.cs, gitignored):

```
root 'scene_data' size=16
  cameras: 1
  cam[0]: proj=PERSPECTIVE fov=41.538998 near=0.1 far=32768 roll=0
    eye=(5, 3557.153, -3145.1)  target=(5, 3557.153, -12625)
  lights: 3  fog: yes
  jobjDescs: 37
```

- The HSD scene_data SOBJ (`HSD_SOBJ`, tools/HSDLib/HSDRaw/Common/HSD_SOBJ.cs) carries a
  camera array at +0x04 (`HSD_Camera`/CObj, HSD_COBJ.cs) — eye/target are WOBJs.
- The 37 exported tl00 GLBs carry **world-space vertices** (e.g. model_05 spans
  x −4941..−3969 / z 5053..6004); full scene extent min(−4995, −1530, −1438) /
  max(5163, 3818, 8701). Mounting all 37 at identity reconstructs the authored room.
- Handedness: the authored camera looks toward −Z but the exported content sits at +Z —
  the exporter's GX→glTF conversion is the standard **180° Y-rotation** (x→−x, z→−z), so
  the camera converts to eye (−5, 3557.153, 3145.1) → target (−5, 3557.153, 12625).
  (Convention assumption labeled in TitleIntro.ts; a mirrored result would indicate a
  Z-negate instead.)
- Earlier negative result stands: the DOL menu cameras (zz_008c88c_ eye (0,0,100)→(0,0,−100),
  zz_008c9d4_ (0,0,0)→(0,0,−10)) are flat UI-plane cameras, not the desk framing.
- Remaining unextracted: the SOBJ's 3 authored lights + fog parameters (probe prints counts
  only) — TitleIntro lighting stays a TUNED warm-room approximation until dumped.

Wired in apps/game/src/ui/screens/TitleIntro.ts (3D desk backdrop layer over the captured
PNG, which remains the instant paint + failure fallback).

This resolves the "per-model desk framing needs the scene's object-placement tables
decoded" blocker in title-main-menu-flow.md — the placement was in the scene all along;
the intro-flow byte-code's camera cues (if any) remain undecoded.
