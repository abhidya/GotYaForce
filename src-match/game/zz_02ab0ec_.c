/* MATCHED  zz_02ab0ec_ @ 0x802ab0ec  (9 instructions)
 *
 *   802ab0ec  9421fff0  stwu r1, -0x10(r1)
 *   802ab0f0  7c0802a6  mflr r0
 *   802ab0f4  90010014  stw r0, 0x14(r1)
 *   802ab0f8  806300a8  lwz r3, 0xa8(r3)
 *   802ab0fc  4bfd0215  bl 0x8027b310
 *   802ab100  80010014  lwz r0, 0x14(r1)
 *   802ab104  7c0803a6  mtlr r0
 *   802ab108  38210010  addi r1, r1, 0x10
 *   802ab10c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 718831590008792a5216d6fb6f21b2b215cbf639c67824873d6b40a572055227
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xa8];
    int                  field_a8;
} S0;

extern int zz_027b310_(int);

int f(S0 *p0)
{
    return zz_027b310_(p0->field_a8);
}
