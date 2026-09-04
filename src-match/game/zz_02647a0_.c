/* MATCHED  zz_02647a0_ @ 0x802647a0  (9 instructions)
 *
 *   802647a0  9421fff0  stwu r1, -0x10(r1)
 *   802647a4  7c0802a6  mflr r0
 *   802647a8  90010014  stw r0, 0x14(r1)
 *   802647ac  80630004  lwz r3, 4(r3)
 *   802647b0  48003cb1  bl 0x80268460
 *   802647b4  80010014  lwz r0, 0x14(r1)
 *   802647b8  7c0803a6  mtlr r0
 *   802647bc  38210010  addi r1, r1, 0x10
 *   802647c0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : eff147f3a7a0f114d2f3be1f23ffc9bfcf862af354cd591923a95da23a927cb8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_0268460_(int);

int f(S0 *p0)
{
    return zz_0268460_(p0->field_4);
}
