/* MATCHED  gnt4-HSD_DObjSetFlags-bl @ 0x8023d770  (6 instructions)
 *
 *   8023d770  28030000  cmplwi r3, 0
 *   8023d774  4d820020  beqlr
 *   8023d778  80030014  lwz r0, 0x14(r3)
 *   8023d77c  7c002378  or r0, r0, r4
 *   8023d780  90030014  stw r0, 0x14(r3)
 *   8023d784  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr lwz or stw blr
 *   exact_bytes      : true
 *   source sha256    : 42450a85a00600d6f69c83d68b1b54483084ddb51ee674cba5d0c97d09b5ef84
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x14];
    int                  field_14;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_14 = p0->field_14 | p1;
}
