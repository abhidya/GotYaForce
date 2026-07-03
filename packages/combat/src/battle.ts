// Battle / force flow — the deterministic orchestrator. createBattle(cfg) builds the world;
// Battle.step(dt, inputs) advances one fixed frame.
//
// Force flow (matches the real rule):
//   - Each force deploys its borgs in order; one active borg per player/force at a time.
//   - When a player's active borg dies, the next in their force auto-deploys (spawn i-frames).
//   - energy[team] = sum of (alive-on-field + not-yet-deployed) borg `energy`.
//   - WIN  = an enemy team's energy hits 0.
//   - LOSE = your team's energy hits 0.
// For the multi-team result we report from the perspective of the lowest team id that still
// has a human owner; "win"/"lose"/"draw"/"ongoing".

import { isFiniteVec, yAtTriangleXZ, type Vec3 } from "@gf/physics";
import { stepAI } from "./ai.js";
import {
  acquireAllyLock,
  acquireLock,
  cycleAllyLock,
  cycleLock,
  isBusy,
  resetProjectileCounter,
  stepActionState,
  stepAttacks,
  stepCooldowns,
  stepGaugeWindows,
  stepInvincibility,
  stepProjectiles,
} from "./combat.js";
import { gaugeInitForBorgId } from "./gauges.js";
import { startingAmmoForProfile } from "./actionProfiles.js";
import { DEFAULT_BOUNDS, JUMP, SIM, SPAWN_INVINCIBILITY_FRAMES } from "./constants.js";
import { clearJumpLatch, stepMovement, type MoveContext } from "./movement.js";
import { resetActorParamTier } from "./paramTier.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import {
  emptyInput,
  type Battle,
  type BattleConfig,
  type BattleState,
  type BorgRuntime,
  type DeployEntry,
  type PlayerInput,
  type RectStageBounds,
  type SpawnPoint,
  type StageCollision,
  normalizeStageBounds,
} from "./types.js";

const SPAWN_RADIUS_FRACTION = 0.35;
const SPAWN_RADIUS_MAX = 3200;
const SPAWN_FLOOR_NORMAL_MIN_Y = 0.5;
const SPAWN_LOW_SURFACE_Y_BAND = 640;

/** Internal per-force runtime: the deploy queue + which team/owner it belongs to. */
interface ForceRuntime {
  team: number;
  ownerPlayer: string | null;
  /** Borgs not yet deployed (FIFO). */
  queue: DeployEntry[];
  /** The uid of this force's currently-active borg (or null between deploys). */
  activeUid: string | null;
  /** Stable key for activeUidByPlayer (player id, or a synthetic CPU key). */
  controlKey: string;
}

class BattleImpl implements Battle {
  state: BattleState;

  private profiles = new Map<string, BorgProfile>();
  private byUid = new Map<string, BorgRuntime>();
  private forces: ForceRuntime[] = [];
  private bounds: RectStageBounds;
  private collision: StageCollision | null;
  private readonly spawnArea: RectStageBounds;
  private readonly spawnPoints: readonly SpawnPoint[];
  private readonly timeLimitFrames: number | null;
  private readonly timerFrozen: boolean;
  private uidCounter = 0;
  private spawnPlanned = new Set<number>(); // team indices flagged for next spawn this frame

  constructor(
    cfg: BattleConfig,
    private readonly statsById: Map<string, BorgStats>,
  ) {
    this.bounds = normalizeStageBounds(cfg.bounds ?? DEFAULT_BOUNDS);
    this.collision = cfg.collision ?? null;
    this.spawnArea = playableSpawnArea(this.collision, this.bounds);
    this.spawnPoints = cfg.spawnPoints ?? [];
    this.timeLimitFrames = cfg.timeLimitFrames !== undefined ? Math.max(0, Math.floor(cfg.timeLimitFrames)) : null;
    this.timerFrozen = cfg.timerFrozen ?? false;
    resetProjectileCounter();

    let cpuIdx = 0;
    cfg.forces.forEach((f, fi) => {
      const queue: DeployEntry[] = f.borgIds.map((id) => {
        const s = this.statsById.get(id);
        if (!s) throw new RangeError(`Unknown borg id in force: ${id}`);
        return { borgId: id, profile: buildProfile(s) };
      });
      const controlKey = f.ownerPlayer ?? `cpu:${fi}:${cpuIdx++}`;
      this.forces.push({
        team: f.team,
        ownerPlayer: f.ownerPlayer,
        queue,
        activeUid: null,
        controlKey,
      });
    });

    this.state = {
      borgs: [],
      projectiles: [],
      energy: {},
      defeated: {},
      defeatedEnergy: {},
      activeUidByPlayer: {},
      frame: 0,
      timeRemainingFrames: this.timeLimitFrames,
      result: "ongoing",
    };

    // Deploy each force's first borg.
    this.forces.forEach((force, fi) => this.deployNext(force, this.spawnPosFor(fi)));
    this.recomputeEnergy();
  }

  // --- Setup helpers ------------------------------------------------------------------

  /** A deterministic spawn position per force, spread around the field facing center. */
  private spawnPosFor(forceIndex: number): { pos: Vec3; rotY: number } {
    const exact = this.spawnPoints[forceIndex];
    if (exact) {
      const centerX = (this.bounds.minX + this.bounds.maxX) * 0.5;
      const centerZ = (this.bounds.minZ + this.bounds.maxZ) * 0.5;
      return {
        pos: { ...exact.pos },
        rotY: exact.rotY ?? Math.atan2(centerX - exact.pos.x, centerZ - exact.pos.z),
      };
    }

    const n = Math.max(1, this.forces.length);
    const angle = (forceIndex / n) * Math.PI * 2;
    const centerX = (this.spawnArea.minX + this.spawnArea.maxX) * 0.5;
    const centerZ = (this.spawnArea.minZ + this.spawnArea.maxZ) * 0.5;
    const halfX = (this.spawnArea.maxX - this.spawnArea.minX) * 0.5;
    const halfZ = (this.spawnArea.maxZ - this.spawnArea.minZ) * 0.5;
    const radius = Math.min(SPAWN_RADIUS_MAX, Math.min(halfX, halfZ) * SPAWN_RADIUS_FRACTION);
    const spawn = supportedSpawnPoint(this.collision, centerX, centerZ, angle, radius, this.spawnArea);
    // Face toward the center of the arena.
    const rotY = Math.atan2(centerX - spawn.x, centerZ - spawn.z);
    return { pos: spawn, rotY };
  }

  private deployNext(force: ForceRuntime, spawn: { pos: Vec3; rotY: number }): void {
    const entry = force.queue.shift();
    if (!entry) {
      force.activeUid = null;
      delete this.state.activeUidByPlayer[force.controlKey];
      return;
    }
    const uid = `borg_${this.uidCounter++}`;
    const prof = entry.profile;
    // VERIFIED per-borg gauge init (pl####data.bin u16[0]/u16[1], chunk_0007.c:47-52) with a
    // DERIVED modal fallback (500/100) for ids missing from the extracted table.
    const gauges = gaugeInitForBorgId(entry.borgId);
    const b: BorgRuntime = {
      uid,
      borgId: entry.borgId,
      team: force.team,
      ownerPlayer: force.ownerPlayer,
      hp: prof.maxHp,
      maxHp: prof.maxHp,
      pos: { x: spawn.pos.x, y: spawn.pos.y, z: spawn.pos.z },
      rotY: spawn.rotY,
      vel: { x: 0, y: 0, z: 0 },
      grounded: true,
      airJumps: prof.airJumpLevel,
      state: "spawn",
      stateTime: 0,
      anim: "spawn",
      ammo: startingAmmoForProfile(prof),
      cooldowns: { boostFuel: JUMP.BOOST_FUEL_FRAMES, jumpHeld: 0 },
      invincTimer: SPAWN_INVINCIBILITY_FRAMES,
      balanceGauge: gauges.balanceGaugeMax,
      balanceGaugeMax: gauges.balanceGaugeMax,
      downGauge: gauges.downGaugeBase,
      downGaugeBase: gauges.downGaugeBase,
      balanceRefillDelay: 0,
      downResetDelay: 0,
      comboWindow: 0,
      comboAccum: 0,
      comboRank: 0,
      paramTier: resetActorParamTier(),
      lockTarget: null,
      allyLockTarget: null,
      alive: true,
    };
    this.state.borgs.push(b);
    this.byUid.set(uid, b);
    this.profiles.set(uid, prof);
    force.activeUid = uid;
    this.state.activeUidByPlayer[force.controlKey] = uid;
  }

  /** energy[team] = sum of (alive on field + queued) borg energy. */
  private recomputeEnergy(): void {
    const energy: Record<number, number> = {};
    for (const force of this.forces) {
      energy[force.team] = energy[force.team] ?? 0;
    }
    // On-field, alive borgs.
    for (const b of this.state.borgs) {
      if (b.alive) energy[b.team] = (energy[b.team] ?? 0) + (this.profiles.get(b.uid)?.energy ?? 0);
    }
    // Queued (not-yet-deployed) borgs.
    for (const force of this.forces) {
      for (const e of force.queue) {
        energy[force.team] = (energy[force.team] ?? 0) + e.profile.energy;
      }
    }
    this.state.energy = energy;
  }

  // --- Per-frame step -----------------------------------------------------------------

  step(_dt: number, inputs: Record<string, PlayerInput>): void {
    void _dt; // sim is fixed-step (SIM.DT); dt accepted for API symmetry.
    if (this.state.result !== "ongoing") return;

    const all = this.state.borgs;
    const profiles = this.profiles;

    // 1) Resolve an input for every active borg (player input or AI).
    const resolved = new Map<string, PlayerInput>();
    for (const force of this.forces) {
      if (force.activeUid === null) continue;
      const b = this.byUid.get(force.activeUid);
      if (!b || !b.alive) continue;
      let input: PlayerInput;
      if (force.ownerPlayer !== null && inputs[force.ownerPlayer]) {
        input = inputs[force.ownerPlayer] as PlayerInput;
      } else {
        const prof = profiles.get(b.uid);
        input = prof ? stepAI(b, prof, all) : emptyInput();
      }
      resolved.set(b.uid, input);
    }

    // 2) Lock-on resolution + facing context, then movement, then attacks.
    for (const b of all) {
      if (!b.alive) continue;
      const prof = profiles.get(b.uid);
      if (!prof) continue;
      const input = resolved.get(b.uid) ?? emptyInput();

      // Tick down timers first (cooldowns, invincibility, post-hit gauge windows) so this
      // frame's gating is correct. stepGaugeWindows self-freezes while in hit/down (the
      // ROM's "in hit reaction" gate, chunk_0006.c:7982-8011).
      stepCooldowns(b);
      stepInvincibility(b);
      stepGaugeWindows(b);

      // Lock-on is the default player movement frame; `lockOn` also lets AI/future callers opt in.
      // R (switch-lock) and Z (ally-lock) are EDGE-TRIGGERED via 0/1 press latches stored in
      // cooldowns (same pattern as movement's jumpHeld; stepCooldowns skips them): holding the
      // button must cycle exactly once per press, not re-cycle at 60 Hz.
      const switchLockPressed = input.switchLock && (b.cooldowns["switchLockHeld"] ?? 0) === 0;
      b.cooldowns["switchLockHeld"] = input.switchLock ? 1 : 0;
      const allyLockPressed = input.allyLock && (b.cooldowns["allyLockHeld"] ?? 0) === 0;
      b.cooldowns["allyLockHeld"] = input.allyLock ? 1 : 0;

      if (switchLockPressed) {
        b.lockTarget = cycleLock(b, all);
      } else if (input.lockOn || b.ownerPlayer !== null) {
        if (b.lockTarget === null || !this.lockStillValid(b)) {
          b.lockTarget = acquireLock(b, all);
        }
      } else {
        b.lockTarget = null;
      }
      // Drop dead/invalid locks (cycleLock/acquireLock are enemy-only, so lockTarget can
      // never be self or a same-team ally; this also drops targets that died this frame).
      if (b.lockTarget && !this.lockStillValid(b)) b.lockTarget = null;
      // Z ally-lock: acquire the nearest ally on first press, cycle allies on later presses.
      if (allyLockPressed) {
        b.allyLockTarget = this.allyLockStillValid(b) ? cycleAllyLock(b, all) : acquireAllyLock(b, all);
      }
      if (b.allyLockTarget && !this.allyLockStillValid(b)) b.allyLockTarget = null;

      const lockPos = b.lockTarget ? this.byUid.get(b.lockTarget)?.pos ?? null : null;
      const ctx: MoveContext = { lockTargetPos: lockPos, bounds: this.bounds, collision: this.collision };

      // Movement (skips horizontal control while busy, but still applies gravity).
      stepMovement(b, prof, input, ctx);
      clearJumpLatch(b, input.jump);

      // Attacks (no-op while busy/hit/down/death/spawn).
      if (!isBusy(b)) {
        const res = stepAttacks(b, prof, input.attack, input.special, all, profiles);
        if (res.projectiles.length) this.state.projectiles.push(...res.projectiles);
      }

      // Advance hit/down/death/spawn timers.
      b.stateTime += 1;
      const r = stepActionState(b);
      if (r.died) {
        this.state.defeated[b.team] = (this.state.defeated[b.team] ?? 0) + 1;
        this.state.defeatedEnergy[b.team] = (this.state.defeatedEnergy[b.team] ?? 0) + prof.energy;
        this.spawnPlanned.add(this.forceIndexOfUid(b.uid));
      }
    }

    // 3) Projectiles.
    this.state.projectiles = stepProjectiles(this.state.projectiles, all, profiles, this.byUid, {
      bounds: this.bounds,
      collision: this.collision,
    });

    // 4) Process any deaths -> auto-deploy next from that force.
    if (this.spawnPlanned.size > 0) {
      for (const fi of this.spawnPlanned) {
        const force = this.forces[fi];
        if (force && force.activeUid && !(this.byUid.get(force.activeUid)?.alive ?? false)) {
          this.deployNext(force, this.spawnPosFor(fi));
        }
      }
      this.spawnPlanned.clear();
    }
    // 5) Energy + win/lose.
    this.recomputeEnergy();
    this.evaluateResult();
    this.tickBattleTimer();

    // 6) Cull fully-dead borgs from the active list to keep arrays small (keep maps for energy already counted via queue=0).
    this.state.borgs = this.state.borgs.filter((b) => {
      if (!b.alive && b.state === "death" && b.stateTime >= 0 && b.hp <= 0) {
        // Already counted as removed; drop from byUid too unless re-queued.
        return false;
      }
      return b.alive;
    });

    this.state.frame += 1;
  }

  private tickBattleTimer(): void {
    if (this.state.result !== "ongoing" || this.timeLimitFrames === null) return;
    // DERIVED — PTR_DAT_80433934[0x50] gate: with the freeze flag set, the original
    // countdown (zz_0029b58_, chunk_0003.c:4631-4638) never decrements +0x4c and the
    // judge's timeout branches (zz_00297c8_, chunk_0003.c:4519-4529/4547-4553) never
    // fire. Challenge sets 18000 frames + frozen (chunk_0048.c:390-392), so a Challenge
    // battle can only end by a side's borg count/energy reaching 0 — never by time.
    if (this.timerFrozen) {
      this.state.timeRemainingFrames = this.timeLimitFrames;
      return;
    }
    const remaining = Math.max(0, this.timeLimitFrames - this.state.frame - 1);
    this.state.timeRemainingFrames = remaining;
    // DERIVED — timeout with neither side at 0 writes winner-mask 4 (a no-winner
    // result, chunk_0003.c:4547-4553); every per-side "won" flag is an equality
    // test (mask == 1<<side, chunk_0003.c:4560-4604), so a timeout displays as a
    // loss for every player. "draw" is the sim-side name for that mask-4 state.
    if (remaining <= 0) this.state.result = "draw";
  }

  private lockStillValid(b: BorgRuntime): boolean {
    if (!b.lockTarget) return false;
    const t = this.byUid.get(b.lockTarget);
    return !!t && t.alive && t.team !== b.team;
  }

  private allyLockStillValid(b: BorgRuntime): boolean {
    if (!b.allyLockTarget) return false;
    const t = this.byUid.get(b.allyLockTarget);
    return !!t && t.alive && t.team === b.team && t.uid !== b.uid;
  }

  private forceIndexOfUid(uid: string): number {
    return this.forces.findIndex((f) => f.activeUid === uid);
  }

  private evaluateResult(): void {
    // Teams with any borg ever, and their current energy.
    const teams = [...new Set(this.forces.map((f) => f.team))];
    const alive = teams.filter((t) => (this.state.energy[t] ?? 0) > 0);

    if (alive.length <= 1) {
      // Determine the "player" perspective: first force with a human owner.
      const human = this.forces.find((f) => f.ownerPlayer !== null);
      const playerTeam = human?.team;
      if (alive.length === 0) {
        this.state.result = "draw";
      } else if (playerTeam !== undefined) {
        this.state.result = alive[0] === playerTeam ? "win" : "lose";
      } else {
        // All-CPU battle: just mark a win for the surviving team.
        this.state.result = "win";
      }
    }
  }
}

function playableSpawnArea(collision: StageCollision | null, fallback: RectStageBounds): RectStageBounds {
  if (!collision || collision.triangles.length === 0) return fallback;
  const lowSurfaceMaxY = spawnLowSurfaceMaxY(collision);
  let out: RectStageBounds | null = null;
  for (const tri of collision.triangles) {
    if (!isSpawnFloorTriangle(tri, lowSurfaceMaxY)) continue;
    out = out
      ? {
          minX: Math.min(out.minX, tri.bounds2d.minX),
          maxX: Math.max(out.maxX, tri.bounds2d.maxX),
          minZ: Math.min(out.minZ, tri.bounds2d.minZ),
          maxZ: Math.max(out.maxZ, tri.bounds2d.maxZ),
        }
      : { ...tri.bounds2d };
  }
  if (!out) return fallback;
  const clipped = {
    minX: Math.max(fallback.minX, out.minX),
    maxX: Math.min(fallback.maxX, out.maxX),
    minZ: Math.max(fallback.minZ, out.minZ),
    maxZ: Math.min(fallback.maxZ, out.maxZ),
  };
  return clipped.minX <= clipped.maxX && clipped.minZ <= clipped.maxZ ? clipped : fallback;
}

function supportedSpawnPoint(
  collision: StageCollision | null,
  centerX: number,
  centerZ: number,
  angle: number,
  radius: number,
  area: RectStageBounds,
): Vec3 {
  if (!collision || collision.triangles.length === 0) {
    return {
      x: clamp(centerX + Math.sin(angle) * radius, area.minX, area.maxX),
      y: JUMP.GROUND_Y,
      z: clamp(centerZ + Math.cos(angle) * radius, area.minZ, area.maxZ),
    };
  }
  const lowSurfaceMaxY = spawnLowSurfaceMaxY(collision);
  for (const radiusScale of [1, 0.75, 0.5, 0.25, 0]) {
    const x = clamp(centerX + Math.sin(angle) * radius * radiusScale, area.minX, area.maxX);
    const z = clamp(centerZ + Math.cos(angle) * radius * radiusScale, area.minZ, area.maxZ);
    const surfaceY = spawnFloorSurfaceYAt(collision, x, z, lowSurfaceMaxY);
    if (surfaceY != null) return { x, y: surfaceY + JUMP.GROUND_Y, z };
  }
  return nearestSpawnFloorPoint(collision, centerX, centerZ, area, lowSurfaceMaxY) ?? { x: centerX, y: JUMP.GROUND_Y, z: centerZ };
}

function spawnFloorSurfaceYAt(
  collision: StageCollision | null,
  x: number,
  z: number,
  lowSurfaceMaxY: number,
): number | null {
  if (!collision || collision.triangles.length === 0) return null;
  let best: number | null = null;
  for (const tri of collision.triangles) {
    if (!isSpawnFloorTriangle(tri, lowSurfaceMaxY)) continue;
    if (x < tri.bounds2d.minX || x > tri.bounds2d.maxX || z < tri.bounds2d.minZ || z > tri.bounds2d.maxZ) continue;
    const y = yAtTriangleXZ(tri, x, z);
    if (y == null || y > lowSurfaceMaxY) continue;
    if (best == null || y < best) best = y;
  }
  return best;
}

function nearestSpawnFloorPoint(
  collision: StageCollision,
  centerX: number,
  centerZ: number,
  area: RectStageBounds,
  lowSurfaceMaxY: number,
): Vec3 | null {
  let best: { pos: Vec3; distSq: number } | null = null;
  for (const tri of collision.triangles) {
    if (!isSpawnFloorTriangle(tri, lowSurfaceMaxY)) continue;
    const x = (tri.vertices[0].x + tri.vertices[1].x + tri.vertices[2].x) / 3;
    const z = (tri.vertices[0].z + tri.vertices[1].z + tri.vertices[2].z) / 3;
    if (x < area.minX || x > area.maxX || z < area.minZ || z > area.maxZ) continue;
    const y = yAtTriangleXZ(tri, x, z);
    if (y == null || y > lowSurfaceMaxY) continue;
    const dx = x - centerX;
    const dz = z - centerZ;
    const candidate = { pos: { x, y: y + JUMP.GROUND_Y, z }, distSq: dx * dx + dz * dz };
    if (!best || candidate.distSq < best.distSq) best = candidate;
  }
  return best?.pos ?? null;
}

function spawnLowSurfaceMaxY(collision: StageCollision): number {
  let minY = Infinity;
  for (const tri of collision.triangles) {
    if (
      tri.marker !== 0xcccccccc ||
      !isFiniteVec(tri.normal) ||
      tri.normal.y < SPAWN_FLOOR_NORMAL_MIN_Y ||
      !tri.vertices.every(isFiniteVec)
    ) {
      continue;
    }
    for (const v of tri.vertices) {
      if (v.y < minY) minY = v.y;
    }
  }
  return Number.isFinite(minY) ? minY + SPAWN_LOW_SURFACE_Y_BAND : Infinity;
}

function isSpawnFloorTriangle(
  tri: { marker: number; normal: Vec3; vertices: [Vec3, Vec3, Vec3] },
  lowSurfaceMaxY: number,
): boolean {
  return (
    tri.marker === 0xcccccccc &&
    isFiniteVec(tri.normal) &&
    tri.normal.y >= SPAWN_FLOOR_NORMAL_MIN_Y &&
    tri.vertices.every(isFiniteVec) &&
    Math.max(...tri.vertices.map((v) => v.y)) <= lowSurfaceMaxY
  );
}

function clamp(v: number, lo: number, hi: number): number {
  return v < lo ? lo : v > hi ? hi : v;
}

/** Build a battle from config. `borgStats` is the full per-borg table (borgs.json). */
export function createBattle(cfg: BattleConfig, borgStats: readonly BorgStats[]): Battle {
  const statsById = new Map<string, BorgStats>(borgStats.map((s) => [s.id, s]));
  return new BattleImpl(cfg, statsById);
}

export { SIM };
