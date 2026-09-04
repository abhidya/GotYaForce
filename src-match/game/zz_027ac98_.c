/* MATCHED  zz_027ac98_ @ 0x8027ac98  (5 instructions)
 *
 *   8027ac98  28030000  cmplwi r3, 0
 *   8027ac9c  4d820020  beqlr
 *   8027aca0  38000000  li r0, 0
 *   8027aca4  90030000  stw r0, 0(r3)
 *   8027aca8  4e800020  blr
 *
 * Same guarded-store shape with a different stored literal.
 * Iterations to match: 1.  exact_bytes: true.
 */

typedef struct S {
    int state;
} S;

void f(S *s)
{
    if (s == 0)
        return;
    s->state = 0;
}
