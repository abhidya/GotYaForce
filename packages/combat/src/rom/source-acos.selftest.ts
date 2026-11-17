import {sourceReciprocalSqrtEstimate} from './source-reciprocal-sqrt-estimate.js';
import {sourceTargetDistanceSeed} from './source-target-distance.js';
import {sourceAcosSmall, sourceAcosUpper, sourceAcosFloatNonnegative} from './source-acos.js';
export function runSourceAcosSmallSelfTest(): void {
  // Controlled calls to GG4E 8023cc8c in Dolphin, with frsqrte values
  // captured from 8023961c. These are emulator samples, not console proof.
  const captures: Array<[number, string | null, string]> = [
    [0, null, '3ff921fb60000000'], [0.10000000149011612, null, '3ff787b220000000'],
    [0.25, null, '3ff51700e0000000'], [0.49900001287460327, null, '3ff0c60ca0000000'],
    [0.5, '3ffffe8000000000', '3ff0c15240000000'], [0.5000010132789612, '400000082c000000', '3ff0c15100000000'],
    [0.625, '4002794000000000', '3feca94940000000'], [0.75, '40069fa000000000', '3fe720a3a0000000'],
    [0.8999999761581421, '4011e3c900000000', '3fdcdd9fc0000000'], [0.9900000095367432, '402c498890000000', '3fc21df6a0000000'],
    [0.9998999834060669, '4061ad2800000000', '3f8cf73aa0000000'], [1, null, '0000000000000000'],
  ];
  const bits = new DataView(new ArrayBuffer(8));
  for (const [x, seed, expected] of captures) {
    const actual = sourceAcosFloatNonnegative(x, () => {
      if (seed === null) throw Error(`unexpected frsqrte at ${x}`);
      bits.setBigUint64(0, BigInt(`0x${seed}`));
      return bits.getFloat64(0);
    });
    bits.setFloat64(0, actual);
    if (bits.getBigUint64(0) !== BigInt(`0x${expected}`)) throw Error(`Dolphin acos mismatch at ${x}`);
    const modelResult = sourceAcosFloatNonnegative(x, sourceReciprocalSqrtEstimate);
    bits.setFloat64(0, modelResult);
    if (bits.getBigUint64(0) !== BigInt(`0x${expected}`)) throw Error(`model-backed Dolphin acos mismatch at ${x}`);
  }
  for (const [value, expected] of [
    [0.25, '3ffffe8000000000'], [0.5, '3ff69fa000000000'], [1, '3feffe8000000000'],
    [2, '3fe69fa000000000'], [0.1875, '4002794000000000'], [0.125, '40069fa000000000'],
    [0.050000011920928955, '4011e3c900000000'], [0.004999995231628418, '402c498890000000'],
    [0.000050008296966552734, '4061ad2800000000'],
  ] as const) {
    bits.setFloat64(0, sourceReciprocalSqrtEstimate(value));
    if (bits.getBigUint64(0) !== BigInt(`0x${expected}`)) throw Error(`Dolphin frsqrte mismatch at ${value}`);
  }
  for (let i = -4999; i <= 4999; i++) {
    const x = i / 10000;
    if (Math.abs(sourceAcosSmall(x) - Math.acos(x)) > 5e-16) throw Error(`acos candidate differs at ${x}`);
  }
  // Existing model-backed Dolphin seed covers z=.25 when x=.5. This is not
  // an independently authenticated physical Gekko measurement.
  const seed = sourceTargetDistanceSeed(0.25);
  if (seed === undefined || Math.abs(sourceAcosUpper(0.5, () => seed) - Math.acos(0.5)) > 5e-16) throw Error('model-backed .25 estimate');
  // This mathematical estimate is a test fixture, not a retail frsqrte oracle.
  for (let i = 5000; i < 10000; i++) {
    const x = i / 10000;
    const result = sourceAcosUpper(x, z => 1 / Math.sqrt(z));
    if (Math.abs(result - Math.acos(x)) > 5e-16) throw Error(`upper acos differs at ${x}`);
  }
  for (let i = 0; i <= 10000; i++) {
    const x = Math.fround(i / 10000);
    const result = sourceAcosFloatNonnegative(x, z => 1 / Math.sqrt(z));
    if (Math.abs(result - Math.fround(Math.acos(x))) > 1.2e-7) throw Error(`float acos differs at ${x}`);
  }
  for (const x of [-0.5, 0.5, Infinity, NaN]) {
    let rejected = false;
    try { sourceAcosSmall(x); } catch (e) { rejected = e instanceof RangeError; }
    if (!rejected) throw Error(`expected rejection for ${x}`);
  }
  console.log('[source-acos-small] mathematical sanity checks pass; retail parity not yet verified');
}
