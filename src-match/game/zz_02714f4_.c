/* MATCHED  zz_02714f4_ @ 0x802714f4  (8 instructions)
 *
 *   802714f4  9421fff0  stwu r1, -0x10(r1)
 *   802714f8  7c0802a6  mflr r0
 *   802714fc  90010014  stw r0, 0x14(r1)
 *   80271500  48008b65  bl 0x8027a064
 *   80271504  80010014  lwz r0, 0x14(r1)
 *   80271508  7c0803a6  mtlr r0
 *   8027150c  38210010  addi r1, r1, 0x10
 *   80271510  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : cd2684d2e648bb8fe422105ed9ab7c8890b41d0729fd78104e8883a082a0a48d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027a064_(void);

void f(void)
{
    zz_027a064_();
}
