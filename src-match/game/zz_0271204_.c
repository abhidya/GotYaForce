/* MATCHED  zz_0271204_ @ 0x80271204  (8 instructions)
 *
 *   80271204  9421fff0  stwu r1, -0x10(r1)
 *   80271208  7c0802a6  mflr r0
 *   8027120c  90010014  stw r0, 0x14(r1)
 *   80271210  48007735  bl 0x80278944
 *   80271214  80010014  lwz r0, 0x14(r1)
 *   80271218  7c0803a6  mtlr r0
 *   8027121c  38210010  addi r1, r1, 0x10
 *   80271220  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 87912bd934b7feda21c9a3d9291446001900e48cb578b4c3e47aee5ef87c125b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0278944_(void);

void f(void)
{
    zz_0278944_();
}
