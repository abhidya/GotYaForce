let lo = 0;
let hi = 0;

export function stepPrng(): number {
  const state = (hi * 0x100 + lo) * 3;
  const highByte = (state >> 8) & 0xff;
  hi = highByte;
  lo = (lo + highByte) & 0xff;
  return lo;
}

export function resetPrng(h: number, l: number): void {
  hi = h;
  lo = l;
}
