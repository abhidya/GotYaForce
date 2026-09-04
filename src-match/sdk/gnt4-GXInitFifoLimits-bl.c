/* MATCHED  gnt4-GXInitFifoLimits-bl @ 0x8022536c  (3 instructions)
 *
 *   8022536c  9083000c  stw r4, 0xc(r3)
 *   80225370  90a30010  stw r5, 0x10(r3)
 *   80225374  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : fc1627f606b2aa9d7a96a2e54b4a201c3a04aa4dca9b2c6fe68411ba4a2425e0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int            field_c;
    int            field_10;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_c = p1;
    p0->field_10 = p2;
}
