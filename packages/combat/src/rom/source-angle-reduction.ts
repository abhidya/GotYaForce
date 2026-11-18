/** Bounded 8023aca4 argument reduction through the short-angle range.
 * Constants came from the supplied GG4E image. JS
 * operations have not been verified against retail PowerPC execution.
 */
export function sourceReduceHalfPi(x: number): {quadrant: number; head: number; tail: number} {
  if (!Number.isFinite(x)) throw new RangeError('finite angle required');
  const bits = new DataView(new ArrayBuffer(8));
  bits.setFloat64(0, x, false);
  const high = bits.getUint32(0, false) & 0x7fffffff;
  if (high < 0x3fe921fc) return {quadrant: 0, head: x, tail: 0};
  if (high >= 0x400921fc) throw new RangeError('angle outside bounded reduction');
  const sign = x < 0 ? -1 : 1;
  if (high >= 0x4002d97c) {
    // The admitted range selects n=2 in the medium reduction. Near pi the
    // source refines its split constants when the first subtraction cancels.
    const absolute = Math.abs(x), n = 2;
    let r = absolute - n * 1.5707963267341256;
    let correction = n * 6.077100506506192e-11;
    let head = r - correction;
    bits.setFloat64(0, head, false);
    const difference = (high >>> 20) - ((bits.getUint32(0, false) >>> 20) & 0x7ff);
    if (high === 0x400921fb && difference > 16) {
      const t = r;
      const second = n * 6.077100506303966e-11;
      r = t - second;
      correction = n * 2.0222662487959506e-21 - ((t - r) - second);
      head = r - correction;
      bits.setFloat64(0, head, false);
      const refinedDifference = (high >>> 20) - ((bits.getUint32(0, false) >>> 20) & 0x7ff);
      if (refinedDifference > 49) {
        const previous = r;
        const third = n * 2.0222662487111665e-21;
        r = previous - third;
        correction = n * 8.4784276603689e-32 - ((previous - r) - third);
        head = r - correction;
      }
    }
    const tail = (r - head) - correction;
    return {quadrant: sign * 2, head: sign * head, tail: sign * tail};
  }
  let r = x - sign * 1.5707963267341256;
  let correction = 6.077100506506192e-11;
  if (high === 0x3ff921fb) {r -= sign * 6.077100506303966e-11; correction = 2.0222662487959506e-21;}
  const head = r - sign * correction;
  const tail = (r - head) - sign * correction;
  return {quadrant: sign, head, tail};
}
