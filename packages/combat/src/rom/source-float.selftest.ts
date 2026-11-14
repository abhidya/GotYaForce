import {addSourceFloat32 as add, fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';
const view = new DataView(new ArrayBuffer(8));
function fromBits(bits: number): number { view.setUint32(0, bits); return view.getFloat32(0); }
function toBits(value: number): number { view.setFloat32(0, value); return view.getUint32(0); }
function check(ok: boolean, label: string): void { if (!ok) throw Error(`[source-float] ${label}`); }
function expect(value: number, bits: number, label: string): void { check(toBits(value) === bits, label); }
function rejects(run: () => number, text: string): void {
  let error = ''; try { run(); } catch (e) { error = String(e); }
  check(error.includes(text), `expected ${text}, got ${error}`);
}
// Independent oracle: encode doubles as integer multiples of 2^-1074, then
// binary-search ordered positive f32 bit patterns and compare exact distances.
// Unlike production this never chooses a bit-length, quantum or right-shift tie.
function units(value: number): bigint {
  view.setFloat64(0, value);
  const hi = view.getUint32(0), lo = view.getUint32(4), field = (hi >>> 20) & 2047;
  let integer = BigInt(hi & 0xfffff) * 0x100000000n + BigInt(lo);
  if (field !== 0) integer = (integer + 0x10000000000000n) << BigInt(field - 1);
  return hi >>> 31 ? -integer : integer;
}
function oracle(integer: bigint, scale: number): number {
  const negative = integer < 0n, target = negative ? -integer : integer;
  function candidate(raw: number): bigint {
    // Also permit the hypothetical finite 2^128 endpoint for overflow ties.
    const field = raw >>> 23, fraction = raw & 0x7fffff;
    return BigInt(field ? fraction + 0x800000 : fraction) << BigInt((field ? field - 150 : -149) + scale);
  }
  let low = 0, high = 0x7f800000;
  while (low + 1 < high) {
    const middle = Math.floor((low + high) / 2);
    if (candidate(middle) <= target) low = middle; else high = middle;
  }
  const down = target - candidate(low), up = candidate(high) - target;
  const selected = down < up || (down === up && (low & 1) === 0) ? low : high;
  return selected + (negative ? 0x80000000 : 0);
}
export function runSourceFloatSelfTest(): void {
  // Wider doubles are outside Gekko's guaranteed single-instruction domain,
  // even if a mathematical exact sum could be calculated by the private kernel.
  for (const invalid of [1 + 2 ** -25, 2 ** 24 + .5, 2 ** 80 + 2 ** 56,
    Number.MIN_VALUE, 2 ** -150, Number.MAX_VALUE, .1]) {
    rejects(() => add(invalid, 0), 'finite float32');
    rejects(() => add(0, invalid), 'finite float32');
  }
  // Exact product = 1.5 + 3*2^-24: midpoint between 3fc00001 and 3fc00002.
  // Subtracting minimum subnormal puts it BELOW the midpoint; f64 loses it.
  expect(Math.fround((1 + 2 ** -23) * 1.5 - 2 ** -149), 0x3fc00002, 'old FMA demonstrably ties up');
  expect(fma(1 + 2 ** -23, 1.5, -(2 ** -149)), 0x3fc00001, 'exact FMA below midpoint');
  expect(Math.fround((1 + 2 ** -23) * 1.5 - 2 ** -126), 0x3fc00002, 'old FMA also fails with normal operands');
  expect(fma(1 + 2 ** -23, 1.5, -(2 ** -126)), 0x3fc00001, 'normal-operand exact FMA below midpoint');
  for (let exponent = -125; exponent <= 127; exponent++) {
    const base = 2 ** exponent, half = 2 ** (exponent - 24);
    expect(add(base, half), toBits(base), `even lower midpoint at ${exponent}`);
    expect(add(fromBits(toBits(base) + 1), half), toBits(base) + 2, `even upper midpoint at ${exponent}`);
  }
  expect(fma(-(1 + 2 ** -23), 1.5, 2 ** -149), 0xbfc00001, 'negative FMA midpoint perturbation');
  expect(add(1, 2 ** -24), 0x3f800000, 'even lower tie');
  expect(add(1 + 2 ** -23, 2 ** -24), 0x3f800002, 'even upper tie');
  expect(add(2 - 2 ** -23, 2 ** -24), 0x40000000, 'carry into next exponent');
  expect(fma(2 ** -149, .5, 0), 0, 'subnormal zero tie');
  expect(fma(-(2 ** -149), .5, 0), 0x80000000, 'negative underflow sign');
  expect(fma(3 * 2 ** -149, .5, 0), 2, 'subnormal odd tie');
  expect(fma(-(2 ** -149), .5, 2 ** -126), 0x00800000, 'subnormal carry to normal');
  expect(add(fromBits(0x007fffff), 2 ** -149), 0x00800000, 'subnormal addition to normal');
  expect(add(2 ** -126, -(2 ** -149)), 0x007fffff, 'largest subnormal');
  for (const a of [0, -0]) for (const b of [0, -0]) {
    check(Object.is(add(a, b), a + b), 'addition signed zeros');
    for (const c of [0, -0]) check(Object.is(fma(a, b, c), a * b + c), 'FMA signed zeros');
  }
  expect(fma(-0, 1, -0), 0x80000000, 'negative zero product plus negative zero');
  expect(fma(0, -1, -0), 0x80000000, 'negative multiplier sets zero product sign');
  expect(fma(-0, -1, -0), 0, 'positive zero product plus negative zero');
  expect(add(1, -1), 0, 'exact cancellation positive zero');
  expect(fma(-2, 3, 6), 0, 'FMA exact cancellation positive zero');
  expect(fma(-(2 ** -149), .5, 0), 0x80000000, 'FMA underflow negative zero');
  expect(fma(2 ** -149, .5, 2 ** -149), 2, 'FMA subnormal tie');
  const max = fromBits(0x7f7fffff), overflowHalf = 2 ** 103;
  expect(add(max, overflowHalf - 2 ** 79), 0x7f7fffff, 'immediately below overflow midpoint');
  rejects(() => add(max, overflowHalf), 'overflow');
  rejects(() => add(-max, -overflowHalf), 'overflow');
  expect(add(max, -max), 0, 'binary32 extremes cancel exactly');
  expect(fma(max, 2, -max), 0x7f7fffff, 'fused product overflow cancels before rounding');
  rejects(() => fma(max, 2, 0), 'overflow');
  for (const invalid of [NaN, Infinity, -Infinity]) {
    rejects(() => add(invalid, 0), 'finite'); rejects(() => add(0, invalid), 'finite');
    for (const args of [[invalid, 1, 0], [1, invalid, 0], [1, 1, invalid]]) {
      rejects(() => fma(args[0]!, args[1]!, args[2]!), 'finite float32');
    }
  }
  for (const args of [[.1, 1, 0], [1, .1, 0], [1, 1, .1]]) {
    rejects(() => fma(args[0]!, args[1]!, args[2]!), 'finite float32');
  }
  let seed = 0x49ac4;
  const random = (): number => { seed = (Math.imul(seed, 1664525) + 1013904223) >>> 0; return seed; };
  const randomFloat = (): number => fromBits(random() % 0x7f800000) * (random() >>> 31 ? -1 : 1);
  function compare(run: () => number, expected: number, label: string): void {
    if ((expected & 0x7fffffff) === 0x7f800000) rejects(run, 'overflow');
    else expect(run(), expected, label);
  }
  for (let i = 0; i < 1500; i++) {
    const a = randomFloat(), b = randomFloat();
    compare(() => add(a, b), oracle(units(a) + units(b), 1074), `random exact addition ${i}`);
    const x = randomFloat(), y = randomFloat(), z = randomFloat();
    compare(() => fma(x, y, z), oracle(units(x) * units(y) + (units(z) << 1074n), 2148), `random exact FMA ${i}`);
  }
  console.log('[source-float] PASS: finite-f32 nearest-even add/FMA (RN=00, NI=0 assumptions), independent integer-distance oracle; synthetic arithmetic, not console replay');
}
