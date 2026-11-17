import {sourceSlerpWeights} from './source-quaternion-slerp-weights.js';
export function runSourceSlerpWeightsSelfTest(): void {
  const estimate = (x: number): number => 1 / Math.sqrt(x); // test fixture, not a retail estimate
  for (let d = 0; d <= 1000; d++) for (let w = 0; w <= 20; w++) {
    const dot = Math.fround(d / 1000), weight = Math.fround(w / 20);
    const actual = sourceSlerpWeights(dot, weight, 1, estimate), theta = Math.acos(dot);
    const first = dot > 0.9999899864196777 ? 1 - weight : Math.sin((1 - weight) * theta) / Math.sin(theta);
    const second = dot > 0.9999899864196777 ? weight : Math.sin(weight * theta) / Math.sin(theta);
    if (Math.abs(actual.first - first) > 3e-7 || Math.abs(actual.second - second) > 3e-7) throw Error(`slerp weight differs at ${dot}, ${weight}`);
    if (sourceSlerpWeights(dot, weight, -1, estimate).second !== -actual.second) throw Error('sign mismatch');
  }
  console.log('[source-slerp-weights] mathematical sanity checks pass; retail parity not yet verified');
}
