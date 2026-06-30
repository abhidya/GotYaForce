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

import type { Vec3 } from "@gf/physics";
import { stepAI } from "./ai.js";
import {
  acquireLock,
  cycleLock,
  isBusy,
  resetProjectileCounter,
  stepActionState,
  stepAttacks,
  stepCooldowns,
  stepInvincibility,
  stepProjectiles,
} from "./combat.js";
import { DEFAULT_BOUNDS, JUMP, SIM, SPAWN_INVINCIBILITY_FRAMES } from "./constants.js";
import { clearJumpLatch, stepMovement, type MoveContext } from "./movement.js";
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
  normalizeStageBounds,
} from "./types.js";

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
  private uidCounter = 0;
  private spawnPlanned = new Set<number>(); // team indices flagged for next spawn this frame

  constructor(
    cfg: BattleConfig,
    private readonly statsById: Map<string, BorgStats>,
  ) {
    this.bounds = normalizeStageBounds(cfg.bounds ?? DEFAULT_BOUNDS);
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
      activeUidByPlayer: {},
      frame: 0,
      result: "ongoing",
    };

    // Deploy each force's first borg.
    this.forces.forEach((force, fi) => this.deployNext(force, this.spawnPosFor(fi)));
    this.recomputeEnergy();
  }

  // --- Setup helpers ------------------------------------------------------------------

  /** A deterministic spawn position per force, spread around the field facing center. */
  private spawnPosFor(forceIndex: number): { pos: Vec3; rotY: number } {
    const n = Math.max(1, this.forces.length);
    const angle = (forceIndex / n) * Math.PI * 2;
    const centerX = (this.bounds.minX + this.bounds.maxX) * 0.5;
    const centerZ = (this.bounds.minZ + this.bounds.maxZ) * 0.5;
    const halfX = (this.bounds.maxX - this.bounds.minX) * 0.5;
    const halfZ = (this.bounds.maxZ - this.bounds.minZ) * 0.5;
    const radius = Math.min(halfX, halfZ) * 0.5;
    const x = centerX + Math.sin(angle) * radius;
    const z = centerZ + Math.cos(angle) * radius;
    // Face toward the center of the arena.
    const rotY = Math.atan2(centerX - x, centerZ - z);
    return { pos: { x, y: JUMP.GROUND_Y, z }, rotY };
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
      ammo: prof.hasShot ? 6 : 0,
      cooldowns: { boostFuel: JUMP.BOOST_FUEL_FRAMES, jumpHeld: 0 },
      invincTimer: SPAWN_INVINCIBILITY_FRAMES,
      lockTarget: null,
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

      // Tick down timers first (cooldowns, invincibility) so this frame's gating is correct.
      stepCooldowns(b);
      stepInvincibility(b);

      // Lock-on (R) / switch-lock (Z).
      if (input.switchLock) {
        b.lockTarget = cycleLock(b, all);
      } else if (input.lockOn) {
        if (b.lockTarget === null || !this.lockStillValid(b)) {
          b.lockTarget = acquireLock(b, all);
        }
      } else {
        b.lockTarget = null;
      }
      // Drop dead/invalid locks.
      if (b.lockTarget && !this.lockStillValid(b)) b.lockTarget = null;

      const lockPos = b.lockTarget ? this.byUid.get(b.lockTarget)?.pos ?? null : null;
      const ctx: MoveContext = { lockTargetPos: lockPos, bounds: this.bounds };

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
      if (r.died) this.spawnPlanned.add(this.forceIndexOfUid(b.uid));
    }

    // 3) Projectiles.
    this.state.projectiles = stepProjectiles(this.state.projectiles, all, profiles, this.byUid);

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
    // Manual switch-borg: if a player pressed switchBorg, retire current and deploy next.
    for (let fi = 0; fi < this.forces.length; fi++) {
      const force = this.forces[fi];
      if (!force || force.ownerPlayer === null) continue;
      const input = inputs[force.ownerPlayer];
      if (input?.switchBorg && force.queue.length > 0 && force.activeUid) {
        const cur = this.byUid.get(force.activeUid);
        if (cur && cur.alive && !isBusy(cur)) {
          // Re-queue current at the back and deploy next.
          const prof = this.profiles.get(cur.uid);
          if (prof) {
            cur.alive = false; // retire from field
            force.queue.push({ borgId: cur.borgId, profile: prof });
            this.deployNext(force, this.spawnPosFor(fi));
          }
        }
      }
    }

    // 5) Energy + win/lose.
    this.recomputeEnergy();
    this.evaluateResult();

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

  private lockStillValid(b: BorgRuntime): boolean {
    if (!b.lockTarget) return false;
    const t = this.byUid.get(b.lockTarget);
    return !!t && t.alive && t.team !== b.team;
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

/** Build a battle from config. `borgStats` is the full per-borg table (borgs.json). */
export function createBattle(cfg: BattleConfig, borgStats: readonly BorgStats[]): Battle {
  const statsById = new Map<string, BorgStats>(borgStats.map((s) => [s.id, s]));
  return new BattleImpl(cfg, statsById);
}

export { SIM };
