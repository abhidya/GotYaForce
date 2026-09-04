/* MATCHED  zz_007f88c_ @ 0x8007f88c  (3 instructions)
 *
 *   8007f88c  38000003  li r0, 3
 *   8007f890  98030018  stb r0, 0x18(r3)
 *   8007f894  4e800020  blr
 *
 * Storing a literal into a byte field.  Note the literal is materialised into
 * r0, the Metrowerks scratch register, not into a parameter register.
 * Iterations to match: 1.  exact_bytes: true.
 */

typedef struct S {
    char pad[0x18];
    char field_18;
} S;

void f(S *s)
{
    s->field_18 = 3;
}
