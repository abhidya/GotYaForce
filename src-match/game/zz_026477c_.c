/* MATCHED  zz_026477c_ @ 0x8026477c  (9 instructions)
 *
 *   8026477c  9421fff0  stwu r1, -0x10(r1)
 *   80264780  7c0802a6  mflr r0
 *   80264784  90010014  stw r0, 0x14(r1)
 *   80264788  80630004  lwz r3, 4(r3)
 *   8026478c  48003c69  bl 0x802683f4
 *   80264790  80010014  lwz r0, 0x14(r1)
 *   80264794  7c0803a6  mtlr r0
 *   80264798  38210010  addi r1, r1, 0x10
 *   8026479c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2e517b0b14283a0d0d5b0734c147d2f453cec15a269b22928777ef689b596eab
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683f4_(int);

int f(S0 *p0)
{
    return zz_02683f4_(p0->field_4);
}
