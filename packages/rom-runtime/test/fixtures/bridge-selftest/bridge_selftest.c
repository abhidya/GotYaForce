/* bridge_selftest.c — threads-target self-test module for the composed-module
 * execution runtime (packages/rom-runtime; design V4 H2 + V5 I2).
 *
 * Compiled with the repo's pinned emsdk (research/tools/emsdk) as a SHARED,
 * IMPORTED-memory module — the exact step-8/step-9 shape (see build.sh; flags
 * mirror research/decomp/oracle-harness/tests/fixtures/spine-synth). The
 * compiled .wasm is COMMITTED (like the spine-synth fixtures) so the smoke
 * phase runs on a clean checkout without the toolchain.
 *
 * The module's only import besides env.memory is the H3 miss handler:
 *     extern int __gf_dispatch_miss(unsigned int gc_addr, int argptr);
 * A miss IS a bridge call (docs/playable-port-design.md V4 H3): every extern
 * call below writes a uniform dispatch frame (frame ABI v1 — the struct
 * mirrors gf_dispatch_frame.h, emitted by OGhidra
 * src/port_dispatch_companion.py) and crosses the worker->main boundary
 * through the Atomics RPC bridge.
 *
 * Synthetic arena layout (16MB module memory; addresses match the ROM's
 * layout in SHAPE, not location — the real composed module maps original GC
 * addresses, and the adapters under test take their base addresses as
 * parameters precisely so this small fixture exercises identical logic):
 *   0x104000  i32   round-trip adapter's side-effect marker
 *   0x104010  i32   trace-delta adapter's recorded write cell
 *   0x104100  ..    damage target struct (fields at +0x1c4/+0x1c6/+0x1c8)
 *   0x104400  u8[2] borgNumber bytes (family, variant) for the lookup
 *   0x105000  ..    dispatch frames F(0)..F(9), 0x90 apiece
 *
 * Bridged callees (adapters registered by the self-test page):
 *   0xd0000001 rt_double        round-trips arg*2 + writes the marker cell
 *   0xd0000002 rt_reentrant     invokes reentry_target on the worker's stack
 *   0xd0000003 rt_overflow      re-invokes overflow_probe -> depth overflow
 *   0xd0000004 rt_async         returns a thenable -> declared error
 *   0xd0000005 rt_tracedelta    TraceDeltaAdapter (recorded write set)
 *   0xd0000006 rt_i64           i64 return -> r3 must be the HIGH word
 *   0xd0000007 rt_retclass      declared I32 but writes VOID -> ledger signal
 *   0x8003d344 zz_003d344_      REAL adapter: scaffold-backed apply-hp
 *   0x80066298 zz_0066298_      REAL adapter: scaffold-backed type lookup
 *   0xdeadbeef (none)           unserviced hit -> no_adapter error
 */

typedef unsigned int u32;

typedef union gf_slot {
  int i32;
  u32 u32v;
  long long i64;
  unsigned long long u64;
  float f32;
  double f64;
  unsigned char raw[8];
} gf_slot;

typedef struct gf_frame {
  u32 arg_count;   /* +0x00 */
  u32 ret_class;   /* +0x04 */
  gf_slot ret;     /* +0x08 */
  gf_slot args[16]; /* +0x10 */
} gf_frame;

_Static_assert(sizeof(gf_frame) == 0x90, "frame ABI v1: sizeof == 0x90");

extern int __gf_dispatch_miss(unsigned int gc_addr, int argptr);

#define FRAME_BASE 0x105000
static gf_frame *F(int i) { return (gf_frame *)(FRAME_BASE + i * 0x90); }

static void set_i32_arg(gf_frame *f, int index, int value) {
  f->args[index].i64 = 0; /* caller-extends: slot fully written */
  f->args[index].i32 = value;
}

/* 1. Round trip: value out through the bridge, doubled by the main-thread
 * adapter, plus the adapter's side-effect write into GC memory. */
int selftest_roundtrip(int x) {
  gf_frame *f = F(0);
  f->arg_count = 1;
  set_i32_arg(f, 0, x);
  int r = __gf_dispatch_miss(0xd0000001u, (int)F(0));
  int marker = *(volatile int *)0x104000; /* written by the adapter */
  return r + f->ret.i32 + marker;
}

/* 2. Reentrant: the adapter for 0xd0000002 invokes THIS export through the
 * dispatch loop while the worker is parked in the bridge call's wait. */
int reentry_target(int a, int b) { return a + b; }

int selftest_reentrant(int a, int b) {
  gf_frame *f = F(1);
  f->arg_count = 2;
  set_i32_arg(f, 0, a);
  set_i32_arg(f, 1, b);
  return __gf_dispatch_miss(0xd0000002u, (int)F(1));
}

/* 3. Nesting overflow: the adapter re-invokes this export with n+1, which
 * bridges again — unbounded mutual recursion the depth cap must refuse. */
int overflow_probe(int n) {
  gf_frame *f = F(2 + (n & 3));
  f->arg_count = 1;
  set_i32_arg(f, 0, n + 1);
  return __gf_dispatch_miss(0xd0000003u, (int)f);
}

/* 4. Async servicing violation: the adapter returns a thenable. */
int selftest_async(void) {
  gf_frame *f = F(6);
  f->arg_count = 0;
  return __gf_dispatch_miss(0xd0000004u, (int)F(6));
}

/* 5. Trace-delta adapter: two recorded calls; each applies its recorded
 * write set to 0x104010 and returns its recorded value. */
int selftest_tracedelta(void) {
  gf_frame *f = F(7);
  f->arg_count = 0;
  int r1 = __gf_dispatch_miss(0xd0000005u, (int)F(7));
  int c1 = *(volatile int *)0x104010;
  int r2 = __gf_dispatch_miss(0xd0000005u, (int)F(7));
  int c2 = *(volatile int *)0x104010;
  return r1 + r2 + c1 + c2;
}

/* 6. REAL adapter (scaffold-backed): zz_003d344_ apply-hp-damage. Builds the
 * target struct in GC memory, bridges, reads back the callee's write set
 * (+0x1c6 clamped HP, +0x1c8 pre-subtract mirror). */
int selftest_apply_hp(int hp, int maxHp, int amount) {
  volatile unsigned char *t = (volatile unsigned char *)0x104100;
  *(volatile unsigned short *)(t + 0x1c4) = (unsigned short)maxHp;
  *(volatile short *)(t + 0x1c6) = (short)hp;
  *(volatile short *)(t + 0x1c8) = 0;
  gf_frame *f = F(8);
  f->arg_count = 2;
  set_i32_arg(f, 0, 0x104100);
  set_i32_arg(f, 1, amount);
  __gf_dispatch_miss(0x8003d344u, (int)F(8));
  int clamped = *(volatile short *)(t + 0x1c6);
  int prev = *(volatile short *)(t + 0x1c8);
  return (prev << 16) | (clamped & 0xffff);
}

/* 7. REAL adapter (scaffold-backed): zz_0066298_ type-category lookup. The
 * borgNumber is stored big-endian BYTEWISE (family high byte first). */
int selftest_lookup_type(int family, int variant) {
  volatile unsigned char *p = (volatile unsigned char *)0x104400;
  p[0] = (unsigned char)family;
  p[1] = (unsigned char)variant;
  gf_frame *f = F(9);
  f->arg_count = 1;
  set_i32_arg(f, 0, 0x104400);
  return __gf_dispatch_miss(0x80066298u, (int)F(9));
}

/* 8. i64 return convention (companion review): the bridge result must be the
 * PPC r3 word — the HIGH word of the authoritative 8-byte ret slot — never
 * the thunk-style low word. Adapter writes 0x00000007_0000002a. */
int selftest_i64ret(void) {
  gf_frame *f = F(5);
  f->arg_count = 0;
  int r = __gf_dispatch_miss(0xd0000006u, (int)F(5));
  int lo = (int)(f->ret.i64 & 0xffffffffll);
  int hi = (int)(f->ret.i64 >> 32);
  return (r == hi && lo == 42 && hi == 7) ? 1 : 0;
}

/* 9. ret_class disagreement: adapter declared I32 but marshals VOID — the
 * call succeeds (result 0) and the ledger must carry the mismatch signal. */
int selftest_retclass(void) {
  gf_frame *f = F(4);
  f->arg_count = 0;
  return __gf_dispatch_miss(0xd0000007u, (int)F(4));
}

/* 10. Unserviced hit: no adapter registered — declared no_adapter error. */
int selftest_noadapter(void) {
  gf_frame *f = F(3);
  f->arg_count = 0;
  return __gf_dispatch_miss(0xdeadbeefu, (int)F(3));
}
