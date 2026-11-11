/* MATCHED  zz_027c990_ @ 0x8027c990  (8 instructions)
 *
 *   8027c990  9421fff0  stwu r1, -0x10(r1)
 *   8027c994  7c0802a6  mflr r0
 *   8027c998  90010014  stw r0, 0x14(r1)
 *   8027c99c  4bd88b59  bl 0x800054f4
 *   8027c9a0  80010014  lwz r0, 0x14(r1)
 *   8027c9a4  7c0803a6  mtlr r0
 *   8027c9a8  38210010  addi r1, r1, 0x10
 *   8027c9ac  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d9ad6241a720430b94d72bbdafe259355e8c7a65150eb4d6d4ce3d48212779d0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_800054f4(void);

void f(void)
{
    FUN_800054f4();
}
