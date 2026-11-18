import {sourceReduceHalfPi} from './source-angle-reduction.js';
import {sourceSineKernel, sourceSineKernelTail} from './source-sine.js';
import {sourceCosineKernel} from './source-cosine.js';
export function runSourceAngleReductionSelfTest(): void {
  for (let i = -31415; i <= 31415; i++) {
    const x = i / 10000, reduced = sourceReduceHalfPi(x);
    const result = reduced.quadrant === 0 ? sourceSineKernel(reduced.head)
      : Math.abs(reduced.quadrant) === 2 ? -sourceSineKernelTail(reduced.head, reduced.tail)
      : reduced.quadrant * sourceCosineKernel(reduced.head, reduced.tail);
    if (Math.abs(result - Math.sin(x)) > 3e-16) throw Error(`reduced sine candidate differs at ${x}`);
    if (Math.abs(reduced.head) <= Math.PI / 4 && !Number.isFinite(sourceSineKernelTail(reduced.head, reduced.tail))) throw Error('invalid tail result');
  }
  for (const x of [-4, 4, NaN, Infinity]) {
    let rejected = false; try { sourceReduceHalfPi(x); } catch (e) { rejected = e instanceof RangeError; }
    if (!rejected) throw Error(`expected rejection for ${x}`);
  }
  console.log('[source-angle-reduction] bounded mathematical sanity checks pass; retail parity not yet verified');
}
