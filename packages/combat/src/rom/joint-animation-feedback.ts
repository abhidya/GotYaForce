/** Pre-resolved existing-joint continuation and actor-part feedback, offline.
 * Source: 4adc8's setup-bit-clear branch (chunk_0006.c:615–679), followed by
 * non-mirrored 4b76c pose/frame extraction (:1076–1139). This is NOT 49e58,
 * mode0/mode2, descriptor setup, mapping/root-motion, stream waits or live wiring.
 *
 * Continue: when flags bit2 is set and JObj AObj is non-null, set its rate from
 * actor1dc8, call exactly one JObjAnim, reload current AObj, then copy WRAPPED
 * into part+2d. Never use animateTree or reset/invoke global completion state.
 * Setup bit1 is explicitly unsupported. With neither bit set, no input is read
 * beyond operationFlags. Null AObj skips timestep, part and effect validation.
 *
 * Extract: copy unmirrored translation, snapshot Euler rotation, run the required
 * synchronous source Euler-to-quaternion converter, then reload current AObj.
 * If non-null, copy its frame to part+0c; only mode0 with signed duration<=frame
 * writes complete+2e=1. This latch is never cleared here. Multiple joints leave
 * the last non-null AObj frame/segment, but an earlier completion remains latched.
 * Quaternion conversion is NOT approximated by host trig or a default identity.
 * The adapter must perform the actual conversion into its supplied output or
 * explicitly refuse. It must not mutate other runtime records or defer work.
 *
 * Factory-owned AObjs, parts and separate poses have symbolic identities. Joints
 * must be from the supplied source runtime. Inputs/tables must be non-proxy own
 * data; functions are snapshotted, records copied/sealed, and aliases excluded.
 * Mirror!=0 is refused before extraction, rather than guessing its constant.
 * Per-access writable/type/finite checks and reentry refusal are host bounds;
 * fields not consumed are not checked. Failures preserve all earlier writes and
 * effects. Rejecting deferred work cannot roll it back. Composed AObj/FObj FP
 * restrictions remain; no original-game or NI=1 arithmetic parity is claimed.
 */
import {AOBJ_STOPPED, createSourceAObj, freeSourceAObj, isLiveSourceAObj, setSourceAObjRate, type SourceAObj} from './aobj-clock.js';
import type {SourceJObjAnimationRuntime, SourceJObjAnimationEffects} from './jobj-animation.js';

export interface SourceJointAnimationPart {
  frame0c: number;
  duration24: number;
  segment2d: number;
  complete2e: number;
  mode2f: number;
  mirror30: number;
}
export interface SourceJointVector {x: number; y: number; z: number}
export interface SourceJointQuaternion extends SourceJointVector {w: number}
export interface SourceJointPose {
  readonly translation: SourceJointVector;
  readonly quaternion: SourceJointQuaternion;
}
export interface SourceJointPoseEffects {
  convertEulerToQuaternion(rotation: Readonly<SourceJointVector>, output: SourceJointQuaternion): void;
}
export interface SourceJointAnimationFeedbackRuntime {
  createAObj(initial: SourceAObj): symbol;
  allocateAObj(): symbol;
  freeAObj(identity: symbol | null): void;
  getAObj(identity: symbol): SourceAObj;
  createPart(initial: SourceJointAnimationPart): symbol;
  getPart(identity: symbol): SourceJointAnimationPart;
  createPose(initial: SourceJointPose): symbol;
  getPose(identity: symbol): SourceJointPose;
  advanceExistingJoint(part: symbol, joint: symbol | null, timestep: number, operationFlags: number,
    effects: SourceJObjAnimationEffects): void;
  capturePoseAndFrame(part: symbol, joint: symbol, pose: symbol, effects: SourceJointPoseEffects): void;
}
const partKeys = ['frame0c', 'duration24', 'segment2d', 'complete2e', 'mode2f', 'mirror30'] as const;
const genuineRuntimes = new WeakSet<object>();
export function isSourceJointAnimationFeedbackRuntime(value: unknown): value is SourceJointAnimationFeedbackRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[joint-feedback] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: object, key: string, writable = true): unknown {
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function f32(value: unknown, where: string): asserts value is number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value as number))) fail(`${where}: expected finite source float32`);
}
function integer(value: unknown, min: number, max: number, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: source integer out of range`);
}
function link(value: unknown): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail('AObj binding: opaque symbol or null required');
}
function method(table: object, key: string): (...args: never[]) => unknown {
  if (table === null || typeof table !== 'object') fail('effect/runtime data table required');
  const fn = own(table, key, false);
  if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
export function createSourceJointAnimationFeedbackRuntime(joints: SourceJObjAnimationRuntime): SourceJointAnimationFeedbackRuntime {
  const jointGet = method(joints, 'getJoint'), bindingGet = method(joints, 'getBinding'), animate = method(joints, 'animateJoint');
  const aobjs = new Map<symbol, SourceAObj>(), parts = new Map<symbol, SourceJointAnimationPart>(), poses = new Map<symbol, SourceJointPose>();
  let busy = false, reentered = false;
  const getAObj = (id: symbol): SourceAObj => {const value = aobjs.get(id); if (!value || !isLiveSourceAObj(value)) fail('unknown/non-owned AObj'); return value;};
  const getPart = (id: symbol): SourceJointAnimationPart => {const value = parts.get(id); if (!value) fail('unknown/non-owned part'); return value;};
  const getPose = (id: symbol): SourceJointPose => {const value = poses.get(id); if (!value) fail('unknown/non-owned pose'); return value;};
  const boundAObj = (joint: symbol | null): SourceAObj | null => {
    const binding = Reflect.apply(bindingGet, joints, [joint]) as ReturnType<SourceJObjAnimationRuntime['getBinding']>;
    const id = own(binding, 'aobj7c'); link(id); return id === null ? null : getAObj(id);
  };
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const effect = (name: string, run: () => unknown): void => {
    let result: unknown;
    try {result = run();} catch (e) {fail(`${name}: effect threw (${String(e)})`);}
    if (result !== undefined) fail(`${name}: effect must complete synchronously and return undefined`);
    if (reentered) fail('same-runtime reentry was caught inside an effect');
  };
  const readFloat = (record: object, key: string): number => {const value = own(record, key); f32(value, key); return value;};
  const write = (record: object, key: string, value: number): void => {
    own(record, key); (record as Record<string, unknown>)[key] = value;
  };
  const createVector = <T extends SourceJointVector>(initial: T, keys: readonly string[]): T => {
    if (initial === null || typeof initial !== 'object') fail('initial pose data record required');
    const copied: Record<string, number> = {};
    for (const key of keys) {const value = own(initial, key, false); f32(value, key); copied[key] = value;}
    return Object.seal(copied) as unknown as T;
  };
  const runtime: SourceJointAnimationFeedbackRuntime = Object.freeze({
    createAObj(initial: SourceAObj): symbol {
      enter();
      try {
        if (initial === null || typeof initial !== 'object') fail('initial AObj data record required');
        const copied = {} as SourceAObj;
        for (const key of ['flags', 'frame', 'rewind', 'end', 'rate', 'fobjs'] as const) {
          Object.defineProperty(copied, key, {value: own(initial, key, false), enumerable: true});
        }
        if (Object.hasOwn(initial, 'joint18')) {
          const joint = own(initial, 'joint18', false); link(joint);
          copied.joint18 = joint;
        }
        const value = createSourceAObj(copied), id = Symbol('owned feedback AObj'); aobjs.set(id, value); return id;
      } finally {busy = false;}
    },
    allocateAObj(): symbol {
      enter();
      try {
        // 80243f20: successful memset(0x1c), STOPPED and FLOAT_8043d1fc = 1.
        const value = createSourceAObj({flags: AOBJ_STOPPED, frame: 0, rewind: 0,
          end: 0, rate: 1, fobjs: null, joint18: null});
        const id = Symbol('owned allocated AObj'); aobjs.set(id, value); return id;
      } finally {busy = false;}
    },
    freeAObj(id: symbol | null): void {
      if (id === null) return;
      enter();
      try {freeSourceAObj(getAObj(id)); aobjs.delete(id);}
      finally {busy = false;}
    },
    getAObj,
    createPart(initial: SourceJointAnimationPart): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial part data record required');
      const copied: Partial<SourceJointAnimationPart> = {};
      for (const key of partKeys) {
        const value = own(initial, key, false);
        if (key === 'frame0c') f32(value, key);
        else integer(value, key === 'duration24' ? -32768 : 0, key === 'duration24' ? 32767 : 255, key);
        copied[key] = value;
      }
      const id = Symbol('owned animation part'); parts.set(id, Object.seal(copied) as SourceJointAnimationPart); return id;
    },
    getPart,
    createPose(initial: SourceJointPose): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial pose data record required');
      const translation = createVector(own(initial, 'translation', false) as SourceJointVector, ['x', 'y', 'z']);
      const quaternion = createVector(own(initial, 'quaternion', false) as SourceJointQuaternion, ['x', 'y', 'z', 'w']);
      const id = Symbol('owned joint pose'); poses.set(id, Object.freeze({translation, quaternion})); return id;
    },
    getPose,
    advanceExistingJoint(part: symbol, joint: symbol | null, timestep: number, operationFlags: number, effects: SourceJObjAnimationEffects): void {
      integer(operationFlags, 0, 0xffffffff, 'operationFlags');
      if ((operationFlags & 1) !== 0) fail('animation setup branch is unsupported');
      if ((operationFlags & 2) === 0) return;
      enter();
      try {
        const before = boundAObj(joint); if (before === null) return;
        f32(timestep, 'actor timestep1dc8');
        setSourceAObjRate(before, timestep);
        effect('animateJoint', () => Reflect.apply(animate, joints, [joint, effects]));
        const after = boundAObj(joint); if (after === null) fail('AObj became null before segment feedback');
        const flags = own(after, 'flags'); integer(flags, 0, 0xffffffff, 'AObj flags');
        write(getPart(part), 'segment2d', (flags >>> 26) & 1);
      } finally {busy = false;}
    },
    capturePoseAndFrame(part: symbol, joint: symbol, pose: symbol, effects: SourceJointPoseEffects): void {
      enter();
      try {
        const state = getPart(part), mirror = own(state, 'mirror30'); integer(mirror, 0, 255, 'mirror30');
        if (mirror !== 0) fail('mirrored pose extraction is unsupported');
        const convert = method(effects, 'convertEulerToQuaternion');
        const source = Reflect.apply(jointGet, joints, [joint]) as ReturnType<SourceJObjAnimationRuntime['getJoint']>;
        const output = getPose(pose);
        const y = readFloat(source, 'translation3c');
        write(output.translation, 'x', readFloat(source, 'translation38'));
        write(output.translation, 'y', y);
        write(output.translation, 'z', readFloat(source, 'translation40'));
        const rotation = Object.freeze({x: readFloat(source, 'rotation1c'), y: readFloat(source, 'rotation20'), z: readFloat(source, 'rotation24')});
        effect('Euler conversion', () => Reflect.apply(convert, effects, [rotation, output.quaternion]));
        for (const key of ['x', 'y', 'z', 'w']) readFloat(output.quaternion, key);
        const aobj = boundAObj(joint); if (aobj === null) return;
        const frame = readFloat(aobj, 'frame'); write(state, 'frame0c', frame);
        const mode = own(state, 'mode2f'); integer(mode, 0, 255, 'mode2f');
        if (mode === 0) {
          const duration = own(state, 'duration24'); integer(duration, -32768, 32767, 'duration24');
          if (duration <= frame) write(state, 'complete2e', 1);
        }
      } finally {busy = false;}
    },
  });
  genuineRuntimes.add(runtime); return runtime;
}
