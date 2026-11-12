/** Pure G BLACK type5 ground wave (800fc208/800fc32c, 800fc6a0/800fc7c0).
 * One call is one source object update, with no initializer fallthrough. The
 * caller schedules the emitter and each pulse separately, owns attack identities
 * and victim history, and supplies the captured root transform and target roots.
 * Terrain, segment collision, bounds and 83714 attraction are explicit seams.
 * This models source operations, not a PPC floating-point instruction oracle.
 */
import type { Vec3 } from '@gf/physics';

export const G_BLACK_GROUND_WAVE = Object.freeze({
  spawner: 0x800fc208, type: 5, rowAddress: 0x8031ec50,
  hitKind: 84, hitRecord: 122, damageRecord: 9, hitRadius: 150,
  parentLife: 600, childLife: 30, retargetFrames: 4,
  initialSpeed: 50, scalarIncrement: 1, maxScalarSpeed: 150,
  minimumSteeringMagnitude: 0.00009999999747378752,
  turnLimit: 0.01745329238474369, targetClearDistance: 100,
  terrainProbeHeight: 100, maxHeightChange: 100, maxDistance: 5000,
  childSpacing: 200, horizontalScale: 0.4000000059604645, verticalScale: 0.5,
});

export type GBlackGroundWavePhase = 'pending' | 'active' | 'retiring' | 'released' | 'freed';
export type GBlackGroundWaveOwnerInvalid = 'owner-dead' | 'owner-changed';
export type GBlackGroundWaveReason = GBlackGroundWaveOwnerInvalid | 'height-change' | 'wall' |
  'distance' | 'bounds' | 'attraction' | 'lifetime' | 'hit-allocation';
export interface GBlackGroundWaveChildSpawn {
  pos: Vec3;
  /** Inherited source +b4: range, spacing and visual scale. */
  modelScale: number;
  /** Inherited source +c0: HIT size, independent of visual scale. */
  collisionScale: number;
}
export interface GBlackGroundWaveParentInput extends GBlackGroundWaveChildSpawn {
  /** Unit horizontal direction resolved from the captured root yaw. */
  facing: Vec3;
  targetUid?: string | null;
}
export interface GBlackGroundWaveParentState extends GBlackGroundWaveChildSpawn {
  kind: 'parent';
  phase: GBlackGroundWavePhase;
  motion: Vec3;
  facing: Vec3;
  targetUid: string | null;
  life: number;
  retargetCounter: number;
  /** Source +44 changes, but never rescales the stored +38 motion vector. */
  speedScalar: number;
  origin: Vec3;
  lastEmit: Vec3;
  reason?: GBlackGroundWaveReason;
}
export interface GBlackGroundWaveParentContext {
  terrainHeight: (pos: Readonly<Vec3>, probeHeight: number) => number;
  /** Read the captured target's root, including its last root before invalidation.
   * Target loss is applied after movement by targetInvalid/83874, not a new lock. */
  targetPosition: (uid: string) => Readonly<Vec3> | null;
  targetInvalid?: (uid: string, state: Readonly<GBlackGroundWaveParentState>) => boolean;
  /** Replace bounded host math with source normalization/6c498 for parity. */
  normalizeTarget?: (delta: Readonly<Vec3>) => Vec3;
  rotateMotion?: (motion: Readonly<Vec3>, delta: Readonly<Vec3>, limit: number, facing: Readonly<Vec3>) => Vec3;
  /** Source 833a4 follows a successful steering update, before projection. */
  afterSteering?: (state: GBlackGroundWaveParentState) => void;
  /** Source +2c is scheduler-owned. Omission explicitly uses the host's prior
   * update position rather than claiming the original scheduler snapshot. */
  previousPosition?: Readonly<Vec3>;
  wallSegment?: (from: Readonly<Vec3>, to: Readonly<Vec3>) => boolean;
  outsideBounds?: (pos: Readonly<Vec3>) => boolean;
  /** Runs after origin distance/bounds are captured; may mutate the copied state. */
  attraction83714?: (state: GBlackGroundWaveParentState) => boolean;
  ownerInvalid?: GBlackGroundWaveOwnerInvalid;
}
export interface GBlackGroundWaveChildState extends GBlackGroundWaveChildSpawn {
  kind: 'child';
  phase: GBlackGroundWavePhase;
  age: number;
  /** Derived remaining updates. The original +1e duration stays constant30. */
  life: number;
  yawBam: number;
  visualScale: [number, number, number];
  hitActive: boolean;
  reason?: GBlackGroundWaveReason;
}
export interface GBlackGroundWaveChildContext {
  terrainHeight: (pos: Readonly<Vec3>, probeHeight: number) => number;
  rngByte: () => number;
  /** 8008ae3c happens before RNG or terrain. False enters state2 immediately. */
  registerHit?: () => boolean;
  ownerInvalid?: GBlackGroundWaveOwnerInvalid;
}
const f = Math.fround;
const s16 = (value: number): number => (value << 16) >> 16;
const length = (v: Readonly<Vec3>): number => Math.hypot(v.x, v.y, v.z);
const delta = (a: Readonly<Vec3>, b: Readonly<Vec3>): Vec3 =>
  ({ x: f(a.x - b.x), y: f(a.y - b.y), z: f(a.z - b.z) });
const scaled = (v: Readonly<Vec3>, scale: number): Vec3 =>
  ({ x: f(v.x * scale), y: f(v.y * scale), z: f(v.z * scale) });
function normalized(v: Readonly<Vec3>): Vec3 {
  const magnitude = length(v);
  return magnitude > 0 ? scaled(v, 1 / magnitude) : { x: 0, y: 0, z: 0 };
}

/** Bounded host horizontal rotation. Math trig is not the original 6c498/PSVEC
 * implementation; inject rotateMotion when reproducing that numerical path. */
export function rotateGBlackGroundWaveMotion(motion: Readonly<Vec3>, toward: Readonly<Vec3>, limit: number,
  facing: Readonly<Vec3>): Vec3 {
  let horizontal = { x: motion.x, y: 0, z: motion.z }, magnitude = length(horizontal);
  if (magnitude < G_BLACK_GROUND_WAVE.minimumSteeringMagnitude) {
    horizontal = scaled({ ...facing, y: 0 }, G_BLACK_GROUND_WAVE.minimumSteeringMagnitude);
    magnitude = G_BLACK_GROUND_WAVE.minimumSteeringMagnitude;
  }
  const destination = normalized({ ...toward, y: 0 });
  const dot = (horizontal.x * destination.x + horizontal.z * destination.z) / magnitude;
  const angle = Math.min(Math.acos(Math.max(-1, Math.min(1, dot))), limit);
  // Cross-product zero (including antiparallel) uses world +Y in 6c498.
  const sign = horizontal.z * destination.x - horizontal.x * destination.z < 0 ? -1 : 1;
  const yaw = Math.atan2(horizontal.x, horizontal.z) + sign * angle;
  return { x: f(Math.sin(yaw) * magnitude), y: motion.y, z: f(Math.cos(yaw) * magnitude) };
}

export function createGBlackGroundWaveParent(input: GBlackGroundWaveParentInput): GBlackGroundWaveParentState {
  return { kind: 'parent', phase: 'pending', pos: { ...input.pos }, facing: { ...input.facing },
    modelScale: input.modelScale, collisionScale: input.collisionScale, targetUid: input.targetUid ?? null,
    motion: { x: 0, y: 0, z: 0 }, life: 0, retargetCounter: 0, speedScalar: 0,
    origin: { ...input.pos }, lastEmit: { ...input.pos } };
}

/** No allocation is attempted here: the returned snapshots are child allocation
 * requests. Spacing is already consumed even if the caller cannot allocate one. */
export function stepGBlackGroundWaveParent(input: GBlackGroundWaveParentState, ctx: GBlackGroundWaveParentContext):
  { state: GBlackGroundWaveParentState; children: GBlackGroundWaveChildSpawn[] } {
  const state = { ...input, pos: { ...input.pos }, facing: { ...input.facing }, motion: { ...input.motion },
    origin: { ...input.origin }, lastEmit: { ...input.lastEmit } };
  const children: GBlackGroundWaveChildSpawn[] = [];
  const emit = (): void => { children.push({ pos: { ...state.pos }, modelScale: state.modelScale,
    collisionScale: state.collisionScale }); };
  if (ctx.ownerInvalid && (state.phase === 'pending' || state.phase === 'active')) {
    state.phase = 'retiring'; state.reason = ctx.ownerInvalid;
  }
  if (state.phase === 'freed') return { state, children };
  if (state.phase === 'released') { state.phase = 'freed'; return { state, children }; }
  if (state.phase === 'retiring') { state.phase = 'released'; return { state, children }; }
  if (state.phase === 'pending') {
    state.phase = 'active'; state.life = G_BLACK_GROUND_WAVE.parentLife;
    state.retargetCounter = G_BLACK_GROUND_WAVE.retargetFrames;
    state.speedScalar = G_BLACK_GROUND_WAVE.initialSpeed;
    state.pos.y = f(ctx.terrainHeight(state.pos, G_BLACK_GROUND_WAVE.terrainProbeHeight));
    const target = state.targetUid === null ? null : ctx.targetPosition(state.targetUid);
    const aim = target ? delta({ ...target, y: state.pos.y }, state.pos) : null;
    state.motion = scaled(aim ? (ctx.normalizeTarget ?? normalized)(aim) : state.facing,
      G_BLACK_GROUND_WAVE.initialSpeed);
    state.origin = { ...state.pos }; state.lastEmit = { ...state.pos }; emit();
    return { state, children };
  }

  const previous = { ...state.pos };
  let steered = false;
  if (state.targetUid !== null) {
    state.retargetCounter = s16(state.retargetCounter - 1);
    if (state.retargetCounter <= 0) {
      state.retargetCounter = G_BLACK_GROUND_WAVE.retargetFrames;
      const target = ctx.targetPosition(state.targetUid);
      if (target) {
        const toward = delta({ ...target, y: state.pos.y }, state.pos);
        if (length(toward) <= G_BLACK_GROUND_WAVE.targetClearDistance) state.targetUid = null;
        else {
          state.motion = (ctx.rotateMotion ?? rotateGBlackGroundWaveMotion)(state.motion, toward,
            G_BLACK_GROUND_WAVE.turnLimit, state.facing);
          state.pos = { x: f(state.pos.x + state.motion.x), y: state.pos.y,
            z: f(state.pos.z + state.motion.z) };
          steered = true;
          ctx.afterSteering?.(state);
        }
      }
    }
  }
  if (!steered) state.pos = { x: f(state.pos.x + state.motion.x), y: f(state.pos.y + state.motion.y),
    z: f(state.pos.z + state.motion.z) };
  state.pos.y = f(ctx.terrainHeight(state.pos, G_BLACK_GROUND_WAVE.terrainProbeHeight));
  const heightOkay = Math.abs(f(state.pos.y - previous.y)) < G_BLACK_GROUND_WAVE.maxHeightChange;
  const wall = ctx.wallSegment?.(ctx.previousPosition ?? previous, state.pos) ?? false;
  state.speedScalar = Math.max(G_BLACK_GROUND_WAVE.initialSpeed, Math.min(G_BLACK_GROUND_WAVE.maxScalarSpeed,
    f(state.speedScalar + G_BLACK_GROUND_WAVE.scalarIncrement)));
  if (state.targetUid !== null && (ctx.targetInvalid?.(state.targetUid, state) ?? false)) state.targetUid = null;
  const fromOrigin = length(delta(state.pos, state.origin));
  const bounds = ctx.outsideBounds?.(state.pos) ?? false;
  const attraction = ctx.attraction83714?.(state) ?? false;
  state.life = s16(state.life - 1);
  // All probes above run even when an earlier predicate already failed.
  const reason = !heightOkay ? 'height-change' : wall ? 'wall' :
    !(fromOrigin < f(G_BLACK_GROUND_WAVE.maxDistance * state.modelScale)) ? 'distance' :
      bounds ? 'bounds' : attraction ? 'attraction' : state.life === 0 ? 'lifetime' : undefined;
  if (reason) { state.phase = 'retiring'; state.reason = reason; }
  else if (length(delta(state.pos, state.lastEmit)) >= f(G_BLACK_GROUND_WAVE.childSpacing * state.modelScale)) {
    state.lastEmit = { ...state.pos }; emit();
  }
  return { state, children };
}

export function createGBlackGroundWaveChild(input: GBlackGroundWaveChildSpawn): GBlackGroundWaveChildState {
  return { kind: 'child', phase: 'pending', pos: { ...input.pos }, modelScale: input.modelScale,
    collisionScale: input.collisionScale, age: 0, life: 0, yawBam: 0,
    visualScale: [0, 0, 0], hitActive: false };
}

/** Source visual keyframes [0:1,1,1], [3:1,5,1], [30:1.25,0,1.25].
 * Age always advances by one, so a call crosses at most one keyframe. */
export function gblackGroundWaveVisualScale(age: number, modelScale: number): [number, number, number] {
  const t = Math.max(0, Math.min(G_BLACK_GROUND_WAVE.childLife, age));
  const xz = t <= 3 ? 1 : f(1 + f((t - 3) / 27) * .25);
  const y = t <= 3 ? f(1 + f(t / 3) * 4) : f(5 - f((t - 3) / 27) * 5);
  const horizontal = f(G_BLACK_GROUND_WAVE.horizontalScale * modelScale);
  const vertical = f(G_BLACK_GROUND_WAVE.verticalScale * modelScale);
  return [f(xz * horizontal), f(y * vertical), f(xz * horizontal)];
}

export function stepGBlackGroundWaveChild(input: GBlackGroundWaveChildState, ctx: GBlackGroundWaveChildContext):
  { state: GBlackGroundWaveChildState } {
  const state: GBlackGroundWaveChildState = { ...input, pos: { ...input.pos }, visualScale: [...input.visualScale] };
  if (ctx.ownerInvalid && (state.phase === 'pending' || state.phase === 'active')) {
    state.phase = 'retiring'; state.hitActive = false; state.reason = ctx.ownerInvalid;
  }
  if (state.phase === 'freed') return { state };
  if (state.phase === 'released') { state.phase = 'freed'; return { state }; }
  if (state.phase === 'retiring') { state.phase = 'released'; state.hitActive = false; return { state }; }
  if (state.phase === 'pending') {
    state.phase = 'active';
    if (!(ctx.registerHit?.() ?? true)) {
      state.phase = 'retiring'; state.reason = 'hit-allocation'; return { state };
    }
    state.hitActive = true; state.age = 0; state.life = G_BLACK_GROUND_WAVE.childLife;
    state.yawBam = (ctx.rngByte() & 0xff) << 8;
    state.pos.y = f(ctx.terrainHeight(state.pos, G_BLACK_GROUND_WAVE.terrainProbeHeight));
    state.visualScale = gblackGroundWaveVisualScale(state.age, state.modelScale);
    return { state };
  }
  state.age = s16(state.age + 1);
  state.life = G_BLACK_GROUND_WAVE.childLife - state.age;
  if (state.age >= G_BLACK_GROUND_WAVE.childLife) {
    state.phase = 'retiring'; state.reason = 'lifetime'; state.hitActive = false;
  }
  // The terminal age30 update still applies the zero-height final keyframe.
  state.visualScale = gblackGroundWaveVisualScale(state.age, state.modelScale);
  return { state };
}
