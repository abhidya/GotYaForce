/* MATCHED  zz_01ecea0_ @ 0x801ecea0  (9 instructions)
 *
 *   801ecea0  9421fff0  stwu r1, -0x10(r1)
 *   801ecea4  7c0802a6  mflr r0
 *   801ecea8  90010014  stw r0, 0x14(r1)
 *   801eceac  48000019  bl 0x801ecec4
 *   801eceb0  48000049  bl 0x801ecef8
 *   801eceb4  80010014  lwz r0, 0x14(r1)
 *   801eceb8  7c0803a6  mtlr r0
 *   801ecebc  38210010  addi r1, r1, 0x10
 *   801ecec0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d342c2047c07dcfe7b2c0febc74e5f6ea674646baea00e4767f8ffe9fc3fbb99
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01ecec4_(void);
extern int zz_01ecef8_(void);

int f(void)
{
    zz_01ecec4_();
    return zz_01ecef8_();
}
