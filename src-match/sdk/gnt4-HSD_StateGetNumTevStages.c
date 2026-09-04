/* MATCHED  gnt4-HSD_StateGetNumTevStages @ 0x80241e60  (2 instructions)
 *
 *   80241e60  806db370  lwz r3, -0x4c90(r13)
 *   80241e64  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : a0740188aa25252270e57b4c8e8b9d89364f206a5a9b50b57960d147cb32efe5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436910;

int f(void)
{
    return DAT_80436910;
}
