/* MATCHED  zz_02a4be0_ @ 0x802a4be0  (3 instructions)
 *
 *   802a4be0  9083010c  stw r4, 0x10c(r3)
 *   802a4be4  90a30110  stw r5, 0x110(r3)
 *   802a4be8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : e4931e2224d4d1109efe7525768a659e4d73ce6fb47d52a7a312140b7caee6aa
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x10c];
    int            field_10c;
    int            field_110;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_10c = p1;
    p0->field_110 = p2;
}
