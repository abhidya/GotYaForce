/* MATCHED  sndSeqContinue @ 0x801c7b68  (14 instructions)
 *
 *   801c7b68  9421fff0  stwu r1, -0x10(r1)
 *   801c7b6c  7c0802a6  mflr r0
 *   801c7b70  90010014  stw r0, 0x14(r1)
 *   801c7b74  93e1000c  stw r31, 0xc(r1)
 *   801c7b78  7c7f1b78  mr r31, r3
 *   801c7b7c  48000269  bl 0x801c7de4
 *   801c7b80  7fe3fb78  mr r3, r31
 *   801c7b84  4800001d  bl 0x801c7ba0
 *   801c7b88  4800016d  bl 0x801c7cf4
 *   801c7b8c  80010014  lwz r0, 0x14(r1)
 *   801c7b90  83e1000c  lwz r31, 0xc(r1)
 *   801c7b94  7c0803a6  mtlr r0
 *   801c7b98  38210010  addi r1, r1, 0x10
 *   801c7b9c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl mr bl bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6a2e0a432d7bd2d2fe8ddd2bf41094b5d848498ad9bbb5d523b1958f7afc73b7
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01c7ba0_(int);
extern int zz_01c7cf4_(void);
extern int zz_01c7de4_(void);

int f(int p0)
{
    zz_01c7de4_();
    zz_01c7ba0_(p0);
    return zz_01c7cf4_();
}
