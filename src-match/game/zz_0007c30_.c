/* MATCHED  zz_0007c30_ @ 0x80007c30  (9 instructions)
 *
 *   80007c30  9421fff0  stwu r1, -0x10(r1)
 *   80007c34  7c0802a6  mflr r0
 *   80007c38  90010014  stw r0, 0x14(r1)
 *   80007c3c  8063000c  lwz r3, 0xc(r3)
 *   80007c40  482472d1  bl 0x8024ef10
 *   80007c44  80010014  lwz r0, 0x14(r1)
 *   80007c48  7c0803a6  mtlr r0
 *   80007c4c  38210010  addi r1, r1, 0x10
 *   80007c50  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d45cb3326e8ab0c3b1b2ec8ab7d01820088a47e0b6332d96c01b7050a55684ac
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int FUN_8024ef10(int);

int f(S0 *p0)
{
    return FUN_8024ef10(p0->field_c);
}
