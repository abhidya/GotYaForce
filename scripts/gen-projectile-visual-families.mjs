#!/usr/bin/env node
// Generates packages/combat/src/data/projectileVisualFamilies.json — a compact per-borg
// lookup of projectile-visual-relevant asset families (fire/beam/gun/bulletProjectile/muzzle),
// extracted from the much larger research/asset-inventory/weapon-attachment-map.json (itself
// built by scripts/map-weapon-attachments.mjs from real per-borg PZZ/model/mot asset-name and
// borgs.json stat/type scans — see that script + its .md summary for the underlying evidence).
//
// This is an evidence upgrade, NOT a ROM decode: no per-move visual-effect/particle-ID field has
// ever been found in the ROM (research/format-specs/hit-bin-format.md's 0xF4 hit-bin records and
// the puVar17 per-move fields documented in research/decomp/behavior-notes.md sections (j)/(o)/(p)
// are all damage/knockback fields, never a visual-asset ID). So the output here is explicitly
// TUNED — just backed by a much broader, weighted, per-borg evidence scan instead of a bare
// English name-string regex. See packages/combat/src/combat.ts's projectileVisualKindForProfile()
// for how this is consumed (as a first-choice lookup, falling back to the old name regex for any
// borg id absent from this table) and behavior-notes.md section (t) for the citation.
//
// Run: node scripts/gen-projectile-visual-families.mjs

import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const SRC = "research/asset-inventory/weapon-attachment-map.json";
const OUT = "packages/combat/src/data/projectileVisualFamilies.json";

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

const confidenceRank = { High: 3, Medium: 2, Low: 1, Unknown: 0 };

// Only families relevant to *projectile visual kind* (energy/flame/muzzle). sword/impact/trail
// aren't projectile-kind signals for this purpose.
const RELEVANT = ["fire", "beam", "gun", "bulletProjectile", "muzzle"];
const PRIORITY = { fire: 3, beam: 2, gun: 1, bulletProjectile: 1, muzzle: 0 };

function kindFromFamilies(families) {
  let best = null;
  let bestRank = -1;
  for (const fam of RELEVANT) {
    const entry = families[fam];
    if (!entry) continue;
    const rank = confidenceRank[entry.confidence ?? "Unknown"] ?? 0;
    if (rank === 0) continue;
    if (rank > bestRank || (rank === bestRank && best !== null && (PRIORITY[fam] ?? -1) > (PRIORITY[best] ?? -1))) {
      bestRank = rank;
      best = fam;
    }
  }
  if (best === "fire") return "flame";
  if (best === "beam") return "energy";
  if (best === "gun" || best === "bulletProjectile" || best === "muzzle") return "muzzle";
  return null; // no relevant-family signal at all; caller falls back to the name-regex heuristic
}

async function main() {
  const raw = JSON.parse(await fs.readFile(abs(SRC), "utf8"));
  const out = {};
  for (const b of raw.borgs) {
    const kind = kindFromFamilies(b.families ?? {});
    if (kind) out[b.id] = kind;
  }
  const sortedOut = Object.fromEntries(Object.keys(out).sort().map((k) => [k, out[k]]));

  const doc = {
    schema: "projectile-visual-families.v1",
    generatedFrom: SRC,
    generatedBy: "scripts/gen-projectile-visual-families.mjs",
    note:
      "TUNED, not ROM-derived: picks the highest-confidence weapon-asset family (fire/beam/gun/bulletProjectile/muzzle) per borg from the asset-inventory scan (PZZ/model/mot filename + borgs.json stat/type signals), not from a real per-move ROM effect-ID field (none has been decoded — see research/format-specs/hit-bin-format.md). Used as a broader-evidence TUNED fallback in front of the old bare name-regex heuristic in packages/combat/src/combat.ts, which still applies to any borg id missing from this table.",
    count: Object.keys(sortedOut).length,
    kinds: sortedOut,
  };

  await fs.writeFile(abs(OUT), JSON.stringify(doc, null, 2) + "\n", "utf8");
  console.log(`Wrote ${OUT} with ${doc.count} borg entries.`);
}

main();
