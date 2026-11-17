/** Bounded source800452a0 ->8023cb78 ->80239984 ->8b73c direction table.
 * Offline actor/return projection only; no production activation or general
 * libm substitute. Evidence: read_archived_angular_axis_evidence.py plus the
 * input-prefix archived caller, not an execution oracle. Inputs are the actual
 * signed8/scale0 converted X/Y (f2/f1): +0 only, not negative zero. The x==1
 * fast atan call80239a04 and non-axis continuation80239a78 refuse by default.
 * Explicit atanRuntime opts into the finite signed-byte closure, not general libm.
 *
 * Constants and direction bytes are caller-owned decoded source data; none are
 * supplied by default. Reached constants must have their authenticated bits.
 * The table's selected byte may change within u8; unselected bytes are not read.
 * Processor/data records and the first reached table retain their identities.
 *
 * HID2[PSE/LSQE]=1, enabled floating-point execution, big-endian source layout
 * and the float GQR0 paired ABI envelope are explicit host preconditions, not
 * captured hardware. Opaque pre-call f31 lanes and all stack/FPR/FPSCR status
 * effects are outside this projection. fpscrControl supplies only controls:
 * RN00 nearest-even, NI0 and all five exception enables off. It is not updated.
 * GQR0 scales are ignored for type0; its store and load types are checked at
 * their respective sites. No claim of preserving opaque f31 denormals is made.
 * Stable synchronous non-proxy own-data records are a host boundary. Caught
 * same-runtime reentry poisons the outer call; no rollback is attempted.
 * Source/manual detail: research/decomp/actor-input-angular-axis-evidence-2026-11-13.md;
 * PowerPC Programming Environments rev1 Tables2-4/3-8 define RN00/ties-even.
 */
import {isSourceInputAtanRuntime, type SourceInputAtanRuntime} from './source-input-atan.js';
import {requireSourceInputFloatPairGqr, storeSourceInputSignedShort} from './source-input-quantized.js';

export interface SourceInputAngleProcessorState {
  gqr0?: number;
  gqr5?: number;
  /** Raw unsigned32 control profile, not a modeled live FPSCR register. */
  fpscrControl?: number;
}
export interface SourceInputAngleData {
  scale8043707c?: number;
  pi8043cd78?: number;
  /** Unreachable with canonical +0 signed8 input; never eagerly required. */
  negativePi8043cd80?: number;
  negativeHalfPi8043cd88?: number;
  halfPi8043cd90?: number;
  piLow8043cdc8?: number;
  direction80433928?: readonly number[];
}
export interface SourceInputAngleSources {
  processor: SourceInputAngleProcessorState;
  data: SourceInputAngleData;
  /** Optional genuine finite atan closure; omission retains historical refusals. */
  atanRuntime?: SourceInputAtanRuntime;
}
export interface SourceInputAngleRuntime {
  getProcessor(): SourceInputAngleProcessorState;
  getData(): SourceInputAngleData;
  getAtanRuntime(): SourceInputAtanRuntime | undefined;
  /** X then Y, after the caller's actual GQR4 conversions. Returns lbzx8b794. */
  direction(x: number, y: number): number;
}
const runtimes = new WeakSet<object>();
export function isSourceInputAngleRuntime(value: unknown): value is SourceInputAngleRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[source-input-angle] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  return property.value;
}
function record(value: unknown, where: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise)
    fail(`${where}: synchronous actual record required`);
  return value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max)
    fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
export function createSourceInputAngleRuntime(sources: SourceInputAngleSources): SourceInputAngleRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const processor = record(read(sources, 'processor'), 'processor') as SourceInputAngleProcessorState;
  const data = record(read(sources, 'data'), 'data') as SourceInputAngleData;
  if (processor === data || processor === sources || data === sources) fail('distinct source owners required');
  const atanProperty = Object.getOwnPropertyDescriptor(sources, 'atanRuntime');
  const atan = atanProperty === undefined ? undefined : read(sources, 'atanRuntime');
  if (atanProperty !== undefined && !isSourceInputAtanRuntime(atan)) fail('atanRuntime requires genuine source runtime');
  const atanRuntime = atan as SourceInputAtanRuntime | undefined;
  if (atanRuntime && atanRuntime.getProcessor() !== processor) fail('atanRuntime requires the same explicit processor owner');
  const atanData = atanRuntime?.getData();
  if (atanData && (atanData === sources || atanData === data || atanData === processor))
    fail('atan data aliases angular source owner');
  let table: object | undefined;
  const independent = (): void => {
    if (!atanData) return;
    const owners: object[] = [sources, processor, data, atanData];
    for (const [owner, keys] of [[data, ['direction80433928']],
      [atanData, ['atanHi802b5168', 'atanLo802b5188', 'coefficients802b51a8']]] as const) {
      for (const key of keys) {
        const property = Object.getOwnPropertyDescriptor(owner, key); check();
        const value: unknown = property && 'value' in property ? property.value : undefined;
        if (value !== null && typeof value === 'object') owners.push(value);
      }
    }
    if (new Set(owners).size !== owners.length) fail('angular/atan source table owner alias');
  };
  const stable = (): void => {
    if (read(sources, 'processor') !== processor) fail('processor owner changed its actual record');
    if (read(sources, 'data') !== data) fail('data owner changed its actual record');
    if (atanProperty !== undefined && read(sources, 'atanRuntime') !== atanRuntime) fail('atanRuntime owner changed its actual runtime');
  };
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {stable(); independent(); const result = run(); stable(); independent(); check(); return result;} finally {busy = false;}
  };
  const control = (key: keyof SourceInputAngleProcessorState, site: string): number => {
    stable();
    return integer(read(processor, key), 0, 0xffffffff, `${site} ${key}`);
  };
  const rounding = (site: string): void => {
    if ((control('fpscrControl', site) & 0xff) !== 0)
      fail(`${site} requires explicit FPSCR RN00/NI0 and disabled floating exception enables`);
  };
  const pair = (operation: 'store' | 'load', site: string): void => {
    const gqr = control('gqr0', site);
    try {requireSourceInputFloatPairGqr(gqr, operation);} catch (error) {fail(`${site}: ${String(error)}`);}
  };
  const scratch = new DataView(new ArrayBuffer(8));
  const constant = (key: keyof SourceInputAngleData, expected: bigint | number, site: string): number => {
    stable(); const value = read(data, key);
    if (typeof value !== 'number' || !Number.isFinite(value)) fail(`${site} ${key}: decoded source constant required`);
    if (typeof expected === 'number') {
      if (!Object.is(value, Math.fround(value))) fail(`${site} ${key}: exact source float32 required`);
      scratch.setFloat32(0, value, false);
      if (scratch.getUint32(0, false) !== expected) fail(`${site} ${key}: authenticated source bits required`);
    } else {
      scratch.setFloat64(0, value, false);
      if (scratch.getBigUint64(0, false) !== expected) fail(`${site} ${key}: authenticated source bits required`);
    }
    return value;
  };
  const runtime: SourceInputAngleRuntime = {
    getProcessor() {return processor;},
    getData() {return data;},
    getAtanRuntime() {return atanRuntime;},
    direction(x, y) {return guard(() => {
      integer(x, -128, 127, 'converted X'); integer(y, -128, 127, 'converted Y');
      if (Object.is(x, -0) || Object.is(y, -0)) fail('signed8/scale0 converted operands require canonical +0');
      pair('store', '800452b0');
      // Source reads f2 as X and f1 as Y. Finite x==1 precedes every axis test.
      let angle: number;
      if (x === 1) {
        if (!atanRuntime) fail('80239a04 reached unsupported source atan call 8023c240');
        angle = atanRuntime.atanSignedByte(y); check();
      } else if (y === 0) {
        angle = x < 0 ? constant('pi8043cd78', 0x400921fb54442d18n, '80239a48') : y;
      } else if (x === 0) {
        angle = y < 0 ? constant('negativeHalfPi8043cd88', 0xbff921fb54442d18n, '80239a68') :
          constant('halfPi8043cd90', 0x3ff921fb54442d18n, '80239a70');
      } else {
        if (!atanRuntime) fail('80239a78 reached unsupported non-axis source atan2 continuation');
        angle = atanRuntime.atanAbsoluteRatio(y, x); check();
        if (x > 0) {if (y < 0) angle = -angle;} // xoris80239bc4, exact sign toggle.
        else {
          // The source loads both constants before either separately rounded
          // fsub. Do not replace this by pi-angle or collapse the two sites.
          const low = constant('piLow8043cdc8', 0x3ca1a62633145c07n, y > 0 ? '80239bd8' : '80239bf0');
          const pi = constant('pi8043cd78', 0x400921fb54442d18n, y > 0 ? '80239bdc' : '80239bf4');
          rounding(y > 0 ? '80239be0' : '80239bf8'); angle = angle - low;
          rounding(y > 0 ? '80239be4' : '80239bfc'); angle = y > 0 ? pi - angle : angle - pi;
        }
      }
      rounding('800452b8'); const roundedAngle = Math.fround(angle); // frsp, one f64 ->f32 rounding.
      const scale = constant('scale8043707c', 0x4622f983, '800452bc');
      rounding('800452c0');
      // Product of two finite f32 values has <=48 significant bits, exactly
      // representable in binary64 in this bounded normal-or-zero signed-byte angular domain.
      const product = Math.fround(scale * roundedAngle);
      const gqr5 = control('gqr5', '800452c4');
      let short: number;
      try {short = storeSourceInputSignedShort(product, gqr5);} catch (error) {fail(`800452c4: ${String(error)}`);}
      pair('load', '800452cc');
      // clrlwi16; addi4096; rlwinm SH19,MB29,ME31, then lbzx.
      const index = (((short & 0xffff) + 4096) >>> 13) & 7;
      stable(); const current = record(read(data, 'direction80433928'), '8008b794 direction table');
      if (current === processor || current === data || current === sources) fail('direction table aliases source owner');
      if (!Array.isArray(current)) fail('8008b794 direction table requires retained own-data array');
      if (table === undefined) table = current;
      else if (table !== current) fail('8008b794 direction table owner changed its actual record');
      return integer(read(current, String(index)), 0, 255, `8008b794 direction table[${index}]`);
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
