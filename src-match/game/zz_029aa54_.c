/* MATCHED  zz_029aa54_ @ 0x8029aa54  (7 instructions)
 *
 *   8029aa54  38000000  li r0, 0
 *   8029aa58  90030000  stw r0, 0(r3)
 *   8029aa5c  90030004  stw r0, 4(r3)
 *   8029aa60  90030008  stw r0, 8(r3)
 *   8029aa64  9003000c  stw r0, 0xc(r3)
 *   8029aa68  90030090  stw r0, 0x90(r3)
 *   8029aa6c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 094cb77609e9dd430dd62861a5405dcbe1e095776c451739d407546d85be441d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
    int            field_4;
    int            field_8;
    int            field_c;
    char pad_10[0x80];
    int            field_90;
} S0;

void f(S0 *p0)
{
    p0->field_0 = 0;
    p0->field_4 = 0;
    p0->field_8 = 0;
    p0->field_c = 0;
    p0->field_90 = 0;
}
