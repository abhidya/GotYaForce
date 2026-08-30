/* MUTANT (return value): the call transcript is IDENTICAL and only the returned
 * value is off by one. This is the mutant boundary_green could not catch — it
 * is the whole reason transcript_green adds the return value to the claim. */
extern int  stub_alpha(int a);
extern void stub_beta(int a, int b);
extern int  stub_gamma(int a);
#define BETA_CELL ((volatile int *)0x00104000u)

int fn_nowrite(int p) {
  int a = stub_alpha(p);
  stub_beta(p + 1, a);
  int g = *BETA_CELL;
  int h = stub_gamma(a + g);
  return a + h + 1;            /* MUTATION */
}

void fn_vacuous(void) { }
