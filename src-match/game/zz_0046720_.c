/* MATCHED  zz_0046720_ @ 0x80046720  (13 instructions)
 *
 *   80046720  9421fff0  stwu r1, -0x10(r1)
 *   80046724  7c0802a6  mflr r0
 *   80046728  90010014  stw r0, 0x14(r1)
 *   8004672c  93e1000c  stw r31, 0xc(r1)
 *   80046730  7c7f1b78  mr r31, r3
 *   80046734  48000021  bl 0x80046754
 *   80046738  7fe3fb78  mr r3, r31
 *   8004673c  480005c5  bl 0x80046d00
 *   80046740  80010014  lwz r0, 0x14(r1)
 *   80046744  83e1000c  lwz r31, 0xc(r1)
 *   80046748  7c0803a6  mtlr r0
 *   8004674c  38210010  addi r1, r1, 0x10
 *   80046750  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl mr bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 49d1e57e7897800b52bd4a3e4009e03cfb4c84e8f2832aa4165a3ecf903ada6d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0046754_(void);
extern int zz_0046d00_(int);

int f(int p0)
{
    zz_0046754_();
    return zz_0046d00_(p0);
}
