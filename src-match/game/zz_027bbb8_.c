/* MATCHED  zz_027bbb8_ @ 0x8027bbb8  (8 instructions)
 *
 *   8027bbb8  9421fff0  stwu r1, -0x10(r1)
 *   8027bbbc  7c0802a6  mflr r0
 *   8027bbc0  90010014  stw r0, 0x14(r1)
 *   8027bbc4  4bfff63d  bl 0x8027b200
 *   8027bbc8  80010014  lwz r0, 0x14(r1)
 *   8027bbcc  7c0803a6  mtlr r0
 *   8027bbd0  38210010  addi r1, r1, 0x10
 *   8027bbd4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1f07633416838d1a68cfc0934af44e9441f0f93e3da647466f354768810afac2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027b200_(void);

void f(void)
{
    zz_027b200_();
}
