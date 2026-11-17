import {sourceSineKernel, sourceSineKernelTail} from './source-sine.js';
export function runSourceSineKernelSelfTest(): void {
  for (let i = -7853; i <= 7853; i++) {
    const x = i / 10000;
    if (Math.abs(sourceSineKernel(x) - Math.sin(x)) > 2e-16) throw Error(`sine candidate differs at ${x}`);
    if (Math.abs(sourceSineKernelTail(x, 1e-17) - Math.sin(x + 1e-17)) > 2e-16) throw Error(`sine tail differs at ${x}`);
  }
  if (!Object.is(sourceSineKernel(-0), -0)) throw Error('negative zero lost');
  for (const x of [-1, 1, NaN, Infinity]) {
    let rejected = false;
    try { sourceSineKernel(x); } catch (e) { rejected = e instanceof RangeError; }
    if (!rejected) throw Error(`expected rejection for ${x}`);
  }
  console.log('[source-sine-kernel] mathematical sanity checks pass; retail parity not yet verified');
}
