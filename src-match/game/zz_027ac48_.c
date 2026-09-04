/* MATCHED  zz_027ac48_ @ 0x8027ac48  (8 instructions)
 *
 *   8027ac48  9421fff0  stwu r1, -0x10(r1)
 *   8027ac4c  7c0802a6  mflr r0
 *   8027ac50  90010014  stw r0, 0x14(r1)
 *   8027ac54  4bffe7c1  bl 0x80279414
 *   8027ac58  80010014  lwz r0, 0x14(r1)
 *   8027ac5c  7c0803a6  mtlr r0
 *   8027ac60  38210010  addi r1, r1, 0x10
 *   8027ac64  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0458cff1e8c0c50daed63b3d78e4c419a14fec037d4b42d83163b318ca8689f8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279414_(void);

void f(void)
{
    zz_0279414_();
}
