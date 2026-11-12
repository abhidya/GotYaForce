/** Source 80084600 adapter, scoped to Revolver/Billy action2. Owner-local model11
 * remains generic shell art. HIT shape/target centers use existing host geometry. */
import type { BorgRuntime, Projectile } from './types.js';
import type { RomActor } from './rom/actor.js';
import { activeSourceTarget } from './targetLock.js';
import { actorAimTarget, livingAttackTarget } from './sourceAttackTarget.js';
import { tierSizeScale } from './timescale.js';
import { attackHitRecordsForKind } from './attackHitData.js';
import { familyDamageRecordForBorg } from './familyDamageData.js';
import { SHOT } from './constants.js';
import {
  createRevolverShot, stepRevolverShot, revolverMuzzle,
  type RevolverShotState, type RevolverRow, type RevolverBasis, type RevolverVec3,
} from './revolverProjectile.js';

export type RevolverSourceState = {
  kind: 'pending';
  row: RevolverRow;
  pos: RevolverVec3;
  yaw: number;
  ownerScale: number;
  ownerPitch: number;
  targetUid: string | null;
  trackingEnabled: boolean;
  ownerBorgId: string;
} | {
  kind: 'flight';
  flight: RevolverShotState;
  ownerBorgId: string;
};
export type RevolverPresentationSink = (
  owner: Pick<BorgRuntime, 'uid' | 'team'>,
  event: { pos: RevolverVec3; basis: RevolverBasis; baseScale: number },
) => void;
export const isRevolver = (id: string): boolean => id === 'pl0100' || id === 'pl0108';
let serial = 0;

export function stepRevolverInput(owner: BorgRuntime, held: boolean) {
  const input = owner.revolverInput ??= { held: false, pressEdge: false, pending: false };
  input.pressEdge = held && !input.held;
  input.held = held;
  input.pending = true;
  return input;
}

export function captureRevolverAttack(owner: BorgRuntime, actor: RomActor, all: readonly BorgRuntime[]): void {
  const target = actorAimTarget(activeSourceTarget(owner, all));
  const origin = owner.sourceFramePose?.pos ?? actor.pos;
  // Enemy/ally base descriptor ranges are both 6000, verified separately.
  const inRange = !!target && Math.hypot(
    target.pos.x - origin.x, target.pos.y - origin.y, target.pos.z - origin.z,
  ) <= 6000;
  owner.revolverAttack = {
    targetUid: target?.uid ?? null,
    pos: { ...(target?.pos ?? origin) },
    trackingEnabled: inRange,
  };
}

function flightTarget(target: BorgRuntime | undefined | null) {
  return livingAttackTarget(target) ? {
    uid: target.uid,
    pos: { ...target.pos },
    scale: tierSizeScale(target),
    radius: SHOT.TARGET_BODY_RADIUS * tierSizeScale(target),
  } : null;
}

export function spawnRevolverSource(
  owner: BorgRuntime, actor: RomActor, address: number, row: number,
): Projectile[] | null {
  if (!isRevolver(owner.borgId) || actor.actionIndex !== 2 || address !== 0x80084600) return null;
  if (!(owner.borgId === 'pl0100' ? [0, 1] : [13, 14]).includes(row)) return [];
  const aim = owner.revolverAttack;
  if (!aim) return [];
  const typedRow = row as RevolverRow;
  const yaw = actor.heading * Math.PI / 32768;
  const ownerScale = actor.modelScale * actor.sizeScale;
  const pos = revolverMuzzle(typedRow, actor.pos, yaw, ownerScale);
  const hit = attackHitRecordsForKind(owner.borgId, 0)[0];
  const damageRecord = hit && familyDamageRecordForBorg(owner.borgId, hit.damageRecordIndex);
  if (!hit || !damageRecord) return [];
  return [{
    uid: `revolver-${++serial}`, ownerUid: owner.uid, team: owner.team,
    pos: { ...pos }, vel: { x: 0, y: 0, z: 0 }, life: 600,
    damage: 1, hitstun: 0, knockback: 1, damageRecord,
    homingTurn: 0, homingTarget: null, aimedTargetUid: aim.targetUid,
    hitRadius: Math.max(hit.radius, ...hit.halfExtent) * ownerScale,
    visualKind: 'energy', romShotKind: 0, sourceHitCollisionFlags: hit.collisionFlags,
    romScale: [ownerScale, ownerScale, ownerScale],
    // Never attach global efct11: 0x400b selects this owner's weapon bank.
    revolverSource: {
      kind: 'pending', row: typedRow, pos: { ...pos }, yaw, ownerScale,
      ownerPitch: actor.bodyPitch * Math.PI / 32768,
      targetUid: aim.targetUid, trackingEnabled: aim.trackingEnabled, ownerBorgId: owner.borgId,
    },
  }];
}

export function advanceRevolverSource(
  pr: Projectile, byUid: Map<string, BorgRuntime>, onLaunch?: RevolverPresentationSink,
): Projectile[] {
  const source = pr.revolverSource!;
  const owner = byUid.get(pr.ownerUid);
  if (owner && (!livingAttackTarget(owner) || owner.borgId !== source.ownerBorgId)) {
    pr.despawnReason = 'owner-dead';
    return [];
  }
  if (source.kind === 'pending') {
    // Actors enqueue children first; object initialization occurs after all actors.
    // The target center here is current, not actor +518's pre-movement snapshot.
    const target = flightTarget(source.targetUid ? byUid.get(source.targetUid) : null);
    const flight = createRevolverShot(
      source.row, source.pos, source.yaw, target, source.ownerScale, source.trackingEnabled, source.ownerPitch,
    );
    pr.revolverSource = { kind: 'flight', flight, ownerBorgId: source.ownerBorgId };
    pr.aimedTargetUid = target?.uid ?? null;
    onLaunch?.({ uid: pr.ownerUid, team: pr.team }, {
      pos: { ...flight.pos }, basis: structuredClone(flight.launchBasis), baseScale: flight.ownerScale,
    });
    // No flight update, lifetime decrement or displacement in constructor.
  } else {
    const target = flightTarget(source.flight.targetUid ? byUid.get(source.flight.targetUid) : null);
    const next = stepRevolverShot(source.flight, target);
    if (!next.alive) {
      pr.despawnReason = 'expired';
      return [];
    }
    pr.revolverSource = { ...source, flight: next.state };
  }
  const state = pr.revolverSource;
  if (state.kind === 'flight') {
    pr.pos = { ...state.flight.pos };
    pr.vel = { ...state.flight.vel };
    pr.life = state.flight.life;
    pr.romScale = [state.flight.scale, state.flight.scale, state.flight.scale];
  }
  return [pr];
}
