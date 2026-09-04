/* MATCHED  zz_0180820_ @ 0x80180820  (12 instructions)
 *
 *   80180820  9421fff0  stwu r1, -0x10(r1)
 *   80180824  7c0802a6  mflr r0
 *   80180828  90010014  stw r0, 0x14(r1)
 *   8018082c  4be8832d  bl 0x80008b58
 *   80180830  4be884c5  bl 0x80008cf4
 *   80180834  4801709d  bl 0x801978d0
 *   80180838  38600000  li r3, 0
 *   8018083c  4be85149  bl 0x80005984
 *   80180840  80010014  lwz r0, 0x14(r1)
 *   80180844  7c0803a6  mtlr r0
 *   80180848  38210010  addi r1, r1, 0x10
 *   8018084c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl bl li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2cbf9c5b7a91ba0c77c79aa757b0ed3d842374d1a827949944f6bcc6e75f56ca
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0005984_(int);
extern int zz_0008b58_(void);
extern int zz_0008cf4_(void);
extern int zz_01978d0_(void);

int f(void)
{
    zz_0008b58_();
    zz_0008cf4_();
    zz_01978d0_();
    return zz_0005984_(0);
}
