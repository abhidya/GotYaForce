# tdc00..09.arc camera-animation decode (corrected 2026-08-01)

The ten bare HSD DATs loaded beside `tl00_mdl.arc` by `zz_0042a58_` are the
title montage's scene/camera resources. They are not actor motion banks: G RED and
Sasuke still animate through each borg family's group-5 stream.

## Structural correction

The earlier signature scan reported no AOBJ/FOBJ records because it assumed the AOBJ
flags word was a small integer. HSD uses a bitfield there. Following the actual camera
loader proves the archive layout:

```text
scene_data + 0x04 -> camera set
camera set[0]     -> static HSD_Camera/COBJ descriptor
camera set[1]     -> null-terminated camera-animation descriptor array
animation desc    -> [camera AOBJ, eye WOBJAnim, target WOBJAnim]
```

`zz_024631c_` loads those three animation objects into the live COBJ. `zz_024652c_`
requests a frame and `zz_02464dc_` interprets the camera/eye/target tracks.
`zz_00088a4_` is the title-side wrapper that performs those operations.

| archive | resource slot | end frame |
| --- | ---: | ---: |
| tdc00 | 12 | 39 |
| tdc01 | 13 | 23 |
| tdc02 | 14 | 60 |
| tdc03 | 15 | 49 |
| tdc04 | 16 | 49 |
| tdc05 | 17 | 80 |
| tdc06 | 18 | 31 |
| tdc07 | 19 | 49 |
| tdc08 | 20 | 29 |
| tdc09 | 21 | 29 |

The browser asset `apps/game/public/ui/scenes/tl00/tdc-camera-anims.json` contains
integer-frame samples evaluated with HSDRaw's `FOBJ_Player`, the same evaluator used by
the borg animation export. `TitleIntro.ts` applies those samples through the recovered
VM timeline.

Examples: tdc00 moves its eye from `(8,364.875,2595.125)` to
`(5.928,649.016,2075.563)`; tdc04 moves target Y from `-881.125` to `723.906`; tdc07
moves its target from `(-3419.375,-2584.125,-2688)` to
`(600.625,2265.125,-3609.125)` while FOV changes `41.539 -> 43.616`.

## VM semantics

- opcode `0x06` selects the scene resource (`0xff` = base `tl00`, 12..21 = tdc00..09).
- opcode `0x07` applies its initial COBJ frame immediately and arms current/target/step.
- opcode `0x08` yields until that COBJ frame is reached (`0xff` = timeline done).
- opcode `0x01` owns the screen-color effect; `0x07/0x08` are not fades.

The corrected fixed-frame execution reaches the end/Press Start gate at frame 1222.

## Residual

The paired tdc08/tdc09 targets identify subject anchors at X -1800 and +1800, Y -1300,
Z 2000. The port roots the figures 150 units below those targets on the authored floor
plane. This is source-derived placement, not a captured final JOBJ world matrix; that
final matrix remains the one visual trace gap.
