/* MATCHED  zz_0271474_ @ 0x80271474  (8 instructions)
 *
 *   80271474  9421fff0  stwu r1, -0x10(r1)
 *   80271478  7c0802a6  mflr r0
 *   8027147c  90010014  stw r0, 0x14(r1)
 *   80271480  480082dd  bl 0x8027975c
 *   80271484  80010014  lwz r0, 0x14(r1)
 *   80271488  7c0803a6  mtlr r0
 *   8027148c  38210010  addi r1, r1, 0x10
 *   80271490  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3dc6dd5f460162c372a65042503a941dc6f480be6b4a3012b3d3dace83f5c3c8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027975c_(void);

void f(void)
{
    zz_027975c_();
}
