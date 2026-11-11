/* MATCHED  zz_02a1168_ @ 0x802a1168  (4 instructions)
 *
 *   802a1168  3c608042  lis r3, -0x7fbe
 *   802a116c  3863d22c  addi r3, r3, -0x2dd4
 *   802a1170  806301fc  lwz r3, 0x1fc(r3)
 *   802a1174  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : 2864275d212d4d7788080a2f2c7814614285a892e58022c654eaad56bc0e7e5d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G8041d22c {
    char pad_0[0x1fc];
    int                  field_1fc;
} G8041d22c;

extern G8041d22c DAT_8041d22c;

int f(void)
{
    return DAT_8041d22c.field_1fc;
}
