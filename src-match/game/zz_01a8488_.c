/* MATCHED  zz_01a8488_ @ 0x801a8488  (8 instructions)
 *
 *   801a8488  9421fff0  stwu r1, -0x10(r1)
 *   801a848c  7c0802a6  mflr r0
 *   801a8490  90010014  stw r0, 0x14(r1)
 *   801a8494  4bee09bd  bl 0x80088e50
 *   801a8498  80010014  lwz r0, 0x14(r1)
 *   801a849c  7c0803a6  mtlr r0
 *   801a84a0  38210010  addi r1, r1, 0x10
 *   801a84a4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7e6aa516b554e1606c7615026a1a39d1574b61b45204f6a94caf5619fab30426
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0088e50_(void);

void f(void)
{
    zz_0088e50_();
}
