import {createSourceInputAngleRuntime, isSourceInputAngleRuntime,
  type SourceInputAngleData, type SourceInputAngleProcessorState, type SourceInputAngleRuntime,
  type SourceInputAngleSources} from './source-input-angle.js';
import {createSourceInputAtanRuntime, type SourceInputAtanSources, type SourceInputAtanData} from './source-input-atan.js';
import {sourceInputAtanTestData} from './source-input-atan.selftest.js';
import {loadSourceInputSignedByte, requireSourceInputFloatPairGqr,
  storeSourceInputSignedShort} from './source-input-quantized.js';

function check(ok: boolean, why: string): void {if (!ok) throw Error(`[source-input-angle-test] ${why}`);}
function equal(actual: unknown, expected: unknown, why: string): void {
  check(Object.is(actual, expected), `${why}: got ${String(actual)}, expected ${String(expected)}`);
}
function rejects(run: () => unknown, fragment: string): void {
  let error = ''; try {run();} catch (e) {error = String(e);}
  check(error.includes(fragment), `expected ${fragment}, got ${error || 'success'}`);
}
function decoded(bits: bigint | number): number {
  const view = new DataView(new ArrayBuffer(8));
  if (typeof bits === 'number') {view.setUint32(0, bits, false); return view.getFloat32(0, false);}
  view.setBigUint64(0, bits, false); return view.getFloat64(0, false);
}
// This is explicit test evidence, not production defaults or host hardware state.
function fixture() {
  const processor: SourceInputAngleProcessorState = {gqr0: 0, gqr5: 7, fpscrControl: 0};
  const table = [2, 10, 8, 9, 1, 5, 4, 6];
  const data: SourceInputAngleData = {scale8043707c: decoded(0x4622f983),
    pi8043cd78: decoded(0x400921fb54442d18n), negativePi8043cd80: decoded(0xc00921fb54442d18n),
    negativeHalfPi8043cd88: decoded(0xbff921fb54442d18n), halfPi8043cd90: decoded(0x3ff921fb54442d18n),
    direction80433928: table};
  const sources: SourceInputAngleSources = {processor, data}, runtime = createSourceInputAngleRuntime(sources);
  return {processor, table, data, sources, runtime};
}
function finiteFixture() {
  const x = fixture(), atanData = sourceInputAtanTestData();
  const atanSources: SourceInputAtanSources = {processor: x.processor, data: atanData};
  const atanRuntime = createSourceInputAtanRuntime(atanSources);
  x.sources.atanRuntime = atanRuntime; x.data.piLow8043cdc8 = decoded(0x3ca1a62633145c07n);
  return {...x, atanData, atanSources, atanRuntime, runtime: createSourceInputAngleRuntime(x.sources)};
}
export function runSourceInputAngleSelfTests(): void {
  {
    const x = fixture();
    check(isSourceInputAngleRuntime(x.runtime) && !isSourceInputAngleRuntime({...x.runtime}) &&
      !isSourceInputAngleRuntime(null), 'genuine identity brand');
    check(Object.isFrozen(x.runtime), 'frozen runtime methods');
    check(x.runtime.getData() === x.data && x.runtime.getProcessor() === x.processor, 'retains actual owners');
    check(!Object.isFrozen(x.data) && !Object.isFrozen(x.processor) && !Object.isFrozen(x.table), 'does not freeze owned data');
    const atan = Math.atan, atan2 = Math.atan2;
    Math.atan = () => {throw Error('host atan forbidden');};
    Math.atan2 = () => {throw Error('host atan2 forbidden');};
    try {
      // Entire converted-input square, including zero: exactly510 supported
      // axis pairs. Every x1 pair refuses its earlier source fast-atan call.
      let admitted = 0;
      for (let a = -128; a <= 127; a++) for (let b = -128; b <= 127; b++) {
        const sx = loadSourceInputSignedByte(a, 0x60000)[0], sy = loadSourceInputSignedByte(b, 0x60000)[0];
        if (a === 1) rejects(() => x.runtime.direction(sx, sy), '80239a04');
        else if (a !== 0 && b !== 0) rejects(() => x.runtime.direction(sx, sy), '80239a78');
        else {
          equal(x.runtime.direction(sx, sy), b === 0 ? (a < 0 ? 1 : 2) : b < 0 ? 4 : 8, `axis${a}/${b}`);
          admitted++;
        }
      }
      equal(admitted, 510, 'all and only bounded source axes');
    } finally {Math.atan = atan; Math.atan2 = atan2;}
    x.table[0] = 173; equal(x.runtime.direction(52, 0), 173, 'retained selected byte mutates without copy');
    x.table[4] = 255; equal(x.runtime.direction(-52, 0), 255, 'all u8 table results retained');
  }
  // Authenticated one-round values and psq_st signed16 saturation, NOT extsh.
  const pi = decoded(0x400921fb54442d18n), scale = decoded(0x4622f983);
  equal(Math.fround(Math.fround(pi) * scale), 32768, '+pi product before saturation');
  equal(Math.fround(Math.fround(-pi) * scale), -32768, '-pi product before saturation');
  equal(Math.fround(Math.fround(pi / 2) * scale), 16384, '+halfpi product');
  equal(Math.fround(Math.fround(-pi / 2) * scale), -16384, '-halfpi product');
  for (let value = -40000; value <= 40000; value++)
    equal(storeSourceInputSignedShort(value, 7), Math.max(-32768, Math.min(32767, value)), `signed16 quantizer/${value}`);
  for (const [value, expected] of [[32768, 32767], [-32769, -32768], [32767.75, 32767],
    [-32767.75, -32767], [1.75, 1], [-1.75, -1], [-0, 0], [-0.75, 0]] as const)
    equal(storeSourceInputSignedShort(value, 7), expected, `truncation/saturation/${value}`);
  for (const value of [NaN, Infinity, -Infinity, 0.1])
    rejects(() => storeSourceInputSignedShort(value, 7), 'finite exact binary32');
  for (const gqr of [-1, 2 ** 32, NaN, 1.5]) {
    rejects(() => storeSourceInputSignedShort(0, gqr), 'unsigned32 GQR5');
    rejects(() => requireSourceInputFloatPairGqr(gqr, 'store'), 'unsigned32 GQR0');
  }
  rejects(() => requireSourceInputFloatPairGqr(0, 'invalid' as 'load'), 'store/load operation required');
  for (let type = 0; type < 8; type++) if (type !== 7)
    rejects(() => storeSourceInputSignedShort(0, type), 'signed16 store type7');
  for (let scaleField = 1; scaleField < 64; scaleField++)
    rejects(() => storeSourceInputSignedShort(0, (scaleField << 8) | 7), 'scale0');
  equal(storeSourceInputSignedShort(32768, 0xffffc0ff), 32767, 'GQR5 load/reserved fields ignored');
  for (let scaleField = 0; scaleField < 64; scaleField++) {
    const gqr0 = ((scaleField << 24) | (scaleField << 8)) >>> 0;
    requireSourceInputFloatPairGqr(gqr0, 'store'); requireSourceInputFloatPairGqr(gqr0, 'load');
  }
  for (let type = 1; type < 8; type++) {
    rejects(() => requireSourceInputFloatPairGqr(type, 'store'), 'float store type0');
    rejects(() => requireSourceInputFloatPairGqr(type << 16, 'load'), 'float load type0');
    requireSourceInputFloatPairGqr(type, 'load'); requireSourceInputFloatPairGqr(type << 16, 'store');
  }
  // All data and processor fields are demanded only at their reached sites.
  {
    const x = fixture(); delete x.data.pi8043cd78; delete x.data.negativePi8043cd80;
    delete x.data.negativeHalfPi8043cd88; delete x.data.halfPi8043cd90;
    equal(x.runtime.direction(52, 0), 2, 'positive x has no pi constant load');
    rejects(() => x.runtime.direction(-52, 0), 'pi8043cd78');
    rejects(() => x.runtime.direction(0, -52), 'negativeHalfPi8043cd88');
    rejects(() => x.runtime.direction(0, 52), 'halfPi8043cd90');
  }
  {
    const processor: SourceInputAngleProcessorState = {gqr0: 0}, data = {};
    const runtime = createSourceInputAngleRuntime({processor, data});
    rejects(() => runtime.direction(1, 0), '80239a04');
    rejects(() => runtime.direction(52, 52), '80239a78');
    rejects(() => runtime.direction(52, 0), 'fpscrControl');
    delete processor.gqr0; rejects(() => runtime.direction(1, 0), 'gqr0');
  }
  for (const [key, a, b, site] of [['pi8043cd78', -52, 0, '80239a48'],
    ['negativeHalfPi8043cd88', 0, -52, '80239a68'], ['halfPi8043cd90', 0, 52, '80239a70'],
    ['scale8043707c', 52, 0, '800452bc']] as const) {
    const x = fixture(); x.data[key] = 0; rejects(() => x.runtime.direction(a, b), site);
    x.data[key] = NaN; rejects(() => x.runtime.direction(a, b), 'decoded source constant');
    Object.defineProperty(x.data, key, {get() {throw Error('accessor invoked');}});
    rejects(() => x.runtime.direction(a, b), 'own data property');
  }
  for (const bit of [1, 2, 4, 8, 16, 32, 64, 128]) {
    const x = fixture(); x.processor.fpscrControl = bit;
    rejects(() => x.runtime.direction(52, 0), '800452b8');
  }
  {
    const x = fixture(); x.processor.fpscrControl = 0xffffff00;
    equal(x.runtime.direction(-52, 0), 1, 'status bits are outside control-only model');
    equal(x.processor.fpscrControl, 0xffffff00, 'no fabricated live FPSCR status writes');
  }
  {
    const x = fixture(); x.processor.gqr0 = 0x70000; delete x.data.direction80433928;
    rejects(() => x.runtime.direction(52, 0), '800452cc'); // Valid spill, invalid later reload.
    delete x.processor.gqr5; rejects(() => x.runtime.direction(52, 0), 'gqr5');
    x.processor.gqr0 = 7; rejects(() => x.runtime.direction(52, 0), '800452b0');
  }
  for (const value of [-129, 128, -0.5, NaN, Infinity, -Infinity]) {
    const x = fixture(); rejects(() => x.runtime.direction(value, 0), 'converted X');
    rejects(() => x.runtime.direction(0, value), 'converted Y');
  }
  {
    const x = fixture(); rejects(() => x.runtime.direction(-0, 52), 'canonical +0');
    rejects(() => x.runtime.direction(52, -0), 'canonical +0');
  }
  // Only the selected table byte is loaded, including holes and bad values.
  {
    const x = fixture(); x.table.length = 1; equal(x.runtime.direction(52, 0), 2, 'table holes not eagerly touched');
    rejects(() => x.runtime.direction(0, 52), 'own data property');
    Object.defineProperty(x.table, '2', {get() {throw Error('unreached table getter');}, configurable: true});
    equal(x.runtime.direction(52, 0), 2, 'unselected accessor not invoked');
    rejects(() => x.runtime.direction(0, 52), 'own data property');
    x.table[0] = 256; rejects(() => x.runtime.direction(52, 0), 'integer out of bounds');
  }
  {
    const x = fixture(); equal(x.runtime.direction(52, 0), 2, 'capture first reached table');
    x.data.direction80433928 = [...x.table]; rejects(() => x.runtime.direction(52, 0), 'table owner changed');
    x.data.direction80433928 = x.table; equal(x.runtime.direction(52, 0), 2, 'same owner restored');
  }
  for (const owner of ['processor', 'data'] as const) {
    const x = fixture(); x.sources[owner] = {}; rejects(() => x.runtime.direction(52, 0), `${owner} owner changed`);
  }
  {
    const shared = {}; rejects(() => createSourceInputAngleRuntime({processor: shared, data: shared}), 'distinct source owners');
    rejects(() => createSourceInputAngleRuntime(Object.create({processor: {}, data: {}}) as SourceInputAngleSources), 'own data property');
    rejects(() => createSourceInputAngleRuntime({processor: Promise.resolve({}) as SourceInputAngleProcessorState, data: {}}), 'synchronous actual record');
  }
  // Descriptor probes stand in for hostile out-of-domain proxies solely to
  // test observation order and swallowed-reentry poisoning, never as support.
  {
    const x = fixture(), reads: string[] = [];
    const observe = <T extends object>(target: T, label: string): T => new Proxy(target, {
      getOwnPropertyDescriptor(owner, key) {reads.push(`${label}.${String(key)}`); return Reflect.getOwnPropertyDescriptor(owner, key);},
    });
    x.data.direction80433928 = observe(x.table, 'table');
    const runtime = createSourceInputAngleRuntime({processor: observe(x.processor, 'processor'), data: observe(x.data, 'data')});
    reads.length = 0; equal(runtime.direction(-52, 0), 1, 'traced axis');
    equal(reads.join(','), 'processor.gqr0,data.pi8043cd78,processor.fpscrControl,data.scale8043707c,processor.fpscrControl,processor.gqr5,processor.gqr0,data.direction80433928,table.4', 'exact reached field read order');
  }
  {
    const x = fixture(); let reads = 0;
    const processor = new Proxy(x.processor, {getOwnPropertyDescriptor(owner, key) {
      if (key === 'fpscrControl' && ++reads === 2) owner.fpscrControl = 1;
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    const runtime = createSourceInputAngleRuntime({processor, data: x.data});
    rejects(() => runtime.direction(52, 0), '800452c0');
  }
  {
    const x = fixture();
    x.data.direction80433928 = new Proxy(x.table, {getOwnPropertyDescriptor(owner, key) {
      if (key === '0') x.sources.processor = {};
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    rejects(() => x.runtime.direction(52, 0), 'processor owner changed');
  }
  {
    const x = fixture(); let runtime: SourceInputAngleRuntime | undefined, armed = false;
    const processor = new Proxy(x.processor, {getOwnPropertyDescriptor(owner, key) {
      if (armed && key === 'gqr0') {try {runtime!.direction(52, 0);} catch { /* outer must fail */ }}
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    runtime = createSourceInputAngleRuntime({processor, data: x.data}); armed = true;
    rejects(() => runtime!.direction(52, 0), 'caught same-runtime reentry');
    armed = false; equal(runtime.direction(52, 0), 2, 'new call can recover after poisoned invocation');
  }
  // Opt-in closure leaves the historical axis-only fixture and its refusals
  // above intact. Numeric direction-bin comparison is independent host libm
  // test evidence, NOT an execution oracle for source binary64 arithmetic.
  {
    const x = finiteFixture(), expected: number[] = [], scale = decoded(0x4622f983);
    equal(x.runtime.getAtanRuntime(), x.atanRuntime, 'retains genuine opt-in atan runtime');
    equal(fixture().runtime.getAtanRuntime(), undefined, 'default remains axis-only');
    for (let a = -128; a <= 127; a++) for (let b = -128; b <= 127; b++) {
      const product = Math.fround(Math.fround(Math.atan2(b, a)) * scale);
      const short = Math.trunc(Math.max(-32768, Math.min(32767, product)));
      expected.push(x.table[(((short & 0xffff) + 4096) >>> 13) & 7]!);
    }
    const atan = Math.atan, atan2 = Math.atan2;
    Math.atan = () => {throw Error('host atan forbidden');}; Math.atan2 = () => {throw Error('host atan2 forbidden');};
    try {
      let i = 0;
      for (let a = -128; a <= 127; a++) for (let b = -128; b <= 127; b++)
        equal(x.runtime.direction(a, b), expected[i++], `complete finite direction/${a}/${b}`);
      equal(i, 65536, 'all canonical signed-byte pairs execute with explicit finite closure');
    } finally {Math.atan = atan; Math.atan2 = atan2;}
    const vectors = [[52, 0], [52, 52], [0, 52], [-52, 52], [-52, 0], [-52, -52], [0, -52], [52, -52]];
    for (let i = 0; i < 8; i++) {
      x.table[i] = 170 + i;
      equal(x.runtime.direction(vectors[i]![0]!, vectors[i]![1]!), 170 + i, `all selected mutable-u8 directions/${i}`);
    }
  }
  {
    const x = fixture();
    rejects(() => createSourceInputAngleRuntime({...x.sources, atanRuntime: {...createSourceInputAtanRuntime({processor: x.processor, data: {}})}}), 'genuine source runtime');
    rejects(() => createSourceInputAngleRuntime({...x.sources, atanRuntime: undefined} as unknown as SourceInputAngleSources), 'genuine source runtime');
    rejects(() => createSourceInputAngleRuntime({...x.sources, atanRuntime: createSourceInputAtanRuntime({processor: {}, data: {}})}), 'same explicit processor');
    rejects(() => createSourceInputAngleRuntime({...x.sources, atanRuntime: createSourceInputAtanRuntime({processor: x.processor, data: x.data as unknown as SourceInputAtanData})}), 'atan data aliases');
  }
  // Supplying an opt-in closure does not demand its constants on actual axes.
  {
    const x = fixture(), atanRuntime = createSourceInputAtanRuntime({processor: x.processor, data: {}});
    const runtime = createSourceInputAngleRuntime({...x.sources, atanRuntime});
    equal(runtime.direction(2, 0), 2, 'positive axis with empty atan data');
    equal(runtime.direction(-2, 0), 1, 'negative axis with empty atan data');
    equal(runtime.direction(0, 2), 8, 'vertical axis with empty atan data');
    rejects(() => runtime.direction(1, 0), 'huge8043d128');
    rejects(() => runtime.direction(2, 1), 'two8043d138');
  }
  {
    const x = finiteFixture(); delete x.data.piLow8043cdc8; delete x.data.pi8043cd78;
    equal(x.runtime.direction(2, 1), 10, 'positive X never loads quadrant constants');
    equal(x.runtime.direction(1, -128), 4, 'fast atan signs do not load quadrant constants');
    rejects(() => x.runtime.direction(-2, 1), 'piLow8043cdc8');
    rejects(() => x.runtime.direction(-2, -1), 'piLow8043cdc8');
    x.data.piLow8043cdc8 = decoded(0x3ca1a62633145c07n);
    rejects(() => x.runtime.direction(-2, 1), 'pi8043cd78');
  }
  for (const y of [-1, 1]) {
    const x = finiteFixture(); x.data.piLow8043cdc8 = 0;
    rejects(() => x.runtime.direction(-2, y), y > 0 ? '80239bd8' : '80239bf0');
    x.data.piLow8043cdc8 = decoded(0x3ca1a62633145c07n); x.data.pi8043cd78 = 0;
    rejects(() => x.runtime.direction(-2, y), y > 0 ? '80239bdc' : '80239bf4');
    const f = finiteFixture(); let armed = false, after = 0;
    const data = new Proxy(f.data, {getOwnPropertyDescriptor(owner, key) {
      if (key === 'piLow8043cdc8') armed = true;
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    const processor = new Proxy(f.processor, {getOwnPropertyDescriptor(owner, key) {
      if (armed && key === 'fpscrControl' && ++after === 2) owner.fpscrControl = 1;
      return Reflect.getOwnPropertyDescriptor(owner, key);
    }});
    const atanRuntime = createSourceInputAtanRuntime({processor, data: f.atanData});
    const runtime = createSourceInputAngleRuntime({processor, data, atanRuntime});
    rejects(() => runtime.direction(-2, y), y > 0 ? '80239be4' : '80239bfc');
    equal(after, 2, 'separate quadrant correction arithmetic controls');
  }
  {
    const x = finiteFixture(); x.sources.atanRuntime = createSourceInputAtanRuntime({processor: x.processor, data: sourceInputAtanTestData()});
    rejects(() => x.runtime.direction(2, 1), 'atanRuntime owner changed');
    x.sources.atanRuntime = x.atanRuntime; x.atanSources.data = {};
    rejects(() => x.runtime.direction(2, 1), 'data owner changed');
  }
  for (const key of ['atanHi802b5168', 'atanLo802b5188', 'coefficients802b51a8'] as const) {
    const x = finiteFixture(); x.atanData[key] = x.table;
    rejects(() => x.runtime.direction(2, 0), 'angular/atan source table owner alias');
  }
  // Source +0 fast path returns before polynomial reads, yet real huge+zero
  // arithmetic is still required before the final caller frsp/fmuls sequence.
  {
    const x = finiteFixture(); delete x.atanData.coefficients802b51a8;
    delete x.atanData.atanHi802b5168; delete x.atanData.atanLo802b5188;
    equal(x.runtime.direction(1, 0), 2, 'actual fast atan tiny return projects east');
    delete x.atanData.huge8043d128;
    rejects(() => x.runtime.direction(1, 0), 'huge8043d128');
  }
  console.log('[source-input-angle] PASS: historical510 axes/refusals unchanged; opt-in all65536 signed-byte pairs, exact source finite atan integration/quadrants, lazy constants/controls, shared owners, GQR0/GQR5 and selected mutable-u8 directions; synthetic offline only');
}
