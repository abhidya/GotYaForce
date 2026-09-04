/* MATCHED  gnt4-HSD_LObjGetLightMaskDiffuse-bl @ 0x80243ffc  (2 instructions)
 *
 *   80243ffc  806db3a4  lwz r3, -0x4c5c(r13)
 *   80244000  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 6fb2361c06c7fb34ca4cec079da33c24ada91a6c264810cb1279ca56742cf3e3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436944;

int f(void)
{
    return DAT_80436944;
}
