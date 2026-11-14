/** Actual7de64..7de88 signed-short conversion and single-precision yaw.
 * Source cell804379d8=4330000080000000,804379ac=38c90fdb and804379a8=+0
 * are independently selected by projectile-flight-prefix-evidence-2026-11-14.
 * RN=00/NI=0 are explicit model preconditions, not observed console state.
 * No host trigonometry or reciprocal-square-root estimate is substituted.
 */
const bits = new DataView(new ArrayBuffer(8));
bits.setUint32(0,0x38c90fdb,false);
const headingScale = bits.getFloat32(0,false);
const signedBias = 4503601774854144; // Exact4330000080000000
export function sourceProjectileHeadingRadians(rawHeading: number): number {
  if (!Number.isInteger(rawHeading) || rawHeading < 0 || rawHeading > 65535)
    throw Error('[projectile-heading] unsigned source heading bits required');
  const signed = rawHeading << 16 >> 16;
  bits.setUint32(0,0x43300000,false);
  bits.setUint32(4,(signed ^ 0x80000000) >>> 0,false);
  // The subtraction is exact in binary64 and the signed16 result is exactf32.
  // Its product with the24-bit constant has at most40 significant bits, so
  // binary64 preserves the exact product before this one fmuls rounding.
  const converted = Math.fround(bits.getFloat64(0,false)-signedBias);
  return Math.fround(headingScale*converted);
}

/**7de80 loads +0;7e024 negates it for the first actual RotRad X call. */
export function sourceProjectileInitialPitch(): number {return -0;}
