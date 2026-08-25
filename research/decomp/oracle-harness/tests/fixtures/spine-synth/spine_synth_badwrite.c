/* spine_synth_badwrite.c — MUTANT of spine_synth.c for the boundary_green
 * self-test: the spine-owned write increments by 2 instead of 1. The call
 * sequence and args are IDENTICAL to the correct module; only the owned
 * bytes diverge. run-spine.mjs must FAIL on this module with a report naming
 * the first boundary whose owned-region bytes mismatch (call index 3,
 * address 0x104000: expected 01, got 02). */
extern int   stub_alpha(int a, int b);
extern void  stub_beta(int a);
extern float stub_gamma(float f);

#define SPINE_TICK ((volatile unsigned int *)0x00104000u)
#define BETA_CELL  ((volatile int *)0x00104004u)

void spine_main(void) {
  int acc = 7;
  do {
    acc = stub_alpha(acc, 3);
    *SPINE_TICK += 2;              /* MUTATION: wrong spine-owned write */
    stub_beta(acc);
    acc = acc + *BETA_CELL;
    acc = (int)stub_gamma((float)acc);
  } while (1);
}
