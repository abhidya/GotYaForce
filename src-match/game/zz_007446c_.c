/* MATCHED  zz_007446c_ @ 0x8007446c  (9 instructions)
 *
 *   8007446c  9421fff0  stwu r1, -0x10(r1)
 *   80074470  7c0802a6  mflr r0
 *   80074474  38800004  li r4, 4
 *   80074478  90010014  stw r0, 0x14(r1)
 *   8007447c  480e420d  bl 0x80158688
 *   80074480  80010014  lwz r0, 0x14(r1)
 *   80074484  7c0803a6  mtlr r0
 *   80074488  38210010  addi r1, r1, 0x10
 *   8007448c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 549c0c614cc7488c4ecdc6c140ded79ebbb8206428a9638ebe855382179b4a76
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0158688_(int, int);

void f(int p0)
{
    zz_0158688_(p0, 4);
}
