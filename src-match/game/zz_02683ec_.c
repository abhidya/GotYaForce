/* MATCHED  zz_02683ec_ @ 0x802683ec  (2 instructions)
 *
 *   802683ec  80630010  lwz r3, 0x10(r3)
 *   802683f0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 72aac307e78705627348fa01d7c7677f077a3389b9239ff9e6f6d2cbb4784984
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x10];
    int            field_10;
} S0;

int f(S0 *p0)
{
    return p0->field_10;
}
