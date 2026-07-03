import type { Battle, BorgActionProfile, BorgRuntime } from "@gf/combat";
import type { AnimSlot } from "./battleScene.js";
import type { HudState } from "../ui/index.js";

export type BattleEventCue = AnimSlot | "lockon" | "charge_release" | "alert";

export interface BattleAudioBorgSnapshot {
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
}

export function snapshotBattleAudio(battle: Battle, localPlayerId: string, allyMax: number): BattleAudioSnapshot {
  const borgs = new Map<string, BattleAudioBorgSnapshot>();
  for (const b of battle.state.borgs) {
    borgs.set(b.uid, {
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
  return {
    borgs,
    localActiveUid: battle.state.activeUidByPlayer[localPlayerId] ?? null,
    allyAlert: allyEnergy > 0 && allyEnergy <= allyMax * 0.25,
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

export interface BattleHudPresentationInput {
  battle: Battle;
  focus: BorgRuntime | null;
  actionProfile: BorgActionProfile | null;
  allyMax: number;
  enemyMax: number;
  defaultBorgId: string;
}

export function battleHudState(input: BattleHudPresentationInput): HudState {
  const { battle, focus, actionProfile, allyMax, enemyMax, defaultBorgId } = input;
  const st = battle.state;
  const ammoMax = actionProfile?.shot?.ammoMax ?? 0;
  const specialCooldownMax = actionProfile?.special.cooldown ?? 90;
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
    timeRemainingFrames: st.timeRemainingFrames,
    alert: (st.energy[0] ?? 0) > 0 && (st.energy[0] ?? 0) <= allyMax * 0.25,
  };
}

function clamp01(v: number): number {
  return v < 0 ? 0 : v > 1 ? 1 : v;
}
