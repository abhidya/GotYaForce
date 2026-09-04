/* MATCHED  gnt4-HSD_JObjGetCurrent @ 0x80250bb4  (2 instructions)
 *
 *   80250bb4  806db3f4  lwz r3, -0x4c0c(r13)
 *   80250bb8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : cf80b2e95bcbad12c0608fbec5ef2fce53842ed8846e38f7984a6534f2aafe94
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436994;

int f(void)
{
    return DAT_80436994;
}
