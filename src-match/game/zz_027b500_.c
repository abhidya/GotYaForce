/* MATCHED  zz_027b500_ @ 0x8027b500  (2 instructions)
 *
 *   8027b500  38600011  li r3, 0x11
 *   8027b504  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li blr
 *   exact_bytes      : true
 *   source sha256    : 10cd14324f44bcce4996bf57701a4b447cb09e835c7851433f7a4a392e62fbc3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(void)
{
    return 0x11;
}
