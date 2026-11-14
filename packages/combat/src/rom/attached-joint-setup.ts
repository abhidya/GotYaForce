/** Bounded continuation INSIDE 8004adc8 after successful archive/JObjAddAnim.
 * Source: chunk_0006.c:674–1013, non-null attached-AObj branch at 838–1009.
 * This helper never attaches animation and cannot enable any setup-bit1 caller.
 * Full archive/descriptor setup, transform fallbacks and live activation refuse
 * elsewhere. Null joint/initial AObj is outside this continuation's domain.
 *
 * Snapshot the initial AObj identity/head, scan every FObj (track13 then live
 * next00), then require masks 2/4/8/20/40/80 before any fallback write. Tracks
 * 0..31 alone are admitted: oversized PPC shifts are not inferred from JS.
 * Loop byte EXACTLY 1 sets LOOP, consumes signed rewind26 and refuses at the
 * unverified DOUBLE_804370f8 conversion. This is a completed prefix, NOT loop
 * support. Other bytes clear LOOP and never consume rewind26. No values for
 * 8043d1fc, 804370f4, 804370f0 or DOUBLE_804370f8 are guessed here.
 *
 * Non-loop continuation reloads current non-null AObj/end, admits only finite
 * exact-f32 end whose truncation toward zero fits signed32, stores the signed
 * low16 into shared part24, requests the joint at shared part0c with mask1,
 * reloads actor1dc8/current AObj, sets rate, animates
 * once and unconditionally stores segment2d=0. No post-animation AObj read,
 * WRAPPED copy, pose capture, complete/mode/mirror read or counter reset occurs.
 * Host order for the rate call is actor timestep before current AObj; relative
 * source argument load order is not established by the decompiled expression.
 * Timestep field access is always checked, but numeric admission belongs to
 * setSourceAObjRate: a null rate target ignores even an invalid numeric value.
 *
 * Runtime/adapters are fixed own-data methods with their original receivers.
 * They must synchronously do real work or refuse; getFObj must resolve the
 * corresponding actual owned node within the supplied initial AObj's runtime.
 * Returned records must be stable, owned, non-proxy data records. bindPart keeps
 * the existing feedback part record, never creates a parallel part record.
 * Only the separate two-field setup binding is copied/sealed. Per-access
 * validation, writable consumed fields, cycle/budget caps and poisoned reentry
 * are host bounds. Fault-injection wrappers are not source callbacks. Completed
 * writes/effects survive refusal; async/deferred work is unsupported.
 */
import {AOBJ_LOOP, clearSourceAObjFlags, setSourceAObjFlags, setSourceAObjRate, type SourceAObj} from './aobj-clock.js';
import type {SourceFObjHeader} from './fobj-list.js';
import type {SourceJObjAnimationRuntime, SourceJObjAnimationEffects} from './jobj-animation.js';
import type {SourceJointAnimationFeedbackRuntime, SourceJointAnimationPart} from './joint-animation-feedback.js';
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceAnimationRequestRuntime} from './animation-request.js';

export interface SourceAttachedJointSetupBinding {rewind26: number; loop2c: number}
export interface SourceAttachedJointSetupSources {
  joints: Pick<SourceJObjAnimationRuntime, 'getBinding' | 'animateJoint'>;
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getPart' | 'getAObj'>;
  actors: Pick<SourceActorJointMappingRuntime, 'getActor'>;
  requests: Pick<SourceAnimationRequestRuntime, 'requestJoint'>;
  fobjs: {getFObj(aobjId: symbol, nodeId: symbol): SourceFObjHeader};
}
export interface SourceAttachedJointSetupRuntime {
  getActualFeedback(): SourceAttachedJointSetupSources['feedback'];
  getActualMapping(): SourceAttachedJointSetupSources['actors'];
  bindPart(identity: symbol, initial: SourceAttachedJointSetupBinding): void;
  getPartBinding(identity: symbol): SourceAttachedJointSetupBinding;
  continueAttachedSetupTail(actor: symbol, part: symbol, joint: symbol | null): void;
}
const genuineRuntimes = new WeakSet<object>();
export function isSourceAttachedJointSetupRuntime(value: unknown): value is SourceAttachedJointSetupRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[attached-joint-setup] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = true): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property.value;
}
function integer(value: unknown, min: number, max: number, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: expected integer ${min}..${max}`);
}
function float(value: unknown, where: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: expected finite source float32`);
}
function link(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function readLink(record: unknown, key: string): symbol | null {const value = own(record, key); link(value, key); return value;}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const value = own(table, key, false); if (typeof value !== 'function') fail(`${key}: own data-function required`);
  return value as (...args: never[]) => unknown;
}
function write(record: object, key: string, value: number): void {own(record, key); (record as Record<string, unknown>)[key] = value;}
export function createSourceAttachedJointSetupRuntime(sources: SourceAttachedJointSetupSources,
  animationEffects: SourceJObjAnimationEffects, maxNodes = 4096): SourceAttachedJointSetupRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  const joints = own(sources, 'joints', false), feedback = own(sources, 'feedback', false), actors = own(sources, 'actors', false);
  const requests = own(sources, 'requests', false), fobjs = own(sources, 'fobjs', false);
  const getBinding = method(joints, 'getBinding'), animate = method(joints, 'animateJoint');
  const getPart = method(feedback, 'getPart'), getAObj = method(feedback, 'getAObj');
  const getActor = method(actors, 'getActor'), request = method(requests, 'requestJoint'), getFObj = method(fobjs, 'getFObj');
  const interpret = method(animationEffects, 'interpretAObj'), robj = method(animationEffects, 'animateRObjs'), dobj = method(animationEffects, 'animateDObjs');
  const parts = new Map<symbol, {part: SourceJointAnimationPart; binding: SourceAttachedJointSetupBinding}>();
  let busy = false, reentered = false;
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const checkReentry = (): void => {if (reentered) fail('same-runtime reentry was caught inside an adapter');};
  const resolve = (table: unknown, get: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const value = Reflect.apply(get, table, args); checkReentry(); return value;
  };
  const call = (name: string, table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): void => {
    let value: unknown;
    try {value = Reflect.apply(fn, table, args);} catch (e) {fail(`${name}: effect threw (${String(e)})`);}
    checkReentry(); if (value !== undefined) fail(`${name}: effect must complete synchronously and return undefined`);
  };
  const fixedEffects = Object.freeze<SourceJObjAnimationEffects>({
    interpretAObj(aobj, owner, callback) {call('interpret AObj', animationEffects, interpret, [aobj, owner, callback]);},
    animateRObjs(list) {call('animate RObjs', animationEffects, robj, [list]);},
    animateDObjs(list) {call('animate DObjs', animationEffects, dobj, [list]);},
  });
  const bound = (joint: symbol): {id: symbol; aobj: SourceAObj} | null => {
    const id = readLink(resolve(joints, getBinding, [joint]), 'aobj7c');
    return id === null ? null : {id, aobj: resolve(feedback, getAObj, [id]) as SourceAObj};
  };
  const partEntry = (id: symbol) => {const value = parts.get(id); if (!value) fail('unknown/non-owned setup part'); return value;};
  const runtime: SourceAttachedJointSetupRuntime = Object.freeze({
    getActualFeedback() {return feedback as SourceAttachedJointSetupSources['feedback'];},
    getActualMapping() {return actors as SourceAttachedJointSetupSources['actors'];},
    bindPart(id: symbol, initial: SourceAttachedJointSetupBinding): void {
      enter();
      try {
        if (typeof id !== 'symbol') fail('part identity must be a symbol');
        if (parts.has(id)) fail('part already has a setup binding');
        const rewind26 = own(initial, 'rewind26', false), loop2c = own(initial, 'loop2c', false);
        integer(rewind26, -32768, 32767, 'rewind26'); integer(loop2c, 0, 255, 'loop2c');
        const part = resolve(feedback, getPart, [id]) as SourceJointAnimationPart;
        parts.set(id, {part, binding: Object.seal({rewind26, loop2c})});
      } finally {busy = false;}
    },
    getPartBinding(id: symbol): SourceAttachedJointSetupBinding {return partEntry(id).binding;},
    continueAttachedSetupTail(actorId: symbol, partId: symbol, joint: symbol | null): void {
      enter();
      try {
        if (typeof joint !== 'symbol') fail('non-null owned joint required after successful attachment');
        const initial = bound(joint); if (initial === null) fail('non-null attached AObj required');
        let current = readLink(initial.aobj, 'fobjs'), mask = 0;
        const seen = new Set<symbol>();
        while (current !== null) {
          if (seen.has(current)) fail('cycle/revisited FObj is unsupported');
          if (seen.size >= maxNodes) fail('FObj visit budget exhausted');
          const node = resolve(fobjs, getFObj, [initial.id, current]); seen.add(current);
          const track = own(node, 'track13'); integer(track, 0, 31, 'track13 (oversized shifts unsupported)');
          mask = (mask | (1 << track)) >>> 0;
          current = readLink(node, 'next00');
        }
        for (const bit of [2, 4, 8, 0x20, 0x40, 0x80]) {
          if ((mask & bit) === 0) fail(`missing track fallback mask 0x${bit.toString(16)} is unsupported`);
        }
        const {part, binding} = partEntry(partId), loop = own(binding, 'loop2c'); integer(loop, 0, 255, 'loop2c');
        const flagTarget = bound(joint);
        if (loop === 1) {
          setSourceAObjFlags(flagTarget?.aobj ?? null, AOBJ_LOOP);
          const rewind = own(binding, 'rewind26'); integer(rewind, -32768, 32767, 'rewind26');
          fail('rewind26 conversion requires unverified DOUBLE_804370f8');
        }
        clearSourceAObjFlags(flagTarget?.aobj ?? null, AOBJ_LOOP);
        const durationTarget = bound(joint); if (durationTarget === null) fail('non-null AObj required for duration24');
        const end = own(durationTarget.aobj, 'end'); float(end, 'AObj end');
        const truncated = Math.trunc(end); integer(truncated, -0x80000000, 0x7fffffff, 'duration24 conversion');
        write(part, 'duration24', (truncated << 16) >> 16);
        const frame = own(part, 'frame0c'); float(frame, 'frame0c');
        call('requestJoint', requests, request, [joint, frame, 1]);
        // Host order only: C argument evaluation does not establish load order.
        const actor = resolve(actors, getActor, [actorId]), timestep = own(actor, 'timestep1dc8') as number;
        const rateTarget = bound(joint); setSourceAObjRate(rateTarget?.aobj ?? null, timestep);
        call('animateJoint', joints, animate, [joint, fixedEffects]);
        write(part, 'segment2d', 0);
      } finally {busy = false;}
    },
  });
  genuineRuntimes.add(runtime); return runtime;
}
