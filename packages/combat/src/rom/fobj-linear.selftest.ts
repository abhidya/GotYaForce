import {evaluateSourceFObjLinearValue} from './fobj-linear.js';
import {createSourceFObjRuntime, type SourceFObjHeader} from './fobj-list.js';
function check(ok: boolean, message: string): void { if (!ok) throw Error(`[fobj-linear] ${message}`); }
function rejects(run: () => unknown, text: string): void {
  let diagnostic = ''; try { run(); } catch (error) { diagnostic = String(error); }
  check(diagnostic.includes(text), `expected ${text}, got ${diagnostic}`);
}
function fixture(fields: Partial<SourceFObjHeader> = {}) {
  const r = createSourceFObjRuntime(() => { throw Error('interpreter deliberately unsupported'); });
  const base = r.createData(Uint8Array.of(0x12, 9, 7));
  const id = r.createNode({next00: null, cursor04: r.cursorAt(base, 1), base08: base, length0c: 3,
    flags10: 0xe4, byte11: 6, byte12: 2, track13: 7, format14: 0x80, format15: 0xa0,
    half16: 17, offset18: -3, half1a: 4, frame1c: 2,
    value20: 10, value24: 18, value28: 99, value2c: -13, ...fields});
  const n = r.getNode(id);
  return {r, n, run: () => evaluateSourceFObjLinearValue(r, n)};
}
function unchanged(n: SourceFObjHeader, before: SourceFObjHeader, except: (keyof SourceFObjHeader)[] = []): void {
  for (const key of Object.keys(before) as (keyof SourceFObjHeader)[]) {
    if (!except.includes(key)) check(Object.is(n[key], before[key]), `${key} unexpectedly changed`);
  }
}
function floatBits(value: number): number {
  const view = new DataView(new ArrayBuffer(4)); view.setFloat32(0, value); return view.getUint32(0);
}
export function runFObjLinearSelfTest(): void {
  {
    const f = fixture(), before = {...f.n};
    check(f.run() === 14 && f.n.value28 === 2 && f.n.flags10 === 0xc4, 'dirty slope and linear value');
    unchanged(f.n, before, ['flags10', 'value28']);
    f.n.value24 = -100; f.n.half1a = 0;
    const cached = {...f.n};
    check(f.run() === 14, 'clean flag uses cached slope even with changed endpoint and zero wait');
    unchanged(f.n, cached);
  }
  {
    const f = fixture({half1a: 0, value24: -0, frame1c: -2}), before = {...f.n};
    check(Object.is(f.run(), -0) && Object.is(f.n.value28, 0) && Object.is(f.n.value20, -0),
      'zero wait stores positive-zero slope then copies endpoint bits, before fmadds');
    unchanged(f.n, before, ['flags10', 'value28', 'value20']);
  }
  for (const [start, end, wait, frame, slope, value] of [
    [10, -10, 4, 2, -5, 0], [-10, 10, 4, -2, 5, -20],
    [1, 7, 3, 0, 2, 1], [0, 65535, 65535, 65535, 1, 65535],
    [0, 1, 3, 3, Math.fround(1 / 3), 1],
    [0, 2 ** -149, 2, 1, 0, 0], [0, -(2 ** -149), 2, 1, -0, 0],
    [0, 3 * 2 ** -149, 2, 1, 2 * 2 ** -149, 2 * 2 ** -149],
    [0, -0, 1, -1, -0, 0], [-0, -0, 1, -1, 0, -0],
  ] as const) {
    const f = fixture({value20: start, value24: end, half1a: wait, frame1c: frame});
    check(Object.is(f.run(), value) && Object.is(f.n.value28, slope), 'signed slope/frame, duration or subnormal result');
  }
  for (const start of [-(2 ** -126), -(2 ** -149)]) {
    const f = fixture({flags10: 4, value28: 1 + 2 ** -23, frame1c: 1.5, value20: start});
    const before = {...f.n};
    check(floatBits(f.run()) === 0x3fc00001 &&
      floatBits(Math.fround(f.n.value28 * f.n.frame1c + f.n.value20)) === 0x3fc00002,
      'fmadds must avoid the binary64 double-rounding witness');
    unchanged(f.n, before);
  }
  {
    const f = fixture({value20: 2 ** -25, value24: 1, half1a: 3, frame1c: 0});
    check(f.run() === 2 ** -25 && floatBits(f.n.value28) === 0x3eaaaaab &&
      floatBits(Math.fround((1 - 2 ** -25) / 3)) === 0x3eaaaaaa,
      'fsubs rounds before fdivs, rather than widening subtraction across division');
  }
  const max = (2 - 2 ** -23) * 2 ** 127;
  {
    const f = fixture({value20: 0, value24: max, half1a: 1, frame1c: 1});
    check(f.run() === max && f.n.value28 === max, 'largest finite slope and result');
    const g = fixture({flags10: 4, value28: max, frame1c: 2, value20: -max});
    check(g.run() === max, 'fused operation does not overflow product before cancellation');
  }
  {
    const f = fixture({value20: -max, value24: max, half1a: 65535}), before = {...f.n};
    rejects(f.run, 'overflow');
    check(f.n.flags10 === (before.flags10 & 0xdf) && f.n.value28 === before.value28,
      'fsubs overflow retains flag clear but not slope store, even if divided result could be finite');
    unchanged(f.n, before, ['flags10']);
    const g = fixture({value20: 0, value24: max, half1a: 1, frame1c: 2}), prior = {...g.n};
    rejects(g.run, 'overflow');
    check(g.n.value28 === max && g.n.flags10 === 0xc4, 'fmadds overflow retains completed slope store and flag clear');
    unchanged(g.n, prior, ['flags10', 'value28']);
    const h = fixture({flags10: 4, value28: max, frame1c: 2, value20: 0}), cached = {...h.n};
    rejects(h.run, 'overflow'); unchanged(h.n, cached);
  }
  for (const opcode of [0, 1, 3, 4, 5, 6, 255]) {
    const f = fixture({byte12: opcode}), before = {...f.n};
    rejects(f.run, 'opcode2 required'); unchanged(f.n, before);
  }
  {
    const f = fixture(), before = {...f.n};
    rejects(() => evaluateSourceFObjLinearValue(f.r, {...f.n}), 'non-owned');
    rejects(() => evaluateSourceFObjLinearValue(fixture().r, f.n), 'non-owned');
    unchanged(f.n, before);
    for (const invalid of [NaN, Infinity, -Infinity, 1 + 2 ** -25]) {
      f.n.frame1c = invalid;
      rejects(f.run, 'finite source float32');
      check(f.n.flags10 === before.flags10 && f.n.value28 === before.value28,
        'invalid header preflight occurs before source writes');
    }
  }
  console.log('[fobj-linear] PASS: bounded opcode2 slope writes and fused scalar evaluation; synthetic tests, no callback/phase interpreter or live integration');
}
