# Particle-bank texId decode — efct00_mdl.arc JOBJDesc array (+ ptcl00.ptl notes)

**Date:** 2026-07-04
**Question:** the impact-effect chain's last unproven hop — what does an effect layer's
`texId` (values up to 146) index, and what does each entry look like?
**Answer:** DECODED, and the working hypothesis is REFUTED: texIds do **not** index
ptcl00.ptl. They index the **scene_data JOBJDesc array of `efct00_mdl.arc`** (157
entries), and the entries are **untextured vertex-colored GX meshes**, not sprite cells.
There is no "texId -> pixel cell" hop at all — there are no pixels.

---

## 1. The proven chain (all static, DERIVED)

### 1a. Bank buffer = efct.pzz member 1 = efct00_mdl.arc

`zz_0042878_ @80042878` (chunk_0005.c:113-141):

- `zz_000b07c_(..., 0x2b9, &DAT_803b0760, ...)` loads AFS file **0x2b9** to
  `DAT_803b0760 = base+0x7a3c00`. AFS index 0x2b9 in afs_data.afs is a 585,728-byte
  member whose bytes are a 3-member PZZ — the size and layout match **efct.pzz**
  exactly (verified by parsing the AFS TOC + the member bytes).
- efct.pzz members (packages/formats pzz.ts unpack):
  | member | bytes | identity |
  |---|---|---|
  | 0 | 32,832 | **efct00.tpl** (first word = TPL magic 0x0020af30; the 256x64 RGB5A3 atlas) |
  | 1 | 417,956 | **efct00_mdl.arc** (byte-identical to the standalone disc file through its full 417,955 bytes; 1 pad byte) |
  | 2 | 408,296 | **efct01_mdl.arc** (same check) |
- `DAT_803bb378 = base+0x7ac400` = load target + 0x8800 = member0 (0x8040) rounded to
  the 0x800 PZZ block grid -> **member 1, efct00_mdl.arc**.

### 1b. Bank object + archive parse

`zz_0042954_ @80042954` allocates the bank handle (`DAT_803bb374 = zz_0197a0c_(1)`, a
generic pool object — NOT itself the data) and calls `zz_0040eb4_ @80040eb4` ->
`zz_0006c88_ @80006c88` (chunk_0000.c:1312):

- `gnt4_HSD_ArchiveParse` on the buffer, then `HSD_ArchiveGetPublicAddress(root 0)` —
  the archive's single public root is **`scene_data`** (standard HSD SOBJ).
- `bank+0x10 = &sceneData`; the function then counts `sceneData->word0[]` (a
  NULL-terminated pointer array) into `bank+0x1a` (u16) — the **JOBJDesc array**, and
  `sceneData->word2[]` into `bank+0x18` (lights), `word3` presence into `+0x19` (fog).

### 1c. texId consumer

`zz_0006fb4_ @80006fb4` (chunk_0000.c:1511) — called by every effect variant handler:

```c
jobjDescArray = (**(int **)(bank + 0x10));       // scene_data word0
desc          = jobjDescArray[texId];             // JOBJDesc = {rootJoint, jointAnim, matAnim, shapeAnim}
gnt4_HSD_JObjLoadJoint(*desc);                    // instantiate the JOBJ tree
```

**=> texId is an index into efct00_mdl.arc's scene_data JOBJDesc array.**
That array has **157 entries** (texIds 0..156) — covering the impact chain's max texId
146 with room to spare (the remaining ids serve the other zz_0006fb4_ callers:
projectile/trail/status effects).

### 1d. What an entry is

Parsed with a from-scratch HSD DAT walker (scripts/gen-ptl-cell-map.mjs; reloc table
used as the authoritative pointer map):

- **Zero image data.** The archive contains no TOBJ, no HSD_Image descriptors, and no
  TEX0 vertex attribute anywhere (exhaustive scans). The bank draws **untextured
  geometry**.
- Each JOBJDesc -> 1..6 JOBJs (plain tree, no billboard flag bits set anywhere — the
  effect handlers orient the layers themselves) -> DOBJs -> POBJs.
- POBJ vertex formats (whole-bank census): POS f32 INDEX8/INDEX16, optional NRM f32,
  optional CLR0 **GX_RGBA8** INDEX8. Primitives: 0x98 tristrip, 0x90 triangles, 0x80 quads.
- MOBJ: material with a constant diffuse RGBA + alpha float; PE desc census:
  `(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE)` = **additive** on 155 MOBJs,
  `(…, GX_BL_INVSRCALPHA)` = normal alpha on 10, null (default alpha) on 98.
- Many entries carry a **matAnim** bank (AOBJ color/alpha tracks; texture-swap tables
  are all empty — consistent with "no textures"). NOT decoded — the port's scale/alpha
  animation comes from the boot.dol per-layer keyframe tracks already decoded in
  impact-effect-id-decode-2026-07-04.md.

### 1e. Validation against the known impact texIds

| texId | impact use (decoded) | bank entry (parsed bytes) | verdict |
|---|---|---|---|
| 21 | id-0 "big swelling flash" | POS-only radial spike-star mesh, r≈67, gray material, additive | ✓ a 3D flash star |
| 2 / 3 | id-1 per-player burst particle (row = attacker player index) | **identical** 14.4-radius disc geometry; white core verts + rim verts `[0,0,255,64]` (BLUE) on 2 vs `[255,0,128,64]` (PINK) on 3 | ✓ explains the per-player split: blue vs pink sparks |
| 144 / 145 | id 2-7 layers 0/1 (flash/core) | big radial spike shells (gray 178) | ✓ |
| 146 | id 2-7 layer 2 (delayed expanding ring) | **flat ring in the XY plane** (max abs z < 1e-3 of extent) with inner-alpha-0 -> outer-alpha-255 gradient | ✓ the ring, and it's directional (faces +Z) |
| 53 / 54 | id-8 slash core / anisotropic cross | radial spike star / ±X elongated cross spikes (x extent ±772) | ✓ matches the (0,1.5,1.5)->(1.5,0,0) collapse keys |

These checks are ASSERTED in scripts/gen-ptl-cell-map.mjs — the generator fails if the
bank bytes stop matching.

---

## 2. ptcl00.ptl — what it actually is (partial, bytes-only)

ptcl00.{ptl,ref,txg} is a SEPARATE system (the point-sprite particle emitters that use
the 8 txg images). Observed structure of `ptcl00.ptl` (2,370 bytes):

- Header: `u16 0x0043` (version/tag?), `u16 0`, `u32 0`, `u32 entryCount = 0x14` (20).
- Then 20 u32 entry offsets (0x60, 0x100, … 0x8e0), then `0xffffffff` terminator.
- `ptcl00.ref` = 20 u32s `0..19` — an identity remap table (texId->entry indirection
  for OTHER regions/files?).
- Entry header hypothesis (first 4 u16s, UNPROVEN): `[?, txgImageIndex, ?, lifeFrames]`
  — the second u16 is always < 8 (4, 5, 2, 6, 4 …) which fits the 8-image txg, and the
  fourth (0x32/0x64/0x28/0x19/5) reads as durations. Entry bodies mix f32 physics-ish
  values and packed RGBA bytes.
- The runtime loader/consumer of ptcl00.ptl was NOT located in the decomp corpus (no
  literal 0xb14-0xb16 AFS index constants — likely loaded via a table). Left as-is:
  nothing in the impact chain needs it.

**Correction to prior notes:** impact-effect-id-decode-2026-07-04.md §1d guessed
"texId indexes ptcl00.ptl entries (values up to 146; ptcl00.txg holds only 8 images)".
Wrong on both counts: ptcl00.ptl has only 20 entries, and the real bank (157 JOBJDescs)
holds meshes, not image references. The "cell map" concept dissolves — see
research/asset-inventory/ptcl00-cell-map.md for the updated role of the txg cells.

---

## 3. Port wiring (2026-07-04)

- **scripts/gen-ptl-cell-map.mjs** (name kept from the commission) parses
  efct00_mdl.arc and emits **apps/game/src/sim/data/efctBankMeshes.json**: all 157
  entries as `{ jobjs: [{parent, flags, t/r/s, dobjs: [{dif, alpha, blend, renderFlags,
  mesh: {positions, colors, indices}}]}], hasMatAnim }` (33,445 triangles total, ~819 KB;
  provenance + validation list in `_meta`).
- **apps/game/src/sim/battleScene.ts**: new `spawnBankFx(texId, pos, opts)` builds
  cached THREE.BufferGeometry per bank entry (vertex RGBA colors, material dif color,
  additive/alpha blend per the PE desc, ROM-unit scale) and `spawnHitFx` now renders
  texIds 21 / 2 / 3 / 144 / 145 / 146 / 53 / 54 from the real bank — the TUNED
  sprite-cell stand-ins remain ONLY as missing-entry fallbacks. The id-1 burst's TUNED
  team tint constants are deleted (the blue/pink rims are IN the bank vertex colors).
- Remaining TUNED in this area: linear approximation of multi-key curves (unchanged
  policy), burst scatter offsets (ROM uses random velocity seeds), and the yaw heuristic
  (victim facing / projectile direction) standing in for the ROM's attacker->contact
  orientation basis (zz_0045ef4_).

**Validation:** `pnpm typecheck` ✓, `packages/combat/dist/selfcheck.js` ✓,
`scripts/selfcheck-1p-challenge.mjs` ✓, `scripts/selfcheck-challenge-stages.mjs` ✓,
generator self-asserts (§1e) ✓.

**Next steps (if ever needed):** ~~decode the matAnim AOBJ color tracks~~ ~~resolve the
other zz_0006fb4_ call sites' texIds (projectiles, trails, status FX)~~ — BOTH DONE later
on 2026-07-04, see research/decomp/efct-consumers-decode-2026-07-04.md (muzzle/launch FX
family zz_00aedc0_, projectile visual rows FUN_8007dd84, slow/haste status clock
zz_013f300_, matAnim extraction + wiring). Remaining: locate the ptcl00.ptl loader to
decode the emitter bank.
