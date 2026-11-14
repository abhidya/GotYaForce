/** Bounded IEEE nearest-even arithmetic for audited source single-round sites.
 * Both operations require finite binary32 operands (Gekko manual §2.2.3).
 * Assumes FPSCR RN=00 (nearest-even), NI=0 (gradual underflow); these are
 * model preconditions, NOT an observed runtime FPSCR configuration.
 * Exact integer arithmetic avoids a binary64 intermediate rounding before f32.
 * Gradual underflow and signed zero are preserved; nonfinite inputs and rounded
 * overflow throw. This does NOT emulate arbitrary PPC FPSCR modes/exceptions,
 * NaN payloads, non-IEEE modes or console execution. Callers retain store order.
 */
interface Dyadic { coefficient: bigint; exponent: number; negative: boolean }
const bits = new DataView(new ArrayBuffer(8));
function decompose(value: number): Dyadic {
  if (!Number.isFinite(value)) throw Error('[source-float] expected finite operand');
  bits.setFloat64(0, value, false);
  const raw = bits.getBigUint64(0, false), negative = (raw >> 63n) !== 0n;
  const field = Number((raw >> 52n) & 0x7ffn);
  const fraction = raw & ((1n << 52n) - 1n);
  const magnitude = field === 0 ? fraction : (1n << 52n) | fraction;
  return {coefficient: negative ? -magnitude : magnitude,
    exponent: field === 0 ? -1074 : field - 1023 - 52, negative};
}
function roundSum(a: Dyadic, b: Dyadic): number {
  const exponent = Math.min(a.exponent, b.exponent);
  const sum = (a.coefficient << BigInt(a.exponent - exponent)) +
    (b.coefficient << BigInt(b.exponent - exponent));
  // Under nearest-even exact cancellation is +0. Only -0 + -0 is -0.
  if (sum === 0n) return a.coefficient === 0n && b.coefficient === 0n && a.negative && b.negative ? -0 : 0;
  const negative = sum < 0n, magnitude = negative ? -sum : sum;
  const topExponent = magnitude.toString(2).length - 1 + exponent;
  const quantum = Math.max(-149, topExponent - 23);
  const shift = quantum - exponent;
  let rounded: bigint;
  if (shift <= 0) rounded = magnitude << BigInt(-shift);
  else {
    const distance = BigInt(shift);
    rounded = magnitude >> distance;
    const remainder = magnitude - (rounded << distance), halfway = 1n << (distance - 1n);
    if (remainder > halfway || (remainder === halfway && (rounded & 1n) !== 0n)) rounded++;
  }
  // At most 25 significant bits (including a rounding carry); multiplication is
  // exact in binary64 across the entire finite binary32 range, including zeros.
  const result = Number(rounded) * 2 ** quantum;
  if (!Number.isFinite(result) || result > (2 - 2 ** -23) * 2 ** 127) {
    throw Error('[source-float] overflow float32 result');
  }
  return negative ? -result : result;
}
function requireFloat32(value: number): void {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value))) {
    throw Error('[source-float] expected finite float32 operand');
  }
}
/** One f32 rounding of the exact sum; operands must already be finite f32. */
export function addSourceFloat32(a: number, b: number): number {
  requireFloat32(a); requireFloat32(b);
  return roundSum(decompose(a), decompose(b));
}
/** One f32 rounding of exact a*b+c; operands must already be finite f32. */
export function fusedMultiplyAddSourceFloat32(a: number, b: number, c: number): number {
  requireFloat32(a); requireFloat32(b); requireFloat32(c);
  const x = decompose(a), y = decompose(b), z = decompose(c);
  return roundSum({coefficient: x.coefficient * y.coefficient,
    exponent: x.exponent + y.exponent, negative: x.negative !== y.negative}, z);
}
