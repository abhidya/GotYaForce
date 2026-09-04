/* MATCHED  zz_02aabdc_ @ 0x802aabdc  (9 instructions)
 *
 *   802aabdc  9421fff0  stwu r1, -0x10(r1)
 *   802aabe0  7c0802a6  mflr r0
 *   802aabe4  90010014  stw r0, 0x14(r1)
 *   802aabe8  806300a8  lwz r3, 0xa8(r3)
 *   802aabec  4bfd0f95  bl 0x8027bb80
 *   802aabf0  80010014  lwz r0, 0x14(r1)
 *   802aabf4  7c0803a6  mtlr r0
 *   802aabf8  38210010  addi r1, r1, 0x10
 *   802aabfc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 13d360191b51be9ca62b1c712313486afd80d5b067a7ebbc85ab3ce8b17c783b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xa8];
    int                  field_a8;
} S0;

extern int zz_027bb80_(int);

int f(S0 *p0)
{
    return zz_027bb80_(p0->field_a8);
}
