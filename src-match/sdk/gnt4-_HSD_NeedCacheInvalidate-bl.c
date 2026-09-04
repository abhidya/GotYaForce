/* MATCHED  gnt4-_HSD_NeedCacheInvalidate-bl @ 0x80254278  (4 instructions)
 *
 *   80254278  800db43c  lwz r0, -0x4bc4(r13)
 *   8025427c  7c001b78  or r0, r0, r3
 *   80254280  900db43c  stw r0, -0x4bc4(r13)
 *   80254284  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz or stw blr
 *   exact_bytes      : false
 *   source sha256    : 26e712cdc9fa86638f0a78d83ae4a0a1af33435b0cdef28c1c997a0fb7684954
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804369dc;

void f(int p0)
{
    DAT_804369dc = DAT_804369dc | p0;
}
