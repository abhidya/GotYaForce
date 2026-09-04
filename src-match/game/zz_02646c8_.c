/* MATCHED  zz_02646c8_ @ 0x802646c8  (9 instructions)
 *
 *   802646c8  9421fff0  stwu r1, -0x10(r1)
 *   802646cc  7c0802a6  mflr r0
 *   802646d0  90010014  stw r0, 0x14(r1)
 *   802646d4  80630004  lwz r3, 4(r3)
 *   802646d8  48003cf5  bl 0x802683cc
 *   802646dc  80010014  lwz r0, 0x14(r1)
 *   802646e0  7c0803a6  mtlr r0
 *   802646e4  38210010  addi r1, r1, 0x10
 *   802646e8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4c4606623968ce36eb87a303af5b8faf7d44448ee090f65a7653a6a77651acd3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683cc_(int);

int f(S0 *p0)
{
    return zz_02683cc_(p0->field_4);
}
