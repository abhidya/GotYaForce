/* MATCHED  zz_00e199c_ @ 0x800e199c  (3 instructions)
 *
 *   800e199c  38000000  li r0, 0
 *   800e19a0  98040000  stb r0, 0(r4)
 *   800e19a4  4e800020  blr
 *
 * The store goes through r4, so the FIRST argument is dead.  Under the EABI
 * that is what a C++ member function looks like when it ignores `this` -- the
 * same signal the spike recorded on zz_008bbc0_.  Modelled here as a C
 * function with an unused first parameter, which is byte-identical.
 * Iterations to match: 1.  exact_bytes: true.
 */

void f(int unused, char *p)
{
    *p = 0;
}
