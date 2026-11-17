/** Bounded transcription of gnt4-__kernel_sin @ 8023bf8c, direct (iy=0)
 * path. Coefficients are binary64 values from the user-supplied GG4E DOL.
 * Only finite reduced arguments are admitted. PowerPC rounding/retail output
 * have not yet been verified; this candidate is not wired into gameplay.
 */
export function sourceSineKernel(x: number): number {
  if (!Number.isFinite(x) || Math.abs(x) > Math.PI / 4) throw new RangeError('sourceSineKernel requires a finite reduced argument');
  if (Math.abs(x) < 2 ** -27) return x;
  const z = x * x, v = z * x;
  const r = 0.00833333333332249 + z * (-0.0001984126982985795 + z * (0.0000027557313707070068 + z * (-0.000000025050760253406863 + z * 1.58969099521155e-10)));
  return x + v * (-0.16666666666666632 + z * r);
}
