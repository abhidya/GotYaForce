/* MATCHED  zz_008e630_ @ 0x8008e630  (4 instructions)
 *
 *   8008e630  3c80803d  lis r4, -0x7fc3
 *   8008e634  3884a850  addi r4, r4, -0x57b0
 *   8008e638  90640010  stw r3, 0x10(r4)
 *   8008e63c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi stw blr
 *   exact_bytes      : false
 *   source sha256    : 549b1064456fa866b1ef5c16a4e23a2e4b4066b0a3e943d15e303c6868529c79
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803ca850 {
    char pad_0[0x10];
    int                  field_10;
} G803ca850;

extern G803ca850 DAT_803ca850;

void f(int p0)
{
    DAT_803ca850.field_10 = p0;
}
