/* MATCHED  zz_029aa40_ @ 0x8029aa40  (5 instructions)
 *
 *   8029aa40  38000000  li r0, 0
 *   8029aa44  90030000  stw r0, 0(r3)
 *   8029aa48  9003000c  stw r0, 0xc(r3)
 *   8029aa4c  90030090  stw r0, 0x90(r3)
 *   8029aa50  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 20d5775f7d2fa4643f2736dcf27233f34bf2a38c6c17cc19ed23212b09abb0be
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
    char pad_4[0x8];
    int            field_c;
    char pad_10[0x80];
    int            field_90;
} S0;

void f(S0 *p0)
{
    p0->field_0 = 0;
    p0->field_c = 0;
    p0->field_90 = 0;
}
