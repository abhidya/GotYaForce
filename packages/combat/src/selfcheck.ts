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

import { actorDataCombatStatsForBorgId, actorDataCombatStatsSummary } from "./actorDataStats.js";
import { createBattle } from "./battle.js";
import { stepAI } from "./ai.js";
import { actionProfileForProfile, startingAmmoForProfile } from "./actionProfiles.js";
import { projectileVisualKindForProfile, stepAttacks } from "./combat.js";
import { DASH, JUMP, WAKE_UP_INVINCIBILITY_FRAMES } from "./constants.js";
import { stepMovement } from "./movement.js";
import { emptyInput, type BorgRuntime, type PlayerInput } from "./types.js";
import { buildProfile, type BorgStats } from "./stats.js";
import { typeCategoryForBorgId, typeDamageMultiplier } from "./typeDamage.js";

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

function assertRectBoundsClamp(borgs: BorgStats[]): void {
  const bounds = { minX: -30, maxX: 40, minZ: -20, maxZ: 50 };
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds,
    },
    borgs,
  );
  const moveRight: PlayerInput = { ...emptyInput(), moveX: 1 };
  for (let f = 0; f < 90; f += 1) {
    battle.step(1 / 60, { p1: moveRight, p2: emptyInput() });
    assertSane(battle.state.borgs, f);
  }
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] rectangular bounds test lost active p1 borg");
  if (active.pos.x > bounds.maxX || active.pos.x < bounds.minX) {
    throw new Error(`[selfcheck] rectangular bounds clamp failed: x=${active.pos.x}`);
  }
  console.log(`[selfcheck] rectangular STIH-style bounds clamp kept p1 at x=${active.pos.x}`);
}

function assertTriangleFloorGrounding(borgs: BorgStats[]): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
      collision: {
        triangles: [
          {
            index: 0,
            layerIndex: null,
            marker: 0xcccccccc,
            vertices: [
              { x: -100, y: 20, z: -100 },
              { x: 100, y: 20, z: -100 },
              { x: 0, y: 20, z: 100 },
            ],
            normal: { x: 0, y: 1, z: 0 },
            planeD: -20,
            bounds2d: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
          },
        ],
      },
    },
    borgs,
  );
  battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] triangle floor test lost active p1 borg");
  if (Math.abs(active.pos.y - 30) > 0.001) {
    throw new Error(`[selfcheck] triangle floor grounding failed: y=${active.pos.y}`);
  }
  console.log(`[selfcheck] STIH triangle floor grounded p1 at y=${active.pos.y}`);
}

function assertTriangleWallCollision(borgs: BorgStats[]): void {
  const wallX = 20;
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
      collision: {
        triangles: [
          {
            index: 0,
            layerIndex: null,
            marker: 0xcccccccc,
            vertices: [
              { x: wallX, y: -20, z: -100 },
              { x: wallX, y: 100, z: 100 },
              { x: wallX, y: -20, z: 100 },
            ],
            normal: { x: -1, y: 0, z: 0 },
            planeD: wallX,
            bounds2d: { minX: wallX, maxX: wallX, minZ: -100, maxZ: 100 },
          },
        ],
      },
    },
    borgs,
  );
  const moveRight: PlayerInput = { ...emptyInput(), moveX: 1 };
  for (let f = 0; f < 40; f += 1) {
    battle.step(1 / 60, { p1: moveRight, p2: emptyInput() });
    assertSane(battle.state.borgs, f);
  }
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] triangle wall test lost active p1 borg");
  if (active.pos.x >= wallX) {
    throw new Error(`[selfcheck] triangle wall collision failed: x=${active.pos.x}`);
  }
  console.log(`[selfcheck] STIH triangle wall stopped p1 at x=${active.pos.x}`);
}

function assertTriangleCeilingCollision(borgs: BorgStats[]): void {
  const ceilingY = 24;
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
      collision: {
        triangles: [
          {
            index: 0,
            layerIndex: null,
            marker: 0xcccccccc,
            vertices: [
              { x: -100, y: ceilingY, z: -100 },
              { x: 0, y: ceilingY, z: 100 },
              { x: 100, y: ceilingY, z: -100 },
            ],
            normal: { x: 0, y: -1, z: 0 },
            planeD: ceilingY,
            bounds2d: { minX: -100, maxX: 100, minZ: -100, maxZ: 100 },
          },
        ],
      },
    },
    borgs,
  );
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] triangle ceiling test lost active p1 borg");

  for (let f = 0; f < 25; f += 1) {
    battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    assertSane(battle.state.borgs, f);
  }

  let maxTopY = active.pos.y + JUMP.GROUND_Y;
  battle.step(1 / 60, { p1: { ...emptyInput(), jump: true }, p2: emptyInput() });
  for (let f = 0; f < 45; f += 1) {
    battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    assertSane(battle.state.borgs, f);
    maxTopY = Math.max(maxTopY, active.pos.y + JUMP.GROUND_Y);
  }

  if (maxTopY > ceilingY + 0.01) {
    throw new Error(`[selfcheck] triangle ceiling collision failed: topY=${maxTopY}`);
  }
  console.log(`[selfcheck] STIH triangle ceiling capped p1 top at y=${maxTopY}`);
}

function assertPlayersAutoLockByDefault(borgs: BorgStats[]): void {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { x: 100, z: 100 },
    },
    borgs,
  );
  battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
  const activeUid = battle.state.activeUidByPlayer["p1"];
  const active = battle.state.borgs.find((b) => b.uid === activeUid);
  if (!active) throw new Error("[selfcheck] auto-lock test lost active p1 borg");
  if (!active.lockTarget) {
    throw new Error("[selfcheck] human-controlled borg did not auto-acquire a default lock target");
  }
  const target = battle.state.borgs.find((b) => b.uid === active.lockTarget);
  if (!target || target.team === active.team) {
    throw new Error("[selfcheck] human-controlled borg auto-locked an invalid target");
  }
  console.log(`[selfcheck] human-controlled borg auto-locked enemy ${active.lockTarget} by default`);
}

function assertActorDataStatsBound(borgs: BorgStats[]): void {
  const expected = actorDataCombatStatsSummary.matchedMetadataRows;
  for (const field of ["defense", "shot", "attack", "speed"] as const) {
    if (actorDataCombatStatsSummary.exactMatches[field] !== expected) {
      throw new Error(`[selfcheck] actor-data ${field} exact matches changed`);
    }
  }
  if (actorDataCombatStatsSummary.mismatches.length > 0) {
    throw new Error("[selfcheck] actor-data stat offsets have mismatches");
  }

  const gRed = borgById(borgs, "pl0615");
  const actorStats = actorDataCombatStatsForBorgId(gRed.id);
  if (!actorStats) throw new Error("[selfcheck] missing actor-data stats for pl0615");

  const spoofedRosterStats: BorgStats = {
    ...gRed,
    defense: 0,
    shot: 0,
    attack: 0,
    speed: 0,
  };
  const profile = buildProfile(spoofedRosterStats);
  if (
    profile.defense !== actorStats.defense ||
    profile.shot !== actorStats.shot ||
    profile.attack !== actorStats.attack ||
    profile.speed !== actorStats.speed
  ) {
    throw new Error(
      `[selfcheck] buildProfile did not bind pl####data.bin stats: profile=${JSON.stringify(profile)} actor=${JSON.stringify(actorStats)}`,
    );
  }
  console.log(
    `[selfcheck] actor-data stat bytes bound: ${expected} exact rows; pl0615 def/shot/atk/spd=${profile.defense}/${profile.shot}/${profile.attack}/${profile.speed}`,
  );
}

function assertLockRelativeControls(borgs: BorgStats[]): void {
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const bounds = { minX: -500, maxX: 500, minZ: -500, maxZ: 500 };
  const ctx = {
    lockTargetPos: { x: 0, y: JUMP.GROUND_Y, z: -100 },
    bounds,
    collision: null,
  };
  let uid = 0;
  const makeLocked = (): BorgRuntime => {
    const b = fakeRuntime(`locked_${uid++}`, 0, 0);
    b.pos = { x: 0, y: JUMP.GROUND_Y, z: 0 };
    b.rotY = 0;
    b.state = "idle";
    b.grounded = true;
    return b;
  };

  const forward = makeLocked();
  stepMovement(forward, profile, { ...emptyInput(), moveZ: 1 }, ctx);
  if (!(forward.vel.z < -0.1 && Math.abs(forward.vel.x) < 0.001)) {
    throw new Error(`[selfcheck] lock-relative forward should approach target: vel=${JSON.stringify(forward.vel)}`);
  }

  const back = makeLocked();
  stepMovement(back, profile, { ...emptyInput(), moveZ: -1 }, ctx);
  if (!(back.vel.z > 0.1 && Math.abs(back.vel.x) < 0.001)) {
    throw new Error(`[selfcheck] lock-relative back should retreat straight away: vel=${JSON.stringify(back.vel)}`);
  }

  const lateral = makeLocked();
  stepMovement(lateral, profile, { ...emptyInput(), moveX: 1 }, ctx);
  if ((lateral.cooldowns["dashActive"] ?? 0) !== DASH.DURATION || Math.abs(lateral.vel.x) < DASH.SPEED * 0.9) {
    throw new Error(`[selfcheck] lock-relative pure lateral should dodge dash: vel=${JSON.stringify(lateral.vel)}`);
  }

  const lateralOnCooldown = makeLocked();
  lateralOnCooldown.cooldowns["dash"] = DASH.COOLDOWN;
  stepMovement(lateralOnCooldown, profile, { ...emptyInput(), moveX: 1 }, ctx);
  if ((lateralOnCooldown.cooldowns["dashActive"] ?? 0) > 0 || Math.hypot(lateralOnCooldown.vel.x, lateralOnCooldown.vel.z) > 0.001) {
    throw new Error(`[selfcheck] lock-relative pure lateral should not become steady walk on dash cooldown: vel=${JSON.stringify(lateralOnCooldown.vel)}`);
  }

  const diagonal = makeLocked();
  stepMovement(diagonal, profile, { ...emptyInput(), moveX: 1, moveZ: 1 }, ctx);
  if ((diagonal.cooldowns["dashActive"] ?? 0) > 0 || !(diagonal.vel.x < -0.1 && diagonal.vel.z < -0.1)) {
    throw new Error(`[selfcheck] lock-relative forward+lateral should circle-strafe, not dodge: vel=${JSON.stringify(diagonal.vel)}`);
  }

  console.log("[selfcheck] lock-relative controls: forward approach, back retreat, lateral dodge, diagonal circle-strafe");
}

function borgById(borgs: BorgStats[], id: string): BorgStats {
  const borg = borgs.find((entry) => entry.id === id);
  if (!borg) throw new Error(`[selfcheck] missing borg stats for ${id}`);
  return borg;
}

function assertProjectileVisualKinds(borgs: BorgStats[]): void {
  const gatling = buildProfile(borgById(borgs, "pl0102"));
  const beam = buildProfile(borgById(borgs, "pl0104"));
  const flame = buildProfile(borgById(borgs, "pl0500"));
  if (projectileVisualKindForProfile(gatling) !== "muzzle") {
    throw new Error("[selfcheck] Gatling Gunner projectile visual should use exported muzzle flash");
  }
  if (projectileVisualKindForProfile(beam) !== "energy") {
    throw new Error("[selfcheck] Beam Gunner projectile visual should use exported energy dot");
  }
  if (projectileVisualKindForProfile(flame) !== "flame") {
    throw new Error("[selfcheck] Flame Dragon projectile visual should use exported flame core");
  }

  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: ["pl0102"] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { minX: -300, maxX: 300, minZ: -300, maxZ: 300 },
    },
    borgs,
  );
  for (let f = 0; f < 25; f += 1) {
    battle.step(1 / 60, { p1: emptyInput(), p2: emptyInput() });
    assertSane(battle.state.borgs, f);
  }
  battle.step(1 / 60, { p1: { ...emptyInput(), attack: true }, p2: emptyInput() });
  const projectile = battle.state.projectiles[0];
  if (!projectile) throw new Error("[selfcheck] Gatling Gunner did not spawn a projectile");
  if (projectile.visualKind !== "muzzle") {
    throw new Error(`[selfcheck] spawned Gatling Gunner projectile visualKind=${projectile.visualKind}`);
  }
  console.log(`[selfcheck] projectile visuals mapped gun/beam/flame assets; spawned ${projectile.visualKind}`);
}

function assertActionProfilesDrivePrimaryAttacks(borgs: BorgStats[]): void {
  const gRed = buildProfile(borgById(borgs, "pl0615"));
  const swordKnight = buildProfile(borgById(borgs, "pl0200"));
  const enemyProfile = buildProfile(borgById(borgs, "pl0008"));

  const gRedRuntime = fakeRuntime("gred", 0, 0);
  gRedRuntime.borgId = gRed.id;
  gRedRuntime.ammo = startingAmmoForProfile(gRed);
  const gRedEnemy = fakeRuntime("gred_enemy", 1, 220);
  const gRedProfiles = new Map([
    [gRedRuntime.uid, gRed],
    [gRedEnemy.uid, enemyProfile],
  ]);
  const gRedResult = stepAttacks(gRedRuntime, gRed, true, false, [gRedRuntime, gRedEnemy], gRedProfiles);
  if (actionProfileForProfile(gRed).primary !== "shot" || gRedResult.projectiles.length === 0 || gRedRuntime.anim !== "shoot") {
    throw new Error("[selfcheck] action profile did not make mixed G RED fire as its primary B attack");
  }

  const swordRuntime = fakeRuntime("sword", 0, 0);
  swordRuntime.borgId = swordKnight.id;
  swordRuntime.ammo = startingAmmoForProfile(swordKnight);
  const swordEnemy = fakeRuntime("sword_enemy", 1, 42);
  const swordProfiles = new Map([
    [swordRuntime.uid, swordKnight],
    [swordEnemy.uid, enemyProfile],
  ]);
  const swordResult = stepAttacks(swordRuntime, swordKnight, true, false, [swordRuntime, swordEnemy], swordProfiles);
  if (actionProfileForProfile(swordKnight).primary !== "melee" || swordResult.projectiles.length !== 0 || swordRuntime.anim !== "melee") {
    throw new Error("[selfcheck] action profile did not keep Sword Knight melee as its primary B attack");
  }

  console.log("[selfcheck] action profiles route mixed/ranged borgs to shots and sword borgs to melee");
}

function assertSameTeamDamageDivisor(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("attacker", 0, 0);
  const ally = fakeRuntime("ally", 0, 20);
  const enemy = fakeRuntime("enemy", 1, 20);
  const profile = buildProfile(borgById(borgs, "pl0615"));
  const profiles = new Map([
    [attacker.uid, profile],
    [ally.uid, profile],
    [enemy.uid, profile],
  ]);

  stepAttacks(attacker, profile, false, true, [attacker, ally, enemy], profiles);

  const allyDamage = ally.maxHp - ally.hp;
  const enemyDamage = enemy.maxHp - enemy.hp;
  if (!(allyDamage > 0 && allyDamage < enemyDamage)) {
    throw new Error(`[selfcheck] same-team routed damage failed: ally=${allyDamage}, enemy=${enemyDamage}`);
  }
  console.log(`[selfcheck] same-team hit divisor reduced raw damage: ally=${allyDamage}, enemy=${enemyDamage}`);
}

function assertTypeDamageMatrixWired(borgs: BorgStats[]): void {
  const missing = borgs.filter((borg) => typeCategoryForBorgId(borg.id) === null).map((borg) => borg.id);
  if (missing.length > 0) {
    throw new Error(`[selfcheck] borg ids missing type category: ${missing.slice(0, 8).join(", ")}`);
  }
  if (typeCategoryForBorgId("pl0b00") !== 15 || typeCategoryForBorgId("pl0701") !== 12) {
    throw new Error("[selfcheck] type category remap changed for pl0b00/pl0701");
  }
  if (typeDamageMultiplier("pl0b00", "pl0701") !== 1.25) {
    throw new Error("[selfcheck] type damage matrix expected pl0b00 -> pl0701 multiplier 1.25");
  }

  const attacker = fakeRuntime("attacker", 0, 0);
  const boosted = fakeRuntime("boosted", 1, 20);
  const neutral = fakeRuntime("neutral", 1, 25);
  attacker.borgId = "pl0b00";
  boosted.borgId = "pl0701";
  neutral.borgId = "pl0b00";

  const base = buildProfile(borgById(borgs, "pl0b00"));
  const attackerProfile = { ...base, id: "pl0b00", attack: 10, hasMelee: true, hasShot: false };
  const boostedProfile = { ...base, id: "pl0701", defense: 0, maxHp: 1000 };
  const neutralProfile = { ...base, id: "pl0b00", defense: 0, maxHp: 1000 };
  boosted.hp = boosted.maxHp = boostedProfile.maxHp;
  neutral.hp = neutral.maxHp = neutralProfile.maxHp;

  const profiles = new Map([
    [attacker.uid, attackerProfile],
    [boosted.uid, boostedProfile],
    [neutral.uid, neutralProfile],
  ]);

  stepAttacks(attacker, attackerProfile, false, true, [attacker, boosted, neutral], profiles);

  const boostedDamage = boosted.maxHp - boosted.hp;
  const neutralDamage = neutral.maxHp - neutral.hp;
  if (!(boostedDamage > neutralDamage)) {
    throw new Error(`[selfcheck] type damage was not applied: boosted=${boostedDamage}, neutral=${neutralDamage}`);
  }
  console.log(`[selfcheck] type matrix maps ${borgs.length} borgs and boosts pl0b00 -> pl0701 damage: ${boostedDamage} > ${neutralDamage}`);
}

function assertMeleeRefreshesInvincibility(borgs: BorgStats[]): void {
  const attacker = fakeRuntime("attacker", 0, 0);
  const enemy = fakeRuntime("enemy", 1, 20);
  const profile = buildProfile(borgById(borgs, "pl0200"));
  attacker.borgId = profile.id;
  const profiles = new Map([
    [attacker.uid, profile],
    [enemy.uid, profile],
  ]);

  stepAttacks(attacker, profile, true, false, [attacker, enemy], profiles);

  if (attacker.invincTimer !== WAKE_UP_INVINCIBILITY_FRAMES) {
    throw new Error(`[selfcheck] melee i-frame refresh failed: invincTimer=${attacker.invincTimer}`);
  }
  console.log(`[selfcheck] melee active handler refreshed i-frames to ${attacker.invincTimer}`);
}

function assertAiKeepsLockedTarget(borgs: BorgStats[]): void {
  const self = fakeRuntime("self", 0, 0);
  const closerEnemy = fakeRuntime("closer", 1, -800);
  const lockedEnemy = fakeRuntime("locked", 1, 900);
  self.lockTarget = lockedEnemy.uid;

  const input = stepAI(self, buildProfile(borgById(borgs, "pl0615")), [self, closerEnemy, lockedEnemy]);
  if (input.moveX <= 0) {
    throw new Error("[selfcheck] AI target memory failed: ignored valid lockTarget for nearer enemy");
  }
  console.log("[selfcheck] AI kept valid lockTarget before nearest-enemy fallback");
}

function fakeRuntime(uid: string, team: number, x: number): BorgRuntime {
  return {
    uid,
    borgId: "pl0615",
    team,
    ownerPlayer: team === 0 ? "p1" : null,
    hp: 100,
    maxHp: 100,
    pos: { x, y: 0, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: true,
    airJumps: 0,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 0,
    cooldowns: {},
    invincTimer: 0,
    lockTarget: null,
    alive: true,
  };
}

export function main(): number {
  const borgs = loadBorgs();
  console.log(`[selfcheck] loaded ${borgs.length} borgs from borgs.json`);
  assertRectBoundsClamp(borgs);
  assertTriangleFloorGrounding(borgs);
  assertTriangleWallCollision(borgs);
  assertTriangleCeilingCollision(borgs);
  assertPlayersAutoLockByDefault(borgs);
  assertActorDataStatsBound(borgs);
  assertLockRelativeControls(borgs);
  assertProjectileVisualKinds(borgs);
  assertActionProfilesDrivePrimaryAttacks(borgs);
  assertSameTeamDamageDivisor(borgs);
  assertTypeDamageMatrixWired(borgs);
  assertMeleeRefreshesInvincibility(borgs);
  assertAiKeepsLockedTarget(borgs);

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
  // Asset-backed action profiles add per-borg attack recovery/reload, so the old generic
  // 1200-frame cap can stop just before the idle-player loss resolves.
  const MAX = 2400;
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
