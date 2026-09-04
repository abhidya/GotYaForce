/* MATCHED  zz_0040edc_ @ 0x80040edc  (16 instructions)
 *
 *   80040edc  9421fff0  stwu r1, -0x10(r1)
 *   80040ee0  7c0802a6  mflr r0
 *   80040ee4  90010014  stw r0, 0x14(r1)
 *   80040ee8  93e1000c  stw r31, 0xc(r1)
 *   80040eec  7c7f1b78  mr r31, r3
 *   80040ef0  38600001  li r3, 1
 *   80040ef4  48156b19  bl 0x80197a0c
 *   80040ef8  907f0000  stw r3, 0(r31)
 *   80040efc  807f0000  lwz r3, 0(r31)
 *   80040f00  809f0004  lwz r4, 4(r31)
 *   80040f04  4bffffb1  bl 0x80040eb4
 *   80040f08  80010014  lwz r0, 0x14(r1)
 *   80040f0c  83e1000c  lwz r31, 0xc(r1)
 *   80040f10  7c0803a6  mtlr r0
 *   80040f14  38210010  addi r1, r1, 0x10
 *   80040f18  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr li bl stw lwz lwz bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 581bbfcba139848aea68c2ad31633e4c52cc5528b2917af52e33d0bc3b9fef7c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int                  field_0;
    int                  field_4;
} S0;

extern int zz_0040eb4_(int, int);
extern int zz_0197a0c_(int);

int f(S0 *p0)
{
    p0->field_0 = zz_0197a0c_(1);
    return zz_0040eb4_(p0->field_0, p0->field_4);
}
