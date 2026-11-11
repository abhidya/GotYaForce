/* MATCHED  zz_02ade24_ @ 0x802ade24  (4 instructions)
 *
 *   802ade24  3c608043  lis r3, -0x7fbd
 *   802ade28  38631084  addi r3, r3, 0x1084
 *   802ade2c  80630038  lwz r3, 0x38(r3)
 *   802ade30  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : d436aef5a9713ebacac6710cfec145aa6fe036d1109bd7789421beb53f1f2385
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80431084 {
    char pad_0[0x38];
    int                  field_38;
} G80431084;

extern G80431084 DAT_80431084;

int f(void)
{
    return DAT_80431084.field_38;
}
