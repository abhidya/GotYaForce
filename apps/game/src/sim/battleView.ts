import type { BorgRuntime, Vec3 } from "@gf/combat";

export interface BattleActorView {
  uid: string;
  borgId: string;
  team: number;
  ownerPlayer: BorgRuntime["ownerPlayer"];
  alive: boolean;
  state: BorgRuntime["state"];
  anim: BorgRuntime["anim"];
  pos: Vec3;
  vel: Vec3;
  rotY: number;
  lockTarget: string | null;
  allyLockTarget: string | null;
  dashActiveFrames: number;
  chargeFrames: number;
}

export function battleActorView(borg: BorgRuntime): BattleActorView {
  return {
    uid: borg.uid,
    borgId: borg.borgId,
    team: borg.team,
    ownerPlayer: borg.ownerPlayer,
    alive: borg.alive,
    state: borg.state,
    anim: borg.anim,
    pos: borg.pos,
    vel: borg.vel,
    rotY: borg.rotY,
    lockTarget: borg.lockTarget,
    allyLockTarget: borg.allyLockTarget,
    dashActiveFrames: borg.cooldowns["dashActive"] ?? 0,
    chargeFrames: borg.cooldowns["chargeFrames"] ?? 0,
  };
}
