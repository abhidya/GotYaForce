/* MATCHED  gnt4-HSD_StateSetNumTexGens-bl @ 0x80241e24  (12 instructions)
 *
 *   80241e24  9421fff0  stwu r1, -0x10(r1)
 *   80241e28  7c0802a6  mflr r0
 *   80241e2c  90010014  stw r0, 0x14(r1)
 *   80241e30  800db358  lwz r0, -0x4ca8(r13)
 *   80241e34  5403063e  clrlwi r3, r0, 0x18
 *   80241e38  4bfe4f35  bl 0x80226d6c
 *   80241e3c  38000000  li r0, 0
 *   80241e40  900db358  stw r0, -0x4ca8(r13)
 *   80241e44  80010014  lwz r0, 0x14(r1)
 *   80241e48  7c0803a6  mtlr r0
 *   80241e4c  38210010  addi r1, r1, 0x10
 *   80241e50  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz clrlwi bl li stw lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 471c7f74a82623fc3eab82add8f6225fd56b395f0825387211c54d173b6ba86d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368f8;

extern int FUN_80226d6c(int);

void f(void)
{
    FUN_80226d6c(DAT_804368f8 & 0xff);
    DAT_804368f8 = 0;
}
