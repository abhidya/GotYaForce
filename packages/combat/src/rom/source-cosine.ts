/** Bounded gnt4-__kernel_cos @ 8023b044, with GG4E DOL coefficients.
 * x is already range-reduced and y is the reduction tail. This candidate has
 * not been compared with retail PowerPC arithmetic and is not wired to gameplay.
 */
export function sourceCosineKernel(x: number, y: number): number {
  if (!Number.isFinite(x) || !Number.isFinite(y) || Math.abs(x) > 0.78539825) throw new RangeError('finite reduced inputs required');
  if (Math.abs(x) < 2 ** -27) return 1;
  const z = x * x;
  const r = z * (0.0416666666666666 + z * (-0.001388888888887411 + z * (0.00002480158728947673 + z * (-0.00000027557314351390663 + z * (2.087572321298175e-9 + z * -1.1359647557788195e-11)))));
  const bytes = new DataView(new ArrayBuffer(8));
  bytes.setFloat64(0, Math.abs(x), false);
  const high = bytes.getUint32(0, false);
  if (high < 0x3fd33333) return 1 - (0.5 * z - (z * r - x * y));
  // Retail constructs qx by subtracting 0x200000 from the absolute high word.
  let qx = 0.28125;
  if (high < 0x3fe90001) {bytes.setUint32(0, high - 0x200000, false); bytes.setUint32(4, 0, false); qx = bytes.getFloat64(0, false);}
  return (1 - qx) - ((0.5 * z - qx) - (z * r - x * y));
}
