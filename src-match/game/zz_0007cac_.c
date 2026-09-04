/* MATCHED  zz_0007cac_ @ 0x80007cac  (9 instructions)
 *
 *   80007cac  9421fff0  stwu r1, -0x10(r1)
 *   80007cb0  7c0802a6  mflr r0
 *   80007cb4  90010014  stw r0, 0x14(r1)
 *   80007cb8  8063000c  lwz r3, 0xc(r3)
 *   80007cbc  48001529  bl 0x800091e4
 *   80007cc0  80010014  lwz r0, 0x14(r1)
 *   80007cc4  7c0803a6  mtlr r0
 *   80007cc8  38210010  addi r1, r1, 0x10
 *   80007ccc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4f6df9e63dc5933d494966b3095e9dfdee6d05dddf60fa5272a89c43bda37b2e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_00091e4_(int);

int f(S0 *p0)
{
    return zz_00091e4_(p0->field_c);
}
