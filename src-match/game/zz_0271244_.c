/* MATCHED  zz_0271244_ @ 0x80271244  (8 instructions)
 *
 *   80271244  9421fff0  stwu r1, -0x10(r1)
 *   80271248  7c0802a6  mflr r0
 *   8027124c  90010014  stw r0, 0x14(r1)
 *   80271250  4bf9fe81  bl 0x802110d0
 *   80271254  80010014  lwz r0, 0x14(r1)
 *   80271258  7c0803a6  mtlr r0
 *   8027125c  38210010  addi r1, r1, 0x10
 *   80271260  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a0b07829ebbeb54cd441f5c005e8b6b8dbfbe5cab07e2c51415174cc84e13824
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_802110d0(void);

void f(void)
{
    FUN_802110d0();
}
