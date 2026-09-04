/* MATCHED  zz_02646ec_ @ 0x802646ec  (9 instructions)
 *
 *   802646ec  9421fff0  stwu r1, -0x10(r1)
 *   802646f0  7c0802a6  mflr r0
 *   802646f4  90010014  stw r0, 0x14(r1)
 *   802646f8  80630004  lwz r3, 4(r3)
 *   802646fc  48003cd9  bl 0x802683d4
 *   80264700  80010014  lwz r0, 0x14(r1)
 *   80264704  7c0803a6  mtlr r0
 *   80264708  38210010  addi r1, r1, 0x10
 *   8026470c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 54f00297bbb6c9b440eff32f28a5ba811cbe117877529bb3012923eeea78856d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683d4_(int);

int f(S0 *p0)
{
    return zz_02683d4_(p0->field_4);
}
