/* MATCHED  zz_02ade14_ @ 0x802ade14  (4 instructions)
 *
 *   802ade14  3c608043  lis r3, -0x7fbd
 *   802ade18  38631084  addi r3, r3, 0x1084
 *   802ade1c  8063003c  lwz r3, 0x3c(r3)
 *   802ade20  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : 1d4a58d7c7caada16501309a0b1ef79b18d3dae98fa7758f49eea34e5b03e9cd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80431084 {
    char pad_0[0x3c];
    int                  field_3c;
} G80431084;

extern G80431084 DAT_80431084;

int f(void)
{
    return DAT_80431084.field_3c;
}
