/* MATCHED  zz_029af30_ @ 0x8029af30  (3 instructions)
 *
 *   8029af30  80631aec  lwz r3, 0x1aec(r3)
 *   8029af34  80630014  lwz r3, 0x14(r3)
 *   8029af38  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lwz blr
 *   exact_bytes      : true
 *   source sha256    : fe2bfb557f4999a61149386331697c8f5588813f9bfc814d563f4f6da4403466
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0_1aec {
    char pad_0[0x14];
    int                  field_14;
} S0_1aec;

typedef struct S0 {
    char pad_0[0x1aec];
    S0_1aec *            field_1aec;
} S0;

int f(S0 *p0)
{
    return p0->field_1aec->field_14;
}
