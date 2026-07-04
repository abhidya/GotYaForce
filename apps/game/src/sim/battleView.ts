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
  /** impactEffectId (damage record u8 +0x09) of the most recent hit applied to this borg —
   *  DERIVED contact-effect selector (chunk_0003.c:8087-8156 -> zz_0019550_ -> effect-def
   *  table 0x802c7ed0). battleScene maps it to an FX style on hit-slot entry. */
  lastHitImpactEffectId: BorgRuntime["lastHitImpactEffectId"];
  /** Attacker team of that hit (the ROM's variant-1 hit burst picks its particle texture by
   *  the ATTACKER's player index — FUN_80019a14, chunk_0002.c:1750-1758). */
  lastHitAttackerTeam: BorgRuntime["lastHitAttackerTeam"];
  /** Slow-on-hit s16 timer (ROM +0x710, 900f seed — @gf/combat types.ts). While > 0 the
   *  renderer shows the DERIVED zz_013f300_(t,0) status aura (blue pulsing clock), exactly
   *  the window the ROM's FX object lives for (FUN_8013f548 dies when the timer hits 0). */
  slowHitTimer: number;
  /** Haste-on-hit s16 timer (ROM +0x712) — zz_013f300_(t,1) aura (orange pulsing clock). */
  hasteHitTimer: number;
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
    lastHitImpactEffectId: borg.lastHitImpactEffectId,
    lastHitAttackerTeam: borg.lastHitAttackerTeam,
    slowHitTimer: borg.slowHitTimer ?? 0,
    hasteHitTimer: borg.hasteHitTimer ?? 0,
  };
}
