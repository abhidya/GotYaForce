/* MATCHED  zz_021c73c_ @ 0x8021c73c  (2 instructions)
 *
 *   8021c73c  806db218  lwz r3, -0x4de8(r13)
 *   8021c740  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 8e9f4340886b49ba820f1abf010f65fcaef78a2b3f003a31b1f0031df07429e8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804367b8;

int f(void)
{
    return DAT_804367b8;
}
