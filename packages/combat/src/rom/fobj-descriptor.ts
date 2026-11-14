/** Bounded offline HSD_FObjLoadDesc / HSD_FObjAlloc field effects.
 * Source: chunk_0071.c:1227–1363, 8024a208 / 8024a430. Ghidra's prologue
 * and return types are imperfect; this is not ABI or instruction matching.
 * Allocation zeroes the modeled 0x30-byte FObj header through the actual FObj
 * runtime. FObjs are allocated head-to-tail, then initialized tail-to-head
 * in source store order. The five unrolled source allocations are not a limit.
 * An iterative stack preserves that order without depending on the JS stack.
 *
 * Records and runtime method tables must be non-proxy own-data objects. Owned
 * sealed descriptors are copied; no source RAM, pointer aliasing, allocator
 * failure semantics or memory faults are modeled. Runtime methods are captured
 * once and retain their original receiver. Supply a real SourceFObjRuntime (or
 * a synchronous wrapper that actually delegates allocation/resolution to it),
 * not an event-only substitute. Data identities stay opaque until the existing
 * decoder consumes them; this loader does not check bytes or declared length.
 *
 * Only finite binary32 integral signed16 start offsets are loaded; wider,
 * fractional and exceptional conversions refuse at the offset-store boundary.
 * No PPC conversion behavior outside that domain is guessed. Descriptor
 * factories may retain any finite binary32 start. Float -0 becomes integer +0.
 * Per-field own-data/writability/type checks occur only when consumed; prior
 * target values and unrelated fields are not read. Cursor remains allocation's
 * null until a later request. Null input bypasses validation and reentry guards.
 * Ownership, cycles/revisits, visit budgets and same-loader reentry refusal are
 * host limits, not retail branches. Failures retain allocations and completed
 * stores, including fully initialized tails; there is no rollback/free.
 */
import type {SourceFObjHeader, SourceFObjRuntime} from './fobj-list.js';

export interface SourceFObjDescriptor {
  next00: symbol | null;
  length04: number;
  start08: number;
  track0c: number;
  format0d: number;
  format0e: number;
  data10: symbol | null;
}
export interface SourceFObjDescriptorRuntime {
  createDescriptor(initial: SourceFObjDescriptor): symbol;
  getDescriptor(identity: symbol): SourceFObjDescriptor;
  loadDescriptors(head: symbol | null): symbol | null;
}
const descriptorKeys = ['next00', 'length04', 'start08', 'track0c', 'format0d', 'format0e', 'data10'] as const;
function fail(reason: string): never {
  throw Error(`[fobj-descriptor] ${reason}; offline execution aborted, prior allocations/stores are not rolled back`);
}
function identity(value: unknown, where: string): asserts value is symbol | null {
  if (value !== null && typeof value !== 'symbol') fail(`${where}: expected opaque symbol or null`);
}
function ownValue(record: object, key: string, writable: boolean): unknown {
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable descriptor field is unsupported`);
  return property.value;
}
function validateField(key: keyof SourceFObjDescriptor, value: unknown): void {
  if (key === 'next00' || key === 'data10') identity(value, key);
  else if (key === 'start08') {
    if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) {
      fail('start08: expected finite source float32');
    }
  } else {
    const max = key === 'length04' ? 0xffffffff : 255;
    if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > max) {
      fail(`${key}: expected integer 0..${max}`);
    }
  }
}
function read<K extends keyof SourceFObjDescriptor>(record: SourceFObjDescriptor, key: K): SourceFObjDescriptor[K] {
  const value = ownValue(record, key, true);
  validateField(key, value);
  return value as SourceFObjDescriptor[K];
}
function store<K extends keyof SourceFObjHeader>(node: SourceFObjHeader, key: K, value: SourceFObjHeader[K]): void {
  const property = Object.getOwnPropertyDescriptor(node, key);
  if (!property || !('value' in property)) fail(`${key}: own target data property required`);
  if (!property.writable) fail(`${key}: non-writable target field is unsupported`);
  // The old target value is deliberately not inspected or validated.
  node[key] = value;
}
function zeroHeader(): SourceFObjHeader {
  return {next00: null, cursor04: null, base08: null, length0c: 0, flags10: 0,
    byte11: 0, byte12: 0, track13: 0, format14: 0, format15: 0, half16: 0,
    offset18: 0, half1a: 0, frame1c: 0, value20: 0, value24: 0, value28: 0, value2c: 0};
}
/** maxNodes is an offline host visit bound, not a source list-length constant. */
export function createSourceFObjDescriptorRuntime(
  fobjs: Pick<SourceFObjRuntime, 'createNode' | 'getNode'>, maxNodes = 4096,
): SourceFObjDescriptorRuntime {
  if (!Number.isSafeInteger(maxNodes) || maxNodes < 1) fail('maxNodes must be a positive safe integer');
  if (fobjs === null || typeof fobjs !== 'object') fail('FObj runtime data table required');
  const createNode = ownValue(fobjs, 'createNode', false), getNode = ownValue(fobjs, 'getNode', false);
  if (typeof createNode !== 'function' || typeof getNode !== 'function') fail('runtime methods must be own data-functions');
  const dispatch = Object.freeze({createNode, getNode});
  const descriptors = new Map<symbol, SourceFObjDescriptor>();
  let busy = false, reentered = false;
  const getDescriptor = (id: symbol): SourceFObjDescriptor => {
    const record = descriptors.get(id);
    if (!record) fail('unknown/non-owned descriptor identity');
    return record;
  };
  const call = (name: keyof typeof dispatch, args: unknown[]): unknown => {
    let result: unknown;
    try { result = Reflect.apply(dispatch[name], fobjs, args); }
    catch (error) { fail(`${name}: runtime threw (${String(error)})`); }
    // In particular, a caught reentry inside allocation must abort BEFORE the
    // descriptor's next read or any following allocation/store.
    if (reentered) fail(`${name}: same-loader reentry was caught inside runtime`);
    return result;
  };
  return Object.freeze({
    createDescriptor(initial: SourceFObjDescriptor): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial descriptor data record required');
      const copied: Partial<SourceFObjDescriptor> = {};
      for (const key of descriptorKeys) {
        const value = ownValue(initial, key, false);
        validateField(key, value);
        Object.defineProperty(copied, key, {value, writable: true, enumerable: true});
      }
      const id = Symbol('owned FObj descriptor');
      descriptors.set(id, Object.seal(copied) as SourceFObjDescriptor);
      return id;
    },
    getDescriptor,
    loadDescriptors(head: symbol | null): symbol | null {
      if (head === null) return null;
      if (busy) { reentered = true; fail('same-loader reentry is unsupported'); }
      busy = true; reentered = false;
      try {
        const seen = new Set<symbol>();
        const pending: {descriptor: SourceFObjDescriptor; node: symbol}[] = [];
        let current: symbol | null = head;
        while (current !== null) {
          identity(current, 'descriptor list');
          if (seen.has(current)) fail('cycle/revisited descriptor is unsupported');
          if (seen.size >= maxNodes) fail('descriptor visit budget exhausted');
          seen.add(current);
          const node = call('createNode', [zeroHeader()]);
          if (typeof node !== 'symbol') fail('createNode: expected owned FObj identity');
          // Ownership resolution, like the next-field access, follows allocation.
          const descriptor = getDescriptor(current);
          pending.push({descriptor, node});
          current = read(descriptor, 'next00');
        }
        let next: symbol | null = null;
        for (let index = pending.length - 1; index >= 0; index--) {
          const entry = pending[index]!;
          const node = call('getNode', [entry.node]) as SourceFObjHeader;
          if (node === null || typeof node !== 'object') fail('getNode: expected owned FObj data record');
          store(node, 'next00', next);
          const start = read(entry.descriptor, 'start08');
          if (!Number.isInteger(start) || start < -32768 || start > 32767) {
            fail('start08: offset store supports only integral signed16 values');
          }
          store(node, 'offset18', start === 0 ? 0 : start);
          store(node, 'track13', read(entry.descriptor, 'track0c'));
          store(node, 'format14', read(entry.descriptor, 'format0d'));
          store(node, 'format15', read(entry.descriptor, 'format0e'));
          store(node, 'base08', read(entry.descriptor, 'data10'));
          store(node, 'length0c', read(entry.descriptor, 'length04'));
          store(node, 'flags10', 0);
          next = entry.node;
        }
        return next;
      } finally { busy = false; }
    },
  });
}
