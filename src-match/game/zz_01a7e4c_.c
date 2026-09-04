/* MATCHED  zz_01a7e4c_ @ 0x801a7e4c  (12 instructions)
 *
 *   801a7e4c  9421fff0  stwu r1, -0x10(r1)
 *   801a7e50  7c0802a6  mflr r0
 *   801a7e54  90010014  stw r0, 0x14(r1)
 *   801a7e58  88030011  lbz r0, 0x11(r3)
 *   801a7e5c  7c000774  extsb r0, r0
 *   801a7e60  2c00000e  cmpwi r0, 0xe
 *   801a7e64  40800008  bge 0x801a7e6c
 *   801a7e68  4bfff981  bl 0x801a77e8
 *   801a7e6c  80010014  lwz r0, 0x14(r1)
 *   801a7e70  7c0803a6  mtlr r0
 *   801a7e74  38210010  addi r1, r1, 0x10
 *   801a7e78  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lbz extsb cmpwi bge bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ec18c7b7257274e76cd70409b2e35694e34974d4500f2ec54485913948d32873
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x11];
    char                 field_11;
} S0;

extern int zz_01a77e8_(void);

void f(S0 *p0)
{
    if (p0->field_11 < 0xe)
        zz_01a77e8_();
}
