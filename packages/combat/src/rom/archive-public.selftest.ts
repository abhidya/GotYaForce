import {createSourceArchivePublicRuntime, type SourceArchivePublicBinding} from './archive-public.js';
function check(ok: boolean, label: string): void {if (!ok) throw Error(`[archive-public-test] ${label}`);}
function rejects(run: () => unknown, part: string): void {let error = ''; try {run();} catch (e) {error = String(e);} check(error.includes(part), `${part}: ${error}`);}
export function runArchivePublicSelfTests(): void {
  const r = createSourceArchivePublicRuntime();
  const bytes = new Uint8Array(80), view = new DataView(bytes.buffer);
  // Nonzero table, string and data bases. Duplicate names preserve first match.
  for (const [i, data, name] of [[0, 2, 0], [1, 3, 0], [2, 4, 2], [3, 5, 3]]) {
    view.setUint32(8 + i! * 8, data!); view.setUint32(12 + i! * 8, name!);
  }
  bytes.set([0xff, 0, 0, 0x61, 0], 48);
  const base = r.createBytes(bytes), table = r.cursorAt(base, 8), strings = r.cursorAt(base, 48), data = r.cursorAt(base, 64);
  const initial = {publicCount0c: 4, data20: data, publicTable28: table, stringTable30: strings};
  const id = r.createArchive(initial); bytes.fill(99); initial.publicCount0c = 0;
  check(r.getPublicAddress(id, strings) === r.cursorAt(base, 66), 'copied bytes/binding and first high-byte duplicate');
  check(r.getPublicAddress(id, r.cursorAt(base, 50)) === r.cursorAt(base, 68), 'empty NUL string');
  check(r.getPublicAddress(id, r.cursorAt(base, 51)) === r.cursorAt(base, 69), 'normal name');
  const absent = r.createBytes(new Uint8Array([98, 0]));
  check(r.getPublicAddress(id, absent) === null, 'absent name');
  check(r.getPublicName(id, 1) === strings && r.cursorOffset(base, strings) === 48, 'canonical name cursor');
  check(r.getPublicName(Symbol(), -1) === null && r.getPublicName(Symbol(), 0x80000000) === null, 'signed negative before ownership');
  check(r.getPublicName(id, 4) === null, 'count guard');
  rejects(() => r.getPublicName(Symbol(), 0), 'owned archive');
  rejects(() => r.cursorOffset(absent, strings), 'does not belong');
  rejects(() => r.createBytes(new Proxy(new Uint8Array(2), {})), 'Uint8Array');
  if (typeof SharedArrayBuffer !== 'undefined') rejects(() => r.createBytes(new Uint8Array(new SharedArrayBuffer(2))), 'non-shared');
  rejects(() => r.createBytes(new Uint16Array(2) as unknown as Uint8Array), 'Uint8Array');
  const control = r.getArchive(id);
  control.data20 = null;
  check(r.getPublicAddress(id, absent) === null, 'unmatched data pointer never reached');
  rejects(() => r.getPublicAddress(id, strings), 'owned byte cursor');
  control.publicCount0c = 0;
  check(r.getPublicAddress(id, null) === null && r.getPublicAddress(id, Symbol()) === null, 'zero count skips query');
  control.publicCount0c = 1;
  rejects(() => r.getPublicAddress(id, null), 'owned byte cursor');
  control.data20 = data;
  control.stringTable30 = r.cursorAt(base, 0xffffffff);
  check(r.getPublicName(id, 0) === control.stringTable30, 'names return unread out-of-bounds cursor');
  rejects(() => r.getPublicAddress(id, strings), 'bounds');
  control.stringTable30 = strings;
  control.publicCount0c = 0x20000001;
  check(r.getPublicName(id, 0x20000000) === strings, 'table multiplication wraps uint32');
  control.publicTable28 = r.cursorAt(base, 0xfffffffc);
  rejects(() => r.getPublicName(id, 0), 'bounds');
  const lazy = {publicCount0c: 0, get data20(): never {throw Error('getter must not run');},
    get publicTable28(): never {throw Error('getter must not run');}, stringTable30: null};
  const lazyId = r.createArchive(lazy);
  check(r.getPublicAddress(lazyId, null) === null, 'unreached accessors copied without invocation');
  r.getArchive(lazyId).publicCount0c = 1;
  rejects(() => r.getPublicName(lazyId, 0), 'own data property');
  const missing = r.createArchive({publicCount0c: 0} as SourceArchivePublicBinding);
  check(r.getPublicName(missing, 0) === null, 'missing unreachable fields');
  const frozen = r.createArchive(Object.freeze({publicCount0c: 1, data20: data, publicTable28: table, stringTable30: strings}));
  check(r.getPublicAddress(frozen, strings) === r.cursorAt(base, 66), 'readonly operands accepted');
  control.publicCount0c = NaN;
  rejects(() => r.getPublicAddress(id, null), 'publicCount0c');
  check(r.getPublicName(id, -5) === null, 'negative bypasses malformed count');
  // Explicit host bounds and unsigned local-offset policy.
  const q = createSourceArchivePublicRuntime({maxEntries: 1, maxStringBytes: 2});
  const qb = q.createBytes(new Uint8Array([0, 0, 0, 0, 0, 0, 0, 8, 65, 65, 65, 0]));
  const qi = q.createArchive({publicCount0c: 2, data20: qb, publicTable28: qb, stringTable30: qb});
  rejects(() => q.getPublicAddress(qi, q.cursorAt(qb, 8)), 'maxStringBytes');
  rejects(() => q.getPublicAddress(qi, qb), 'maxEntries');
  const ob = q.createBytes(new Uint8Array([255, 255, 255, 255, 255, 255, 255, 255]));
  const oi = q.createArchive({publicCount0c: 1, data20: ob, publicTable28: ob, stringTable30: q.cursorAt(ob, 1)});
  rejects(() => q.getPublicName(oi, 0), 'cursor offset');
  // NUL is unnecessary after a decisive unequal byte; partial equal strings refuse.
  const mismatch = q.createBytes(new Uint8Array([66]));
  q.getArchive(qi).publicCount0c = 1;
  check(q.getPublicAddress(qi, mismatch) === null, 'mismatch stops before missing terminator');
  const prefix = q.createBytes(new Uint8Array([65]));
  rejects(() => q.getPublicAddress(qi, prefix), 'bounds');
  const noNul = q.createBytes(new Uint8Array([65]));
  q.getArchive(qi).stringTable30 = noNul;
  rejects(() => q.getPublicAddress(qi, noNul), 'bounds');
  rejects(() => createSourceArchivePublicRuntime({maxEntries: 0}), 'maxEntries');
  rejects(() => createSourceArchivePublicRuntime({maxStringBytes: Infinity}), 'maxStringBytes');
  let inner = false;
  const proxy = new Proxy({publicCount0c: 0}, {getOwnPropertyDescriptor(target, key) {
    if (!inner) {inner = true; try {r.createBytes(new Uint8Array());} catch { /* poison persists */ }}
    return Object.getOwnPropertyDescriptor(target, key);
  }});
  rejects(() => r.createArchive(proxy as SourceArchivePublicBinding), 'caught same-runtime reentry');
  check(r.getPublicAddress(missing, null) === null, 'runtime recovers after reentry');
}
