/* MATCHED  gnt4-GXGetTexObjFmt-bl @ 0x80228f6c  (2 instructions)
 *
 *   80228f6c  80630014  lwz r3, 0x14(r3)
 *   80228f70  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 18c5fa9f7c6129a699ef86c8fe1aa87d6d5c0294c009b4a19e5f290f0869aead
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x14];
    int            field_14;
} S0;

int f(S0 *p0)
{
    return p0->field_14;
}
