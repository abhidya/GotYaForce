/* MATCHED  zz_0041288_ @ 0x80041288  (15 instructions)
 *
 *   80041288  9421fff0  stwu r1, -0x10(r1)
 *   8004128c  7c0802a6  mflr r0
 *   80041290  90010014  stw r0, 0x14(r1)
 *   80041294  93e1000c  stw r31, 0xc(r1)
 *   80041298  3be00000  li r31, 0
 *   8004129c  7fe3fb78  mr r3, r31
 *   800412a0  4bfffe1d  bl 0x800410bc
 *   800412a4  3bff0001  addi r31, r31, 1
 *   800412a8  2c1f0006  cmpwi r31, 6
 *   800412ac  4180fff0  blt 0x8004129c
 *   800412b0  80010014  lwz r0, 0x14(r1)
 *   800412b4  83e1000c  lwz r31, 0xc(r1)
 *   800412b8  7c0803a6  mtlr r0
 *   800412bc  38210010  addi r1, r1, 0x10
 *   800412c0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/counted-call (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw li mr bl addi cmpwi blt lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2cc10293ee6e8ddd245fc4374e105bb17a605c2579beca9b6580450a1028a46a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00410bc_(int);

void f(void)
{
    int i = 0;
    do {
        zz_00410bc_(i);
        i += 1;
    } while (i < 6);
}
