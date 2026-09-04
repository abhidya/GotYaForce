/* MATCHED  zz_009edd4_ @ 0x8009edd4  (8 instructions)
 *
 *   8009edd4  9421fff0  stwu r1, -0x10(r1)
 *   8009edd8  7c0802a6  mflr r0
 *   8009eddc  90010014  stw r0, 0x14(r1)
 *   8009ede0  4bf78179  bl 0x80016f58
 *   8009ede4  80010014  lwz r0, 0x14(r1)
 *   8009ede8  7c0803a6  mtlr r0
 *   8009edec  38210010  addi r1, r1, 0x10
 *   8009edf0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 128062f4c875c359aaf4d5ef5df756a287dab41b9bec5bd162f501d7c2eee9a9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0016f58_(void);

void f(void)
{
    zz_0016f58_();
}
