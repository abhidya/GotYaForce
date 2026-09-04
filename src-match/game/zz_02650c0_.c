/* MATCHED  zz_02650c0_ @ 0x802650c0  (3 instructions)
 *
 *   802650c0  88630001  lbz r3, 1(r3)
 *   802650c4  7c630774  extsb r3, r3
 *   802650c8  4e800020  blr
 *
 * THE VERSION DISCRIMINATOR.  Plain `char` is signed by default from
 * mwcceppc 2.4.2 build 81 (GC/1.3.2) onward and UNSIGNED in build 53
 * (GC/1.3), so the `extsb` is present here only because the game was NOT
 * built with GC/1.3.  This is the one function in this set whose calibration
 * sweep discriminates: 36 of 42 (build x -O level) combinations match, and
 * the six that fail are exactly the six GC/1.3 rows.
 *
 * The first candidate returned `char` rather than `int` and lost the
 * `extsb`, because mwcc-rs does not sign-extend a `char` return value on the
 * way out (real MWCC does).  Widening the return type to `int` puts the
 * extension back where the retail bytes have it.
 *
 * Iterations to match: 2.  exact_bytes: true.
 */

typedef struct S {
    char pad0;
    char flag;
} S;

int f(S *s)
{
    return s->flag;
}
