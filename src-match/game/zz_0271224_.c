/* MATCHED  zz_0271224_ @ 0x80271224  (8 instructions)
 *
 *   80271224  9421fff0  stwu r1, -0x10(r1)
 *   80271228  7c0802a6  mflr r0
 *   8027122c  90010014  stw r0, 0x14(r1)
 *   80271230  48006ae5  bl 0x80277d14
 *   80271234  80010014  lwz r0, 0x14(r1)
 *   80271238  7c0803a6  mtlr r0
 *   8027123c  38210010  addi r1, r1, 0x10
 *   80271240  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 553fb148a3332bc27d1922f06a42750ba47f60b4ed05ef518e81910266a5d582
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0277d14_(void);

void f(void)
{
    zz_0277d14_();
}
