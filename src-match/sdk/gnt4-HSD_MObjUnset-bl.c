/* MATCHED  gnt4-HSD_MObjUnset-bl @ 0x80243744  (9 instructions)
 *
 *   80243744  9421fff0  stwu r1, -0x10(r1)
 *   80243748  7c0802a6  mflr r0
 *   8024374c  38600000  li r3, 0
 *   80243750  90010014  stw r0, 0x14(r1)
 *   80243754  4bffccbd  bl 0x80240410
 *   80243758  80010014  lwz r0, 0x14(r1)
 *   8024375c  7c0803a6  mtlr r0
 *   80243760  38210010  addi r1, r1, 0x10
 *   80243764  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2a15fccc49a7b8fdd76782e50b8833e8068dbd3343961e01257f90d5e4a1377a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80240410(int);

void f(void)
{
    FUN_80240410(0);
}
