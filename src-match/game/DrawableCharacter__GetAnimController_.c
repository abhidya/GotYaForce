/* MATCHED  DrawableCharacter::GetAnimController( @ 0x802a0bcc  (3 instructions)
 *
 *   802a0bcc  80631b30  lwz r3, 0x1b30(r3)
 *   802a0bd0  8063007c  lwz r3, 0x7c(r3)
 *   802a0bd4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lwz blr
 *   exact_bytes      : true
 *   source sha256    : 307958063f6703fd78de77a051126e1cc894eb87f2d31e6144243910a3713f32
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0_1b30 {
    char pad_0[0x7c];
    int                  field_7c;
} S0_1b30;

typedef struct S0 {
    char pad_0[0x1b30];
    S0_1b30 *            field_1b30;
} S0;

int f(S0 *p0)
{
    return p0->field_1b30->field_7c;
}
