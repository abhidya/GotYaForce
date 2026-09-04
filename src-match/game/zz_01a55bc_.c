/* MATCHED  zz_01a55bc_ @ 0x801a55bc  (9 instructions)
 *
 *   801a55bc  9421fff0  stwu r1, -0x10(r1)
 *   801a55c0  7c0802a6  mflr r0
 *   801a55c4  38800000  li r4, 0
 *   801a55c8  90010014  stw r0, 0x14(r1)
 *   801a55cc  4bfa5c61  bl 0x8014b22c
 *   801a55d0  80010014  lwz r0, 0x14(r1)
 *   801a55d4  7c0803a6  mtlr r0
 *   801a55d8  38210010  addi r1, r1, 0x10
 *   801a55dc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1e2dd63c575bc5a1e9bdc6bd7556b9ad308f65eab9d9ec283b10e35bde95d63b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_014b22c_(int, int);

void f(int p0)
{
    zz_014b22c_(p0, 0);
}
