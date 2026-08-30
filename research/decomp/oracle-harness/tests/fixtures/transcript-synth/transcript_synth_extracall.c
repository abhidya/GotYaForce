/* MUTANT (extra call): every captured call is emitted correctly and then one
 * MORE call is made. A returning function's capture is complete, so an extra
 * call is extra behaviour and must go RED — it must never be mistaken for the
 * spine standard's call-cap terminator. */
extern int  stub_alpha(int a);
extern void stub_beta(int a, int b);
extern int  stub_gamma(int a);
#define BETA_CELL ((volatile int *)0x00104000u)

int fn_nowrite(int p) {
  int a = stub_alpha(p);
  stub_beta(p + 1, a);
  int g = *BETA_CELL;
  int h = stub_gamma(a + g);
  stub_alpha(p);               /* MUTATION: one call too many */
  return a + h;
}

void fn_vacuous(void) { }
