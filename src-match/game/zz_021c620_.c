/* MATCHED  zz_021c620_ @ 0x8021c620  (3 instructions)
 *
 *   8021c620  38000000  li r0, 0
 *   8021c624  900db210  stw r0, -0x4df0(r13)
 *   8021c628  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : 2cf45d221577e238bddd4de37fa2e3531127322beeaf38a1281a35ec4e7a5b6a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804367b0;

void f(void)
{
    DAT_804367b0 = 0;
}
