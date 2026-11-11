/* MATCHED  zz_01ca918_ @ 0x801ca918  (12 instructions)
 *
 *   801ca918  9421fff0  stwu r1, -0x10(r1)
 *   801ca91c  7c0802a6  mflr r0
 *   801ca920  28030000  cmplwi r3, 0
 *   801ca924  90010014  stw r0, 0x14(r1)
 *   801ca928  41820010  beq 0x801ca938
 *   801ca92c  38800000  li r4, 0
 *   801ca930  38a00258  li r5, 0x258
 *   801ca934  4be3aad9  bl 0x8000540c
 *   801ca938  80010014  lwz r0, 0x14(r1)
 *   801ca93c  7c0803a6  mtlr r0
 *   801ca940  38210010  addi r1, r1, 0x10
 *   801ca944  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : stwu mflr cmplwi stw beq li li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ee49663ce6f36da44369efefa7a7a2b1007805c01ccddf454db4bfcef4a5fd2c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_8000540c(int, int, int);

void f(unsigned int p0)
{
    if (p0 != 0)
        FUN_8000540c(p0, 0, 0x258);
}
