/* MATCHED  zz_0206f8c_ @ 0x80206f8c  (2 instructions)
 *
 *   80206f8c  806302d4  lwz r3, 0x2d4(r3)
 *   80206f90  4e800020  blr
 *
 * A plain member accessor.  r3 in, r3 out, no frame, no relocation.
 * Iterations to match: 1.  exact_bytes: true.
 */

typedef struct S {
    char pad[0x2d4];
    int  field_2d4;
} S;

int f(S *s)
{
    return s->field_2d4;
}
