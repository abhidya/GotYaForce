/* MATCHED  zz_01a53f8_ @ 0x801a53f8  (9 instructions)
 *
 *   801a53f8  9421fff0  stwu r1, -0x10(r1)
 *   801a53fc  7c0802a6  mflr r0
 *   801a5400  38800001  li r4, 1
 *   801a5404  90010014  stw r0, 0x14(r1)
 *   801a5408  4bf9f9bd  bl 0x80144dc4
 *   801a540c  80010014  lwz r0, 0x14(r1)
 *   801a5410  7c0803a6  mtlr r0
 *   801a5414  38210010  addi r1, r1, 0x10
 *   801a5418  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a70b51117922dcbc574fe6b20aca1c9f38f650e788bddce0135c9eb9dd8bfce1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0144dc4_(int, int);

void f(int p0)
{
    zz_0144dc4_(p0, 1);
}
