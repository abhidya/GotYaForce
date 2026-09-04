/* MATCHED  zz_0007cd0_ @ 0x80007cd0  (9 instructions)
 *
 *   80007cd0  9421fff0  stwu r1, -0x10(r1)
 *   80007cd4  7c0802a6  mflr r0
 *   80007cd8  90010014  stw r0, 0x14(r1)
 *   80007cdc  8063000c  lwz r3, 0xc(r3)
 *   80007ce0  480017d9  bl 0x800094b8
 *   80007ce4  80010014  lwz r0, 0x14(r1)
 *   80007ce8  7c0803a6  mtlr r0
 *   80007cec  38210010  addi r1, r1, 0x10
 *   80007cf0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : f8861811506f865625299d819d5e47bf03d62a3a3e83377beca17b7f548cb087
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_00094b8_(int);

int f(S0 *p0)
{
    return zz_00094b8_(p0->field_c);
}
