/** Bounded host adapter for family29 type2 / appearance10. Static bind pose,
 * spherical/swept contact and Math.sin remain explicit presentation/geometry seams.
 * The pure child lifecycle owns source update ordering and resource-return events.
 */
import type { Vec3 } from '@gf/physics';
import type { BorgRuntime, Projectile } from './types.js';
import type { RomActor } from './rom/actor.js';
import { createTimeBomberMine, type TimeBomberMineState } from './timeBomberMine.js';
import { attackHitRecordsForKind } from './attackHitData.js';
import { familyDamageRecordForBorg } from './familyDamageData.js';
export interface TimeBomberMineSource extends TimeBomberMineState {
  kind: 'mine'; ownerBorgId: string; ownerScale: number;
  contactPending: boolean; hitUids: string[]; receivedAttackUids: string[];
}
let serial = 0;
/** Row10 joint8 bind-world translation plus appearance10 local offset. Animated attachment is not yet exposed. */
export function timeBomberMinePose(pos: Vec3, yaw: number, scale = 1): { pos: Vec3; direction: Vec3 } {
  const x = 39.99942827224688, y = 162.00003814697266, z = .0000027059288554;
  return { pos: { x: pos.x + (x * Math.cos(yaw) + z * Math.sin(yaw)) * scale,
    y: pos.y + y * scale, z: pos.z + (-x * Math.sin(yaw) + z * Math.cos(yaw)) * scale },
    direction: { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) } };
}
export function spawnTimeBomberMine(owner: BorgRuntime, actor: RomActor): Projectile {
  const scale = actor.modelScale * actor.sizeScale;
  const pose = timeBomberMinePose(actor.pos, actor.heading * Math.PI * 2 / 65536, scale);
  const state: TimeBomberMineSource = { ...createTimeBomberMine(pose.pos, pose.direction), kind: 'mine',
    ownerBorgId: owner.borgId, ownerScale: scale, contactPending: false, hitUids: [], receivedAttackUids: [] };
  const hit = attackHitRecordsForKind('pl0106', 15)[0]!;
  const record = familyDamageRecordForBorg('pl0106', hit.damageRecordIndex)!;
  return { uid: `time-bomber-mine-${++serial}`, ownerUid: owner.uid, team: owner.team,
    pos: { ...pose.pos }, vel: { x: 0, y: 0, z: 0 }, life: 0, damage: 1, hitstun: 0, knockback: 1,
    damageRecord: record, homingTurn: 0, homingTarget: null, aimedTargetUid: null,
    hitRadius: Math.max(hit.radius, ...hit.halfExtent) * scale, visualKind: 'energy', romShotKind: 15,
    sourceHitCollisionFlags: hit.collisionFlags, sourceSelfContactEnabled: false, romScale: [scale, scale, scale], timeBomberSource: state };
}
export function isLiveTimeBomberMine(pr: Projectile): boolean {
  return pr.timeBomberSource?.kind === 'mine' && pr.timeBomberSource.phase === 'active';
}
