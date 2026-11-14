/** Bounded explicit actor matrix primitives, not traversal or a clock/setup effect.
 * Evidence: research/decomp/jobj-world-matrix-integration-2026-11-13.md.
 * Terrain/MultVec: research/decomp/terrain-orientation-evidence-2026-11-13.md.
 * Primary: research/decomp/primary-terrain-placement-evidence-2026-11-13.md.
 * Parent and actual translation are already resolved by the caller. Owned matrices
 * have row-major 3x4 storage; no default matrix or pose association is invented.
 * The admitted PSMTXQuat input is exactly (+0,+0,+0,1), including zero signs.
 * Its audited output has -0 at [6] and [8]. Corrections admit only zero shorts,
 * selecting 80045838's PSMTXCopy branch, never an approximation of source trig.
 * 800457d4 zero-short wrappers retain RotRad and Concat semantics: audited zero
 * sin/cos return +0/1, and X/Y/Z rotation matrices have -0 at [6]/[8]/[1].
 * The wrapper additionally assumes GQR5 signed-short loads with scale 0; live
 * register initialization/invariance has not been established.
 * PSMTXConcat uses audited paired-single multiply/FMA order including the +0
 * translation lane in column 2. Paired loads/stores require GQR0 floating-point
 * types with no quantization; initialization/live invariance is not established.
 * RN=00/NI=0 finite-f32 bounds are assumptions,
 * not original-runtime parity. No arbitrary quaternion/fres emulation is claimed.
 * Terrain 45918 admits only axes (2,1), flat (±0,1,±0), and nondegenerate
 * signed-axis columns with magnitudes .5,1,2,4,8; the first construction must
 * succeed. Mag/Normalize use the real SDK refinement of a separately derived
 * finite reciprocal-estimate specialization, not sqrt or an identity shortcut.
 * This specialization is canonical Dolphin-model-backed, not a hardware capture.
 * Primary47368 additionally admits measured signed-axis length pairs (2,.5)
 * and (1,1), and target displacement (±0,1,±0). Its historical folded name
 * now covers minimum-reach folding and one positive-sine case. Three-step
 * binary64 refinements, cosines, sine branches, RotTrig and both Concats really
 * execute. This is not general IK or a promise that the endpoint hits.
 * Non-proxy own-data inputs only. Adapters retain their receiver and are captured
 * once; they must be synchronous and cannot mutate other records. Per-access
 * validation, reentry poison, and failures retain prior writes. Finite-intermediate
 * overflow refusal is host admission policy, not source FP exception behavior.
 * Symbols are local ownership handles, not emulated source addresses. Matrix capacity is host policy.
 */
import type {SourceJointAnimationFeedbackRuntime, SourceJointVector} from './joint-animation-feedback.js';
import {addSourceFloat32, fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';
import {primarySineCorrection} from './actor-primary-float.js';

/** Live primary entry fields. Raw bytes are sign-extended only when reached. */
export interface SourcePrimaryFoldedPlacement extends SourceJointVector {
  axis0d: number;
  axis0e: number;
  bend0f: number;
}

export interface SourceActorJointMatrixRuntime {
  createMatrix(initial: readonly number[]): symbol;
  getMatrix(identity: symbol): number[];
  identity(matrix: symbol): void;
  translate(matrix: symbol, translation: Readonly<SourceJointVector>): void;
  correctShort(matrix: symbol, correction: Readonly<SourceJointVector>): void;
  scale(matrix: symbol, scaling: Readonly<SourceJointVector>): void;
  copy(source: symbol, destination: symbol): void;
  /** SDK 8020b7a8; caller owns the explicit output vector, which may alias input. */
  transformPoint(matrix: symbol, input: Readonly<SourceJointVector>, output: SourceJointVector): void;
  /** Bounded 45918 path; no general terrain orientation/estimate implementation. */
  orientTerrainMatrix(matrix: symbol, normal: Readonly<SourceJointVector>, axisA: number, axisB: number): void;
  /** Historical name: 47368 (2,.5) folded and (1,1) positive-sine subsets only.
   * World captures current X, reloads entry joint,
   * then captures current Y/Z before calling. Next translation is still raw;
   * physical current/next/end are joint-2/joint-1/joint, not topology links. */
  primaryFoldedPlacement(parent: symbol, current: symbol, next: symbol, end: symbol,
    translation: Readonly<SourceJointVector>, nextTranslation: Readonly<SourceJointVector>,
    correction: Readonly<SourcePrimaryFoldedPlacement>): void;
  rotateShort(axis: 'x' | 'y' | 'z', parent: symbol, destination: symbol, angle: number): void;
  /** Quaternion, local translation and first Concat only; no correction or scale. */
  composePose(parent: symbol, destination: symbol, pose: symbol,
    translationOverride?: Readonly<SourceJointVector>): void;
  composeJoint(parent: symbol, destination: symbol, pose: symbol,
    correction: Readonly<SourceJointVector>, scale: Readonly<SourceJointVector>,
    translationOverride?: Readonly<SourceJointVector>): void;
}
function fail(reason: string): never {
  throw Error(`[actor-joint-matrix] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(record: unknown, key: string, writable = false): unknown {
  if (record === null || typeof record !== 'object') fail(`${key}: data record required`);
  const p = Object.getOwnPropertyDescriptor(record, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value))) fail(`${where}: expected finite source float32`);
  return value;
}
function snapshot(matrix: readonly number[]): number[] {
  if (!Array.isArray(matrix) || own(matrix, 'length') !== 12) fail('matrix must contain exactly 12 entries');
  return Array.from({length: 12}, (_, i) => float(own(matrix, String(i)), `matrix[${i}]`));
}
function store(matrix: number[], i: number, value: number): void {
  own(matrix, String(i), true); matrix[i] = value;
}
function load(matrix: number[], i: number): number {
  return float(own(matrix, String(i)), `matrix[${i}]`);
}
function vectorLoad(vector: Readonly<SourceJointVector>, key: 'x' | 'y' | 'z', where: string): number {
  return float(own(vector, key), `${where}.${key}`);
}
function vectorStore(vector: SourceJointVector, key: 'x' | 'y' | 'z', value: number): void {
  own(vector, key, true); vector[key] = value;
}
function multiply(a: number, b: number): number {
  return float(Math.fround(a * b), 'single product');
}
function add(a: number, b: number): number {
  return float(Math.fround(a + b), 'single sum');
}
function transformPoint(matrix: number[], input: Readonly<SourceJointVector>, output: SourceJointVector): void {
  // 8020b7a8..b7f4: each paired row accumulates Z into X's product and
  // translation into Y's product, THEN sums the lanes. Reassociating the
  // dot product (or using Concat's ordering) loses real rounding/zero behavior.
  const x = vectorLoad(input, 'x', 'point'), y = vectorLoad(input, 'y', 'point');
  const m0 = load(matrix, 0), m1 = load(matrix, 1);
  const z = vectorLoad(input, 'z', 'point'); // W=1 supplies exactly +1.
  const p0 = multiply(m0, x), p1 = multiply(m1, y);
  const m2 = load(matrix, 2), m3 = load(matrix, 3);
  const q0 = fma(m2, z, p0), q1 = fma(m3, 1, p1);
  const m4 = load(matrix, 4), m5 = load(matrix, 5);
  const resultX = add(q0, q1);
  const m6 = load(matrix, 6), m7 = load(matrix, 7);
  const p4 = multiply(m4, x), p5 = multiply(m5, y);
  vectorStore(output, 'x', resultX);
  const q4 = fma(m6, z, p4), q5 = fma(m7, 1, p5);
  const m8 = load(matrix, 8), m9 = load(matrix, 9);
  const resultY = add(q4, q5);
  const m10 = load(matrix, 10), m11 = load(matrix, 11);
  const p8 = multiply(m8, x), p9 = multiply(m9, y);
  vectorStore(output, 'y', resultY);
  const q8 = fma(m10, z, p8), q9 = fma(m11, 1, p9);
  vectorStore(output, 'z', add(q8, q9));
}
function short(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < -32768 || value > 32767) fail(`${where}: signed short required`);
  return value;
}
function copy(source: number[], destination: number[]): void {
  // PSMTXCopy 8020af28 loads and stores one row-major pair at a time,
  // including when source and destination alias. Do not snapshot all inputs.
  for (let i = 0; i < 12; i += 2) {
    const first = load(source, i), second = load(source, i + 1);
    store(destination, i, first); store(destination, i + 1, second);
  }
}
function correctShort(matrix: number[], correction: Readonly<SourceJointVector>): void {
  for (const key of ['x', 'y', 'z'] as const) {
    if (short(own(correction, key), key) !== 0) fail('nonzero short correction is unsupported');
  }
  // 80045838's zero Z branch still copies; zero Y and X skip their rotations.
  copy(matrix, matrix);
}
function scale(matrix: number[], scaling: Readonly<SourceJointVector>): void {
  const x = float(own(scaling, 'x'), 'scale.x'), y = float(own(scaling, 'y'), 'scale.y'), z = float(own(scaling, 'z'), 'scale.z');
  // PSMTXScale 8020b4f8 temporary; the caller still performs PSMTXConcat
  // for unit scales. The temporary's stores are not externally observable.
  concat(matrix, [x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0], matrix);
}
function translate(matrix: number[], translation: Readonly<SourceJointVector>): void {
  // The caller loads XYZ arguments before TransApply. Its frsp instructions
  // preserve these admitted f32 values. 8020b4ac then interleaves matrix loads,
  // sums and stores; do not validate the entire matrix before its first store.
  const x = float(own(translation, 'x'), 'translation.x');
  const y = float(own(translation, 'y'), 'translation.y');
  const z = float(own(translation, 'z'), 'translation.z');
  const m0 = load(matrix, 0), m1 = load(matrix, 1);
  const m2 = load(matrix, 2), m3 = load(matrix, 3);
  const m6 = load(matrix, 6), m7 = load(matrix, 7);
  const m10 = load(matrix, 10), m11 = load(matrix, 11);
  store(matrix, 0, m0); store(matrix, 1, m1);
  const tx = float(Math.fround(x + m3), 'translated x');
  const m4 = load(matrix, 4), m5 = load(matrix, 5);
  store(matrix, 2, m2); store(matrix, 3, tx);
  const ty = float(Math.fround(y + m7), 'translated y');
  const m8 = load(matrix, 8), m9 = load(matrix, 9);
  store(matrix, 4, m4); store(matrix, 5, m5);
  const tz = float(Math.fround(z + m11), 'translated z');
  store(matrix, 6, m6); store(matrix, 7, ty);
  store(matrix, 8, m8); store(matrix, 9, m9);
  store(matrix, 10, m10); store(matrix, 11, tz);
}
// PSMTXConcat psq_st order, not naive row-major host assignment.
const concatStores = [0, 1, 4, 5, 2, 3, 6, 7, 8, 9, 10, 11] as const;
function concat(aInput: number[], bInput: number[], destination: number[]): void {
  const a = snapshot(aInput), b = snapshot(bInput);
  const compute = (i: number): number => {
    const row = i - i % 4, col = i % 4;
    let value = float(Math.fround(b[col]! * a[row]!), 'concat product');
    value = fma(b[4 + col]!, a[row + 1]!, value);
    value = fma(b[8 + col]!, a[row + 2]!, value);
    if (col >= 2) value = fma(col === 3 ? 1 : 0, a[row + 3]!, value);
    return value;
  };
  for (let pair = 0; pair < concatStores.length; pair += 2) {
    const i = concatStores[pair]!, j = concatStores[pair + 1]!;
    const first = compute(i), second = compute(j);
    store(destination, i, first); store(destination, j, second);
  }
}
type LocalVector = [number, number, number];
function finiteAxisMagnitude(vector: LocalVector): number {
  const nonzero = vector.filter(value => value !== 0);
  if (nonzero.length !== 1) fail('terrain vector outside signed-axis estimate proof domain');
  const magnitude = Math.abs(nonzero[0]!);
  if (![0.5, 1, 2, 4, 8].includes(magnitude)) fail('terrain magnitude outside finite estimate proof domain');
  return magnitude;
}
function squareMagnitude(vector: LocalVector): number {
  // Both SDK sites use ps_mul XY, ps_madd Z, then ps_sum0. Even though
  // only one axis is nonzero in this domain, retain that exact operation tree.
  const xSquared = multiply(vector[0], vector[0]), ySquared = multiply(vector[1], vector[1]);
  return add(fma(vector[2], vector[2], xSquared), ySquared);
}
function refinedAxisReciprocal(magnitude: number, squared: number): number {
  // Independently derived finite facts, not copied emulator code/table:
  // Dolphin 221d396b3acb9e0d1a815cbf7613a9f7032cc14a, FloatUtils.cpp
  // lines75..139 and FloatUtilsTest.cpp lines69..103 corroborate unit seed
  // 0x3feffe8000000000. For m in {.5,1,2,4,8}, frsqrte(m*m) is exactly
  // (16381/16384)/m. All five seeds are binary32-exact; Force25Bit does
  // not change them. Division here only scales that proven power-of-two seed.
  // The authenticated SDK's fmuls/fmuls/fnmsubs/fmuls must still execute:
  // q=1-2^-24 is their RESULT, not a replacement for the operations.
  const estimate = (16381 / 16384) / magnitude;
  const estimateSquared = multiply(estimate, estimate);
  const halfEstimate = multiply(estimate, 0.5);
  const correction = -fma(estimateSquared, squared, -3);
  return multiply(correction, halfEstimate);
}
function axisMagnitude(vector: LocalVector): number {
  const magnitude = finiteAxisMagnitude(vector);
  const squared = squareMagnitude(vector);
  // 8020bb14's zero branch is unreachable inside this admitted axis domain.
  return multiply(squared, refinedAxisReciprocal(magnitude, squared));
}
function normalizeAxis(vector: LocalVector): LocalVector {
  const magnitude = finiteAxisMagnitude(vector);
  const reciprocal = refinedAxisReciprocal(magnitude, squareMagnitude(vector));
  // 8020bae8/baec operate/store XY before baf0/baf4 operate/store Z.
  const x = multiply(vector[0], reciprocal), y = multiply(vector[1], reciprocal);
  return [x, y, multiply(vector[2], reciprocal)];
}
function cross(a: LocalVector, b: LocalVector): LocalVector {
  // 8020bb78: ps_msub subtracts a separately rounded product. Y and Z are
  // explicitly negated AFTER that fused subtraction, including zero results.
  const bx = b[0], by = b[1], az = a[2], ax = a[0], ay = a[1], bz = b[2];
  const bxAz = multiply(bx, az), byAz = multiply(by, az);
  const bxAx = multiply(bx, ax), byAx = multiply(by, ax);
  const negativeY = fma(ax, bz, -bxAz), x = fma(ay, bz, -byAz);
  // Both lanes execute even though the first is not stored by this routine.
  fma(ax, by, -bxAx);
  const negativeZ = fma(ay, bx, -byAx);
  return [x, -negativeY, -negativeZ];
}
function orientTerrainMatrix(matrix: number[], normal: Readonly<SourceJointVector>, axisA: number, axisB: number): void {
  // 45954..459a0 load ALL three columns, column-major, before the three
  // Mag calls at459a8/b4/c0. Translation is first read by final Concat.
  const oldX: LocalVector = [load(matrix, 0), load(matrix, 4), load(matrix, 8)];
  const oldY: LocalVector = [load(matrix, 1), load(matrix, 5), load(matrix, 9)];
  const oldZ: LocalVector = [load(matrix, 2), load(matrix, 6), load(matrix, 10)];
  const magnitudeX = axisMagnitude(oldX), magnitudeY = axisMagnitude(oldY), magnitudeZ = axisMagnitude(oldZ);
  const y: LocalVector = [vectorLoad(normal, 'x', 'normal'), vectorLoad(normal, 'y', 'normal'),
    vectorLoad(normal, 'z', 'normal')];
  if (y[0] !== 0 || y[1] !== 1 || y[2] !== 0) fail('only flat (±0,1,±0) terrain normal is supported');
  if (axisA !== 2 || axisB !== 1) fail('only positive terrain axes (2,1) are supported');
  // 45a10/18/20 freshly load the selected reference column. The authenticated
  // lookup at802d0d34+7 selects2; dispatch cell802d0d4c selects80046158.
  let x: LocalVector = [load(matrix, 0), load(matrix, 4), load(matrix, 8)];
  if (new Set([oldX, oldY, oldZ].map(column => column.findIndex(value => value !== 0))).size !== 3) {
    fail('terrain basis must have three distinct signed axes');
  }
  const z = cross(x, y);
  // 461c4/cc/d4 separately square XYZ, then add X+Y and that sum+Z.
  const zx2 = multiply(z[0], z[0]), zy2 = multiply(z[1], z[1]), zz2 = multiply(z[2], z[2]);
  const lengthSquared = add(zz2, add(zx2, zy2));
  // Authenticated 80437080 bits2edbe6fe. A failed first construction would
  // select another reference/dispatch entry; none is silently synthesized.
  if (!(lengthSquared > 9.999999439624929e-11)) fail('terrain fallback construction is unsupported');
  x = cross(y, z);
  const normalizedX = normalizeAxis(x), normalizedY = normalizeAxis(y), normalizedZ = normalizeAxis(z);
  // 45f70..45fb0 stores column-major, only after all three normalizations.
  // Per-store host refusals preserve precisely the completed output prefix.
  for (const [column, values] of [[0, normalizedX], [1, normalizedY], [2, normalizedZ]] as const) {
    store(matrix, column, values[0]); store(matrix, 4 + column, values[1]); store(matrix, 8 + column, values[2]);
  }
  // 45b7c/45b8c really restore the SAVED source magnitudes through Scale and
  // Concat. Unit-axis inputs therefore finish below one, not as an identity.
  scale(matrix, {x: magnitudeX, y: magnitudeY, z: magnitudeZ});
}
function primarySignedByte(record: Readonly<SourcePrimaryFoldedPlacement>, key: 'axis0d' | 'axis0e' | 'bend0f'): number {
  const value = own(record, key);
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 255) fail(`${key}: raw byte required`);
  return (value << 24) >> 24;
}
function primaryLength(a: LocalVector, b: LocalVector, admitted: readonly number[]): number {
  // 8020bc88: unlike Mag, SquareDistance forms YZ first, then XY. Its
  // unused second FMA lane still executes, but ps_sum0 selects the old Z².
  const dy = addSourceFloat32(a[1], -b[1]), dz = addSourceFloat32(a[2], -b[2]);
  const ySquared = multiply(dy, dy), zSquared = multiply(dz, dz);
  const dx = addSourceFloat32(a[0], -b[0]), dyAgain = addSourceFloat32(a[1], -b[1]);
  const xySquared = fma(dx, dx, ySquared);
  fma(dyAgain, dyAgain, zSquared);
  const squared = add(xySquared, zSquared);
  const magnitude = finiteAxisMagnitude([dx, dy, dz]);
  if (!admitted.includes(magnitude)) fail(`primary retained bone length must be exactly ${admitted.join(' or ')}`);
  // 47440..47490 and 474ac..474fc: positive squares use THREE binary64
  // Newton steps, unlike the SDK's one single-precision step. For admitted
  // s=m² (4,1 or .25), multiplying rounded e² by s is exact normal power-of-two
  // scaling, so -(s*e²-3) has exactly the authenticated fnmsub64 rounding.
  // Every other operator below has a separate binary64 rounding. The finite
  // Dolphin-model seed is exact; no host sqrt/trig or ideal length is used.
  let estimate = (16381 / 16384) / magnitude;
  for (let iteration = 0; iteration < 3; iteration++) {
    const estimateSquared = estimate * estimate;
    const halfEstimate = 0.5 * estimate;
    const correction = -(squared * estimateSquared - 3);
    estimate = halfEstimate * correction;
  }
  return float(Math.fround(squared * estimate), 'primary retained length');
}
// Local exact fdivs for the two authenticated primary cosine sites. Keeping
// this private avoids expanding any shared arithmetic API or admission domain.
const primaryFloatBits = new DataView(new ArrayBuffer(4));
function primaryDyadic(value: number): {mantissa: bigint; exponent: number; negative: boolean} {
  primaryFloatBits.setFloat32(0, value, false);
  const raw = primaryFloatBits.getUint32(0, false), field = (raw >>> 23) & 255;
  return {mantissa: BigInt((raw & 0x7fffff) | (field === 0 ? 0 : 0x800000)),
    exponent: field === 0 ? -149 : field - 150, negative: (raw >>> 31) !== 0};
}
function primaryDivide(a: number, b: number): number {
  const x = primaryDyadic(a), y = primaryDyadic(b), negative = x.negative !== y.negative;
  if (y.mantissa === 0n) fail('primary fdivs zero divisor outside finite domain');
  if (x.mantissa === 0n) return negative ? -0 : 0;
  let power = x.mantissa.toString(2).length - y.mantissa.toString(2).length;
  if (power >= 0 ? x.mantissa < (y.mantissa << BigInt(power)) :
    (x.mantissa << BigInt(-power)) < y.mantissa) power--;
  const exponent = x.exponent - y.exponent;
  const quantum = Math.max(-149, power + exponent - 23), shift = exponent - quantum;
  const numerator = shift >= 0 ? x.mantissa << BigInt(shift) : x.mantissa;
  const denominator = shift < 0 ? y.mantissa << BigInt(-shift) : y.mantissa;
  let rounded = numerator / denominator;
  const twiceRemainder = (numerator % denominator) * 2n;
  if (twiceRemainder > denominator || (twiceRemainder === denominator && (rounded & 1n) !== 0n)) rounded++;
  const result = Number(rounded) * 2 ** quantum;
  return float(negative ? -result : result, 'primary fdivs');
}
function primarySine(cosine: number): number {
  const squared = -fma(cosine, cosine, -1); // fnmsubs leaves an exact zero complement as -0.
  if (!(squared > 0)) return squared; // Source zero branch skips frsqrte and every Newton stage.
  primaryFloatBits.setFloat32(0, squared, false);
  const raw = primaryFloatBits.getUint32(0, false);
  // Independently derived canonical Dolphin-model facts, not hardware captures:
  // 221d396b3acb9e0d1a815cbf7613a9f7032cc14a FloatUtils.cpp,
  // blob312d4a88a217e061a8d5f91061272a417b1d484b. Exactly two sine inputs:
  // 3f400000 -> f64 seed3ff2794000000000;
  // 3f3fffff -> f64 seed3ff2794cb8000000. No general estimate lookup.
  let estimate: number;
  if (raw === 0x3f400000) estimate = 18917 / 16384;
  else if (raw === 0x3f3fffff) estimate = 38742423 / 33554432;
  else return fail('primary positive sine square outside two-input estimate proof domain');
  for (let iteration = 0; iteration < 3; iteration++) {
    const estimateSquared = estimate * estimate; // RN64 fmul, not fmuls.
    const halfEstimate = 0.5 * estimate;
    const correction = primarySineCorrection(squared, estimateSquared); // One fused RN64 fnmsub.
    estimate = halfEstimate * correction;
  }
  return float(Math.fround(squared * estimate), 'primary sine magnitude');
}
function primaryRotation(axis: 'x' | 'y' | 'z', sine: number, cosine: number): number[] {
  // 8020b2a8's actual paired merges, not the misleading decompiled Y/Z
  // assignments. All stores target the private source-stack temporary.
  if (axis === 'x') return [1, 0, 0, 0, 0, cosine, -sine, 0, 0, sine, cosine, 0];
  if (axis === 'y') return [cosine, 0, sine, 0, 0, 1, 0, 0, -sine, 0, cosine, 0];
  return [cosine, -sine, 0, 0, sine, cosine, 0, 0, 0, 0, 1, 0];
}
function primaryFoldedPlacement(parent: number[], current: number[], next: number[], end: number[],
  translation: Readonly<SourceJointVector>, nextTranslation: Readonly<SourceJointVector>,
  correction: Readonly<SourcePrimaryFoldedPlacement>): void {
  // World has captured raw current X, then the fresh entry joint, then Y/Z.
  // These are that source-stack local, not an adjusted joint1 translation.
  const local = {x: vectorLoad(translation, 'x', 'primary current'),
    y: vectorLoad(translation, 'y', 'primary current'), z: vectorLoad(translation, 'z', 'primary current')};
  // 473d8/dc/e0 save the adjacent RAW pose, not the next topology-linked pose.
  const nextX = vectorLoad(nextTranslation, 'x', 'primary next');
  const nextY = vectorLoad(nextTranslation, 'y', 'primary next');
  const nextZ = vectorLoad(nextTranslation, 'z', 'primary next');
  // All nine retained coordinates are loaded before either distance call.
  const oldCurrent: LocalVector = [load(current, 3), load(current, 7), load(current, 11)];
  const oldNext: LocalVector = [load(next, 3), load(next, 7), load(next, 11)];
  const oldEnd: LocalVector = [load(end, 3), load(end, 7), load(end, 11)];
  const firstLength = primaryLength(oldCurrent, oldNext, [2, 1]);
  // Admit only these PAIRS, not the Cartesian product of the five axis powers.
  // The second distance/refinement is still reached after the first completes.
  const secondLength = primaryLength(oldNext, oldEnd, [firstLength === 2 ? 0.5 : 1]);
  transformPoint(parent, local, local);
  store(current, 3, local.x); store(current, 7, local.y); store(current, 11, local.z);
  // 8020ba78's subtraction stores its private XY before loading target Z.
  // Entry axes are fresh later reads, never preflighted before translation.
  const targetX = vectorLoad(correction, 'x', 'primary target'), targetY = vectorLoad(correction, 'y', 'primary target');
  const delta = {x: addSourceFloat32(targetX, -local.x), y: addSourceFloat32(targetY, -local.y), z: NaN};
  delta.z = addSourceFloat32(vectorLoad(correction, 'z', 'primary target'), -local.z);
  const axisA = primarySignedByte(correction, 'axis0d'), axisB = primarySignedByte(correction, 'axis0e');
  orientTerrainMatrix(current, delta, axisA, axisB);
  // 47560 follows the completed orientation (including its Scale/Concat).
  let distance = axisMagnitude([delta.x, delta.y, delta.z]);
  const reach = multiply(0.9990000128746033, add(firstLength, secondLength)); // 804370d0=3f7fbe77
  if (reach < distance) distance = reach;
  // Exact instruction ordering at47584..475c4. In particular both rounded
  // square sums precede either numerator subtraction, and no ideal cosine or
  // binary64 quotient replaces the two independently rounded fdivs.
  const distanceSquared = multiply(distance, distance), firstSquared = multiply(firstLength, firstLength);
  const secondSquared = multiply(secondLength, secondLength), twiceDistance = multiply(2, distance);
  const sumDistanceFirst = add(distanceSquared, firstSquared), sumLengths = add(firstSquared, secondSquared);
  const twiceFirst = multiply(2, firstLength);
  const numeratorFirst = addSourceFloat32(sumDistanceFirst, -secondSquared), denominatorFirst = multiply(twiceDistance, firstLength);
  const numeratorSecond = addSourceFloat32(sumLengths, -distanceSquared), denominatorSecond = multiply(twiceFirst, secondLength);
  const rawCosineFirst = primaryDivide(numeratorFirst, denominatorFirst);
  const negativeNumeratorSecond = -numeratorSecond;
  const firstAtMostOne = rawCosineFirst <= 1;
  const rawCosineSecond = primaryDivide(negativeNumeratorSecond, denominatorSecond);
  let cosineFirst = 1;
  if (firstAtMostOne) {cosineFirst = rawCosineFirst; if (cosineFirst < -1) cosineFirst = -1;}
  let cosineSecond = 1;
  if (rawCosineSecond <= 1) {cosineSecond = rawCosineSecond; if (cosineSecond < -1) cosineSecond = -1;}
  const negativeBend = primarySignedByte(correction, 'bend0f') < 0;
  let sineFirst = primarySine(cosineFirst);
  if (!negativeBend) sineFirst = -sineFirst;
  let sineSecond = primarySine(cosineSecond);
  // 476d8 or477b8 reloads bend before the authenticated table lookup. Only
  // indices1..3 (x/y/z) are admitted; zero/-128 never invent a table entry.
  const reloadedBend = primarySignedByte(correction, 'bend0f');
  if (negativeBend) sineSecond = -sineSecond; // 476e0 follows the byte reload.
  const axisIndex = negativeBend ? -reloadedBend : reloadedBend;
  if (axisIndex < 1 || axisIndex > 3) fail('primary bend axis must be signed 1, 2 or 3');
  const axis = (['x', 'y', 'z'] as const)[axisIndex - 1]!;
  const firstRotation = primaryRotation(axis, sineFirst, cosineFirst);
  concat(current, firstRotation, current);
  const secondRotation = primaryRotation(axis, sineSecond, cosineSecond);
  secondRotation[3] = nextX; secondRotation[7] = nextY; secondRotation[11] = nextZ;
  concat(current, secondRotation, next);
}
export function createSourceActorJointMatrixRuntime(
  feedback: Pick<SourceJointAnimationFeedbackRuntime, 'getPose'>, maxMatrices = 128,
): SourceActorJointMatrixRuntime {
  if (!Number.isSafeInteger(maxMatrices) || maxMatrices < 1) fail('positive safe matrix capacity required');
  const poseMethod = own(feedback, 'getPose');
  if (typeof poseMethod !== 'function') fail('getPose: own data-function required');
  const poseGet = poseMethod;
  const matrices = new Map<symbol, number[]>();
  let busy = false, reentered = false;
  function enter(): void {
    if (busy) {reentered = true; fail('same-runtime reentry is unsupported');}
    busy = true; reentered = false;
  }
  function getMatrix(id: symbol): number[] {
    const value = matrices.get(id); if (!value) fail('unknown/non-owned matrix'); return value;
  }
  function composePose(parent: symbol, destination: symbol, pose: symbol,
    translationOverride?: Readonly<SourceJointVector>): number[] {
    const resolved = Reflect.apply(poseGet, feedback, [pose]) as unknown;
    if (reentered) fail('same-runtime reentry was caught inside getPose');
    // Own records reject promises/thenables without reading any accessors.
    const q = own(resolved, 'quaternion');
    for (const key of ['x', 'y', 'z', 'w'] as const) {
      const value = float(own(q, key), `quaternion.${key}`);
      if (!Object.is(value, key === 'w' ? 1 : 0)) fail('only exact (+0,+0,+0,1) quaternion is supported');
    }
    const local = [1, 0, 0, 0, 0, 1, -0, 0, -0, 0, 1, 0];
    // 4679c joint 1 supplies actor+1d54 while retaining its ordinary pose
    // quaternion. Do not read unused pose translation on that branch.
    const translation = translationOverride === undefined ? own(resolved, 'translation') : translationOverride;
    local[3] = float(own(translation, 'x'), 'translation.x');
    local[7] = float(own(translation, 'y'), 'translation.y');
    local[11] = float(own(translation, 'z'), 'translation.z');
    const output = getMatrix(destination);
    concat(getMatrix(parent), local, output);
    return output;
  }
  return Object.freeze({
    createMatrix(initial: readonly number[]): symbol {
      enter();
      try {
        if (matrices.size >= maxMatrices) fail('matrix capacity exceeded');
        const copied = snapshot(initial), id = Symbol('owned actor joint matrix');
        matrices.set(id, Object.seal(copied)); return id;
      } finally {busy = false;}
    },
    getMatrix,
    identity(matrix: symbol): void {
      enter();
      try {
        const output = getMatrix(matrix);
        // PSMTXIdentity 8020aefc: actual paired store order, not row-major.
        // Old destination values are not source operands and are not read.
        for (const i of [2, 3, 6, 7, 8, 9, 4, 5, 0, 1, 10, 11]) {
          store(output, i, i === 0 || i === 5 || i === 10 ? 1 : 0);
        }
      } finally {busy = false;}
    },
    translate(matrix: symbol, translation: Readonly<SourceJointVector>): void {
      enter();
      try {translate(getMatrix(matrix), translation);} finally {busy = false;}
    },
    correctShort(matrix: symbol, correction: Readonly<SourceJointVector>): void {
      enter();
      try {correctShort(getMatrix(matrix), correction);} finally {busy = false;}
    },
    scale(matrix: symbol, scaling: Readonly<SourceJointVector>): void {
      enter();
      try {scale(getMatrix(matrix), scaling);} finally {busy = false;}
    },
    copy(source: symbol, destination: symbol): void {
      enter();
      try {copy(getMatrix(source), getMatrix(destination));} finally {busy = false;}
    },
    transformPoint(matrix: symbol, input: Readonly<SourceJointVector>, output: SourceJointVector): void {
      enter();
      try {transformPoint(getMatrix(matrix), input, output);} finally {busy = false;}
    },
    orientTerrainMatrix(matrix: symbol, normal: Readonly<SourceJointVector>, axisA: number, axisB: number): void {
      enter();
      try {orientTerrainMatrix(getMatrix(matrix), normal, axisA, axisB);} finally {busy = false;}
    },
    primaryFoldedPlacement(parent: symbol, current: symbol, next: symbol, end: symbol,
      translation: Readonly<SourceJointVector>, nextTranslation: Readonly<SourceJointVector>,
      correction: Readonly<SourcePrimaryFoldedPlacement>): void {
      enter();
      try {
        if (current === next || current === end || next === end) fail('primary retained matrix slots must be distinct');
        primaryFoldedPlacement(getMatrix(parent), getMatrix(current), getMatrix(next), getMatrix(end),
          translation, nextTranslation, correction);
      } finally {busy = false;}
    },
    rotateShort(axis: 'x' | 'y' | 'z', parent: symbol, destination: symbol, angle: number): void {
      enter();
      try {
        if (axis !== 'x' && axis !== 'y' && axis !== 'z') fail('rotation axis must be x, y or z');
        if (short(angle, 'angle') !== 0) fail('nonzero short rotation is unsupported');
        // Authenticated 800457d4 / 8020b238 / 8020b2a8 and zero sin/cos paths:
        // source signed short 0 (including a host -0) loads as +0 and multiplies
        // positive 80437078=0x38c90fdb. sin returns +0 and cos returns 1.
        // RotTrig's paired merges put -sin in an axis-specific position.
        // See read_archived_actor_traversal_evidence.py. No identity shortcut:
        // every wrapper performs its own source Concat, even for zero angles.
        const rotation = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0];
        rotation[axis === 'x' ? 6 : axis === 'y' ? 8 : 1] = -0;
        concat(getMatrix(parent), rotation, getMatrix(destination));
      } finally {busy = false;}
    },
    composePose(parent: symbol, destination: symbol, pose: symbol,
      translationOverride?: Readonly<SourceJointVector>): void {
      enter();
      try {composePose(parent, destination, pose, translationOverride);} finally {busy = false;}
    },
    composeJoint(parent: symbol, destination: symbol, pose: symbol,
      correction: Readonly<SourceJointVector>, scaling: Readonly<SourceJointVector>,
      translationOverride?: Readonly<SourceJointVector>): void {
      enter();
      try {
        const output = composePose(parent, destination, pose, translationOverride);
        correctShort(output, correction);
        scale(output, scaling);
      } finally {busy = false;}
    },
  });
}
