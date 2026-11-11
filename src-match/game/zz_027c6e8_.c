/* MATCHED  zz_027c6e8_ @ 0x8027c6e8  (10 instructions)
 *
 *   8027c6e8  9421fff0  stwu r1, -0x10(r1)
 *   8027c6ec  7c0802a6  mflr r0
 *   8027c6f0  38800000  li r4, 0
 *   8027c6f4  38a00054  li r5, 0x54
 *   8027c6f8  90010014  stw r0, 0x14(r1)
 *   8027c6fc  4bd88d11  bl 0x8000540c
 *   8027c700  80010014  lwz r0, 0x14(r1)
 *   8027c704  7c0803a6  mtlr r0
 *   8027c708  38210010  addi r1, r1, 0x10
 *   8027c70c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3d58ef61ba1995a45cb0cd8201a7dc671d1e5b66745d3f7e96bf8c0c566d315f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8000540c(int, int, int);

void f(int p0)
{
    FUN_8000540c(p0, 0, 0x54);
}
