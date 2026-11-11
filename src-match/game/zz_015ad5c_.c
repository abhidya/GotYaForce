/* MATCHED  zz_015ad5c_ @ 0x8015ad5c  (10 instructions)
 *
 *   8015ad5c  9421fff0  stwu r1, -0x10(r1)
 *   8015ad60  7c0802a6  mflr r0
 *   8015ad64  3c808034  lis r4, -0x7fcc
 *   8015ad68  90010014  stw r0, 0x14(r1)
 *   8015ad6c  38844878  addi r4, r4, 0x4878
 *   8015ad70  4801f605  bl 0x8017a374
 *   8015ad74  80010014  lwz r0, 0x14(r1)
 *   8015ad78  7c0803a6  mtlr r0
 *   8015ad7c  38210010  addi r1, r1, 0x10
 *   8015ad80  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ab1e57872b49c0dcfe25538745c921df675ebdc90a94e2684aa07bf72977af48
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80344878;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_80344878);
}
