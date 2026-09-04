/* MATCHED  zz_01a5514_ @ 0x801a5514  (9 instructions)
 *
 *   801a5514  9421fff0  stwu r1, -0x10(r1)
 *   801a5518  7c0802a6  mflr r0
 *   801a551c  38800041  li r4, 0x41
 *   801a5520  90010014  stw r0, 0x14(r1)
 *   801a5524  4bedd301  bl 0x80082824
 *   801a5528  80010014  lwz r0, 0x14(r1)
 *   801a552c  7c0803a6  mtlr r0
 *   801a5530  38210010  addi r1, r1, 0x10
 *   801a5534  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 738a16de4225b0a0e617a3cf28d3b7c60a4824fd5ed5a565d691f819dbcfb8c9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0082824_(int, int);

void f(int p0)
{
    zz_0082824_(p0, 0x41);
}
