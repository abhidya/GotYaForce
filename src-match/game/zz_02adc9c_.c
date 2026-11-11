/* MATCHED  zz_02adc9c_ @ 0x802adc9c  (4 instructions)
 *
 *   802adc9c  3c608043  lis r3, -0x7fbd
 *   802adca0  38631084  addi r3, r3, 0x1084
 *   802adca4  80630034  lwz r3, 0x34(r3)
 *   802adca8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : 0a56bc9e09e81726a73c0c2a0edc6ef4ed4b7f7a68fb4b31ad8695a407328dcd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80431084 {
    char pad_0[0x34];
    int                  field_34;
} G80431084;

extern G80431084 DAT_80431084;

int f(void)
{
    return DAT_80431084.field_34;
}
