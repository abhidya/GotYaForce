/* MATCHED  gnt4-OSSetArenaHi-bl @ 0x80200320  (2 instructions)
 *
 *   80200320  906dae78  stw r3, -0x5188(r13)
 *   80200324  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : 43770b2ad60f47bba72d8d4b21423ea534086c534c1c285a024690312067a04f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436418;

void f(int p0)
{
    DAT_80436418 = p0;
}
