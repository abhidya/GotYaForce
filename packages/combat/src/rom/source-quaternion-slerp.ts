import {addSourceFloat32} from './source-float.js';
import {sourceSlerpWeights} from './source-quaternion-slerp-weights.js';

/** Bounded candidate for C_QUATSlerp 8020bf08. Inputs are finite float32
 * quaternions and a float32 weight. The required frsqrte owner is explicit;
 * this is not yet retail-execution verified or connected to gameplay. */
export function sourceQuaternionSlerp(a: readonly number[], b: readonly number[], weight: number,
  reciprocalSqrtEstimate: (x: number) => number): [number, number, number, number] {
  if (a.length !== 4 || b.length !== 4 || [...a, ...b].some(x => !Number.isFinite(x) || !Object.is(x, Math.fround(x)))) throw new RangeError('two finite float32 quaternions required');
  const product = (index: number): number => Math.fround(a[index]! * b[index]!);
  const xy = addSourceFloat32(product(0), product(1));
  const xyz = addSourceFloat32(product(2), xy);
  let dot = addSourceFloat32(product(3), xyz);
  const sign = dot < 0 ? -1 : 1;
  if (dot < 0) dot = -dot;
  const weights = sourceSlerpWeights(dot, weight, sign, reciprocalSqrtEstimate);
  return [0, 1, 2, 3].map(i => addSourceFloat32(Math.fround(weights.first * a[i]!), Math.fround(weights.second * b[i]!))) as [number, number, number, number];
}
