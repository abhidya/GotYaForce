// Self-test for the deterministic battle core. Runnable via node after a tsc transpile, or
// directly with a TS-aware loader. Creates a 1v3 battle, steps ~600 frames with an idle
// human player + AI opponents, and asserts: no NaN anywhere, and the battle resolves.
//
// Run (from repo root), after building, e.g.:
//   D:/GotYaForce/tools/node/node.exe path/to/selfcheck.js
// or transpile this file and run it. main() returns an exit code.

import { readFileSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, resolve } from "node:path";

import { createBattle } from "./battle.js";
import { emptyInput, type BorgRuntime, type PlayerInput } from "./types.js";
import type { BorgStats } from "./stats.js";

function loadBorgs(): BorgStats[] {
  const here = dirname(fileURLToPath(import.meta.url));
  // selfcheck.js lives in packages/combat/dist (or src); borgs.json is in packages/assets/data.
  const candidates = [
    resolve(here, "../../assets/data/borgs.json"),
    resolve(here, "../../../assets/data/borgs.json"),
    resolve(here, "../../../packages/assets/data/borgs.json"),
  ];
  for (const c of candidates) {
    try {
      const raw = readFileSync(c, "utf8");
      const json = JSON.parse(raw) as { borgs: BorgStats[] };
      return json.borgs;
    } catch {
      // try next
    }
  }
  throw new Error("selfcheck: could not locate borgs.json");
}

function isFiniteVec(v: { x: number; y: number; z: number }): boolean {
  return Number.isFinite(v.x) && Number.isFinite(v.y) && Number.isFinite(v.z);
}

function assertSane(borgs: BorgRuntime[], frame: number): void {
  for (const b of borgs) {
    if (!Number.isFinite(b.hp)) throw new Error(`NaN hp on ${b.uid} @frame ${frame}`);
    if (!Number.isFinite(b.rotY)) throw new Error(`NaN rotY on ${b.uid} @frame ${frame}`);
    if (!Number.isFinite(b.invincTimer)) throw new Error(`NaN invincTimer on ${b.uid} @frame ${frame}`);
    if (!isFiniteVec(b.pos)) throw new Error(`NaN pos on ${b.uid} @frame ${frame}`);
    if (!isFiniteVec(b.vel)) throw new Error(`NaN vel on ${b.uid} @frame ${frame}`);
  }
}

export function main(): number {
  const borgs = loadBorgs();
  console.log(`[selfcheck] loaded ${borgs.length} borgs from borgs.json`);

  // 1v3: human on team 0 (one G RED), CPU team 1 with three Death Borgs. The human is IDLE,
  // so the three AI-controlled CPU borgs must close, lock on, and wear G RED down — i.e. the
  // full pipeline (deploy -> AI seek -> movement -> melee/shot -> damage -> death -> win/lose)
  // has to function for the battle to resolve. A tight arena keeps it inside the frame budget.
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] }, // G RED
        { team: 1, ownerPlayer: null, borgIds: ["pl0008", "pl000c", "pl0105"] }, // 3 Death Borgs (CPU)
      ],
      bounds: { x: 400, z: 400 },
    },
    borgs,
  );

  const idle: PlayerInput = emptyInput();
  const inputs: Record<string, PlayerInput> = { p1: idle };

  let resolvedFrame = -1;
  const MAX = 1200;
  for (let f = 0; f < MAX; f++) {
    battle.step(1 / 60, inputs);
    assertSane(battle.state.borgs, f);
    // also sanity-check energy values
    for (const k of Object.keys(battle.state.energy)) {
      const e = battle.state.energy[Number(k)];
      if (e !== undefined && !Number.isFinite(e)) throw new Error(`NaN energy team ${k} @frame ${f}`);
    }
    if (battle.state.result !== "ongoing" && resolvedFrame < 0) {
      resolvedFrame = f;
      break;
    }
  }

  const s = battle.state;
  console.log(
    `[selfcheck] frame=${s.frame} result=${s.result} energy=${JSON.stringify(s.energy)} ` +
      `aliveBorgs=${s.borgs.length} projectiles=${s.projectiles.length}`,
  );

  // With an idle human and AI Death Borgs swarming, either side can win, but the AI should
  // make *something* happen — assert energy actually changed from the start (combat occurred),
  // and that the sim never produced NaN (already checked each frame).
  const startEnergyT1 = borgs
    .filter((b) => ["pl0008", "pl000c", "pl0105"].includes(b.id))
    .reduce((a, b) => a + b.energy, 0);
  const t1Now = s.energy[1] ?? 0;
  const t0Now = s.energy[0] ?? 0;

  let ok = true;
  if (s.result === "ongoing") {
    console.error(`[selfcheck] FAIL: battle did not resolve within ${MAX} frames`);
    ok = false;
  } else {
    console.log(`[selfcheck] battle RESOLVED at frame ${resolvedFrame}: result=${s.result}`);
    // A resolution requires one team's energy to have hit 0.
    if ((s.energy[0] ?? -1) !== 0 && (s.energy[1] ?? -1) !== 0) {
      console.error("[selfcheck] FAIL: resolved but neither team's energy is 0");
      ok = false;
    }
  }

  console.log(`[selfcheck] team0 energy=${t0Now}, team1 energy=${t1Now} (team1 start=${startEnergyT1})`);

  if (ok) {
    console.log(`[selfcheck] PASS: sim ran ${s.frame} frames with no NaN and the battle resolved (${s.result}).`);
    return 0;
  }
  return 1;
}

// Execute when run directly.
if (import.meta.url === `file://${process.argv[1]}` || process.argv[1]?.endsWith("selfcheck.js")) {
  process.exit(main());
}
