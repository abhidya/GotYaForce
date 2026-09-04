/* MATCHED  zz_01634e4_ @ 0x801634e4  (13 instructions)
 *
 *   801634e4  a8830074  lha r4, 0x74(r3)
 *   801634e8  a8030146  lha r0, 0x146(r3)
 *   801634ec  7c040214  add r0, r4, r0
 *   801634f0  b0030074  sth r0, 0x74(r3)
 *   801634f4  a8830146  lha r4, 0x146(r3)
 *   801634f8  380400b0  addi r0, r4, 0xb0
 *   801634fc  b0030146  sth r0, 0x146(r3)
 *   80163500  a8030146  lha r0, 0x146(r3)
 *   80163504  2c000c00  cmpwi r0, 0xc00
 *   80163508  4c810020  blelr
 *   8016350c  38000c00  li r0, 0xc00
 *   80163510  b0030146  sth r0, 0x146(r3)
 *   80163514  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha lha add sth lha addi sth lha cmpwi blelr li sth blr
 *   exact_bytes      : true
 *   source sha256    : cff1605586e9955b8ffb05c3316c4609ab556cb30e10d1d714add2ca5f2232ff
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x74];
    short                field_74;
    char pad_76[0xd0];
    short                field_146;
} S0;

void f(S0 *p0)
{
    p0->field_74 = p0->field_74 + p0->field_146;
    p0->field_146 = p0->field_146 + 0xb0;
    if (p0->field_146 <= 0xc00)
        return;
    p0->field_146 = 0xc00;
}
