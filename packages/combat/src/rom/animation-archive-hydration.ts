/** Bounded bare HSD DAT -> existing animation descriptor owners, offline only.
 * Header/table geometry and relative pointers: chunk_0072.c:3637–3669;
 * public lookup: :3684–3723. AnimJoint: chunk_0071.c:4000–4030,4167–4174;
 * AObjDesc: chunk_0070.c:2691–2713; FObjDesc: chunk_0071.c:1328–1335.
 *
 * Callers explicitly identify public indices containing single-joint AnimJoint
 * roots. No scene-root inference, tagged4d548 allocation/cache, retail RAM
 * relocation, native fault order, live Battle ownership or asset provenance is
 * claimed. Child/next, RObj, external tables and AObj joint references refuse.
 * Unselected publics remain in the real public table but are not hydrated.
 * Duplicate names retain first-match lookup; a selected name's first target
 * must also be explicitly selected (aliases by target need no extra selection).
 *
 * This is a host preflight/import contract, NOT source ArchiveParse effect order.
 * All bytes, geometry, reachable descriptor graph, relocation classifications,
 * cycle/type/overlap checks and budgets validate before any owner factory runs.
 * Unsupported packed opcodes/formats and finite start values outside the loader's
 * signed16-integral domain are left to the actual consuming owners. Packed bytes
 * are never decoded/re-encoded here. Header reserved words and FObj pad0f are
 * uninterpreted unless a relocation would change a consumed descriptor scalar.
 *
 * Relocated raw zero means data+0. An unrelocated zero pointer is null, while
 * an unrelocated nonzero pointer refuses. Public offset zero is always data+0.
 * Descriptor aliases at the same offset share actual owner identities. Equal
 * packed-data offsets share one real createData base, sized to the greatest
 * declared length; each FObj retains its own length. Different start offsets
 * (even overlapping spans) use separately copied immutable streams, bounded by
 * an aggregate byte budget: physical RAM aliasing is NOT modeled. An interior
 * fobjData.cursorAt is not a valid stream base and is deliberately never used.
 *
 * The immutable private input copy, 16MiB ceiling, selected leaf-root domain,
 * aligned/nonoverlapping descriptor extents, finite scalars, bounds/budgets,
 * stable non-proxy own-data adapters, captured receivers, synchronous owned
 * results and caught-reentry poison are host limits. Source owner mutations or
 * allocations already completed survive an adapter failure; no rollback exists.
 */
import type {SourceArchivePublicRuntime} from './archive-public.js';
import type {SourceFObjData} from './fobj-data.js';
import type {SourceFObjDescriptorRuntime} from './fobj-descriptor.js';
import type {SourceAllocatedAObjDescriptorRuntime} from './allocated-aobj-descriptor.js';
import type {SourceJObjAddAnimationRuntime} from './jobj-add-animation.js';
import type {SourceArchiveJointSetupRuntime} from './archive-joint-setup.js';

export interface SourceAnimationArchiveHydrationSources {
  archives: Pick<SourceArchivePublicRuntime, 'createBytes' | 'cursorAt' | 'createArchive'>;
  fobjData: Pick<SourceFObjData, 'createData'>;
  fobjs: Pick<SourceFObjDescriptorRuntime, 'createDescriptor'>;
  aobjs: Pick<SourceAllocatedAObjDescriptorRuntime, 'createDescriptor'>;
  joints: Pick<SourceJObjAddAnimationRuntime, 'createDescriptor'>;
  setup: Pick<SourceArchiveJointSetupRuntime, 'createDescriptor' | 'bindAddress'>;
}
export interface SourceAnimationArchiveHydrationLimits {
  maxArchiveBytes?: number;
  maxRelocations?: number;
  maxPublics?: number;
  maxDescriptors?: number;
  maxStringBytes?: number;
  maxPackedBytes?: number;
}
export interface SourceHydratedAnimationArchive {
  readonly archive: symbol;
  readonly setupDescriptor: symbol;
  readonly byteBase: symbol;
  /** Data-relative original address and actual descriptor identity. Names use
   * byte-preserving Latin-1 code units, not guessed Unicode decoding. */
  readonly roots: readonly Readonly<{publicIndex: number; name: string; dataOffset: number; address: symbol; descriptor: symbol}>[];
  readonly aobjDescriptors: readonly Readonly<{dataOffset: number; descriptor: symbol}>[];
  readonly fobjDescriptors: readonly Readonly<{dataOffset: number; descriptor: symbol; packedDataOffset: number | null; length: number}>[];
  readonly packedData: readonly Readonly<{dataOffset: number; data: symbol; length: number}>[];
}
export interface SourceAnimationArchiveHydrationRuntime {
  hydrateAnimationArchive(bytes: Uint8Array, animJointPublicIndices: readonly number[]): SourceHydratedAnimationArchive;
}
const CAP = 16 * 1024 * 1024;
function fail(reason: string): never {throw Error(`[animation-archive-hydration] ${reason}; offline import aborted, completed owner effects are not rolled back`);}
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

export function createSourceAnimationArchiveHydrationRuntime(
  sources: SourceAnimationArchiveHydrationSources, limits: SourceAnimationArchiveHydrationLimits = {},
): SourceAnimationArchiveHydrationRuntime {
  const budget = (key: keyof SourceAnimationArchiveHydrationLimits, fallback: number, ceiling: number): number => {
    const p = Object.getOwnPropertyDescriptor(limits, key);
    const n = p === undefined ? fallback : uint(own(limits, key), key);
    if (n < 1 || n > ceiling) fail(`${key}: expected 1..${ceiling}`);
    return n;
  };
  const maxArchiveBytes = budget('maxArchiveBytes', CAP, CAP), maxRelocations = budget('maxRelocations', 65536, CAP / 4);
  const maxPublics = budget('maxPublics', 4096, CAP / 8), maxDescriptors = budget('maxDescriptors', 4096, CAP / 16);
  const maxStringBytes = budget('maxStringBytes', 65536, CAP), maxPackedBytes = budget('maxPackedBytes', CAP, CAP);
  const archives = own(sources, 'archives'), fobjData = own(sources, 'fobjData'), fobjs = own(sources, 'fobjs');
  const aobjs = own(sources, 'aobjs'), joints = own(sources, 'joints'), setup = own(sources, 'setup');
  const bytesFactory = method(archives, 'createBytes'), cursorFactory = method(archives, 'cursorAt'), archiveFactory = method(archives, 'createArchive');
  const dataFactory = method(fobjData, 'createData'), fobjFactory = method(fobjs, 'createDescriptor');
  const aobjFactory = method(aobjs, 'createDescriptor'), jointFactory = method(joints, 'createDescriptor');
  const setupFactory = method(setup, 'createDescriptor'), bindAddress = method(setup, 'bindAddress');
  let busy = false, poisoned = false;
  const poisonCheck = (): void => {if (poisoned) fail('same-runtime reentry caught inside adapter/input');};
  const invoke = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, table, args); poisonCheck(); return result;
  };
  const symbolCall = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): symbol => {
    const result = invoke(table, fn, args);
    if (typeof result !== 'symbol') fail('factory must synchronously return an actual owned symbol');
    return result;
  };
  return Object.freeze({
    hydrateAnimationArchive(input: Uint8Array, indices: readonly number[]): SourceHydratedAnimationArchive {
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
        const names = new Map<number, string>(), firstNames = new Map<string, number>();
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
          if (!firstNames.has(name)) firstNames.set(name, offset);
        }
        if (!Array.isArray(indices)) fail('explicit AnimJoint public-index array required');
        const selectionCount = uint(own(indices, 'length'), 'selected public count'); poisonCheck();
        if (selectionCount === 0 || selectionCount > maxPublics) fail('selected public count outside host bound');
        const selected: number[] = [], selectedIndices = new Set<number>(), selectedOffsets = new Set<number>();
        for (let i = 0; i < selectionCount; i++) {
          const index = uint(own(indices, String(i)), 'selected public index'); poisonCheck();
          if (index >= publicCount) fail('selected public index out of bounds');
          if (selectedIndices.has(index)) fail('duplicate selected public index');
          selected.push(index); selectedIndices.add(index); selectedOffsets.add(publics[index]!.offset);
        }
        for (const index of selected) {
          if (!selectedOffsets.has(firstNames.get(publics[index]!.name)!)) fail('first-match public target must also be explicitly selected');
        }
        type Kind = 'AnimJoint' | 'AObj' | 'FObj';
        const kinds = new Map<number, Kind>(), occupied = new Map<number, number>();
        const claim = (at: number, kind: Kind, size: number, pointerFields: readonly number[]): boolean => {
          range(at, size, kind);
          if (at % 4 !== 0) fail(`${kind}: unaligned descriptor unsupported`);
          const old = kinds.get(at);
          if (old !== undefined) {if (old !== kind) fail('descriptor address type conflict'); return false;}
          if (kinds.size >= maxDescriptors) fail('descriptor budget exceeded');
          for (let delta = 0; delta < size; delta += 4) {
            if (occupied.has(at + delta)) fail('overlapping descriptor extents unsupported');
            if (relocations.has(at + delta) && !pointerFields.includes(delta)) fail('relocation on descriptor scalar/padding unsupported');
          }
          kinds.set(at, kind);
          for (let delta = 0; delta < size; delta += 4) occupied.set(at + delta, at);
          return true;
        };
        const finite = (at: number, field: string): number => {
          const value = view.getFloat32(dataStart + at, false);
          if (!Number.isFinite(value)) fail(`${field}: finite float32 required`);
          return value;
        };
        const anims = new Map<number, {aobj: number | null; flags: number}>();
        const aobjPlans = new Map<number, {flags: number; end: number; fobj: number | null}>();
        const fobjPlans = new Map<number, {next: number | null; length: number; start: number; track: number; format0d: number; format0e: number; data: number | null}>();
        const packedLengths = new Map<number, number>();
        // Parse each chain iteratively. Completed shared suffixes are safe aliases;
        // a revisit within the current unfinished chain is a host cycle refusal.
        const parseFobjs = (head: number | null): void => {
          const visiting = new Set<number>(); let at = head;
          while (at !== null) {
            if (visiting.has(at)) fail('FObj descriptor cycle unsupported');
            if (fobjPlans.has(at)) break;
            visiting.add(at); claim(at, 'FObj', 0x14, [0, 0x10]);
            const next = pointer(at), length = word(dataStart + at + 4), start = finite(at + 8, 'FObj start08');
            const data = pointer(at + 0x10);
            if (data === null) {if (length !== 0) fail('nonempty FObj has null packed data');}
            else {range(data, length, 'packed data'); packedLengths.set(data, Math.max(packedLengths.get(data) ?? 0, length));}
            fobjPlans.set(at, {next, length, start, track: bytes[dataStart + at + 0xc]!,
              format0d: bytes[dataStart + at + 0xd]!, format0e: bytes[dataStart + at + 0xe]!, data});
            at = next;
          }
        };
        for (const index of selected) {
          const at = publics[index]!.offset;
          if (!claim(at, 'AnimJoint', 0x14, [0, 4, 8, 12])) continue;
          if (pointer(at) !== null || pointer(at + 4) !== null) fail('AnimJoint child/next graph unsupported by single-joint import');
          if (pointer(at + 12) !== null) fail('AnimJoint RObj animation unsupported');
          const aobj = pointer(at + 8); anims.set(at, {aobj, flags: word(dataStart + at + 16)});
          if (aobj !== null && claim(aobj, 'AObj', 0x10, [8, 12])) {
            if (pointer(aobj + 12) !== null) fail('AObj joint reference unsupported');
            const fobj = pointer(aobj + 8);
            aobjPlans.set(aobj, {flags: word(dataStart + aobj), end: finite(aobj + 4, 'AObj end04'), fobj});
            parseFobjs(fobj);
          }
        }
        let packedBytes = 0;
        const occupiedWords = [...occupied.keys()].sort((a, b) => a - b), relocWords = [...relocations].sort((a, b) => a - b);
        const overlapsWord = (words: readonly number[], at: number, length: number): boolean => {
          if (length === 0) return false;
          // Lower bound for first word whose end follows this span's start.
          let low = 0, high = words.length;
          while (low < high) {const mid = Math.floor((low + high) / 2); if (words[mid]! + 4 <= at) low = mid + 1; else high = mid;}
          return low < words.length && words[low]! < at + length;
        };
        for (const [at, length] of packedLengths) {
          packedBytes += length;
          if (packedBytes > maxPackedBytes) fail('aggregate packed byte budget exceeded');
          if (overlapsWord(occupiedWords, at, length)) fail('packed data overlaps descriptor extent');
          if (overlapsWord(relocWords, at, length)) fail('relocation overlaps packed data');
        }
        poisonCheck();
        // All preflight ends here. These are real owner calls, not simulated
        // source allocation/relocation effects. A later adapter failure is partial.
        const byteBase = symbolCall(archives, bytesFactory, [bytes.slice()]);
        const cursor = (offset: number): symbol => symbolCall(archives, cursorFactory, [byteBase, offset]);
        const archive = symbolCall(archives, archiveFactory, [{publicCount0c: publicCount,
          data20: dataSize === 0 ? null : cursor(dataStart), publicTable28: publicCount === 0 ? null : cursor(publicStart),
          stringTable30: stringStart < bytes.length ? cursor(stringStart) : null}]);
        const dataIds = new Map<number, symbol>(), fobjIds = new Map<number, symbol>(), aobjIds = new Map<number, symbol>(), animIds = new Map<number, symbol>();
        const packedData: {dataOffset: number; data: symbol; length: number}[] = [];
        for (const [at, length] of packedLengths) {
          // Pass an owned copy, not a writable view over our private archive.
          const data = symbolCall(fobjData, dataFactory, [bytes.slice(dataStart + at, dataStart + at + length)]);
          dataIds.set(at, data); packedData.push(Object.freeze({dataOffset: at, data, length}));
        }
        for (const start of fobjPlans.keys()) {
          const pending: number[] = []; let at: number | null = start;
          while (at !== null && !fobjIds.has(at)) {pending.push(at); at = fobjPlans.get(at)!.next;}
          for (let i = pending.length - 1; i >= 0; i--) {
            const offset = pending[i]!, plan = fobjPlans.get(offset)!;
            const descriptor = symbolCall(fobjs, fobjFactory, [{next00: plan.next === null ? null : fobjIds.get(plan.next)!,
              length04: plan.length, start08: plan.start, track0c: plan.track, format0d: plan.format0d,
              format0e: plan.format0e, data10: plan.data === null ? null : dataIds.get(plan.data)!}]);
            fobjIds.set(offset, descriptor);
          }
        }
        for (const [at, plan] of aobjPlans) aobjIds.set(at, symbolCall(aobjs, aobjFactory, [{flags00: plan.flags, end04: plan.end,
          fobj08: plan.fobj === null ? null : fobjIds.get(plan.fobj)!, joint0c: null}]));
        for (const [at, plan] of anims) animIds.set(at, symbolCall(joints, jointFactory, [{aobj08: plan.aobj === null ? null : aobjIds.get(plan.aobj)!, robj0c: null, flags10: plan.flags}]));
        for (const [at, descriptor] of animIds) {
          if (invoke(setup, bindAddress, [byteBase, cursor(dataStart + at), descriptor]) !== undefined) fail('bindAddress must synchronously return void');
        }
        const setupDescriptor = symbolCall(setup, setupFactory, [{archive0c: archive}]);
        const roots = selected.map(index => {const p = publics[index]!;
          return Object.freeze({publicIndex: index, name: p.name, dataOffset: p.offset, address: cursor(dataStart + p.offset), descriptor: animIds.get(p.offset)!});});
        const aobjDescriptors = [...aobjIds].map(([dataOffset, descriptor]) => Object.freeze({dataOffset, descriptor}));
        const fobjDescriptors = [...fobjIds].map(([dataOffset, descriptor]) => {const p = fobjPlans.get(dataOffset)!;
          return Object.freeze({dataOffset, descriptor, packedDataOffset: p.data, length: p.length});});
        return Object.freeze({archive, setupDescriptor, byteBase, roots: Object.freeze(roots), aobjDescriptors: Object.freeze(aobjDescriptors),
          fobjDescriptors: Object.freeze(fobjDescriptors), packedData: Object.freeze(packedData)});
      } finally {busy = false;}
    },
  });
}
