/* MATCHED  zz_01dcf7c_ @ 0x801dcf7c  (9 instructions)
 *
 *   801dcf7c  9421fff0  stwu r1, -0x10(r1)
 *   801dcf80  7c0802a6  mflr r0
 *   801dcf84  90010014  stw r0, 0x14(r1)
 *   801dcf88  48000019  bl 0x801dcfa0
 *   801dcf8c  4800027d  bl 0x801dd208
 *   801dcf90  80010014  lwz r0, 0x14(r1)
 *   801dcf94  7c0803a6  mtlr r0
 *   801dcf98  38210010  addi r1, r1, 0x10
 *   801dcf9c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 23584570cd7c375d6bac19c8d0a578cd1a51806f8f2aa174b56c75fd480ea0df
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01dcfa0_(void);
extern int zz_01dd208_(void);

int f(void)
{
    zz_01dcfa0_();
    return zz_01dd208_();
}
