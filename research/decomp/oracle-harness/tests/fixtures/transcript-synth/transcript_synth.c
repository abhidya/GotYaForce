/* transcript_synth.c — synthetic NO-WRITE returning function for the
 * transcript_green harness self-test (run-transcript.mjs).
 *
 * Shape mirrors the population the standard exists for: `fn_nowrite` performs
 * NOT ONE MEMORY WRITE, so oracle_green (run-unit.mjs) has literally nothing to
 * compare on it. Its entire observable behaviour is
 *   (a) the sequence of out-of-unit calls, with their arguments,
 *   (b) its return value,
 *   (c) the memory it READS — here BETA_CELL, whose value arrives only via a
 *       callee's captured delta, so a runner that failed to apply that delta
 *       would produce a wrong gamma argument and a wrong return value.
 * That last point is why the fixture reads a delta-written cell: it proves the
 * "reads are constrained through the arguments and the return value" claim
 * concretely rather than by assertion.
 *
 * `fn_vacuous` observes nothing at all — no calls, no return value, no writes.
 * It exists so the self-test can prove the NON-VACUITY GUARD: a capture of it
 * must FAIL rather than hand out a free green.
 *
 * No Dolphin capture is involved; the paired transcript-synth.capture.jsonl is
 * hand-authored from this source, exactly as spine_synth.c / the boundary_green
 * self-test do. Real Dolphin captures (capture_transcript.py) plug into the
 * same transcript_schema 1.
 *
 * Callees (all out-of-unit, resolved as env imports by the harness stubs):
 *   stub_alpha(i32)->i32       pure boundary value
 *   stub_beta(i32,i32)->void   side effect: its captured delta writes BETA_CELL
 *   stub_gamma(i32)->i32       consumes a value derived from that delta
 */
extern int  stub_alpha(int a);
extern void stub_beta(int a, int b);
extern int  stub_gamma(int a);

/* Absolute-address style matches the port units: the cell lives at a fixed
 * arena address, not a C global, so the capture can name it without reading the
 * compiled binary's layout. Written ONLY by stub_beta's captured delta. */
#define BETA_CELL ((volatile int *)0x00104000u)

int fn_nowrite(int p) {
  int a = stub_alpha(p);
  stub_beta(p + 1, a);
  int g = *BETA_CELL;          /* read of a cell the callee delta wrote */
  int h = stub_gamma(a + g);
  return a + h;
}

void fn_vacuous(void) { }
