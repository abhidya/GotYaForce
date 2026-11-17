import {createSourceFObjRuntime, type SourceFObjHeader} from './fobj-list.js';
import {SOURCE_FOBJ_MAX_DATA_BYTES} from './fobj-data.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[fobj-data] ${message}`); }
function rejects(run: () => void, text: string): void {
  let diagnostic = '';
  try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic}`);
}
function floatBytes(value: number): number[] {
  const bytes = new Uint8Array(4); new DataView(bytes.buffer).setFloat32(0, value, true);
  return [...bytes];
}
function fixture(bytes: number[], fields: Partial<SourceFObjHeader> = {}) {
  // This callback intentionally calls ONLY the loader, not a pretend interpreter.
  const r = createSourceFObjRuntime(n => { r.loadData(n); });
  const input = Uint8Array.from(bytes), base = r.createData(input);
  const initial: SourceFObjHeader = {next00: null, cursor04: base, base08: base,
    length0c: bytes.length, flags10: 0xb1, byte11: 9, byte12: 8, track13: 7,
    format14: 0, format15: 0, half16: 0, offset18: -1, half1a: 22,
    frame1c: 33, value20: 10, value24: 20, value28: 30, value2c: 40, ...fields};
  const id = r.createNode(initial), n = r.getNode(id);
  return {r, n, id, base, input, load: () => r.loadData(n),
    offset: () => r.cursorOffset(base, n.cursor04!)};
}
export function runFObjDataSelfTest(): void {
  for (const state of [1, 2]) for (let opcode = 1; opcode <= 6; opcode++) {
    const f = fixture([opcode, ...floatBytes(-12.5), ...floatBytes(2.25)], {flags10: 0xb0 | state});
    const result = f.load();
    check(result === (opcode === 5 ? state : state + 2), `opcode${opcode} return/state${state}`);
    check(f.n.flags10 === ((opcode === 6 ? 0xf0 : 0xb0) | result), 'preserves high flags');
    check(f.n.byte12 === 9 && f.n.byte11 === opcode && f.n.half16 === 0, 'command writes');
    check(f.n.value20 === (opcode === 5 || opcode === 6 ? 10 : 20), 'old value write');
    check(f.n.value24 === (opcode === 5 ? 20 : -12.5), 'new value write');
    check(f.n.value28 === (opcode === 6 ? 30 : 40), 'old slope write');
    check(f.n.value2c === (opcode === 4 ? 2.25 : opcode === 5 ? -12.5 : opcode === 6 ? 40 : 0), 'new slope write');
    check(f.offset() === (opcode === 4 ? 9 : 5), 'loader does not read trailing duration');
    check(f.n.track13 === 7 && f.n.frame1c === 33 && f.n.half1a === 22 && f.n.offset18 === -1,
      'loader leaves track/time fields unchanged');
  }
  for (const op of [1, 2]) {
    const f = fixture([op, ...floatBytes(7)], {byte11: 5}); f.load();
    check(f.n.value28 === 30 && f.n.value2c === 40 && f.n.byte12 === 5, 'prior op5 preserves both slopes');
  }
  {
    const f = fixture([6, ...floatBytes(7)], {flags10: 0x61}); f.load();
    check(f.n.flags10 === 0xe3 && f.n.byte12 === 6 && f.n.value20 === 20 && f.n.value24 === 7,
      'pending40 clears/sets flags, copies opcode and previous value');
    const g = fixture([6], {flags10: 0x61, format14: 1});
    rejects(g.load, 'unsupported numeric format');
    check(g.n.flags10 === 0xa1 && g.n.byte12 === 6 && g.n.value20 === 20 && g.n.value24 === 20,
      'pending40 pre-read writes retained on unsupported format');
  }
  // Every integer format and fraction bit, both signed boundaries, unsigned maxima.
  const formats = [
    {kind: 0x20, samples: [-32768, -1, 0, 32767], width: 2},
    {kind: 0x40, samples: [0, 32768, 65535], width: 2},
    {kind: 0x60, samples: [-128, -1, 0, 127], width: 1},
    {kind: 0x80, samples: [0, 128, 255], width: 1},
  ];
  for (const {kind, samples, width} of formats) for (let bits = 0; bits < 32; bits++) for (const value of samples) {
    const payload = width === 1 ? [value & 255] : [value & 255, (value >> 8) & 255];
    for (const op of [1, 5]) {
      const f = fixture([op, ...payload], {format14: kind | bits, format15: kind | bits});
      f.load();
      const divisor = bits === 31 ? -(2 ** 31) : 2 ** bits;
      check(Object.is(op === 5 ? f.n.value2c : f.n.value24, Math.fround(value / divisor)),
        `integer format${kind} frac${bits} value${value}, including sign of zero`);
      check(f.offset() === 1 + width, 'integer byte width');
    }
  }
  for (const value of [0, -0, 2 ** -149, -(2 ** -149), 1.25, Math.fround(3.4028234663852886e38)]) {
    const f = fixture([1, ...floatBytes(value)]); f.load();
    check(Object.is(f.n.value24, value), 'float32 LE exact bits including zero/subnormal');
  }
  {
    const f = fixture([0x25, 11, 12, 13, 1, 14], {format14: 0x80, format15: 0x80});
    for (let i = 0; i < 3; i++) {
      check(f.load() === 1 && f.n.half16 === 2 - i && f.n.value2c === 11 + i, 'packed repeat group');
      check(f.offset() === i + 2 && f.n.byte12 === (i === 0 ? 9 : 5), 'repeat consumes no command byte');
    }
    check(f.load() === 3 && f.n.value24 === 14 && f.n.value28 === 12 && f.n.value2c === 13,
      'new command after repeated op5 preserves slopes');
  }
  for (const [encoding, count] of [ [[0x85, 1], 9], [[0xf5, 0x81, 1], 1040],
    [[0xe5, 0xff, 63], 65535] ] as const) {
    const f = fixture([...encoding, 9], {format15: 0x80}); f.load();
    check(f.n.half16 === count - 1 && f.n.value2c === 9, 'bounded count continuation');
  }
  for (const op of [0, 7, 15]) {
    const f = fixture([op, 99], {flags10: 0});
    check(f.load() === 0 && f.offset() === 1 && f.n.byte12 === 9 && f.n.byte11 === op &&
      f.n.value20 === 10 && f.n.flags10 === 0, 'unknown/zero opcode has no guessed payload effects/assertion');
  }
  {
    const f = fixture([1, 9], {length0c: 0}); const before = {...f.n};
    check(f.load() === 6 && JSON.stringify(f.n) === JSON.stringify(before) && f.offset() === 0,
      'end return before any header writes');
    f.n.length0c = 1; f.n.cursor04 = f.r.cursorAt(f.base, 2);
    const beforeCursor = f.n.cursor04;
    check(f.load() === 6 && f.n.cursor04 === beforeCursor && f.n.byte12 === 8,
      'cursor beyond declared end also returns six unchanged');
  }
  {
    const f = fixture([0x15, 9], {format15: 0x80}); f.load();
    const before = {...f.n}, cursor = f.n.cursor04;
    check(f.n.half16 === 1 && f.load() === 6 && f.n.cursor04 === cursor &&
      JSON.stringify(f.n) === JSON.stringify(before), 'EOF guard precedes pending repeat processing');
    const g = fixture([], {length0c: 1}); rejects(g.load, 'truncated');
    check(g.n.byte12 === 9 && g.n.byte11 === 9 && g.offset() === 0,
      'missing fresh command retains previous-op store but not opcode/cursor/count');
  }
  for (let packed = 0; packed < 8; packed++) {
    const f = fixture([(packed << 4) | 5, 9], {format15: 0x80}); f.load();
    check(f.n.half16 === packed, 'all inline count values');
  }
  for (const state of [0, 3, 4, 5, 6, 15]) {
    const f = fixture([1, 9], {flags10: 0xa0 | state, format14: 0x80});
    rejects(f.load, 'source assertion');
    check(f.offset() === 1 && f.n.byte12 === 9 && f.n.half16 === 0 && f.n.value20 === 10,
      'assertion follows command writes but precedes operand writes');
  }
  for (const format of [1, 31, 0xa0, 0xc0, 0xff]) {
    const f = fixture([1, 9, 9, 9, 9], {format14: format}); rejects(f.load, 'unsupported numeric format');
    check(f.offset() === 1 && f.n.value20 === 20 && f.n.value24 === 20 && f.n.value28 === 30,
      'unsupported format abort does not fabricate zero or consume a float');
  }
  for (const op of [1, 2, 3, 4, 5, 6]) {
    const f = fixture([op], {format14: 0x20, format15: 0x20}); rejects(f.load, 'truncated');
    check(f.offset() === 1 && f.n.flags10 === 0xb1 && f.n.value24 === 20 && f.n.value2c === 40,
      'truncation retains flags/value destinations');
    check(f.n.value20 === (op === 5 || op === 6 ? 10 : 20) &&
      f.n.value28 === (op === 3 || op === 5 ? 40 : 30), 'pre-read writes are opcode specific');
  }
  {
    const f = fixture([4, 7, 0, 9], {format14: 0x20, format15: 0x20}); rejects(f.load, 'truncated');
    check(f.offset() === 3 && f.n.value24 === 7 && f.n.value28 === 40 && f.n.value2c === 40,
      'op4 value stored and slope copied before failing slope read; LE16 read is atomic');
    const g = fixture([1, 0, 0]); rejects(g.load, 'truncated');
    check(g.offset() === 3 && g.n.value20 === 20, 'float byte reads preserve partial cursor advancement');
    const h = fixture([1, 7, 0], {length0c: 2, format14: 0x20}); rejects(h.load, 'truncated');
    check(h.offset() === 1, 'declared bound enforced even with extra copied bytes');
  }
  for (const value of [NaN, Infinity, -Infinity]) {
    const f = fixture([1, ...floatBytes(value)]); rejects(f.load, 'nonfinite');
    check(f.offset() === 5 && f.n.value20 === 20 && f.n.value24 === 20 && f.n.flags10 === 0xb1,
      'nonfinite consumes bytes but never stores invalid scalar or transition');
  }
  for (const bytes of [[0x81], [0xf1, 0xff, 63], [0x81, 0x80, 0x80, 0]]) {
    const f = fixture(bytes); rejects(f.load, bytes.length === 1 ? 'truncated' : 'packed count');
    check(f.n.byte12 === 9 && f.n.byte11 === 1 && f.n.half16 === 0 && f.n.value20 === 10,
      'malformed count retains earlier opcode/cursor stores only');
  }
  {
    const f = fixture([1, 7], {format14: 0x80}); f.input.fill(255);
    f.r.effects.requestAll(f.id, 4);
    check(f.n.cursor04 === f.base && f.n.track13 === 7 && f.n.format14 === 0x80 && f.n.length0c === 2,
      'request resets cursor and preserves newly modeled metadata');
    f.r.effects.interpretAll(f.id, 0, null);
    check(f.n.value24 === 7 && f.n.flags10 === 0xb3 && f.n.frame1c === 3,
      'actual loader via list callback reads copied bytes, does not advance time');
    const endCursor = f.n.cursor04;
    check(endCursor === f.r.cursorAt(f.base, 2) && endCursor === f.r.cursorAt(f.base, 2),
      'same base/offset has canonical pointer identity');
    f.r.effects.requestAll(f.id, 4); check(f.load() === 3 && f.n.value24 === 7 && f.n.cursor04 === endCursor,
      'request replays immutable copy and preserves equal cursor identities');
    const twin = f.r.createNode({...f.n, cursor04: f.base, flags10: 1, half16: 0});
    f.r.loadData(f.r.getNode(twin));
    check(f.r.getNode(twin).cursor04 === endCursor, 'nodes sharing a stream reach identical cursors');
    const window = new Uint8Array([99, 1, 8, 99]);
    const windowBase = f.r.createData(window.subarray(1, 3)); window.fill(0);
    f.n.base08 = windowBase; f.n.cursor04 = windowBase; f.n.flags10 = 1; f.n.half16 = 0;
    check(f.load() === 3 && f.n.value24 === 8, 'copied view respects byte offset/length');
    f.n.base08 = f.base; f.n.cursor04 = f.base;
    f.n.length0c = NaN; rejects(f.load, 'length0c'); f.n.length0c = 2;
    const foreign = fixture([1, 8]);
    rejects(() => f.r.loadData(foreign.n), 'non-owned header');
    f.n.cursor04 = foreign.base; rejects(f.load, 'provenance');
    f.n.cursor04 = null; rejects(f.load, 'null stream');
    f.n.cursor04 = f.base; f.n.base08 = Symbol(); rejects(f.load, 'non-owned stream');
    rejects(() => f.r.cursorAt(f.base, -1), 'outside');
    rejects(() => f.r.cursorAt(f.base, 3), 'outside');
    rejects(() => f.r.cursorAt(f.base, .5), 'outside');
    rejects(() => f.r.createData(new Uint8Array(SOURCE_FOBJ_MAX_DATA_BYTES + 1)), 'bounded');
    rejects(() => f.r.createData(new Uint8Array(new SharedArrayBuffer(1))), 'non-shared');
    for (const fields of [{length0c: -1}, {length0c: 2 ** 32}, {track13: 256}, {format14: -1}, {format15: 1.5}]) {
      rejects(() => f.r.createNode({...foreign.n, ...fields}), Object.keys(fields)[0]!);
    }
  }
  console.log('[fobj-data] PASS: bounded source loader opcodes/formats/counts/order/provenance; synthetic tests, no per-node interpreter or live integration');
}
