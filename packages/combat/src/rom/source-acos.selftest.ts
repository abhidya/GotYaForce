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
  // Positive subnormal, exponent-boundary and distant exponent captures.
  const extremeCaptures = [
    ['0000000000000001', '617ffe8000000000'], ['0000000000000002', '61769fa000000000'],
    ['0000000000000003', '6172794000000000'], ['0000000000000100', '613ffe8000000000'],
    ['0000010000000000', '603ffe8000000000'], ['0007ffffffffffff', '5fe6a04b98000000'],
    ['0008000000000000', '5fe69fa000000000'], ['000fffffffffffff', '5fe000082c000000'],
    ['0010000000000000', '5fdffe8000000000'], ['0010000000000001', '5fdffe8000000000'],
    ['0123456789abcdef', '5f549e8464000000'], ['123456789abcdef0', '56cc62b2d0000000'],
    ['2000000000000000', '4fe69fa000000000'], ['3e40000000000000', '40c69fa000000000'],
    ['3e50000000000000', '40bffe8000000000'], ['7fefffffffffffff', '1ff000082c000000'],
  ];
  for (const [input, expected] of extremeCaptures) {
    bits.setBigUint64(0, BigInt(`0x${input}`));
    const result = sourceReciprocalSqrtEstimate(bits.getFloat64(0));
    bits.setFloat64(0, result);
    if (bits.getBigUint64(0) !== BigInt(`0x${expected}`)) throw Error(`Dolphin frsqrte extreme ${input}`);
  }
  // Separate midpoint/end captures exercise the interpolation in all 32
  // segments, not only the two samples used to derive each segment.
  const segmentCaptures = [
    ['3fef845e90000000', '3fef0a1e90000000'],
    ['3fee9a5c00000000', '3fee2a5c00000000'],
    ['3fedc399c0000000', '3fed5c99c0000000'],
    ['3fecfd77c8000000', '3fec9e57c8000000'],
    ['3fec461610000000', '3febedd610000000'],
    ['3feb9b9490000000', '3feb495490000000'],
    ['3feafcd330000000', '3feab01330000000'],
    ['3fea6831f8000000', '3fea2051f8000000'],
    ['3fe9dcb0e8000000', '3fe99910e8000000'],
    ['3fe959afe8000000', '3fe91a0fe8000000'],
    ['3fe8ddef08000000', '3fe8a1cf08000000'],
    ['3fe868ee38000000', '3fe8300e38000000'],
    ['3fe7fa6d78000000', '3fe7c48d78000000'],
    ['3fe7916cc8000000', '3fe75e4cc8000000'],
    ['3fe72dac28000000', '3fe6fd0c28000000'],
    ['3fe6ceab98000000', '3fe6a04b98000000'],
    ['3fe64935a0000000', '3fe5f2b5a0000000'],
    ['3fe5a3c3cc000000', '3fe55493cc000000'],
    ['3fe50be234000000', '3fe4c31234000000'],
    ['3fe47fc0d4000000', '3fe43c70d4000000'],
    ['3fe3fe1f9c000000', '3fe3bfaf9c000000'],
    ['3fe385ae88000000', '3fe34b8e88000000'],
    ['3fe3153d94000000', '3fe2deed94000000'],
    ['3fe2ac2cb8000000', '3fe2794cb8000000'],
    ['3fe2498bf0000000', '3fe219cbf0000000'],
    ['3fe1eccb40000000', '3fe1bfcb40000000'],
    ['3fe1954aa0000000', '3fe16acaa0000000'],
    ['3fe142ba0c000000', '3fe11a8a0c000000'],
    ['3fe0f47984000000', '3fe0ce6984000000'],
    ['3fe0aa390c000000', '3fe086090c000000'],
    ['3fe063c898000000', '3fe0416898000000'],
    ['3fe020b82c000000', '3fe000082c000000'],
  ];
  for (let segment = 0; segment < segmentCaptures.length; segment++) {
    for (let j = 0; j < 2; j++) {
      const exponent = segment < 16 ? 1023n : 1024n;
      const input = (exponent << 52n) | (BigInt(segment % 16) << 48n) | (BigInt(j ? 2047 : 1023) << 37n);
      bits.setBigUint64(0, input);
      const result = sourceReciprocalSqrtEstimate(bits.getFloat64(0));
      bits.setFloat64(0, result);
      if (bits.getBigUint64(0) !== BigInt(`0x${segmentCaptures[segment]![j]!}`)) throw Error(`Dolphin frsqrte segment ${segment}/${j}`);
    }
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
