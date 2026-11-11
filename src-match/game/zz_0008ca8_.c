/* MATCHED  zz_0008ca8_ @ 0x80008ca8  (19 instructions)
 *
 *   80008ca8  9421fff0  stwu r1, -0x10(r1)
 *   80008cac  7c0802a6  mflr r0
 *   80008cb0  90010014  stw r0, 0x14(r1)
 *   80008cb4  93e1000c  stw r31, 0xc(r1)
 *   80008cb8  7c7f1b78  mr r31, r3
 *   80008cbc  48000039  bl 0x80008cf4
 *   80008cc0  881f0019  lbz r0, 0x19(r31)
 *   80008cc4  7c000775  extsb. r0, r0
 *   80008cc8  41820018  beq 0x80008ce0
 *   80008ccc  807f0010  lwz r3, 0x10(r31)
 *   80008cd0  8063000c  lwz r3, 0xc(r3)
 *   80008cd4  80630000  lwz r3, 0(r3)
 *   80008cd8  482517f5  bl 0x8025a4cc
 *   80008cdc  906dac64  stw r3, -0x539c(r13)
 *   80008ce0  80010014  lwz r0, 0x14(r1)
 *   80008ce4  83e1000c  lwz r31, 0xc(r1)
 *   80008ce8  7c0803a6  mtlr r0
 *   80008cec  38210010  addi r1, r1, 0x10
 *   80008cf0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl lbz extsb. beq lwz lwz lwz bl stw lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 82159eb78f568707b8d480015522770f7452376f9396e25918eba372e4aa1042
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0_10_c {
    int                  field_0;
} S0_10_c;

typedef struct S0_10 {
    char pad_0[0xc];
    S0_10_c *            field_c;
} S0_10;

typedef struct S0 {
    char pad_0[0x10];
    S0_10 *              field_10;
    char pad_14[0x5];
    char                 field_19;
} S0;

extern int DAT_80436204;

extern int FUN_8025a4cc(int);
extern int zz_0008cf4_(void);

void f(S0 *p0)
{
    zz_0008cf4_();
    if (p0->field_19 != 0)
        DAT_80436204 = FUN_8025a4cc(p0->field_10->field_c->field_0);
}
