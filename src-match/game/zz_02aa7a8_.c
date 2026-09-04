/* MATCHED  zz_02aa7a8_ @ 0x802aa7a8  (13 instructions)
 *
 *   802aa7a8  9421fff0  stwu r1, -0x10(r1)
 *   802aa7ac  7c0802a6  mflr r0
 *   802aa7b0  90010014  stw r0, 0x14(r1)
 *   802aa7b4  93e1000c  stw r31, 0xc(r1)
 *   802aa7b8  7c7f1b78  mr r31, r3
 *   802aa7bc  4bfc2e9d  bl 0x8026d658
 *   802aa7c0  7fe3fb78  mr r3, r31
 *   802aa7c4  4bfc31e9  bl 0x8026d9ac
 *   802aa7c8  80010014  lwz r0, 0x14(r1)
 *   802aa7cc  83e1000c  lwz r31, 0xc(r1)
 *   802aa7d0  7c0803a6  mtlr r0
 *   802aa7d4  38210010  addi r1, r1, 0x10
 *   802aa7d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl mr bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ee0e7a669d0b415943e496a40a4c2fde48f9ed1468f8669332ed95068c0f68c2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_026d658_(void);
extern int zz_026d9ac_(int);

int f(int p0)
{
    zz_026d658_();
    return zz_026d9ac_(p0);
}
