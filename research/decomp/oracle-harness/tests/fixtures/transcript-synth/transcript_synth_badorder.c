/* MUTANT (call order): stub_gamma is called BEFORE stub_beta. Must make
 * run-transcript.mjs go RED naming the first divergent call. */
extern int  stub_alpha(int a);
extern void stub_beta(int a, int b);
extern int  stub_gamma(int a);
#define BETA_CELL ((volatile int *)0x00104000u)

int fn_nowrite(int p) {
  int a = stub_alpha(p);
  int h = stub_gamma(a);       /* MUTATION: out of order */
  stub_beta(p + 1, a);
  return a + h;
}

void fn_vacuous(void) { }
