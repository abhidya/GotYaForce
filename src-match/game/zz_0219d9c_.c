/* MATCHED  zz_0219d9c_ @ 0x80219d9c  (2 instructions)
 *
 *   80219d9c  806db1cc  lwz r3, -0x4e34(r13)
 *   80219da0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : f91225a2f62b4902478c44787a3807799e390d23ee516f5cf9b5e0f7e741a01a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043676c;

int f(void)
{
    return DAT_8043676c;
}
