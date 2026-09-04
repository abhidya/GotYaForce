/* MATCHED  zz_022d840_ @ 0x8022d840  (2 instructions)
 *
 *   8022d840  38600000  li r3, 0
 *   8022d844  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li blr
 *   exact_bytes      : true
 *   source sha256    : 214473976f249725daa3acb732e1fd55caed95079e4db214022146d6de4d1783
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(void)
{
    return 0;
}
