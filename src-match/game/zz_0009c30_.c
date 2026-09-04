/* MATCHED  zz_0009c30_ @ 0x80009c30  (2 instructions)
 *
 *   80009c30  9083001c  stw r4, 0x1c(r3)
 *   80009c34  4e800020  blr
 *
 * The link-order neighbour of zz_0009c28_, and almost certainly the next
 * setter in the same translation unit.  Iterations to match: 1.
 * exact_bytes: true.
 */

typedef struct S {
    char pad[0x1c];
    int  field_1c;
} S;

void f(S *s, int value)
{
    s->field_1c = value;
}
