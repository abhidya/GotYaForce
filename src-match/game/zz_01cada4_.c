/* MATCHED  zz_01cada4_ @ 0x801cada4  (24 instructions)
 *
 *   801cada4  9421ffe0  stwu r1, -0x20(r1)
 *   801cada8  7c0802a6  mflr r0
 *   801cadac  90010024  stw r0, 0x24(r1)
 *   801cadb0  93e1001c  stw r31, 0x1c(r1)
 *   801cadb4  7cbf2b78  mr r31, r5
 *   801cadb8  93c10018  stw r30, 0x18(r1)
 *   801cadbc  7c9e2378  mr r30, r4
 *   801cadc0  93a10014  stw r29, 0x14(r1)
 *   801cadc4  7c7d1b78  mr r29, r3
 *   801cadc8  4bfffb51  bl 0x801ca918
 *   801cadcc  7fc3f378  mr r3, r30
 *   801cadd0  4bfffb79  bl 0x801ca948
 *   801cadd4  7fe3fb78  mr r3, r31
 *   801cadd8  4bfffd7d  bl 0x801cab54
 *   801caddc  7fa3eb78  mr r3, r29
 *   801cade0  7fe4fb78  mr r4, r31
 *   801cade4  48000021  bl 0x801cae04
 *   801cade8  80010024  lwz r0, 0x24(r1)
 *   801cadec  83e1001c  lwz r31, 0x1c(r1)
 *   801cadf0  83c10018  lwz r30, 0x18(r1)
 *   801cadf4  83a10014  lwz r29, 0x14(r1)
 *   801cadf8  7c0803a6  mtlr r0
 *   801cadfc  38210020  addi r1, r1, 0x20
 *   801cae00  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr stw mr stw mr bl mr bl mr bl mr mr bl lwz lwz lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : dfe3dd230b390ab7bc13077d7ef533a7dacf043ae4e062afce2efc939629581a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01ca918_(void);
extern int zz_01ca948_(int);
extern int zz_01cab54_(int);
extern int zz_01cae04_(int, int);

int f(int p0, int p1, int p2)
{
    zz_01ca918_();
    zz_01ca948_(p1);
    zz_01cab54_(p2);
    return zz_01cae04_(p0, p2);
}
