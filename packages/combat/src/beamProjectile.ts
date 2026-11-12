/** Bounded pl0104 action2 / 800e19a8 row1 plus admitted RED/NEO charge row15.
 * See beam-source-x-2026-11-12.md and gred-charged-b-2026-11-12.md.
 * Source lifecycle and pulse cadence; static joint and capsule collision are host
 * approximations. No flying-bullet lifetime, terrain consumption or global rehit timer. */
import type { BorgRuntime, Projectile, PlayerInput } from './types.js';
import type { Vec3 } from '@gf/physics';
import type { RomActor } from './rom/actor.js';
import { attackHitRecordsForKind } from './attackHitData.js';
import { familyDamageRecordForBorg } from './familyDamageData.js';
import { activeSourceTarget } from './targetLock.js';
import { actorAimTarget, livingAttackTarget } from './sourceAttackTarget.js';
import {getGRedChargeState} from './gredCharge.js';
import type { RevolverBasis } from './revolverProjectile.js';
export interface BeamOwnerState {
    dt: number;
    state: number;
    pos: Vec3;
    yaw: number;
    pitch: number;
    scale: number;
}
export interface BeamPulse {
    /** One source attack identity across this pulse's sphere and sweep passes. */
    attackUid: string;
    stage: 'init' | 'sweep';
    start: Vec3;
    end: Vec3;
    radius: number;
    hitUids: string[];
}
export interface BeamSourceState {
    /** Undefined retains the original Beam Gunner row1 adapter. */
    sourceRow?: 1 | 15;
    ownerBorgId?: string;
    ownerFormId?: string;
    phase: 'init' | 'active' | 'tail';
    age: number;
    tailAge: number;
    scale: number;
    ownerScale: number;
    origin: Vec3;
    direction: Vec3;
    drawDirection: Vec3;
    drawBasis: RevolverBasis;
    start: Vec3;
    end: Vec3;
    tailStartScale: number;
    targetUid: string | null;
    pulse: boolean;
    pulseTimer: number;
    pulses: BeamPulse[];
}
/** Original row1 and emitter literals (80317268,80438dc8..80438df0). */
export const BEAM_SOURCE = {
    spawner: 0x800e19a8,
    row: 1,
    hitKind: 10,
    maxScale: 3,
    growFrames: 15,
    tailFrames: 10,
    startOffset: 10,
    endOffset: 15110,
    aimDot: 0.9238790273666382,
    hitRadius: 30,
    jointHeight: 109.79737567901611,
    muzzleUp: 25,
    muzzleForward: 350,
} as const;
/** Original80317428/e19a8 row15. Joint1 is a verified static bind fallback,
 * never an animated attachment. Pulse HIT27/record34 has radius20/damage31. */
export const GRED_CHARGE_BEAM = {...BEAM_SOURCE,row:15,hitKind:27,maxScale:1,hitRadius:20,
    jointHeight:129.60008239746094,muzzleUp:40,muzzleForward:10} as const;
type BeamProfile=typeof BEAM_SOURCE | typeof GRED_CHARGE_BEAM;
const addAlong = (p: Vec3, d: Vec3, n: number): Vec3 => ({
    x: p.x + d.x * n, y: p.y + d.y * n, z: p.z + d.z * n,
});
export function beamMuzzle(pos: Vec3, yaw: number, scale = 1, profile:BeamProfile = BEAM_SOURCE): Vec3 {
    // Verified per-profile static joint1 bind plus row-local offset; animated pose unavailable.
    return {
        x: pos.x + Math.sin(yaw) * profile.muzzleForward * scale,
        y: pos.y + (profile.jointHeight + profile.muzzleUp) * scale,
        z: pos.z + Math.cos(yaw) * profile.muzzleForward * scale,
    };
}
function basis(yaw: number): RevolverBasis {
    return {
        right: { x: Math.cos(yaw), y: 0, z: -Math.sin(yaw) },
        up: { x: 0, y: 1, z: 0 },
        forward: { x: Math.sin(yaw), y: 0, z: Math.cos(yaw) },
    };
}
/** Raw PAD A/B/X/Y bits survive 8010d450 -> 8008bbc0 -> actor5b4.
 * Browser adapter binds jump/attack/special/hyper to PAD A/B/X/Y. Rising
 * edges match 5bc=current & ~previous; held frames never fabricate extension. */
type BeamInput = Pick<PlayerInput, 'special' | 'attack' | 'jump' | 'hyper'> &
    Partial<Pick<PlayerInput, 'moveX' | 'moveZ'>>;
export function stepBeamInput(owner: BorgRuntime, input: BeamInput) {
    const state = owner.beamInput ??= { held: false, pressEdge: false, pending: false, buttons: 0, edges: 0 };
    // Browser normalized axes do not expose physical PAD bytes. Quantize to the
    // signed-byte range here; the source octant/deadzone logic below is exact.
    const x = Math.trunc(Math.max(-1, Math.min(1, -(input.moveX ?? 0))) * 127);
    const y = Math.trunc(Math.max(-1, Math.min(1, input.moveZ ?? 0)) * 127);
    const angle = Math.trunc(Math.fround(Math.fround(Math.atan2(y, x)) * 10430.3779296875)) & 0xffff;
    const octants = [2, 10, 8, 9, 1, 5, 4, 6];
    const stick = x * x + y * y < 30 * 30 ? 0 : octants[((angle + 0x1000) >> 13) & 7]!;
    const buttons = (stick << 16) | (input.jump ? 0x100 : 0) | (input.attack ? 0x200 : 0) |
        (input.special ? 0x400 : 0) | (input.hyper ? 0x800 : 0);
    state.edges = buttons & ~state.buttons;
    state.buttons = buttons;
    state.pressEdge = input.special && !state.held;
    state.held = input.special;
    state.pending = true;
    return state;
}
export function captureBeamAim(owner: BorgRuntime, actor: RomActor, all: readonly BorgRuntime[]): void {
    const target = actorAimTarget(activeSourceTarget(owner, all));
    owner.beamAim = {
        targetUid: target?.uid ?? null,
        pos: target ? { ...target.pos } :
            addAlong(actor.pos, basis(actor.heading * Math.PI / 32768).forward, 20000),
    };
}
export function spawnBeamSource(
    owner: BorgRuntime, actor: RomActor, address: number, row: number,
): Projectile[] | null {
    const charge=getGRedChargeState(actor);
    const chargeRoute=!!charge && (owner.borgId==='pl0615'||owner.borgId==='pl0629') && actor.actionIndex===3 && actor.variantIndex===0;
    if ((!chargeRoute && (owner.borgId !== 'pl0104' || actor.actionIndex !== 2)) || address !== BEAM_SOURCE.spawner)
        return null;
    const profile=chargeRoute?GRED_CHARGE_BEAM:BEAM_SOURCE;
    if (row !== profile.row)
        return [];
    const ownerScale = actor.modelScale * actor.sizeScale, yaw = actor.heading * Math.PI / 32768;
    const origin = beamMuzzle(actor.pos, yaw, ownerScale,profile), drawBasis = basis(yaw);
    const hit = attackHitRecordsForKind(owner.borgId, profile.hitKind)[0];
    const damageRecord = hit && familyDamageRecordForBorg(owner.borgId, hit.damageRecordIndex);
    if (!hit || !damageRecord)
        return [];
    return [{
            uid: `beam-${++serial}`, ownerUid: owner.uid, team: owner.team,
            pos: { ...origin }, vel: { x: 0, y: 0, z: 0 }, life: 1,
            damage: 1, hitstun: 0, knockback: 1, damageRecord, homingTurn: 0, homingTarget: null,
            aimedTargetUid: owner.beamAim?.targetUid ?? null, hitRadius: 0, visualKind: 'energy', romShotKind: profile.hitKind,
            sourceHitCollisionFlags: hit.collisionFlags, romScale: [0, 0, 0],
            beamSource: { ...(chargeRoute?{sourceRow:15 as const,ownerBorgId:owner.borgId,ownerFormId:owner.combatFormId??owner.borgId}:{}),phase: 'init', age: 0, tailAge: 0, scale: 0, ownerScale, origin,
                direction: { ...drawBasis.forward },
                drawDirection: { ...drawBasis.forward }, drawBasis, start: { ...origin },
                end: { ...origin }, tailStartScale: 0,
                targetUid: owner.beamAim?.targetUid ?? null, pulse: false, pulseTimer: 0, pulses: [] } }];
}
let serial = 0;
let pulseSerial = 0;
export function advanceBeamSource(pr: Projectile, byUid: Map<string, BorgRuntime>): Projectile[] {
    const s = pr.beamSource!, owner = byUid.get(pr.ownerUid), pose = owner?.beamOwner;
    const profile=s.sourceRow===15?GRED_CHARGE_BEAM:BEAM_SOURCE;
    s.pulse = false;
    s.pulses = s.pulses.filter(pulse => pulse.stage === 'init');
    // Source death/form invalidation forces state2, skips active damage. Browser
    // disappearance cannot recompute the attachment, so keep its last transform.
    const invalid = !livingAttackTarget(owner) || owner.borgId !== (s.ownerBorgId??'pl0104') ||
        (s.sourceRow===15 && (owner.combatFormId??owner.borgId)!==s.ownerFormId);
    if (invalid && s.phase !== 'tail') {
        s.phase = 'tail';
        s.tailAge = 0;
        // The death wrapper jumps directly to tail without the normal stop
        // branch's c0=148 write. Its c0 still holds ownerScale*beamScale.
        s.tailStartScale = s.scale * s.ownerScale;
    }
    if (pose) {
        s.ownerScale = pose.scale;
        // Source draw follows the owner even after host hit/death takes over
        // movement and stops bridge syncOut. Missing owners keep the last pose.
        const root = owner?.pos ?? pose.pos;
        const yaw = owner?.rotY ?? pose.yaw;
        s.origin = beamMuzzle(root, yaw, s.ownerScale,profile);
        s.drawBasis = basis(yaw);
        s.drawDirection = { ...s.drawBasis.forward };
    }
    if (s.phase === 'init') {
        s.phase = 'active';
    }
    else if (s.phase === 'tail') {
        s.scale = s.tailStartScale - (++s.tailAge / profile.tailFrames) * profile.maxScale;
        if (s.scale <= 0) {
            s.scale = 0;
            // Pulse children outlive the parent's visual teardown. Preserve the
            // last sphere->sweep pass even when an early interrupt removes art.
            if (s.pulses.length === 0) {
                pr.despawnReason = 'expired';
                return [];
            }
        }
    }
    else {
        s.age++;
        if (!pose || pose.state < 1) {
            s.phase = 'tail';
            s.tailAge = 0;
            s.tailStartScale = s.scale;
        }
        else {
            s.scale = Math.min(profile.maxScale, s.age / profile.growFrames * profile.maxScale);
            s.direction = { ...s.drawDirection };
            const target = s.targetUid ? byUid.get(s.targetUid) : null;
            if (livingAttackTarget(target)) {
                const d = { x: target.pos.x - s.origin.x, y: target.pos.y - s.origin.y, z: target.pos.z - s.origin.z };
                const n = Math.hypot(d.x, d.y, d.z);
                if (n > 0) {
                    d.x /= n;
                    d.y /= n;
                    d.z /= n;
                    if (d.x * s.direction.x + d.y * s.direction.y + d.z * s.direction.z > profile.aimDot)
                        s.direction = d;
                }
            }
            else
                s.targetUid = null;
            s.start = addAlong(s.origin, s.direction, profile.startOffset * s.scale * s.ownerScale);
            s.end = addAlong(s.origin, s.direction, profile.endOffset * s.scale * s.ownerScale);
            // Source pulse countdown uses the same live dt as the owner phase timer.
            s.pulseTimer -= pose.dt;
            if (s.pulseTimer <= 0) {
                s.pulse = true;
                s.pulseTimer = 1;
            }
        }
    }
    // Missing corpus function80139c50 (original binary): a live endpoint read on
    // the second update. Retain initial radius and victim IDs across both passes.
    for (const pulse of s.pulses) {
        pulse.stage = 'sweep';
        pulse.end = { ...s.end };
    }
    if (s.pulse)
        s.pulses.push({ attackUid: `beam-pulse-${++pulseSerial}`, stage: 'init', start: { ...s.start }, end: { ...s.start },
            radius: profile.hitRadius * s.scale * s.ownerScale, hitUids: [] });
    pr.pos = { ...s.origin };
    pr.vel = { ...s.direction };
    pr.hitRadius = profile.hitRadius * s.scale * s.ownerScale;
    pr.romScale = [s.scale * s.ownerScale, s.scale * s.ownerScale, s.scale * s.ownerScale];
    return [pr];
}
/** Host 3D capsule distance. Exact source dynamic HIT segment shape is not claimed. */
export function beamPulseOverlaps(s: Pick<BeamPulse, 'start' | 'end'>, pos: Vec3, radius: number): boolean {
    const d = { x: s.end.x - s.start.x, y: s.end.y - s.start.y, z: s.end.z - s.start.z };
    const l = d.x * d.x + d.y * d.y + d.z * d.z;
    const projection = (pos.x - s.start.x) * d.x + (pos.y - s.start.y) * d.y + (pos.z - s.start.z) * d.z;
    const t = l > 0 ? Math.max(0, Math.min(1, projection / l)) : 0;
    return Math.hypot(pos.x - s.start.x - d.x * t, pos.y - s.start.y - d.y * t, pos.z - s.start.z - d.z * t) <= radius;
}
