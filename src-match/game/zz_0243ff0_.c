/* MATCHED  zz_0243ff0_ @ 0x80243ff0  (3 instructions)
 *
 *   80243ff0  38000000  li r0, 0
 *   80243ff4  900db388  stw r0, -0x4c78(r13)
 *   80243ff8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : c37ca624ef97c076a7f000ea2382188a3abdc7f4107ca53cd783b2fb55c4ac5d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436928;

void f(void)
{
    DAT_80436928 = 0;
}
