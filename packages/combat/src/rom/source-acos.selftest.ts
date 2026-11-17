import {sourceAcosSmall, sourceAcosUpper} from './source-acos.js';
export function runSourceAcosSmallSelfTest(): void {
  for (let i = -4999; i <= 4999; i++) {
    const x = i / 10000;
    if (Math.abs(sourceAcosSmall(x) - Math.acos(x)) > 5e-16) throw Error(`acos candidate differs at ${x}`);
  }
  // This mathematical estimate is a test fixture, not a retail frsqrte oracle.
  for (let i = 5000; i < 10000; i++) {
    const x = i / 10000;
    const result = sourceAcosUpper(x, z => 1 / Math.sqrt(z));
    if (Math.abs(result - Math.acos(x)) > 5e-16) throw Error(`upper acos differs at ${x}`);
  }
  for (const x of [-0.5, 0.5, Infinity, NaN]) {
    let rejected = false;
    try { sourceAcosSmall(x); } catch (e) { rejected = e instanceof RangeError; }
    if (!rejected) throw Error(`expected rejection for ${x}`);
  }
  console.log('[source-acos-small] mathematical sanity checks pass; retail parity not yet verified');
}
