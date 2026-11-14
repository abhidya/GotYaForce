import {createSourceInputAtanRuntime, isSourceInputAtanRuntime,
  type SourceInputAtanData, type SourceInputAtanRuntime, type SourceInputAtanSources} from './source-input-atan.js';
import type {SourceInputAngleProcessorState} from './source-input-angle.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[source-input-atan-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function decoded(bits: bigint): number {
  const view = new DataView(new ArrayBuffer(8)); view.setBigUint64(0, bits, false); return view.getFloat64(0, false);
}
function bits(value: number): bigint {
  const view = new DataView(new ArrayBuffer(8)); view.setFloat64(0, value, false); return view.getBigUint64(0, false);
}
/** Explicit test evidence decoded from both authenticated archived snapshots;
 * never imported by production and never a runtime default data provider. */
export function sourceInputAtanTestData(): SourceInputAtanData {
  return {
    huge8043d128: decoded(0x7e37e43c8800759cn), one8043d130: decoded(0x3ff0000000000000n),
    two8043d138: decoded(0x4000000000000000n), onePointFive8043d140: decoded(0x3ff8000000000000n),
    negativeOne8043d148: decoded(0xbff0000000000000n),
    atanHi802b5168: [0x3fddac670561bb4fn, 0x3fe921fb54442d18n, 0x3fef730bd281f69bn, 0x3ff921fb54442d18n].map(decoded),
    atanLo802b5188: [0x3c7a2b7f222f65e2n, 0x3c81a62633145c07n, 0x3c7007887af0cbbdn, 0x3c91a62633145c07n].map(decoded),
    coefficients802b51a8: [0x3fd555555555550dn, 0xbfc999999998ebc4n, 0x3fc24924920083ffn,
      0xbfbc71c6fe231671n, 0x3fb745cdc54c206en, 0xbfb3b0f2af749a6dn, 0x3fb10d66a0d03d51n,
      0xbfadde2d52defd9an, 0x3fa97b4b24760debn, 0xbfa2b4442c6a6c2fn, 0x3f90ad3ae322da11n].map(decoded),
  };
}
function fixture() {
  const processor: SourceInputAngleProcessorState = {fpscrControl: 0};
  const data = sourceInputAtanTestData();
  const sources: SourceInputAtanSources = {processor, data}, runtime = createSourceInputAtanRuntime(sources);
  return {processor, data, sources, runtime};
}
export function runSourceInputAtanSelfTests(): void {
  const x = fixture();
  check(isSourceInputAtanRuntime(x.runtime) && !isSourceInputAtanRuntime({...x.runtime}) &&
    !isSourceInputAtanRuntime(null), 'genuine runtime identity only');
  check(Object.isFrozen(x.runtime), 'frozen public methods');
  check(x.runtime.getProcessor() === x.processor && x.runtime.getData() === x.data, 'retains owners without copies');
  check(!Object.isFrozen(x.processor) && !Object.isFrozen(x.data) && !Object.isFrozen(x.data.coefficients802b51a8), 'does not freeze owned data');
  const hostAtan = Math.atan, hostAtan2 = Math.atan2;
  Math.atan = () => {throw Error('host atan forbidden');}; Math.atan2 = () => {throw Error('host atan2 forbidden');};
  try {
    // Expected bits independently calculated with rational products/sums and
    // one binary64 conversion per fused operation, then checked by source path.
    // These synthetic vectors are not console observations or a general oracle.
    for (const [argument, expected] of [[0, 0n], [1, 0x3fe921fb54442d18n], [-1, 0xbfe921fb54442d18n],
      [2, 0x3ff1b6e192ebbe44n], [-128, 0xbff901fb7eee715en], [127, 0x3ff901bafef076bbn]] as const)
      equal(bits(x.runtime.atanSignedByte(argument)), expected, `fast-path bits/${argument}`);
    for (const [y, a, expected] of [[1, -128, 0x3f7fffd555bbba97n], [7, 16, 0x3fda64eec3cc23fdn],
      [11, 16, 0x3fe345f01cce37bbn], [19, 16, 0x3febde70ed439fe7n], [39, 16, 0x3ff2e75728833a54n],
      [1, 2, 0x3fddac670561bb4fn], [3, 2, 0x3fef730bd281f69bn], [29, 70, 0x3fd922fda18451b4n],
      [70, 29, 0x3ff2d93bebe318abn], [3, 7, 0x3fd9e9bf3d20dc70n], [5, 8, 0x3fe1e00babdefeb4n],
      [8, 7, 0x3feb434ee31013fcn], [15, 7, 0x3ff2258e91851052n], [125, 127, 0x3fe8e0f79d787b3en],
      [127, -128, 0x3fe901db3eeef187n]] as const)
      equal(bits(x.runtime.atanAbsoluteRatio(y, a)), expected, `quotient bits/${y}/${a}`);
  } finally {Math.atan = hostAtan; Math.atan2 = hostAtan2;}
  for (const bad of [-129, 128, -0, NaN, Infinity, -Infinity, .5, undefined as unknown as number]) {
    rejects(() => x.runtime.atanSignedByte(bad), 'canonical signed-byte');
    rejects(() => x.runtime.atanAbsoluteRatio(bad, 2), 'canonical signed-byte');
    rejects(() => x.runtime.atanAbsoluteRatio(2, bad), 'canonical signed-byte');
  }
  rejects(() => x.runtime.atanAbsoluteRatio(0, 2), 'nonzero');
  rejects(() => x.runtime.atanAbsoluteRatio(2, 0), 'nonzero');
  rejects(() => x.runtime.atanAbsoluteRatio(2, 1), 'earlier fast-path');
  // The true tiny (+0) path loads only huge/one, executes fadd and returns +0.
  {
    const processor = {fpscrControl: 0}, data = {huge8043d128: x.data.huge8043d128!, one8043d130: 1};
    const runtime = createSourceInputAtanRuntime({processor, data});
    equal(runtime.atanSignedByte(0), 0, 'tiny path does not demand polynomial/hi/lo arrays');
    rejects(() => runtime.atanAbsoluteRatio(1, -128), 'coefficients802b51a8');
    const missing = createSourceInputAtanRuntime({processor, data: {}});
    rejects(() => missing.atanSignedByte(0), 'huge8043d128');
    rejects(() => missing.atanSignedByte(1), 'one8043d130');
  }
  // Region -1 never loads hi/lo or reduction constants; tiny constant is lazy.
  {
    const f = fixture(); delete f.data.huge8043d128; delete f.data.one8043d130; delete f.data.two8043d138;
    delete f.data.onePointFive8043d140; delete f.data.negativeOne8043d148;
    delete f.data.atanHi802b5168; delete f.data.atanLo802b5188;
    equal(bits(f.runtime.atanAbsoluteRatio(1, -128)), 0x3f7fffd555bbba97n, 'unreached reduction/hi/lo fields absent');
    rejects(() => f.runtime.atanSignedByte(0), 'huge8043d128');
  }
  // Every actually loaded constant and selected coefficient is authenticated.
  for (const [key, y, a, site] of [['huge8043d128', 0, 1, '8023c2e8'], ['one8043d130', 0, 1, '8023c2ec'],
    ['two8043d138', 1, 2, '8023c328'], ['onePointFive8043d140', 3, 2, '8023c374'],
    ['negativeOne8043d148', 4, -1, '8023c394']] as const) {
    const f = fixture(), run = () => a === 1 ? f.runtime.atanSignedByte(y) : f.runtime.atanAbsoluteRatio(y, a);
    f.data[key] = 0; rejects(run, `${site} ${key}`);
    f.data[key] = NaN; rejects(run, 'decoded source constant');
    Object.defineProperty(f.data, key, {get() {throw Error('getter invoked');}}); rejects(run, 'own data property');
  }
  for (let i = 0; i < 11; i++) {
    const f = fixture(); (f.data.coefficients802b51a8 as number[])[i] = 0;
    rejects(() => f.runtime.atanAbsoluteRatio(1, 2), `coefficients802b51a8[${i}]`);
  }
  for (const key of ['atanHi802b5168', 'atanLo802b5188'] as const) for (let i = 0; i < 4; i++) {
    const f = fixture(); (f.data[key] as number[])[i] = 0;
    const y = [1, 3, 3, 4][i]!, a = [2, 4, 2, -1][i]!;
    rejects(() => f.runtime.atanAbsoluteRatio(y, a), `${key}[${i}]`);
  }
  // Unselected hi/lo slots and array length are not eagerly required.
  {
    const f = fixture(); f.data.atanHi802b5168 = [f.data.atanHi802b5168![0]!];
    f.data.atanLo802b5188 = [f.data.atanLo802b5188![0]!];
    equal(bits(f.runtime.atanAbsoluteRatio(1, 2)), 0x3fddac670561bb4fn, 'only region-zero slots loaded');
    rejects(() => f.runtime.atanSignedByte(1), 'own data property');
  }
  // All controls are lazy, and every reached arithmetic instruction rechecks.
  const polynomial = ['8023c3b4', '8023c3c8', '8023c3d8', '8023c3e4', '8023c3ec', '8023c3f0',
    '8023c3f4', '8023c3f8', '8023c3fc', '8023c400', '8023c404', '8023c408', '8023c40c'];
  for (const [y, a, sites] of [
    [0, 1, ['8023c2f0']],
    [1, -128, ['80239b84', ...polynomial, '8023c414', '8023c418']],
    [1, 2, ['80239b84', '8023c334', '8023c338', '8023c33c', ...polynomial, '8023c428', '8023c43c', '8023c440', '8023c444']],
    [1, 1, ['8023c350', '8023c354', '8023c358', ...polynomial, '8023c428', '8023c43c', '8023c440', '8023c444']],
    [3, 2, ['80239b84', '8023c380', '8023c384', '8023c388', ...polynomial, '8023c428', '8023c43c', '8023c440', '8023c444']],
    [4, -1, ['80239b84', '8023c39c', ...polynomial, '8023c428', '8023c43c', '8023c440', '8023c444']],
  ] as const) for (let stop = 0; stop < sites.length; stop++) {
    const f = fixture(); let reads = 0;
    const processor = new Proxy(f.processor, {getOwnPropertyDescriptor(owner, key) {
      if (key === 'fpscrControl' && reads++ === stop) owner.fpscrControl = 1;
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    const runtime = createSourceInputAtanRuntime({processor, data: f.data});
    rejects(() => a === 1 ? runtime.atanSignedByte(y) : runtime.atanAbsoluteRatio(y, a), sites[stop]!);
    equal(reads, stop + 1, 'stops at first unsupported arithmetic control');
  }
  for (const control of [-1, 2 ** 32, 1.5, NaN, undefined]) {
    const f = fixture(); if (control === undefined) delete f.processor.fpscrControl; else f.processor.fpscrControl = control;
    rejects(() => f.runtime.atanAbsoluteRatio(1, 2), control === undefined ? 'fpscrControl: own data property' : '80239b84 fpscrControl');
  }
  for (const bit of [1, 2, 4, 8, 16, 32, 64, 128]) {
    const f = fixture(); f.processor.fpscrControl = bit; rejects(() => f.runtime.atanSignedByte(0), '8023c2f0');
  }
  {
    const f = fixture(); f.processor.fpscrControl = 0xffffff00;
    equal(f.runtime.atanSignedByte(0), 0, 'FPSCR status bits outside control model');
    equal(f.processor.fpscrControl, 0xffffff00, 'no invented FPSCR writes');
  }
  for (const key of ['processor', 'data'] as const) {
    const f = fixture(); f.sources[key] = {}; rejects(() => f.runtime.atanSignedByte(0), `${key} owner changed`);
  }
  for (const key of ['atanHi802b5168', 'atanLo802b5188', 'coefficients802b51a8'] as const) {
    const f = fixture(); f.runtime.atanAbsoluteRatio(1, 2); f.data[key] = [...f.data[key]!];
    rejects(() => f.runtime.atanAbsoluteRatio(1, 2), `${key}: table owner changed`);
    const bad = fixture(); bad.data[key] = bad.processor as readonly number[];
    rejects(() => bad.runtime.atanSignedByte(0), 'table aliases source owner');
  }
  {
    const f = fixture(); f.data.atanLo802b5188 = f.data.atanHi802b5168!;
    rejects(() => f.runtime.atanSignedByte(0), 'table aliases source owner or another table');
    const shared = {}; rejects(() => createSourceInputAtanRuntime({processor: shared, data: shared}), 'distinct source owners');
    rejects(() => createSourceInputAtanRuntime(Object.create({processor: {}, data: {}}) as SourceInputAtanSources), 'own data property');
    rejects(() => createSourceInputAtanRuntime({processor: Promise.resolve({}) as SourceInputAngleProcessorState, data: {}}), 'synchronous actual record');
  }
  // Interleaved source load/arithmetic sequence, excluding reference-only probes.
  {
    const f = fixture(), events: string[] = [];
    const table = (values: readonly number[], label: string) => new Proxy(values, {getOwnPropertyDescriptor(owner, key) {
      if (/^[0-9]+$/.test(String(key))) events.push(`${label}${String(key)}`);
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    f.data.coefficients802b51a8 = table(f.data.coefficients802b51a8!, 'c');
    f.data.atanHi802b5168 = table(f.data.atanHi802b5168!, 'h'); f.data.atanLo802b5188 = table(f.data.atanLo802b5188!, 'l');
    const processor = new Proxy(f.processor, {getOwnPropertyDescriptor(owner, key) {
      if (key === 'fpscrControl') events.push('op'); return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    const data = new Proxy(f.data, {getOwnPropertyDescriptor(owner, key) {
      if (key === 'one8043d130' || key === 'two8043d138') events.push(String(key));
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    const runtime = createSourceInputAtanRuntime({processor, data}); runtime.atanAbsoluteRatio(1, 2);
    equal(events.join(','), ['op', 'two8043d138', 'one8043d130', 'op', 'op', 'op', 'c10', 'op',
      'c8', 'c6', 'c9', 'c7', 'op', 'c4', 'c5', 'c2', 'op', 'c3', 'c0', 'op', 'c1',
      'op', 'op', 'op', 'op', 'op', 'op', 'op', 'op', 'op', 'op', 'l0', 'h0', 'op', 'op', 'op'].join(','),
    'exact interleaved finite source loads and arithmetic');
  }
  {
    const f = fixture(); let runtime: SourceInputAtanRuntime | undefined, armed = false;
    const processor = new Proxy(f.processor, {getOwnPropertyDescriptor(owner, key) {
      if (armed && key === 'fpscrControl') {try {runtime!.atanSignedByte(0);} catch { /* outer must fail */ }}
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    runtime = createSourceInputAtanRuntime({processor, data: f.data}); armed = true;
    rejects(() => runtime!.atanSignedByte(0), 'caught same-runtime reentry');
    armed = false; equal(runtime.atanSignedByte(0), 0, 'fresh invocation recovers after reentry poison');
  }
  console.log('[source-input-atan] PASS: authenticated finite signed-byte/quotient closure, tiny +0, all reduction regions, fused exact-bit vectors, every reached control/load, lazy constants and retained owners; synthetic offline only');
}
