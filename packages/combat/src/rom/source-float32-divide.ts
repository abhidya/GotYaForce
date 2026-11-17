// Shared finite RN00/NI0 float32 division used by animation setup and slerp.
function fail(reason: string): never {throw Error(`[actor-animation-transition] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: finite exact source float32 required`);
  return value;
}
const bits = new DataView(new ArrayBuffer(4));
function dyadic(value: number): {mantissa: bigint; exponent: number; negative: boolean} {
  float(value, 'fdivs operand'); bits.setFloat32(0, value, false);
  const raw = bits.getUint32(0, false), e = (raw >>> 23) & 255;
  return {mantissa: BigInt((raw & 0x7fffff) | (e === 0 ? 0 : 0x800000)),
    exponent: e === 0 ? -149 : e - 150, negative: (raw >>> 31) !== 0};
}
/** Internal exact rational RN00/NI0 fdivs shared with mode1 setup. */
export function divideSourceAnimationFloat32(a: number, b: number): number {
  const x = dyadic(a), y = dyadic(b), negative = x.negative !== y.negative;
  if (y.mantissa === 0n) fail('fdivs zero divisor outside finite domain');
  if (x.mantissa === 0n) return negative ? -0 : 0;
  let power = x.mantissa.toString(2).length - y.mantissa.toString(2).length;
  if (power >= 0 ? x.mantissa < (y.mantissa << BigInt(power)) : (x.mantissa << BigInt(-power)) < y.mantissa) power--;
  const exponent = x.exponent - y.exponent, quantum = Math.max(-149, power + exponent - 23), shift = exponent - quantum;
  const numerator = shift >= 0 ? x.mantissa << BigInt(shift) : x.mantissa;
  const denominator = shift < 0 ? y.mantissa << BigInt(-shift) : y.mantissa;
  let rounded = numerator / denominator;
  const twice = (numerator % denominator) * 2n;
  if (twice > denominator || (twice === denominator && (rounded & 1n) !== 0n)) rounded++;
  return float((negative ? -1 : 1) * Number(rounded) * 2 ** quantum, 'fdivs result');
}
