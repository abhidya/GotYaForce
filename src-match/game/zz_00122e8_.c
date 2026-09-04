/* MATCHED  zz_00122e8_ @ 0x800122e8  (8 instructions)
 *
 *   800122e8  9421fff0  stwu r1, -0x10(r1)
 *   800122ec  7c0802a6  mflr r0
 *   800122f0  90010014  stw r0, 0x14(r1)
 *   800122f4  48000345  bl 0x80012638
 *   800122f8  80010014  lwz r0, 0x14(r1)
 *   800122fc  7c0803a6  mtlr r0
 *   80012300  38210010  addi r1, r1, 0x10
 *   80012304  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7e46e64e42e4dc1782736d7a350ee15aa7eae713015f9dbcb4a774f4bf56e003
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0012638_(void);

void f(void)
{
    zz_0012638_();
}
