/* MATCHED  zz_01f17c8_ @ 0x801f17c8  (13 instructions)
 *
 *   801f17c8  9421fff0  stwu r1, -0x10(r1)
 *   801f17cc  7c0802a6  mflr r0
 *   801f17d0  90010014  stw r0, 0x14(r1)
 *   801f17d4  4be98999  bl 0x8008a16c
 *   801f17d8  38600038  li r3, 0x38
 *   801f17dc  4be98425  bl 0x80089c00
 *   801f17e0  3c608009  lis r3, -0x7ff7
 *   801f17e4  38639f28  addi r3, r3, -0x60d8
 *   801f17e8  4be9a91d  bl 0x8008c104
 *   801f17ec  80010014  lwz r0, 0x14(r1)
 *   801f17f0  7c0803a6  mtlr r0
 *   801f17f4  38210010  addi r1, r1, 0x10
 *   801f17f8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3a9cab7da159b66dda22de0a90cf2fcdfb2dfd35f35f59de809be6428ec6e1fc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80089f28;

extern int zz_0089c00_(int);
extern int zz_008a16c_(void);
extern int zz_008c104_(int);

int f(void)
{
    zz_008a16c_();
    zz_0089c00_(0x38);
    return zz_008c104_(&DAT_80089f28);
}
