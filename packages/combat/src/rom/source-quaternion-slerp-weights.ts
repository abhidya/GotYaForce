import {sourceAcosFloatNonnegative} from './source-acos.js';
import {sourceSineFloatBounded} from './source-sine.js';

/** Candidate nonlinear weight calculation in C_QUATSlerp 8020bf08.
 * The caller supplies a nonnegative dot and sign after the source sign branch.
 * Limited to ordinary interpolation weights. No gameplay wiring or retail
 * PowerPC equivalence is claimed until frsqrte and arithmetic are verified.
 */
export function sourceSlerpWeights(dot: number, weight: number, sign: 1 | -1,
  reciprocalSqrtEstimate: (x: number) => number): {first: number; second: number} {
  if (!Number.isFinite(dot) || !Object.is(dot, Math.fround(dot)) || dot < 0 || dot > 1 ||
      !Number.isFinite(weight) || !Object.is(weight, Math.fround(weight)) || weight < 0 || weight > 1 || (sign !== 1 && sign !== -1)) {
    throw new RangeError('finite float32 dot and interpolation weight in [0,1] required');
  }
  if (dot > 0.9999899864196777) return {first: Math.fround(1 - weight), second: Math.fround(sign * weight)};
  const theta = sourceAcosFloatNonnegative(dot, reciprocalSqrtEstimate);
  const denom = sourceSineFloatBounded(theta);
  if (denom === 0) throw new RangeError('zero sine denominator');
  const firstArg = Math.fround(Math.fround(1 - weight) * theta);
  const secondArg = Math.fround(weight * theta);
  const first = Math.fround(sourceSineFloatBounded(firstArg) / denom);
  const second = Math.fround(sign * Math.fround(sourceSineFloatBounded(secondArg) / denom));
  return {first, second};
}
