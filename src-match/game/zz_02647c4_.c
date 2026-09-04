/* MATCHED  zz_02647c4_ @ 0x802647c4  (9 instructions)
 *
 *   802647c4  9421fff0  stwu r1, -0x10(r1)
 *   802647c8  7c0802a6  mflr r0
 *   802647cc  90010014  stw r0, 0x14(r1)
 *   802647d0  80630004  lwz r3, 4(r3)
 *   802647d4  48003c99  bl 0x8026846c
 *   802647d8  80010014  lwz r0, 0x14(r1)
 *   802647dc  7c0803a6  mtlr r0
 *   802647e0  38210010  addi r1, r1, 0x10
 *   802647e4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : eac4e53c5149d3a864e0fb3f5990f114ee793915ef3f37fb72db570aa47afa12
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_026846c_(int);

int f(S0 *p0)
{
    return zz_026846c_(p0->field_4);
}
