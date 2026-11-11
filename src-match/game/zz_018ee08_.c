/* MATCHED  zz_018ee08_ @ 0x8018ee08  (10 instructions)
 *
 *   8018ee08  9421fff0  stwu r1, -0x10(r1)
 *   8018ee0c  7c0802a6  mflr r0
 *   8018ee10  3c808036  lis r4, -0x7fca
 *   8018ee14  90010014  stw r0, 0x14(r1)
 *   8018ee18  3884586c  addi r4, r4, 0x586c
 *   8018ee1c  4bfeaf05  bl 0x80179d20
 *   8018ee20  80010014  lwz r0, 0x14(r1)
 *   8018ee24  7c0803a6  mtlr r0
 *   8018ee28  38210010  addi r1, r1, 0x10
 *   8018ee2c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : bc9dac4194ab4d11c5e0d94361beac4669aaef64a0482e5ace979f60a5586b0d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8036586c;

extern int zz_0179d20_(int, int);

int f(int p0)
{
    return zz_0179d20_(p0, &DAT_8036586c);
}
