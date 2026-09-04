/* MATCHED  zz_02a6b30_ @ 0x802a6b30  (4 instructions)
 *
 *   802a6b30  2c040000  cmpwi r4, 0
 *   802a6b34  4c810020  blelr
 *   802a6b38  9083000c  stw r4, 0xc(r3)
 *   802a6b3c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmpwi blelr stw blr
 *   exact_bytes      : true
 *   source sha256    : 0bf587ec1b091b681b0c00acc54324a3f0fc44767e50b05c83f869f1ed255631
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

void f(S0 *p0, int p1)
{
    if (p1 <= 0)
        return;
    p0->field_c = p1;
}
