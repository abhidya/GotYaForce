/* MATCHED  zz_0042300_ @ 0x80042300  (9 instructions)
 *
 *   80042300  9421fff0  stwu r1, -0x10(r1)
 *   80042304  7c0802a6  mflr r0
 *   80042308  90010014  stw r0, 0x14(r1)
 *   8004230c  806dacb4  lwz r3, -0x534c(r13)
 *   80042310  48009af9  bl 0x8004be08
 *   80042314  80010014  lwz r0, 0x14(r1)
 *   80042318  7c0803a6  mtlr r0
 *   8004231c  38210010  addi r1, r1, 0x10
 *   80042320  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 97f242424c0544d582e28fb337f1b4772ec36ea47c2530c200ecd533f8d4f66a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436254;

extern int zz_004be08_(int);

int f(void)
{
    return zz_004be08_(DAT_80436254);
}
