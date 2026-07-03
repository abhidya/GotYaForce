// Generate packages/combat/src/data/borgMoveProperties.json — a roster-keyed, per-move
// properties table (solidity / penetration / refill / explodes / ammo / effect) distilled
// from research/decomp/data/wiki-borg-moves.json (the wiki harvest, behavior-notes (aw)),
// normalized to the port's enums and carrying the ROM cross-validation summary.
//
// Tier: OBSERVED_WIKI — community-cataloged, cross-checked against extracted ROM stat rows
// but not itself DERIVED from decomp; the port consumes it as taxonomy/fallback data, and
// traces T5/T6 remain the arbiter of engine truth for solidity/penetration.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const src = JSON.parse(fs.readFileSync(path.join(repoRoot, "research/decomp/data/wiki-borg-moves.json"), "utf8"));

const PEN = { none: "none", borgs: "borgs", total: "total" };
function penetration(s) {
  if (!s) return null;
  const t = s.trim().toLowerCase();
  if (t === "none") return PEN.none;
  if (t === "borgs" || t === "borg") return PEN.borgs;
  if (t === "total") return PEN.total;
  return null; // unknown label recorded as null, not guessed
}
function solidity(s) {
  if (!s) return null;
  const t = s.trim().toLowerCase();
  if (t === "solid") return "solid";
  if (t === "nonsolid" || t === "non-solid") return "nonsolid";
  return null;
}
function refill(s) {
  if (!s) return null;
  const t = s.trim().toLowerCase();
  if (t === "n/a" || t === "na") return null;
  if (/all at once/.test(t)) return "all_at_once"; // ROM type 0
  if (/gradual|over time/.test(t)) return "gradual"; // ROM type 1
  return "other"; // preserve unmapped labels rather than force a bucket
}
function bool(s) {
  if (!s) return null;
  const t = s.trim().toLowerCase();
  if (t === "yes" || t === "true") return true;
  if (t === "no" || t === "false") return false;
  return null;
}
function ammoPair(s) {
  if (!s || /n\/a/i.test(s)) return null;
  const m = s.match(/^(\d+|\?+)\s*\/\s*(\d+|\?+)$/);
  if (!m) return { raw: s };
  return { lv1: /^\d+$/.test(m[1]) ? Number(m[1]) : null, lv10: /^\d+$/.test(m[2]) ? Number(m[2]) : null };
}
function effect(s) {
  if (!s) return null;
  const t = s.trim();
  return /^none$/i.test(t) ? null : t;
}

const borgs = {};
let moveCount = 0;
for (const entry of Object.values(src.borgs)) {
  if (!entry.id) continue; // only roster-matched borgs get an id-keyed record
  const moves = entry.moves
    .filter((m) => m.name)
    .map((m) => {
      moveCount++;
      return {
        name: m.name,
        button: m.type ?? null, // "B Shot" / "B Attack" / "B Charge" / "X" / "X Charge"
        flair: m.flair ?? null,
        solidity: solidity(m.solidity),
        penetration: penetration(m.penetration),
        refill: refill(m.refillType),
        explodes: bool(m.explodes),
        ammo: ammoPair(m.ammoLv1Lv10),
        effect: effect(m.effect),
      };
    });
  if (moves.length === 0) continue;
  borgs[entry.id.toLowerCase()] = { wikiTitle: entry.wikiTitle, moves };
}

const out = {
  schema: "gotyaforce.borgMoveProperties.v1",
  provenance: {
    source: "research/decomp/data/wiki-borg-moves.json (Gotcha Force Wiki harvest, behavior-notes (aw))",
    generator: "scripts/gen-borg-move-properties.mjs",
    tier: "OBSERVED_WIKI — community-cataloged; solidity/penetration are the arbiter-pending taxonomy for ATK-007/008 (traces T5/T6); refill labels cross-validated to ROM weapon-cell types (all_at_once=type0, gradual=type1, behavior-notes (aw)/(ax); ROM types 2/3 are dead per (ax))",
    license: "Source wiki content CC-BY-SA; extracted field values with attribution",
  },
  penetrationEnum: ["none", "borgs", "total"],
  romCrossValidation: src.crossValidation,
  borgs,
};
const outPath = path.join(repoRoot, "packages/combat/src/data/borgMoveProperties.json");
fs.writeFileSync(outPath, JSON.stringify(out, null, 1));
console.log(`wrote ${Object.keys(borgs).length} roster borgs, ${moveCount} moves -> ${path.relative(repoRoot, outPath)}`);
console.log(`penetration classes present:`, [...new Set(Object.values(borgs).flatMap((b) => b.moves.map((m) => m.penetration)))].join(", "));
