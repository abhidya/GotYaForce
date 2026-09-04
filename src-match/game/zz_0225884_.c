/* MATCHED  zz_0225884_ @ 0x80225884  (2 instructions)
 *
 *   80225884  806db268  lwz r3, -0x4d98(r13)
 *   80225888  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 03e835fd09a9df07cde8555ecb4773410187b318e7a076f9a6a4406813115dd1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436808;

int f(void)
{
    return DAT_80436808;
}
