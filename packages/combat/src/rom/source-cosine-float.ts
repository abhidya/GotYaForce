import {sourceReduceHalfPi} from './source-angle-reduction.js';
import {sourceCosineKernel} from './source-cosine.js';
import {sourceSineKernelTail} from './source-sine.js';

/** Bounded candidate for GG4E cosf/cos at 8023cc68/8023c480. Input and
 * output are float32; the existing reduction handles only |x| < ~3pi/4.
 * This is an offline candidate, not a gameplay or hardware-parity claim. */
export function sourceCosineFloatBounded(x: number): number {
  if (!Number.isFinite(x) || !Object.is(x, Math.fround(x))) throw new RangeError('finite float32 input required');
  const reduced = sourceReduceHalfPi(x);
  const value = reduced.quadrant === 0 ? sourceCosineKernel(reduced.head, reduced.tail)
    : -reduced.quadrant * sourceSineKernelTail(reduced.head, reduced.tail);
  return Math.fround(value);
}
