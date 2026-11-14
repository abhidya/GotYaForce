/** Bounded single-JObj HSD_JObjAddAnim (8024dc04), chunk_0071.c:3971–4054.
 * Material/shape descriptors are fixed null, as at caller 8004adc8. This is
 * not generic material attachment or tree setup. The real lifetime loader,
 * track12 promotion and JObj flag owners perform all supported effects.
 * RObjAddAnimAll (chunk_0072.c:637+) returns if either argument is null;
 * both non-null explicitly refuse. DObjAddAnimAll (chunk_0069.c:6239+)
 * preserves existing display animations with null descriptors when the optional
 * display attachment owner is supplied; otherwise non-null targets refuse.
 * Final flags14 and bindings are freshly resolved.
 *
 * Own-data non-proxy tables/records, copied sealed descriptors, opaque symbols,
 * synchronous adapters and poisoned reentry are host bounds. Methods are
 * captured once with original receivers. Argument reads choose target before
 * descriptor where C does not establish evaluation order. Fields are admitted
 * only when consumed; stores require writable targets but ignore prior values.
 * Delegated descriptor, track-order and flag helpers retain their own admission bounds.
 * Failures preserve actual allocations, releases and stores, including dangling
 * old bindings after removal followed by failed loading. No rollback is implied.
 */
import type {SourceDisplayAnimationAttachmentRuntime} from './display-animation-attachment.js';
import type {SourceJObjAnimationRuntime} from './jobj-animation.js';
import type {SourceJObjTrackOrderRuntime} from './jobj-track-order.js';
import type {SourceAObjLifecycleRuntime} from './aobj-lifecycle.js';
export interface SourceJObjAddAnimationDescriptor {aobj08: symbol | null; robj0c: symbol | null; flags10: number}
export interface SourceJObjAddAnimationSources {
  joints: Pick<SourceJObjAnimationRuntime, 'getBinding' | 'getJoint' | 'setFlags' | 'clearFlags'>;
  lifecycle: Pick<SourceAObjLifecycleRuntime, 'removeAObj' | 'loadDescriptor'>;
  order: SourceJObjTrackOrderRuntime;
  displayAttachment?: SourceDisplayAnimationAttachmentRuntime;
}
export interface SourceJObjAddAnimationRuntime {
  createDescriptor(initial: SourceJObjAddAnimationDescriptor): symbol;
  getDescriptor(id: symbol): SourceJObjAddAnimationDescriptor;
  addAnimation(joint: symbol | null, descriptor: symbol | null): void;
}
function fail(why: string): never {throw Error(`[jobj-add-animation] ${why}; offline execution aborted, prior allocations/releases/stores are not rolled back`);}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable target field is unsupported`);
  return p.value;
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function link(record: unknown, key: string): symbol | null {const v = own(record, key); identity(v, key); return v;}
function uint(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) fail(`${where}: expected uint32`);
  return value;
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const fn = own(table, key); if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
export function createSourceJObjAddAnimationRuntime(sources: SourceJObjAddAnimationSources): SourceJObjAddAnimationRuntime {
  const joints = own(sources, 'joints'), lifecycle = own(sources, 'lifecycle'), order = own(sources, 'order');
  const binding = method(joints, 'getBinding'), jointRecord = method(joints, 'getJoint');
  const set = method(joints, 'setFlags'), clear = method(joints, 'clearFlags');
  const remove = method(lifecycle, 'removeAObj'), load = method(lifecycle, 'loadDescriptor');
  const promote = method(order, 'promoteFirstTrack12');
  const displayProperty = Object.getOwnPropertyDescriptor(sources, 'displayAttachment');
  if (displayProperty && !('value' in displayProperty)) fail('displayAttachment: own data property required');
  const display = displayProperty?.value;
  const attachDisplay = display === undefined ? undefined : method(display, 'attachNullDescriptors');
  const descriptors = new Map<symbol, SourceJObjAddAnimationDescriptor>();
  let busy = false, reentered = false;
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const invoke = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[], returnsVoid = false): unknown => {
    const result = Reflect.apply(fn, table, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    if (returnsVoid && result !== undefined) fail('effect must synchronously return void');
    return result;
  };
  const getDescriptor = (id: symbol): SourceJObjAddAnimationDescriptor => {
    const d = descriptors.get(id); if (!d) fail('unknown/non-owned animation descriptor'); return d;
  };
  return Object.freeze({
    createDescriptor(initial: SourceJObjAddAnimationDescriptor): symbol {
      enter(); try {
        const aobj08 = link(initial, 'aobj08'), robj0c = link(initial, 'robj0c');
        const flags10 = uint(own(initial, 'flags10'), 'flags10');
        const id = Symbol('owned AnimJoint descriptor'); descriptors.set(id, Object.seal({aobj08, robj0c, flags10})); return id;
      } finally {busy = false;}
    }, getDescriptor,
    addAnimation(joint: symbol | null, descriptor: symbol | null): void {
      if (joint === null) return;
      enter(); try {
        identity(joint, 'JObj'); identity(descriptor, 'AnimJoint');
        if (descriptor !== null) {
          const old = link(invoke(joints, binding, [joint]), 'aobj7c');
          if (old !== null) invoke(lifecycle, remove, [old], true);
          const loaded = invoke(lifecycle, load, [link(getDescriptor(descriptor), 'aobj08')]);
          identity(loaded, 'loaded AObj');
          const target = invoke(joints, binding, [joint]); own(target, 'aobj7c', true);
          (target as {aobj7c: symbol | null}).aobj7c = loaded;
          invoke(order, promote, [joint], true);
          const robj = link(invoke(joints, binding, [joint]), 'robj80');
          const robjDescriptor = link(getDescriptor(descriptor), 'robj0c');
          if (robj !== null && robjDescriptor !== null) fail('non-null RObj animation attachment is unsupported');
          const flags = uint(own(getDescriptor(descriptor), 'flags10'), 'flags10');
          invoke(joints, (flags & 1) === 0 ? clear : set, [joint, 8], true);
        }
        const flags = uint(own(invoke(joints, jointRecord, [joint]), 'flags14'), 'flags14');
        if ((flags & 0x4020) === 0) {
          const dobj = link(invoke(joints, binding, [joint]), 'dobj18');
          if (attachDisplay) invoke(display, attachDisplay, [dobj], true);
          else if (dobj !== null) fail('non-null DObj animation attachment is unsupported');
        }
      } finally {busy = false;}
    },
  });
}
