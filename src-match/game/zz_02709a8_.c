/* MATCHED  zz_02709a8_ @ 0x802709a8  (4 instructions)
 *
 *   802709a8  b0830034  sth r4, 0x34(r3)
 *   802709ac  b0a30036  sth r5, 0x36(r3)
 *   802709b0  b0c30038  sth r6, 0x38(r3)
 *   802709b4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : sth sth sth blr
 *   exact_bytes      : true
 *   source sha256    : ca70e80b542a86d95a88af4135e9cc0a34f2e004a6137f6383446e156e51c82e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x34];
    short          field_34;
    short          field_36;
    short          field_38;
} S0;

void f(S0 *p0, int p1, int p2, int p3)
{
    p0->field_34 = p1;
    p0->field_36 = p2;
    p0->field_38 = p3;
}
