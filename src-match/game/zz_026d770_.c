/* MATCHED  zz_026d770_ @ 0x8026d770  (7 instructions)
 *
 *   8026d770  80030008  lwz r0, 8(r3)
 *   8026d774  28000000  cmplwi r0, 0
 *   8026d778  4182000c  beq 0x8026d784
 *   8026d77c  80630054  lwz r3, 0x54(r3)
 *   8026d780  4e800020  blr
 *   8026d784  38600000  li r3, 0
 *   8026d788  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (6 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 6
 *   shape            : lwz cmplwi beq lwz blr li blr
 *   exact_bytes      : true
 *   source sha256    : f71036f62806e35770b3138172321349a527b4ed43c508fc0d467151fc8c0994
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    unsigned int                  field_8;
    char pad_c[0x48];
    int                  field_54;
} S0;

int f(S0 *p0)
{
    if (p0->field_8 != 0)
        return p0->field_54;
    return 0;
}
