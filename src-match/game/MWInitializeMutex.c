/* MATCHED  MWInitializeMutex @ 0x802a0be8  (4 instructions)
 *
 *   802a0be8  38000003  li r0, 3
 *   802a0bec  9003004c  stw r0, 0x4c(r3)
 *   802a0bf0  38600000  li r3, 0
 *   802a0bf4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw li blr
 *   exact_bytes      : true
 *   source sha256    : da56dda86d6b876282def1e74c078e3b3df31dce9d16bf1fbf545c5a3ebd68c6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4c];
    int            field_4c;
} S0;

int f(S0 *p0)
{
    p0->field_4c = 3;
    return 0;
}
