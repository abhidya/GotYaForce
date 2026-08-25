/* spine_synth.c — synthetic nonterminating spine for the boundary_green harness
 * self-test (design v5 I3, step-8 subtask). Shape mirrors run_main_game_loop
 * (chunk_0006.c:5790-5833): a do/while(true) whose body is out-of-unit calls
 * plus exactly one spine-owned memory write. No Dolphin capture is involved —
 * the paired capture file (spine-synth.capture.jsonl) is hand-authored from
 * this source, which is the point: it proves the HARNESS SHAPE (call-order
 * assert, delta application, owned-write byte compare, K-iteration cut), and
 * real Dolphin captures plug into the same schema later.
 *
 * Absolute-address style matches the port units: spine-owned state lives at a
 * fixed arena address, not a C global, so the capture can name addresses
 * without reading the compiled binary's layout.
 *
 * Callees (all out-of-unit, resolved as env imports by the harness stubs):
 *   stub_alpha(i32,i32)->i32   pure boundary value
 *   stub_beta(i32)->void       side effect: its captured delta writes BETA_CELL,
 *                              which the spine then CONSUMES — proving the
 *                              runner really applied the callee delta
 *   stub_gamma(f32)->f32       float boundary value
 */
extern int   stub_alpha(int a, int b);
extern void  stub_beta(int a);
extern float stub_gamma(float f);

#define SPINE_TICK ((volatile unsigned int *)0x00104000u) /* the one spine-owned write */
#define BETA_CELL  ((volatile int *)0x00104004u)          /* written only by stub_beta's delta */

void spine_main(void) {
  int acc = 7;
  do {
    acc = stub_alpha(acc, 3);
    *SPINE_TICK += 1;              /* spine-owned write, once per iteration */
    stub_beta(acc);
    acc = acc + *BETA_CELL;        /* consumes the delta the stub applied */
    acc = (int)stub_gamma((float)acc);
  } while (1);
}
