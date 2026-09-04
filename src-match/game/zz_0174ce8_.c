/* MATCHED  zz_0174ce8_ @ 0x80174ce8  (9 instructions)
 *
 *   80174ce8  9421fff0  stwu r1, -0x10(r1)
 *   80174cec  7c0802a6  mflr r0
 *   80174cf0  90010014  stw r0, 0x14(r1)
 *   80174cf4  48000019  bl 0x80174d0c
 *   80174cf8  48000049  bl 0x80174d40
 *   80174cfc  80010014  lwz r0, 0x14(r1)
 *   80174d00  7c0803a6  mtlr r0
 *   80174d04  38210010  addi r1, r1, 0x10
 *   80174d08  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ba1a049aa6d9fb1901e350e914934814201712ca164486c61f94ad7382abb703
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0174d0c_(void);
extern int zz_0174d40_(void);

int f(void)
{
    zz_0174d0c_();
    return zz_0174d40_();
}
