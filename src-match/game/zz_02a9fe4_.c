/* MATCHED  zz_02a9fe4_ @ 0x802a9fe4  (9 instructions)
 *
 *   802a9fe4  9421fff0  stwu r1, -0x10(r1)
 *   802a9fe8  7c0802a6  mflr r0
 *   802a9fec  90010014  stw r0, 0x14(r1)
 *   802a9ff0  80630040  lwz r3, 0x40(r3)
 *   802a9ff4  4bfee8e1  bl 0x802988d4
 *   802a9ff8  80010014  lwz r0, 0x14(r1)
 *   802a9ffc  7c0803a6  mtlr r0
 *   802aa000  38210010  addi r1, r1, 0x10
 *   802aa004  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0cd2b93e9e1baf92d116c7be80e090fb523963eb0772bf4c9d6e48839f6f7b11
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x40];
    int                  field_40;
} S0;

extern int zz_02988d4_(int);

int f(S0 *p0)
{
    return zz_02988d4_(p0->field_40);
}
