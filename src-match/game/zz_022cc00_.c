/* MATCHED  zz_022cc00_ @ 0x8022cc00  (9 instructions)
 *
 *   8022cc00  9421fff0  stwu r1, -0x10(r1)
 *   8022cc04  7c0802a6  mflr r0
 *   8022cc08  90010014  stw r0, 0x14(r1)
 *   8022cc0c  80630008  lwz r3, 8(r3)
 *   8022cc10  48000a65  bl 0x8022d674
 *   8022cc14  80010014  lwz r0, 0x14(r1)
 *   8022cc18  7c0803a6  mtlr r0
 *   8022cc1c  38210010  addi r1, r1, 0x10
 *   8022cc20  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 66a4ad478e65585408a01cb0d622b29d1ed398a35d0bc293b2d48af0380f9a7e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int                  field_8;
} S0;

extern int TRKReleaseBuffer(int);

int f(S0 *p0)
{
    return TRKReleaseBuffer(p0->field_8);
}
