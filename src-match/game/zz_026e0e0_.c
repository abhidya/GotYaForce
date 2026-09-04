/* MATCHED  zz_026e0e0_ @ 0x8026e0e0  (8 instructions)
 *
 *   8026e0e0  9421fff0  stwu r1, -0x10(r1)
 *   8026e0e4  7c0802a6  mflr r0
 *   8026e0e8  90010014  stw r0, 0x14(r1)
 *   8026e0ec  4bffbc21  bl 0x80269d0c
 *   8026e0f0  80010014  lwz r0, 0x14(r1)
 *   8026e0f4  7c0803a6  mtlr r0
 *   8026e0f8  38210010  addi r1, r1, 0x10
 *   8026e0fc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : cdfdb03ac6b8e527d8a0577180bec85480d2331c3cf72f7e7acd952d2fb93080
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void SetTRKConnected(void);

void f(void)
{
    SetTRKConnected();
}
