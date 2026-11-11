/* MATCHED  zz_02af490_ @ 0x802af490  (18 instructions)
 *
 *   802af490  9421fff0  stwu r1, -0x10(r1)
 *   802af494  7c0802a6  mflr r0
 *   802af498  90010014  stw r0, 0x14(r1)
 *   802af49c  93e1000c  stw r31, 0xc(r1)
 *   802af4a0  7c9f2378  mr r31, r4
 *   802af4a4  93c10008  stw r30, 8(r1)
 *   802af4a8  7c7e1b78  mr r30, r3
 *   802af4ac  80630044  lwz r3, 0x44(r3)
 *   802af4b0  4bffb421  bl 0x802aa8d0
 *   802af4b4  7fc3f378  mr r3, r30
 *   802af4b8  7fe4fb78  mr r4, r31
 *   802af4bc  4bffac69  bl 0x802aa124
 *   802af4c0  80010014  lwz r0, 0x14(r1)
 *   802af4c4  83e1000c  lwz r31, 0xc(r1)
 *   802af4c8  83c10008  lwz r30, 8(r1)
 *   802af4cc  7c0803a6  mtlr r0
 *   802af4d0  38210010  addi r1, r1, 0x10
 *   802af4d4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr stw mr lwz bl mr mr bl lwz lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 73975d87c5d2a7980419ada7f23728eba2155530483cde6d4f8c4926bf9ff152
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x44];
    int                  field_44;
} S0;

extern int FUN_802aa124(int, int);
extern int zz_02aa8d0_(int);

int f(S0 *p0, int p1)
{
    zz_02aa8d0_(p0->field_44);
    return FUN_802aa124(p0, p1);
}
