/* MATCHED  zz_0191014_ @ 0x80191014  (9 instructions)
 *
 *   80191014  9421fff0  stwu r1, -0x10(r1)
 *   80191018  7c0802a6  mflr r0
 *   8019101c  90010014  stw r0, 0x14(r1)
 *   80191020  48000019  bl 0x80191038
 *   80191024  48000049  bl 0x8019106c
 *   80191028  80010014  lwz r0, 0x14(r1)
 *   8019102c  7c0803a6  mtlr r0
 *   80191030  38210010  addi r1, r1, 0x10
 *   80191034  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6ba000aaea089a5695b5ef761d6a1c505b6e3939869fae47bd59faf0d2dce498
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0191038_(void);
extern int zz_019106c_(void);

int f(void)
{
    zz_0191038_();
    return zz_019106c_();
}
