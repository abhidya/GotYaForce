/* MATCHED  zz_008e600_ @ 0x8008e600  (4 instructions)
 *
 *   8008e600  3c80803d  lis r4, -0x7fc3
 *   8008e604  3884a850  addi r4, r4, -0x57b0
 *   8008e608  90640008  stw r3, 8(r4)
 *   8008e60c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi stw blr
 *   exact_bytes      : false
 *   source sha256    : 2cc4bb9188a2b86e1cbad1f1f7a2422e5098ff825c7a47e37183eb0bec2cc934
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803ca850 {
    char pad_0[0x8];
    int                  field_8;
} G803ca850;

extern G803ca850 DAT_803ca850;

void f(int p0)
{
    DAT_803ca850.field_8 = p0;
}
