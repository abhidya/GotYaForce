/* MATCHED  gnt4-OSInitThreadQueue-bl @ 0x80205f04  (4 instructions)
 *
 *   80205f04  38000000  li r0, 0
 *   80205f08  90030004  stw r0, 4(r3)
 *   80205f0c  90030000  stw r0, 0(r3)
 *   80205f10  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : true
 *   source sha256    : ef30d06ede73604897ae4cbe8ef7b7ff0aab5891453b5ece8f2a303f8ee6fdb5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
    int            field_4;
} S0;

void f(S0 *p0)
{
    p0->field_4 = 0;
    p0->field_0 = 0;
}
