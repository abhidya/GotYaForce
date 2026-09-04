/* MATCHED  zz_008c098_ @ 0x8008c098  (7 instructions)
 *
 *   8008c098  38000000  li r0, 0
 *   8008c09c  900dac3c  stw r0, -0x53c4(r13)
 *   8008c0a0  900dac40  stw r0, -0x53c0(r13)
 *   8008c0a4  900dac34  stw r0, -0x53cc(r13)
 *   8008c0a8  900dac44  stw r0, -0x53bc(r13)
 *   8008c0ac  900dac30  stw r0, -0x53d0(r13)
 *   8008c0b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 3cf1b89669f61d764bfb67ad80be0a6b3eeb8ae3644ef8d860601a20e217062a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361d0;
extern int DAT_804361d4;
extern int DAT_804361dc;
extern int DAT_804361e0;
extern int DAT_804361e4;

void f(void)
{
    DAT_804361dc = 0;
    DAT_804361e0 = 0;
    DAT_804361d4 = 0;
    DAT_804361e4 = 0;
    DAT_804361d0 = 0;
}
