/* MATCHED  zz_02aa02c_ @ 0x802aa02c  (9 instructions)
 *
 *   802aa02c  9421fff0  stwu r1, -0x10(r1)
 *   802aa030  7c0802a6  mflr r0
 *   802aa034  90010014  stw r0, 0x14(r1)
 *   802aa038  80630040  lwz r3, 0x40(r3)
 *   802aa03c  4bfee79d  bl 0x802987d8
 *   802aa040  80010014  lwz r0, 0x14(r1)
 *   802aa044  7c0803a6  mtlr r0
 *   802aa048  38210010  addi r1, r1, 0x10
 *   802aa04c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1325bfc92d560104df878a214b1f78961c8a3e0e8c30d2e3eb820327481261ba
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x40];
    int                  field_40;
} S0;

extern int zz_02987d8_(int);

int f(S0 *p0)
{
    return zz_02987d8_(p0->field_40);
}
