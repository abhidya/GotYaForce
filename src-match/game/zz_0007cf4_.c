/* MATCHED  zz_0007cf4_ @ 0x80007cf4  (9 instructions)
 *
 *   80007cf4  9421fff0  stwu r1, -0x10(r1)
 *   80007cf8  7c0802a6  mflr r0
 *   80007cfc  90010014  stw r0, 0x14(r1)
 *   80007d00  8063000c  lwz r3, 0xc(r3)
 *   80007d04  480016d5  bl 0x800093d8
 *   80007d08  80010014  lwz r0, 0x14(r1)
 *   80007d0c  7c0803a6  mtlr r0
 *   80007d10  38210010  addi r1, r1, 0x10
 *   80007d14  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3086b2342fe17ea22d483b388e5d816e71cdba720f929b5f9ce3834f7037aafb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_00093d8_(int);

int f(S0 *p0)
{
    return zz_00093d8_(p0->field_c);
}
