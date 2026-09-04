/* MATCHED  zz_002bae8_ @ 0x8002bae8  (11 instructions)
 *
 *   8002bae8  9421fff0  stwu r1, -0x10(r1)
 *   8002baec  7c0802a6  mflr r0
 *   8002baf0  38600000  li r3, 0
 *   8002baf4  90010014  stw r0, 0x14(r1)
 *   8002baf8  4824576d  bl 0x80271264
 *   8002bafc  38600000  li r3, 0
 *   8002bb00  482450d5  bl 0x80270bd4
 *   8002bb04  80010014  lwz r0, 0x14(r1)
 *   8002bb08  7c0803a6  mtlr r0
 *   8002bb0c  38210010  addi r1, r1, 0x10
 *   8002bb10  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 8251d35974e2128cd1834cbeb0ed41b28a2645ca9d7a019f0660eafbef85439d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0270bd4_(int);
extern int zz_0271264_(int);

int f(void)
{
    zz_0271264_(0);
    return zz_0270bd4_(0);
}
