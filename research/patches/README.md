# Out-of-repo pipeline patches (reproducibility snapshots)

`tools/HSDLib` and `user-data/` are gitignored, so the 2026-07-04 texture-pipeline fixes that
live there are snapshotted here. Full context: research/decomp/PORT-1TO1-STATUS.md
("2026-07-04 session" section).

- `hsdlib-modelexporter-texture-fix.patch` — apply inside `tools/HSDLib` (a git clone of
  Ploaj/HSDLib). Fixes `HSDRawViewer/IO/ModelExporter.cs`: texture PNGs are named by content
  hash (the old `Texture_{count}` names restarted per sub-model and overwrote each other in
  shared output directories), and diffuse/specular maps bind the CURRENT TObj's image (the old
  code always bound the texture-list head, mis-texturing multi-texture materials).
- `gltf-export-Program.cs` — the batch model-export harness at
  `user-data/GG4E/gltf-export/Program.cs`. Env modes: `ONLY=<arc>`/`OUTDIR=<name>` for one
  archive, `BATCH_DIR=<staged arcs>`/`BATCH_OUT=<out>` to export model_00 for every staged
  `pl####_mdl.arc`, `TEX=1` to export textures.
