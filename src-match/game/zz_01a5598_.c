/* MATCHED  zz_01a5598_ @ 0x801a5598  (9 instructions)
 *
 *   801a5598  9421fff0  stwu r1, -0x10(r1)
 *   801a559c  7c0802a6  mflr r0
 *   801a55a0  38800003  li r4, 3
 *   801a55a4  90010014  stw r0, 0x14(r1)
 *   801a55a8  4bfa57ed  bl 0x8014ad94
 *   801a55ac  80010014  lwz r0, 0x14(r1)
 *   801a55b0  7c0803a6  mtlr r0
 *   801a55b4  38210010  addi r1, r1, 0x10
 *   801a55b8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e801732b4926867033521d59487b6760ed0a8055436d1b1a5cec43fabe6c8ed1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_014ad94_(int, int);

void f(int p0)
{
    zz_014ad94_(p0, 3);
}
