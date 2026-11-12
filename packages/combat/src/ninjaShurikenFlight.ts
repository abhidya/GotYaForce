/** Normal Ninja/Sasuke X shuriken, 8007db5c table802d6d68 rows0/3 ONLY.
 * Source: research/decomp/ghidra-export/chunk_0011.c:4210–4650;
 * shared seams: chunk_0012.c:2586–2893,3244–3272. One call is one source
 * child dispatch, not a dt-scaled update. Allocation and phase0 are distinct;
 * successful phase0 calls active7e200 in that SAME dispatch.
 *
 * Float stores are rounded. JS sqrt/trig and normalization are NOT a PPC/libm
 * oracle. In particular this uses the source's subtractive ballistic root,
 * not Powered's rationalized root or finite-gravity fallback. Animated joints,
 * target ownership, stage geometry, contact scheduling and incoming shared
 * modifiers are injected. Omitted shared hooks mean no incoming influence;
 * they do not stand in for implementations of those source systems.
 */
export interface NinjaShurikenVec3 { readonly x: number; readonly y: number; readonly z: number }
export type NinjaShurikenRow = 0 | 3;
export type NinjaShurikenPhase = 'pending' | 'active' | 'retiring' | 'released' | 'freed';
export type NinjaShurikenRetireReason = 'lifetime' | 'bounds' | 'contact' | 'terrain' |
  'attraction' | 'owner-dead' | 'owner-changed' | 'hit-registration';
const f = Math.fround;
export const NINJA_SHURIKEN_FLIGHT_CONSTANTS = Object.freeze({
  table: '0x802d6d68', stride: 0x38, model: 14, joint: 11, hitKind: 1,
  localOffset: Object.freeze({ x: 55, y: 0, z: 0 }), speed: 40, life: 600,
  gravityInterval: 4, gravityMin: 0, gravityMax: 7.5,
  gravityChange: f(.15), initialGravity: f(.3), halfGravity: .5,
  horizontalMinimum: f(.0001), maximumPitch: f(.8),
  angleUnit: f(.0000958738019107841), spinIncrement: 0x1800,
  drawMultiplier: 2, impactRow: 0, launchEffect: -1, proximityChild: -1,
});
const C = NINJA_SHURIKEN_FLIGHT_CONSTANTS;

export interface NinjaShurikenLaunchPose {
  readonly origin: NinjaShurikenVec3;
  /** Owner's source yaw, in radians. It is not the aimed flight heading. */
  readonly yaw: number;
  readonly ownerScale?: number;
  readonly collisionScale?: number;
  readonly collisionScaleRatio?: number;
  /** Saved actor +0x518 point, enabled only when the owner has +0xc8 at init. */
  readonly initialAimPoint?: NinjaShurikenVec3 | null;
  /** The independently inherited +0xc8/+0xcc target, never reacquired. */
  readonly targetUid?: string | null;
  readonly targetPoint?: NinjaShurikenVec3 | null;
}
export interface NinjaShurikenInitPose {
  readonly origin: NinjaShurikenVec3;
  readonly yaw: number;
  /** Current owner +0xc8 gate. The saved aim and inherited scale/target remain
   * allocation snapshots, even if the owner changed target in the meantime. */
  readonly initialAimEnabled?: boolean;
}
export interface NinjaShurikenFlightState {
  readonly row: NinjaShurikenRow;
  readonly phase: NinjaShurikenPhase;
  readonly pos: NinjaShurikenVec3;
  readonly previousPos: NinjaShurikenVec3;
  readonly velocity: NinjaShurikenVec3;
  readonly yaw: number;
  /** Relative visual Y rotation in signed source angle units, not flight yaw. */
  readonly spinAngleS16: number;
  readonly ownerScale: number;
  readonly modelScale: number;
  readonly collisionScale: number;
  readonly collisionScaleRatio: number;
  /** Uniform draw-only multiplier2 applied after the inherited model matrix. */
  readonly visualScale: number;
  readonly speed: number;
  readonly gravity: number;
  readonly gravityTimer: number;
  readonly life: number;
  readonly initialAimPoint: NinjaShurikenVec3 | null;
  readonly targetUid: string | null;
  readonly targetPoint: NinjaShurikenVec3 | null;
  readonly hitActive: boolean;
  readonly visible: boolean;
  readonly reason?: NinjaShurikenRetireReason;
}
export interface NinjaShurikenTarget {
  readonly uid: string;
  readonly point: NinjaShurikenVec3;
  /** Source +0xcc exists, is active, and !(owner+83==0 && owner+656!=0). */
  readonly valid: boolean;
}
export interface NinjaShurikenScalePatch {
  readonly modelScale: number;
  readonly collisionScale: number;
  readonly collisionScaleRatio: number;
}
export interface NinjaShurikenFlightContext {
  /** Resolve the animated joint11 + local[55,0,0] on successful phase0. */
  readonly initPose?: () => NinjaShurikenInitPose;
  readonly ownerInvalid?: 'owner-dead' | 'owner-changed';
  readonly hitRegistrationSucceeds?: boolean;
  /** +0x1d9 from the previous collision pass; ANY nonzero byte is contact. */
  readonly priorContact?: boolean;
  /** Undefined retains the supplied snapshot; null/mismatched/invalid loses it. */
  readonly currentTarget?: NinjaShurikenTarget | null;
  /** Source checks 83244 before contact/spin/motion, after life predecrement. */
  readonly outsideBounds?: (pos: NinjaShurikenVec3) => boolean;
  /** Every targeted-motion frame, after movement, even without gravity refresh. */
  readonly targetOwner833a4?: (state: NinjaShurikenFlightState) => void;
  readonly scale833ec?: (state: NinjaShurikenFlightState) => NinjaShurikenScalePatch | void;
  readonly speedGravity83610?: (state: NinjaShurikenFlightState) =>
    { readonly speed: number; readonly gravity: number } | void;
  /** May move the projectile even when consumed=false. Runs after normalization. */
  readonly attraction83714?: (state: NinjaShurikenFlightState) =>
    { readonly consumed: boolean; readonly pos?: NinjaShurikenVec3 };
  /** Return the snapped contact point, or null. Terrain retirement defers HIT-off. */
  readonly terrain84170?: (state: NinjaShurikenFlightState) => NinjaShurikenVec3 | null;
}
export type NinjaShurikenFlightEvent =
  | { readonly kind: 'initialized'; readonly row: NinjaShurikenRow }
  | { readonly kind: 'impact'; readonly row: 0; readonly reason: 'contact' | 'terrain'; readonly pos: NinjaShurikenVec3 }
  | { readonly kind: 'hit-disabled' | 'hidden' | 'freed'; readonly reason: NinjaShurikenRetireReason };
export interface NinjaShurikenStepResult {
  readonly state: NinjaShurikenFlightState;
  readonly events: readonly NinjaShurikenFlightEvent[];
}
type MutableState = { -readonly [K in keyof NinjaShurikenFlightState]: NinjaShurikenFlightState[K] };
const copy = (v: NinjaShurikenVec3): NinjaShurikenVec3 => ({ x: f(v.x), y: f(v.y), z: f(v.z) });
const nullableCopy = (v: NinjaShurikenVec3 | null): NinjaShurikenVec3 | null => v ? copy(v) : null;
const s16 = (n: number): number => (n << 16) >> 16;
const normalizedTimes = (v: NinjaShurikenVec3, speed: number): NinjaShurikenVec3 => {
  const magnitude = Math.hypot(v.x, v.y, v.z);
  return { x: f(f(v.x / magnitude) * speed), y: f(f(v.y / magnitude) * speed), z: f(f(v.z / magnitude) * speed) };
};

/** Allocation has no flight, HIT registration, spin, lifetime, or launch effect. */
export function createNinjaShurikenFlight(row: NinjaShurikenRow, pose: NinjaShurikenLaunchPose): NinjaShurikenFlightState {
  if (row !== 0 && row !== 3) throw new RangeError('Ninja shuriken supports only table rows0/3');
  const ownerScale = f(pose.ownerScale ?? 1);
  return { row, phase: 'pending', pos: copy(pose.origin), previousPos: copy(pose.origin),
    velocity: { x: 0, y: 0, z: 0 }, yaw: f(pose.yaw), spinAngleS16: 0,
    ownerScale, modelScale: ownerScale, collisionScale: f(pose.collisionScale ?? ownerScale),
    collisionScaleRatio: f(pose.collisionScaleRatio ?? 1), visualScale: ownerScale,
    speed: 0, gravity: 0, gravityTimer: 0, life: 0,
    initialAimPoint: nullableCopy(pose.initialAimPoint ?? null),
    targetUid: pose.targetUid ?? null, targetPoint: nullableCopy(pose.targetPoint ?? null),
    hitActive: false, visible: false };
}

/** 7dd84 low ballistic root, preserving source stores and subtractive numerator. */
function launchVelocity(state: NinjaShurikenFlightState, aimEnabled: boolean): NinjaShurikenVec3 {
  let heading = state.yaw, pitch = 0;
  if (aimEnabled && state.initialAimPoint) {
    const dx = f(state.initialAimPoint.x - state.pos.x), dy = f(state.initialAimPoint.y - state.pos.y);
    const dz = f(state.initialAimPoint.z - state.pos.z);
    const horizontal = Math.max(f(Math.sqrt(f(f(dx * dx) + f(dz * dz)))), C.horizontalMinimum);
    const square = f(horizontal * horizontal);
    const q = f(f(C.initialGravity * square) / f(2 * C.speed * C.speed));
    const discriminant = Math.max(0, f(square - f(f(4 * q) * f(q + dy))));
    const tangent = f(f(horizontal - f(Math.sqrt(discriminant))) / f(2 * q));
    pitch = Math.min(f(Math.atan(tangent)), C.maximumPitch);
    heading = f(Math.atan2(dx, dz));
  }
  return normalizedTimes({ x: f(Math.sin(heading) * Math.cos(pitch)),
    y: f(Math.sin(pitch)), z: f(Math.cos(heading) * Math.cos(pitch)) }, C.speed);
}

/** One source dispatch. Neither input nor its vectors are mutated. Hook results
 * are copied; callbacks see readonly state and must not mutate or retain it as
 * a mutable store. Events report state changes, not redundant aff0 calls.
 */
export function stepNinjaShurikenFlight(input: NinjaShurikenFlightState,
  ctx: NinjaShurikenFlightContext = {}): NinjaShurikenStepResult {
  const state: MutableState = { ...input, pos: copy(input.pos), previousPos: copy(input.pos),
    velocity: copy(input.velocity), initialAimPoint: nullableCopy(input.initialAimPoint), targetPoint: nullableCopy(input.targetPoint) };
  const events: NinjaShurikenFlightEvent[] = [];
  const disableHit = (): void => {
    if (state.hitActive) events.push({ kind: 'hit-disabled', reason: state.reason! });
    state.hitActive = false;
  };
  const hide = (): void => {
    if (state.visible) events.push({ kind: 'hidden', reason: state.reason! });
    state.visible = false;
  };
  const retire = (reason: NinjaShurikenRetireReason, immediateHitOff = true): NinjaShurikenStepResult => {
    state.phase = 'retiring'; state.reason = reason;
    if (immediateHitOff) disableHit();
    return { state, events };
  };
  const impact = (reason: 'contact' | 'terrain'): void => {
    events.push({ kind: 'impact', row: C.impactRow, reason, pos: copy(state.pos) });
  };

  // 7dcec guards phases0/1 only, then dispatches the NEW phase2 immediately.
  if (ctx.ownerInvalid && (state.phase === 'pending' || state.phase === 'active')) {
    state.phase = 'retiring'; state.reason = ctx.ownerInvalid; disableHit(); hide();
  }
  if (state.phase === 'freed') return { state, events };
  if (state.phase === 'released') {
    state.phase = 'freed'; events.push({ kind: 'freed', reason: state.reason! });
    return { state, events };
  }
  if (state.phase === 'retiring') {
    state.phase = 'released'; disableHit(); hide(); return { state, events };
  }
  if (state.phase === 'pending') {
    // Registration precedes muzzle resolution and all life/flight initialization.
    if (ctx.hitRegistrationSucceeds === false) return retire('hit-registration');
    const pose = ctx.initPose?.();
    if (pose) {
      state.pos = copy(pose.origin); state.previousPos = copy(pose.origin); state.yaw = f(pose.yaw);
    }
    state.velocity = launchVelocity(state, pose?.initialAimEnabled ?? state.initialAimPoint !== null);
    state.speed = C.speed; state.gravity = C.initialGravity;
    state.gravityTimer = C.gravityInterval; state.life = C.life;
    state.visualScale = f(C.drawMultiplier * state.modelScale);
    state.phase = 'active'; state.hitActive = state.visible = true;
    events.push({ kind: 'initialized', row: state.row });
    // Deliberate fallthrough into 7e200, including contact/bounds probes.
  }

  state.life = s16(state.life - 1);
  if (state.life <= 0) return retire('lifetime');
  if (ctx.outsideBounds?.(state.pos)) return retire('bounds');
  if (ctx.priorContact) { impact('contact'); return retire('contact'); }
  state.spinAngleS16 = s16(state.spinAngleS16 + C.spinIncrement);

  if (state.targetUid !== null && ctx.currentTarget !== undefined) {
    if (!ctx.currentTarget || !ctx.currentTarget.valid || ctx.currentTarget.uid !== state.targetUid) {
      state.targetUid = null; state.targetPoint = null;
    } else state.targetPoint = copy(ctx.currentTarget.point);
  }
  const targeted = state.targetUid !== null && state.targetPoint !== null;
  if (targeted) {
    state.gravityTimer = s16(state.gravityTimer - 1);
    if (state.gravityTimer < 1) {
      state.gravityTimer = C.gravityInterval;
      const point = state.targetPoint!;
      const dx = f(point.x - state.pos.x), dy = f(point.y - state.pos.y), dz = f(point.z - state.pos.z);
      const horizontal = f(Math.hypot(dx, dz));
      const speedXZ = f(Math.sqrt(f(f(state.velocity.x * state.velocity.x) + f(state.velocity.z * state.velocity.z))));
      const time = f(horizontal / speedXZ);
      let desired = f(f(2 * f(time * state.velocity.y - dy)) / f(time * time));
      if (desired < C.gravityMin) desired = C.gravityMin;
      if (C.gravityMax < desired) desired = C.gravityMax;
      let change = f(desired - state.gravity);
      if (C.gravityChange < Math.abs(change)) change = f(C.gravityChange * (Math.abs(change) / change));
      state.gravity = f(state.gravity + change);
    }
  }
  const verticalMotion = f(state.velocity.y - f(state.gravity * C.halfGravity));
  state.pos = { x: f(state.pos.x + state.velocity.x), y: f(state.pos.y + verticalMotion), z: f(state.pos.z + state.velocity.z) };
  state.velocity = { ...state.velocity, y: f(state.velocity.y - state.gravity) };
  if (targeted) ctx.targetOwner833a4?.(state);
  const scale = ctx.scale833ec?.(state);
  if (scale) {
    state.modelScale = f(scale.modelScale); state.collisionScale = f(scale.collisionScale);
    state.collisionScaleRatio = f(scale.collisionScaleRatio);
    state.visualScale = f(C.drawMultiplier * state.modelScale);
  }
  const speedGravity = ctx.speedGravity83610?.(state);
  if (speedGravity) { state.speed = f(speedGravity.speed); state.gravity = f(speedGravity.gravity); }
  const vy = state.velocity.y;
  state.velocity = { ...normalizedTimes(state.velocity, state.speed), y: vy };
  const attraction = ctx.attraction83714?.(state);
  if (attraction?.pos) state.pos = copy(attraction.pos);
  if (attraction?.consumed) return retire('attraction');
  const terrainPoint = ctx.terrain84170?.(state);
  if (terrainPoint) {
    state.pos = copy(terrainPoint); impact('terrain');
    return retire('terrain', false); // 7e200's terrain early return omits aff0.
  }
  return { state, events };
}
