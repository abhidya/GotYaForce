/* MUTANT (argument): stub_beta receives p instead of p+1. Same callees, same
 * order, same return shape — only one argument differs. Must go RED. */
extern int  stub_alpha(int a);
extern void stub_beta(int a, int b);
extern int  stub_gamma(int a);
#define BETA_CELL ((volatile int *)0x00104000u)

int fn_nowrite(int p) {
  int a = stub_alpha(p);
  stub_beta(p, a);             /* MUTATION: p, not p + 1 */
  int g = *BETA_CELL;
  int h = stub_gamma(a + g);
  return a + h;
}

void fn_vacuous(void) { }
