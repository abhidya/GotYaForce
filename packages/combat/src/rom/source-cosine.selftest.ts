import {sourceCosineKernel} from './source-cosine.js';
export function runSourceCosineKernelSelfTest(): void {
  for (let i = -7853; i <= 7853; i++) {
    const x = i / 10000;
    if (Math.abs(sourceCosineKernel(x, 0) - Math.cos(x)) > 2e-16) throw Error(`cosine candidate differs at ${x}`);
  }
  for (const x of [-1, 1, NaN, Infinity]) {
    let rejected = false;
    try { sourceCosineKernel(x, 0); } catch (e) { rejected = e instanceof RangeError; }
    if (!rejected) throw Error(`expected rejection for ${x}`);
  }
  console.log('[source-cosine-kernel] mathematical sanity checks pass; retail parity not yet verified');
}
