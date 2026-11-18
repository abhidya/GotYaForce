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

/** The 4a8cc pose blender chooses the shorter quaternion hemisphere before
 * calling C_QUATSlerp. This pure counterpart is for presentation integration;
 * it does not reproduce source stores, visibility, or pose-bank ownership. */
export function sourceBlendQuaternion(current: readonly number[], previous: readonly number[], weight: number,
  reciprocalSqrtEstimate: (x: number) => number): [number, number, number, number] {
  if (current.length !== 4 || previous.length !== 4 || [...current, ...previous, weight].some(x =>
    !Number.isFinite(x) || !Object.is(x, Math.fround(x))) || weight < 0 || weight > 1) {
    throw new RangeError('finite float32 quaternions and weight in [0,1] required');
  }
  const add = addSourceFloat32, sub = (a: number, b: number): number => add(a, -b);
  const mul = (a: number, b: number): number => Math.fround(a * b);
  const a = current, b = [...previous];
  const dx = sub(a[0]!, b[0]!), dy = sub(a[1]!, b[1]!), sx = add(a[0]!, b[0]!), sy = add(a[1]!, b[1]!);
  const dx2 = mul(dx, dx), dy2 = mul(dy, dy), dz = sub(a[2]!, b[2]!), sz = add(a[2]!, b[2]!);
  const sx2 = mul(sx, sx), sy2 = mul(sy, sy), dw = sub(a[3]!, b[3]!), sw = add(a[3]!, b[3]!), dz2 = mul(dz, dz);
  const diffXY = add(dx2, dy2), sz2 = mul(sz, sz), sumXY = add(sx2, sy2), dw2 = mul(dw, dw);
  const diffXYZ = add(dz2, diffXY), sw2 = mul(sw, sw), sumXYZ = add(sz2, sumXY);
  if (add(dw2, diffXYZ) > add(sw2, sumXYZ)) for (let i = 0; i < 4; i++) b[i] = -b[i]!;
  const xy = add(mul(a[0]!, b[0]!), mul(a[1]!, b[1]!));
  let dot = add(mul(a[3]!, b[3]!), add(mul(a[2]!, b[2]!), xy)), sign: 1 | -1 = 1;
  if (dot < 0) { dot = -dot; sign = -1; }
  // Source takes the linear branch even if float32 rounding puts dot above 1.
  const weights = dot > 0.9999899864196777
    ? { first: sub(1, weight), second: mul(sign, weight) }
    : sourceSlerpWeights(dot, weight, sign, reciprocalSqrtEstimate);
  return [0, 1, 2, 3].map(i => add(mul(weights.first, a[i]!), mul(weights.second, b[i]!))) as [number, number, number, number];
}
