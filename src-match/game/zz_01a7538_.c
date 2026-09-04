/* MATCHED  zz_01a7538_ @ 0x801a7538  (10 instructions)
 *
 *   801a7538  9421fff0  stwu r1, -0x10(r1)
 *   801a753c  7c0802a6  mflr r0
 *   801a7540  38a00001  li r5, 1
 *   801a7544  38c0000b  li r6, 0xb
 *   801a7548  90010014  stw r0, 0x14(r1)
 *   801a754c  48000015  bl 0x801a7560
 *   801a7550  80010014  lwz r0, 0x14(r1)
 *   801a7554  7c0803a6  mtlr r0
 *   801a7558  38210010  addi r1, r1, 0x10
 *   801a755c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c8032b51cd45a5ed926af75399da9e2bd4e6ff56552d30e28dba008436120693
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01a7560_(int, int, int, int);

void f(int p0, int p1)
{
    zz_01a7560_(p0, p1, 1, 0xb);
}
