/* MATCHED  zz_01f1928_ @ 0x801f1928  (11 instructions)
 *
 *   801f1928  9421fff0  stwu r1, -0x10(r1)
 *   801f192c  7c0802a6  mflr r0
 *   801f1930  38600000  li r3, 0
 *   801f1934  38800000  li r4, 0
 *   801f1938  90010014  stw r0, 0x14(r1)
 *   801f193c  38a00000  li r5, 0
 *   801f1940  48000141  bl 0x801f1a80
 *   801f1944  80010014  lwz r0, 0x14(r1)
 *   801f1948  7c0803a6  mtlr r0
 *   801f194c  38210010  addi r1, r1, 0x10
 *   801f1950  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c8dc0db3f31030c5d11eabd1f13f96dcd0cd5b9462daa6d753665b04bfafd3d2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01f1a80_(int, int, int);

void f(void)
{
    zz_01f1a80_(0, 0, 0);
}
