/* MATCHED  zz_02aa670_ @ 0x802aa670  (9 instructions)
 *
 *   802aa670  9421fff0  stwu r1, -0x10(r1)
 *   802aa674  7c0802a6  mflr r0
 *   802aa678  90010014  stw r0, 0x14(r1)
 *   802aa67c  4bfce1d1  bl 0x8027884c
 *   802aa680  80010014  lwz r0, 0x14(r1)
 *   802aa684  38600001  li r3, 1
 *   802aa688  7c0803a6  mtlr r0
 *   802aa68c  38210010  addi r1, r1, 0x10
 *   802aa690  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz li mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a58975729c7a0aefd796d78e57ad7bb6f13278509d2ab885a0a033255497794e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_027884c_(void);

int f(void)
{
    zz_027884c_();
    return 1;
}
