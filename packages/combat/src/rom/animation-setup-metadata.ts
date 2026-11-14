/** Shared metadata stores from 8004d244, chunk_0006.c:2230–2362.
 * Offline prerequisite only: no ready result, stream start, mapping, attachment,
 * animation or live dispatch. Existing records retain ownership of scale32,
 * bank33, mirror30, rewind26 and loop2c. Only previously unmodeled bytes get
 * sidecars. Source actor+582 remains exclusively stream-start-owned.
 *
 * Operands are read lazily and need not be writable. Stores validate their own
 * destinations without validating the overwritten value. Completed prefixes
 * survive failures. Two bank indexing is a host bound, not source clamping.
 * Indexed fallback ordering follows the archived PPC instruction audit:
 * snapshot bank33, read descriptor4b0, sign/scale bank, load fallback, store.
 * Adapter methods and receivers are captured. Adapters must return stable actual
 * owned non-proxy data synchronously, never defer work. Reentry poisons the call.
 */
import type {SourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
import type {SourceActorJointMappingRuntime, SourceActorJointMappingHeader, SourceActorJointPartBinding, SourceActorJointLayout} from './actor-joint-mapping.js';
import type {SourceJointAnimationFeedbackRuntime, SourceJointAnimationPart} from './joint-animation-feedback.js';
import type {SourceAttachedJointSetupRuntime, SourceAttachedJointSetupBinding} from './attached-joint-setup.js';

export interface SourceAnimationSetupMetadataPart {selector2a: number; selector2b: number; auxiliary37: number}
export interface SourceAnimationSetupMetadataActor {
  byte1d74: number; byte1d75: number; byte1d76: number; byte1d77: number;
  byte1d94: number; byte1d95: number; byte1d98: number; byte1d99: number; byte1d9b: number;
}
export interface SourceAnimationSetupDescriptorDefaults {bytebe: number; bytebf: number}
export interface SourceAnimationSetupMetadataSources {
  descriptors: Pick<SourceAnimationDescriptorBankRuntime, 'readByte'>;
  actors: Pick<SourceActorJointMappingRuntime, 'getActor' | 'getDescriptor' | 'getPartBinding' | 'getLayout'>;
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getPart'>;
  attached: Pick<SourceAttachedJointSetupRuntime, 'getPartBinding'>;
}
export interface SourceAnimationSetupMetadataRuntime {
  bindActor(identity: symbol, initial: SourceAnimationSetupMetadataActor): void;
  getActorBinding(identity: symbol): SourceAnimationSetupMetadataActor;
  bindPart(identity: symbol, initial: SourceAnimationSetupMetadataPart): void;
  getPartBinding(identity: symbol): SourceAnimationSetupMetadataPart;
  bindDescriptorDefaults(identity: symbol, initial: SourceAnimationSetupDescriptorDefaults): void;
  getDescriptorDefaults(identity: symbol): SourceAnimationSetupDescriptorDefaults;
  applyMetadata(actor: symbol, part: symbol, channel: number, cursor: symbol): void;
}
function fail(reason: string): never {
  throw Error(`[animation-setup-metadata] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, key: string): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${key}: expected integer ${min}..${max}`);
}
function byte(record: unknown, key: string): number {const value = own(record, key); integer(value, 0, 255, key); return value;}
function write(record: object, key: string, value: number): void {own(record, key, true); (record as Record<string, unknown>)[key] = value;}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const value = own(table, key); if (typeof value !== 'function') fail(`${key}: own data-function required`);
  return value as (...args: never[]) => unknown;
}
function copy<T extends object>(initial: T, keys: readonly (keyof T & string)[]): T {
  const result = {} as T;
  for (const key of keys) result[key] = byte(initial, key) as T[typeof key];
  return Object.seal(result);
}
export function createSourceAnimationSetupMetadataRuntime(sources: SourceAnimationSetupMetadataSources): SourceAnimationSetupMetadataRuntime {
  const descriptors = own(sources, 'descriptors'), actors = own(sources, 'actors');
  const feedback = own(sources, 'feedback'), attached = own(sources, 'attached');
  const readByte = method(descriptors, 'readByte'), getActor = method(actors, 'getActor');
  const getDescriptor = method(actors, 'getDescriptor'), getLayout = method(actors, 'getLayout');
  const getMapping = method(actors, 'getPartBinding'), getPart = method(feedback, 'getPart'), getAttached = method(attached, 'getPartBinding');
  const actorBindings = new Map<symbol, {actual: SourceActorJointMappingHeader; layout: SourceActorJointLayout; bytes: SourceAnimationSetupMetadataActor}>();
  const partBindings = new Map<symbol, {mapping: SourceActorJointPartBinding; actual: SourceJointAnimationPart; setup: SourceAttachedJointSetupBinding; bytes: SourceAnimationSetupMetadataPart}>();
  const defaults = new Map<symbol, SourceAnimationSetupDescriptorDefaults>();
  let busy = false, reentered = false;
  const enter = (): void => {if (busy) {reentered = true; fail('same-runtime reentry is unsupported');} busy = true; reentered = false;};
  const resolve = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, table, args);
    if (reentered) fail('same-runtime reentry was caught inside an adapter');
    // Every dependency here returns either a byte or a concrete owned record.
    if (result instanceof Promise) fail('adapter must complete synchronously');
    return result;
  };
  const partEntry = (id: symbol) => {const value = partBindings.get(id); if (!value) fail('unknown/non-owned metadata part'); return value;};
  const actorEntry = (id: symbol) => {const value = actorBindings.get(id); if (!value) fail('unknown/non-owned metadata actor'); return value;};
  const getDescriptorDefaults = (id: symbol) => {const value = defaults.get(id); if (!value) fail('unknown/non-owned descriptor defaults'); return value;};
  const actorForPart = (id: symbol, part: symbol) => {
    const entry = actorEntry(id);
    if (!entry.layout.parts.some(row => row.includes(part))) fail('part does not belong to actor layout');
    return entry;
  };
  return Object.freeze({
    bindActor(id: symbol, initial: SourceAnimationSetupMetadataActor): void {
      enter(); try {
        if (actorBindings.has(id)) fail('actor already bound');
        const actual = resolve(actors, getActor, [id]) as SourceActorJointMappingHeader;
        const layout = resolve(actors, getLayout, [id]) as SourceActorJointLayout;
        const bytes = copy(initial, ['byte1d74', 'byte1d75', 'byte1d76', 'byte1d77', 'byte1d94', 'byte1d95', 'byte1d98', 'byte1d99', 'byte1d9b']);
        actorBindings.set(id, {actual, layout, bytes});
      } finally {busy = false;}
    },
    getActorBinding(id: symbol) {return actorEntry(id).bytes;},
    bindPart(id: symbol, initial: SourceAnimationSetupMetadataPart): void {
      enter(); try {
        if (partBindings.has(id)) fail('part already bound');
        const mapping = resolve(actors, getMapping, [id]) as SourceActorJointPartBinding;
        const actual = resolve(feedback, getPart, [id]) as SourceJointAnimationPart;
        const setup = resolve(attached, getAttached, [id]) as SourceAttachedJointSetupBinding;
        const bytes = copy(initial, ['selector2a', 'selector2b', 'auxiliary37']);
        partBindings.set(id, {mapping, actual, setup, bytes});
      } finally {busy = false;}
    },
    getPartBinding(id: symbol) {return partEntry(id).bytes;},
    bindDescriptorDefaults(id: symbol, initial: SourceAnimationSetupDescriptorDefaults): void {
      enter(); try {
        if (defaults.has(id)) fail('descriptor defaults already bound');
        resolve(actors, getDescriptor, [id]);
        defaults.set(id, copy(initial, ['bytebe', 'bytebf']));
      } finally {busy = false;}
    },
    getDescriptorDefaults,
    applyMetadata(actorId: symbol, partId: symbol, channel: number, cursor: symbol): void {
      enter(); try {
        integer(channel, -0x80000000, 0x7fffffff, 'channel');
        const part = partEntry(partId);
        const read = (offset: number): number => {
          const value = resolve(descriptors, readByte, [cursor, offset]); integer(value, 0, 255, `metadata[${offset}]`); return value;
        };
        write(part.mapping, 'scaleIndex32', read(0));
        if (channel < 0 || channel > 3) return;
        const base = 4 + channel * 8;
        write(part.bytes, 'selector2a', read(base));
        write(part.bytes, 'selector2b', read(base + 1));
        write(part.setup, 'rewind26', read(base + 3));
        write(part.bytes, 'auxiliary37', read(base + 4));
        const flags = read(base + 2) & 3;
        if (flags === 3) write(part.actual, 'mirror30', byte(part.actual, 'mirror30') ^ 1);
        else if (flags === 1) write(part.actual, 'mirror30', 0);
        else if (flags === 2) write(part.actual, 'mirror30', 1);
        write(part.setup, 'loop2c', (read(base + 2) & 4) !== 0 ? 1 : 0);
        if (channel === 1) {
          const actor = actorForPart(actorId, partId).bytes;
          write(actor, 'byte1d98', read(0x11));
          write(actor, 'byte1d99', read(0x12));
          write(actor, 'byte1d9b', read(0x13));
        } else if (channel === 0) {
          const actor = actorForPart(actorId, partId);
          const bank = (raw: number): number => {
            const value = (raw << 24) >> 24;
            integer(value, 0, 1, 'jointBank33 (two-bank host bound)'); return value;
          };
          for (const [offset, fallback, keys] of [[9, 'bytebe', ['byte1d74', 'byte1d76']], [10, 'bytebf', ['byte1d75', 'byte1d77']]] as const) {
            let value: number, targetBank: number;
            const metadata = read(offset);
            if (((metadata << 24) >> 24) < 0) {
              const rawBank = byte(part.mapping, 'jointBank33');
              const descriptor = own(actor.actual, 'descriptor4b0');
              targetBank = bank(rawBank);
              if (typeof descriptor !== 'symbol') fail('fallback requires non-null owned descriptor4b0');
              resolve(actors, getDescriptor, [descriptor]);
              value = byte(getDescriptorDefaults(descriptor), fallback);
            } else {
              // PPC retains the metadata byte across its sign test, with no reread.
              value = metadata; targetBank = bank(byte(part.mapping, 'jointBank33'));
            }
            write(actor.bytes, keys[targetBank]!, value);
          }
          if (((byte(part.mapping, 'jointBank33') << 24) >> 24) !== 0) return;
          write(actor.bytes, 'byte1d94', byte(actor.bytes, 'byte1d74'));
          write(actor.bytes, 'byte1d95', byte(actor.bytes, 'byte1d75'));
        }
      } finally {busy = false;}
    },
  });
}
