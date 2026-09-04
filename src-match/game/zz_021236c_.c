/* MATCHED  zz_021236c_ @ 0x8021236c  (2 instructions)
 *
 *   8021236c  806db004  lwz r3, -0x4ffc(r13)
 *   80212370  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 7c62a38592c12570e2aedbd70a463af68779cd88daf7447aa7a5b5bdae4de16b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804365a4;

int f(void)
{
    return DAT_804365a4;
}
