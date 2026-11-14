/** Bounded, single-round IEEE binary64 fused arithmetic for audited source sites.
 * Requires finite binary64 operands, FPSCR RN=00 (nearest-even), NI=0 (gradual
 * underflow) and disabled exception traps. Callers must validate those control
 * preconditions; this helper neither observes nor changes FPSCR status.
 * Products and sums stay exact until one binary64 rounding. Signed zero and
 * gradual underflow are preserved; a rounded infinite result is refused.
 * NaN/Infinity inputs, other rounding modes, exception/status emulation and
 * non-IEEE execution are outside this domain. This is not console evidence.
 */
interface Dyadic64 { coefficient: bigint; exponent: number; negative: boolean }
const view = new DataView(new ArrayBuffer(8));
const signBit = 1n << 63n;
const hiddenBit = 1n << 52n;

function decompose(value: number): Dyadic64 {
  if (!Number.isFinite(value)) throw Error('[source-float64] expected finite float64 operand');
  view.setFloat64(0, value, false);
  const raw = view.getBigUint64(0, false);
  const negative = (raw & signBit) !== 0n;
  const field = Number((raw >> 52n) & 0x7ffn);
  const fraction = raw & (hiddenBit - 1n);
  const magnitude = field === 0 ? fraction : hiddenBit | fraction;
  return {coefficient: negative ? -magnitude : magnitude,
    exponent: field === 0 ? -1074 : field - 1075, negative};
}

function roundSum(a: Dyadic64, b: Dyadic64): number {
  const exponent = Math.min(a.exponent, b.exponent);
  const sum = (a.coefficient << BigInt(a.exponent - exponent)) +
    (b.coefficient << BigInt(b.exponent - exponent));
  // RN-even exact cancellation is +0. Two negative zero terms retain -0.
  if (sum === 0n) return a.coefficient === 0n && b.coefficient === 0n && a.negative && b.negative ? -0 : 0;
  const negative = sum < 0n;
  const magnitude = negative ? -sum : sum;
  const topExponent = magnitude.toString(2).length - 1 + exponent;
  let quantum = Math.max(-1074, topExponent - 52);
  const shift = quantum - exponent;
  let rounded: bigint;
  if (shift <= 0) rounded = magnitude << BigInt(-shift);
  else {
    const distance = BigInt(shift);
    rounded = magnitude >> distance;
    const remainder = magnitude - (rounded << distance);
    const halfway = 1n << (distance - 1n);
    if (remainder > halfway || (remainder === halfway && (rounded & 1n) !== 0n)) rounded++;
  }
  // The only 54-bit result is a rounding carry, exactly 2^53.
  if (rounded === (hiddenBit << 1n)) { rounded >>= 1n; quantum++; }
  let raw: bigint;
  if (rounded < hiddenBit) raw = rounded; // Subnormal (including rounded zero).
  else {
    const field = quantum + 1075;
    if (field >= 0x7ff) throw Error('[source-float64] overflow float64 result');
    raw = (BigInt(field) << 52n) | (rounded - hiddenBit);
  }
  // Encode the rounded bits directly: no host multiply can round again, flush
  // a subnormal, or overflow a power-of-two intermediate during reconstruction.
  view.setBigUint64(0, raw | (negative ? signBit : 0n), false);
  return view.getFloat64(0, false);
}

/** One binary64 rounding of the exact a*b+c, not the host's rounded a*b plus c. */
export function fusedMultiplyAddSourceFloat64(a: number, b: number, c: number): number {
  const x = decompose(a), y = decompose(b), z = decompose(c);
  return roundSum({coefficient: x.coefficient * y.coefficient,
    exponent: x.exponent + y.exponent, negative: x.negative !== y.negative}, z);
}

/** One binary64 rounding of exact a*b-c; negating a finite operand is exact. */
export function fusedMultiplySubtractSourceFloat64(a: number, b: number, c: number): number {
  return fusedMultiplyAddSourceFloat64(a, b, -c);
}

/** Negate AFTER rounding a*b-c, including +0 from exact cancellation. */
export function negatedFusedMultiplySubtractSourceFloat64(a: number, b: number, c: number): number {
  return -fusedMultiplySubtractSourceFloat64(a, b, c);
}
