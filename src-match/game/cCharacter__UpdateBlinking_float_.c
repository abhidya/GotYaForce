/* MATCHED  cCharacter::UpdateBlinking(float) @ 0x802aa124  (11 instructions)
 *
 *   802aa124  9421fff0  stwu r1, -0x10(r1)
 *   802aa128  7c0802a6  mflr r0
 *   802aa12c  90010014  stw r0, 0x14(r1)
 *   802aa130  8063004c  lwz r3, 0x4c(r3)
 *   802aa134  28030000  cmplwi r3, 0
 *   802aa138  41820008  beq 0x802aa140
 *   802aa13c  4bfcbad9  bl 0x80275c14
 *   802aa140  80010014  lwz r0, 0x14(r1)
 *   802aa144  7c0803a6  mtlr r0
 *   802aa148  38210010  addi r1, r1, 0x10
 *   802aa14c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : stwu mflr stw lwz cmplwi beq bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0694b7bb6d148a17beebd4855bbe12d7dc6cae8ea2d783bbf2e044587b5563e8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4c];
    unsigned int                  field_4c;
} S0;

extern int zz_0275c14_(int);

void f(S0 *p0)
{
    if (p0->field_4c != 0)
        zz_0275c14_(p0->field_4c);
}
