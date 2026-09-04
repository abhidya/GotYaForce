/* MATCHED  zz_0270dec_ @ 0x80270dec  (8 instructions)
 *
 *   80270dec  9421fff0  stwu r1, -0x10(r1)
 *   80270df0  7c0802a6  mflr r0
 *   80270df4  90010014  stw r0, 0x14(r1)
 *   80270df8  480070ed  bl 0x80277ee4
 *   80270dfc  80010014  lwz r0, 0x14(r1)
 *   80270e00  7c0803a6  mtlr r0
 *   80270e04  38210010  addi r1, r1, 0x10
 *   80270e08  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 07a62136be8508e55f86d9b37fa671dd14034ab52f3479cc375b2cdbd444a91e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0277ee4_(void);

void f(void)
{
    zz_0277ee4_();
}
