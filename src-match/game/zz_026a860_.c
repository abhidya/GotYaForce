/* MATCHED  zz_026a860_ @ 0x8026a860  (3 instructions)
 *
 *   8026a860  38000001  li r0, 1
 *   8026a864  98030003  stb r0, 3(r3)
 *   8026a868  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : true
 *   source sha256    : 2ad45e1893ee629ee935c5ecb7e1ef2f08f99e79f5bdf47e6ffa97941fbc9a83
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x3];
    char           field_3;
} S0;

void f(S0 *p0)
{
    p0->field_3 = 1;
}
