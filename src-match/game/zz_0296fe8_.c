/* MATCHED  zz_0296fe8_ @ 0x80296fe8  (2 instructions)
 *
 *   80296fe8  3860ffff  li r3, -1
 *   80296fec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li blr
 *   exact_bytes      : true
 *   source sha256    : f10edbb776cd156f11a352d0fc97c237eacc912da019dd15a07d68b9fe4f3aef
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(void)
{
    return -1;
}
