/* MATCHED  zz_0008924_ @ 0x80008924  (9 instructions)
 *
 *   80008924  9421fff0  stwu r1, -0x10(r1)
 *   80008928  7c0802a6  mflr r0
 *   8000892c  90010014  stw r0, 0x14(r1)
 *   80008930  806dac70  lwz r3, -0x5390(r13)
 *   80008934  4823d991  bl 0x802462c4
 *   80008938  80010014  lwz r0, 0x14(r1)
 *   8000893c  7c0803a6  mtlr r0
 *   80008940  38210010  addi r1, r1, 0x10
 *   80008944  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0a05a80412c3bf7adf149f41439d1a4a7a3d7483875a1da9eddcb4689c202227
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436210;

extern int zz_02462c4_(int);

int f(void)
{
    return zz_02462c4_(DAT_80436210);
}
