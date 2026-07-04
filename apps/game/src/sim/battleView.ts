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
  /** The CURRENT melee swing's (or charged release's) exact action-script anim target
   *  (mot.bin bank group/slot), when combat.ts's combo-ladder step / air-B leaf / charge leaf
   *  resolved one (@gf/combat actionStreamData.ts ComboStep/ExactMoveLeaf.animStreamRef).
   *  Null/undefined when unresolved — battleScene falls back to the existing generic
   *  melee/melee_alt/charge_shot slot heuristic. */
  meleeAnimStream: BorgRuntime["meleeAnimStream"];
  /** The CURRENT swing/release's PATH-B authored sound events (DERIVED, @gf/combat
   *  BorgRuntime.meleeSounds — frame = ROM anim-clock frame, id = soundId/se_<hex> key axis).
   *  Null when the swing has none; the SFX layer keeps its TUNED slot-keyed fallback then. */
  meleeSounds: BorgRuntime["meleeSounds"];
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
    meleeAnimStream: borg.meleeAnimStream,
    meleeSounds: borg.meleeSounds,
  };
}
