/* MATCHED  gnt4-HSD_LObjGetLightMaskAlpha-bl @ 0x80244004  (2 instructions)
 *
 *   80244004  806db3b0  lwz r3, -0x4c50(r13)
 *   80244008  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 2e66d781a3aa06f11916aabf2d7ccf6aae3e82a4ac37b45fc6d4466fb386e05b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436950;

int f(void)
{
    return DAT_80436950;
}
