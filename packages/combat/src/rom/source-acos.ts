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
