/* MATCHED  zz_01c6e08_ @ 0x801c6e08  (10 instructions)
 *
 *   801c6e08  9421fff0  stwu r1, -0x10(r1)
 *   801c6e0c  7c0802a6  mflr r0
 *   801c6e10  38600000  li r3, 0
 *   801c6e14  38800077  li r4, 0x77
 *   801c6e18  90010014  stw r0, 0x14(r1)
 *   801c6e1c  4bf29551  bl 0x800f036c
 *   801c6e20  80010014  lwz r0, 0x14(r1)
 *   801c6e24  7c0803a6  mtlr r0
 *   801c6e28  38210010  addi r1, r1, 0x10
 *   801c6e2c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4301b2c044c99e87b93f670558b31de733ba1d4e8e4dbca1b56f20a4f19d791f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00f036c_(int, int);

void f(void)
{
    zz_00f036c_(0, 0x77);
}
