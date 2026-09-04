/* MATCHED  zz_0219d94_ @ 0x80219d94  (2 instructions)
 *
 *   80219d94  806db1c8  lwz r3, -0x4e38(r13)
 *   80219d98  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 70a98c8deb14be22b259af8e9ead41720a65f0540a1e242ee35d8db634e5bb15
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436768;

int f(void)
{
    return DAT_80436768;
}
