/* MATCHED  gnt4-HSD_FogAdjGetFlags-bl @ 0x8025a6e0  (6 instructions)
 *
 *   8025a6e0  28030000  cmplwi r3, 0
 *   8025a6e4  4182000c  beq 0x8025a6f0
 *   8025a6e8  80630008  lwz r3, 8(r3)
 *   8025a6ec  4e800020  blr
 *   8025a6f0  38600000  li r3, 0
 *   8025a6f4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beq lwz blr li blr
 *   exact_bytes      : true
 *   source sha256    : 9e2be9113f79560457589aa467d7ef2a87ea2f038ea5f719b30d4f58c7000b5f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int                  field_8;
} S0;

int f(S0 *p0)
{
    if (p0 != 0)
        return p0->field_8;
    return 0;
}
