/* MATCHED  zz_00282c0_ @ 0x800282c0  (9 instructions)
 *
 *   800282c0  9421fff0  stwu r1, -0x10(r1)
 *   800282c4  7c0802a6  mflr r0
 *   800282c8  90010014  stw r0, 0x14(r1)
 *   800282cc  48001989  bl 0x80029c54
 *   800282d0  48057a8d  bl 0x8007fd5c
 *   800282d4  80010014  lwz r0, 0x14(r1)
 *   800282d8  7c0803a6  mtlr r0
 *   800282dc  38210010  addi r1, r1, 0x10
 *   800282e0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 609a86a5e569ec3839c09d360286dd8e4a34e4943ab4ce8b65f9e883b644cc8e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0029c54_(void);
extern int zz_007fd5c_(void);

int f(void)
{
    zz_0029c54_();
    return zz_007fd5c_();
}
