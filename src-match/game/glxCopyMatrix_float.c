/* MATCHED  glxCopyMatrix(float @ 0x800061cc  (9 instructions)
 *
 *   800061cc  9421fff0  stwu r1, -0x10(r1)
 *   800061d0  7c0802a6  mflr r0
 *   800061d4  38a00000  li r5, 0
 *   800061d8  90010014  stw r0, 0x14(r1)
 *   800061dc  48000015  bl 0x800061f0
 *   800061e0  80010014  lwz r0, 0x14(r1)
 *   800061e4  7c0803a6  mtlr r0
 *   800061e8  38210010  addi r1, r1, 0x10
 *   800061ec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : afe9a5d372c146318870a8888b19c8c0b3a8f9ec894621aa1b95a428cdcf7c8f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00061f0_(int, int, int);

void f(int p0, int p1)
{
    zz_00061f0_(p0, p1, 0);
}
