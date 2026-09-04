/* MATCHED  zz_00122c8_ @ 0x800122c8  (8 instructions)
 *
 *   800122c8  9421fff0  stwu r1, -0x10(r1)
 *   800122cc  7c0802a6  mflr r0
 *   800122d0  90010014  stw r0, 0x14(r1)
 *   800122d4  48000035  bl 0x80012308        -> zz_0012308_
 *   800122d8  80010014  lwz r0, 0x14(r1)
 *   800122dc  7c0803a6  mtlr r0
 *   800122e0  38210010  addi r1, r1, 0x10
 *   800122e4  4e800020  blr
 *
 * The canonical Metrowerks non-leaf frame with one call.  This is the target
 * the harness's T6/T7 relocation controls were built around: the compiled
 * object leaves the `bl` operand ZERO and carries an R_PPC_REL24 naming the
 * callee, so `exact_bytes` is FALSE and the match is established by the
 * relocation's SYMBOL matching what the retail branch resolves to through the
 * link map.  Substituting any other callee makes the oracle report MISMATCH.
 *
 * Iterations to match: 1.  exact_bytes: false (correctly).
 */

extern void zz_0012308_(void);

void f(void)
{
    zz_0012308_();
}
