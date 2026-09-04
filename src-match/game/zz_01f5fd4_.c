/* MATCHED  zz_01f5fd4_ @ 0x801f5fd4  (10 instructions)
 *
 *   801f5fd4  9421fff0  stwu r1, -0x10(r1)
 *   801f5fd8  7c0802a6  mflr r0
 *   801f5fdc  38600038  li r3, 0x38
 *   801f5fe0  90010014  stw r0, 0x14(r1)
 *   801f5fe4  4be938b5  bl 0x80089898
 *   801f5fe8  4be93671  bl 0x80089658
 *   801f5fec  80010014  lwz r0, 0x14(r1)
 *   801f5ff0  7c0803a6  mtlr r0
 *   801f5ff4  38210010  addi r1, r1, 0x10
 *   801f5ff8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 67d10c5791c0c42e54964a534bc028300fc6912d43560b53f0615af7da44e38d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089658_(void);
extern int zz_0089898_(int);

int f(void)
{
    zz_0089898_(0x38);
    return zz_0089658_();
}
