/* MATCHED  gnt4-HSD_ObjFree @ 0x80257440  (10 instructions)
 *
 *   80257440  80030004  lwz r0, 4(r3)
 *   80257444  90040000  stw r0, 0(r4)
 *   80257448  90830004  stw r4, 4(r3)
 *   8025744c  8083000c  lwz r4, 0xc(r3)
 *   80257450  38040001  addi r0, r4, 1
 *   80257454  9003000c  stw r0, 0xc(r3)
 *   80257458  80830008  lwz r4, 8(r3)
 *   8025745c  3804ffff  addi r0, r4, -1
 *   80257460  90030008  stw r0, 8(r3)
 *   80257464  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw stw lwz addi stw lwz addi stw blr
 *   exact_bytes      : true
 *   source sha256    : 790a0d86ea301a94d4135a02ff508a010f746e9117529d3382f60c7d024d0dcb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
    int                  field_8;
    int                  field_c;
} S0;

typedef struct S1 {
    int                  field_0;
} S1;

void f(S0 *p0, S1 *p1)
{
    p1->field_0 = p0->field_4;
    p0->field_4 = p1;
    p0->field_c = p0->field_c + 1;
    p0->field_8 = p0->field_8 + -1;
}
