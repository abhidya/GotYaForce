/* MATCHED  zz_0217dc4_ @ 0x80217dc4  (5 instructions)
 *
 *   80217dc4  800db160  lwz r0, -0x4ea0(r13)
 *   80217dc8  7c001840  cmplw r0, r3
 *   80217dcc  4d820020  beqlr
 *   80217dd0  906db160  stw r3, -0x4ea0(r13)
 *   80217dd4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : lwz cmplw beqlr stw blr
 *   exact_bytes      : false
 *   source sha256    : 13d3f42b6e830a2b69f4d5d4b70d0d7b09a9d3aec0f733fc261dc9e70407bb33
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436700;

void f(unsigned int p0)
{
    if (DAT_80436700 == p0)
        return;
    DAT_80436700 = p0;
}
