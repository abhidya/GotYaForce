let lo = 0;
let hi = 0;

// 8-bit RNG state (DAT_804360c6/c7) — initialized by zz_00055e0_ @0x800055e0
let _rng8_lo = 0;
let _rng8_hi = 0;

/**
 * zz_00055e0_ @0x800055e0 — Initialize the 8-bit RNG globals.
 *
 * Original decomp:
 *   void zz_00055e0_(void) {
 *     DAT_804360c7 = 1;
 *     DAT_804360c6 = 0xc3;
 *     DAT_804360c4 = 0x1c3;
 *     return;
 *   }
 *
 * Called from zz_0018238_ and zz_003fc84_ during boot/setup sequences.
 */
export function initRng8(): void {
  _rng8_hi = 1;
  _rng8_lo = 0xc3;
  // Also initialize the 16-bit PRNG state (DAT_804360c4)
  hi = 0x01;
  lo = 0xc3;
}

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

/**
 * Read the 8-bit RNG state (DAT_804360c6/c7).
 * Used by zz_00055fc_ (the 8-bit RNG generator @0x800055fc).
 */
export function getRng8(): [number, number] {
  return [_rng8_lo, _rng8_hi];
}

/**
 * Advance the 8-bit RNG (zz_00055fc_ @0x800055fc).
 *
 * ROM behavior:
 *   next = (((hi<<8|lo)*3)>>8) & 0xFF
 *   lo = next
 *   hi = (hi*3 + carry) & 0xFF
 *
 * Returns the new low byte (the RNG result).
 */
export function stepRng8(): number {
  const state = (_rng8_hi * 0x100 + _rng8_lo) * 3;
  const next = (state >> 8) & 0xff;
  const carry = (_rng8_hi * 3) & 0xff;
  _rng8_lo = next;
  _rng8_hi = carry;
  return next;
}
