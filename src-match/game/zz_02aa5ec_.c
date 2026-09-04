/* MATCHED  zz_02aa5ec_ @ 0x802aa5ec  (8 instructions)
 *
 *   802aa5ec  9421fff0  stwu r1, -0x10(r1)
 *   802aa5f0  7c0802a6  mflr r0
 *   802aa5f4  90010014  stw r0, 0x14(r1)
 *   802aa5f8  4bfcd439  bl 0x80277a30
 *   802aa5fc  80010014  lwz r0, 0x14(r1)
 *   802aa600  7c0803a6  mtlr r0
 *   802aa604  38210010  addi r1, r1, 0x10
 *   802aa608  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5172ccfbc85b58ee7a6c5bbc9433681732577f51b8d40540b84b5c4cad6ceec2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0277a30_(void);

void f(void)
{
    zz_0277a30_();
}
