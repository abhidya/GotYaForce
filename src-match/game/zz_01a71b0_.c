/* MATCHED  zz_01a71b0_ @ 0x801a71b0  (22 instructions)
 *
 *   801a71b0  9421fff0  stwu r1, -0x10(r1)
 *   801a71b4  7c0802a6  mflr r0
 *   801a71b8  90010014  stw r0, 0x14(r1)
 *   801a71bc  4bfff519  bl 0x801a66d4
 *   801a71c0  48000049  bl 0x801a7208
 *   801a71c4  480006a5  bl 0x801a7868
 *   801a71c8  48000e91  bl 0x801a8058
 *   801a71cc  4800133d  bl 0x801a8508
 *   801a71d0  4800c855  bl 0x801b3a24
 *   801a71d4  48021c59  bl 0x801c8e2c
 *   801a71d8  48006aa1  bl 0x801adc78
 *   801a71dc  48001b45  bl 0x801a8d20
 *   801a71e0  480016a1  bl 0x801a8880
 *   801a71e4  48002789  bl 0x801a996c
 *   801a71e8  48002155  bl 0x801a933c
 *   801a71ec  480050e1  bl 0x801ac2cc
 *   801a71f0  4803b2f1  bl 0x801e24e0
 *   801a71f4  480001e1  bl 0x801a73d4
 *   801a71f8  80010014  lwz r0, 0x14(r1)
 *   801a71fc  7c0803a6  mtlr r0
 *   801a7200  38210010  addi r1, r1, 0x10
 *   801a7204  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl bl bl bl bl bl bl bl bl bl bl bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4cb5517caa421c50733e62d9a8d9ac17c75e857b7265ff3a30dbbeac1b0f5b37
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01a66d4_(void);
extern int zz_01a7208_(void);
extern int zz_01a73d4_(void);
extern int zz_01a7868_(void);
extern int zz_01a8058_(void);
extern int zz_01a8508_(void);
extern int zz_01a8880_(void);
extern int zz_01a8d20_(void);
extern int zz_01a933c_(void);
extern int zz_01a996c_(void);
extern int zz_01ac2cc_(void);
extern int zz_01adc78_(void);
extern int zz_01b3a24_(void);
extern int zz_01c8e2c_(void);
extern int zz_01e24e0_(void);

int f(void)
{
    zz_01a66d4_();
    zz_01a7208_();
    zz_01a7868_();
    zz_01a8058_();
    zz_01a8508_();
    zz_01b3a24_();
    zz_01c8e2c_();
    zz_01adc78_();
    zz_01a8d20_();
    zz_01a8880_();
    zz_01a996c_();
    zz_01a933c_();
    zz_01ac2cc_();
    zz_01e24e0_();
    return zz_01a73d4_();
}
