/* MATCHED  zz_019e958_ @ 0x8019e958  (9 instructions)
 *
 *   8019e958  9421fff0  stwu r1, -0x10(r1)
 *   8019e95c  7c0802a6  mflr r0
 *   8019e960  38800000  li r4, 0
 *   8019e964  90010014  stw r0, 0x14(r1)
 *   8019e968  4bfabf59  bl 0x8014a8c0
 *   8019e96c  80010014  lwz r0, 0x14(r1)
 *   8019e970  7c0803a6  mtlr r0
 *   8019e974  38210010  addi r1, r1, 0x10
 *   8019e978  4e800020  blr
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
