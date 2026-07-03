// Selftest for the OBSERVED_WIKI per-move properties dataset (moveProperties.ts).
// Run: tools/node/node.exe scripts/run-move-properties-tests.mjs
import {
  moveProfileForBorgId,
  moveByButton,
  moveDataCoverage,
  type Penetration,
} from "./moveProperties.js";

let checks = 0;
let failures = 0;
function ok(cond: boolean, msg: string): void {
  checks++;
  if (!cond) {
    failures++;
    console.error(`  FAIL: ${msg}`);
  }
}

// Coverage: the harvest yielded 164 roster borgs / 452 moves (behavior-notes (aw)).
const cov = moveDataCoverage();
ok(cov.borgs >= 160, `coverage borgs >= 160 (got ${cov.borgs})`);
ok(cov.moves >= 440, `coverage moves >= 440 (got ${cov.moves})`);

// G Red anchor: known move properties from the wiki page.
const gred = moveProfileForBorgId("pl0615");
ok(gred !== null, "pl0615 (G Red) has move data");
if (gred) {
  const beam = gred.moves.find((m) => m.name === "Beam Gun");
  ok(beam?.solidity === "nonsolid", `G Red Beam Gun solidity nonsolid (got ${beam?.solidity})`);
  ok(beam?.penetration === "borgs", `G Red Beam Gun penetration borgs (got ${beam?.penetration})`);
  ok(beam?.refill === "all_at_once", `G Red Beam Gun refill all_at_once (got ${beam?.refill})`);
  ok(beam?.ammo?.lv1 === 5 && beam?.ammo?.lv10 === 8, `G Red Beam Gun ammo 5/8 (got ${JSON.stringify(beam?.ammo)})`);
  const knuckle = gred.moves.find((m) => m.name === "Plasma Knuckle");
  ok(knuckle?.penetration === "total", `G Red Plasma Knuckle penetration total (got ${knuckle?.penetration})`);
}

// Gatling Gunner: X grenade is Solid + Explodes (the solid-projectile anchor).
const gg = moveProfileForBorgId("pl0102");
ok(gg !== null, "pl0102 (Gatling Gunner) has move data");
if (gg) {
  const grenade = gg.moves.find((m) => m.name === "Grenade");
  ok(grenade?.solidity === "solid", `Gatling grenade solidity solid (got ${grenade?.solidity})`);
  ok(grenade?.explodes === true, `Gatling grenade explodes true (got ${grenade?.explodes})`);
}

// moveByButton accessor.
const bshot = moveByButton("pl0615", "B Shot");
ok(bshot?.name === "Beam Gun", `moveByButton pl0615 "B Shot" -> Beam Gun (got ${bshot?.name})`);

// Penetration values are all within the enum (no stray labels leaked through).
const validPen = new Set<Penetration | null>(["none", "borgs", "total", null]);
let allValid = true;
for (const b of [gred, gg, moveProfileForBorgId("pl0500"), moveProfileForBorgId("pl070a")]) {
  for (const m of b?.moves ?? []) if (!validPen.has(m.penetration)) allValid = false;
}
ok(allValid, "all penetration values within {none,borgs,total,null}");

export function runSelfTest(): number {
  console.log(`moveProperties.selftest: ${checks - failures}/${checks} checks passed`);
  return failures;
}
