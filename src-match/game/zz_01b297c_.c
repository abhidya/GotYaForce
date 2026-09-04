/* MATCHED  zz_01b297c_ @ 0x801b297c  (9 instructions)
 *
 *   801b297c  9421fff0  stwu r1, -0x10(r1)
 *   801b2980  7c0802a6  mflr r0
 *   801b2984  38800042  li r4, 0x42
 *   801b2988  90010014  stw r0, 0x14(r1)
 *   801b298c  4bf14b61  bl 0x800c74ec
 *   801b2990  80010014  lwz r0, 0x14(r1)
 *   801b2994  7c0803a6  mtlr r0
 *   801b2998  38210010  addi r1, r1, 0x10
 *   801b299c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : aae8abb12e93ced3ed35a5a994c09e36399b4cf8057e32ac62f29ed6d908539c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00c74ec_(int, int);

void f(int p0)
{
    zz_00c74ec_(p0, 0x42);
}
