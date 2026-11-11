/* MATCHED  zz_0269590_ @ 0x80269590  (17 instructions)
 *
 *   80269590  9421fff0  stwu r1, -0x10(r1)
 *   80269594  7c0802a6  mflr r0
 *   80269598  90010014  stw r0, 0x14(r1)
 *   8026959c  93e1000c  stw r31, 0xc(r1)
 *   802695a0  7c7f1b79  or. r31, r3, r3
 *   802695a4  4182001c  beq 0x802695c0
 *   802695a8  48000065  bl 0x8026960c
 *   802695ac  7fe3fb78  mr r3, r31
 *   802695b0  38800000  li r4, 0
 *   802695b4  38a00030  li r5, 0x30
 *   802695b8  4bd9be55  bl 0x8000540c
 *   802695bc  48000019  bl 0x802695d4
 *   802695c0  80010014  lwz r0, 0x14(r1)
 *   802695c4  83e1000c  lwz r31, 0xc(r1)
 *   802695c8  7c0803a6  mtlr r0
 *   802695cc  38210010  addi r1, r1, 0x10
 *   802695d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (3 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 3
 *   shape            : stwu mflr stw stw or. beq bl mr li li bl bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0510cb59afea04d95286351da9db0d33382d003a6dc7a28aa51e82844bcfd551
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_8000540c(int, int, int);
extern int zz_02695d4_(void);
extern int zz_026960c_(void);

void f(void * p0)
{
    if (p0 != 0)
    {
        zz_026960c_();
        FUN_8000540c(p0, 0, 0x30);
        zz_02695d4_();
    }
}
