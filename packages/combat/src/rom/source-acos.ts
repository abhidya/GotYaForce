import {fusedMultiplyAddSourceFloat64 as fma, negatedFusedMultiplySubtractSourceFloat64 as fnmsub} from './source-float64.js';
// Horner order and fused instructions from GG4E 80239494..802394e0.
function sourceAcosRatio(z: number): number {
  let p = fma(0.00003479331075960212, z, 0.0007915349942898145);
  p = fma(z, p, -0.04005553450067941);
  p = fma(z, p, 0.20121253213486293);
  p = fma(z, p, -0.3255658186224009);
  p = fma(z, p, 0.16666666666666666);
  let q = fma(0.07703815055590194, z, -0.6882839716054533);
  q = fma(z, q, 2.0209457602335057);
  q = fma(z, q, -2.403394911734414);
  q = fma(z, q, 1);
  return (z * p) / q;
}
/** Bounded transcription of gnt4-__ieee754_acos @ 80239410.
 * Coefficients are binary64 values read from the supplied GG4E DOL data5.
 * Only |x| < 0.5 is transcribed here; the square-root paths remain to port.
 * Fused binary64 steps follow the original instruction order, but output has not yet been compared to retail execution,
 * so this is not a bit-exact or production-parity claim.
 */
export function sourceAcosSmall(x: number): number {
  if (!Number.isFinite(x) || Math.abs(x) >= 0.5) throw new RangeError('sourceAcosSmall requires finite |x| < 0.5');
  const pio2 = 1.5707963267948966;
  if (Math.abs(x) < 2 ** -57) return pio2;
  const z = x * x;
  const ratio = sourceAcosRatio(z);
  return pio2 - (x - fnmsub(x, ratio, 6.123233995736766e-17));
}

/** Positive upper-domain 80239410 candidate. The caller must supply the real
 * frsqrte estimate; no Math.sqrt substitute is used in this implementation.
 * Its binary64 operation rounding still requires comparison with retail. */
export function sourceAcosUpper(x: number, reciprocalSqrtEstimate: (value: number) => number): number {
  if (!Number.isFinite(x) || x < 0.5 || x >= 1) throw new RangeError('sourceAcosUpper requires 0.5 <= x < 1');
  const z = 0.5 * (1 - x);
  let estimate = reciprocalSqrtEstimate(z);
  if (!Number.isFinite(estimate) || estimate <= 0) throw new RangeError('positive finite frsqrte estimate required');
  for (let i = 0; i < 4; i++) {
    const squared = estimate * estimate, half = 0.5 * estimate;
    estimate = half * fnmsub(z, squared, 3);
  }
  const root = z * estimate;
  const bits = new DataView(new ArrayBuffer(8));
  bits.setFloat64(0, root, false); bits.setUint32(4, 0, false);
  const highRoot = bits.getFloat64(0, false);
  const correction = fnmsub(highRoot, highRoot, z) / (root + highRoot);
  return 2 * (highRoot + fma(sourceAcosRatio(z), root, correction));
}

/** 8023cc8c wrapper, restricted to the nonnegative finite float32 dot-product
 * domain used by quaternion blending. The upper path requires an frsqrte owner.
 * This is not yet an execution-verified retail implementation. */
export function sourceAcosFloatNonnegative(x: number, reciprocalSqrtEstimate: (value: number) => number): number {
  if (!Number.isFinite(x) || !Object.is(x, Math.fround(x)) || x < 0 || x > 1) throw new RangeError('float32 dot product in [0, 1] required');
  if (x === 1) return 0;
  return Math.fround(x < 0.5 ? sourceAcosSmall(x) : sourceAcosUpper(x, reciprocalSqrtEstimate));
}
