/** Source-owned AObj allocation/removal and descriptor-load composition.
 * 80243f20 / 80243eb0 / 80243f8c, chunk_0070.c:2741–2813; load 80243d88.
 * The feedback owner allocates real clock records (STOPPED, rate 1, zero/null
 * remainder), and releases their logical identities. FLOAT_8043d1fc = 1 is
 * verified by the archived program constants. Physical pool layout/reuse, OOM,
 * allocator counts and non-null joint-reference unref are unsupported.
 *
 * Removal executes the real FObj release before either null store or AObj free.
 * Descriptor load allocates BEFORE the existing continuation resolves its input.
 * Failure preserves all real allocations/releases and completed source stores.
 * Fixed own-data methods retain receivers and must synchronously perform real
 * work. Non-proxy stable records and caught-reentry poison are host bounds.
 * The delegated descriptor continuation retains its narrower writable-descriptor
 * admission checks. This removal helper accepts read-only operands and checks
 * writability only at its reached stores.
 * No alternate clock, allocator, FObj implementation or rollback is supplied.
 */
import type {SourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import type {SourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import type {SourceFObjRuntime} from './fobj-list.js';

export interface SourceAObjLifecycleSources {
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'allocateAObj' | 'getAObj' | 'freeAObj'>;
  fobjs: Pick<SourceFObjRuntime, 'removeAll'>;
  descriptors: Pick<SourceAllocatedAObjDescriptorRuntime, 'continueAllocatedLoad'>;
}
export interface SourceAObjLifecycleRuntime {
  allocateAObj(): symbol;
  removeAObj(identity: symbol | null): void;
  loadDescriptor(descriptor: symbol | null): symbol | null;
}
function fail(reason: string): never {
  throw Error(`[aobj-lifecycle] ${reason}; offline execution aborted, prior allocations/releases/stores are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function link(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: opaque symbol or null required`);
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const value = own(table, key);
  if (typeof value !== 'function') fail(`${key}: own data-function required`);
  return value as (...args: never[]) => unknown;
}
export function createSourceAObjLifecycleRuntime(sources: SourceAObjLifecycleSources): SourceAObjLifecycleRuntime {
  const feedback = own(sources, 'feedback'), fobjs = own(sources, 'fobjs'), descriptors = own(sources, 'descriptors');
  const allocate = method(feedback, 'allocateAObj'), get = method(feedback, 'getAObj'), free = method(feedback, 'freeAObj');
  const remove = method(fobjs, 'removeAll'), load = method(descriptors, 'continueAllocatedLoad');
  let busy = false, reentered = false;
  const enter = (): void => {
    if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
    busy = true; reentered = false;
  };
  const invoke = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, table, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    return result;
  };
  const allocateOwned = (): symbol => {
    const id = invoke(feedback, allocate, []);
    if (typeof id !== 'symbol') fail('allocateAObj must synchronously return an owned symbol');
    return id;
  };
  return Object.freeze({
    allocateAObj(): symbol {
      enter();
      try {return allocateOwned();} finally {busy = false;}
    },
    removeAObj(id: symbol | null): void {
      if (id === null) return;
      enter();
      try {
        link(id, 'AObj identity');
        const target = invoke(feedback, get, [id]);
        const head = own(target, 'fobjs'); link(head, 'fobjs');
        if (head !== null) {
          const result = invoke(fobjs, remove, [head]);
          if (result !== undefined) fail('removeAll must synchronously return undefined');
        }
        own(target, 'fobjs', true);
        (target as {fobjs: symbol | null}).fobjs = null;
        const joint = own(target, 'joint18'); link(joint, 'joint18');
        if (joint !== null) fail('non-null joint18 reference unref is unsupported');
        own(target, 'joint18', true);
        (target as {joint18: symbol | null}).joint18 = null;
        const result = invoke(feedback, free, [id]);
        if (result !== undefined) fail('freeAObj must synchronously return undefined');
      } finally {busy = false;}
    },
    loadDescriptor(descriptor: symbol | null): symbol | null {
      if (descriptor === null) return null;
      enter();
      try {
        // No descriptor-field validation before the actual owned allocation.
        const id = allocateOwned();
        const result = invoke(descriptors, load, [id, descriptor]);
        if (result !== id) fail('continueAllocatedLoad must synchronously return the allocated identity');
        return id;
      } finally {busy = false;}
    },
  });
}
