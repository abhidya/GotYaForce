/* MATCHED  gnt4-GXGetGPFifo-bl @ 0x8022588c  (2 instructions)
 *
 *   8022588c  806db26c  lwz r3, -0x4d94(r13)
 *   80225890  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 4687038ef6f22fa1625622edb24a9b8ae807e7ab94dc16956b08864391dfa16c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043680c;

int f(void)
{
    return DAT_8043680c;
}
