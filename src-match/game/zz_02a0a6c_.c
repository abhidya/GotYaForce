/* MATCHED  zz_02a0a6c_ @ 0x802a0a6c  (5 instructions)
 *
 *   802a0a6c  28030000  cmplwi r3, 0
 *   802a0a70  4d820020  beqlr
 *   802a0a74  38000004  li r0, 4
 *   802a0a78  90030000  stw r0, 0(r3)
 *   802a0a7c  4e800020  blr
 *
 * CONTROL FLOW.  A null guard that Metrowerks compiles into a conditional
 * return (`beqlr`) rather than a forward branch -- the shape the spike's
 * census counts 4 instances of.  `cmplwi` (unsigned) says the compare is
 * against a pointer.  Iterations to match: 1.  exact_bytes: true.
 */

typedef struct S {
    int state;
} S;

void f(S *s)
{
    if (s == 0)
        return;
    s->state = 4;
}
