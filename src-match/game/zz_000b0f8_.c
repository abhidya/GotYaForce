/* MATCHED  zz_000b0f8_ @ 0x8000b0f8  (11 instructions)
 *
 *   8000b0f8  9421fff0  stwu r1, -0x10(r1)
 *   8000b0fc  7c0802a6  mflr r0
 *   8000b100  38a00000  li r5, 0
 *   8000b104  38c00005  li r6, 5
 *   8000b108  90010014  stw r0, 0x14(r1)
 *   8000b10c  480000c9  bl 0x8000b1d4
 *   8000b110  80010014  lwz r0, 0x14(r1)
 *   8000b114  38600000  li r3, 0
 *   8000b118  7c0803a6  mtlr r0
 *   8000b11c  38210010  addi r1, r1, 0x10
 *   8000b120  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz li mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 8f8a7183a9243f65d6b6150c57bab933c561cb76e25ddc89607cfa2cae06469d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_000b1d4_(int, int, int, int);

int f(int p0, int p1)
{
    zz_000b1d4_(p0, p1, 0, 5);
    return 0;
}
