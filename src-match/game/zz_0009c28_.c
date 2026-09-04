/* MATCHED  zz_0009c28_ @ 0x80009c28  (2 instructions)
 *
 *   80009c28  90830018  stw r4, 0x18(r3)
 *   80009c2c  4e800020  blr
 *
 * A member setter.  Iterations to match: 1.  exact_bytes: true.
 */

typedef struct S {
    char pad[0x18];
    int  field_18;
} S;

void f(S *s, int value)
{
    s->field_18 = value;
}
