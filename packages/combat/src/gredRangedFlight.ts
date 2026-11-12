/** G RED-family normal-shot child 800c3be0, rows 43/101/102 of 80303138.
 * Source bodies: research/decomp/ghidra-export/chunk_0020.c:2158–2630;
 * owner guard 80084000 and shared hooks: chunk_0012.c; homing 8006c1c8/
 * 8006c440: chunk_0009.c. This unit does not choose actor frames or attachments.
 * The caller supplies the source launch pose and already-transformed target aim.
 * HIT0 is record15's sphere, radius20 * collisionScale. Visual Z is NOT hit extent.
 * Float stores are rounded, but JS sqrt/trig are not a PPC instruction oracle.
 */
export interface GredRangedVec3 { x: number; y: number; z: number }
export type GredRangedRow = 43 | 101 | 102;
export type GredRangedFlightPhase = 'pending' | 'active' | 'retiring' |
  'contact-tail' | 'expire-tail' | 'released' | 'freed';
export type GredRangedRetireReason = 'contact' | 'attraction' | 'terrain' |
  'bounds' | 'lifetime' | 'hit-registration' | 'owner-dead' | 'owner-changed';
const f = Math.fround;
export const GRED_RANGED_FLIGHT_CONSTANTS = Object.freeze({
  speed: 80, acceleration: .5, maxSpeed: 160, life: 300, width: 40,
  widthNormalizer: 36.959999084472656, lengthNormalizer: 22,
  hitRadius: 20, contactMask: 0xa2, targetClearRadius: 20,
  trackingInitialCountdown: 1, trackingRepeatCountdown: 1,
  turnDegrees: f(.35), radiansPerDegree: .01745329238474369,
  shrinkMultiplier: f(.9), shrinkThreshold: f(.05), sound: 185,
});
const C = GRED_RANGED_FLIGHT_CONSTANTS;

export interface GredRangedFlightState {
  row: GredRangedRow;
  phase: GredRangedFlightPhase;
  origin: GredRangedVec3;
  pos: GredRangedVec3;
  previousPos: GredRangedVec3;
  /** Pending: supplied launch direction. Active/tails: source velocity +0x38. */
  velocity: GredRangedVec3;
  ownerModelScale: number;
  speed: number;
  life: number;
  /** +0xb4, independently retired from HIT scale +0xc0. */
  widthScale: number;
  /** +0x188, the initial width, including inherited model scale. */
  baseWidth: number;
  /** +0x184, capped drawing length, shortened in the stationary contact tail. */
  length: number;
  /** +0x180, Euclidean distance from the saved launch origin, not path length. */
  distance: number;
  collisionScale: number;
  collisionScaleRatio: number;
  visualScale: GredRangedVec3;
  hitActive: boolean;
  visible: boolean;
  /** Null means source +0xc8 is cleared. No automatic target reacquisition. */
  targetPoint: GredRangedVec3 | null;
  trackingCountdown: number;
  reason?: GredRangedRetireReason;
}
export interface GredRangedLaunchPose {
  origin: GredRangedVec3;
  direction: GredRangedVec3;
  ownerModelScale?: number;
  /** Supply only a target retained by source +0xd0 bit4 after initial aiming. */
  targetPoint?: GredRangedVec3 | null;
}
export type GredRangedFlightEvent =
  | { kind: 'initialized'; row: GredRangedRow; sound: 185 }
  | { kind: 'hit-disabled'; reason: GredRangedRetireReason }
  | { kind: 'hidden'; reason: GredRangedRetireReason }
  | { kind: 'freed'; reason: GredRangedRetireReason };
export interface GredRangedFlightContext {
  /** Resolve the animated pose at initialization, not necessarily allocation. */
  initPose?: () => GredRangedLaunchPose;
  ownerInvalid?: 'owner-dead' | 'owner-changed';
  hitRegistrationSucceeds?: boolean;
  /** Contact flags saved by the previous collision pass, not a speculative hit. */
  priorContactBits?: number;
  /** Refresh the currently retained target's transformed aim before c4540. */
  targetPoint?: GredRangedVec3;
  /** 833a4 target-owner notification, only after an actual homing update. */
  afterHoming?: (state: GredRangedFlightState) => void;
  /** 83874 geometry/owner validation occurs AFTER motion and speed increment. */
  validateTarget?: (state: Readonly<GredRangedFlightState>) => boolean;
  /** 83714 external attraction. A true result retires into the contact tail. */
  attraction83714?: (state: GredRangedFlightState) => boolean;
  /** 84170 stage clipping/intersection; the hook may snap state.pos to contact. */
  terrain84170?: (state: GredRangedFlightState) => boolean;
  outsideBounds?: (pos: Readonly<GredRangedVec3>) => boolean;
  /** Exact shared-modifier seams. Defaults have no incoming modifier effects. */
  scale834b0?: (state: GredRangedFlightState) => void;
  speed83524?: (state: GredRangedFlightState) => void;
}

const copy = (v: GredRangedVec3): GredRangedVec3 => ({ ...v });
const add = (a: GredRangedVec3, b: GredRangedVec3): GredRangedVec3 =>
  ({ x: f(a.x + b.x), y: f(a.y + b.y), z: f(a.z + b.z) });
const sub = (a: GredRangedVec3, b: GredRangedVec3): GredRangedVec3 =>
  ({ x: f(a.x - b.x), y: f(a.y - b.y), z: f(a.z - b.z) });
const mul = (v: GredRangedVec3, n: number): GredRangedVec3 =>
  ({ x: f(v.x * n), y: f(v.y * n), z: f(v.z * n) });
const dot = (a: GredRangedVec3, b: GredRangedVec3): number => a.x * b.x + a.y * b.y + a.z * b.z;
const cross = (a: GredRangedVec3, b: GredRangedVec3): GredRangedVec3 =>
  ({ x: f(a.y * b.z - a.z * b.y), y: f(a.z * b.x - a.x * b.z), z: f(a.x * b.y - a.y * b.x) });
const magnitude = (v: GredRangedVec3): number => Math.hypot(v.x, v.y, v.z);
const normalize = (v: GredRangedVec3): GredRangedVec3 => {
  const length = magnitude(v);
  // The adapter must provide a resolved source direction. Do not invent a yaw.
  if (!(length > 0) || !Number.isFinite(length)) throw new Error('G RED flight requires a finite nonzero direction');
  return mul(v, 1 / length);
};
const sourceDistance = (state: GredRangedFlightState): number => f(magnitude(sub(state.pos, state.origin)));
const maxLength = (row: GredRangedRow): number => row === 101 ? 500 : 1000;
const updateLength = (state: GredRangedFlightState): void => {
  state.length = Math.min(state.distance, maxLength(state.row));
  state.visualScale.z = f(state.length / C.lengthNormalizer);
};

/** Allocates a pending child, with no movement, registration, cue or active tick.
 * targetPoint is an already-retained +0xc8 target, never merely an initial aim.
 */
export function createGredRangedFlight(row: GredRangedRow, origin: GredRangedVec3,
  direction: GredRangedVec3, ownerModelScale = 1, targetPoint: GredRangedVec3 | null = null): GredRangedFlightState {
  return { row, phase: 'pending', origin: copy(origin), pos: copy(origin), previousPos: copy(origin),
    velocity: copy(direction), ownerModelScale, speed: 0, life: 0,
    widthScale: ownerModelScale, baseWidth: 0, length: 0, distance: 0,
    collisionScale: ownerModelScale, collisionScaleRatio: 1,
    visualScale: { x: ownerModelScale, y: ownerModelScale, z: ownerModelScale },
    hitActive: false, visible: false, targetPoint: targetPoint ? copy(targetPoint) : null,
    trackingCountdown: C.trackingInitialCountdown };
}

/** Source 6c1c8/6c440: capped axis-angle turn in DEGREES, then exactly one move. */
function homeAndMove(state: GredRangedFlightState, delta: GredRangedVec3): void {
  let direction = normalize(state.velocity);
  const distance = magnitude(delta);
  if (distance > 0) {
    const cosine = Math.max(-1, Math.min(1, f(dot(direction, delta) / distance)));
    const angle = Math.min(f(Math.acos(cosine)), f(C.radiansPerDegree * C.turnDegrees));
    const rawAxis = cross(direction, delta);
    const axis = dot(rawAxis, rawAxis) <= 0 ? { x: 0, y: 1, z: 0 } : normalize(rawAxis);
    const sine = Math.sin(angle), cos = Math.cos(angle), axisDot = dot(axis, direction);
    const tangent = cross(axis, direction);
    direction = {
      x: f(direction.x * cos + tangent.x * sine + axis.x * axisDot * (1 - cos)),
      y: f(direction.y * cos + tangent.y * sine + axis.y * axisDot * (1 - cos)),
      z: f(direction.z * cos + tangent.z * sine + axis.z * axisDot * (1 - cos)),
    };
  }
  state.velocity = mul(normalize(direction), state.speed);
  state.pos = add(state.pos, state.velocity);
}

/** One source child dispatch. The input and its vectors are never mutated.
 * Hooks operate on the new state only; attachment/collision implementations and
 * incoming external modifiers remain caller-owned, explicit integration seams.
 */
export function stepGredRangedFlight(input: GredRangedFlightState, ctx: GredRangedFlightContext = {}):
  { state: GredRangedFlightState; events: GredRangedFlightEvent[] } {
  const state: GredRangedFlightState = { ...input, origin: copy(input.origin), pos: copy(input.pos),
    previousPos: copy(input.pos), velocity: copy(input.velocity), visualScale: copy(input.visualScale),
    targetPoint: input.targetPoint ? copy(input.targetPoint) : null };
  const events: GredRangedFlightEvent[] = [];
  const disableHit = (reason: GredRangedRetireReason): void => {
    state.hitActive = false;
    events.push({ kind: 'hit-disabled', reason });
  };
  const hide = (): void => {
    if (state.visible) events.push({ kind: 'hidden', reason: state.reason! });
    state.visible = false;
  };
  const release = (): void => { state.phase = 'released'; hide(); };
  const retire = (phase: 'contact-tail' | 'expire-tail', reason: GredRangedRetireReason): void => {
    state.phase = phase; state.reason = reason; disableHit(reason);
  };

  // 84000 executes before dispatch only for source phases 0/1. It does not
  // inspect the owner's current action or control flag 0x01000000.
  if (ctx.ownerInvalid && (state.phase === 'pending' || state.phase === 'active')) {
    state.phase = 'retiring'; state.reason = ctx.ownerInvalid;
    disableHit(ctx.ownerInvalid); hide();
  }
  if (state.phase === 'freed') return { state, events };
  if (state.phase === 'released') {
    state.phase = 'freed'; events.push({ kind: 'freed', reason: state.reason! });
    return { state, events };
  }
  if (state.phase === 'retiring') { release(); return { state, events }; }
  if (state.phase === 'contact-tail') {
    state.length = f(state.length - state.speed);
    state.visualScale.z = f(state.length / C.lengthNormalizer);
    if (state.visualScale.z <= 0) release();
    return { state, events };
  }
  if (state.phase === 'expire-tail') {
    // c4308 does not rebuild velocity from the increasing scalar speed.
    state.pos = add(state.pos, state.velocity);
    state.distance = sourceDistance(state);
    state.speed = Math.min(f(state.speed + C.acceleration), C.maxSpeed);
    state.widthScale = f(state.widthScale * C.shrinkMultiplier);
    if (state.widthScale <= C.shrinkThreshold) release();
    state.visualScale.x = state.visualScale.y = state.widthScale;
    updateLength(state);
    // Inactive HIT +0xc0/+0xc4 deliberately retain their last active values.
    return { state, events };
  }
  if (state.phase === 'pending') {
    state.life = C.life;
    if (ctx.hitRegistrationSucceeds === false) {
      state.phase = 'retiring'; state.reason = 'hit-registration';
      return { state, events };
    }
    const pose = ctx.initPose?.();
    if (pose) {
      state.origin = copy(pose.origin); state.pos = copy(pose.origin);
      state.previousPos = copy(pose.origin); state.velocity = copy(pose.direction);
      if (pose.ownerModelScale !== undefined) state.ownerModelScale = pose.ownerModelScale;
      if (pose.targetPoint !== undefined) state.targetPoint = pose.targetPoint ? copy(pose.targetPoint) : null;
    }
    const direction = normalize(state.velocity);
    state.pos = add(state.origin, direction);
    state.distance = sourceDistance(state);
    state.speed = C.speed;
    state.velocity = mul(direction, state.speed);
    state.baseWidth = f(f(C.width / C.widthNormalizer) * state.ownerModelScale);
    state.widthScale = state.collisionScale = state.baseWidth;
    state.collisionScaleRatio = f(state.widthScale / state.baseWidth);
    state.visualScale.x = state.visualScale.y = state.widthScale;
    updateLength(state);
    state.hitActive = state.visible = true; state.phase = 'active';
    state.trackingCountdown = C.trackingInitialCountdown;
    events.push({ kind: 'initialized', row: state.row, sound: 185 });
    return { state, events };
  }

  // c4540 normalizes and rescales before target checks or movement.
  state.velocity = mul(normalize(state.velocity), state.speed);
  let turned = false;
  if (state.targetPoint) {
    if (ctx.targetPoint) state.targetPoint = copy(ctx.targetPoint);
    const delta = sub(state.targetPoint, state.pos);
    if (dot(delta, delta) <= C.targetClearRadius * C.targetClearRadius || dot(state.velocity, delta) < 0) {
      state.targetPoint = null;
    } else {
      state.trackingCountdown = ((state.trackingCountdown - 1) << 24) >> 24;
      if (state.trackingCountdown === 0) {
        state.trackingCountdown = C.trackingRepeatCountdown;
        homeAndMove(state, delta); turned = true;
        ctx.afterHoming?.(state);
      }
    }
  }
  if (!turned) state.pos = add(state.pos, state.velocity);
  state.distance = sourceDistance(state);
  state.speed = Math.min(f(state.speed + C.acceleration), C.maxSpeed);
  if (state.targetPoint && ctx.validateTarget?.(state) === false) state.targetPoint = null;
  const attracted = ctx.attraction83714?.(state) ?? false;
  if (attracted || ((ctx.priorContactBits ?? 0) & C.contactMask) !== 0) {
    retire('contact-tail', attracted ? 'attraction' : 'contact');
  } else if (ctx.terrain84170?.(state)) {
    retire('contact-tail', 'terrain');
    state.distance = sourceDistance(state);
  } else if (ctx.outsideBounds?.(state.pos)) {
    retire('expire-tail', 'bounds');
  } else {
    state.life = ((state.life - 1) << 16) >> 16;
    if (state.life < 1) retire('expire-tail', 'lifetime');
  }
  // c4088 applies these even on the frame that starts retirement.
  ctx.scale834b0?.(state);
  ctx.speed83524?.(state);
  state.collisionScale = state.widthScale;
  state.collisionScaleRatio = f(state.widthScale / state.baseWidth);
  state.visualScale.x = state.visualScale.y = state.widthScale;
  updateLength(state);
  return { state, events };
}
