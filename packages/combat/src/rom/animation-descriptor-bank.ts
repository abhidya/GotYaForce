/** Bounded byte-backed 8004d1f4, chunk_0006.c:2208–2227.
 * Actual live readiness/selector records are read at each reached operand, never
 * cloned into sidecar owners. defaultSelector582 holds raw unsigned byte bits
 * and is sign-extended only on the reached default branch. Inputs must be non-proxy own-data records; readonly
 * operands are supported. No arbitrary resolver callback or RAM alias emulation.
 * Signed BE16 displacements are relative to the selected bank/group pointer, not
 * the table entry. Bit7 chooses shared before any signed-char default substitution.
 * Index multiplication wraps modulo32; pointer coordinates do not wrap. Negative
 * or overflowing coordinates refuse. Owned canonical cursors can be outside the
 * backing until read. Copies are private and limited to 16MiB (a host bound).
 * No user getters/iterators are invoked by byte copying. Same-runtime reentry,
 * including caught reentry from a proxy trap, poisons the outer operation. Proxy
 * objects and modified platform intrinsics are outside the host contract. This
 * is offline synthetic-source coverage, not production asset or replay evidence.
 */
export interface SourceAnimationDescriptorBankRuntime {
  createBytes(bytes: Uint8Array): symbol;
  cursorAt(rootBase: symbol, offset: number): symbol;
  cursorOffset(rootBase: symbol, cursor: symbol): number;
  readByte(cursor: symbol, delta?: number): number;
  resolveDescriptor(readiness: {readonly family1d88: symbol | null; readonly shared1d8c: symbol | null},
    selectorSource: {readonly defaultSelector582: number}, group: number, action: number): symbol;
}
function fail(reason: string): never {throw Error(`[animation-descriptor-bank] ${reason}; offline lookup aborted`);}
function integer(value: unknown, min: number, max: number, label: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${label}: integer out of range`);
  return value;
}
export function createSourceAnimationDescriptorBankRuntime(): SourceAnimationDescriptorBankRuntime {
  type Backing = {bytes: Uint8Array; cursors: Map<number, symbol>};
  const roots = new Map<symbol, Backing>();
  const cursors = new Map<symbol, {backing: Backing; offset: number}>();
  let busy = false, poisoned = false;
  function guarded<T>(run: () => T): T {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); if (poisoned) fail('caught same-runtime reentry'); return result;}
    finally {busy = false;}
  }
  function own(record: object, key: string): unknown {
    if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
    const descriptor = Object.getOwnPropertyDescriptor(record, key);
    if (poisoned) fail('caught same-runtime reentry');
    if (!descriptor || !('value' in descriptor)) fail(`${key}: own data property required`);
    return descriptor.value;
  }
  function cursor(id: unknown) {
    const found = typeof id === 'symbol' ? cursors.get(id) : undefined;
    if (!found) fail('owned byte cursor required');
    return found;
  }
  function intern(backing: Backing, offset: number): symbol {
    integer(offset, 0, 0xffffffff, 'cursor coordinate');
    let id = backing.cursors.get(offset);
    if (id === undefined) {id = Symbol('animation descriptor byte cursor'); backing.cursors.set(offset, id); cursors.set(id, {backing, offset});}
    return id;
  }
  function add(id: unknown, delta: number): symbol {
    const found = cursor(id); return intern(found.backing, found.offset + delta);
  }
  function read(id: unknown, delta: number): number {
    const found = cursor(id), at = found.offset + delta;
    integer(at, 0, 0xffffffff, 'read coordinate');
    if (at >= found.backing.bytes.length) fail('byte read out of bounds');
    return found.backing.bytes[at]!;
  }
  function short(id: symbol, delta: number): number {
    const bits = read(id, delta) * 256 + read(id, delta + 1);
    return bits >= 0x8000 ? bits - 0x10000 : bits;
  }
  return Object.freeze({
    createBytes(bytes: Uint8Array): symbol {return guarded(() => {
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
      const root = intern(backing, 0); roots.set(root, backing); return root;
    });},
    cursorAt(rootBase: symbol, offset: number): symbol {return guarded(() => {
      const backing = roots.get(rootBase); if (!backing) fail('owned root byte base required');
      return intern(backing, offset);
    });},
    cursorOffset(rootBase: symbol, id: symbol): number {return guarded(() => {
      const found = cursor(id), backing = roots.get(rootBase);
      if (!backing || found.backing !== backing) fail('cursor does not belong to root byte base');
      return found.offset;
    });},
    readByte(id: symbol, delta = 0): number {return guarded(() => {
      integer(delta, -0xffffffff, 0xffffffff, 'read delta'); return read(id, delta);
    });},
    resolveDescriptor(readiness: {readonly family1d88: symbol | null; readonly shared1d8c: symbol | null},
      selectorSource: {readonly defaultSelector582: number}, group: number, action: number): symbol {return guarded(() => {
      integer(group, 0, 0xffffffff, 'group');
      let bank: symbol, index: number;
      if ((group & 0x80) === 0) {
        index = group === 0 ? (integer(own(selectorSource, 'defaultSelector582'), 0, 255, 'defaultSelector582') << 24) >> 24 : group;
        const selected = own(readiness, 'family1d88'); cursor(selected); bank = selected as symbol;
      } else {
        index = group & 0x7f;
        const selected = own(readiness, 'shared1d8c'); cursor(selected); bank = selected as symbol;
      }
      const groupBase = add(bank, short(bank, (index * 2) >>> 0));
      integer(action, -0x80000000, 0xffffffff, 'action');
      return add(groupBase, short(groupBase, (action * 2) >>> 0));
    });},
  });
}
