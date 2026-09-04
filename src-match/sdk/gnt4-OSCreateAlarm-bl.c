/* MATCHED  gnt4-OSCreateAlarm-bl @ 0x801ff628  (4 instructions)
 *
 *   801ff628  38000000  li r0, 0
 *   801ff62c  90030000  stw r0, 0(r3)
 *   801ff630  90030004  stw r0, 4(r3)
 *   801ff634  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : true
 *   source sha256    : ecf9e3b85e73438242d591b7bb0edeff7484370f9c42d9b4201fddc703c4f16a
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
    p0->field_0 = 0;
    p0->field_4 = 0;
}
