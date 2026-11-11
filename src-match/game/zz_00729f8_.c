/* MATCHED  zz_00729f8_ @ 0x800729f8  (18 instructions)
 *
 *   800729f8  9421fff0  stwu r1, -0x10(r1)
 *   800729fc  7c0802a6  mflr r0
 *   80072a00  90010014  stw r0, 0x14(r1)
 *   80072a04  93e1000c  stw r31, 0xc(r1)
 *   80072a08  7c7f1b78  mr r31, r3
 *   80072a0c  4bfffa2d  bl 0x80072438
 *   80072a10  7fe3fb78  mr r3, r31
 *   80072a14  388000c1  li r4, 0xc1
 *   80072a18  38a00000  li r5, 0
 *   80072a1c  4bffa6c1  bl 0x8006d0dc
 *   80072a20  801f05e0  lwz r0, 0x5e0(r31)
 *   80072a24  54000734  rlwinm r0, r0, 0, 0x1c, 0x1a
 *   80072a28  901f05e0  stw r0, 0x5e0(r31)
 *   80072a2c  83e1000c  lwz r31, 0xc(r1)
 *   80072a30  80010014  lwz r0, 0x14(r1)
 *   80072a34  7c0803a6  mtlr r0
 *   80072a38  38210010  addi r1, r1, 0x10
 *   80072a3c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl mr li li bl lwz rlwinm stw lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 942aa213673c0875c7d5b0baa17525e183e63b348b42a1a9fa2378709f55d552
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x5e0];
    int                  field_5e0;
} S0;

extern int zz_006d0dc_(int, int, int);
extern int zz_0072438_(void);

void f(S0 *p0)
{
    zz_0072438_();
    zz_006d0dc_(p0, 0xc1, 0);
    p0->field_5e0 = p0->field_5e0 & 0xffffffef;
}
