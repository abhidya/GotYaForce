import {isSourceTeleportX,getTeleportXState,prepareTeleportX,clearTeleportX} from './teleportX.js';
import {spawnNinjaSource} from './ninjaProjectile.js';
import {isSourceNinjaX,getNinjaXState,prepareNinjaX,clearNinjaX,startNinjaXStream,tickNinjaXStreamPart} from './ninjaX.js';
import {getGRedAirShotState,prepareGRedAirShot,clearGRedAirShot,startGRedAirShotStream,tickGRedAirShotStreamPart} from './gredAirShot.js';
import {getGRedShotState,prepareGRedShot,clearGRedShot,startGRedShotStream,tickGRedShotStreamPart} from './gredShot.js';
import {refreshTargetVisibility} from './families/shared-aimed-shot-x.js';
import {spawnGredRangedSource,prepareGredRangedEntryVisibility} from './gredRangedProjectile.js';
import {getGBlackChargeState,prepareGBlackCharge,clearGBlackCharge,startGBlackChargeStream,tickGBlackChargeStreamPart} from './gblackCharge.js';
import {spawnGBlackChargeSource} from './gblackChargeProjectile.js';
import {getGRedChargeState,prepareGRedCharge,clearGRedCharge,startGRedChargeStream,tickGRedChargeStreamPart} from './gredCharge.js';
import { spawnGBlackGroundWaveSource } from './gblackGroundWaveAdapter.js';
import { getGRedCrashState, prepareGRedCrash, clearGRedCrash,
  startGRedCrashStream, tickGRedCrashStreamPart, beginGRedCrashTick,
  acceptGRedCrashContact } from './gredCrash.js';
import {getGRedAirMeleeState,prepareGRedAirMelee,clearGRedAirMelee,
  startGRedAirMeleeStream,tickGRedAirMeleeStreamPart,beginGRedAirMeleeTick,
  acceptGRedAirMeleeContact} from './gredAirMelee.js';
import {gredAirMeleeStreamProfile} from './gredAirMeleeConfig.js';
import { captureTimeBomberAim, spawnTimeBomberSource } from "./timeBomberProjectile.js";
import { getNurseXState, isNurseX, prepareNurseX, clearNurseX, canStartNurseX, isCloseNurseX } from "./nurseX.js";
import { isArrowNinja, captureArrowAttack, spawnArrowSource } from "./arrowProjectile.js";
import { createBeamStreamClock, tickBeamStream, type BeamStreamClock } from "./beamStream.js";
import { createArrowStreamClock, tickArrowStream, type ArrowStreamClock } from "./arrowStream.js";
import { spawnBeamSource, captureBeamAim } from "./beamProjectile.js";
import { captureRevolverAttack, spawnRevolverSource, isRevolver } from "./revolverProjectileRuntime.js";
import { actorAimTarget } from "./sourceAttackTarget.js";
import { captureGatlingAim, spawnGatlingSource } from "./gatlingProjectile.js";
import { capturePoweredNormalAim, spawnPoweredSource } from "./poweredProjectileRuntime.js";
import { createKnightWindupClock, tickKnightWindupClock, type KnightWindupClock } from "./rom/knight-windup-clock.js";
import { isDiverAmmoFamily } from "./diverAmmo.js";
import { attackHitMaxReachForKind } from "./attackHitData.js";
import { getNeoGredMeleeState, prepareNeoGredMelee, clearNeoGredMelee,
  startNeoGredMeleeStream, tickNeoGredMeleeStreamPart, beginNeoGredMeleeTick,
  acceptNeoGredMeleeContact } from "./neoGredMelee.js";
// Bridge between the existing @gf/combat `BorgRuntime` (the canonical game state —
// HP, lock-on, ammo, gauges, status, projectiles, results telemetry) and the ROM
// `RomActor` runtime (the 1:1 ported state machine). The existing layer stays
// authoritative for everything EXCEPT the action/motion that a ported ROM family
// owns; the bridge syncs fields both ways each frame.
//
// INTEGRATION (3 lines, minimal surgery on the existing code):
//   battle.ts  before stepMovement/stepAttacks:
//     if (b.romDriver?.tick(b, dt, all, ctx)) continue;   // ROM owned this frame
//   combat.ts  X-special branch, before spawnSpecialProjectiles:
//     if (b.romDriver?.tryStartXSpecial(b, all, ctx)) return { projectiles: out };
//
// BorgRuntime keeps its vec3 `vel` model; RomActor uses the ROM's scalar hSpeed +
// yVel model. The bridge decomposes/recomposes each sync.

import { activeSourceTarget } from "./targetLock.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import type { BorgRuntime, MineReceiverMeleeAttack, PlayerInput, RomFamilyDriver } from "./types.js";
import { comboLadderForBorgId, OPEN_WINDOW_ACTIVE_FRAMES } from "./actionStreamData.js";
import type { Vec3 } from "@gf/physics";
import type { RomActor, RomPhysicsRuntime, RomVisibilityTarget } from "./rom/actor.js";
import { createRomActor } from "./rom/actor.js";
import {
  createRomStateTables,
  stepRomActor,
  type StateHandler,
} from "./rom/state-tables.js";
import { resetStreamParts, tickStream } from "./rom/stream-vm.js";
import {
  dispatchCommandRecord,
  dispatchUpperBodyCue,
  dispatchFullBodyCue,
} from "./rom/dispatch.js";
import { configureGRedFamily, type GRedFamilyCtx } from "./families/gred.js";
import { configureDeathBorgFamily } from "./families/death-borg.js";
import { configureClawRobotFamily, configureDeathBorgOmegaFamily } from "./families/shared-aerial-dive-x.js";
import { configureSamuraiClusterFamily, type SamuraiClusterBorgId } from "./families/samurai.js";
import { configureGirlClusterFamily, type GirlClusterBorgId } from "./families/girl-cluster.js";
import { createFamily1Charge3Action, createFamily2Charge3Action } from "./families/shared-charge3.js";
import { createFamily1GunXAction, createFamily2GunXAction } from "./families/shared-gun-x.js";
import {
  createSharedAimedShotX,
  TITAN_ROBOT_X_CONFIG,
  PANTHER_ROBOT_X_CONFIG,
  createTitanPantherGunAction0,
  createTitanPantherAction1,
} from "./families/shared-aimed-shot-x.js";
import {
  createSharedMorphXSpecial,
  TITAN_MORPH_CONFIG,
  PANTHER_MORPH_CONFIG,
  VICTORY_MACHINE_MORPH_CONFIG,
} from "./families/shared-morph-x.js";
import { configureSatelliteFamily, satelliteFamilyUpdate } from "./families/satellite.js";
import { stepRng8 } from "./prng.js";
import { configureStarHeroFamily } from "./families/star-hero.js";
import { configureCyberMachineFamily } from "./families/cyber-machine.js";
import {
  configureMachineRedFamily,
  configureMachineBlueFamily,
  type MachineRedBorgId,
  type MachineBlueBorgId,
} from "./families/machine-red-blue.js";
import { configureDragonFamily } from "./families/dragon.js";
import { configureCyberDragonFamily } from "./families/cyber-dragon.js";
import { configureWormFamily } from "./families/worm.js";
import { configureWireGunnerFamily } from "./families/wire-gunner.js";
import { configureRobotFamily } from "./families/robot.js";
import { configureMagnetRobotFamily } from "./families/magnet-robot.js";
import { configureOmega2Family } from "./families/omega2-robot.js";
import { configureDrillFamily } from "./families/drill-robot.js";
import { configureThunderFamily } from "./families/thunder-robot.js";
import { configureHammerFamily } from "./families/hammer-robot.js";
import { configureKnightFamily } from "./families/knight-family.js";
import { configureBeamWingFamily } from "./families/beam-wing.js";
import { configureEagleJetFamily } from "./families/eagle-jet.js";
import { configureEagleRobotFamily } from "./families/eagle-robot.js";
import { createRobotDashHandler, ROBOT_ACTION0_CONFIGS, type RobotDashConfig } from "./families/shared-robot-dash.js";
import { configureSwordKnightFamily } from "./families/sword-knight.js";
import { createGenericKnightRootAction } from "./families/shared-knight-melee.js";
import { configureJellyDiverFamily } from "./families/jelly-diver.js";
import { configureCopyManFamily } from "./families/copy-man.js";
import { createMeleeRobot, ROBOT_MELEE_RANGE_ROWS } from "./families/melee-robot.js";
import { createMeleeSamurai, SAMURAI_MELEE_DEFAULT_CONFIG } from "./families/melee-samurai.js";
import { configureValkrieFamily } from "./families/valkrie.js";
import { configureNurseFamily } from "./families/nurse-wizard-idol.js";
import { configureTankFamily } from "./families/tank-borg.js";
import { configureBeamTankFamily } from "./families/beam-tank.js";
import { configureIcbmTankFamily } from "./families/icbm-tank.js";
import { configureUltimateCannonFamily } from "./families/ultimate-cannon.js";
import { configureGatlingTankFamily } from "./families/gatling-tank.js";
import { configureArrowNinjaFamily } from "./families/arrow-ninja.js";
import { configureFortressFamily } from "./families/fortress-borg.js";
import {
  configureDeathBorgMuFamily,
  configureDeathBorgNuFamily,
  configureDeathEyeFamily,
  configureRoachFamily,
} from "./families/death-borg-nu.js";
import { configureFighterFamily } from "./families/fighter-craft.js";
import { configurePhoenixDragonFamily } from "./families/phoenix-dragon.js";
import { configureSiriusFamily } from "./families/sirius.js";
import { configureVehicleFamily } from "./families/vehicle-borg.js";
import { configureVictoryJetFamily } from "./families/victory-jet.js";
import { configureVictoryKingFamily } from "./families/victory-king.js";
import { configurePantherVehicleFamily } from "./families/panther-vehicle.js";
import { configureAccelerationNinjaFamily } from "./families/acceleration-ninja.js";
import { configureWingSoldierFamily } from "./families/wing-soldier.js";
import { configureCosmicDragonFamily } from "./families/cosmic-dragon.js";
import { configureGoldHeroFamily } from "./families/gold-hero.js";
import { configureCyberHeroFamily } from "./families/cyber-hero.js";
import { configureNormalNinjaFamily, configureDoubleNinjaFamily, configureShurikenNinjaFamily } from "./families/ninja-cluster.js";
import { configureFlameNinjaFamily, configureCyberNinjaFamily } from "./families/flame-cyber-ninja.js";
import { configureTeleportNinjaFamily } from "./families/teleport-ninja.js";
import {
  configurePatraWitchFamily,
  configureBastetWitchFamily,
  configureBugWitchFamily,
  configureGuardWitchFamily,
} from "./families/witch-cluster.js";
import {
  configureRevolverGunmanFamily,
  configureBeamGunnerFamily,
  configureGatlingGunnerFamily,
  configurePoweredGunmanFamily,
} from "./families/gunman-cluster.js";
import {
  configureSapphireKnightFamily,
  configureElementalKnightFamily,
  configureImperialKnightFamily,
  configureDarkKnightFamily,
  configureAxeKnightFamily,
  configureChainsawKnightFamily,
} from "./families/knight-cluster.js";
import { configureKungFuMasterFamily } from "./families/kung-fu-master.js";
import { configureTaoMasterFamily } from "./families/tao-master.js";
import {
  configureAnubisWingFamily,
  configureDemonWingFamily,
  configureDeathBorgSigmaFamily,
  configureDeathBorgBetaFamily as configureDeathBorgBetaIIFamily,
} from "./families/wing-blob-cluster.js";
import {
  configureDeathBorgAlphaFamily,
  configureDeathBorgBetaFamily,
  configureDeathBorgTauFamily,
  configureMetalHeroFamily,
  configurePopHoneyFamily,
  configureJetHeroFamily,
  configureCarrierHelicopterFamily,
  configureFlyingSaucerFamily,
} from "./families/unregistered-cluster.js";
import { configureDeathBorgChiFamily } from "./families/death-borg-chi.js";
import { configureWaveBFamily } from "./families/wave-b-catch-all.js";
import { HERO_X_BUFF, MELEE } from "./constants.js";
import { applyActorParamTierDelta127 } from "./paramTier.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./families/shared-engine.js";
import { spawnRomProjectile } from "./projectiles.js";
import { movementPhysicsForBorgId } from "./movementData.js";
import { sourceStatsForBorgId } from "./sourceBorgStats.js";
import { tierSizeScale } from "./timescale.js";
import type { Projectile, ProjectileVisualKind, WeaponCell } from "./types.js";
import attackHitTablesData from "./data/attackHitTables.json" with { type: "json" };
import actionStreamTablesData from "./data/actionStreamTables.json" with { type: "json" };
import meleeAnimKindsData from "./data/meleeAnimKinds.json" with { type: "json" };
import familyCueTablesFullData from "./data/familyCueTablesFull.json" with { type: "json" };
import animMetadataHopData from "./data/animMetadataHop.generated.json" with { type: "json" };

const TAU = Math.PI * 2;
const BAM_FULL = 0x10000;
const ACTOR_SIZE_NORMALIZER = 167.75999450683594; // FLOAT_80437620
// Never reset with a bridge replacement: a surviving mine may retain an older
// activation from the same owner UID (morph/rebind must not reuse that identity).
let mineMeleeSerial = 0;
/** zz_0068004_: max(data page +0x4c, +0x50) / FLOAT_80437620. The Girl pages
 * share 9/6 except pl0308 (25/3); values were read directly from pl####data.bin. */
function girlDescriptorSizeScale(borgId: string): number {
  if (borgId === "pl0308") return 25 / ACTOR_SIZE_NORMALIZER;
  return /^pl030[0-9a-d]$/.test(borgId) ? 9 / ACTOR_SIZE_NORMALIZER : 1;
}

/** An armed hitbox window (from attackHitTables.json, looked up per kind). */
interface ArmedHit {
  /** Only the admitted NEO chain uses activation-wave actor identity. */
  neoActivated?: boolean;
  /** Scoped G RED-family X HIT lifecycle. Countdown advances on active HIT
   * updates even when mode8 freezes animation; burst/hitstop gates are unbound. */
  crashHit?: { recordIndex: number; activated: boolean; refresh: number; countdown: number;
    localOffset: readonly number[]; radius: number };
  /** Admitted airborne B refresh0 volumes. BLACK's later overlapping record
   * renews the shared actor identity for BOTH volumes before the pair pass. */
  airMeleeHit?: {recordIndex:number;activated:boolean;shapeKind:0|2;
    localOffset:readonly number[];halfExtent:readonly number[];radius:number};
  collisionFlags: number;
  activeStart: number;
  activeEnd: number;
  reach: number;
  damageRecordIndex: number;
  /** Uids already struck by this window or shared source activation identity. */
  struck: Set<string>;
  /** One identity for this supported armHit activation, shared across its active frames. */
  mineReceiverAttackUid?: string;
}
let gredCrashHitSerial=0;
let gredAirMeleeHitSerial=0;
// One namespace across admitted B/X routes and replacement bridges. A cached
// clip must not mistake a new animation start for an earlier source epoch.
let sourceAnimationSerial=0;

// Lazy-loaded per-borg hit-table data (attackHitTables.json). Loaded once, cached.
const HIT_TABLES: Record<string, { kinds: Record<string, number[]>; records: Record<string, unknown> }> =
  (attackHitTablesData as { borgs: Record<string, { kinds: Record<string, number[]>; records: Record<string, unknown> }> }).borgs;
function hitTablesFor(borgId: string): { kinds: Record<string, number[]>; records: Record<string, unknown> } | null {
  return HIT_TABLES[borgId] ?? null;
}

// --- Pre-decoded stream events (meleeAnimKinds.json) ---
// The stream banks' bytecode is already decoded into frame-keyed events by
// scripts/gen-melee-anim-kinds.mjs. The bridge plays these back directly, bypassing
// the raw bytecode walker when familyStreamBank is null (which it is for all families
// until the bank-byte extractor lands). This gives every family working anim + hitbox
// arming from the ALREADY-DECODED data.

interface StreamEvent {
  op: string;
  frame?: number;
  kind?: number;
  statusId?: number;
  statusArg?: number;
  group?: number;
  slot?: number;
  mode?: number;
  blend?: boolean;
  part?: number;
  state?: number;
  aux?: number;
  variant?: number;
}

const ACTION_STREAM_DATA = actionStreamTablesData as unknown as {
  borgs: Record<string, {
    actions?: Record<string, {
      variants?: Record<string, { bank?: string } | undefined>;
    }>;
  }>;
};

const ACTION_STREAM_BANKS: Record<string, { bank: string; group: number; seedSlot: number } | undefined> = (() => {
  const data = actionStreamTablesData as unknown as { borgs: Record<string, { actions: Record<string, { variants: Record<string, { bank: string; group: number; seedSlot: number } | undefined> }> }> };
  const out: Record<string, { bank: string; group: number; seedSlot: number } | undefined> = {};
  for (const [borgId, b] of Object.entries(data.borgs || {})) {
    const xLeaf = b.actions?.["2"]?.variants?.["0"];
    if (xLeaf) out[borgId] = { bank: xLeaf.bank, group: xLeaf.group, seedSlot: xLeaf.seedSlot ?? 0 };
  }
  return out;
})();

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const MELEE_ANIM_BANKS: Record<string, any> = (meleeAnimKindsData as { banks?: Record<string, unknown> }).banks ?? {};

// --- +0x1d88 anim-metadata hop (animMetadataHop.generated.json) ---
// The playAnim stream op's operands are (metaBank, metaAnim) — NOT the motion-file
// (group, slot). Each borg's familyAnimDescBank (+0x1d88) remaps (metaBank, metaAnim)
// → (motionFile, animInFile) via a two-hop s16 table (DOL-dumped by
// scripts/gen-anim-metadata-hop.mjs). Borgs without a remap entry (ctor has no
// metadata bank, or the specific (metaBank, metaAnim) pair isn't in the bank) fall
// back to the direct (group, slot) lookup — preserving the 24 already-working borgs
// and G RED. See research/decomp/title-intro-residuals-decode-2026-07-06.md §1.
type AnimMetaEntry = { motionFile: number; animInFile: number; shared: boolean };
const ANIM_META_HOP: Record<string, Record<string, Record<string, AnimMetaEntry>>> =
  (animMetadataHopData as { borgs?: Record<string, Record<string, Record<string, AnimMetaEntry>>> }).borgs ?? {};

/** Resolve a playAnim (metaBank, metaAnim) pair to the motion-file (group, slot) the
 *  renderer should load. Returns null when no remap exists (caller falls back to the
 *  raw metaBank/metaAnim as motion-file group/slot — the legacy behavior). */
function resolveAnimMetaHop(
  borgId: string,
  metaBank: number,
  metaAnim: number,
): { group: number; slot: number } | null {
  const entry = ANIM_META_HOP[borgId]?.[String(metaBank)]?.[String(metaAnim)];
  if (!entry) return null;
  // motionFile bit7 selects the SHARED motion set (+0x1d7c). Shared-motion entries
  // should resolve into the shared borg's baked clips; until the shared motion-set
  // owner is ported, approximate with the borg's own g0 (TODO: shared motion set).
  // TODO(shared-motion-set): resolve motionFile bit7 entries via +0x1d7c / DAT_80436254.
  const group = entry.shared ? 0 : entry.motionFile;
  return { group, slot: entry.animInFile };
}

/** Look up the pre-decoded stream events for a borg's X-special. Returns null when
 *  the borg has no decoded action-stream data (uncommon — 156/208 borgs have it). */
function streamEventsForSlot(
  borgId: string,
  actionIndex: number,
  variantIndex: number,
  groupIndex: number,
  slotIndex: number,
): StreamEvent[] | null {
  const variants = ACTION_STREAM_DATA.borgs[borgId]?.actions?.[String(actionIndex)]?.variants;
  const leaf = variants?.[String(variantIndex)] ?? variants?.["0"];
  const bankAddress = leaf?.bank ?? ACTION_STREAM_BANKS[borgId]?.bank;
  if (!bankAddress) return null;
  const bank = MELEE_ANIM_BANKS[bankAddress];
  if (!bank) return null;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  const group = bank.groups?.["g" + groupIndex] as any;
  const slot = group?.["s" + slotIndex] as { events?: StreamEvent[] } | undefined;
  return slot?.events ?? null;
}

/** BorgRuntime.rotY is in radians (atan2(x,z) convention, +Z forward); RomActor.heading
 *  is BAM16 (0..0xFFFF, 0 = +Z forward). */
function radToBam(rad: number): number {
  let bam = Math.round((rad / TAU) * BAM_FULL);
  bam &= 0xffff;
  if (bam >= 0x8000) bam -= 0x10000;
  return bam;
}
function bamToRad(bam: number): number {
  let s = bam & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return (s / BAM_FULL) * TAU;
}

/** Decompose BorgRuntime.vel (vec3) into RomActor's scalar hSpeed + yVel model. */
function decomposeVel(vel: Vec3): { hSpeed: number; yVel: number } {
  return { hSpeed: Math.hypot(vel.x, vel.z), yVel: vel.y };
}
/** Recompose RomActor's hSpeed (yaw-projected) + yVel back into BorgRuntime.vel. */
function recomposeVel(hSpeed: number, yVel: number, yawBam: number): Vec3 {
  const rad = bamToRad(yawBam);
  // Match physics.ts: pos.x += hSpeed × sin(yaw); pos.z += hSpeed × cos(yaw).
  // The sign of hSpeed carries direction (the ROM allows negative hSpeed for reverse).
  return { x: Math.sin(rad) * hSpeed, y: yVel, z: Math.cos(rad) * hSpeed };
}

/** Per-family registry. Maps borg-id → factory that wires the RomActor + cue table.
 *  Returns null for borgs whose family hasn't been ported yet (they keep the generic
 *  archetype logic). */
export interface FamilyRegistration {
  /** Configure a freshly-created RomActor for this borg-id (sets the family virtual,
   *  stamps the borg-number switch, etc.). */
  configure: (actor: RomActor, ctx: RomHostContext) => void;
  /** The cue→state table for this family (48 entries × 2 bytes). Extracted from
   *  boot.dol; hardcoded for G RED until the extractor script lands. */
  cueTable: Int8Array;
  /**
   * The family's `+0x4bc` PER-FRAME virtual — the ROM invokes it every frame regardless of
   * what action (if any) the actor is running, so `tick()` calls it BEFORE its
   * `specialActive` early-return. That is the whole point of the offset: these handlers do
   * the between-actions housekeeping (ammo-regen latch clears, cooldown bookkeeping) that
   * an action-gated hook can never reach.
   *
   * Optional: only families with a ported +0x4bc set it.
   */
  frameUpdate?: (actor: RomActor, runtime: BorgRuntime) => void;
}

// Lazily built so the cue-table data consts below are initialized first (the
// registrations read cueTableForBorg at construction time).
let FAMILY_REGISTRY_CACHE: Record<string, FamilyRegistration> | null = null;
function familyRegistry(): Record<string, FamilyRegistration> {
  if (!FAMILY_REGISTRY_CACHE) {
    FAMILY_REGISTRY_CACHE = {
      // G RED family (ctor 0x8018ccfc) — cue table @0x80365cf8, full 48-row DOL dump.
      pl0615: makeGRedFamilyRegistration(),
      pl0629: makeGRedFamilyRegistration(),
      pl062a: makeGRedFamilyRegistration(),
      // NORMAL NINJA family (ctor 0x8006f4f8) — bespoke action 0/1 ported in
      // families/ninja-cluster.ts (composes ninja.ts action-2 X via shared zz_00ff2bc_).
      pl0000: makeSimpleRegistration("pl0000", (a, ctx) => configureNormalNinjaFamily(a, "pl0000", ctx)),
      pl000a: makeSimpleRegistration("pl000a", (a, ctx) => configureNormalNinjaFamily(a, "pl000a", ctx)),
      // DOUBLE NINJA (pl0003, ctor 0x8006f60c) + SHURIKEN NINJA (pl0001, ctor 0x800ea500)
      // — bespoke melee/X ports in families/ninja-cluster.ts.
      pl0003: makeSimpleRegistration("pl0003", (a, ctx) => configureDoubleNinjaFamily(a, ctx)),
      pl0001: makeSimpleRegistration("pl0001", (a, ctx) => configureShurikenNinjaFamily(a, ctx)),
      // FLAME NINJA (pl0006, ctor 0x800b2ef8) + CYBER NINJA (pl0007, ctor 0x800a6f4c)
      // — bespoke multi-action ports in families/flame-cyber-ninja.ts.
      pl0006: makeSimpleRegistration("pl0006", (a, ctx) => configureFlameNinjaFamily(a, ctx)),
      pl0007: makeSimpleRegistration("pl0007", (a, ctx) => configureCyberNinjaFamily(a, ctx)),
      // DEATH BORG ALPHA family (ctor 0x8019e9a4) — third family on the shared-X
      // machine (config @0x80435750). pl000c ONLY: pl0008's X command is descriptor-
      // disabled in the ROM (+0xba mode 0xff) — it keeps the generic fallback.
      pl000c: makeDeathBorgFamilyRegistration(),
      // DEATH BORG ALPHA (pl0008, ctor 0x8019e9a4) + DEATH BORG BETA (pl0109, ctor 0x801d8730)
      // — unregistered-cluster ports (families/unregistered-cluster.ts).
      pl0008: makeSimpleRegistration("pl0008", (a, ctx) => configureDeathBorgAlphaFamily(a, ctx)),
      // ---- Wave-A verified shared-engine families (2026-07-06, wf_1141168b-7b5) ----
      // Aerial dive/leap-shot engine zz_00f41c4_ (shared-aerial-dive-x.ts):
      pl0400: withRobotDash(makeSimpleRegistration("pl0400", (a, ctx) => configureClawRobotFamily(a, "pl0400", ctx)), ROBOT_ACTION0_CONFIGS.pl0400),
      pl040a: withRobotDash(makeSimpleRegistration("pl040a", (a, ctx) => configureClawRobotFamily(a, "pl040a", ctx)), ROBOT_ACTION0_CONFIGS.pl040a),
      pl0406: makeSimpleRegistration("pl0406", (a, ctx) => configureDeathBorgOmegaFamily(a, "pl0406", ctx)),
      // GIRL cluster (families/girl-cluster.ts, 2026-07-06): 14 borgs / 8 families on
      // the shared action-0 B-ranged volley (variant table 0x80325a00, G-A/G-B/G-C
      // tables @0x80325a14/a20/a2c) + the 5 shared melee tables (M-1..M-5
      // @0x80325a68..aa8, per-family seed slots) + per-family X machines
      // (battle @0x80433b18, barrier @0x804344d8, killer @0x80336da4, shared cfg X
      // @0x80434508; cyber-girl.ts + shared-series3-x.ts machines REUSED). Supersedes
      // the earlier series-3-only registrations (pl0301/0302/0303/0306/0307/030d),
      // the cyber-girl-only registrations (pl0305/0309/030a), the wave-B shared-engine
      // fallbacks (pl0300/030b, pl0304/0308), and the wave-C girlMelee injection.
      ...girlClusterRegistrations(),
      // Samurai cluster (families/samurai.ts, 2026-07-06): 13 borgs / 6 families on
      // the shared S-A ranged dash-slash (table 0x8033ed0c) + S-B close slash (table
      // 0x8033ed20) + per-family action-1 v2 machines + zz_0149178_ lunge (v3/v4, ROM
      // config) + X (shared lance flight zz_0149708_; SONIC/SHOGUN bespoke tables).
      ...samuraiClusterRegistrations(),
      // Charge-3 release engine zz_0177a3c_ + morph engine zz_017a374_ composites:
      // plus the shared GUN volley (action 0, zz_0177634_) for the tank line.
      pl0619: makeSimpleRegistration("pl0619", (a, ctx) => {
        a.borgNumber = 0x619;
        a.rootAction = composeActionTable([createFamily1GunXAction(ctx), null, null, createFamily1Charge3Action(ctx), null]);
        a.defaultGroup = 0;
        a.streamSlot = 0;
      }),
      pl061f: makeSimpleRegistration("pl061f", (a, ctx) => {
        // VICTORY TANK: gun volley at [0] + charge3 at [3]; its morph branch is a DEAD
        // borg branch (verified) — action 2 keeps the generic fallback.
        a.borgNumber = 0x61f;
        a.rootAction = composeActionTable([createFamily2GunXAction(ctx), null, null, createFamily2Charge3Action(ctx), null]);
        a.defaultGroup = 0;
        a.streamSlot = 0;
      }),
      pl0625: makeSimpleRegistration("pl0625", (a, ctx) => {
        // VICTORY MACHINE: gun volley at [0] + morph at [2] + charge3 at [3].
        a.borgNumber = 0x625;
        a.rootAction = composeActionTable([
          createFamily2GunXAction(ctx), null,
          createSharedMorphXSpecial(VICTORY_MACHINE_MORPH_CONFIG, ctx, {}),
          createFamily2Charge3Action(ctx),
          null,
        ]);
        a.defaultGroup = 0;
        a.streamSlot = 0;
      }),
      // Titan/Panther robots: morph at [2] + aimed-shot at [3] (two engines composed).
      pl0604: makeMorphAimedComposite("pl0604", 0x604, "titan", TITAN_MORPH_CONFIG, TITAN_ROBOT_X_CONFIG, true),
      pl0618: makeMorphAimedComposite("pl0618", 0x618, "titan", TITAN_MORPH_CONFIG, TITAN_ROBOT_X_CONFIG, false),
      pl0613: makeMorphAimedComposite("pl0613", 0x613, "panther", PANTHER_MORPH_CONFIG, PANTHER_ROBOT_X_CONFIG, true),
      pl0627: makeMorphAimedComposite("pl0627", 0x627, "panther", PANTHER_MORPH_CONFIG, PANTHER_ROBOT_X_CONFIG, false),
      // PANTHER VEHICLE (pl0628, ctor 0x8018bb6c) — bespoke action-0 volley + action-3
      // charge machines (families/panther-vehicle.ts). Actions 1/2 are morph-back paths,
      // not player command slots; they keep the generic fallback.
      pl0628: makeSimpleRegistration("pl0628", (a, ctx) => configurePantherVehicleFamily(a, "pl0628", ctx)),
// Eagle Robot / Proto Eagle bespoke action 0; pl0606 composes its shared morph X.
pl0606: makeSimpleRegistration("pl0606", (a, ctx) => configureEagleRobotFamily(a, "pl0606", ctx)),
pl061a: makeSimpleRegistration("pl061a", (a, ctx) => configureEagleRobotFamily(a, "pl061a", ctx)),
      // EAGLE JET (ctor 0x8012ae74): action 1 is the code-driven 45-frame handler
      // FUN_8012b458. Other action rows retain the generic host fallback.
      pl061b: makeSimpleRegistration("pl061b", (a, ctx) => configureEagleJetFamily(a, ctx)),
      // Satellite family (engine 0x80188da4, x-action 1 + B actions):
      pl0d01: makeSatelliteRegistration("pl0d01"),
      pl0d05: makeSatelliteRegistration("pl0d05"),
      // STAR HERO family (ctor 0x8010f5ac) — cue table @0x80326cf0. PLANET HERO (pl080c)
      // shares the entire family module (status-effects-decode §A verified chain).
      pl0804: makeStarHeroFamilyRegistration(),
      pl080c: makeStarHeroFamilyRegistration(),
      // GOLD HERO (pl0802, ctor 0x8013c714) — bespoke blast/melee (tables @0x803399f8…);
      // CYBER HERO (pl0808, ctor 0x801d9314) — bespoke blink-dash/charge-flurry/recovery
      // (tables @0x8038a6d8…); see families/gold-hero.ts + families/cyber-hero.ts.
      pl0802: makeSimpleRegistration("pl0802", (a, ctx) => configureGoldHeroFamily(a, ctx)),
      pl0808: makeSimpleRegistration("pl0808", (a, ctx) => configureCyberHeroFamily(a, ctx)),
      // KUNG-FU MASTER (pl0800, ctor 0x80076784) + TAO MASTER (pl0801, ctor 0x800a3b34)
      // — hero melee archetype; see families/kung-fu-master.ts + tao-master.ts.
      pl0800: makeSimpleRegistration("pl0800", (a, ctx) => configureKungFuMasterFamily(a, ctx)),
      pl0801: makeSimpleRegistration("pl0801", (a, ctx) => configureTaoMasterFamily(a, ctx)),
      // DEATH BORG TAU (pl0807, ctor 0x801a04f0) + METAL HERO (pl080a, ctor 0x801bfe64)
      // + POP HONEY (pl0904, ctor 0x8012c498) + JET HERO (pl0a01, ctor 0x80100ef4)
      // — unregistered-cluster ports (families/unregistered-cluster.ts).
      pl0807: makeSimpleRegistration("pl0807", (a, ctx) => configureDeathBorgTauFamily(a, ctx)),
      pl080a: makeSimpleRegistration("pl080a", (a, ctx) => configureMetalHeroFamily(a, ctx)),
      pl0904: makeSimpleRegistration("pl0904", (a, ctx) => configurePopHoneyFamily(a, ctx)),
      pl0a01: makeSimpleRegistration("pl0a01", (a, ctx) => configureJetHeroFamily(a, ctx)),
      // VICTORY KING family (ctor 0x8015a494) — cue table @0x80344b50. X-special routes
      // through the shared engine zz_017a374_ (phase table 0x804347b0): action-2 handler
      // FUN_8015ad10 delegates all arms to zz_017a374_ (no bespoke family phase machine).
      // X group-4 seed slot per borg (actionStreamTables): pl0610 gnd 0 / air 1,
      // pl0621 slot 0, pl0623 slot 1; pl061e has no action 2.
      // VICTORY KING family (ctor 0x8015a494) — bespoke action-0 dash + action-3
      // B-charge flurry (tables @0x804346f8 / @0x803448b0); see families/victory-king.ts.
      // Action 2 (X-special) routes through the shared engine zz_017a374_.
      pl0610: makeSimpleRegistration("pl0610", (a, ctx) => configureVictoryKingFamily(a, "pl0610", ctx)),
      pl061e: makeSimpleRegistration("pl061e", (a, ctx) => configureVictoryKingFamily(a, "pl061e", ctx)),
      pl0621: makeSimpleRegistration("pl0621", (a, ctx) => configureVictoryKingFamily(a, "pl0621", ctx)),
      pl0623: makeSimpleRegistration("pl0623", (a, ctx) => configureVictoryKingFamily(a, "pl0623", ctx)),
      // SWORD KNIGHT family (ctor 0x80073b70) — cue table @0x802d4b50. NORMAL KNIGHT
      // (pl020a) and DEATH BORG GAMMA II (pl020f) share the entire family module (the
      // ctor block-copies word @0x802d47b8 to all three; only pl0200 wires command
      // records to the X-special actionIndex 2 — cue-script-stream-decode §"Second family").
      pl0200: makeSwordKnightFamilyRegistration(),
      pl020a: makeSwordKnightFamilyRegistration(),
      pl020f: makeSwordKnightFamilyRegistration(),
      // FLAME DRAGON family (ctor 0x80075658) — cue table @0x802d5a58. All 6 members
      // share the bespoke X-special phase machine (3 breath variants); see families/dragon.ts.
      pl0500: makeDragonFamilyRegistration(),
      pl0509: makeDragonFamilyRegistration(),
      pl050a: makeDragonFamilyRegistration(),
      pl050c: makeDragonFamilyRegistration(),
      pl0515: makeDragonFamilyRegistration(),
      pl0516: makeDragonFamilyRegistration(),
      // CYBER DEATH DRAGON family (ctor 0x800b8188) — cue table @0x802fec20. All 6
      // members share the bespoke X-special phase machine (3 breath variants); see
      // families/cyber-dragon.ts. Sister port of FLAME DRAGON (same 3-variant
      // ground/air/charged structure, identical float constants at FLOAT_804384*).
      pl0503: makeCyberDragonFamilyRegistration(),
      pl0506: makeCyberDragonFamilyRegistration(),
      pl0507: makeCyberDragonFamilyRegistration(),
      pl050f: makeCyberDragonFamilyRegistration(),
      pl0512: makeCyberDragonFamilyRegistration(),
      pl0513: makeCyberDragonFamilyRegistration(),
      // ALIEN WORM family (ctor 0x80118cb8) — cue table @0x8032b8d8. All 4 members
      // share the bespoke X-special spawn dispatcher (FUN_80118efc); see
      // families/worm.ts. pl0501/pl050d spawn a worm-child via FUN_8011a108;
      // pl050b/pl0517 spawn a venom/poison cloud via zz_01d4d00_.
      pl0501: makeWormFamilyRegistration(),
      pl050b: makeWormFamilyRegistration(),
      pl050d: makeWormFamilyRegistration(),
      pl0517: makeWormFamilyRegistration(),
      // CYBER MACHINE family (ctor 0x800cc454) — cue table @0x8030c3c0. The four
      // beast-god borgs (SEIRYU/SUZAKU/BYAKKO/GENBU) share the entire family module
      // (X-special = ammo-gated shot deploy, FUN_800ce5dc).
      pl0602: makeCyberMachineFamilyRegistration(),
      pl060a: makeCyberMachineFamilyRegistration(),
      pl060c: makeCyberMachineFamilyRegistration(),
      pl060e: makeCyberMachineFamilyRegistration(),
      // MACHINE RED family (ctor 0x800c91bc) — cue table @0x8030a248. The four machine
      // borgs (MACHINE RED/CYBER MARS/PROTO RED/PROTO MARS) share the X-special engine
      // zz_0179d20_ (phaseTable 0x804347a8, group 4 seed slot 0) — the same shared
      // X-special engine has its own two-entry table and family callback. The dedicated
      // module preserves those boundaries instead of aliasing a similar dash engine.
      pl0600: makeMachineRedFamilyRegistration(),
      pl0608: makeMachineRedFamilyRegistration(),
      pl0616: makeMachineRedFamilyRegistration(),
      pl061c: makeMachineRedFamilyRegistration(),
      // MACHINE BLUE family (ctor 0x800ce730) — cue table @0x8030c9c8. The four
      // machine borgs (MACHINE BLUE/CYBER ATLAS/PROTO BLUE/PROTO ATLAS) share the
      // X-special engine zz_0179fcc_ (phaseTable 0x80352b64, group 4 seed slot 0 /
      // air slot 1) — the same shared group-4 X-special engine family used by 12+
      // other borgs. Action-2 leaf FUN_800cf9cc (chunk_0021.c:4080) is a thin wrapper
      // that halves steerYaw (+0x18da >>= 1) then tail-calls the shared engine; no
      // action 3/4 hardpoint handlers are constructor-specific; the dedicated module
      // owns the full live routing table and delegates only the proven shared X leaf.
      pl0601: makeMachineBlueFamilyRegistration(),
      pl0609: makeMachineBlueFamilyRegistration(),
      pl0617: makeMachineBlueFamilyRegistration(),
      pl061d: makeMachineBlueFamilyRegistration(),
      // DEMON SAMURAI family (ctor 0x801223c0) — cue table @0x8032d4d8. Registered in
      // the samurai cluster block above (families/samurai.ts): full action 0/1/2
      // machines, X via the real zz_0149708_ port with the borg-switched configs
      // (@0x8032c814 pl0701/pl0708; @0x8032c838 pl070c/pl070d).
      // BUILD ROBOT family (ctor 0x80112b44) — cue table @0x80328148. The three robot
      // borgs (BUILD/MEGATON/ARMY) share the bespoke X-special dive-bomb deploy
      // (FUN_801132f8 → PTR_FUN_80327f98 phase machine); see families/robot.ts. The
      // phase-1 contact spawns a borg-switched child: pl0402/pl0408 via zz_01138c0_
      // (family child-deploy), pl0407 via FUN_801b8b6c (MEGATON heavy deploy, one-shot
      // latched). All 3 members share ctor 0x80112b44 + group-4 seedSlot 0 (air 1).
      pl0402: withRobotDash(makeRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0402),
      pl0407: withRobotDash(makeRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0407),
      pl0408: withRobotDash(makeRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0408),
      // WIRE GUNNER family (ctor 0x801301f8) — cue table @0x80336178. The three gunner
      // borgs share the bespoke X-special phase machine FUN_80131688 → zz_01316e0_
      // (direction-gated aim→fire shot deploy, group 4 slots 2/3/4); see
      // families/wire-gunner.ts.
      pl0103: makeWireGunnerFamilyRegistration(),
      pl0106: makeWireGunnerFamilyRegistration(),
      pl0107: makeWireGunnerFamilyRegistration(),
      // CYBER GIRL family (ctor 0x8012f204) — registered in the girl-cluster block
      // above (families/girl-cluster.ts): the bespoke X (families/cyber-girl.ts) is
      // reused unchanged, and actions 0/1 gain their ROM machines.
      // ---- Wave-B: batch-registered 2-borg families via shared engine (2026-07-06) ----
      // Generated by tmp_gen_regs.mjs: each entry pairs the family's data-driven cue
      // table (cueTableForBorg) with a shared-engine rootAction. Borgs whose X-special
      // stream bank/group/seedSlot has not yet been extracted get the cue table only —
      // rootAction stays null so the generic combat layer owns the X press.
      // NORMAL TANK / LEOPARD family (ctor 0x8007ca5c) — shared-X engine (group 4 seed 0).
      pl0c00: makeSimpleRegistration("pl0c00", (a, ctx) => configureTankFamily(a, "pl0c00", ctx)),
      // GATLING TANK (pl0c01, ctor 0x800ad7cc) — bespoke 2-action port
      // (families/gatling-tank.ts): B volley + X-special.
      pl0c01: makeSimpleRegistration("pl0c01", (a, ctx) => configureGatlingTankFamily(a, ctx)),
      // BEAM TANK (pl0c02, ctor 0x80105144) — bespoke 3-action port
      // (families/beam-tank.ts): B volley + B charge + X-special.
      pl0c02: makeSimpleRegistration("pl0c02", (a, ctx) => configureBeamTankFamily(a, ctx)),
      // ULTIMATE CANNON (pl0c04, ctor 0x800b05b4) — bespoke 3-action port
      // (families/ultimate-cannon.ts): B volley + X-special + B-charge launch.
      pl0c04: makeSimpleRegistration("pl0c04", (a, ctx) => configureUltimateCannonFamily(a, ctx)),
      // ICBM TANK (pl0c05, ctor 0x800af538) — bespoke 2-action port
      // (families/icbm-tank.ts): B volley + X-special.
      pl0c05: makeSimpleRegistration("pl0c05", (a, ctx) => configureIcbmTankFamily(a, ctx)),
      pl0c06: makeSimpleRegistration("pl0c06", (a, ctx) => configureTankFamily(a, "pl0c06", ctx)),
      // SAPPHIRE KNIGHT / RUBY KNIGHT family (ctor 0x800bb390) — knight-cluster port
      // (bespoke action 0/2 tables pending; action 1 shared melee + shared-engine X).
      pl0208: makeSimpleRegistration("pl0208", (a, ctx) => configureSapphireKnightFamily(a, "pl0208", ctx)),
      pl020e: makeSimpleRegistration("pl020e", (a, ctx) => configureSapphireKnightFamily(a, "pl020e", ctx)),
      // BATTLE GIRL / KEI family (ctor 0x800c04c0) — registered in the girl-cluster
      // block above (families/girl-cluster.ts): bespoke X @0x80433b18 + full 0/1.
      // AXE KNIGHT / HATCHET KNIGHT family (ctor 0x800d6d10) — knight-cluster port.
      pl0204: makeSimpleRegistration("pl0204", (a, ctx) => configureAxeKnightFamily(a, "pl0204", ctx)),
      pl020d: makeSimpleRegistration("pl020d", (a, ctx) => configureAxeKnightFamily(a, "pl020d", ctx)),
      // DEATH BORG GAMMA (pl0206, ctor 0x8019c02c) — shared melee + shared engine fallback.
      pl0206: {
        configure: (a, ctx) => {
          const knight = createGenericKnightRootAction(ctx);
          const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
          a.borgNumber = 0x206; a.rootAction = (aa) => { if (aa.actionIndex === 1) knight(aa); else shared(aa); }; a.defaultGroup = 0; a.streamSlot = 0;
        },
        cueTable: cueTableForBorg("pl0206")!,
      },
      // ALIEN INSECT (pl0207, ctor 0x800ba144) — shared melee + shared engine fallback.
      pl0207: {
        configure: (a, ctx) => {
          const knight = createGenericKnightRootAction(ctx);
          const shared = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) });
          a.borgNumber = 0x207; a.rootAction = (aa) => { if (aa.actionIndex === 1) knight(aa); else shared(aa); }; a.defaultGroup = 0; a.streamSlot = 0;
        },
        cueTable: cueTableForBorg("pl0207")!,
      },
      // IMPERIAL KNIGHT (pl0209, ctor 0x801b7c74) — knight-cluster port.
      pl0209: makeSimpleRegistration("pl0209", (a, ctx) => configureImperialKnightFamily(a, "pl0209", ctx)),
      // DARK KNIGHT (pl0205, ctor 0x801567f0) + CHAINSAW KNIGHT (pl0201, ctor 0x800c8560)
      // — bespoke knight-cluster ports (DARK fully ported; CHAINSAW shared fallback).
      pl0205: makeSimpleRegistration("pl0205", (a, ctx) => configureDarkKnightFamily(a, "pl0205", ctx)),
      pl0201: makeSimpleRegistration("pl0201", (a, ctx) => configureChainsawKnightFamily(a, "pl0201", ctx)),
// DRILL ROBOT family (ctor 0x800e67d4) — bespoke 5-phase X-special
// (FUN_800d81f8 → PTR_FUN_803109b4 phase machine); see families/drill-robot.ts.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
pl0401: withRobotDash(makeDrillRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0401),
// HAMMER ROBOT family (ctor 0x800e5a0c) — bespoke 5-phase X-special
// (zz_00e5a0c_ → PTR_FUN_803188d4 phase machine); see families/hammer-robot.ts.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
pl0403: withRobotDash(makeHammerRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0403),
// THUNDER ROBOT family (ctor 0x800e0174) — bespoke 5-phase X-special
// (FUN_800e0174 → PTR_FUN_80316b1c phase machine); see families/thunder-robot.ts.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
pl0404: withRobotDash(makeThunderRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0404),
      // MAGNET ROBOT (+) / MAGNET ROBOT (-) family (ctor 0x800da9fc) — bespoke X-special
      // (FUN_800dafb4 → PTR_FUN_80311ca4 3-phase magnet-suck-in deploy); see families/magnet-robot.ts.
      // Phase-1 contact deploys a borg-switched child: pl0405→variant 0, pl0409→variant 1.
      pl0405: withRobotDash(makeMagnetRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0405),
      pl0409: withRobotDash(makeMagnetRobotFamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl0409),
// SPIKE KNIGHT / HAMMER KNIGHT family (ctor 0x800e5288) — bespoke shot (action-2) + jump
// (action-4) X-specials. Shared knight melee wired at action-1. See families/knight-family.ts.
pl0203: {
  configure: (actor, ctx) => {
    configureKnightFamily(actor, "pl0203", ctx);
    const knight = createGenericKnightRootAction(ctx);
    const origRoot = actor.rootAction!;
    actor.rootAction = (a) => { if (a.actionIndex === 1) knight(a); else origRoot(a); };
  },
  cueTable: cueTableForBorg("pl0203")!,
},
pl020c: {
  configure: (actor, ctx) => {
    configureKnightFamily(actor, "pl020c", ctx);
    const knight = createGenericKnightRootAction(ctx);
    const origRoot = actor.rootAction!;
    actor.rootAction = (a) => { if (a.actionIndex === 1) knight(a); else origRoot(a); };
  },
  cueTable: cueTableForBorg("pl020c")!,
},
      // BEAM WING BLUE / BEAM WING RED family (ctor 0x800f9a28) — full port (5 tables, 21 fns).
      // See families/beam-wing.ts. Root engine at action 0, melee at action 1/3, X-special at action 2.
      pl0a03: makeBeamWingFamilyRegistration("pl0a03"),
      pl0a06: makeBeamWingFamilyRegistration("pl0a06"),
      // COSMIC DRAGON / SPACE DRAGON family (ctor 0x80108954) — both members not yet in registry.
      // ELEMENTAL KNIGHT / GHOST KNIGHT family (ctor 0x80123438) — both members not yet in registry.
      // KILLER GIRL / SHADOW GIRL family (ctor 0x80134078) — registered in the
      // girl-cluster block above (families/girl-cluster.ts): pl0304 shared cfg X
      // @0x80336d94, pl0308 bespoke 5-phase X @0x80336da4, full actions 0/1.
      // PHOENIX DRAGON / WING DRAGON family (ctor 0x80142674) — both members not yet in registry.
      // TELEPORT NINJA / SWITCHING NINJA family (ctor 0x801456d4) — both members not yet in registry.
      // DEMON WING / DEATH WING family (ctor 0x8014bd68) — both members not yet in registry.
      // GUARD WITCH / SHIELD WITCH family (ctor 0x80151790)
      pl0903: makeSimpleRegistration("pl0903", (a, ctx) => configureGuardWitchFamily(a, "pl0903", ctx)),
      pl090a: makeSimpleRegistration("pl090a", (a, ctx) => configureGuardWitchFamily(a, "pl090a", ctx)),
      // PATRA WITCH / ISIS WITCH family (ctor 0x8015d674)
      pl0902: makeSimpleRegistration("pl0902", (a, ctx) => configurePatraWitchFamily(a, "pl0902", ctx)),
      pl0909: makeSimpleRegistration("pl0909", (a, ctx) => configurePatraWitchFamily(a, "pl0909", ctx)),
      // BUG WITCH (pl0901, ctor 0x8014d200) — shared witch action-0 machine.
      pl0901: makeSimpleRegistration("pl0901", (a, ctx) => configureBugWitchFamily(a, "pl0901", ctx)),
      // SAMURAI SHOGUN / CHRONO SAMURAI family (ctor 0x80174d88) — registered in the
      // samurai cluster block above (families/samurai.ts): bespoke action-1 tables
      // @0x80351908/14/24 + bespoke X @0x80351950 (borg-switched slot + payload).
      // SIRIUS / DEATH ARC family (ctor 0x801898b0)
      pl0e00: makeSimpleRegistration("pl0e00", (a, ctx) => configureSiriusFamily(a, "pl0e00", ctx)),
      pl0e01: makeSimpleRegistration("pl0e01", (a, ctx) => configureVehicleFamily(a, "pl0e01", ctx)),
      pl0e02: makeSimpleRegistration("pl0e02", (a, ctx) => configureVehicleFamily(a, "pl0e02", ctx)),
      pl0e03: makeSimpleRegistration("pl0e03", (a, ctx) => configureVehicleFamily(a, "pl0e03", ctx)),
      pl0e04: makeSimpleRegistration("pl0e04", (a, ctx) => configureFortressFamily(a, "pl0e04", ctx)),
      pl0e05: makeSimpleRegistration("pl0e05", (a, ctx) => configureSiriusFamily(a, "pl0e05", ctx)),
      // BLUE STRIKER (pl0d00, ctor 0x800f7580) + ORANGE FIGHTER (pl0d04, ctor
      // 0x800f7660) fighter-craft family — shared 4-action root dispatching 4 phase
      // tables (@0x8031d130/d140/d14c/d158); see families/fighter-craft.ts. Borg-gated
      // phases route d00 to action 1 (hardpoint spawn) and d04 to action 2 (dual-port).
      pl0d00: makeSimpleRegistration("pl0d00", (a, ctx) => configureFighterFamily(a, "pl0d00", ctx)),
      pl0d04: makeSimpleRegistration("pl0d04", (a, ctx) => configureFighterFamily(a, "pl0d04", ctx)),
      // CARRIER HELICOPTER (pl0d02, ctor 0x80135ee8) + FLYING SAUCER (pl0d03, ctor 0x80188ff4)
      // — unregistered-cluster vehicle ports.
      pl0d02: makeSimpleRegistration("pl0d02", (a, ctx) => configureCarrierHelicopterFamily(a, ctx)),
      pl0d03: makeSimpleRegistration("pl0d03", (a, ctx) => configureFlyingSaucerFamily(a, ctx)),
      // ACCELERATION NINJA (pl0004, ctor 0x80162128) — bespoke 3-action melee/dash
      // (tables @0x8034c750/c770/c7a8); see families/acceleration-ninja.ts.
      pl0004: makeSimpleRegistration("pl0004", (a, ctx) => configureAccelerationNinjaFamily(a, ctx)),
      // VICTORY JET (pl0620, ctor 0x8015bd74) — bespoke action-3 spawn machine
      // (table @0x80346284); see families/victory-jet.ts.
      pl0620: makeSimpleRegistration("pl0620", (a, ctx) => configureVictoryJetFamily(a, ctx)),
      // DEATH BORG LAMBDA / DEATH BORG LAMBDA II family (ctor 0x8019e414) — valkrie-
      // cluster machines (families/valkrie.ts): action 0 = table-A B volley, action 1 =
      // table-B melee / table-C air lunge. NO action 2 in ROM (tables A-C only) — the
      // wave-B "cue table only" registration is composed with the ported rootAction.
      pl0b05: makeSimpleRegistration("pl0b05", (a, ctx) => configureValkrieFamily(a, "pl0b05", ctx)),
      pl0b07: makeSimpleRegistration("pl0b07", (a, ctx) => configureValkrieFamily(a, "pl0b07", ctx)),
      // DEATH BORG THETA / DEATH BORG IOTA family (ctor 0x801a10e8)
      pl0906: makeSimpleRegistration("pl0906", (a, ctx) => configureNurseFamily(a, "pl0906", ctx)),
      pl090b: makeSimpleRegistration("pl090b", (a, ctx) => configureNurseFamily(a, "pl090b", ctx)),
      // BASTET WITCH / SEKHMET WITCH family (ctor 0x801b3c6c)
      pl0907: makeSimpleRegistration("pl0907", (a, ctx) => configureBastetWitchFamily(a, "pl0907", ctx)),
      pl090c: makeSimpleRegistration("pl090c", (a, ctx) => configureBastetWitchFamily(a, "pl090c", ctx)),
      // ---- Wave-B: batch-register 6 three-borg families (2026-07-06) ----
      // Each family's ctor was searched in the corpus (actionStreamTables.json) to find
      // the X-special engine. Shared-vs-bespoke determination: leaf == engine in family
      // code block (not a cross-family zz_0177dd8_/zz_0179d20_/etc. address) → BESPOKE.
      // BESPOKE families get a families/<name>.ts port; the rest get cue table +
      // shared-engine fallback (cue table + createSharedEngineRootAction).

      // Wave-B catch-all borgs (no dedicated family file yet)
      pl0100: makeSimpleRegistration("pl0100", (a, ctx) => configureRevolverGunmanFamily(a, "pl0100", ctx)),
      pl0108: makeSimpleRegistration("pl0108", (a, ctx) => configureRevolverGunmanFamily(a, "pl0108", ctx)),
      pl0002: makeSimpleRegistration("pl0002", (a, ctx) => configureArrowNinjaFamily(a, "pl0002", ctx)),
      pl000b: makeSimpleRegistration("pl000b", (a, ctx) => configureArrowNinjaFamily(a, "pl000b", ctx)),
      pl0005: makeSimpleRegistration("pl0005", (a, ctx) => configureTeleportNinjaFamily(a, "pl0005", ctx)),
      pl0009: makeSimpleRegistration("pl0009", (a, ctx) => configureTeleportNinjaFamily(a, "pl0009", ctx)),
      pl0504: makeSimpleRegistration("pl0504", (a, ctx) => configureCosmicDragonFamily(a, "pl0504", ctx)),
      pl0510: makeSimpleRegistration("pl0510", (a, ctx) => configureCosmicDragonFamily(a, "pl0510", ctx)),
      pl0502: makeSimpleRegistration("pl0502", (a, ctx) => configurePhoenixDragonFamily(a, "pl0502", ctx)),
      pl050e: makeSimpleRegistration("pl050e", (a, ctx) => configurePhoenixDragonFamily(a, "pl050e", ctx)),
      pl0505: makeSimpleRegistration("pl0505", (a, ctx) => configureWaveBFamily(a, "pl0505", ctx)),
      pl0511: makeSimpleRegistration("pl0511", (a, ctx) => configureWaveBFamily(a, "pl0511", ctx)),
      pl0202: makeSimpleRegistration("pl0202", (a, ctx) => configureElementalKnightFamily(a, "pl0202", ctx)),
      pl020b: makeSimpleRegistration("pl020b", (a, ctx) => configureElementalKnightFamily(a, "pl020b", ctx)),
      pl0a02: makeSimpleRegistration("pl0a02", (a, ctx) => configureDemonWingFamily(a, "pl0a02", ctx)),
      // WING SOLDIER (pl0a00, ctor 0x80091824) — bespoke hover-volley + variant dives
      // (tables @0x802db468/db48c, X @0x8033ecb8); see families/wing-soldier.ts.
      pl0a00: makeSimpleRegistration("pl0a00", (a, ctx) => configureWingSoldierFamily(a, ctx)),
      pl0a07: makeSimpleRegistration("pl0a07", (a, ctx) => configureDemonWingFamily(a, "pl0a07", ctx)),
      pl0a04: makeSimpleRegistration("pl0a04", (a, ctx) => configureAnubisWingFamily(a, "pl0a04", ctx)),
      pl0a08: makeSimpleRegistration("pl0a08", (a, ctx) => configureAnubisWingFamily(a, "pl0a08", ctx)),
      pl0a09: makeSimpleRegistration("pl0a09", (a, ctx) => configureAnubisWingFamily(a, "pl0a09", ctx)),
      pl0105: makeSimpleRegistration("pl0105", (a, ctx) => configureDeathBorgBetaIIFamily(a, "pl0105", ctx)),
      pl010a: makeSimpleRegistration("pl010a", (a, ctx) => configureDeathBorgBetaIIFamily(a, "pl010a", ctx)),
      // GATLING GUNNER (pl0102, ctor 0x80134d68), BEAM GUNNER (pl0104, ctor 0x80102824),
      // POWERED GUNMAN (pl0101, ctor 0x80165f64) — bespoke ranged-burst ports in
      // families/gunman-cluster.ts.
      pl0102: makeSimpleRegistration("pl0102", (a, ctx) => configureGatlingGunnerFamily(a, ctx)),
      pl0104: makeSimpleRegistration("pl0104", (a, ctx) => configureBeamGunnerFamily(a, ctx)),
      pl0101: makeSimpleRegistration("pl0101", (a, ctx) => configurePoweredGunmanFamily(a, ctx)),
      // DEATH BORG BETA (pl0109) — unregistered-cluster port.
      pl0109: makeSimpleRegistration("pl0109", (a, ctx) => configureDeathBorgBetaFamily(a, ctx)),
      pl0a05: makeSimpleRegistration("pl0a05", (a, ctx) => configureDeathBorgSigmaFamily(a, "pl0a05", ctx)),
      pl0a0a: makeSimpleRegistration("pl0a0a", (a, ctx) => configureDeathBorgSigmaFamily(a, "pl0a0a", ctx)),
      pl0d06: makeSimpleRegistration("pl0d06", (a, ctx) => configureWaveBFamily(a, "pl0d06", ctx)),
      pl0d07: makeSimpleRegistration("pl0d07", (a, ctx) => configureWaveBFamily(a, "pl0d07", ctx)),
      // JELLY DIVER family (ctor 0x80114838) — BESPOKE X-special (FUN_80116808 →
      // PTR_FUN_80434550 phase machine, chunk_0031.c). 2-phase ammo-gated borg-switched
      // child deploy (zz_01213bc_); see families/jelly-diver.ts.
      pl0805: makeSimpleRegistration("pl0805", (a, ctx) => configureJellyDiverFamily(a, "pl0805", ctx)),
      pl080d: makeSimpleRegistration("pl080d", (a, ctx) => configureJellyDiverFamily(a, "pl080d", ctx)),
      pl080e: makeSimpleRegistration("pl080e", (a, ctx) => configureJellyDiverFamily(a, "pl080e", ctx)),
      // COPY MAN family (ctor 0x8015613c) — BESPOKE X-special (FUN_80156460 →
      // PTR_FUN_8034267c phase machine, chunk_0040.c). 3-phase borg-switched child deploy
      // (zz_01639c0_ / zz_00c4704_); see families/copy-man.ts.
      pl0806: makeSimpleRegistration("pl0806", (a, ctx) => configureCopyManFamily(a, "pl0806", ctx)),
      pl0809: makeSimpleRegistration("pl0809", (a, ctx) => configureCopyManFamily(a, "pl0809", ctx)),
      pl080f: makeSimpleRegistration("pl080f", (a, ctx) => configureCopyManFamily(a, "pl080f", ctx)),
      // ANGEL NURSE family (ctor 0x80079410)
      pl0900: makeSimpleRegistration("pl0900", (a, ctx) => configureNurseFamily(a, "pl0900", ctx)),
      pl0908: makeSimpleRegistration("pl0908", (a, ctx) => configureNurseFamily(a, "pl0908", ctx)),
      pl090d: makeSimpleRegistration("pl090d", (a, ctx) => configureNurseFamily(a, "pl090d", ctx)),
// DEATH BORG OMEGA II/III/IV family (ctor 0x801d4590) — bespoke 5-phase X-special
// (FUN_800f3cb4 → PTR_FUN_8031b918 phase machine); see families/omega2-robot.ts.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
pl040b: withRobotDash(makeOmega2FamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl040b),
pl040c: withRobotDash(makeOmega2FamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl040c),
pl040d: withRobotDash(makeOmega2FamilyRegistration(), ROBOT_ACTION0_CONFIGS.pl040d),
      // DEATH BORG NU family (ctor 0x801b3598) — bespoke 4-phase ammo-gated spawn
      // machine (table @0x80380ee8; zz_01b3768_/zz_01b3798_/zz_01b3824_/zz_01b3990_).
      // DEATH EYE (ctor 0x801e43f8) shares the identical machine (table @0x80391cd8;
      // FUN_801e460c/463c/46c8/47f8) — see families/death-borg-nu.ts. pl0f01 loops
      // (shot 0x4a), pl0f02/pl0f03 single-shot (effect 0x3d/0xb), pl0f06 loops
      // (shot 0x7a). DEATH BORG MU (pl0f00, ctor 0x801b289c, table @0x80380a80) and
      // ROACH (pl0f05, ctor 0x801e7d78, table @0x803929a8) have their own single-shot
      // machines in the same module. pl0f04 (Death Borg Chi) stays on configureNuFamily
      // (null rootAction → generic layer).
      pl0f01: makeSimpleRegistration("pl0f01", (a, ctx) => configureDeathBorgNuFamily(a, "pl0f01", ctx)),
      pl0f02: makeSimpleRegistration("pl0f02", (a, ctx) => configureDeathBorgNuFamily(a, "pl0f02", ctx)),
      pl0f03: makeSimpleRegistration("pl0f03", (a, ctx) => configureDeathBorgNuFamily(a, "pl0f03", ctx)),
      pl0f00: makeSimpleRegistration("pl0f00", (a, ctx) => configureDeathBorgMuFamily(a, ctx)),
      pl0f04: makeSimpleRegistration("pl0f04", (a, ctx) => configureDeathBorgChiFamily(a, ctx)),
      pl0f05: makeSimpleRegistration("pl0f05", (a, ctx) => configureRoachFamily(a, ctx)),
      pl0f06: makeSimpleRegistration("pl0f06", (a, ctx) => configureDeathEyeFamily(a, ctx)),
      // ---- Valkrie cluster (2026-07-06): 6 valkrie families on the 4 shared phase-table
      // machines ported in families/valkrie.ts (tables @0x8033ed68/ed78/ed88/0x804346b8;
      // engines zz_014a200_/zz_014a8c0_/zz_014ad94_/zz_014b22c_, chunk_0038.c). Action 0 =
      // B ranged volley, action 1 = B melee (v4 = air lunge), action 2 = X special. The
      // per-borg volley config blocks (count/timer/shot record) are DOL-read — see the
      // valkrie.ts header. DEATH BORG LAMBDA (pl0b05/pl0b07) shares tables A-C above.
      pl0b00: makeSimpleRegistration("pl0b00", (a, ctx) => configureValkrieFamily(a, "pl0b00", ctx)),
      pl0b01: makeSimpleRegistration("pl0b01", (a, ctx) => configureValkrieFamily(a, "pl0b01", ctx)),
      pl0b02: makeSimpleRegistration("pl0b02", (a, ctx) => configureValkrieFamily(a, "pl0b02", ctx)),
      pl0b03: makeSimpleRegistration("pl0b03", (a, ctx) => configureValkrieFamily(a, "pl0b03", ctx)),
      pl0b04: makeSimpleRegistration("pl0b04", (a, ctx) => configureValkrieFamily(a, "pl0b04", ctx)),
      pl0b06: makeSimpleRegistration("pl0b06", (a, ctx) => configureValkrieFamily(a, "pl0b06", ctx)),
    };

    // ---- Wave-C: bespoke B-melee engine wiring (2026-07-06, batch 2 — 48 borgs) ----
    // 4 bespoke B-melee dispatchers ported in families/melee-*.ts, each covering 12
    // borgs' action 1 (ground B-melee):
    //   zz_010c220_ (standing) + zz_010b7ac_ (lunge) — 12 girl/delta borgs (2 variants)
    //   zz_00f2374_ (3-phase)                         — 12 robot/omega borgs
    //   zz_0149178_ (config-driven lunge)            — 12 samurai/zeta borgs
    // Each borg's existing registration (X-special/dash/charge wiring) is preserved; the
    // bespoke melee is INJECTED at actionIndex 1 via withBespokeMelee. Borgs not yet in
    // the registry get a cue-table-only base registration first.

    // Girl group: the wave-C standing/lunge injection is SUPERSEDED by the girl
    // cluster registrations above (families/girl-cluster.ts wires the full
    // M-1..M-5 variant map with the real per-family seed slots).

    // Robot group: zz_00f2374_ (3-phase melee).
    for (const id of [
      "pl0400", "pl0401", "pl0402", "pl0403", "pl0404", "pl0405",
      "pl0406", "pl0407", "pl0408", "pl0409", "pl040a", "pl040b",
    ] as const) {
      const base = FAMILY_REGISTRY_CACHE[id] ?? makeSimpleRegistration(id, () => {});
      FAMILY_REGISTRY_CACHE[id] = withBespokeMelee(
        base,
        (ctx) => createMeleeRobot(ctx, { rangeRows868: ROBOT_MELEE_RANGE_ROWS[id] }),
        0,
      );
    }

    // Samurai group: zz_0149178_ (config-driven lunge melee). Only pl0706 remains on
    // the wave-C injection — the other 12 borgs now route action-1 variants through
    // families/samurai.ts (v3/v4 → createMeleeSamurai with the DOL-read
    // SAMURAI_LUNGE_ROM_CONFIG; v0/v1 → table S-B; v2 → the family machine).
    const samuraiMeleeFactory = (ctx: GRedFamilyCtx) =>
      createMeleeSamurai(ctx, SAMURAI_MELEE_DEFAULT_CONFIG);
    for (const id of ["pl0706"] as const) {
      const base = FAMILY_REGISTRY_CACHE[id] ?? makeSimpleRegistration(id, () => {});
      FAMILY_REGISTRY_CACHE[id] = withBespokeMelee(base, samuraiMeleeFactory);
    }
  }
  return FAMILY_REGISTRY_CACHE;
}

// ---- Fleet-wide DERIVED cue tables (familyCueTablesFull.json, 2026-07-06) ----
// 119/119 family ctors' 48×2 cue→state tables dumped from boot.dol at each ctor's
// +0x4f0 binding, byte-validated against the two hand-verified dumps (family 0 +
// G RED, nn-family-decode-2026-07-06.md §A11). Rows 44 AND 45 → state 61 in ALL 119
// families (the universal root-action trampoline). Three ctors carry per-borg
// memberOverrides (variant sub-families binding a different table).

interface CueTableFamilyEntry {
  cueTable: string;
  members: string[];
  rows: number[][] | null;
  memberOverrides?: Record<string, { cueTable: string; rows: number[][] | null }>;
}
const CUE_TABLE_FAMILIES = (familyCueTablesFullData as unknown as {
  families: Record<string, CueTableFamilyEntry>;
}).families;

/** borgId → family ctor address (actionStreamTables.json). */
const BORG_CTOR: Record<string, string | undefined> = (() => {
  const data = actionStreamTablesData as unknown as { borgs: Record<string, { constructorAddress?: string }> };
  const out: Record<string, string | undefined> = {};
  for (const [borgId, b] of Object.entries(data.borgs || {})) out[borgId] = b.constructorAddress;
  return out;
})();

/** The borg's REAL ROM cue table (per-borg override → family rows), as the Int8Array
 *  shape dispatch.ts consumes. Null when the borg has no extracted family entry. */
export function cueTableForBorg(borgId: string): Int8Array | null {
  const ctor = BORG_CTOR[borgId];
  if (!ctor) return null;
  const fam = CUE_TABLE_FAMILIES[ctor];
  if (!fam) return null;
  const rows = fam.memberOverrides?.[borgId]?.rows ?? fam.rows;
  if (!rows) return null;
  const t = new Int8Array(96);
  for (let i = 0; i < 48 && i < rows.length; i++) {
    t[i * 2] = rows[i]![0]!;
    t[i * 2 + 1] = rows[i]![1]!;
  }
  return t;
}

function makeGRedFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x629 ? "pl0629" : actor.borgNumber === 0x62a ? "pl062a" : "pl0615";
      configureGRedFamily(actor, id as "pl0615" | "pl0629" | "pl062a", ctx);
    },
    cueTable: cueTableForBorg("pl0615")!,
  };
}

/**
 * SATELLITE family (pl0d01 / pl0d05) — the only registration that carries a `frameUpdate`,
 * because it is the only family whose `+0x4bc` per-frame virtual (FUN_80188a64) is ported.
 *
 * WHY THIS EXISTS: satelliteFamilyUpdate was a complete port with no caller, so the deploy
 * latches the X and pod machines SET (+0x145 in satXPhase1, +0x146/+0x147/+0x148 in podPhase1)
 * were never cleared — the ROM clears them from this virtual when the matching ammo slot
 * regenerates, and there was nothing in the port running per-frame to do it. Re-deploy gating
 * in this family is ammo-regen-driven, not timer-driven, so the clear has no other home.
 *
 * AMMO PREDICATES: the ROM reads the cells at actor+0x774+slot*8 (cur) / +0x78e+slot*8 (max);
 * BorgRuntime.weaponCells is the port's mirror of exactly those. "Refilled" is `cur >= max`,
 * with the ROM's own infinite-cell convention on top — `max <= 0` means infinite
 * (chunk_0002.c:7158-7165, types.ts WeaponCell.max), and an infinite cell is never waiting on
 * a refill. Satellite binding has not been migrated: its browser cell2 is still
 * inert. FUN_800562b8 actually maps two source segments to ROM cells0/2; the
 * Diver-specific binding now uses that fact. Satellite migration is separate work,
 * not evidence of a missing third segment.
 */
function makeSatelliteRegistration(borgId: "pl0d01" | "pl0d05"): FamilyRegistration {
  return {
    configure: (actor, ctx) => configureSatelliteFamily(actor, borgId, ctx),
    cueTable: cueTableForBorg(borgId)!,
    frameUpdate: (actor, runtime) => {
      satelliteFamilyUpdate(actor, weaponCellRefilled(runtime, 0), weaponCellRefilled(runtime, 2));
    },
  };
}

/** ROM weapon-cell "refilled" predicate: cur >= max, with `max <= 0` (infinite, never waiting
 *  on a refill) reading as refilled. Absent cells (a fake/constructor that never ran through
 *  combat.ts's lazy ensureWeaponCells) read as infinite too — the same self-heal default the
 *  rest of the port uses. */
function weaponCellRefilled(runtime: BorgRuntime, slot: number): boolean {
  const cell = runtime.weaponCells?.[slot];
  if (!cell || cell.max <= 0) return true;
  return cell.cur >= cell.max;
}

/** Small helper: registration from a configure closure + the borg's data-driven cue table. */
function makeSimpleRegistration(
  borgId: string,
  configure: (actor: RomActor, ctx: RomHostContext) => void,
): FamilyRegistration {
  return { configure, cueTable: cueTableForBorg(borgId)! };
}

/** Compose a 5-slot actionTable rootAction from per-slot handlers (null = generic fallback). */
function composeActionTable(
  table: Array<((actor: RomActor) => void) | null>,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const fn = table[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Wrap an existing registration so the bespoke B-melee engine (action 1) is injected
 *  on top of whatever rootAction the base configure closure sets. The base configure
 *  runs first (stamping borgNumber + wiring X-special/dash/charge slots); then this
 *  wraps rootAction to route actionIndex 1 to the bespoke melee, preserving the base
 *  handler for all other action indices. Used by the batch-2 B-melee port to give 48
 *  borgs their real ROM B-melee without touching each family's X-special wiring. */
function withBespokeMelee(
  base: FamilyRegistration,
  melee: (ctx: RomHostContext) => (actor: RomActor) => void,
  variant?: number,
): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      base.configure(actor, ctx);
      const meleeHandler = melee(ctx);
      const existing = actor.rootAction;
      if (!existing) {
        actor.rootAction = (a) => {
          if (a.actionIndex === 1 && (variant === undefined || a.variantIndex === variant)) { meleeHandler(a); return; }
        };
      } else {
        actor.rootAction = (a) => {
          if (a.actionIndex === 1 && (variant === undefined || a.variantIndex === variant)) { meleeHandler(a); return; }
          existing(a);
        };
      }
    },
    cueTable: base.cueTable,
  };
}

/** Wrap a family registration so action 0 routes to the shared robot-dash engine
 *  (PTR_FUN_8031b8a0 → zz_00f1e30_ ported in shared-robot-dash.ts). Preserves the
 *  base rootAction for actions 1..4 (X-special, B-melee, charge, etc.). */
function withRobotDash(
  base: FamilyRegistration,
  config: RobotDashConfig,
): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      base.configure(actor, ctx);
      const dashHandler = createRobotDashHandler(config, ctx);
      const existing = actor.rootAction;
      if (!existing) {
        actor.rootAction = composeActionTable([dashHandler, null, null, null, null]);
      } else {
        actor.rootAction = (a) => {
          if (a.actionIndex === 0) { dashHandler(a); return; }
          existing(a);
        };
      }
    },
    cueTable: base.cueTable,
  };
}

/** Titan/Panther composite: morph engine at actionTable[2] + aimed-shot engine at [3]
 *  (the ROM's PTR_FUN_8032f41c/PTR_FUN_8036546c wiring, split across two shared modules). */
function makeMorphAimedComposite(
  borgId: string,
  borgNumber: number,
  family: "titan" | "panther",
  morphCfg: Parameters<typeof createSharedMorphXSpecial>[0],
  aimedCfg: Parameters<typeof createSharedAimedShotX>[0],
  morphLive: boolean,
): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      actor.borgNumber = borgNumber;
      actor.rootAction = composeActionTable([
        createTitanPantherGunAction0(ctx),
        createTitanPantherAction1(family, ctx),
        morphLive ? createSharedMorphXSpecial(morphCfg, ctx, ctx.onMorph ? { onMorph: ctx.onMorph } : {}) : null,
        createSharedAimedShotX(aimedCfg, ctx),
        null,
      ]);
      actor.defaultGroup = 0;
      actor.streamSlot = 0;
    },
    cueTable: cueTableForBorg(borgId)!,
  };
}

// GIRL cluster (families/girl-cluster.ts) — 14 borgs / 8 families (BATTLE GIRL
// 0x800c04c0, WIRE GIRL 0x80106e3c, BARRIER GIRL 0x80107e7c, DEATH BORG DELTA II
// 0x8019c380, KILLER GIRL 0x80134078, CYBER GIRL SUPER 0x8012f204, SPINNER GIRL
// 0x801ba020, DEATH BORG DELTA 0x801d429c). Composes the already-ported series-3 X
// (shared-series3-x.ts, per-borg slot layout preserved) and cyber-girl X
// (cyber-girl.ts) with the newly ported shared ranged/melee/X machines.
function girlClusterRegistrations(): Record<string, FamilyRegistration> {
  const ids: GirlClusterBorgId[] = [
    "pl0300", "pl0301", "pl0302", "pl0303", "pl0304", "pl0305", "pl0306",
    "pl0307", "pl0308", "pl0309", "pl030a", "pl030b", "pl030c", "pl030d",
  ];
  const out: Record<string, FamilyRegistration> = {};
  for (const id of ids) {
    out[id] = makeSimpleRegistration(id, (a, ctx) => configureGirlClusterFamily(a, id, ctx));
  }
  return out;
}

// SAMURAI cluster (families/samurai.ts) — 13 borgs / 6 families (NORMAL SAMURAI
// 0x800c7c80, DEMON SAMURAI 0x801223c0, VAMPIRE KNIGHT 0x80143b7c, SONIC SAMURAI
// 0x80164324, SAMURAI SHOGUN 0x80174d88, DEATH BORG ZETA 0x8019c510). Supersedes the
// earlier lance-flight-only registrations (pl0700/09, pl0702/0a, pl0705/0b), the
// wave-A demon shared-engine registration (pl0701/0708/070c/070d), and the wave-B
// shogun dashAttack fallback (pl0704/0707): the X wiring those provided is preserved
// inside configureSamuraiClusterFamily (same shared-flight configs / real bespoke
// machines), and actions 0/1 gain their ROM machines.
function samuraiClusterRegistrations(): Record<string, FamilyRegistration> {
  const ids: SamuraiClusterBorgId[] = [
    "pl0700", "pl0701", "pl0702", "pl0703", "pl0704", "pl0705",
    "pl0707", "pl0708", "pl0709", "pl070a", "pl070b", "pl070c", "pl070d",
  ];
  const out: Record<string, FamilyRegistration> = {};
  for (const id of ids) {
    out[id] = makeSimpleRegistration(id, (a, ctx) => configureSamuraiClusterFamily(a, id, ctx));
  }
  return out;
}

function makeDeathBorgFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => configureDeathBorgFamily(actor, "pl000c", ctx),
    cueTable: cueTableForBorg("pl000c")!,
  };
}

function makeStarHeroFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x80c ? "pl080c" : "pl0804";
      configureStarHeroFamily(actor, id as "pl0804" | "pl080c", ctx);
    },
    cueTable: cueTableForBorg("pl0804")!,
  };
}

// VICTORY KING family (ctor 0x8015a494) — bespoke action-0 dash + action-3 B-charge
// flurry ported in families/victory-king.ts (tables @0x804346f8 / @0x803448b0). The
// X-special (action 2) routes through the shared engine zz_017a374_, wired inside
// configureVictoryKingFamily with the per-borg seed slot.

function makeSwordKnightFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x20a ? "pl020a" :
        actor.borgNumber === 0x20f ? "pl020f" : "pl0200";
      configureSwordKnightFamily(actor, id as "pl0200" | "pl020a" | "pl020f", ctx);
    },
    cueTable: cueTableForBorg("pl0200")!,
  };
}

// MACHINE RED family (ctor 0x800c91bc) — cue table @0x8030a248. The X-special ROUTES
// THROUGH THE SHARED ENGINE zz_0179d20_ (phaseTable 0x804347a8, chunk_0044.c:4086):
// action-2 handler FUN_800cb9d4 (chunk_0021.c:1545) tail-calls zz_0179d20_ — the same
// cross-family group-4 X-special engine reused by 12+ borgs across the roster (per the
// actionStreamTables.json engines header). All 5 action-2 variants route to leaf
// 0x800cba10 with config @0x8030a66c (seedSlot 0), so every member uses the same config.
// The dedicated module ports that exact two-phase engine and its family callback;
// actions 0/1 retain their distinct leaves for conservative fallback.
function makeMachineRedFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x608 ? "pl0608" :
        actor.borgNumber === 0x616 ? "pl0616" :
        actor.borgNumber === 0x61c ? "pl061c" : "pl0600";
      configureMachineRedFamily(actor, id as MachineRedBorgId, ctx);
    },
    cueTable: cueTableForBorg("pl0600")!,
  };
}

// MACHINE BLUE family (ctor 0x800ce730) — cue table @0x8030c9c8. The X-special ROUTES
// THROUGH THE SHARED ENGINE zz_0179fcc_ (phaseTable 0x80352b64, chunk_0044.c:4185):
// action-2 handler FUN_800cf990 (chunk_0021.c:4071) dispatches the variant table
// PTR_FUN_8030cef8 — all 5 variants route to leaf 0x800cf9cc, which halves steerYaw
// (+0x18da >>= 1) then tail-calls zz_0179fcc_. The shared engine consumes the config
// block @0x8030cf0c (seedSlot 0 ground / 1 air, group 4). pl0601/pl0609/pl0617/pl061d
// all bind the same config (actionStreamTables.json confirms identical leaf + engine
// + phaseTable across the 4 members). Actions 3/4 are constructor-specific hardpoint
// deploy handlers, so the dedicated module owns the root while delegating action 2
// only to the proven shared engine. The borgNumber stamp below is overwritten
// by RomDriverBridge.attach (line `actor.borgNumber = borgIdToNumber(runtime.borgId)`)
// so the per-member number (0x601/0x609/0x617/0x61d) is set correctly post-configure.
function makeMachineBlueFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x609 ? "pl0609" :
        actor.borgNumber === 0x617 ? "pl0617" :
        actor.borgNumber === 0x61d ? "pl061d" : "pl0601";
      configureMachineBlueFamily(actor, id as MachineBlueBorgId, ctx);
    },
    cueTable: cueTableForBorg("pl0601")!,
  };
}

function makeCyberMachineFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x60a ? "pl060a" :
        actor.borgNumber === 0x60c ? "pl060c" :
        actor.borgNumber === 0x60e ? "pl060e" : "pl0602";
      configureCyberMachineFamily(actor, id as "pl0602" | "pl060a" | "pl060c" | "pl060e", ctx);
    },
    cueTable: cueTableForBorg("pl0602")!,
  };
}

// FLAME DRAGON family (ctor 0x80075658) — cue table @0x802d5a58. The X-special is a
// BESPOKE 3-variant phase machine (ground/air/charged flame breath) ported in
// families/dragon.ts; engines 0x80075ef0/0x80076088/0x80076244 live in the family code
// block (not shared-engine ranges). All 6 members (pl0500/pl0509/pl050a/pl050c/
// pl0515/pl0516) share one module — the ctor block-copies the same +0x4b4 binding;
// only the borg-number switch inside zz_0076408_ (flame-child record select) differs.
function makeDragonFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x509 ? "pl0509" :
        actor.borgNumber === 0x50a ? "pl050a" :
        actor.borgNumber === 0x50c ? "pl050c" :
        actor.borgNumber === 0x515 ? "pl0515" :
        actor.borgNumber === 0x516 ? "pl0516" : "pl0500";
      configureDragonFamily(actor, id as "pl0500" | "pl0509" | "pl050a" | "pl050c" | "pl0515" | "pl0516", ctx);
    },
    cueTable: cueTableForBorg("pl0500")!,
  };
}

// CYBER DEATH DRAGON family (ctor 0x800b8188) — cue table @0x802fec20. The X-special
// is a BESPOKE 3-variant phase machine (ground/air/charged breath) ported in
// families/cyber-dragon.ts; engines 0x800b96c4/0x800b9888/0x800b9a74 live in the
// family code block (not shared-engine ranges). All 6 members (pl0503/pl0506/pl0507/
// pl050f/pl0512/pl0513) share one module — the ctor block-copies the same +0x4b4
// binding; only FUN_800b866c's borg-id switch (animation record select) differs.
// Sister family to FLAME DRAGON (identical phase structure; no per-frame flame-child
// spawner — the contact calls zz_0098dbc_ instead, a shared kind-6 attack resolver).
function makeCyberDragonFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x506 ? "pl0506" :
        actor.borgNumber === 0x507 ? "pl0507" :
        actor.borgNumber === 0x50f ? "pl050f" :
        actor.borgNumber === 0x512 ? "pl0512" :
        actor.borgNumber === 0x513 ? "pl0513" : "pl0503";
      configureCyberDragonFamily(actor, id as "pl0503" | "pl0506" | "pl0507" | "pl050f" | "pl0512" | "pl0513", ctx);
    },
    cueTable: cueTableForBorg("pl0503")!,
  };
}

// ALIEN WORM family (ctor 0x80118cb8) — cue table @0x8032b8d8. The X-special is a
// BESPOKE borg-switched spawn dispatcher (FUN_80118efc @ chunk_0032.c:662) ported in
// families/worm.ts. pl0501/pl050d spawn a worm-child via FUN_8011a108 (family code
// block); pl050b/pl0517 spawn a venom/poison cloud via the shared zz_01d4d00_ — the
// routing decision is bespoke even though the cloud spawner is shared. All 4 members
// share the cue table (ctor block-copy of the +0x4f0 binding).
function makeWormFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x50b ? "pl050b" :
        actor.borgNumber === 0x50d ? "pl050d" :
        actor.borgNumber === 0x517 ? "pl0517" : "pl0501";
      configureWormFamily(actor, id as "pl0501" | "pl050b" | "pl050d" | "pl0517", ctx);
    },
    cueTable: cueTableForBorg("pl0501")!,
  };
}

// BUILD ROBOT family (ctor 0x80112b44) — cue table @0x80328148. The X-special is a
// BESPOKE 3-phase dive-bomb deploy (FUN_801132f8 → PTR_FUN_80327f98) ported in
// families/robot.ts; engine 0x801132f8 lives in the family code block (not a shared-
// engine range). The phase-1 contact spawns a borg-switched child: pl0402/pl0408 via
// zz_01138c0_ (family child-deploy @0x801138c0), pl0407 via FUN_801b8b6c (MEGATON
// heavy deploy @0x801b8b6c, one-shot latched at +0x150). All 3 members share the cue
// table (ctor block-copy of the +0x4f0 binding) + group-4 seedSlot 0 (air 1).
function makeRobotFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x407 ? "pl0407" :
        actor.borgNumber === 0x408 ? "pl0408" : "pl0402";
      configureRobotFamily(actor, id as "pl0402" | "pl0407" | "pl0408", ctx);
    },
    cueTable: cueTableForBorg("pl0402")!,
  };
}

// MAGNET ROBOT family (ctor 0x800da9fc) — cue table @0x803168f8. Both members
// (pl0405/pl0409) share the bespoke X-special 3-phase magnet-suck-in deploy
// (FUN_800dafb4 → PTR_FUN_80311ca4 phase machine); see families/magnet-robot.ts.
// The X handler is at action 2; action 0 gets the shared robot-dash via withRobotDash.
function makeMagnetRobotFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x409 ? "pl0409" as const : "pl0405" as const;
      configureMagnetRobotFamily(actor, id, ctx);
    },
    cueTable: cueTableForBorg("pl0405")!,
  };
}

// DEATH BORG OMEGA II family (ctor 0x801d4590, members pl040b/pl040c/pl040d) —
// cue table @0x80319410. All 3 members share the bespoke 5-phase X-special
// (FUN_800f3cb4 → PTR_FUN_8031b918 phase machine); see families/omega2-robot.ts.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
function makeOmega2FamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x40c ? "pl040c" as const :
        actor.borgNumber === 0x40d ? "pl040d" as const : "pl040b" as const;
      configureOmega2Family(actor, id, ctx);
    },
    cueTable: cueTableForBorg("pl040b")!,
  };
}

// DRILL ROBOT family (ctor 0x800e67d4, member pl0401) — cue table @0x803168f8.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
function makeDrillRobotFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      configureDrillFamily(actor, "pl0401", ctx);
    },
    cueTable: cueTableForBorg("pl0401")!,
  };
}

// HAMMER ROBOT family (ctor 0x800e5a0c, member pl0403) — cue table @0x803168f8.
// Also shared by HATCHET KNIGHT (pl020c, borg 0x20c) — differs only in hitbox offset.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
function makeHammerRobotFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      configureHammerFamily(actor, "pl0403", ctx);
    },
    cueTable: cueTableForBorg("pl0403")!,
  };
}

// THUNDER ROBOT family (ctor 0x800e0174, member pl0404) — cue table @0x803168f8.
// X handler at action 2; action 0 gets the shared robot-dash via withRobotDash.
function makeThunderRobotFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      configureThunderFamily(actor, "pl0404", ctx);
    },
    cueTable: cueTableForBorg("pl0404")!,
  };
}

// BEAM WING family (ctor 0x800f9a28) — full port (5 tables, 21 fns). Both borgs share
// cue table @0x8031d4b0.
function makeBeamWingFamilyRegistration(borgId: "pl0a03" | "pl0a06"): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      configureBeamWingFamily(actor, borgId, ctx);
    },
    cueTable: cueTableForBorg(borgId)!,
  };
}

// WIRE GUNNER family (ctor 0x801301f8) — cue table @0x80336178. The X-special is a
// BESPOKE 2-phase direction-gated shot deploy (FUN_80131688 → zz_01316e0_) ported in
// families/wire-gunner.ts; engine 0x80131688 lives in the family code block (not a
// shared-engine range). All 3 members (pl0103/pl0106/pl0107) share ctor 0x801301f8 +
// group-4 slots 2/3/4 (direction-switched via +0x5e0 bits 0x10/0x40).
function makeWireGunnerFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x106 ? "pl0106" :
        actor.borgNumber === 0x107 ? "pl0107" : "pl0103";
      configureWireGunnerFamily(actor, id as "pl0103" | "pl0106" | "pl0107", ctx);
    },
    cueTable: cueTableForBorg("pl0103")!,
  };
}

function makeDefaultCueTable(): Int8Array {
  const t = new Int8Array(96).fill(-1);
  t[44 * 2] = 61;
  t[44 * 2 + 1] = 0;
  t[7 * 2] = 6;
  t[7 * 2 + 1] = 6;
  return t;
}

/** Host-provided hit resolver — called by the bridge when an armed hitbox's active
 *  window intersects an enemy. The host (battle.ts) implements this using the real
 *  `applyHit` + the profiles map + the damage records + burst/energy context, giving
 *  full damage-formula fidelity without the bridge needing to import the combat stack. */
export type RomHitResolver = (
  attacker: BorgRuntime,
  victim: BorgRuntime,
  damageRecordIndex: number,
  knockbackMult: number,
  onContactAccepted?: () => void,
) => number | void;

/** Host-provided ground clamp — called after the ROM physics step to snap the borg
 *  to the stage floor. Without this the ROM integrator (no collision awareness) lets
 *  borgs fall through the ground. */
export type RomGroundClamp = (pos: { x: number; y: number; z: number }, velY: number) => { y: number; velY: number; grounded: boolean };

/** Cohesive battle-owned dependency used by every ROM family driver in one battle. */
export interface RomBattleRuntime {
  readonly floor: RomPhysicsRuntime & {
    readonly bounds: { minX: number; maxX: number; minZ: number; maxZ: number };
    isSupported(x: number, z: number): boolean;
  };
  returnResource?(owner: BorgRuntime, cell: number): void;
  allocateResource(owner: BorgRuntime, type: number, count: number, consume: boolean): boolean;
  spawnProjectile(owner: BorgRuntime, spawnerAddr: number, kind: number, actor?: RomActor): void;
  resolveHit(attacker: BorgRuntime, victim: BorgRuntime, damageRecordIndex: number, knockbackMult: number,
    onContactAccepted?: () => void): void;
  /** Optional observer for zz_01cb750_'s form-change event. */
  postMorphEvent?(owner: BorgRuntime, borgNumber: number, slot: number): void;
  /** ROM cue sink — port of zz_00f036c_(owner, cueId). Fired by the stream VM's
   *  onPlayCue hook when a ported family handler triggers a sound. The host (battle.ts)
   *  routes this through to its own Battle.onRomCue; undefined → cues drop silently
   *  at this seam (matches the silent no-op the prior attachToBattle produced). */
  onRomCue?(owner: BorgRuntime, cueId: number): void;
}

// ============================================================================
// RomHostContext — unified host-interface for ALL family ctx types.
// Every hook defaults to a bridge implementation. battle.ts overrides any hook
// that needs game-level access (spawn, ammo, collision, etc.).
// ============================================================================

/** All hooks from all family ctx types (StreamContext + family-specific extras). */
export interface RomHostContext {
  /** Family29 allocation seam; false means allocation failed after consuming cell0. */
  onTimeBomberMine?: (actor: RomActor) => boolean;
  onReturnResource?: (actor: RomActor, cell: number) => void;
  // ── StreamContext hooks ──
  onArmHit?: (actor: RomActor, kind: number, statusId: number, statusArg: number) => void;
  onPlayAnim?: (actor: RomActor, group: number, slot: number, blend: boolean) => void;
  onFireChild?: (actor: RomActor, variant: number) => void;
  onIndirect?: (actor: RomActor, a: number, b: number) => void;
  onFamilyProjectile?: (actor: RomActor, spawnerAddr: number, type: number) => void;
  onParamTierDelta?: (actor: RomActor, signedDelta: number) => void;
  onPlayCue?: (actor: RomActor, cueId: number) => void;
  onRefreshTargetVisibility?: (actor: RomActor) => void;
  onMorph?: (actor: RomActor, newBorgId: number, previousBorgId: number) => void;

  // ── Dragon / CyberDragon / CyberMachine / Worm ──
  onFaceComplete?: (actor: RomActor, mask: number) => boolean;
  onAllocateResource?: (actor: RomActor, type: number, count: number, mode?: number) => boolean;
  onExitFb?: (actor: RomActor) => void;

  // ── CyberDragon extras ──
  onFaceTarget?: (actor: RomActor, aimType: number) => void;
  onGroundSnap?: (actor: RomActor) => void;
  onSpawnChild?: (actor: RomActor, childId: number) => boolean;
  onSpawnProjectile?: (actor: RomActor, childId: number, t1: Vec3, t2: Vec3, vs: number) => void;

  // ── BeamWing / Knight ──
  onTickStream?: (actor: RomActor, group: number) => void;
  onSpawnFX?: (actor: RomActor, fxId: number) => void;
  onFrameUpdate?: (actor: RomActor) => void;
  onCheckCollision?: (actor: RomActor) => number;
  onExitUb?: (actor: RomActor) => void;
  onClearAction?: (actor: RomActor) => void;
  onStopStream?: (actor: RomActor, group: number) => void;
}

/** The bridge sidecar attached to BorgRuntime (via the `romDriver` field). Owns the
 *  RomActor + state tables + per-frame sync. Activates when a ported family exists. */
export class RomDriverBridge implements RomFamilyDriver {
  readonly actor: RomActor;
  private readonly tables: { fullBody: StateHandler[]; upperBody: StateHandler[] };
  /** The family's ported `+0x4bc` per-frame virtual, when it has one (see
   *  FamilyRegistration.frameUpdate). Runs every frame from tick(), before the
   *  action-ownership gate — the ROM's own cadence for that offset. */
  familyFrameUpdate: ((actor: RomActor, runtime: BorgRuntime) => void) | null = null;
  /** Armed hitbox records for the current special. */
  private armedHits: ArmedHit[] = [];
  /** Only the observed G RED ground action1/v0 group3/slot0 stream is admitted. */
  private mineMeleeOpenerStream = false;
  /** Which button started the active ROM machine ("x" | "b"), for the impotence latch. */
  private specialKind: "x" | "b" | null = null;
  /** True once the active ROM special armed a resolvable hit or fired a child projectile. */
  private specialHadEffect = false;
  /** A source Diver/Powered resource denial is a valid no-payload outcome, not an unported X. */
  private sourceXResourceDenied = false;
  /** Accumulated |Δpos| the ROM machine drove this special (movement X moves count as effect). */
  private specialMotionAccum = 0;
  /** Position at special start, for the NET displacement test in the impotence latch. */
  private specialStartPos = { x: 0, y: 0, z: 0 };
  /** Latched when this borg's ROM X special completed with NO payload at all (no armed
   *  hits, no child projectiles, no meaningful motion). Many families have decoded
   *  choreography but no resolvable hit kinds yet — their X was a pure pantomime that
   *  consumed the press and dealt nothing. Once latched, tryStartXSpecial refuses
   *  ownership and the caller's generic startSpecialAttack (the pre-ROM behavior)
   *  handles the X press instead. PLACEHOLDER policy until every family's hit kinds
   *  are decoded. */
  private xImpotent = false;
  private streamFrame = 0;
  /** Frames since the current armHit. Hit windows are authored relative to the
   *  arm, not to the stream clock, and the two must not share a counter: the
   *  stream clock also drives streamSchedules and the specialMaxFrames timeout. */
  private armedHitFrame = 0;
  /** Pre-decoded stream events from meleeAnimKinds.json. Played back each tick to
   *  drive anim changes + hitbox arming at the decoded ROM frames. */
  private streamEvents: StreamEvent[] | null = null;
  /** Every zz_004beb8_ call schedules the exact decoded group/slot stream here. */
  private streamSchedules: Array<{
    startFrame: number;
    endFrame: number;
    mask: number;
    events: StreamEvent[];
    completed: boolean;
    knightClocks?: Map<number, KnightWindupClock>;
  }> = [];
  /** Max frames the special runs before auto-completing (from the decoded stream length). */
  private specialMaxFrames = 30;
  readonly ctx: RomHostContext;
  /** Host-provided hit resolver (battle.ts). When null, hits are recorded but no
   *  damage is applied — the bridge logs the connection for debugging. */
  private get hitResolver(): RomHitResolver | null {
    return this.battleRuntime?.resolveHit ?? null;
  }
  private get groundClamp(): RomGroundClamp | null {
    const floor = this.battleRuntime?.floor;
    return floor ? (pos, velY) => floor.clampToGround(pos, velY) : null;
  }
  private get bounds(): RomBattleRuntime["floor"]["bounds"] | null {
    return this.battleRuntime?.floor.bounds ?? null;
  }
  private get offMeshCheck(): ((x: number, z: number) => boolean) | null {
    const floor = this.battleRuntime?.floor;
    return floor ? (x, z) => floor.isSupported(x, z) : null;
  }
  /** Projectiles spawned by the ROM stream's fireChild op (op 0x09) during the
   *  current special. Drained by battle.ts after each tick. */
  private pendingProjectiles: Projectile[] = [];
  /** Projectiles spawned by family hooks during the current special. */
  private familyProjectiles: Projectile[] = [];
  /** Never reset: family projectile uids must stay unique across specials. */
  private familyProjectileSeq = 0;

  /** Drain projectiles spawned by the ROM stream's fireChild op. Called by battle.ts
   *  after each romDriver.tick(). */
  drainProjectiles(): Projectile[] {
    // Both queues, not just pendingProjectiles. familyProjectiles was pushed to
    // and never read: on the plain attach() path -- any host that does not
    // override onFamilyProjectile, which is every standalone and selftest
    // harness -- every family-spawner shot was allocated, silently swallowed,
    // and accumulated until interrupt(). attachToBattle happens to override the
    // hook, which is the only reason production never saw it.
    const drained = this.pendingProjectiles.concat(this.familyProjectiles);
    this.pendingProjectiles = [];
    this.familyProjectiles = [];
    return drained;
  }

  /** Spawn a projectile via a family spawner address + type. Port of zz_016cc24_ /
   *  zz_006a668_ / etc. The bridge stores it in familyProjectiles for battle.ts to
   *  drain after each tick alongside the stream's pendingProjectiles. */
  private spawnFamilyProjectile(actor: RomActor, spawnerAddr: number, type: number): void {
    if (this.runtime) {
      const ninja=spawnNinjaSource(this.runtime,actor,spawnerAddr,type,this.visibilityBindings.map(binding=>binding.runtime));
      if(ninja!==null){this.familyProjectiles.push(...ninja);this.specialHadEffect=true;return;}
      const ranged=spawnGredRangedSource(this.runtime,actor,spawnerAddr,type,this.visibilityBindings.map(binding=>binding.runtime));
      if(ranged!==null){this.familyProjectiles.push(...ranged);this.specialHadEffect=true;return;}
      const blackCharge=spawnGBlackChargeSource(this.runtime,actor,spawnerAddr,type);
      if(blackCharge!==null){this.familyProjectiles.push(...blackCharge);this.specialHadEffect=true;return;}
      const wave = spawnGBlackGroundWaveSource(this.runtime,actor,spawnerAddr,type);
      if(wave!==null){this.familyProjectiles.push(...wave);this.specialHadEffect=true;return;}
      const beam = spawnBeamSource(this.runtime, actor, spawnerAddr, type);
      if (beam !== null) { this.familyProjectiles.push(...beam); this.specialHadEffect = true; return; }
      const arrow = spawnArrowSource(this.runtime, actor, spawnerAddr, type, this.arrowRoster);
      if (arrow !== null) { this.familyProjectiles.push(...arrow); this.specialHadEffect = true; return; }
      const revolver = spawnRevolverSource(this.runtime, actor, spawnerAddr, type);
      if (revolver !== null) { this.familyProjectiles.push(...revolver); this.specialHadEffect = true; return; }
      const timeBomber = spawnTimeBomberSource(this.runtime, actor, spawnerAddr, type, this.visibilityBindings.map(binding => binding.runtime));
      if (timeBomber !== null) { this.familyProjectiles.push(...timeBomber); this.specialHadEffect = true; return; }
      const gatling = spawnGatlingSource(this.runtime, actor, spawnerAddr, type,
        this.visibilityBindings.map(binding => binding.runtime));
      if (gatling !== null) { this.familyProjectiles.push(...gatling); this.specialHadEffect = true; return; }
      const powered = spawnPoweredSource(this.runtime, actor, spawnerAddr, type,
        this.visibilityBindings.map(binding => binding.runtime));
      if (powered !== null) {
        this.familyProjectiles.push(...powered);
        this.specialHadEffect = true;
        return;
      }
    }
    const p: Projectile = {
      // Monotonic, not a length: the array is cleared on every drain and on
      // interrupt(), so a length-based id repeats across specials and two live
      // projectiles can share a uid.
      uid: `family-${type}-${(this.familyProjectileSeq += 1)}`,
      ownerUid: this.runtime?.uid ?? "",
      team: this.runtime?.team ?? 0,
      pos: { x: 0, y: 0, z: 0 },
      vel: { x: 0, y: 0, z: 0 },
      damage: 0,
      hitstun: 0,
      knockback: 1,
      homingTurn: 0,
      homingTarget: null,
      life: 1,
      hitRadius: 0,
      visualKind: type as unknown as ProjectileVisualKind,
    };
    this.familyProjectiles.push(p);
  }
  /** True while the ROM state machine is mid-special. */
  private specialActive = false;
  /** True when the ROM phase machine owns the borg's per-frame motion (B-charge's 4-phase
   *  zz_0179814_ machine). When true, tick() calls stepRomActor each frame and returns true
   *  so battle.ts skips stepMovement/stepAttacks. False for X-specials (which compose with
   *  normal movement — tick() returns false and only layers stream events). */
  private romOwnedSpecial = false;
  private timeBomberLandingCooldown = false;
  /** Temporary mapping of an established host run into source control10. */
  private timeBomberMovementControl: number | null = null;
  private restoreTimeBomberMovementControl(): void {
    if(this.timeBomberMovementControl === null)return;
    this.actor.controlWord=(this.actor.controlWord&~0x30)|this.timeBomberMovementControl;
    this.timeBomberMovementControl=null;
  }
  private gredAirShotLocomotion: {state:BorgRuntime['state'];anim:BorgRuntime['anim'];stateTime:number}|null=null;
  private timeBomberLocomotion: { state:BorgRuntime['state']; anim:BorgRuntime['anim']; stateTime:number } | null = null;

  /** Variants1/3 are part0 shots. Host movement stands in for the lower channel,
   * whose state is not otherwise continuously mirrored into this bridge. */
  runHostLocomotion(runtime:BorgRuntime, update:()=>void):void {
    const airShot=getGRedAirShotState(this.actor);
    if(this.specialActive&&airShot?.partMode&&this.gredAirShotLocomotion){
      const upper={state:runtime.state,anim:runtime.anim,stateTime:runtime.stateTime};
      Object.assign(runtime,this.gredAirShotLocomotion);update();runtime.stateTime+=1;
      this.gredAirShotLocomotion={state:runtime.state,anim:runtime.anim,stateTime:runtime.stateTime};
      Object.assign(runtime,upper);return;
    }
    if(!this.specialActive || runtime.borgId!=="pl0106" || this.actor.actionIndex!==0 ||
       (this.actor.variantIndex!==1 && this.actor.variantIndex!==3) || !this.timeBomberLocomotion)return;
    const presentation={state:runtime.state,anim:runtime.anim,stateTime:runtime.stateTime};
    Object.assign(runtime,this.timeBomberLocomotion);
    update();
    // Battle's normal path increments the locomotion clock after movement.
    runtime.stateTime+=1;
    this.timeBomberLocomotion={state:runtime.state,anim:runtime.anim,stateTime:runtime.stateTime};
    Object.assign(runtime,presentation);
  }

  private runtime: BorgRuntime | null = null;
  private visibilityBindings: Array<{ runtime: BorgRuntime; state: RomVisibilityTarget }> = [];
  private beamStreamClock: BeamStreamClock | null = null;
  private arrowStreamClock: ArrowStreamClock | null = null;
  private arrowStreamMask = 0;
  private positionHistoryFrame: number | null = null;
  private neoBWasHeld = false;
  private neoBPressed = false;
  private shotAWasHeld=false;
  private shotABuffer=0;
  private shotAActive=false;
  private shotDirectionActive=false;
  private neoWaveStruck = new Set<string>();

  private constructor(
    actor: RomActor,
    private readonly battleRuntime: RomBattleRuntime | null,
  ) {
    this.actor = actor;
    actor.physicsRuntime = battleRuntime?.floor ?? null;
    this.tables = createRomStateTables();
    this.ctx = this.buildDefaultCtx();
    (actor as RomActor & {
      onStartStream?: (group: number, slot: number, mask: number) => boolean;
    }).onStartStream = (group, slot, mask) => this.onStartStream(group, slot, mask);
    (actor as RomActor & { onTickStreamPart?: (index: number) => boolean }).onTickStreamPart =
      (index) => tickNinjaXStreamPart(this.actor,index,this.ctx) || tickGRedAirShotStreamPart(this.actor,index,this.ctx) || tickGRedShotStreamPart(this.actor,index,this.ctx) || tickGBlackChargeStreamPart(this.actor,index,this.ctx) || tickGRedChargeStreamPart(this.actor,index,this.ctx) || tickGRedCrashStreamPart(this.actor,index,this.ctx) ||
        tickGRedAirMeleeStreamPart(this.actor,index,this.ctx) ||
        tickNeoGredMeleeStreamPart(this.actor,index,this.ctx) ||
        this.tickArrowStreamPart(index) || this.tickBeamStreamPart(index) || this.tickKnightStreamPart(index);
  }

  private onStartStream(group: number, slot: number, mask: number): boolean {
    if (!this.runtime) return false;
    for (const hit of this.armedHits) delete hit.mineReceiverAttackUid;
    this.mineMeleeOpenerStream = this.runtime.borgId === "pl0615" && this.runtime.grounded &&
      this.specialKind === "b" && this.romOwnedSpecial && this.actor.actionIndex === 1 &&
      this.actor.variantIndex === 0 && group === 3 && slot === 0 && (mask & this.actor.weaponPartMask & 1) !== 0;
    if(getNinjaXState(this.actor)&&group===4&&(slot===0||slot===1)){
      this.streamSchedules=[];this.armedHits=[];this.specialMaxFrames=Math.max(this.specialMaxFrames,240);
      return startNinjaXStream(this.actor,group,slot,mask,this.ctx);
    }
    if(getGBlackChargeState(this.actor) && group===4 && slot===3){
      this.streamSchedules=[];this.armedHits=[];this.specialMaxFrames=Math.max(this.specialMaxFrames,240);
      return startGBlackChargeStream(this.actor,group,slot,mask,this.ctx);
    }
    if(getGRedChargeState(this.actor) && group===4 && slot===2){
      this.streamSchedules=[];this.armedHits=[];this.specialMaxFrames=Math.max(this.specialMaxFrames,300);
      return startGRedChargeStream(this.actor,group,slot,mask,this.ctx);
    }
    if(getGRedAirShotState(this.actor)&&((group===2&&[4,5,6,7].includes(slot))||(group===0&&slot===13))){
      this.streamSchedules=[];this.armedHits=[];
      return startGRedAirShotStream(this.actor,group,slot,mask,this.ctx);
    }
    if(getGRedShotState(this.actor) && group===2 && (slot===0||slot===1)){
      this.streamSchedules=[];this.armedHits=[];
      return startGRedShotStream(this.actor,group,slot,mask,this.ctx);
    }
    const crash=getGRedCrashState(this.actor);
    if(crash && group===4 && slot===(crash.family==='red'?0:crash.family==='neo'?1:4)){
      this.streamSchedules=[];this.armedHits=[];
      this.specialMaxFrames=Math.max(this.specialMaxFrames,240);
      return startGRedCrashStream(this.actor,group,slot,mask,this.ctx);
    }
    const airMelee=getGRedAirMeleeState(this.actor);
    if(airMelee && group===3 && gredAirMeleeStreamProfile(airMelee.family,slot)){
      this.streamSchedules=[];this.armedHits=[];
      // Safety ceiling only; source conditional stream/phase completion owns exit.
      this.specialMaxFrames=Math.max(this.specialMaxFrames,240);
      return startGRedAirMeleeStream(this.actor,group,slot,mask,this.ctx);
    }
    if (getNeoGredMeleeState(this.actor) && group === 3 && (slot === 0 || slot === 1 || slot === 2 || slot === 13 || slot === 14 || slot === 15 || slot === 25 || slot === 26 || slot === 27)) {
      this.streamSchedules = [];
      this.armedHits = [];
      this.neoWaveStruck = new Set();
      // Safety ceiling only. Source end/wait/phase transitions own normal exit.
      this.specialMaxFrames = Math.max(this.specialMaxFrames, 240);
      return startNeoGredMeleeStream(this.actor,group,slot,mask,this.ctx);
    }
    if ((this.runtime.borgId === "pl0002" || this.runtime.borgId === "pl000b")
      && this.actor.actionIndex === 2 && group === 4 && (slot === 0 || slot === 1)) {
      this.arrowStreamClock = createArrowStreamClock(slot);
      this.arrowStreamMask = mask & this.actor.weaponPartMask;
      this.streamSchedules = [];
      if ((this.arrowStreamMask & 1) !== 0) {
        this.actor.wallContact = 0;
        this.actor.contactP0 = 0;
        this.actor.defaultGroup = 1;
        (this.actor.parts[0] as { c?: number }).c = 0;
        const flags = this.actor as RomActor & { arrowFlags6e8?: number; arrowFlags6e9?: number };
        flags.arrowFlags6e8 = 3;
        flags.arrowFlags6e9 = 1;
      }
      if ((this.arrowStreamMask & 2) !== 0) {
        this.actor.parts[1]!.stateByte = 0;
        (this.actor.parts[1] as { c?: number }).c = 1;
      }
      // Source terminal waits for AOBJ end45, not the final contact event34.
      // Ceiling only guards a corrupt state; the clock owns normal completion.
      this.specialMaxFrames = Math.max(this.specialMaxFrames, 64);
      this.ctx.onPlayAnim?.(this.actor, 4, slot, false);
      return true;
    }
    if (this.runtime.borgId === "pl0104" && this.actor.actionIndex === 2 && group === 4 && slot >= 0 && slot <= 2) {
      this.beamStreamClock = createBeamStreamClock(slot);
      this.streamSchedules = [];
      this.actor.wallContact = 0;
      this.actor.contactP0 = slot === 1 ? 1 : 0;
      this.actor.contactP1 = 0;
      if (slot !== 1) this.actor.defaultGroup = 1;
      const flags = this.actor as RomActor & {
        beamFlags6e8?: number; beamFlags6e9?: number; beamContactFlags709?: number;
      };
      flags.beamFlags6e8 = 0;
      flags.beamFlags6e9 = slot === 1 ? 2 : 0;
      // startStream clears709 first; slot0 then executes op0b010100 (OR1).
      flags.beamContactFlags709 = slot === 0 ? 1 : 0;
      // Original 8004c488 op3: replace posture bits4..11 with operand&ff0.
      // Slot0 explicitly sets airborne40; release/recovery slots clear it.
      this.actor.controlWord = (this.actor.controlWord & ~0xff0) | (slot === 0 ? 0x40 : 0);
      this.ctx.onPlayAnim?.(this.actor, 4, slot, false);
      return true;
    }
    const events = streamEventsForSlot(
      this.runtime.borgId,
      this.actor.actionIndex,
      this.actor.variantIndex,
      group,
      slot,
    );
    const effective = mask & this.actor.weaponPartMask;
    const knightWindup = (this.runtime.borgId === "pl0208" || this.runtime.borgId === "pl020e")
      && this.actor.actionIndex === 2 && this.actor.variantIndex === 0 && group === 4 && slot === 2
      && ACTION_STREAM_DATA.borgs[this.runtime.borgId]?.actions?.["2"]?.variants?.["0"]?.bank === "0x80300420";
    // A replacement (even within the same bridge frame, or lacking decoded data)
    // must revoke old ownership. Restrict this change to the verified wait path.
    for (const schedule of this.streamSchedules) {
      if (schedule.knightClocks || knightWindup) {
        schedule.mask &= ~effective;
        for (const index of schedule.knightClocks?.keys() ?? []) {
          if ((effective & (1 << index)) !== 0) schedule.knightClocks!.delete(index);
        }
        if (schedule.knightClocks?.size === 0) schedule.completed = true;
      }
    }
    if (!events) return false;
    if (knightWindup && effective !== 0) {
      const clocks = new Map<number, KnightWindupClock>();
      for (let i = 0; i < this.actor.parts.length; i++) {
        if ((effective & (1 << i)) !== 0) clocks.set(i, createKnightWindupClock(1));
      }
      this.streamSchedules.push({ startFrame: this.streamFrame, endFrame: Infinity,
        mask: effective, events: [], completed: false, knightClocks: clocks });
      if ((effective & 1) !== 0) this.actor.wallContact = 0;
      // Immediate source setup only. The terminal wait owns all subsequent ticks.
      this.dispatchEventList(events.slice(0, events.findIndex((event) => event.op === "wait")), 0);
      return true;
    }
    const poweredSourceAction = group === 4 && ((this.runtime.borgId === "pl0101" && (this.actor.actionIndex === 2 || this.actor.actionIndex === 3)) || (isRevolver(this.runtime.borgId) && this.actor.actionIndex === 2));
    const startFrame = poweredSourceAction ? this.streamFrame - 1 : this.streamFrame;
    const maxFrame = events.reduce((max, event) =>
      Math.max(max, typeof event.frame === "number" ? event.frame : 0), 0);
    this.streamSchedules.push({
      startFrame,
      endFrame: startFrame + maxFrame + 1,
      mask,
      events,
      completed: false,
    });
    this.specialMaxFrames = Math.max(this.specialMaxFrames, this.streamFrame + maxFrame + 5);
    if (poweredSourceAction) this.dispatchEventList(events, 0);
    return true;
  }

  private tickArrowStreamPart(index: number): boolean {
    const clock = this.arrowStreamClock;
    if (!clock || this.actor.actionIndex !== 2 ||
      (this.runtime?.borgId !== "pl0002" && this.runtime?.borgId !== "pl000b")) return false;
    if ((this.arrowStreamMask & (1 << index)) === 0) return false;
    // All parts share this authored animation; advance once, at the first
    // selected part. The family observes contact in this same tickStream call.
    const firstPart = 31 - Math.clz32(this.arrowStreamMask & -this.arrowStreamMask);
    if (index !== firstPart) return true;
    const event = tickArrowStream(clock, this.actor.dt);
    if (event.contact !== undefined && (this.arrowStreamMask & 1) !== 0) {
      this.actor.contactP0 = event.contact;
      this.actor.parts[0]!.stateByte = event.contact;
      const flags = this.actor as RomActor & { arrowFlags6e8?: number; arrowFlags6e9?: number };
      flags.arrowFlags6e8 = event.gate === 9 ? 1 : event.gate === 17 ? 2 : 0;
      flags.arrowFlags6e9 = event.gate === 9 || event.gate === 34 ? 1 : 2;
      if (clock.slot === 1 && event.gate === 17) this.actor.defaultGroup = 1;
    }
    if (event.gate === 21 && (this.arrowStreamMask & 2) !== 0) {
      // Original8004c488: op3 b1/b2 write part1 state/aux; u16ffff
      // preserves posture. Ground operand0 replaces bits4..11 with zero.
      this.actor.parts[1]!.stateByte = clock.slot === 1 ? 0x20 : 0;
      (this.actor.parts[1] as { c?: number }).c = 0;
      if (clock.slot === 0) this.actor.controlWord &= ~0xff0;
    }
    if (event.completed) {
      for (let part = 0; part < this.actor.parts.length; part++) {
        if ((this.arrowStreamMask & (1 << part)) !== 0) this.actor.parts[part]!.streamPtr = -1;
      }
      this.arrowStreamClock = null;
    }
    return true;
  }

  private tickBeamStreamPart(index: number): boolean {
    if (!this.beamStreamClock || this.runtime?.borgId !== "pl0104" || this.actor.actionIndex !== 2)
      return false;
    if (index !== 0) return true;
    const event = tickBeamStream(this.beamStreamClock, this.actor.dt);
    if (event.contact !== undefined) {
      this.actor.contactP0 = event.contact;
      if (event.contact === 0) {
        (this.actor as RomActor & { beamFlags6e9?: number }).beamFlags6e9 = 2;
      }
    }
    if (event.animation !== undefined) this.ctx.onPlayAnim?.(this.actor, 4, event.animation, false);
    if (event.completed) {
      for (const part of this.actor.parts) part.streamPtr = -1;
      this.beamStreamClock = null;
    }
    return true;
  }

  private tickKnightStreamPart(index: number): boolean {
    const schedule = this.streamSchedules.find((candidate) =>
      candidate.knightClocks && (candidate.mask & (1 << index)) !== 0 && !candidate.completed);
    const clock = schedule?.knightClocks?.get(index);
    if (!schedule || !clock) return false;
    // Existing bridge animation-rate approximation: neutral 1. Source +1dc8's
    // tier/action/status/freeze factors are NOT wired here (see findings doc).
    if (tickKnightWindupClock(clock, 1)) {
      this.actor.parts[index]!.streamPtr = -1;
      schedule.knightClocks!.delete(index);
      if (schedule.knightClocks!.size === 0) schedule.completed = true;
    }
    return true;
  }

  private hasPendingKnightWindup(): boolean {
    return this.streamSchedules.some((schedule) => schedule.knightClocks
      && !schedule.completed && schedule.mask !== 0);
  }

  /** Build a comprehensive RomHostContext with default implementations. The bridge
   *  constructs this before configure so the family configure closure receives a ctx
   *  with ALL hooks wired (default bridge behaviors → can be overridden by the host
   *  context passed to attach). */
  private buildDefaultCtx(): RomHostContext {
    const bridge = this;
    return {
      // StreamContext hooks: no-op defaults (bridge wraps later in attach)
      onArmHit: () => {},
      onPlayAnim: () => {},
      onFireChild: () => {},
      onIndirect: () => {},
      onFamilyProjectile: (a, addr, type) => { bridge.spawnFamilyProjectile(a, addr, type); },
      onTimeBomberMine: (a) => { bridge.ctx.onFamilyProjectile?.(a,0x800e058c,2); return true; },
      onReturnResource: (_a, cell) => {
        const runtime=bridge.runtime, slot=runtime?.weaponCells?.[cell];
        if(runtime && slot && slot.max>0){slot.cur=Math.min(slot.max,slot.cur+1);if(cell===0)runtime.ammo=slot.cur;}
      },
      onParamTierDelta: () => {},
      onPlayCue: () => {},
      onRefreshTargetVisibility: (a) => bridge.flushVisibilityState(a),
      onMorph: (a, next, previous) => bridge.applyMorphLifecycle(a, next, previous),

      // Dragon / CyberDragon / CyberMachine / Worm
      onFaceComplete: (a, mask) => bridge.defaultOnFaceComplete(a, mask),
      onAllocateResource: () => true,
      onExitFb: (a) => bridge.defaultOnExitFb(a),

      // CyberDragon extras
      onFaceTarget: (a, aimType) => bridge.defaultOnFaceTarget(a, aimType),
      onGroundSnap: (a) => bridge.defaultOnGroundSnap(a),
      onSpawnChild: (a, childId) => bridge.defaultOnSpawnChild(a, childId),
      onSpawnProjectile: () => {},

      // BeamWing / Knight
      onTickStream: (a, group) => bridge.defaultOnTickStream(a, group),
      onSpawnFX: () => {},
      onFrameUpdate: () => {},
      onCheckCollision: (a) => bridge.defaultOnCheckCollision(a),
      onExitUb: (a) => bridge.defaultOnExitUb(a),
      onClearAction: (a) => bridge.defaultOnClearAction(a),
      onStopStream: () => {},
    };
  }

  /** ── Default implementations ── */

  private flushVisibilityState(actor: RomActor): void {
    void actor;
    for (const binding of this.visibilityBindings) {
      binding.runtime.targetVisibilityMask5e6 = binding.state.visibilityMask5e6 & 0xff;
    }
  }

  private applyMorphLifecycle(actor: RomActor, newBorgNumber: number, previousBorgNumber: number): void {
    void previousBorgNumber;
    const runtime = this.runtime;
    if (!runtime) return;
    const formId = `pl${(newBorgNumber & 0xffff).toString(16).padStart(4, "0")}`;
    const movement = movementPhysicsForBorgId(formId);
    const stats = sourceStatsForBorgId(formId);
    if (!movement || !stats) {
      throw new Error(`incomplete internal morph form data for ${formId}`);
    }
    const descriptor = {
        header: 0, mainHandBone: 0, subtypeCommand: new Int8Array(0),
        handlerData6c: movement.gravityFall, subtypePartCommand: new Int8Array(0),
        buttonLiveFlag: new Int8Array(0), defaultHand0: 0, defaultHand1: 0,
        maxHSpeed: movement.maxHSpeed, groundAccel: movement.groundAccel,
        jumpImpulse: movement.jumpImpulse, minSpeed: movement.minTurnSpeed,
        gravitySlotA: movement.gravityGround, gravitySlotC: movement.gravityC,
        handlerData68: movement.gravityGround, handlerData48: movement.jumpImpulse,
        handlerData2c: movement.maxHSpeed, turnStep0: movement.turnStep0,
        turnStep1: movement.turnStep1,
      };
    const cells: WeaponCell[] = stats.weaponSlots.map((slot) => ({
      cur: slot.ammoCount, max: slot.ammoCount, refillType: slot.chargeType,
      refillParam: slot.chargeCount, timer: slot.chargeType === 1 ? 0 : slot.chargeCount,
    }));
    cells.push({ cur: 0, max: 0, refillType: 0, refillParam: 0, timer: 0 });

    // One synchronous commit: no observer can see form id with stale descriptor/ammo.
    actor.maxHSpeed = movement.maxHSpeed;
    actor.gravityCoeff = movement.gravityFall;
    actor.actionSpeedRows = [movement.actionSpeed0, movement.actionSpeed1, movement.actionSpeed2];
    actor.descriptor = descriptor;
    runtime.weaponCells = cells;
    runtime.ammo = cells[0]!.max <= 0 ? Number.POSITIVE_INFINITY : cells[0]!.cur;
    runtime.combatFormId = formId;
    runtime.meleeAnimStream = null;
    delete runtime.sourceAnimSample;
    (runtime.romMorphEvents ??= []).push({
      eventAddress: 0x801cb750, borgNumber: newBorgNumber, slot: actor.slot,
    });
    this.battleRuntime?.postMorphEvent?.(runtime, newBorgNumber, actor.slot);
  }

  private defaultOnFaceComplete(actor: RomActor, mask: number): boolean {
    void mask;
    const lt = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
    if (!lt) return true;
    const dx = lt.x - actor.pos.x;
    const dz = lt.z - actor.pos.z;
    if (Math.abs(dx) < 0.001 && Math.abs(dz) < 0.001) return true;
    const targetBam = radToBam(Math.atan2(dx, dz));
    const diff = ((targetBam - actor.heading + 0x8000) & 0xffff) - 0x8000;
    const step = Math.max(256, Math.abs(diff) >> 3);
    if (Math.abs(diff) <= step) {
      actor.heading = targetBam;
      return true;
    }
    actor.heading = (actor.heading + (diff > 0 ? step : -step)) & 0xffff;
    return false;
  }

  private defaultOnExitFb(actor: RomActor): void {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
  }

  private defaultOnFaceTarget(actor: RomActor, aimType: number): void {
    void aimType;
    const lt = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
    if (!lt) return;
    const dx = lt.x - actor.pos.x;
    const dz = lt.z - actor.pos.z;
    if (Math.abs(dx) < 0.001 && Math.abs(dz) < 0.001) return;
    actor.heading = radToBam(Math.atan2(dx, dz));
  }

  private defaultOnGroundSnap(actor: RomActor): void {
    if (this.groundClamp) {
      const result = this.groundClamp(actor.pos, actor.yVel);
      actor.pos.y = result.y;
      actor.yVel = result.velY;
    }
  }

  private defaultOnSpawnChild(actor: RomActor, childId: number): boolean {
    void actor; void childId;
    return true;
  }

  private defaultOnTickStream(actor: RomActor, group: number): void {
    void group;
    tickStream(actor, 0xf, this.ctx);
  }

  private defaultOnCheckCollision(actor: RomActor): number {
    return (actor as RomActor & { grounded?: boolean }).grounded ? 0 : 1;
  }

  private defaultOnExitUb(actor: RomActor): void {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchUpperBodyCue(actor, 0);
  }

  private defaultOnClearAction(actor: RomActor): void {
    actor.controlWord = actor.controlWord & ~0x3;
    dispatchFullBodyCue(actor, 0);
    dispatchUpperBodyCue(actor, 0);
  }

  /** Attach a bridge to a freshly-spawned BorgRuntime. Returns the bridge, or null if
   *  the borg has no ported family (caller keeps generic archetypes). */
  static attach(runtime: BorgRuntime, hostCtx: RomHostContext): RomDriverBridge | null {
    return RomDriverBridge.attachWith(runtime, hostCtx, null);
  }

  /** Production construction seam: one battle runtime supplies all external facts. */
  static attachToBattle(runtime: BorgRuntime, battleRuntime: RomBattleRuntime): RomDriverBridge | null {
    const hostCtx: RomHostContext = {
      onReturnResource: (_actor, cell) => battleRuntime.returnResource?.(runtime, cell),
      onAllocateResource: (_actor, type, count, mode) =>
        battleRuntime.allocateResource(runtime, type, count, (mode ?? 0) !== 0),
      onFamilyProjectile: (actor, addr, kind) =>
        battleRuntime.spawnProjectile(runtime, addr, kind, actor),
      onSpawnChild: (_actor, childId) => {
        battleRuntime.spawnProjectile(runtime, 0, childId);
        return true;
      },
      // Route the stream VM's onPlayCue (fired by family handlers — STAR HERO buff cue
      // 0xa5, beam-wing/dragon spawn stingers, magnet/omega/morph cues, etc.) through
      // the battle runtime's onRomCue sink. battle.ts plumbs this to its Battle.onRomCue
      // field, which apps/game wires to playSfx(resolveCueToAsset(cueId, sfxKeys)).
      // Without this override the bridge falls back to the silent default ctx.onPlayCue
      // no-op (overlayHostCtx's else branch never runs for onPlayCue, so the cue would
      // never escape the package).
      onPlayCue: (_actor, cueId) => battleRuntime.onRomCue?.(runtime, cueId),
    };
    return RomDriverBridge.attachWith(runtime, hostCtx, battleRuntime);
  }

  private static attachWith(
    runtime: BorgRuntime,
    hostCtx: RomHostContext,
    battleRuntime: RomBattleRuntime | null,
  ): RomDriverBridge | null {
    const reg = familyRegistry()[runtime.borgId];
    const actor = createRomActor();
    // Every borg gets its REAL family cue table when extracted (119/119 families);
    // the hand-rolled default remains only as a last-resort fallback.
    actor.cueTable = reg?.cueTable ?? cueTableForBorg(runtime.borgId) ?? makeDefaultCueTable();
    const bridge = new RomDriverBridge(actor, battleRuntime);
    if (reg?.frameUpdate) bridge.familyFrameUpdate = reg.frameUpdate;
    actor.borgNumber = borgIdToNumber(runtime.borgId);
    actor.team = runtime.team;
    // Merge host-provided hooks into bridge ctx (overrides defaults).
    bridge.overlayHostCtx(hostCtx, runtime);
    if (reg) {
      reg.configure(actor, bridge.ctx);
    } else {
      const streamMeta = ACTION_STREAM_BANKS[runtime.borgId];
      if (!streamMeta) return null;
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: DEFAULT_CONFIGS.dashAttack(streamMeta.seedSlot ?? 0),
      });
    }
    // Family configure helpers may stamp the constructor's first/default member while
    // selecting shared behavior. Restore the actual runtime member afterwards so all
    // per-borg switches observe the real +0x3e8 value (e.g. MACHINE RED/BLUE variants).
    actor.borgNumber = borgIdToNumber(runtime.borgId);
    const movement = movementPhysicsForBorgId(runtime.borgId);
    if (movement) {
      actor.maxHSpeed = movement.maxHSpeed;
      actor.gravityCoeff = movement.gravityFall;
      actor.actionSpeedRows = [movement.actionSpeed0, movement.actionSpeed1, movement.actionSpeed2];
      actor.descriptor = {
        header: 0,
        mainHandBone: 0,
        subtypeCommand: new Int8Array(0),
        handlerData6c: movement.gravityFall,
        subtypePartCommand: new Int8Array(0),
        buttonLiveFlag: new Int8Array(0),
        defaultHand0: 0,
        defaultHand1: 0,
        maxHSpeed: movement.maxHSpeed,
        groundAccel: movement.groundAccel,
        jumpImpulse: movement.jumpImpulse,
        minSpeed: movement.minTurnSpeed,
        gravitySlotA: movement.gravityGround,
        gravitySlotC: movement.gravityC,
        handlerData68: movement.gravityGround,
        handlerData48: movement.jumpImpulse,
        handlerData2c: movement.maxHSpeed,
        turnStep0: movement.turnStep0,
        turnStep1: movement.turnStep1,
      };
    }
    // Source spawn setup seeds both own-position samples from +0x20, after the
    // spawn/floor placement (chunk_0007.c:699-704). Do not seed from a lock target.
    Object.assign(actor.pos, runtime.pos);
    Object.assign(actor.savedGroundPos, runtime.pos);
    Object.assign(actor.targetCache5e8, runtime.pos);
    return bridge;
  }

  /** Overlay a host-provided context onto the bridge's default ctx. Pipes StreamContext
   *  hooks through bridge interceptors; passes family hooks through directly. */
  private overlayHostCtx(host: RomHostContext, runtime: BorgRuntime): void {
    this.runtime = runtime;
    // StreamContext hooks: wrap with bridge interceptors
    if (host.onArmHit) {
      const orig = host.onArmHit;
      host.onArmHit = (a, kind, statusId, statusArg) => {
        orig(a, kind, statusId, statusArg);
        this.onArmHit(kind);
      };
    } else {
      const bridge = this;
      host.onArmHit = (a, kind, statusId, statusArg) => { bridge.onArmHit(kind); void a; void statusId; void statusArg; };
    }
    if (host.onPlayAnim) {
      const orig = host.onPlayAnim;
      host.onPlayAnim = (a, group, slot, blend) => {
        orig(a, group, slot, blend);
        this.onPlayAnim(group, slot);
      };
    } else {
      // No host hook — wire the bridge's own onPlayAnim (sets runtime.anim +
      // meleeAnimStream so the renderer receives the attack clip slot). Without
      // this else branch, attack animations never reach the renderer.
      const bridge = this;
      host.onPlayAnim = (a, group, slot, blend) => { bridge.onPlayAnim(group, slot); void a; void blend; };
    }
    if (host.onFireChild) {
      const orig = host.onFireChild;
      host.onFireChild = (a, variant) => {
        orig(a, variant);
        this.onFireChild(variant);
      };
    } else {
      // No host hook — wire the bridge's own onFireChild (spawns the projectile
      // child via spawnRomProjectile). Without this else branch, beam/child
      // spawns (G RED beam, etc.) never create a projectile entity.
      const bridge = this;
      host.onFireChild = (a, variant) => { bridge.onFireChild(variant); void a; };
    }
    if (host.onParamTierDelta) {
      const orig = host.onParamTierDelta;
      host.onParamTierDelta = (a, delta) => {
        orig(a, delta);
        this.onParamTierDelta(delta);
      };
    } else {
      // Production attachToBattle has no observer. Still commit the family writer
      // to runtime state, just as animation/projectile hooks do above.
      host.onParamTierDelta = (_actor, delta) => this.onParamTierDelta(delta);
    }
    // Copy all hooks from host to bridge.ctx — explicit per-hook to avoid union-of-
    // function-types issue with exactOptionalPropertyTypes.
    const dest = this.ctx;
    if(host.onTimeBomberMine)dest.onTimeBomberMine=host.onTimeBomberMine;
    if(host.onReturnResource)dest.onReturnResource=host.onReturnResource;
    if (host.onArmHit) dest.onArmHit = host.onArmHit;
    if (host.onPlayAnim) dest.onPlayAnim = host.onPlayAnim;
    if (host.onFireChild) dest.onFireChild = host.onFireChild;
    if (host.onIndirect) dest.onIndirect = host.onIndirect;
    if (host.onFamilyProjectile) dest.onFamilyProjectile = (actor, addr, type) => {
      host.onFamilyProjectile!(actor, addr, type);
      // A persistent child is a real X effect even when it arms no actor hitbox.
      this.specialHadEffect = true;
    };
    if (host.onParamTierDelta) dest.onParamTierDelta = host.onParamTierDelta;
    if (host.onPlayCue) dest.onPlayCue = host.onPlayCue;
    if (host.onRefreshTargetVisibility) dest.onRefreshTargetVisibility = host.onRefreshTargetVisibility;
    if (host.onMorph) dest.onMorph = host.onMorph;
    if (host.onFaceComplete) dest.onFaceComplete = host.onFaceComplete;
    if (host.onAllocateResource) dest.onAllocateResource = (actor, type, count, mode) => {
      const accepted = host.onAllocateResource!(actor, type, count, mode);
      if (!accepted && type === 2 &&
          ((mode ?? 0) !== 0 || runtime.borgId === "pl0104") &&
          (isSourceNinjaX(runtime.borgId) || isNurseX(runtime.borgId) || isDiverAmmoFamily(runtime.combatFormId ?? runtime.borgId) ||
           runtime.borgId === "pl0101" || runtime.borgId === "pl0102" || runtime.borgId === "pl0106" ||
           runtime.borgId === "pl0104" || isArrowNinja(runtime.borgId) || isRevolver(runtime.borgId))) {
        this.sourceXResourceDenied = true;
      }
      return accepted;
    };
    if (host.onExitFb) dest.onExitFb = host.onExitFb;
    if (host.onFaceTarget) dest.onFaceTarget = host.onFaceTarget;
    if (host.onGroundSnap) dest.onGroundSnap = host.onGroundSnap;
    if (host.onSpawnChild) dest.onSpawnChild = host.onSpawnChild;
    if (host.onSpawnProjectile) dest.onSpawnProjectile = host.onSpawnProjectile;
    if (host.onTickStream) dest.onTickStream = host.onTickStream;
    if (host.onSpawnFX) dest.onSpawnFX = host.onSpawnFX;
    if (host.onFrameUpdate) dest.onFrameUpdate = host.onFrameUpdate;
    if (host.onCheckCollision) dest.onCheckCollision = host.onCheckCollision;
    if (host.onExitUb) dest.onExitUb = host.onExitUb;
    if (host.onClearAction) dest.onClearAction = host.onClearAction;
    if (host.onStopStream) dest.onStopStream = host.onStopStream;
  }

  /** zz_005685c_ (chunk_0007.c:201-206): shift own-position history exactly once
   * before this simulation frame's movement/action work, even while the driver
   * is inactive or the actor is airborne/hit/dead. The older +0x5e8 sample is used
   * by family movement carry; +0x2c is the current frame's pre-movement position.
   * Battle owns this clock. syncIn/admission/interrupt must not advance it. */
  beginFrame(runtime: BorgRuntime, frame: number): void {
    if (this.positionHistoryFrame === frame) return;
    this.positionHistoryFrame = frame;
    // 005568c runs before action dispatch. Time Bomber B and fallback landing
    // share +694; active low action bits freeze this source timer.
    if(runtime.borgId === "pl0106" && (this.actor.controlWord&3)===0){
      this.actor.stateTimer=Math.max(0,this.actor.stateTimer-this.actor.dt);
      if(this.actor.stateTimer===0)this.timeBomberLandingCooldown=false;
    }
    if(isSourceTeleportX(runtime.borgId)&&(runtime.sourceTeleportRecentMeleeTimer144??0)>0)
      runtime.sourceTeleportRecentMeleeTimer144=Math.fround(runtime.sourceTeleportRecentMeleeTimer144!-this.actor.dt);
    Object.assign(this.actor.targetCache5e8, this.actor.savedGroundPos);
    Object.assign(this.actor.savedGroundPos, runtime.pos);
  }

  /** 801304b8 runs after action dispatch; B neither owns nor interrupts X. */
  postAction(runtime: BorgRuntime, all: readonly BorgRuntime[], _input: PlayerInput): void {
    if(runtime.borgId!=="pl0106" || !runtime.alive || runtime.hp<=0 || runtime.state==="death" || runtime.state==="spawn")return;
    if(!runtime.timeBomberBInput?.pressEdge || this.actor.stateTimer>0)return;
    this.runtime=runtime;
    this.syncIn(runtime,all);
    if(this.ctx.onAllocateResource?.(this.actor,0,1,1)) {
      if(this.ctx.onTimeBomberMine?.(this.actor)===false)this.ctx.onReturnResource?.(this.actor,0);
      this.ctx.onPlayCue?.(this.actor,235);
    }
    // Empty cell still arms +694. Admission of a later X resets the same timer.
    this.actor.stateTimer=Math.fround(4+this.actor.dt);
  }

  private arrowRoster: readonly BorgRuntime[] = [];

  /** Copy BorgRuntime → RomActor (before the ROM step). During an active special,
   *  velocity is NOT synced — the ROM handler owns it (syncIn would overwrite the
   *  phase machine's impulses with stale BorgRuntime.vel from before the special). */
  syncIn(runtime: BorgRuntime, all: readonly BorgRuntime[]): void {
    this.arrowRoster = all;
    const a = this.actor;
    const slot = Math.max(0, all.indexOf(runtime));
    a.slot = slot;
    a.visibilityBit = (1 << slot) & 0xff;
    a.identityVariant = runtime.colorVariant ?? 0;
    this.visibilityBindings = all.slice(0, 6).map((candidate) => {
      const state: RomVisibilityTarget = {
        eligibility83: candidate.targetEligibility83 ?? (candidate.alive ? 0 : 1),
        controlWord: candidate.alive ? 0 : 0x80000000,
        visibilityMask5e6: candidate.targetVisibilityMask5e6 ?? 0,
      };
      return { runtime: candidate, state };
    });
    a.visibilityRoster = this.visibilityBindings.map((binding) => binding.state);
    const activeTarget = activeSourceTarget(runtime, all);
    a.visibilityTarget = activeTarget
      ? this.visibilityBindings.find((binding) => binding.runtime.uid === activeTarget.uid)?.state ?? null
      : null;
    a.pos.x = runtime.pos.x;
    a.pos.y = runtime.pos.y;
    a.pos.z = runtime.pos.z;
    // The host's proven root transform is the current +0x20 position; until a model bone
    // transform overrides it, this is the exact host-resolved +0x518 aim-origin surface.
    a.aimOrigin518.x = runtime.pos.x;
    a.aimOrigin518.y = runtime.pos.y;
    a.aimOrigin518.z = runtime.pos.z;
    a.modelScale = tierSizeScale(runtime);
    a.sizeScale = girlDescriptorSizeScale(runtime.combatFormId ?? runtime.borgId);
    a.heading = radToBam(runtime.rotY);
    // Only sync velocity on the FIRST entry frame (specialActive was just set).
    // Subsequent ticks: ROM handler owns velocity; skip the copy.
    if (!this.specialActive || getGRedAirShotState(a)?.partMode || (runtime.borgId === "pl0106" && this.actor.actionIndex === 0 && (this.actor.variantIndex === 1 || this.actor.variantIndex === 3))) {
      a.lockYaw = a.heading;
      a.activeYaw = a.heading;
      if(getGRedAirShotState(a)?.partMode || (runtime.borgId === "pl0106" && a.actionIndex === 0 && (a.variantIndex === 1 || a.variantIndex === 3)))
        a.lockYaw = Math.hypot(runtime.vel.x,runtime.vel.z)>0 ? radToBam(Math.atan2(runtime.vel.x,runtime.vel.z)) : a.heading;
      const { hSpeed, yVel } = decomposeVel(runtime.vel);
      a.hSpeed = hSpeed;
      a.yVel = yVel;
    }
    a.dt = 1;
    a.timescale = 1;
    a.tierScale = 1;
    a.maxFall = -9999;
    (a as RomActor & { grounded?: boolean }).grounded = runtime.grounded;
    (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = null;
    (a as RomActor & { targetDistance760?: number }).targetDistance760 = 0;
    // Source +c8/+cc freezes attack identity, not target position. Only these
    // verified source actions consume the global pre-movement +518 refresh.
    // Generic aimOrigin518 above retains its existing shooter-root meaning.
    const captured = this.specialActive && (a.actionIndex === 2 || (runtime.borgId === "pl0106" && a.actionIndex === 0))
      ? (isArrowNinja(runtime.borgId) ? runtime.arrowAttack : isRevolver(runtime.borgId) ? runtime.revolverAttack
        : runtime.borgId === "pl0104" ? runtime.beamAim
        : runtime.borgId === "pl0106" ? runtime.timeBomberSavedAim
        : runtime.borgId === "pl0102" ? runtime.gatlingSavedAim
        : runtime.borgId === "pl0101" ? runtime.poweredNormalAim : undefined)
      : undefined;
    const nurse = this.specialActive && a.actionIndex === 2 ? getNurseXState(a) : undefined;
    const neo = this.specialActive && a.actionIndex === 1 ? getNeoGredMeleeState(a) : undefined;
    const airMelee=this.specialActive && a.actionIndex===1?getGRedAirMeleeState(a):undefined;
    const airShot=getGRedAirShotState(a);
    const shot=getGRedShotState(a);
    const charge=getGRedChargeState(a);
    const blackCharge=getGBlackChargeState(a);
    const crash = getGRedCrashState(a);
    const ninja=getNinjaXState(a),teleport=getTeleportXState(a);
    const candidate = teleport?all.find(target=>target.uid===teleport.targetUid):ninja?all.find(target=>target.uid===ninja.targetUid): airShot ? all.find(target=>target.uid===airShot.targetUid) : shot ? all.find(target=>target.uid===shot.targetUid) : blackCharge ? all.find(target=>target.uid===blackCharge.targetUid) : charge ? all.find(target=>target.uid===charge.targetUid) : crash ? all.find(target=>target.uid===crash.targetUid)
      : airMelee ? all.find(target=>target.uid===airMelee.targetUid)
      : neo ? all.find(target => target.uid === neo.targetUid)
      : nurse ? all.find(target => target.uid === nurse.targetUid)
      : captured ? all.find(target => target.uid === captured.targetUid) : activeTarget;
    if (nurse && (!candidate || !candidate.alive || candidate.hp <= 0 ||
        candidate.state === "death" || (candidate.targetEligibility83 ?? 0) !== 0)) nurse.targetUid = null;
    const sourceAdmission = this.specialActive && this.specialKind === "x" &&
      ((runtime.command?.actionIndex ?? 2) === 2 || (runtime.borgId === "pl0106" && runtime.command?.actionIndex === 0)) &&
      (isArrowNinja(runtime.borgId) || isRevolver(runtime.borgId) || runtime.borgId === "pl0102" || runtime.borgId === "pl0106" || runtime.borgId === "pl0101");
    // All other families retain their existing current-root aiming behavior.
    const sourceTarget = teleport ? actorAimTarget(candidate) : ninja ? (ninja.noTargetLatch541===0?actorAimTarget(candidate):null) : airShot ? actorAimTarget(candidate) : shot ? actorAimTarget(candidate) : blackCharge ? actorAimTarget(candidate) : charge ? (!charge.captureBlocked6b8?actorAimTarget(candidate):null) : crash ? (crash.noTargetLatch541===0 ? actorAimTarget(candidate) : null)
      : airMelee ? (airMelee.noTargetLatch541===0?actorAimTarget(candidate):null)
      : neo ? (neo.noTargetLatch541 === 0 ? actorAimTarget(candidate) : null)
      : nurse ? (nurse.targetUid ? actorAimTarget(candidate) : null) : captured || sourceAdmission ? actorAimTarget(candidate) : candidate;
    if(teleport){teleport.capturedTargetCc=!!sourceTarget;if(!sourceTarget)teleport.targetUid=null;else Object.assign(teleport.target518,sourceTarget.pos);}
    if(ninja){if(!sourceTarget)ninja.targetUid=null;else ninja.targetPoint={...sourceTarget.pos};}
    if(airShot){
      if(!sourceTarget)airShot.targetUid=null;
      airShot.targetEligible=!!sourceTarget&&((candidate?.targetEligibility83??0)!==0||
        (((candidate?.targetVisibilityMask5e6??0)&a.visibilityBit)!==0));
    }
    if(shot&&!sourceTarget)shot.targetUid=null;
    if(blackCharge&&!sourceTarget)blackCharge.targetUid=null;
    if(charge){
      if(!sourceTarget)charge.targetUid=null;
      if(runtime.beamAim){
        runtime.beamAim.targetUid=charge.targetUid;
        Object.assign(charge.aimTarget524,runtime.beamAim.pos);
      }
    }
    if (neo && !sourceTarget) neo.targetUid = null;
    if (crash && !sourceTarget) crash.targetUid=null;
    if(airMelee && !sourceTarget)airMelee.targetUid=null;
    const targetPos = runtime.borgId === "pl0104" && captured
      ? captured.pos : sourceTarget ? captured?.pos ?? sourceTarget.pos : null;
    if (captured && !sourceTarget) captured.targetUid = null;
    if (targetPos) {
      const target = { pos: targetPos };
      (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = {
        x: target.pos.x, y: target.pos.y, z: target.pos.z,
      };
      (a as RomActor & { targetDistance760?: number }).targetDistance760 = Math.hypot(
        target.pos.x - runtime.pos.x,
        target.pos.y - runtime.pos.y,
        target.pos.z - runtime.pos.z,
      ) / (neo ? a.modelScale : 1);
      // zz_006d0dc_ -> FUN_800669d0 consumes the captured target bearing as BAM16.
      // Height participates in pitch seeking, while yaw is atan2(horizontal x,z).
      const targetYaw = radToBam(Math.atan2(target.pos.x - runtime.pos.x, target.pos.z - runtime.pos.z));
      // Source recover owns +5ae (the backward recoil bearing). A global
      // +518 refresh must not overwrite it after phase1 releases the shots.
      const sourceRecover = captured && (a.fbPhaseSlots[0] ?? 0) >= 2;
      if (!sourceRecover && !teleport && !ninja && !neo && !crash && !airMelee && !charge && !blackCharge && !shot && !airShot) {
        const timeBomberKeepsMotionYaw = runtime.borgId === "pl0106" && a.actionIndex === 0 && (a.variantIndex === 1 || a.variantIndex === 3 || a.variantIndex === 4);
        if(!timeBomberKeepsMotionYaw)a.lockYaw = targetYaw;
        a.activeYaw = targetYaw;
      }
    }
  }

  /** Mirror the live host buttons into the decoded actor status words consumed by
   * continuation/exit callbacks (+0x5bc bit 0x200 and +0x5d8 high nibble). */
  private syncActionInput(input: PlayerInput | null, fallbackHeld = false): void {
    const held = input ? input.attack || input.special : fallbackHeld;
    const scratch = this.actor as RomActor & {
      inputFlags5d4?: number;
      inputFlags5d8?: number;
      statusWord5bc?: number;
      bRetapInput?: boolean;
      streamTickEnabled?: boolean;
    };
    scratch.inputFlags5d4 = held ? 0x20 : 0;
    scratch.inputFlags5d8 = held ? 0x10 : 0;
    scratch.statusWord5bc = held ? 0x200 : 0;
    scratch.bRetapInput = input?.attack ?? fallbackHeld;
    scratch.streamTickEnabled = true;
    if (this.runtime?.borgId === "pl0104") {
      (this.actor as RomActor & { inputEdges5bc?: number }).inputEdges5bc = this.runtime.beamInput?.edges ?? 0;
    }
    const charge=getGRedChargeState(this.actor);
    if(charge)charge.freshInput5bc=this.runtime?.beamInput?.edges??0;
    const shot=getGRedAirShotState(this.actor)??getGRedShotState(this.actor);
    if(shot){
      // Buffered source descriptors: B edge lasts one update; A edge lasts16.
      shot.input5d4=(this.neoBPressed?0x20:0)|(this.shotAActive?1:0);
      // Browser stick threshold is a bounded adapter for68980, not its full
      // directional latch/repeat buffer. B-held must never set this word.
      shot.input5d8=this.shotDirectionActive?0x10:0;
      scratch.inputFlags5d4=shot.input5d4;scratch.inputFlags5d8=shot.input5d8;
    }
    this.actor.inputEdge5d4 = input?.attack || input?.special ? 0x41 : 0;
    this.actor.inputHeld5d8 = held ? 0x10 : 0;
    if (this.runtime?.borgId === "pl0106" && this.actor.actionIndex === 0) {
      // Source5d8 high nibble is stick direction, never X-held.
      this.actor.inputHeld5d8 = input && Math.max(Math.abs(input.moveX),Math.abs(input.moveZ)) >= 0x34/127 ? 0x10 : 0;
      this.actor.inputEdge5d4 = 0; // No speculative mapping of unrelated X/B buttons.
    }
    if(getNinjaXState(this.actor))this.actor.inputHeld5d8=input&&Math.max(Math.abs(input.moveX),Math.abs(input.moveZ))>=0x34/127?0x10:0;
    this.actor.statusWord5b4 = held ? 0x200 : 0;
    if (!getTeleportXState(this.actor) && !getNinjaXState(this.actor) && !getGRedAirShotState(this.actor) && !getGRedShotState(this.actor) && !getGBlackChargeState(this.actor) && !getGRedChargeState(this.actor) && !getGRedCrashState(this.actor) && !getGRedAirMeleeState(this.actor) && !getNeoGredMeleeState(this.actor) && (this.runtime?.borgId !== "pl0106" || this.actor.actionIndex !== 0))
      this.actor.streamHold1b03 = 0;
    if (getNeoGredMeleeState(this.actor) || getGRedAirMeleeState(this.actor)) {
      // Descriptor802d3904 count1/flags0/duration1/mask0200 consumes B's
      // rising edge, emitting5d4bit40 in this same update. Holding never retaps.
      this.actor.inputEdge5d4 = this.neoBPressed ? 0x40 : 0;
      scratch.bRetapInput = this.neoBPressed;
    }
  }

  /** Copy RomActor → BorgRuntime (after the ROM step). */
  syncOut(runtime: BorgRuntime): void {
    const a = this.actor;
    const charge=getGRedChargeState(a),blackCharge=getGBlackChargeState(a);
    if(runtime.borgId==='pl062a'){
      const target=(a as RomActor&{lockTarget?:Vec3|null}).lockTarget;
      const retained=runtime.gblackChargeOwner?.target518;
      runtime.gblackChargeOwner={dt:a.dt,modelScale:a.modelScale,collisionScale:a.collisionScale??a.modelScale,
        controlWord:a.controlWord,...(target?{target518:{...target}}:retained?{target518:{...retained}}:{})};
    }
    if(charge)runtime.beamOwner={dt:a.dt,state:charge.chargeState6f7,pos:{...a.pos},yaw:bamToRad(a.heading),pitch:bamToRad(a.bodyPitch),scale:a.modelScale*a.sizeScale};
    if (runtime.borgId === "pl0104") {
      const beam = a as RomActor & { gmBeamState6f7?: number };
      runtime.beamOwner = { dt: a.dt, state: beam.gmBeamState6f7 ?? 0, pos: { ...a.pos },
        yaw: bamToRad(a.heading), pitch: bamToRad(a.bodyPitch), scale: a.modelScale * a.sizeScale };
    }
    runtime.pos.x = a.pos.x;
    runtime.pos.y = a.pos.y;
    runtime.pos.z = a.pos.z;
    const airShot=getGRedAirShotState(a),preserveLower=airShot?.partMode&&!airShot.physicsAdvanced;
    if(!preserveLower)runtime.rotY = bamToRad(a.heading);
    const crash=getGRedCrashState(a),ninja=getNinjaXState(a),teleport=getTeleportXState(a);
    if(teleport){runtime.sourceDefenseDisabled=(teleport.flags272&2)!==0;runtime.sourceHidden=teleport.visibility82===0;}
    const airMelee=getGRedAirMeleeState(a);
    const vel = recomposeVel(a.hSpeed, a.yVel, airShot || ninja || blackCharge || charge || crash || airMelee || (runtime.borgId === "pl0106" && a.actionIndex === 0 && a.variantIndex === 4) ? a.lockYaw : a.activeYaw);
    if(!preserveLower){runtime.vel.x = vel.x;runtime.vel.y = vel.y;runtime.vel.z = vel.z;}
    if(teleport||ninja||(airShot&&!preserveLower)||blackCharge || charge || crash || airMelee)runtime.grounded=(a as RomActor&{grounded?:boolean}).grounded===true;
    const sourceStream=teleport?.stream ?? ninja?.stream ?? airShot?.stream ?? getGRedShotState(a)?.stream ?? blackCharge?.stream ?? charge?.stream ?? crash?.stream ?? airMelee?.stream ?? getNeoGredMeleeState(a)?.stream;
    if(sourceStream && runtime.sourceAnimSample)
      runtime.sourceAnimSample={serial:runtime.sourceAnimSample.serial,frame:sourceStream.frame};
    const nurse = this.specialActive ? getNurseXState(a) : undefined;
    if (nurse && !nurse.close && (a.fbPhaseSlots[0] ?? 0) >= 2 && (a.fbPhaseSlots[0] ?? 0) < 7) {
      Object.assign(runtime.vel, a.motion);
    }
    const previousSerial = runtime.romAfterimage?.serial ?? 0;
    if (a.afterimageSerial !== previousSerial) {
      const baseScale = a.modelScale * a.sizeScale;
      const ownerYaw = bamToRad(a.lockYaw);
      // FUN_800b2924: subtract local-forward * (FLOAT_80438398=50 * owner scales).
      const pos = {
        x: a.afterimageSamplePos.x - Math.sin(ownerYaw) * 50 * baseScale,
        y: a.afterimageSamplePos.y,
        z: a.afterimageSamplePos.z - Math.cos(ownerYaw) * 50 * baseScale,
      };
      // zz_00055fc_ << 8: the ROM 8-bit RNG's byte becomes the effect's BAM16 yaw. prng.ts's
      // stepRng8() IS the 1:1 port of zz_00055fc_ @0x800055fc (chunk_0000.c:373-386), so it is
      // the value the ROM actually produces here — Math.random() was a stand-in for a function
      // the port already had, and it made the afterimage effect replay-nondeterministic.
      const effectYaw = (stepRng8() & 0xff) * (TAU / 256);
      runtime.romAfterimage = {
        serial: a.afterimageSerial,
        pos,
        effectYaw,
        baseScale,
        effectId: 69,
        lifetimeFrames: 20,
        renderState: 0x1e,
      };
    }
  }

  /** Called from combat.ts's X-special branch. Returns true if the ROM family handled
   *  the press (caller skips spawnSpecialProjectiles). Arms the multi-frame phase
   *  machine; subsequent `tick` calls advance it. */
  tryStartXSpecial(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean {
    if (this.specialActive) return false;
    if(runtime.borgId === "pl0106" && this.timeBomberLandingCooldown && this.actor.stateTimer>0)return false;
    if (runtime.borgId === "pl0106") {
      const walking = runtime.timeBomberInput?.walking === true && runtime.grounded &&
        runtime.state === "move" && this.actor.bodyPitch === 0 && runtime.command?.subtype === 1;
      const neutral = runtime.timeBomberInput?.neutral !== false &&
        (runtime.grounded ? runtime.command?.variantIndex === 0 : runtime.command?.variantIndex === 3);
      if (runtime.command?.type !== 2 || runtime.command.actionIndex !== 0 ||
          (!walking && !neutral) || (walking && runtime.command.variantIndex !== 0 && runtime.command.variantIndex !== 1)) return false;
    }
    if (isNurseX(runtime.borgId)) {
      const target = activeSourceTarget(runtime, all);
      if (!canStartNurseX(runtime, target)) return false;
      prepareNurseX(this.actor, target!.uid, isCloseNurseX(runtime, target!));
    }
    // Impotence latch (see the field's doc): this borg's ROM X already proved to be a
    // no-payload pantomime — hand the press to the generic startSpecialAttack path.
    if (this.xImpotent && !isSourceTeleportX(runtime.borgId) && !isSourceNinjaX(runtime.borgId) && !(runtime.borgId === "pl0106" && runtime.command?.actionIndex === 0)) return false;
    const actionIndex = runtime.command?.actionIndex ?? 2;
    const variantIndex = runtime.command?.variantIndex ?? 0;
    // Original80365830 maps both v0 and v4 to18e838. Admit only the proven
    // neutral ground row or airborne subtype4 row, not contextual variants1..3.
    const admittedGRedCrash = (runtime.borgId==='pl0615'||runtime.borgId==='pl0629'||runtime.borgId==='pl062a') &&
      runtime.command?.exact===true && runtime.command.type===2 && actionIndex===2 &&
      (runtime.grounded ? variantIndex===0 : variantIndex===4 && runtime.command.subtype===4);
    const admittedNinja=isSourceNinjaX(runtime.borgId)&&runtime.command?.exact===true&&runtime.command.type===2&&actionIndex===2&&
      (runtime.grounded?variantIndex===0:variantIndex===4&&runtime.command.subtype===4);
    const admittedTeleport=isSourceTeleportX(runtime.borgId)&&runtime.command?.exact===true&&runtime.command.type===2&&actionIndex===2&&
      (runtime.grounded?variantIndex===0:variantIndex===4&&runtime.command.subtype===4);
    // Only the audited ordinary rows are source-owned. Charged release remains a
    // separately labeled generic fallback; no context variant is silently enabled.
    if(isSourceTeleportX(runtime.borgId)&&!admittedTeleport)return false;
    this.runtime = runtime;
    delete runtime.sourceAnimSample;
    this.armedHits = [];
    this.specialKind = "x";
    this.mineMeleeOpenerStream = false;
    this.specialHadEffect = false;
    this.sourceXResourceDenied = false;
    this.specialMotionAccum = 0;
    this.specialStartPos = { x: runtime.pos.x, y: runtime.pos.y, z: runtime.pos.z };
    this.streamFrame = 0;
    // Load pre-decoded stream events for the choreography (anim + hitbox arming).
    this.streamEvents = null;
    this.streamSchedules = [];
    // Determine the special's duration from the decoded stream (default 30 frames).
    clearGRedShot(this.actor);clearGRedAirShot(this.actor);this.gredAirShotLocomotion=null;
    this.specialMaxFrames = runtime.borgId === "pl0106" && actionIndex === 0 ? 120 : (runtime.borgId === "pl0104" || isNurseX(runtime.borgId)) && actionIndex === 2 ? 240 : 30;
    // Fire frame-0 events immediately (armHit + playAnim).
    this.dispatchEvent(0);
    this.streamFrame = 1;
    // The ROM-owned special path owns this borg for the move's duration (tick()
    // returns true → battle.ts skips stepAttacks/stepMovement, which are the
    // normal state/anim setters). So the bridge MUST set runtime.state/anim here
    // or the renderer's slotForBorg keys off stale state and never plays the
    // attack clip. X-special → state "special" (slotForBorg returns "special").
    this.timeBomberLocomotion = runtime.borgId === "pl0106" && (variantIndex === 1 || variantIndex === 3)
      ? {state:runtime.state,anim:runtime.anim,stateTime:runtime.stateTime} : null;
    runtime.state = "special";
    runtime.anim = "special";
    this.romOwnedSpecial = true;
    this.specialActive = true;
    this.actor.controlWord = (this.actor.controlWord & ~0x3) | 0x1;
    clearTeleportX(this.actor,runtime);
    clearNinjaX(this.actor);
    if(admittedTeleport)this.actor.controlWord=runtime.grounded?this.actor.controlWord&~0x40:this.actor.controlWord|0x40;
    if(admittedNinja)this.actor.controlWord=runtime.grounded?this.actor.controlWord&~0x40:this.actor.controlWord|0x40;
    if (runtime.borgId === "pl0104") delete runtime.beamAim;
    if (isArrowNinja(runtime.borgId)) {
      this.actor.controlWord = runtime.grounded ? this.actor.controlWord & ~0x40 : this.actor.controlWord | 0x40;
      delete runtime.arrowAttack;
    }
    if (isRevolver(runtime.borgId)) {
      this.actor.controlWord = runtime.grounded ? this.actor.controlWord & ~0x40 : this.actor.controlWord | 0x40;
      // Discard the previous action's pointer before admission sync selects the
      // currently active target. Subsequent syncs use this new captured identity.
      delete runtime.revolverAttack;
    } else if (runtime.borgId === "pl0106") {
      this.actor.controlWord = runtime.grounded ? this.actor.controlWord & ~0x40 : this.actor.controlWord | 0x40;
      delete runtime.timeBomberSavedAim;
      if(runtime.timeBomberInput?.walking) {
        this.timeBomberMovementControl=this.actor.controlWord&0x30;
        this.actor.controlWord=(this.actor.controlWord&~0x30)|0x10;
      }
    }
    else if (runtime.borgId === "pl0102") delete runtime.gatlingSavedAim;
    else if (runtime.borgId === "pl0101" && actionIndex === 2) delete runtime.poweredNormalAim;
    this.syncActionInput(null, true);
    // For G RED family (custom handler): also run the ROM physics for the launch arc.
    // The custom handler sets velocities that stepMovement will integrate.
    if (this.actor.rootAction) {
      const preX = runtime.pos.x;
      const preZ = runtime.pos.z;
      this.syncIn(runtime, all);
      if (isArrowNinja(runtime.borgId) && actionIndex === 2) captureArrowAttack(runtime,this.actor,all);
      if (runtime.borgId === "pl0104" && actionIndex === 2) captureBeamAim(runtime, this.actor, all);
      if (runtime.borgId === "pl0106" && actionIndex === 0) captureTimeBomberAim(runtime,this.actor,all);
      if (runtime.borgId === "pl0102" && actionIndex === 2) captureGatlingAim(runtime,this.actor,all);
      if (runtime.borgId === "pl0101" && actionIndex === 2) capturePoweredNormalAim(runtime,this.actor,all);
      if (isRevolver(runtime.borgId) && actionIndex === 2) captureRevolverAttack(runtime,this.actor,all);
      // Arrow: ground802d4668=[44,3,2,0], air802d46a8=[45,3,2,4].
      // Nurse air802d6908/802d6910=[45,3,2,1]; G RED family80365de0=[45,3,2,4].
      const airCue = (isNurseX(runtime.borgId) && variantIndex === 1) ||
        ((isArrowNinja(runtime.borgId) || isRevolver(runtime.borgId)) && variantIndex === 4) ||
        (runtime.borgId === "pl0104" && (variantIndex === 3 || variantIndex === 4)) ||
        (admittedGRedCrash && variantIndex===4) || (admittedNinja&&variantIndex===4) || (admittedTeleport&&variantIndex===4);
      const timeBomberPart = runtime.borgId === "pl0106" && actionIndex === 0 && (variantIndex === 1 || variantIndex === 3);
      const cueId = airCue || (timeBomberPart && variantIndex === 3) ? 45 : 44;
      if(admittedGRedCrash||admittedNinja||admittedTeleport){
        // Source X selection sets585=2 before6a104 snapshots584. Its range
        // row is therefore138/144/150 indexed by the real command snapshot.
        this.actor.cmdButton=2;this.actor.cmdSubtype=runtime.command?.subtype??0;
        this.actor.cmdChargedRanged=0;
      }
      dispatchCommandRecord(this.actor, { cueId, stateMode: timeBomberPart ? 1 : 3, actionIndex, variantIndex });
      if(admittedTeleport){
        const target=actorAimTarget(activeSourceTarget(runtime,all));
        prepareTeleportX(this.actor,runtime,target?.uid??null,target?.pos??null);
        prepareGredRangedEntryVisibility(this.actor);this.flushVisibilityState(this.actor);
        this.syncIn(runtime,all);this.specialHadEffect=true;
        this.specialMaxFrames=90; // Host safety ceiling, not an original action timer.
      }
      if(admittedNinja){
        const target=actorAimTarget(activeSourceTarget(runtime,all));
        prepareNinjaX(this.actor,target?.uid??null,target?.pos??null);
        // Source command admission captures identity and updates visibility before
        // the family stream. Reuse the proven6a104 writer, never a spawn-time target.
        prepareGredRangedEntryVisibility(this.actor);this.flushVisibilityState(this.actor);
        this.syncIn(runtime,all);
      }
      clearGRedCrash(this.actor);
      if(admittedGRedCrash){
        const crash=prepareGRedCrash(this.actor,activeSourceTarget(runtime,all)?.uid??null);
        crash.onRefreshTarget=()=>{
          const target=actorAimTarget(activeSourceTarget(runtime,this.arrowRoster));
          crash.targetUid=target?.uid??null;
          (this.actor as RomActor&{lockTarget?:Vec3|null}).lockTarget=target?.pos??null;
          this.actor.visibilityTarget=this.visibilityBindings.find(b=>b.runtime.uid===crash.targetUid)?.state??null;
        };
        this.syncIn(runtime,all);
      }
      if(timeBomberPart){
        const velocity=decomposeVel(runtime.vel);
        this.actor.hSpeed=velocity.hSpeed;this.actor.yVel=velocity.yVel;
        this.actor.lockYaw=Math.hypot(runtime.vel.x,runtime.vel.z)>0?radToBam(Math.atan2(runtime.vel.x,runtime.vel.z)):this.actor.heading;
        this.actor.rootAction?.(this.actor);
      } else {stepRomActor(this.actor, this.tables, this.ctx);this.syncOut(runtime);}
      // The shared-X movement carry (phase 0's pos += (pos−olderOwnPos)×0.95) can
      // cross the arena walls near stage edges — the ROM's own step runs the
      // ground/wall collide (zz_00677b0_) right after; the port applies the host's
      // bounds clamp + off-mesh revert here (same policy tick() documents).
      if (!timeBomberPart && this.bounds) {
        runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
        runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
      }
      if (!timeBomberPart && this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
        runtime.pos.x = preX;
        runtime.pos.z = preZ;
      }
      // Y-guard: a family phase-0 reposition/impulse must never leave the borg BELOW
      // the floor surface (the ROM's own step runs zz_00677b0_ ground collide right
      // after; sword-knight's X dove through the mesh without this).
      if (!timeBomberPart && !getGRedCrashState(this.actor) && !getNinjaXState(this.actor) && !getTeleportXState(this.actor) && this.groundClamp) {
        const clamped = this.groundClamp(runtime.pos, runtime.vel.y);
        if (clamped.y > runtime.pos.y) {
          runtime.pos.y = clamped.y;
          runtime.vel.y = Math.max(0, runtime.vel.y);
        }
      }
    }
    const handled = this.actor.fbPhaseSlots.some((phase) => phase !== 0)
      || this.actor.parts.some((part) => part.streamPtr >= 0)
      || this.streamSchedules.length > 0;
    if (!handled) {
      this.restoreTimeBomberMovementControl();
      this.specialActive = false;
      this.romOwnedSpecial = false;
      this.actor.controlWord &= ~0x3;
      this.streamSchedules = [];
      clearGRedCrash(this.actor);
      return false;
    }
    runtime.cooldowns["romSpecialActive"] = 1;
    return true;
  }

  /** Called from combat.ts's B-attack branch (before startShotAttack/startMeleeAttack).
   *  Returns true if the ROM family's B-charge phase machine (zz_0179814_) handled the
   *  press — the caller skips the generic melee/shot path. Only intercepts when the borg's
   *  family explicitly wires a B-charge handler (RomActor.hasBCharge). Subsequent `tick`
   *  calls advance the 4-phase machine each frame (ROM owns motion until recovery). */
  tryStartBAttack(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean {
    if (this.specialActive) return false;
    if (!this.actor.hasBCharge) return false;
    if (!runtime.command?.exact || runtime.command.actionIndex === null) return false;
    const actionIndex = runtime.command.actionIndex;
    const variantIndex = runtime.command?.variantIndex ?? 0;
    const admittedAirShot=(runtime.borgId==='pl0615'||runtime.borgId==='pl0629'||runtime.borgId==='pl062a')&&!runtime.grounded&&runtime.command.button==='B Shot'&&runtime.command.subtype===4&&actionIndex===0&&variantIndex===3;
    const admittedShot=(runtime.borgId==='pl0615'||runtime.borgId==='pl0629'||runtime.borgId==='pl062a')&&runtime.grounded&&runtime.command.button==='B Shot'&&runtime.command.subtype===0&&actionIndex===0&&variantIndex===0;
    const admittedBlackCharge=runtime.borgId==='pl062a'&&runtime.command.type===3&&runtime.command.subtype===5&&actionIndex===3&&variantIndex===0;
    const admittedCharge=(runtime.borgId==='pl0615'||runtime.borgId==='pl0629') && runtime.command.type===3 && runtime.command.subtype===5 && actionIndex===3 && variantIndex===0;
    const admittedAirMelee=(runtime.borgId==='pl0615'||runtime.borgId==='pl062a'||runtime.borgId==='pl0629') && !runtime.grounded && runtime.command.type===1 &&
      runtime.command.subtype===4 && actionIndex===1 && variantIndex===4;
    this.runtime = runtime;
    this.gredAirShotLocomotion=admittedAirShot?{state:runtime.state,anim:runtime.anim,stateTime:runtime.stateTime}:null;
    delete runtime.sourceAnimSample;
    this.romOwnedSpecial = true;
    this.armedHits = [];
    this.specialKind = "b";
    this.mineMeleeOpenerStream = false;
    this.specialHadEffect = false;
    this.sourceXResourceDenied = false;
    this.specialMotionAccum = 0;
    this.streamFrame = 0;
    // Load pre-decoded stream events for the group-4 charge choreography (anim + fireChild).
    this.streamEvents = null;
    this.streamSchedules = [];
    this.specialMaxFrames = 90; // generous ceiling; the phase machine's exit clears it sooner
    // Fire frame-0 events immediately (armHit + playAnim).
    this.dispatchEvent(0);
    this.streamFrame = 1;
    runtime.cooldowns["romSpecialActive"] = 1;
    // B-charge ROM-owned path: set state "attack" + anim "charge_shot" so
    // slotForBorg selects the charge slot AND playSlot routes through
    // loadClipByStreamRef (the charge_shot slot is in the stream-ref allow-list).
    runtime.state = "attack";
    runtime.anim = "charge_shot";
    this.specialActive = true;
    this.syncActionInput(null, true);
    // Arm the action-mode bits so the phase-3 exit (controlWord &= ~0x3) can signal
    // completion. The ROM sets these on entering attack state (cue 44 → state 61).
    this.actor.controlWord = (this.actor.controlWord & ~0x3) | 0x1;
    // Run phase 0 immediately (same pattern as tryStartXSpecial): syncIn → dispatch the
    // command record (actionIndex 3 = B-charge) → stepRomActor (runs rootAction → phase 0)
    // → syncOut → bounds/ground clamps.
    const preX = runtime.pos.x;
    const preZ = runtime.pos.z;
    this.syncIn(runtime, all);
    if(admittedAirShot){
      this.actor.cmdButton=0;this.actor.cmdSubtype=4;this.actor.cmdChargedRanged=0;
      // Browser airborne selection uses subtype4, but original ordinary jump
      // posture is40 (subtype3, the same45/1/0/3 row). Do not synthesize the
      // distinct source locomotion80 state, or stale run/step10/20 controls.
      this.actor.controlWord=(this.actor.controlWord&~0xb0)|0x40;
    }
    if(admittedShot){
      this.actor.cmdButton=0;this.actor.cmdSubtype=0;this.actor.cmdChargedRanged=0;
      // Host posture reconciliation only: source69ea4 would select subtype3
      // with control40, never this admitted grounded neutral row. Do not clear
      // the bit in18d350 or on later ticks, where its branch remains meaningful.
      this.actor.controlWord&=~0x40;
    }
    if(admittedCharge||admittedBlackCharge){this.actor.cmdButton=3;this.actor.cmdSubtype=5;this.actor.cmdChargedRanged=1;runtime.cooldowns["chargeFrames"]=0;}
    if (admittedAirMelee || ((runtime.borgId === "pl0615" || runtime.borgId === "pl0629" || runtime.borgId === "pl062a") && runtime.grounded && actionIndex === 1 && variantIndex === 0)) {
      // Source contextual B has already selected585=1/586=subtype before6a104
      // snapshots584. Do not silently use the spawn-default row0 lunge range.
      this.actor.cmdButton=1;this.actor.cmdSubtype=runtime.command.subtype ?? 0;
      this.actor.cmdChargedRanged=0;
    }
    if((runtime.borgId==='pl0615'||runtime.borgId==='pl0629'||runtime.borgId==='pl062a')&&actionIndex===0&&(variantIndex===0||admittedAirShot)){
      // Source6a104 populates target5e6 before cue/ammo. The generic command
      // dispatcher omits this writer; keep this bind limited to ordinary shots.
      prepareGredRangedEntryVisibility(this.actor,runtime.sourceGredRangedCaptureBlocked6b8??false);
      this.flushVisibilityState(this.actor);
    }
    // Original G RED-family close-air row80365dc8=[45,3,1,4]. Other B routes unchanged.
    dispatchCommandRecord(this.actor, { cueId: admittedAirMelee||admittedAirShot?45:44, stateMode: admittedAirShot?1:3, actionIndex, variantIndex });
    clearNeoGredMelee(this.actor);
    clearGRedAirMelee(this.actor);
    clearGRedCharge(this.actor);
    clearGBlackCharge(this.actor);
    clearGRedShot(this.actor);
    clearGRedAirShot(this.actor);
    if(admittedAirShot){
      const air=prepareGRedAirShot(this.actor,runtime.sourceGredRangedCaptureBlocked6b8?null:activeSourceTarget(runtime,all)?.uid??null);
      air.onReadAmmo=()=>runtime.weaponCells?.[0]?.cur??runtime.ammo;
      air.onCaptureTarget=()=>{
        air.targetUid=runtime.sourceGredRangedCaptureBlocked6b8?null:activeSourceTarget(runtime,all)?.uid??null;
        this.syncIn(runtime,all);
        if(runtime.sourceGredRangedCaptureBlocked6b8)this.actor.visibilityTarget=null;
        refreshTargetVisibility(this.actor);this.flushVisibilityState(this.actor);
      };
      air.onRedispatch=subtype=>{
        air.targetUid=runtime.sourceGredRangedCaptureBlocked6b8?null:activeSourceTarget(runtime,all)?.uid??null;
        this.syncIn(runtime,all);
        prepareGredRangedEntryVisibility(this.actor,runtime.sourceGredRangedCaptureBlocked6b8??false);
        this.flushVisibilityState(this.actor);
        this.actor.cmdButton=0;this.actor.cmdSubtype=subtype;this.actor.cmdChargedRanged=2;
        dispatchCommandRecord(this.actor,{cueId:subtype===4?45:44,stateMode:3,actionIndex:0,variantIndex:subtype===4?4:0});
        if(subtype===4){air.lowerStream=null;return;}
        clearGRedAirShot(this.actor);this.gredAirShotLocomotion=null;
        const ground=prepareGRedShot(this.actor,air.targetUid,false);
        ground.onReadAmmo=air.onReadAmmo;
        ground.onCaptureTarget=()=>{
          ground.targetUid=runtime.sourceGredRangedCaptureBlocked6b8?null:activeSourceTarget(runtime,all)?.uid??null;
          this.syncIn(runtime,all);
          if(runtime.sourceGredRangedCaptureBlocked6b8)this.actor.visibilityTarget=null;
          refreshTargetVisibility(this.actor);this.flushVisibilityState(this.actor);
        };
      };
      this.syncIn(runtime,all);this.syncActionInput(null,false);
    }
    if(admittedShot){
      const shot=prepareGRedShot(this.actor,runtime.sourceGredRangedCaptureBlocked6b8?null:activeSourceTarget(runtime,all)?.uid??null);
      shot.onReadAmmo=()=>runtime.weaponCells?.[0]?.cur??runtime.ammo;
      shot.onCaptureTarget=()=>{
        shot.targetUid=runtime.sourceGredRangedCaptureBlocked6b8?null:activeSourceTarget(runtime,all)?.uid??null;
        this.syncIn(runtime,all);
        if(runtime.sourceGredRangedCaptureBlocked6b8)this.actor.visibilityTarget=null;
        refreshTargetVisibility(this.actor);this.flushVisibilityState(this.actor);
      };
      this.syncIn(runtime,all);this.syncActionInput(null,false);
    }
    if(admittedBlackCharge){prepareGBlackCharge(this.actor,activeSourceTarget(runtime,all)?.uid??null);this.syncIn(runtime,all);this.syncActionInput(null,false);}
    if(admittedCharge){
      // Source6bda8 captures current selection;524 remains a saved point.
      const target=actorAimTarget(activeSourceTarget(runtime,all));
      const oldPoint=runtime.beamAim?.pos;
      captureBeamAim(runtime,this.actor,all);
      if(!target && oldPoint && runtime.beamAim)runtime.beamAim.pos={...oldPoint};
      prepareGRedCharge(this.actor,target?.uid??null,runtime.beamAim!.pos);
      this.syncIn(runtime,all);this.syncActionInput(null,false);
    }
    if(admittedAirMelee){
      prepareGRedAirMelee(this.actor,activeSourceTarget(runtime,all)?.uid??null);
      this.syncIn(runtime,all);this.syncActionInput(null,true);
    }
    if ((runtime.borgId === "pl0615" || runtime.borgId === "pl0629" || runtime.borgId === "pl062a") && runtime.grounded && actionIndex === 1 && variantIndex === 0) {
      const neo = prepareNeoGredMelee(this.actor, activeSourceTarget(runtime,all)?.uid ?? null);
      neo.onRedispatchTarget = () => {
        neo.targetUid = activeSourceTarget(runtime,all)?.uid ?? null;
        this.syncIn(runtime,all);
      };
      this.syncIn(runtime,all);
      this.syncActionInput(null,true);
    }
    if(admittedAirShot)this.actor.rootAction?.(this.actor);else stepRomActor(this.actor, this.tables, this.ctx);
    this.syncOut(runtime);
    if (this.bounds) {
      runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
      runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
    }
    if (this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
      runtime.pos.x = preX;
      runtime.pos.z = preZ;
    }
    if (!getGBlackChargeState(this.actor) && !getGRedChargeState(this.actor) && !getGRedAirMeleeState(this.actor) && !getNinjaXState(this.actor) && this.groundClamp) {
      const clamped = this.groundClamp(runtime.pos, runtime.vel.y);
      if (clamped.y > runtime.pos.y) {
        runtime.pos.y = clamped.y;
        runtime.vel.y = Math.max(0, runtime.vel.y);
      }
    }
    const handled = this.actor.fbPhaseSlots.some((phase) => phase !== 0)
      || this.actor.parts.some((part) => part.streamPtr >= 0)
      || this.streamSchedules.length > 0;
    if (!handled) {
      this.specialActive = false;
      this.romOwnedSpecial = false;
      this.actor.controlWord &= ~0x3;
      this.streamSchedules = [];
      runtime.cooldowns["romSpecialActive"] = 0;
      return false;
    }
    return true;
  }

  /** Called from battle.ts before stepMovement/stepAttacks. Returns true ONLY when the
   *  ROM driver needs to exclusively own the borg's motion/action phase. Ported
   *  multi-frame X and B-charge handlers return true until their ROM exit clears the
   *  action bits; unhandled generic paths return false before reaching this tick. */
  tick(
    runtime: BorgRuntime,
    _dt: number,
    all: readonly BorgRuntime[],
    input: PlayerInput | null = null,
    onMineReceiverMelee?: (attack: MineReceiverMeleeAttack) => void,
  ): boolean {
    if (runtime.borgId === "pl0615" || runtime.borgId === "pl0629" || runtime.borgId === "pl062a") {
      const held = input?.attack ?? false;
      this.neoBPressed = held && !this.neoBWasHeld;
      this.neoBWasHeld = held;
      const aHeld=input?.jump??false;
      if(aHeld&&!this.shotAWasHeld)this.shotABuffer=16;
      this.shotAWasHeld=aHeld;this.shotAActive=this.shotABuffer>0;
      if(this.shotABuffer>0)this.shotABuffer--;
      this.shotDirectionActive=!!input&&Math.max(Math.abs(input.moveX),Math.abs(input.moveZ))>=0x34/127;
    }
    // The family's +0x4bc per-frame virtual runs EVERY frame in the ROM — before, during and
    // after any action — so it must run above the action-ownership early-return below.
    this.familyFrameUpdate?.(this.actor, runtime);
    if(getTeleportXState(this.actor)&&(runtime.combatFormId??runtime.borgId)!=='pl0005'){this.interrupt();return false;}
    if (!this.specialActive) return false;
    this.runtime = runtime;

    // --- ROM-owned multi-frame machine (B-charge zz_0179814_): advance the 4-phase
    //     state machine each tick. Phase 0 armed in tryStartBAttack; phases 1-3 advance
    //     here via stepRomActor → rootAction → phase-table dispatch. Returns true so
    //     battle.ts skips stepMovement/stepAttacks (the ROM owns motion + facing). ---
    if (this.romOwnedSpecial) {
      const preX = runtime.pos.x;
      const preY = runtime.pos.y;
      const preZ = runtime.pos.z;
      this.syncIn(runtime, all);
      this.syncActionInput(input, true);
      beginNeoGredMeleeTick(this.actor);
      beginGRedCrashTick(this.actor);
      beginGRedAirMeleeTick(this.actor);
      const poweredSourceAction = (runtime.borgId === "pl0101" && (this.actor.actionIndex === 2 || this.actor.actionIndex === 3)) || (isRevolver(runtime.borgId) && this.actor.actionIndex === 2);
      // This source handler ticks its stream before testing +0x1cf0 in the same frame.
      if (poweredSourceAction) this.dispatchEvent(this.streamFrame);
      // State 61 and the command fields remain live after the entry dispatch. Re-dispatching
      // cue 44 here would reset +0x540..+0x543 every frame, trapping every multi-phase ROM
      // machine in phase 0 and preventing an authored +0x1cee completion from being consumed.
      const airShotBefore=getGRedAirShotState(this.actor);
      const timeBomberPart = runtime.borgId === "pl0106" && this.actor.actionIndex === 0 && (this.actor.variantIndex === 1 || this.actor.variantIndex === 3);
      if(airShotBefore?.partMode){
        // Source55568 runs the lower channel before the upper handler. The
        // host lower update has already run; do not dispatch it again here.
        this.actor.controlWord=runtime.grounded?this.actor.controlWord&~0x40:this.actor.controlWord|0x40;
        this.actor.rootAction?.(this.actor);this.syncOut(runtime);
      }else if(timeBomberPart){
        this.actor.controlWord=runtime.grounded?this.actor.controlWord&~0x40:this.actor.controlWord|0x40;
        this.actor.rootAction?.(this.actor);
        if(this.actor.variantIndex!==1 && this.actor.variantIndex!==3){
          // 006a3d0 -> 006a104 snapshots the currently selected target again.
          captureTimeBomberAim(runtime,this.actor,all);
          this.timeBomberLocomotion=null;
        }
      } else {stepRomActor(this.actor, this.tables, this.ctx);this.syncOut(runtime);}
      if (!timeBomberPart && this.bounds) {
        runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
        runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
      }
      if (!timeBomberPart && !(runtime.borgId === "pl0106" && this.actor.variantIndex === 4) && this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
        runtime.pos.x = preX;
        runtime.pos.z = preZ;
      }
      if (!timeBomberPart && !getGBlackChargeState(this.actor) && !getGRedChargeState(this.actor) && !getGRedCrashState(this.actor) && !getGRedAirMeleeState(this.actor) && !getTeleportXState(this.actor) && this.groundClamp) {
        const clamped = this.groundClamp(runtime.pos, runtime.vel.y);
        if (clamped.y > runtime.pos.y) {
          runtime.pos.y = clamped.y;
          runtime.vel.y = Math.max(0, runtime.vel.y);
        }
      }
      // The host floor owns the far action's grounded presentation; +1d9 is a
      // contact byte, never a floor flag. Preserve close and other families here.
      const nurseMotion = getNurseXState(this.actor);
      if ((getNeoGredMeleeState(this.actor) || (nurseMotion && !nurseMotion.close) || (runtime.borgId === "pl0106" && this.actor.variantIndex === 4)) && this.groundClamp) {
        runtime.grounded = this.groundClamp(runtime.pos, runtime.vel.y).grounded;
      }
      const resumedAirShot=getGRedAirShotState(this.actor);
      if(resumedAirShot?.partMode&&resumedAirShot.physicsAdvanced)
        this.gredAirShotLocomotion={state:runtime.grounded?'idle':'jump',anim:runtime.grounded?'idle':'jump',stateTime:0};
      // Stream events (anim + hitbox + fireChild) for this frame.
      if (!poweredSourceAction) this.dispatchEvent(this.streamFrame);
      this.streamFrame++;
      this.resolveHits(runtime, all, onMineReceiverMelee);
      // Payload tracking for the X impotence latch: ROM-driven motion counts as a real
      // effect (movement/reposition X moves like Fly or a launch arc have no hitboxes).
      this.specialMotionAccum +=
        Math.abs(runtime.pos.x - preX) + Math.abs(runtime.pos.y - preY) + Math.abs(runtime.pos.z - preZ);
      // Completion: the phase machine's phase-3 exit clears +0x5e0's action bits
      // (controlWord &= ~0x3). Detect that OR the max-frame safety timeout.
      const phaseDone = (this.actor.controlWord & 0x3) === 0 && this.streamFrame > 2;
      // Resource-bounded source repeats may legitimately exceed the generic90
      // frame ceiling. Their authored completion and interruption own exit.
      if (phaseDone || (!getGRedShotState(this.actor) && !getGRedAirShotState(this.actor) && !this.hasPendingKnightWindup() && this.streamFrame >= this.specialMaxFrames)) {
        const sourceTeleport=getTeleportXState(this.actor);
        const sourceAirShot=getGRedAirShotState(this.actor);
        const sourceShot=sourceAirShot??getGRedShotState(this.actor);
        // Generic attack edge bookkeeping is skipped while ROM-owned. Preserve
        // the actual final held state so the next fresh B is not swallowed, and
        // holding through cleanup cannot fabricate a second admission.
        if(sourceShot)runtime.cooldowns["attackHeld"]=input?.attack?1:0;
        if(runtime.borgId === "pl0106" && this.actor.actionIndex===0 && this.actor.variantIndex===4 && this.actor.ubCue===7 && this.actor.stateTimer>0)
          this.timeBomberLandingCooldown=true;
        clearTeleportX(this.actor,runtime);
        clearNinjaX(this.actor);
        clearNurseX(this.actor);
        clearNeoGredMelee(this.actor);
        clearGRedCrash(this.actor);
        clearGRedAirMelee(this.actor);
        if(getGRedChargeState(this.actor)&&runtime.beamOwner)runtime.beamOwner.state=0;
        clearGRedCharge(this.actor);
        clearGBlackCharge(this.actor);
        clearGRedShot(this.actor);
        clearGRedAirShot(this.actor);
        delete runtime.sourceAnimSample;
        this.specialActive = false;
        this.romOwnedSpecial = false;
        this.armedHits = [];
        this.streamEvents = null;
        this.streamSchedules = [];
        runtime.cooldowns["romSpecialActive"] = 0;
        // Re-arm the B cooldown so a mash cannot chain ROM machines back-to-back —
        // the X path does the same with cooldowns["special"] below. PLACEHOLDER (not
        // ROM-derived): the ROM's post-charge recovery frame count is untraced; reuse
        // the generic shot cooldown slot at the melee-cooldown magnitude.
        if (!sourceTeleport && !sourceShot && (runtime.borgId !== "pl0106" || this.actor.actionIndex !== 0))
          runtime.cooldowns["shot"] = Math.max(runtime.cooldowns["shot"] ?? 0, 20);
        // X impotence latch: this ROM X ran to completion with no armed hit and no
        // child projectile, and either barely moved OR moved-and-returned (a spin/dash
        // that ends where it began, e.g. Iron Spin/Senpuken with undecoded hit kinds)
        // — a pure pantomime. A genuine movement X (Fly, a launch arc) ENDS somewhere
        // else, so the net-displacement test keeps it ROM-owned. Latch so every FUTURE
        // X press on this borg goes to the generic startSpecialAttack fallback instead
        // of silently doing nothing again. PLACEHOLDER policy until every family's hit
        // kinds are decoded.
        if (this.specialKind === "x" && !this.specialHadEffect &&
            !this.sourceXResourceDenied && !isSourceTeleportX(runtime.borgId) && !isSourceNinjaX(runtime.borgId) && runtime.borgId !== "pl0106" && !isNurseX(runtime.borgId)) {
          const net =
            Math.abs(runtime.pos.x - this.specialStartPos.x) +
            Math.abs(runtime.pos.y - this.specialStartPos.y) +
            Math.abs(runtime.pos.z - this.specialStartPos.z);
          if (this.specialMotionAccum < 20 || net < 40) this.xImpotent = true;
        }
        this.specialKind = null;
        // Return to idle so the renderer stops selecting the attack slot now
        // that the ROM no longer owns the borg (stepMovement will take over and
        // re-derive state from velocity next frame).
        if(sourceAirShot&&this.gredAirShotLocomotion)Object.assign(runtime,this.gredAirShotLocomotion);
        else if(timeBomberPart && this.timeBomberLocomotion)Object.assign(runtime,this.timeBomberLocomotion);
        else if(sourceTeleport){runtime.state=runtime.grounded?'idle':'jump';runtime.anim=runtime.state;}
        else {runtime.state = "idle";runtime.anim = "idle";}
        this.timeBomberLocomotion=null;this.gredAirShotLocomotion=null;
        this.restoreTimeBomberMovementControl();
      }
      return true; // ROM owns this frame — skip stepMovement/stepAttacks
    }

    // --- X-special path: layer stream events on top of normal movement (tick returns
    //     false → stepMovement + stepAttacks run normally). ---
    // Play pre-decoded stream events for this frame (anim + hitbox arming).
    this.dispatchEvent(this.streamFrame);
    this.streamFrame++;
    // Resolve armed hitbox windows against nearby enemies (damage).
    this.resolveHits(runtime, all, onMineReceiverMelee);
    // Drain any fireChild-spawned projectiles.
    // (battle.ts drains via drainProjectiles after tick returns)
    // Check completion: if the special's frame count exceeded the stream length,
    // end the special. The stream length comes from the decoded anim bank (typically
    // 15-81 frames depending on the move).
    if (this.streamFrame >= this.specialMaxFrames) {
      this.specialActive = false;
      this.armedHits = [];
      this.streamEvents = null;
      this.streamSchedules = [];
      runtime.cooldowns["romSpecialActive"] = 0;
      runtime.cooldowns["special"] = 90;
    }
    // Return false → stepMovement + stepAttacks run normally. The bridge's
    // hitbox/anim/damage are layered ON TOP of normal movement, not replacing it.
    return false;
  }

  /** Called by the stream VM when a playAnim op fires. Sets the BorgRuntime's anim
   *  label + meleeAnimStream ref so the renderer (borgPresentationAssets) plays the
   *  decoded clip. The (group, slot) args are the playAnim op's (metaBank, metaAnim)
   *  operands — NOT the motion-file group/slot. The +0x1d88 anim-metadata hop
   *  (animMetadataHop.generated.json) remaps them to the real motion-file
   *  (group, slot) that anim_index.json exports. Borgs without a remap entry fall
   *  back to the raw (group, slot) (legacy behavior — works for identity-mapped
   *  borgs and the 24 hand-tuned borgs). */
  private onPlayAnim(group: number, slot: number): void {
    if (this.runtime) {
      this.runtime.anim = "special";
      const remapped = this.runtime.borgId
        ? resolveAnimMetaHop(this.runtime.borgId, group, slot)
        : null;
      this.runtime.meleeAnimStream = remapped ?? { group, slot };
      // These admitted clocks already account for blend holds, mode2 advance,
      // authored pauses and recovery resets. Only actual playAnim allocates an
      // epoch; later syncOut samples the same clock without advancing it.
      const sourceStream=getTeleportXState(this.actor)?.stream ?? getNinjaXState(this.actor)?.stream ?? getGRedAirShotState(this.actor)?.stream ?? getGRedShotState(this.actor)?.stream ?? getGBlackChargeState(this.actor)?.stream ?? getGRedChargeState(this.actor)?.stream ?? getGRedCrashState(this.actor)?.stream ?? getGRedAirMeleeState(this.actor)?.stream ?? getNeoGredMeleeState(this.actor)?.stream;
      if(sourceStream)
        this.runtime.sourceAnimSample={serial:++sourceAnimationSerial,frame:sourceStream.frame};
    }
  }

  /** Called by the stream VM when an armHit op fires. Looks up the kind's hit records
   *  from attackHitTables.json and arms them — each record carries its active window
   *  (frame range), reach, and damage record. The bridge checks them each tick. */
  private onArmHit(kind: number): void {
    if (!this.runtime) return;
    if(kind===0 && getGRedChargeState(this.actor)){this.armedHits=[];return;}
    // Only this source X continuation uses kind0 as its explicit HIT clear.
    // Nurse B also owns a real kind0 record and must retain ordinary arming.
    if (kind === 0 && isNurseX(this.runtime.borgId) && this.actor.actionIndex === 2 &&
        getNurseXState(this.actor)) { this.armedHits = []; return; }
    const tables = hitTablesFor(this.runtime.borgId);
    if (!tables) return;
    const recordIndices = tables.kinds[String(kind)];
    if (!recordIndices) return;
    const neo = getNeoGredMeleeState(this.actor);
    const crash=getGRedCrashState(this.actor);
    const airMelee=getGRedAirMeleeState(this.actor);
    const airStream=airMelee?.stream?gredAirMeleeStreamProfile(airMelee.family,airMelee.stream.slot):undefined;
    const neoReach = neo ? attackHitMaxReachForKind(this.runtime.borgId,kind) : null;
    const opener = this.mineMeleeOpenerStream && this.runtime.borgId === "pl0615" &&
      this.actor.actionIndex === 1 && this.actor.variantIndex === 0 && kind === 1 && recordIndices.length === 1
      ? comboLadderForBorgId(this.runtime.borgId)?.[0] : null;
    const mineReceiverAttackUid = opener?.slot === 0 && opener.kind === 1 &&
      opener.activeStart === 10 && opener.activeEnd === 12 && opener.damageRecord?.index === 2
      ? `rom-melee-${this.runtime.uid}-${++mineMeleeSerial}` : undefined;
    this.armedHits = recordIndices.map((idx): ArmedHit | null => {
      const rec = tables.records[String(idx)] as {
        activeStart: number; activeEnd: number; halfExtent: number[]; localOffset: number[];
        damageRecordIndex: number; collisionFlags: number; shapeKind:number; radius:number;
      } | undefined;
      if (!rec) return null;
      // OPEN-WINDOW sentinel normalization: attackHitTables.json encodes "active from
      // activeStart until the anim ends" as an activeEnd -1/-2 sentinel (2,190 of the
      // 4,258 records — 1,800 x -1, 259 x -2, plus 131 with 0 <= activeEnd < activeStart).
      // Copying the raw value made resolveHits' inclusive [activeStart, activeEnd] test
      // an EMPTY window, so none of those hits could ever fire. Mirror the combo-ladder
      // resolver (actionStreamData.ts stepFromKind): give them the labeled TUNED
      // open-window active length instead.
      const activeEnd =
        rec.activeEnd < rec.activeStart
          ? rec.activeStart + OPEN_WINDOW_ACTIVE_FRAMES - 1
          : rec.activeEnd;
      return {
        collisionFlags: rec.collisionFlags,
        activeStart: rec.activeStart,
        activeEnd,
        reach: neoReach ?? rec.halfExtent?.[0] ?? 50,
        damageRecordIndex: rec.damageRecordIndex,
        struck: new Set<string>(),
        ...(neo ? { neoActivated: false as boolean } : {}),
        ...(crash && (crash.family==='red'?kind===15 && (idx===33 || idx===21):kind===29 && (idx===41 || idx===42)) ? { crashHit: {
          recordIndex: idx, activated: false, refresh: familyDamageRecordForBorg(this.runtime!.borgId,rec.damageRecordIndex)?.rehitIntervalFrames??0,
          countdown: 0, localOffset: rec.localOffset, radius: rec.halfExtent[0]??0,
        } } : {}),
        ...(airStream && kind===airStream.hitKind && airStream.hitRecords.includes(idx) &&
          (rec.shapeKind===0||rec.shapeKind===2)?{airMeleeHit:{
          recordIndex:idx,activated:false,shapeKind:rec.shapeKind,localOffset:rec.localOffset,
          halfExtent:rec.halfExtent,radius:rec.shapeKind===2?rec.radius:rec.halfExtent[0]??0,
        }}:{}),
        ...(mineReceiverAttackUid && rec.activeStart === 10 && rec.activeEnd === 12 &&
          rec.damageRecordIndex === 2 && (rec.collisionFlags & 1) !== 0 ? { mineReceiverAttackUid } : {}),
      } satisfies ArmedHit;
    }).filter((h): h is ArmedHit => h !== null);
    // Count as a real payload only when at least one armed window can actually fire
    // (activeStart reachable and the inclusive window non-empty after the sentinel
    // normalization above). Before the normalization, arming an open-window record
    // latched specialHadEffect=true while resolveHits could never fire it — so the
    // xImpotent fallback never engaged and borgs like pl0400/pl0800 kept a zero-damage
    // X special forever.
    if (this.armedHits.some((h) => h.activeStart >= 0 && h.activeEnd >= h.activeStart)) {
      this.specialHadEffect = true;
    }
    // Reset the HIT clock only. Rewinding streamFrame here desynchronised every
    // streamSchedule (whose startFrame was recorded on the old clock) and
    // restarted the specialMaxFrames timeout, so the special outran its author.
    this.armedHitFrame = 0;
  }

  /** Called by the stream VM when a fireChild op (0x09) fires. Spawns a ROM-data-driven
   *  projectile using the decoded variant table (DAT_802f3dda). The projectile gets
   *  real speed/drop/lifetime from the variant, replacing the TUNED spawnSpecialProjectiles
   *  path. Collected in pendingProjectiles; battle.ts drains them after tick. */
  private onFireChild(variant: number): void {
    if (!this.runtime) return;
    const yawRad = (this.actor.activeYaw / 0x10000) * Math.PI * 2;
    const proj = spawnRomProjectile(this.runtime, variant, yawRad);
    if (proj) {
      this.pendingProjectiles.push(proj);
      this.specialHadEffect = true;
    }
  }

  /** Called by family handlers (STAR HERO / PLANET HERO X-special) when they apply a
   *  param-tier delta via `apply_actor_param_tier_delta_127`. Routes to BorgRuntime's
   *  authoritative paramTier and keeps heroTierBuffFrames in sync so the existing
   *  stepHitStatus revert path owns expiry (ROM postState only ticks during specials). */
  private onParamTierDelta(signedDelta: number): void {
    if (!this.runtime) return;
    applyActorParamTierDelta127(this.runtime.paramTier, signedDelta);
    if (signedDelta > 0) {
      // Buff application: arm the heroTierBuffFrames timer (stepHitStatus reverts at 0).
      this.runtime.heroTierBuffFrames = HERO_X_BUFF.DURATION_FRAMES;
    } else if (signedDelta < 0) {
      // Revert (ROM-driven): clear the timer so stepHitStatus doesn't double-revert.
      this.runtime.heroTierBuffFrames = 0;
    }
  }

  /** Fire any stream events scheduled for the given frame (from meleeAnimKinds.json).
   *  This drives the anim + hitbox arming at the exact ROM frame numbers, bypassing
   *  the raw bytecode walker when the bank bytes aren't loaded. */
  private dispatchEvent(frame: number): void {
    if (this.streamEvents) this.dispatchEventList(this.streamEvents, frame);
    for (const schedule of this.streamSchedules) {
      if (schedule.knightClocks || schedule.mask === 0) continue;
      const localFrame = frame - schedule.startFrame;
      if (localFrame >= 0) this.dispatchEventList(schedule.events, localFrame);
      if (!schedule.completed && frame >= schedule.endFrame) {
        schedule.completed = true;
        for (let partIndex = 0; partIndex < this.actor.parts.length; partIndex++) {
          if ((schedule.mask & (1 << partIndex)) === 0) continue;
          // Do not complete a newer overlapping stream on the same part.
          const newer = this.streamSchedules.some((candidate) =>
            candidate !== schedule
            && candidate.startFrame > schedule.startFrame
            && candidate.startFrame <= frame
            && (candidate.mask & (1 << partIndex)) !== 0
            && !candidate.completed);
          if (newer) continue;
          const part = this.actor.parts[partIndex]!;
          part.streamPtr = -1;
          part.active = 0;
          if (partIndex === 0) this.actor.wallContact = 1;
        }
      }
    }
  }

  private dispatchEventList(events: readonly StreamEvent[], frame: number): void {
    for (const ev of events) {
      const evFrame = ev.frame ?? 0;
      if (evFrame !== frame) continue;
      switch (ev.op) {
        case "armHit":
          if (ev.kind !== undefined && ev.kind > 0) {
            this.ctx.onArmHit?.(this.actor, ev.kind, ev.statusId ?? 0, ev.statusArg ?? 255);
          }
          break;
        case "playAnim":
        case "blendAnim":
          if (ev.group !== undefined && ev.slot !== undefined) {
            this.ctx.onPlayAnim?.(this.actor, ev.group, ev.slot, ev.op === "blendAnim");
          }
          break;
        case "fireChild":
          if (ev.variant !== undefined) this.ctx.onFireChild?.(this.actor, ev.variant);
          break;
        case "partState": {
          const partIndex = ev.part ?? 0;
          const part = this.actor.parts[partIndex];
          if (!part) break;
          part.stateByte = ev.state ?? 0;
          (part as typeof part & { c?: number }).c = ev.aux ?? 0;
          if (partIndex === 0) {
            this.actor.contactP0 = part.stateByte;
            // Verified Gunman actions consume part-0 aux (+0x1cf0), not part1.state.
            // Powered sets it at16; Revolver/Billy at14.
            if ((this.runtime?.borgId === "pl0101" && (this.actor.actionIndex === 2 || this.actor.actionIndex === 3)) || (this.runtime && isRevolver(this.runtime.borgId) && this.actor.actionIndex === 2))
              this.actor.contactP1 = ((ev.aux ?? 0) << 24) >> 24;
          }
          break;
        }
      }
    }
  }

  /** Per-frame hit check: if any armed hitbox's active window is live this frame,
   *  resolve hits against nearby enemies via the host's applyHit callback. */
  private resolveHits(runtime: BorgRuntime, all: readonly BorgRuntime[],
    onMineReceiverMelee?: (attack: MineReceiverMeleeAttack) => void): void {
    if (this.armedHits.length === 0) return;
    // Check this frame BEFORE advancing: windows are authored inclusive of frame
    // 0, which is the most common activeStart in attackHitTables.json (1,947 of
    // 4,258 records). Advancing first made frame 0 unreachable, and advancing a
    // clock that tick() had already advanced left only even values reachable --
    // 2,282 of 4,258 windows could never fire.
    // Nurse HIT windows are animation frames (including continuation and HOLD),
    // not elapsed time since armHit. Other families retain their existing clock.
    const nurse = this.actor.actionIndex === 2 ? getNurseXState(this.actor) : undefined;
    const neo = getNeoGredMeleeState(this.actor);
    const crash=getGRedCrashState(this.actor);
    const airMelee=getGRedAirMeleeState(this.actor);
    // HIT8 dies when its animation ID changes to g0s14. Source windows use
    // the verified NEO animation clock, including its mode1/mode2 blend behavior.
    const frame = crash?.stream ? (crash.stream.recovery?Infinity:Math.trunc(crash.stream.frame))
      : airMelee?.stream ? (airMelee.stream.recovery?Infinity:Math.trunc(airMelee.stream.frame))
      : neo?.stream ? (neo.stream.recovery ? Infinity : neo.stream.frame)
      : nurse?.stream.frame ?? this.armedHitFrame;
    this.armedHitFrame += 1;
    if(airMelee){
      // Source8a65c/8a5d0 stores actor26c globally. Updating the full HIT list
      // before collision means BLACK record19's activation at17 renews the
      // still-active record6 too; their overlap cannot hit a victim twice.
      const newlyActive=this.armedHits.filter(hit=>hit.airMeleeHit && !hit.airMeleeHit.activated &&
        frame>=hit.activeStart && frame<=hit.activeEnd);
      if(newlyActive.length){
        const history=new Set<string>();
        for(const hit of newlyActive)hit.airMeleeHit!.activated=true;
        for(const hit of this.armedHits)if(hit.airMeleeHit)hit.struck=history;
        airMelee.hitActivationSerial=++gredAirMeleeHitSerial;
        airMelee.hitRecordIndex=newlyActive[0]!.airMeleeHit!.recordIndex;
      }
    }
    if (neo) {
      const newlyActive = this.armedHits.filter(hit=>!hit.neoActivated && frame>=hit.activeStart && frame<=hit.activeEnd);
      if(newlyActive.length) {
        // Source8a65c: all new records in one activation pass share actor26c;
        // later waves renew it. HIT8 windows7..9 and10..16 are separate waves,
        // refresh0, so the same victim may receive each once.
        this.neoWaveStruck = new Set();
        for(const hit of newlyActive)hit.neoActivated=true;
      }
    }
    if(crash){
      // Source29434 updates the entire HIT list before running any pair pass.
      // Simultaneous activation seeds refresh only on the FIRST actor1ca gate;
      // subsequent records start at0. HIT29's [7,0] counters therefore renew
      // the shared actor ID at +1,+7,+8,..., including frozen animation updates.
      // All volumes then use one FINAL actor ID/history for this collision pass.
      let activatedThisPass=false,renew=false;
      for(const hit of this.armedHits){
        if(!hit.crashHit || frame<hit.activeStart || frame>hit.activeEnd)continue;
        const h=hit.crashHit;
        if(!h.activated){
          h.activated=true;h.countdown=0;
          if(!activatedThisPass){h.countdown=h.refresh;renew=true;activatedThisPass=true;
            crash.hitRecordIndex=h.recordIndex;crash.hitActivationSerial=++gredCrashHitSerial;}
        } else if(h.refresh>0 && --h.countdown<1){
          h.countdown=h.refresh;renew=true;crash.hitRenewalCount++;
          crash.hitActivationSerial=++gredCrashHitSerial;
        }
      }
      if(renew){const history=new Set<string>();for(const hit of this.armedHits)if(hit.crashHit)hit.struck=history;}
    }
    for (const hit of this.armedHits) {
      if (frame < hit.activeStart || frame > hit.activeEnd) continue;
      const record = familyDamageRecordForBorg(runtime.borgId, hit.damageRecordIndex);
      if (hit.mineReceiverAttackUid && record && runtime.borgId === "pl0615") {
        // Snapshot while this actual arm is active, before later actor hits can interrupt
        // it. Battle defers reception until AFTER every mine's child update. The
        // admitted source animation clock supplies the original inclusive10..12 window;
        // it no longer uses elapsed updates since HIT arming. Root reach/front/vertical
        // geometry is bounded host glue,
        // not animated bone1 HIT geometry. No generic, air, later-combo or NEO inference.
        const opener = comboLadderForBorgId(runtime.borgId)![0]!;
        onMineReceiverMelee?.({
          uid: hit.mineReceiverAttackUid, ownerUid: runtime.uid, team: runtime.team,
          pos: { ...runtime.pos }, forward: { x: Math.sin(runtime.rotY), y: 0, z: Math.cos(runtime.rotY) },
          reach: opener.reach, yTolerance: MELEE.Y_TOLERANCE,
          damage: 1, damageRecord: { ...record },
        });
      }
      // Nurse actor HIT descriptors use list 177c (descriptor 128), whose
      // secondary-v-borg pass permits allies: chunk_0013.c:1068-1079 and
      // chunk_0003.c:7338-7357. Do not apply the active-object pass's flagsB16
      // ally exclusion here. Keep other families' existing contact policy.
      const nurseHealing = (runtime.borgId === "pl0900" || runtime.borgId === "pl0908" || runtime.borgId === "pl090d") &&
        (hit.collisionFlags & 0x80) !== 0 && record !== null && (record.flagsA & 0x2) !== 0;
      for (const target of all) {
        if (!target.alive || target.sourceDefenseDisabled || target.uid === runtime.uid || (!nurseHealing && target.team === runtime.team)) continue;
        const struck = neo ? this.neoWaveStruck : hit.struck;
        if (struck.has(target.uid)) continue;
        const dx = target.pos.x - runtime.pos.x;
        const dz = target.pos.z - runtime.pos.z;
        if (neo && (Math.abs(target.pos.y-runtime.pos.y)>MELEE.Y_TOLERANCE ||
          dx*Math.sin(runtime.rotY)+dz*Math.cos(runtime.rotY)<0)) continue;
        // Nurse uses the existing root-radius approximation in three dimensions:
        // admission alone cannot prevent a target moving vertically before impact.
        // The radius is the authored HIT halfExtent, not a new tolerance.
        let dist = nurseHealing ? Math.hypot(dx, target.pos.y - runtime.pos.y, dz) : Math.hypot(dx, dz);
        let reach=hit.reach;
        const sourceVolume=crash?hit.crashHit:airMelee?hit.airMeleeHit:undefined;
        if(sourceVolume){
          // Original shape0 radius or shape2 offset±extent capsule. Animated
          // bone origins/orientations are replaced by root+yaw; BLACK3b304's
          // previous/current endpoint sweep is explicitly not reproduced.
          // Source+c0 is independent from visual scale; undefined explicitly
          // falls back to modelScale, as in the other scoped source adapters.
          const h=sourceVolume,scale=this.actor.collisionScale??this.actor.modelScale;
          const [lx=0,ly=0,lz=0]=h.localOffset,yaw=runtime.rotY;
          const cx=runtime.pos.x+(Math.cos(yaw)*lx+Math.sin(yaw)*lz)*this.actor.modelScale;
          const cy=runtime.pos.y+ly*this.actor.modelScale;
          const cz=runtime.pos.z+(-Math.sin(yaw)*lx+Math.cos(yaw)*lz)*this.actor.modelScale;
          if('shapeKind' in h && h.shapeKind===2){
            const [ex=0,ey=0,ez=0]=h.halfExtent;
            const vx=(Math.cos(yaw)*ex+Math.sin(yaw)*ez)*this.actor.modelScale;
            const vy=ey*this.actor.modelScale;
            const vz=(-Math.sin(yaw)*ex+Math.cos(yaw)*ez)*this.actor.modelScale;
            const sx=cx-vx,sy=cy-vy,sz=cz-vz;
            const dx=2*vx,dy=2*vy,dz=2*vz,lengthSquared=dx*dx+dy*dy+dz*dz;
            const projection=(target.pos.x-sx)*dx+(target.pos.y-sy)*dy+(target.pos.z-sz)*dz;
            const t=lengthSquared>0?Math.max(0,Math.min(1,projection/lengthSquared)):0;
            dist=Math.hypot(target.pos.x-sx-dx*t,target.pos.y-sy-dy*t,target.pos.z-sz-dz*t);
          }else dist=Math.hypot(target.pos.x-cx,target.pos.y-cy,target.pos.z-cz);
          reach=h.radius*scale;
        }
        if (dist <= reach) {
          if(!neo && !crash && !airMelee)hit.struck.add(target.uid);
          // Route through the host's full applyHit path for damage-formula fidelity.
          if (this.hitResolver) {
            const resolved = this.hitResolver(runtime, target, hit.damageRecordIndex, 1.0,
              neo ? () => { struck.add(target.uid); acceptNeoGredMeleeContact(this.actor,neo); }
                : crash ? () => { struck.add(target.uid);if(hit.crashHit)crash.hitRecordIndex=hit.crashHit.recordIndex;
                  acceptGRedCrashContact(this.actor,crash); }
                : airMelee ? ()=>{struck.add(target.uid);if(hit.airMeleeHit)airMelee.hitRecordIndex=hit.airMeleeHit.recordIndex;
                  acceptGRedAirMeleeContact(this.actor,airMelee);} : undefined);
            if (nurse && typeof resolved === "number" && resolved < 0) nurse.pendingContact |= 0x10;
          } else if (!nurseHealing && !neo && !crash && !airMelee) {
            // Healing requires the full resolver (immunity, signed HP, gauges and
            // reactions). Never turn it into the legacy damaging fallback.
            // Fallback (no resolver wired): direct HP subtraction so hits are still visible.
            target.hp = Math.max(0, target.hp - 20);
            target.lastHitAttackerTeam = runtime.team;
            target.lastHitAttackerOwner = runtime.ownerPlayer;
          }
        }
      }
    }
  }

  /** Force-clear when host lifecycle (hit/down/death) outranks ROM action ownership.
   *  Deliberately leaves runtime state/animation untouched for the host lifecycle to own. */
  interrupt(): void {
    this.restoreTimeBomberMovementControl();
    if(this.timeBomberLandingCooldown)this.actor.stateTimer=0;
    this.timeBomberLandingCooldown=false;
    this.timeBomberLocomotion=null;
    if(getGRedChargeState(this.actor)&&this.runtime?.beamOwner)this.runtime.beamOwner.state=0;
    clearGRedCharge(this.actor);
    clearGBlackCharge(this.actor);
    clearGRedShot(this.actor);
    clearGRedAirShot(this.actor);this.gredAirShotLocomotion=null;
    clearTeleportX(this.actor,this.runtime??undefined);
    clearNinjaX(this.actor);
    clearNurseX(this.actor);
    clearNeoGredMelee(this.actor);
    clearGRedCrash(this.actor);
    clearGRedAirMelee(this.actor);
    if(this.runtime)delete this.runtime.sourceAnimSample;
    const wasActive = this.specialActive || this.romOwnedSpecial;
    this.arrowStreamClock = null;
    this.arrowStreamMask = 0;
    this.beamStreamClock = null;
    if (this.runtime?.borgId === "pl0104") {
      (this.actor as RomActor & { gmBeamState6f7?: number }).gmBeamState6f7 = 0;
      if (this.runtime.beamOwner) this.runtime.beamOwner.state = 0;
    }
    this.specialActive = false;
    this.romOwnedSpecial = false;
    this.armedHits = [];
    this.mineMeleeOpenerStream = false;
    this.streamEvents = null;
    this.streamSchedules = [];
    this.pendingProjectiles = [];
    this.familyProjectiles = [];
    // The host-scheduled path parks streamPtr at MAX_SAFE_INTEGER, and the
    // `handled` predicate in tryStartXSpecial treats any streamPtr >= 0 as a
    // live special. Clearing the schedules alone left that sentinel standing
    // forever, so after one interrupt -- a death, say -- every later X press
    // was claimed by the ROM path and the generic fallback never ran again.
    resetStreamParts(this.actor);
    this.actor.controlWord &= ~0x3;
    if (this.runtime) {
      this.runtime.cooldowns["romSpecialActive"] = 0;
    }
    if (wasActive && this.actor.fbState === 61) {
      dispatchFullBodyCue(this.actor, 0);
      dispatchUpperBodyCue(this.actor, 6);
    }
  }
}

/** Convert a pl#### borg id to the ROM's internal borg number (the +0x3e8 u16). */
function borgIdToNumber(borgId: string): number {
  const m = /^pl([0-9a-f]{4})$/i.exec(borgId);
  return m ? parseInt(m[1]!, 16) : 0;
}
