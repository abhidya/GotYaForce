/* MATCHED  zz_0296ff0_ @ 0x80296ff0  (2 instructions)
 *
 *   80296ff0  3860ffff  li r3, -1
 *   80296ff4  4e800020  blr
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
