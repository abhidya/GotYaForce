/* MATCHED  zz_00528b4_ @ 0x800528b4  (20 instructions)
 *
 *   800528b4  9421fff0  stwu r1, -0x10(r1)
 *   800528b8  7c0802a6  mflr r0
 *   800528bc  38600000  li r3, 0
 *   800528c0  90010014  stw r0, 0x14(r1)
 *   800528c4  4bfb2da5  bl 0x80005668
 *   800528c8  38600000  li r3, 0
 *   800528cc  38800001  li r4, 1
 *   800528d0  4bfb3001  bl 0x800058d0
 *   800528d4  48039881  bl 0x8008c154
 *   800528d8  38600006  li r3, 6
 *   800528dc  38800000  li r4, 0
 *   800528e0  4bffdf21  bl 0x80050800
 *   800528e4  38600007  li r3, 7
 *   800528e8  38800000  li r4, 0
 *   800528ec  4bffdf15  bl 0x80050800
 *   800528f0  4bffdd15  bl 0x80050604
 *   800528f4  80010014  lwz r0, 0x14(r1)
 *   800528f8  7c0803a6  mtlr r0
 *   800528fc  38210010  addi r1, r1, 0x10
 *   80052900  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl li li bl bl li li bl li li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 69a1ad124a9444f9681e107a0ba7c1541eca5610ba40b3ea9eecd62c16e682f0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0005668_(int);
extern int zz_00058d0_(int, int);
extern int zz_0050604_(void);
extern int zz_0050800_(int, int);
extern int zz_008c154_(void);

int f(void)
{
    zz_0005668_(0);
    zz_00058d0_(0, 1);
    zz_008c154_();
    zz_0050800_(6, 0);
    zz_0050800_(7, 0);
    return zz_0050604_();
}
