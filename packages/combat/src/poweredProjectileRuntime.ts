/** Narrow source-spawner adapter; never resolves through the owner's generic B shot. */
import type { BorgRuntime, Projectile } from "./types.js";
import type { RomActor } from "./rom/actor.js";
import { activeSourceTarget } from "./targetLock.js";
import { tierSizeScale } from "./timescale.js";
import { attackHitRecordsForKind } from "./attackHitData.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { stepRng8 } from "./prng.js";
import { beginPoweredSecondaryShrink, createPoweredPrimary, stepPoweredPrimary, createPoweredSecondaries, stepPoweredSecondary, poweredPrimaryMuzzle, createPoweredNormalPort, poweredNormalMuzzle,
  type PoweredPrimaryState, type PoweredSecondaryState } from "./poweredProjectile.js";
let serial = 0;
export type PoweredSourceState = PoweredPrimaryState | PoweredSecondaryState;
function targetData(b: BorgRuntime | undefined | null) {
  // Source center +0x64 and owner saved aim +0x518 are not independently animated
  // in the browser. Root position is the explicitly bounded host approximation.
  // zz_007e200_ also tests (*target == 0) or (+0x83 == 0 && +0x656 != 0).
  // +0x656 is not exposed by the host: alive/HP/death approximate inactivity;
  // targetEligibility83 alone is deliberately NOT an invalidation condition.
  return b && b.alive && b.hp > 0 && b.state !== "death"
    ? { uid: b.uid, pos: { ...b.pos }, scale: tierSizeScale(b) } : null;
}
function wrap(owner: Pick<BorgRuntime,"uid"|"team">, state: PoweredSourceState, targetUid: string | null, skipAdvance = true): Projectile {
  const hitKind = state.kind === "primary" ? 15 : 0;
  const hit = attackHitRecordsForKind("pl0101", hitKind)[0];
  const record = hit ? familyDamageRecordForBorg("pl0101", hit.damageRecordIndex) : null;
  if (!record) throw new Error("Powered source family damage record 1 missing");
  return {
    uid: `powered-${++serial}`, ownerUid: owner.uid, team: owner.team,
    pos: { ...state.pos }, vel: { ...state.vel }, life: state.life,
    damage: 1, hitstun: 0, knockback: 1, damageRecord: record,
    homingTurn: 0, homingTarget: null, aimedTargetUid: targetUid,
    hitRadius: Math.max(hit!.radius, ...hit!.halfExtent), visualKind: "energy", romShotKind: hitKind,
    sourceHitCollisionFlags: hit!.collisionFlags,
    romScale: [state.scale,state.scale,state.scale],
    flightVisual: { bankTexId: state.kind === "primary" ? 125 : 26, teamTint: true, launchFxId: null },
    poweredSource: state, poweredSkipAdvance: skipAdvance,
  };
}
/** zz_006a104_ -> zz_006bda8_: save aim on admission, before the authored windup.
 * Target center is the host root approximation; no-target Y uses static joint3.
 * The source no-target X/Z are absolute world coordinates, not owner-relative.
 */
export function capturePoweredNormalAim(owner:BorgRuntime,actor:RomActor,all:readonly BorgRuntime[]):void {
  const target=targetData(activeSourceTarget(owner,all));
  const yaw=actor.heading*Math.PI*2/65536;
  owner.poweredNormalAim={targetUid:target?.uid??null,pos:target?{...target.pos}:{
    x:20000*Math.sin(yaw),
    y:actor.pos.y+actor.modelScale*actor.sizeScale*124.89293384552002,
    z:20000*Math.cos(yaw),
  }};
}
export function spawnPoweredSource(owner: BorgRuntime, actor: RomActor, addr: number, row: number,
  all: readonly BorgRuntime[]): Projectile[] | null {
  if (owner.borgId !== "pl0101") return null;
  if (actor.actionIndex === 2 && addr === 0x8016d584 && row >= 0 && row <= 3) {
    // Four port callbacks each emit four children. Rows are NOT HIT kinds.
    const aim = owner.poweredNormalAim;
    if (!aim) return []; // no invented aim or generic damaging fallback
    const yaw = actor.heading * Math.PI * 2 / 65536;
    const ownerScale = actor.modelScale * actor.sizeScale;
    const port = row as 0|1|2|3;
    const pos = poweredNormalMuzzle(port,actor.pos,yaw,ownerScale);
    return createPoweredNormalPort(port,pos,yaw,aim.pos,ownerScale,stepRng8)
      .map(state => wrap(owner,state,aim.targetUid));
  }
  if (actor.actionIndex !== 3) return null;
  if (addr === 0x800f036c && row === 6) return []; // source presentation effect, never damage
  if (addr !== 0x8007db5c || ![6,7,8,9].includes(row)) return null;
  const target = targetData(activeSourceTarget(owner, all));
  const yaw = actor.heading * Math.PI * 2 / 65536;
  const ownerScale = actor.modelScale * actor.sizeScale;
  const pos = poweredPrimaryMuzzle(row as 6|7|8|9, actor.pos, yaw, ownerScale);
  const state = createPoweredPrimary(row as 6|7|8|9, pos, yaw, target, ownerScale);
  if (state.split) return createPoweredSecondaries(state, stepRng8).map(s => wrap(owner,s,target?.uid ?? null));
  if (!state.alive) return [];
  const projectile = wrap(owner,state,target?.uid ?? null);
  projectile.poweredInitialPosition = { ...pos };
  return [projectile];
}
export function advancePoweredSource(pr: Projectile, byUid: Map<string,BorgRuntime>): Projectile[] {
  let state = pr.poweredSource!;
  const owner = byUid.get(pr.ownerUid);
  if (owner && !owner.alive) {
    if (state.kind === "primary") { pr.despawnReason = "owner-dead"; return []; }
    // 8016d95c -> 0084000: owner death ends secondary flight through shrink.
    if (state.phase === "flight") state = beginPoweredSecondaryShrink(state);
    pr.poweredSkipAdvance = false;
  }
  if (pr.poweredSkipAdvance) { pr.poweredSkipAdvance = false; return [pr]; }
  if (state.kind === "primary") {
    const next = stepPoweredPrimary(state,targetData(state.targetUid ? byUid.get(state.targetUid) : null));
    if (next.split) {
      pr.despawnReason = "expired";
      return createPoweredSecondaries(next.state,stepRng8).map(s => wrap({uid:pr.ownerUid,team:pr.team},s,pr.aimedTargetUid ?? null,false));
    }
    if (!next.alive) { pr.despawnReason = "expired"; return []; }
    pr.poweredSource = next.state;
  } else {
    const next = stepPoweredSecondary(state);
    if (!next.alive) { pr.despawnReason = "expired"; return []; }
    pr.poweredSource = next.state;
  }
  const next = pr.poweredSource;
  pr.pos = { ...next.pos }; pr.vel = { ...next.vel }; pr.life = next.life;
  pr.romScale = [next.scale,next.scale,next.scale];
  return [pr];
}
export function poweredCanCollide(pr: Projectile): boolean {
  return !pr.poweredSource || pr.poweredSource.kind === "primary" || pr.poweredSource.phase === "flight";
}

export function shrinkPoweredOnContact(pr: Projectile): boolean {
  if (pr.poweredSource?.kind !== "secondary") return false;
  pr.poweredSource = beginPoweredSecondaryShrink({ ...pr.poweredSource, pos: { ...pr.pos } });
  pr.vel = { ...pr.poweredSource.vel };
  return true;
}
