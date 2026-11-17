/** Bounded transcription of gnt4-__ieee754_acos @ 80239410.
 * Coefficients are binary64 values read from the supplied GG4E DOL data5.
 * Only |x| < 0.5 is transcribed here; the square-root paths remain to port.
 * JavaScript arithmetic has not yet been compared to retail PowerPC execution,
 * so this is not a bit-exact or production-parity claim.
 */
export function sourceAcosSmall(x: number): number {
  if (!Number.isFinite(x) || Math.abs(x) >= 0.5) throw new RangeError('sourceAcosSmall requires finite |x| < 0.5');
  const pio2 = 1.5707963267948966;
  if (Math.abs(x) < 2 ** -57) return pio2;
  const z = x * x;
  const p = z * (0.16666666666666666 + z * (-0.3255658186224009 + z * (0.20121253213486293 + z * (-0.04005553450067941 + z * (0.0007915349942898145 + z * 0.00003479331075960212)))));
  const q = 1 + z * (-2.403394911734414 + z * (2.0209457602335057 + z * (-0.6882839716054533 + z * 0.07703815055590194)));
  return pio2 - (x - (6.123233995736766e-17 - x * (p / q)));
}

/** Positive upper-domain 80239410 candidate. The caller must supply the real
 * frsqrte estimate; no Math.sqrt substitute is used in this implementation.
 * Its binary64 operation rounding still requires comparison with retail. */
export function sourceAcosUpper(x: number, reciprocalSqrtEstimate: (value: number) => number): number {
  if (!Number.isFinite(x) || x < 0.5 || x >= 1) throw new RangeError('sourceAcosUpper requires 0.5 <= x < 1');
  const z = 0.5 * (1 - x);
  let estimate = reciprocalSqrtEstimate(z);
  if (!Number.isFinite(estimate) || estimate <= 0) throw new RangeError('positive finite frsqrte estimate required');
  for (let i = 0; i < 3; i++) estimate = 0.5 * estimate * -(z * estimate * estimate - 3);
  const root = z * 0.5 * estimate * -(z * estimate * estimate - 3);
  const bits = new DataView(new ArrayBuffer(8));
  bits.setFloat64(0, root, false); bits.setUint32(4, 0, false);
  const highRoot = bits.getFloat64(0, false);
  const p = z * (0.16666666666666666 + z * (-0.3255658186224009 + z * (0.20121253213486293 + z * (-0.04005553450067941 + z * (0.0007915349942898145 + z * 0.00003479331075960212)))));
  const q = 1 + z * (-2.403394911734414 + z * (2.0209457602335057 + z * (-0.6882839716054533 + z * 0.07703815055590194)));
  return 2 * (highRoot + ((p / q) * root + -(highRoot * highRoot - z) / (root + highRoot)));
}
