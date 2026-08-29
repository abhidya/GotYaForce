# Composed-module dispatch pilot

The first time a REAL assembly-gate composed module runs inside the actual
GotYaForce browser game. It connects three things that were each proven alone
and had never met: the composition ladder's rung-0 link (docs/composition-ladder.md),
the `@gf/rom-runtime` host bridge (design V4 H2, V5 I1/I2), and the shipped
game under cross-origin isolation (V4 H1).

**Name it precisely.** This gate is the **composed-module dispatch pilot**. It
is *not* control inversion, and no artifact here may be cited as such.

## What it is, and what it is not

Design V4 H2 gate (b) — control inversion — requires **the composed module to
drive N frames** with the TS engine passive, and gate (a) requires
`run_main_game_loop` (`0x800527d8`) to be `boundary_green` and **linked into the
window** first. Rung 0 is five units; the ROM's loop is not one of them and has
no execution model in this module at all.

The pilot drives the *inverse* of control inversion and says so: **the host
calls into the composed module once per rendered game frame, and every call the
module makes back out of its window crosses the declared H2 bridge.**

| Design requirement | Pilot status |
| --- | --- |
| Composed module instantiated in the browser with shared memory + DOL arena at GC addresses | **met** |
| Live dispatch table resolves a GC address and runs the ROM's own compiled code | **met** (40-thunk table, `__gf_dispatch`) |
| Table MISS routed through `__gf_dispatch_miss` to a bridged host adapter (H3: a miss is a bridge call, never a trap) | **met** |
| DIRECT call from linked code to an unlinked callee routed through the bridge | **met** (per-import trampolines, see below) |
| Adapters own the memory contract: GC-pointer args read from the arena, side-effects written back at original addresses (I1) | **met, mechanically** |
| I2 reentrant case: a bridged adapter invokes a linked export through the worker's dispatch loop | **met** |
| Per-frame bridged-call ledger records every crossing (H2) | **met** |
| Adapters derived from Dolphin trace evidence (I1) | **NOT met** — pilot stand-ins, see "Honest gaps" |
| Frame-boundary arena compared against a DTM trace (I1 state evidence) | **NOT met** — checks are against a declared expectation |
| `run_main_game_loop` `boundary_green` and linked (H2 gate (a)) | **NOT met** — the whole remaining gap |
| Composed module drives the frames (H2 gate (b)) | **NOT met** — the host drives |
| Rung-0 units behaviourally verified against the relinked artifact | **NOT met** — suspended, see below |

## The two out-of-window edges

The gate's link leaves a composed module with exactly two kinds of edge out of
its window, and H2 says both are bridge edges:

1. **Table miss.** An address-keyed indirect call whose GC address is not in
   the companion's table. The companion routes it to the declared import
   `__gf_dispatch_miss(u32 gc_addr, i32 argptr)`. `@gf/rom-runtime`'s worker
   already bound this straight to the Atomics RPC bridge.
2. **Direct call to an unlinked callee.** A linked function calling an
   out-of-window symbol *by name*. emcc leaves these as ordinary function
   imports (`env.zz_0085e00_`, `env.gnt4_PSVECMag_bl`, …) with their **true C
   signatures**, not the companion's uniform `(i32 argptr) -> i32` shape. Before
   this pilot, the runtime threw `unshimmed import env.<x>` on all of them.

Edge 2 is closed by `packages/rom-runtime/src/composed.ts` +
`makeBridgeTrampolines` in `worker.ts`: the worker reads every imported
function's real signature out of the module's own type/import sections and
synthesizes a trampoline that marshals the call into a dispatch frame in shared
memory and hands it to the same bridge stub. Rung 0 declares **31** such
symbols; all 31 are bound, so no out-of-window call can escape the ledger. An
import that cannot be bound stays a loud composition error.

Symbol → ledger key uses the gate's own convention: `zz_<7 hex>_` spells its GC
address with the leading `8` nibble dropped (`zz_01b98ec_` == `0x801b98ec`),
`FUN_<8 hex>` spells it in full. SDK shim symbols (`gnt4_*`) have **no** GC
address, so they get a deterministic synthetic key in a reserved range
(`0x7F000000 | fnv1a(name) & 0xFFFFFF`) that can never collide with GC memory.
Synthetic keys are registry/ledger keys only and are never dereferenced;
`window.__gf.bridgeImports()` reports each symbol's `source` so the distinction
is visible, not buried.

## The driven window

`apps/game/src/rom/composedPilot.ts` drives two rung-0 table entries chosen
because between them they exercise every edge in one frame, plus one deliberate
miss:

```
zz_01b9b1c_ @ 0x801b9b1c        (unit auto-c0053-013, table entry)
    zz_0085e00_(p, p+0x20, 0);  -> DIRECT out-of-window call  (bridged)
    *(u8*)(p+0x18) = 2;         -> the module's own write into the arena
    zz_008aff0_(p);             -> DIRECT out-of-window call  (bridged;
                                   this is the REENTRANT adapter)
    *(u8*)(p+0x82) = 0;         -> the module's own write into the arena

zz_01b9b68_ @ 0x801b9b68        (same unit, table entry)
    q = *(int*)(p+0x90);
    if (*(s16*)(q+1000) == 0x407 && *(s8*)(q+0x150) == 1) {
        zz_006de10_(q, 2);      -> CONDITIONAL bridged call, gated on arena
        *(u8*)(q+0x150) = 0;       state the pilot seeds
    }
    ... then the same two writes and zz_008aff0_ again.

zz_0085e00_ @ 0x80085e00        dispatched DIRECTLY as an address: it is out of
                                window, absent from the 40-entry table, so it
                                takes the MISS path on purpose.
```

Five bridged crossings per frame, pinned in both the pilot and the smoke.

**The reentrant case is not a formality.** `zz_008aff0_`'s adapter, mid-service
on the main thread, asks the *parked* worker to run `__gf_dispatch` for
`zz_01b9be0_ @ 0x801b9be0` on the worker's own stack — the exact shape I2 exists
to keep from deadlocking. With `*(int*)(q+200) == 0` that function takes its
early exit, returning `-(short)(int)(FLOAT_8043ba9c * FLOAT_8043ba5c)`. The
pilot seeds those two GC floats with 14.0 and 3.0, so the expected answer is
**-42** — a value computed by the ROM's own compiled code from state the pilot
put in the arena, which a stub cannot fake by returning zero.

## Evidence surface

With `?composed=1` (or `?composed=<n>` for n frames) on the game page:

- `window.__gf.composedPilot()` — the gate's own record. Its first two fields are
  `behaviouralClaim` (always `NONE. ...` for this pilot) and `verified: false`,
  ahead of any number; then artifact sha256, rung, units, table size,
  shared-memory size, boot timings, the registered adapter roster, and per-frame
  results with every state check. The per-frame and overall verdicts are named
  `declaredChecksPass`, **not** `pass`: they say the pilot's own declared
  expectations held, which is a mechanism check and not a verification result.
- `<html data-gf-composed-pilot="synthetic-no-behavioural-claim">` — set as soon
  as the pilot boots, plus an on-screen banner, so a live page carrying pilot
  numbers cannot be mistaken for a normal run.
- `window.__gf.bridgeLedger()` — per-frame crossings, per-symbol totals,
  declared servicing errors (H2/I2).
- `window.__gf.bridgeAdapters()` — `{ behaviouralClaim, adapters }`. Each adapter
  carries its evidence string **and** an `evidenceClass` of `verified` or
  `synthetic`. `synthetic` adapters are refused by `AdapterRegistry` unless the
  host was opened with `admitSyntheticAdapters: true` — which only this pilot
  and the rom-runtime self-test do, so a stand-in cannot service a frame
  anywhere else.
- `window.__gf.bridgeImports()` — the **declared** boundary: all 31 symbols that
  *can* cross, with signature and address source. The adapter roster is the
  subset the ledger proves is *hit* (I1's work-queue relationship, visible).
- `window.__gf.composedRun(n)` / `window.__gf.composedShutdown()` — controls.

Headless proof: `node scripts/smoke-composed-pilot-phase.mjs` (or
`GF_SMOKE_COMPOSED_PILOT=1 node scripts/smoke-browser-game.mjs`). It builds the
real production bundle, serves it COOP/COEP-isolated, and drives **16 frames in
two batches**: 8 while the game is still loading assets, then — after the game
reports `boot-ready` and the smoke confirms `window.__gf.navigation.screen ===
"title"` — 8 more requested through `composedRun()`. The second batch is what
makes "driven from the game's frame loop in a real game context" an assertion
rather than a claim: those frames provably ran off the same render loop that was
drawing the live title screen. The phase then asserts all four proofs plus exact
per-frame *and* per-symbol crossing counts. Screenshot, console log and
ledger/pilot JSON land in `.tmp/composed-pilot-smoke/evidence/`.

Recorded run: 16/16 frames pass, 80 crossings (5/frame exactly), 0 servicing
errors, 31 declared bridged imports, 3 adapters — the ledger's per-symbol totals
(`8006de10`: 8, `80085e00`: 16, `8008aff0`: 16) isolate the conditional edge, the
miss-plus-direct edge, and the direct-only edge from each other.

## The 2GB shared-memory finding

The assembly gate links every module with
`-sINITIAL_MEMORY=2155479040 -sALLOW_MEMORY_GROWTH=0` — a fixed **0x807A0000**-byte
flat linear memory whose top is the GC arena at *original* addresses
(`0x80000000` …). **This is not a tuning knob.** Any smaller memory puts
`0x801b9b1c` out of bounds and breaks the entire flat-arena address model, so
"reduce it for the pilot" is not an available deviation.

Measured, and it did not need to be: a **shared** `WebAssembly.Memory` of
32,890 pages (2,155,479,040 B) instantiates fine in headless Chrome under
cross-origin isolation, and the allocation itself costs **~2 ms** — V8 reserves
the address space and commits lazily rather than touching 2GB up front. The
same allocation in Node is ~2 ms. Worker-side boot breakdown from the smoke's
own evidence: memory 2 ms, compile 2 ms, instantiate 1 ms, arena install 0 ms;
the ~2 s wall clock of `bootComposedModule` is the *worker module graph* (Vite
chunk fetch + parse), not the memory.

No deviation from the gate's link settings was needed or taken. The pilot's
module is the gate's own bytes plus exactly the two documented threads flags.

## Provenance of the served module

`apps/game/public/rom/composed-rung0.threads.wasm`, with
`composed-rung0.provenance.json` beside it (units, gate result and `checked_at`,
companion sha256, table size and full 40-entry dispatch table, link recipe, both
module hashes, memory model).

How it was produced — reproducible, entirely in scratch, never touching live
pipeline state and never taking the driver lock:

```
# 1. snapshot the live artifacts + canonical state into scratch
python scripts/composition_ladder.py init --scratch <dir>

# 2. re-run rung 0 as recorded in research/decomp/data/composition-ladder.json
python scripts/composition_ladder.py rung --scratch <dir> --tag rung0 \
    --units auto-c0054-000,auto-c0054-001,auto-c0054-002,auto-c0054-003,auto-c0053-013
#    -> passed, stage "pass", 40-thunk companion table, 0 conflicts
#    -> <dir>/workdir-rung0/assembly.wasm
#       sha256 3d80e6da10cb0b3ad95ac77f1cddd8bd87e937cfd2613eb090da66866a26e6cd

# 3. base-proof (docs/threads-relink-reverify.md step 1): rebuild from the
#    gate's own derived sources with its exact flags and byte-compare
#    -> byte-identical, same sha256

# 4. relink threads-target (step 2): SAME sources, SAME flags, plus exactly
#    -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1
#    -> assembly.threads.wasm
#       sha256 269ae98b0f4bc170294f4b59f20dc97dd8f4a3beb6dbd57b232a1351c1f3b5e1
```

The rung-0 gate result reproduced the committed ledger entry exactly — same 5
units, `stage: pass`, 40 companion functions, zero conflicts, and the same
companion sha256 `5f07b283ec20c5be3f74eceb96188f7c7f47b92c954108aebda3eae77d96ef7a`
as `research/decomp/data/composition-ladder.json` rung 0.

## Honest gaps

These are stated here rather than implied, because every one of them is a real
requirement the pilot does not satisfy.

1. **No behavioural claim.** `docs/threads-relink-reverify.md` **suspends** every
   unit's `oracle_green` / `boundary_green` status across a threads relink until
   its full corpus replays byte-equal against the relinked artifact. None of the
   five rung-0 units has had that pass, and the composed module has no corpus of
   its own. The artifact is compile/link-only inventory. The provenance file
   says so in its own `verification_status` field, and the game logs it at boot.
2. **The adapters are not I1-valid.** I1 requires each adapter to be derived
   from the same Dolphin trace evidence as ports, reproducing the callee's
   captured per-call write set. No DTM capture exists for `zz_0085e00_`,
   `zz_008aff0_` or `zz_006de10_`. Two are hand-written pilot stubs whose
   `evidence` string says exactly that; the third runs the real
   `TraceDeltaAdapter` class against a **synthetic** fixture
   (`composed-rung0.pilot-fixture.json`), which proves the *mechanism* — recorded
   per-call write sets applied in lockstep, exhaustion raising a declared
   servicing error — and proves nothing about what the ROM writes.
3. **The frame-boundary state check is not state evidence.** I1's gate compares
   the arena against a Dolphin trace of the same DTM at the same frame boundary.
   The pilot compares it against a **declared expectation** written next to the
   code. It catches a broken bridge; it cannot catch a wrong port.
4. **The arena state is synthetic.** The pilot stands up an actor/target pair in
   otherwise-unused GC scratch (`0x80500000`, proven empty at boot) because there
   is no live game object to point rung-0 code at. R2 already says
   adapter-serviced frames are DTM-replay frames, not interactive play; these
   frames are not even that — they are *pilot* frames.
5. **The ledger's `dtm-replay` mode label is mechanical.** `BridgeLedger` marks a
   frame `dtm-replay` as soon as any bridge crossing happens. In this pilot that
   means "adapter-serviced", and there is no DTM pinned behind it.
6. **The remaining distance to control inversion is the whole H2 prerequisite
   chain**, unchanged by this work: `run_main_game_loop` must reach
   `boundary_green` over K owner-approved iterations (I3), the ladder must grow
   far enough to link it and its spine into the window (G3/E1 — currently
   **stopped at rung 1** on a rising contested-symbol ratio pending ABI
   unification), and the frames it then drives must pass I1 state evidence
   against an owner-supplied DTM. This pilot moves none of those; it proves the
   machinery those frames would run on.

## File map

| Path | Role |
| --- | --- |
| `packages/rom-runtime/src/composed.ts` | module-shape parsing, symbol→address authority, bridged-import planning, scratch-region layout |
| `packages/rom-runtime/src/worker.ts` | per-import bridge trampolines; boot timings |
| `packages/rom-runtime/src/protocol.ts` | `bridgeAllImports` init fields; `bridgedImports` + `timings` in ready |
| `packages/rom-runtime/src/host.ts` | passes the new options through; `bridgedImports` / `bootTimings`; `window.__gf.bridgeImports()` |
| `apps/game/src/rom/composedWorker.ts` | the Vite worker entry |
| `apps/game/src/rom/composedPilot.ts` | the pilot: driven window, adapters, per-frame state checks |
| `apps/game/src/rom/composedBoot.ts` | fetch + boot + arena install + controls + frame hook |
| `apps/game/src/main.ts` | `?composed=` opt-in; one `onComposedGameFrame()` call in `tick()` |
| `apps/game/public/rom/composed-rung0.threads.wasm` | the served composed module |
| `apps/game/public/rom/composed-rung0.provenance.json` | its provenance |
| `apps/game/public/rom/composed-rung0.pilot-fixture.json` | the synthetic trace-delta fixture |
| `scripts/smoke-composed-pilot-phase.mjs` | the headless gate |
| `scripts/smoke-browser-game.mjs` | one opt-in import line at the end |
