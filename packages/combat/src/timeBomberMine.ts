/** Pure family29/type2 drifting-mine lifecycle, connected through the bounded Battle adapter.
 * Source: 800e06c4 dispatcher, 800e075c initializer, 800e0a30 flight,
 * 800e0db8 retirement. Caller supplies the animated joint8 launch position and
 * normalized joint1 column2 direction at initialization, not allocation. Neither
 * target aiming nor X homing applies. Arithmetic models source semantic operations;
 * it is not a PPC instruction/FMA rounding oracle.
 * Collision/terrain and the original sine routine are explicit injected seams.
 */
import type { Vec3 } from '@gf/physics';

export type TimeBomberMineReason = 'contact' | 'bounds' | 'durability' | 'lifetime' |
  'collision' | 'wall' | 'owner-dead' | 'owner-changed';
export interface TimeBomberMineState {
  phase: 'pending' | 'active' | 'retiring' | 'released' | 'freed';
  motion: 'drift' | 'bob';
  pos: Vec3;
  direction: Vec3;
  speed: number;
  life: number;
  durability: number;
  center: Vec3;
  bobPhase: number;
  floorTarget: number;
  /** A consumed source cell0 unit, returned exactly once at retirement. */
  resourceOwed: boolean;
  reason?: TimeBomberMineReason;
}
export type TimeBomberMineEvent =
  | { kind: 'explosion'; row: 19; pos: Vec3; reason: TimeBomberMineReason }
  | { kind: 'refund'; cell: 0; count: 1; reason: TimeBomberMineReason }
  | { kind: 'free'; reason: TimeBomberMineReason };
export interface TimeBomberMineContext {
  /** zz_00055fc_, called once at initialization and once when drifting stops. */
  rngByte: () => number;
  /** Resolve animated attachments on phase0, which may follow allocation later. */
  initPose?: () => { pos: Vec3; direction: Vec3 };
  /** Signed BAM16 angle. Inject the source routine for parity, not Math.sin. */
  sinBam: (phase: number) => number;
  terrainHeight: (pos: Readonly<Vec3>) => number;
  ownerInvalid?: 'owner-dead' | 'owner-changed';
  contact?: boolean;
  outsideBounds?: (pos: Readonly<Vec3>) => boolean;
  /** Source 833ec/83524 update seam, before 83714 and 84170 tests. */
  afterMotion?: (state: TimeBomberMineState) => void;
  collision83714?: (pos: Readonly<Vec3>) => boolean;
  wall84170?: (pos: Readonly<Vec3>) => boolean;
}
const f = Math.fround;
const s16 = (value: number): number => (value << 16) >> 16;

/** pos/direction are pre-resolved phase0 inputs for pure callers. A delayed live
 * adapter must supply ctx.initPose to refresh them at initialization time. */
export function createTimeBomberMine(pos: Vec3, direction: Vec3, resourceOwed = true): TimeBomberMineState {
  return { phase: 'pending', motion: 'drift', pos: { ...pos }, direction: { ...direction },
    speed: 5, life: 0, durability: 1, center: { ...pos }, bobPhase: 0, floorTarget: 0, resourceOwed };
}

/** One child update, not a duration-scaled simulation tick. Input is never mutated.
 * Normal retirement enters state2 without dispatching it until the next update.
 * Owner invalidation occurs before dispatch, so state2 refunds on that same update.
 */
export function stepTimeBomberMine(input: TimeBomberMineState, ctx: TimeBomberMineContext):
  { state: TimeBomberMineState; events: TimeBomberMineEvent[] } {
  const state = { ...input, pos: { ...input.pos }, direction: { ...input.direction }, center: { ...input.center } };
  const events: TimeBomberMineEvent[] = [];
  const retire = (reason: TimeBomberMineReason, explode: boolean): void => {
    state.phase = 'retiring'; state.reason = reason;
    if (explode) events.push({ kind: 'explosion', row: 19, pos: { ...state.pos }, reason });
  };
  if (ctx.ownerInvalid && (state.phase === 'pending' || state.phase === 'active')) retire(ctx.ownerInvalid, false);
  if (state.phase === 'freed') return { state, events };
  if (state.phase === 'released') {
    state.phase = 'freed';
    events.push({ kind: 'free', reason: state.reason! });
    return { state, events };
  }
  if (state.phase === 'retiring') {
    state.phase = 'released';
    if (state.resourceOwed) {
      state.resourceOwed = false;
      events.push({ kind: 'refund', cell: 0, count: 1, reason: state.reason! });
    }
    return { state, events };
  }
  if (state.phase === 'pending') {
    const pose = ctx.initPose?.();
    if (pose) { state.pos = { ...pose.pos }; state.direction = { ...pose.direction }; }
    state.life = 180 + (ctx.rngByte() & 63);
    state.phase = 'active';
    return { state, events };
  }
  if (ctx.contact) retire('contact', true);
  else if (ctx.outsideBounds?.(state.pos)) retire('bounds', false);
  else if (state.durability < 1) retire('durability', true);
  else {
    state.life = s16(state.life - 1);
    if (state.life < 1) retire('lifetime', true);
    else {
      if (state.motion === 'bob') {
        state.bobPhase = s16(state.bobPhase + 0x180);
        state.pos = { x: state.center.x, y: f(40 * ctx.sinBam(state.bobPhase) + state.center.y), z: state.center.z };
        if (state.floorTarget < state.center.y) state.center.y = f(state.center.y - .125);
      } else {
        state.speed = f(state.speed + f(-.1));
        if (state.speed > 0) {
          state.pos = { x: f(state.pos.x + f(state.direction.x * state.speed)),
            y: f(state.pos.y + f(state.direction.y * state.speed)),
            z: f(state.pos.z + f(state.direction.z * state.speed)) };
        } else {
          state.speed = 0; state.motion = 'bob'; state.center = { ...state.pos };
          state.bobPhase = s16((ctx.rngByte() & 15) << 12);
          state.center.y = -f(40 * ctx.sinBam(state.bobPhase) - state.center.y);
          state.floorTarget = f(f(ctx.terrainHeight(state.pos)) + 150);
        }
      }
      ctx.afterMotion?.(state);
      if (ctx.collision83714?.(state.pos)) retire('collision', false);
      else if (ctx.wall84170?.(state.pos)) retire('wall', true);
    }
  }
  return { state, events };
}
