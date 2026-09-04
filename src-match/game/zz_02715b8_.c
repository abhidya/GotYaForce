/* MATCHED  zz_02715b8_ @ 0x802715b8  (8 instructions)
 *
 *   802715b8  9421fff0  stwu r1, -0x10(r1)
 *   802715bc  7c0802a6  mflr r0
 *   802715c0  90010014  stw r0, 0x14(r1)
 *   802715c4  48009611  bl 0x8027abd4
 *   802715c8  80010014  lwz r0, 0x14(r1)
 *   802715cc  7c0803a6  mtlr r0
 *   802715d0  38210010  addi r1, r1, 0x10
 *   802715d4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 43a3b36cc680bd72ae8142ff870068103529cff39061c3488c81ec9c2159d179
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027abd4_(void);

void f(void)
{
    zz_027abd4_();
}
