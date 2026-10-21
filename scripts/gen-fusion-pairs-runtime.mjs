#!/usr/bin/env node
// Generate the runtime-shaped Power Burst fusion pair table consumed by
// packages/combat/src/fusionPairs.ts.
//
// Source chain:
// - ROM pair table DAT_802d352c, extracted by scripts/gen_fusion_pairs.py from the
//   user-supplied DOL into research/decomp/data/fusion-pairs-802d352c.json
//   (behavior-notes.md (aj)): 17 family slots, only families 5 and 6 non-null;
//   each populated variant carries a -1-terminated sub-list of (partner, result)
//   spawn-id pairs (spawnId = family << 8 | variant, plId = pl<family:02x><variant:02x>).
//
// This script only reshapes that DERIVED extraction into the flat directed-pair
// list the runtime lookup wants. It invents nothing: every emitted row is one
// (self variant, pair) entry of the research JSON, in table order.
//   node scripts/gen-fusion-pairs-runtime.mjs

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const sourcePath = path.join(repoRoot, "research/decomp/data/fusion-pairs-802d352c.json");
const outPath = path.join(repoRoot, "packages/combat/src/data/fusionPairs.json");

const doc = JSON.parse(fs.readFileSync(sourcePath, "utf8"));

const pairs = [];
for (const fam of Object.values(doc.families)) {
  for (const variant of fam.variants) {
    const self = `pl${fam.familyByte.toString(16).padStart(2, "0")}${variant.variant
      .toString(16)
      .padStart(2, "0")}`;
    for (const pair of variant.pairs) {
      pairs.push({ self, partner: pair.partner.plId, result: pair.result.plId });
    }
  }
}

const out = {
  schema: "gotyaforce.fusionPairs.v1",
  source:
    "research/decomp/data/fusion-pairs-802d352c.json (ROM pair table DAT_802d352c, DOL-extracted by scripts/gen_fusion_pairs.py; behavior-notes.md (aj))",
  generatedBy: "scripts/gen-fusion-pairs-runtime.mjs",
  note: "Directed pairs: `self` is the borg whose family/variant sub-list carries the entry; the ROM table lists both directions explicitly where both borgs can initiate. Only families 5 and 6 of the 17-slot table are non-null.",
  pairs,
};

fs.writeFileSync(outPath, `${JSON.stringify(out, null, 2)}\n`);
console.log(`wrote ${path.relative(repoRoot, outPath)}: ${pairs.length} directed pairs`);
