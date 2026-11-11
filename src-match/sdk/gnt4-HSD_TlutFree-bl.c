/* MATCHED  gnt4-HSD_TlutFree-bl @ 0x80240cf4  (11 instructions)
 *
 *   80240cf4  9421fff0  stwu r1, -0x10(r1)
 *   80240cf8  7c0802a6  mflr r0
 *   80240cfc  28030000  cmplwi r3, 0
 *   80240d00  90010014  stw r0, 0x14(r1)
 *   80240d04  4182000c  beq 0x80240d10
 *   80240d08  38800010  li r4, 0x10
 *   80240d0c  4801c18d  bl 0x8025ce98
 *   80240d10  80010014  lwz r0, 0x14(r1)
 *   80240d14  7c0803a6  mtlr r0
 *   80240d18  38210010  addi r1, r1, 0x10
 *   80240d1c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : stwu mflr cmplwi stw beq li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5439a7fed1c355b57d4222cc5192e4963013622e0a99db7c70c8e07a0f423cc0
 *
 * Source refined after generation: explicit pointer argument flow.
 * Retail evidence: hsdFreeMemPiece copies r3 to r31; 0x8025cec8 stores through r31.
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_8025ce98(void *, int);

void f(void *p0)
{
    if (p0 != 0)
        FUN_8025ce98(p0, 0x10);
}
