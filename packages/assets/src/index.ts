// @gf/assets — runtime asset layer. Loads converted assets (glTF/GLB, KTX2, OGG/Opus,
// JSON) from the IndexedDB cache keyed by disc SHA-1, resolves them via the build-time
// manifest, and hands typed handles to render/audio/combat. Consumes @gf/formats for
// any parsing done in-browser straight from cached disc bytes. (PHASE0 §10.)
export {};
