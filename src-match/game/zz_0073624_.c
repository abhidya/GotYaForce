/* MATCHED  zz_0073624_ @ 0x80073624  (9 instructions)
 *
 *   80073624  9421fff0  stwu r1, -0x10(r1)
 *   80073628  7c0802a6  mflr r0
 *   8007362c  38800006  li r4, 6
 *   80073630  90010014  stw r0, 0x14(r1)
 *   80073634  480ee279  bl 0x801618ac
 *   80073638  80010014  lwz r0, 0x14(r1)
 *   8007363c  7c0803a6  mtlr r0
 *   80073640  38210010  addi r1, r1, 0x10
 *   80073644  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 959a42bc03ec0999476b1744e5155f2afaacef720f770ad017e564e02d2d153f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01618ac_(int, int);

void f(int p0)
{
    zz_01618ac_(p0, 6);
}
