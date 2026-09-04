/* Candidate for zz_00660b8_ @ 0x800660b8 -- UNVERIFIED, NEVER COMPILED.
 *
 * RETAIL:
 *   800660b8  8803057b  lbz  r0, 0x57b(r3)
 *   800660bc  7c002378  or   r0, r0, r4      rA=r0 <- rS=r0 | rB=r4
 *   800660c0  9803057b  stb  r0, 0x57b(r3)
 *   800660c4  4e800020  blr
 *
 * A one-line flag setter on a byte at offset 0x57B of the object in r3.
 * No frame and no calls: MWCC needed no stack, so the body is a single
 * read-modify-write and there is nowhere for a wrong guess to hide.
 *
 * The operand ORDER is load-bearing. Retail is `or r0, r0, r4` = loaded byte
 * in rS, argument in rB. Writing `f | self->flags57B` instead of
 * `self->flags57B | f` can swap rS and rB and produce 0x7c042378, which the
 * oracle rejects outright. Test T4 of selftest.py demonstrates that a
 * behaviourally identical rewrite of this exact function is rejected -- that
 * strictness is the whole value of the route, and its whole cost.
 */

typedef unsigned char u8;

struct Obj {
    u8 pad_000[0x57B];
    u8 flags57B;
};

void Obj_orFlags(struct Obj *self, u8 f)
{
    self->flags57B |= f;
}
