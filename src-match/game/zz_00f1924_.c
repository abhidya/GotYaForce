/* MATCHED  zz_00f1924_ @ 0x800f1924  (2 instructions)
 *
 *   800f1924  806dada8  lwz r3, -0x5258(r13)
 *   800f1928  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 464c277acaeb57b317e1b43022a7317d19e7ea7ffebfd2594cb32810d519998c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436348;

int f(void)
{
    return DAT_80436348;
}
