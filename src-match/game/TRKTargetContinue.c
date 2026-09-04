/* MATCHED  TRKTargetContinue @ 0x80231c3c  (13 instructions)
 *
 *   80231c3c  9421fff0  stwu r1, -0x10(r1)
 *   80231c40  7c0802a6  mflr r0
 *   80231c44  38600000  li r3, 0
 *   80231c48  90010014  stw r0, 0x14(r1)
 *   80231c4c  4bffdd11  bl 0x8022f95c
 *   80231c50  4bfffba9  bl 0x802317f8
 *   80231c54  4bffdbc9  bl 0x8022f81c
 *   80231c58  4bfffbd1  bl 0x80231828
 *   80231c5c  80010014  lwz r0, 0x14(r1)
 *   80231c60  38600000  li r3, 0
 *   80231c64  7c0803a6  mtlr r0
 *   80231c68  38210010  addi r1, r1, 0x10
 *   80231c6c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl bl bl bl lwz li mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2be3f4f52b90e075b662b582724b28586b544f27a3e5d13835d4cfe34cca2aee
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int TRKPostInterruptEvent(void);
extern int TRKTargetSetInputPendingPtr(int);
extern int zz_02317f8_(void);
extern int zz_0231828_(void);

int f(void)
{
    TRKTargetSetInputPendingPtr(0);
    zz_02317f8_();
    TRKPostInterruptEvent();
    zz_0231828_();
    return 0;
}
