# Threads-target relink + Stage-B re-verification (design v5 step 8)

The pass every verified unit follows when it is relinked for the shared-memory
composed module. Governing principle (docs/playable-port-design.md, V4 H1,
"verified-bytes"): **the threads relink changes module bytes versus what Stage B
verified, so every `oracle_green` / `boundary_green` status is SUSPENDED until
the unit's full corpus replays byte-equal against the relinked artifact.** A
compile-only threads build is inventory, not progress; no composed-module claim
may cite pre-relink verification.

Pilot: damage-core, 2026-08-26 — see
`research/decomp/data/oracle-results/damage-core.threads.json` for the recorded
run this document generalizes.

## 0. Preconditions

- The unit is currently verified: a `pass` artifact exists under
  `research/decomp/data/oracle-results/<unit>.json`.
- The pinned toolchain is present: `research/tools/emsdk` (emcc 6.0.6,
  `ce75e06884093bcefb86a6b8fd56a5d62a4cc245`). On Windows invoke it as
  `research/tools/emsdk/python/3.13.3_64bit/python.exe
  research/tools/emsdk/upstream/emscripten/emcc.py <args>`.
- The harness supports imported shared memory
  (`research/decomp/oracle-harness/lib/wasm.mjs` `importedMemoryLimits` +
  the `env.memory` path in `loadUnit`; fixture proof:
  `oracle-harness/tests/fixtures/spine-synth/spine_synth.threads.wasm`).

## 1. Reproduce the ORIGINAL build first (base-proof gate)

Rebuild the unit from its committed source with its exact recorded flags and
**byte-compare** (`cmp`) against the committed `unit.wasm`.

- Byte-identical → the recipe is proven; proceed.
- Any drift → **STOP.** Do not relink on a divergent base; report the drift.
  A relink from an unproven recipe silently unverifies the unit.

For damage-core the recipe is `research/decomp/poc/wasm-port-poc/build.sh`:

```
emcc unit_poc.c -O1 -fno-strict-aliasing --no-entry \
  -Wno-implicit-function-declaration -Wno-int-conversion \
  -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=2155479040 -sALLOW_MEMORY_GROWTH=0 \
  -sEXPORTED_FUNCTIONS=_zz_003cd5c_,_zz_003d344_,_zz_0066298_,_FUN_80031634 \
  -o unit_poc.wasm
```

Result 2026-08-26: byte-identical
(`3de9a52a61ecfcd416fd89dae049e9e42f214100bca51b31ef0cafdbcb1e25f5`).

## 2. Relink with the threads flags

Same command, same source, ADD exactly:

```
-sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1
```

and output `<unit>.threads.wasm` (never overwrite the verified module). This is
threads-target codegen (atomics memory model, `env.memory` imported as a shared
`WebAssembly.Memory`) **without** the pthread JS runtime, whose `wasi_*` imports
are outside the harness's env-only shim contract. The module now declares its
memory in the import section (for damage-core: initial=maximum=32890 pages,
shared) and additionally exports `_initialize` / stack helpers — memory-init
runs via the wasm start section, so neither the harness nor the browser loader
calls `_initialize`; instantiation semantics stay identical to the verified
path.

## 3. Re-verify: full-corpus replay against the relinked module

Run the unit's FULL corpus through the standard harness entry; `loadUnit`
auto-detects `env.memory`, reads the declared limits out of the binary import
section, and constructs the shared memory host-side:

```
# same-checkout baseline (fresh replay of the verified module)
ORACLE_RESULTS_DIR=<scratch-a> node run-unit.mjs --unit <unit>
# threads candidate
ORACLE_RESULTS_DIR=<scratch-b> ORACLE_WASM=<path>/<unit>.threads.wasm node run-unit.mjs --unit <unit>
```

**Requirement — byte-identical verdict:** diff the two result artifacts; the
ONLY permitted differences are `generated_at`, `wasm.path`, `wasm.sha256`.
Per-function `exact` / `rounding_explained` / `unexplained` counts, the
coverage block, and the corpus identity must match exactly (same
explained-rounding set, all pass). Anything else is a red: the relink changed
behavior and the unit stays suspended.

Record the outcome as `research/decomp/data/oracle-results/<unit>.threads.json`:
the threads run's result artifact plus a `relink` block carrying **both module
sha256s**, the added flags, the toolchain id, the declared imported-memory
limits, the base-reproduction proof, and the verdict-delta statement. The
original `<unit>.json` stays untouched — the exported-memory verdict remains
the verdict of record for the exported-memory module.

Damage-core result 2026-08-26: 26,232/26,232 replayed, verdict PASS,
verdict-delta none (19998+2/20000, 232/232, 4000/4000, 2000/2000), threads
module `9ba2c4c082d8729c87c432b6d1c1a123b9509c5b334272c994f4aba594b31044`.

## 4. Browser proof under COI

The relinked module must serve the real game, not just the harness:

- The loader (`packages/combat/src/rom/wasmDamageCore.ts`) mirrors the
  harness: it detects `env.memory` in the module's import section, parses the
  declared limits from the binary, constructs the shared `WebAssembly.Memory`,
  and otherwise leaves the exported-memory path untouched.
  `RomDamageCore.memoryInfo` reports `{imported, shared}` as the proof surface.
- Variant selection: `?romwasm=threads` fetches
  `rom/<unit>.threads.wasm` (`apps/game/src/sim/romDamageBoot.ts`); the
  exported-memory module stays the default. **Switching the default is a
  separate reviewed decision.**
- Smoke: `GF_SMOKE_ROMWASM=threads GF_SMOKE_ROM_HIT=1 node
  scripts/smoke-browser-game.mjs` drives the whole playable route with
  `?romwasm=threads` under the COOP/COEP serving path, asserts
  `window.__romDamage` is live **with imported shared memory**
  (`memoryInfo.imported && memoryInfo.shared` — shared instantiation is only
  possible when `crossOriginIsolated` holds), and lands a real hit whose damage
  the threads module computes. The H1 COI phase at the end of the smoke
  continues to assert `window.crossOriginIsolated === true` in both serving
  modes.

## 5. What this pass does NOT do

- It does not replace the production `rom/<unit>.wasm`; the threads module is
  committed under the distinct `.threads.wasm` name beside it.
- It does not re-green anything else: each verified unit needs its OWN pass —
  base-proof, relink, full-corpus replay, `.threads.json` artifact — before its
  suspension lifts for the composed-module lane.
