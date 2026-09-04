/* MATCHED  zz_02502c4_ @ 0x802502c4  (6 instructions)
 *
 *   802502c4  28030000  cmplwi r3, 0
 *   802502c8  4182000c  beq 0x802502d4
 *   802502cc  80630014  lwz r3, 0x14(r3)
 *   802502d0  4e800020  blr
 *   802502d4  38600000  li r3, 0
 *   802502d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beq lwz blr li blr
 *   exact_bytes      : true
 *   source sha256    : 157d5d868f093eac0a7b85600fe54fbf8a3e3e91ca5705303d7b993886f29060
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x14];
    int                  field_14;
} S0;

int f(S0 *p0)
{
    if (p0 != 0)
        return p0->field_14;
    return 0;
}
