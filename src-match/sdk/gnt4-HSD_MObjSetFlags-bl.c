/* MATCHED  gnt4-HSD_MObjSetFlags-bl @ 0x802422ac  (6 instructions)
 *
 *   802422ac  28030000  cmplwi r3, 0
 *   802422b0  4d820020  beqlr
 *   802422b4  80030004  lwz r0, 4(r3)
 *   802422b8  7c002378  or r0, r0, r4
 *   802422bc  90030004  stw r0, 4(r3)
 *   802422c0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr lwz or stw blr
 *   exact_bytes      : true
 *   source sha256    : d97452803fdd2f3eb5ab8308c932ee95e1c11ccaa2de33e8353dd2c5d3a1146d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_4 = p0->field_4 | p1;
}
