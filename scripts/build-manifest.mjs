#!/usr/bin/env node
// build-manifest.mjs — produces a hash-keyed asset manifest for the runtime cache.
//
// Scans converted assets and emits a manifest the browser uses to populate its IndexedDB
// cache. The manifest is KEYED BY DISC SHA-1 so a given dump maps deterministically to its
// asset set (different regions/revisions never collide). STUB: spawn/IO wiring is TODO.
//
// Usage:
//   node scripts/build-manifest.mjs <REGION>
//   # e.g.  node scripts/build-manifest.mjs GG4E
//
// Manifest shape (sketch — finalize alongside @gf/assets):
//   {
//     "disc": { "region": "GG4E", "sha1": "<computed-from-research/disc/GG4E>" },
//     "assets": {
//       "<logicalId>": { "path": "...", "type": "gltf|ktx2|ogg|webm|json", "sha1": "...", "bytes": 0 }
//     }
//   }
//
// (PHASE0_RESEARCH.md §10: build-manifest -> IndexedDB cache, keyed by disc hash.)

const [region] = process.argv.slice(2);

if (!region) {
  console.error("usage: node scripts/build-manifest.mjs <GG4E|GG4J|GG4P>");
  process.exit(1);
}

// TODO: read the disc SHA-1 from research/disc/<region>/<region>.hashes (no fabrication).
// TODO: walk user-data/converted/<region>; hash each asset; classify by type.
// TODO: write manifest JSON (keyed by disc sha1) for @gf/assets to load.
console.log(`[stub] would build manifest for ${region} per PHASE0 §10 — not yet implemented.`);
