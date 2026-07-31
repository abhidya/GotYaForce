let lo = 0;
let hi = 0;

/**
 * Advance the GameCube PRNG global (zz_0005630_ @0x80005630).
 *
 * ROM behavior (DAT_804360c4 is a 16-bit unsigned word):
 *   1. result = DAT_804360c4 * 3
 *   2. highByte = (result >> 8) & 0xff
 *   3. newLo   = (DAT_804360c4 & 0xff) + highByte   (keep low byte)
 *   4. DAT_804360c4 = (highByte << 8) | newLo
 *
 * The current `hi`/`lo` split mirrors this exactly:
 *   state = (hi * 0x100 + lo) * 3
 *   highByte = (state >> 8) & 0xff
 *   hi = highByte
 *   lo = (lo + highByte) & 0xff
 */
export function stepPrng(): number {
  const state = (hi * 0x100 + lo) * 3;
  const highByte = (state >> 8) & 0xff;
  hi = highByte;
  lo = (lo + highByte) & 0xff;
  return lo;
}

export function resetPrng(h: number, l: number): void {
  hi = h & 0xff;
  lo = l & 0xff;
}
