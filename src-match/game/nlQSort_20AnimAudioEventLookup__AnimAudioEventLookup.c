/* MATCHED  nlQSort<20AnimAudioEventLookup>(AnimAudioEventLookup @ 0x801a7640  (10 instructions)
 *
 *   801a7640  9421fff0  stwu r1, -0x10(r1)
 *   801a7644  7c0802a6  mflr r0
 *   801a7648  7ca62b78  mr r6, r5
 *   801a764c  38a00001  li r5, 1
 *   801a7650  90010014  stw r0, 0x14(r1)
 *   801a7654  4bffff0d  bl 0x801a7560
 *   801a7658  80010014  lwz r0, 0x14(r1)
 *   801a765c  7c0803a6  mtlr r0
 *   801a7660  38210010  addi r1, r1, 0x10
 *   801a7664  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1d2d37de3e23ed170bd3a029d1cc4dc8e3c50334fa60a16f98549e0f965609bf
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01a7560_(int, int, int, int);

void f(int p0, int p1, int p2)
{
    zz_01a7560_(p0, p1, 1, p2);
}
