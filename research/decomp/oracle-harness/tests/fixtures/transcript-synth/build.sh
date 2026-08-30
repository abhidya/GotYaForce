#!/usr/bin/env bash
# build.sh — rebuild the transcript-synth self-test wasm fixtures with the
# repo's pinned emsdk (research/tools/emsdk), mirroring
# ../spine-synth/build.sh exactly. The compiled .wasm files are COMMITTED (like
# port-units/*/unit.wasm) so the oracle test suite runs on a clean checkout
# without the toolchain; rerun this only when a .c fixture changes, and commit
# the rebuilt binaries with it.
#
# Windows (no bash/emsdk_env): invoke emcc.py under the bundled python instead:
#   research/tools/emsdk/python/3.13.3_64bit/python.exe \
#     research/tools/emsdk/upstream/emscripten/emcc.py <same args>
set -e
cd "$(dirname "$0")"
source ../../../../../tools/emsdk/emsdk_env.sh >/dev/null 2>&1

# The synthetic arena is a single i32 at 0x104000, so 16MB (256 pages) is plenty
# and keeps the committed fixture instantiation cheap in tests.
FLAGS="-O1 -fno-strict-aliasing --no-entry -sERROR_ON_UNDEFINED_SYMBOLS=0 \
  -sINITIAL_MEMORY=16777216 -sALLOW_MEMORY_GROWTH=0 \
  -sEXPORTED_FUNCTIONS=_fn_nowrite,_fn_vacuous"

emcc transcript_synth.c            $FLAGS -o transcript_synth.wasm

# Mutants: induced-failure proofs for run-transcript.mjs. A verifier that cannot
# fail is worse than none, so each divergence CLASS the standard claims to catch
# has its own mutant.
emcc transcript_synth_badorder.c   $FLAGS -o transcript_synth_badorder.wasm
emcc transcript_synth_badarg.c     $FLAGS -o transcript_synth_badarg.wasm
emcc transcript_synth_badret.c     $FLAGS -o transcript_synth_badret.wasm
emcc transcript_synth_extracall.c  $FLAGS -o transcript_synth_extracall.wasm

ls -la ./*.wasm
