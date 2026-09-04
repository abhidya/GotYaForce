/* MATCHED  gnt4-HSD_LObjGetNbActive-bl @ 0x80244014  (2 instructions)
 *
 *   80244014  806db3a0  lwz r3, -0x4c60(r13)
 *   80244018  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : ddfe2bb0372108f44cbf6adcf7cae67ab7252f4aff81066607023f7b7ba1ca85
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436940;

int f(void)
{
    return DAT_80436940;
}
