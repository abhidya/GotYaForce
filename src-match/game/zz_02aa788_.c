/* MATCHED  zz_02aa788_ @ 0x802aa788  (8 instructions)
 *
 *   802aa788  9421fff0  stwu r1, -0x10(r1)
 *   802aa78c  7c0802a6  mflr r0
 *   802aa790  90010014  stw r0, 0x14(r1)
 *   802aa794  4bfc3049  bl 0x8026d7dc
 *   802aa798  80010014  lwz r0, 0x14(r1)
 *   802aa79c  7c0803a6  mtlr r0
 *   802aa7a0  38210010  addi r1, r1, 0x10
 *   802aa7a4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 09f627532e85786f7477b03c807efdbba15936f395e80a91f70c781dbc7f13e2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_026d7dc_(void);

void f(void)
{
    zz_026d7dc_();
}
