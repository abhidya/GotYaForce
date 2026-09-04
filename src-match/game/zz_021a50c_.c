/* MATCHED  zz_021a50c_ @ 0x8021a50c  (2 instructions)
 *
 *   8021a50c  906db1f0  stw r3, -0x4e10(r13)
 *   8021a510  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : 087e30443684c9253f03386db5b11cf5e6a2abdc1f0f0d6bad91df638373ee7d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436790;

void f(int p0)
{
    DAT_80436790 = p0;
}
