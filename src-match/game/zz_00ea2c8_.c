/* MATCHED  zz_00ea2c8_ @ 0x800ea2c8  (9 instructions)
 *
 *   800ea2c8  9421fff0  stwu r1, -0x10(r1)
 *   800ea2cc  7c0802a6  mflr r0
 *   800ea2d0  38a0ffff  li r5, -1
 *   800ea2d4  90010014  stw r0, 0x14(r1)
 *   800ea2d8  48000015  bl 0x800ea2ec
 *   800ea2dc  80010014  lwz r0, 0x14(r1)
 *   800ea2e0  7c0803a6  mtlr r0
 *   800ea2e4  38210010  addi r1, r1, 0x10
 *   800ea2e8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ffda354dd0977d32e339d706b8cc7763665408a963f5bec524020e94ffe593d3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00ea2ec_(int, int, int);

void f(int p0, int p1)
{
    zz_00ea2ec_(p0, p1, -1);
}
