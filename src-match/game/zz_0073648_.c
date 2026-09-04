/* MATCHED  zz_0073648_ @ 0x80073648  (8 instructions)
 *
 *   80073648  9421fff0  stwu r1, -0x10(r1)
 *   8007364c  7c0802a6  mflr r0
 *   80073650  90010014  stw r0, 0x14(r1)
 *   80073654  48000015  bl 0x80073668
 *   80073658  80010014  lwz r0, 0x14(r1)
 *   8007365c  7c0803a6  mtlr r0
 *   80073660  38210010  addi r1, r1, 0x10
 *   80073664  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 059a621e12ae6209be6acc822bdcdc83eb34871e6f02f8af10192327896e9101
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0073668_(void);

void f(void)
{
    zz_0073668_();
}
