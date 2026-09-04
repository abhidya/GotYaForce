/* MATCHED  zz_0074448_ @ 0x80074448  (9 instructions)
 *
 *   80074448  9421fff0  stwu r1, -0x10(r1)
 *   8007444c  7c0802a6  mflr r0
 *   80074450  38800003  li r4, 3
 *   80074454  90010014  stw r0, 0x14(r1)
 *   80074458  480e4231  bl 0x80158688
 *   8007445c  80010014  lwz r0, 0x14(r1)
 *   80074460  7c0803a6  mtlr r0
 *   80074464  38210010  addi r1, r1, 0x10
 *   80074468  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4f96524881a4b704b5e6e8167e13a56b0464514e132f44a51a5742655c4f371f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0158688_(int, int);

void f(int p0)
{
    zz_0158688_(p0, 3);
}
