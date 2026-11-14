import {fusedMultiplyAddSourceFloat64 as fma, fusedMultiplySubtractSourceFloat64 as fms,
  negatedFusedMultiplySubtractSourceFloat64 as fnms} from './source-float64.js';

const view = new DataView(new ArrayBuffer(8));
const infinityBits = 0x7ff0000000000000n;
const signBit = 0x8000000000000000n;
function fromBits(raw: bigint): number { view.setBigUint64(0, raw); return view.getFloat64(0); }
function toBits(value: number): bigint { view.setFloat64(0, value); return view.getBigUint64(0); }
function negative(value: number): boolean { return value < 0 || Object.is(value, -0); }
function check(ok: boolean, label: string): void { if (!ok) throw Error(`[source-float64] ${label}`); }
function expect(value: number, raw: bigint, label: string): void {
  check(toBits(value) === raw, `${label}: got ${toBits(value).toString(16)}, expected ${raw.toString(16)}`);
}
function rejects(run: () => number, text: string): void {
  let error = ''; try { run(); } catch (e) { error = String(e); }
  check(error.includes(text), `expected ${text}, got ${error}`);
}

// Independent representation/oracle: every operand is an integer number of
// minimum-subnormal units. Exact products then lie on the fixed 2^-2148 lattice.
// Search ordered binary64 bit patterns and compare integer distances. This does
// not share production's dyadics, significant-bit count, quantum or shift/tie
// rounding. Split 32-bit reads also avoid reusing its binary64 decoder.
function units(value: number): bigint {
  view.setFloat64(0, value);
  const hi = view.getUint32(0), lo = view.getUint32(4);
  const field = (hi >>> 20) & 2047;
  let integer = BigInt(hi & 0xfffff) * 0x100000000n + BigInt(lo);
  if (field !== 0) integer = (integer + 0x10000000000000n) << BigInt(field - 1);
  return hi >>> 31 ? -integer : integer;
}
function oracle(a: number, b: number, c: number): bigint {
  const x = units(a), y = units(b), z = units(c);
  const exact = x * y + (z << 1074n);
  if (exact === 0n) return x * y === 0n && z === 0n &&
    negative(a) !== negative(b) && negative(c) ? signBit : 0n;
  const target = exact < 0n ? -exact : exact;
  function candidate(raw: bigint): bigint {
    // At infinityBits, use the hypothetical finite 2^1024 endpoint so midpoint
    // overflow has the same nearest-even distance rule as finite neighbours.
    const field = Number(raw / 0x10000000000000n);
    const fraction = raw % 0x10000000000000n;
    return (field === 0 ? fraction : fraction + 0x10000000000000n) <<
      BigInt(field === 0 ? 1074 : field + 1073);
  }
  let low = 0n, high = infinityBits;
  while (low + 1n < high) {
    const middle = (low + high) / 2n;
    if (candidate(middle) <= target) low = middle; else high = middle;
  }
  const down = target - candidate(low), up = candidate(high) - target;
  const selected = down < up || (down === up && low % 2n === 0n) ? low : high;
  return selected | (exact < 0n ? signBit : 0n);
}
function compare(run: () => number, expected: bigint, label: string): void {
  if ((expected & ~signBit) === infinityBits) rejects(run, 'overflow');
  else expect(run(), expected, label);
}

export function runSourceFloat64SelfTests(): void {
  const min = Number.MIN_VALUE, minNormal = 2 ** -1022, max = Number.MAX_VALUE;
  const nextOne = 1 + 2 ** -52;
  // Product is 1.5 + 3*2^-53, an odd/even midpoint. The small subtractend
  // changes the correct rounding but is lost after an ordinary host product.
  expect(nextOne * 1.5 - min, 0x3ff8000000000002n, 'separate rounding demonstrably ties up');
  expect(fma(nextOne, 1.5, -min), 0x3ff8000000000001n, 'exact product below midpoint');
  expect(fma(nextOne, 1.5, -minNormal), 0x3ff8000000000001n, 'normal operand below midpoint');
  expect(fma(-nextOne, 1.5, min), 0xbff8000000000001n, 'negative midpoint perturbation');
  expect(fma(nextOne, 1.5, min), 0x3ff8000000000002n, 'above midpoint');
  expect(nextOne * (1 - 2 ** -52) - 1, 0n, 'separate product loses cancellation residual');
  expect(fma(nextOne, 1 - 2 ** -52, -1), toBits(-(2 ** -104)), 'exact cancellation residual');
  expect(fma(1 + 2 ** -27, 1 - 2 ** -27, -1), toBits(-(2 ** -54)), 'half-ulp cancellation');
  expect(fma(max, 2, -max), 0x7fefffffffffffffn, 'product overflow cancels before rounding');
  expect(fma(-max, 2, max), 0xffefffffffffffffn, 'negative product overflow cancels');

  for (let exponent = -1021; exponent <= 1023; exponent++) {
    const base = 2 ** exponent, raw = toBits(base), half = 2 ** (exponent - 53);
    expect(fma(1, base, half), raw, `even lower midpoint at ${exponent}`);
    expect(fma(1, fromBits(raw + 1n), half), raw + 2n, `even upper midpoint at ${exponent}`);
  }
  expect(fma(1, 2 - 2 ** -52, 2 ** -53), toBits(2), 'rounding carry into next exponent');
  for (let low = 0; low < 64; low++) {
    expect(fma((2 * low + 1) * min, .5, 0), BigInt(low + low % 2), `subnormal midpoint ${low}`);
  }
  expect(fma(min, .5, 0), 0n, 'minimum subnormal half rounds to zero');
  expect(fma(min, .5 + 2 ** -53, 0), 1n, 'just above minimum subnormal half');
  expect(fma(min, .5 - 2 ** -54, 0), 0n, 'just below minimum subnormal half');
  expect(fma(-min, .5, 0), signBit, 'negative underflow preserves sign');
  expect(fma(min, min, 0), 0n, 'product far below subnormal range');
  expect(fma(-min, min, -0), signBit, 'negative product far below subnormal range');
  expect(fma(min, .5, min), 2n, 'subnormal addend participates before rounding');
  expect(fma(-min, .5, minNormal), 0x0010000000000000n, 'subnormal-to-normal midpoint carry');
  expect(fma(min, .5, minNormal), 0x0010000000000000n, 'minimum normal even midpoint');
  expect(fma(min, .5, minNormal + min), 0x0010000000000002n, 'minimum normal odd midpoint');
  expect(fma(-min, 1, minNormal), 0x000fffffffffffffn, 'largest subnormal');
  expect(fma(minNormal, minNormal, min), 1n, 'tiny product plus minimum subnormal');

  for (const a of [0, -0]) for (const b of [0, -0, 1, -1]) for (const c of [0, -0]) {
    expect(fma(a, b, c), toBits(a * b + c), 'FMA zero signs');
    expect(fms(a, b, c), toBits(a * b - c), 'FMS zero signs');
    expect(fnms(a, b, c), toBits(-(a * b - c)), 'negated FMS zero signs');
  }
  expect(fma(-2, 3, 6), 0n, 'exact nonzero cancellation is positive zero');
  expect(fms(2, 3, 6), 0n, 'FMS exact cancellation is positive zero');
  expect(fnms(2, 3, 6), signBit, 'negated FMS cancellation negates rounded positive zero');
  expect(fnms(min, .5, 0), signBit, 'negated FMS negates positive underflow zero');
  expect(fnms(-min, .5, 0), 0n, 'negated FMS negates negative underflow zero');
  expect(fms(nextOne, 1.5, min), 0x3ff8000000000001n, 'FMS single rounding');
  expect(fnms(nextOne, 1.5, min), 0xbff8000000000001n, 'negated FMS single rounding');

  const overflowHalf = 2 ** 970;
  expect(fma(max, 1, overflowHalf - 2 ** 917), toBits(max), 'immediately below overflow midpoint');
  expect(fma(-max, 1, -(overflowHalf - 2 ** 917)), toBits(-max), 'negative below overflow midpoint');
  for (const args of [[max, 1, overflowHalf], [-max, 1, -overflowHalf],
    [max, 2, 0], [-max, 2, 0], [max, max, -max], [-max, max, max]]) {
    rejects(() => fma(args[0]!, args[1]!, args[2]!), 'overflow');
  }
  rejects(() => fms(max, 1, -overflowHalf), 'overflow');
  rejects(() => fnms(max, 1, -overflowHalf), 'overflow');
  for (const invalid of [NaN, Infinity, -Infinity]) {
    for (const operation of [fma, fms, fnms]) {
      rejects(() => operation(invalid, 1, 0), 'finite float64');
      rejects(() => operation(1, invalid, 0), 'finite float64');
      rejects(() => operation(1, 1, invalid), 'finite float64');
    }
  }

  let seed = 0x64f0a492;
  const random = (): number => { seed = (Math.imul(seed, 1664525) + 1013904223) >>> 0; return seed; };
  const randomFloat = (): number => fromBits((BigInt(random()) << 32n | BigInt(random())) %
    infinityBits | (random() >>> 31 ? signBit : 0n));
  for (let i = 0; i < 4000; i++) {
    const a = randomFloat(), b = randomFloat(), c = randomFloat();
    compare(() => fma(a, b, c), oracle(a, b, c), `independent random FMA ${i}`);
    compare(() => fms(a, b, c), oracle(a, b, -c), `independent random FMS ${i}`);
    compare(() => fnms(a, b, c), oracle(a, b, -c) ^ signBit, `independent random negated FMS ${i}`);
  }
  // Uniform bit patterns often have a dominant term. These cases instead put
  // the addend at the rounded product to expose all residual product bits.
  for (let i = 0; i < 2000; i++) {
    const a = (1 + random() / 2 ** 32) * 2 ** (random() % 1001 - 500);
    const b = (1 + random() / 2 ** 32) * 2 ** (random() % 1001 - 500);
    const c = -(a * b);
    compare(() => fma(a, b, c), oracle(a, b, c), `independent cancellation FMA ${i}`);
    compare(() => fma(-a, b, -c), oracle(-a, b, -c), `independent negative cancellation FMA ${i}`);
  }
  // Concentrate on the normal/subnormal boundary rather than relying on the
  // small fraction of full-range samples whose product and addend both land here.
  const boundaryFloat = (): number => fromBits((BigInt(random()) << 32n | BigInt(random())) %
    0x0030000000000000n | (random() >>> 31 ? signBit : 0n));
  for (let i = 0; i < 2000; i++) {
    const a = boundaryFloat(), b = .5 + random() / 2 ** 32, c = boundaryFloat();
    compare(() => fma(a, b, c), oracle(a, b, c), `independent subnormal-boundary FMA ${i}`);
    compare(() => fma(a, b, 0), oracle(a, b, 0), `independent underflow product ${i}`);
  }
  console.log('[source-float64] PASS: finite-f64 single-round FMA/FMS/negated FMS under RN=00, NI=0, disabled-trap assumptions; independent integer-distance oracle; synthetic arithmetic, not console replay');
}
