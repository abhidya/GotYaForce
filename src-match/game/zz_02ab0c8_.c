/* MATCHED  zz_02ab0c8_ @ 0x802ab0c8  (9 instructions)
 *
 *   802ab0c8  9421fff0  stwu r1, -0x10(r1)
 *   802ab0cc  7c0802a6  mflr r0
 *   802ab0d0  90010014  stw r0, 0x14(r1)
 *   802ab0d4  806300a8  lwz r3, 0xa8(r3)
 *   802ab0d8  4bfd0159  bl 0x8027b230
 *   802ab0dc  80010014  lwz r0, 0x14(r1)
 *   802ab0e0  7c0803a6  mtlr r0
 *   802ab0e4  38210010  addi r1, r1, 0x10
 *   802ab0e8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0af151b9af21e14d18d628b406955d1b20f3cc8559b21ded5f00a991c0cbc97f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xa8];
    int                  field_a8;
} S0;

extern int zz_027b230_(int);

int f(S0 *p0)
{
    return zz_027b230_(p0->field_a8);
}
