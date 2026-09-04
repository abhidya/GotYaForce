/* BLOCKED  zz_008bbc0_ @ 0x8008bbc0  (4 instructions)  -- NOT MATCHED
 *
 *   8008bbc0  3c6000ff  lis  r3, 0xff
 *   8008bbc4  38031f7f  addi r0, r3, 0x1f7f      ; r0 = 0x00FF1F7F
 *   8008bbc8  7c830038  and  r3, r4, r0
 *   8008bbcc  4e800020  blr
 *
 * The spike's own first-choice target (doc section 3.4).  mwcc-rs refuses it:
 *
 *   mwcc: a general register was requested for a non-leaf expression:
 *         IntegerLiteral(16719743) (in function 'f')
 *
 * mwcc-rs implements only the `rlwinm` path for AND-with-constant, so a mask
 * that is not a contiguous bit run has nowhere to go.  Real MWCC materialises
 * the constant with lis+addi -- which is visible in the retail bytes above --
 * and uses a register `and`.  The sibling OR / XOR / ADD paths in mwcc-rs
 * already materialise constants correctly, so this is ONE MISSING LOWERING,
 * not a deep gap, and it is the single highest-value contribution this
 * project could make upstream.
 *
 * The C below is almost certainly correct.  It has never compiled.
 */

int f(int unused, int value)
{
    return value & 0x00FF1F7F;
}
