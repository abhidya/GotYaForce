/** Experimental Dolphin-observed frsqrte model for positive normal inputs.
 * 32 segment starts and adjacent output differences were sampled by executing
 * GG4E instruction 8023961c in Dolphin 2606-97 (JIT64), 2026-11-17.
 * Interpolation and exponent scaling are a model, not hardware proof.
 * See https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Common/FloatUtils.cpp
 * for the independently consulted Dolphin model; no Dolphin source is included.
 */
const starts = [
  0x3feffe8000000000n,
  0x3fef0a4000000000n,
  0x3fee2a8000000000n,
  0x3fed5c8000000000n,
  0x3fec9e4000000000n,
  0x3febedc000000000n,
  0x3feb498000000000n,
  0x3feab00000000000n,
  0x3fea204000000000n,
  0x3fe9994000000000n,
  0x3fe91a0000000000n,
  0x3fe8a1c000000000n,
  0x3fe8304000000000n,
  0x3fe7c48000000000n,
  0x3fe75e4000000000n,
  0x3fe6fd0000000000n,
  0x3fe69fa000000000n,
  0x3fe5f2e000000000n,
  0x3fe554a000000000n,
  0x3fe4c30000000000n,
  0x3fe43c8000000000n,
  0x3fe3bfc000000000n,
  0x3fe34b8000000000n,
  0x3fe2df0000000000n,
  0x3fe2794000000000n,
  0x3fe219c000000000n,
  0x3fe1bfc000000000n,
  0x3fe16ae000000000n,
  0x3fe11a8000000000n,
  0x3fe0ce6000000000n,
  0x3fe0862000000000n,
  0x3fe0416000000000n,
];
const increments = [
  0x1e90000000n,
  0x1c00000000n,
  0x19c0000000n,
  0x17c8000000n,
  0x1610000000n,
  0x1490000000n,
  0x1330000000n,
  0x11f8000000n,
  0x10e8000000n,
  0xfe8000000n,
  0xf08000000n,
  0xe38000000n,
  0xd78000000n,
  0xcc8000000n,
  0xc28000000n,
  0xb98000000n,
  0x15a0000000n,
  0x13cc000000n,
  0x1234000000n,
  0x10d4000000n,
  0xf9c000000n,
  0xe88000000n,
  0xd94000000n,
  0xcb8000000n,
  0xbf0000000n,
  0xb40000000n,
  0xaa0000000n,
  0xa0c000000n,
  0x984000000n,
  0x90c000000n,
  0x898000000n,
  0x82c000000n,
];

export function sourceReciprocalSqrtEstimate(value: number): number {
  if (!(value > 0) || !Number.isFinite(value)) throw new RangeError('positive finite normal value required');
  const view = new DataView(new ArrayBuffer(8));
  view.setFloat64(0, value);
  const input = view.getBigUint64(0);
  const exponent = Number((input >> 52n) & 0x7ffn);
  if (exponent === 0) throw new RangeError('subnormal estimate is not implemented');
  const referenceExponent = exponent % 2 === 1 ? 1023 : 1024;
  const segment = Number((input >> 48n) & 15n) + (referenceExponent === 1024 ? 16 : 0);
  const offset = (input >> 37n) & 2047n;
  const scale = BigInt((exponent - referenceExponent) / 2);
  const resultBits = starts[segment]! - increments[segment]! * offset - (scale << 52n);
  view.setBigUint64(0, resultBits);
  return view.getFloat64(0);
}
