/** Bounded GG4E splGetHelmite at 80255050. F32 instruction order was read
 * from the authenticated archived ProgramDB, SHA-256 of its 96-byte span:
 * ddf577b38e65a5db55837bf2f2db537277c7aaaf96420e691caa9ddf1ba2c042.
 * RN=nearest, NI=0 is an admission assumption, not a hardware parity claim.
 */
import {addSourceFloat32 as add, fusedMultiplyAddSourceFloat32 as fma} from './source-float.js';

export function sourceHermite(inv: number, t: number, p0: number, p1: number, m0: number, m1: number): number {
  for (const x of [inv,t,p0,p1,m0,m1]) {
    if (!Number.isFinite(x) || !Object.is(x, Math.fround(x))) throw Error('[source-hermite] finite float32 operands required');
  }
  const mul = (a: number, b: number): number => {
    const v = Math.fround(a * b);
    if (!Number.isFinite(v)) throw Error('[source-hermite] float32 overflow unsupported');
    return v;
  };
  const t2 = mul(t,t), inv2 = mul(inv,inv), t3 = mul(t2,t);
  const a = mul(inv2,t3), b = mul(t2,inv), c = mul(mul(3,t2),inv2);
  const twoA = mul(2,a), d = add(a,-b), e = add(d,-b);
  const twoAInv = mul(twoA,inv), h = add(twoAInv,-c);
  const tPlusE = add(t,e), k = add(-twoAInv,c);
  const basis0 = add(1,h);
  let result = mul(p1,k);
  result = fma(p0,basis0,result);
  result = fma(m0,tPlusE,result);
  return fma(m1,d,result);
}
