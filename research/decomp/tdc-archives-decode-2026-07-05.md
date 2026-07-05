# tdc00..09.arc decode (2026-07-05)

The 10 archives preloaded alongside `tl00_mdl.arc` by the front-end preload
`zz_0042a58_` (archive ids `0xa86..0xa8f`, per
`user-data/GG4E/afs_data/sys/afs_rebuild.csv`). The desk-intro script
(`DAT_8038a3ec`, opcode `0x02` waitForArchive) blocks on their attach before the
montage begins.

## Headline correction

**The tdc archives are NOT actor-animation banks.** A prior (2026-07-05) inference
guessed "anim/pose banks" from their high float density. A structural walk of the
object graph (this session, via `research/prototypes/hsd_walker.py`'s validated DAT
loader) finds **zero AObj/FObj signatures** — i.e. no HSD animation objects, no
keyframe tracks. They are SCENE-STATE fragments (a `scene_data` SCENE struct:
JOBJ/COBJ/LOB descriptors), not keyframed motion data.

## Structure (all 10 share the shape)

- **Format**: bare HSD DAT (no 0x100 wrapper). Header `{fileSize, dsize, relocCount
  (65-89), rootCount=1, extRef=0}`. Root name `scene_data`. Sizes 1.3-1.8 KB each.
  `tdc08` and `tdc09` are byte-identical.
- **Root `scene_data`** = the standard GF SCENE struct (4 leading reloc pointers ->
  4 sub-trees, matching the "3 cross-linked pointer tables" shape hsd_walker documents
  for GF `scene_data`). Sub-tree layout per tdc00:
  - `[0]`, `[1]`: linked node chains (descriptor records).
  - `[2]`: a 5-element pointer array (`0x3b8 -> 0x3b0, 0x3a0, 0x390, 0x380, 0x370`) —
    the **LOBJ (light) chain** shape.
  - `[3]`: a header node that cross-links `[0]`/`[1]`/`[2]` + a node offset (0x14c).
- **Sparse transform values** carried by some nodes (most are pointer-only/zero):
  - tdc00: `-1.0/-1.0/-1.0` (scale sentinel), `39.0` (frame count), light-direction
    floats matching tl00's authored lights (0.9625, 2.0371).
  - tdc03: `49.0` (frame count), `-177.728`, `-9729.222` (the latter a world coord in
    the tl00 scene's scale, extent ~±5000..12000).
- **No geometry**: zero POBJ/VtxDescList/POS hits (hsd_walker's `find_pobjs` returns
  empty). No textures (no TNAM/IMG). No bytecode (the script is in `DAT_8038a3ec` in
  boot.dol, not here).

## Verdict

Each tdc is a **per-beat scene descriptor** — a lighting/camera/desk-prop-state
fragment the front-end applies as the montage progresses. The script's `screenColor`/
`fade`/`toggleOverlay` opcodes drive the visible transitions; the tdc data supplies the
static scene state those opcodes modulate (light setups, camera cues, prop joint
poses). 10 archives = 10 scene-state patches across the ~150-frame intro.

## Implications for the port

1. **Actor animation source = the borg mot banks, NOT tdc.** The current TitleIntro
   wiring (load baked battle anims from `/models/plXXXX/anim_g0X_sNN_*.json`) is
   structurally correct. The residual TUNED item is the `groupSel=5 -> g0` mapping in
   `zz_0057ff8_(actor, 5, animId) -> zz_004beb8_(... groupSel=5, animId)`: the ROM's
   `groupSel=5` indexes the actor's `+0x1d80` anim-descriptor bank (populated at actor
   spawn from the borg's data). Confirming whether bank index 5 == the g0 battle bank
   needs reading the actor-spawn path (`zz_005809c_` / the family ctor that binds
   `+0x1d80`), not the tdc data.
2. **Actor world placement is NOT in tdc.** The `−9729` world coord in tdc03 is a
   scene-prop/camera placement, not an actor stand position. Actor placement most likely
   comes from the actor-spawn path (the same `Battle_SpawnActiveBorgFromSlotTables`
   family that reads `DAT_8038a4ec`) OR the tl00 scene's authored desk surface. The
   port's TUNED stage coords (`stageBaseForSlot`) stay until that spawn-path placement
   is decoded.
3. **`pl000amot.bin` absence explained**: Sasuke (pl000a) shares the Normal Ninja
   family motion bank (`pl0000mot.bin`) — the port's `pl000a` baked anims already
   derive from that family mot, so the battle-anim stand-in for Sasuke is valid.

## Decoder

`scripts/decode-tdc-archives.py` walks every tdc using `hsd_walker.py`'s DAT loader,
dumps the root scene_data + leading sub-trees, and runs an AObj/FObj signature scan
(the scan returns 0/0 — the negative result that corrected the hypothesis).

## Evidence

- DAT headers + root walks: `scripts/decode-tdc-archives.py` output (this session).
- GF `scene_data` SCENE-struct shape: `research/prototypes/hsd_walker.py:11-12,265-267`.
- AFS id mapping: `user-data/GG4E/afs_data/sys/afs_rebuild.csv:2695-2704` (tdc00..09 =
  0xa86..0xa8f).
- Script waitForArchive opcode: `research/decomp/ghidra-export/chunk_0055.c:2541`
  (`FUN_801c7f00`), and `apps/game/src/ui/intro/titleVm.ts` op_waitForArchive.
- Borg mot bank binding: `packages/formats/src/hsd-anim.ts`; family-mot convention per
  `research/format-specs/mot-animation-format.md`.
