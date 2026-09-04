/* MATCHED  gnt4-_HSD_StateInvalidateTexCoordGen @ 0x80242298  (3 instructions)
 *
 *   80242298  38000000  li r0, 0
 *   8024229c  900db358  stw r0, -0x4ca8(r13)
 *   802422a0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : bb02fbaff76155433adc4743e6bda05a392fdde2a0746937a24470cd83eceb88
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368f8;

void f(void)
{
    DAT_804368f8 = 0;
}
