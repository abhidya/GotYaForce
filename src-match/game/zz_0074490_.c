/* MATCHED  zz_0074490_ @ 0x80074490  (9 instructions)
 *
 *   80074490  9421fff0  stwu r1, -0x10(r1)
 *   80074494  7c0802a6  mflr r0
 *   80074498  38800005  li r4, 5
 *   8007449c  90010014  stw r0, 0x14(r1)
 *   800744a0  480e45f5  bl 0x80158a94
 *   800744a4  80010014  lwz r0, 0x14(r1)
 *   800744a8  7c0803a6  mtlr r0
 *   800744ac  38210010  addi r1, r1, 0x10
 *   800744b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : bcf1b9076fb47f224b4400075b4863e779949e785b90533d132bc6e4976e2252
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0158a94_(int, int);

void f(int p0)
{
    zz_0158a94_(p0, 5);
}
