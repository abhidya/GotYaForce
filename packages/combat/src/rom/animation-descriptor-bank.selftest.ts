import {createSourceAnimationDescriptorBankRuntime} from './animation-descriptor-bank.js';
function check(ok: boolean, label: string): void {if (!ok) throw Error(`[animation-descriptor-bank-test] ${label}`);}
function rejects(run: () => unknown, part: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(part), `${part}: ${error}`);
}
export function runAnimationDescriptorBankSelfTests(): void {
  const r = createSourceAnimationDescriptorBankRuntime();
  const bytes = new Uint8Array(128), view = new DataView(bytes.buffer);
  // Family base16, group1 at48, action1 returns44. Shared base80, group1
  // points backwards to64, whose action1 points forwards to76.
  view.setInt16(16, 32); view.setInt16(18, 32); view.setInt16(20, 48);
  view.setInt16(48, 4); view.setInt16(50, -4);
  view.setInt16(64, 12); view.setInt16(66, 12);
  view.setInt16(80, -16); view.setInt16(82, -16);
  bytes[44] = 0xa7;
  const root = r.createBytes(bytes), family = r.cursorAt(root, 16), shared = r.cursorAt(root, 80);
  const ready = {family1d88: family, shared1d8c: shared}, selector = {defaultSelector582: 1};
  const resolve = (group: number, action: number) => r.resolveDescriptor(ready, selector, group, action);
  check(resolve(1, 1) === r.cursorAt(root, 44), 'family forward group and backward action, BE16');
  check(resolve(0x81, 1) === r.cursorAt(root, 76), 'shared backward group and forward action');
  check(resolve(0xffffff81, 1) === resolve(0x81, 1), 'shared masks all but low seven bits');
  check(resolve(0, 1) === resolve(1, 1), 'default selector');
  selector.defaultSelector582 = 2;
  check(resolve(0, 1) === r.cursorAt(root, 76), 'live default source');
  ready.family1d88 = shared;
  check(resolve(1, 1) === r.cursorAt(root, 76), 'live readiness source'); ready.family1d88 = family;
  check(resolve(0x80000001, 1) === resolve(1, 1), 'group multiplication wraps');
  check(resolve(1, -0x80000000) === resolve(1, 0), 'signed action multiplication wraps');
  check(resolve(1, 0x80000001) === resolve(1, 1), 'unsigned action multiplication wraps');
  rejects(() => resolve(1, -1), 'read coordinate');
  selector.defaultSelector582 = 0xff;
  rejects(() => resolve(0, 0), 'read coordinate'); // Sign extends, not shared group127.
  selector.defaultSelector582 = 0x80;
  rejects(() => resolve(0, 0), 'bounds'); // Branch chosen before default.
  const never = {get defaultSelector582(): never {throw Error('getter invoked');}};
  const partial = {get family1d88(): never {throw Error('getter invoked');}, shared1d8c: shared};
  check(r.resolveDescriptor(partial, never, 0x81, 1) === r.cursorAt(root, 76), 'unreached getters skipped');
  rejects(() => r.resolveDescriptor(ready, never, 0, 0), 'own data property');
  check(r.resolveDescriptor(Object.freeze({...ready}), Object.freeze({defaultSelector582: 1}), 0, 1) === r.cursorAt(root, 44), 'readonly records');
  bytes.fill(255);
  check(r.readByte(resolve(1, 1)) === 0xa7, 'private copied backing');
  check(r.readByte(family, 28) === 0xa7 && r.readByte(r.cursorAt(root, 45), -1) === 0xa7, 'relative byte reads');
  check(r.cursorOffset(root, family) === 16, 'root-based offset');
  rejects(() => r.cursorAt(family, 0), 'root byte base');
  rejects(() => r.cursorOffset(r.createBytes(new Uint8Array(0)), family), 'does not belong');
  rejects(() => r.readByte(Symbol()), 'owned byte cursor');
  rejects(() => r.readByte(r.cursorAt(root, 0xffffffff)), 'bounds');
  rejects(() => r.readByte(root, -1), 'read coordinate');
  rejects(() => r.cursorAt(root, 0x100000000), 'cursor coordinate');
  for (const bad of [NaN, Infinity, 1.5, -1, 0x100000000]) rejects(() => resolve(bad, 0), 'group');
  for (const bad of [NaN, Infinity, 1.5, -0x80000001, 0x100000000]) rejects(() => resolve(1, bad), 'action');
  for (const bad of [-1, 256, NaN]) {selector.defaultSelector582 = bad; rejects(() => resolve(0, 0), 'defaultSelector582');}
  ready.family1d88 = Symbol(); rejects(() => resolve(1, 0), 'owned byte cursor'); ready.family1d88 = family;
  rejects(() => r.resolveDescriptor({family1d88: null, shared1d8c: shared}, selector, 1, 0), 'owned byte cursor');
  rejects(() => r.createBytes(new Proxy(new Uint8Array(1), {})), 'Uint8Array');
  rejects(() => r.createBytes(new Uint16Array(1) as unknown as Uint8Array), 'Uint8Array');
  if (typeof SharedArrayBuffer !== 'undefined') rejects(() => r.createBytes(new Uint8Array(new SharedArrayBuffer(1))), 'non-shared');
  rejects(() => r.createBytes(new Uint8Array(16 * 1024 * 1024 + 1)), '16MiB');
  const exotic = new Uint8Array([0x5a]);
  for (const key of ['buffer', 'length', 'byteLength', Symbol.iterator]) Object.defineProperty(exotic, key, {get() {throw Error('getter invoked');}});
  check(r.readByte(r.createBytes(exotic)) === 0x5a, 'native copy bypasses properties and iterator');
  check(r.readByte(r.createBytes(new Uint8Array([1, 2, 3]).subarray(1, 2))) === 2, 'native view offset/length');
  const foreign = createSourceAnimationDescriptorBankRuntime().createBytes(new Uint8Array(2));
  rejects(() => r.resolveDescriptor({family1d88: foreign, shared1d8c: null}, selector, 1, 0), 'owned byte cursor');
  rejects(() => r.resolveDescriptor(Object.create({family1d88: family}), selector, 1, 0), 'own data property');
  const extremes = new Uint8Array(32772), extremeView = new DataView(extremes.buffer);
  extremeView.setInt16(32768, -32768); extremeView.setInt16(0, 32767);
  const extremeRoot = r.createBytes(extremes);
  check(r.cursorOffset(extremeRoot, r.resolveDescriptor({family1d88: r.cursorAt(extremeRoot, 32768), shared1d8c: null}, {defaultSelector582: 0}, 0, 0)) === 32767, 'signed short extrema');
  // A descriptor cursor can be unreadable: returning it must not probe bytes.
  const lazyRoot = r.createBytes(new Uint8Array([0, 2, 0x7f, 0xff]));
  const lazyReady = {family1d88: lazyRoot, shared1d8c: null};
  check(r.cursorOffset(lazyRoot, r.resolveDescriptor(lazyReady, {defaultSelector582: 0}, 0, 0)) === 32769, 'lazy result pointer');
  const negativeRoot = r.createBytes(new Uint8Array([0xff, 0xff]));
  rejects(() => r.resolveDescriptor({family1d88: negativeRoot, shared1d8c: null}, {defaultSelector582: 0}, 0, 0), 'cursor coordinate');
  const truncatedRoot = r.createBytes(new Uint8Array([0]));
  rejects(() => r.resolveDescriptor({family1d88: truncatedRoot, shared1d8c: null}, {defaultSelector582: 0}, 0, NaN), 'bounds');
  let trapped = false;
  const proxy = new Proxy(ready, {getOwnPropertyDescriptor(target, key) {
    try {r.readByte(root);} catch {trapped = true;}
    return Object.getOwnPropertyDescriptor(target, key);
  }});
  rejects(() => r.resolveDescriptor(proxy, selector, 1, 0), 'caught same-runtime reentry');
  check(trapped && resolve(1, 1) === r.cursorAt(root, 44), 'poisoned reentry resets after failure');

  // Disjoint synthetic windows use real logical coordinates, never a fabricated
  // contiguous zero bank. The high/low group displacement crosses adjacent views.
  const ground = new Uint8Array(20), air = new Uint8Array(20); ground[3] = 91; air[3] = 92;
  const windowInput = [
    {offset: 0x5f4, bytes: air}, {offset: 8, bytes: new Uint8Array([0x01])},
    {offset: 9, bytes: new Uint8Array([0x24])}, {offset: 0x124, bytes: new Uint8Array([0x04, 0xbc, 0x04, 0xd0])},
    {offset: 0x5e0, bytes: ground},
  ];
  const sparseRoot = r.createByteWindows(windowInput), sparseReady = {family1d88: sparseRoot, shared1d8c: null};
  const sparseResolve = (action: number) => r.resolveDescriptor(sparseReady, {defaultSelector582: 4}, 4, action);
  const groundCursor = sparseResolve(0), airCursor = sparseResolve(1);
  check(groundCursor === r.cursorAt(sparseRoot, 0x5e0) && airCursor === r.cursorAt(sparseRoot, 0x5f4),
    'sparse lookup returns the same canonical interned descriptor cursors');
  check(r.readByte(groundCursor, 3) === 91 && r.readByte(airCursor, 3) === 92, 'explicit descriptor bytes reached through genuine bank lookup');
  ground.fill(255); air.fill(255); windowInput[0]!.offset = 0; windowInput.length = 0;
  check(r.readByte(sparseResolve(0), 3) === 91 && r.readByte(sparseResolve(1), 3) === 92,
    'sparse input mutation cannot replace owned records or lookup bytes');
  for (const offset of [0, 7, 10, 0x123, 0x128, 0x5df, 0x608, 0xffffffff])
    rejects(() => r.readByte(r.cursorAt(sparseRoot, offset)), 'uncovered');
  rejects(() => sparseResolve(2), 'byte296: uncovered');
  rejects(() => r.resolveDescriptor(sparseReady, selector, 3, 0), 'byte6: uncovered');
  rejects(() => r.readByte(groundCursor, -0x5e1), 'read coordinate');
  const sparseLazy = r.createByteWindows([{offset: 8, bytes: new Uint8Array([0, 10, 0, 20])}]);
  const sparseLazyResult = r.resolveDescriptor({family1d88: sparseLazy, shared1d8c: null}, selector, 4, 0);
  check(sparseLazyResult === r.cursorAt(sparseLazy, 30), 'missing descriptor coverage is not read during pointer resolution');
  rejects(() => r.readByte(sparseLazyResult), 'uncovered');
  const emptySparse = r.createByteWindows([]);
  rejects(() => r.readByte(emptySparse), 'uncovered');
  const sparseLast = r.createByteWindows([{offset: 0xffffffff, bytes: new Uint8Array([37])}]);
  check(r.readByte(r.cursorAt(sparseLast, 0xffffffff)) === 37, 'last logical coordinate is independent of copy budget');
  rejects(() => r.readByte(r.cursorAt(sparseLast, 0xffffffff), 1), 'read coordinate');
  rejects(() => r.cursorOffset(root, groundCursor), 'does not belong');
  const otherRuntime = createSourceAnimationDescriptorBankRuntime();
  rejects(() => otherRuntime.readByte(groundCursor), 'owned byte cursor');
  for (const offset of [-1, NaN, Infinity, 0.5, 0x100000000])
    rejects(() => r.createByteWindows([{offset, bytes: new Uint8Array([1])}]), 'window offset');
  rejects(() => r.createByteWindows([{offset: 0xffffffff, bytes: new Uint8Array(2)}]), 'extent overflows');
  rejects(() => r.createByteWindows([{offset: 0, bytes: new Uint8Array(0)}]), 'nonempty');
  rejects(() => r.createByteWindows([{offset: 5, bytes: new Uint8Array(2)}, {offset: 4, bytes: new Uint8Array(2)}]), 'overlapping');
  rejects(() => r.createByteWindows([{offset: 0, bytes: new Proxy(new Uint8Array(1), {})}]), 'Uint8Array');
  if (typeof SharedArrayBuffer !== 'undefined')
    rejects(() => r.createByteWindows([{offset: 0, bytes: new Uint8Array(new SharedArrayBuffer(1))}]), 'non-shared');
  rejects(() => r.createByteWindows([{offset: 0, bytes: new Uint8Array(2)}], {maxBytes: 1}), 'aggregate copied byte budget');
  rejects(() => r.createByteWindows([{offset: 0, bytes: new Uint8Array(1)}, {offset: 2, bytes: new Uint8Array(1)}], {maxWindows: 1}),
    'window count budget');
  const sparseExotic = new Uint8Array([73]);
  for (const key of ['buffer', 'length', 'byteLength', Symbol.iterator])
    Object.defineProperty(sparseExotic, key, {get() {throw Error('getter invoked');}});
  check(r.readByte(r.createByteWindows([{offset: 0, bytes: sparseExotic}])) === 73, 'window copy bypasses view getters and iterator');
  let windowGetter = false;
  const badWindow = {get offset() {windowGetter = true; return 0;}, bytes: new Uint8Array(1)};
  rejects(() => r.createByteWindows([badWindow]), 'offset: own data property');
  check(!windowGetter, 'window accessors rejected without invocation');
  const reentrantWindow = new Proxy({offset: 0, bytes: new Uint8Array(1)}, {getOwnPropertyDescriptor(target, key) {
    try {r.readByte(groundCursor);} catch {trapped = true;}
    return Object.getOwnPropertyDescriptor(target, key);
  }});
  trapped = false;
  rejects(() => r.createByteWindows([reentrantWindow]), 'caught same-runtime reentry');
  check(trapped && r.readByte(groundCursor, 3) === 91, 'window import reentry poisons and resets same bank guard');
  console.log('[animation-descriptor-bank] PASS: complete and disjoint copied bytes, canonical cursors and reached uncovered-byte refusals; synthetic inputs only, no source provenance or archive parsing claim');
}
