/* MATCHED  zz_02683c4_ @ 0x802683c4  (2 instructions)
 *
 *   802683c4  80630030  lwz r3, 0x30(r3)
 *   802683c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 477971f85a283f0391ff22a14a8d3aada35229f30a523c617d5b2d246667d000
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x30];
    int            field_30;
} S0;

int f(S0 *p0)
{
    return p0->field_30;
}
