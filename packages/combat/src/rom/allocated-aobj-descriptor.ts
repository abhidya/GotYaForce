/** Bounded post-allocation continuation of HSD_AObjLoadDesc (80243d88),
 * chunk_0070.c:2665–2737. The caller supplies the already allocated identity;
 * this does not implement AObjAlloc, its rate initialization, or allocator failure.
 * FLOAT_8043d1f8 is verified positive zero. No other allocation constants are used.
 *
 * Real FObj loading precedes old-list logical lifetime release and attachment.
 * Non-null joint0c lookup/load/reference ownership explicitly refuses, preserving
 * completed stores and real allocations. Pool layout/reuse/counts are not modeled.
 * Null AObj still consumes end04, loads FObjs and consumes joint0c.
 * Null descriptor retains the outer source null branch without allocation.
 * Flags-expression operand read order is a host choice; only stage order is claimed.
 * Fixed own-data adapters retain this and must synchronously perform real work
 * or refuse. Records must be stable, owned, non-proxy own-data objects. Copied
 * sealed descriptors, per-consumption validation and poisoned reentry are host
 * bounds, not source branches. There is no rollback, parallel AObj or fake loader.
 */
import {setSourceAObjFlags, setSourceAObjRewindFrame, setSourceAObjEndFrame, type SourceAObj} from './aobj-clock.js';
import type {SourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import type {SourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import type {SourceFObjRuntime} from './fobj-list.js';

export interface SourceAllocatedAObjDescriptor {flags00: number; end04: number; fobj08: symbol | null; joint0c: symbol | null}
export interface SourceAllocatedAObjDescriptorSources {
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getAObj'>;
  fobjs: Pick<SourceFObjDescriptorRuntime, 'loadDescriptors'>;
  removal: Pick<SourceFObjRuntime, 'removeAll'>;
}
export interface SourceAllocatedAObjDescriptorRuntime {
  createDescriptor(initial: SourceAllocatedAObjDescriptor): symbol;
  getDescriptor(identity: symbol): SourceAllocatedAObjDescriptor;
  continueAllocatedLoad(aobjId: symbol | null, descriptorId: symbol | null): symbol | null;
}
function fail(reason: string): never {
  throw Error(`[allocated-aobj-descriptor] ${reason}; offline execution aborted, prior allocations/stores are not rolled back`);
}
function own(record: unknown, key: string, writable = true): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function link(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function flags(value: unknown): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) fail('flags00: expected uint32');
}
function finiteFloat(value: unknown): asserts value is number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail('end04: expected finite source float32');
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const fn = own(table, key, false);
  if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
export function createSourceAllocatedAObjDescriptorRuntime(sources: SourceAllocatedAObjDescriptorSources): SourceAllocatedAObjDescriptorRuntime {
  const feedback = own(sources, 'feedback', false), fobjs = own(sources, 'fobjs', false);
  const removal = own(sources, 'removal', false);
  const getAObj = method(feedback, 'getAObj'), load = method(fobjs, 'loadDescriptors');
  const remove = method(removal, 'removeAll');
  const descriptors = new Map<symbol, SourceAllocatedAObjDescriptor>();
  let busy = false, reentered = false;
  const enter = (): void => {
    if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
    busy = true; reentered = false;
  };
  const invoke = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const value = Reflect.apply(fn, table, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    return value;
  };
  const getDescriptor = (id: symbol): SourceAllocatedAObjDescriptor => {
    const value = descriptors.get(id); if (!value) fail('unknown/non-owned descriptor identity'); return value;
  };
  return Object.freeze({
    createDescriptor(initial: SourceAllocatedAObjDescriptor): symbol {
      enter();
      try {
        const flags00 = own(initial, 'flags00', false); flags(flags00);
        const end04 = own(initial, 'end04', false); finiteFloat(end04);
        const fobj08 = own(initial, 'fobj08', false); link(fobj08, 'fobj08');
        const joint0c = own(initial, 'joint0c', false); link(joint0c, 'joint0c');
        const id = Symbol('owned allocated AObj descriptor');
        descriptors.set(id, Object.seal({flags00, end04, fobj08, joint0c}));
        return id;
      } finally {busy = false;}
    },
    getDescriptor,
    continueAllocatedLoad(aobjId: symbol | null, descriptorId: symbol | null): symbol | null {
      if (descriptorId === null) return null;
      enter();
      try {
        if (typeof descriptorId !== 'symbol') fail('non-null descriptor identity required after allocation');
        const descriptor = getDescriptor(descriptorId);
        link(aobjId, 'allocated AObj');
        // Resolve once and retain this actual owned target across real loading.
        const target = aobjId === null ? null : invoke(feedback, getAObj, [aobjId]) as SourceAObj;
        if (aobjId !== null && (target === null || typeof target !== 'object')) fail('getAObj: owned AObj data record required');
        if (target !== null) {
          const mask = own(descriptor, 'flags00'); flags(mask); setSourceAObjFlags(target, mask);
        }
        setSourceAObjRewindFrame(target, 0);
        // Access is unconditional, numeric admission belongs to the actual setter.
        const end = own(descriptor, 'end04'); setSourceAObjEndFrame(target, end as number);
        const head = own(descriptor, 'fobj08'); link(head, 'fobj08');
        const loaded = invoke(fobjs, load, [head]); link(loaded, 'loadDescriptors result');
        if (target !== null) {
          const old = own(target, 'fobjs', false); link(old, 'AObj fobjs');
          if (old !== null) {
            const result = invoke(removal, remove, [old]);
            if (result !== undefined) fail('removeAll must complete synchronously and return undefined');
          }
          // Source attachment follows release. Reject a non-writable destination
          // here, without validating the old value again or undoing real release.
          own(target, 'fobjs');
          target.fobjs = loaded;
        }
        const joint = own(descriptor, 'joint0c'); link(joint, 'joint0c');
        if (joint !== null) fail('non-null joint ID lookup/load/reference ownership is unsupported');
        return aobjId;
      } finally {busy = false;}
    },
  });
}
