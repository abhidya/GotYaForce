/* MATCHED  zz_0007d8c_ @ 0x80007d8c  (9 instructions)
 *
 *   80007d8c  9421fff0  stwu r1, -0x10(r1)
 *   80007d90  7c0802a6  mflr r0
 *   80007d94  90010014  stw r0, 0x14(r1)
 *   80007d98  8063000c  lwz r3, 0xc(r3)
 *   80007d9c  480018f5  bl 0x80009690
 *   80007da0  80010014  lwz r0, 0x14(r1)
 *   80007da4  7c0803a6  mtlr r0
 *   80007da8  38210010  addi r1, r1, 0x10
 *   80007dac  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : f2958c99424e1309b3ae319658be1c2e8a7b6f1be3d129983730a1ad4e817203
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_0009690_(int);

int f(S0 *p0)
{
    return zz_0009690_(p0->field_c);
}
