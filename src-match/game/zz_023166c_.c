/* MATCHED  zz_023166c_ @ 0x8023166c  (8 instructions)
 *
 *   8023166c  9421fff0  stwu r1, -0x10(r1)
 *   80231670  7c0802a6  mflr r0
 *   80231674  90010014  stw r0, 0x14(r1)
 *   80231678  48000289  bl 0x80231900
 *   8023167c  80010014  lwz r0, 0x14(r1)
 *   80231680  7c0803a6  mtlr r0
 *   80231684  38210010  addi r1, r1, 0x10
 *   80231688  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 10fe6390e7d8e27e24c8771875d8816ec7c35dbf085f7650d4f812ded9ec2762
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void EnableEXI2Interrupts(void);

void f(void)
{
    EnableEXI2Interrupts();
}
