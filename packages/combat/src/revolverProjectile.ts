/** Pure 80084790/80084cec Revolver flight, table 802d9758 rows 0/1/13/14.
 * Angles are radians. Static bind joints replace unavailable animated matrices.
 * JS trig, degenerate-basis fallback and zero-time gravity retention are bounded host
 * safeguards, not PPC bit parity. Caller owns allocation, collision and status effects.
 */
export interface RevolverVec3 {
    x: number;
    y: number;
    z: number;
}
export interface RevolverBasis {
    right: RevolverVec3;
    up: RevolverVec3;
    forward: RevolverVec3;
}
export interface RevolverTarget {
    uid: string;
    pos: RevolverVec3;
    scale: number; /** Host world-space shape radius, not inferred from scale. */
    radius: number;
}
export type RevolverRow = 0 | 1 | 13 | 14;
const GRAVITY = Math.fround(.3), SLEW = Math.fround(.15), EPS = Math.fround(.0001);
export const REVOLVER_SHOT_CONTRACT = Object.freeze({
    model: 0x400b, ownerLocalModel: 11, hitKind: 0, speed: 60, initialGravity: GRAVITY, life: 600,
        correctionInterval: 1, turnDegrees: 1, gravityMin: 0, gravityMax: 7.5, gravitySlew: SLEW,
        detachDistance: 25, directionMode: 5, directionInvert: 0, referenceMode: 2, referenceInvert: 0,
        effect: 5, cue: 6
});
export interface RevolverShotState {
    row: RevolverRow;
    pos: RevolverVec3;
    vel: RevolverVec3;
    life: number;
    gravity: number;
    targetUid: string | null;
    spin: number;
    ownerScale: number;
    scale: number;
    alive: boolean;
    yaw: number;
    gravityTimer: number;
    /** Unit pre-speed-normalization orientation captured for effect5; ownerScale supplies scale. */
    launchBasis: RevolverBasis;
    /** Static attachment basis captured at launch for target offset (0,20,0). */
    attachmentBasis: RevolverBasis;
    reference: RevolverVec3;
}
const copy = (v: RevolverVec3): RevolverVec3 => ({ ...v });
const mul = (v: RevolverVec3, s: number): RevolverVec3 => ({ x: v.x * s, y: v.y * s, z: v.z * s });
const cross = (a: RevolverVec3, b: RevolverVec3): RevolverVec3 => ({ x: a.y * b.z - a.z * b.y,
    y: a.z * b.x - a.x * b.z, z: a.x * b.y - a.y * b.x });
const norm = (v: RevolverVec3, fallback: RevolverVec3): RevolverVec3 => Math.hypot(v.x, v.y,
    v.z) > 1e-12 ? mul(v, 1 / Math.hypot(v.x, v.y, v.z)) : copy(fallback);
const clamp = (n: number, a: number, b: number): number => Math.min(b, Math.max(a, n));
const wrap = (a: number): number => Math.atan2(Math.sin(a), Math.cos(a));
const finite = (v: RevolverVec3): boolean => Number.isFinite(v.x) && Number.isFinite(v.y) && Number.isFinite(v.z);
function requireInputs(pos: RevolverVec3, yaw: number, scale: number): void {
    if (!finite(pos) || !Number.isFinite(yaw) || !Number.isFinite(scale) || scale <= 0)
        throw new RangeError('Revolver requires finite position/yaw and positive finite scale');
}
function validTarget(t: RevolverTarget | null): t is RevolverTarget {
    return t !== null && finite(t.pos) &&
    Number.isFinite(t.radius) && t.radius >= 0 && Number.isFinite(t.scale) && t.scale > 0;
}
function rowCheck(row: RevolverRow): void {
    if (![0, 1, 13, 14].includes(row))
        throw new RangeError('Unsupported Revolver row');
}
/** Static bind + joint-local (+/-118,6,23), then owner scale/yaw. */
export function revolverMuzzle(row: RevolverRow, ownerPos: RevolverVec3, yaw: number, scale = 1): RevolverVec3 {
    rowCheck(row);
    requireInputs(ownerPos, yaw, scale);
    const left = row === 0 || row === 13;
    const x = ((left ? -67.59277391433716 : 67.59280443191528) + (left ? -118 : 118)) * scale;
    const y = ((left ? 136.1260347366333 : 136.12609577178955) + 6) * scale;
    const z = ((left ? -.00000385384 : -.0000139372) + 23) * scale;
    return {
        x: ownerPos.x + x * Math.cos(yaw) + z * Math.sin(yaw), y: ownerPos.y + y,
            z: ownerPos.z - x * Math.sin(yaw) + z * Math.cos(yaw)
    };
}
function gravityAdjust(s: RevolverShotState, t: RevolverTarget): void {
    const goal = {
        x: t.pos.x + s.attachmentBasis.up.x * 20, y: t.pos.y + s.attachmentBasis.up.y * 20,
            z: t.pos.z + s.attachmentBasis.up.z * 20
    };
    const horizontal = Math.hypot(s.vel.x, s.vel.z), time = Math.hypot(goal.x - s.pos.x, goal.z - s.pos.z) / horizontal;
    // Source divides by t². Retain current gravity when that expression degenerates.
    if (horizontal <= 1e-12 || time <= 1e-12 || !Number.isFinite(time))
        return;
    const desired = 2 * (time * s.vel.y - (goal.y - s.pos.y)) / (time * time);
    if (Number.isFinite(desired))
        s.gravity += clamp(clamp(desired, 0, 7.5) - s.gravity, -SLEW, SLEW);
}
export function createRevolverShot(row: RevolverRow, pos: RevolverVec3, yaw: number,
    target: RevolverTarget | null, ownerScale = 1, trackingEnabled = true, ownerPitch = 0): RevolverShotState {
    rowCheck(row);
    requireInputs(pos, yaw, ownerScale);
    if (!Number.isFinite(ownerPitch))
        throw new RangeError('Finite owner pitch required');
    const t = validTarget(target) ? target : null;
    let pitch = 0;
    if (t) {
        const d = Math.max(Math.hypot(t.pos.x - pos.x, t.pos.z - pos.z), EPS), dy = t.pos.y - pos.y,
            q = GRAVITY * d * d / (2 * 60 * 60);
        const disc = d * d - 4 * q * (q + dy);
        const root = Math.sqrt(Math.max(0, disc));
        const tangent = disc >= 0 ? 2 * (q + dy) / (d + root) : (d - root) / (2 * q);
        pitch = Math.min(Math.atan(tangent), Math.fround(.8));
    }
    // Source helper returns signed BAM16 (-ownerPitchBAM - trunc(pitch*10430.3779)).
    const bam = -Math.trunc(ownerPitch * 32768 / Math.PI) - Math.trunc(10430.3779296875 * pitch);
    const signedBam = ((bam % 65536) + 65536 + 32768) % 65536 - 32768;
    const angle = signedBam * Math.fround(Math.PI / 32768);
    const a = ownerPitch + angle;
    const direction = { x: Math.sin(yaw) * Math.cos(a), y: -Math.sin(a), z: Math.cos(yaw) * Math.cos(a) };
    const attachmentBasis = {
        right: { x: ownerScale * Math.cos(yaw), y: 0, z: -ownerScale * Math.sin(yaw) }, up: { x: 0,
            y: ownerScale, z: 0 }, forward: { x: ownerScale * Math.sin(yaw), y: 0, z: ownerScale * Math.cos(yaw) }
    };
    const forward = norm(direction, { x: 0, y: 0, z: 1 });
    let right = cross(attachmentBasis.forward, forward);
    if (Math.hypot(right.x, right.y, right.z) < 1e-12)
        right = cross({ x: 0, y: 1, z: 0 }, forward);
    right = norm(right, { x: 1, y: 0, z: 0 });
    const launchBasis = {
        right, up: norm(cross(forward, right), { x: 0, y: 1, z: 0 }), forward: copy(forward)
    };
    const state: RevolverShotState = {
        row, pos: copy(pos), vel: mul(forward, 60), life: 600, gravity: GRAVITY, targetUid: t?.uid ?? null,
            spin: 0, ownerScale, scale: ownerScale, alive: true, yaw, gravityTimer: 1, launchBasis,
            attachmentBasis, reference: copy(attachmentBasis.forward)
    };
    if (!trackingEnabled) {
        if (t)
            gravityAdjust(state, t);
        state.targetUid = null;
    }
    return state;
}
export function stepRevolverShot(input: RevolverShotState, target: RevolverTarget | null): {
    state: RevolverShotState;
    alive: boolean;
} {
    const state = { ...input, pos: copy(input.pos), vel: copy(input.vel) };
    if (!state.alive)
        return { state, alive: false };
    if (--state.life <= 0) {
        state.alive = false;
        return { state, alive: false };
    }
    state.spin = wrap(state.spin + 0x1400 * Math.PI / 32768);
    let t = validTarget(target) && target.uid === state.targetUid ? target : null;
    if (t && Math.hypot(t.pos.x - state.pos.x, t.pos.y - state.pos.y, t.pos.z - state.pos.z) - t.radius <= 25)
        t = null;
    if (!t)
        state.targetUid = null;
    if (t && --state.gravityTimer <= 0) {
        state.gravityTimer = 1;
        const speed = Math.max(EPS, Math.hypot(state.vel.x, state.vel.z));
        const heading = Math.hypot(state.vel.x, state.vel.z) >= EPS ? Math.atan2(state.vel.x, state.vel.z) : state.yaw;
        const goalX = t.pos.x + state.attachmentBasis.up.x * 20, goalZ = t.pos.z + state.attachmentBasis.up.z * 20;
        const desired = Math.atan2(goalX - state.pos.x, goalZ - state.pos.z);
        // 006c498 uses +Y when velocity/goal cross product is exactly zero.
        const delta = wrap(desired - heading);
        const antipodal = Math.abs(Math.abs(delta) - Math.PI) < 1e-14;
        const angle = heading + clamp(antipodal ? Math.PI : delta, -Math.fround(Math.PI / 180),
            Math.fround(Math.PI / 180));
        state.vel.x = Math.sin(angle) * speed;
        state.vel.z = Math.cos(angle) * speed;
        state.pos.x += state.vel.x;
        state.pos.z += state.vel.z;
        gravityAdjust(state, t);
    }
    else {
        state.pos.x += state.vel.x;
        state.pos.z += state.vel.z;
    }
    state.pos.y += state.vel.y - state.gravity / 2;
    const vy = state.vel.y - state.gravity;
    state.vel = mul(norm({ ...state.vel, y: vy }, { x: Math.sin(state.yaw), y: 0, z: Math.cos(state.yaw) }), 60);
    state.vel.y = vy;
    if (!finite(state.pos) || !finite(state.vel) || !Number.isFinite(state.gravity))
        state.alive = false;
    return { state, alive: state.alive };
}
