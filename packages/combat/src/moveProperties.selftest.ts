// Selftest for the OBSERVED_WIKI per-move properties dataset (moveProperties.ts).
// Run: tools/node/node.exe scripts/run-move-properties-tests.mjs
import {
  moveProfileForBorgId,
  moveByButton,
  moveDataCoverage,
  type Penetration,
} from "./moveProperties.js";
import {
  commandMoveRecordsForBorgButton,
  commandMoveTableAssignmentForBorgId,
  commandMoveTableCoverage,
  hasExactCommandMoveTableForBorgId,
} from "./commandMoveTables.js";
import {
  runtimeMoveBindingsForProfile,
  runtimeMoveCoverage,
  runtimeShotPenetrationForBorgId,
  usesContextualBResolver,
} from "./moveRuntime.js";
import { buildProfile, type BorgStats } from "./stats.js";

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

const G_RED_STATS: BorgStats = {
  id: "pl0615",
  name: "G RED",
  energy: 300,
  hp: "200/290",
  defense: 3,
  shot: 4,
  attack: 4,
  speed: 6,
};

const gRedRuntimeMoves = runtimeMoveBindingsForProfile(buildProfile(G_RED_STATS, 9));
const gRedButtons = new Set(gRedRuntimeMoves.map((move) => move.button));
ok(gRedButtons.has("B Shot"), "runtime move overlay includes G RED B Shot");
ok(gRedButtons.has("B Attack"), "runtime move overlay includes G RED B Attack");
ok(gRedButtons.has("B Charge"), "runtime move overlay includes G RED B Charge");
ok(gRedButtons.has("X"), "runtime move overlay includes G RED X");
const gRedBShot = gRedRuntimeMoves.find((move) => move.button === "B Shot");
ok(gRedBShot?.ammo.lv1 === 5 && gRedBShot.ammo.lv10 === 8 && gRedBShot.ammo.current === 8, `runtime G RED B Shot ammo lv1/lv10/current = 5/8/8 (got ${JSON.stringify(gRedBShot?.ammo)})`);
ok(gRedBShot?.commandStatus === "contextual-b", `runtime G RED B Shot commandStatus contextual-b (got ${gRedBShot?.commandStatus})`);
ok(gRedBShot?.exactCommand === true, "runtime G RED B Shot has exact ROM command records");
ok(gRedBShot?.commandRecords[0]?.commandType === 0, `runtime G RED B Shot command type 0 far/default (got ${gRedBShot?.commandRecords[0]?.commandType})`);
ok(gRedBShot?.hitboxStatus === "source-shot-radius", `runtime G RED B Shot hitbox source-shot-radius (got ${gRedBShot?.hitboxStatus})`);
ok(gRedBShot?.exactHitbox === true, "runtime G RED B Shot has exact source-backed shot radius");
const gRedBAttack = gRedRuntimeMoves.find((move) => move.button === "B Attack");
ok(gRedBAttack?.exactCommand === true, "runtime G RED B Attack has exact ROM command records");
ok(gRedBAttack?.commandRecords[0]?.commandType === 1, `runtime G RED B Attack command type 1 close/proximity (got ${gRedBAttack?.commandRecords[0]?.commandType})`);
ok(gRedBAttack?.hitboxStatus === "source-hit-record", `runtime G RED B Attack hitbox source-hit-record (got ${gRedBAttack?.hitboxStatus})`);
ok(gRedBAttack?.exactHitbox === true, "runtime G RED B Attack has exact source-backed melee ladder hitbox");
const gRedBCharge = gRedRuntimeMoves.find((move) => move.button === "B Charge");
ok(gRedBCharge?.exactCommand === true, "runtime G RED B Charge has exact ROM command records");
ok(gRedBCharge?.commandRecords[0]?.commandType === 3, `runtime G RED B Charge command type 3 (got ${gRedBCharge?.commandRecords[0]?.commandType})`);
const gRedX = gRedRuntimeMoves.find((move) => move.button === "X");
ok(gRedX?.exactCommand === true, "runtime G RED X has exact ROM command records");
ok(gRedX?.commandRecords[0]?.commandType === 2, `runtime G RED X command type 2 (got ${gRedX?.commandRecords[0]?.commandType})`);
ok(gRedX?.hitboxStatus === "source-hit-record", `runtime G RED X hitbox source-hit-record (got ${gRedX?.hitboxStatus})`);
ok(gRedX?.exactHitbox === true, "runtime G RED X has exact source-backed X hitbox");
ok(usesContextualBResolver("pl0615"), "G RED participates in roster-wide contextual B resolver");
ok(runtimeShotPenetrationForBorgId("pl0615", false) === "borgs", "runtime shot penetration reads G RED B Shot");
ok(runtimeShotPenetrationForBorgId("pl0615", true) === "total", "runtime shot penetration reads G RED B Charge");
ok(hasExactCommandMoveTableForBorgId("pl0615"), "G RED has an exact constructor command table assignment");
ok(commandMoveTableAssignmentForBorgId("pl0615")?.constructorAddress === "0x8018ccfc", "G RED constructor table dispatch resolves to 0x8018ccfc");
ok(commandMoveRecordsForBorgButton("pl0615", "B Shot").length === 24, "G RED B Shot far/default command table exposes 24 directional records");

const commandCoverage = commandMoveTableCoverage();
ok(commandCoverage.decodedTables >= 120, `command table coverage decoded tables >= 120 (got ${commandCoverage.decodedTables})`);
ok(
  commandCoverage.exactCommandTableBorgs === commandCoverage.rosterBorgs,
  `command table exact borgs cover roster (${commandCoverage.exactCommandTableBorgs}/${commandCoverage.rosterBorgs})`,
);
ok(
  (commandCoverage.derivedConstructorVectorSources ?? 0) >= 100,
  `command table coverage includes constructor-vector sources (got ${commandCoverage.derivedConstructorVectorSources ?? 0})`,
);
for (const id of ["pl0500", "pl0405", "pl0900", "pl0e01"]) {
  ok(hasExactCommandMoveTableForBorgId(id), `${id} has source-derived constructor command table assignment`);
  ok(
    commandMoveTableAssignmentForBorgId(id)?.commandTableResolution === "constructor-vector",
    `${id} command table comes from constructor-vector extraction`,
  );
  ok(commandMoveRecordsForBorgButton(id, "B Shot").length > 0, `${id} B Shot has exact ROM command records`);
  ok(commandMoveRecordsForBorgButton(id, "X").length > 0, `${id} X has exact ROM command records`);
}

const runtimeCoverage = runtimeMoveCoverage();
ok(runtimeCoverage.borgsWithMoves >= 160, `runtime coverage borgs >= 160 (got ${runtimeCoverage.borgsWithMoves})`);
ok(runtimeCoverage.moves >= 440, `runtime coverage moves >= 440 (got ${runtimeCoverage.moves})`);
ok(runtimeCoverage.contextualBProfiles >= 90, `runtime contextual B profiles >= 90 (got ${runtimeCoverage.contextualBProfiles})`);
ok(runtimeCoverage.exactHitboxMoves >= 100, `runtime exact-hitbox moves >= 100 (got ${runtimeCoverage.exactHitboxMoves})`);

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
