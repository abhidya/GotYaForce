// mdl-arc.ts — the `.arc` model container. SOLVED (2026-06-30); intentionally a stub.
//
// `_mdl.arc` (deck00_mdl.arc, box00_mdl.arc, pl****_mdl.arc, …) holds borg/prop geometry,
// skeleton, materials, and animation. The format is **HSD DAT** (HAL Sysdolphin) —
// container CONFIRMED against real GG4E bytes; full spec with header layout, the two
// populations (182 bare DATs, 1187 `pl****` files with a 0x100-byte wrapper before the
// DAT), and validation evidence: `research/format-specs/arc-hsd-format.md`.
//
// Why this module is (and stays) a stub: parsing happens OFFLINE, not in the browser.
// Ploaj/HSDLib `HSDRaw` (C#) parses GF `.arc` unmodified — scene_data root → JOBJ tree →
// DOBJ/POBJ → GX vertex accessors — and the exporter at `user-data/GG4E/gltf-export/`
// (HSDRawViewer ModelExporter, net6.0, build-time only, never shipped) emits Collada DAE
// with skeleton, skin weights, materials, and CMPR textures decoded to PNG. The web app
// loads that converted output (three.js ColladaLoader; see `apps/game/public/models/`).
// Porting an HSD parser to TypeScript would duplicate a solved pipeline for no runtime
// benefit.
//
// Historical note, kept because the two claims are easy to conflate: "HSD is statically
// linked into boot.dol, so Melee/HSDLib tooling applies to the RUNTIME binary" was tested
// and REFUTED 0-3. That refutation was about the game's executable — it never contradicted
// "the `.arc` FILES are HSD DAT archives", which is the claim that later proved true.
// Different claims; both results stand.
//
// Remaining model work (pipeline coverage, not format research):
//   - wire animation-track export (mot.bin / HSD anim tracks → clips; HSDRawViewer has the
//     machinery — see `scripts/export-borg-animation-hsd.mjs` for current progress)
//   - batch-convert coverage of all 1369 `.arc` files
//   - one POBJ "out of struct range" edge case (probe: `user-data/GG4E/hsd-test-csharp/`)
//
// (The old header's `chd/dpk/tsb/txg` triage resolved elsewhere: chd/dpk/tsb are audio,
// txg is particle images — none are model data.)
export {};
