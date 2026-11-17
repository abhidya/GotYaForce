/** Bounded 8023aca4 argument reduction for |x| below its 0x4002d97c
 * high-word boundary. Constants came from the supplied GG4E image. JS
 * operations have not been verified against retail PowerPC execution.
 */
export function sourceReduceHalfPi(x: number): {quadrant: number; head: number; tail: number} {
  if (!Number.isFinite(x)) throw new RangeError('finite angle required');
  const bits = new DataView(new ArrayBuffer(8));
  bits.setFloat64(0, x, false);
  const high = bits.getUint32(0, false) & 0x7fffffff;
  if (high < 0x3fe921fc) return {quadrant: 0, head: x, tail: 0};
  if (high >= 0x4002d97c) throw new RangeError('angle outside bounded reduction');
  const sign = x < 0 ? -1 : 1;
  let r = x - sign * 1.5707963267341256;
  let correction = 6.077100506506192e-11;
  if (high === 0x3ff921fb) {r -= sign * 6.077100506303966e-11; correction = 2.0222662487959506e-21;}
  const head = r - sign * correction;
  const tail = (r - head) - sign * correction;
  return {quadrant: sign, head, tail};
}
