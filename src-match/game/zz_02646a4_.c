/* MATCHED  zz_02646a4_ @ 0x802646a4  (9 instructions)
 *
 *   802646a4  9421fff0  stwu r1, -0x10(r1)
 *   802646a8  7c0802a6  mflr r0
 *   802646ac  90010014  stw r0, 0x14(r1)
 *   802646b0  80630004  lwz r3, 4(r3)
 *   802646b4  48003d11  bl 0x802683c4
 *   802646b8  80010014  lwz r0, 0x14(r1)
 *   802646bc  7c0803a6  mtlr r0
 *   802646c0  38210010  addi r1, r1, 0x10
 *   802646c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a267e3a5efb306f8a079d2b260eeb63b6d1abb6af2b73e70f9d73dad37a4c13e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683c4_(int);

int f(S0 *p0)
{
    return zz_02683c4_(p0->field_4);
}
