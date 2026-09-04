/* MATCHED  zz_0218548_ @ 0x80218548  (2 instructions)
 *
 *   80218548  906db180  stw r3, -0x4e80(r13)
 *   8021854c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : 8574d321bdf3cee997f60980ec1d56184c5d6cced913b0d5363dbafca725b46c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436720;

void f(int p0)
{
    DAT_80436720 = p0;
}
