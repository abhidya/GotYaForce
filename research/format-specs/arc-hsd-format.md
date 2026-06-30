# Gotcha Force `.arc` model format — HSD DAT (HAL Sysdolphin)

> **Status:** Container CONFIRMED as HSD DAT (validated 2026-06-30 on real GG4E disc data). Internal node graph = HSD-family, walk-and-export validation pending.
> **This is the breakthrough on the project's critical-path blocker (the 3D model format).**

## Source of evidence
Extracted from the user's GG4E disc → `afs_data.afs` → 1369 `.arc` files in `user-data/GG4E/afs_data/root/`. All facts below are computed from those real bytes; reproduction scripts in `/tmp/hsd_check.py`, `/tmp/pl_probe.py`, `/tmp/hsd_roots.py` (re-runnable).

## Two populations of `.arc`

| Population | Count | Examples | Layout |
|---|---|---|---|
| **Bare HSD DAT** | 182 | `arrow_mdl.arc`, `deck00_mdl.arc`, `box00_mdl.arc`, `collision.arc`, `cnd000_mdl.arc` | DAT header at offset 0 |
| **Wrapped HSD DAT** (`pl****_mdl.arc`) | 1187 | `pl0000_mdl.arc`, `pl0f06k_mdl.arc`, `pl0505k_mdl.arc` | 0x100-byte wrapper, then DAT at offset 0x100 |

The `pl****` files are the **borg/character models** (the most important assets). Suffix variants seen: none/`b`/`c`/`g`/`k`/`s` (LOD or part variants — e.g. `k` files are smallest, likely low-detail/icon).

## HSD DAT header (standard HAL Sysdolphin, big-endian)

At the DAT base (0x0 for bare, 0x100 for wrapped):

| Off | Field | `arrow_mdl.arc` | Meaning |
|---|---|---|---|
| 0x00 | `fileSize` | 0x0B57 (=2903, == file size) | total DAT size |
| 0x04 | `dataBlockSize` | 0x09F8 | size of data block → reloc table at base+0x20+dataBlockSize |
| 0x08 | `relocCount` | 0x4B (75) | # of 4-byte pointer fixups in reloc table |
| 0x0C | `rootCount` | 0x01 | # public root nodes |
| 0x10 | `externalRefCount` | 0x00 | # external-reference nodes |
| 0x14–0x1C | reserved/version | 0 | — |

Layout: `[0x20 header][data block][reloc table: relocCount×u32][roots: rootCount×8][extRefs: extRef×8][symbol/string table]` → sums exactly to `fileSize`. Validated on all 182 bare files (fileSize == on-disk size, layout fits).

**Root node entry (8 bytes):** `u32 dataOffset`, `u32 stringOffset` (offset into symbol table). For every `.arc`, rootCount=1 and the root name is **`scene_data`**.

## The `pl****` wrapper (0x100 bytes)

| Off | Value (`pl0f06k`) | Meaning (hypothesis) |
|---|---|---|
| 0x00 | 0x100 | offset to embedded HSD DAT (== wrapper size) |
| 0x04 | 0x20 | unknown (header/table size?) |
| 0x08 | 0xC0 | unknown |
| 0x20 | 0x01FFFF00 FFFF0000 | small marker/table — possibly LOD/part or palette descriptor (Speculative) |
| 0x100 | HSD DAT begins (first u32 == filesize-0x100) | payload |

Detection rule: `u32@0 == 0x100 && u32@0x100 == filesize-0x100` → wrapped; else bare.

## Node graph (to validate)

`scene_data` root → sysdolphin scene struct → model set(s) → **JOBJ** (joint tree / skeleton) → **DOBJ** (display objects / meshes) → **POBJ** (polygon objects: GX display lists, vertex attribute descriptors) → **TOBJ/IMG** (textures, likely referencing the sibling `.tpl` files or embedded). This is the standard Melee/HSD model graph. GF may use game-specific fields inside `scene_data`, but the container + node typing is HSD.

## Why this matters
The project's dominant cost (research Phases 5–6, ~14–26 person-weeks "from scratch") is potentially collapsible: the **mature Melee modding toolchain (HSDRaw, HSDLib) already parses this container and exports JOBJ models to glTF/OBJ.** If GF's `scene_data` graph is HSD-standard, model recovery becomes "adapt an existing parser," not "RE from zero."

## Confidence
- Container = HSD DAT: **Confirmed** (5-field header match + symbol-table root-name read succeeds on 182+ files; wrapper decoded).
- Internal JOBJ/DOBJ/POBJ graph = Melee-compatible: **Likely**, pending an actual HSDRaw/HSDLib parse + visual export.
- Note: this *supports* the "ARC = HSD Files" wiki label. It does NOT resurrect the separately-refuted claim "HSD statically linked into boot.dol" — file-format lineage and static-linkage are different claims.

## RESULT — GO. The model blocker is solved at the parse level (validated 2026-06-30)

Cloned `Ploaj/HSDLib`, built `HSDRaw` (netstandard2.0) with the only installed SDK (.NET 2.1), wrote a netcoreapp2.1 console probe. **HSDRaw parses Gotcha Force `.arc` files with ZERO modification.**

- HSDRaw natively types the `scene_data` root as **`HSD_SOBJ`** (standard HAL sysdolphin Scene Object). Descent path: `HSD_SOBJ.JOBJDescs[]` → `HSD_JOBJDesc.RootJoint` (`HSD_JOBJ`) → JOBJ tree (`Child`/`Next`) → `HSD_DOBJ` (mesh) → `HSD_POBJ` (GX display list) → `GX_VertexAccessor.GetDecodedVertices`.
- `HSD_JOBJDesc` also carries `JointAnimations`, `MaterialAnimations`, `ShapeAnimations` in the same struct — **animation data ships with each model.**
- Vertex attributes are standard GX (`GX_INDEX8/INDEX16/DIRECT`), decoded cleanly.

Node-count probe:
| File | Models(JOBJDesc) | Bones(JOBJ) | Meshes(DOBJ) | POBJ | Materials | DL bytes | Anims |
|---|---|---|---|---|---|---|---|
| deck00_mdl.arc | 175 | 210 | 256 | 256 | 49 | 47,136 | 100 mat |
| box00_mdl.arc | 1 | 8 | 26 | 26 | 19 | 20,768 | 1 |
| pl0000_mdl.arc (borg) | 16 | 35 | 41 | 48 | 19 | 41,632 | 1 |
| pl0f06k_mdl.arc (borg) | 2 | 3 | 2 | 2 | 0 | 1,536 | — |

**OBJ export proof** (triangulated per GX primitive group, JOBJ world transforms applied; no skinning yet) → `user-data/GG4E/hsd-test-csharp/`:
- `box00.obj` 4379 v / 3389 t · `arrow.obj` 84 v / 72 t · **`pl0000_borg.obj` 9141 v / 8227 t** (bbox X[-260,88] Y[-36,222] Z[-119,65], Y-up, character-shaped).
- One POBJ in pl0000 threw "out of struct range" (1 of 48) — minor GF/decoder edge case to investigate.

### Confidence: container HSD = **Confirmed**; scene graph standard sysdolphin = **Confirmed** (HSDRaw parses natively); geometry decode = **Confirmed** (real OBJ exported).

## Revised strategy (model pipeline)
The dominant project cost (research Phases 5–6) collapses. Recommended pipeline:
1. **Offline batch-convert** all 1369 `.arc` → glTF/GLB using HSDRaw (either get .NET 6 to reuse HSDRawViewer's existing glTF/Collada exporter, or extend our netstandard2.0 exporter to emit glTF with skinning + materials + animations).
2. **Browser loads glTF** via three.js `GLTFLoader` (already confirmed). No need to port the HSD parser to TS for the model path.
3. Remaining model work: skinning weights (envelope/PNMTXIDX → joint indices+weights), materials (MOBJ), textures (TOBJ → resolve to sibling `.tpl` / embedded → PNG/KTX2), animations (HSD anim tracks → glTF channels). HSDRawViewer already does most of this for Melee — adapt it.
4. Investigate the single POBJ "out of struct range" case.

## Independent cross-validation (hand-written Python parser, 2026-06-30)

A second, from-scratch Python parser (`research/prototypes/hsd_walker.py`, no .NET) was written blind and **agrees with HSDRaw at the geometry level**, which is strong corroboration:
- Container/header/reloc/roots: **Confirmed** by both (layout_ok on all test files).
- `arrow_mdl.arc`: **byte-identical** result in both parsers — 84 verts / 72 tris.
- `deck00_mdl.arc`: both find 256 POBJ. POBJ counts match across files.
- **HSD_POBJ layout Confirmed byte-exact:** `+0x00 class`, `+0x04 next`, `+0x08 →VtxDescList`, `+0x0C u16 flags/u16 nDisplay`, `+0x10 →display list`.
- **HSD_VtxDescList entry = 0x18 bytes (Confirmed):** `u32 attr, u32 attrType, u32 compCnt, u32 compType, u8 frac, u8 pad, u16 stride, u32 arrayPtr`; list terminated by `attr==0xFF`. Attributes seen: POS(9)/NRM(10)/CLR0(11)/TEX0(13)/PNMTXIDX(0); INDEX8 & INDEX16; positions F32 XYZ. Display lists use TRISTRIP(0x98)/QUADS(0x80)/TRIFAN(0xA0).
- **Critical TS-port caveat (Confirmed):** offset 0x0 is a *valid* pointer target (arrow's POS array sits at data-block-rel 0x0). Decide pointer-ness from the **reloc table**, never by `value==0`.

### One unresolved discrepancy — the JOBJ/skeleton layer
- **HSDRaw (C#)**: typed `scene_data` as `HSD_SOBJ`, followed `JOBJDescs → RootJoint → JOBJ tree`, found sane bone counts (e.g. 35 for pl0000), applied JOBJ world transforms, exported character-shaped meshes. Implies **GF JOBJ layout = standard sysdolphin**.
- **Python (hand-written)**: did *not* reproduce the `SOBJ→JOBJDesc→RootJoint` indirection; tried to interpret nodes directly, found floats/child-next didn't match Melee's JOBJ(0x40) offsets, concluded the JOBJ/wrapper layer "diverges" and **bypassed it**, detecting POBJ directly via the reloc graph.
- **Assessment:** the divergence claim is **most likely a Python-side decode miss** (it didn't walk the SOBJ indirection HSDRaw uses), not a real format difference — HSDRaw is the mature, widely-validated tool and its typed parse succeeded cleanly. **To verify:** confirm HSDRaw's JOBJ transforms assemble multi-part borgs correctly (vs in-game screenshot). Both parsers **agree** that **skinning (PNMTXIDX→matrix / envelope deформation) and the assembled skeleton pose are the real remaining model work.** Trust HSDRaw's JOBJ path; keep the Python VtxDescList/POBJ offsets for the TS port.

## FULL EXPORT PIPELINE WORKING (2026-06-30, .NET 6)

With .NET 6 installed, `HSDRawViewer` builds (`net6.0-windows`, 0 errors) and its `ModelExporter` runs **headless** from a console app. Working invocation: `ModelExporter.ExportFile(path, rootJOBJ, ModelExportSettings{ExportMesh,ExportTextures,ExportBindPose,Optimize}, new JointMap())` — **must pass `new JointMap()` not null** (null throws NRE at ModelExporter.cs:200). Tool at `user-data/GG4E/gltf-export/` (references HSDRawViewer.csproj + lib/IONET.dll).

Exported from real disc (`box00`, `pl0f06k`, `pl0000`): rigged + skinned + textured Collada. `pl0000/model_00.dae` (borg body) contains: `library_geometries`, `library_controllers` with **17 `<skin>`** (skinning weights), **20 `<node type="JOINT">`** (skeleton), materials, images. Textures decode GameCube **CMPR → PNG** (pl0000: 4×128×128; box00: 64×64 + 256×256). 16 sub-models per borg (body + parts/LODs); model_00 is the main body.

**Output format note:** the bundled `IONET.dll` exports **DAE / SMD / OBJ only — NO native glTF.** Paths to glTF for the browser: (a) use DAE now via three.js `ColladaLoader` (works today, incl. skinning); (b) later add a DAE→glb batch step (assimp/Blender/SharpGLTF) or write an `IOScene→glb` exporter with SharpGLTF for production. DAE is sufficient to start.

**Still TODO on models:** animations (`*mot.bin` / HSD joint+material anim tracks → DAE/anim export — HSDRawViewer has animation export too, not yet wired); batch-convert all 1369 `.arc`; the 1 POBJ "out of struct range" edge case.

## `pl****` wrapper note
The 0x100 header is stripped before HSDRaw load (`bytes[0x100:]`). Detection rule (u32@0==0x100 && u32@0x100==size-0x100) holds.
