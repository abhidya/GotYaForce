import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { RomDriverBridge } from "./bridge.js";
import { activeSourceTargetUid, homingTargetForSpawn, stepAttacks } from "./combat.js";
import { spawnRomProjectile } from "./projectiles.js";
import { STATE } from "./constants.js";
import { buildProfile, type BorgStats } from "./stats.js";
import { emptyInput } from "./types.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[targetLock.selftest] ${message}`);
}

export function runSelfTest(): void {
  const stats = (borgsData as { borgs: BorgStats[] }).borgs;
  const battle = createBattle({
    stageId: "st00", bounds: { x: 2000, z: 2000 },
    forces: [
      { team: 0, ownerPlayer: "p1", borgIds: ["pl0000"] },
      { team: 0, ownerPlayer: "p2", borgIds: ["pl0615"] },
      { team: 1, ownerPlayer: "p3", borgIds: ["pl0008"] },
    ],
  }, stats);
  const idle = { p1: emptyInput(), p2: emptyInput(), p3: emptyInput() };
  for (let i = 0; i <= STATE.SPAWN_DURATION; i++) battle.step(1 / 60, idle);
  const state = battleStateForSelfcheck(battle);
  const [self, ally, enemy] = state.borgs;
  assert(self && ally && enemy, "fixture roster");
  self.pos = { x: 0, y: 0, z: 0 };
  ally.pos = { x: 50, y: 0, z: 500 };
  enemy.pos = { x: -100, y: 0, z: 1000 };
  self.rotY = 0;
  battle.step(1 / 60, { ...idle, p1: { ...emptyInput(), allyLock: true } });
  assert(activeSourceTargetUid(self) === ally.uid && self.lockTarget === enemy.uid, "Z selects ally and retains enemy");
  assert(homingTargetForSpawn(self, state.borgs, self.pos, { x: 0, y: 0, z: 1 }) === ally.uid, "spawn aim follows ally");
  const bridge = self.romDriver;
  assert(bridge instanceof RomDriverBridge, "fixture has actual ROM bridge");
  const lockPosition = () => (bridge.actor as typeof bridge.actor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  bridge.syncIn(self, state.borgs);
  assert(lockPosition()?.z === ally.pos.z, "ROM lock coordinates follow ally");
  assert(bridge.actor.targetCache5e8.z === ally.pos.z, "ROM target cache follows ally");
  assert(bridge.actor.visibilityTarget === bridge.actor.visibilityRoster[1], "ROM visibility follows ally");

  // Invoke the actual Ninja fire callback installed by attachToBattle, reaching the
  // production Battle family-projectile spawner (not a test-owned stand-in).
  assert(bridge.ctx.onFamilyProjectile, "Battle installs family projectile callback");
  bridge.ctx.onFamilyProjectile(bridge.actor, 0x8006ee14, 0);
  const familyShot = state.projectiles.at(-1);
  assert(familyShot?.ownerUid === self.uid && familyShot.homingTarget === ally.uid && familyShot.aimedTargetUid === ally.uid,
    "actual Battle family shot uses active ally");
  const familySlope = (ally.pos.x - familyShot.pos.x) / (ally.pos.z - familyShot.pos.z);
  assert(Math.abs(familyShot.vel.x / familyShot.vel.z - familySlope) < 1e-8,
    "actual family shot velocity points at ally from authored muzzle");

  // Exercise generic firing through its real B press/release path, retaining the Battle's
  // input-selected target state. The ROM-family driver is disabled only for this branch.
  delete self.romDriver;
  const selfStats = stats.find((entry) => entry.id === self.borgId);
  assert(selfStats, "shooter stats");
  const profile = buildProfile(selfStats);
  const profiles = new Map([[self.uid, profile]]);
  self.state = "idle";
  self.cooldowns = { allyLockHeld: 1 };
  const press = stepAttacks(self, profile, true, false, state.borgs, profiles);
  const release = stepAttacks(self, profile, false, false, state.borgs, profiles);
  const shot = [...press.projectiles, ...release.projectiles][0];
  assert(shot, "generic B produces an actual projectile");
  assert(shot.homingTarget === ally.uid && shot.aimedTargetUid === ally.uid, "generic projectile target and telemetry agree");
  assert(shot.vel.x > 0, "generic shot actually flies toward ally bearing, not enemy");
  const romShot = spawnRomProjectile(self, 0, self.rotY);
  assert(romShot?.aimedTargetUid === ally.uid, "fireChild copies active attack target");

  battle.step(1 / 60, idle);
  assert(activeSourceTargetUid(self) === enemy.uid, "Z release restores enemy");
  assert(shot.homingTarget === ally.uid && shot.aimedTargetUid === ally.uid, "launched shot retains its original target");
  assert(romShot.aimedTargetUid === ally.uid, "launched fireChild retains original target");
  assert(familyShot.homingTarget === ally.uid && familyShot.aimedTargetUid === ally.uid, "launched family shot retains original target");
  bridge.syncIn(self, state.borgs);
  assert(lockPosition()?.z === enemy.pos.z, "ROM bridge restores enemy");

  self.state = "idle";
  self.rotY = 0;
  self.cooldowns = {};
  const enemyPress = stepAttacks(self, profile, true, false, state.borgs, profiles);
  const enemyRelease = stepAttacks(self, profile, false, false, state.borgs, profiles);
  const enemyShot = [...enemyPress.projectiles, ...enemyRelease.projectiles][0];
  assert(enemyShot?.homingTarget === enemy.uid && enemyShot.vel.x < 0, "released generic shot aims toward enemy bearing");

  // A live selected ally behind the muzzle fails the cone, even if the retained enemy
  // is in front. No fallback to the enemy is allowed for a rejected active target.
  battle.step(1 / 60, { ...idle, p1: { ...emptyInput(), allyLock: true } });
  ally.pos.z = -500;
  assert(homingTargetForSpawn(self, state.borgs, self.pos, { x: 0, y: 0, z: 1 }) === null, "ally outside cone rejects aim");
  ally.pos.z = 500;
  ally.hp = 0;
  assert(homingTargetForSpawn(self, state.borgs, self.pos, { x: 0, y: 0, z: 1 }) === null, "dead selected ally cannot acquire homing");
  bridge.syncIn(self, state.borgs);
  assert(lockPosition() === null && bridge.actor.visibilityTarget === null, "dead selected ally clears live bridge target");
  ally.hp = 1;
  const missing = state.borgs.filter((actor) => actor !== ally);
  assert(homingTargetForSpawn(self, missing, self.pos, { x: 0, y: 0, z: 1 }) === null, "missing selected ally cannot acquire homing");
  bridge.syncIn(self, missing);
  assert(lockPosition() === null && bridge.actor.visibilityTarget === null, "missing ally clears bridge target");
  ally.hp = 0;
  battle.step(1 / 60, { ...idle, p1: { ...emptyInput(), allyLock: true } });
  assert(activeSourceTargetUid(self) === enemy.uid, "normal battle refresh reacquires enemy after ally dies");

  delete self.targetLockState;
  assert(activeSourceTargetUid(self) === enemy.uid, "legacy no-state target fallback");
  assert(homingTargetForSpawn(self, [self, enemy], self.pos, { x: 0, y: 0, z: 1 }) === enemy.uid, "legacy spawn aim remains intact");
  bridge.syncIn(self, [self, enemy]);
  assert(lockPosition()?.z === enemy.pos.z, "legacy bridge aim remains intact");
  console.log("[targetLock.selftest] Battle Z/release, generic firing, ROM bridge/fireChild, cone, invalid target, immutable launch target, legacy fallback passed");
}
