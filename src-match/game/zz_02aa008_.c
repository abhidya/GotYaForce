/* MATCHED  zz_02aa008_ @ 0x802aa008  (9 instructions)
 *
 *   802aa008  9421fff0  stwu r1, -0x10(r1)
 *   802aa00c  7c0802a6  mflr r0
 *   802aa010  90010014  stw r0, 0x14(r1)
 *   802aa014  80630040  lwz r3, 0x40(r3)
 *   802aa018  4bfee949  bl 0x80298960
 *   802aa01c  80010014  lwz r0, 0x14(r1)
 *   802aa020  7c0803a6  mtlr r0
 *   802aa024  38210010  addi r1, r1, 0x10
 *   802aa028  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d9eb2bc785987871b3ebf4d7cecf0b666a34a0be4e9afc9720a11caa2dca45ea
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x40];
    int                  field_40;
} S0;

extern int zz_0298960_(int);

int f(S0 *p0)
{
    return zz_0298960_(p0->field_40);
}
