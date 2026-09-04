/* MATCHED  zz_006e1ac_ @ 0x8006e1ac  (9 instructions)
 *
 *   8006e1ac  9421fff0  stwu r1, -0x10(r1)
 *   8006e1b0  7c0802a6  mflr r0
 *   8006e1b4  38c04000  li r6, 0x4000
 *   8006e1b8  90010014  stw r0, 0x14(r1)
 *   8006e1bc  48000015  bl 0x8006e1d0
 *   8006e1c0  80010014  lwz r0, 0x14(r1)
 *   8006e1c4  7c0803a6  mtlr r0
 *   8006e1c8  38210010  addi r1, r1, 0x10
 *   8006e1cc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e5d33e4b437c76410f4b03991ae5530c84520700bba434d392d466088e8a37f7
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_006e1d0_(int, int, int, int);

void f(int p0, int p1, int p2)
{
    zz_006e1d0_(p0, p1, p2, 0x4000);
}
