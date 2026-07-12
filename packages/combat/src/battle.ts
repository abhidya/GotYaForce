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
import { stepRomAI, hasRomAiParams } from "./romAi.js";
import { RomDriverBridge, type RomBattleRuntime } from "./bridge.js";
import { applyHit } from "./combat.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { damageRecordByIndex, DAMAGE_RECORD_INDEX } from "./gauges.js";
import {
  canActivateBurst,
  createBurstMeter,
  stepActiveBurst,
  stepBurst,
  sweepBurstCharged,
  tryActivateBurst,
} from "./burst.js";
import {
  activeSourceTargetUid,
  isBusy,
  refreshSourceTargetLock,
  sourceReleaseAllyLock,
  resetProjectileCounter,
  sourceSwitchAllyLock,
  sourceSwitchEnemyLock,
  slotTelemetryFor,
  stepActionState,
  stepAmmoRefill,
  stepAttacks,
  stepContactDamage,
  stepCooldowns,
  stepGaugeWindows,
  stepHitStatus,
  stepInvincibility,
  stepProjectiles,
  useWeaponCell,
  stepVampireDrain,
} from "./combat.js";
import { challengeSideRanksForMode } from "./damageFormula.js";
import { gaugeInitForBorgId } from "./gauges.js";
import { startingAmmoForProfile } from "./actionProfiles.js";
import { stepStatus } from "./status.js";
import { DEFAULT_BOUNDS, JUMP, SIM } from "./constants.js";
import { floorSurfaceYAt } from "@gf/physics";
import { clearJumpLatch, stepMovement, type MoveContext } from "./movement.js";
import { resetActorParamTier } from "./paramTier.js";
import { buildProfile, type BorgProfile, type BorgStats } from "./stats.js";
import {
  emptyInput,
  type Battle,
  type BattleActorObservation,
  type BattleConfig,
  type BattleObservation,
  type BattleState,
  type BorgRuntime,
  type BurstMeterState,
  type DeployEntry,
  type PlayerInput,
  type RectStageBounds,
  type SpawnPoint,
  type Projectile,
  type StageCollision,
  normalizeStageBounds,
} from "./types.js";

const SPAWN_RADIUS_FRACTION = 0.35;
const SPAWN_RADIUS_MAX = 3200;
const SPAWN_FLOOR_NORMAL_MIN_Y = 0.5;
const SPAWN_LOW_SURFACE_Y_BAND = 640;

// W17 (wiki-mechanics-queue.md): a player whose force is exhausted while a same-team ally
// still fights respawns as a hidden 1-HP husk borg, and keeps respawning until the ally
// falls. LIVE-VERIFIED (2026-07-03 GDB probe of the owned "meter charged.sav", 2v2): the
// husk actor reads species word actor+0x3e8 = 0xf07 (pl0f07 — the unnamed final entry of
// the Death Borg family; assets exist but it is not in the player roster/borgs.json),
// hp = 1, weapon cell +0x774/+0x776 = 1/1. NOTE the chunk_0006.c:7175 +0x4a0 spawn path
// queued as a lead in W17 was disproven by the same probe (+0x4a0 = 0 on the husk).
export const HUSK_BORG_ID = "pl0f07";
const HUSK_HP = 1; // live-verified
const HUSK_AMMO = 1; // live-verified (HUD "B 1" + weapon cell 1/1)

/**
 * pl0f07 has no roster stats (hidden borg), so the profile is synthesized. hp/ammo are
 * live-verified; energy MUST be 0 so the husk never contributes to the team energy pool
 * (the team is destroyed when its real forces hit 0, husks on-field or not). The remaining
 * stat bytes are TUNED minimal placeholders until pl0f07data.bin is parsed like the roster.
 */
function buildHuskProfile(): BorgProfile {
  return {
    id: HUSK_BORG_ID,
    name: "DEATH BORG HUSK",
    energy: 0,
    maxHp: HUSK_HP,
    defense: 1,
    shot: 1,
    attack: 0,
    speed: 1,
    airJumpLevel: 0,
    flyer: false,
    hasShot: true,
    hasMelee: false,
    rangePref: "ranged",
  };
}

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
  private state: BattleState;
  private observationCache: BattleObservation | null = null;

  private profiles = new Map<string, BorgProfile>();
  private byUid = new Map<string, BorgRuntime>();
  private forces: ForceRuntime[] = [];
  private bounds: RectStageBounds;
  private collision: StageCollision | null;
  private readonly spawnArea: RectStageBounds;
  private readonly spawnPoints: readonly SpawnPoint[];
  private readonly timeLimitFrames: number | null;
  private readonly timerFrozen: boolean;
  private readonly sideRanks: readonly [number, number];
  /**
   * T4 item 3 CPU-side halving gate: the doc scopes the CPU-controlled ×0.5 halvings to
   * "Challenge modes 0/1" specifically. `cfg.challengeMode` is only ever set by Challenge battle
   * setup (undefined for Versus) — reusing its presence as the gate keeps Versus-mode damage
   * byte-for-byte unchanged while still wiring the discrepancy for the mode the doc describes it
   * in, rather than guessing at Versus's own (unread) CPU-halving semantics.
   */
  private readonly isChallengeMode: boolean;
  private readonly useRomAi: boolean;
  private readonly romRuntime: RomBattleRuntime;
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
    this.sideRanks = challengeSideRanksForMode(cfg.challengeMode ?? 0);
    this.isChallengeMode = cfg.challengeMode !== undefined;
    // ROM AI is the DEFAULT as of 2026-07-06 (waypoint policy now DERIVED end-to-end:
    // rom-waypoint.ts ring positioning + rom-movement.ts state machine + cadence/range
    // executor). `useRomAi: false` opts back into the legacy heuristic stepAI.
    this.useRomAi = cfg.useRomAi !== false;
    resetProjectileCounter();

    let cpuIdx = 0;
    cfg.forces.forEach((f, fi) => {
      const queue: DeployEntry[] = f.borgIds.map((id, slotIdx) => {
        const s = this.statsById.get(id);
        if (!s) throw new RangeError(`Unknown borg id in force: ${id}`);
        const rawLevel = f.borgLevels?.[slotIdx];
        const level = typeof rawLevel === "number" && Number.isFinite(rawLevel) ? rawLevel : undefined;
        return { borgId: id, profile: buildProfile(s, level) };
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

    // Per-player Power Burst meters (Q4 RESOLVED 2026-07-03 — findings §S): PER-PLAYER like
    // the ROM's player-struct array (+i*0x3c), created ONCE at battle creation and never
    // touched by deployNext — the meter persists across borg deaths/deploys/switches of the
    // same player. CPU forces (ownerPlayer === null) get no entry in this wave (documented in
    // creditBurstFill, burst.ts). Battle start = empty/uncharged (createBurstMeter).
    const burstMeterByPlayer: Record<string, BurstMeterState> = {};
    for (const force of this.forces) {
      if (force.ownerPlayer !== null) burstMeterByPlayer[force.ownerPlayer] = createBurstMeter();
    }

    this.state = {
      borgs: [],
      projectiles: [],
      energy: {},
      energyMax: {},
      defeated: {},
      defeatedEnergy: {},
      activeUidByPlayer: {},
      burstMeterByPlayer,
      telemetry: { damageByTeam: {}, hitsByTeam: {}, attemptsByTeam: {}, slots: {} },
      defeatedPlayerBorgs: 0,
      defeatedAllyBorgs: 0,
      frame: 0,
      timeRemainingFrames: this.timeLimitFrames,
      result: "ongoing",
    };

    this.romRuntime = {
      floor: {
        bounds: this.bounds,
        clampToGround: (pos, velY) => this.clampRomToGround(pos, velY),
        isSupported: (x, z) => floorSurfaceYAt(this.collision, x, z, 100) != null,
      },
      allocateResource: (owner, type, count, consume) => {
        const profile = this.profiles.get(owner.uid);
        return profile ? useWeaponCell(owner, profile, type, count, consume) : false;
      },
      spawnProjectile: (owner, spawnerAddr, kind) =>
        this.addRomProjectile(owner, spawnerAddr, kind),
      resolveHit: (attacker, victim, damageRecordIndex, knockbackMult) =>
        this.resolveRomHit(attacker, victim, damageRecordIndex, knockbackMult),
    };

    // Deploy each force's first borg.
    this.forces.forEach((force, fi) => this.deployNext(force, this.spawnPosFor(fi)));
    this.refreshSourceLocks();
    this.recomputeEnergy();
    // T4 force-gauge MAX snapshot: the team's total energy at battle start (all borgs alive +
    // still queued, i.e. THIS frame's just-computed state.energy, before any death can reduce
    // it), rounded DOWN to a multiple of 10 (chunk_0000.c:1076-1079). Snapshotted once — never
    // recomputed — matching the ROM's side[+0x114] init-once-per-battle semantics.
    const energyMax: Record<number, number> = {};
    for (const [team, total] of Object.entries(this.state.energy)) {
      energyMax[Number(team)] = Math.floor(total / 10) * 10;
    }
    this.state.energyMax = energyMax;
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

  /**
   * W17: true while any OTHER same-team force still has real fight left (queued borgs or a
   * live non-husk active borg). Gates husk (re)deploys — once every real allied force is
   * gone the team's energy is 0 and the battle is decided, so no further husk spawns.
   */
  private allyForceStillFighting(force: ForceRuntime): boolean {
    return this.forces.some((f) => {
      if (f === force || f.team !== force.team) return false;
      if (f.queue.length > 0) return true;
      if (f.activeUid === null) return false;
      const active = this.byUid.get(f.activeUid);
      return !!active && active.alive && active.hp > 0 && active.borgId !== HUSK_BORG_ID;
    });
  }

  private deployNext(force: ForceRuntime, spawn: { pos: Vec3; rotY: number }): void {
    // W17: an exhausted force with a fighting ally deploys the husk instead of going dark;
    // the husk's own deaths land back here, so it respawns until the ally falls
    // (owner-observed live behavior; identity/stats live-verified — see HUSK_BORG_ID).
    const entry =
      force.queue.shift() ??
      (this.allyForceStillFighting(force) ? { borgId: HUSK_BORG_ID, profile: buildHuskProfile() } : undefined);
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
      // 3-phase deploy (DEPLOY, behavior-notes.md (af)): phase tracked in stepActionState;
      // ally cue 8 fires at the phase-0 -> 1 boundary (~frame 20). The spawn STATE itself is
      // the deploy-lock protection (combat.ts isInvincible), replacing the old flat TUNED 45f
      // invincTimer — so invincTimer starts at 0 (no separate post-deploy residual is wired;
      // the ROM's +0x720 30/60 respawn-reset dispatch is unproven, see DEPLOY comment).
      deployPhase: 0,
      ammo: entry.borgId === HUSK_BORG_ID ? HUSK_AMMO : startingAmmoForProfile(prof),
      cooldowns: { boostFuel: JUMP.BOOST_FUEL_FRAMES, jumpHeld: 0 },
      invincTimer: 0,
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
      statusId: 0,
      statusTimer: 0,
      statusImmunityMask: 0,
      lockTarget: null,
      allyLockTarget: null,
      targetLockState: {
        mode: "enemy",
        sourceState: 0,
        cameraState: 2,
        enemyIndex: -1,
        allyIndex: -1,
        activeTargetUid: null,
      },
      burstArmFrames: 0,
      burstActive: false,
      burstPaired: false,
      fusionPartnerUid: null,
      fusionState: 0,
      defeatAccounted: false,
      alive: true,
      // ROM-family driver sidecar: attaches when the borg's family has been ported to
      // the 1:1 ROM runtime (currently the G RED family). Borgs without a ported family
      // stay null and keep the generic archetype combat logic. See bridge.ts.
      romDriver: null,
      // Hit-inflicted status effects (status-effects-decode-2026-07-04.md) — all start
      // inactive; aura levels are cleared every frame regardless (stepHitStatus).
      slowHitLevel: 0,
      slowHitTimer: 0,
      hasteHitLevel: 0,
      hasteHitTimer: 0,
      slowAuraLevel: 0,
      hasteAuraLevel: 0,
      freezeFrames: 0,
      sizeTierDelta: 0,
      sizeTierTimer: 0,
      heroTierBuffFrames: 0,
    };
    this.state.borgs.push(b);
    this.byUid.set(uid, b);
    this.profiles.set(uid, prof);
    force.activeUid = uid;
    this.state.activeUidByPlayer[force.controlKey] = uid;
    // ROM-family driver: attach for ALL borgs with ported families or shared-engine
    // fallback. The bridge's tick now COMPOSES with normal movement (returns false)
    // — it layers hitbox/anim/damage ON TOP of stepMovement, not replacing it. This
    // means AI borgs navigate normally while still getting ROM-driven X-specials.
    const driver = RomDriverBridge.attachToBattle(b, this.romRuntime);
    if (driver) {
      b.romDriver = driver;
    }
  }

  observe(): BattleObservation {
    if (this.observationCache) return this.observationCache;
    const state = this.state;
    this.observationCache = {
      actors: state.borgs.map(snapshotActor),
      // Copy the container but deliberately preserve projectile element identity. The renderer
      // retains those elements to read despawn metadata after a later step removes them.
      projectiles: [...state.projectiles],
      activeUidByPlayer: { ...state.activeUidByPlayer },
      energy: { ...state.energy },
      energyMax: { ...(state.energyMax ?? {}) },
      defeated: { ...state.defeated },
      defeatedEnergy: { ...state.defeatedEnergy },
      burstMeterByPlayer: structuredClone(state.burstMeterByPlayer),
      telemetry: structuredClone(
        state.telemetry ?? { damageByTeam: {}, hitsByTeam: {}, attemptsByTeam: {} },
      ),
      defeatedPlayerBorgs: state.defeatedPlayerBorgs ?? 0,
      defeatedAllyBorgs: state.defeatedAllyBorgs ?? 0,
      defeats: (state.defeats ?? []).map((defeat) => ({ ...defeat })),
      frame: state.frame,
      timeRemainingFrames: state.timeRemainingFrames,
      result: state.result,
      winnerMask: state.winnerMask ?? 0,
    };
    return this.observationCache;
  }

  activeActor(playerId: string): BattleActorObservation | undefined {
    const observation = this.observe();
    const uid = observation.activeUidByPlayer[playerId];
    return uid ? observation.actors.find((actor) => actor.uid === uid) : undefined;
  }

  actor(uid: string): BattleActorObservation | undefined {
    return this.observe().actors.find((actor) => actor.uid === uid);
  }

  /** Package-internal mutation seam for exact selfcheck arrangements. */
  stateForSelfcheck(): BattleState {
    this.observationCache = null;
    return this.state;
  }

  private clampRomToGround(pos: Vec3, velY: number): { y: number; velY: number; grounded: boolean } {
    const groundY = this.groundYFor(pos.x, pos.z, pos.y);
    if (pos.y <= groundY) return { y: groundY, velY: 0, grounded: true };
    return { y: pos.y, velY, grounded: false };
  }

  private resolveRomHit(
    attacker: BorgRuntime,
    victim: BorgRuntime,
    damageRecordIndex: number,
    knockbackMult: number,
  ): void {
    const victimProfile = this.profiles.get(victim.uid);
    if (!victimProfile) return;
    const record =
      familyDamageRecordForBorg(attacker.borgId, damageRecordIndex) ??
      damageRecordByIndex(DAMAGE_RECORD_INDEX.CHARGE_OR_SPECIAL);
    const attackerProfile = this.profiles.get(attacker.uid);
    const dir = { x: victim.pos.x - attacker.pos.x, y: 0, z: victim.pos.z - attacker.pos.z };
    applyHit(victim, victimProfile, 0, knockbackMult, dir, attacker.pos, false, record,
      attackerProfile ? { attacker, attackerProfile, damageScale: 1, attackerSideRank: this.sideRankForTeam(attacker.team), defenderSideRank: this.sideRankForTeam(victim.team) } : undefined,
      { burstMeters: this.state.burstMeterByPlayer, telemetry: this.state.telemetry, energyByTeam: this.state.energy, energyMaxByTeam: this.state.energyMax, cpuHalvingEnabled: this.isChallengeMode });
  }

  /** Spawn a projectile via the ROM family spawner. Placeholder — routes to the
   *  bridge's native fireChild path until the family spawner tables are extracted. */
  private addRomProjectile(b: BorgRuntime, spawnerAddr: number, kind: number): void {
    void spawnerAddr;
    const p: Projectile = {
      uid: `rom-family-${kind}-${Date.now()}`,
      ownerUid: b.uid,
      team: b.team,
      pos: { x: b.pos.x, y: b.pos.y, z: b.pos.z },
      vel: { x: 0, y: 0, z: 0 },
      damage: 0,
      hitstun: 0,
      knockback: 1,
      homingTurn: 0,
      homingTarget: null,
      life: 1,
      hitRadius: 0,
      visualKind: "energy",
    };
    this.state.projectiles.push(p);
  }

  /** Ground-Y query for the ROM driver's ground clamp — mirrors movement.ts's
   *  groundYAt (floorSurfaceYAt + GROUND_SNAP_UP fallback to JUMP.GROUND_Y). */
  private groundYFor(x: number, z: number, currentY: number): number {
    const GROUND_SNAP_UP = 35;
    const surfaceY = floorSurfaceYAt(this.collision, x, z, currentY - 10 + GROUND_SNAP_UP);
    if (surfaceY != null) return surfaceY;
    return 10; // JUMP.GROUND_Y
  }

  /** energy[team] = sum of not-yet-defeated on-field borgs + queued borgs. */
  private recomputeEnergy(): void {
    const energy: Record<number, number> = {};
    for (const force of this.forces) {
      energy[force.team] = energy[force.team] ?? 0;
    }
    // On-field borgs whose HP-zero kill event has not already removed their force cost.
    for (const b of this.state.borgs) {
      if (b.alive && !b.defeatAccounted) {
        energy[b.team] = (energy[b.team] ?? 0) + (this.profiles.get(b.uid)?.energy ?? 0);
      }
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

  private burstMeterFor(b: BorgRuntime): BurstMeterState | undefined {
    return b.ownerPlayer === null ? undefined : this.state.burstMeterByPlayer[b.ownerPlayer];
  }

  /**
   * Sample Y press edges for human-controlled active borgs, then resolve Power Burst
   * activation after all same-frame teammate inputs are visible.
   */
  private stepPowerBurstInputs(resolved: Map<string, PlayerInput>): void {
    const humanBorgsByTeam = new Map<number, BorgRuntime[]>();

    for (const force of this.forces) {
      if (force.ownerPlayer === null || force.activeUid === null) continue;
      const b = this.byUid.get(force.activeUid);
      if (!b || !b.alive) continue;
      const input = resolved.get(b.uid) ?? emptyInput();
      const hyperPressed = input.hyper && (b.cooldowns["hyperHeld"] ?? 0) === 0;
      b.cooldowns["hyperHeld"] = input.hyper ? 1 : 0;
      stepBurst(b, hyperPressed);

      const teamBorgs = humanBorgsByTeam.get(b.team);
      if (teamBorgs) {
        teamBorgs.push(b);
      } else {
        humanBorgsByTeam.set(b.team, [b]);
      }
    }

    for (const [team, teamBorgs] of humanBorgsByTeam) {
      if (teamBorgs.length === 1) {
        const b = teamBorgs[0];
        if (!b) continue;
        if (tryActivateBurst(b, this.burstMeterFor(b), false)) {
          this.activateSideWideBurst(team);
        }
        continue;
      }

      const ready = teamBorgs.every((b) => canActivateBurst(b, this.burstMeterFor(b)));
      if (!ready) continue;
      let activated = false;
      for (const b of teamBorgs) {
        if (tryActivateBurst(b, this.burstMeterFor(b), true)) activated = true;
      }
      if (activated) this.activateSideWideBurst(team);
    }
  }

  /**
   * SIDE-WIDE burst flag — DERIVED (combat-feel-gaps-decode-2026-07-05.md T3): `+0x6fc` is set
   * on EVERY LIVING actor of the side by `zz_005b2b8_` (chunk_0007.c:3429-3445), not only the
   * armed Y-presser(s). The port previously only flipped `burstActive` on the presser(s)
   * (tryActivateBurst above); this propagates the SAME activation to every other living,
   * same-team borg still on the field (including CPU-controlled allies, which the ROM's
   * per-actor loop does not distinguish). Non-presser teammates get `burstPaired = true` too
   * (T3: the whole side entered the "Power Burst active" state together) but do NOT consume
   * their own meter or the `charged` flag — the ROM's activation precondition (armed Y +
   * charged meter) is a presser-only gate; only the presser(s)' own meters are spent.
   */
  private activateSideWideBurst(team: number): void {
    for (const b of this.state.borgs) {
      if (!b.alive || b.team !== team) continue;
      if (b.burstActive) continue; // already set (the presser(s), handled by tryActivateBurst)
      b.burstActive = true;
      b.burstPaired = true;
    }
  }

  /**
   * Drain active Power Bursts. SIDE-WIDE per T3: the port's per-player meter is the only drain
   * clock this port has (the ROM's real side timer pair +0x10c/+0x10e is trace-gated per the
   * doc), so a side's burst duration is driven by its presser's OWN meter — when that empties
   * (stepActiveBurst clears the presser's burstActive), every OTHER living teammate that was
   * riding the side-wide flag (activateSideWideBurst, no meter of its own) ends together too,
   * since there is no ROM-decoded reason a subset of one side would drop out of burst before
   * the rest. CPU-owned/non-active teammates never had a meter to drain in the first place —
   * this loop is what actually turns their flag back off once the side's burst ends.
   */
  private drainPowerBursts(): void {
    const teamsStillBursting = new Set<number>();
    for (const force of this.forces) {
      if (force.ownerPlayer === null || force.activeUid === null) continue;
      const b = this.byUid.get(force.activeUid);
      if (!b || !b.burstActive) continue;
      stepActiveBurst(b, this.burstMeterFor(b));
      if (b.burstActive) teamsStillBursting.add(b.team);
    }
    for (const b of this.state.borgs) {
      if (!b.alive || !b.burstActive) continue;
      if (teamsStillBursting.has(b.team)) continue;
      // No metered presser kept this team's burst alive this frame (either the presser's
      // meter just emptied, or this borg's team has no active metered presser at all — e.g.
      // an all-CPU side, which cannot self-activate burst today per burst.ts creditBurstFill,
      // but stays defensive here in case a future wave adds CPU meters) — end it.
      b.burstActive = false;
      b.burstPaired = false;
    }
  }

  step(_dt: number, inputs: Record<string, PlayerInput>): BattleObservation {
    void _dt; // sim is fixed-step (SIM.DT); dt accepted for API symmetry.
    if (this.state.result !== "ongoing") return this.observe();
    this.observationCache = null;

    // 0) Power Burst charged-flag sweep (ROM +0x103, Q4): the flag flips ONE frame AFTER the
    // clamped meter reaches METER_MAX. Deterministic check-BEFORE-fill ordering: this runs
    // before any of this frame's hit connections (stepAttacks in loop 2 / stepProjectiles in
    // step 3) can fill meters, so a meter maxed on frame N is first seen — and charged — on
    // frame N+1, matching the live-observed delay. See sweepBurstCharged (burst.ts).
    sweepBurstCharged(this.state.burstMeterByPlayer);

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
        // ROM-architecture AI (romAi.ts + rom/rom-movement.ts + rom/rom-waypoint.ts;
        // cpu-ai-decode-2026-07-06.md + the ai-state-handlers decode): DERIVED retarget
        // cadence, per-borg attack-slot ranges, difficulty idle pacing, level-0 block,
        // AND the waypoint policy (per-borg engage-radius ring + per-class bearing
        // jitter — flankers orbit behind). Default ON; cfg.useRomAi=false opts back to
        // the legacy heuristic; borgs without extracted params (13/208) use it too.
        input = prof
          ? this.useRomAi && hasRomAiParams(b.borgId)
            ? stepRomAI(b, prof, all, { bounds: this.bounds })
            : stepAI(b, prof, all)
          : emptyInput();
      }
      resolved.set(b.uid, input);
    }

    this.stepPowerBurstInputs(resolved);

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
      stepAmmoRefill(b, prof);
      stepStatus(b);
      stepInvincibility(b);
      stepGaugeWindows(b);
      // Hit-inflicted status decay (status-effects-decode-2026-07-04.md): UNCONDITIONAL,
      // unlike stepGaugeWindows — clears aura levels for re-application this frame and ticks
      // the discrete slow/haste/freeze/size-tier/hero-buff timers regardless of hit reaction.
      stepHitStatus(b);

      // Source lock-on is continuous for active borgs. R/L are edge-triggered switch-lock
      // (+0x73c = 2/3). Z is hold-ally-lock: press requests ally lock (+0x73c = 5), release
      // restores the retained enemy lock (+0x73c = 4). Latches live in cooldowns like
      // movement's jumpHeld, and stepCooldowns skips them.
      const switchLockPressed = input.switchLock && (b.cooldowns["switchLockHeld"] ?? 0) === 0;
      const switchLockPrevPressed =
        input.switchLockPrev && (b.cooldowns["switchLockPrevHeld"] ?? 0) === 0;
      b.cooldowns["switchLockHeld"] = input.switchLock ? 1 : 0;
      b.cooldowns["switchLockPrevHeld"] = input.switchLockPrev ? 1 : 0;
      const allyLockWasHeld = (b.cooldowns["allyLockHeld"] ?? 0) !== 0;
      const allyLockPressed = input.allyLock && !allyLockWasHeld;
      const allyLockReleased = !input.allyLock && allyLockWasHeld;
      b.cooldowns["allyLockHeld"] = input.allyLock ? 1 : 0;

      if (switchLockPressed) {
        sourceSwitchEnemyLock(b, all, "next");
      } else if (switchLockPrevPressed) {
        sourceSwitchEnemyLock(b, all, "prev");
      } else if (allyLockPressed) {
        sourceSwitchAllyLock(b, all);
      } else if (allyLockReleased) {
        sourceReleaseAllyLock(b, all);
      } else {
        refreshSourceTargetLock(b, all);
      }

      const activeTargetUid = activeSourceTargetUid(b);
      const lockPos = activeTargetUid ? this.byUid.get(activeTargetUid)?.pos ?? null : null;
      const ctx: MoveContext = { lockTargetPos: lockPos, bounds: this.bounds, collision: this.collision };

      // ROM-family driver (1:1 ported state machine) — when active, owns the borg's
      // motion + attacks for this frame; skip the generic stepMovement/stepAttacks.
      // See packages/combat/src/bridge.ts. Borgs without a ported family are unaffected.
      if (b.romDriver?.tick(b, SIM.DT, this.state.borgs, input)) {
        // Drain any projectiles the ROM stream's fireChild op spawned this tick.
        const romProjs = b.romDriver.drainProjectiles();
        if (romProjs.length > 0) this.state.projectiles.push(...romProjs);
        continue;
      }

      // Movement (skips horizontal control while busy, but still applies gravity).
      stepMovement(b, prof, input, ctx);
      clearJumpLatch(b, input.jump);

      // Attacks (no-op while busy/hit/down/death/spawn).
      if (!isBusy(b)) {
        const meleeActiveBefore = b.cooldowns["meleeActive"] ?? 0;
        const specialCdBefore = b.cooldowns["special"] ?? 0;
        const res = stepAttacks(b, prof, input.attack, input.special, all, profiles, {
          sideRankForTeam: (team) => this.sideRankForTeam(team),
          // Burst-meter fill plumbing (Q4): applyHit credits the attacker's player per
          // hit connection — see creditBurstFill (burst.ts).
          burstMeters: this.state.burstMeterByPlayer,
          telemetry: this.state.telemetry,
          // T4 FORCE-GAUGE: side energy pool + its once-per-battle max snapshot — see
          // BattleState.energyMax / damageFormula.ts forceGaugeRatioIndex.
          energyByTeam: this.state.energy,
          energyMaxByTeam: this.state.energyMax,
          // T4 item 3: CPU-side x0.5 halvings, Challenge-mode-only (see isChallengeMode doc).
          cpuHalvingEnabled: this.isChallengeMode,
        });
        if (res.projectiles.length) this.state.projectiles.push(...res.projectiles);
        // Results telemetry ATTEMPTS: each attack initiation counts once — a new melee
        // swing (meleeActive grew this frame), each projectile spawned, or a special fire
        // (its cooldown was re-armed this frame). One AoE attempt can connect with several
        // victims, so hits may legitimately exceed attempts. DERIVED semantics
        // (results-scoring-decode-2026-07-04.md, zz_008a5d0_ @0x8008a5d0 via FUN_8008a65c
        // chunk_0013.c:1219-1224): the ROM counts one attempt per attack-object ACTIVATION
        // (rehits excluded) — per-slot attempts are the results screen's "ATTACK" number.
        // The SAME activation also counts INCOMING on the attack's aimed target when it is
        // an enemy (target +0xcc, chunk_0013.c:1110-1121) — whether or not it ever hits;
        // that is the DODGE RATIO's +0x40c counter.
        const t = this.state.telemetry;
        if (t) {
          const meleeActiveAfter = b.cooldowns["meleeActive"] ?? 0;
          const specialFired = (b.cooldowns["special"] ?? 0) > specialCdBefore ? 1 : 0;
          const started =
            (meleeActiveAfter > meleeActiveBefore ? 1 : 0) + res.projectiles.length + specialFired;
          if (started > 0) {
            t.attemptsByTeam[b.team] = (t.attemptsByTeam[b.team] ?? 0) + started;
            if (t.slots) {
              if (b.ownerPlayer !== null) {
                slotTelemetryFor(t.slots, b.ownerPlayer).attempts += started;
              }
              const aimed = activeTargetUid ? this.byUid.get(activeTargetUid) : undefined;
              if (aimed && aimed.team !== b.team && aimed.ownerPlayer !== null) {
                slotTelemetryFor(t.slots, aimed.ownerPlayer).incomingAimed += started;
              }
            }
          }
        }
      }

      // Passive contact damage (ATK-006 scaffold): immediate no-op while
      // CONTACT_DAMAGE.ENABLED stays false (the default) — see combat.ts stepContactDamage
      // for the evidence gap and the per-borg-data enable path.
      stepContactDamage(b, all);

      // Vampire passive self-bleed (ATK-019, (ay)): 1 HP / 30 frames for ids 0x702/0x70a,
      // floored at 1 HP. No-op for non-vampires. The steal half is applied in applyHit.
      stepVampireDrain(b);

      // Advance hit/down/death/spawn timers.
      b.stateTime += 1;
      const r = stepActionState(b);
      if (r.died) {
        this.spawnPlanned.add(this.forceIndexOfUid(b.uid));
      }
    }
    this.drainPowerBursts();
    this.accountPendingDefeats();

    // 3) Projectiles.
    this.state.projectiles = stepProjectiles(
      this.state.projectiles,
      all,
      profiles,
      this.byUid,
      {
        bounds: this.bounds,
        collision: this.collision,
      },
      {
        sideRankForTeam: (team) => this.sideRankForTeam(team),
        // Burst-meter fill plumbing (Q4): projectile hit connections credit the OWNER'S
        // player meter per connection (a persisting beam re-hitting = one credit per
        // connection, matching the ROM's dead-husk 3 x 50 trace).
        burstMeters: this.state.burstMeterByPlayer,
        telemetry: this.state.telemetry,
        // T4 FORCE-GAUGE: see the stepAttacks call above.
        energyByTeam: this.state.energy,
        energyMaxByTeam: this.state.energyMax,
        cpuHalvingEnabled: this.isChallengeMode,
      },
    );
    this.accountPendingDefeats();

    // 4) Process any deaths -> auto-deploy next from that force.
    if (this.spawnPlanned.size > 0) {
      for (const fi of this.spawnPlanned) {
        const force = this.forces[fi];
        if (force && force.activeUid && !(this.byUid.get(force.activeUid)?.alive ?? false)) {
          this.deployNext(force, this.spawnPosFor(fi));
        }
      }
      this.spawnPlanned.clear();
      this.refreshSourceLocks();
    }
    // 5) Energy + win/lose.
    this.recomputeEnergy();
    this.evaluateResult();
    this.tickBattleTimer();

    // 6) Cull fully-dead borgs from the active list to keep arrays small (keep maps for energy already counted via queue=0).
    // NOTE: byUid deliberately RETAINS defeated borgs (alive === false, never deleted). The
    // projectile owner-liveness despawn (stepProjectiles, zz_00840b8_ chunk_0012.c:3216)
    // depends on this: a dead owner is found in byUid with alive=false, which despawns its
    // in-flight projectiles. Deleting entries here would silently disable that despawn (a
    // missing uid is treated as "no liveness info" for synthetic callers).
    this.state.borgs = this.state.borgs.filter((b) => {
      if (!b.alive && b.state === "death" && b.stateTime >= 0 && b.hp <= 0) {
        // Already counted as removed; stays in byUid (see NOTE above).
        return false;
      }
      return b.alive;
    });

    this.state.frame += 1;
    return this.observe();
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
    if (remaining <= 0) {
      this.state.result = "draw";
      this.state.winnerMask = 4; // mask 4 = timeout no-winner (chunk_0003.c:4547-4553)
    }
  }

  private sideRankForTeam(team: number): number {
    return team === 0 ? this.sideRanks[0] : this.sideRanks[1];
  }

  private refreshSourceLocks(): void {
    for (const b of this.state.borgs) {
      if (!b.alive) continue;
      refreshSourceTargetLock(b, this.state.borgs);
    }
  }

  private forceIndexOfUid(uid: string): number {
    return this.forces.findIndex((f) => f.activeUid === uid);
  }

  private accountPendingDefeats(): void {
    for (const b of this.state.borgs) {
      if (b.defeatAccounted || b.hp > 0 || (b.alive && b.state !== "death")) continue;
      const prof = this.profiles.get(b.uid);
      if (!prof) continue;
      b.defeatAccounted = true;
      // DERIVED defeat-list entry (BattleState.defeats — GET drop pool feed, see the field
      // doc in types.ts): appended for EVERY accounted defeat (including the husk — callers
      // that need to filter it out can match borgId === HUSK_BORG_ID). killerTeam/killerOwner
      // are only set on a genuine cross-team damager, same gate the ROM's kill event uses
      // (chunk_0003.c:8066 `pcVar16[0x88] != pcVar18[0x88]`), independent of whether that
      // damager was human or CPU-owned (unlike the slot-telemetry kills counter below, which
      // only credits a PLAYER slot and so requires killerOwner !== null).
      const crossTeamKill =
        b.lastHitAttackerTeam !== undefined && b.lastHitAttackerTeam !== b.team
          ? { killerTeam: b.lastHitAttackerTeam, killerOwner: b.lastHitAttackerOwner ?? null }
          : null;
      (this.state.defeats ??= []).push({
        borgId: b.borgId,
        colorVariant: b.colorVariant ?? 0,
        victimTeam: b.team,
        ...(crossTeamKill ?? {}),
      });
      // W17: husk deaths carry no force cost (energy 0) and are excluded from the defeated
      // counters — the husk respawns indefinitely, so counting it would inflate the
      // score/stat counters with unbounded repeat kills.
      if (b.borgId === HUSK_BORG_ID) continue;
      this.state.defeated[b.team] = (this.state.defeated[b.team] ?? 0) + 1;
      this.state.defeatedEnergy[b.team] = (this.state.defeatedEnergy[b.team] ?? 0) + prof.energy;
      // Results split for the player side: PLAYER BORGS DEFEATED counts human-owned borgs,
      // ALLY BORGS DEFEATED counts CPU teammates (same team, ownerPlayer null).
      if (b.team === 0) {
        if (b.ownerPlayer !== null) this.state.defeatedPlayerBorgs = (this.state.defeatedPlayerBorgs ?? 0) + 1;
        else this.state.defeatedAllyBorgs = (this.state.defeatedAllyBorgs ?? 0) + 1;
      }
      // DERIVED per-slot kill/cost accounting — ROM kill event zz_002f8dc_ @0x8002f8dc
      // (chunk_0003.c:8287-8312, results-scoring-decode-2026-07-04.md): the LAST damager,
      // if cross-team, gets kills(+0x434) and the victim's cost into costWon(+0x420); the
      // victim's own slot books the cost into costLost(+0x424). Ally losses stay OUT of
      // costLost (they are +0x430/+0x437 — validated by the WIN capture: 1 ally lost,
      // player TOTAL COST still 0 and the no-loss +1000 tier still granted).
      const slots = this.state.telemetry?.slots;
      if (slots) {
        const killerOwner = b.lastHitAttackerOwner;
        if (
          killerOwner !== undefined &&
          killerOwner !== null &&
          b.lastHitAttackerTeam !== undefined &&
          b.lastHitAttackerTeam !== b.team
        ) {
          const ks = slotTelemetryFor(slots, killerOwner);
          ks.kills += 1;
          ks.costWon += prof.energy;
        }
        if (b.ownerPlayer !== null) {
          slotTelemetryFor(slots, b.ownerPlayer).costLost += prof.energy;
        }
      }
    }
  }

  private evaluateResult(): void {
    if (this.state.result !== "ongoing") return;
    // Winner-mask judge (behavior-notes (ae), zz_00297c8_ @0x800297c8). A side is "destroyed"
    // when its remaining force reaches 0 — the ROM tests count byte OR energy s32 (rule-flag
    // selectable, chunk_0003.c:4519-4529); here count and energy are coupled (recomputeEnergy
    // sums remaining borgs), so energy<=0 is the single destroyed test. The winner mask
    // (PTR_DAT_80433934[0x1f]) marks who WON: bit0 = side 0, bit1 = side 1, 3 = mutual
    // simultaneous destruction, 0 = no winner yet.
    const teams = [...new Set(this.forces.map((f) => f.team))];
    const survivors = teams.filter((t) => (this.state.energy[t] ?? 0) > 0);
    if (survivors.length === teams.length) return; // nobody destroyed -> battle ongoing

    const mask = survivors.length === 0 ? 3 : survivors.reduce((m, t) => m | (1 << t), 0);
    this.state.winnerMask = mask;

    const human = this.forces.find((f) => f.ownerPlayer !== null);
    const playerTeam = human?.team;
    if (playerTeam === undefined) {
      // All-CPU battle: a lone survivor wins; mutual destruction is a no-winner draw.
      this.state.result = mask === 3 ? "draw" : "win";
      return;
    }
    // Per-side "won" is an EQUALITY test mask == 1<<side, and Challenge advances only when
    // (mask & 1<<playerSide) && mask <= 2 (FUN_801969a0, chunk_0048.c:466-506). Mask 3 (mutual)
    // exits to the same failure screen as a loss, so it resolves to "lose" for the player.
    const playerBit = 1 << playerTeam;
    this.state.result = (mask & playerBit) !== 0 && mask <= 2 ? "win" : "lose";
  }
}

function snapshotActor(actor: BorgRuntime): BattleActorObservation {
  // The ROM driver owns executable behavior and is intentionally absent from the public actor
  // view. Every remaining actor field is structured data, so structuredClone gives a stable
  // fixed-step snapshot including nested position, velocity, cooldown, and weapon-cell facts.
  const { romDriver: _romDriver, ...observable } = actor;
  void _romDriver;
  return structuredClone(observable);
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

/**
 * Package-internal test seam. Selfchecks import this file directly; it is intentionally not
 * re-exported from `@gf/combat` and must not be used by application code.
 */
export function battleStateForSelfcheck(battle: Battle): BattleState {
  if (!(battle instanceof BattleImpl)) throw new TypeError("selfcheck seam requires BattleImpl");
  return battle.stateForSelfcheck();
}

export { SIM };
