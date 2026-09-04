/* MATCHED  zz_0007f38_ @ 0x80007f38  (9 instructions)
 *
 *   80007f38  9421fff0  stwu r1, -0x10(r1)
 *   80007f3c  7c0802a6  mflr r0
 *   80007f40  90010014  stw r0, 0x14(r1)
 *   80007f44  8063000c  lwz r3, 0xc(r3)
 *   80007f48  48001651  bl 0x80009598
 *   80007f4c  80010014  lwz r0, 0x14(r1)
 *   80007f50  7c0803a6  mtlr r0
 *   80007f54  38210010  addi r1, r1, 0x10
 *   80007f58  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 22ea8200a77ed7763e95730d264a9ed84d225dc7dd7ee2da6c22e28150939cb9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_0009598_(int);

int f(S0 *p0)
{
    return zz_0009598_(p0->field_c);
}
