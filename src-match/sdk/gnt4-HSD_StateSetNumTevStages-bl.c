/* MATCHED  gnt4-HSD_StateSetNumTevStages-bl @ 0x80241e94  (12 instructions)
 *
 *   80241e94  9421fff0  stwu r1, -0x10(r1)
 *   80241e98  7c0802a6  mflr r0
 *   80241e9c  90010014  stw r0, 0x14(r1)
 *   80241ea0  800db370  lwz r0, -0x4c90(r13)
 *   80241ea4  5403063e  clrlwi r3, r0, 0x18
 *   80241ea8  4bfe8441  bl 0x8022a2e8
 *   80241eac  38000000  li r0, 0
 *   80241eb0  900db370  stw r0, -0x4c90(r13)
 *   80241eb4  80010014  lwz r0, 0x14(r1)
 *   80241eb8  7c0803a6  mtlr r0
 *   80241ebc  38210010  addi r1, r1, 0x10
 *   80241ec0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz clrlwi bl li stw lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ee9c2bc3f0723022f496bf80249de7420a24e85ef0e00e91821d5f1cc3eae42e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436910;

extern int FUN_8022a2e8(int);

void f(void)
{
    FUN_8022a2e8(DAT_80436910 & 0xff);
    DAT_80436910 = 0;
}
