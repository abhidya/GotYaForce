/* spine_synth_badorder.c — MUTANT of spine_synth.c for the boundary_green
 * self-test: stub_gamma is called where the capture expects stub_beta (the
 * beta/gamma pair is swapped). run-spine.mjs must FAIL on this module with a
 * report naming call index 1: expected stub_beta, got stub_gamma. */
extern int   stub_alpha(int a, int b);
extern void  stub_beta(int a);
extern float stub_gamma(float f);

#define SPINE_TICK ((volatile unsigned int *)0x00104000u)
#define BETA_CELL  ((volatile int *)0x00104004u)

void spine_main(void) {
  int acc = 7;
  do {
    acc = stub_alpha(acc, 3);
    *SPINE_TICK += 1;
    acc = (int)stub_gamma((float)acc);   /* MUTATION: gamma before beta */
    stub_beta(acc);
    acc = acc + *BETA_CELL;
  } while (1);
}
