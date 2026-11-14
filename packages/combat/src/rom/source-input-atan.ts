/** Bounded source atan8023c240 and its finite atan2 quotient call prefix.
 * Only canonical signed-byte inputs or absolute nonzero signed-byte quotients
 * enter this projection. This proves |argument| in [1/128,128], or +0 for the
 * x==1 fast call. NaN/Inf/huge-input libm branches are deliberately absent.
 * +0 follows the actual huge+zero comparison, not a fabricated polynomial call.
 * Source instruction order, including interleaved constant loads and binary64
 * fmadd/fmsub/fnmsub single rounding, comes from both authenticated archived
 * ProgramDB snapshots: read_archived_angular_finite_evidence.py. Not an oracle.
 *
 * Every source numeric datum is explicitly caller-owned and authenticated at
 * its reached load. Array owners retain identity, while unselected values are
 * not read. Stable synchronous non-proxy own-data records are required; hostile
 * proxy tests only check fail-closed ordering/reentry. No FPSCR status effects,
 * stack/FPR effects, general libm implementation or production activation.
 */
import {fusedMultiplyAddSourceFloat64, fusedMultiplySubtractSourceFloat64,
  negatedFusedMultiplySubtractSourceFloat64} from './source-float64.js';
import type {SourceInputAngleProcessorState} from './source-input-angle.js';

export interface SourceInputAtanData {
  huge8043d128?: number;
  one8043d130?: number;
  two8043d138?: number;
  onePointFive8043d140?: number;
  negativeOne8043d148?: number;
  atanHi802b5168?: readonly number[];
  atanLo802b5188?: readonly number[];
  coefficients802b51a8?: readonly number[];
}
export interface SourceInputAtanSources {
  processor: SourceInputAngleProcessorState;
  data: SourceInputAtanData;
}
export interface SourceInputAtanRuntime {
  getProcessor(): SourceInputAngleProcessorState;
  getData(): SourceInputAtanData;
  /** Actual atan callee for the atan2 x==1 fast path, including y==+0. */
  atanSignedByte(y: number): number;
  /** Actual fdiv80239b84/fabs80239b88 then atan8023c240 for nonzero X/Y. */
  atanAbsoluteRatio(y: number, x: number): number;
}
const runtimes = new WeakSet<object>();
export function isSourceInputAtanRuntime(value: unknown): value is SourceInputAtanRuntime {
  return value !== null && typeof value === 'object' && runtimes.has(value);
}
function fail(reason: string): never {
  throw Error(`[source-input-atan] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(owner: unknown, key: string): unknown {
  if (owner === null || typeof owner !== 'object') fail(`${key}: own data record required`);
  const property = Object.getOwnPropertyDescriptor(owner, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  return property.value;
}
function record(value: unknown, site: string): object {
  if (value === null || typeof value !== 'object' || value instanceof Promise)
    fail(`${site}: synchronous actual record required`);
  return value;
}
function byte(value: number, where: string): void {
  if (!Number.isInteger(value) || value < -128 || value > 127 || Object.is(value, -0))
    fail(`${where}: canonical signed-byte operand required`);
}
// Authentication metadata, never decoded default source values.
const hiBits = [0x3fddac670561bb4fn, 0x3fe921fb54442d18n, 0x3fef730bd281f69bn, 0x3ff921fb54442d18n] as const;
const loBits = [0x3c7a2b7f222f65e2n, 0x3c81a62633145c07n, 0x3c7007887af0cbbdn, 0x3c91a62633145c07n] as const;
const coefficientBits = [0x3fd555555555550dn, 0xbfc999999998ebc4n, 0x3fc24924920083ffn,
  0xbfbc71c6fe231671n, 0x3fb745cdc54c206en, 0xbfb3b0f2af749a6dn, 0x3fb10d66a0d03d51n,
  0xbfadde2d52defd9an, 0x3fa97b4b24760debn, 0xbfa2b4442c6a6c2fn, 0x3f90ad3ae322da11n] as const;
const tableKeys = ['atanHi802b5168', 'atanLo802b5188', 'coefficients802b51a8'] as const;
type TableKey = typeof tableKeys[number];

export function createSourceInputAtanRuntime(sources: SourceInputAtanSources): SourceInputAtanRuntime {
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const read = (owner: unknown, key: string): unknown => {const value = own(owner, key); check(); return value;};
  const processor = record(read(sources, 'processor'), 'processor') as SourceInputAngleProcessorState;
  const data = record(read(sources, 'data'), 'data') as SourceInputAtanData;
  if (processor === data || processor === sources || data === sources) fail('distinct source owners required');
  const retained = new Map<TableKey, object>();
  const stable = (): void => {
    if (read(sources, 'processor') !== processor) fail('processor owner changed its actual record');
    if (read(sources, 'data') !== data) fail('data owner changed its actual record');
  };
  // Reference-only inspection, without requiring absent arrays or selected values.
  const independent = (): void => {
    const owners: object[] = [sources, processor, data];
    for (const key of tableKeys) {
      const property = Object.getOwnPropertyDescriptor(data, key); check();
      const value: unknown = property && 'value' in property ? property.value : undefined;
      if (value !== null && typeof value === 'object') owners.push(value);
    }
    if (new Set(owners).size !== owners.length) fail('atan table aliases source owner or another table');
  };
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {stable(); independent(); const result = run(); stable(); independent(); check(); return result;}
    finally {busy = false;}
  };
  const rounding = (site: string): void => {
    stable(); const value = read(processor, 'fpscrControl');
    if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff)
      fail(`${site} fpscrControl: explicit unsigned32 control required`);
    if ((value & 0xff) !== 0) fail(`${site} requires explicit FPSCR RN00/NI0 and disabled floating exception enables`);
  };
  const arithmetic = (site: string, run: () => number): number => {
    rounding(site); const value = run();
    if (!Number.isFinite(value)) fail(`${site}: finite binary64 result required`);
    return value;
  };
  const scratch = new DataView(new ArrayBuffer(8));
  const authenticated = (value: unknown, expected: bigint, site: string): number => {
    if (typeof value !== 'number' || !Number.isFinite(value)) fail(`${site}: decoded source constant required`);
    scratch.setFloat64(0, value, false);
    if (scratch.getBigUint64(0, false) !== expected) fail(`${site}: authenticated source bits required`);
    return value;
  };
  const constant = (key: keyof SourceInputAtanData, expected: bigint, site: string): number => {
    stable(); return authenticated(read(data, key), expected, `${site} ${key}`);
  };
  const tableAt = (key: TableKey, index: number, expected: readonly bigint[], site: string): number => {
    stable(); const current = record(read(data, key), `${site} ${key}`);
    if (current === sources || current === data || current === processor) fail(`${site} ${key}: table aliases source owner`);
    if (!Array.isArray(current)) fail(`${site} ${key}: retained own-data array required`);
    for (const [otherKey, other] of retained) if (otherKey !== key && current === other)
      fail(`${site} ${key}: table aliases another retained table`);
    const previous = retained.get(key);
    if (previous === undefined) retained.set(key, current);
    else if (current !== previous) fail(`${site} ${key}: table owner changed its actual record`);
    return authenticated(read(current, String(index)), expected[index]!, `${site} ${key}[${index}]`);
  };
  const coefficient = (index: number, site: string): number => tableAt('coefficients802b51a8', index, coefficientBits, site);
  const atan = (argument: number): number => {
    const magnitude = Math.abs(argument);
    if (!(magnitude === 0 || magnitude >= 1 / 128 && magnitude <= 128)) fail('bounded atan argument escaped signed-byte closure');
    // Source high-word thresholds have zero low words, so these comparisons are
    // equivalent for every admitted finite normal-or-zero argument.
    let reduced = argument, region = -1;
    if (magnitude < 0.4375) {
      if (magnitude < 2 ** -29) {
        // In this domain only +0 reaches c2e8..c2fc; no ratio is this tiny.
        const huge = constant('huge8043d128', 0x7e37e43c8800759cn, '8023c2e8');
        const one = constant('one8043d130', 0x3ff0000000000000n, '8023c2ec');
        const sum = arithmetic('8023c2f0', () => huge + argument);
        if (sum > one) return argument; // fcmpo8023c2f4, b8023c2fc.
        fail('authenticated tiny-argument branch did not return');
      }
    } else if (magnitude < 1.1875) {
      if (magnitude < 0.6875) {
        const two = constant('two8043d138', 0x4000000000000000n, '8023c328');
        const one = constant('one8043d130', 0x3ff0000000000000n, '8023c330');
        const denominator = arithmetic('8023c334', () => two + magnitude);
        const numerator = arithmetic('8023c338', () => fusedMultiplySubtractSourceFloat64(two, magnitude, one));
        reduced = arithmetic('8023c33c', () => numerator / denominator); region = 0;
      } else {
        const one = constant('one8043d130', 0x3ff0000000000000n, '8023c348');
        const numerator = arithmetic('8023c350', () => magnitude - one);
        const denominator = arithmetic('8023c354', () => one + magnitude);
        reduced = arithmetic('8023c358', () => numerator / denominator); region = 1;
      }
    } else if (magnitude < 2.4375) {
      const onePointFive = constant('onePointFive8043d140', 0x3ff8000000000000n, '8023c374');
      const one = constant('one8043d130', 0x3ff0000000000000n, '8023c37c');
      const numerator = arithmetic('8023c380', () => magnitude - onePointFive);
      const denominator = arithmetic('8023c384', () => fusedMultiplyAddSourceFloat64(onePointFive, magnitude, one));
      reduced = arithmetic('8023c388', () => numerator / denominator); region = 2;
    } else {
      const negativeOne = constant('negativeOne8043d148', 0xbff0000000000000n, '8023c394');
      reduced = arithmetic('8023c39c', () => negativeOne / magnitude); region = 3;
    }
    // Keep source FPR names and interleaved loads: regrouping Horner evaluation
    // or replacing fused instructions by a*b+c changes rounding and read order.
    const f9 = reduced;
    let f4 = coefficient(10, '8023c3ac');
    const f11 = arithmetic('8023c3b4', () => f9 * f9);
    let f1 = coefficient(8, '8023c3b8');
    let f7 = coefficient(6, '8023c3bc');
    let f3 = coefficient(9, '8023c3c0');
    let f0 = coefficient(7, '8023c3c4');
    const f10 = arithmetic('8023c3c8', () => f11 * f11);
    const f6 = coefficient(4, '8023c3cc');
    let f2 = coefficient(5, '8023c3d0');
    const f5 = coefficient(2, '8023c3d4');
    const f8 = arithmetic('8023c3d8', () => fusedMultiplyAddSourceFloat64(f10, f4, f1));
    f1 = coefficient(3, '8023c3dc');
    f4 = coefficient(0, '8023c3e0');
    f3 = arithmetic('8023c3e4', () => fusedMultiplyAddSourceFloat64(f10, f3, f0));
    f0 = coefficient(1, '8023c3e8');
    f7 = arithmetic('8023c3ec', () => fusedMultiplyAddSourceFloat64(f10, f8, f7));
    f2 = arithmetic('8023c3f0', () => fusedMultiplyAddSourceFloat64(f10, f3, f2));
    f3 = arithmetic('8023c3f4', () => fusedMultiplyAddSourceFloat64(f10, f7, f6));
    f1 = arithmetic('8023c3f8', () => fusedMultiplyAddSourceFloat64(f10, f2, f1));
    f2 = arithmetic('8023c3fc', () => fusedMultiplyAddSourceFloat64(f10, f3, f5));
    f0 = arithmetic('8023c400', () => fusedMultiplyAddSourceFloat64(f10, f1, f0));
    f1 = arithmetic('8023c404', () => fusedMultiplyAddSourceFloat64(f10, f2, f4));
    f2 = arithmetic('8023c408', () => f10 * f0);
    f0 = arithmetic('8023c40c', () => f11 * f1);
    if (region < 0) {
      f0 = arithmetic('8023c414', () => f0 + f2);
      return arithmetic('8023c418', () => negatedFusedMultiplySubtractSourceFloat64(f9, f0, f9));
    }
    f1 = arithmetic('8023c428', () => f0 + f2);
    f0 = tableAt('atanLo802b5188', region, loBits, '8023c42c');
    f2 = tableAt('atanHi802b5168', region, hiBits, '8023c438');
    f0 = arithmetic('8023c43c', () => fusedMultiplySubtractSourceFloat64(f9, f1, f0));
    f0 = arithmetic('8023c440', () => f0 - f9);
    f1 = arithmetic('8023c444', () => f2 - f0);
    return argument < 0 ? -f1 : f1; // fneg8023c44c is exact, not rounded.
  };
  const runtime: SourceInputAtanRuntime = {
    getProcessor() {return processor;},
    getData() {return data;},
    atanSignedByte(y) {return guard(() => {byte(y, 'fast-path Y'); return atan(y);});},
    atanAbsoluteRatio(y, x) {return guard(() => {
      byte(y, 'quotient Y'); byte(x, 'quotient X');
      if (x === 0 || y === 0) fail('quotient requires nonzero signed-byte X/Y');
      if (x === 1) fail('quotient X==1 requires the earlier fast-path atanSignedByte');
      // For this domain high-word exponent difference is in [-7,7], so both
      // source atan2 shortcuts at >60 and (negative X && <-60) are unreachable.
      const quotient = arithmetic('80239b84', () => y / x);
      return atan(Math.abs(quotient)); // fabs80239b88, bl80239b8c.
    });},
  };
  runtimes.add(runtime); return Object.freeze(runtime);
}
