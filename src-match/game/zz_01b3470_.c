/* MATCHED  zz_01b3470_ @ 0x801b3470  (8 instructions)
 *
 *   801b3470  9421fff0  stwu r1, -0x10(r1)
 *   801b3474  7c0802a6  mflr r0
 *   801b3478  90010014  stw r0, 0x14(r1)
 *   801b347c  4bed59d5  bl 0x80088e50
 *   801b3480  80010014  lwz r0, 0x14(r1)
 *   801b3484  7c0803a6  mtlr r0
 *   801b3488  38210010  addi r1, r1, 0x10
 *   801b348c  4e800020  blr
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
