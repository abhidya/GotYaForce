/* MATCHED  zz_00f5fb8_ @ 0x800f5fb8  (14 instructions)
 *
 *   800f5fb8  9421fff0  stwu r1, -0x10(r1)
 *   800f5fbc  7c0802a6  mflr r0
 *   800f5fc0  90010014  stw r0, 0x14(r1)
 *   800f5fc4  93e1000c  stw r31, 0xc(r1)
 *   800f5fc8  7c7f1b78  mr r31, r3
 *   800f5fcc  806300e0  lwz r3, 0xe0(r3)
 *   800f5fd0  4bf11c61  bl 0x80007c30
 *   800f5fd4  807f00e4  lwz r3, 0xe4(r31)
 *   800f5fd8  4bf11c59  bl 0x80007c30
 *   800f5fdc  80010014  lwz r0, 0x14(r1)
 *   800f5fe0  83e1000c  lwz r31, 0xc(r1)
 *   800f5fe4  7c0803a6  mtlr r0
 *   800f5fe8  38210010  addi r1, r1, 0x10
 *   800f5fec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr lwz bl lwz bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ebae94c263e1369d19d364299f452748c97c45d8ab947a78a594d3ec30da1b0b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xe0];
    int                  field_e0;
    int                  field_e4;
} S0;

extern int zz_0007c30_(int);

int f(S0 *p0)
{
    zz_0007c30_(p0->field_e0);
    return zz_0007c30_(p0->field_e4);
}
