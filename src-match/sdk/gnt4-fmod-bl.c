/* MATCHED  gnt4-fmod-bl @ 0x8023cbb8  (8 instructions)
 *
 *   8023cbb8  9421fff0  stwu r1, -0x10(r1)
 *   8023cbbc  7c0802a6  mflr r0
 *   8023cbc0  90010014  stw r0, 0x14(r1)
 *   8023cbc4  4bffd275  bl 0x80239e38
 *   8023cbc8  80010014  lwz r0, 0x14(r1)
 *   8023cbcc  7c0803a6  mtlr r0
 *   8023cbd0  38210010  addi r1, r1, 0x10
 *   8023cbd4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 74855b02e4a6a95da19139f9ba4fbfd1c8540b5014c6fb855f352c021dc9a97d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80239e38(void);

void f(void)
{
    FUN_80239e38();
}
