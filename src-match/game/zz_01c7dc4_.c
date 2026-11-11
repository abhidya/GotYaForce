/* MATCHED  zz_01c7dc4_ @ 0x801c7dc4  (4 instructions)
 *
 *   801c7dc4  3c80803d  lis r4, -0x7fc3
 *   801c7dc8  38845d78  addi r4, r4, 0x5d78
 *   801c7dcc  9064001c  stw r3, 0x1c(r4)
 *   801c7dd0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi stw blr
 *   exact_bytes      : false
 *   source sha256    : 636dc3752d59e5368cb93fe7aabb9b7b9f6a9d835579c9ade92e4a18753bfe82
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803d5d78 {
    char pad_0[0x1c];
    int                  field_1c;
} G803d5d78;

extern G803d5d78 DAT_803d5d78;

void f(int p0)
{
    DAT_803d5d78.field_1c = p0;
}
