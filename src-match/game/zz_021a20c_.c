/* MATCHED  zz_021a20c_ @ 0x8021a20c  (3 instructions)
 *
 *   8021a20c  906da7a0  stw r3, -0x5860(r13)
 *   8021a210  908da7a4  stw r4, -0x585c(r13)
 *   8021a214  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 2a998b98eaceab056ce703b62f9cedbd4fc4ce2e818f6db9ec3c8c6b3533ba78
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80435d40;
extern int DAT_80435d44;

void f(int p0, int p1)
{
    DAT_80435d40 = p0;
    DAT_80435d44 = p1;
}
