# pi-port / sdk-shims

Portable-C implementations of the gnt4_* SDK seam declared in
`research/decomp/generated/finish-game-port/gnt4_shim_seed.h`.

## Provenance

- Authored by the LOCAL model `unsloth/Qwen3.8-27B-GGUF` driven through the
  `pi` coding agent (pi 0.84.3) as an agentic harness. The harness supplied
  prototypes, build commands, and compile/test error feedback; the model wrote
  the C.
- Status: **UNREVIEWED — NOT INTEGRATED.** Nothing here is wired into the
  port driver, the assembly gate, or any composed module. Integration is an
  owner/orchestrator decision after review.

## Layout

- `gnt4_sdk_shim.h` — typedefs + EXACT prototypes copied verbatim from the
  seed header (no arena/address macros; shims must not touch GC addresses).
- One `.c` file per symbol family (`psvec.c`, `psquat.c`, `psmtx.c`, ...),
  plus `test_<family>.c` self-tests exercising known identities.
- `LEDGER.md` — per-function status: implemented / compiled / self-tested,
  plus semantics-uncertainty notes.

## Semantics reference

PSMTX/PSVEC/PSQUAT follow public libogc / Dolphin SDK semantics: row-major
3x4 matrices (`f32 m[3][4]`), paired-single math treated as plain float.
Prototypes are the Ghidra-derived corpus prototypes (floats promoted to
double, PPC float-args-first ordering), NOT the original SDK prototypes; the
mapping between the two is documented per function in `LEDGER.md`.

## Build / test

Compiled and self-tested with the repo's pinned emsdk toolchain
(`research/tools/emsdk`): `emcc` compile, tests run under the bundled node
(wasm). Example:

    python research/tools/emsdk/python/3.13.3_64bit/python.exe \
      research/tools/emsdk/upstream/emscripten/emcc.py \
      psvec.c test_psvec.c -O1 -fno-strict-aliasing -o test_psvec.js
    research/tools/emsdk/node/24.19.0_64bit/node.exe test_psvec.js
