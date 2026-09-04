/* MATCHED  zz_008ae3c_ @ 0x8008ae3c  (9 instructions)
 *
 *   8008ae3c  9421fff0  stwu r1, -0x10(r1)
 *   8008ae40  7c0802a6  mflr r0
 *   8008ae44  38c00001  li r6, 1
 *   8008ae48  90010014  stw r0, 0x14(r1)
 *   8008ae4c  48000015  bl 0x8008ae60
 *   8008ae50  80010014  lwz r0, 0x14(r1)
 *   8008ae54  7c0803a6  mtlr r0
 *   8008ae58  38210010  addi r1, r1, 0x10
 *   8008ae5c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d975f318aee63a6850f0465af9638525529ed6c1001e2c8f7b8dfc2c72d3e12d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_008ae60_(int, int, int, int);

void f(int p0, int p1, int p2)
{
    zz_008ae60_(p0, p1, p2, 1);
}
