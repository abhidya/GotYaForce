/* MATCHED  zz_0218954_ @ 0x80218954  (11 instructions)
 *
 *   80218954  38000000  li r0, 0
 *   80218958  900db1c0  stw r0, -0x4e40(r13)
 *   8021895c  900db1bc  stw r0, -0x4e44(r13)
 *   80218960  900db1b8  stw r0, -0x4e48(r13)
 *   80218964  900db1b4  stw r0, -0x4e4c(r13)
 *   80218968  900db1b0  stw r0, -0x4e50(r13)
 *   8021896c  900db1ac  stw r0, -0x4e54(r13)
 *   80218970  900db1a8  stw r0, -0x4e58(r13)
 *   80218974  900db1a4  stw r0, -0x4e5c(r13)
 *   80218978  900db1a0  stw r0, -0x4e60(r13)
 *   8021897c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw stw stw stw stw stw stw blr
 *   exact_bytes      : false
 *   source sha256    : bb1cf711e0b8784ffbb0351b8727f7525f6993bf247bd13ac9843d8cb75e3a9c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436740;
extern int DAT_80436744;
extern int DAT_80436748;
extern int DAT_8043674c;
extern int DAT_80436750;
extern int DAT_80436754;
extern int DAT_80436758;
extern int DAT_8043675c;
extern int DAT_80436760;

void f(void)
{
    DAT_80436760 = 0;
    DAT_8043675c = 0;
    DAT_80436758 = 0;
    DAT_80436754 = 0;
    DAT_80436750 = 0;
    DAT_8043674c = 0;
    DAT_80436748 = 0;
    DAT_80436744 = 0;
    DAT_80436740 = 0;
}
