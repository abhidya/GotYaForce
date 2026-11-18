import {fusedMultiplyAddSourceFloat64 as fma, fusedMultiplySubtractSourceFloat64 as fmsub, negatedFusedMultiplySubtractSourceFloat64 as fnmsub} from './source-float64.js';
import {sourceReduceHalfPi} from './source-angle-reduction.js';
import {sourceCosineKernel} from './source-cosine.js';
// Exact Horner/fused order from 8023bfe0..8023bff0.
function sinePolynomial(z: number): number {
  let r = fma(1.58969099521155e-10, z, -0.000000025050760253406863);
  r = fma(z, r, 0.0000027557313707070068);
  r = fma(z, r, -0.0001984126982985795);
  return fma(z, r, 0.00833333333332249);
}
/** Bounded transcription of gnt4-__kernel_sin @ 8023bf8c, direct (iy=0)
 * path. Coefficients are binary64 values from the user-supplied GG4E DOL.
 * Only finite reduced arguments are admitted. PowerPC rounding/retail output
 * have not yet been verified; this candidate is not wired into gameplay.
 */
export function sourceSineKernel(x: number): number {
  if (!Number.isFinite(x) || Math.abs(x) > 0.78539825) throw new RangeError('sourceSineKernel requires a finite reduced argument');
  if (Math.abs(x) < 2 ** -27) return x;
  const z = x * x, v = z * x;
  const r = sinePolynomial(z);
  return fma(v, fma(z, r, -0.16666666666666632), x);
}

/** The same kernel's iy=1 path for an angle-reduction tail. */
export function sourceSineKernelTail(x: number, y: number): number {
  if (!Number.isFinite(x) || !Number.isFinite(y) || Math.abs(x) > 0.78539825) throw new RangeError('finite reduced inputs required');
  if (Math.abs(x) < 2 ** -27) return x;
  const z = x * x, v = z * x;
  const r = sinePolynomial(z);
  const a = fmsub(0.5, y, v * r);
  const b = fmsub(z, a, y);
  return x - fnmsub(-0.16666666666666632, v, b);
}

/** 8023cc44/8023c9e8 bounded to the admitted half-pi reduction.
 * Input/output are float32 at the wrapper boundary. Still a candidate until
 * its operations are compared with the retail execution environment. */
export function sourceSineFloatBounded(x: number): number {
  if (!Number.isFinite(x) || !Object.is(x, Math.fround(x))) throw new RangeError('finite float32 input required');
  const reduced = sourceReduceHalfPi(x);
  const value = reduced.quadrant === 0 ? sourceSineKernel(reduced.head)
    : Math.abs(reduced.quadrant) === 2 ? -sourceSineKernelTail(reduced.head, reduced.tail)
    : reduced.quadrant * sourceCosineKernel(reduced.head, reduced.tail);
  return Math.fround(value);
}
