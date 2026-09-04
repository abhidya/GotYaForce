/* MATCHED  zz_01a761c_ @ 0x801a761c  (9 instructions)
 *
 *   801a761c  9421fff0  stwu r1, -0x10(r1)
 *   801a7620  7c0802a6  mflr r0
 *   801a7624  38c0000b  li r6, 0xb
 *   801a7628  90010014  stw r0, 0x14(r1)
 *   801a762c  4bffff35  bl 0x801a7560
 *   801a7630  80010014  lwz r0, 0x14(r1)
 *   801a7634  7c0803a6  mtlr r0
 *   801a7638  38210010  addi r1, r1, 0x10
 *   801a763c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9726e9a3e6c385e8620813f8eb9f3af09dbf186ce26e2cb26e07810d26d147fe
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01a7560_(int, int, int, int);

void f(int p0, int p1, int p2)
{
    zz_01a7560_(p0, p1, p2, 0xb);
}
