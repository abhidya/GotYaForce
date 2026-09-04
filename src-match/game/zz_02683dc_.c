/* MATCHED  zz_02683dc_ @ 0x802683dc  (2 instructions)
 *
 *   802683dc  a8630024  lha r3, 0x24(r3)
 *   802683e0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha blr
 *   exact_bytes      : true
 *   source sha256    : 6e63256ddd4151dd29da736950483f1b9b0a48f3b3bf148b290192796b78c7f4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x24];
    short          field_24;
} S0;

int f(S0 *p0)
{
    return p0->field_24;
}
