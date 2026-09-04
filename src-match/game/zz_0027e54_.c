/* MATCHED  zz_0027e54_ @ 0x80027e54  (3 instructions)
 *
 *   80027e54  38000000  li r0, 0
 *   80027e58  900dab74  stw r0, -0x548c(r13)
 *   80027e5c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : d5cf9f5759c18ecda8e2965ff3b26e7b66f5252c812f843f858dfcbe8deffada
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436114;

void f(void)
{
    DAT_80436114 = 0;
}
