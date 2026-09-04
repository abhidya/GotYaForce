/* MATCHED  zz_0196f64_ @ 0x80196f64  (8 instructions)
 *
 *   80196f64  9421fff0  stwu r1, -0x10(r1)
 *   80196f68  7c0802a6  mflr r0
 *   80196f6c  90010014  stw r0, 0x14(r1)
 *   80196f70  48000015  bl 0x80196f84
 *   80196f74  80010014  lwz r0, 0x14(r1)
 *   80196f78  7c0803a6  mtlr r0
 *   80196f7c  38210010  addi r1, r1, 0x10
 *   80196f80  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 39cb15e6e4e9f7bdd34d1fb521ec98507fd50a206bab41bd2434188fdc2ec02d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0196f84_(void);

void f(void)
{
    zz_0196f84_();
}
