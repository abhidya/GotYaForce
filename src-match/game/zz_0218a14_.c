/* MATCHED  zz_0218a14_ @ 0x80218a14  (2 instructions)
 *
 *   80218a14  806db1d0  lwz r3, -0x4e30(r13)
 *   80218a18  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 23746a67dc333b27963b3dcc4d22cc6ab8c084bf6aaadddfa306cd5ef8d7c527
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436770;

int f(void)
{
    return DAT_80436770;
}
