/** Experimental fres candidate derived from controlled Dolphin observations.
 * Only exact finite float32 inputs in (0.5,4] are admitted. The 32 segment
 * coefficients and 256-bit input steps were independently inferred from the
 * captured interval grid and fine sweep; exponent scaling is checked against
 * the separate 65-input sweep. This is not a physical-console proof, a general
 * PPC implementation, or an automatic gameplay fallback. */
const BASE = [
  0x3f7ff800,0x3f783800,0x3f70ea00,0x3f6a0800,0x3f638800,0x3f5d6200,0x3f579000,0x3f520800,
  0x3f4cc800,0x3f47ca00,0x3f430800,0x3f3e8000,0x3f3a2c00,0x3f360800,0x3f321400,0x3f2e4a00,
  0x3f2aa800,0x3f272c00,0x3f23d600,0x3f209e00,0x3f1d8800,0x3f1a9000,0x3f17ae00,0x3f14f800,
  0x3f124400,0x3f0fbe00,0x3f0d3800,0x3f0ade00,0x3f088400,0x3f065000,0x3f041c00,0x3f020c00,
] as const;
const SLOPE = [993,935,881,832,787,746,708,672,639,609,581,554,530,507,485,465,
  446,428,411,395,380,366,347,347,323,323,301,301,282,282,264,262] as const;

export function sourceReciprocalEstimateBounded(value: number): number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value)) || value <= 0.5 || value > 4)
    throw new RangeError('reciprocal estimate requires float32 in (0.5,4]');
  const bytes = new DataView(new ArrayBuffer(4));
  bytes.setFloat32(0, value, false);
  const input = bytes.getUint32(0, false), exponent = (input >>> 23) & 255;
  const segment = (input >>> 18) & 31, offset = (input & 0x3ffff) >>> 8;
  const output = BASE[segment]! - Math.floor((SLOPE[segment]! * offset + 1) / 2) - (exponent - 127) * 0x800000;
  bytes.setUint32(0, output, false);
  return bytes.getFloat32(0, false);
}
