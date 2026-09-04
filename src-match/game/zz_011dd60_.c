/* MATCHED  zz_011dd60_ @ 0x8011dd60  (10 instructions)
 *
 *   8011dd60  9421fff0  stwu r1, -0x10(r1)
 *   8011dd64  7c0802a6  mflr r0
 *   8011dd68  38800045  li r4, 0x45
 *   8011dd6c  90010014  stw r0, 0x14(r1)
 *   8011dd70  806300e0  lwz r3, 0xe0(r3)
 *   8011dd74  4beeba41  bl 0x800097b4
 *   8011dd78  80010014  lwz r0, 0x14(r1)
 *   8011dd7c  7c0803a6  mtlr r0
 *   8011dd80  38210010  addi r1, r1, 0x10
 *   8011dd84  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 624daa598740136298558939fb3273d846e28b1ba91f2819903706c53e7796a9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xe0];
    int                  field_e0;
} S0;

extern int zz_00097b4_(int, int);

int f(S0 *p0)
{
    return zz_00097b4_(p0->field_e0, 0x45);
}
