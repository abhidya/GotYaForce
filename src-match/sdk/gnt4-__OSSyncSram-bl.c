/* MATCHED  gnt4-__OSSyncSram-bl @ 0x8020561c  (4 instructions)
 *
 *   8020561c  3c60803d  lis r3, -0x7fc3
 *   80205620  38636c60  addi r3, r3, 0x6c60
 *   80205624  8063004c  lwz r3, 0x4c(r3)
 *   80205628  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : 95c3952c9d52b424223cedadfc4be56272975530c3e1f256e996cc5ed4a50cb2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803d6c60 {
    char pad_0[0x4c];
    int                  field_4c;
} G803d6c60;

extern G803d6c60 DAT_803d6c60;

int f(void)
{
    return DAT_803d6c60.field_4c;
}
