import {sourceCosineFloatBounded} from './source-cosine-float.js';
import {sourceCosineKernel} from './source-cosine.js';
export function runSourceCosineKernelSelfTest(): void {
  // Unique input/output pairs from a live GG4E Dolphin JIT64 battle; neither
  // physical hardware nor all possible float32 arguments are represented.
  {
    const cases: Array<[string,string]> = [["00000000","3f800000"],["3cfe7811","3f7fe062"],["bd82928c","3f7f7ad9"],["bfc90fdb","b33bbd2e"],["3fc90fdb","b33bbd2e"],["3f060a92","3f5db3d7"],["c00c6a1b","bf156822"],["bf604e08","3f23dc73"],["bf491623","3f350082"],["c005c038","befdfc36"],["bdbd15a9","3f7ee8e1"],["bd6ccc2c","3f7f9283"],["3f31d7f6","3f44abb1"],["3d848934","3f7f76d1"],["bd7aef4a","3f7f850e"]];
    const view = new DataView(new ArrayBuffer(4));
    for (const [input, expected] of cases) {
      view.setUint32(0, parseInt(input,16)); const x=view.getFloat32(0);
      view.setFloat32(0, sourceCosineFloatBounded(x));
      if (view.getUint32(0) !== parseInt(expected,16)) throw Error(`Dolphin cosine mismatch at ${input}`);
    }
  }
  for (let i = -23561; i <= 23561; i++) {
    const x = Math.fround(i / 10000);
    if (Math.abs(sourceCosineFloatBounded(x) - Math.fround(Math.cos(x))) > 1.2e-7)
      throw Error(`bounded float cosine differs at ${x}`);
  }
  if (sourceCosineFloatBounded(-0) !== 1) throw Error('negative zero cosine');
  for (const x of [NaN, Infinity, 1 + 2 ** -30, Math.fround(2.4)]) {
    let rejected = false; try {sourceCosineFloatBounded(x);} catch {rejected = true;}
    if (!rejected) throw Error(`bounded cosine accepted ${x}`);
  }
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
