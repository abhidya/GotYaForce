/* MATCHED  zz_002a4b0_ @ 0x8002a4b0  (9 instructions)
 *
 *   8002a4b0  9421fff0  stwu r1, -0x10(r1)
 *   8002a4b4  7c0802a6  mflr r0
 *   8002a4b8  38600000  li r3, 0
 *   8002a4bc  90010014  stw r0, 0x14(r1)
 *   8002a4c0  48229d0d  bl 0x802541cc
 *   8002a4c4  80010014  lwz r0, 0x14(r1)
 *   8002a4c8  7c0803a6  mtlr r0
 *   8002a4cc  38210010  addi r1, r1, 0x10
 *   8002a4d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9fd3c5e09dfca330b948edb385d94aa8b9498ab032523b218f28013bc44e4c8e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_802541cc(int);

void f(void)
{
    FUN_802541cc(0);
}
