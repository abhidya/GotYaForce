/** Bounded byte-backed HSD public lookup, chunk_0072.c:3684–3723.
 * No archive hydration, relocation, RAM aliases or production asset provenance.
 * Bytewise NUL equality models strcmp results, not its optimized aligned-word
 * reads (chunk_0069.c:2586–2650), speculative reads or native fault ordering.
 * BE32 offsets use an explicit unsigned local-coordinate host convention: the
 * decompiler loads int, and retail pointer addition is 32-bit. We preserve the
 * table displacement modulo 32 bits, but refuse coordinate overflow rather than
 * inventing address wrap or treating high-bit offsets as negative displacement.
 * Bytes are immutable private copies; cursors may point outside backing until a
 * reached read. 16MiB copies, entry/string budgets are host bounds, not source.
 * Binding descriptors are copied/sealed without invoking accessors; malformed
 * values/accessors are rejected only when reached. Readonly fields are accepted.
 */
export interface SourceArchivePublicBinding {
  publicCount0c: number;
  data20: symbol | null;
  publicTable28: symbol | null;
  stringTable30: symbol | null;
}
export interface SourceArchivePublicRuntime {
  createBytes(bytes: Uint8Array): symbol;
  cursorAt(base: symbol, offset: number): symbol;
  cursorOffset(base: symbol, cursor: symbol): number;
  createArchive(initial: Readonly<SourceArchivePublicBinding>): symbol;
  getArchive(archive: symbol): SourceArchivePublicBinding;
  getPublicName(archive: symbol, index: number): symbol | null;
  getPublicAddress(archive: symbol, name: symbol | null): symbol | null;
}
function fail(reason: string): never {throw Error(`[archive-public] ${reason}; offline lookup aborted`);}
function uint(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) fail(`${where}: uint32 required`);
  return value;
}
function own(record: object, key: string): unknown {
  const descriptor = Object.getOwnPropertyDescriptor(record, key);
  if (!descriptor || !('value' in descriptor)) fail(`${key}: own data property required`);
  return descriptor.value;
}
export function createSourceArchivePublicRuntime({maxEntries = 4096, maxStringBytes = 65536}: {
  maxEntries?: number; maxStringBytes?: number;
} = {}): SourceArchivePublicRuntime {
  for (const [key, value] of [['maxEntries', maxEntries], ['maxStringBytes', maxStringBytes]] as const) {
    if (!Number.isSafeInteger(value) || value <= 0) fail(`${key}: positive safe integer required`);
  }
  type Backing = {bytes: Uint8Array; cursors: Map<number, symbol>};
  const bases = new Map<symbol, Backing>();
  const cursors = new Map<symbol, {backing: Backing; offset: number}>();
  const archives = new Map<symbol, SourceArchivePublicBinding>();
  let busy = false, poisoned = false;
  function guarded<T>(run: () => T): T {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); if (poisoned) fail('caught same-runtime reentry'); return result;}
    finally {busy = false;}
  }
  function cursor(id: unknown) {
    const found = typeof id === 'symbol' ? cursors.get(id) : undefined;
    if (!found) fail('owned byte cursor required');
    return found;
  }
  function intern(backing: Backing, offset: number): symbol {
    uint(offset, 'cursor offset');
    let id = backing.cursors.get(offset);
    if (id === undefined) {id = Symbol('archive byte cursor'); backing.cursors.set(offset, id); cursors.set(id, {backing, offset});}
    return id;
  }
  function add(base: unknown, offset: number): symbol {
    const found = cursor(base); return intern(found.backing, found.offset + offset);
  }
  function read(base: unknown, delta: number): number {
    const found = cursor(base), at = found.offset + delta;
    if (at > 0xffffffff || at >= found.backing.bytes.length) fail('byte read out of bounds');
    return found.backing.bytes[at]!;
  }
  function word(base: unknown, delta: number): number {
    return read(base, delta) * 0x1000000 + read(base, delta + 1) * 0x10000 + read(base, delta + 2) * 256 + read(base, delta + 3);
  }
  function archive(id: symbol): SourceArchivePublicBinding {
    const found = archives.get(id); if (!found) fail('owned archive required'); return found;
  }
  function count(binding: SourceArchivePublicBinding): number {return uint(own(binding, 'publicCount0c'), 'publicCount0c');}
  function nameAt(binding: SourceArchivePublicBinding, displacement: number): symbol {
    const offset = word(own(binding, 'publicTable28'), displacement + 4);
    return add(own(binding, 'stringTable30'), offset);
  }
  function equal(left: symbol, right: symbol | null): boolean {
    for (let i = 0; i < maxStringBytes; i++) {
      const a = read(left, i), b = read(right, i);
      if (a !== b) return false;
      if (a === 0) return true;
    }
    fail('maxStringBytes host budget exhausted');
  }
  return {
    createBytes(bytes) {return guarded(() => {
      const typed = Object.getPrototypeOf(Uint8Array.prototype) as object;
      const tag = Reflect.apply(Object.getOwnPropertyDescriptor(typed, Symbol.toStringTag)!.get!, bytes, []);
      if (tag !== 'Uint8Array') fail('non-shared Uint8Array required');
      const buffer = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'buffer')!.get!, bytes, []);
      try {Reflect.apply(Object.getOwnPropertyDescriptor(ArrayBuffer.prototype, 'byteLength')!.get!, buffer, []);}
      catch {fail('non-shared Uint8Array required');}
      const length = Reflect.apply(Object.getOwnPropertyDescriptor(typed, 'length')!.get!, bytes, []) as number;
      if (length > 16 * 1024 * 1024) fail('16MiB host copy cap exceeded');
      const copy = new Uint8Array(length); Reflect.apply(Uint8Array.prototype.set, copy, [bytes]);
      const backing: Backing = {bytes: copy, cursors: new Map()};
      const base = intern(backing, 0); bases.set(base, backing); return base;
    });},
    cursorAt(base, offset) {return guarded(() => {
      const backing = bases.get(base); if (!backing) fail('owned byte base required'); return intern(backing, offset);
    });},
    cursorOffset(base, id) {const backing = bases.get(base), found = cursor(id);
      if (!backing || found.backing !== backing) fail('cursor does not belong to byte base'); return found.offset;},
    createArchive(initial) {return guarded(() => {
      if (initial === null || typeof initial !== 'object') fail('archive data record required');
      const result = Object.create(null) as SourceArchivePublicBinding;
      for (const key of ['publicCount0c', 'data20', 'publicTable28', 'stringTable30']) {
        const descriptor = Object.getOwnPropertyDescriptor(initial, key);
        if (poisoned) fail('caught same-runtime reentry');
        if (descriptor) Object.defineProperty(result, key, descriptor);
      }
      const id = Symbol('archive public binding'); archives.set(id, Object.seal(result)); return id;
    });},
    getArchive: archive,
    getPublicName(id, index) {return guarded(() => {
      // uint32 input convention admits 0x80000000..ffffffff, interpreted signed.
      // Also accept natural signed int32 callers without JS coercion surprises.
      if (typeof index !== 'number' || !Number.isInteger(index) || index < -0x80000000 || index > 0xffffffff) fail('index: int32/uint32 required');
      if (index < 0 || index >= 0x80000000) return null;
      const binding = archive(id); if (index >= count(binding)) return null;
      return nameAt(binding, (index * 8) >>> 0);
    });},
    getPublicAddress(id, name) {return guarded(() => {
      const binding = archive(id);
      for (let index = 0; ; index++) {
        if (index >= count(binding)) return null;
        if (index >= maxEntries) fail('maxEntries host budget exhausted');
        const displacement = (index * 8) >>> 0;
        if (equal(nameAt(binding, displacement), name)) {
          const offset = word(own(binding, 'publicTable28'), displacement);
          return add(own(binding, 'data20'), offset);
        }
      }
    });},
  };
}
