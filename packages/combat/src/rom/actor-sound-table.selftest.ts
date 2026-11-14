import {createSourceActorSoundTable, isSourceActorSoundTable, readSourceActorSoundTableByte,
  type SourceActorSoundByteWindow, type SourceActorSoundTableLimits} from './actor-sound-table.js';
function check(ok: boolean, label: string): void {if (!ok) throw Error(`[actor-sound-table-test] ${label}`);}
function rejects(run: () => unknown, part: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(part), `${part}: ${error}`);
}
export function runActorSoundTableSelfTests(): void {
  const bytes = new Uint8Array([99, 17, 0, 254, 88]), window = {offset: 16, bytes: bytes.subarray(1, 4)};
  const input = [window, {offset: 2, bytes: new Uint8Array([7])}, {offset: 19, bytes: new Uint8Array([255])}];
  const table = createSourceActorSoundTable(input);
  check(isSourceActorSoundTable(table) && Object.isFrozen(table), 'genuine frozen opaque table');
  check(Reflect.ownKeys(table).join(',') === 'readByte', 'no public backing or duplicate source pointer/scalars');
  check(table.readByte(2) === 7 && table.readByte(16) === 17 && table.readByte(17) === 0 && table.readByte(19) === 255,
    'unsorted windows, explicit zero, offset view and adjacency preserve only supplied bytes');
  check(readSourceActorSoundTableByte(table, 18) === 254, 'helper reads genuine owner');
  bytes.fill(0); window.offset = 0; window.bytes = new Uint8Array([1]); input.length = 0;
  check(table.readByte(16) === 17 && table.readByte(18) === 254, 'input arrays, records and bytes are detached from private copies');
  for (const offset of [0, 1, 3, 15, 20, 0xffffffff]) rejects(() => table.readByte(offset), `byte${offset}: uncovered`);
  for (const bad of [-1, 1.5, NaN, Infinity, 0x100000000]) rejects(() => table.readByte(bad), 'uint32');
  check(table.readByte(16) === 17, 'refused read does not corrupt owner');
  const empty = createSourceActorSoundTable([]);
  rejects(() => empty.readByte(0), 'uncovered');
  const highest = createSourceActorSoundTable([{offset: 0xffffffff, bytes: new Uint8Array([13])}]);
  check(highest.readByte(0xffffffff) === 13, 'last uint32 coordinate allowed without padding');
  rejects(() => highest.readByte(0), 'uncovered');

  const fake = {...table}, inherited = Object.create(table) as object;
  for (const value of [null, undefined, {}, fake, inherited, new Proxy(table, {}), Promise.resolve(table),
    {readByte() {throw Error('forged method invoked');}}, new Uint8Array([1])])
    check(!isSourceActorSoundTable(value), 'brand requires exact genuine owner identity');
  for (const value of [null, undefined, fake, inherited, new Proxy(table, {}), {readByte: table.readByte},
    Object.assign(Object.create(Uint8Array.prototype) as object, {0: 3}), new Uint16Array([3]), new Proxy(new Uint8Array([3]), {})])
    rejects(() => readSourceActorSoundTableByte(value, 0), 'explicit Uint8Array or genuine');
  rejects(() => table.readByte.call(fake, 16), 'genuine source sound table receiver');
  check(table.readByte.call(highest, 0xffffffff) === 13, 'borrowed method can read only its genuine receiver');

  const full = new Uint8Array([3, 5, 7]);
  check(readSourceActorSoundTableByte(full, 1) === 5, 'historical complete Uint8Array path');
  full[1] = 9; check(readSourceActorSoundTableByte(full, 1) === 9, 'historical complete table remains live');
  rejects(() => readSourceActorSoundTableByte(full, 3), '3: own data property');
  const view = full.subarray(1, 2);
  check(readSourceActorSoundTableByte(view, 0) === 9, 'historical view offsets preserved');
  for (const key of ['buffer', 'length', 'byteLength', Symbol.iterator])
    Object.defineProperty(full, key, {get() {throw Error('getter invoked');}});
  check(readSourceActorSoundTableByte(full, 0) === 3, 'historical own byte read ignores unconsumed getters');
  const exotic = new Uint8Array([0x5a]);
  for (const key of ['buffer', 'length', 'byteLength', Symbol.iterator])
    Object.defineProperty(exotic, key, {get() {throw Error('getter invoked');}});
  check(createSourceActorSoundTable([{offset: 0, bytes: exotic}]).readByte(0) === 0x5a, 'native copy bypasses overridden getters and iterator');
  const frozen = Object.freeze([Object.freeze({offset: 4, bytes: new Uint8Array([29])})]);
  check(createSourceActorSoundTable(frozen).readByte(4) === 29, 'readonly own-data inputs');

  const make = (offset: number, bytes: Uint8Array = new Uint8Array([1])) => createSourceActorSoundTable([{offset, bytes}]);
  for (const bad of [-1, NaN, Infinity, 1.5, 0x100000000]) rejects(() => make(bad), 'window offset: uint32');
  rejects(() => make(0xffffffff, new Uint8Array(2)), 'extent overflows');
  rejects(() => make(0, new Uint8Array(0)), 'nonempty');
  for (const bad of [new Uint16Array([1]), new DataView(new ArrayBuffer(1)), {}, new Proxy(new Uint8Array([1]), {})])
    rejects(() => make(0, bad as Uint8Array), 'Uint8Array');
  if (typeof SharedArrayBuffer !== 'undefined')
    rejects(() => make(0, new Uint8Array(new SharedArrayBuffer(1))), 'non-shared');
  for (const ranges of [
    [{offset: 4, bytes: new Uint8Array(2)}, {offset: 4, bytes: new Uint8Array(1)}],
    [{offset: 5, bytes: new Uint8Array(2)}, {offset: 4, bytes: new Uint8Array(2)}],
    [{offset: 4, bytes: new Uint8Array(4)}, {offset: 5, bytes: new Uint8Array(1)}],
  ]) rejects(() => createSourceActorSoundTable(ranges), 'overlapping');
  rejects(() => createSourceActorSoundTable({length: 0} as unknown as SourceActorSoundByteWindow[]), 'explicit decoded window array');
  rejects(() => createSourceActorSoundTable(new Array<SourceActorSoundByteWindow>(1)), '0: own data property');
  rejects(() => createSourceActorSoundTable([Object.create({offset: 0, bytes: new Uint8Array([1])}) as SourceActorSoundByteWindow]),
    'offset: own data property');
  let getter = false;
  for (const key of ['offset', 'bytes'] as const) {
    const row = {offset: 0, bytes: new Uint8Array([1])};
    Object.defineProperty(row, key, {get() {getter = true; return key === 'offset' ? 0 : new Uint8Array([1]);}});
    rejects(() => createSourceActorSoundTable([row]), `${key}: own data property`);
  }
  const accessorRows: SourceActorSoundByteWindow[] = [];
  Object.defineProperty(accessorRows, '0', {get() {getter = true; return {offset: 0, bytes: new Uint8Array([1])};}});
  rejects(() => createSourceActorSoundTable(accessorRows), '0: own data property');
  const badLimits: SourceActorSoundTableLimits = {};
  Object.defineProperty(badLimits, 'maxBytes', {get() {getter = true; return 1;}});
  rejects(() => createSourceActorSoundTable([], badLimits), 'maxBytes: own data property');
  check(!getter, 'no input getter invoked');
  for (const key of ['maxBytes', 'maxWindows'] as const) {
    for (const bad of [0, -1, NaN, Infinity, 1.5, 0x100000000])
      rejects(() => createSourceActorSoundTable([], {[key]: bad}), key);
  }
  rejects(() => createSourceActorSoundTable([], {maxBytes: 16 * 1024 * 1024 + 1}), 'maxBytes');
  rejects(() => createSourceActorSoundTable([], {maxWindows: 4097}), 'maxWindows');
  rejects(() => createSourceActorSoundTable([], null as unknown as SourceActorSoundTableLimits), 'window limits');
  const two = [{offset: 0, bytes: new Uint8Array([1])}, {offset: 10, bytes: new Uint8Array([2])}];
  check(createSourceActorSoundTable(two, {maxBytes: 2, maxWindows: 2}).readByte(10) === 2, 'exact aggregate host budgets');
  rejects(() => createSourceActorSoundTable(two, {maxBytes: 1}), 'aggregate copied byte budget');
  rejects(() => createSourceActorSoundTable(two, {maxWindows: 1}), 'window count budget');
  rejects(() => createSourceActorSoundTable(new Array<SourceActorSoundByteWindow>(4097)), 'window count budget');
  rejects(() => make(0, new Uint8Array(16 * 1024 * 1024 + 1)), 'aggregate copied byte budget');

  let trapped = 0;
  for (const nested of [() => table.readByte(16), () => readSourceActorSoundTableByte(full, 0), () => createSourceActorSoundTable([])]) {
    const row = new Proxy({offset: 0, bytes: new Uint8Array([1])}, {getOwnPropertyDescriptor(target, key) {
      try {nested();} catch {trapped++;}
      return Object.getOwnPropertyDescriptor(target, key);
    }});
    rejects(() => createSourceActorSoundTable([row]), 'caught same-runtime reentry');
    check(table.readByte(16) === 17, 'caught reentry resets module operation guard');
  }
  check(trapped === 3, 'factory trap cannot swallow nested factory or read failure');
  const proxiedLimits = new Proxy({}, {getOwnPropertyDescriptor(target, key) {
    try {createSourceActorSoundTable([]);} catch {trapped++;}
    return Object.getOwnPropertyDescriptor(target, key);
  }});
  rejects(() => createSourceActorSoundTable([], proxiedLimits), 'caught same-runtime reentry');
  const proxiedRows = new Proxy(two, {getOwnPropertyDescriptor(target, key) {
    try {table.readByte(16);} catch {trapped++;}
    return Object.getOwnPropertyDescriptor(target, key);
  }});
  rejects(() => createSourceActorSoundTable(proxiedRows), 'caught same-runtime reentry');
  // The same descriptor interception used by source-order regressions proves
  // a caught nested operation cannot make a historical byte read succeed.
  const descriptor = Object.getOwnPropertyDescriptor;
  try {
    Object.getOwnPropertyDescriptor = (target: object, key: PropertyKey): PropertyDescriptor | undefined => {
      if (target === full) {try {table.readByte(16);} catch {trapped++;}}
      return descriptor(target, key);
    };
    rejects(() => readSourceActorSoundTableByte(full, 0), 'caught same-runtime reentry');
  } finally {Object.getOwnPropertyDescriptor = descriptor;}
  check(trapped === 6 && table.readByte(16) === 17, 'factory and reached legacy reads reset guard after poisoned input');
  console.log('[actor-sound-table] PASS: private copied explicit windows, genuine identity, reached gap refusals, budgets and reentry; supplied synthetic bytes only, no archive parsing, source provenance or audio claim');
}
