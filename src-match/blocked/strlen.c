/* BLOCKED  strlen @ 0x80238db8  (7 instructions)  -- NOT MATCHED
 *
 *   80238db8  3883ffff  addi   r4, r3, -1
 *   80238dbc  3860ffff  li     r3, -1
 *   80238dc0  8c040001  lbzu   r0, 1(r4)
 *   80238dc4  38630001  addi   r3, r3, 1
 *   80238dc8  28000000  cmplwi r0, 0
 *   80238dcc  4082fff4  bne    0x80238dc0
 *   80238dd0  4e800020  blr
 *
 * The MSL runtime's strlen, and a genuine counted-free loop built on the
 * load-with-update form `lbzu`.  mwcc-rs does not generate update forms at
 * all, so no C spelling reaches these bytes.  Two were tried: a pre-increment
 * walk (refused outright) and a post-increment walk (compiled, diverged at
 * instruction 0).
 *
 * Recorded because `strlen` is a fair proxy for the MSL/SDK half of the
 * binary: the SDK code leans on exactly the idioms the general generator is
 * weakest at.
 */

unsigned long f(const char *s)
{
    unsigned long n = 0;
    while (*s++)
        n++;
    return n;
}
