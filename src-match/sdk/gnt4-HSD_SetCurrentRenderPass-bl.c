/* MATCHED  gnt4-HSD_SetCurrentRenderPass-bl @ 0x802541c4  (2 instructions)
 *
 *   802541c4  806db440  lwz r3, -0x4bc0(r13)
 *   802541c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 321b400af688ffb854d278e1b679bbb705a1dbbd02377007a86dd9860923be4d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804369e0;

int f(void)
{
    return DAT_804369e0;
}
