/* MATCHED  zz_0275b58_ @ 0x80275b58  (8 instructions)
 *
 *   80275b58  9421fff0  stwu r1, -0x10(r1)
 *   80275b5c  7c0802a6  mflr r0
 *   80275b60  90010014  stw r0, 0x14(r1)
 *   80275b64  48000c11  bl 0x80276774
 *   80275b68  80010014  lwz r0, 0x14(r1)
 *   80275b6c  7c0803a6  mtlr r0
 *   80275b70  38210010  addi r1, r1, 0x10
 *   80275b74  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2d772710b756493dac728995d29e18beb9f2cf93d5c3213a6eeb80fa0dbcc2a5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0276774_(void);

void f(void)
{
    zz_0276774_();
}
