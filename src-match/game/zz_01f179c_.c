/* MATCHED  zz_01f179c_ @ 0x801f179c  (11 instructions)
 *
 *   801f179c  9421fff0  stwu r1, -0x10(r1)
 *   801f17a0  7c0802a6  mflr r0
 *   801f17a4  38600038  li r3, 0x38
 *   801f17a8  90010014  stw r0, 0x14(r1)
 *   801f17ac  4be980ed  bl 0x80089898
 *   801f17b0  4be97da5  bl 0x80089554
 *   801f17b4  4be97ea5  bl 0x80089658
 *   801f17b8  80010014  lwz r0, 0x14(r1)
 *   801f17bc  7c0803a6  mtlr r0
 *   801f17c0  38210010  addi r1, r1, 0x10
 *   801f17c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 500b4dff9487ec08daf7f5abdc28c5047ccdd5ef0c38dc44b17d3d706252ccf9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089554_(void);
extern int zz_0089658_(void);
extern int zz_0089898_(int);

int f(void)
{
    zz_0089898_(0x38);
    zz_0089554_();
    return zz_0089658_();
}
