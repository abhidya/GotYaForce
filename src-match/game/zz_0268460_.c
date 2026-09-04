/* MATCHED  zz_0268460_ @ 0x80268460  (3 instructions)
 *
 *   80268460  8863000e  lbz r3, 0xe(r3)
 *   80268464  7c630774  extsb r3, r3
 *   80268468  4e800020  blr
 *
 * Second instance of the signed-char accessor shape; same GC/1.3 exclusion.
 * Iterations to match: 1 (the idiom was already learned on zz_02650c0_).
 * exact_bytes: true.
 */

typedef struct S {
    char pad[0xe];
    char flag;
} S;

int f(S *s)
{
    return s->flag;
}
