/* MATCHED  zz_0008948_ @ 0x80008948  (10 instructions)
 *
 *   80008948  9421fff0  stwu r1, -0x10(r1)
 *   8000894c  7c0802a6  mflr r0
 *   80008950  7c641b78  mr r4, r3
 *   80008954  90010014  stw r0, 0x14(r1)
 *   80008958  806dac70  lwz r3, -0x5390(r13)
 *   8000895c  4823f20d  bl 0x80247b68
 *   80008960  80010014  lwz r0, 0x14(r1)
 *   80008964  7c0803a6  mtlr r0
 *   80008968  38210010  addi r1, r1, 0x10
 *   8000896c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 68e394fa54f7b6c340cf98d80820616807e914ca8e9f7b26a77bddc3b63600da
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436210;

extern int FUN_80247b68(int, int);

int f(int p0)
{
    return FUN_80247b68(DAT_80436210, p0);
}
