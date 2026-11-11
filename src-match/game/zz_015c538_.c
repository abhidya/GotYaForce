/* MATCHED  zz_015c538_ @ 0x8015c538  (10 instructions)
 *
 *   8015c538  9421fff0  stwu r1, -0x10(r1)
 *   8015c53c  7c0802a6  mflr r0
 *   8015c540  3c808034  lis r4, -0x7fcc
 *   8015c544  90010014  stw r0, 0x14(r1)
 *   8015c548  3884626c  addi r4, r4, 0x626c
 *   8015c54c  4801de29  bl 0x8017a374
 *   8015c550  80010014  lwz r0, 0x14(r1)
 *   8015c554  7c0803a6  mtlr r0
 *   8015c558  38210010  addi r1, r1, 0x10
 *   8015c55c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7d9394d274a0ea6b9f5aa22c402d1bedb0c438ef0b03cec6560429001342188b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8034626c;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_8034626c);
}
