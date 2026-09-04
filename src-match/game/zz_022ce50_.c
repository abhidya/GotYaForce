/* MATCHED  zz_022ce50_ @ 0x8022ce50  (9 instructions)
 *
 *   8022ce50  9421fff0  stwu r1, -0x10(r1)
 *   8022ce54  7c0802a6  mflr r0
 *   8022ce58  90010014  stw r0, 0x14(r1)
 *   8022ce5c  480009e5  bl 0x8022d840
 *   8022ce60  80010014  lwz r0, 0x14(r1)
 *   8022ce64  38600000  li r3, 0
 *   8022ce68  7c0803a6  mtlr r0
 *   8022ce6c  38210010  addi r1, r1, 0x10
 *   8022ce70  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz li mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4c4d6b7b31249c5df5ff84d8e646bdb35e984e6cc52003ed80dfb9b7be5c537e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_022d840_(void);

int f(void)
{
    zz_022d840_();
    return 0;
}
