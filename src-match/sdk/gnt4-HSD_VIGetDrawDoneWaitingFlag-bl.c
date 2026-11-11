/* MATCHED  gnt4-HSD_VIGetDrawDoneWaitingFlag-bl @ 0x802547e0  (4 instructions)
 *
 *   802547e0  3c608040  lis r3, -0x7fc0
 *   802547e4  38638e80  addi r3, r3, -0x7180
 *   802547e8  806301e0  lwz r3, 0x1e0(r3)
 *   802547ec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : bc7b057489d79a43648a1ebfd707396bfc7fc701c6873b864adfb3363c7b09c2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803f8e80 {
    char pad_0[0x1e0];
    int                  field_1e0;
} G803f8e80;

extern G803f8e80 DAT_803f8e80;

int f(void)
{
    return DAT_803f8e80.field_1e0;
}
