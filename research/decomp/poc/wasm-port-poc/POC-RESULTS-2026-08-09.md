# POC RESULTS — Ghidra-C → wasm port, oracle-gated (2026-08-09)

Execution of HANDOFF-2026-08-09 §5, run E2E with zero human/semantic edits to the
ported code. Verdict: **PASS** on every §5 criterion. Model-tier loops (§5 optional
experiment, owner-requested): see §6 (filled as runs complete).

## 1. What was built (all NEW files, no living files edited)

| File | Role |
|---|---|
| `build.sh` | sed-extracts the VERBATIM Ghidra C + compiles with emcc (provably untouched bodies) |
| `gnt4_shim.h` | stage-2 scaffold: typedefs, arena-address macros, CONCAT44 bit-cast, cntlzw, SDK externs |
| `gen_arena.py` | stage-2 arena: boot.dol → byte-order-converted table image at ORIGINAL GC addresses |
| `harness.mjs` | oracle diff driver: same corpus into wasm + sourceDamage.ts, byte-compare |
| `verify_tables.mjs` / `probe.mjs` / `probe2.mjs` | diagnosis tools (table compare, 1-D sweeps, delta-debug) |
| `poc-run.js` + `smoke-browser-wasm-poc.mjs` | browser step: real game app + wasm in the same page |
| `model_loop.py` | model-tier compile-fix loop (35B vs 27B) |

Ported verbatim: `zz_003cd5c_` (damage formula, chunk_0004.c:6667-6828),
`zz_003d344_` (HP subtract+clamp, 6832-6860), `zz_0066298_` (type category,
chunk_0008.c:2976-2982) = Unit A; `FUN_80031634` (chunk_0004.c:202-231, 3 distinct
`gnt4_PSVEC*/PSQUAT*` SDK calls) = Unit B.

Toolchain: emsdk 6.0.6 installed to `research/tools/emsdk` (self-contained checkout,
no PATH/system changes). Memory model: single 2,055 MiB wasm32 linear memory; all
DOL data lives at its ORIGINAL GameCube addresses (0x802xxxxx/0x804xxxxx), so even
raw pointer literals in the decompiled C (`-0x7fd3a2a0` = the 0x802c5d60 type matrix)
work unmodified. Byte order converted once, at arena generation (design §4 rule).

## 2. §5 pass criteria — all met

| Criterion | Result |
|---|---|
| Compile-fix converged, zero semantic/human edits to code | **2 iterations** (`bool` → add `<stdbool.h>` to scaffold header; C bodies untouched) |
| Corpus outputs match oracle; float diffs eliminated or explained | **19,998/20,000 exact; 2/2 residuals proven f32-rounding** (wasm == float32-instrumented reference); 0 unexplained |
| Sub-oracles | type category 232/232; HP subtract+clamp incl. lethal flag 4,000/4,000 |
| Shims linked (SDK seam) | Unit B **2,000/2,000 exact** (bool + out-vector bytes) via 3 JS-shimmed SDK fns |
| Runs in the actual browser app | **PASS**: headless Chrome, real game booted (`data-gf-runtime=loaded`, `window.__gf` live, 40 stages), wasm instantiated in-page, 32/32 snapshot cases exact |

## 3. Go/no-go metrics (§5)

- **Compile-fix iterations/unit: 2** (scaling cost ≈ negligible for family-shaped units).
- **Output parity: 100%** of diffs eliminated (99.99% exact) or proven-rounding (0.01%).
- **Shim calls/unit (seam load): 4.02/case** across 3 SDK functions (Unit B); Unit A
  needs zero SDK imports. Seam overhead is real but small.

## 4. Findings the POC surfaced (each worth owner attention)

1. **The TS oracle's data is decimal-rounded.** `damageFormula.json` stores `1.02`
   (f64) where the DOL stores f32(1.02) = `1.0199999809…`. The ROM multiplies by the
   f32; the shipped TS multiplies by the f64. Same for `comboRankScale` etc. The wasm
   path is bit-faithful by construction; the TS path carries a systematic (tiny)
   representation drift. This is exactly the class of drift the recomp trunk removes.
2. **Oracle gate deviations found (documented, benign in-domain):** the TS oracle
   applies status-immunity and the /40 guard without the ROM's `defender[0x83]==0`
   (is-a-borg) gate, and clamps curve indices where the ROM reads out-of-table for
   out-of-domain inputs (hp>maxHp). In-game inputs can't hit these; a future caller
   passing summarized ctx for a non-borg defender could. Noted in-code in the POC.
3. **Per-team shared state is a corpus-modeling trap:** side rank and side energy are
   one-slot-per-team; any test generator giving same-team actors different values
   silently produces impossible inputs (cost one diagnosis cycle here).
4. **The current `apps/game/dist` does not pass the stock browser smoke**: it is
   built with the GH-Pages base (`/GotYaForce/game/…`) which
   `scripts/smoke-browser-game.mjs` does not map → readiness signal never appears.
   The POC smoke maps the prefix; the stock smoke needs the same fix (or a fresh
   root-base build) — confirms the handoff's "smoke gate is weak" item, and worse:
   it currently FAILS, so nothing is gating browser boot at all.
5. **wasm-side gotchas confirmed and one-line-solvable:** i32 pointers arrive in JS
   shims SIGNED (must `>>> 0`); borgNumber u16 at +1000 must keep PPC byte order at
   the data boundary; `undefined8`-as-double + CONCAT44-as-bit-reinterpret belongs in
   the common header once.

## 5. Iteration ledger (full honesty trail)

| # | Change | Class |
|---|---|---|
| 1 | emcc: `bool` unknown → `#include <stdbool.h>` in scaffold header | syntactic scaffold |
| 2 | build OK, harness run 1: 87.2% | — |
| 3 | corpus fix: hp ≤ maxHp (ROM reads OOB for impossible inputs) | corpus domain |
| 4 | table verify: arena==JSON only after fround → finding §4.1 | diagnosis |
| 5 | corpus fix: same-team shared sideRank (finding §4.3) → 98.2% | corpus domain |
| 6 | corpus fix: immunity/guard ctx only for borg defenders (finding §4.2) → 99.99% + 2 proven-rounding, 0 unexplained | corpus domain |

Zero edits to the extracted C at any point. All fixes were in test-input generation
or the generated scaffold.

## 6. Model-tier experiment (owner-requested: run loop with 35B and untried 27B)

Protocol: same verbatim C; scaffold header degraded by removing exactly the four
definitions the human loop had to supply (stdbool, CONCAT44, countLeadingZeros, ABS);
model iterates against exact emcc errors (max 8); linked wasm then faces the same
20k oracle corpus. CONCAT44 is the tier discriminator: a numeric-conversion definition
compiles clean but fails the oracle — which is why stage 4 exists.

| Run | Linked (iters) | Oracle corpus | Wall time |
|---|---|---|---|
| Claude (baseline) | 2 | 19,998 exact + 2 proven-rounding / 20,000 | minutes |
| Qwen3.6-35B-A3B UD-Q4_K_XL | 2 (after link-gate added; first pass left CONCAT44 as a rogue env import) | **REJECTED: 1,495/20,000 (7.5%)** — defined CONCAT44 as numeric u64 concat despite the correct spec sitting in the header comment above it; CONCAT44-free sub-units perfect (232/232, 4,000/4,000, 2,000/2,000) | 500s + 346s |
| ↳ 35B attempt 3 (independent sample, temp 0.6; the planned oracle-feedback round mis-fired — model_loop.py runs its loop at import, so this is a fresh plain-loop sample) | 2 | **PASS: 19,998 exact + 2 proven-rounding / 20,000** — wrote the correct union bit-cast CONCAT44 this time; all sub-units perfect | 465s |
| Qwen3.6-27B-MTP UD-Q4_K_XL, thinking ENABLED, 262k ctx (first time this model was ever run) | 3 iters / 2 model calls | **PASS on first linked build: 19,998 exact + 2 proven-rounding / 20,000**; all sub-units + Unit B perfect | 4,038s + 2,947s (~116 min; CPU-bound at 262k-ctx KV) |

**The reasoning answer (owner's question):** the thinking 27B derived the hard semantic
unprompted — its stream literally reasoned "On wasm (LE), we swap array order to
preserve the original 64-bit pattern when reinterpreted as double" and emitted the
correct union bit-cast CONCAT44 with the endian swap — the exact construction the
muted 35B got wrong in 2 of 3 samples with the spec in front of it. Its one miss was
trivial (forgot ABS; stream shows it got cut off mid-checklist), which the link gate
fixed in one cheap round. Division of labor confirmed: gates catch trivial misses,
reasoning carries semantics. Cost: ~35-67 min/call at 262k ctx on this rig (CPU-bound
KV spill); a right-sized context would recover most of that.

Ops findings from the 27B campaign (each cost a debugging cycle, all now handled in
model_loop.py or documented): JIT model reload silently resets context to 4096 (the
`max_context_length` field lies BOTH ways); the server keeps generating for
disconnected clients — a 79-minute zombie request hogged the single slot until
force-unload (pipeline needs cancel-on-abandon); SSE error events arrive in-band and
must be raised, not skipped; streaming sends no bytes until first token, so read
timeouts must cover full CPU prefill; cp1252 consoles crash on model emoji.

**The model-tier answer in one line:** across 3 sampled 35B attempts — one rogue-import
(caught by the link gate), one semantically wrong (caught by the oracle), one FULLY
CORRECT — the 35B can produce oracle-green units, but only probabilistically (~1/3 here);
the objective gates are what convert that into a reliable pipeline (retry-until-green),
exactly the design's premise. Log-review rating of the 35B: syntactic fixing 9/10,
semantic fidelity 3/10, instruction-following 2/10 (wrote the definition its own retained
comment forbids), speed 5/10 (~170s/call small prompts, ~9.6min/call at pipeline scale).

**Model-tier lessons already banked:**
- "Make this C compile" is within the 35B's reach (2 iterations, correct stdbool/clz/ABS fixes).
- Semantic fidelity is NOT: it chose the numerically-wrong CONCAT44 with the right answer
  written directly above it. The oracle gate (stage 4) is what catches this — never trust
  link success (Chromatron finding reproduced locally).
- Pipeline hardening discovered: `-sERROR_ON_UNDEFINED_SYMBOLS=0` must be paired with a
  post-link import whitelist (gnt4_* only). The 35B's first unit "linked" with its missing
  CONCAT44 silently converted into a wasm env import — a stub would have zeroed damage
  quietly. This gate is now in model_loop.py and belongs in the real pipeline.

## 7. Reproduce

```bash
cd research/decomp/poc/wasm-port-poc
bash build.sh          # verbatim extraction + emcc → unit_poc.wasm
python gen_arena.py    # boot.dol → arena.json
node harness.mjs 20000 # oracle diff
node smoke-browser-wasm-poc.mjs  # browser step (real app + wasm in-page)
python model_loop.py 35b "unsloth/Qwen3.6-35B-A3B-MTP-GGUF"
POC_WASM=model-run-35b/unit_model.wasm node harness.mjs 20000
```
