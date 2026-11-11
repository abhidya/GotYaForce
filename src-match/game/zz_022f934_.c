/* MATCHED  zz_022f934_ @ 0x8022f934  (4 instructions)
 *
 *   8022f934  3c80803f  lis r4, -0x7fc1
 *   8022f938  388475dc  addi r4, r4, 0x75dc
 *   8022f93c  906400a0  stw r3, 0xa0(r4)
 *   8022f940  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi stw blr
 *   exact_bytes      : false
 *   source sha256    : 0d8ea3d6dd2470fef5196d87f7d7b6c32b3197c1a01f6ca1deb6e7f26633bca8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803f75dc {
    char pad_0[0xa0];
    int                  field_a0;
} G803f75dc;

extern G803f75dc DAT_803f75dc;

void f(int p0)
{
    DAT_803f75dc.field_a0 = p0;
}
