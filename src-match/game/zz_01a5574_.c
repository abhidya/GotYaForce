/* MATCHED  zz_01a5574_ @ 0x801a5574  (9 instructions)
 *
 *   801a5574  9421fff0  stwu r1, -0x10(r1)
 *   801a5578  7c0802a6  mflr r0
 *   801a557c  38800000  li r4, 0
 *   801a5580  90010014  stw r0, 0x14(r1)
 *   801a5584  4bfa533d  bl 0x8014a8c0
 *   801a5588  80010014  lwz r0, 0x14(r1)
 *   801a558c  7c0803a6  mtlr r0
 *   801a5590  38210010  addi r1, r1, 0x10
 *   801a5594  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 02d9e47e308e29163e26ecb82590059f291f91575ab4f6eba4f4e35b75aaff72
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_014a8c0_(int, int);

void f(int p0)
{
    zz_014a8c0_(p0, 0);
}
