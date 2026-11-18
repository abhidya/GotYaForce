import {sourceSineKernel, sourceSineKernelTail, sourceSineFloatBounded} from './source-sine.js';
export function runSourceSineKernelSelfTest(): void {
  // GG4E 8023cc44 controlled calls in Dolphin 2606-97, not hardware captures.
  const captures: Array<[number, string]> = [
    [-1.5707963705062866, 'bff0000000000000'], [-1.2000000476837158, 'bfedd343a0000000'],
    [-0.7853981852531433, 'bfe6a09e60000000'], [-0.5, 'bfdeaee880000000'],
    [-0.10000000149011612, 'bfb98eaee0000000'], [-0, '8000000000000000'],
    [0, '0000000000000000'], [9.999999717180685e-10, '3e112e0be0000000'],
    [0.10000000149011612, '3fb98eaee0000000'], [0.5, '3fdeaee880000000'],
    [0.7853981852531433, '3fe6a09e60000000'], [0.800000011920929, '3fe6f494c0000000'],
    [1, '3feaed5480000000'], [1.2000000476837158, '3fedd343a0000000'],
    [1.5707963705062866, '3ff0000000000000'],
  ];
  const view = new DataView(new ArrayBuffer(8));
  for (const [x, expected] of captures) {
    view.setFloat64(0, sourceSineFloatBounded(x));
    if (view.getBigUint64(0) !== BigInt(`0x${expected}`)) throw Error(`Dolphin sine mismatch at ${x}`);
  }
  for (let i = -7853; i <= 7853; i++) {
    const x = i / 10000;
    if (Math.abs(sourceSineKernel(x) - Math.sin(x)) > 2e-16) throw Error(`sine candidate differs at ${x}`);
    if (Math.abs(sourceSineKernelTail(x, 1e-17) - Math.sin(x + 1e-17)) > 2e-16) throw Error(`sine tail differs at ${x}`);
  }
  for (let i = -31415; i <= 31415; i++) {
    const x = Math.fround(i / 10000);
    if (Math.abs(sourceSineFloatBounded(x) - Math.fround(Math.sin(x))) > 1.2e-7) throw Error(`float sine differs at ${x}`);
  }
  for (const x of [Math.fround(Math.PI), Math.fround(-Math.PI), Math.fround(3 * Math.PI / 4), Math.fround(-3 * Math.PI / 4)]) {
    if (Math.abs(sourceSineFloatBounded(x) - Math.fround(Math.sin(x))) > 1.2e-7)
      throw Error(`float sine boundary differs at ${x}`);
  }
  // Every signed short passed through the source's float32 angle multiplier.
  // Host trig is only a mathematical sanity check, not an emulator oracle.
  for (let short = -32768; short <= 32767; short++) {
    const radians = Math.fround(short * Math.fround(0.0000958738019107841));
    if (Math.abs(sourceSineFloatBounded(radians) - Math.fround(Math.sin(radians))) > 1.2e-7)
      throw Error(`short-angle sine differs at ${short}`);
  }
  if (!Object.is(sourceSineFloatBounded(-0), -0)) throw Error('float negative zero lost');
  if (!Object.is(sourceSineKernel(-0), -0)) throw Error('negative zero lost');
  for (const x of [-1, 1, NaN, Infinity]) {
    let rejected = false;
    try { sourceSineKernel(x); } catch (e) { rejected = e instanceof RangeError; }
    if (!rejected) throw Error(`expected rejection for ${x}`);
  }
  console.log('[source-sine-kernel] mathematical sanity checks pass; retail parity not yet verified');
}
