/** Bounded decoded, untagged archive selection from actual 8004d548,
 * chunk_0006.c:2366–2411. This does not parse archives, strip pointer tags,
 * allocate wrappers, infer addresses, or activate production animation.
 * Explicit owned table cursors model cell displacement (including signed
 * selector2b from a shifted group base). 4096 cells is a host admission cap.
 * Tables are copied/sealed but their cells remain live. Only reached operands
 * are checked; read-only operands are legal. Completed stores survive refusal.
 * Adapters must return actual owned, synchronous non-proxy records. Methods
 * and receivers are captured; caught same-runtime reentry poisons the operation.
 */
import type {SourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import type {SourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import type {SourceArchiveJointSetupRuntime} from './archive-joint-setup.js';
export interface SourceAnimationArchiveBankSources {
  mapping: Pick<SourceActorJointMappingRuntime, 'getPartBinding'>;
  metadata: Pick<SourceAnimationSetupMetadataRuntime, 'getPartBinding'>;
  archives: Pick<SourceArchiveJointSetupRuntime, 'getPartBinding' | 'getDescriptor'>;
}
export interface SourceAnimationArchiveBankRuntime {
  getActualArchives(): SourceAnimationArchiveBankSources['archives'];
  getActualMetadata(): SourceAnimationArchiveBankSources['metadata'];
  getActualMapping(): SourceAnimationArchiveBankSources['mapping'];
  createPointerTable(entries: readonly (symbol | null)[]): symbol;
  pointerAt(root: symbol, index: number): symbol;
  getPointerTable(root: symbol): (symbol | null)[];
  resolveArchive(part: symbol): -1 | 0 | 1;
}
const genuineRuntimes = new WeakSet<object>();
export function isSourceAnimationArchiveBankRuntime(value: unknown): value is SourceAnimationArchiveBankRuntime {
  return value !== null && typeof value === 'object' && genuineRuntimes.has(value);
}
function fail(reason: string): never {throw Error(`[animation-archive-bank] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function pointer(value: unknown): symbol | null {
  if (value !== null && typeof value !== 'symbol') fail('decoded untagged symbol or null required'); return value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`); return value;
}
function method(table: unknown, key: string): (...args: never[]) => unknown {
  const value = own(table, key); if (typeof value !== 'function') fail(`${key}: own data-function required`); return value as (...args: never[]) => unknown;
}
export function createSourceAnimationArchiveBankRuntime(sources: SourceAnimationArchiveBankSources): SourceAnimationArchiveBankRuntime {
  const mapping = own(sources, 'mapping'), metadata = own(sources, 'metadata'), archives = own(sources, 'archives');
  const mappingGet = method(mapping, 'getPartBinding'), metadataGet = method(metadata, 'getPartBinding');
  const archiveGet = method(archives, 'getPartBinding'), descriptorGet = method(archives, 'getDescriptor');
  type Table = {cells: (symbol | null)[]; cursors: Map<number, symbol>; length: number};
  const cursors = new Map<symbol, {table: Table; index: number}>();
  let busy = false, poisoned = false;
  const enter = (): void => {if (busy) {poisoned = true; fail('same-runtime reentry is unsupported');} busy = true; poisoned = false;};
  const invoke = (table: unknown, fn: (...args: never[]) => unknown, args: unknown[]): unknown => {
    const result = Reflect.apply(fn, table, args);
    if (poisoned) fail('same-runtime reentry caught inside adapter');
    if (result instanceof Promise) fail('adapter must complete synchronously'); return result;
  };
  const cursor = (id: symbol | null) => {const value = id === null ? undefined : cursors.get(id); if (!value) fail('unknown/non-owned table cursor'); return value;};
  const at = (root: symbol, offset: number): symbol => {
    const entry = cursor(root), index = entry.index + integer(offset, -4096, 4096, 'cell displacement');
    integer(index, 0, entry.table.length - 1, 'table cursor');
    let id = entry.table.cursors.get(index);
    if (id === undefined) {id = Symbol('decoded archive table cursor'); entry.table.cursors.set(index, id); cursors.set(id, {table: entry.table, index});}
    return id;
  };
  const read = (root: symbol | null, displacement: number): symbol | null => {
    const entry = cursor(root), index = entry.index + displacement;
    integer(index, 0, entry.table.length - 1, 'reached table cell'); return pointer(own(entry.table.cells, String(index)));
  };
  const partMapping = (part: symbol) => invoke(mapping, mappingGet, [part]);
  const partArchive = (part: symbol) => invoke(archives, archiveGet, [part]);
  const store = (part: symbol, value: symbol | null): void => {
    const record = partArchive(part); own(record, 'descriptor04', true);
    (record as {descriptor04: symbol | null}).descriptor04 = value;
  };
  const loadArchive = (part: symbol) => pointer(own(partArchive(part), 'descriptor04'));
  const selector = (part: symbol, key: string): number => integer(own(invoke(metadata, metadataGet, [part]), key), 0, 255, key);
  const runtime: SourceAnimationArchiveBankRuntime = Object.freeze({
    getActualArchives() {return archives as SourceAnimationArchiveBankSources['archives'];},
    getActualMetadata() {return metadata as SourceAnimationArchiveBankSources['metadata'];},
    getActualMapping() {return mapping as SourceAnimationArchiveBankSources['mapping'];},
    createPointerTable(entries: readonly (symbol | null)[]): symbol {
      enter(); try {
        if (!Array.isArray(entries)) fail('decoded pointer array required');
        const length = integer(own(entries, 'length'), 0, 4096, 'pointer table length'), cells: (symbol | null)[] = [];
        for (let i = 0; i < length; i++) cells.push(pointer(own(entries, String(i))));
        const table: Table = {cells: Object.seal(cells), cursors: new Map(), length};
        const root = Symbol('decoded archive table root'); table.cursors.set(0, root); cursors.set(root, {table, index: 0}); return root;
      } finally {busy = false;}
    },
    pointerAt(root: symbol, index: number): symbol {enter(); try {return at(root, index);} finally {busy = false;}},
    getPointerTable(root: symbol): (symbol | null)[] {return cursor(root).table.cells;},
    resolveArchive(part: symbol): -1 | 0 | 1 {
      enter(); try {
        const bank = pointer(own(partMapping(part), 'descriptor00'));
        if (bank === null) return -1;
        let status: 0 | 1 = 0;
        // PPC loads selector2a and the selected group only once (4d57c–4d588).
        const group = read(bank, selector(part, 'selector2a') & 0x7f);
        if (group === null) {
          status = 1; store(part, read(read(bank, 0), 0));
        } else {
          const displacement = (selector(part, 'selector2b') << 24) >> 24;
          store(part, read(group, displacement));
          if (loadArchive(part) === null) {
            status = 1;
            const reloadedBank = pointer(own(partMapping(part), 'descriptor00'));
            store(part, read(read(reloadedBank, 0), 0));
          }
        }
        const selected = loadArchive(part);
        // Null is untagged zero and valid here; downstream setup owns its refusal.
        if (selected !== null) {
          const descriptor = invoke(archives, descriptorGet, [selected]);
          if (descriptor === null || typeof descriptor !== 'object') fail('actual owned archive wrapper required');
        }
        return status;
      } finally {busy = false;}
    },
  });
  genuineRuntimes.add(runtime); return runtime;
}
