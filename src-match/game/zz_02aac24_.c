/* MATCHED  zz_02aac24_ @ 0x802aac24  (9 instructions)
 *
 *   802aac24  9421fff0  stwu r1, -0x10(r1)
 *   802aac28  7c0802a6  mflr r0
 *   802aac2c  90010014  stw r0, 0x14(r1)
 *   802aac30  806300a8  lwz r3, 0xa8(r3)
 *   802aac34  4bfd0f79  bl 0x8027bbac
 *   802aac38  80010014  lwz r0, 0x14(r1)
 *   802aac3c  7c0803a6  mtlr r0
 *   802aac40  38210010  addi r1, r1, 0x10
 *   802aac44  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 22c7b3ff5b116048f3b37ebb8e621dc3c14f724820b6e16ef94f60db5af5f075
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xa8];
    int                  field_a8;
} S0;

extern int zz_027bbac_(int);

int f(S0 *p0)
{
    return zz_027bbac_(p0->field_a8);
}
