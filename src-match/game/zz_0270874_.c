/* MATCHED  zz_0270874_ @ 0x80270874  (6 instructions)
 *
 *   80270874  8003000c  lwz r0, 0xc(r3)
 *   80270878  2c000003  cmpwi r0, 3
 *   8027087c  4c820020  bnelr
 *   80270880  38000000  li r0, 0
 *   80270884  9003000c  stw r0, 0xc(r3)
 *   80270888  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz cmpwi bnelr li stw blr
 *   exact_bytes      : true
 *   source sha256    : 9ff21564f8cbc41570ef16dd046cfdd6cc5be07e9a34ce073e73f6b06ec354b3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

void f(S0 *p0)
{
    if (p0->field_c != 3)
        return;
    p0->field_c = 0;
}
