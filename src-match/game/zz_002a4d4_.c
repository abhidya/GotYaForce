/* MATCHED  zz_002a4d4_ @ 0x8002a4d4  (18 instructions)
 *
 *   8002a4d4  9421fff0  stwu r1, -0x10(r1)
 *   8002a4d8  7c0802a6  mflr r0
 *   8002a4dc  3860ffff  li r3, -1
 *   8002a4e0  90010014  stw r0, 0x14(r1)
 *   8002a4e4  48217379  bl 0x8024185c
 *   8002a4e8  48229d85  bl 0x8025426c
 *   8002a4ec  38600000  li r3, 0
 *   8002a4f0  4822a559  bl 0x80254a48
 *   8002a4f4  4822a6d1  bl 0x80254bc4
 *   8002a4f8  481e6bd9  bl 0x802110d0
 *   8002a4fc  800dac24  lwz r0, -0x53dc(r13)
 *   8002a500  2c000000  cmpwi r0, 0
 *   8002a504  41820008  beq 0x8002a50c
 *   8002a508  48246d1d  bl 0x80271224
 *   8002a50c  80010014  lwz r0, 0x14(r1)
 *   8002a510  7c0803a6  mtlr r0
 *   8002a514  38210010  addi r1, r1, 0x10
 *   8002a518  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl bl li bl bl bl lwz cmpwi beq bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2927dc953488c1c4bbf64c271ac6e755ed75f6e3eb5ffc0afe386ae8bdcff74a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361c4;

extern int FUN_802110d0(void);
extern int FUN_8024185c(int);
extern int FUN_80254a48(int);
extern int FUN_80254bc4(void);
extern int zz_025426c_(void);
extern int zz_0271224_(void);

void f(void)
{
    FUN_8024185c(-1);
    zz_025426c_();
    FUN_80254a48(0);
    FUN_80254bc4();
    FUN_802110d0();
    if (DAT_804361c4 != 0)
        zz_0271224_();
}
