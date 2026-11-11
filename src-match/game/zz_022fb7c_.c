/* MATCHED  zz_022fb7c_ @ 0x8022fb7c  (4 instructions)
 *
 *   8022fb7c  3c60803f  lis r3, -0x7fc1
 *   8022fb80  38637680  addi r3, r3, 0x7680
 *   8022fb84  80630080  lwz r3, 0x80(r3)
 *   8022fb88  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : c8722aa070ebcd7313b890969a73b61162a0a3029567c5ab62445d7731c4ba97
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803f7680 {
    char pad_0[0x80];
    int                  field_80;
} G803f7680;

extern G803f7680 DAT_803f7680;

int f(void)
{
    return DAT_803f7680.field_80;
}
