/* MATCHED  zz_00eb378_ @ 0x800eb378  (10 instructions)
 *
 *   800eb378  9421fff0  stwu r1, -0x10(r1)
 *   800eb37c  7c0802a6  mflr r0
 *   800eb380  3c808032  lis r4, -0x7fce
 *   800eb384  90010014  stw r0, 0x14(r1)
 *   800eb388  3884b160  addi r4, r4, -0x4ea0
 *   800eb38c  480139e1  bl 0x800fed6c
 *   800eb390  80010014  lwz r0, 0x14(r1)
 *   800eb394  7c0803a6  mtlr r0
 *   800eb398  38210010  addi r1, r1, 0x10
 *   800eb39c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3b801643b30f12ffbab2e08362c664e4cc1d7ea0e6dd330bb41ac95d66de7bfd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8031b160;

extern int zz_00fed6c_(int, int);

int f(int p0)
{
    return zz_00fed6c_(p0, &DAT_8031b160);
}
