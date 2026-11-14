/** Bounded bare DAT -> existing scalar JObj owners, offline only.
 * Source: chunk_0071.c:5577–5798,6113–6200,7583–7599; DAT: chunk_0072.c:3637–3723.
 * Explicit public index selects ONE root; no actor-bank inference. Root next is
 * source-ignored: it is not followed or pointer-classified, although global DAT
 * relocation validity still applies. Child next links retain source order.
 * This imports scalar transforms/topology, NOT full models: even the source's
 * identity live matrix initialization is outside the scalar owner. No renderer,
 * world matrix, ID-table reconstruction, live wiring or source fault order.
 * Classnames, instance/quaternion flags, DObj (including gated), RObj and matrix
 * pointers refuse. Repeated reachable descriptors refuse: retail non-instance
 * loads allocate fresh objects, so aliases MUST NOT be collapsed to one owner.
 * All geometry/names/relocations and the reachable graph preflight before owner
 * factories. Finite f32 copies preserve signed zero/subnormals. Init flags 0x40
 * OR descriptor flags; AddChild flags use each completed subtree, postorder.
 * The private byte copy, finite budgets, aligned disjoint descriptors, no scalar
 * relocation, non-shared Uint8Array and stable non-proxy own-data synchronous
 * adapters are host limits. Captured receivers and caught-reentry poison apply.
 * Failures retain completed owner allocations/writes, without rollback.
 * Relocated zero is data+0; unrelocated zero is null. Public zero is data+0.
 * Output metadata is frozen; owned joint/binding records remain mutable. No
 * AObj/RObj/DObj or class callback is fabricated: callers bind actual owners.
 */
import type {SourceJObjAnimationRuntime, SourceJObjAnimationBinding} from './jobj-animation.js';
import type {SourceJObjScalarHeader} from './jobj-update.js';
export interface SourceJObjModelHydrationLimits {
  maxArchiveBytes?: number; maxRelocations?: number; maxPublics?: number;
  maxStringBytes?: number; maxDescriptors?: number; maxDepth?: number;
}
export interface SourceHydratedJObjModel {
  readonly root: symbol; readonly publicIndex: number; readonly name: string; readonly dataOffset: number;
  readonly joints: readonly Readonly<{dataOffset: number; joint: symbol}>[];
}
export interface SourceJObjModelHydrationRuntime {
  hydrateModelArchive(bytes: Uint8Array, publicIndex: number): SourceHydratedJObjModel;
}
const scalarKeys = ['rotation1c', 'rotation20', 'rotation24', 'scale2c', 'scale30', 'scale34',
  'translation38', 'translation3c', 'translation40'] as const;
const bindingKeys = ['parent0c', 'aobj7c', 'robj80', 'dobj18', 'classUpdate50'] as const;
const CAP = 16 * 1024 * 1024;
function fail(reason: string): never {throw Error(`[jobj-model-hydration] ${reason}; offline import aborted, completed owner effects are not rolled back`);}
function own(record: unknown, key: string): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own-data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  return p.value;
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const fn = own(table, key); if (typeof fn !== 'function') fail(`${key}: own data-function required`);
  return fn as (...args: never[]) => unknown;
}
function uint(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) fail(`${where}: uint32 required`);
  return value;
}
function copiedBytes(value: Uint8Array, cap: number): Uint8Array {
  const typed = Object.getPrototypeOf(Uint8Array.prototype) as object;
  const tag = Reflect.apply(Object.getOwnPropertyDescriptor(typed, Symbol.toStringTag)!.get!, value, []);
  if (tag !== 'Uint8Array') fail('non-shared Uint8Array required');
  const buffer = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'buffer')!.get!, value, []);
  try {Reflect.apply(Object.getOwnPropertyDescriptor(ArrayBuffer.prototype, 'byteLength')!.get!, buffer, []);}
  catch {fail('non-shared Uint8Array required');}
  const length = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'length')!.get!, value, []) as number;
  if (length > cap) fail('archive byte budget exceeded');
  const copy = new Uint8Array(length);
  try {Reflect.apply(Uint8Array.prototype.set, copy, [value]);} catch {fail('detached Uint8Array unsupported');}
  return copy;
}

export function createSourceJObjModelHydrationRuntime(
  joints: Pick<SourceJObjAnimationRuntime, 'createJoint' | 'getJoint' | 'getBinding'>,
  limits: SourceJObjModelHydrationLimits = {},
): SourceJObjModelHydrationRuntime {
  const budget = (key: keyof SourceJObjModelHydrationLimits, fallback: number, ceiling: number): number => {
    const p = Object.getOwnPropertyDescriptor(limits, key);
    const n = p === undefined ? fallback : uint(own(limits, key), key);
    if (n < 1 || n > ceiling) fail(`${key}: expected 1..${ceiling}`);
    return n;
  };
  const maxArchiveBytes = budget('maxArchiveBytes', CAP, CAP), maxRelocations = budget('maxRelocations', 65536, CAP / 4);
  const maxPublics = budget('maxPublics', 4096, CAP / 8), maxStringBytes = budget('maxStringBytes', 65536, CAP);
  const maxDescriptors = budget('maxDescriptors', 4096, CAP / 64), maxDepth = budget('maxDepth', 4096, CAP / 64);
  const factory = method(joints, 'createJoint'), getJoint = method(joints, 'getJoint'), getBinding = method(joints, 'getBinding');
  let busy = false, poisoned = false;
  const poisonCheck = (): void => {if (poisoned) fail('same-runtime reentry caught inside adapter/input');};
  const invoke = (fn: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const value = Reflect.apply(fn, joints, args); poisonCheck(); return value;
  };
  const writable = (record: unknown, key: string): unknown => {
    const value = own(record, key);
    if (!Object.getOwnPropertyDescriptor(record, key)!.writable) fail(`${key}: writable own data required`);
    return value;
  };
  return Object.freeze({
    hydrateModelArchive(input: Uint8Array, publicIndex: number): SourceHydratedJObjModel {
      if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
      busy = true; poisoned = false;
      try {
        const bytes = copiedBytes(input, maxArchiveBytes), view = new DataView(bytes.buffer);
        if (bytes.length < 0x20) fail('truncated DAT header');
        const word = (at: number): number => view.getUint32(at, false);
        const fileSize = word(0), dataSize = word(4), relocCount = word(8), publicCount = word(12), externCount = word(16);
        if (fileSize !== bytes.length) fail('DAT file size must equal supplied byte length');
        if (externCount !== 0) fail('external-reference table unsupported');
        if (relocCount > maxRelocations) fail('relocation budget exceeded');
        if (publicCount > maxPublics) fail('public entry budget exceeded');
        const dataStart = 0x20, relocStart = dataStart + dataSize, publicStart = relocStart + relocCount * 4;
        const stringStart = publicStart + publicCount * 8;
        if (stringStart > bytes.length) fail('DAT table extents out of bounds');
        const range = (at: number, length: number, kind: string): void => {
          if (at < 0 || at + length > dataSize) fail(`${kind}: data extent out of bounds`);
        };
        const relocations = new Set<number>();
        for (let i = 0; i < relocCount; i++) {
          const at = word(relocStart + i * 4);
          if (at % 4 !== 0) fail('unaligned relocation slot unsupported');
          range(at, 4, 'relocation slot');
          if (relocations.has(at)) fail('duplicate relocation slot unsupported');
          if (word(dataStart + at) >= dataSize) fail('relocation target out of bounds');
          relocations.add(at);
        }
        const pointer = (at: number): number | null => {
          const raw = word(dataStart + at);
          if (relocations.has(at)) return raw; // Including relocated zero.
          if (raw !== 0) fail(`unrelocated nonzero pointer at data+${at.toString(16)}`);
          return null;
        };
        let stringBytes = 0;
        const names = new Map<number, string>();
        const publics: {offset: number; name: string}[] = [];
        for (let i = 0; i < publicCount; i++) {
          const offset = word(publicStart + i * 8), nameOffset = word(publicStart + i * 8 + 4);
          if (offset >= dataSize) fail('public target out of bounds');
          const nameStart = stringStart + nameOffset;
          if (nameStart >= bytes.length) fail('public name offset out of bounds');
          let name = names.get(nameOffset);
          if (name === undefined) {
            name = '';
            for (let at = nameStart; ; at++) {
              if (at >= bytes.length) fail('unterminated public name');
              if (++stringBytes > maxStringBytes) fail('public string byte budget exceeded');
              const byte = bytes[at]!; if (byte === 0) break;
              name += String.fromCharCode(byte);
            }
            names.set(nameOffset, name);
          }
          publics.push({offset, name});
        }
        const index = uint(publicIndex, 'public index');
        if (index >= publics.length) fail('selected public index out of bounds');
        const selected = publics[index]!;
        type Plan = {at: number; parent: number | null; child: number | null; next: number | null; header: SourceJObjScalarHeader};
        const plans: Plan[] = [], byOffset = new Map<number, Plan>(), occupied = new Set<number>();
        const stack: {at: number; parent: number | null; depth: number}[] = [{at: selected.offset, parent: null, depth: 1}];
        while (stack.length) {
          const {at, parent, depth} = stack.pop()!;
          if (depth > maxDepth) fail('depth budget exceeded');
          if (byOffset.has(at)) fail('repeated reachable descriptor/cycle unsupported');
          if (plans.length >= maxDescriptors) fail('descriptor budget exceeded');
          range(at, 0x40, 'JObj');
          if (at % 4) fail('unaligned JObj descriptor');
          for (let delta = 0; delta < 0x40; delta += 4) {
            if (occupied.has(at + delta)) fail('overlapping descriptor extents');
            if (relocations.has(at + delta) && ![0, 8, 12, 16, 56, 60].includes(delta)) fail('relocation on descriptor scalar');
            occupied.add(at + delta);
          }
          if (pointer(at) !== null) fail('custom classname unsupported');
          const flags = word(dataStart + at + 4);
          if (flags & 0x1000) fail('instance joint unsupported');
          if (flags & 0x20000) fail('quaternion joint unsupported');
          if (pointer(at + 16) !== null) fail('DObj descriptor unsupported, including gated DObj');
          if (pointer(at + 56) !== null) fail('matrix descriptor unsupported');
          if (pointer(at + 60) !== null) fail('RObj descriptor unsupported');
          const header = {sibling08: null, child10: null, flags14: (flags | 0x40) >>> 0} as SourceJObjScalarHeader;
          for (let i = 0; i < scalarKeys.length; i++) {
            const value = view.getFloat32(dataStart + at + 20 + i * 4, false);
            if (!Number.isFinite(value)) fail(`${scalarKeys[i]}: finite float32 required`);
            header[scalarKeys[i]!] = value;
          }
          const child = pointer(at + 8), next = parent === null ? null : pointer(at + 12);
          const plan = {at, parent, child, next, header}; plans.push(plan); byOffset.set(at, plan);
          if (next !== null) stack.push({at: next, parent, depth});
          if (child !== null) stack.push({at: child, parent: at, depth: depth + 1});
        }
        // Reverse preorder completes descendants before each parent's AddChild
        // contribution. The OR contributions commute across ordered siblings.
        for (let i = plans.length - 1; i >= 0; i--) {
          const p = plans[i]!;
          if (p.parent !== null) {
            const parent = byOffset.get(p.parent)!.header, f = p.header.flags14;
            parent.flags14 = (parent.flags14 | ((f | (f << 10)) & 0x70000000)) >>> 0;
          }
        }
        poisonCheck();
        const ids = new Map<number, symbol>(), headers = new Map<number, SourceJObjScalarHeader>();
        const bindings = new Map<number, SourceJObjAnimationBinding>(), seenIds = new Set<symbol>(), records = new Set<object>();
        for (const p of plans) {
          const initial = {...p.header};
          const binding: SourceJObjAnimationBinding = {parent0c: null, aobj7c: null, robj80: null, dobj18: null, classUpdate50: null};
          const id = invoke(factory, [initial, {...binding}]);
          if (typeof id !== 'symbol' || seenIds.has(id)) fail('factory must synchronously return a fresh owned symbol');
          seenIds.add(id);
          const h = invoke(getJoint, [id]), b = invoke(getBinding, [id]);
          for (const key of ['sibling08', 'child10', 'flags14', ...scalarKeys] as const) {
            if (!Object.is(writable(h, key), p.header[key])) fail(`owner header mismatch: ${key}`);
          }
          for (const key of bindingKeys) if (writable(b, key) !== null) fail(`owner binding mismatch: ${key}`);
          if (records.has(h as object) || records.has(b as object) || h === b) fail('owner records must be distinct');
          records.add(h as object); records.add(b as object);
          ids.set(p.at, id); headers.set(p.at, h as SourceJObjScalarHeader); bindings.set(p.at, b as SourceJObjAnimationBinding);
        }
        for (const p of plans) {
          // Re-resolve to reject adapters returning temporary/non-owned copies.
          if (invoke(getJoint, [ids.get(p.at)!]) !== headers.get(p.at) || invoke(getBinding, [ids.get(p.at)!]) !== bindings.get(p.at)) fail('unstable owned record');
          const h = headers.get(p.at)!, b = bindings.get(p.at)!;
          for (const key of ['sibling08', 'child10', 'flags14', ...scalarKeys] as const) {
            if (!Object.is(writable(h, key), p.header[key])) fail(`owner header changed during allocation: ${key}`);
          }
          for (const key of bindingKeys) if (writable(b, key) !== null) fail(`owner binding changed during allocation: ${key}`);
          h.child10 = p.child === null ? null : ids.get(p.child)!;
          h.sibling08 = p.next === null ? null : ids.get(p.next)!;
          b.parent0c = p.parent === null ? null : ids.get(p.parent)!;
        }
        // No adapter calls after this final own-data validation. Earlier calls
        // may have mutated an already-linked record; do not report a bad graph.
        for (const p of plans) {
          const h = headers.get(p.at)!, b = bindings.get(p.at)!;
          for (const key of ['flags14', ...scalarKeys] as const) {
            if (!Object.is(writable(h, key), p.header[key])) fail(`final owner header mismatch: ${key}`);
          }
          if (writable(h, 'child10') !== (p.child === null ? null : ids.get(p.child)) ||
              writable(h, 'sibling08') !== (p.next === null ? null : ids.get(p.next))) fail('final topology mismatch');
          for (const key of bindingKeys) {
            const expected = key === 'parent0c' && p.parent !== null ? ids.get(p.parent) : null;
            if (writable(b, key) !== expected) fail(`final owner binding mismatch: ${key}`);
          }
        }
        poisonCheck();
        return Object.freeze({root: ids.get(selected.offset)!, publicIndex: index, name: selected.name, dataOffset: selected.offset,
          joints: Object.freeze(plans.map(p => Object.freeze({dataOffset: p.at, joint: ids.get(p.at)!})))});
      } finally {busy = false;}
    },
  });
}
