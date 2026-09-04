/* MATCHED  zz_02aa8d0_ @ 0x802aa8d0  (10 instructions)
 *
 *   802aa8d0  9421fff0  stwu r1, -0x10(r1)
 *   802aa8d4  7c0802a6  mflr r0
 *   802aa8d8  28030000  cmplwi r3, 0
 *   802aa8dc  90010014  stw r0, 0x14(r1)
 *   802aa8e0  41820008  beq 0x802aa8e8
 *   802aa8e4  4bfc25e9  bl 0x8026cecc
 *   802aa8e8  80010014  lwz r0, 0x14(r1)
 *   802aa8ec  7c0803a6  mtlr r0
 *   802aa8f0  38210010  addi r1, r1, 0x10
 *   802aa8f4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : stwu mflr cmplwi stw beq bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e65628756e25d20b3eb291f5ec34831aa9663da5e1da139730cad1a3947de3a5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_026cecc_(void);

void f(unsigned int p0)
{
    if (p0 != 0)
        zz_026cecc_();
}
