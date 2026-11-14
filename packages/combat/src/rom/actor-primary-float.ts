/** Internal primary47368 sine-refinement arithmetic, not a shared float API.
 * Only the two admitted sine squares and their normal refinement operands are
 * supported. Assumes binary64 RN=nearest-even; no FPSCR/exception emulation.
 */
const bits = new DataView(new ArrayBuffer(8));
function dyadic(value: number): {coefficient: bigint; exponent: number} {
  bits.setFloat64(0, value, false);
  const raw = bits.getBigUint64(0, false), field = Number((raw >> 52n) & 0x7ffn);
  const magnitude = (1n << 52n) | (raw & ((1n << 52n) - 1n));
  return {coefficient: (raw >> 63n) !== 0n ? -magnitude : magnitude, exponent: field - 1075};
}
function fusedMultiplyAdd64(a: number, b: number, c: number): number {
  // The caller bounds every operand away from zero, subnormal and nonfinite
  // values, and the exact sum is strictly negative and normal. Thus this is
  // deliberately not a general binary64 FMA implementation.
  const x = dyadic(a), y = dyadic(b), z = dyadic(c);
  const productExponent = x.exponent + y.exponent;
  const exponent = Math.min(productExponent, z.exponent);
  const sum = ((x.coefficient * y.coefficient) << BigInt(productExponent - exponent)) +
    (z.coefficient << BigInt(z.exponent - exponent));
  const negative = sum < 0n, magnitude = negative ? -sum : sum;
  const shift = magnitude.toString(2).length - 53;
  let rounded: bigint;
  if (shift <= 0) rounded = magnitude << BigInt(-shift);
  else {
    const distance = BigInt(shift);
    rounded = magnitude >> distance;
    const remainder = magnitude - (rounded << distance), halfway = 1n << (distance - 1n);
    if (remainder > halfway || (remainder === halfway && (rounded & 1n) !== 0n)) rounded++;
  }
  // At most 53 significant bits (or a power-of-two carry) and an admitted
  // normal power-of-two scale: neither conversion nor scaling rounds again.
  const result = Number(rounded) * 2 ** (exponent + shift);
  return negative ? -result : result;
}
/** Actual fnmsub64(s,q,3), used only by the primary sine Newton stages. */
export function primarySineCorrection(squared: number, estimateSquared: number): number {
  if ((squared !== 0.75 && squared !== 0.75 - 2 ** -24) ||
    !Number.isFinite(estimateSquared) || estimateSquared < 1 || estimateSquared > 2) {
    throw Error('[actor-primary-float] outside bounded primary sine refinement domain');
  }
  return -fusedMultiplyAdd64(squared, estimateSquared, -3);
}
