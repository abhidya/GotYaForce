/* MATCHED  gnt4-HSD_LObjGetLightMaskSpecular-bl @ 0x8024400c  (2 instructions)
 *
 *   8024400c  806db3a8  lwz r3, -0x4c58(r13)
 *   80244010  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 3e7f45e7f90ede500a1d04f42b3e9c1230ab445eed2b404d06f479b69f4a21ad
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436948;

int f(void)
{
    return DAT_80436948;
}
