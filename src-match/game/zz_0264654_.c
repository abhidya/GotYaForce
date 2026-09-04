/* MATCHED  zz_0264654_ @ 0x80264654  (9 instructions)
 *
 *   80264654  9421fff0  stwu r1, -0x10(r1)
 *   80264658  7c0802a6  mflr r0
 *   8026465c  90010014  stw r0, 0x14(r1)
 *   80264660  80630004  lwz r3, 4(r3)
 *   80264664  48003d0d  bl 0x80268370
 *   80264668  80010014  lwz r0, 0x14(r1)
 *   8026466c  7c0803a6  mtlr r0
 *   80264670  38210010  addi r1, r1, 0x10
 *   80264674  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1b6725ff3662d04d06539b8259136c25b6332cedbb9e40cc21b893fe095f2fdb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_0268370_(int);

int f(S0 *p0)
{
    return zz_0268370_(p0->field_4);
}
