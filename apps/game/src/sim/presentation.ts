import type { Battle, BorgActionProfile, BorgRuntime, MeleeActionDef, Projectile } from "@gf/combat";
import { JUMP, MELEE } from "@gf/combat";
// Deep source imports: BURST (METER_MAX, Q4/findings §S) and the contextual-B melee engage
// test are not re-exported from the package index this wave (index.ts belongs to the combat
// workstream), so the HUD layer reads them straight from the sources. Both are read-only
// consumers; no combat behavior is duplicated here.
import { BURST } from "@gf/combat/src/constants";
import { targetWithinMeleeEngage } from "@gf/combat/src/combat";
import type { BattleOutcome } from "@gf/missions";

const BOOST_FUEL_FRAMES = JUMP.BOOST_FUEL_FRAMES;
import type { AnimSlot } from "./battleScene.js";
import type { HudState } from "../ui/index.js";

export type BattleEventCue =
  | AnimSlot
  | "lockon"
  | "charge_start"
  | "charge_tier1"
  | "charge_tier2"
  | "charge_release"
  | "alert";

export interface BattleAudioBorgSnapshot {
  borgId: string;
  hp: number;
  alive: boolean;
  state: BorgRuntime["state"];
  anim: string;
  lockTarget: string | null;
  allyLockTarget: string | null;
  chargeFrames: number;
}

export interface BattleAudioSnapshot {
  borgs: Map<string, BattleAudioBorgSnapshot>;
  localActiveUid: string | null;
  allyAlert: boolean;
  /**
   * Local active borg's hold-B charge tier thresholds (frames), read from its action profile's
   * shot def (chargeTier1Frames/chargeTier2Frames, packages/combat actionProfiles.ts — the same
   * per-profile values combat.ts stepAttacks compares chargeFrames against on release). 0 when
   * no profile accessor was supplied or the borg has no chargeable shot, which suppresses the
   * tier-crossing cues in battleAudioEvents.
   */
  localChargeTier1: number;
  localChargeTier2: number;
}

export function snapshotBattleAudio(
  battle: Battle,
  localPlayerId: string,
  allyMax: number,
  actionProfileFor?: (borgId: string) => BorgActionProfile | null,
): BattleAudioSnapshot {
  const borgs = new Map<string, BattleAudioBorgSnapshot>();
  for (const b of battle.state.borgs) {
    borgs.set(b.uid, {
      borgId: b.borgId,
      hp: b.hp,
      alive: b.alive,
      state: b.state,
      anim: b.anim,
      lockTarget: b.lockTarget,
      allyLockTarget: b.allyLockTarget,
      chargeFrames: b.cooldowns?.["chargeFrames"] ?? 0,
    });
  }
  const allyEnergy = battle.state.energy[0] ?? 0;
  const localActiveUid = battle.state.activeUidByPlayer[localPlayerId] ?? null;
  // Resolve charge tier thresholds for the LOCAL borg only (the only borg whose charge cues
  // are audible, mirroring the charge_release scoping below). actionProfileForProfile caches
  // per profile upstream, so this per-step lookup is cheap and allocation-free.
  const localBorg = localActiveUid ? battle.state.borgs.find((b) => b.uid === localActiveUid) ?? null : null;
  const localShot = localBorg && actionProfileFor ? actionProfileFor(localBorg.borgId)?.shot ?? null : null;
  const localChargeable = localShot?.chargeable === true;
  return {
    borgs,
    localActiveUid,
    allyAlert: allyEnergy > 0 && allyEnergy <= allyMax * 0.25,
    localChargeTier1: localChargeable ? localShot.chargeTier1Frames : 0,
    localChargeTier2: localChargeable ? localShot.chargeTier2Frames : 0,
  };
}

export function battleAudioEvents(before: BattleAudioSnapshot, after: BattleAudioSnapshot): BattleEventCue[] {
  const events: BattleEventCue[] = [];
  const emitted = new Set<BattleEventCue>();
  const emit = (cue: BattleEventCue): void => {
    if (emitted.has(cue)) return;
    emitted.add(cue);
    events.push(cue);
  };

  const localNext = after.localActiveUid ? after.borgs.get(after.localActiveUid) ?? null : null;
  const localPrev = after.localActiveUid ? before.borgs.get(after.localActiveUid) ?? null : null;
  if (localNext && localPrev) {
    if (localNext.state === "death" && localPrev.state !== "death") emit("death");
    else if (localNext.state === "down" && localPrev.state !== "down") emit("down");
    else if (localNext.state === "hit" && (localPrev.state !== "hit" || localNext.hp < localPrev.hp)) emit("hit");
    else if (localNext.state === "special" && localPrev.state !== "special") emit("special");
    else if (
      localNext.state === "attack" &&
      localNext.anim === "shoot" &&
      (localPrev.state !== "attack" || localPrev.anim !== "shoot")
    ) {
      emit(localPrev.chargeFrames > 0 && localNext.chargeFrames === 0 ? "charge_release" : "shoot");
    } else if (
      localNext.state === "attack" &&
      localNext.anim === "melee" &&
      (localPrev.state !== "attack" || localPrev.anim !== "melee")
    ) {
      emit("melee");
    } else if (localNext.hp < localPrev.hp) {
      emit("hit");
    }

    if (localNext.lockTarget && localNext.lockTarget !== localPrev.lockTarget) emit("lockon");

    // Hold-B charge build-up cues, edge-detected per sim step exactly like charge_release
    // above (deterministic frame-count transitions, no wall-clock). chargeFrames accumulates
    // +1/frame while the attack button is held on a chargeable shooter and is zeroed on
    // release (packages/combat combat.ts stepAttacks, hold/release branch), so:
    //   0 -> >0            = a new hold began            -> charge_start
    //   crosses tier1/tier2 = a charge tier was reached  -> charge_tier1 / charge_tier2
    // Tier thresholds come from the borg's OWN profile via the snapshot (localChargeTier1/2,
    // packages/combat actionProfiles.ts chargeTier1Frames/chargeTier2Frames — the same values
    // the sim's release-tier comparison uses); 0 thresholds suppress the tier cues. The cap
    // at chargeTier2Frames means charge_tier2 fires exactly once per hold. No ROM audio-event
    // table exists to cite (behavior-notes.md (v)), so the EXISTENCE of these cues is TUNED
    // presentation; the thresholds themselves are the sim's.
    if (localPrev.chargeFrames === 0 && localNext.chargeFrames > 0) emit("charge_start");
    if (
      after.localChargeTier1 > 0 &&
      localPrev.chargeFrames < after.localChargeTier1 &&
      localNext.chargeFrames >= after.localChargeTier1
    ) {
      emit("charge_tier1");
    }
    if (
      after.localChargeTier2 > 0 &&
      localPrev.chargeFrames < after.localChargeTier2 &&
      localNext.chargeFrames >= after.localChargeTier2
    ) {
      emit("charge_tier2");
    }
  }

  if (after.allyAlert && !before.allyAlert) emit("alert");

  const localTargetUid = localNext?.lockTarget ?? null;
  for (const [uid, next] of after.borgs) {
    const prev = before.borgs.get(uid);
    if (uid !== localTargetUid || uid === after.localActiveUid) continue;
    if (!prev) continue;
    if (next.hp >= prev.hp && next.state === prev.state) continue;

    if (next.state === "death" && prev.state !== "death") emit("death");
    else if (next.state === "down" && prev.state !== "down") emit("down");
    else if (next.state === "hit" && (prev.state !== "hit" || next.hp < prev.hp)) emit("hit");
    else if (next.hp < prev.hp) emit("hit");
  }

  return events;
}

/**
 * Map a borg id to one of its two per-family voice-cue manifest keys.
 *
 * DERIVED from the voice-asset naming (behavior-notes.md (az)): the 46 extracted cues are keyed
 * `pl{familyByte}_00_{variant}` where the family byte is the borg id's family nibble-pair
 * (id.slice(2,4)) and variant ∈ {00, 01}. Every roster family (0x00–0x0f) has a group, so all
 * 208 roster borgs resolve (e.g. pl0615 G RED → family 06 → `pl06_00_0N`). The family→group
 * mapping is DERIVED; the cue-VARIANT role (which of 00/01 is "deploy" vs "KO") is TUNED — no
 * trace confirms it, so the caller's event→variant binding below is a documented default,
 * pending an SE/voice-dispatch trace. Returns null for a non-`pl####` id.
 */
export function voiceKeyForBorgId(borgId: string, variant: 0 | 1): string | null {
  if (!/^pl[0-9a-fA-F]{4}$/.test(borgId)) return null;
  const family = borgId.slice(2, 4).toLowerCase();
  return `pl${family}_00_0${variant}`;
}

/**
 * Per-borg VOICE cues for the frame (behavior-notes (az)). Scoped to the LOCAL player's active
 * borg only (TUNED — avoids 8-borg voice spam; the player hears their own borg's deploy shout
 * and death cry). Event→variant binding is the TUNED default from (az): a fresh deploy plays
 * cue 00, entering the death state plays cue 01. Returns manifest keys to hand straight to the
 * audio manager (playSfx falls back to the voice map). Handles same-frame death+deploy: the
 * outgoing borg's death cry (keyed on the previous-frame active uid) and the incoming borg's
 * deploy shout (keyed on the new active uid) are both emitted.
 */
export function battleVoiceCues(before: BattleAudioSnapshot, after: BattleAudioSnapshot): string[] {
  const out: string[] = [];

  // Death cry (cue 01): the borg the player controlled last frame entered "death" this frame.
  // The dead borg lingers in after.borgs (death-visual-but-accounted) so this resolves even when
  // the active slot has already switched to the auto-deployed replacement the same frame.
  const prevUid = before.localActiveUid;
  if (prevUid) {
    const deathNext = after.borgs.get(prevUid);
    const deathPrev = before.borgs.get(prevUid);
    if (deathNext && deathPrev && deathNext.state === "death" && deathPrev.state !== "death") {
      const key = voiceKeyForBorgId(deathNext.borgId, 1);
      if (key) out.push(key);
    }
  }

  // Deploy shout (cue 00): the local active-borg uid changed to a new, live borg this frame
  // (first deploy, or an auto-deploy after a KO).
  const curUid = after.localActiveUid;
  if (curUid && curUid !== before.localActiveUid) {
    const cur = after.borgs.get(curUid);
    if (cur && cur.alive && cur.state !== "death") {
      const key = voiceKeyForBorgId(cur.borgId, 0);
      if (key) out.push(key);
    }
  }

  return out;
}

export interface BattleHudPresentationInput {
  battle: Battle;
  focus: BorgRuntime | null;
  actionProfile: BorgActionProfile | null;
  allyMax: number;
  enemyMax: number;
  defaultBorgId: string;
  /** Local player id — keys burstMeterByPlayer / activeUidByPlayer for the burst gauge + DEFEATED banner. */
  localPlayerId: string;
}

export interface BattlePresentationInput {
  battle: Battle;
  localPlayerId: string;
  allyMax: number;
  enemyMax: number;
  defaultBorgId: string;
  actionProfileFor(borgId: string): BorgActionProfile | null;
}

export interface BattlePresentationState {
  activeUid: string | null;
  focus: BorgRuntime | null;
  hud: HudState;
}

export interface BattleEnergyMaxima {
  allyMax: number;
  enemyMax: number;
}

export function battleEnergyMaxima(battle: Battle): BattleEnergyMaxima {
  return {
    allyMax: battle.state.energy[0] ?? 0,
    enemyMax: battle.state.energy[1] ?? 0,
  };
}

export function activeBorgForPlayer(battle: Battle, playerId: string): BorgRuntime | null {
  const uid = battle.state.activeUidByPlayer[playerId] ?? null;
  return uid ? battle.state.borgs.find((b) => b.uid === uid) ?? null : null;
}

/**
 * Scene-facing battle snapshot. `projectiles` is deliberately the live sim array passed
 * VERBATIM (no clone): stepProjectiles mutates Projectile objects in place and writes
 * `despawnReason` on the OBJECT the frame it drops it from the list (packages/combat
 * types.ts), and BattleScene.syncProjectiles keeps per-uid references so it can read that
 * reason after removal and fire impact FX only for real impacts. Snapshotting/cloning the
 * projectile objects here would silently break that contract.
 */
export function battleSceneState(battle: Battle, focus: BorgRuntime | null): {
  borgs: readonly BorgRuntime[];
  projectiles: readonly Projectile[];
  focusUid: string | null;
} {
  return {
    borgs: battle.state.borgs,
    projectiles: battle.state.projectiles,
    focusUid: focus?.uid ?? null,
  };
}

export function liveActorPositions<T>(battle: Battle, positionOf: (uid: string) => T | null): T[] {
  return battle.state.borgs
    .filter((b) => b.alive)
    .map((b) => positionOf(b.uid))
    .filter((p): p is T => p !== null);
}

export function battleOutcomeFromState(battle: Battle): BattleOutcome {
  const st = battle.state;
  const win = st.result === "win";
  const enemyDefeated = st.defeated[1] ?? 0;
  const playerDefeated = st.defeated[0] ?? 0;
  const costWon = st.defeatedEnergy[1] ?? 0;
  const costLost = st.defeatedEnergy[0] ?? 0;
  return {
    win,
    attack: Math.round(costWon),
    hits: enemyDefeated,
    attempts: Math.max(1, enemyDefeated + 2),
    dodges: 0,
    incoming: 1,
    enemyBorgsDefeated: enemyDefeated,
    playerBorgsDefeated: playerDefeated,
    allyBorgsDefeated: 0,
    costWon,
    costLost,
  };
}

export function battlePresentationState(input: BattlePresentationInput): BattlePresentationState {
  const activeUid = input.battle.state.activeUidByPlayer[input.localPlayerId] ?? null;
  const active = activeUid ? input.battle.state.borgs.find((b) => b.uid === activeUid) ?? null : null;
  const focus = focusBorg(input.battle, active);
  return {
    activeUid,
    focus,
    hud: battleHudState({
      battle: input.battle,
      focus,
      actionProfile: focus ? input.actionProfileFor(focus.borgId) : null,
      allyMax: input.allyMax,
      enemyMax: input.enemyMax,
      defaultBorgId: input.defaultBorgId,
      localPlayerId: input.localPlayerId,
    }),
  };
}

function focusBorg(battle: Battle, active: BorgRuntime | null): BorgRuntime | null {
  if (active?.alive) return active;

  // FIGHT ALONE can leave the player slot empty while a CPU ally is still alive.
  const fallbackTeam = active?.team ?? 0;
  return (
    battle.state.borgs.find((b) => b.alive && b.team === fallbackTeam) ??
    battle.state.borgs.find((b) => b.alive) ??
    null
  );
}

export function battleHudState(input: BattleHudPresentationInput): HudState {
  const { battle, focus, actionProfile, allyMax, enemyMax, defaultBorgId, localPlayerId } = input;
  const st = battle.state;

  // Power Burst gauge (Q4 RESOLVED 2026-07-03 — research/decomp/attack-mechanics-open-
  // questions.md Q4, attack-mechanics-findings.md §S): per-PLAYER meter, ROM player struct
  // +i*0x3c: +0x126 clamped value / +0x124 max (BURST.METER_MAX = 3000) / +0x103 charged flag
  // (flips one frame after max). Fills +50 per attacker hit connection (BURST.FILL_PER_HIT).
  // Display-only until ATK-012 (BURST.ENABLED stays false); this just SURFACES the sim's
  // value — CPU-owned forces have no meter entry (documented decision in packages/combat
  // burst.ts creditBurstFill), so a missing entry reads as an empty, uncharged gauge.
  const burstMeter = st.burstMeterByPlayer[localPlayerId] ?? null;
  const burst01 = burstMeter ? clamp01(burstMeter.meter / BURST.METER_MAX) : 0;
  const burstCharged = burstMeter?.charged ?? false;

  // DEFEATED banner flag: the LOCAL player's own slot is down — their active borg is dead or
  // absent while awaiting redeploy (battle.ts deployNext keeps activeUidByPlayer pointing at
  // the dead borg until the planned respawn lands, and DELETES the key when the force is
  // exhausted), or the battle is lost outright. Gated to result === "ongoing" for the
  // awaiting-redeploy case so a win/draw on the same frame never flashes the banner. Note this
  // reads the local ACTIVE slot, not `focus` — focus falls back to a live ally (FIGHT ALONE)
  // exactly when the banner should be up.
  const localActiveUid = st.activeUidByPlayer[localPlayerId] ?? null;
  const localActive = localActiveUid ? st.borgs.find((b) => b.uid === localActiveUid) ?? null : null;
  const defeated =
    st.result === "lose" || (st.result === "ongoing" && (localActive === null || !localActive.alive));
  const ammoMax = actionProfile?.shot?.ammoMax ?? 0;
  const specialCooldownMax = actionProfile?.special.cooldown ?? 90;

  // Hold-B charge gauge (TUNED-faithful-to-sim): chargeFrames is a TUNED accumulator (combat.ts
  // stepAttacks) capped at shot.chargeTier2Frames. Read the cap from the profile; guard absent
  // key / zero cap -> 0 so the meter stays hidden for non-charge borgs.
  const chargeCap = actionProfile?.shot?.chargeTier2Frames ?? 90;
  const chargeFrames = focus?.cooldowns?.["chargeFrames"] ?? 0;
  const charge01 = chargeCap > 0 ? clamp01(chargeFrames / chargeCap) : 0;

  // Melee/"battle mode" flag: true when the focus borg has a lock target inside the contextual-B
  // melee SELECTION window — the SAME window the sim resolves B with (combat.ts
  // targetWithinMeleeEngage / meleeEngageRangeFor, i.e. MELEE.ENGAGE_RANGE widened by the borg's
  // own reach), so the yellow -> red reticle flip and the sim's melee selection agree.
  // Behavior-notes (ao), CONFIRMED_MANUAL: the target cursor flips yellow -> red at the
  // HUD-observable battle-mode threshold; the ROM's numeric threshold FLOAT_8043762c is still
  // untraced (behavior-notes (ai)/(av), T1-blocked), so MELEE.ENGAGE_RANGE remains TUNED.
  const meleeRange = focusHasMeleeRangeTarget(battle, focus, actionProfile);

  // X-ammo readout (behavior-notes (ao), CONFIRMED_MANUAL: weapon 1 = X-attack ammo, separate
  // from weapon 0 = B-attack ammo). Sourced from the focus borg's weapon cell 1 (combat.ts
  // wires the X/special attack to consume it). Only surfaced for borgs that actually have
  // X-ammo (cell max > 0, DERIVED per-borg data); undefined leaves the HUD readout hidden and
  // back-compatible, exactly like charge01/meleeRange.
  const xCell = focus?.weaponCells?.[1];
  const hasXAmmo = !!xCell && xCell.max > 0;
  const xAmmo = hasXAmmo ? Math.max(0, Math.round(xCell.cur)) : undefined;
  const xReload01 = hasXAmmo ? clamp01(xCell.cur / xCell.max) : undefined;

  // Jump Gauge (behavior-notes (ao), CONFIRMED_MANUAL: "a Jump Gauge showing multi-level jumps").
  // Discrete mid-air jumps remaining out of the borg's max (airJumpLevel). Surfaced only for borgs
  // that actually have air jumps (airJumpLevel >= 1); flyers (sustained flight) are covered by the
  // boost gauge instead, so they're excluded here. Optional/back-compatible like the other gauges.
  const jumpMax = actionProfile && !actionProfile.flyer ? actionProfile.airJumpLevel : 0;
  const jumpsMax = jumpMax >= 1 ? jumpMax : undefined;
  const jumpsRemaining =
    jumpsMax !== undefined && focus ? Math.max(0, Math.min(jumpsMax, Math.round(focus.airJumps))) : undefined;

  return {
    allyEnergy: st.energy[0] ?? 0,
    allyMax,
    enemyEnergy: st.energy[1] ?? 0,
    enemyMax,
    hp: focus?.hp ?? 0,
    maxHp: focus?.maxHp ?? 1,
    ammo: focus?.ammo ?? 0,
    reload01: focus && ammoMax > 0 ? clamp01((focus.ammo ?? 0) / ammoMax) : 0,
    cooldown01: focus
      ? focus.cooldowns?.["special"]
        ? clamp01(1 - focus.cooldowns["special"] / specialCooldownMax)
        : 1
      : 1,
    borgId: focus?.borgId ?? defaultBorgId,
    lockOn: Boolean(focus?.lockTarget),
    // Boost gauge from the tracked boostFuel cooldown (movement.ts drains it while boost-
    // flying, refills on land). Absent key = full fuel. BOOST_FUEL_FRAMES=90 is the drain
    // budget; TUNED, so the gauge faithfully reads the sim rather than a ROM-timed value.
    boost01: focus ? clamp01((focus.cooldowns?.["boostFuel"] ?? BOOST_FUEL_FRAMES) / BOOST_FUEL_FRAMES) : 1,
    charge01,
    meleeRange,
    burst01,
    burstCharged,
    defeated,
    // Conditional-spread so the keys are simply absent (not `undefined`) for borgs without
    // X-ammo — required under exactOptionalPropertyTypes, and keeps the HUD readout hidden.
    ...(xAmmo !== undefined ? { xAmmo } : {}),
    ...(xReload01 !== undefined ? { xReload01 } : {}),
    ...(jumpsMax !== undefined ? { jumpsMax } : {}),
    ...(jumpsRemaining !== undefined ? { jumpsRemaining } : {}),
    timeRemainingFrames: st.timeRemainingFrames,
    alert: (st.energy[0] ?? 0) > 0 && (st.energy[0] ?? 0) <= allyMax * 0.25,
  };
}

/**
 * TUNED melee-def stand-in for the rare case where the focus borg's action profile could not
 * be resolved at all (unknown borg id): mirrors the combat defaults (MELEE.RANGE = 60,
 * MELEE.Y_TOLERANCE = 50, actionProfiles.ts DEFAULT_MELEE) so targetWithinMeleeEngage still
 * evaluates the shared window. Display-only; the exact ROM threshold FLOAT_8043762c is
 * trace-T1-blocked per behavior-notes (ai)/(av).
 */
const MELEE_DEF_HUD_FALLBACK: MeleeActionDef = {
  startup: MELEE.STARTUP,
  active: MELEE.ACTIVE,
  duration: MELEE.DURATION,
  cooldown: MELEE.COOLDOWN,
  range: MELEE.RANGE,
  yTolerance: MELEE.Y_TOLERANCE,
  damageMultiplier: 1,
  knockbackMultiplier: 1,
  comboHits: 1,
  comboWindowFrames: 0,
  swordBeam: null,
};

/**
 * True when the focus borg's LOCK target is inside the contextual-B melee SELECTION window —
 * evaluated with the sim's own targetWithinMeleeEngage (combat.ts: XZ within
 * max(meleeDef.range, MELEE.ENGAGE_RANGE), vertical within max(meleeDef.yTolerance,
 * MELEE.ENGAGE_Y_TOLERANCE)) so the reticle's yellow -> red flip matches when B actually
 * selects melee. Behavior-notes (ao): manual-confirmed HUD-observable threshold;
 * FLOAT_8043762c untraced, so the window's numbers stay TUNED in packages/combat constants.ts.
 * A profile WITHOUT a melee def can never be resolved to battle-mode melee by the sim
 * (combat.ts resolveBActionOrder requires meleeDef), so it never flips the reticle.
 */
function focusHasMeleeRangeTarget(
  battle: Battle,
  focus: BorgRuntime | null,
  actionProfile: BorgActionProfile | null,
): boolean {
  if (!focus?.lockTarget) return false;
  const target = battle.state.borgs.find((b) => b.uid === focus.lockTarget && b.alive);
  if (!target) return false;
  if (actionProfile && !actionProfile.melee) return false; // sim cannot select melee for this borg
  const meleeDef = actionProfile?.melee ?? MELEE_DEF_HUD_FALLBACK;
  return targetWithinMeleeEngage(focus.pos, target.pos, meleeDef);
}

function clamp01(v: number): number {
  return v < 0 ? 0 : v > 1 ? 1 : v;
}
