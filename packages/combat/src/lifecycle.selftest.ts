import {runActorFrameSuffixSelfTests} from './rom/actor-frame-suffix.selftest.js';
import {runActorAnimationTransitionSelfTests} from './rom/actor-animation-transition.selftest.js';
import {runActorFrameLifecycleSelfTests} from './rom/actor-frame-lifecycle.selftest.js';
import {runActorDoublePrehookSelfTests} from './rom/actor-double-prehook.selftest.js';
import {runActorDoubleActionSelfTests} from './rom/actor-double-action.selftest.js';
import {runSourceInputAtanSelfTests} from './rom/source-input-atan.selftest.js';
import {runSourceFloat64SelfTests} from './rom/source-float64.selftest.js';
import {runSourceInputAngleSelfTests} from './rom/source-input-angle.selftest.js';
import {runActorInputAxisSelfTests} from './rom/actor-input-axis.selftest.js';
import {runActorInputMachineSelfTests} from './rom/actor-input-machine.selftest.js';
import {runActorInputChargeSelfTests} from './rom/actor-input-charge.selftest.js';
import {runActorControlLifecycleSelfTests} from './rom/actor-control-lifecycle.selftest.js';
import {runActorReadyTransitionsSelfTests} from './rom/actor-ready-transitions.selftest.js';
import {runActorInputTestersSelfTests} from './rom/actor-input-testers.selftest.js';
import {runActorCue0LifecycleSelfTests} from './rom/actor-cue0-lifecycle.selftest.js';
import {runActorCue0TailSelfTests} from './rom/actor-cue0-tail.selftest.js';
import {runActorCommandAdmissionSelfTests} from './rom/actor-command-admission.selftest.js';
import {runActorRotationDampingSelfTests} from './rom/actor-rotation-damping.selftest.js';
import {runActorNormalLifecycleSelfTests} from './rom/actor-normal-lifecycle.selftest.js';
import {runActorTierLifecycleSelfTests} from './rom/actor-tier-lifecycle.selftest.js';
import {runActorCeilingLifecycleSelfTests} from './rom/actor-ceiling-lifecycle.selftest.js';
import {runActorRateLifecycleSelfTests} from './rom/actor-rate-lifecycle.selftest.js';
import {runActorActionRequestSelfTests} from './rom/actor-action-request.selftest.js';
import {runActorChargeEffectsSelfTests} from './rom/actor-charge-effects.selftest.js';
import {runActorInputPrefixSelfTests} from './rom/actor-input-prefix.selftest.js';
import {runActorTerrainQuerySelfTests} from './rom/actor-terrain-query.selftest.js';
import {runActorTransformHistorySelfTests} from './rom/actor-transform-history.selftest.js';
import {runActorMatrixUpdateSelfTests} from './rom/actor-matrix-update.selftest.js';
import {runActorWorldMatrixSelfTests} from './rom/actor-world-matrix.selftest.js';
import {runActorJointMatrixSelfTests} from './rom/actor-joint-matrix.selftest.js';
import {runJObjModelHydrationSelfTest} from './rom/jobj-model-hydration.selftest.js';
import {runDisplayAnimationAttachmentSelfTest} from './rom/display-animation-attachment.selftest.js';
import {runAnimationArchiveHydrationSelfTest} from './rom/animation-archive-hydration.selftest.js';
import {runActorMovementFollowupSelfTests} from './rom/actor-movement-followup.selftest.js';
import {runActorAttributeRefreshSelfTests} from './rom/actor-attribute-refresh.selftest.js';
import {runActorStatusTimersSelfTests} from './rom/actor-status-timers.selftest.js';
import {runActorGaugeScaleSelfTests} from './rom/actor-gauge-scale.selftest.js';
import {runActorStageBoundsSelfTests} from './rom/actor-stage-bounds.selftest.js';
import {runActorTickPrefixSelfTests} from './rom/actor-tick-prefix.selftest.js';
import {runAnimationArchiveBankSelfTests} from './rom/animation-archive-bank.selftest.js';
import {runActorAnimationSetupSelfTests} from './rom/actor-animation-setup.selftest.js';
import {runAnimationDescriptorBankSelfTests} from './rom/animation-descriptor-bank.selftest.js';
import {runAnimationSetupMetadataSelfTests} from './rom/animation-setup-metadata.selftest.js';
import {runArchivePublicSelfTests} from './rom/archive-public.selftest.js';
import {runArchiveJointSetupSelfTest} from './rom/archive-joint-setup.selftest.js';
import {runAObjLifecycleSelfTest} from './rom/aobj-lifecycle.selftest.js';
import {runJObjAddAnimationSelfTest} from './rom/jobj-add-animation.selftest.js';
import {runSourceStreamWaitSelfTest} from './rom/stream-wait.selftest.js';
import {runStreamWaitTargetSelfTest} from './rom/stream-wait-target.selftest.js';
import {runActorAnimationDispatchSelfTest} from './rom/actor-animation-dispatch.selftest.js';
import {runAnimationRequestTreeSelfTest} from './rom/animation-request-tree.selftest.js';
import {runAnimationRequestTreePlaybackSelfTest} from './rom/animation-request-tree-playback.selftest.js';
import {runActorJointScalingSelfTest} from './rom/actor-joint-scaling.selftest.js';
import {runAllocatedAObjReplacementSelfTest} from './rom/allocated-aobj-replacement.selftest.js';
import {runFObjRemovalSelfTest} from './rom/fobj-removal.selftest.js';
import {runAObjFrameSettersSelfTest} from './rom/aobj-frame-setters.selftest.js';
import {runAllocatedAObjDescriptorSelfTest} from './rom/allocated-aobj-descriptor.selftest.js';
import {runJObjFlagsSelfTest} from './rom/jobj-flags.selftest.js';
import {runJObjFlagsAnimationSelfTest} from './rom/jobj-flags-animation.selftest.js';
import {runJObjTrackOrderSelfTest} from './rom/jobj-track-order.selftest.js';
import {runTrackOrderAnimationSelfTest} from './rom/track-order-animation.selftest.js';
import {runSourceFloatSelfTest} from './rom/source-float.selftest.js';
import {runJObjUpdateSelfTest} from './rom/jobj-update.selftest.js';
import {runJObjAnimationSelfTest} from './rom/jobj-animation.selftest.js';
import {runJObjTreeSelfTest} from './rom/jobj-tree.selftest.js';
import {runAObjEndCallbackSelfTest} from './rom/aobj-end-callbacks.selftest.js';
import {runDObjAnimationSelfTest} from './rom/dobj-animation.selftest.js';
import {runPObjAnimationSelfTest} from './rom/pobj-animation.selftest.js';
import {runMObjAnimationSelfTest} from './rom/mobj-animation.selftest.js';
import {runDisplayAnimationSelfTest} from './rom/display-animation.selftest.js';
import {runTObjUpdateSelfTest} from './rom/tobj-update.selftest.js';
import {runTObjAnimationSelfTest} from './rom/tobj-animation.selftest.js';
import {runTextureAnimationSelfTest} from './rom/texture-animation.selftest.js';
import {runJointAnimationFeedbackSelfTest} from './rom/joint-animation-feedback.selftest.js';
import {runActorJointMappingSelfTest} from './rom/actor-joint-mapping.selftest.js';
import {runDescriptorAnimationSelfTest} from './rom/descriptor-animation.selftest.js';
import {runFObjDescriptorSelfTest} from './rom/fobj-descriptor.selftest.js';
import {runAnimationRequestSelfTest} from './rom/animation-request.selftest.js';
import {runRequestedAnimationSelfTest} from './rom/requested-animation.selftest.js';
import {runAttachedJointSetupSelfTest} from './rom/attached-joint-setup.selftest.js';
import {runAttachedSetupAnimationSelfTest} from './rom/attached-setup-animation.selftest.js';
import {runFObjCallbackSelfTest} from './rom/fobj-callback.selftest.js';
import {runFObjLinearSelfTest} from './rom/fobj-linear.selftest.js';
import {runFObjTimingSelfTest} from './rom/fobj-timing.selftest.js';
import {runFObjDataSelfTest} from './rom/fobj-data.selftest.js';
import {runFObjListSelfTest} from './rom/fobj-list.selftest.js';
import {runAObjClockSelfTest} from './rom/aobj-clock.selftest.js';
import {runActorDispatchOrderSelfTest} from './rom/dispatch-order.selftest.js';
import {runDoubleCloneContactSelfTest} from './doubleCloneContact.selftest.js';
import {runDoubleCloneReactionObservationSelfTest} from './doubleCloneReactionObservation.selftest.js';
import {runDoubleCloneReactionObservationBattleSelfTest} from './doubleCloneReactionObservationBattle.selftest.js';
import {runDoubleCloneReactionFrameSelfTest} from './doubleCloneReactionFrame.selftest.js';
import {runDoubleCloneReactionSelfTest} from './doubleCloneReaction.selftest.js';
import {runDoubleNinjaChargeStreamSelfTest} from './doubleNinjaChargeStream.selftest.js';
import {runDoubleCloneLifecycleSelfTest} from './doubleCloneLifecycle.selftest.js';
import {runDoubleNinjaXBattleSelfTest} from './doubleNinjaXBattle.selftest.js';
import {runDoubleNinjaXEngineSelfTest} from './doubleNinjaXEngine.selftest.js';
import {runDoubleNinjaXInputSelfTest} from './doubleNinjaXInput.selftest.js';
import { runNinjaProjectileSelfTest } from "./ninjaProjectile.selftest.js";
import { runNinjaXStreamSelfTest } from "./ninjaXStream.selftest.js";
import { runNinjaXSelfTest } from "./ninjaX.selftest.js";
import { runNinjaXBattleSelfTest } from "./ninjaXBattle.selftest.js";
import { runTeleportXBattleSelfTest } from "./teleportXBattle.selftest.js";
import { runSwitchingXBattleSelfTest } from "./switchingXBattle.selftest.js";
import { runSwitchingFieldSelfTest } from "./switchingField.selftest.js";
import { runSwitchingXStreamSelfTest } from "./switchingXStream.selftest.js";
import { runSwitchingXSelfTest } from "./switchingX.selftest.js";
import { runTeleportXEngineSelfTest } from "./teleportXEngine.selftest.js";
import { runTeleportXSelfTest } from "./teleportX.selftest.js";
import { runSelfTest as runNinjaShurikenFlightSelfTest } from "./ninjaShurikenFlight.selftest.js";
import {runSharedXCarrySelfTest} from './sharedXCarry.selftest.js';
import {runSharedXCarryBattleSelfTest} from './sharedXCarryBattle.selftest.js';
import {runSelfTest as runGredRangedFlightSelfTest} from './gredRangedFlight.selftest.js';
import {runGredShotBattleSelfTest} from './gredShotBattle.selftest.js';
import {runGredShotTimingBattleSelfTest} from './gredShotTimingBattle.selftest.js';
import {runGredAirShotBattleSelfTest} from './gredAirShotBattle.selftest.js';
import {runGredAirShotEngineSelfTest} from './gredAirShotEngine.selftest.js';
import {runGredAirShotLowerStreamSelfTest} from './gredAirShotLowerStream.selftest.js';
import {runGredShotEngineSelfTest} from './gredShotEngine.selftest.js';
import {runGredShotStreamSelfTest} from './gredShotStream.selftest.js';
import {runGredRangedProjectileSelfTest} from './gredRangedProjectile.selftest.js';
import {runGredRangedCarryBattleSelfTest} from './gredRangedCarryBattle.selftest.js';
import {runGredShotCarrySelfTest} from './gredShotCarry.selftest.js';
import {runGblackChargeEngineSelfTest} from './families/gblack-charge-engine.selftest.js';
import {runGBlackChargeStreamSelfTest} from './gblackChargeStream.selftest.js';
import {runGBlackChargeProjectileSelfTest} from './gblackChargeProjectile.selftest.js';
import {runGblackChargeBattleSelfTest} from './gblackChargeBattle.selftest.js';
import {runGredChargeBattleSelfTest} from './gredChargeBattle.selftest.js';
import {runGredChargeEngineSelfTest} from './families/gred-charge-engine.selftest.js';
import {runGRedChargeStreamSelfTest} from './gredChargeStream.selftest.js';
import { runNeoAirMeleeStreamSelfTest } from './neoAirMeleeStream.selftest.js';
import { runNeoAirMeleeBattleSelfTest } from './neoAirMeleeBattle.selftest.js';
import { runGblackAirMeleeStreamSelfTest } from './gblackAirMeleeStream.selftest.js';
import { runGblackAirMeleeBattleSelfTest } from './gblackAirMeleeBattle.selftest.js';
import { runGredAirMeleeEngineSelfTest } from './families/gred-air-melee-engine.selftest.js';
import { runGredAirMeleeStreamSelfTest } from './gredAirMeleeStream.selftest.js';
import { runGredAirMeleeBattleSelfTest } from './gredAirMeleeBattle.selftest.js';
import { runGredAirCrashBattleSelfTest } from './gredAirCrashBattle.selftest.js';
import { runGredFamilyCrashStreamSelfTest } from './gredFamilyCrashStream.selftest.js';
import { runGredFamilyCrashBattleSelfTest } from './gredFamilyCrashBattle.selftest.js';
import { runGredCrashStreamSelfTest } from './gredCrashStream.selftest.js';
import { runGredCrashBattleSelfTest } from './gredCrashBattle.selftest.js';
import { runGredCrashMotionSelfTest } from './gredCrashMotion.selftest.js';
import { runGredMeleeBattleSelfTest } from './gredMeleeBattle.selftest.js';
import { runGredMeleeStreamSelfTest } from './gredMeleeStream.selftest.js';
import { runGblackMeleeBattleSelfTest } from './gblackMeleeBattle.selftest.js';
import { runGblackGroundWaveSelfTest } from './gblackGroundWave.selftest.js';
import { runGblackMeleeStreamSelfTest } from './gblackMeleeStream.selftest.js';
import { runNeoMeleeStreamSelfTest } from './neoMeleeStream.selftest.js';
import { runNeoGredMeleeBattleSelfTest } from './neoGredMeleeBattle.selftest.js';
import { runNeoGredFinisherSelfTest } from './families/neo-gred-finisher.selftest.js';
import { runGredMeleeConfigSelfTest } from './gredMeleeConfig.selftest.js';
import { runMeleeMineBattleSelfTest } from './meleeMineBattle.selftest.js';
import { runBeamMineBattleSelfTest } from './beamMineBattle.selftest.js';
import { runTimeBomberMineBattleSelfTest } from './timeBomberMineBattle.selftest.js';
import { runTimeBomberBattleSelfTest } from "./timeBomberBattle.selftest.js";
import { runTimeBomberAirBattleSelfTest } from "./timeBomberAirBattle.selftest.js";
import { runTimeBomberWalkBattleSelfTest } from "./timeBomberWalkBattle.selftest.js";
import { runTimeBomberMineSelfTest } from "./timeBomberMine.selftest.js";
import { runNurseStreamSelfTest } from "./nurseStream.selftest.js";
import { runHealingContactSelfTest } from "./healingContact.selftest.js";
import { runNurseBattleSelfTest } from "./nurseBattle.selftest.js";
import { runArrowBattleSelfTest } from "./arrowBattle.selftest.js";
import { runBeamBattleSelfTest } from "./beamBattle.selftest.js";
import { runRevolverBattleSelfTest } from "./revolverBattle.selftest.js";
import { runPoweredChargeSelfTest } from "./poweredCharge.selftest.js";
import { runGatlingBattleSelfTest } from "./gatlingBattle.selftest.js";
import { runSourcePositionHistorySelfTest } from "./sourcePositionHistory.selftest.js";
import { runKnightWindupSelfTest } from "./knightWindup.selftest.js";
import { runPrimaryAmmoSelfTest } from "./primaryAmmo.selftest.js";
import { runHitDrainSelfTest } from "./hitDrain.selftest.js";
import { runDiverAuraSelfTest } from "./diverAura.selftest.js";
import { runContactAuraSelfTest } from "./contactAura.selftest.js";
import { runSelfTest as runTargetLockSelfTest } from "./targetLock.selftest.js";
import { runRomCollisionSelfTest } from "./romCollision.selftest.js";
import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { applyHit } from "./combat.js";
import { STATE } from "./constants.js";
import { buildProfile, type BorgStats } from "./stats.js";
import { emptyInput, type Battle, type BorgRuntime, type PlayerInput } from "./types.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`[lifecycle.selftest] ${message}`);
}

function loadStats(): BorgStats[] {
  return (borgsData as { borgs: BorgStats[] }).borgs;
}

const IDLE: PlayerInput = emptyInput();

function setupBattle(
  stats: readonly BorgStats[],
  replacement: boolean,
  timeLimitFrames?: number,
): {
  battle: Battle;
  victim: BorgRuntime;
  attacker: BorgRuntime;
  inputs: Record<string, PlayerInput>;
} {
  const battle = createBattle(
    {
      stageId: "st00",
      forces: [
        {
          team: 0,
          ownerPlayer: "p1",
          borgIds: replacement ? ["pl0615", "pl000c"] : ["pl0615"],
        },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
      ],
      bounds: { x: 40, z: 40 },
      ...(timeLimitFrames !== undefined ? { timeLimitFrames } : {}),
    },
    stats,
  );
  const inputs = { p1: IDLE, p2: IDLE };
  for (let frame = 0; frame <= STATE.SPAWN_DURATION; frame += 1) {
    battle.step(1 / 60, inputs);
  }
  const state = battleStateForSelfcheck(battle);
  const victim = state.borgs.find((actor) => actor.team === 0);
  const attacker = state.borgs.find((actor) => actor.team === 1);
  assert(victim, "missing ported-family victim");
  assert(attacker, "missing attacker");
  assert(victim.romDriver, "G RED did not receive a RomDriverBridge");
  assert(victim.state === "idle", `victim did not finish deployment: ${victim.state}`);
  return { battle, victim, attacker, inputs };
}

function killDuringRomSpecial(
  stats: readonly BorgStats[],
  victim: BorgRuntime,
  attacker: BorgRuntime,
): void {
  const stateActors = [victim, attacker];
  const started = victim.romDriver?.tryStartXSpecial(victim, stateActors);
  assert(started === true, "ported ROM special did not take action ownership");
  assert(victim.cooldowns["romSpecialActive"] === 1, "ROM ownership latch was not armed");

  const victimStats = stats.find((entry) => entry.id === victim.borgId);
  const attackerStats = stats.find((entry) => entry.id === attacker.borgId);
  assert(victimStats, `missing stats for ${victim.borgId}`);
  assert(attackerStats, `missing stats for ${attacker.borgId}`);
  victim.hp = 1;
  victim.invincTimer = 0;
  const damage = applyHit(
    victim,
    buildProfile(victimStats),
    1,
    0,
    { x: 1, y: 0, z: 0 },
    attacker.pos,
    true,
    undefined,
    {
      attacker,
      attackerProfile: buildProfile(attackerStats),
      aimedTargetUid: victim.uid,
    },
  );
  assert(damage > 0, "lethal hit dealt no damage");
  assert(victim.hp === 0 && victim.state === "death", "lethal hit did not enter death");
}

function assertReplacementAndExactlyOnceAccounting(stats: readonly BorgStats[]): void {
  const { battle, victim, attacker, inputs } = setupBattle(stats, true);
  killDuringRomSpecial(stats, victim, attacker);

  battle.step(1 / 60, inputs);
  let state = battleStateForSelfcheck(battle);
  assert(victim.state === "death" && victim.stateTime === 1, "ROM ownership consumed death frame 1");
  assert(victim.cooldowns["romSpecialActive"] === 0, "lethal lifecycle did not cancel ROM ownership");
  assert(victim.defeatAccounted, "kill event was not force-accounted");

  for (let frame = 1; frame < STATE.DEATH_DURATION + 5 && victim.alive; frame += 1) {
    battle.step(1 / 60, inputs);
  }
  state = battleStateForSelfcheck(battle);
  const replacement = state.borgs.find((actor) => actor.team === 0 && actor.uid !== victim.uid);
  const victimCost = buildProfile(stats.find((entry) => entry.id === victim.borgId)!).energy;
  const replacementCost = buildProfile(stats.find((entry) => entry.id === "pl000c")!).energy;

  assert(!victim.alive, "death lifecycle never reached alive=false");
  assert(replacement?.borgId === "pl000c", "next force member was not deployed");
  assert(state.result === "ongoing", `replacement battle settled early as ${state.result}`);
  assert(state.energy[0] === replacementCost, "force energy did not retain exactly the replacement cost");
  assert(state.defeated[0] === 1, "defeated count was not exactly one");
  assert(state.defeatedEnergy[0] === victimCost, "defeated energy was not exactly the victim cost");
  assert(state.defeats?.filter((entry) => entry.victimTeam === 0).length === 1, "defeat list duplicated victim");
  assert(victim.deaths === 1, "ROM death accounting ran more or less than once");
  assert(attacker.kills === 1, "killer accounting ran more or less than once");
  assert(state.telemetry?.slots?.p2?.kills === 1, "persistent killer slot was not credited exactly once");
  assert(state.telemetry?.slots?.p1?.costLost === victimCost, "victim slot lost the wrong force cost");

  for (let frame = 0; frame < 10; frame += 1) battle.step(1 / 60, inputs);
  state = battleStateForSelfcheck(battle);
  assert(state.defeated[0] === 1, "defeated count changed after deployment");
  assert(state.defeats?.filter((entry) => entry.victimTeam === 0).length === 1, "defeat list changed after deployment");
}

function assertFinalDeathSettlesResult(stats: readonly BorgStats[]): void {
  const { battle, victim, attacker, inputs } = setupBattle(stats, false);
  killDuringRomSpecial(stats, victim, attacker);

  for (let frame = 0; frame < STATE.DEATH_DURATION + 5; frame += 1) {
    battle.step(1 / 60, inputs);
    if (battle.observe().result !== "ongoing") break;
  }
  const state = battleStateForSelfcheck(battle);
  assert(!victim.alive, "final death settled the result before alive=false");
  assert(state.energy[0] === 0, "destroyed force retained energy");
  assert(state.result === "lose", `final death did not settle player loss: ${state.result}`);
  assert(state.defeated[0] === 1, "final defeat was not counted exactly once");
  assert(state.defeats?.filter((entry) => entry.victimTeam === 0).length === 1, "final defeat list duplicated victim");
}

function assertFinalKillNearTimeoutFinishesDeathFirst(stats: readonly BorgStats[]): void {
  const timeoutFrame = STATE.SPAWN_DURATION + 2;
  const { battle, victim, attacker, inputs } = setupBattle(stats, false, timeoutFrame);
  killDuringRomSpecial(stats, victim, attacker);

  for (let frame = 0; frame < STATE.DEATH_DURATION + 5 && victim.alive; frame += 1) {
    const observation = battle.step(1 / 60, inputs);
    if (victim.alive) {
      assert(observation.result === "ongoing", `timeout preempted pending final death as ${observation.result}`);
    }
  }
  const state = battleStateForSelfcheck(battle);
  assert(!victim.alive, "final kill near timeout never completed death lifecycle");
  assert(state.result === "lose", `final kill near timeout settled as ${state.result}`);
  assert(state.winnerMask === 2, `final kill near timeout produced winner mask ${String(state.winnerMask)}`);
  assert(state.defeated[0] === 1, "final kill near timeout was not counted exactly once");
}

function assertReplacementNearTimeoutDeploysBeforeDraw(stats: readonly BorgStats[]): void {
  const timeoutFrame = STATE.SPAWN_DURATION + 2;
  const { battle, victim, attacker, inputs } = setupBattle(stats, true, timeoutFrame);
  killDuringRomSpecial(stats, victim, attacker);

  for (let frame = 0; frame < STATE.DEATH_DURATION + 5 && victim.alive; frame += 1) {
    const observation = battle.step(1 / 60, inputs);
    if (victim.alive) {
      assert(observation.result === "ongoing", `timeout preempted replacement death as ${observation.result}`);
    }
  }
  const state = battleStateForSelfcheck(battle);
  assert(!victim.alive, "replacement kill near timeout never completed death lifecycle");
  const replacement = state.borgs.find((actor) => actor.team === 0 && actor.uid !== victim.uid);
  const replacementCost = buildProfile(stats.find((entry) => entry.id === "pl000c")!).energy;
  assert(replacement?.borgId === "pl000c", "timeout settled before replacement deployment");
  assert(state.energy[0] === replacementCost, "replacement energy was not recomputed before timeout");
  assert(state.result === "draw", `replacement near timeout did not settle draw: ${state.result}`);
  assert(state.winnerMask === 4, `replacement timeout produced winner mask ${String(state.winnerMask)}`);
  assert(state.defeated[0] === 1, "replacement timeout defeat was not counted exactly once");
}

function assertNonRomAirborneDeathKeepsGravity(stats: readonly BorgStats[]): void {
  const { battle, victim, inputs } = setupBattle(stats, false);
  victim.romDriver = null;
  victim.hp = 0;
  victim.state = "death";
  victim.stateTime = 0;
  victim.pos.y = 100;
  victim.vel.y = -2;
  victim.grounded = false;
  const beforeY = victim.pos.y;
  const beforeVelocityY = victim.vel.y;

  battle.step(1 / 60, inputs);
  assert(victim.stateTime === 1, "non-ROM death lifecycle did not advance exactly one frame");
  assert(victim.vel.y < beforeVelocityY, "non-ROM airborne death did not apply gravity");
  assert(victim.pos.y < beforeY, "non-ROM airborne death did not integrate vertical position");
}

export function runSelfTest(): void {
  runSourceFloatSelfTest();
  runFObjLinearSelfTest();
  runFObjListSelfTest();
  runFObjDescriptorSelfTest();
  runAnimationRequestSelfTest();
  runFObjDataSelfTest();
  runFObjTimingSelfTest();
  runFObjCallbackSelfTest();
  runJObjUpdateSelfTest();
  runJObjAnimationSelfTest();
  runAObjEndCallbackSelfTest();
  runJObjTreeSelfTest();
  runDObjAnimationSelfTest();
  runPObjAnimationSelfTest();
  runMObjAnimationSelfTest();
  runDisplayAnimationSelfTest();
  runTObjUpdateSelfTest();
  runTObjAnimationSelfTest();
  runTextureAnimationSelfTest();
  runJointAnimationFeedbackSelfTest();
  runActorJointMappingSelfTest();
  runDescriptorAnimationSelfTest();
  runRequestedAnimationSelfTest();
  runAttachedJointSetupSelfTest();
  runAttachedSetupAnimationSelfTest();
  runActorAnimationDispatchSelfTest();
  runSourceStreamWaitSelfTest();
  runStreamWaitTargetSelfTest();
  runJObjFlagsSelfTest();
  runJObjFlagsAnimationSelfTest();
  runJObjTrackOrderSelfTest();
  runTrackOrderAnimationSelfTest();
  runAObjClockSelfTest();
  runAObjFrameSettersSelfTest();
  runAllocatedAObjDescriptorSelfTest();
  runAnimationArchiveBankSelfTests();
  runActorAnimationSetupSelfTests();
  runActorAnimationTransitionSelfTests();
  runActorFrameLifecycleSelfTests();
  runActorDoublePrehookSelfTests();
  runActorDoubleActionSelfTests();
  runActorFrameSuffixSelfTests();
  runActorMovementFollowupSelfTests();
  runActorAttributeRefreshSelfTests();
  runAnimationArchiveHydrationSelfTest();
  runJObjModelHydrationSelfTest();
  runActorJointMatrixSelfTests();
  runActorTerrainQuerySelfTests();
  runActorTransformHistorySelfTests();
  runActorMatrixUpdateSelfTests();
  runActorWorldMatrixSelfTests();
  runDisplayAnimationAttachmentSelfTest();
  runAnimationDescriptorBankSelfTests();
  runAnimationSetupMetadataSelfTests();
  runArchivePublicSelfTests();
  runArchiveJointSetupSelfTest();
  runAObjLifecycleSelfTest();
  runJObjAddAnimationSelfTest();
  runAllocatedAObjReplacementSelfTest();
  runActorJointScalingSelfTest();
  runAnimationRequestTreeSelfTest();
  runAnimationRequestTreePlaybackSelfTest();
  runFObjRemovalSelfTest();
  runActorDispatchOrderSelfTest();
  runNinjaXStreamSelfTest();
  runNinjaXSelfTest();
  runNinjaShurikenFlightSelfTest();
  runNinjaProjectileSelfTest();
  runDoubleCloneLifecycleSelfTest();
  runDoubleCloneReactionSelfTest();
  runDoubleCloneReactionFrameSelfTest();
  runDoubleCloneContactSelfTest();
  runDoubleCloneReactionObservationBattleSelfTest();
  runDoubleCloneReactionObservationSelfTest();
  runDoubleNinjaXEngineSelfTest();
  runDoubleNinjaChargeStreamSelfTest();
  runDoubleNinjaXInputSelfTest();
  runDoubleNinjaXBattleSelfTest();
  runNinjaXBattleSelfTest();
  runTeleportXBattleSelfTest();
  runSwitchingXStreamSelfTest();
  runSwitchingXSelfTest();
  runSwitchingFieldSelfTest();
  runSwitchingXBattleSelfTest();
  runTeleportXEngineSelfTest();
  runTeleportXSelfTest();
  runHealingContactSelfTest();
  runNurseStreamSelfTest();
  runNurseBattleSelfTest();
  runHitDrainSelfTest();
  runContactAuraSelfTest();
  runDiverAuraSelfTest();
  runPoweredChargeSelfTest();
  runGatlingBattleSelfTest();
  runArrowBattleSelfTest();
  runRevolverBattleSelfTest();
  runTimeBomberBattleSelfTest();
  runTimeBomberAirBattleSelfTest();
  runTimeBomberWalkBattleSelfTest();
  runTimeBomberMineSelfTest();
  runTimeBomberMineBattleSelfTest();
  runBeamMineBattleSelfTest();
  runMeleeMineBattleSelfTest();
  runGredMeleeConfigSelfTest();
  runNeoMeleeStreamSelfTest();
  runGblackMeleeStreamSelfTest();
  runGblackGroundWaveSelfTest();
  runGblackMeleeBattleSelfTest();
  runGredMeleeStreamSelfTest();
  runGredMeleeBattleSelfTest();
  runGredCrashMotionSelfTest();
  runGredCrashStreamSelfTest();
  runGredCrashBattleSelfTest();
  runGredFamilyCrashStreamSelfTest();
  runGredFamilyCrashBattleSelfTest();
  runGredAirCrashBattleSelfTest();
  runGredAirMeleeEngineSelfTest();
  runGredAirMeleeStreamSelfTest();
  runGredAirMeleeBattleSelfTest();
  runGblackAirMeleeStreamSelfTest();
  runGblackAirMeleeBattleSelfTest();
  runNeoAirMeleeStreamSelfTest();
  runGredChargeEngineSelfTest();
  runGRedChargeStreamSelfTest();
  runGredChargeBattleSelfTest();
  runGredShotCarrySelfTest();
  runGredRangedCarryBattleSelfTest();
  runGredRangedFlightSelfTest();
  runGredShotBattleSelfTest();
  runGredShotTimingBattleSelfTest();
  runSharedXCarrySelfTest();
  runSharedXCarryBattleSelfTest();
  runGredAirShotBattleSelfTest();
  runGredAirShotEngineSelfTest();
  runGredAirShotLowerStreamSelfTest();
  runGredShotEngineSelfTest();
  runGredShotStreamSelfTest();
runGredRangedProjectileSelfTest();
  runGblackChargeEngineSelfTest();
  runGBlackChargeStreamSelfTest();
  runGBlackChargeProjectileSelfTest();
  runGblackChargeBattleSelfTest();

  runNeoAirMeleeBattleSelfTest();
  runNeoGredFinisherSelfTest();
  runNeoGredMeleeBattleSelfTest();
  runBeamBattleSelfTest();
  runSourcePositionHistorySelfTest();
  runKnightWindupSelfTest();
  runPrimaryAmmoSelfTest();
  runTargetLockSelfTest();
  const stats = loadStats();
  runRomCollisionSelfTest();
  assertReplacementAndExactlyOnceAccounting(stats);
  assertFinalDeathSettlesResult(stats);
  assertFinalKillNearTimeoutFinishesDeathFirst(stats);
  assertReplacementNearTimeoutDeploysBeforeDraw(stats);
  assertNonRomAirborneDeathKeepsGravity(stats);
  runActorStatusTimersSelfTests();
  runActorGaugeScaleSelfTests();
  runActorTickPrefixSelfTests();
  runActorStageBoundsSelfTests();
  runActorCueResetSelfTests();
  runActorInputPrefixSelfTests();
  runActorInputMachineSelfTests();
  runActorInputChargeSelfTests();
  runActorControlLifecycleSelfTests();
  runActorReadyTransitionsSelfTests();
  runActorActionRequestSelfTests();
  runActorRateLifecycleSelfTests();
  runActorCeilingLifecycleSelfTests();
  runActorTierLifecycleSelfTests();
  runActorNormalLifecycleSelfTests();
  runActorRotationDampingSelfTests();
  runActorCue0LifecycleSelfTests();
  runActorCue0TailSelfTests();
  runActorCommandAdmissionSelfTests();
  runActorInputTestersSelfTests();
  runActorChargeEffectsSelfTests();
  runActorInputAxisSelfTests();
  runSourceInputAngleSelfTests();
  runSourceInputAtanSelfTests();
  runSourceFloat64SelfTests();
  console.log("[lifecycle.selftest] PASS: lethal ROM ownership interruption, deployment, accounting, and result settlement");
}

if (import.meta.url === `file://${process.argv[1]}` || process.argv[1]?.endsWith("lifecycle.selftest.js")) {
  runSelfTest();
}

import {runActorCueResetSelfTests} from './rom/actor-cue-reset.selftest.js';
