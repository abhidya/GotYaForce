/* MATCHED  zz_008bbc0_ @ 0x8008bbc0  (4 instructions)
 *
 *   8008bbc0  3c6000ff  lis  r3, 0xff
 *   8008bbc4  38031f7f  addi r0, r3, 0x1f7f      ; r0 = 0x00FF1F7F
 *   8008bbc8  7c830038  and  r3, r4, r0
 *   8008bbcc  4e800020  blr
 *
 * The spike's own first-choice target (doc section 3.4), blocked from
 * 2026-09-03 to 2026-09-04 and now matched.  The C never changed -- it is the
 * same one line that was committed under `blocked/` -- so this is entirely a
 * COMPILER result, and the honest reading of the old header ("the C below is
 * almost certainly correct; it has never compiled") is that it was right.
 *
 * mwcc-rs at the pinned commit implemented only the `rlwinm` path for
 * AND-with-constant, so a mask that is not a contiguous bit run had nowhere to
 * go and the compiler reported
 *
 *   mwcc: a general register was requested for a non-leaf expression:
 *         IntegerLiteral(16719743) (in function 'f')
 *
 * This project's fork adds the three forms mwcc actually uses -- `andi.` for a
 * mask inside 16 bits, `andis.` when only the high half is set, and, for a
 * constant with both halves set, materialise-and-AND.  The retail bytes above
 * ARE the specification of that last form: the high half goes to a free
 * register (here r3, the dead incoming first argument), the assembled constant
 * to the scratch r0, and the operand stays where it is.
 *
 * See research/tools/matching-decomp/mwcc_fork.py and TOOLCHAIN.md section 5.
 *
 * Iterations to match: 1 (the original candidate, unmodified).
 */

int f(int unused, int value)
{
    return value & 0x00FF1F7F;
}
