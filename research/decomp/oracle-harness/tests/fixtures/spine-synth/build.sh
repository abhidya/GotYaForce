#!/usr/bin/env bash
# build.sh — rebuild the spine-synth self-test wasm fixtures with the repo's
# pinned emsdk (research/tools/emsdk), mirroring the sdk-shims lane's compile
# method (research/decomp/generated/pi-port/sdk-shims/README.md "Build / test").
# The compiled .wasm files are COMMITTED (like port-units/*/unit.wasm) so the
# oracle test suite runs on a clean checkout without the toolchain; rerun this
# only when a .c fixture changes, and commit the rebuilt binaries with it.
#
# Windows (no bash/emsdk_env): invoke emcc.py under the bundled python instead:
#   research/tools/emsdk/python/3.13.3_64bit/python.exe \
#     research/tools/emsdk/upstream/emscripten/emcc.py <same args>
set -e
cd "$(dirname "$0")"
source ../../../../../tools/emsdk/emsdk_env.sh >/dev/null 2>&1

# Common shape mirrors poc/wasm-port-poc/build.sh; the synthetic arena lives at
# 0x104000-0x104007, so 16MB (256 pages) is plenty and keeps the committed
# fixture instantiation cheap in tests.
FLAGS="-O1 -fno-strict-aliasing --no-entry -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=16777216 -sALLOW_MEMORY_GROWTH=0 -sEXPORTED_FUNCTIONS=_spine_main"

# Exported-memory build (the Stage-B status quo the harness already supports).
emcc spine_synth.c $FLAGS -o spine_synth.wasm

# Threads-target build: IMPORTS env.memory declared shared (the step-8 shape).
# -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1 gives threads-target codegen (atomics,
# shared imported memory) without the pthread JS runtime, whose wasi_* imports
# are out of the harness's env-only contract.
emcc spine_synth.c $FLAGS -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1 -o spine_synth.threads.wasm

# Mutants (exported memory): induced-failure proofs for run-spine.mjs.
emcc spine_synth_badorder.c $FLAGS -o spine_synth_badorder.wasm
emcc spine_synth_badwrite.c $FLAGS -o spine_synth_badwrite.wasm

ls -la ./*.wasm
