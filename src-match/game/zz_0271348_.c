/* MATCHED  zz_0271348_ @ 0x80271348  (9 instructions)
 *
 *   80271348  9421fff0  stwu r1, -0x10(r1)
 *   8027134c  7c0802a6  mflr r0
 *   80271350  90010014  stw r0, 0x14(r1)
 *   80271354  8063000c  lwz r3, 0xc(r3)
 *   80271358  48000015  bl 0x8027136c
 *   8027135c  80010014  lwz r0, 0x14(r1)
 *   80271360  7c0803a6  mtlr r0
 *   80271364  38210010  addi r1, r1, 0x10
 *   80271368  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2b008e7625353a814bb27faf74286625aef8582ad4556abb82bc32ea385b2bdf
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_027136c_(int);

int f(S0 *p0)
{
    return zz_027136c_(p0->field_c);
}
