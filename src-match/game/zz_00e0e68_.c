/* MATCHED  zz_00e0e68_ @ 0x800e0e68  (10 instructions)
 *
 *   800e0e68  9421fff0  stwu r1, -0x10(r1)
 *   800e0e6c  7c0802a6  mflr r0
 *   800e0e70  2c040000  cmpwi r4, 0
 *   800e0e74  90010014  stw r0, 0x14(r1)
 *   800e0e78  41800008  blt 0x800e0e80
 *   800e0e7c  4bf8cf95  bl 0x8006de10
 *   800e0e80  80010014  lwz r0, 0x14(r1)
 *   800e0e84  7c0803a6  mtlr r0
 *   800e0e88  38210010  addi r1, r1, 0x10
 *   800e0e8c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr cmpwi stw blt bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d0e6dbaa0e6c463d60c4033f49f42c318ab01d0dd25c2f036439e88072ba92d8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_006de10_(void);

void f(int p0, int p1)
{
    if (p1 >= 0)
        zz_006de10_();
}
