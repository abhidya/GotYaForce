/* MATCHED  zz_02ab458_ @ 0x802ab458  (2 instructions)
 *
 *   802ab458  3860301f  li r3, 0x301f
 *   802ab45c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li blr
 *   exact_bytes      : true
 *   source sha256    : 07af0afca00a7f4b0bcb4e5d1bec9b288036924bb451647775085ae320191214
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(void)
{
    return 0x301f;
}
