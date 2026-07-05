// @gf/missions — selfcheck.ts
//
// Node-runnable sanity check. Builds a NORMAL challenge run, loads the full
// adventure campaign, and reports battle counts, enemy borg ids per battle, and
// any name→id resolution failures across all stages.
//
// Run:
//   node --experimental-strip-types packages/missions/src/selfcheck.ts
// (or transpile first). Data is read from packages/assets/data at runtime so
// the library itself stays free of filesystem access.

import { readFileSync, existsSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, resolve } from "node:path";

import { createChallengeRun, createChallengeRng, CHALLENGE_DIFFICULTIES, enemyTargetForBattle } from "./challenge.js";
import { stageIdForBattleConfig, type CombatStageCatalog } from "./combat-config.js";
import {
  CHALLENGE_ALLY_BUDGETS,
  CHALLENGE_ALLY_GROUP_CODES,
  CHALLENGE_ALLY_MAX_MEMBERS,
  CHALLENGE_BATTLE_COUNTS,
  CHALLENGE_ENEMY_BUDGETS,
  CHALLENGE_ENEMY_GROUP_CODES,
  CHALLENGE_ENEMY_MAX_MEMBERS,
  CHALLENGE_GROUP_ROSTERS,
  CHALLENGE_STAGE_BYTES,
  STAGE_ARENA_NAMES,
  arenaNameForStageByte,
  arenaNameForStageId,
  challengeStageId,
  challengeStageVariantCount,
  selectChallengeStage,
  type ChallengeGroupCode,
  type ChallengeMode,
} from "./challenge-reference.js";
import { createAdventureCampaign } from "./adventure.js";
import type { MissionBattleConfig } from "./battle-config.js";
import { computeResults, type BattleOutcome } from "./scoring.js";
import { readBorgs, type BorgData } from "./borg-data.js";
import type { StagesData } from "./adventure.js";
import {
  BORG_GET_DROP_TABLE,
  createGetPool,
  clonePool,
  snapshotPool,
  restorePool,
  registerKill,
  rollDrops,
  getDropRowForBorgId,
  type GetPool,
} from "./getSystem.js";

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`selfcheck failed: ${message}`);
}

function assertChallengeReferenceInvariants(): void {
  assert(CHALLENGE_DIFFICULTIES.NORMAL === 1500, "Challenge NORMAL must be GF ENERGY 1500");
  assert(CHALLENGE_DIFFICULTIES.TUFF === 2000, "Challenge TUFF must be GF ENERGY 2000");
  assert(CHALLENGE_DIFFICULTIES.INSANE === 2500, "Challenge INSANE must be GF ENERGY 2500");
  assert(
    Object.keys(CHALLENGE_DIFFICULTIES).join(",") === "NORMAL,TUFF,INSANE",
    "Challenge difficulty labels must match captured UI order",
  );
  assert(
    enemyTargetForBattle(CHALLENGE_DIFFICULTIES.NORMAL, 0) === 1000,
    "NORMAL BATTLE 1 target should match recovered DOL table",
  );
  assert(
    enemyTargetForBattle(CHALLENGE_DIFFICULTIES.NORMAL, 1) === 1000,
    "NORMAL BATTLE 2 target should match recovered DOL table",
  );
  assert(
    CHALLENGE_STAGE_BYTES.map(challengeStageId).join(",") === "st00,st01,st02,st03,st04,st05,st08,st0a,st0b,st0c,st0e",
    "Challenge stage-byte table should map to the recovered exported base stage ids",
  );
  assert(
    CHALLENGE_STAGE_BYTES.every((stageByte) => challengeStageVariantCount(stageByte) === 4),
    "Challenge stage bytes should use the recovered DOL variant-count table, not a literal hardcoded count",
  );
  assert(
    challengeStageVariantCount(0x09) === 5,
    "DOL stage-variant count table should preserve the non-Challenge st09 five-variant entry",
  );

  // Per-mode table rows must exactly cover the DOL battle counts (5/10/15).
  for (const mode of [0, 1, 2] as const) {
    const count = CHALLENGE_BATTLE_COUNTS[mode];
    assert(CHALLENGE_ALLY_BUDGETS[mode].length === count, `ally budget rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ENEMY_BUDGETS[mode].length === count, `enemy budget rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ALLY_MAX_MEMBERS[mode].length === count, `ally max-member rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ENEMY_MAX_MEMBERS[mode].length === count, `enemy max-member rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ALLY_GROUP_CODES[mode].length === count, `ally group rows must cover mode ${mode}'s ${count} battles`);
    assert(CHALLENGE_ENEMY_GROUP_CODES[mode].length === count, `enemy group rows must cover mode ${mode}'s ${count} battles`);
    for (const row of CHALLENGE_ENEMY_GROUP_CODES[mode]) {
      assert(row.length === 4, "each enemy group row carries the DOL's four random choices");
      assert(
        row.every((code) => CHALLENGE_GROUP_ROSTERS[code].length > 0),
        `mode ${mode} enemy group row [${row.join(",")}] must only reference non-empty spawn pools`,
      );
    }
    for (const row of CHALLENGE_ALLY_GROUP_CODES[mode]) {
      assert(row.length === 4, "each ally group row carries the DOL's four random choices");
      assert(
        row.every((code) => CHALLENGE_GROUP_ROSTERS[code].length > 0),
        `mode ${mode} ally group row [${row.join(",")}] must only reference non-empty spawn pools`,
      );
    }
  }

  // RAM-trace cross-check (research/traces/GG4E/spawn-evidence.json):
  // battle1_start_checkpoint.sav captured a NORMAL BATTLE 1 with enemy borgs
  // 0a05/0705 and CPU ally 020a. Those must be reachable from the round's
  // DOL group rows (enemy row 48, ally row 50).
  assert(
    CHALLENGE_ENEMY_GROUP_CODES[0][0]!.every((code) => code === 48),
    "NORMAL BATTLE 1 enemy group row must be the traced group 48",
  );
  assert(
    CHALLENGE_ALLY_GROUP_CODES[0][0]!.every((code) => code === 50),
    "NORMAL BATTLE 1 ally group row must be the traced group 50",
  );
  assert(
    (CHALLENGE_GROUP_ROSTERS[48] as readonly string[]).includes("pl0a05") &&
      (CHALLENGE_GROUP_ROSTERS[48] as readonly string[]).includes("pl0705"),
    "group 48 must contain the enemy borgs (pl0a05, pl0705) observed in the battle-1 RAM trace",
  );
  assert(
    (CHALLENGE_GROUP_ROSTERS[50] as readonly string[]).includes("pl020a"),
    "group 50 must contain the CPU ally borg (pl020a) observed in the battle-1 RAM trace",
  );
}

function assertChallengeStageFamilyResolution(): void {
  const catalog = (ids: readonly string[]): CombatStageCatalog => {
    const available = new Set(ids);
    return {
      defaultStageId: "st00",
      hasStageCollision(stageId: string): boolean {
        return available.has(stageId);
      },
    };
  };
  const cfg = (stageByte: number, stageSubtable: number): MissionBattleConfig => ({
    arena: "challenge",
    forces: [],
    meta: {
      mode: "challenge",
      index: 0,
      stageByte,
      stageSubtable,
      stageVariant: 0,
    },
  });

  assert(
    stageIdForBattleConfig(cfg(0x0a, 1), catalog(["st0a", "st2a"])) === "st2a",
    "Challenge stage selector must prefer exported subtable-family stages when present",
  );
  assert(
    stageIdForBattleConfig(cfg(0x0b, 2), catalog(["st0b"])) === "st0b",
    "Challenge stage selector must fall back to the base stage when a family stage is unavailable",
  );
  assert(
    stageIdForBattleConfig({ arena: "challenge", forces: [] }, catalog(["st05"])) === "st00",
    "Challenge arena without raw selector bytes should use the catalog default",
  );
}

/**
 * DERIVED — research/decomp/challenge-stage-naming-2026-07-05.md section 2.
 * Every stage byte that has an authentic name (18 rows of vsel00_mdl
 * texture_016, id = 112 + stageByte) must resolve via STAGE_ARENA_NAMES, and
 * every byte in the 11-entry Challenge pool must be among them (the pool is
 * a subset of the 18 "everyday town" arenas — see doc section 2.4).
 */
function assertArenaNameCoverage(): void {
  assert(Object.keys(STAGE_ARENA_NAMES).length === 18, "authentic arena-name table must carry all 18 stage-select rows");
  for (const stageByte of CHALLENGE_STAGE_BYTES) {
    const name = arenaNameForStageByte(stageByte);
    assert(typeof name === "string" && name.length > 0, `every challenge-pool stage byte 0x${stageByte.toString(16)} must have an arena name`);
  }
  assert(arenaNameForStageByte(0x00) === "KOU'S HOME", "stage byte 0x00 arena name must match the verified table");
  assert(arenaNameForStageByte(0x0c) === "LITTLE HILL", "stage byte 0x0c arena name must match the verified table");
  assert(arenaNameForStageByte(0x10) === "STRATOSPHERE", "stage byte 0x10 arena name must match the verified table");
  assert(arenaNameForStageByte(0x11) === "????", "stage byte 0x11 (stff) must keep its literal in-game display name");
  assert(arenaNameForStageByte(0x99) === null, "an out-of-range stage byte must not resolve to a name");

  // Family variant ids (st2x/st4x) must resolve to their base arena's name —
  // the name is per stage BYTE, not per st## build (doc section 2.4 header).
  assert(arenaNameForStageId("st00") === "KOU'S HOME", "st00 must resolve to its arena name");
  assert(arenaNameForStageId("st20") === "KOU'S HOME", "st20 (family variant of st00) must share st00's arena name");
  assert(arenaNameForStageId("st40") === "KOU'S HOME", "st40 (family variant of st00) must share st00's arena name");
  assert(arenaNameForStageId("st2c") === "LITTLE HILL", "st2c (family variant of st0c) must share st0c's arena name");
  assert(arenaNameForStageId("st4c") === "LITTLE HILL", "st4c (family variant of st0c) must share st0c's arena name");
  assert(arenaNameForStageId("stff") === "????", "stff must resolve to the literal ???? display name");
  assert(arenaNameForStageId("not-a-stage") === null, "a malformed stage id must not resolve to a name");
}

/**
 * DERIVED — research/decomp/challenge-stage-naming-2026-07-05.md section 1.2.
 * `[0x1d]` (Challenge `rand%3`) selects the st0x/st2x/st4x archive family for
 * the "outdoor" arenas that have one; a seeded run over many battles must
 * observe all three families for a family-bearing stage. Stages without a
 * family (st06/st07/st08/st0d/st0f/st10/st11 — none of which are in the
 * Challenge pool except st08) always resolve to their single build regardless
 * of the rolled subtable.
 */
function assertStageFamilyRollDistribution(): void {
  const rng = createChallengeRng(0x51a9e2);
  const subtableCounts = new Map<number, number>([[0, 0], [1, 0], [2, 0]]);
  const rollsPerStageByte = new Map<number, number[]>();
  let previousStageByte: number | null = null;

  const SAMPLE_SIZE = 3000;
  for (let i = 0; i < SAMPLE_SIZE; i += 1) {
    const stage = selectChallengeStage(rng, previousStageByte);
    previousStageByte = stage.stageByte;
    subtableCounts.set(stage.stageSubtable, (subtableCounts.get(stage.stageSubtable) ?? 0) + 1);
    const rolls = rollsPerStageByte.get(stage.stageByte) ?? [];
    rolls.push(stage.stageSubtable);
    rollsPerStageByte.set(stage.stageByte, rolls);
  }

  for (const [subtable, count] of subtableCounts) {
    assert(count > 0, `stageSubtable ${subtable} must be reachable from the rand%3 family roll over ${SAMPLE_SIZE} samples`);
  }

  // st08 has no family (fallback-only stage per doc section 3 / combat-config
  // fallback list) but still rolls stageSubtable 0..2 uniformly — the roll
  // itself is unconditional; only the archive resolution short-circuits to
  // the base build. A family-bearing pool stage (st00) must observe all three
  // subtable values, confirming the roll drives real variety for stages that
  // do have st2x/st4x builds.
  const st00Rolls = new Set(rollsPerStageByte.get(0x00) ?? []);
  assert(st00Rolls.has(0) && st00Rolls.has(1) && st00Rolls.has(2), "family-bearing stage byte 0x00 must hit all three families (0/1/2) over a seeded run");
}

/**
 * Seeded end-to-end audit of the Borg GET / Gotcha-Box drop pipeline
 * (research/decomp/items-evidence-inventory-2026-07-05.md, getSystem.ts).
 *
 *  - register kills until a known low-threshold row (pl0003, normal threshold 16) crosses,
 *    then assert the exact resulting drop;
 *  - assert the pl0503 CYBER DEATH DRAGON fusion-credit special case (credits pl0505 +
 *    pl0506 instead, both at partsKind 5 -> PARTS GET);
 *  - assert lose/abandon revert restores the pre-battle snapshot exactly;
 *  - assert points reset to 0 after a drop;
 *  - assert never-drop borgs (no table row) never drop regardless of accrued points.
 */
function assertGetSystem(): void {
  assert(BORG_GET_DROP_TABLE.rows.length === 197, "GET drop table must carry all 197 extracted rows");

  // --- 1) register kills until a known threshold crosses; assert the exact drop. ---
  // Seed 12345's first roll is gain=16 (verified offline), which exactly meets pl0003's
  // (SHURIKEN NINJA) normal-variant threshold of 16 on the FIRST registered kill.
  const pl0003Row = getDropRowForBorgId("pl0003");
  assert(pl0003Row !== null, "pl0003 must have a drop-table row");
  assert(pl0003Row.thresholds.normal === 16, "pl0003 normal threshold must be the known low value 16 (selfcheck picks this row deliberately)");

  const rng = createChallengeRng(12345);
  const pool = createGetPool();
  registerKill(pool, "pl0003", 0, rng);
  const entryBefore = pool.entries.find((e) => e.borgId === "pl0003" && e.colorVariant === 0);
  assert(entryBefore !== undefined, "registerKill must create a pool entry for a new (borgId, colorVariant) pair");
  assert(entryBefore.points === 16, `pl0003 pool entry must have accrued exactly 16 points from the seeded first roll, got ${entryBefore.points}`);

  const drops = rollDrops(pool, rng);
  assert(drops.length === 1, `expected exactly one qualifying drop, got ${drops.length}`);
  const drop = drops[0]!;
  assert(drop.borgId === "pl0003", "the qualifying drop must be pl0003");
  assert(drop.colorVariant === 0, "the drop must carry the registered color variant (0/normal)");
  assert(drop.kind === "unit", "pl0003 is partsKind 1 -> a whole-unit ('UNIT GET') drop");
  assert(drop.partIndex === 0, "a whole-unit drop's partIndex must be 0");

  // --- 4) points reset after a drop. ---
  const entryAfter = pool.entries.find((e) => e.borgId === "pl0003" && e.colorVariant === 0);
  assert(entryAfter !== undefined && entryAfter.points === 0, "pl0003's pool entry points must reset to 0 immediately after it drops");

  // Rolling again with nothing re-accrued must yield no further drops.
  assert(rollDrops(pool, rng).length === 0, "rollDrops must not re-emit a drop for an entry sitting at 0 points");

  // --- 2) fusion-credit special case (pl0503 CYBER DEATH DRAGON -> pl0505 + pl0506). ---
  const fusionPool = createGetPool();
  const fusionRng = createChallengeRng(999);
  registerKill(fusionPool, "pl0503", 2 /* gold */, fusionRng);
  assert(fusionPool.entries.length === 2, "killing pl0503 must credit exactly its two fusion components, not pl0503 itself");
  const deathHead = fusionPool.entries.find((e) => e.borgId === "pl0505");
  const cyberDragon = fusionPool.entries.find((e) => e.borgId === "pl0506");
  assert(deathHead !== undefined, "pl0503 kill must credit pl0505 (DEATH HEAD)");
  assert(cyberDragon !== undefined, "pl0503 kill must credit pl0506 (CYBER DRAGON)");
  assert(deathHead.colorVariant === 2 && cyberDragon.colorVariant === 2, "fusion credits must carry the victim's color variant");
  assert(!fusionPool.entries.some((e) => e.borgId === "pl0503"), "pl0503 itself must never appear in the pool (it has no GET row)");

  // Push both credited entries over their (shared) gold threshold and confirm both resolve
  // as PARTS GET (partsKind 5 for both pl0505 and pl0506).
  const goldThreshold = getDropRowForBorgId("pl0505")!.thresholds.gold;
  assert(getDropRowForBorgId("pl0506")!.thresholds.gold === goldThreshold, "pl0505/pl0506 must share the same gold threshold for this assertion to be well-posed");
  while ((fusionPool.entries.find((e) => e.borgId === "pl0505")?.points ?? 0) < goldThreshold) {
    registerKill(fusionPool, "pl0503", 2, fusionRng);
  }
  const fusionDrops = rollDrops(fusionPool, fusionRng);
  const fusionBorgIds = new Set(fusionDrops.map((d) => d.borgId));
  assert(fusionBorgIds.has("pl0505") && fusionBorgIds.has("pl0506"), "once both fusion-credited entries cross the gold threshold, both must drop");
  assert(fusionDrops.every((d) => d.kind === "parts" && d.partsCount === 5), "pl0505/pl0506 are partsKind 5 -> every drop must be a 5-part PARTS GET");
  assert(fusionDrops.every((d) => d.partIndex >= 1 && d.partIndex <= 5), "a parts drop's partIndex must be in 1..partsCount");

  // --- 3) lose/abandon revert restores the pre-battle snapshot exactly. ---
  const revertRng = createChallengeRng(42);
  const livePool: GetPool = createGetPool();
  registerKill(livePool, "pl0000", 0, revertRng); // seed one entry pre-battle.
  const preBattleSnapshot = snapshotPool(livePool);
  const preBattlePointsCopy = clonePool(livePool);

  // Simulate an in-battle kill, then abandon: pool must revert byte-for-byte.
  registerKill(livePool, "pl0001", 0, revertRng);
  assert(livePool.entries.length === 2, "the in-battle kill must have added a second pool entry before revert");
  restorePool(livePool, preBattleSnapshot);
  assert(livePool.entries.length === preBattlePointsCopy.entries.length, "revert must drop the in-battle-only entry");
  assert(
    JSON.stringify(livePool.entries) === JSON.stringify(preBattlePointsCopy.entries),
    "revert must restore the pool to an exact byte-for-byte match of the pre-battle snapshot",
  );
  // Snapshot must be independent of subsequent pool mutation (deep clone, not a reference).
  registerKill(livePool, "pl0002", 0, revertRng);
  assert(
    JSON.stringify(preBattleSnapshot.entries) === JSON.stringify(preBattlePointsCopy.entries),
    "mutating the live pool after taking a snapshot must not retroactively change the snapshot",
  );

  // --- 5) never-drop borgs (no table row) never drop, regardless of accrued points. ---
  const neverDropIds = ["pl0503", "pl0507", "pl050f", "pl0513", "pl0615"];
  for (const id of neverDropIds) {
    assert(getDropRowForBorgId(id) === null, `${id} must have NO drop-table row (never-drop borg)`);
  }
  const neverDropPool = createGetPool();
  const neverDropRng = createChallengeRng(7);
  // Directly seed a huge point total for a never-drop borg (bypassing registerKill's
  // fusion-credit redirect) to prove rollDrops still refuses it even at absurd points.
  neverDropPool.entries.push({ borgId: "pl0615", colorVariant: 0, points: 65535 });
  const neverDrops = rollDrops(neverDropPool, neverDropRng);
  assert(neverDrops.length === 0, "a never-drop borg (no table row) must never produce a drop, no matter how many points it has accrued");

  console.log("GET system: seeded end-to-end audit PASS (threshold crossing, fusion credit, lose-revert, points reset, never-drop borgs)");
}

/**
 * Deep per-round audit: for each difficulty, generate a full run and verify
 * every battle's enemy/ally rosters, budgets, member caps, and stage selector
 * bytes against the recovered DOL tables in challenge-reference.ts.
 */
function auditChallengeRunAgainstReference(borgs: BorgData): void {
  const validBorgIds = new Set(readBorgs(borgs).map((b) => b.id));

  // Every spawn-pool borg id must resolve against borgs.json.
  for (const [group, roster] of Object.entries(CHALLENGE_GROUP_ROSTERS)) {
    for (const id of roster) {
      assert(validBorgIds.has(id), `group ${group} roster id ${id} must exist in borgs.json`);
    }
  }

  const budgets: Array<[number, ChallengeMode]> = [
    [CHALLENGE_DIFFICULTIES.NORMAL, 0],
    [CHALLENGE_DIFFICULTIES.TUFF, 1],
    [CHALLENGE_DIFFICULTIES.INSANE, 2],
  ];

  for (const [budget, mode] of budgets) {
    const run = createChallengeRun({
      budget,
      playerCount: 1,
      playerForces: [{ player: 0, borgIds: ["pl0615"] }],
      borgs,
    });
    assert(run.mode === mode, `budget ${budget} must map to Challenge mode ${mode}`);
    assert(run.battles.length === CHALLENGE_BATTLE_COUNTS[mode], `mode ${mode} run must have ${CHALLENGE_BATTLE_COUNTS[mode]} battles`);

    let previousStageByte: number | null = null;
    run.battles.forEach((battle, i) => {
      const meta = battle.meta;
      assert(meta !== undefined, `battle ${i + 1} must carry meta`);

      // --- stage selector bytes ---
      const stageByte = meta.stageByte;
      assert(
        typeof stageByte === "number" && (CHALLENGE_STAGE_BYTES as readonly number[]).includes(stageByte),
        `battle ${i + 1} stage byte ${String(stageByte)} must come from the DOL Challenge stage table`,
      );
      assert(battle.arena === challengeStageId(stageByte as number), `battle ${i + 1} arena must match its stage byte`);
      assert(stageByte !== previousStageByte, `battle ${i + 1} must not repeat the previous battle's stage byte`);
      previousStageByte = stageByte as number;
      assert(
        typeof meta.stageSubtable === "number" && meta.stageSubtable >= 0 && meta.stageSubtable <= 2,
        `battle ${i + 1} stage subtable must be 0..2`,
      );
      assert(
        typeof meta.stageVariant === "number" &&
          meta.stageVariant >= 0 &&
          meta.stageVariant < challengeStageVariantCount(stageByte as number),
        `battle ${i + 1} stage variant must respect the DOL variant-count table`,
      );

      // --- enemy rosters ---
      const enemyForces = battle.forces.filter((f) => f.team === "enemy");
      assert(enemyForces.length === 2, `battle ${i + 1} must carry the original two enemy CPU slots`);
      const allowedEnemy = new Set<string>();
      for (const code of CHALLENGE_ENEMY_GROUP_CODES[mode][i]!) {
        for (const id of CHALLENGE_GROUP_ROSTERS[code as ChallengeGroupCode]) allowedEnemy.add(id);
      }
      const maxEnemyMembers = CHALLENGE_ENEMY_MAX_MEMBERS[mode][i]!;
      for (const force of enemyForces) {
        assert(force.borgIds.length <= maxEnemyMembers, `battle ${i + 1} enemy slot must respect the DOL member cap ${maxEnemyMembers}`);
        for (const id of force.borgIds) {
          assert(allowedEnemy.has(id), `battle ${i + 1} enemy borg ${id} must come from the round's DOL group rosters`);
        }
      }
      const enemyCharges = meta.enemySlotBudgetCharge ?? [];
      const enemyTarget = CHALLENGE_ENEMY_BUDGETS[mode][i]!;
      assert(meta.enemyTargetEnergy === enemyTarget, `battle ${i + 1} enemy target must match the DOL budget table`);
      for (const charge of enemyCharges) {
        assert(charge <= enemyTarget, `battle ${i + 1} enemy slot charge ${charge} must fit the DOL budget ${enemyTarget}`);
      }

      // --- CPU ally roster (FIGHT ALONE) ---
      const allyForce = battle.forces.find((f) => f.team === "player" && f.cpuAlly);
      assert(allyForce !== undefined, `battle ${i + 1} FIGHT ALONE must include the CPU ally force`);
      const allowedAlly = new Set<string>();
      for (const code of CHALLENGE_ALLY_GROUP_CODES[mode][i]!) {
        for (const id of CHALLENGE_GROUP_ROSTERS[code as ChallengeGroupCode]) allowedAlly.add(id);
      }
      const maxAllyMembers = CHALLENGE_ALLY_MAX_MEMBERS[mode][i]!;
      assert(allyForce.borgIds.length <= maxAllyMembers, `battle ${i + 1} ally roster must respect the DOL member cap ${maxAllyMembers}`);
      for (const id of allyForce.borgIds) {
        assert(allowedAlly.has(id), `battle ${i + 1} ally borg ${id} must come from the round's DOL ally group rosters`);
      }
      const allyTarget = CHALLENGE_ALLY_BUDGETS[mode][i]!;
      assert(meta.allyTargetEnergy === allyTarget, `battle ${i + 1} ally target must match the DOL budget table`);
      assert((meta.allyBudgetCharge ?? 0) <= allyTarget, `battle ${i + 1} ally charge must fit the DOL budget ${allyTarget}`);
    });
  }
  console.log("challenge per-round audit vs challenge-reference tables: PASS (NORMAL/TUFF/INSANE, stages+rosters+budgets)");
}

/** Find packages/assets/data by walking up from a start directory. */
function findDataDir(): string {
  let dir = dirname(fileURLToPath(import.meta.url));
  for (let i = 0; i < 12; i++) {
    const candidate = resolve(dir, "packages/assets/data/borgs.json");
    if (existsSync(candidate)) return dirname(candidate);
    const sibling = resolve(dir, "../../assets/data/borgs.json");
    if (existsSync(sibling)) return dirname(sibling);
    dir = resolve(dir, "..");
  }
  throw new Error("Could not locate packages/assets/data (borgs.json/stages.json).");
}

function loadData(): { borgs: BorgData; stages: StagesData } {
  const dataDir = findDataDir();
  const borgs = JSON.parse(
    readFileSync(resolve(dataDir, "borgs.json"), "utf8"),
  ) as BorgData;
  const stages = JSON.parse(
    readFileSync(resolve(dataDir, "stages.json"), "utf8"),
  ) as StagesData;
  return { borgs, stages };
}

export function main(): void {
  const { borgs, stages } = loadData();
  assertChallengeReferenceInvariants();
  assertChallengeStageFamilyResolution();
  assertArenaNameCoverage();
  assertStageFamilyRollDistribution();
  auditChallengeRunAgainstReference(borgs);
  assertGetSystem();

  console.log("=".repeat(70));
  console.log("CHALLENGE — NORMAL run (budget", CHALLENGE_DIFFICULTIES.NORMAL, ")");
  console.log("=".repeat(70));

  // A simple player force; ids exist in the roster (G RED + some ninjas).
  const playerForces = [{ player: 0, borgIds: ["pl0615", "pl0000", "pl000a"] }];

  const run = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1, // FIGHT ALONE → CPU ally added
    playerForces,
    borgs,
  });
  assert(run.battles.length === 5, "NORMAL Challenge run should default to DOL table count");
  assert(run.battles[0]?.label === "BATTLE 1 VS", "Challenge battle label should match captured VS flow");
  assert(run.battles[1]?.label === "BATTLE 2 VS", "WIN branch should advance to BATTLE 2 VS");
  assert(
    run.battles.every((battle) => /^st[0-9a-f]{2}$/.test(battle.arena)),
    "Challenge generated battles should carry literal exported stage ids, not arena-name fallbacks",
  );
  assert(
    run.battles.every((battle) => battle.meta?.stageByte !== undefined && battle.meta.stageSubtable !== undefined && battle.meta.stageVariant !== undefined),
    "Challenge generated battles should preserve all three raw stage selector bytes",
  );
  assert(
    run.battles[0]?.forces.filter((f) => f.team === "player" && f.ownerPlayer == null && f.cpuAlly).length === 1,
    "FIGHT ALONE should add one CPU ally on the player side",
  );
  const clampedTeamRun = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 4,
    playerForces,
    borgs,
    battleCount: 1,
  });
  assert(clampedTeamRun.playerCount === 2, "Challenge player count should clamp to original 1P/2P branches");
  assert(
    clampedTeamRun.battles[0]?.forces.every((f) => !f.cpuAlly),
    "TEAM UP branch should not add the FIGHT ALONE CPU ally",
  );

  console.log(`battles in run: ${run.total}`);
  for (const battle of run.battles) {
    const enemy = battle.forces.find((f) => f.team === "enemy");
    const allies = battle.forces.filter((f) => f.team === "player");
    const hasCpuAlly = allies.some((f) => f.cpuAlly);
    console.log(
      `  ${battle.label}  target=${battle.meta?.enemyTargetEnergy} ` +
        `actual=${battle.meta?.enemyForceEnergy} ` +
        `enemyCount=${enemy?.borgIds.length} cpuAlly=${hasCpuAlly}`,
    );
    console.log(`     enemy ids: ${enemy?.borgIds.join(", ")}`);
  }

  // Drive the progression: win the first 2, then lose.
  console.log("\n  progression demo (win, win, lose):");
  // DERIVED outcome shape (ROM slot counters +0x404..+0x437). Expected grand totals per
  // the decoded formula (scoring.ts): wins -> costWon 1800 in [1701,1800] -> 18000,
  // costLost 0 -> +1000 (flawless bonus), first strike +5000 = 24000.
  // loss -> costWon 600 in [501,600] -> 6000, costLost 900 in [801,1000] -> −1000, no
  // first strike = 5000 — POSITIVE even on a LOSS (the ROM formula has no win/lose flip).
  const wins: BattleOutcome = {
    win: true,
    attempts: 100,
    hits: 80,
    incomingAimed: 40,
    hitsTakenAimed: 10,
    hitsTakenOther: 5,
    enemyBorgsDefeated: 8,
    playerBorgsDefeated: 0,
    allyBorgsDefeated: 1,
    costWon: 1800,
    costLost: 0,
    firstStrike: true,
  };
  const loss: BattleOutcome = {
    ...wins,
    win: false,
    enemyBorgsDefeated: 3,
    playerBorgsDefeated: 3,
    costWon: 600,
    costLost: 900,
    firstStrike: false,
  };
  for (const outcome of [wins, wins, loss]) {
    const results = computeResults(outcome);
    const prog = run.next(results);
    console.log(
      `    -> ${prog.outcome} grand=${results.grandTotal} ` +
        `action=${prog.action} runScore=${prog.score} current=${prog.current}`,
    );
  }

  const branchRun = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1,
    playerForces,
    borgs,
  });
  const firstWin = branchRun.next(computeResults(wins));
  assert(firstWin.action === "advance", "WIN should advance Challenge to the next battle");
  assert(firstWin.nextBattle?.label === "BATTLE 2 VS", "WIN should load BATTLE 2 VS next");
  const losingRun = createChallengeRun({
    budget: CHALLENGE_DIFFICULTIES.NORMAL,
    playerCount: 1,
    playerForces,
    borgs,
  });
  const firstLoss = losingRun.next(computeResults(loss));
  assert(firstLoss.action === "title", "LOSE should return Challenge to title/menu");
  assert(firstLoss.nextBattle == null, "LOSE should not enqueue an auto-retry battle");

  console.log("\n" + "=".repeat(70));
  console.log("ADVENTURE — campaign load");
  console.log("=".repeat(70));

  const campaign = createAdventureCampaign(stages, borgs);
  console.log(`total stages: ${campaign.total}`);

  const stage1 = campaign.getStage(0);
  if (stage1) {
    console.log(`\nstage 1: "${stage1.name}" @ ${stage1.arena}`);
    console.log(`  confidence=${stage1.confidence} boss=${stage1.boss}`);
    for (const e of stage1.enemies) {
      console.log(
        `  ${e.count}x ${e.name} -> ${e.id ?? "UNRESOLVED"} (energy ${e.energy})`,
      );
    }
    const enemyForce = stage1.battle.forces.find((f) => f.team === "enemy");
    console.log(`  battle enemy borgIds: ${enemyForce?.borgIds.join(", ")}`);
    console.log(`  enemyForceEnergy: ${stage1.enemyForceEnergy}`);
  }

  // Resolution audit across ALL stages.
  console.log("\nname -> id resolution audit (all stages):");
  const unresolvedSet = new Set<string>();
  let resolvedCleanly = 0;
  for (const stage of campaign.stages) {
    if (stage.unresolved.length === 0) resolvedCleanly++;
    for (const name of stage.unresolved) unresolvedSet.add(name);
  }
  console.log(
    `  stages with ALL enemies resolved: ${resolvedCleanly}/${campaign.total}`,
  );
  console.log(`  distinct unresolved enemy names: ${unresolvedSet.size}`);
  for (const name of [...unresolvedSet].sort()) {
    console.log(`    - ${name}`);
  }
}

// Run when executed directly.
main();
