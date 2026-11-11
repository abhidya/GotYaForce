/* MATCHED  zz_01c7dd4_ @ 0x801c7dd4  (4 instructions)
 *
 *   801c7dd4  3c60803d  lis r3, -0x7fc3
 *   801c7dd8  38635d78  addi r3, r3, 0x5d78
 *   801c7ddc  8063001c  lwz r3, 0x1c(r3)
 *   801c7de0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : 037a03e9e95121e74d25551be6617f8907f75072b8e65748a1bb877442a6778b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803d5d78 {
    char pad_0[0x1c];
    int                  field_1c;
} G803d5d78;

extern G803d5d78 DAT_803d5d78;

int f(void)
{
    return DAT_803d5d78.field_1c;
}
