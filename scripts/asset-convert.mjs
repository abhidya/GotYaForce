#!/usr/bin/env node
// asset-convert.mjs — converts extracted disc assets to browser-ready formats.
//
// Drives existing converters over the extract from extract-user-disc.mjs. STUB: documents
// each conversion; spawn wiring is TODO. Outputs land under user-data/converted/ (gitignored).
//
// Usage:
//   node scripts/asset-convert.mjs <REGION>
//   # e.g.  node scripts/asset-convert.mjs GG4E
//
// --- Conversions (PHASE0_RESEARCH.md §7 asset-recovery plan) --------------------------
//
//   ADX  -> OGG/Opus   : vgmstream (degod/guessadx handle the encrypted-key brute force).
//                        Confirmed/Easy. BGM, SFX, voice. Played via @gf/audio (Web Audio).
//   SFD  -> WebM/MP4    : sfd2mpg (bero) to demux Sofdec MPEG, then re-encode for <video>.
//                        Confirmed/Easy. Use sfd2mpg, NOT adXtract.
//   TPL  -> KTX2        : decode standard GC texture (@gf/formats tpl) -> PNG -> KTX2/Basis
//                        for three.js KTX2Loader. Med difficulty.
//   TXG  -> PNG/KTX2    : texture group, UNSOLVED (custom parser needed). Triage first.
//   model -> glTF/GLB   : *** TODO — BLOCKED on _mdl.arc parser (@gf/formats mdl-arc). ***
//                        This is the project's critical path; no converter exists yet.
//
// Each class converts independently and can run in parallel Web Workers / child processes.

const [region] = process.argv.slice(2);

if (!region) {
  console.error("usage: node scripts/asset-convert.mjs <GG4E|GG4J|GG4P>");
  process.exit(1);
}

// TODO: glob ADX -> vgmstream -> OGG/Opus.
// TODO: glob SFD -> sfd2mpg -> WebM/MP4.
// TODO: glob TPL -> decode -> KTX2 (basisu/toktx).
// TODO: TXG -> custom parser (unsolved).
// TODO: model (_mdl.arc) -> glTF — BLOCKED on the format parser.
console.log(`[stub] would convert ${region} assets per PHASE0 §7 — not yet implemented.`);
